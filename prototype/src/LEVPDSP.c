/***************************************************************************
                          LEVPDSP.c  -  description
                             -------------------
			     Visa data om en standarleveransplats
    Version		 : 0.2
    begin                : Tis  8 mars	2005
    Modified		 : Lör 12 mars  2005
    copyright            : (C) 2005 by Jan Pihlgren
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

	Kommando: ./LEVPDSP kundnr standardlevplatsnr

	Function: Visa data för en standardleveransplats

	OUTPUT:	6 st fält,
		STDLEVPLATS, KUNDNR, ADRESS, POSTNR, POSTADR, LAND
		samt errornb och error (text)

***************************************************************************/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/LEVPDSP.c,v 1.2 2005/03/12 17:38:31 janpihlgren Exp $ " ;

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

  char database[15]="";

int main(int argc, char *argv[], char *envp[])
{
  int res;
/*  int i;	*/
  int num_rows;
  int status;
  const char *userp = getenv("USER");	/* vem är inloggad?	*/
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


  if (argc <3){
  	fprintf(stderr,"Error: Nr för standardleveransplats eller kundnr saknas.\n");
	exit(-1);
  }
/*
int i;
  for (i=0;i<argc;i++){
  	fprintf(stderr,"argc=%d argv[%d]=%s\n",argc,i,argv[i]);
  }
*/
  char temp1a[]="SELECT * FROM STDLEVPLATS WHERE (KUNDNR = \"";
  char temp1b[]=" AND STDLEVPLATS = \"";
  char temp2[]="\"";
  char temp4[]=")";
  char temp5[200]="";
  char kundnr[31]="";
  char levplatsnr[4]="";

  strncpy(kundnr,argv[1],sizeof(kundnr));
  strncpy(levplatsnr,argv[2],sizeof(levplatsnr));
/*  fprintf(stderr,"LEVPDSP kundnr = %s\n",kundnr);
  fprintf(stderr,"LEVPDSP levplatsnr = %s\n",levplatsnr);
*/
  strncpy(temp5,temp1a,strlen(temp1a));
/* SELECT * FROM STDLEVPLATS WHERE (KUNDNR = "	*/
  strncat(temp5,kundnr,strlen(kundnr));/* 12334 */
/* SELECT * FROM STDLEVPLATS WHERE (kundnrnr = "12334	*/
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
/* SELECT * FROM STDLEVPLATS WHERE (kundnr = "12334"	*/
  strncat(temp5,temp1b,strlen(temp1b));
/* SELECT * FROM STDLEVPLATS WHERE (kundnr = "12334" AND STDLEVPLATS = "	*/
  strncat(temp5,levplatsnr,strlen(levplatsnr));
/* SELECT * FROM STDLEVPLATS WHERE (kundnr = "12334" AND STDLEVPLATS = "002	*/
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
/* SELECT * FROM STDLEVPLATS WHERE (kundnr = "12334" AND STDLEVPLATS = "002"	*/
  strncat(temp5,temp4,strlen(temp4)); /*  )     */
/* SELECT * FROM STDLEVPLATS WHERE (kundnr = "12334" AND STDLEVPLATS = "002")	*/
/*  fprintf(stderr,"LEVPDSP temp5 = %s\n",temp5);	*/

  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
/*  	fprintf(stdout,"LEVPDSP_Connection success\n");	*/
  	res = mysql_query(&my_connection,temp5);
  	if (res){
/*  		fprintf(stderr,"LEVPDSP ERROR\n");	*/
		fprintf(stderr,"Error: LEVPDSP SELECT errno: %d\n",mysql_errno(&my_connection));
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
			fprintf(stdout,"04:%s  ",sqlrow[3]);
			fprintf(stdout,"05:%s  ",sqlrow[4]);
			fprintf(stdout,"06:%s  ",sqlrow[5]);
			fprintf(stdout,":END\n");
		}
		else{
			fprintf(stderr,"Error: LEVPDSP Data saknas:  %s\n", mysql_error(&my_connection));
		}
		if (mysql_errno(&my_connection))  {
		fprintf(stderr,"Error: LEVPDSP Retriev error:  %s\n", mysql_error(&my_connection));
		}
	}
	mysql_free_result(res_ptr);
    	mysql_close(&my_connection);
  }
  else {
    	fprintf(stderr,"Error: LEVPDSP Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: LEVPDSP Connection error %d:  %s\n",
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
