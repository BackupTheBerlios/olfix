/***************************************************************************
                          AR2ADD.c  -  description
                             -------------------
    Version		 : 0.1
    Modified		 :
    begin                : Fre 14 nov 2003
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
	INPUT: lagerdata [databas]
		lagerdataformat=_:_1_:_100234_:_Lagerhylla_:_10_:_001_:_A_:_SEK_:_20.50_:_
		0.00_:_0.00_:_0.00_:_25.75_:_0.00_:_150_:_

	Fältavskiljare = _:_

	Function: gör  INSERT INTO LAGERSTELLEREG
			(ARLAGST,ARTIKELNR,ARLAGHYLLA,ARLAGSALDO,ARINVGRP,ARABC,ARVALUTA,
	ARIPRIS,ARIKVANT0,ARIKVANT1,ARIKVANT2,ARKALKPRIS,ARBESTKVANT,ARBESTPUNKT) VALUES (
	"1","100234","AHX105","10","001","A","SEK","20.50","0.00","0.00","0.00","25.75","0.00","150")
	i databasen olfix

	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/C/Attic/AR2ADD.c,v 1.1 2004/05/03 04:42:57 janpihlgren Exp $ " ;

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql.h"
#define ANTFELT 14		/*	Antal datafält i LAGERSTELLEREG	*/

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

  char temp1a[]="INSERT INTO LAGERSTELLEREG (ARLAGST,ARTIKELNR,ARLAGHYLLA,ARLAGSALDO,ARINVGRP,ARABC,ARVALUTA,ARIPRIS,ARIKVANT0,ARIKVANT1,ARIKVANT2,ARKALKPRIS,ARBESTKVANT,ARBESTPUNKT) VALUES (";

  char temp2[]="\"";
  char temp3[]=",";
  char temp4[]=")";
  char temp5[1500]="";
  char lagerdata[2000];

  char *pos1;
  char *pos2;
  int tmp,lenght,ant,i,j,k,n;

  if (argv[1] != NULL){
  	strncpy(lagerdata,argv[1],strlen(argv[1]));
  }
  else{
  	fprintf(stderr,"Error: AR2ADD: Ange lagerdata!\n");
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


  lenght=strlen(lagerdata);
/*  fprintf(stderr,"lenght=%d\n",lenght);	*/
  strncpy(temp5,temp1a,strlen(temp1a));
/*  fprintf(stderr,"lagerdata=%s\n",lagerdata);	*/
  pos1=strstr(lagerdata,"_:_")+3;
  k=3;
  n=0;
  ant=ANTFELT;		/* antal fält att uppdatera	*/
  for (i=0;i<ant;i++){
  	for (j=k;j<lenght;j++){
/*		fprintf(stderr,"j=%d\n",j);	*/
  		if (lagerdata[j]== 95 && lagerdata[j+1]== 58 && lagerdata[j+2]== 95){
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
/*	fprintf(stderr,"temp5 = %s\n",temp5);			*/
  }
  strncat(temp5,temp4,strlen(temp4));
/*
 fprintf(stderr,"AR2ADD: temp5 = %s\n",temp5);
 exit(0);
*/

  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
/*  	fprintf(stderr,"AR2ADD:Connection success\n");		*/

  res = mysql_query(&my_connection,temp5);

  if (!res){
 	fprintf(stdout,"OK: AR2ADD Inserted %lu rows\n",
		(unsigned long)mysql_affected_rows(&my_connection));
        }else{
	fprintf(stderr,"Error: AR2ADD INSERT error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
	}
	mysql_close(&my_connection);
 }else {
	fprintf(stderr,"Error: AR2ADD Connection failed\n");
 	if (mysql_errno(&my_connection))   {
 		fprintf(stderr,"Error: AR2ADD Connection error %d:  %s\n",
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
