/***************************************************************************
                          PKDADD.c  -  description
                             -------------------
    Version		 : 0.1
    begin                : Mån 29 nov 2004
    modified		 :
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
 *********************************************** ****************************/

/*	INPUT: 2 st arg. PRODKLASS och BESKRIVNING (fälten i tabellen PRODUKTGRUPP)
	Function: Add record i tabell PRODUKTGRUPP

	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/PKDADD.c,v 1.1 2004/11/29 16:54:30 janpihlgren Exp $ " ;

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
/*  int i;	*/
  int res;
  int status;
  const char *userp = getenv("USER");	/* vem är inloggad?	*/
  char databas[25]="olfix";
  char usr[15];				/* userid		*/

  char temp1[]="INSERT INTO PRODUKTGRUPP(PRODKLASS,BESKRIVNING) VALUES (\"";
  char temp2[]="\"";
  char temp3[]=",";
  char temp4[]=")";
  char temp5[200]="";
  char prodkod[6]="";
  char beskrivning[2000]="";
/*
  for (i=0;i<argc;i++){
  	fprintf(stderr,"argc=%d, argv[%d]=%s\n",argc,i,argv[i]);
	}
*/
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

  strncpy(prodkod,argv[1],strlen(argv[1]));
  strncpy(beskrivning,argv[2],strlen(argv[2]));

/*  fprintf(stderr,"argv1=%s argv2=%s\n",argv[1],argv[2]);	*/

  strncat(temp5,temp1,strlen(temp1));
/* INSERT INTO PRODUKTGRUPP(PRODKLASS,BESKRIVNING) VALUES ("  */
  strncat(temp5,prodkod,strlen(prodkod));/* 001 */
/* INSERT INTO PRODUKTGRUPP(PRODKLASS,BESKRIVNING) VALUES ("001  */
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
  strncat(temp5,temp3,strlen(temp3)); /*  ,     */
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
/* INSERT INTO PRODUKTGRUPP(PRODKLASS,BESKRIVNING) VALUES ("001","  */
  strncat(temp5,beskrivning,strlen(beskrivning));/*   */
/* INSERT INTO PRODUKTGRUPP(PRODKLASS,BESKRIVNING) VALUES ("001","Löpande text med information  */
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
  strncat(temp5,temp4,strlen(temp4)); /*  )     */
/* INSERT INTO PRODUKTGRUPP(PRODKLASS,BESKRIVNING) VALUES ("001","Löpande text med information")  */
/*  fprintf(stderr,"temp5=%s\n",temp5);	*/
/*  exit(0);*/

  mysql_init(&my_connection);

  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){


    res = mysql_query(&my_connection,temp5);

  	if (!res){
		fprintf(stdout,"OK: PKDADD Inserted %lu rows\n",
			(unsigned long)mysql_affected_rows(&my_connection));
        }else{
	fprintf(stderr,"Error: PKDADD INSERT error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
        }
	mysql_close(&my_connection);

 } else {
	fprintf(stderr,"Error: PKDADD Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: PKDADD Connection error %d:  %s\n",
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
