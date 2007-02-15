/***************************************************************************
                          LSDEL.c  -  description
                             -------------------
    Version		 : 0.2
    begin                : Ons  10 maj	2006
    modified		 : Tors 15 febr 2007
    copyright            : (C) 2006 by Jan Pihlgren
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
	INPUT: 2 st arg. LSDEL artnr lagerst

	Kommando: ./LSDEL artnr lagerst

	Function: Radera post från tabell LAGERSTELLEREG

	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/LSDEL.c,v 1.2 2007/02/15 04:07:23 janpihlgren Exp $ " ;

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
/*  int i;*/
  int res;
  int status;
  const char *userp = getenv("USER");	/* vem är inloggad?	*/
  char databas[25]="olfix";
  char usr[21];				/* userid 20070215 utökat från 15 till 21 tecken */

  char temp1[]="DELETE FROM LAGERSTELLEREG WHERE ARLAGST = \"";
  char temp1b[]=" AND ARTIKELNR = \"";
  char temp2[]="\"";
  char temp5[200]="";
  char lagerstelle[2]="";
  char artikelnr[31]="";

/* ================================================================================ */
/* 		Val av databas, START						    */
/* ================================================================================ */

  status = which_database(envp);

  if (status != 0)
	exit(status);

  strncpy(usr,userp,sizeof(usr));			/* Den inloggades userid 20070215 */
  if (argc < ANTARG+1){
    	if (strlen(database)!= 0){
		strncpy(databas,database,sizeof(databas));
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
/* Om usr (userid) börjar på 'test' eller 'prov' använd databas 'olfixtst' */
  if (strncmp(usr,"test",4)==0 || strncmp(usr,"prov",4)==0 ) {
  	strncpy(databas,"olfixtst",15);
  }
/* ================================================================================ */
/* 		Val av databas, END!						    */
/* ================================================================================ */

  strncpy(lagerstelle,argv[1],sizeof(lagerstelle));
  strncpy(artikelnr,argv[2],sizeof(artikelnr));

  strncat(temp5,temp1,strlen(temp1));
/* DELETE FROM LAGERSTELLEREG WHERE ARLAGST = "  */
  strncat(temp5,lagerstelle,sizeof(lagerstelle));/* 001 */
/* DELETE FROM LAGERSTELLEREG WHERE ARLAGST = "001  	*/
  strncat(temp5,temp2,sizeof(temp2)); /*  "     */
/* DELETE FROM LAGERSTELLEREG WHERE ARLAGST = "001" 	*/
  strncat(temp5,temp1b,sizeof(temp1b)); /* AND ARTIKELNR = "*/
/* DELETE FROM LAGERSTELLEREG WHERE ARLAGST = "001" AND ARTIKELNR = "	*/
  strncat(temp5,artikelnr,sizeof(artikelnr));/* 1000-1001 */
/* DELETE FROM LAGERSTELLEREG WHERE ARLAGST = "001" AND ARTIKELNR = "1000-1001	*/
  strncat(temp5,temp2,sizeof(temp2)); /*  "     */
/* DELETE FROM LAGERSTELLEREG WHERE ARLAGST = "001" AND ARTIKELNR = "1000-1001"	*/
/*  fprintf(stderr,"LSDEL: temp5 = %s\n",temp5);	*/
/* exit(0);	*/

  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
  	res = mysql_query(&my_connection,temp5);
  	if (!res){
		fprintf(stdout,"OK: LSDEL Deleted %lu rows\n",
			(unsigned long)mysql_affected_rows(&my_connection));
  	}else{
	fprintf(stderr,"Error: LSDEL DELETE error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
	}
	mysql_close(&my_connection);
  }else{
    	fprintf(stderr,"Error: LSDEL Connection failed\n");
    	if (mysql_errno(&my_connection)){
    		fprintf(stderr,"Error: LSDEL Connection error %d:  %s\n",
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
			status=strcmp(temp,"HOME");
			if (status == 0){
				home_pek=(strstr(envp[i],"HOME="));
				home_pek=home_pek+5;
				strcpy(home,home_pek);
			}
		}
	}
	strncpy(filename,home,strlen(home));
	strncat(filename,resource,strlen(resource));

	status=-1;

	if ((fil_pek = fopen(filename,"r")) != NULL){
		while (fgets(tmp,150,fil_pek) != NULL){
			if(strstr(tmp,"DATABASE=")){
				tmp_pek=(strstr(tmp,"DATABASE="))+9;
				strncpy(database,tmp_pek,strlen(tmp_pek));
				status=0;
			}
		}
		fclose(fil_pek);
	}
	else{
	 	fprintf(stderr,"Error: Filen .olfixrc kan inte öppnas\n");
	}
	for (i=0;i < strlen(database);i++){
		tmp[i]=database[i];
	}
	tmp[i-1]=0;
	strncpy(database,tmp,strlen(tmp));
	database[strlen(tmp)]=0;

	return status;
}
