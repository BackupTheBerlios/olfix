/***************************************************************************
                          ORDCHK.c  -  description
                             -------------------
    Version		 : 0.2
    begin                : Lör  2 april 2005
    Modified		 : Fre 30 sept  2005
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
	INPUT: val ordernr [databas]

	Kommando: ./ ORDCHK val ordernr [databas]

	Function: Kontrollera om angivet
	1. ordernr finns.
	2. orderstatus

	OUTPUT: data, errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/ORDCHK.c,v 1.3 2005/09/30 05:22:57 janpihlgren Exp $ " ;

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

  void display_row();
  int which_database(char *envp[]);

  char database[15]="";

int main(int argc, char *argv[], char *envp[])
{
if(argv[1]==NULL){
	fprintf(stderr,"Ange önskat val!\n");
	exit(0);
	}
if (argv[2]==NULL){
	fprintf(stderr,"Ange ordernr!\n");
	exit(0);
	}
  int res,status;
  int i;
  const char *userp = getenv("USER");	/* vem är inloggad?	*/
  char databas[25]="olfix";
  char usr[15];				/* userid		*/

  char temp1a[]="SELECT ORDERNR FROM ORDERREG WHERE ORDERNR = \"";
  char temp1b[]="SELECT ORDERSTATUS FROM ORDERREG WHERE ORDERNR = \"";
  char temp2[]="\"";
  char temp5[200]="";
  char ordernr[11]="";
  char val[3]="";
  int valt=0;
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

  strncpy(val,argv[1],sizeof(val));
  valt=atoi(val);
  if (argv[2] != NULL){
  	strncpy(ordernr,argv[2],sizeof(ordernr));
  }else{
  	fprintf(stderr,"Error: ORDCHK: Ange ordernummer!\n");
	exit(-1);
  }
/*  fprintf(stderr,"val=%s\n",val);		*/

  if (valt==1){
  	strncpy(temp5,temp1a,strlen(temp1a));
	/* SELECT ORDERNR FROM ORDERREG WHERE ORDERNR = "  */
  	strncat(temp5,ordernr,strlen(ordernr));/* 4376 */
	/* SELECT ORDERNR FROM ORDERREG WHERE ORDERNR = "4376  */
  	strncat(temp5,temp2,strlen(temp2)); /*  "     */
	/* SELECT ORDERNR FROM ORDERREG WHERE ORDERNR = "4376" */
	/*  fprintf(stderr,"ORDCHKmain: temp5 = %s\n",temp5);	*/
  }
  if (valt==2){
  	strncpy(temp5,temp1b,strlen(temp1b));
	/* SELECT ORDERNR FROM ORDERREG WHERE ORDERNR = "  */
  	strncat(temp5,ordernr,strlen(ordernr));/* 4376 */
	/* SELECT ORDERNR FROM ORDERREG WHERE ORDERNR = "4376  */
  	strncat(temp5,temp2,strlen(temp2)); /*  "     */
	/* SELECT ORDERNR FROM ORDERREG WHERE ORDERNR = "4376" */
	/*  fprintf(stderr,"ORDCHKmain: temp5 = %s\n",temp5);	*/
  }
  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
/*  fprintf(stdout,"ORDCHKmain:Connection success\n");	*/
  	res = mysql_query(&my_connection,temp5);
  	if (res){
		fprintf(stderr,"Error: ORDCHK SELECT error: %s\n",mysql_error(&my_connection));
  	}
  	else{
		res_ptr=mysql_store_result(&my_connection);
		if (res_ptr){
			i=1;
			fprintf(stdout,"OK: NR_:_%lu_:_",(unsigned long)mysql_num_rows(res_ptr));
			while ((sqlrow=mysql_fetch_row(res_ptr)))  {
				display_row();
				fprintf(stdout,"\n");
				i++;
			}
			if (mysql_errno(&my_connection)){
				fprintf(stderr,"Error: ORDCHK Retriev error:  %s\n", mysql_error(&my_connection));
			}
		}
		mysql_free_result(res_ptr);
	}
  	mysql_close(&my_connection);
 }
  else {
  	fprintf(stderr,"Error: ORDCHK Connection failed\n");
	if (mysql_errno(&my_connection)){
		fprintf(stderr,"Error: ORDCHK Connection error %d:  %s\n",
		mysql_errno(&my_connection), mysql_error(&my_connection));
	}
  }
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

void display_row()
{
   unsigned int field_count;
   field_count=0;
	while (field_count < mysql_field_count(&my_connection))
	{
		fprintf(stdout,"%s_:_",sqlrow[field_count]);
		field_count++;
	}
/*	fprintf(stdout,"\n");		*/
}
