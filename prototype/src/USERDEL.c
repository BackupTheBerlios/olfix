/***************************************************************************
                          USERDEL.c  -  description
                             -------------------
    Version		 : 0.5
    begin                : tis   4  febr 2003
    modified		 : Ons   5  dec  2007
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
	INPUT: 1 st arg. USERID

	Kommando: ./USERDEL JAPI

	Function: Radera record i tabell USR

	OUTPUT: errornb och error (text)

	Anrop till databas på annan server/host
*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/USERDEL.c,v 1.6 2007/12/05 05:15:50 janpihlgren Exp $ " ;

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
int which_host(char *envp[]);	// 20071205
char database[15]="";
char host[200]="";		// 20071205

int main(int argc, char *argv[], char *envp[])
{
/* int i;	*/
  int res;
  int status;
  const char *userp = getenv("USER");	/* vem är inloggad?	*/
  char databas[25]="olfix";
  char usr[21];				/* userid 2007-02-11 utökat från 15 till 21 */

  char temp1[]="DELETE FROM USR WHERE USERID = \"";
  char temp2[]="\"";
  char temp5[200]="";
  char userid[21]="";			/* 2007-02-11 utökad från 9 till 21 */

/* ================================================================================ */
/* 		Val av databas, START						    */
/* ================================================================================ */
/*	fprintf(stderr,"1. host=%s\n",host);	*/
  status = which_host(envp);	// 20071205
	fprintf(stdout,"host=%s ",host);	/* Det ska vara ett mellanslag i slutet! */
  if (status != 0)
	exit(status);

  status = which_database(envp);

  if (status != 0)
	exit(status);

  strncpy(usr,userp,21);			/* Den inloggades userid 2007-02-11	*/
/*  fprintf(stderr,"status=%d ANTARG=%d len(database)=%d\n",status,ANTARG,strlen(database));	*/
  if (argc < ANTARG+1){
    	if (strlen(database)!= 0){
		strncpy(databas,database,sizeof(databas));		/* 2005-02-24	*/
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

  strncpy(userid,argv[1],sizeof(userid));				/* 2005-02-24	*/

  strncpy(temp5,temp1,strlen(temp1));
/* DELETE FROM USR WHERE USERID = "  */
  strncat(temp5,userid,strlen(userid));/* KALLE */
/* DELETE FROM USR WHERE USERID = "KALLE  */
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
/* DELETE FROM USR WHERE USERID = "KALLE" */

  mysql_init(&my_connection);

  if (mysql_real_connect(&my_connection, host,  "olfix", "olfix", databas, 0, NULL, 0)){
/*  fprintf("USERDEL_Connection success\n");	*/

    res = mysql_query(&my_connection,temp5);

  	if (!res){
		printf("OK: USERDEL Deleted %lu rows\n",
			(unsigned long)mysql_affected_rows(&my_connection));
        }else{
	fprintf(stderr,"Error: USERDEL INSERT error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
        }
	mysql_close(&my_connection);

 } else {
	fprintf(stderr,"Error: USERDEL Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: USERDEL Connection error %d:  %s\n",
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

int which_host(char *envp[])
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
	
	strncpy(host,"localhost",10);

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
/*			fprintf(stderr,"tmp=%s\n",tmp); 	*/
			if(strstr(tmp,"HOST=")){
				tmp_pek=(strstr(tmp,"HOST="))+5;
				strncpy(host,tmp_pek,strlen(tmp_pek));
				status=0;
			}
		}
/*		fprintf(stderr," Host=%s_len=%d\n",host,strlen(host)); 	*/
		fclose(fil_pek);
	}
	else{
/*		fprintf(stderr," Host=%s_len=%d\n",host,strlen(host)); 	*/
	 	fprintf(stderr,"Error: Filen .olfixrc kan inte öppnas\n");
	}
	for (i=0;i < strlen(host);i++){
		tmp[i]=host[i];
	}
	tmp[i-1]=0;
/*	fprintf(stderr,"tmp=%s, i=%d len(tmp)=%d\n",tmp,i,strlen(tmp));	*/
	strncpy(host,tmp,strlen(tmp));
	host[strlen(tmp)]=0;
/*	fprintf(stderr,"host=%s\n",host);	*/

	return status;
}



