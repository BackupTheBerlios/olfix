/***************************************************************************
                          PKDDSP.c  -  description
                             -------------------
			     Visa data om en produktgrupp/produktklass
    Version		 : 0.1
    begin                : Tis  8 mars	2005
    Modified		 :
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
	INPUT: 2 st arg.

	Kommando: ./PKDDSP produktklass

	Function: Visa data f�r en produktgrupp

	OUTPUT:	6 st f�lt,
		PRODUKTKLASS, BESKRIVNING , MOMSKOD
		samt errornb och error (text)

***************************************************************************/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/PKDDSP.c,v 1.2 2007/02/18 10:49:45 janpihlgren Exp $ " ;

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

  void display_row();
  int which_database(char *envp[]);

  char database[15]="";

int main(int argc, char *argv[], char *envp[])
{
  int res;
  int num_rows;
  int status;
  const char *userp = getenv("USER");	/* vem �r inloggad?	*/
  char databas[25]="olfix";
  char usr[15];				/* userid		*/

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


  if (argc <ANTARG - 1){
  	fprintf(stderr,"Error: Nr f�r produktklass saknas.\n");
	exit(-1);
  }
/*
  int i;
  for (i=0;i<argc;i++){
  	fprintf(stderr,"argc=%d argv[%d]=%s\n",argc,i,argv[i]);
  }
*/
  char temp1a[]="SELECT * FROM PRODUKTGRUPP WHERE (PRODKLASS = \"";
  char temp2[]="\"";
  char temp4[]=")";
  char temp5[200]="";
  char prodklass[6]="";

  strncpy(prodklass,argv[1],sizeof(prodklass));
/*
    fprintf(stderr,"PKDDSP Prodklass = %s\n",prodklass);
*/
  strncpy(temp5,temp1a,strlen(temp1a));
/* SELECT * FROM PRODUKTGRUPP WHERE (PRODKLASS = "	*/
  strncat(temp5,prodklass,strlen(prodklass));/* 12334 */
/* SELECT * FROM PRODUKTGRUPP WHERE (PRODKLASS = "12334	*/
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
/* SELECT * FROM PRODUKTGRUPP WHERE (PRODKLASS = "12334"	*/
  strncat(temp5,temp4,strlen(temp4)); /*  )     */
/* SELECT * FROM PRODUKTGRUPP WHERE (PRODKLASS = "12334")	*/
/*  fprintf(stderr,"PKDDSP temp5 = %s\n",temp5);		*/

  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
/*  	fprintf(stdout,"PKDDSP_Connection success\n");	*/
  	res = mysql_query(&my_connection,temp5);
  	if (res){
/*  		fprintf(stderr,"PKDDSP ERROR\n");	*/
		fprintf(stderr,"Error: PKDDSP SELECT errno: %d\n",mysql_errno(&my_connection));
        }
	else{
		res_ptr=mysql_store_result(&my_connection);
		num_rows = mysql_affected_rows(&my_connection);
/*		fprintf(stderr,"num_rows=%d\n",num_rows);	*/
/*		if (res_ptr){	*/
		if(num_rows != 0){
			sqlrow=mysql_fetch_row(res_ptr);
			fprintf(stdout,"OK: ");
			fprintf(stdout,"01:%s  ",sqlrow[0]);
			fprintf(stdout,"02:%s  ",sqlrow[1]);
			fprintf(stdout,"03:%s  ",sqlrow[2]);
//			fprintf(stdout,"04:%s  ",sqlrow[3]);
//			fprintf(stdout,"05:%s  ",sqlrow[4]);
//			fprintf(stdout,"06:%s  ",sqlrow[5]);

			fprintf(stdout,"\n");
		}
		else{
			fprintf(stderr,"Warning: PKDDSP Data saknas:  %s\n", mysql_error(&my_connection));
		}
		if (mysql_errno(&my_connection))  {
		fprintf(stderr,"Error: PKDDSP Retriev error:  %s\n", mysql_error(&my_connection));
		}
	}
	mysql_free_result(res_ptr);
    	mysql_close(&my_connection);
  }
  else {
    	fprintf(stderr,"Error: PKDDSP Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: PKDDSP Connection error %d:  %s\n",
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
