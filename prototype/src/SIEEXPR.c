/***************************************************************************
                          SIEEXPR.c  -  description
                             -------------------
			     Ver: 0.1
    begin                : Ons  13 april 2005
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
	INPUT: arid		(bokf�rings�r)

	Kommando: ./SIEEXPR arid

	Function: Exportera resultat f�r angivet bokf�rings�r i SIE-format.

	OUTPUT: KTONR saldo
	samt errornb och error (text)

***************************************************************************/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/SIEEXPR.c,v 1.1 2005/04/13 08:21:58 janpihlgren Exp $ " ;

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
  const char *userp = getenv("USER");	/* vem �r inloggad?	*/
  char databas[25]="olfix";
  char usr[15];				/* userid		*/
  char arid[3]="";			/* bokf�rings�r		*/

  char temp1[]="SELECT KTONR, SUM(BELOPP),DK FROM VERRAD";
  char temp1c[]=" WHERE ARID = \"";
  char temp2[]="\" ";
  char temp3[]=" GROUP BY KTONR,DK";
  char temp5[500]="";

/*  for (i=0;i< argc;i++){
  	fprintf(stderr,"SIEEXPR argv%d = %s\n",i,argv[i]);
  }
*/
/*  fprintf(stderr,"argc=%d\n",argc);	*/
  if (argc<2){
  	fprintf(stderr,"Error: SIEEXPK. ARID saknas!\n");
	exit(0);
  }
  strncpy(arid,argv[1],sizeof(arid));

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
		strncpy(databas,database,sizeof(databas));
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

  strncpy(temp5,temp1,strlen(temp1));
/*  SELECT KTONR, SUM(BELOPP),DK FROM VERRAD	*/
  strncat(temp5,temp1c,strlen(temp1c));
/*  SELECT KTONR, SUM(BELOPP),DK FROM VERRAD WHERE ARID = "  */
  strncat(temp5,arid,strlen(arid));
/*  SELECT KTONR, SUM(BELOPP),DK FROM VERRAD WHERE ARID = " AD  */
  strncat(temp5,temp2,strlen(temp2));
/*  SELECT KTONR, SUM(BELOPP),DK FROM VERRAD WHERE ARID = " AD " */
  strncat(temp5,temp3,strlen(temp3));
/*  SELECT KTONR, SUM(BELOPP),DK FROM VERRAD WHERE ARID = " AD "
    ORDER BY KTONR */
/*     fprintf(stderr,"temp5=%s\n",temp5);	*/

  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
  	res = mysql_query(&my_connection,temp5);
  	if (res){
		fprintf(stderr,"Error: SIEEXPR SELECT errno: %d\n",mysql_errno(&my_connection));
        }
	else{
		res_ptr=mysql_store_result(&my_connection);
		if (res_ptr){
			i=1;
			fprintf(stdout,"OK: ANTAL_%lu_\n",(unsigned long)mysql_num_rows(res_ptr));
			while ((sqlrow=mysql_fetch_row(res_ptr)))  {
				display_row();
				i++;
			}
			fprintf(stdout,"END:");
			fprintf(stdout,"\n");
		}
		else{
			fprintf(stderr,"Error:  Data saknas:  %s\n", mysql_error(&my_connection));
		}
			if (mysql_errno(&my_connection))  {
				fprintf(stderr,"Error: SIEEXPR Retriev error:  %s\n", mysql_error(&my_connection));
			}
		}
	mysql_free_result(res_ptr);
    	mysql_close(&my_connection);
  }
  else{
    	fprintf(stderr,"Error: SIEEXPR Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: SIEEXPR Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
	}
    }
  return EXIT_SUCCESS;
}

void display_row()
{
   unsigned int field_count;
   field_count=0;
   int tmp=0;
//   	fprintf(stdout,"%s  %s  %s\n",sqlrow[0],sqlrow[1],sqlrow[2]);
   tmp=atoi(sqlrow[0]);
   if(tmp<3000){
	fprintf(stdout,"#UB 0 ");
   }else{
   	fprintf(stdout,"#RES 0 ");
   }
   fprintf(stdout,"%s ",sqlrow[0]);
   if(strcmp(sqlrow[2],"K")==0){
	fprintf(stdout,"-");
   }
   fprintf(stdout,"%s\n",sqlrow[1]);
//   fprintf(stdout,"%s\n",sqlrow[field_count]);
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
	 	fprintf(stderr,"Error: Filen .olfixrc kan inte �ppnas\n");
	}
	for (i=0;i < strlen(database);i++){
		tmp[i]=database[i];
	}
	tmp[i-1]=0;
	strncpy(database,tmp,strlen(tmp));
	database[strlen(tmp)]=0;
	return status;
}
