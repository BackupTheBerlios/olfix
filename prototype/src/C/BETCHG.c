/***************************************************************************
                          BETCHG.c  -  description
                             -------------------
    Version		 : 0.1
    begin                : Fre 28 nov	2003
    modified		 :
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
 *********************************************** ****************************/

/*
	INPUT: 3 st arg. BETVILKOR, DAGAR och BESKRIVNING (f�lten i tabellen BETVILKOR)

	Kommando: ./BETCHG 001 10 "10 dagar netto"

	Function: �ndra record i tabell BETVILKOR

	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/C/Attic/BETCHG.c,v 1.1 2004/05/03 04:42:57 janpihlgren Exp $ " ;

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql.h"
#define ANTARG 4

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

  char temp1[]="UPDATE BETVILKOR SET DAGAR = ";
  char temp1b[]=" WHERE BETVILKOR = ";
  char temp1c[]="BESKRIVNING = ";
  char temp2[]="\"";
  char temp3[]=",";
  char temp5[200]="";
  char betvilkor[4]="";
  char dagar[4]="";
  char beskrivning[41]="";

//  fprintf(stderr,"argc=%d\n",argc);
  if (argc < ANTARG){
  	fprintf(stderr,"Data saknas!\n");
	exit(0);
  }
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

  strncpy(betvilkor,argv[1],strlen(argv[1]));
  strncpy(dagar,argv[2],strlen(argv[2]));
  strncpy(beskrivning,argv[3],strlen(argv[3]));

  strncpy(temp5,temp1,strlen(temp1));
/* UPDATE BETVILKOR SET DAGAR =   */
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
  strncat(temp5,dagar,strlen(dagar));/* 10 */
/* UPDATE BETVILKOR SET DAGAR = "10  */
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
  strncat(temp5,temp3,strlen(temp3)); /*  ,     */
  strncat(temp5,temp1c,strlen(temp1c));
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
/* UPDATE BETVILKOR SET DAGAR = "10",BESKRIVNING = "  */
  strncat(temp5,beskrivning,strlen(beskrivning));/* 10 dagar netto  */
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
/* UPDATE BETVILKOR SET DAGAR = "10",BESKRIVNING = "10 dagar netto"  */
  strncat(temp5,temp1b,strlen(temp1b));
/* UPDATE BETVILKOR SET DAGAR = "10",BESKRIVNING = "10 dagar netto" WHERE BETVILKOR =  */
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
  strncat(temp5,betvilkor,strlen(betvilkor));
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
/* UPDATE BETVILKOR SET DAGAR = "10",BESKRIVNING = "10 dagar netto" WHERE BETVILKOR = "001"  */
/*  fprintf(stderr,"temp5=%s\n",temp5);
  exit(0);	*/
  mysql_init(&my_connection);

  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
/* fprintf(stdout,"USERADD:Connection success\n");		*/

    res = mysql_query(&my_connection,temp5);

  	if (!res){
		if ((unsigned long)mysql_affected_rows(&my_connection) > 0){
			fprintf(stdout,"OK: BETCHG Updated %lu rows\n",
				(unsigned long)mysql_affected_rows(&my_connection));
		}else{
			fprintf(stdout,"Error: BETCHG Updated %lu rows\n",
				(unsigned long)mysql_affected_rows(&my_connection));
		}
        }else{
	fprintf(stderr,"Error: BETCHG UPDATE error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
	}
	mysql_close(&my_connection);

 } else {
	fprintf(stderr,"Error: BETADD Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: BETADD Connection error %d:  %s\n",
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
