/***************************************************************************
                          KTOCHG.c  -  description
                             -------------------
    Version		 : 0.4
    begin                : Fre  31 jan  2003
    modified		 : Ons  14 febr 2007
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
	INPUT:	ARID,KTONR,BENAMNING,MANUELL,MOMSKOD,SRUNR,KSTALLE,PROJEKT,SUBKTO,KTOPLAN
	Function: gör  UPDATE KTOPLAN SET BENAMNING = "benamn",MANUELL = "manuell",
		MOMSKOD = "momskod",
		SRUNR = "srunr",KSTALLE = "kstalle",PROJEKT = "projekt",SUBKTO = "subkto",
		KTOPLAN = "ktoplan"
		WHERE (ARID = "arid" AND KTONR ="ktonr") i databasen olfix

	OUTPUT: errornr och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/KTOCHG.c,v 1.4 2007/02/14 14:56:29 janpihlgren Exp $ " ;

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql.h"
#define ANTARG 13

  MYSQL my_connection;
  MYSQL_RES *res_ptr;
  MYSQL_ROW sqlrow;

int which_database(char *envp[]);
void display_row();
char database[15]="";

int main(int argc, char *argv[], char *envp[])
{
  int res;
  /*int i;	*/
  int status;
  const char *userp = getenv("USER");	/* vem är inloggad?	*/
  char databas[25]="olfix";
  char usr[21];				/* userid 20070214 utökad från 15 till 21 tecken */

  char temp1a[]="UPDATE KTOPLAN SET BENAMNING = \'";
  char temp1b[]="\' WHERE (ARID = \'";
  char temp1c[]=" AND KTONR = \'";
  char temp2[]="\'";
  char temp4[]=")";
  char temp5[200]="";
  char arid[3]="";
  char ktonr[5]="";
  char benamn[101]="";
  char manuell[2]="";
  char momskod[5]="";
  char srunr[4]="";
  char kstalle[5]="";
  char projekt[5]="";
  char subkto[5]="";
  char ktoplan[16]="";
/*  char ib[]="0.00";	*/
/*  char ub[]="0.00";	*/

  /* ================================================================================ */
/* 		Val av databas, START						    */
/* ================================================================================ */

  status = which_database(envp);

  if (status != 0)
	exit(status);

  strncpy(usr,userp,sizeof(usr));			/* Den inloggades userid 20070214 */
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
/*  fprintf(stderr,"argc=%d ANTARG=%d,argv[ANTARG-1]=%s\n",argc,ANTARG,argv[ANTARG-1]);	*/
/* Om usr (userid) börjar på 'test' eller 'prov' använd databas 'olfixtst' */
  if (strncmp(usr,"test",4)==0 || strncmp(usr,"prov",4)==0 ) {
  	strncpy(databas,"olfixtst",15);
  }
/*  fprintf(stderr,"Databas=%s\n",databas);	*/
/* ================================================================================ */
/* 		Val av databas, END!						    */
/* ================================================================================ */

  if (argv[1] != NULL){
  	strncpy(arid,argv[1],sizeof(arid));		/* 2005-02-24	*/
  }
  else{
  	fprintf(stderr,"Error: KTOCHG: Ange årtal!\n");
	exit(-1);
  }

  if (argv[2] != NULL){
  	strncpy(ktonr,argv[2],sizeof(ktonr));		/* 2005-02-24	*/
  }
  else{
  	fprintf(stderr,"Error: KTOCHG: Ange kontonr!\n");
	exit(-1);
  }

  strncpy(benamn,argv[3],sizeof(benamn));		/* 2005-02-24	*/
  strncpy(manuell,argv[4],sizeof(manuell));		/* 2005-02-24	*/
  strncpy(momskod,argv[5],sizeof(momskod));		/* 2005-02-24	*/
  strncpy(srunr,argv[6],sizeof(srunr));			/* 2005-02-24	*/
  strncpy(kstalle,argv[7],sizeof(kstalle));		/* 2005-02-24	*/
  strncpy(projekt,argv[8],sizeof(projekt));		/* 2005-02-24	*/
  strncpy(subkto,argv[9],sizeof(subkto));		/* 2005-02-24	*/
  strncpy(ktoplan,argv[10],sizeof(ktoplan));		/* 2005-02-24	*/

/* "UPDATE KTOPLAN SET BENAMNING = "benamn",MANUELL = "manuell",MOMSKOD = "momskod",	*/
/*	SRUNR = "srunr",KSTALLE = "kstalle",PROJEKT = "projekt",SUBKTO = "subkto",	*/
/*	KTOPLAN = "ktoplan"								*/
/*	WHERE (ARID = "arid" AND KTONR ="ktonr")					*/

  strncpy(temp5,temp1a,strlen(temp1a));
/* "UPDATE KTOPLAN SET BENAMNING = "	*/
  strncat(temp5,benamn,strlen(benamn));
/* "UPDATE KTOPLAN SET BENAMNING = "xxxxxxx	*/
  strncat(temp5,"\',MANUELL = \'",13);
  strncat(temp5,manuell,strlen(manuell));
/* "UPDATE KTOPLAN SET BENAMNING = "xxxxxxx",MANUELL = "J"	*/
  strncat(temp5,"\',MOMSKOD = \'",13);
  strncat(temp5,momskod,strlen(momskod));
  strncat(temp5,"\',SRUNR = \'",11);
  strncat(temp5,srunr,strlen(srunr));
  strncat(temp5,"\',KSTALLE = \'",13);
  strncat(temp5,kstalle,strlen(kstalle));
  strncat(temp5,"\',PROJEKT = \'",13);
  strncat(temp5,projekt,strlen(projekt));
  strncat(temp5,"\',SUBKTO = \'",12);
  strncat(temp5,subkto,strlen(subkto));
  strncat(temp5,"\',KTOPLAN = \'",13);
  strncat(temp5,ktoplan,strlen(ktoplan));
  strncat(temp5,temp1b,strlen(temp1b));
  strncat(temp5,arid,strlen(arid));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp1c,strlen(temp1c));
  strncat(temp5,ktonr,strlen(ktonr));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp4,strlen(temp4));

/*  fprintf(stderr,"KTOCHGmain: temp5 = %s\n",temp5);	*/
/*  fprintf(stderr,"databas=%s\n",databas);		*/

  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
/*  	fprintf(stderr,"KTOVIEW:Connection success\n");	*/

  res = mysql_query(&my_connection,temp5);

  if (!res){
  	if ((unsigned long)mysql_affected_rows(&my_connection) > 0){
 		fprintf(stdout,"OK: KTOCHG Updated %lu rows\n",
			(unsigned long)mysql_affected_rows(&my_connection));
	}else{
		fprintf(stderr,"Error: KTOCHG Updated %lu rows\n",
			(unsigned long)mysql_affected_rows(&my_connection));
	}
  }else{
/*	fprintf(stderr,"stderr-KTOCHG:UPDATE error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
*/
	fprintf(stderr,"Error: KTOCHG UPDATE error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
	}
	mysql_close(&my_connection);
 }else {
	fprintf(stderr,"Error: KTOCHG Connection failed\n");
 	if (mysql_errno(&my_connection))   {
 		fprintf(stderr,"Error: KTOCHG Connection error %d:  %s\n",
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
