/***************************************************************************
                          SIEEXPV.c  -  description
                             -------------------
			     Ver: 0.3
    begin                : Tis  23 nov   2004
    modified		 : Tors 11 april 2005
    copyright            : (C) 2004 by Jan Pihlgren
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
	INPUT: arid		(bokföringsår)

	Kommando: ./SIEEXPV arid serie

	Function: Exportera verifikationer för angivet bokföringsår i SIE-format

	OUTPUT: VERRAD.VERNR, VERRAD.RADNR,
	        VERHUVUD.VERDATUM, VERHUVUD.VERTEXT, VERHUVUD.REGDAT,
		VERRAD.KTONR, VERRAD.BELOPP, VERRAD.DK
	samt errornb och error (text)

***************************************************************************/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/SIEEXPV.c,v 1.2 2005/04/12 09:46:31 janpihlgren Exp $ " ;

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql.h"
#define ANTARG 3


  MYSQL my_connection;
  MYSQL_RES *res_ptr;
  MYSQL_ROW sqlrow;

  int which_database(char *envp[]);
  void display_row();

  char database[15]="";
  char serie[7]="";
  char flag[11]="0";
 

int main(int argc, char *argv[], char *envp[])
{
  int i;
  int res;
  int status;
  const char *userp = getenv("USER");	/* vem är inloggad?	*/
  char databas[25]="olfix";
  char usr[15];				/* userid		*/
  char arid[3]="";			/* bokföringsår		*/
//  char serie[7]="";

  char temp1[]="SELECT VERRAD.VERNR, VERRAD.RADNR, VERHUVUD.VERDATUM, VERHUVUD.VERTEXT, VERHUVUD.REGDAT, VERRAD.KTONR, VERRAD.DK, VERRAD.BELOPP";
  char temp1b[]=" FROM VERHUVUD,VERRAD";
  char temp1c[]=" WHERE VERHUVUD.ARID = \"";
  char temp2[]="\"";
  char temp2b[]=" AND VERRAD.ARID=VERHUVUD.ARID AND VERHUVUD.VERNR=VERRAD.VERNR";
  char temp3[]=" ORDER BY VERRAD.VERNR,VERRAD.RADNR";
  char temp5[500]="";

/*  for (i=0;i< argc;i++){
  	fprintf(stderr,"SIEEXPV argv%d = %s\n",i,argv[i]);
  }
*/
/*  fprintf(stderr,"argc=%d\n",argc);		*/
  if (argc<2){
	fprintf(stderr,"Error: arid saknas!\n");
	exit(0);
  }
  if (argc<3){
  	fprintf(stderr,"Error: serie saknas!\n");
	exit(0);
  }
  strncpy(arid,argv[1],sizeof(arid));
  strncpy(serie,argv[2],sizeof(serie));

/* ================================================================================ */
/* 		Val av databas, START						    */
/* ================================================================================ */

  status = which_database(envp);

  if (status != 0)
	exit(status);

  strncpy(usr,userp,15);			/* Den inloggades userid	*/
/*  fprintf(stderr,"status=%d ANTARG=%d len(database)=%d\n",status,ANTARG,strlen(database));	*/
  if (argc < ANTARG+1){
    	if (strlen(database)!= 0){
		strncpy(databas,database,sizeof(databas));	/* 2005-02-24	*/
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
/*  fprintf(stderr,"ANTARG=%d,argv[ANTARG]=%s\n",ANTARG,argv[ANTARG]);	*/
/* Om usr (userid) börjar på 'test' eller 'prov' använd databas 'olfixtst' */
  if (strncmp(usr,"test",4)==0 || strncmp(usr,"prov",4)==0 ) {
  	strncpy(databas,"olfixtst",15);
  }
 /* fprintf(stderr,"Databas=%s\n",databas);	*/
/* ================================================================================ */
/* 		Val av databas, END!						    */
/* ================================================================================ */

  strncpy(temp5,temp1,strlen(temp1));
/* SELECT VERRAD.VERNR, VERRAD.RADNR, VERHUVUD.VERDATUM, VERHUVUD.VERTEXT,
   VERHUVUD.REGDAT, VERRAD.KTONR,VERRAD.BELOPP,VERRAD.DK 	*/
  strncat(temp5,temp1b,strlen(temp1b));
/*  SELECT VERRAD.VERNR, VERRAD.RADNR, VERHUVUD.VERDATUM, VERHUVUD.VERTEXT,
    VERHUVUD.REGDAT, VERRAD.KTONR,VERRAD.BELOPP,VERRAD.DK
    FROM VERHUVUD,VERRAD */
  strncat(temp5,temp1c,strlen(temp1c));
/*  SELECT VERRAD.VERNR, VERRAD.RADNR, VERHUVUD.VERDATUM, VERHUVUD.VERTEXT,
    VERHUVUD.REGDAT, VERRAD.KTONR,VERRAD.BELOPP,VERRAD.DK
    FROM VERHUVUD,VERRAD  WHERE ARID = "  */
  strncat(temp5,arid,strlen(arid));
/*  SELECT VERRAD.VERNR, VERRAD.RADNR, VERHUVUD.VERDATUM, VERHUVUD.VERTEXT,
    VERHUVUD.REGDAT, VERRAD.KTONR,VERRAD.BELOPP,VERRAD.DK
    FROM VERHUVUD,VERRAD  WHERE VERHUVUD.ARID = " AD  */
  strncat(temp5,temp2,strlen(temp2));
/*  SELECT VERRAD.VERNR, VERRAD.RADNR, VERHUVUD.VERDATUM, VERHUVUD.VERTEXT,
    VERHUVUD.REGDAT, VERRAD.KTONR,VERRAD.BELOPP,VERRAD.DK
    FROM VERHUVUD,VERRAD  WHERE VERHUVUD.ARID = " AD " */
  strncat(temp5,temp2b,strlen(temp2b));
/*  SELECT VERRAD.VERNR, VERRAD.RADNR, VERHUVUD.VERDATUM, VERHUVUD.VERTEXT,
    VERHUVUD.REGDAT, VERRAD.KTONR,VERRAD.BELOPP,VERRAD.DK
    FROM VERHUVUD,VERRAD  WHERE VERHUVUD.ARID = " AD "
    AND VERRAD.ARID=VERHUVUD.ARID AND VERHUVUD.VERNR=VERRAD.VERNR */
  strncat(temp5,temp3,strlen(temp3));
/*  SELECT VERRAD.VERNR, VERRAD.RADNR, VERHUVUD.VERDATUM, VERHUVUD.VERTEXT,
    VERHUVUD.REGDAT, VERRAD.KTONR,VERRAD.BELOPP,VERRAD.DK
    FROM VERHUVUD,VERRAD  WHERE VERHUVUD.ARID = " AD "
    AND VERRAD.ARID=VERHUVUD.ARID AND VERHUVUD.VERNR=VERRAD.VERNR
    ORDER BY VERRAD.VERNR,VERRAD.RADNR */
/*     fprintf(stderr,"temp5=%s\n",temp5);		*/

  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
  	res = mysql_query(&my_connection,temp5);
  	if (res){
		fprintf(stderr,"Error: SIEEXPV SELECT errno: %d\n",mysql_errno(&my_connection));
        }
	else{
		res_ptr=mysql_store_result(&my_connection);
		if (res_ptr){
			i=0;
			fprintf(stdout,"OK: ANTAL_%lu_\n",(unsigned long)mysql_num_rows(res_ptr));
			while ((sqlrow=mysql_fetch_row(res_ptr)))  {
				display_row();
				fprintf(stdout,"\n");
				i++;
			}
			fprintf(stdout,"}\nEND:");
			fprintf(stdout,"\n");
		}
		else{
			fprintf(stderr,"Error: SIEEXPV Data saknas:  %s\n", mysql_error(&my_connection));
		}
			if (mysql_errno(&my_connection))  {
				fprintf(stderr,"Error: SIEEXPV Retriev error:  %s\n", mysql_error(&my_connection));
			}
		}
	mysql_free_result(res_ptr);
    	mysql_close(&my_connection);
  }
  else{
    	fprintf(stderr,"Error: SIEEXPV Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: SIEEXPV Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
	}
    }
  return EXIT_SUCCESS;
}

void display_row()
{
   unsigned int field_count;
   field_count=0;
   if (strcmp(sqlrow[0],flag)!=0){
   	if(strncmp(flag,"0",1)!=0){
		fprintf(stdout,"}\n");
	}
	fprintf(stdout,"#VER \"%s\" \"%s\" ",serie,sqlrow[0]);
	fprintf(stdout,"%s\" \"",sqlrow[2]);
	fprintf(stdout,"%s\" \"",sqlrow[3]);
	fprintf(stdout,"%s\"\n{\n",sqlrow[4]);
	fprintf(stdout,"#TRANS %s ",sqlrow[5]);
	if (!strcmp(sqlrow[6],"K")){
		fprintf(stdout," {} -");
	}else{
		fprintf(stdout," {} ");
	}
	fprintf(stdout,"%s ",sqlrow[7]);
   }else{
	fprintf(stdout,"#TRANS %s ",sqlrow[5]);
	if (!strcmp(sqlrow[6],"K")){
		fprintf(stdout," {} -");
	}else{
		fprintf(stdout," {} ");
	}
   	fprintf(stdout,"%s ",sqlrow[7]);
   }
   strncpy(flag,sqlrow[0],sizeof(flag));
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
			status=strcmp(temp,"HOME");
			if (status == 0){
				home_pek=(strstr(envp[i],"HOME="));
				home_pek=home_pek+5;
				strcpy(home,home_pek);
			}
		}
	}
	strncpy(filename,home,strlen(home));
	strncat(filename,resource,strlen(resource));

	status=-1;

	if ((fil_pek = fopen(filename,"r")) != NULL){
		while (fgets(tmp,150,fil_pek) != NULL){
			if(strstr(tmp,"DATABASE=")){
				tmp_pek=(strstr(tmp,"DATABASE="))+9;
				strncpy(database,tmp_pek,strlen(tmp_pek));
				status=0;
			}
		}
		fclose(fil_pek);
	}
	else{
	 	fprintf(stderr,"Error: Filen .olfixrc kan inte öppnas\n");
	}
	for (i=0;i < strlen(database);i++){
		tmp[i]=database[i];
	}
	tmp[i-1]=0;
	strncpy(database,tmp,strlen(tmp));
	database[strlen(tmp)]=0;
	return status;
}
