/***************************************************************************
                          AR2UPD.c  -  description
                             -------------------
			     Uppdaterar LAGERSTELLEREG
    Version		 : 0.1
    begin                : Sön 27 mars	2005
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
	INPUT:

	Kommando: ./AR2UPD  val artikelnr data

	Function: Uppdatera angivet val i tabellen LAGERSTELLEREG


	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/AR2UPD.c,v 1.1 2005/03/27 06:52:33 janpihlgren Exp $ " ;

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
#define ANTARG 4

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

  char temp1a[]="UPDATE LAGERSTELLEREG SET RESERVERAT = RESERVERAT + ";
  char temp2[]=" WHERE ARTIKELNR = ";
  char temp5[TEXTSIZE+200]="";

  char val[3]="0";			/* Vad ska uppdateras (1=RESERVERAT) */
  int felt=0;				/* Integer av val */
  char artikelnr[31]="";		/* ARTIKELNR */
  char data[61]="";			/* Det nya värdet */

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

   strncpy(val,argv[1],sizeof(val));
   strncpy(artikelnr,argv[2],sizeof(artikelnr));
   strncpy(data,argv[3],sizeof(data));
   felt=atoi(val);
/*    fprintf(stderr,"AR2UPDmain1: argv1 = %s argv2 = %s len text=%d\n",ptyp,txt,strlen(txt));	*/
/*    fprintf(stderr,"AR2UPDmain: argv2 = %s\n",txt);						*/
  if (felt < 1){
  	fprintf(stderr,"Error: Måste sätta val större än 0!\n");
	exit(1);
  }
  if(felt == 1){
  	strncpy(temp5,temp1a,strlen(temp1a));
	/* UPDATE LAGERSTELLEREG SET RESERVERAT =	*/
  }
  strncat(temp5,"'",1);
  strncat(temp5,data,strlen(data));
  strncat(temp5,"'",1);
/*  fprintf(stderr,"AR2UPDmain2: temp5=%s\n",temp5);	*/
/* UPDATE LAGERSTELLEREG SET RESERVERAT = 'data' */
  strncat(temp5,temp2,strlen(temp2)); /* WHERE ARTIKELNR =  */
/* UPDATE LAGERSTELLEREG SET RESERVERAT = 'txt, WHERE ARTIKELNR =    */
  strncat(temp5,"'",1);
/*  fprintf(stderr,"AR2UPDmain3: temp5=%s\n",temp5);	*/
  strncat(temp5,artikelnr,strlen(artikelnr));
/*  fprintf(stderr,"AR2UPDmain4: temp5=%s\n",temp5);	*/
/* UPDATE LAGERSTELLEREG SET RESERVERAT = 'data' WHERE ARTIKELNR = '1000-1001' */
  strncat(temp5,"'",1);

/* fprintf(stderr,"AR2UPDmain: temp5=%s\n",temp5);		*/

  mysql_init(&my_connection);

  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
/*    fprintf(stderr,"AR2UPD:Connection success\n");	*/
    res = mysql_query(&my_connection,temp5);
  	if (!res){
		fprintf(stderr,"OK: AR2UPD Inserted %lu rows\n",
			(unsigned long)mysql_affected_rows(&my_connection));
        }else{
	fprintf(stderr,"Error: AR2UPD UPDATE error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
	}
	mysql_close(&my_connection);

 } else {
	fprintf(stderr,"Error: AR2UPD Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: AR2UPD Connection error %d:  %s\n",
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

