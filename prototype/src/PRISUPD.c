/***************************************************************************
                          PRISUPD.c  -  description
                             -------------------
    Version		 : 0.1
    begin                : Tis 24 jan 2006
    modified		 :
    copyright            : (C) 2006 by Jan Pihlgren
    email                : jan@pihlgren.se
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *********************************************** ****************************/

/*
	INPUT: inputfilename,pricelisttype

	Kommando:  $HOME/tmp/loadfile.tmp A

	Function: Uppdatera tabellen PRISLISTA eller ARTIKELREG.ARFPRIS

	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/PRISUPD.c,v 1.1 2006/01/29 08:14:29 janpihlgren Exp $ " ;

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "mysql.h"

#define FORMAT_STR "%Y-%m-%d_%H:%M:%S"    /* YYYY-MM-DD */
#define MAXSIZE 20
#define MAXSTRING 5000
#define TEXTSIZE 500
#define ANTARG 3
#define ANTFELT 13
/* ANTFIELD = antal prislistor */
#define ANTFIELD 15
#define FIELDLEN 50

  MYSQL my_connection;
  MYSQL_RES *res_ptr;
  MYSQL_ROW sqlrow;

  int which_database(char *envp[]);
  void extractField(char *inrad);
  int doSql(char *sqlCommand);

  char database[15]="";

  char databas[25]="olfix";
  char ut[ANTFIELD][FIELDLEN];
  char infilename[100]="";
  char tmp[2000]="";

int main(int argc, char *argv[], char *envp[])
{
  int status;
  char pricelist[3]="";

  const char *userp = getenv("USER");	/* vem är inloggad?	*/
  char usr[15]="";			/* userid		*/

  char temp0a[]="UPDATE IGNORE ARTIKELREG SET ARFPRIS = \"";
  char temp0b[]="\" WHERE ARTIKELNR = \"";
  char temp2[]="\"";
  char temp3[]=",";	/* kommatecken */ 
  char temp5[TEXTSIZE]="";

  char temp1a[]="UPDATE IGNORE PRISLISTA SET";
  char temp1a1[]=" PRIS1 = \"";
  char temp1a2[]=" PRIS2 = \"";
  char temp1a3[]=" PRIS3 = \"";
  char temp1a4[]=" PRIS4 = \"";
  char temp1a5[]=" PRIS5 = \"";
  char temp1a6[]=" WHERE ARTIKELNR = \"";

  char artikelnr[31]="xx";
  char fpris[14]="0.00";
  char pris1[14]="0.00";
  char pris2[14]="0.00";
  char pris3[14]="0.00";
  char pris4[14]="0.00";
  char pris5[14]="0.00";
  
  char kommando[200]="";		/* Används för systemkommando */

  strncpy(infilename,argv[1],sizeof(infilename));
  /* 	fprintf(stderr,"PRISUPDmain: temp5=%s\n",temp5);	*/
  strncpy(pricelist,argv[2],sizeof(pricelist));
  fprintf(stderr,"infilename=%s pricelist=%s\n",infilename,pricelist);

  status=-15;
  /* ================================================================================ */
  /* 		Val av databas, START						    */
  /* ================================================================================ */

  status = which_database(envp);

  if (status != 0){
	exit(status);
  }
  strncpy(usr,userp,15);			/* Den inloggades userid	*/
  /*  fprintf(stderr,"status=%d ANTARG=%d len(database)=%d\n",status,ANTARG,strlen(database));	*/
  if (argc < ANTARG+1){
    	if (strlen(database)!= 0){
		strncpy(databas,database,15);
	}else{
  		strncpy(databas,"olfixtst",15);	/* olfixtst = testföretag	*/
	}
  }else{
	if (strlen(argv[ANTARG]) != 0){
  		if (strncmp(argv[ANTARG],"99",2)==0){
			strncpy(databas,"olfixtst",15);
		}else{
  			strncpy(databas,argv[ANTARG],15);
  		}
  	}
  }

  /* Om usr (userid) börjar på 'test' eller 'prov' använd databas 'olfixtst' */
  if (strncmp(usr,"test",4)==0 || strncmp(usr,"prov",4)==0 ) {
  	strncpy(databas,"olfixtst",15);
  }
  /* fprintf(stderr,"Databas=%s\n",databas);		*/
  /* ================================================================================ */
  /* 		Val av databas, END!						    */
  /* ================================================================================ */

  /* ================================================================================ */
  /* 		Läsa infilen (loadfile.tmp!					    */
  /* ================================================================================ */
  char inrad[200];
  char *inpek;
  inpek = &inrad[0];

  FILE *infile;
  infile = fopen(infilename,"r");
  while (fgets(inrad,150,infile) != NULL){
  /*      prisrad ser ut på följande sätt:  1000-1001;132.00	*/
  /*      fältavskiljare = ;				*/
  /*	1000-1001 kan innehålla upp till 30 tecken	*/
  /*	132.00 kan inne hålla 10 heltal och 2 decimaler	*/
		extractField(inpek);
  /*		fprintf(stderr,"ut[0]=%s\n",ut[0]);		*/

		strcpy(temp5,"");				/* Nollställ temp5 */
		strcpy(artikelnr,ut[0]);

		if (strncmp(pricelist,"F",1)==0){
			strcpy(fpris,ut[1]);
			strncpy(temp5,temp0a,sizeof(temp0a));
			strncat(temp5,fpris,sizeof(fpris));
			strncat(temp5,temp0b,sizeof(temp0b));
  			strncat(temp5,artikelnr,sizeof(artikelnr));
			strncat(temp5,temp2,sizeof(temp2));
  		}else{
			strcpy(pris1,ut[1]);
			strcpy(pris2,ut[2]);
			strcpy(pris3,ut[3]);
			strcpy(pris4,ut[4]);
			strcpy(pris5,ut[5]);
			strncpy(temp5,temp1a,sizeof(temp1a));
			if (strncmp(pricelist,"A",1)==0){
				strncat(temp5,temp1a1,sizeof(temp1a1)); /* PRIS1*/
				strncat(temp5,pris1,sizeof(pris1));
  				strncat(temp5,temp2,sizeof(temp2));
				strncat(temp5,temp3,sizeof(temp3));
  				strncat(temp5,temp1a2,sizeof(temp1a2)); /* PRIS2*/
  				strncat(temp5,pris2,sizeof(pris2));
				strncat(temp5,temp2,sizeof(temp2));
				strncat(temp5,temp3,sizeof(temp3));
  				strncat(temp5,temp1a3,sizeof(temp1a3)); /* PRIS3*/
  				strncat(temp5,pris3,sizeof(pris3));
				strncat(temp5,temp2,sizeof(temp2));
				strncat(temp5,temp3,sizeof(temp3));
  				strncat(temp5,temp1a4,sizeof(temp1a4)); /* PRIS4*/
  				strncat(temp5,pris4,sizeof(pris4));
				strncat(temp5,temp2,sizeof(temp2));
				strncat(temp5,temp3,sizeof(temp3));
  				strncat(temp5,temp1a5,sizeof(temp1a5)); /* PRIS5*/
  				strncat(temp5,pris5,sizeof(pris5));
				strncat(temp5,temp2,sizeof(temp2));
			}
			if (strncmp(pricelist,"1",1) == 0){
			strncat(temp5,temp1a1,sizeof(temp1a1)); /* PRIS1*/
			strncat(temp5,pris1,sizeof(pris1));
  			strncat(temp5,temp2,sizeof(temp2));
	 		}
			if (strncmp(pricelist,"2",1) == 0){
			strncat(temp5,temp1a2,sizeof(temp1a2)); /* PRIS1*/
			strncat(temp5,pris2,sizeof(pris2));
  			strncat(temp5,temp2,sizeof(temp2));
 			}
			if (strncmp(pricelist,"3",1) == 0){
  				strncat(temp5,temp1a3,sizeof(temp1a3)); /* PRIS3*/
  				strncat(temp5,pris3,sizeof(pris3));
				strncat(temp5,temp2,sizeof(temp2));
 			}
			if (strncmp(pricelist,"4",1) == 0){
  				strncat(temp5,temp1a4,sizeof(temp1a4)); /* PRIS4*/
  				strncat(temp5,pris4,sizeof(pris4));
				strncat(temp5,temp2,sizeof(temp2));
 			}
			if (strncmp(pricelist,"5",1) == 0){
  				strncat(temp5,temp1a5,sizeof(temp1a5)); /* PRIS5*/
  				strncat(temp5,pris5,sizeof(pris5));
				strncat(temp5,temp2,sizeof(temp2));
 			}
			strncat(temp5,temp1a6,sizeof(temp1a6)); /* ARTIKELNR*/
			strncat(temp5,artikelnr,sizeof(artikelnr));
			strncat(temp5,temp2,sizeof(temp2));

  		}
/*  		fprintf(stderr,"temp5=%s\n",temp5);	*/
		doSql(temp5);
	}
	fclose(infile);
	strncpy(kommando,"rm ",4);
	strncat(kommando,infilename,sizeof(infilename));
/*	fprintf(stderr,"kommando=%s\n",kommando);		*/
	system(kommando);				
	fprintf(stdout,"OK: Uppdatering klar!\n");
/*	exit(0); */
	return EXIT_SUCCESS;
}

void extractField(char *inrad)
{
/*
Jari Kanerva. jari.kan@comhem.se

Version 2 accepterar att raden inte börjar eller slutar med ';' Vilket är bättre tycker jag. 
Dessutom hanterar den tomma fält ";;". Den hanterar max 15 fält, "j < 15" kan ändras annars.(ANTFIELD) 
Och fälten får inte vara längre än 50 tecken. Det kan du också ändra om du vill "i < 49". (FIELDLEN -1)
Sen innehåller ut[0] första fältet, ut[1] andra osv.

Observera att jag deklarerade ut[15][50] som en global variabel för att jag inte kom ihåg hur jag skulle deklarera den i funktionsanropet.
*/
char *ptr1, *ptr2;
int i, j = 0;
   for(i = 0; i < ANTFIELD; i++)
       ut[i][0] = '\0';  	/* Nolla varje fält för att kunna se vilka som inte använts	*/
     if(inrad[0] != ';')  	/* Om inte raden börjar med ';' tar vi det första fältet här.	*/
   {
       for(i = 0; inrad[i] != ';' && inrad[i] != '\n' && inrad[i] != '\0' && i < FIELDLEN-1; i++)
           ut[j][i] = inrad[i];
       ut[j++][i] = '\0';
   }
     ptr1 = strchr(inrad, ';');
   while(ptr1[1] != '\0' && ptr1[1] != '\n' && j < ANTFIELD)
   {
       ptr2 = &ptr1[1];
       if(ptr2[0] != ';')   	/* Kolla så att färltet inte är tomt				*/
       {
           for(i = 0; ptr2[i] != ';' &&  ptr2[i] != '\0' &&  ptr2[i] != '\n' && i < FIELDLEN-1; i++)
               ut[j][i] = ptr2[i];
           ut[j][i] = '\0';
       }
       j++;
       ptr1 = strchr(ptr2, ';');
       if(!ptr1)
           break;    		/* Om raden inte slutar med ';' vill vi inte ha "seg fault"	*/
   }
   return;
}

int doSql(char *sqlCommand)
{
  int res;
  int flag=-1;
// fprintf(stderr,"Error:doSql");
	mysql_init(&my_connection);

  	if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
    		res = mysql_query(&my_connection,sqlCommand);
  		if (!res){
			if ((unsigned long)mysql_affected_rows(&my_connection) < 1){
				fprintf(stderr,"OK: 1:PRISUPD %lu poster uppdaterade. \n",(unsigned long)mysql_affected_rows(&my_connection));
				flag=0;
			}else{
				fprintf(stderr,"OK: 2:PRISUPD %lu poster uppdaterade.\n",
				(unsigned long)mysql_affected_rows(&my_connection));
			}
        	}else{
			fprintf(stderr,"Error: PRISUPD UPDATE error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
		}
		mysql_close(&my_connection);
 	} else {
		fprintf(stderr,"Error: PRISUPD Connection failed\n");
    		if (mysql_errno(&my_connection))   {
    			fprintf(stderr,"Error: PRISUPD Connection error %d:  %s\n",
				mysql_errno(&my_connection), mysql_error(&my_connection));
		}
    	}
  return EXIT_SUCCESS;
}

int which_database(char *envp[])
{
	FILE *fil_pek;

	char home[50];
	char *home_pek;
	char resource[]="/.olfixrc";
	char filename[50]="";
	char tmp[20]="";
	char temp[10]="";
	char *tmp_pek;
	int i,status;

	for (i = 0;envp[i]!=NULL;i++){
		if(strstr(envp[i],"HOME=") != NULL){
			strncpy(temp,envp[i],4);
/*			fprintf(stderr,"temp=%s\n",temp); */
			status=strcmp(temp,"HOME");
/*			fprintf(stderr,"status=%d\n",status); */
			if (status == 0){
				home_pek=(strstr(envp[i],"HOME="));
				home_pek=home_pek+5;
				strcpy(home,home_pek);
			}
/*			fprintf(stderr,"home_pek=%d %s\n",home_pek,home_pek);	*/
		}
	}
/*	fprintf(stderr,"home=%s\n",home);	*/
	strncpy(filename,home,strlen(home));
	strncat(filename,resource,strlen(resource));

/*	fprintf(stderr,"filename=%s\n",filename);	*/
	status=-1;

	if ((fil_pek = fopen(filename,"r")) != NULL){
		while (fgets(tmp,150,fil_pek) != NULL){
/*			fprintf(stderr,"tmp=%s\n",tmp); */
			if(strstr(tmp,"DATABASE=")){
				tmp_pek=(strstr(tmp,"DATABASE="))+9;
				strncpy(database,tmp_pek,strlen(tmp_pek));
				status=0;
			}
		}
/*		fprintf(stderr,"database=%s_len=%d\n",database,strlen(database)); */
		fclose(fil_pek);
	}
	else{
/*		fprintf(stderr,"database=%s_len=%d\n",database,strlen(database)); */
	 	fprintf(stderr,"Error: Filen .olfixrc kan inte öppnas\n");
	}
	for (i=0;i < strlen(database);i++){
		tmp[i]=database[i];
	}
	tmp[i-1]=0;
/*	fprintf(stderr,"tmp=%s, i=%d len(tmp)=%d\n",tmp,i,strlen(tmp));	*/
	strncpy(database,tmp,strlen(tmp));
	database[strlen(tmp)]=0;
/*	fprintf(stderr,"databas=%s\n",database);	*/
	return status;
}

