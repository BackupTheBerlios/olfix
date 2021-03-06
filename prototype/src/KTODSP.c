/***************************************************************************
                          KTODSP.c  -  description
                             -------------------
    Version		 : 0.3
    begin                : Fre  31 jan	2003
    modified		 : Tors 24 febr 2005
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
	INPUT: 2 st arg. ARID, KTONR [databas]

	Kommando: ./KTODSP arid ktonr [databas]

	Function: Visa all information p� ett konto i tabell KTOPLAN

	OUTPUT: ARID, KTONR, BENAMNING, MANUELL, MOMSKOD, SRUNR,
		KSTALLE, PROJEKT, SUBKTO, KTOPLAN, IB, UB
		samt errornb och error (text)

***************************************************************************/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/KTODSP.c,v 1.5 2007/02/14 14:56:29 janpihlgren Exp $ " ;

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
char database[15]="";

int main(int argc, char *argv[], char *envp[])
{
  int res;
  int status;
  const char *userp = getenv("USER");	/* vem �r inloggad?	*/
  char databas[25]="olfix";
  char usr[15];				/* userid		*/

  int num_rows;

  char temp1[]="SELECT * FROM KTOPLAN WHERE (ARID = \"";
  char temp1b[]=" AND KTONR = \"";
  char temp2[]="\"";
  char temp4[]=")";
  char temp5[200]="";
  char arid[3]="";
  char ktonr[5]="";

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

/*  for (i=0;i< argc;i++){
  	fprintf(stderr,"KTODSPmain argv%d = %s\n",i,argv[i]);
  }
*/

  strncpy(arid,argv[1],sizeof(arid));		/* 2005-02-24	*/
  strncpy(ktonr,argv[2],sizeof(ktonr));		/* 2005-02-24	*/

  strncpy(temp5,temp1,strlen(temp1));
/* SELECT * FROM KTOPLAN WHERE (ARID = "	*/
  strncat(temp5,arid,strlen(arid));/* AC */
/* SELECT * FROM KTOPLAN WHERE (ARID = "AC	*/
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
/* SELECT * FROM KTOPLAN WHERE (ARID = "AC"	*/
  strncat(temp5,temp1b,strlen(temp1b));
/* SELECT * FROM KTOPLAN WHERE (ARID = "AC" AND KTONR = "	*/
  strncat(temp5,ktonr,strlen(ktonr));/* 1020 */
/* SELECT * FROM KTOPLAN WHERE (ARID = "AC" AND KTONR = "1020	*/
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
/* SELECT * FROM KTOPLAN WHERE (ARID = "AC" AND KTONR = "1020"	*/
  strncat(temp5,temp4,strlen(temp4)); /*  )     */
/* SELECT * FROM KTOPLAN WHERE (ARID = "AC" AND KTONR = "1020")	*/
  strncat(temp5,"\n",1);
/*  fprintf(stderr,"KTODSP temp5 = %s\n",temp5);	*/

  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
/*  	fprintf(stdout,"KTODSP_Connection success\n");	*/
  	res = mysql_query(&my_connection,temp5);
/*  	fprintf(stderr,"KTODSP hit res=%d\n",res);	*/
  	if (res){
		fprintf(stderr,"Error: KTODSP SELECT errno: %d\n",mysql_errno(&my_connection));
		fprintf(stderr,"Error: KTODSP SELECT error: %s\n",mysql_error(&my_connection));
        }
	else{
		res_ptr=mysql_store_result(&my_connection);
		num_rows = mysql_affected_rows(&my_connection);
/*		fprintf(stderr,"num_rows=%d\n",num_rows);	*/
/*		if (res_ptr){					*/
		if(num_rows != 0){
			sqlrow=mysql_fetch_row(res_ptr);
			fprintf(stdout,"1:%s  ",sqlrow[0]);
			fprintf(stdout,"2:%s  ",sqlrow[1]);
			fprintf(stdout,"3:%s  ",sqlrow[2]);
			fprintf(stdout,"4:%s  ",sqlrow[3]);
			fprintf(stdout,"5:%s  ",sqlrow[4]);
			fprintf(stdout,"6:%s  ",sqlrow[5]);
			fprintf(stdout,"7:%s  ",sqlrow[6]);
			fprintf(stdout,"8:%s  ",sqlrow[7]);
			fprintf(stdout,"9:%s  ",sqlrow[8]);
			fprintf(stdout,"10:%s  ",sqlrow[9]);
			fprintf(stdout,"11:%s  ",sqlrow[10]);
			fprintf(stdout,"12:%s  ",sqlrow[11]);
			fprintf(stdout,"\n");
		}
		else{
			fprintf(stderr,"Error: KTODSP Data saknas:  %s\n", mysql_error(&my_connection));
		}
		if (mysql_errno(&my_connection))  {
		fprintf(stderr,"Error: KTODSP Retriev error:  %s\n", mysql_error(&my_connection));
		}
	}
	mysql_free_result(res_ptr);
    	mysql_close(&my_connection);
  }
  else {
    	fprintf(stderr,"Error: KTODSP Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: KTODSP Connection error %d:  %s\n",
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
