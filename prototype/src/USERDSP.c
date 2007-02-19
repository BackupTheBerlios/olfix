/***************************************************************************
                          USERDSP.c  -  description
                             -------------------
    Version		 : 0.3
    begin                : Ons  13  nov	 2002
    modified		 : Tors 24  febr 2005
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
	INPUT: 1 st arg. USERID

	Kommando: ./USERDSP userid funktion

	Function: Visa all information för userid i tabell USR

	OUTPUT: USERID, NAMN, AVD, GRUPP samt errornb och error (text)

*/
/*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/USERDSP.c,v 1.5 2007/02/19 06:42:51 janpihlgren Exp $ " ;

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
/* int i;	*/
  int res;
  int status;
  const char *userp = getenv("USER");	/* vem är inloggad?	*/
  char databas[25]="olfix";
  char usr[21];				/* userid 2007-02-11 Utökad från 15 till 21	*/

  char temp1[]="SELECT USERID, NAMN, AVD, GRUPP FROM USR WHERE USERID = \"";
  char temp2[]="\"";
  char temp5[200]="";
  char userid[21]="";			/* 20070211 */

/*  for (i=0;i< argc;i++){
  	fprintf(stderr,"USERDSPmain argv%d = %s\n",i,argv[i]);
  }
*/

/* ================================================================================ */
/* 		Val av databas, START						    */
/* ================================================================================ */

  status = which_database(envp);

  if (status != 0)
	exit(status);

  strncpy(usr,userp,21);			/* Den inloggades userid	*/
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

  if (argv[1] != NULL){
  	strncpy(userid,argv[1],sizeof(userid));			/* 2005-02-24	*/
  }
  else{
  	fprintf(stderr,"Error: USERDSP: Ange userid!\n");
	exit(-1);
  }

//  strncpy(userid,argv[1],strlen(argv[1]));

  strncat(temp5,temp1,strlen(temp1));
/* SELECT USERID,NAMN,AVD,GRUPP FROM USR WHERE USERID = "  */
  strncat(temp5,userid,strlen(userid));/* KALLE */
/* SELECT USERID,NAMN,AVD,GRUPP FROM USR WHERE USERID = "KALLE  */
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
/* SELECT USERID,NAMN,AVD,GRUPP FROM USR WHERE USERID = "KALLE" */
/*  fprintf(stderr,"RGTDSPmain: temp5 = %s\n",temp5);		*/

  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
/*  fprintf(stdout,"RGTDSPmain:Connection success\n");		*/

  res = mysql_query(&my_connection,temp5);
  if (res){
	fprintf(stderr,"Error: USERDSP SELECT error: %s\n",mysql_error(&my_connection));
  }else{
	res_ptr=mysql_store_result(&my_connection);
	if (res_ptr){
		sqlrow=mysql_fetch_row(res_ptr);
		if (sqlrow > 0){
/*		fprintf(stderr,"sqlrow=%d\n",sqlrow);	*/
/*	 	fprintf(stdout,"Fetched data....}");		*/
			fprintf(stdout,"1:%s  ",sqlrow[0]);
			fprintf(stdout,"2:%s  ",sqlrow[1]);
			fprintf(stdout,"3:%s  ",sqlrow[2]);
			fprintf(stdout,"4:%s  ",sqlrow[3]);
			fprintf(stdout,"\n");
		}else{
			fprintf(stderr,"Error: USERDSP. User %s finns ej!\n",userid);
		}
	if (mysql_errno(&my_connection))  {
		fprintf(stderr,"Error: USERDSP Retriev error:  %s\n", mysql_error(&my_connection));
		}
	}
	mysql_free_result(res_ptr);
	}
	mysql_close(&my_connection);

  	} else {
    	fprintf(stderr,"Error: USERDSP Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: USERDSP Connection error %d:  %s\n",
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
