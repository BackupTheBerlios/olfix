/***************************************************************************
                          ARICHK.c  -  description
                             -------------------
    Version		 : 0.2
    begin                : Mån 2  dec	2002
    modified		 : Mån 27 okt   2003
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
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/C/Attic/ARICHK.c,v 1.1 2004/05/03 04:42:57 janpihlgren Exp $ " ;

/*
	INPUT: 2 st arg. ARID

	Kommando: ./ARCHK arid [databas]

	Function: Kontrollera om bokföringsår arid existerar i tabell BOKFAR

	OUTPUT: errornb och error (text)

*/
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mysql.h"

  MYSQL my_connection;
  MYSQL_RES *res_ptr;
  MYSQL_ROW sqlrow;
int which_database(char *envp[]);

  char database[15]="";

int main(int argc, char *argv[], char *envp[])
{
//  MYSQL my_connection;
  int res;
  int status;
  const char *userp = getenv("USER");	// vem är inloggad?
  char databas[25]="olfix";
  char usr[15];		// userid

  char temp1[]="SELECT ARID FROM BOKFAR WHERE ARID = \"";
  char temp2[]="\"";
  char temp5[200]="";
  char arid[4];



/* ================================================================================ */
/* 		Val av databas, START						    */
/* ================================================================================ */

  status = which_database(envp);

  if (status != 0)
	exit(status);

  strncpy(usr,userp,15);			// Den inloggades userid

  if (argc<3){
    	if (strlen(database)!= 0){
		strncpy(databas,database,15);
	}else{
  		strncpy(databas,"olfixtst",15);	// olfixtst = testföretag
	}
  }else{
	if (strlen(argv[2]) != 0){
  		if (strncmp(argv[2],"99",2)==0){
			strncpy(databas,"olfixtst",15);
		}else{
  			strncpy(databas,argv[2],15);
  		}
  	}
  }
/* Om usr (userid) börjar på 'test' eller 'prov' använd databas 'olfixtst' */
  if (strncmp(usr,"test",4)==0 || strncmp(usr,"prov",4)==0 ) {
  	strncpy(databas,"olfixtst",15);
  }
/* fprintf(stderr,"Databas=%s\n",databas); */
/* ================================================================================ */
/* 		Val av databas, END!						    */
/* ================================================================================ */

/*  fprintf(stderr,"ARICHKmain: argv1 = %s, argv2 = %s\n",argv[1],argv[2]); */
  strncpy(arid,argv[1],4);
/*  fprintf(stderr,ARICHKmain: ari = %s\n",ari); */

  strncat(temp5,temp1,strlen(temp1));
/* SELECT ARID FROM BOKFAR WHERE ARID = "  */
/*  fprintf(stderr,"ARICHKmain: temp5 (1) = %s\n",temp5); */
  strncat(temp5,arid,4);/* AC */
/* SELECT ARID FROM BOKFAR WHERE ARID = "AC */
/*  fprintf(stderr,"ARICHKmain: temp5 (2) = %s\n",temp5); */

  strncat(temp5,temp2,strlen(temp2)); /*  "     */
/* SELECT ARID FROM BOKFAR WHERE ARID = "AC" */
/*  fprintf(stderr,"ARICHKmain: temp5 = %s\n",temp5); */

  mysql_init(&my_connection);
if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
/*	fprintf(stdout,"ARICHKmain:Connection success\n"); */
	res = mysql_query(&my_connection,temp5);
/*  	fprintf(stderr,"ARICHKmain: res= %d\n",res); */
  	if (res){
		fprintf(stderr,"Error: ARICHK Selection error: %s\n", mysql_error(&my_connection));
	}
	else {
		res_ptr = mysql_store_result(&my_connection);
		if (res_ptr){
/*			fprintf(stderr,"ARICHKmain:Retrieved %lu rows\n",(unsigned long)mysql_num_rows(res_ptr)); */
			if((unsigned long)mysql_num_rows(res_ptr) > 0){ /* En rad har hittats */
				status=0;
			}else{						/* Ingen rad hittades */
				status=-1;
			}
    			if (mysql_errno(&my_connection)) {
    				fprintf(stderr,"Error: ARICHK Retrieve error  %s\n",mysql_error(&my_connection));
			}
		}
		mysql_free_result(res_ptr);
	}
	mysql_close(&my_connection);
}
else {
	fprintf(stderr,"Error: ARICHK: Connection faild\n");
	if (mysql_errno(&my_connection))  {
		fprintf(stderr,"Error: ARICHK: Connection error: %d  %s\n",
			mysql_errno(&my_connection),mysql_error(&my_connection));
	}
}
  fprintf(stdout,"OK: ARICHK: Jobb klart. Status = %d\n",status);
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
				strncpy(home,home_pek,strlen(home));
			}
/*			fprintf(stderr,"home_pek=%d %s\n",home_pek,home_pek); */
		}
	}
/*	fprintf(stderr,"home=%s\n",home); */
	strncpy(filename,home,strlen(home));
	strncat(filename,resource,strlen(resource));

/*	fprintf(stderr,"filename=%s\n",filename); */
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
//	fprintf(stderr,"tmp=%s, i=%d len tmp=%d\n",tmp,i,strlen(tmp));
	strncpy(database,tmp,strlen(tmp));
	database[strlen(tmp)]=0;

	return status;
}
