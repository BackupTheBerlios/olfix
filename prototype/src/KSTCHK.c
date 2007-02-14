/***************************************************************************
                          KSTCHK.c  -  description
                             -------------------
    Version		 : 0.4
    begin                : Lör  1 mars 2003
    modified		 : Ons 14 febr 2007
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
	INPUT: ARID KSTALLE
	Function: gör  SELECT * FROM KSTALLE WHERE ARID = "AC" AND KSTALLE = 9037" i databasen olfix

	OUTPUT: ARID, KSTALLE, BENAMNING från tabellen KSTALLE samt
	errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/KSTCHK.c,v 1.4 2007/02/14 14:56:29 janpihlgren Exp $ " ;

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
  char database[15]="";

int main(int argc, char *argv[], char *envp[])
{
  int res;
  int status;
  const char *userp = getenv("USER");	/* vem är inloggad?	*/
  char databas[25]="olfix";
  char usr[21];				/* userid 20070214 utökat från 15 till 21 tecken */

  char temp1[]="SELECT * FROM KSTALLE WHERE (ARID = \"";
  char temp1b[]=" AND KSTALLE = \"";
  char temp2[]="\"";
  char temp4[]=")";
  char temp5[200]="";
  char arid[3]="";
  char kstalle[5]="";
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
/*  fprintf(stderr,"ANTARG=%d,argv[ANTARG]=%s\n",ANTARG,argv[ANTARG]);	*/
/* Om usr (userid) börjar på 'test' eller 'prov' använd databas 'olfixtst' */
  if (strncmp(usr,"test",4)==0 || strncmp(usr,"prov",4)==0 ) {
  	strncpy(databas,"olfixtst",15);
  }
/* fprintf(stderr,"Databas=%s\n",databas);	*/
/* ================================================================================ */
/* 		Val av databas, END!						    */
/* ================================================================================ */

  strncpy(arid,argv[1],sizeof(arid));			/* 2005-02-24	*/
  strncpy(kstalle,argv[2],sizeof(kstalle));


  strncpy(temp5,temp1,strlen(temp1));
/* SELECT * FROM KSTALLE WHERE (ARID = "  */
  strncat(temp5,arid,strlen(arid));/* AC */
/* SELECT * FROM KSTALLE WHERE (ARID = "AC  */
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
/* SELECT * FROM KSTALLE WHERE (ARID = "AC" */
  strncat(temp5,temp1b,strlen(temp1b));
/* SELECT * FROM KSTALLE WHERE (ARID = "AC" AND KSTALLE = " */
  strncat(temp5,kstalle,strlen(kstalle));
/* SELECT * FROM KSTALLE WHERE (ARID = "AC" AND KSTALLE = "9037 */
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp4,strlen(temp4));
/* SELECT * FROM KSTALLE WHERE (ARID = "AC" AND KSTALLE = "9037") */

/*  fprintf(stderr,"KSTCHKmain: temp5 = %s\n",temp5);	*/

  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
/*  fprintf(stderr,"KSTCHK:Connection success\n");	*/
  res = mysql_query(&my_connection,temp5);
  if (res){
	fprintf(stderr,"Error: KSTCHK SELECT error: %s\n",mysql_error(&my_connection));
        }
	else{
		res_ptr=mysql_store_result(&my_connection);
		if (res_ptr){
/*			fprintf(stderr,"KSTCHK Retrieved %lu rows\n",(unsigned long)mysql_num_rows(res_ptr));	*/
			if((unsigned long)mysql_num_rows(res_ptr) > 0){ /* En rad har hittats */
				status=0;
			}else{						/* Ingen rad hittades */
				status=-1;
			}

			if (mysql_errno(&my_connection))  {
				fprintf(stderr,"Error: KSTCHK Retriev error:  %s\n", mysql_error(&my_connection));
			}
		}
		mysql_free_result(res_ptr);
	}
	mysql_close(&my_connection);
 }
  else {
    	fprintf(stderr,"Error: KSTCHK Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: KSTCHK Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
	}
    }
if(status == 0){
	fprintf(stdout,"OK: KSTCHK Status = %d\n",status);
}
if(status != 0){
	fprintf(stderr,"Error: KSTCHK Kostnadställe %s finns inte!\n",kstalle);
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

