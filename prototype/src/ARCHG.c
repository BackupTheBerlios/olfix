/***************************************************************************
                          ARCHG.c  -  description
                             -------------------
    Version		 : 0.1
    Modified		 :
    begin                : M?n 17 nov 2003
    copyright            : (C) 2003 by Jan Pihlgren
    email                : jan@pihlgren.se
 ***************************************************************************/
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

/*
	INPUT: artikeldata [databas]
		artikeldataformat=_:_2345_:_Testartikel_:_Provprodukt_:_ST_:_200,00_:_20_:_
		12345_:_67890_:_123_:_124_:_125_:_2.5_:_2_:_B_:_Mesurment Part_:_England_:_MP23Z_:_
		1234567_:_2.500_:_10:_:

	F?ltavskiljare = _:_

	Function: g?r  UPDATE ARTIKELREG SET (ARTIKELNR="2345",ARBENEMNING1="Testaretikel",
	ARBENEMNING2="Provprodukt",ARENHET="ST",ARFPRIS="200.00",ARLEDTID="20",
	ARPRODKLASS="12345",ARPRODKTO="67890",ARLEVNr1="123",ARLEVNR2="124",ARLEVNR3="125",
	ARNETTOVIKT="2.5",ARARTTYP="2",ARSTRUKT="B",ARURBENEMNING="Mesurment Part",ARURLAND="England",
	ARURARTNR="MP2Z,ARTULLTAX="1234567",ARVOLYM="2.500",AROMRFAKTOR="10") WHERE ARTIKELNR"2345"

	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/ARCHG.c,v 1.1 2003/11/19 09:16:04 janpihlgren Exp $ " ;

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql.h"
#define ANTARG 2
#define ANTFELT 20		/*	Antal dataf?lt i ARTIKELREG	*/

  MYSQL my_connection;
  MYSQL_RES *res_ptr;
  MYSQL_ROW sqlrow;

  int which_database(char *envp[]);
  char database[15]="";

int main(int argc, char *argv[], char *envp[])
{
  int res,status;
  char databas[25]="olfix";
  const char *userp = getenv("USER");	/* vem ?r inloggad?	*/
  char usr[15];				/* userid		*/

  static char *temp1[ANTFELT]={"","UPDATE ARTIKELREG SET ARBENEMNING1=\"",
  ",ARBENEMNING2=\"",",ARENHET=\"",",AROMRFAKTOR=\"",",ARNETTOVIKT=\"",",ARFPRIS=\"",",ARLEDTID=\"",
  ",ARPRODKLASS=\"",",ARPRODKTO=\"",",ARARTTYP=\"",",ARSTRUKT=\"",",ARTULLTAX=\"",
  ",ARLEVNR1=\"",",ARLEVNR2=\"",",ARLEVNR3=\"",
  ",ARURBENEMNING=\"",",ARURLAND=\"",",ARURARTNR=\"",",ARVOLYM=\""};

  char temp1b[]=" WHERE ARTIKELNR = \"";
  char temp2[]="\"";
//  char temp3[]=",";
//  char temp4[]=")";
  char temp5[1500]="";
  char artikeldata[2000];
  char artikelnr[30]="";

  char *pos1;
  char *pos2;
  int tmp,lenght,ant,i,j,k,n;
  if (argv[1] != NULL){
  	strncpy(artikeldata,argv[1],strlen(argv[1]));
  }
  else{
  	fprintf(stderr,"Error: ARCHG: Data saknas!\n");
	exit(-1);
  }
/*  fprintf(stderr,"argv[1]=%s\n",argv[1]);	*/
/* ================================================================================ 	*/
/* 		Val av databas, START							*/
/* ================================================================================	*/
  status = which_database(envp);

  if (status != 0)
	exit(status);

  strncpy(usr,userp,15);				// Den inloggades userid

 if (argc<3){
    	if (strlen(database)!= 0){
		strncpy(databas,database,15);
	}else{
  		strncpy(databas,"olfixtst",15);	// olfixtst = testf?retag
	}
  }else{
	if (strlen(argv[2]) != 0){
  		if (strncmp(argv[2],"99",2)==0){
			strncpy(databas,"olfixtst",15);
		}else{
  			strncpy(databas,argv[2],strlen(argv[2]));
  		}
  	}
  }
  /* Om usr (userid) b?rjar p? 'test' eller 'prov' anv?nd databas 'olfixtst' */
  if (strncmp(usr,"test",4)==0 || strncmp(usr,"prov",4)==0 ) {
  	strncpy(databas,"olfixtst",15);
  }
/* ================================================================================	*/
/* 		Val av databas, END!							*/
/* ================================================================================	*/


  lenght=strlen(artikeldata);
/*  fprintf(stderr,"lenght=%d\n",lenght);	*/
/*  strncpy(temp5,temp1a,strlen(temp1a));	*/
/*  fprintf(stderr,"artikeldata=%s\n",artikeldata);	*/
  pos1=strstr(artikeldata,"_:_")+3;
  k=3;
  n=0;
  ant=ANTFELT;		/* antal f?lt att uppdatera	*/
  for (i=0;i<ant;i++){
  	for (j=k;j<lenght;j++){
/*		fprintf(stderr,"j=%d\n",j);	*/
  		if (artikeldata[j]== 95 && artikeldata[j+1]== 58 && artikeldata[j+2]== 95){
			j=lenght;
		}
		n=n+1;
  	}
	k=k+(n-1)+3;
	pos2=pos1+3+(n-1);
	tmp=pos2-pos1-3;
	if (i==0){
		strncpy(artikelnr,pos1,tmp);
	}else{
  		strcat(temp5,temp1[i]);
  		strncat(temp5,pos1,tmp);
  		strncat(temp5,temp2,strlen(temp2));
	}
	pos1=pos2;
/*	fprintf(stderr,"i=%d, k=%d, n=%d, tmp=%d\n",i,k,n,tmp);	*/
	n=0;
/*	fprintf(stderr,"temp5 = %s\n",temp5);			*/
  }
  strncat(temp5,temp1b,strlen(temp1b));
  strncat(temp5,artikelnr,strlen(artikelnr));
  strncat(temp5,temp2,strlen(temp2));

/* fprintf(stderr,"ARCHG: temp5 = %s\n",temp5);	*/
/* exit(0);					*/


  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
/*  	fprintf(stderr,"ARCHG:Connection success\n");		*/

  res = mysql_query(&my_connection,temp5);

   if (!res){
    	if ((unsigned long)mysql_affected_rows(&my_connection) > 0){
 		fprintf(stdout,"OK: ARCHG Updated %lu rows\n",
			(unsigned long)mysql_affected_rows(&my_connection));
	}else{
		fprintf(stdout,"Error: ARCHG Updated %lu rows\n",
		(unsigned long)mysql_affected_rows(&my_connection));
	}
   }else{
	fprintf(stderr,"Error: ARCHG UPDATE error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
   }
   mysql_close(&my_connection);
 }else {
	fprintf(stderr,"Error: ARCHG Connection failed\n");
 	if (mysql_errno(&my_connection))   {
 		fprintf(stderr,"Error: ARCHG Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
	}
  }
 	fprintf(stdout,"\n");
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
/*			fprintf(stderr,"temp=%s\n",temp);		*/
			status=strcmp(temp,"HOME");
/*			fprintf(stderr,"status=%d\n",status);		*/
			if (status == 0){
				home_pek=(strstr(envp[i],"HOME="));
				home_pek=home_pek+5;
				strcpy(home,home_pek);
			}
/*			fprintf(stderr,"home_pek=%d %s\n",home_pek,home_pek);	*/
/*			fprintf(stderr,"home_pek=%d %s\n",home_pek,home_pek);	*/
		}
	}
/*	fprintf(stderr,"home=%s\n",home);				*/
	strcpy(filename,home);
	strncat(filename,resource,strlen(resource));

/*	fprintf(stderr,"filename=%s\n",filename);			*/
	status=-1;

	if ((fil_pek = fopen(filename,"r")) != NULL){
		while (fgets(tmp,150,fil_pek) != NULL){
/*			fprintf(stderr,"tmp=%s\n",tmp);			*/
			if(strstr(tmp,"DATABASE=")){
				tmp_pek=(strstr(tmp,"DATABASE="))+9;
				strncpy(database,tmp_pek,strlen(tmp_pek));
				status=0;
			}
		}
/*		fprintf(stderr,"database=%s_len=%d\n",database,strlen(database));	*/
		fclose(fil_pek);
	}
	else{
	 	fprintf(stderr,"Error: Filen .olfixrc kan inte ?ppnas\n");
	}
	for (i=0;i < strlen(database);i++){
		tmp[i]=database[i];
	}
	tmp[i-1]=0;
/*	fprintf(stderr,"tmp=%s, i=%d len tmp=%d\n",tmp,i,strlen(tmp));			*/
	strncpy(database,tmp,strlen(tmp));
	database[strlen(tmp)]=0;

	return status;
}
