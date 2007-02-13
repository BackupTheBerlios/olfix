/***************************************************************************
                          BARFND.c  -  description
			  Hitta bokföringsår
                             -------------------
			 ; Vers. 0.3
    begin                : Lör  9 aug	2003
    modified		 : Ons 13 febr  2007
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
 *********************************************** ****************************/

/*
	INPUT: datum [databas]

	Kommando: ./BARCHK datum [databas] (yyyy-mm-dd)

	Function: Hitta bokföringsår för angivet datum.
        SQLanrop: SELECT ARID FROM BOKFAR WHERE ARSTART < "2003-08-09" AND ARSLUT > "2003-08-09"
	OUTPUT: data, errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/BARFND.c,v 1.5 2007/02/13 05:44:15 janpihlgren Exp $ " ;

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql.h"
#define ANTARG 2

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
  char usr[21];				/* userid 20070213 utökad från 15 till 21 tecken */

  char temp1[]="SELECT ARID FROM BOKFAR WHERE ARSTART < ";
  char temp1b[]=" AND ARSLUT > ";
  char temp2[]="\"";
  char temp5[200]="";
  char datum[11]="";

/* ================================================================================ */
/* 		Val av databas, START						    */
/* ================================================================================ */

  status = which_database(envp);

  if (status != 0)
	exit(status);

  strncpy(usr,userp,sizeof(usr));			/* Den inloggades userid	*/
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
/*  fprintf(stderr,"Databas=%s\n",databas);	*/
/* ================================================================================ */
/* 		Val av databas, END!						    */
/* ================================================================================ */

  strncpy(datum,argv[1],sizeof(datum));			/* 2005-02-23	*/
/*  fprintf(stderr,"argv[1]=%s\n",argv[1]);	*/
/*  fprintf(stderr,"datum=%s\n",datum);	*/
  strncpy(temp5,temp1,strlen(temp1));
/* SELECT ARID FROM BOKFAR WHERE ARSTART <   */
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
  strncat(temp5,datum,strlen(datum));/* 2003-08-09 */
/* SELECT ARID FROM BOKFAR WHERE ARSTART < "2003-08-09  */
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
/* SELECT ARID FROM BOKFAR WHERE ARSTART < "2003-08-09"  */
  strncat(temp5,temp1b,strlen(temp1b));
/* SELECT ARID FROM BOKFAR WHERE ARSTART < "2003-08-09" AND ARSLUT >   */
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
  strncat(temp5,datum,strlen(datum));
/* SELECT ARID FROM BOKFAR WHERE ARSTART < "2003-08-09" AND ARSLUT > "2003-08-09  */
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
/* SELECT ARID FROM BOKFAR WHERE ARSTART < "2003-08-09" AND ARSLUT > "2003-08-09"  */

/*  fprintf(stderr,"BARCHKmain: temp5 = %s\n",temp5);	*/

  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
/*  fprintf(stdout,"BARCHKmain:Connection success\n");	*/
  	res = mysql_query(&my_connection,temp5);
  	if (res){
		fprintf(stderr,"Error: BARFND SELECT error: %s\n",mysql_error(&my_connection));
  	}
  	else{
		res_ptr=mysql_store_result(&my_connection);
		if (res_ptr){
/*			fprintf(stderr,"BARFND Retrieved %lu rows\n",(unsigned long)mysql_num_rows(res_ptr));	*/
			if((unsigned long)mysql_num_rows(res_ptr) > 0){ /* En rad har hittats */
				status=0;
				sqlrow=mysql_fetch_row(res_ptr);
				fprintf(stdout,"1:%s  ",sqlrow[0]);
			}else{						/* Ingen rad hittades */
				status=-1;
			}

			if (mysql_errno(&my_connection)){
				fprintf(stderr,"Error: BARFND Retriev error:  %s\n", mysql_error(&my_connection));
			}
		}
		mysql_free_result(res_ptr);
	}
  	mysql_close(&my_connection);
 }
  else {
  	fprintf(stderr,"Error: BARFND Connection failed\n");
	if (mysql_errno(&my_connection)){
		fprintf(stderr,"Error: BARFND Connection error %d:  %s\n",
		mysql_errno(&my_connection), mysql_error(&my_connection));
	}
  }
/*
if(status == 0){
	fprintf(stdout,"OK: BARFND Status = %d\n",status);
}
*/
if(status != 0){
	fprintf(stderr,"Error: BARFND Bokföringsår för datum %s finns inte!\n",datum);
}
  return status;
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
