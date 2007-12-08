/***************************************************************************
                          VALCHG.c  -  description
                             -------------------
    Version		 : 0.5
    begin                : Fre  21 Febr 2003
    modified		 : Lör   8 dec  2007
    copyright            : (C) 2003 by Jan Pihlgren
    email                : jan@pihlgren.se
	Anrop till databas på annan server/host
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
	INPUT: 5 st arg. VALUTAID, LAND, SALJ, KOP och BETECKNING (fälten i tabellen VALUTA)

	Kommando: ./VALCHG SEK Sverige 1.01 1.02 Kronor

	Function: Ändra record i tabell VALUTA

	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/VALCHG.c,v 1.5 2007/12/08 09:53:53 janpihlgren Exp $ " ;

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql.h"
#define ANTARG 6

  MYSQL my_connection;
  MYSQL_RES *res_ptr;
  MYSQL_ROW sqlrow;

int which_database(char *envp[]);
int which_host(char *envp[]);	// 20071208
char host[200]="";		// 20071208
char database[15]="";

int main(int argc, char *argv[], char *envp[])
{
/* int i;	*/
  int res;
  int status;
  const char *userp = getenv("USER");	/* vem är inloggad?	*/
  char databas[25]="olfix";
  char usr[21];				/* userid 20070219 utökat från 15 till 21 tecken */

  char temp1a[]="UPDATE VALUTA SET LAND = ";
  char temp1b[]=" WHERE VALUTAID = ";
  char temp1c[]="SALJ = ";
  char temp1d[]="KOP = ";
  char temp1e[]="BETECKNING = ";
  char temp2[]="\"";
  char temp3[]=",";
  char temp5[200]="";
  char valuta[4]="";
  char land[16]="";
  char kop[15]="";
  char salj[15]="";
  char beteck[16]="";

  if (argc < 2){
	fprintf(stderr,"Error: Valuta saknas!\n");
	exit(0);
  }

/* ================================================================================ */
/* 		Val av databas, START						    */
/* ================================================================================ */
/*	fprintf(stderr,"1. host=%s\n",host);	*/
  status = which_host(envp);			// 20071208
	fprintf(stdout,"host=%s ",host);	/* Det ska vara ett mellanslag i slutet! */
  if (status != 0)
	exit(status);


  status = which_database(envp);

  if (status != 0)
	exit(status);

  strncpy(usr,userp,sizeof(usr));			/* Den inloggades userid 20070219 */
/*  fprintf(stderr,"status=%d ANTARG=%d len(database)=%d\n",status,ANTARG,strlen(database));	*/
  if (argc < ANTARG+1){
    	if (strlen(database)!= 0){
		strncpy(databas,database,sizeof(databas));		/* 2005-02-24	*/
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

  strncpy(valuta,argv[1],sizeof(valuta));		/* 2005-02-24	*/
  strncpy(land,argv[2],sizeof(land));			/* 2005-02-24	*/
  strncpy(salj,argv[3],sizeof(salj));			/* 2005-02-24	*/
  strncpy(kop,argv[4],sizeof(kop));			/* 2005-02-24	*/
  strncpy(beteck,argv[5],sizeof(beteck));		/* 2005-02-24	*/

  strncpy(temp5,temp1a,strlen(temp1a));
/* UPDATE VALUTA SET LAND =   */
  strncat(temp5,temp2,strlen(temp2));
/* UPDATE VALUTA SET LAND = "   */
  strncat(temp5,land,strlen(land));
/* UPDATE VALUTA SET LAND ="Sverige   */
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
  strncat(temp5,temp3,strlen(temp3)); /*  ,     */
/* UPDATE VALUTA SET LAND ="Sverige", */
  strncat(temp5,temp1c,strlen(temp1c));
/* UPDATE VALUTA SET LAND ="Sverige",SALJ =    */
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
  strncat(temp5,salj,strlen(salj));
/* UPDATE VALUTA SET LAND ="Sverige",SALJ = "1.01    */
  strncat(temp5,temp2,strlen(temp2));  /*  "     */
  strncat(temp5,temp3,strlen(temp3)); /*  ,     */
  strncat(temp5,temp1d,strlen(temp1d));
/* UPDATE VALUTA SET LAND ="Sverige",SALJ = "1.01",KOP =   */
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
  strncat(temp5,kop,strlen(kop));
/* UPDATE VALUTA SET LAND = "Sverige",SALJ = "1.01",KOP = "1.02 */
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
  strncat(temp5,temp3,strlen(temp3)); /*  ,     */
/* UPDATE VALUTA SET LAND = "Sverige",SALJ = "1.01",KOP = "1.02", */
  strncat(temp5,temp1e,strlen(temp1e));
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
/* UPDATE VALUTA SET LAND = "Sverige",SALJ = "1.01",KOP = "1.02",BETECKNING = "  */
  strncat(temp5,beteck,strlen(beteck));
/* UPDATE VALUTA SET LAND = "Sverige",SALJ = "1.01",KOP = "1.02",BETECKNING = "Kronor  */
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
  strncat(temp5,temp1b,strlen(temp1b));
/* UPDATE VALUTA SET LAND = "Sverige",SALJ = "1.01",KOP = "1.02",BETECKNING = "Kronor" WHERE VALUTAID = */
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
  strncat(temp5,valuta,strlen(valuta));
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
/* UPDATE VALUTA SET LAND = "Sverige",SALJ = "1.01",KOP = "1.02",BETECKNING = "Kronor" WHERE VALUTAID = "SEK"*/

  fprintf(stderr,"VALCHG temp5=%s\n",temp5);	

  mysql_init(&my_connection);

  if (mysql_real_connect(&my_connection, host,  "olfix", "olfix", databas, 0, NULL, 0)){
/*	fprintf(stdout,"VALCHG_Connection success\n");		*/

    res = mysql_query(&my_connection,temp5);

  	if (!res){
		fprintf(stdout,"OK: VALCHG Inserted %lu rows\n",
			(unsigned long)mysql_affected_rows(&my_connection));
        }else{
/*	fprintf(stderr,"stderr-VALCHG:INSERT error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
*/
	fprintf(stderr,"Error: VALCHG INSERT error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
	}
	mysql_close(&my_connection);

 } else {
	fprintf(stderr,"Error: VALCHG Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: VALCHG Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
	}
    }
  fprintf(stdout,"\n");
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
