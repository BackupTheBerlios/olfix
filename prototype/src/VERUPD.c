/***************************************************************************
                          VERUPD.c  -  description
                             -------------------
    Version		 : 0.91
    begin                : Tis  29 april 2003
    modified		 : Mån  19 febr  2007
    copyright            : (C) 2002 by Jan Pihlgren
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
	INPUT: 1 st arg, vernr

	Kommando: ./VERUPD 12345

	Function: Läsa filen 12345.txt och uppdatera databasen med info för aktuell
	verifikation. När uppdateringe är klar ska filen /tmp/12345.txt raderas.

	OUTPUT: errornb och error (text)
*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/VERUPD.c,v 1.7 2007/02/19 07:03:19 janpihlgren Exp $ " ;


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "mysql.h"
#define MAXSTRING 10000
#define MAXSIZE 200
#define POSTSIZE 178
#define TRHDSIZE 255
#define FORMAT_STR "%Y-%m-%d_%H:%M:%S"    /* YYYY-MM-DD */
#define ANTARG 2

  MYSQL my_connection;
  MYSQL_RES *res_ptr;
  MYSQL_ROW sqlrow;

char tid[22]="";
char userid[21]=""; 		/* 20070219 utökat från 9 till 21 tecken */
char tmpfilepath[50]="";
char database[15]="";
char databas[25]="olfix";

int updateVERHUVUD(char hpost[MAXSIZE]);
int updateVERRAD(char dpost[MAXSIZE]);
int updateTRHD(char kpost[MAXSIZE]);
int updateVERNR(char vpost[MAXSIZE]);
int find_tmp_path(char *envp[]);
void getTime();
int which_database(char *envp[]);

int main(int argc, char *argv[], char *envp[])
{
 int i;
/*  int res;	*/
  const char *userp = getenv("USER");	/* vem är inloggad?	*/

  char usr[21];				/* userid 20070219 utökat från 15 till 21 tecken */

  char vrnrfil[50]="";
  char post[MAXSIZE]="";
/*  char tmp[MAXSIZE]="";		*/
  char kommando[MAXSIZE]="";
  char ext[]=".txt";
  int status=-15;

	status = find_tmp_path(envp);
/*	fprintf(stderr,"status=%d\n",status);	*/
	if (status != 0)
		exit(status);

/* ================================================================================ */
/* 		Val av databas, START						    */
/* ================================================================================ */

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


	FILE *verfil;

	if (argc < 2){
		fprintf(stderr,"Error: VERUPD. Argumentet med vernummer saknas!\n");
		return -1;
	}
/*	fprintf(stdout,"VERUPDmain: argv[1] = %s\n",argv[1]);		*/
	for (i=0;i<strlen(tmpfilepath);i++){
		if (tmpfilepath[i]==13 ||tmpfilepath[i]==10 ){
			tmpfilepath[i]=0;
		}
	}

	strcpy(vrnrfil,tmpfilepath);
	strncat(vrnrfil,argv[1],sizeof(vrnrfil));		/* argv[1] = vernr	2005-02-24 */
	strncat(vrnrfil,ext,strlen(ext));
/*	fprintf(stderr,"VERUPDmain: vrnrfil = %s\n",&vrnrfil);		*/
/*	exit(0);							*/
	if ((verfil = fopen(vrnrfil,"r")) == NULL){
		fprintf(stderr,"Error: VERUPD. Filen \"%s\" finns inte!\n",vrnrfil);
		return -1;
	}
/*	fprintf(stdout,"VERUPDmain: verfil = %d\n",verfil);		*/

	fread(post,1,POSTSIZE,verfil);
	while (feof(verfil) == 0){

/*		fprintf(stdout,"VERUPDmain:Posttyp = %d\n",post[0]);	*/
		if (post[0] == 72){
			status=updateVERHUVUD(post);
			if (status == 0)
				status=updateVERNR(post);
			status=updateVERRAD(post);	/* Ska detta göras ?	*/
		}
		if (status == -1)
			exit(status);
		if (post[0] == 68){
			status=updateVERRAD(post);
/*			fprintf(stdout,"Status=%d\n",status);		*/
		}
		if (status == -1)
			exit(status);
		status=updateTRHD(post);
		if (status == -1)
			exit(status);
		fread(post,1,POSTSIZE,verfil);
	}
	fclose(verfil);
/*	Radera verfil.							*/
	strncpy(kommando,"rm ",3);
	strncat(kommando,vrnrfil,strlen(vrnrfil));
	status=system(kommando);
	if (status == 0){
		fprintf(stdout,"OK: Databasen uppdaterad!\n");
	}
	return status;
}

int updateVERHUVUD(char hpost[MAXSIZE])
{
   MYSQL my_connection;
   int res;
/*   int status=0;	*/

   char temp1a[]="INSERT INTO VERHUVUD (VERNR,ARID,VERDATUM,REGDAT,DEBET,KREDIT,VERTEXT,KORRIGERAR,KORRIGERAD,USERID)VALUES (\"";
   char temp2[]="\"";
   char temp3[]=",";
   char temp4[]=")";
   char temp5[TRHDSIZE+POSTSIZE]="";
/*   char trnsid[]="BOKFOR";		*/
/*   char posttyp[2]="";		*/
   char bar[3]="";
   char vernr[9]="";
   char radnr[4]="";
   char ktonr[5]="";
   char dk[2]="";
/*   char belopp[13]="";		*/
   char debet[13]="";
   char kredit[13]="";
/*   char kst[5]="";			*/
/*   char subkto[5]="";			*/
   char datum[11]="";
   char regdat[11]="";
/*   char userid[21]="";		*/
   char vertext[101]="";
   char *pos;
   char korrigerar[9]="";
   char korrigerad[9]="";

/*   fprintf(stderr,"H-post=%s\n",hpost);		*/
   pos=strstr(hpost,"H");
/*   fprintf(stderr,"pos=%d\n",pos);			*/
   strncpy(bar,pos+2,2);
   strncpy(vernr,pos+5,8);
   strncpy(radnr,pos+14,3);
   strncpy(ktonr,pos+18,4);
   strncpy(dk,pos+23,1);
   if (strcmp(dk,"D") == 0){
	strncpy(debet,pos+25,12);	/* belopp till debet	*/
	strncpy(kredit,"0",1);		/* 0 kr till kredit	*/
   }
   if (strcmp(dk,"K") == 0){
	strncpy(kredit,pos+25,12);	/* belopp till kredit	*/
	strncpy(debet,"0",1);		/* 0 kr till debet	*/
   }
   strncpy(datum,pos+48,10);
   strncpy(regdat,pos+48,10);
   strncpy(userid,pos+59,20);		/* 20070219 utökat från 8 till 20 */
   strncpy(vertext,pos+68,60);
/*	fprintf(stderr,"bar=%s vernr=%s radnr=%s ktonr=%s dk=%s belopp=%s\n",bar,vernr,radnr,ktonr,dk,belopp);	*/
/*	fprintf(stderr,"kst=%s subkont=%s datum=%s userid=%s vertext=%s\n",kst,subkto,datum,userid,vertext);	*/
  strncpy(temp5,temp1a,strlen(temp1a));
  strncat(temp5,vernr,strlen(vernr));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,bar,strlen(bar));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,datum,strlen(datum));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,regdat,strlen(regdat));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,debet,strlen(debet));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,kredit,strlen(kredit));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,vertext,strlen(vertext));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,korrigerar,strlen(korrigerar));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,korrigerad,strlen(korrigerad));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,userid,strlen(userid));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp4,strlen(temp4));

/*  fprintf(stderr,"VERHUVUD temp5=%s\n",temp5);	*/
  mysql_init(&my_connection);

  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
/*    fprintf(stderr,"Error: VERUPD_TRHDupdate_Connection success\n");	*/
    res = mysql_query(&my_connection,temp5);

  	if (!res){
		fprintf(stdout,"OK: VERUPD VERHUVUD_Inserted %lu rows\n",
			(unsigned long)mysql_affected_rows(&my_connection));
        }else{
	fprintf(stderr,"Error: VERUPD VERHUVUD_INSERT error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
					return -1;
	}
	mysql_close(&my_connection);
 } else {
	fprintf(stderr,"Error: VERUPD VERHUVUD_Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: VERUPD VERHUVUD_Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
			return -1;
	}
    }
  return EXIT_SUCCESS;
}

int updateVERRAD(char dpost[MAXSIZE])
{
   MYSQL my_connection;
   int res;
/*   int status=0;		*/

   char temp1a[]="INSERT INTO VERRAD (VERNR,RADNR,ARID,KTONR,BELOPP,DK,KSTALLE,PROJEKT,SUBKTO,DEFINITIV,STRUKEN)VALUES (\"";
   char temp2[]="\"";
   char temp3[]=",";
   char temp4[]=")";
   char temp5[TRHDSIZE+POSTSIZE]="";
/*   char trnsid[]="BOKFOR";		*/

   char bar[3]="";
   char vernr[9]="";
   char radnr[4]="";
   char ktonr[5]="";
   char dk[2]="";
   char belopp[13]="";
   char kst[5]="";
   char projekt[5]="";
   char subkto[5]="";
   char def[2]="N";
   char struken[2]="N";
   char *pos;

   pos=strstr(dpost,"H");
   if (pos == NULL){
   	pos=strstr(dpost,"D");
   }
   strncpy(bar,pos+2,2);
   strncpy(vernr,pos+5,8);
   strncpy(radnr,pos+14,3);
   strncpy(ktonr,pos+18,4);
   strncpy(dk,pos+23,1);
   strncpy(belopp,pos+25,12);
   strncpy(kst,pos+38,4);
   strncpy(subkto,pos+43,4);
/*	fprintf(stderr,"bar=%s vernr=%s radnr=%s ktonr=%s dk=%s belopp=%s kst=%s subkto=%s\n",bar,vernr,radnr,ktonr,dk,belopp,kst,subkto);	*/
/*	fprintf(stderr,"D-post=%s",dpost);			*/

  strncpy(temp5,temp1a,strlen(temp1a));
  strncat(temp5,vernr,strlen(vernr));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,radnr,strlen(radnr));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,bar,strlen(bar));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,ktonr,strlen(ktonr));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,belopp,strlen(belopp));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,dk,strlen(dk));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,kst,strlen(kst));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,projekt,strlen(projekt));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,subkto,strlen(subkto));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,def,strlen(def));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,struken,strlen(struken));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp4,strlen(temp4));

/*  fprintf(stderr,"temp5=%s\n",temp5);		*/

  mysql_init(&my_connection);

  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
/*    fprintf(stderr,"Error: VERUPD_TRHDupdate_Connection success\n");		*/
    res = mysql_query(&my_connection,temp5);

  	if (!res){
		fprintf(stdout,"OK: VERUPD VERRAD_Inserted %lu rows\n",
			(unsigned long)mysql_affected_rows(&my_connection));
        }else{
	fprintf(stderr,"Error: VERUPD VERRAD INSERT error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
	}
	mysql_close(&my_connection);

 } else {
	fprintf(stderr,"Error: VERUPD VERRAD Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: VERUPD VERRAD Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
	}
    }
  return EXIT_SUCCESS;
}

int updateTRHD(char kpost[MAXSIZE])
{
  MYSQL my_connection;
  int res;
/*  int status=0;		*/

  char temp1a[]="INSERT INTO TRHD (TRNSID,TID,USERID,TRNSDATA)VALUES (\"";
  char temp2[]="\"";
  char temp3[]=",";
  char temp4[]=")";
  char temp5[TRHDSIZE+POSTSIZE]="";
  char trnsid[]="BOKFOR";

  getTime();

  strncpy(temp5,temp1a,strlen(temp1a));
  strncat(temp5,trnsid,strlen(trnsid));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,tid,strlen(tid));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,userid,strlen(userid));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,kpost,strlen(kpost));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp4,strlen(temp4));
/*  fprintf(stderr,"temp5=%s\n",temp5);		*/
/*  return 0;					*/
  mysql_init(&my_connection);

  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
/*    fprintf(stderr,"Error: VERUPD_TRHDupdate_Connection success\n");		*/
    res = mysql_query(&my_connection,temp5);

  	if (!res){
		fprintf(stdout,"OK: VERUPD TRHD Inserted %lu rows\n",
			(unsigned long)mysql_affected_rows(&my_connection));
        }else{
	fprintf(stderr,"Error: VERUPD TRHD INSERT error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
					exit(-1);
	}
	mysql_close(&my_connection);

 } else {
	fprintf(stderr,"Error: VERUPD TRHD Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: VERUPD TRHD Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
			exit(-1);
	}
    }
  return EXIT_SUCCESS;
}

void getTime()
{
  time_t t;
  struct tm *tm_t;
  char *str;
  t = time(NULL);
  tm_t = localtime(&t);

  str = malloc(MAXSIZE + 1);
  strftime(str, 25, FORMAT_STR, tm_t);
  strncpy(tid,str,20);
  free(str);
/*  fprintf(stderr,"tid nr 5= %s\n",tid);	*/
  return;
}

int updateVERNR(char vpost[MAXSIZE])
{
  MYSQL my_connection;
  int res;
/*  int status=0;	*/

  char temp1a[]="UPDATE BOKFAR SET VERNR = VERNR + 1 ";
  char temp1b[]="SENVERDAT = ";
  char temp1c[]=" WHERE ARID = ";
  char temp2[]="\"";
  char temp3[]=",";
  char temp5[TRHDSIZE+POSTSIZE]="";
  char *pos;
  char bar[3]="";
  char vernr[9]="";
  char datum[11]="";

  pos=strstr(vpost,"H");
  strncpy(bar,pos+2,2);
  strncpy(vernr,pos+5,8);
  strncpy(datum,pos+48,10);


  strncpy(temp5,temp1a,strlen(temp1a));
/* UPDATE BOKFAR SET VERNR = VERNR + 1 */
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp1b,strlen(temp1b));
/* UPDATE BOKFAR SET VERNR = VERNR + 1 ,SENVERDAT = */
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,datum,strlen(datum));
  strncat(temp5,temp2,strlen(temp2));
/* UPDATE BOKFAR SET VERNR = VERNR + 1 ,SENVERDAT = "2003-03-04"*/
  strncat(temp5,temp1c,strlen(temp1c));
/* UPDATE BOKFAR SET VERNR = VERNR + 1 ,SENVERDAT = "2003-03-04" WHERE ARID = */
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,bar,strlen(bar));
  strncat(temp5,temp2,strlen(temp2));
/* UPDATE BOKFAR SET VERNR = VERNR + 1 ,SENVERDAT = "2003-03-04" WHERE ARID = "AC"*/
/*  fprintf(stderr,"temp5=%s\n",temp5);		*/

  mysql_init(&my_connection);

  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
/*    fprintf(stderr,"Error: VERUPD_TRHDupdate_Connection success\n");		*/
    res = mysql_query(&my_connection,temp5);

  	if (!res){
		fprintf(stdout,"OK: VERUPD VERNR updated %lu rows\n",
			(unsigned long)mysql_affected_rows(&my_connection));
        }else{
	fprintf(stderr,"Error: VERUPD VERNR INSERT error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
					exit(-1);
	}
	mysql_close(&my_connection);

 } else {
	fprintf(stderr,"Error: VERUPD VERNR Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: VERUPD VERNR Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
			exit(-1);
	}
    }
  return EXIT_SUCCESS;
}

int find_tmp_path(char *envp[])
{
	FILE *fil_pek;

/*	char home[]="$HOME";		*/
	char home[50]="";
	char *home_pek;
	char resource[]="/.olfixrc";
	char filename[50]="";
	char tmp[50]="";
	char temp[10]="";
	char *tmp_pek;
	int i,status;

	for (i = 0;envp[i]!=NULL;i++){
/*	fprintf(stderr,"envp[%d]=%s\n",i,envp[i]);		*/
		if(strstr(envp[i],"HOME=") != NULL){
			strncpy(temp,envp[i],4);
/*			fprintf(stderr,"temp=%s\n",temp);	*/
			status=strcmp(temp,"HOME");
/*			fprintf(stderr,"status=%d\n",status);	*/
			if (status == 0){
				home_pek=(strstr(envp[i],"HOME="));
				home_pek=home_pek+5;
				strcpy(home,home_pek);
			}
/*			fprintf(stderr,"home_pek=%d %s\n",home_pek,home_pek);	*/
/*			fprintf(stderr,"home_pek=%d %s\n",home_pek,home_pek);	*/
		}
	}
/*	fprintf(stderr,"home=%s\n",home);			*/
	strncpy(filename,home,strlen(home));
	strncat(filename,resource,strlen(resource));
/*	fprintf(stderr,"filename=%s\n",filename);		*/
	status=-1;
	if ((fil_pek = fopen(filename,"r")) != NULL){
		while (fgets(tmp,50,fil_pek) != NULL){
/*			fprintf(stderr,"tmp=%s\n",tmp);		*/
			if(strstr(tmp,"VTMP=")){
				tmp_pek=(strstr(tmp,"VTMP="))+5;
				strncpy(tmpfilepath,tmp_pek,strlen(tmp_pek));
				status=0;
			}
		}
		fclose(fil_pek);
	}
	else{
	 	fprintf(stderr,"Error: Filen .olfixrc kan inte öppnas\n");
	}
/*	fprintf(stderr,"tmpfilepath=%s\n",tmpfilepath);		*/
	return status;
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
