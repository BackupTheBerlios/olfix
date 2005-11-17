/***************************************************************************
                          ORADUPD.c  -  description
                             -------------------
    Version		 : 0.1
    begin                : Ons 16 nov 2005
    modified		 :
    copyright            : (C) 2005 by Jan Pihlgren
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
	INPUT: ORDERNR antpost data

	Kommando: ./ORADUPD 3  | 35  010 1 | 35  020 2 | 35  030 3 |
			       ordernr		radnr		antal fakturerat

	Function: Uppdatera fälten  LEVERERAT och RFAKTURERAT i tabellen ORDERRADREG

	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/ORADUPD.c,v 1.2 2005/11/17 09:22:07 janpihlgren Exp $ " ;

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "mysql.h"

#define FORMAT_STR "%Y-%m-%d_%H:%M:%S"    /* YYYY-MM-DD */
#define MAXSIZE 20
#define MAXSTRING 5000
#define TEXTSIZE 500
#define ANTARG 4
#define ANTFELT 3

  MYSQL my_connection;
  MYSQL_RES *res_ptr;
  MYSQL_ROW sqlrow;

int which_database(char *envp[]);
char database[15]="";

int main(int argc, char *argv[], char *envp[])
{
  int res;
  int status;
  int flag=-1;
  int i,l,j,k,n,m;
  int anttecken;
  char *pos1;


  const char *userp = getenv("USER");	/* vem är inloggad?	*/
  char databas[25]="olfix";
  char usr[15]="";			/* userid		*/

  char temp1a[]="UPDATE ORDERRADREG SET FAKTURERAT = FAKTURERAT + \"";

  char temp1b[]=" , LEVERERAT = LEVERERAT + \"";
  char temp2a[]=" WHERE ORDERNR = \"";
  char temp2b[]=" AND ORDERRAD = \"";
  char temp3[]="\"";
  char temp5[TEXTSIZE]="";

  int antalposter;
  char ordernr[11]="";
  char radnr[4]="";
  char levererat[14]="0";			/* levererat antal */
  char fakturerat[14]="";			/* fakturerat antal */
  char data[MAXSTRING]="";			/* data, radinformation		*/
  char temp[5]="";

  status=-15;
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
/* fprintf(stderr,"Databas=%s\n",databas);		*/
/* ================================================================================ */
/* 		Val av databas, END!						    */
/* ================================================================================ */
  strncpy(temp,argv[1],sizeof(temp));
/*  fprintf(stderr,"temp=%s\n",temp);		*/
  antalposter=atoi(temp);
/*  fprintf(stderr,"antalposter=%d\n",antalposter);	*/
/*  fprintf(stderr,"argc=%d argv[0]=%s argv[1]=%s argv[2]=%s \n",argc,argv[0],argv[1],argv[2]);		*/
  strncpy(data,argv[2],sizeof(data));
//  fprintf(stderr,"data=%s\n",data);
  l=strlen(data);
//  fprintf(stderr,"l=%d\n",l);

  pos1=strstr(data,"|");
  k=2;
  n=1;
  m=0;
  for(i=0;i<antalposter;i++){
/*  	fprintf(stderr,"n=%d\n",n);	*/
	for (j=n;j<l;j++){
		if(data[j] == 124){
			anttecken=j-n;
			strncpy(ordernr,pos1+n,anttecken);
/*			fprintf(stderr,"1.  ordernr=%s j=%d n=%d anttecken=%d\n",ordernr,j,n,anttecken);	*/
			n=j+1;
			m=j;
			j=l;
		}
	}
/*	fprintf(stderr,"n=%d\n",n);	*/
	for (j=n;j<l;j++){
		if(data[j] == 124){
			anttecken=j-n;
			strncpy(radnr,pos1+n,anttecken);
/*			fprintf(stderr,"2.  radnr=%s j=%d n=%d anttecken=%d\n",radnr,j,n,anttecken);	*/
			n=j+1;
			m=j;
			j=l;
		}
	}
/*	fprintf(stderr,"n=%d\n",n);	*/
	for (j=n;j<l;j++){
		if(data[j] == 124){
			anttecken=j-n;
			strncpy(fakturerat,pos1+n,anttecken);
/*			fprintf(stderr,"3.  fakturerat=%s j=%d n=%d anttecken=%d\n",fakturerat,j,n,anttecken);	*/
			n=j+1;
			m=j;
			j=l;
		}
	}
	strncpy(temp5,temp1a,sizeof(temp1a));
/* UPDATE ORDERRADREG SET FAKTURERAT = FAKTURERAT + "  */
  	strncat(temp5,fakturerat,sizeof(fakturerat));
  	strncat(temp5,temp3,sizeof(temp3));
/* UPDATE ORDERRADREG SET LEVERERAT = LEVERERAT +  "15"  */
  	strncat(temp5,temp1b,sizeof(temp1b));
/*  UPDATE ORDERRADREG SET LEVERERAT = LEVERERAT + "15" , LEVERERAT = LEVERERAT + " */
        strncat(temp5,levererat,sizeof(levererat));
	strncat(temp5,temp3,sizeof(temp3));
/*  UPDATE ORDERRADREG SET LEVERERAT = LEVERERAT + "15" , LEVERERAT = LEVERERAT + "15" */
  	strncat (temp5,temp2a,sizeof(temp2a));
/*  UPDATE ORDERRADREG SET LEVERERAT = LEVERERAT + "15" , LEVERERAT = LEVERERAT + "15"  WHERE ORDERNR = "  */
  	strncat(temp5,ordernr,sizeof(ordernr));
  	strncat(temp5,temp3,sizeof(temp3));
/*  UPDATE ORDERRADREG SET LEVERERAT = LEVERERAT + "15" , LEVERERAT = LEVERERAT + "15"  WHERE ORDERNR = "45123"  */
  	strncat(temp5,temp2b,sizeof(temp2b));
/*  UPDATE ORDERRADREG SET LEVERERAT = LEVERERAT + "15" , LEVERERAT = LEVERERAT + "15"  WHERE ORDERNR = "45123" AND ORDERRAD = " */
  	strncat(temp5,radnr,sizeof(radnr));
  	strncat(temp5,temp3,sizeof(temp3));
/*  UPDATE ORDERRADREG SET LEVERERAT = LEVERERAT + "15" , LEVERERAT = LEVERERAT + "15"  WHERE ORDERNR = "45123" AND ORDERRAD = "010" */

/* 	fprintf(stderr,"ORADUPDmain: temp5=%s\n",temp5);	*/

 	strncpy(ordernr," ",sizeof(ordernr));
	strncpy(radnr," ",sizeof(radnr));
	strncpy(fakturerat," ",sizeof(fakturerat));
/*	fprintf(stderr,"\n");	*/

//  exit(0);
	mysql_init(&my_connection);

  	if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
/*    fprintf(stderr,"ORADUPD:Connection success\n");	*/
    		res = mysql_query(&my_connection,temp5);
  		if (!res){
			if ((unsigned long)mysql_affected_rows(&my_connection) < 1){
				fprintf(stderr,"Error: ORADUPD Updated %lu rows\n",(unsigned long)mysql_affected_rows(&my_connection));
				flag=0;
			}else{
				flag=-1;
//				fprintf(stderr,"OK: ORADUPD Updated %lu rows\n",
//				(unsigned long)mysql_affected_rows(&my_connection));
			}
        	}else{
			fprintf(stderr,"Error: ORADUPD UPDATE error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
		}
		mysql_close(&my_connection);
 	} else {
		fprintf(stderr,"Error: ORADUPD Connection failed\n");
    		if (mysql_errno(&my_connection))   {
    			fprintf(stderr,"Error: ORADUPD Connection error %d:  %s\n",
				mysql_errno(&my_connection), mysql_error(&my_connection));
		}
    	}
    }
    if(flag==-1){
	fprintf(stdout,"OK: ORADUPD Updated %d poster\n",antalposter);
//	fprintf(stderr,"OK: ORADUPD Updated %lu rows\n",
//	(unsigned long)mysql_affected_rows(&my_connection));
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

