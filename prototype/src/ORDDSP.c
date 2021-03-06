/***************************************************************************
                          ORDDSP.c  -  description
                             -------------------
			     Visa en kundorders huvudpost
			     Ver: 0.1
    begin                : Fre  25  mars 2005
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
	INPUT: 1 st arg. ORDERNR

	Kommando: ./ORDDSP ordernr

	Function: Visa huvudpostens information p� en kundorder i tabell ORDERREG

	OUTPUT: ORDERNR KUNDNR ORDERTYP ORDERSTATUS ORDERDATUM LEVDATUM
	KUNDNAMN  KUNDADRESS KUNDPOSTNR KUNDPOSTADR KUNDLAND
	ERREF LEVADRESS LEVPOSTNR LEVPOSTADR LEVLAND
	VARREF SELJARE GODSMERKE BETVILLKTYP BETVILLKOR LEVVILLKOR LEVSETT PLOCKLISTA
	F�LJESEDEL FRAKTAVG SKATTEKOD MOMS VALUTA EXPORTKOD SPRAKKOD ORDERSUMMA
	FRAKTSUMMA FRAKTMOMSKR ORDERMOMS ORDERTOTAL
	samt errornb och error (text)

	ex:
	OK: 1:31  2:4377  3:N  4:A  5:2005-03-14  6:2005-03-14
	7:Nya Kund AB  8:Provgatan 23  9:199 97  10:LILLEBY  11:Sverige
	12:Per Karlsson  13:Testgatan 21  14:199 91  15:LILLEBY  16:Sverige
	17:(null)  18:Josef Seljare  19:  20:F  21:1  22:001  23:002  24:J
	25:J  26:J  27:001  28:25.00  29:SEK  30:001  31:sv
	32:2500.00  33:90.00  34:22.50  35:647.50  36:3260.00 END

***************************************************************************/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/ORDDSP.c,v 1.1 2005/03/25 14:43:15 janpihlgren Exp $ " ;

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
  const char *userp = getenv("USER");	/* vem �r inloggad?	*/
  char databas[25]="olfix";
  char usr[15];				/* userid		*/
  int num_rows;

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
  		strncpy(databas,"olfixtst",15);	/* olfixtst = testf�retag	*/
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
/* Om usr (userid) b�rjar p� 'test' eller 'prov' anv�nd databas 'olfixtst' */
  if (strncmp(usr,"test",4)==0 || strncmp(usr,"prov",4)==0 ) {
  	strncpy(databas,"olfixtst",15);
  }
/*  fprintf(stderr,"Databas=%s\n",databas);	*/
/* ================================================================================ */
/* 		Val av databas, END!						    */
/* ================================================================================ */

  char temp1[]="SELECT * FROM ORDERREG WHERE (ORDERNR = \"";
  char temp2[]="\"";
  char temp4[]=")";
  char temp5[200]="";
  char ordernr[11]="";

/*  int i;
  fprintf(stderr,"ORDDSP argc = %d\n",argc);
  for (i=0;i< argc;i++){
  	fprintf(stderr,"ORDDSP argv%d = %s\n",i,argv[i]);
  }
*/
  strncpy(ordernr,argv[1],sizeof(ordernr));		/* 2005-02-24	*/
  strncat(temp5,temp1,strlen(temp1));
/* SELECT * FROM LEVREG WHERE (ordernr = "	*/
  strncat(temp5,ordernr,strlen(ordernr));/* 1234 */
/* SELECT * FROM LEVREG WHERE (ordernr = "1234	*/
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
/* SELECT * FROM LEVREG WHERE (ordernr = "1234"	*/
  strncat(temp5,temp4,strlen(temp4)); /*  )     */
/* SELECT * FROM LEVREG WHERE (ordernr = "1234")	*/
  strncat(temp5,"\n",1);
/*  fprintf(stderr,"ORDDSP temp5 = %s\n",temp5);	*/

  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
/*  	fprintf(stdout,"ORDDSP_Connection success\n");		*/
  	res = mysql_query(&my_connection,temp5);
/*  	fprintf(stderr,"ORDDSP hit res=%d\n",res);		*/
  	if (res){
/*  		fprintf(stderr,"ORDDSP ERROR\n");		*/
		fprintf(stderr,"Error: ORDDSP SELECT errno: %d\n",mysql_errno(&my_connection));
        }
	else{
		res_ptr=mysql_store_result(&my_connection);
		num_rows = mysql_affected_rows(&my_connection);
/*		fprintf(stderr,"num_rows=%d\n",num_rows);	*/
		if(num_rows != 0){
			sqlrow=mysql_fetch_row(res_ptr);
			fprintf(stdout,"OK: ");
			fprintf(stdout,"01:%s  ",sqlrow[0]);
			fprintf(stdout,"02:%s  ",sqlrow[1]);
			fprintf(stdout,"03:%s  ",sqlrow[2]);
			fprintf(stdout,"04:%s  ",sqlrow[3]);
			fprintf(stdout,"05:%s  ",sqlrow[4]);
			fprintf(stdout,"06:%s  ",sqlrow[5]);
			fprintf(stdout,"07:%s  ",sqlrow[6]);
			fprintf(stdout,"08:%s  ",sqlrow[7]);
			fprintf(stdout,"09:%s  ",sqlrow[8]);
			fprintf(stdout,"10:%s  ",sqlrow[9]);
			fprintf(stdout,"11:%s  ",sqlrow[10]);
			fprintf(stdout,"12:%s  ",sqlrow[11]);
			fprintf(stdout,"13:%s  ",sqlrow[12]);
			fprintf(stdout,"14:%s  ",sqlrow[13]);
			fprintf(stdout,"15:%s  ",sqlrow[14]);
			fprintf(stdout,"16:%s  ",sqlrow[15]);
			fprintf(stdout,"17:%s  ",sqlrow[16]);
			fprintf(stdout,"18:%s  ",sqlrow[17]);
			fprintf(stdout,"19:%s  ",sqlrow[18]);
			fprintf(stdout,"20:%s  ",sqlrow[19]);
			fprintf(stdout,"21:%s  ",sqlrow[20]);
			fprintf(stdout,"22:%s  ",sqlrow[21]);
			fprintf(stdout,"23:%s  ",sqlrow[22]);
			fprintf(stdout,"24:%s  ",sqlrow[23]);
			fprintf(stdout,"25:%s  ",sqlrow[24]);
			fprintf(stdout,"26:%s  ",sqlrow[25]);
			fprintf(stdout,"27:%s  ",sqlrow[26]);
			fprintf(stdout,"28:%s  ",sqlrow[27]);
			fprintf(stdout,"29:%s  ",sqlrow[28]);
			fprintf(stdout,"30:%s  ",sqlrow[29]);
			fprintf(stdout,"31:%s  ",sqlrow[30]);
			fprintf(stdout,"32:%s  ",sqlrow[31]);
			fprintf(stdout,"33:%s  ",sqlrow[32]);
			fprintf(stdout,"34:%s  ",sqlrow[33]);
			fprintf(stdout,"35:%s  ",sqlrow[34]);
			fprintf(stdout,"36:%s  ",sqlrow[35]);
			fprintf(stdout,"END");
			fprintf(stdout,"\n");
		}
		else{
			fprintf(stderr,"Error: ORDDSP Data saknas:  %s\n", mysql_error(&my_connection));
		}
		if (mysql_errno(&my_connection))  {
			fprintf(stderr,"Error: ORDDSP Retriev error:  %s\n", mysql_error(&my_connection));
		}
	}
	mysql_free_result(res_ptr);
    	mysql_close(&my_connection);
  }
  else {
    	fprintf(stderr,"Error: ORDDSP Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: ORDDSP Connection error %d:  %s\n",
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
	 	fprintf(stderr,"Error: Filen .olfixrc kan inte �ppnas\n");
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
