/***************************************************************************
                          INKRLST.c  -  description
                             -------------------
			     Ver: 0.3
    begin                : Sön 21  dec 2003
    modified		 : Tis 3 feb 2004
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
	INPUT: inköpsordernr

	Kommando: ./INKRLST inkordnr

	Function: Visa all information för alla orderrader på en inköpsorder i tabell INKRADREG
		samt BENEMNING1 från ARTIKELREG

	OUTPUT: INKORDNR INKORDRADNR ARTIKELNR ENHET BESTANTAL LEVERERAT RESTNOTERAT INKPRIS
		LEVVECKA TORDNR OPNR BENEMNING1
	samt errornb och error (text)

***************************************************************************/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/INKRLST.c,v 1.3 2004/02/03 07:51:48 janpihlgren Exp $ " ;

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
  void display_row();

  char database[15]="";

int main(int argc, char *argv[], char *envp[])
{
  int i;
  int res;
  int status;
  const char *userp = getenv("USER");	/* vem är inloggad?	*/
  char databas[25]="olfix";
  char usr[15];				/* userid		*/
  char inkordnr[11]="";			/* inköpsordernummer	*/

  char temp1[]="SELECT INKORDNR, INKORDRADNR,ARTIKELNR,ENHET,BESTANTAL,LEVERERAT,RESTNOTERAT,INKPRIS,LEVVECKA,TORDNR,OPNR,BENEMNING from INKRADREG WHERE INKORDNR = ";
  char temp1a[]=" ORDER BY INKORDRADNR";
  char temp5[500]="";

/*  for (i=0;i< argc;i++){
  	fprintf(stderr,"INKRLST argv%d = %s\n",i,argv[i]);
  }
*/
/*  fprintf(stderr,"argc=%d\n",argc);	*/
  if (argc<2){
  	fprintf(stderr,"Error: Inköpsordernr saknas!\n");
	exit(0);
  }
  strncpy(inkordnr,argv[1],strlen(argv[1]));

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

  strncpy(temp5,temp1,strlen(temp1));
/* SELECT INKORDNR, INKORDRADNR,INKRADREG.ARTIKELNR,ENHET,BESTANTAL,LEVERERAT,RESTNOTERAT,INKPRIS,LEVVECKA,TORDNR,OPNR,ARBENEMNING1 from INKRADREG,ARTIKELREG WHERE INKRADREG.ARTIKELNR = ARTIKELREG.ARTIKELNR AND INKRADREG.INKORDNR = 	*/
  strncat(temp5,inkordnr,strlen(inkordnr));
  /*fprintf(stderr,"temp5=%s\n",temp5);		*/
/* SELECT INKORDNR, INKORDRADNR,INKRADREG.ARTIKELNR,ENHET,BESTANTAL,LEVERERAT,RESTNOTERAT,INKPRIS,LEVVECKA,TORDNR,OPNR,ARBENEMNING1 from INKRADREG,ARTIKELREG WHERE INKRADREG.ARTIKELNR = ARTIKELREG.ARTIKELNR AND INKRADREG.INKORDNR = 99999	*/
  strncat(temp5,temp1a,strlen(temp1a));
/* SELECT INKORDNR, INKORDRADNR,INKRADREG.ARTIKELNR,ENHET,BESTANTAL,LEVERERAT,RESTNOTERAT,INKPRIS,LEVVECKA,TORDNR,OPNR,ARBENEMNING1 from INKRADREG,ARTIKELREG WHERE INKRADREG.ARTIKELNR = ARTIKELREG.ARTIKELNR AND INKRADREG.INKORDNR = 99999 ORDER BY INKORDRADNR	*/
/* fprintf(stderr,"temp5=%s\n",temp5);		*/

  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
/*  	fprintf(stdout,"INKRLST_Connection success\n");	*/
  	res = mysql_query(&my_connection,temp5);
/*  	fprintf(stderr,"INKRLST hit res=%d\n",res);	*/
  	if (res){
/*  		fprintf(stderr,"INKRLST ERROR\n");	*/
		fprintf(stderr,"Error: INKRLST SELECT errno: %d\n",mysql_errno(&my_connection));
        }else{
		res_ptr=mysql_store_result(&my_connection);
		if (res_ptr){
			i=1;
/*			fprintf(stdout,"INKRLST:Retrieved %lu rows\n",(unsigned long)mysql_num_rows(res_ptr));	*/
			fprintf(stdout,"OK: NR_%lu_:",(unsigned long)mysql_num_rows(res_ptr));
			while ((sqlrow=mysql_fetch_row(res_ptr)))  {
		 		//printf("INKRLST:Fetched data....}");
				display_row();
				i++;
			}
			fprintf(stdout,"\n");
			if (mysql_errno(&my_connection))  {
				fprintf(stderr,"Error: INKRLST Retriev error:  %s\n", mysql_error(&my_connection));
			}
		}
	mysql_free_result(res_ptr);
	}
    	mysql_close(&my_connection);
  }
  else {
    	fprintf(stderr,"Error: INKRLST Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: INKRLST Connection error %d:  %s\n",
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
/*	fprintf(stdout,"\n");	*/
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
