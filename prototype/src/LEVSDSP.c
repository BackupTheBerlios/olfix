/***************************************************************************
                          LEVSDSP.c  -  description
                             -------------------
    Version		 : 0.1
    begin                : Ons 4 febr 2004
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

	Kommando: ./LEVSDSP levsett [databas]

	Function: H?mta data f?r angivet leveranss?tt fr?n tabellen LEVSETT

	OUTPUT: data, errornb och error (text)

 ***************************************************************************/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/LEVSDSP.c,v 1.2 2004/02/07 08:13:46 janpihlgren Exp $ " ;

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
  const char *userp = getenv("USER");	// vem ?r inloggad?
  char databas[25]="olfix";
  char usr[15];		// userid

  char temp1[]="SELECT * FROM LEVSETT WHERE LEVSETTNR = \"";
  char temp2[]="\"";
  char temp5[200]="";
  char betvilkor[8];
/*  fprintf(stderr,"argc=%d \n",argc); */
  if (argc <2){
  	fprintf(stderr,"Error: Leveranss?tt saknas.\n");
	exit(-1);
  }
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
  		strncpy(databas,"olfixtst",15);	// olfixtst = testf?retag
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
/* Om usr (userid) b?rjar p? 'test' eller 'prov' anv?nd databas 'olfixtst' */
  if (strncmp(usr,"test",4)==0 || strncmp(usr,"prov",4)==0 ) {
  	strncpy(databas,"olfixtst",15);
  }
/* fprintf(stderr,"Databas=%s\n",databas);  */
/* ================================================================================ */
/* 		Val av databas, END!						    */
/* ================================================================================ */

/*  fprintf(stderr,"betvilk=%d\n",betvilk); */

  strncpy(betvilkor,argv[1],8);
  strncat(temp5,temp1,strlen(temp1));
/* SELECT * FROM BETVILKOR WHERE BETVILKOR = "  */
  strncat(temp5,betvilkor,8);/* AC */
/* SELECT * FROM BETVILKOR WHERE BETVILKOR = "1  */
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
/* SELECT * FROM BETVILKOR WHERE BETVILKOR = "1" */
/*  fprintf(stderr,"LEVSDSP: temp5 = %s\n",temp5); */

  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
/*  fprintf(stdout,"BARDSPmain:Connection success\n"); */
  	res = mysql_query(&my_connection,temp5);
  	if (res){
		fprintf(stderr,"Error: LEVSDSP SELECT error: %s\n",mysql_error(&my_connection));
  	}
  	else{
		res_ptr=mysql_store_result(&my_connection);
		if (res_ptr){
/*			fprintf(stderr,"Retrieved %lu rows\n",(unsigned long)mysql_num_rows(res_ptr)); */
			if(mysql_num_rows(res_ptr)>0){
				sqlrow=mysql_fetch_row(res_ptr);
				fprintf(stdout,"OK: ");
				fprintf(stdout,"01: %s ",sqlrow[0]);
				fprintf(stdout,"02: %s ",sqlrow[1]);
				fprintf(stdout,"END:");
				fprintf(stdout,"\n");
			}
			else{
				fprintf(stderr,"Error: LEVSDSP Leveranss?tt saknas!\n");
			}
			if (mysql_errno(&my_connection)){
				fprintf(stderr,"Error: LEVSDSP Retriev error:  %s\n", mysql_error(&my_connection));
			}
		}
		mysql_free_result(res_ptr);
	}
  	mysql_close(&my_connection);
  	}
  else {
  	fprintf(stderr,"Error: LEVSDSP Connection failed\n");
	if (mysql_errno(&my_connection)){
		fprintf(stderr,"Error: LEVSDSP Connection error %d:  %s\n",
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
	 	fprintf(stderr,"Error: Filen .olfixrc kan inte ?ppnas\n");
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
