/***************************************************************************
                          TRHDADD.c  -  description
                             -------------------
    Version		 : 0.2
    begin                : fre 1 nov 2002
    modified		 : S�n 9 nov 2003
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
	INPUT: 4 st arg. TRNSID, TID, USERID och TRNSDATA (f�lten i tabellen TRHD)
	Function: Add record i tabell TRHD

	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/C/Attic/TRHDADD.c,v 1.1 2004/05/03 04:42:57 janpihlgren Exp $ " ;

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql.h"
#define TRNSSIZE 255
#define ANTARG 5

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
  const char *userp = getenv("USER");	/* vem �r inloggad?	*/
  char databas[25]="olfix";
  char usr[15];				/* userid		*/


  char temp1[]="INSERT INTO TRHD(TRNSID,TID,USERID,TRNSDATA) VALUES (\"";
  char temp2[]="\"";
  char temp3[]=",";
  char temp4[]=")";
  char temp5[TRNSSIZE+200]="";
  char trnsid[9]="";
  char trnstid[21]="";
  char userid[9]="";
  char trnstxt[TRNSSIZE]="";

/*
  fprintf(stderr,"TRHDADD:argv0=%s\n",argv[0]);
  fprintf(stderr,"TRHDADD:argv1=%s\n",argv[1]);
  fprintf(stderr,"TRHDADD:argv2=%s\n",argv[2]);
  fprintf(stderr,"TRHDADD:argv3=%s\n",argv[3]);
  fprintf(stderr,"TRHDADD:argv4=%s\n",argv[4]);
  fprintf(stderr,"TRHDADD:argv5=%s\n",argv[5]);
*/

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

  strncpy(trnsid,argv[1],strlen(argv[1]));
  strncpy(trnstid,argv[2],strlen(argv[2]));
/*  fprintf(stderr,"trnstid=%s\n",trnstid);	*/
  strncpy(userid,argv[3],strlen(argv[3]));
  strncpy(trnstxt,argv[4],strlen(argv[4]));
  strncpy(temp5,temp1,strlen(temp1));
/* INSERT INTO TRHD(TRNSID,TID,USERID,TRNSDATA) VALUES ("  */
  strncat(temp5,trnsid,strlen(trnsid));/* VERADD */
/* INSERT INTO TRHD(TRNSID,TID,USERID,TRNSDATA) VALUES ("VERADD  */
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
  strncat(temp5,temp3,strlen(temp3)); /*  ,     */
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
/* INSERT INTO TRHD(TRNSID,TID,USERID,TRNSDATA) VALUES ("VERADD","  */
  strncat(temp5,trnstid,strlen(trnstid));/* timestamp  */
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
  strncat(temp5,temp3,strlen(temp3)); /*  ,     */
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
/* INSERT INTO TRHD(TRNSID,TID,USERID,TRNSDATA) VALUES ("VERADD","2002-11-01_08:56:51"," */
  strncat(temp5,userid,strlen(userid));
/* INSERT INTO TRHD(TRNSID,TID,USERID,TRNSDATA) VALUES ("VERADD","2002-11-01_08:56:51","olfix */
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
  strncat(temp5,temp3,strlen(temp3)); /*  ,     */
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
/* INSERT INTO TRHD(TRNSID,TID,USERID,TRNSDATA) VALUES ("VERADD","2002-11-01_08:56:51","olfix"," */
  strncat(temp5,trnstxt,strlen(trnstxt));
/* INSERT INTO TRHD(TRNSID,TID,USERID,TRNSDATA) VALUES ("VERADD","2002-11-01_08:56:51","olfix","1120 -:- K -:- 2500 */
  strncat(temp5,temp2,strlen(temp2));/*  "     */
  strncat(temp5,temp4,strlen(temp4));/*  )     */
/* INSERT INTO TRHD(TRNSID,TID,USERID,TRNSDATA) VALUES ("VERADD","2002-11-01_08:56:51","olfix","1120 -:- K -:- 2500") */
/*  fprintf(stderr,"TRHDADD:temp5=%s\n",temp5);	*/

  mysql_init(&my_connection);

  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
/* fprintf(stdout,"OK: TRHDADD Connection success\n");	*/
/* fprintf(stderr,"SQLfr�ga  %s\n TRNSID = %s\n TRNSTXT = %s\n",temp5,trnsid,trnstxt);	*/
    res = mysql_query(&my_connection,temp5);

  	if (!res){
		fprintf(stdout,"OK: TRHDADD Inserted %lu rows\n",
			(unsigned long)mysql_affected_rows(&my_connection));
        }else{
	fprintf(stderr,"Error: TRHDADD INSERT error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
        }
	mysql_close(&my_connection);

 } else {
	fprintf(stderr,"Error: TRHDADD Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: TRHDADD Connection error %d:  %s\n",
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
