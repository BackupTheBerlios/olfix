/***************************************************************************
                          DBOKRPT.c  -  description
                          -------------------------
			  Dagboksrapport

    Version		 : 0.3
    begin                : L�r 10 april 2004
    modified		 : Tis 13 febr  2007
    copyright            : (C) 2004 by Jan Pihlgren
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
	INPUT: arid,fromdatum,tomdatum	(Bokf�rings�r, Fr�n och med datum, Till och med datum)
	Function: g�r SELECT
	VERHUVUD.VERDATUM,VERRAD.VERNR,VERHUVUD.VERTEXT,VERRAD.KTONR,
	KTOPLAN.BENAMNING,VERRAD.DK,VERRAD.BELOPP
	FROM VERRAD
	LEFT JOIN KTOPLAN ON KTOPLAN.KTONR = VERRAD.KTONR AND VERRAD.ARID = KTOPLAN.ARID
	LEFT JOIN VERHUVUD ON VERRAD.ARID = VERHUVUD.ARID AND VERRAD.VERNR=VERHUVUD.VERNR
	WHERE VERRAD.ARID = "AD"
	AND VERHUVUD.VERDATUM >= "2003-06-10"
	AND VERHUVUD.VERDATUM <= "2003-10-16"
	ORDER BY VERHUVUD.VERDATUM,VERNR,VERRAD.KTONR,


	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/DBOKRPT.c,v 1.3 2007/02/13 07:34:08 janpihlgren Exp $ " ;

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql.h"
#define ANTARG 4

  MYSQL my_connection;
  MYSQL_RES *res_ptr;
  MYSQL_ROW sqlrow;


void display_row();
int which_database(char *envp[]);
char database[15]="";

int main(int argc, char *argv[], char *envp[])
{
  int i;
  int res;
  int status;
  const char *userp = getenv("USER");	/* vem �r inloggad?	*/
  char databas[25]="olfix";
  char usr[21];				/* userid 20070213 ut�kat fr�n 15 till 21 tecken */

  char temp1a[]="SELECT VERHUVUD.VERDATUM,VERRAD.VERNR,VERHUVUD.VERTEXT,VERRAD.KTONR,KTOPLAN.BENAMNING,VERRAD.DK,VERRAD.BELOPP FROM VERRAD ";
  char temp1b[]="LEFT JOIN KTOPLAN ON KTOPLAN.KTONR = VERRAD.KTONR AND VERRAD.ARID = KTOPLAN.ARID ";
  char temp1c[]="LEFT JOIN VERHUVUD ON VERRAD.ARID = VERHUVUD.ARID AND VERRAD.VERNR=VERHUVUD.VERNR ";
  char temp1d[]="WHERE VERRAD.ARID = ";
  char temp1e[]=" AND VERHUVUD.VERDATUM >= ";
  char temp1f[]=" AND VERHUVUD.VERDATUM <= ";
  char temp1g[]=" ORDER BY VERHUVUD.VERDATUM,VERNR,VERRAD.KTONR";
  char temp2[]="\"";
  char temp5[400]="";
  char arid[3]="";
  char fromdatum[11]="";
  char tomdatum[11]="";

/*  for (i=0;i<argc;i++){
  	fprintf(stderr,"argc=%d, argv[%d]=argv[%s]\n",argc,i,argv[i]);
  }	*/
/* ================================================================================ */
/* 		Val av databas, START						    */
/* ================================================================================ */

  status = which_database(envp);

  if (status != 0)
	exit(status);

  strncpy(usr,userp,sizeof(usr));			/* Den inloggades userid 20070213 */
/*  fprintf(stderr,"status=%d ANTARG=%d len(database)=%d\n",status,ANTARG,strlen(database));	*/
  if (argc < ANTARG+1){
    	if (strlen(database)!= 0){
		strncpy(databas,database,15);
	}else{
  		strncpy(databas,"olfixtst",15);	/* olfixtst = testf�retag	*/
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
/* Om usr (userid) b�rjar p� 'test' eller 'prov' anv�nd databas 'olfixtst' */
  if (strncmp(usr,"test",4)==0 || strncmp(usr,"prov",4)==0 ) {
  	strncpy(databas,"olfixtst",15);
  }
/* fprintf(stderr,"Databas=%s\n",databas);	*/
/* ================================================================================ */
/* 		Val av databas, END!						    */
/* ================================================================================ */

  strncpy(arid,argv[1],sizeof(arid));			/* 2005-02-23*/
  strncpy(fromdatum,argv[2],sizeof(fromdatum));		/* 2005-02-23*/
  strncpy(tomdatum,argv[3],sizeof(tomdatum));		/* 2005-02-23*/
/*  fprintf(stderr,"arid=%s,fromdatum=%s,tomdatum=%s\n",arid,fromdatum,tomdatum);		*/
  strncpy(temp5,temp1a,strlen(temp1a));
  strncat(temp5,temp1b,strlen(temp1b));
  strncat(temp5,temp1c,strlen(temp1c));
  strncat(temp5,temp1d,strlen(temp1d));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,arid,strlen(arid));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp1e,strlen(temp1e));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,fromdatum,strlen(fromdatum));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp1f,strlen(temp1f));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,tomdatum,strlen(tomdatum));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp1g,strlen(temp1g));
/*  fprintf(stderr,"temp5=%s\n",temp5);		*/
  mysql_init(&my_connection);

  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
/*  fprintf(stderr,"DBOKRPT:Connection success\n");	*/

  res = mysql_query(&my_connection,temp5);

  if (res){
	fprintf(stderr,"Error: DBOKRPT SELECT error: %s\n",mysql_error(&my_connection));
        }else{
	res_ptr=mysql_store_result(&my_connection);
	if (res_ptr){
		i=1;
/*		fprintf(stderr,"DBOKRPT:Retrieved %lu rows\n",(unsigned long)mysql_num_rows(res_ptr));	*/
		fprintf(stdout,"NR_%lu_:",(unsigned long)mysql_num_rows(res_ptr));
		while ((sqlrow=mysql_fetch_row(res_ptr)))  {
/*		fprintf(stderr,"DBOKRPT:Fetched data....}");	*/
/*			fprintf(stdout,"%d ",i);		*/
			display_row();
			i++;
		}
	if (mysql_errno(&my_connection))  {
		fprintf(stderr,"Error: DBOKRPT Retriev error:  %s\n", mysql_error(&my_connection));
		}
	}
	mysql_free_result(res_ptr);
	}
	mysql_close(&my_connection);

  	} else {
    	fprintf(stderr,"Error: DBOKRPT Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: DBOKRPT Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
	}
    }
  fprintf(stdout,"END:\n");
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
/*	fprintf(stdout,"\n");	*/
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
	 	fprintf(stderr,"Error: Filen .olfixrc kan inte �ppnas\n");
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
