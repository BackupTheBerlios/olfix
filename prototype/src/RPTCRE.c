/***************************************************************************
                          RPTCRE.c  -  description
                             -------------------
    Version		 : 0.3
    begin                : Mån  25 aug  2003
    modified		 : Tors 24 febr 2005
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
	INPUT: 1 argument med en sqlfråga
	Function: en sqlfråga till databasen olfix

	OUTPUT: errornb och error (text)
*/

 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/RPTCRE.c,v 1.3 2005/02/24 10:22:06 janpihlgren Exp $ " ;

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

  FILE *fp;

int which_database(char *envp[]);
void display_header();
void display_row();

char database[15]="";

int main(int argc, char *argv[], char *envp[])
{
  int res;
  int status;
  const char *userp = getenv("USER");	/* vem är inloggad?	*/
  char databas[25]="olfix";
  char usr[15];				/* userid		*/
//  char sqlquery[1000]="SELECT * FROM VERRAD";
  char sqlquery[1000]="";

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
/*  fprintf(stderr,"ANTARG=%d,argv[ANTARG]=%s\n",ANTARG,argv[ANTARG]);	*/
/* Om usr (userid) börjar på 'test' eller 'prov' använd databas 'olfixtst' */
  if (strncmp(usr,"test",4)==0 || strncmp(usr,"prov",4)==0 ) {
  	strncpy(databas,"olfixtst",15);
  }
/* fprintf(stderr,"Databas=%s\n",databas);	*/
/* ================================================================================ */
/* 		Val av databas, END!						    */
/* ================================================================================ */

  strncpy(sqlquery,argv[1],sizeof(sqlquery));		/* 2005-02-24	*/

  fp = fopen ("/tmp/rptcre.txt","a");		/* skapa och öppna resultatfilen	*/
  mysql_init(&my_connection);

  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
/*  fprintf(stderr,"RPTCRE:Connection success\n");	*/
	res = mysql_query(&my_connection,sqlquery);

  	if (res){
		fprintf(stderr,"Error: RPTCRE SELECT error: %s\n",mysql_error(&my_connection));
        }else{
		res_ptr=mysql_use_result(&my_connection);
		if (res_ptr){
/*			i=1;
			fprintf(stderr,"RPTCRE:Retrieved %lu rows\n",(unsigned long)mysql_num_rows(res_ptr));
			fprintf(stdout,"NR_%lu_:",(unsigned long)mysql_num_rows(res_ptr));
*/
			display_header();
			while ((sqlrow=mysql_fetch_row(res_ptr)))  {
/*				fprintf(stderr,"RPTCRE:Fetched data....}");	*/
/*				fprintf(stdout,"%d ",i);			*/
				display_row();
/*				i++;						*/
			}
			if (mysql_errno(&my_connection))  {
				fprintf(stderr,"Error: RPTCRE Retriev error:  %s\n", mysql_error(&my_connection));
			}
		}
		mysql_free_result(res_ptr);
	}
	mysql_close(&my_connection);

  } else {
    	fprintf(stderr,"Error: RPTCRE Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: RPTCRE Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
	}
    }
  fprintf(stdout,"\n");
  fclose(fp);			/* Stäng resultatfilen	*/
  return EXIT_SUCCESS;
}

void display_header()
{
	MYSQL_FIELD *field_ptr;
	while((field_ptr = mysql_fetch_field(res_ptr)) != NULL){
/*		fprintf(stdout,"%s,",field_ptr->name);			*/
		fputs(field_ptr->name,fp);
		fputs(",",fp);
	}
/*	fprintf(stdout,"\n");						*/
   	fputs("\n",fp);
}


void display_row()
{
   unsigned int field_count;
   field_count=0;
   while (field_count < mysql_field_count(&my_connection)){
/*		fprintf(stdout,"%s,",sqlrow[field_count]);		*/
		fputs(sqlrow[field_count],fp);
		fputs(",",fp);
		field_count++;
   }
   	fputs("\n",fp);
/*	fprintf(stdout,"\n");						*/
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
