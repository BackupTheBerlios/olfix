/***************************************************************************
                          FORADD.c  -  description
                             -------------------
    begin                : Ons 12 nov	2004
    Modified		 : Ons 23 febr  2005
    			 : Ons 28 sept  2005
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
	INPUT: databasnr, databasnamn

	Kommando: ./FORADD dbnr dbnamn [databas]

	Function: Skapa en ny databas och en ny post i tabellen DATABAS

	OUTPUT: data, errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/FORADD.c,v 1.4 2005/09/28 08:19:02 janpihlgren Exp $ " ;

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
  void display_row();
  int which_database(char *envp[]);
  int newdatabase(char dbnr[4], char dbnamn[15]); /* 2005-09-25 */

  char database[15]="";

int main(int argc, char *argv[], char *envp[])
{
/* int i;	*/
  int res,status;

  char temp1[]="INSERT INTO DATABAS(DATABASNR,DATABASTEXT) VALUES (\"";
  char temp2[]="\"";
  char temp3[]=",";
  char temp4[]=")";
  char temp5[200]="";
  char dbnr[4]="";
  char dbnamn[16]="";
  const char *userp = getenv("USER");	/* vem är inloggad?	*/
  char databas[25]="olfix";
  char usr[15];				/* userid		*/

  if (argv[1] != NULL){
  	strncpy(dbnr,argv[1],sizeof(dbnr));	/* 2005-02-23	*/
  }else{
  	fprintf(stderr,"Error: FORADD: Ange databasnummer!\n");
	exit(-1);
  }
  if (argv[2] != NULL){
  	strncpy(dbnamn,argv[2],sizeof(dbnamn));	/* 2005-02-23	*/
  }else{
  	fprintf(stderr,"Error: FORADD: Ange databasnamn!\n");
	exit(-1);
  }
/*  fprintf(stderr,"argc=%d argv[argc]=%s\n",argc,argv[argc]);
  for (i=0;i<argc;i++){
  	fprintf(stderr,"argv[%d]=%s\n",i,argv[i]);
  }
*/
//  status = newdatabase(dbnr, dbnamn);				/* 2005-09-25 */
// exit (0);
  if((argc > 3) && (argv[3] != NULL)){
	strncpy(database,argv[3],sizeof(database));	/* 2005-02-23	*/
  }else{
	  status = which_database(envp);
  }

/*  fprintf(stderr,"FORADD: dbnr=%s dbnamn=%s databas=%s\n",dbnr,dbnamn,database);	*/

  if (status != 0)
	exit(status);

  strncpy(usr,userp,15);			/* Den inloggades userid	*/

  if (argc < ANTARG+1){
    	if (strlen(database)!= 0){
		strncpy(databas,database,15);
	}else{
  		strncpy(databas,"olfixtst",15);	/* olfixtst = testföretag, används som grundvärde	*/
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
  /* Om usr (userid) börjar på 'test' eller 'prov' använd databas 'olfixtst' */
  if (strncmp(usr,"test",4)==0 || strncmp(usr,"prov",4)==0 ) {
  	strncpy(databas,"olfixtst",15);
  }
//  fprintf(stderr,"FORADD database = %s databas=%s\n",database,databas);

// ================================================================================
// 		Val av databas, END!
// ================================================================================

  strcpy(temp5,temp1);
/* INSERT INTO DATABAS (DATABASNR,DATABASNAMN)VALUES ("  */
  strncat(temp5,dbnr,strlen(dbnr));/* 55 */
/* INSERT INTO DATABAS (DATABASNR,DATABASNAMN)VALUES ("55  */
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
/* INSERT INTO DATABAS (DATABASNR,DATABASNAMN)VALUES ("55" */
  strncat(temp5,temp3,strlen(temp3)); /*  ,     */
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
  strncat(temp5,dbnamn,strlen(dbnamn));/* olfixtest */
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
  strncat(temp5,temp4,strlen(temp4)); /*  )     */
/* INSERT INTO DATABAS (DATABASNR,DATABASNAMN)VALUES ("55","olfixtest") */
/*  fprintf(stderr,"FORADD: temp5 = %s\n",temp5);		*/

  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
//  fprintf(stdout,"KUCHKmain:Connection success\n");
  	res = mysql_query(&my_connection,temp5);
  	if (!res){
		fprintf(stdout,"OK: Inserted %lu rows\n",
			(unsigned long)mysql_affected_rows(&my_connection));
  	}
  	else{
		fprintf(stderr,"Error: FORADD INSERT error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
	}
	mysql_error(&my_connection);
  }else{
	fprintf(stderr,"Error: FORADD Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: FORADD Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
	}
 }
if(status != 0){
	fprintf(stderr,"Error: FORADD Databasen %s finns inte!\n",dbnr);
 }
  return status;
}
int which_database(char *envp[])
{
	FILE *fil_pek;

//	char home[]="$HOME";
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
//			fprintf(stderr,"temp=%s\n",temp);
			status=strcmp(temp,"HOME");
//			fprintf(stderr,"status=%d\n",status);
			if (status == 0){
				home_pek=(strstr(envp[i],"HOME="));
				home_pek=home_pek+5;
				strcpy(home,home_pek);
			}
//			fprintf(stderr,"home_pek=%d %s\n",home_pek,home_pek);
//			fprintf(stderr,"home_pek=%d %s\n",home_pek,home_pek);
		}
	}
//	fprintf(stderr,"home=%s\n",home);
	strncpy(filename,home,strlen(home));
	strncat(filename,resource,strlen(resource));

//	fprintf(stderr,"filename=%s\n",filename);
	status=-1;

	if ((fil_pek = fopen(filename,"r")) != NULL){
		while (fgets(tmp,150,fil_pek) != NULL){
//			fprintf(stderr,"tmp=%s\n",tmp);
			if(strstr(tmp,"DATABASE=")){
				tmp_pek=(strstr(tmp,"DATABASE="))+9;
				strncpy(database,tmp_pek,strlen(tmp_pek));
				status=0;
			}
		}
//		fprintf(stderr,"database=%s_len=%d\n",database,strlen(database));
		fclose(fil_pek);
	}
	else{
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

void display_row()
{
   unsigned int field_count;
   field_count=0;
	while (field_count < mysql_field_count(&my_connection))
	{
		fprintf(stdout,"%s: ",sqlrow[field_count]);
		field_count++;
	}
/*	fprintf(stdout,"\n");	*/
}
