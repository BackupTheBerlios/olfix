/***************************************************************************
                          ARADD.c  -  description
                             -------------------
    Version		 : 0.2
    Modified		 : Ons 23 febr 2005
    begin                : Ons 29 okt 2003
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
	INPUT: artikeldata [databas]
		artikeldataformat=_:_2345_:_Testartikel_:_Provprodukt_:_ST_:_1_:_2,5_:_200,00_:_20_:_
		12345_:_67890_:_2_:_ _:_1234567_:_DA123_:_ _:_ _:_
		Mesurment Part_:_England_:_MP23Z_:_2,500_:_

	Fältavskiljare = _:_

	Function: gör  INSERT INTO ARTIKELREG
			(ARTIKELNR,ARBENEMNING1,ARBENEMNING2,ARENHET,OMRFAKTOR,ARFPRIS,ARLEDTID,
	ARPRODKLASS,ARPRODKTO,ARLEVNr1,ARLEVNR2,ARLEVNR3,ARNETTOVIKT,ARARTTTYP,
	ARSTRUKT,ARURBENEMNING,ARURLAND,ARURARTNR,ARTULLTAX,ARVOLYM) VALUES (
	"2345","Testartikel","Provprodukt","ST","1","2,5","200,00","20","12345","67890",
	"2"," ","1234567","DA123"," "," ",
	"Mesurment Part","England","MP023Z", "2,500")i databasen olfix

	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/ARADD.c,v 1.4 2006/05/03 03:53:01 janpihlgren Exp $ " ;

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql.h"
#define ANTFELT 20		/*	Antal datafält i ARTIKELREG	*/

  MYSQL my_connection;
  MYSQL_RES *res_ptr;
  MYSQL_ROW sqlrow;

  int which_database(char *envp[]);
  char database[15]="";

int main(int argc, char *argv[], char *envp[])
{
  int res,status;
  char databas[25]="olfix";
  const char *userp = getenv("USER");	/* vem är inloggad?	*/
  char usr[15];				/* userid		*/

  char temp1a[]="INSERT INTO ARTIKELREG (ARTIKELNR,ARBENEMNING1,ARBENEMNING2,ARENHET,AROMRFAKTOR,ARNETTOVIKT,ARFPRIS,ARLEDTID,ARPRODKLASS,ARPRODKTO,ARARTTYP,ARSTRUKT,ARTULLTAX,ARLEVNr1,ARLEVNR2,ARLEVNR3,ARURBENEMNING,ARURLAND,ARURARTNR,ARVOLYM) VALUES (";
  char temp2[]="\"";
  char temp3[]=",";
  char temp4[]=")";
  char temp5[1500]="";
  char artikeldata[200];

  char *pos1;
  char *pos2;
  int tmp,lenght,ant,i,j,k,n;

  if (argv[1] != NULL){
  	strncpy(artikeldata,argv[1],sizeof(artikeldata));
  }
  else{
  	fprintf(stderr,"Error: ARADD: Ange artikeldata!\n");
	exit(-1);
  }
/*  fprintf(stderr,"argv[1]=%s\n",argv[1]);	*/
/* ================================================================================ 	*/
/* 		Val av databas, START							*/
/* ================================================================================	*/
  status = which_database(envp);

  if (status != 0)
	exit(status);

  strncpy(usr,userp,15);				// Den inloggades userid

 if (argc<3){
    	if (strlen(database)!= 0){
		strncpy(databas,database,15);
	}else{
  		strncpy(databas,"olfixtst",15);	// olfixtst = testföretag
	}
  }else{
	if (strlen(argv[2]) != 0){
  		if (strncmp(argv[2],"99",2)==0){
			strncpy(databas,"olfixtst",15);
		}else{
  			strncpy(databas,argv[2],strlen(argv[2]));
  		}
  	}
  }
  /* Om usr (userid) börjar på 'test' eller 'prov' använd databas 'olfixtst' */
  if (strncmp(usr,"test",4)==0 || strncmp(usr,"prov",4)==0 ) {
  	strncpy(databas,"olfixtst",15);
  }
/* ================================================================================	*/
/* 		Val av databas, END!							*/
/* ================================================================================	*/


  lenght=strlen(artikeldata);
/*  fprintf(stderr,"lenght=%d\n",lenght);	*/
  strncpy(temp5,temp1a,strlen(temp1a));
//  fprintf(stderr,"artikeldata=%s\n\n\n",artikeldata);	
  pos1=strstr(artikeldata,"_:_")+3;
  k=3;
  n=0;
  ant=ANTFELT;		/* antal fält att uppdatera	*/
  for (i=0;i<ant;i++){
  	for (j=k;j<lenght;j++){
/*		fprintf(stderr,"j=%d\n",j);	*/
  		if (artikeldata[j]== 95 && artikeldata[j+1]== 58 && artikeldata[j+2]== 95){
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
/*	fprintf(stderr,"Nr %d   temp5 = %s\n\n",i,temp5);	*/
  }
  strncat(temp5,temp4,strlen(temp4));

 /*fprintf(stderr,"ARADD: temp5_TOTAL = %s\n\n",temp5);		*/	
/* exit(0);							*/


  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
/*  	fprintf(stderr,"ARADD:Connection success\n");		*/

  res = mysql_query(&my_connection,temp5);

  if (!res){
 	fprintf(stdout,"OK: ARADD Inserted %lu rows\n",
		(unsigned long)mysql_affected_rows(&my_connection));
        }else{
	fprintf(stderr,"Error: ARADD INSERT error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
	}
	mysql_close(&my_connection);
 }else {
	fprintf(stderr,"Error: ARADD Connection failed\n");
 	if (mysql_errno(&my_connection))   {
 		fprintf(stderr,"Error: ARADD Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
	}
  }
 	fprintf(stdout,"\n");
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
/*			fprintf(stderr,"temp=%s\n",temp);		*/
			status=strcmp(temp,"HOME");
/*			fprintf(stderr,"status=%d\n",status);		*/
			if (status == 0){
				home_pek=(strstr(envp[i],"HOME="));
				home_pek=home_pek+5;
				strcpy(home,home_pek);
			}
/*			fprintf(stderr,"home_pek=%d %s\n",home_pek,home_pek);	*/
/*			fprintf(stderr,"home_pek=%d %s\n",home_pek,home_pek);	*/
		}
	}
/*	fprintf(stderr,"home=%s\n",home);				*/
	strcpy(filename,home);
	strncat(filename,resource,strlen(resource));

/*	fprintf(stderr,"filename=%s\n",filename);			*/
	status=-1;

	if ((fil_pek = fopen(filename,"r")) != NULL){
		while (fgets(tmp,150,fil_pek) != NULL){
/*			fprintf(stderr,"tmp=%s\n",tmp);			*/
			if(strstr(tmp,"DATABASE=")){
				tmp_pek=(strstr(tmp,"DATABASE="))+9;
				strncpy(database,tmp_pek,strlen(tmp_pek));
				status=0;
			}
		}
/*		fprintf(stderr,"database=%s_len=%d\n",database,strlen(database));	*/
		fclose(fil_pek);
	}
	else{
	 	fprintf(stderr,"Error: Filen .olfixrc kan inte öppnas\n");
	}
	for (i=0;i < strlen(database);i++){
		tmp[i]=database[i];
	}
	tmp[i-1]=0;
/*	fprintf(stderr,"tmp=%s, i=%d len tmp=%d\n",tmp,i,strlen(tmp));			*/
	strncpy(database,tmp,strlen(tmp));
	database[strlen(tmp)]=0;

	return status;
}
