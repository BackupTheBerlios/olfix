/***************************************************************************
                          BARADD.c  -  description
                             -------------------
    Version		 : 0.2
    begin                : Tors 16 jan 2003
    modified		 : Fre  31 okt 2003
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
	INPUT:	ARID,BENAMNING,ARSTART,ARSLUT,ARLAST,BESKATTNINGSAR,SENVERDAT,VERNR,KONTOPLAN [databas]
	Function: gör  INSERT INTO BOKFAR(ARID,BENAMNING,ARSTART,ARSLUT,BESKATTBINGSAR,SENVERDAT,
		VERNR,KONTOPLAN) VALUES ("SS","2003-01-01--2003-12-31","2003-01-01","2003-12-31","N",
		"2003","0000-00-00","987124","EUBAS97")  i databasen olfix

	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/BARADD.c,v 1.2 2003/10/31 13:38:09 janpihlgren Exp $ " ;

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql.h"
#define ANTARG 10

  MYSQL my_connection;
  MYSQL_RES *res_ptr;
  MYSQL_ROW sqlrow;

int which_database(char *envp[]);
void display_row();

  char database[15]="";

int main(int argc, char *argv[], char *envp[])
{
/* int i;	*/
  int res;
  int status;
  const char *userp = getenv("USER");	// vem är inloggad?
  char databas[25]="olfix";
  char usr[15];				// userid


  char temp1a[]="INSERT INTO BOKFAR(ARID,BENAMNING,ARSTART,ARSLUT,ARLAST,BESKATTNINGSAR,SENVERDAT,VERNR,KONTOPLAN) VALUES (";
  char temp2[]="\"";
  char temp3[]=",";
  char temp4[]=")";
  char temp5[200]="";
  char arid[5];
  char benamn[26];
  char arstart[11];
  char arslut[11];
  char arlast[2];
  char beskattar[5];
  char senverdat[11];
  char vernr[12];
  char ktoplan[16];

/*  fprintf(stderr,"BARADD: argc = %d\n",argc);
  for (i=0;i<=argc;i++){
	fprintf(stderr,"argv%d = %s\n",i,argv[i]);
	}	*/
/*  fprintf(stderr,"ANTARG=%d,argv[ANTARG]=%s\n",ANTARG,argv[ANTARG]);	*/

/* ================================================================================ */
/* 		Val av databas, START						    */
/* ================================================================================ */

  status = which_database(envp);

  if (status != 0)
	exit(status);

  strncpy(usr,userp,15);			// Den inloggades userid
/*  fprintf(stderr,"status=%d ANTARG=%d len(database)=%d\n",status,ANTARG,strlen(database));	*/
  if (argc < ANTARG+1){
    	if (strlen(database)!= 0){
		strncpy(databas,database,15);
	}else{
  		strncpy(databas,"olfixtst",15);	// olfixtst = testföretag
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
 fprintf(stderr,"Databas=%s\n",databas);
/* ================================================================================ */
/* 		Val av databas, END!						    */
/* ================================================================================ */

  if (argv[1] != NULL){
  	strncpy(arid,argv[1],strlen(argv[1]));
  }
  else{
  	fprintf(stderr,"Error: BARADD: Ange årtal!\n");
	exit(-1);
  }

  strncpy(benamn,argv[2],strlen(argv[2]));
  strncpy(arstart,argv[3],strlen(argv[3]));
  strncpy(arslut,argv[4],strlen(argv[4]));
  strncpy(arlast,argv[5],strlen(argv[5]));
  strncpy(beskattar,argv[6],strlen(argv[6]));
  strncpy(senverdat,argv[7],strlen(argv[7]));
  strncpy(vernr,argv[8],strlen(argv[8]));
  strncpy(ktoplan,argv[9],strlen(argv[9]));

  strncpy(temp5,temp1a,strlen(temp1a));
/* INSERT INTO BOKFAR(ARID,BENAMNING,ARSTART,ARSLUT,ARLAST,BESKATTNINGSAR,SENVERDAT,VERNR,KONTOPLAN) VALUES (   */
  strncat(temp5,temp2,strlen(temp2));
/* INSERT INTO BOKFAR(ARID,BENAMNING,ARSTART,ARSLUT,ARLAST,BESKATTNINGSAR,SENVERDAT,VERNR,KONTOPLAN) VALUES ("  */
  strncat(temp5,arid,strlen(arid));
/* INSERT INTO BOKFAR(ARID,BENAMNING,ARSTART,ARSLUT,ARLAST,BESKATTNINGSAR,SENVERDAT,VERNR,KONTOPLAN) VALUES ("AC   */
  strncat(temp5,temp2,strlen(temp2));
/* INSERT INTO BOKFAR(ARID,BENAMNING,ARSTART,ARSLUT,ARLAST,BESKATTNINGSAR,SENVERDAT,VERNR,KONTOPLAN) VALUES ("AC"   */
  strncat(temp5,temp3,strlen(temp3));
/* INSERT INTO BOKFAR(ARID,BENAMNING,ARSTART,ARSLUT,ARLAST,BESKATTNINGSAR,SENVERDAT,VERNR,KONTOPLAN) VALUES ("AC",   */
  strncat(temp5,temp2,strlen(temp2));
/* INSERT INTO BOKFAR(ARID,BENAMNING,ARSTART,ARSLUT,ARLAST,BESKATTNINGSAR,SENVERDAT,VERNR,KONTOPLAN) VALUES ("AC"," */
  strncat(temp5,benamn,strlen(benamn));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
/* INSERT INTO BOKFAR(ARID,BENAMNING,ARSTART,ARSLUT,ARLAST,BESKATTNINGSAR,SENVERDAT,VERNR,KONTOPLAN) VALUES ("AC","2003-01-01--2003-12-31"," */
  strncat(temp5,arstart,strlen(arstart));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
/* INSERT INTO BOKFAR(ARID,BENAMNING,ARSTART,ARSLUT,ARLAST,BESKATTNINGSAR,SENVERDAT,VERNR,KONTOPLAN) VALUES ("AC","2003-01-01--2003-12-31",
"2003-01-01"," */
  strncat(temp5,arslut,strlen(arslut));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
/* INSERT INTO BOKFAR(ARID,BENAMNING,ARSTART,ARSLUT,ARLAST,BESKATTNINGSAR,SENVERDAT,VERNR,KONTOPLAN) VALUES ("AC","2003-01-01--2003-12-31",
"2003-01-01","2003-12-31"," */
  strncat(temp5,arlast,strlen(arlast));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
/* INSERT INTO BOKFAR(ARID,BENAMNING,ARSTART,ARSLUT,ARLAST,BESKATTNINGSAR,SENVERDAT,VERNR,KONTOPLAN) VALUES ("AC","2003-01-01--2003-12-31",
"2003-01-01","2003-12-31","N"," */
  strncat(temp5,beskattar,strlen(beskattar));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
/* INSERT INTO BOKFAR(ARID,BENAMNING,ARSTART,ARSLUT,ARLAST,BESKATTNINGSAR,SENVERDAT,VERNR,KONTOPLAN) VALUES ("AC","2003-01-01--2003-12-31",
"2003-01-01","2003-12-31","N","2003"," */
  strncat(temp5,senverdat,strlen(senverdat));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
/* INSERT INTO BOKFAR(ARID,BENAMNING,ARSTART,ARSLUT,ARLAST,BESKATTNINGSAR,SENVERDAT,VERNR,KONTOPLAN) VALUES ("AC","2003-01-01--2003-12-31",
"2003-01-01","2003-12-31","N","2003","0000-00-00"," */
  strncat(temp5,vernr,strlen(vernr));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
/* INSERT INTO BOKFAR(ARID,BENAMNING,ARSTART,ARSLUT,ARLAST,BESKATTNINGSAR,SENVERDAT,VERNR,KONTOPLAN) VALUES ("AC","2003-01-01--2003-12-31",
"2003-01-01","2003-12-31","N","2003","0000-00-00","987124"," */
  strncat(temp5,ktoplan,strlen(ktoplan));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp4,strlen(temp4));
/*  strcat(temp5,temp2); */
/* INSERT INTO BOKFAR(ARID,BENAMNING,ARSTART,ARSLUT,ARLAST,BESKATTNINGSAR,SENVERDAT,VERNR,KONTOPLAN) VALUES ("AC","2003-01-01--2003-12-31",
"2003-01-01","2003-12-31","N","2003","0000-00-00","987124","EUBAS97" */

/*  fprintf(stderr,"BARADDmain: temp5 = %s\n",temp5);	*/

  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
/*  	fprintf(stderr,"BARADD:Connection success\n");	*/

  res = mysql_query(&my_connection,temp5);

  if (!res){
 	fprintf(stderr,"OK: BARADD Inserted %lu rows\n",
		(unsigned long)mysql_affected_rows(&my_connection));
        }else{
/*	fprintf(stderr,"stderr-BARADD:INSERT error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
*/
	fprintf(stderr,"Error: BARADD databas %s INSERT error: %d  %s\n",databas, mysql_errno(&my_connection),
					mysql_error(&my_connection));
	}
	mysql_close(&my_connection);
 }else {
	fprintf(stderr,"Error: BARADD Connection failed\n");
 	if (mysql_errno(&my_connection))   {
 		fprintf(stderr,"Error: BARADD Connection error %d:  %s\n",
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
