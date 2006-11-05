/***************************************************************************
                          OFFRDSP.c  -  description
                             -------------------
			     Visa en offerts samtliga offertrader
			     Ver: 0.4.3
    begin                : Fre  29  april 2006
    modified		 : 
    copyright            : (C) 2006 by Jan Pihlgren
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
	INPUT: 1 st arg. OFFERTNR

	Kommando: ./OFFRDSP offertnr

	Function: Visa samtliga offertrader på en kundoffert i tabell OFFERTRADREG

	OUTPUT: OFFERTNR ORDERNR OFFERTRAD KUNDNR RADORDERTYP ARTIKELNR BENEMNING LEVERANSVECKA
	BESTELLT APRIS SUMMA MOMSKR  LEVERERAT RESTNOTERAT RADRABATT KALKYLPRIS
	LEVDATUM ENHET
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
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/OFFRDSP.c,v 1.2 2006/11/05 07:32:29 janpihlgren Exp $ " ;

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
  int i,res;
  int status;
  const char *userp = getenv("USER");	/* vem är inloggad?	*/
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
/*  fprintf(stderr,"Databas=%s\n",databas);	*/
/* ================================================================================ */
/* 		Val av databas, END!						    */
/* ================================================================================ */

  char temp1[]="SELECT * FROM OFFERTRADREG WHERE (OFFERTNR = \"";
  char temp2[]="\"";
  char temp4[]=")";
  char temp5[200]="";
  char offertnr[11]="";

/*  fprintf(stderr,"OFFRDSP argc = %d\n",argc);
  for (i=0;i< argc;i++){
  	fprintf(stderr,"OFFRDSP argv%d = %s\n",i,argv[i]);
  }
*/
  strncpy(offertnr,argv[1],sizeof(offertnr));		/* 2005-02-24	*/
  strncat(temp5,temp1,strlen(temp1));
/* SELECT * FROM OFFERTRADREG WHERE (offertnr = "	*/
  strncat(temp5,offertnr,strlen(offertnr));/* 1234 */
/* SELECT * FROM OFFERTRADREG WHERE (offertnr = "1234	*/
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
/* SELECT * FROM OFFERTRADREG WHERE (offertnr = "1234"	*/
  strncat(temp5,temp4,strlen(temp4)); /*  )     */
/* SELECT * FROM OFFERTRADREG WHERE (offertnr = "1234")	*/
  strncat(temp5,"\n",1);
/*  fprintf(stderr,"OFFRDSP temp5 = %s\n",temp5);	*/

  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
/*  	fprintf(stdout,"ORDRDSP_Connection success\n");		*/
  	res = mysql_query(&my_connection,temp5);
/*  	fprintf(stderr,"OFFRDSP hit res=%d\n",res);		*/
  	if (res){
/*  		fprintf(stderr,"OFFRDSP ERROR\n");		*/
		fprintf(stderr,"Error: OFFRDSP SELECT errno: %d\n",mysql_errno(&my_connection));
        }
	else{
		res_ptr=mysql_store_result(&my_connection);
		num_rows = mysql_affected_rows(&my_connection);
/*		fprintf(stderr,"num_rows=%d\n",num_rows);		*/
		if(num_rows != 0){
/*			fprintf(stdout,"OK: ");				*/
			fprintf(stdout,"OK: %d_:_ ",num_rows);

			for (i=0;i<num_rows;i++){
				sqlrow=mysql_fetch_row(res_ptr);
/*				fprintf(stdout,"OK: ");				*/
				fprintf(stdout,"01_:_ %s_:_",sqlrow[0]);	
				fprintf(stdout,"02_:_ %s_:_",sqlrow[1]);
				fprintf(stdout,"03_:_ %s_:_",sqlrow[2]);
				fprintf(stdout,"04_:_ %s_:_",sqlrow[3]);
				fprintf(stdout,"05_:_ %s_:_",sqlrow[4]);
				fprintf(stdout,"06_:_ %s_:_",sqlrow[5]);
				fprintf(stdout,"07_:_ %s_:_",sqlrow[6]);
				fprintf(stdout,"08_:_ %s_:_",sqlrow[7]);
				fprintf(stdout,"09_:_ %s_:_",sqlrow[8]);
				fprintf(stdout,"10_:_ %s_:_",sqlrow[9]);
				fprintf(stdout,"11_:_ %s_:_",sqlrow[10]);
				fprintf(stdout,"12_:_ %s_:_",sqlrow[11]);
				fprintf(stdout,"13_:_ %s_:_",sqlrow[12]);
				fprintf(stdout,"14_:_ %s_:_",sqlrow[13]);
				fprintf(stdout,"15_:_ %s_:_",sqlrow[14]);
				fprintf(stdout,"16_:_ %s_:_",sqlrow[15]);
				fprintf(stdout,"17_:_ %s_:_",sqlrow[16]);
				fprintf(stdout,"18_:_ %s_:_",sqlrow[17]); /* Fre   4  nov  2005 */
				fprintf(stdout,"_:_NEXT_:_");
				fprintf(stdout,"\n");
			}
			fprintf(stdout,"END");
			fprintf(stdout,"\n");
		}
		else{
			fprintf(stderr,"Error: OFFRDSP Data saknas:  %s\n", mysql_error(&my_connection));
		}
		if (mysql_errno(&my_connection))  {
			fprintf(stderr,"Error: OFFRDSP Retriev error:  %s\n", mysql_error(&my_connection));
		}
	}
	mysql_free_result(res_ptr);
    	mysql_close(&my_connection);
  }
  else {
    	fprintf(stderr,"Error: OFFRDSP Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: OFFRDSP Connection error %d:  %s\n",
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
