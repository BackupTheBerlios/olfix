/***************************************************************************
                          RGTCHK.c  -  description
                             -------------------
    version		 : 0.4
    begin                : Ons   6 nov	2002
    modified		 : Tors 24 febr 2005
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
	INPUT: 2 st arg. USERID och TRNSID

	Kommando: ./RGTCHK userid funktion

	Function: Visa behörghet för userid och funktion i tabell RIGHTS

	OUTPUT: errornb och error (text)

*/
/*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/RGTCHK.c,v 1.4 2005/02/24 09:51:50 janpihlgren Exp $ " ;

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
  char usr[15];				/* userid		*/

  char temp1[]="SELECT USERID,TRNSID FROM RIGHTS WHERE USERID = \"";
  char temp2[]="\"";
  char temp5[200]="";
  char temp6[16]=" AND TRNSID = \"";
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
/*  fprintf(stderr,"ANTARG=%d,argv[ANTARG]=%s\n",ANTARG,argv[ANTARG]);		*/
/* Om usr (userid) börjar på 'test' eller 'prov' använd databas 'olfixtst' 	*/
  if (strncmp(usr,"test",4)==0 || strncmp(usr,"prov",4)==0 ) {
  	strncpy(databas,"olfixtst",15);
  }
/* fprintf(stderr,"Databas=%s\n",databas);	*/
/* ================================================================================ */
/* 		Val av databas, END!						    */
/* ================================================================================ */

/*  fprintf(stderr,"RGTCHKmain: argv1 = %s, argv2 = %s\n",argv[1],argv[2]);		*/

  strncpy(userid,argv[1],sizeof(userid));	/* 2005-02-24	*/
  strncpy(trnsid,argv[2],sizeof(trnsid));	/* 2005-02-24	*/

  strncpy(temp5,temp1,strlen(temp1));
/* SELECT USERID,TRNSID FROM RIGHTS WHERE USERID = "  					*/
/*  fprintf(stderr,"1.RGTCHKmain: temp5 = %s\n",temp5);					*/
  strncat(temp5,userid,strlen(userid));/* KALLE */
/* SELECT USERID,TRNSID FROM RIGHTS WHERE USERID = "KALLE  				*/
/*  fprintf(stderr,"2.RGTCHKmain: temp5 = %s\n",temp5);					*/
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
/* SELECT USERID,TRNSID FROM RIGHTS WHERE USERID = "KALLE" 				*/
/*  fprintf(stderr,"3.RGTCHKmain: temp5 = %s\n",temp5);					*/
  strncat(temp5,temp6,strlen(temp6));
/*  SELECT USERID,TRNSID FROM RIGHTS WHERE USERID = "KALLE" AND TRNSID ="  		*/
/*  fprintf(stderr,"4.RGTCHKmain: temp5 = %s\n",temp5);					*/
  strncat(temp5,trnsid,strlen(trnsid)); /* USERADD */
/* SELECT USERID,TRNSID FROM RIGHTS WHERE USERID = "KALLE" AND TRNSID ="USERADD  	*/
/*  fprintf(stderr,"5.RGTCHKmain: temp5 = %s\n",temp5);					*/
  strncat(temp5,temp2,strlen(temp2));
/* SELECT USERID,TRNSID FROM RIGHTS WHERE USERID = "KALLE" AND TRNSID ="USERADD"  	*/
/*  fprintf(stderr,"RGTCHKmain: temp5 = %s\n",temp5);					*/

  mysql_init(&my_connection);

if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
/*	fprintf(stdout,"RGTCHKmain:Connection success\n");	*/
	res = mysql_query(&my_connection,temp5);
/*  	fprintf(stderr,"RGTCHKmain: res= %d\n",res);		*/
  	if (res){
		fprintf(stderr,"Error: RGTCHK_Selection error: %s\n", mysql_error(&my_connection));
	}
	else {
		res_ptr = mysql_store_result(&my_connection);
		if (res_ptr){
			fprintf(stderr,"RGTCHKmain:Retrieved %lu rows\n",(unsigned long)mysql_num_rows(res_ptr));
			if((unsigned long)mysql_num_rows(res_ptr) > 0){ /* En rad har hittats */
				status=0;
			}else{						/* Ingen rad hittades */
				status=-1;
			}
    			if (mysql_errno(&my_connection)) {
    				fprintf(stderr,"Error: RGTCHK_Retrieve error  %s\n",mysql_error(&my_connection));
			}
		}
		mysql_free_result(res_ptr);
	}
	mysql_close(&my_connection);
}
else{
	fprintf(stderr,"Error: RGTCHK_Connection faild\n");
	if (mysql_errno(&my_connection))  {
		fprintf(stderr,"Error: RGTCHK_Connection error: %d  %s\n",
			mysql_errno(&my_connection),mysql_error(&my_connection));
	}
}
if(status == 0){
	fprintf(stdout,"OK: RGTCHK_Status = %d\n",status);
}
if(status != 0){
	fprintf(stderr,"Error: RGTCHK_%s har inte behörighet till %s\n",userid,trnsid);
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
