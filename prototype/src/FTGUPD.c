/***************************************************************************
                          FTGUPD.c  -  description
                             -------------------
    Version		 : 0.3
    begin                : mån 18 nov	2002
    modified		 : Ons 23 febr  2005
    copyright            : (C) 2002 by Jan Pihlgren
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
	INPUT:

	Kommando: ./FTGUPD posttyp fdata

	Function: Uppdatera fältet FDATA i tabellen FTGDATA


	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/FTGUPD.c,v 1.3 2005/02/23 15:17:31 janpihlgren Exp $ " ;

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "mysql.h"

#define FORMAT_STR "%Y-%m-%d_%H:%M:%S"    /* YYYY-MM-DD */
#define MAXSIZE 20
#define MAXSTRING 5000
#define TEXTSIZE 255
#define ANTARG 3

  MYSQL my_connection;
  MYSQL_RES *res_ptr;
  MYSQL_ROW sqlrow;

int which_database(char *envp[]);
char database[15]="";

int main(int argc, char *argv[], char *envp[])
{
  int res;
  int status;
  const char *userp = getenv("USER");	/* vem är inloggad?	*/
  char databas[25]="olfix";
  char usr[15]="";			/* userid		*/

  char temp1a[]="UPDATE FTGDATA SET FDATA = ";
  char temp2[]=" WHERE POSTTYP = ";
  char temp5[TEXTSIZE+200]="";

  char ptyp[5]="";		/* posttyp */
  char txt[61]="";		/* ftgdata */

  status=-15;
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
/*  fprintf(stderr,"ANTARG=%d,argv[ANTARG]=%s\n",ANTARG,argv[ANTARG]);	*/
/* Om usr (userid) börjar på 'test' eller 'prov' använd databas 'olfixtst' */
  if (strncmp(usr,"test",4)==0 || strncmp(usr,"prov",4)==0 ) {
  	strncpy(databas,"olfixtst",15);
  }
/* fprintf(stderr,"Databas=%s\n",databas);	*/
/* ================================================================================ */
/* 		Val av databas, END!						    */
/* ================================================================================ */

   strncpy(ptyp,argv[1],sizeof(ptyp));	/* 2005-02-23	*/
   strncpy(txt,argv[2],sizeof(txt));	/* 2005-02-23	*/

/*    fprintf(stderr,"FTGUPDmain1: argv1 = %s argv2 = %s len text=%d\n",ptyp,txt,strlen(txt));	*/
/*    fprintf(stderr,"FTGUPDmain: argv2 = %s\n",txt);						*/

  strncpy(temp5,temp1a,strlen(temp1a));
/* UPDATE FTGDATA SET FDATA =  */
  strncat(temp5,"'",1);
  strncat(temp5,txt,strlen(txt));
  strncat(temp5,"'",1);
/*  fprintf(stderr,"FTGUPDmain2: temp5=%s\n",temp5);	*/
/* UPDATE FTGDATA SET FDATA = 'txt' */
  strncat(temp5,temp2,strlen(temp2)); /* WHERE POSTTYP =  */
/* UPDATE FTGDATA SET FDATA = 'txt, WHERE POSTTYP =    */
  strncat(temp5,"'",1);
/*  fprintf(stderr,"FTGUPDmain3: temp5=%s\n",temp5);	*/
  strncat(temp5,ptyp,strlen(ptyp));
/*  fprintf(stderr,"FTGUPDmain4: temp5=%s\n",temp5);	*/
/* UPDATE FTGDATA SET FDATA = 'txt' WHERE POSTTYP = 'ADR1' */
  strncat(temp5,"'",1);

/* fprintf(stderr,"FTGUPDmain: temp5=%s\n",temp5);	*/

  mysql_init(&my_connection);

  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
/*    fprintf(stderr,"FTGUPD:Connection success\n");	*/
    res = mysql_query(&my_connection,temp5);
  	if (!res){
		fprintf(stderr,"OK: FTGUPD Inserted %lu rows\n",
			(unsigned long)mysql_affected_rows(&my_connection));
        }else{
	fprintf(stderr,"Error: FTGUPD UPDATE error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
	}
	mysql_close(&my_connection);

 } else {
	fprintf(stderr,"Error: FTGUPD Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: FTGUPD Connection error %d:  %s\n",
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

