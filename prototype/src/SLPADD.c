/***************************************************************************
                          SLPADD.c  -  description
                             -------------------
    Vesrsion		 : 0.3
    begin                : Ons  10 aug  2003
    Modifierad		 : Tors 24 febr 2005
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
 *********************************************** ****************************/

/*
	INPUT: KUNDNR, STDLEVPLATS, ADRESS, POSTNR, POSTADR, LAND  och databas

	Kommando: ./SLPADD kundnr stdlevplats adress postnr postadr land databas

	Function: Add record i tabell STDLEVPLATS

	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/SLPADD.c,v 1.4 2005/02/24 10:34:21 janpihlgren Exp $ " ;

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql.h"
#define ANTARG 7

  MYSQL my_connection;
  MYSQL_RES *res_ptr;
  MYSQL_ROW sqlrow;

  int which_database(char *envp[]);
  char database[15]="";

int main(int argc, char *argv[], char *envp[])
{
/* int i;	*/
  int res;
  int status;
  char databas[25]="olfix";
  const char *userp = getenv("USER");	// vem �r inloggad?
  char usr[15];				// userid

  char temp1[]="INSERT INTO STDLEVPLATS(KUNDNR,STDLEVPLATS,ADRESS,POSTNR,POSTADR,LAND) VALUES (\"";
  char temp2[]="\"";
  char temp3[]=",";
  char temp4[]=")";
  char temp5[200]="";
  char kundnr[11]="";
  char stdlevplats[4]="";
  char adress[31]="";
  char postnr[7]="";
  char postadr[31]="";
  char land[31]="";

/*  fprintf(stderr,"argc=%d, argv[argc-1]=%s\n",argc,argv[argc-1]);	*/
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
/* fprintf(stderr,"Databas=%s\n",databas);	*/
/* ================================================================================ */
/* 		Val av databas, END!						    */
/* ================================================================================ */

  strncpy(kundnr,argv[1],sizeof(kundnr));		/* 2005-02-24	*/
  strncpy(stdlevplats,argv[2],sizeof(stdlevplats));	/* 2005-02-24	*/
  strncpy(adress,argv[3],sizeof(adress));		/* 2005-02-24	*/
  strncpy(postnr,argv[4],sizeof(postnr));		/* 2005-02-24	*/
  strncpy(postadr,argv[5],sizeof(postadr));		/* 2005-02-24	*/
  strncpy(land,argv[6],sizeof(land));			/* 2005-02-24	*/


  strncpy(temp5,temp1,strlen(temp1));
/* INSERT INTO STDLEVPLATS(KUNDNR,STDLEVPLATS,ADRESS,POSTNR,POSTADR,LAND) VALUES ("  */
  strncat(temp5,kundnr,strlen(kundnr));/* 4376 */
/* INSERT INTO STDLEVPLATS(KUNDNR,STDLEVPLATS,ADRESS,POSTNR,POSTADR,LAND) VALUES ("4376  */
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
  strncat(temp5,temp3,strlen(temp3)); /*  ,     */
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
  strncat(temp5,stdlevplats,strlen(stdlevplats));/* 001  */
/* INSERT INTO STDLEVPLATS(KUNDNR,STDLEVPLATS,ADRESS,POSTNR,POSTADR,LAND) VALUES ("4376","001 */
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
  strncat(temp5,temp3,strlen(temp3)); /*  ,     */
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
/* INSERT INTO STDLEVPLATS(KUNDNR,STDLEVPLATS,ADRESS,POSTNR,POSTADR,LAND) VALUES ("4376","001","  */
  strncat(temp5,adress,strlen(adress));
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
  strncat(temp5,temp3,strlen(temp3)); /*  ,     */
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
/* INSERT INTO STDLEVPLATS(KUNDNR,STDLEVPLATS,ADRESS,POSTNR,POSTADR,LAND) VALUES ("4376","001","Provstigen 1","  */
  strncat(temp5,postnr,strlen(postnr));
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
  strncat(temp5,temp3,strlen(temp3)); /*  ,     */
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
/* INSERT INTO STDLEVPLATS(KUNDNR,STDLEVPLATS,ADRESS,POSTNR,POSTADR,LAND) VALUES ("4376","001","Provstigen 1","199 99","  */
  strncat(temp5,postadr,strlen(postadr));
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
  strncat(temp5,temp3,strlen(temp3)); /*  ,     */
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
/* INSERT INTO STDLEVPLATS(KUNDNR,STDLEVPLATS,ADRESS,POSTNR,POSTADR,LAND) VALUES ("4376","001","Provstigen 1","199 99","LILLEBY","  */
  strncat(temp5,land,strlen(land));
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
  strncat(temp5,temp4,strlen(temp4)); /*  )     */
/* INSERT INTO STDLEVPLATS(KUNDNR,STDLEVPLATS,ADRESS,POSTNR,POSTADR,LAND) VALUES ("4376","001","Provstigen 1","199 99","LILLEBY","Svberige")  */

/* fprintf(stderr,"temp5=%s\n",temp5);	*/

  mysql_init(&my_connection);

  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
/* fprintf(stdout,"SLPADD:Connection success\n");	*/

    res = mysql_query(&my_connection,temp5);

  	if (!res){
		fprintf(stdout,"OK: SLPADD Inserted %lu rows\n",
			(unsigned long)mysql_affected_rows(&my_connection));
        }else{
/*	fprintf(stderr,"stderr-SLPADD:INSERT error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
*/
	fprintf(stderr,"Error: SLPADD INSERT error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
	}
	mysql_close(&my_connection);

 } else {
	fprintf(stderr,"Error: SLPADD Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: SLPADD Connection error %d:  %s\n",
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
