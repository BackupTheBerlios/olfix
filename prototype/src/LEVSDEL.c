/***************************************************************************
                          LEVSDL.c  -  description
                             -------------------
			     Radera leveranss�tt
    Version		 : 0.1
    begin                : Fre  13 juli 2007
    modified		 : 
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
 ***************************************************************************/

/***************************************************************************
	INPUT: levvilkor

	Kommando: ./LEVSDEL levsett [databas]

	Function: H�mta data och radera ett angivet leveranss�tt fr�n tabellen LEVSETT

	OUTPUT: data, errornb och error (text)

 ***************************************************************************/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/LEVSDEL.c,v 1.1 2007/09/22 15:43:09 janpihlgren Exp $ " ;

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
  const char *userp = getenv("USER");	/* vem �r inloggad? */
  char databas[25]="olfix";
  char usr[21];

  char temp1[]="DELETE FROM LEVSETT WHERE LEVSETTNR = \"";
  char temp2[]="\"";
  char temp5[200]="";
  char betvilkor[8];
/*  fprintf(stderr,"argc=%d \n",argc); */
  if (argc <2){
  	fprintf(stderr,"Error: Leveranss�tt saknas.\n");
	exit(-1);
  }
/* ================================================================================ */
/* 		Val av databas, START						    */
/* ================================================================================ */

  status = which_database(envp);

  if (status != 0)
	exit(status);

  strncpy(usr,userp,sizeof(usr));

  if (argc<3){
    	if (strlen(database)!= 0){
		strncpy(databas,database,sizeof(databas));
	}else{
  		strncpy(databas,"olfixtst",15);	// olfixtst = testf�retag
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
/* Om usr (userid) b�rjar p� 'test' eller 'prov' anv�nd databas 'olfixtst' */
  if (strncmp(usr,"test",4)==0 || strncmp(usr,"prov",4)==0 ) {
  	strncpy(databas,"olfixtst",15);
  }
/* fprintf(stderr,"Databas=%s\n",databas);  */
/* ================================================================================ */
/* 		Val av databas, END!						    */
/* ================================================================================ */

/*  fprintf(stderr,"betvilk=%d\n",betvilk); */

  strncpy(betvilkor,argv[1],sizeof(betvilkor));		/* 2005-02-24	*/
  strncat(temp5,temp1,strlen(temp1));
/* DELETE FROM LEVSETT WHERE LEVSETTNR = "  */
  strncat(temp5,betvilkor,8);/* AC */
/* DELETE FROM LEVSETT WHERE LEVSETTNR = "1  */
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
/* DELETE FROM LEVSETT WHERE LEVSETTNR = "1" */
/*  fprintf(stderr,"LEVSDEL: temp5 = %s\n",temp5); */

  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
/*  fprintf(stdout,"BARDSPmain:Connection success\n"); */
  	res = mysql_query(&my_connection,temp5);
  	if (!res){
		fprintf(stdout,"OK: LEVSDEL Deleted %lu rows\n",
			(unsigned long)mysql_affected_rows(&my_connection));
  	}else{
	fprintf(stderr,"Error: LEVSDEL DELETE error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
	}
  	mysql_close(&my_connection);
  	}
  else {
  	fprintf(stderr,"Error: LEVSDEL Connection failed\n");
	if (mysql_errno(&my_connection)){
		fprintf(stderr,"Error: LEVSDEL Connection error %d:  %s\n",
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
	 	fprintf(stderr,"Error: Filen .olfixrc kan inte �ppnas\n");
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
