/***************************************************************************
                          ARDSP.c  -  description
                             -------------------
    Version		 : 0.1
    begin                : Lör 15  nov	2003
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
	INPUT: 1 st arg.

	Kommando: ./ARDSP artikelnr

	Function: Visa grunddata för en artikel

	OUTPUT:	20 st fält,
		ARTIKELNR, ARBENEMNING1, ARBENEMNING2, ARENHET, ARFPRIS, ARLEDTID, ARPRODKLASS, ARPRODKTO, ARLEVNR1,
		ARLEVNR2, ARLEVNR3, ARNETTOVIKT, ARARTTYP, ARSTRUKT, ARURBENEMNING, ARURLAND, ARURARTNR,
		ARTULLTAX, ARVOLYM, AROMRFAKTOR,
		samt errornb och error (text)

***************************************************************************/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/ARDSP.c,v 1.1 2003/11/15 10:09:10 janpihlgren Exp $ " ;

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
  int res,i;
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


  if (argc <2){
  	fprintf(stderr,"Error: Artikelnr saknas.\n");
	exit(-1);
  }
  for (i=0;i<argc;i++){
/*  	fprintf(stderr,"argc=%d argv[%d]=%s\n",argc,i,argv[i]);		*/
  }

  char temp1[]="SELECT * FROM ARTIKELREG WHERE (ARTIKELNR = \"";
  char temp2[]="\"";
  char temp4[]=")";
  char temp5[200]="";
  char artikelnr[11]="";

/*  for (i=0;i< argc;i++){
  	fprintf(stderr,"ARDSP main argv%d = %s\n",i,argv[i]);
  }
*/
  strncpy(artikelnr,argv[1],strlen(argv[1]));

  strncpy(temp5,temp1,strlen(temp1));
/* SELECT * FROM ARTIKELREG WHERE (artikelnr = "	*/
  strncat(temp5,artikelnr,strlen(artikelnr));/* 12334 */
/* SELECT * FROM ARTIKELREG WHERE (artikelnr = "12334	*/
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
/* SELECT * FROM ARTIKELREG WHERE (artikelnr = "12334"	*/
  strncat(temp5,temp4,strlen(temp4)); /*  )     */
/* SELECT * FROM ARTIKELREG WHERE (artikelnr = "12334")	*/
  strncat(temp5,"\n",1);
/*  fprintf(stderr,"ARDSP temp5 = %s\n",temp5);		*/

  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
/*  	fprintf(stdout,"ARDSP_Connection success\n");	*/
  	res = mysql_query(&my_connection,temp5);
  	if (res){
/*  		fprintf(stderr,"ARDSP ERROR\n");	*/
		fprintf(stderr,"Error: ARDSP SELECT errno: %d\n",mysql_errno(&my_connection));
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
			fprintf(stdout,"07:%s  ",sqlrow[6]);
			fprintf(stdout,"08:%s  ",sqlrow[7]);
			fprintf(stdout,"09:%s  ",sqlrow[8]);
			fprintf(stdout,"10:%s  ",sqlrow[9]);
			fprintf(stdout,"11:%s  ",sqlrow[10]);
			fprintf(stdout,"12:%s  ",sqlrow[11]);
			fprintf(stdout,"13:%s  ",sqlrow[12]);
			fprintf(stdout,"14:%s  ",sqlrow[13]);
			fprintf(stdout,"15:%s  ",sqlrow[14]);
			fprintf(stdout,"16:%s  ",sqlrow[15]);
			fprintf(stdout,"17:%s  ",sqlrow[16]);
			fprintf(stdout,"18:%s  ",sqlrow[17]);
			fprintf(stdout,"19:%s  ",sqlrow[18]);
			fprintf(stdout,"20:%s  ",sqlrow[19]);
/*
			fprintf(stdout,"21:%s  ",sqlrow[20]);
			fprintf(stdout,"22:%s  ",sqlrow[21]);
			fprintf(stdout,"23:%s  ",sqlrow[22]);
			fprintf(stdout,"24:%s  ",sqlrow[23]);
			fprintf(stdout,"25:%s  ",sqlrow[24]);
			fprintf(stdout,"26:%s  ",sqlrow[25]);
			fprintf(stdout,"27:%s  ",sqlrow[26]);
			fprintf(stdout,"28:%s  ",sqlrow[27]);
			fprintf(stdout,"29:%s  ",sqlrow[28]);
			fprintf(stdout,"30:%s  ",sqlrow[29]);
			fprintf(stdout,"31:%s  ",sqlrow[30]);
			fprintf(stdout,"32:%s  ",sqlrow[31]);
			fprintf(stdout,"33:%s  ",sqlrow[32]);
			fprintf(stdout,"34:%s  ",sqlrow[33]);
			fprintf(stdout,"35:%s  ",sqlrow[34]);
			fprintf(stdout,"36:%s  ",sqlrow[35]);
			fprintf(stdout,"37:%s  ",sqlrow[36]);
			fprintf(stdout,"38:%s  ",sqlrow[37]);
			fprintf(stdout,"39:%s  ",sqlrow[38]);
			fprintf(stdout,"40:%s  ",sqlrow[39]);
			fprintf(stdout,"41:%s  ",sqlrow[40]);
*/
			fprintf(stdout,"\n");
		}
		else{
			fprintf(stderr,"Error: ARDSP Data saknas:  %s\n", mysql_error(&my_connection));
		}
		if (mysql_errno(&my_connection))  {
		fprintf(stderr,"Error: ARDSP Retriev error:  %s\n", mysql_error(&my_connection));
		}
	}
	mysql_free_result(res_ptr);
    	mysql_close(&my_connection);
  }
  else {
    	fprintf(stderr,"Error: ARDSP Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: ARDSP Connection error %d:  %s\n",
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
