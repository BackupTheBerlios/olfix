/***************************************************************************
                          ATTBET.c  -  description
                             -------------------
    Version		 : 0.2
    begin                : Mån 18 aug 2003
    modified		 : Mån 27 okt 2003
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
	INPUT:	datum
	Function: gör  SELECT EXPIREDATUM,LEVNR,FAKTURANR,FAKTBELOPP,VALUTA INTO OUTFILE "/tmp/AttBetala.txt"
	FIELDS TERMINATED BY ','
	FROM `LEVRESK`
	where EXPIREDATUM < " 2003-09-09" and BETALD = "N"
	order by LEVNR,EXPIREDATUM,FAKTURANR;


	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/C/Attic/ATTBET.c,v 1.1 2004/05/03 04:42:57 janpihlgren Exp $ " ;

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
void display_row();

  char database[15]="";

int main(int argc, char *argv[], char *envp[])
{
  int res,i;
  int status;
  const char *userp = getenv("USER");	// vem är inloggad?
  char databas[25]="olfix";
  char usr[15];		// userid

  char temp1a[]="SELECT EXPIREDATUM,LEVNR,FAKTURANR,FAKTBELOPP,VALUTA ";
  char temp1d[]="FROM LEVRESK where EXPIREDATUM <= '";
  char temp1e[]="' and BETALD = 'N' ORDER BY EXPIREDATUM,LEVNR";
  char temp5[200]="";
  char datum[11];

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

/*  fprintf(stderr,"ATTBET: argv[1]=%s\n",argv[1]); */
  strncpy(datum,argv[1],11);
/*  fprintf(stderr,"ATTBET: datum=%s\n",datum); */
  strncpy(temp5,temp1a,strlen(temp1a));
  strncat(temp5,temp1d,strlen(temp1d));
  strncat(temp5,datum,strlen(datum));
  strncat(temp5,temp1e,strlen(temp1e));

/*  fprintf(stderr,"ATTBET: temp5=%s\n",temp5); */

  mysql_init(&my_connection);

  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
	  res = mysql_query(&my_connection,temp5);

  	if (res){
		fprintf(stderr,"Error: ATTBET SELECT error: %s\n",mysql_error(&my_connection));
        }else{
		res_ptr=mysql_store_result(&my_connection);
		if (res_ptr){
			fprintf(stdout,"OK: NR_%lu_:",(unsigned long)mysql_num_rows(res_ptr));
			while ((sqlrow=mysql_fetch_row(res_ptr)))  {
/*		 		printf("KTOLST:Fetched data....}"); */
				display_row();
				i++;
			}
			if (mysql_errno(&my_connection))  {
				fprintf(stderr,"Error: ATTBET Retriev error:  %s\n", mysql_error(&my_connection));
			}
		}
		mysql_free_result(res_ptr);
  	}
	mysql_close(&my_connection);

  } else {
    	fprintf(stderr,"Error: ATTBET Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: ATTBET Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
	}
  }
  fprintf(stdout,"\n");
  return EXIT_SUCCESS;
}

void display_row()
{
   unsigned int field_count;
   field_count=0;
	while (field_count < mysql_field_count(&my_connection))
	{
		fprintf(stdout,"%s_:",sqlrow[field_count]);
		field_count++;
	}
/*	fprintf(stdout,"\n"); */
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
