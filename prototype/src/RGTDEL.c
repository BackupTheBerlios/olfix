/***************************************************************************
                          RGTDEL.c  -  description
                             -------------------
    Version		 : 0.4
    begin                : Mån 3 febr	2003
    modified		 : Lör 8 nov    2003
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
	INPUT: 2 st arg. USERID och TRNSID

	Kommando: ./RGTDEL JAPI USERADD

	Function: Radera record i tabell RIGHTS

	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/RGTDEL.c,v 1.3 2003/11/08 15:31:50 janpihlgren Exp $ " ;

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
/* int i;	*/
  int res;
  int status;
  const char *userp = getenv("USER");	/* vem är inloggad?	*/
  char databas[25]="olfix";
  char usr[15];				/* userid		*/

/*  for(i=0;i<argc;i++){
  	fprintf(stderr,"argv%d = %s\n",i,argv[i]);
  }
*/

  char temp1[]="DELETE FROM RIGHTS WHERE USERID = \"";
  char temp2[]="\"";
  char temp5[200]="";
  char temp6[]=" AND TRNSID =\"";
  char userid[9]="";
  char trnsid[9]="";

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

  strncpy(userid,argv[1],strlen(argv[1]));
  strncpy(trnsid,argv[2],strlen(argv[2]));

  strncpy(temp5,temp1,strlen(temp1));
/* DELETE FROM RIGHTS WHERE USERID = "  */
  strncat(temp5,userid,strlen(userid));/* KALLE */
/* DELETE FROM RIGHTS WHERE USERID = "KALLE  */
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
/* DELETE FROM RIGHTS WHERE USERID = "KALLE" */
  strncat(temp5,temp6,strlen(temp6));
/* DELETE FROM RIGHTS WHERE USERID = "KALLE" AND TRNSID ="  */
  strncat(temp5,trnsid,strlen(trnsid)); /* USERADD */
/* DELETE FROM RIGHTS WHERE USERID = "KALLE" AND TRNSID ="USERADD  */
  strncat(temp5,temp2,strlen(temp2));
/* DELETE FROM RIGHTS WHERE USERID = "KALLE" AND TRNSID ="USERADD"  */
/*  fprintf(stderr,"SQLkommando= %s\n",temp5);				*/

  mysql_init(&my_connection);

  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
/*  fprintf(stdout,"RGTDEL Connection success\n");	*/

    	res = mysql_query(&my_connection,temp5);
/*	fprintf(stderr,"RGTDEL res = %d\n",res);	*/
/*	fprintf(stdout,"RGTDEL affeted rows = %lu rows\n",(unsigned long)mysql_affected_rows(&my_connection));	*/
	if ((unsigned long)mysql_affected_rows(&my_connection) < 1){
		fprintf(stderr,"Error: RGTDEL DELETE ERROR: Ingen post raderad\n");
        }else{
		fprintf(stdout,"OK: RGTDEL Deleted %lu rows\n",(unsigned long)mysql_affected_rows(&my_connection));
	}
	mysql_close(&my_connection);
 } else {
	fprintf(stderr,"Error: RGTDEL Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: RGTDEL Connection error %d:  %s\n",
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
