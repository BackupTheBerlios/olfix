/***************************************************************************
                          INKHDSP.c  -  description
                             -------------------
			     Ver: 0.2
    begin                : Sön 21  dec 2003
    modified	: Tis 3 febr 2004
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

	Kommando: ./INKHDSP inkordnr

	Function: Visa all information för alla orderrader på en inköpsorder i tabell INKRADREG

	OUTPUT: INKORDNR BESTTYP ORDERDATUM LEVNR LEVNAMN LEVADRESS LEVPOSTNR LEVPOSTADR LEVLAND LEVVALUTA LEVBETVILLKOR GODSMERKE BESTTEXT VARREF LEVDATUM KUNDNR FTGNAMN FTGADR FTGPOSTNR FTGPOSTADR SPRAKKOD BEKREFTKOD ORDERSTATUS UTSKRIFTSKOD ORDERSUMMA
	samt errornb och error (text)

***************************************************************************/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/C/Attic/INKHDSP.c,v 1.1 2004/05/03 04:42:57 janpihlgren Exp $ " ;

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
/*  int i;	*/
  int res;
  int num_rows;
  int status;
  const char *userp = getenv("USER");	/* vem är inloggad?	*/
  char databas[25]="olfix";
  char usr[15];				/* userid		*/
  char inkordnr[11]="";			/* inköpsordernummer	*/

  char temp1[]="SELECT * FROM INKREG WHERE INKORDNR =  ";
//  char temp1a[]=" ORDER BY INKORDRADNR";
  char temp5[200]="";

/*  for (i=0;i< argc;i++){
  	fprintf(stderr,"INKHDSP argv%d = %s\n",i,argv[i]);
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
/* SELECT * FROM INKREG WHERE INKORDNR = 	*/
  strncat(temp5,inkordnr,strlen(inkordnr));
/* SELECT * FROM INKREG WHERE INKORDNR = 99999	*/
/* fprintf(stderr,"temp5=%s\n",temp5);		*/

  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
/*  	fprintf(stdout,"INKHDSP_Connection success\n");	*/
  	res = mysql_query(&my_connection,temp5);
/*  	fprintf(stderr,"INKHDSP hit res=%d\n",res);	*/
  	if (res){
/*  		fprintf(stderr,"INKHDSP ERROR\n");	*/
		fprintf(stderr,"Error: INKHDSP SELECT errno: %d\n",mysql_errno(&my_connection));
        }
	else{
		res_ptr=mysql_store_result(&my_connection);
		num_rows = mysql_affected_rows(&my_connection);
/*		fprintf(stderr,"num_rows=%d\n",num_rows);	*/
/*		if (res_ptr){	*/
		if(num_rows != 0){
			sqlrow=mysql_fetch_row(res_ptr);
			fprintf(stdout,"OK: ");
			fprintf(stdout,"01:%s  ",sqlrow[0]);	/* beställningsordernr */
			fprintf(stdout,"02:%s  ",sqlrow[1]);	/* bestellningstyp */
			fprintf(stdout,"03:%s  ",sqlrow[2]);	/* beställningsdatum */
			fprintf(stdout,"04:%s  ",sqlrow[3]);	/* leverantörsnr */
			fprintf(stdout,"05:%s  ",sqlrow[4]);	/* levnamn */
			fprintf(stdout,"06:%s  ",sqlrow[5]);	/* leverantörsadress */
			fprintf(stdout,"07:%s  ",sqlrow[6]);	/* leverantörspostnr */
			fprintf(stdout,"08:%s  ",sqlrow[7]);	/* leverantörspostadr */
			fprintf(stdout,"09:%s  ",sqlrow[8]);	/* leverantörsland */
			fprintf(stdout,"10:%s  ",sqlrow[9]);	/* valuta */
			fprintf(stdout,"11:%s  ",sqlrow[10]);	/* betalningsvillkor */
			fprintf(stdout,"12:%s  ",sqlrow[11]);	/* leveransvillkor */
			fprintf(stdout,"13:%s  ",sqlrow[12]);	/* leveranssätt */
			fprintf(stdout,"14:%s  ",sqlrow[13]);	/* godsmärke */
			fprintf(stdout,"15:%s  ",sqlrow[14]);	/* kommentar */
			fprintf(stdout,"16:%s  ",sqlrow[15]);	/* beställningseftertext */
			fprintf(stdout,"17:%s  ",sqlrow[16]);	/* varref */
			fprintf(stdout,"18:%s  ",sqlrow[17]);	/* varreftfn */
			fprintf(stdout,"19:%s  ",sqlrow[18]);	/* varreffax */
			fprintf(stdout,"20:%s  ",sqlrow[19]);	/* erref */
			fprintf(stdout,"21:%s  ",sqlrow[20]);	/* leveransdatum */
			fprintf(stdout,"22:%s  ",sqlrow[21]);	/* kundnr */
			fprintf(stdout,"23:%s  ",sqlrow[22]);	/* ftgnamn */
			fprintf(stdout,"24:%s  ",sqlrow[23]);	/* ftglevadr */
			fprintf(stdout,"25:%s  ",sqlrow[24]);	/* ftglevpostnr */
			fprintf(stdout,"26:%s  ",sqlrow[25]);	/* ftglevpostadr */
			fprintf(stdout,"27:%s  ",sqlrow[26]);	/* språkkod */
			fprintf(stdout,"28:%s  ",sqlrow[27]);	/* bekräftelsekod */
			fprintf(stdout,"29:%s  ",sqlrow[28]);	/* orderstatus */
			fprintf(stdout,"30:%s  ",sqlrow[29]);	/* utskriftskod */
			fprintf(stdout,"31:%s  ",sqlrow[30]);	/* ordersumma */
			fprintf(stdout,"END:");
			fprintf(stdout,"\n");
		}
		else{
			fprintf(stderr,"Error: INKHDSP Data saknas:  %s\n", mysql_error(&my_connection));
		}
			if (mysql_errno(&my_connection))  {
				fprintf(stderr,"Error: INKHDSP Retriev error:  %s\n", mysql_error(&my_connection));
			}
		}
	mysql_free_result(res_ptr);
    	mysql_close(&my_connection);
  }
  else{
    	fprintf(stderr,"Error: INKHDSP Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: INKHDSP Connection error %d:  %s\n",
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
