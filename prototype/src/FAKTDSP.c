/***************************************************************************
                          FAKTDSP.c  -  description
                             -------------------
    Version		 : 0.2
    begin                : Mån  5  dec	2005
    modified		 : Ons 14  febr 2007
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
	INPUT: fakturanummer [databas]

	Kommando: ./FAKTDSP fakturanummer [olfix]

	Function: Hämta data för angiven faktura från KRESK (kundreskontraregistret)

	OUTPUT: data, errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/FAKTDSP.c,v 1.1 2007/02/14 05:14:27 janpihlgren Exp $ " ;

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql.h"
#define ANTARG 2

  MYSQL my_connection;
  MYSQL_RES *res_ptr;
  MYSQL_ROW sqlrow;
int which_database(char *envp[]);

  char database[15]="";

int main(int argc, char *argv[], char *envp[])
{
  int res;
  int status;
  const char *userp = getenv("USER");	/* vem är inloggad?	*/
  char databas[25]="olfix";
  char usr[21];				/* userid 20070214 utökat från 15 till 21 tecken */

  char temp1[]="SELECT * FROM KURESK WHERE FAKTURANR = \"";
  char temp2[]="\"";
  char temp5[200]="";
  char fakturanr[21];
/*
  int i;
  fprintf(stderr,"argc = %d \n",argc );

  for (i=0;i<argc;i++){
  	fprintf(stderr,"argv[%d]=%s\n",i,argv[i]);
	}
*/
  /* ================================================================================ */
/* 		Val av databas, START						    */
/* ================================================================================ */

  status = which_database(envp);

  if (status != 0)
	exit(status);

  strncpy(usr,userp,sizeof(usr));			/* Den inloggades userid 20070214 */
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

  strncpy(fakturanr,argv[1],sizeof(fakturanr));
/*  fprintf(stderr,"strlen argv1=%d\n",strlen(argv[1]));	*/
/*  fprintf(stderr,"FAKTDSPmain: fakturanr = %s strlen argv1=%d\n",fakturanr,strlen(argv[1]));	*/

  strncat(temp5,temp1,strlen(temp1));
/* SELECT * FROM KRESK WHERE FAKTURANR = "  */
  strncat(temp5,fakturanr,strlen(fakturanr));/* 496127 */
/* SELECT * FROM KRESK WHERE FAKTURANR = "496127  */
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
/* SELECT * FROM KRESK WHERE FAKTURANR = "496127" */
/*  fprintf(stderr,"FAKTDSPmain: temp5 = %s\n",temp5);	*/

  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
/*  fprintf(stdout,"FAKTDSPmain:Connection success\n");	*/
  	res = mysql_query(&my_connection,temp5);
  	if (res){
		fprintf(stderr,"Error: FAKTDSP SELECT error: %s\n",mysql_error(&my_connection));
  	}
  	else{
		res_ptr=mysql_store_result(&my_connection);
		if (res_ptr){
/*			fprintf(stderr,"Retrieved %lu rows\n",(unsigned long)mysql_num_rows(res_ptr));	*/
			if(mysql_num_rows(res_ptr)>0){
				sqlrow=mysql_fetch_row(res_ptr);
				fprintf(stdout,"OK:_");
				fprintf(stdout,"_:ORDERNR:%s",sqlrow[0]);
				fprintf(stdout,"_:FAKTURANR:%s",sqlrow[1]);
				fprintf(stdout,"_:KUNDNR:%s",sqlrow[2]);
				fprintf(stdout,"_:FAKTURADATUM:%s",sqlrow[3]);
				fprintf(stdout,"_:EXPIREDATUM:%s",sqlrow[4]);
				fprintf(stdout,"_:NETTOBELOPP:%s",sqlrow[5]);
				fprintf(stdout,"_:MOMSBELOPP:%s",sqlrow[6]);
				fprintf(stdout,"_:FAKTURABELOPP:%s",sqlrow[7]);
				fprintf(stdout,"_:BETALD:%s",sqlrow[8]);
				fprintf(stdout,"_:BETALDATUM:%s",sqlrow[9]);
				fprintf(stdout,"_:USERID:%s",sqlrow[10]);
				fprintf(stdout,"_:VALUTA:%s",sqlrow[11]);
				fprintf(stdout,"_:VALUTAKURS:%s",sqlrow[12]);
				fprintf(stdout,"_:VALUTABELOPP:%s",sqlrow[13]);
				fprintf(stdout,"_:BAR:%s",sqlrow[14]);
				fprintf(stdout,"_:VERNR:%s",sqlrow[15]);
				fprintf(stdout,"_:MOMSKTONR:%s",sqlrow[16]);
				fprintf(stdout,"_:KTONR:%s",sqlrow[17]);
				fprintf(stdout,"_:DEBETBELOPP:%s",sqlrow[18]);
				fprintf(stdout,"_:END_:\n");
			}
			else{
				fprintf(stderr,"Error: Fakturanr %s saknas! Status = -1.\n",fakturanr);
			}
			if (mysql_errno(&my_connection)){
				fprintf(stderr,"Error: FAKTDSP Retriev error:  %s\n", mysql_error(&my_connection));
			}
		}
		mysql_free_result(res_ptr);
	}
  	mysql_close(&my_connection);
  	}
  else {
  	fprintf(stderr,"Error: FAKTDSP Connection failed\n");
	if (mysql_errno(&my_connection)){
		fprintf(stderr,"Error: FAKTDSP Connection error %d:  %s\n",
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
