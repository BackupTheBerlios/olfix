/***************************************************************************
                          VERUPD.c  -  description
                             -------------------
			     Ver 0.05
    begin                : Ons 26 mars 2003
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
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/VERUPD.c,v 1.1 2003/05/08 08:54:14 frazze Exp $ " ;


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

char tid[22]="";
char userid[9]="";
char tmpfilepath[50];

int updateVERHUVUD(char hpost[MAXSIZE]);
int updateVERRAD(char dpost[MAXSIZE]);
int updateTRHD(char kpost[MAXSIZE]);
int updateVERNR(char vpost[MAXSIZE]);
int find_tmp_path(char *envp[]);

void getTime();

int main(int argc, char *argv[], char *envp[])
{
	char vrnrfil[50]="";
	char post[MAXSIZE]="";
	char tmp[MAXSIZE]="";
	char kommando[MAXSIZE]="";
	char ext[]=".txt";
	int status=-15;

	FILE *verfil;

	if (argc < 2){
		fprintf(stderr,"Error: VERUPD. Argumentet med vernummer saknas!\n");
		return -1;
	}
	status = find_tmp_path(envp);
//	fprintf(stderr,"status=%d\n",status);

//	fprintf(stdout,"VERUPDmain: argv[1] = %s\n",argv[1]);
	strcpy(vrnrfil,tmpfilepath);
	strcat(vrnrfil,argv[1]);
	strcat(vrnrfil,ext);
//	fprintf(stderr,"VERUPDmain: vrnrfil = %s\n",&vrnrfil);
//	exit(0);
	if ((verfil = fopen(vrnrfil,"r")) == NULL){
		fprintf(stderr,"Error: VERUPD. Filen \"%s\" finns inte!\n",vrnrfil);
		return -1;
	}
//	fprintf(stdout,"VERUPDmain: verfil = %d\n",verfil);

	fread(post,1,POSTSIZE,verfil);
	while (feof(verfil) == 0){

//		fprintf(stdout,"VERUPDmain:Posttyp = %d\n",post[0]);
		if (post[0] == 72){
			status=updateVERHUVUD(post);
			if (status == 0)
				status=updateVERNR(post);
			status=updateVERRAD(post);	// Ska detta göras ?
		}
		if (status == -1)
			exit(status);
		if (post[0] == 68){
			status=updateVERRAD(post);
//			fprintf(stdout,"Status=%d\n",status);
		}
		if (status == -1)
			exit(status);
		status=updateTRHD(post);
		if (status == -1)
			exit(status);
		fread(post,1,POSTSIZE,verfil);
	}
	fclose(verfil);
//	Radera verfil.
	strcpy(kommando,"rm ");
	strcat(kommando,vrnrfil);
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
   int status=0;

   char temp1a[]="INSERT INTO VERHUVUD (VERNR,ARID,VERDATUM,REGDAT,DEBET,KREDIT,VERTEXT,KORRIGERAR,KORRIGERAD,USERID)VALUES (\"";
   char temp2[]="\"";
   char temp3[]=",";
   char temp4[]=")";
   char temp5[TRHDSIZE+POSTSIZE]="";
   char trnsid[]="BOKFOR";
   char posttyp[2];
   char bar[3]="";
   char vernr[9]="";
   char radnr[4]="";
   char ktonr[5]="";
   char dk[2]="";
   char belopp[13]="";
   char debet[13]="";
   char kredit[13]="";
   char kst[5]="";
   char subkto[5]="";
   char datum[11]="";
   char regdat[11]="";
//   char userid[9]="";
   char vertext[101]="";
   char *pos;
   char korrigerar[9]="";
   char korrigerad[9]="";

//   fprintf(stderr,"H-post=%s\n",hpost);
   pos=strstr(hpost,"H");
//   fprintf(stderr,"pos=%d\n",pos);
   strncpy(bar,pos+2,2);
   strncpy(vernr,pos+5,8);
   strncpy(radnr,pos+14,3);
   strncpy(ktonr,pos+18,4);
   strncpy(dk,pos+23,1);
   if (strcmp(dk,"D") == 0){
	strncpy(debet,pos+25,12);	// belopp till debet
	strcpy(kredit,"0");		// 0 kr till kredit
   }
   if (strcmp(dk,"K") == 0){
	strncpy(kredit,pos+25,12);	// belopp till kredit
	strcpy(debet,"0");		// 0 kr till debet
   }
   strncpy(datum,pos+48,10);
   strncpy(regdat,pos+48,10);
   strncpy(userid,pos+59,8);
   strncpy(vertext,pos+68,60);
//	fprintf(stderr,"bar=%s vernr=%s radnr=%s ktonr=%s dk=%s belopp=%s\n",bar,vernr,radnr,ktonr,dk,belopp);
//	fprintf(stderr,"kst=%s subkont=%s datum=%s userid=%s vertext=%s\n",kst,subkto,datum,userid,vertext);
  strcpy(temp5,temp1a);
  strcat(temp5,vernr);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,bar);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,datum);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,regdat);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,debet);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,kredit);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,vertext);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,korrigerar);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,korrigerad);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,userid);
  strcat(temp5,temp2);
  strcat(temp5,temp4);

//  fprintf(stderr,"VERHUVUD temp5=%s\n",temp5);
  mysql_init(&my_connection);

  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", "olfix", 0, NULL, 0)){
//    fprintf(stderr,"Error: VERUPD_TRHDupdate_Connection success\n");
    res = mysql_query(&my_connection,temp5);

  	if (!res){
		fprintf(stdout,"OK: VERUPD_VERHUVUD_Inserted %lu rows\n",
			(unsigned long)mysql_affected_rows(&my_connection));
        }else{
	fprintf(stderr,"Error: VERUPD_VERHUVUD_INSERT error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
					return -1;
	}
	mysql_close(&my_connection);
 } else {
	fprintf(stderr,"Error: VERUPD_VERHUVUD_Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: VERUPD_VERHUVUD_Connection error %d:  %s\n",
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
   int status=0;

   char temp1a[]="INSERT INTO VERRAD (VERNR,RADNR,ARID,KTONR,BELOPP,DK,KSTALLE,PROJEKT,SUBKTO,DEFINITIV,STRUKEN)VALUES (\"";
   char temp2[]="\"";
   char temp3[]=",";
   char temp4[]=")";
   char temp5[TRHDSIZE+POSTSIZE]="";
   char trnsid[]="BOKFOR";

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
//	fprintf(stderr,"bar=%s vernr=%s radnr=%s ktonr=%s dk=%s belopp=%s kst=%s subkto=%s\n",bar,vernr,radnr,ktonr,dk,belopp,kst,subkto);
//	fprintf(stderr,"D-post=%s",dpost);

  strcpy(temp5,temp1a);
  strcat(temp5,vernr);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,radnr);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,bar);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,ktonr);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,belopp);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,dk);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,kst);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,projekt);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,subkto);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,def);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,struken);
  strcat(temp5,temp2);
  strcat(temp5,temp4);

//  fprintf(stderr,"temp5=%s\n",temp5);

  mysql_init(&my_connection);

  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", "olfix", 0, NULL, 0)){
//    fprintf(stderr,"Error: VERUPD_TRHDupdate_Connection success\n");
    res = mysql_query(&my_connection,temp5);

  	if (!res){
		fprintf(stdout,"OK: VERUPD_VERRAD_Inserted %lu rows\n",
			(unsigned long)mysql_affected_rows(&my_connection));
        }else{
	fprintf(stderr,"Error: VERUPD_VERRAD_INSERT error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
	}
	mysql_close(&my_connection);

 } else {
	fprintf(stderr,"Error: VERUPD_VERRAD_Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: VERUPD_VERRAD_Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
	}
    }
  return EXIT_SUCCESS;
}

int updateTRHD(char kpost[MAXSIZE])
{
  MYSQL my_connection;
  int res;
  int status=0;

  char temp1a[]="INSERT INTO TRHD (TRNSID,TID,USERID,TRNSDATA)VALUES (\"";
  char temp2[]="\"";
  char temp3[]=",";
  char temp4[]=")";
  char temp5[TRHDSIZE+POSTSIZE]="";
  char trnsid[]="BOKFOR";

  getTime();
  
  strcpy(temp5,temp1a);
  strcat(temp5,trnsid);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,tid);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,userid);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,kpost);
  strcat(temp5,temp2);
  strcat(temp5,temp4);
//  fprintf(stderr,"temp5=%s\n",temp5);
//  return 0;
  mysql_init(&my_connection);

  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", "olfix", 0, NULL, 0)){
//    fprintf(stderr,"Error: VERUPD_TRHDupdate_Connection success\n");
    res = mysql_query(&my_connection,temp5);

  	if (!res){
		fprintf(stdout,"OK: VERUPD_TRHD_Inserted %lu rows\n",
			(unsigned long)mysql_affected_rows(&my_connection));
        }else{
	fprintf(stderr,"Error: VERUPD_TRHD_INSERT error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
					exit(-1);
	}
	mysql_close(&my_connection);

 } else {
	fprintf(stderr,"Error: VERUPD_TRHD_Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: VERUPD_TRHD_Connection error %d:  %s\n",
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
//  fprintf(stderr,"tid nr 5= %s\n",tid);
  return;
}

int updateVERNR(char vpost[MAXSIZE])
{
  MYSQL my_connection;
  int res;
  int status=0;

  char temp1a[]="UPDATE BOKFAR SET VERNR = VERNR + 1 ";
  char temp1b[]="SENVERDAT = ";
  char temp1c[]=" WHERE ARID = ";
  char temp2[]="\"";
  char temp3[]=",";
  char temp4[]=")";
  char temp5[TRHDSIZE+POSTSIZE]="";
  char *pos;
  char bar[3]="";
  char vernr[9]="";
  char datum[11]="";

  pos=strstr(vpost,"H");
  strncpy(bar,pos+2,2);
  strncpy(vernr,pos+5,8);
  strncpy(datum,pos+48,10);


  strcpy(temp5,temp1a);
/* UPDATE BOKFAR SET VERNR = VERNR + 1 */
  strcat(temp5,temp3);
  strcat(temp5,temp1b);
/* UPDATE BOKFAR SET VERNR = VERNR + 1 ,SENVERDAT = */
  strcat(temp5,temp2);
  strcat(temp5,datum);
  strcat(temp5,temp2);
/* UPDATE BOKFAR SET VERNR = VERNR + 1 ,SENVERDAT = "2003-03-04"*/
  strcat(temp5,temp1c);
/* UPDATE BOKFAR SET VERNR = VERNR + 1 ,SENVERDAT = "2003-03-04" WHERE ARID = */
  strcat(temp5,temp2);
  strcat(temp5,bar);
  strcat(temp5,temp2);
/* UPDATE BOKFAR SET VERNR = VERNR + 1 ,SENVERDAT = "2003-03-04" WHERE ARID = "AC"*/
//  fprintf(stderr,"temp5=%s\n",temp5);
  
  mysql_init(&my_connection);

  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", "olfix", 0, NULL, 0)){
//    fprintf(stderr,"Error: VERUPD_TRHDupdate_Connection success\n");
    res = mysql_query(&my_connection,temp5);

  	if (!res){
		fprintf(stdout,"OK: VERUPD_VERNR_updated %lu rows\n",
			(unsigned long)mysql_affected_rows(&my_connection));
        }else{
	fprintf(stderr,"Error: VERUPD_VERNR_INSERT error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
					exit(-1);
	}
	mysql_close(&my_connection);

 } else {
	fprintf(stderr,"Error: VERUPD_VERNR_Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: VERUPD_VERNR_Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
			exit(-1);
	}
    }
  return EXIT_SUCCESS;
}

int find_tmp_path(char *envp[])
{
	FILE *fil_pek;

//	char home[]="$HOME";
	char home[50];
	char *home_pek;
	char resource[]="/.olfixrc";
	char filename[50]="";
	char tmp[50]="";
	char temp[10]="";
	char *tmp_pek;
	int i,j,status;

	for (i = 0;envp[i]!=NULL;i++){
//	fprintf(stderr,"envp[%d]=%s\n",i,envp[i]);
		if(strstr(envp[i],"HOME=") != NULL){
			strncpy(temp,envp[i],4);
//			fprintf(stderr,"temp=%s\n",temp);
			status=strcmp(temp,"HOME");
//			fprintf(stderr,"status=%d\n",status);
			if (status == 0){
				home_pek=(strstr(envp[i],"HOME="));
				home_pek=home_pek+5;
				strcpy(home,home_pek);
			}
//			fprintf(stderr,"home_pek=%d %s\n",home_pek,home_pek);
//			fprintf(stderr,"home_pek=%d %s\n",home_pek,home_pek);
		}
	}
//	fprintf(stderr,"home=%s\n",home);
	strcpy(filename,home);
	strcat(filename,resource);
//	fprintf(stderr,"filename=%s\n",filename);
	status=-1;

	fil_pek = fopen(filename,"r");
	while (fgets(tmp,50,fil_pek) != NULL){
//		fprintf(stderr,"tmp=%s\n",tmp);
		if(strstr(tmp,"VTMP=")){
			tmp_pek=(strstr(tmp,"VTMP="))+5;
			strcpy(tmpfilepath,tmp_pek);
			status=0;
		}
	}
//	fprintf(stderr,"tmpfilepath=%s\n",tmpfilepath);
	fclose(fil_pek);
	return status;
}

