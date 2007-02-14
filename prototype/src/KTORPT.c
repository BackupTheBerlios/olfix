/***************************************************************************
                          KTORPT.c  -  description
                             -------------------
    Version		 : 0.6
    begin                : Lör   8 mars 2003
    modified		 : Ons  14 febr 2007
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
	INPUT: arid,fromdatum,tomdatum	(Bokföringsår, Från och med datum, Till och med datum)
	Function: gör  	SELECT VERRAD.KTONR,KTOPLAN.BENAMNING,VERRAD.DK,VERRAD.BELOPP FROM VERRAD
			LEFT JOIN KTOPLAN ON KTOPLAN.KTONR = VERRAD.KTONR AND VERRAD.ARID = KTOPLAN.ARID
			LEFT JOIN VERHUVUD ON VERRAD.ARID = VERHUVUD.ARID AND VERRAD.VERNR=VERHUVUD.VERNR
			WHERE VERRAD.ARID = "AD" AND
			VERHUVUD.VERDATUM >= "2003-08-12" AND
			VERHUVUD.VERDATUM <= "2003-08-16"
			ORDER BY KTONR

	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/KTORPT.c,v 1.7 2007/02/14 14:56:29 janpihlgren Exp $ " ;

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
  const char *userp = getenv("USER");	/* vem är inloggad?	*/
  char databas[25]="olfix";
  char usr[21];				/* userid 20070214 utökat från 15 till 21 tecken */

  char temp1a[]="SELECT VERRAD.KTONR,KTOPLAN.BENAMNING,VERRAD.DK,VERRAD.BELOPP,VERRAD.VERNR FROM VERRAD ";
  char temp1b[]="LEFT JOIN KTOPLAN ON KTOPLAN.KTONR = VERRAD.KTONR AND VERRAD.ARID = KTOPLAN.ARID ";
  char temp1c[]="LEFT JOIN VERHUVUD ON VERRAD.ARID = VERHUVUD.ARID AND VERRAD.VERNR=VERHUVUD.VERNR ";
  char temp1d[]="WHERE VERRAD.ARID = ";
  char temp1e[]=" AND VERHUVUD.VERDATUM >= ";
  char temp1f[]=" AND VERHUVUD.VERDATUM <= ";
  char temp1g[]=" ORDER BY KTONR";
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

  strncpy(usr,userp,sizeof(usr));			/* Den inloggades userid 20070214 */
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

  strncpy(arid,argv[1],sizeof(arid));			/* 2005-02-24	*/
  strncpy(fromdatum,argv[2],sizeof(fromdatum));		/* 2005-02-24	*/
  strncpy(tomdatum,argv[3],sizeof(tomdatum));		/* 2005-02-24	*/

  fprintf(stderr,"arid=%s,fromdatum=%s,tomdatum=%s\n",arid,fromdatum,tomdatum);
  strncpy(temp5,temp1a,strlen(temp1a));
/* SELECT VERRAD.KTONR,KTOPLAN.BENAMNING,VERRAD.DK,VERRAD.BELOPP,VERRAD.VERNR FROM VERRAD 	*/
  strncat(temp5,temp1b,strlen(temp1b));
/* SELECT VERRAD.KTONR,KTOPLAN.BENAMNING,VERRAD.DK,VERRAD.BELOPP,VERRAD.VERNR FROM VERRAD 	*/
/* LEFT JOIN KTOPLAN ON KTOPLAN.KTONR = VERRAD.KTONR AND VERRAD.ARID = KTOPLAN.ARID 		*/
  strncat(temp5,temp1c,strlen(temp1c));
/* SELECT VERRAD.KTONR,KTOPLAN.BENAMNING,VERRAD.DK,VERRAD.BELOPP,VERRAD.VERNR FROM VERRAD 	*/
/* LEFT JOIN KTOPLAN ON KTOPLAN.KTONR = VERRAD.KTONR AND VERRAD.ARID = KTOPLAN.ARID 		*/
/* LEFT JOIN VERHUVUD ON VERRAD.ARID = VERHUVUD.ARID AND VERRAD.VERNR=VERHUVUD.VERNR 		*/
  strncat(temp5,temp1d,strlen(temp1d));
/* SELECT VERRAD.KTONR,KTOPLAN.BENAMNING,VERRAD.DK,VERRAD.BELOPP,VERRAD.VERNR FROM VERRAD 	*/
/* LEFT JOIN KTOPLAN ON KTOPLAN.KTONR = VERRAD.KTONR AND VERRAD.ARID = KTOPLAN.ARID 		*/
/* LEFT JOIN VERHUVUD ON VERRAD.ARID = VERHUVUD.ARID AND VERRAD.VERNR=VERHUVUD.VERNR 		*/
/* WHERE VERRAD.ARID = 										*/
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,arid,strlen(arid));
  strncat(temp5,temp2,strlen(temp2));
/* SELECT VERRAD.KTONR,KTOPLAN.BENAMNING,VERRAD.DK,VERRAD.BELOPP,VERRAD.VERNR FROM VERRAD 	*/
/* LEFT JOIN KTOPLAN ON KTOPLAN.KTONR = VERRAD.KTONR AND VERRAD.ARID = KTOPLAN.ARID 		*/
/* LEFT JOIN VERHUVUD ON VERRAD.ARID = VERHUVUD.ARID AND VERRAD.VERNR=VERHUVUD.VERNR 		*/
/* WHERE VERRAD.ARID = "AD"									*/
  strncat(temp5,temp1e,strlen(temp1e));
/* SELECT VERRAD.KTONR,KTOPLAN.BENAMNING,VERRAD.DK,VERRAD.BELOPP,VERRAD.VERNR FROM VERRAD 	*/
/* LEFT JOIN KTOPLAN ON KTOPLAN.KTONR = VERRAD.KTONR AND VERRAD.ARID = KTOPLAN.ARID 		*/
/* LEFT JOIN VERHUVUD ON VERRAD.ARID = VERHUVUD.ARID AND VERRAD.VERNR=VERHUVUD.VERNR 		*/
/* WHERE VERRAD.ARID = "AD"									*/
/* AND VERHUVUD.VERDATUM >= 									*/
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,fromdatum,strlen(fromdatum));
  strncat(temp5,temp2,strlen(temp2));
/* SELECT VERRAD.KTONR,KTOPLAN.BENAMNING,VERRAD.DK,VERRAD.BELOPP,VERRAD.VERNR FROM VERRAD 	*/
/* LEFT JOIN KTOPLAN ON KTOPLAN.KTONR = VERRAD.KTONR AND VERRAD.ARID = KTOPLAN.ARID 		*/
/* LEFT JOIN VERHUVUD ON VERRAD.ARID = VERHUVUD.ARID AND VERRAD.VERNR=VERHUVUD.VERNR 		*/
/* WHERE VERRAD.ARID = "AD"									*/
/* AND VERHUVUD.VERDATUM >= "2003-08-10"							*/
  strncat(temp5,temp1f,strlen(temp1f));
/* SELECT VERRAD.KTONR,KTOPLAN.BENAMNING,VERRAD.DK,VERRAD.BELOPP,VERRAD.VERNR FROM VERRAD 	*/
/* LEFT JOIN KTOPLAN ON KTOPLAN.KTONR = VERRAD.KTONR AND VERRAD.ARID = KTOPLAN.ARID 		*/
/* LEFT JOIN VERHUVUD ON VERRAD.ARID = VERHUVUD.ARID AND VERRAD.VERNR=VERHUVUD.VERNR 		*/
/* WHERE VERRAD.ARID = "AD"									*/
/* AND VERHUVUD.VERDATUM >= "2003-08-10"							*/
/* AND VERHUVUD.VERDATUM <= 									*/
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,tomdatum,strlen(tomdatum));
  strncat(temp5,temp2,strlen(temp2));
/* SELECT VERRAD.KTONR,KTOPLAN.BENAMNING,VERRAD.DK,VERRAD.BELOPP,VERRAD.VERNR FROM VERRAD 	*/
/* LEFT JOIN KTOPLAN ON KTOPLAN.KTONR = VERRAD.KTONR AND VERRAD.ARID = KTOPLAN.ARID 		*/
/* LEFT JOIN VERHUVUD ON VERRAD.ARID = VERHUVUD.ARID AND VERRAD.VERNR=VERHUVUD.VERNR 		*/
/* WHERE VERRAD.ARID = "AD"									*/
/* AND VERHUVUD.VERDATUM >= "2003-08-10"							*/
/* AND VERHUVUD.VERDATUM <= "2003-08-16"							*/
  strncat(temp5,temp1g,strlen(temp1g));
/* SELECT VERRAD.KTONR,KTOPLAN.BENAMNING,VERRAD.DK,VERRAD.BELOPP,VERRAD.VERNR FROM VERRAD 	*/
/* LEFT JOIN KTOPLAN ON KTOPLAN.KTONR = VERRAD.KTONR AND VERRAD.ARID = KTOPLAN.ARID 		*/
/* LEFT JOIN VERHUVUD ON VERRAD.ARID = VERHUVUD.ARID AND VERRAD.VERNR=VERHUVUD.VERNR 		*/
/* WHERE VERRAD.ARID = "AD"									*/
/* AND VERHUVUD.VERDATUM >= "2003-08-10"							*/
/* AND VERHUVUD.VERDATUM <= "2003-08-16"							*/
/* ORDER BY KTONR										*/
/*  fprintf(stderr,"temp5=%s\n",temp5);		*/
  mysql_init(&my_connection);

  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
/*  fprintf(stderr,"KTORPT:Connection success\n");	*/

  res = mysql_query(&my_connection,temp5);

  if (res){
	fprintf(stderr,"Error: KTORPT SELECT error: %s\n",mysql_error(&my_connection));
        }else{
	res_ptr=mysql_store_result(&my_connection);
	if (res_ptr){
		i=1;
/*		fprintf(stderr,"KTORPT:Retrieved %lu rows\n",(unsigned long)mysql_num_rows(res_ptr));	*/
		fprintf(stdout,"NR_%lu_:",(unsigned long)mysql_num_rows(res_ptr));
		while ((sqlrow=mysql_fetch_row(res_ptr)))  {
/*		fprintf(stderr,"KTORPT:Fetched data....}");	*/
/*			fprintf(stdout,"%d ",i);		*/
			display_row();
			i++;
		}
		fprintf(stdout,"END");
	if (mysql_errno(&my_connection))  {
		fprintf(stderr,"Error: KTORPT Retriev error:  %s\n", mysql_error(&my_connection));
		}
	}
	mysql_free_result(res_ptr);
	}
	mysql_close(&my_connection);

  	} else {
    	fprintf(stderr,"Error: KTORPT Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: KTORPT Connection error %d:  %s\n",
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
