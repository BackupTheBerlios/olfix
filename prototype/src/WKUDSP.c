/***************************************************************************
                          WKUDSP.c  -  description
                             -------------------
    Version		 : 0.1
    begin                : Mån   6  dec	2004
    Modified		 :
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
	INPUT: 1 st arg.

	Kommando: ./WKUDSP kundnr password

	Function: Visa all information på ett konto i tabell KTOPLAN

	SQL-kommando:
	SELECT KUNDREG.KUNDNR,KUNDREG.NAMN,KUNDREG.ADRESS,KUNDREG.POSTNR,KUNDREG.POSTADR,
	KUNDREG.LAND,KUNDREG.EMAILADR,STDLEVPLATS.ADRESS,STDLEVPLATS.POSTNR,STDLEVPLATS.POSTADR,
	STDLEVPLATS.LAND,PASSW.PASSW FROM  KUNDREG
	join PASSW,STDLEVPLATS
	where KUNDREG.KUNDNR = "4376"  and  KUNDREG.KUNDNR =  PASSW.KUNDNR and
	STDLEVPLATS.KUNDNR = KUNDREG.KUNDNR AND  STDLEVPLATS.STDLEVPLATS="001"  and
	PASSW.PASSW LIKE "webbson"

	OUTPUT:	12 st fält,
		KUNDNR,  NAMN, ADRESS, POSTNR, POSTADR, LAND, EMAILADR,
		ADRESS2, POSTNR2, POSTADR2, LAND2,
		PASSW,

		samt errornb och error (text)

***************************************************************************/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/WKUDSP.c,v 1.1 2004/12/10 06:12:09 janpihlgren Exp $ " ;

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
  int res,i;
  int num_rows;
  int status;
  const char *userp = getenv("USER");	/* vem är inloggad?	*/
  char databas[25]="olfix";
  char usr[15];				/* userid		*/
  char passw[17]="";

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
  	fprintf(stderr,"Error: Lösenord måste anges!\n");
	exit(-1);
  }else{
  	strncpy(passw,argv[2],strlen(argv[2]));
  }
  if (argc <2){
  	fprintf(stderr,"Error: Kundnr saknas.\n");
	exit(-1);
  }
  for (i=0;i<argc;i++){
/*  	fprintf(stderr,"argc=%d argv[%d]=%s\n",argc,i,argv[i]);		*/
  }

  char temp1[]="SELECT KUNDREG.KUNDNR,KUNDREG.NAMN,KUNDREG.ADRESS,KUNDREG.POSTNR,KUNDREG.POSTADR,KUNDREG.LAND,KUNDREG.EMAILADR,STDLEVPLATS.ADRESS,STDLEVPLATS.POSTNR,STDLEVPLATS.POSTADR,STDLEVPLATS.LAND,PASSW.PASSW FROM KUNDREG join PASSW,STDLEVPLATS where KUNDREG.KUNDNR = PASSW.KUNDNR AND STDLEVPLATS.KUNDNR = KUNDREG.KUNDNR AND STDLEVPLATS.STDLEVPLATS = \"001\" AND KUNDREG.KUNDNR = \"";
  char temp1b[]=" AND PASSW.PASSW = \"";
  char temp2[]="\"";
//  char temp4[]=")";
  char temp5[600]="";
  char kundnr[11]="";

/*  for (i=0;i< argc;i++){
  	fprintf(stderr,"WKUDSP main argv%d = %s\n",i,argv[i]);
  }
*/
  strncpy(kundnr,argv[1],strlen(argv[1]));

  strncpy(temp5,temp1,strlen(temp1));
  strncat(temp5,kundnr,strlen(kundnr));/* 12334 */
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
  strncat(temp5,temp1b,strlen(temp1b));
  strncat(temp5,passw,strlen(passw));
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
  strncat(temp5,"\n",1);
/*  fprintf(stderr,"WKUDSP temp5 = %s\n",temp5);	*/
/* exit(-1);	*/
  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
/*  	fprintf(stdout,"WKUDSP_Connection success\n");	*/
  	res = mysql_query(&my_connection,temp5);
  	if (res){
/*  		fprintf(stderr,"WKUDSP ERROR\n");	*/
		fprintf(stderr,"Error: WKUDSP SELECT errno: %d\n",mysql_errno(&my_connection));
        }
	else{
		res_ptr=mysql_store_result(&my_connection);
		num_rows = mysql_affected_rows(&my_connection);
/*		fprintf(stderr,"num_rows=%d\n",num_rows);	*/
/*		if (res_ptr){	*/
		if(num_rows != 0){
			sqlrow=mysql_fetch_row(res_ptr);
			fprintf(stdout,"OK: ");
			fprintf(stdout,"_:%s ",sqlrow[0]);
			fprintf(stdout,"_:%s ",sqlrow[1]);
			fprintf(stdout,"_:%s ",sqlrow[2]);
			fprintf(stdout,"_:%s ",sqlrow[3]);
			fprintf(stdout,"_:%s ",sqlrow[4]);
			fprintf(stdout,"_:%s ",sqlrow[5]);
			fprintf(stdout,"_:%s ",sqlrow[6]);
			fprintf(stdout,"_:%s ",sqlrow[7]);
			fprintf(stdout,"_:%s ",sqlrow[8]);
			fprintf(stdout,"_:%s ",sqlrow[9]);
			fprintf(stdout,"_:%s ",sqlrow[10]);
			fprintf(stdout,"_:%s ",sqlrow[11]);
			fprintf(stdout,"_:%s ",sqlrow[12]);
			fprintf(stdout,"\n");
		}
		else{
			fprintf(stderr,"Error: WKUDSP Data saknas:  %s\n", mysql_error(&my_connection));
		}
		if (mysql_errno(&my_connection))  {
		fprintf(stderr,"Error: WKUDSP Retriev error:  %s\n", mysql_error(&my_connection));
		}
	}
	mysql_free_result(res_ptr);
    	mysql_close(&my_connection);
  }
  else {
    	fprintf(stderr,"Error: WKUDSP Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: WKUDSP Connection error %d:  %s\n",
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
