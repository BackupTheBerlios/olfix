/***************************************************************************
                          OLFIX.c  -  description
                             -------------------
    Version		 : 0.6
    begin                : Tors 29 maj  2003
    modified		 : Tors 24 febr 2005
    copyright            : (C) 2002 by Jan Pihlgren
    email                : jan@pihlgren.se
 ***************************************************************************/
/* fgets har ersatt getrad(s,lim)	20030530 /yann			   */
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *********************************************** ****************************/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/OLFIX.c,v 1.5 2005/02/24 08:53:04 janpihlgren Exp $ " ;

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "vt220.h"
#define FILEPATH 100
#define ANTARG 1

void meny(void);
void inloggning(void);
int find_tmp_path(char *envp[]);
int which_database(char *envp[]);

char userid[9]="";
char tmpfilepath[FILEPATH]="";
char database[15]="";

int main(int argc, char *argv[], char *envp[])
{
  int i;
  int status;
  const char *userp = getenv("USER");	/* vem är inloggad?	*/
  char databas[25]="olfix";
  char usr[15];				/* userid		*/

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

/*	fprintf(stderr,"argc=%d  argv1=%s\n",argc,argv[1]);	*/
	if (argc<2){
/*		argv[1] == NULL){	*/
		inloggning();
	}
	else{
		strncpy(userid,argv[1], sizeof(userid)-1);
		userid[sizeof(userid)-1]=0;
		for (i = 0;i < strlen(userid); i++){
			userid[i]=toupper(userid[i]);
		}
	}
	status = find_tmp_path(envp);
	if (status != 0)
		exit(status);
	meny();
	return 0;
}

void meny(void)
{
	char rad[2];
	int status,i;
	char svar;
	char anrop[FILEPATH]="";
start:
	status=0;
	cls();
	locate(1,35);
	fprintf(stdout,"*** OLFIX ***");
	locate(1,60);
	fprintf(stdout,"UserID: %s",userid);
	locate(3,25);
	fprintf(stdout,"1. (EKONOMI)");
	locate(4,25);
	fprintf(stdout,"2. (OLF)");
	locate(5,25);
	fprintf(stdout,"3. (PERSONAL)");
	locate(6,25);
	fprintf(stdout,"4. vadå");
	locate(7,25);
	fprintf(stdout,"5. vadå");
	locate(8,25);
	fprintf(stdout,"6. vadå");
	locate(9,25);
	fprintf(stdout,"7. vadå");
	locate(10,25);
	fprintf(stdout,"8. vadå");
	locate(11,25);
	fprintf(stdout,"9. ADMINISTRERA OLFIX");
	locate(12,25);
	fprintf(stdout,"0. SLUTA");
	locate(16,25);
	fprintf(stdout,"Vad v\xE4ljer du? ");
	fgets(rad, sizeof(rad), stdin);
	svar = rad[0];

/*	fprintf(stderr,"svaret är %c",svar);		*/

	switch (svar){
		case '0':
			status = -1;
			cls();
			break;
/*
		case '1':
			i=strlen(tmpfilepath);
			strncpy(anrop,tmpfilepath,i-1);
			strncat(anrop,"REDOV ",6);
			strncat(anrop,userid,strlen(userid));
			locate(22,1);
			fprintf(stderr,"anrop = %s\n",anrop);
			status=system(anrop);
			break;
*/
		case '9':
			i=strlen(tmpfilepath);
			strncpy(anrop,tmpfilepath,i-1);
/*			fprintf(stderr,"anrop=%s len=%d\n",anrop,strlen(tmpfilepath));		*/
			strncat(anrop,"ADMIN ",6);
			strncat(anrop,userid,strlen(userid));
/*			locate(22,1);				*/
/*			fprintf(stderr,"anrop = %s\n",anrop);	*/
			status=system(anrop);
			break;
		default:
			bell();
			break;
	}
	if(status == 0)
 		goto start;
}

void inloggning(void)
{
	int i;

	cls();
	locate(1,35);
	fprintf(stdout,"*** OLFIX ***");
	locate(10,25);
	fprintf(stdout,"Ange ditt UserID:");
	locate(10,42);
	fgets(userid,sizeof(userid),stdin);
	userid[sizeof(userid)-1]=0;
	for (i = 0;i < strlen(userid); i++){
		userid[i]=toupper(userid[i]);
/*		printf("%c\n",userid[i]);		*/
	}
}

int find_tmp_path(char *envp[])
{
	FILE *fil_pek;

	char home[50];
	char *home_pek;
	char resource[]="/.olfixrc";
	char filename[50]="";
	char tmp[50]="";
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
		while (fgets(tmp,50,fil_pek) != NULL){
			if(strstr(tmp,"PATH=")){
				tmp_pek=(strstr(tmp,"PATH="))+5;
				strncpy(tmpfilepath,tmp_pek,strlen(tmp_pek));
				status=0;
			}
		}
		fclose(fil_pek);
	}
	else{
	 	fprintf(stderr,"Error: Filen .olfixrc kan inte öppnas\n");
	}
/*	fclose(fil_pek);	*/
	return status;
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




