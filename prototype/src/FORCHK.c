/***************************************************************************
                          FORCHK.c  -  description
                             -------------------
			     Version: 0.3
    begin                : Tis  9 nov	2004
    Modified		 : Ons 14 febr  2007
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
	INPUT: databasnr

	Kommando: ./FORCHK dbnr [databas]

	Function: Kontrollera om angiven databas existerar.

	OUTPUT: data, errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/FORCHK.c,v 1.4 2007/02/14 05:10:33 janpihlgren Exp $ " ;

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
  void display_row();
  int which_database(char *envp[]);

  char database[15]="";

int main(int argc, char *argv[], char *envp[])
{
  int res,status;

  char temp1[]="SELECT DATABASNR FROM DATABAS WHERE DATABASNR = \"";
  char temp2[]="\"";
  char temp5[200]="";
  char dbnr[4]="";
  const char *userp = getenv("USER");	/* vem �r inloggad?	*/
  char databas[25]="olfix";
  char usr[21];				/* userid 20070214 ut�kad fr�n 15 till 21 tecken */

  if (argv[1] != NULL){
  	strncpy(dbnr,argv[1],sizeof(dbnr));	/* 2005-02-23	*/
  }else{
  	fprintf(stderr,"Error: FORCHK: Ange databasnummer!\n");
	exit(-1);
  }

  status = which_database(envp);

  if (status != 0)
	exit(status);

  strncpy(usr,userp,sizeof(usr));			/* Den inloggades userid 20070214 */

  if (argc<3){
    	if (strlen(database)!= 0){
		strncpy(databas,database,15);
	}else{
  		strncpy(databas,"olfixtst",15);	/* olfixtst = testf�retag, anv�nds som grundv�rde	*/
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
//  fprintf(stderr,"ARCHK database = %s databas=%s\n",database,databas);

// ================================================================================
// 		Val av databas, END!
// ================================================================================

  strcpy(temp5,temp1);
/* SELECT DATABASNR FROM DATABAS WHERE DATABASNRNR = "  */
  strncat(temp5,dbnr,strlen(dbnr));/* 55 */
/* SELECT DATABASNR FROM DATABAS WHERE DATABASNRNR = "55  */
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
/* SELECT DATABASNR FROM DATABAS WHERE DATABASNRNR = "55" */
/*  fprintf(stderr,"FORCHK: temp5 = %s\n",temp5);	  */

  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
/*  fprintf(stdout,"FORCHKmain:Connection success\n");		*/
  	res = mysql_query(&my_connection,temp5);
  	if (res){
		fprintf(stderr,"Error: FORCHK SELECT error: %s\n",mysql_error(&my_connection));
  	}
  	else{
		res_ptr=mysql_store_result(&my_connection);
		if (res_ptr){
//			fprintf(stderr,"FORCHK_Retrieved %lu rows\n",(unsigned long)mysql_num_rows(res_ptr));
			if((unsigned long)mysql_num_rows(res_ptr) > 0){ /* En rad har hittats */
				status=0;
			}else{						/* Ingen rad hittades */
				status=-1;
			}

			if (mysql_errno(&my_connection)){
				fprintf(stderr,"Error: FORCHK Retriev error:  %s\n", mysql_error(&my_connection));
			}
		}
		mysql_free_result(res_ptr);
	}
  	mysql_close(&my_connection);
 }
  else {
  	fprintf(stderr,"Error: FORCHK Connection failed\n");
	if (mysql_errno(&my_connection)){
		fprintf(stderr,"Error: FORCHK Connection error %d:  %s\n",
		mysql_errno(&my_connection), mysql_error(&my_connection));
	}
  }
if(status == 0){
	fprintf(stdout,"OK: FORCHK Status = %d\n",status);
}
if(status != 0){
	fprintf(stderr,"Error: FORCHK Databasen %s finns inte!\n",dbnr);
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
