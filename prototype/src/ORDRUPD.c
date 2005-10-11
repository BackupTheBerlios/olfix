/***************************************************************************
                          ORDRUPD.c  -  description
                             -------------------
    Version		 : 0.1
    begin                : Ons 11 maj 2005
    modified		 :
    copyright            : (C) 2005 by Jan Pihlgren
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
	INPUT: ORDERNR ORDERRAD LEVERERAT RESTNOTERAT

	Kommando: ./ORDRUPD ordernr radnr levererat restnoterat

	Function: Uppdatera fälten  LEVERERAT och RESTNOTERAT i tabellen ORDERRADREG

	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/ORDRUPD.c,v 1.1 2005/10/11 04:54:27 janpihlgren Exp $ " ;

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
#define TEXTSIZE 500
#define ANTARG 5

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

  char temp1a[]="UPDATE ORDERRADREG SET LEVERERAT = LEVERERAT + \"";
  char temp1b[]=" , RESTNOTERAT = BESTELLT - LEVERERAT";
  char temp2a[]=" WHERE ORDERNR = \"";
  char temp2b[]=" AND ORDERRAD = \"";
  char temp3[]="\"";
  char temp5[TEXTSIZE]="";

  char ordernr[11]="";
  char radnr[4]="";
  char levererat[14]="";			/* levererat antal */
  char restnoterat[14]="";			/* restnoterat antal */
/*  fprintf(stderr,"ordernr=%s radnr=%s levererat=%s restnoterat=%s\n",argv[1],argv[2],argv[3],argv[4]);  */
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
 fprintf(stderr,"Databas=%s\n",databas);
/* ================================================================================ */
/* 		Val av databas, END!						    */
/* ================================================================================ */

   strncpy(ordernr,argv[1],sizeof(ordernr));
   strncpy(radnr,argv[2],sizeof(radnr));
   strncpy(levererat,argv[3],sizeof(levererat));
   strncpy(restnoterat,argv[4],sizeof(restnoterat));

/*    fprintf(stderr,"ORDRUPDmain1: argv1 = %s argv2 = %s len text=%d\n",ptyp,txt,strlen(txt));	*/
/*    fprintf(stderr,"ORDRUPDmain: argv2 = %s\n",txt);						*/

  strncpy(temp5,temp1a,strlen(temp1a));
/* UPDATE ORDERRADREG SET LEVERERAT = "  */
  strncat(temp5,levererat,strlen(levererat));
  strncat(temp5,temp3,strlen(temp3));
/* UPDATE ORDERRADREG SET LEVERERAT = LEVERERAT +  "15"  */
  strncat(temp5,temp1b,strlen(temp1b));
/*  UPDATE ORDERRADREG SET LEVERERAT = LEVERERAT + "15" , SET RESTNOTERAT = BESTELLT - LEVERERAT */
  strncat (temp5,temp2a,strlen(temp2a));
/*  UPDATE ORDERRADREG SET LEVERERAT = LEVERERAT + "15" , SET RESTNOTERAT = BESTELLT - LEVERERAT WHERE ORDERNR = "  */
  strncat(temp5,ordernr,strlen(ordernr));
  strncat(temp5,temp3,strlen(temp3));
/*  UPDATE ORDERRADREG SET LEVERERAT = LEVERERAT + "15" , SET RESTNOTERAT = BESTELLT - LEVERERAT WHERE ORDERNR = "1001"  */
  strncat(temp5,temp2b,strlen(temp2b));
/*  UPDATE ORDERRADREG SET LEVERERAT = LEVERERAT + "15" , SET RESTNOTERAT = BESTELLT - LEVERERAT WHERE ORDERNR = "1001"  AND ORDERRAD = " */
  strncat(temp5,radnr,strlen(radnr));
  strncat(temp5,temp3,strlen(temp3));
/*  UPDATE ORDERRADREG SET LEVERERAT = LEVERERAT + "15" , SET RESTNOTERAT = BESTELLT - LEVERERAT WHERE ORDERNR = "1001"  AND ORDERRAD = "010" */

/* fprintf(stderr,"ORDRUPDmain: temp5=%s\n",temp5);	*/

  mysql_init(&my_connection);

  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
/*    fprintf(stderr,"ORDRUPD:Connection success\n");	*/
    res = mysql_query(&my_connection,temp5);
  	if (!res){
		if ((unsigned long)mysql_affected_rows(&my_connection) < 1){
			fprintf(stderr,"Error: ORDRUPD Updated %lu rows\n",(unsigned long)mysql_affected_rows(&my_connection));
		}else{
		fprintf(stderr,"OK: ORDRUPD Updated %lu rows\n",
			(unsigned long)mysql_affected_rows(&my_connection));
		}
        }else{
	fprintf(stderr,"Error: ORDRUPD UPDATE error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
	}
	mysql_close(&my_connection);

 } else {
	fprintf(stderr,"Error: ORDRUPD Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: ORDRUPD Connection error %d:  %s\n",
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

