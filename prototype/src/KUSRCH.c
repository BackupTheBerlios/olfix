/***************************************************************************
                          KUSRCH.c  -  description
                             -------------------
			     Söka kunder
			     Ver: 0.1
    begin                : Tors 17  mars  2005
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
 ***************************************************************************/
/*
	Val av databas görs från filen $HOME/.olfixrc
	Programmet letar efter raden som börjar med DATABASE=

	INPUT: soekbegrepp soekord

	Kommando: ./KUSRCH

	Function: Lista kunder ur KUNDREG, KUNDNR NAMN POSTNR POSTADR TFNNR

	OUTPUT: KUNDNR NAMN POSTNR POSTADR TFNNR
	samt errornb och error (text)

***************************************************************************/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/KUSRCH.c,v 1.1 2005/03/17 15:21:15 janpihlgren Exp $ " ;

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
  int res,i,status;
  const char *userp = getenv("USER");	// vem är inloggad?
  char databas[25]="olfix";
  char usr[15];				// userid
  char soekbegrepp[2]="";
  char soekord[31]="";
  int begrepp=0;

  char temp1[]="SELECT KUNDNR,NAMN,POSTNR,POSTADR,TFNNR FROM KUNDREG WHERE NAMN LIKE \"%";
  char temp1b[]="%\" ORDER BY NAMN";
  char temp2[]="SELECT KUNDNR,NAMN,POSTNR,POSTADR,TFNNR FROM KUNDREG WHERE POSTNR LIKE \"%";
  char temp2b[]="%\" ORDER BY POSTNR";
  char temp3[]="SELECT KUNDNR,NAMN,POSTNR,POSTADR,TFNNR FROM KUNDREG WHERE TFNNR LIKE \"%";
  char temp3b[]="%\" ORDER BY TFNNR";
  char temp4[]="SELECT KUNDNR,NAMN,POSTNR,POSTADR,TFNNR FROM KUNDREG WHERE POSTADR LIKE \"%";
  char temp4b[]="%\" ORDER BY POSTADR";

  char temp5[200]="";

/* fprintf(stderr,"KUSRCH argc = %d\n",argc);			*/
/*  for (i=0;i< argc;i++){
  	fprintf(stderr,"KUSRCH argv%d = %s\n",i,argv[i]);
    }
*/
  strncpy(soekbegrepp,argv[1],sizeof(soekbegrepp));
  strncpy(soekord,argv[2],sizeof(soekord));
  begrepp=atoi(soekbegrepp);
/*  fprintf(stderr,"soekbegrepp=%s soekord=%s begrepp=%d\n",soekbegrepp,soekord,begrepp);	*/
  if (begrepp == 1){				/* namn */
  	strncpy(temp5,temp1,sizeof(temp1));
	strncat(temp5,soekord,sizeof(soekord));
	strncat(temp5,temp1b,sizeof(temp1b));
  }else if (begrepp == 2){			/* postnr */
  	strncpy(temp5,temp2,sizeof(temp2));
	strncat(temp5,soekord,sizeof(soekord));
	strncat(temp5,temp2b,sizeof(temp2b));
  }else if (begrepp == 3){			/* telefonnummer */
  	strncpy(temp5,temp3,sizeof(temp3));
	strncat(temp5,soekord,sizeof(soekord));
	strncat(temp5,temp3b,sizeof(temp3b));
  }else if (begrepp == 4){			/* postadress */
    	strncpy(temp5,temp4,sizeof(temp4));
	strncat(temp5,soekord,sizeof(soekord));
	strncat(temp5,temp4b,sizeof(temp4b));
  }
  fprintf(stderr,"temp5=%s\n",temp5);

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
		strncpy(databas,database,sizeof(databas));	/* 2005-02-24	*/
	}else{
  		strncpy(databas,"olfixtst",15);			/* olfixtst = testföretag	*/
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

  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
/*  	fprintf(stdout,"KUSRCH_Connection success\n");	*/
  	res = mysql_query(&my_connection,temp5);
/*  	fprintf(stderr,"KUSRCH hit res=%d\n",res);	*/
  	if (res){
/*  		fprintf(stderr,"KUSRCH ERROR\n");	*/
		fprintf(stderr,"Error: KUSRCH SELECT errno: %d\n",mysql_errno(&my_connection));
        }else{
		res_ptr=mysql_store_result(&my_connection);
		if (res_ptr){
			i=1;
/*			fprintf(stdout,"KUSRCH:Retrieved %lu rows\n",(unsigned long)mysql_num_rows(res_ptr));	*/
			fprintf(stdout,"OK: NR_%lu_:",(unsigned long)mysql_num_rows(res_ptr));
			while ((sqlrow=mysql_fetch_row(res_ptr)))  {
/*				fprintf(stderr,"KUSRCH:Fetched data....}");	*/
				display_row();
				i++;
			}
			fprintf(stdout,"\n");
			if (mysql_errno(&my_connection))  {
				fprintf(stderr,"Error: KUSRCH Retriev error:  %s\n", mysql_error(&my_connection));
			}
		}
	mysql_free_result(res_ptr);
	}
    	mysql_close(&my_connection);
  }
  else {
    	fprintf(stderr,"Error: KUSRCH Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: KUSRCH Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
	}
    }
  return EXIT_SUCCESS;
}

void display_row()
{
   unsigned int field_count;
   field_count=0;
	while (field_count < mysql_field_count(&my_connection))
	{
		fprintf(stdout,"%s_:",sqlrow[field_count]);
		field_count++;
	}
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
