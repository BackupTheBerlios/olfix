/***************************************************************************
                          SLPADD.c  -  description
                             -------------------
    Vesrsion		 : 0.2
    Modifierad		 : Mån 20 okt 2003
    begin                : Ons 10 aug 2003
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
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/SLPADD.c,v 1.2 2003/10/20 06:15:00 janpihlgren Exp $ " ;

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mysql.h"

  MYSQL my_connection;
  MYSQL_RES *res_ptr;
  MYSQL_ROW sqlrow;

  int which_database(char *envp[]);
  char database[15]="";

int main(int argc, char *argv[], char *envp[])
{
  int res,status;
  char databas[25]="olfix";
  const char *userp = getenv("USER");	// vem är inloggad?
  char usr[15];				// userid

  char temp1[]="INSERT INTO STDLEVPLATS(KUNDNR,STDLEVPLATS,ADRESS,POSTNR,POSTADR,LAND) VALUES (\"";
  char temp2[]="\"";
  char temp3[]=",";
  char temp4[]=")";
  char temp5[200]="";
  char kundnr[11];
  char stdlevplats[4];
  char adress[31];
  char postnr[7];
  char postadr[31];
  char land[31];
//  fprintf(stderr,"argc=%d, argv[argc-1]=%s\n",argc,argv[argc-1]);
// ================================================================================
// 		Val av databas, START
// ================================================================================
  status = which_database(envp);

  if (status != 0)
	exit(status);

  strcpy(usr,userp);				// Den inloggades userid

 if (argc<8){
    	if (strlen(database)!= 0){
		strcpy(databas,database);
	}else{
  		strcpy(databas,"olfixtst");	// olfixtst = testföretag
	}
  }else{
	if (strlen(argv[7]) != 0){
  		if (strncmp(argv[7],"99",2)==0){
			strcpy(databas,"olfixtst");
		}else{
  			strcpy(databas,argv[7]);
  		}
  	}
  }
  /* Om usr (userid) börjar på 'test' eller 'prov' använd databas 'olfixtst' */
  if (strncmp(usr,"test",4)==0 || strncmp(usr,"prov",4)==0 ) {
  	strcpy(databas,"olfixtst");
  }
// ================================================================================
// 		Val av databas, END!
// ================================================================================
//  fprintf(stderr,"databas=%s\n",databas);

  strcpy(kundnr,argv[1]);
  strcpy(stdlevplats,argv[2]);
  strcpy(adress,argv[3]);
  strcpy(postnr,argv[4]);
  strcpy(postadr,argv[5]);
  strcpy(land,argv[6]);


  strcat(temp5,temp1);
/* INSERT INTO STDLEVPLATS(KUNDNR,STDLEVPLATS,ADRESS,POSTNR,POSTADR,LAND) VALUES ("  */
  strcat(temp5,kundnr);/* 4376 */
/* INSERT INTO STDLEVPLATS(KUNDNR,STDLEVPLATS,ADRESS,POSTNR,POSTADR,LAND) VALUES ("4376  */
  strcat(temp5,temp2); /*  "     */
  strcat(temp5,temp3); /*  ,     */
  strcat(temp5,temp2); /*  "     */
  strcat(temp5,stdlevplats);/* 001  */
/* INSERT INTO STDLEVPLATS(KUNDNR,STDLEVPLATS,ADRESS,POSTNR,POSTADR,LAND) VALUES ("4376","001 */
  strcat(temp5,temp2); /*  "     */
  strcat(temp5,temp3); /*  ,     */
  strcat(temp5,temp2); /*  "     */
/* INSERT INTO STDLEVPLATS(KUNDNR,STDLEVPLATS,ADRESS,POSTNR,POSTADR,LAND) VALUES ("4376","001","  */
  strcat(temp5,adress);
  strcat(temp5,temp2); /*  "     */
  strcat(temp5,temp3); /*  ,     */
  strcat(temp5,temp2); /*  "     */
/* INSERT INTO STDLEVPLATS(KUNDNR,STDLEVPLATS,ADRESS,POSTNR,POSTADR,LAND) VALUES ("4376","001","Provstigen 1","  */
  strcat(temp5,postnr);
  strcat(temp5,temp2); /*  "     */
  strcat(temp5,temp3); /*  ,     */
  strcat(temp5,temp2); /*  "     */
/* INSERT INTO STDLEVPLATS(KUNDNR,STDLEVPLATS,ADRESS,POSTNR,POSTADR,LAND) VALUES ("4376","001","Provstigen 1","199 99","  */
  strcat(temp5,postadr);
  strcat(temp5,temp2); /*  "     */
  strcat(temp5,temp3); /*  ,     */
  strcat(temp5,temp2); /*  "     */
/* INSERT INTO STDLEVPLATS(KUNDNR,STDLEVPLATS,ADRESS,POSTNR,POSTADR,LAND) VALUES ("4376","001","Provstigen 1","199 99","LILLEBY","  */
  strcat(temp5,land);
  strcat(temp5,temp2); /*  "     */
  strcat(temp5,temp4); /*  )     */
/* INSERT INTO STDLEVPLATS(KUNDNR,STDLEVPLATS,ADRESS,POSTNR,POSTADR,LAND) VALUES ("4376","001","Provstigen 1","199 99","LILLEBY","Svberige")  */

 // fprintf(stderr,"temp5=%s\n",temp5);

  mysql_init(&my_connection);

  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
  // fprintf(stdout,"SLPADD:Connection success\n");

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
