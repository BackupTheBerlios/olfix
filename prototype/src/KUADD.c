/***************************************************************************
                          KUADD.c  -  description
                             -------------------
    Version		 : 0.6
    begin                : Mån   8 aug   2003
    Modified		 : Ons  14 febr  2007
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
	INPUT: kunddata databas
		format=_:_4376_:_559999-9999_:_Test AB_:_Provgatan 2_:_199 99_:_LILLEBY_:_Sverige_:_ 09-999990_:_09-999999_:_info@test.se_:_Karl Andersson _:_09-999991_:_karl.a@test.se_:_
Caroline Seljare_:_KalmarSoftware_:_1 _:_001_:_001_:_001_:_1_:_SEK_:_sv_:_J_:_J_:_J_:_J_:_J_:_J_:_2000_:_JN_:_J_:_J_:_Fritt textfält_:_

Fältavskiljare = _:_

	Function: gör  INSERT INTO KUNDREG(KUNDNR,KUNDORGNR,NAMN,ADRESS,POSTNR,POSTADR,LAND,TFNNR,FAXNR,EMAILADR,ERREFERENT,ERREFTFNNR,ERREFEMAIL,SELJARE,DISTRIKT,KUNDKATEGORI,PRISLISTA,STDLEVPLATS,LEVVILLKOR,LEVSETT,BETALVILLKOR,VALUTA,SPRAKKOD,ORDERERKENNANDE,PLOCKLISTA,FOLJESEDEL,EXPAVGIFT,FRAKTAVG,KRAVBREV,KREDITLIMIT,KREDITKOD,DROJMALSRTA,DROJMALSFAKTURA,FRITEXT) VALUES ("2345","Kund AB","Provgatan 33","199 99","KUNDBY","SVERIGE","09-999999","09-999998","info@kund.se","Karl Andersson","09-999997",
"karl.a@kund.se","Eva Seljare","Kalmar","001","001","001","001","1","SEK","sv",
"J","J","J","J","J","J","10000","JN","J","J","Fritt textfält")i databasen olfix

	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/KUADD.c,v 1.6 2007/02/14 14:56:29 janpihlgren Exp $ " ;

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql.h"
#define ANTARG 2
#define ANTFIELD 34

  MYSQL my_connection;
  MYSQL_RES *res_ptr;
  MYSQL_ROW sqlrow;

  int which_database(char *envp[]);
  char database[15]="";

int main(int argc, char *argv[], char *envp[])
{
  int res,status;
  char databas[25]="olfix";
  const char *userp = getenv("USER");	/* vem är inloggad? */
  char usr[21];				/* userid 20070214 utökat från 15 till 21 tecken */

  char temp1a[]="INSERT INTO KUNDREG (KUNDNR,KUNDORGNR,NAMN,ADRESS,POSTNR,POSTADR,LAND,TFNNR,FAXNR,EMAILADR,ERREFERENT,ERREFTFNNR,ERREFEMAIL,SELJARE,DISTRIKT,KUNDKATEGORI,PRISLISTA,STDLEVPLATS,LEVVILLKOR,LEVSETT,BETALVILLKOR,VALUTA,SPRAKKOD,ORDERERKENNANDE,PLOCKLISTA,FOLJESEDEL,EXPAVGIFT,FRAKTAVG,KRAVBREV,KREDITLIMIT,KREDITKOD,DROJMALSRTA,DROJMALSFAKTURA,FRITEXT) VALUES (";
  char temp2[]="\"";
  char temp3[]=",";
  char temp4[]=")";
  char temp5[1500]="";
  char kunddata[2000]="";

  char *pos1;
  char *pos2;
  int tmp,lenght,ant,i,j,k,n;
fprintf(stderr,"argv[1]=%s",argv[1]);
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
  } /* fprintf(stderr,"Databas=%s\n",databas);	*/

/* ================================================================================ */
/* 		Val av databas, END!						    */
/* ================================================================================ */

  if (argv[1] != NULL){
  	strncpy(kunddata,argv[1],sizeof(kunddata));	/* 2005-02-24	*/
  }
  else{
  	fprintf(stderr,"Error: KUADD: Ange kundnummer!\n");
	exit(-1);
  }


  lenght=strlen(kunddata);
/*  fprintf(stderr,"lenght=%d\n",lenght);	*/
  strncpy(temp5,temp1a,strlen(temp1a));
/*  fprintf(stderr,"kunddata=%s\n",kunddata);	*/
  pos1=strstr(kunddata,"_:_")+3;
  k=3;
  n=0;
  ant=ANTFIELD;		// antal fält = ANTFIELD = 34
  for (i=0;i<ant;i++){
  	for (j=k;j<lenght;j++){
/*		fprintf(stderr,"j=%d\n",j);	*/
  		if (kunddata[j]== 95 && kunddata[j+1]== 58 && kunddata[j+2]== 95){
			j=lenght;
		}
		n=n+1;
  	}
	k=k+(n-1)+3;

	pos2=pos1+3+(n-1);

	tmp=pos2-pos1-3;
  	strncat(temp5,temp2,strlen(temp2));
  	strncat(temp5,pos1,tmp);
  	strncat(temp5,temp2,strlen(temp2));
	if (i<(ant-1)){
  		strncat(temp5,temp3,strlen(temp3));
	}
	pos1=pos2;
/*	fprintf(stderr,"i=%d, k=%d, n=%d, tmp=%d\n",i,k,n,tmp);	*/
	n=0;
/*	fprintf(stderr,"temp5 = %s\n",temp5);	*/
  }
  strncat(temp5,temp4,strlen(temp4));

 fprintf(stderr,"Error:\nKUADD: temp5 = %s\n\n",temp5);	
/* exit(0);	*/


  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
/*  	fprintf(stderr,"KUADD:Connection success\n");	*/

  res = mysql_query(&my_connection,temp5);

  if (!res){
 	fprintf(stdout,"OK: KUADD Inserted %lu rows\n",
		(unsigned long)mysql_affected_rows(&my_connection));
        }else{
	fprintf(stderr,"Error: KUADD INSERT error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
	}
	mysql_close(&my_connection);
 }else {
	fprintf(stderr,"Error: KUADD Connection failed\n");
 	if (mysql_errno(&my_connection))   {
 		fprintf(stderr,"Error: KUADD Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
	}
  }
 	fprintf(stdout,"\n");
  return EXIT_SUCCESS;
}

int which_database(char *envp[])
{
	FILE *fil_pek;

//	char home[]="$HOME";
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

	if ((fil_pek = fopen(filename,"r")) != NULL){
		while (fgets(tmp,150,fil_pek) != NULL){
//			fprintf(stderr,"tmp=%s\n",tmp);
			if(strstr(tmp,"DATABASE=")){
				tmp_pek=(strstr(tmp,"DATABASE="))+9;
				strncpy(database,tmp_pek,strlen(tmp_pek));
				status=0;
			}
		}
//		fprintf(stderr,"database=%s_len=%d\n",database,strlen(database));
		fclose(fil_pek);
	}
	else{
	 	fprintf(stderr,"Error: Filen .olfixrc kan inte öppnas\n");
	}
	for (i=0;i < strlen(database);i++){
		tmp[i]=database[i];
	}
	tmp[i-1]=0;
//	fprintf(stderr,"tmp=%s, i=%d len tmp=%d\n",tmp,i,strlen(tmp));
	strncpy(database,tmp,strlen(tmp));
	database[strlen(tmp)]=0;

	return status;
}
