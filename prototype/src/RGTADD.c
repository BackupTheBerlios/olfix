/***************************************************************************
                          RGTADD.c  -  description
                             -------------------
    Version		 : 0.6
    begin                : fre   24 jan  2003
    modified		 : Tors  13 dec  2007
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
 *********************************************** ****************************/

/*
	Tabellen RIGHTS är korsreferens mellan tabellerna USR och TRANSID
	och bestämmer vem som har behörighet (rights) till viss transaktionstyp */

/*	INPUT: 2 st arg. USERID och TRNSID (fälten i tabellen RIGHTS)
	Function: Add record i tabell RIGHTS

	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/RGTADD.c,v 1.5 2007/12/13 05:59:20 janpihlgren Exp $ " ;

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
int which_host(char *envp[]);	// 20071213
char database[15]="";
char host[200]="";		// 20071213

int main(int argc, char *argv[], char *envp[])
{
  int res;
  int status;
  const char *userp = getenv("USER");	/* vem är inloggad?	*/
  char databas[25]="olfix";
  char usr[21];				/* userid 20070218 utökat från 15 till 21 tecken */

  char temp1[]="INSERT INTO RIGHTS(USERID,TRNSID) VALUES (\"";
  char temp2[]="\"";
  char temp3[]=",";
  char temp4[]=")";
  char temp5[200]="";
  char userid[21]="";			/* 20070218 utökat från 9 till 21 tecken */
  char trnsid[9]="";

  if (argc < 3){
	fprintf(stderr,"Error: USERID och/eller TRNSID saknas!\n");
	exit(0);
  }

/* ================================================================================ */
/* 		Val av databas, START						    */
/* ================================================================================ */
/*	fprintf(stderr,"1. host=%s\n",host);	*/
  status = which_host(envp);			// 20071213
	fprintf(stdout,"host=%s ",host);	/* Det ska vara ett mellanslag i slutet! */
  if (status != 0)
	exit(status);

  status = which_database(envp);

  if (status != 0)
	exit(status);

  strncpy(usr,userp,sizeof(usr));			/* Den inloggades userid 20070218 */
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

  strncpy(userid,argv[1],sizeof(userid));	/* 2005-02-24	*/
  strncpy(trnsid,argv[2],sizeof(trnsid));	/* 2005-02-24	*/

/*  fprintf(stderr,"argv1=%s argv2=%s\n",argv[1],argv[2]);	*/

  strncat(temp5,temp1,strlen(temp1));
/* INSERT INTO RIGHTS(USERID,TRNSID) VALUES (USERID,TRNSID) VALUES ("  */
  strncat(temp5,userid,strlen(userid));/* KALLE */
/* INSERT INTO RIGHTS(USERID,TRNSID) VALUES (USERID,TRNSID) VALUES ("KALLE  */
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
  strncat(temp5,temp3,strlen(temp3)); /*  ,     */
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
/* INSERT INTO RIGHTS(USERID,TRNSID) VALUES (USERID,TRNSID) VALUES ("KALLE","  */
  strncat(temp5,trnsid,strlen(trnsid));/* KTOADD  */
/* INSERT INTO RIGHTS(USERID,TRNSID) VALUES (USERID,TRNSID) VALUES ("KALLE","KTOADD  */
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
  strncat(temp5,temp4,strlen(temp4)); /*  )     */
/* INSERT INTO RIGHTS(USERID,TRNSID) VALUES (USERID,TRNSID) VALUES ("KALLE","KTOADD")  */

  mysql_init(&my_connection);

  if (mysql_real_connect(&my_connection, host,  "olfix", "olfix", databas, 0, NULL, 0)){
/*  fprintf(stdout,"OK: RGTADD_Connection success\n");	*/
/*  printf("SQLfr�ga  %s\n USERID = %s\n TRNSID = %s\n",temp5,userid,trnsid);	*/
    res = mysql_query(&my_connection,temp5);

  	if (!res){
		fprintf(stdout,"OK: RGTADD Inserted %lu rows\n",
			(unsigned long)mysql_affected_rows(&my_connection));
        }else{
	fprintf(stderr,"Error: RGTADD INSERT error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
        }
	mysql_close(&my_connection);

 } else {
	fprintf(stderr,"Error: RGTADD Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: RGTADD Connection error %d:  %s\n",
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

int which_host(char *envp[])
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
	
	strncpy(host,"localhost",10);		/* default, överskrivs om .olfirc innehåller en hostadr */

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
/*			fprintf(stderr,"tmp=%s\n",tmp); 	*/
			if(strstr(tmp,"HOST=")){
				tmp_pek=(strstr(tmp,"HOST="))+5;
				strncpy(host,tmp_pek,strlen(tmp_pek));
				status=0;
			}
		}
/*		fprintf(stderr," Host=%s_len=%d\n",host,strlen(host)); 	*/
		fclose(fil_pek);
	}
	else{
/*		fprintf(stderr," Host=%s_len=%d\n",host,strlen(host)); 	*/
	 	fprintf(stderr,"Error: Filen .olfixrc kan inte öppnas\n");
	}
	for (i=0;i < strlen(host);i++){
		tmp[i]=host[i];
	}
	tmp[i-1]=0;
/*	fprintf(stderr,"tmp=%s, i=%d len(tmp)=%d\n",tmp,i,strlen(tmp));	*/
	strncpy(host,tmp,strlen(tmp));
	host[strlen(tmp)]=0;
/*	fprintf(stderr,"host=%s\n",host);	*/

	return status;
}
