/***************************************************************************
                          OLFIX.c  -  description
                             -------------------
			     version 0.04
    begin                : Tors 29 maj 2003
    copyright            : (C) 2002 by Jan Pihlgren
    email                : jan@pihlgren.se
 ***************************************************************************/
/* fgets har ersatt getrad(s,lim)	20030530 /yann	*/
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *********************************************** ****************************/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/ADMIN.c,v 1.3 2003/05/30 07:11:38 janpihlgren Exp $ " ;

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "vt220.h"
#define FILEPATH 100

void meny(void);
void inloggning(void);
int find_tmp_path(char *envp[]);

char userid[9];
char tmpfilepath[FILEPATH];

int main(int argc, char *argv[], char *envp[])
{
	int i,status;
//	fprintf(stderr,"argc=%d  argv1=%s\n",argc,argv[1]);
	if (argc<2){
		//argv[1] == NULL){
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

//	fprintf(stderr,"svaret är %c",svar);

	switch (svar){
		case '0':
			status = -1;
			cls();
			break;
//		case '1':
//			i=strlen(tmpfilepath);
//			strncpy(anrop,tmpfilepath,i-1);
//			strcat(anrop,"REDOV ");
//			strcat(anrop,userid);
//			locate(22,1);
//			fprintf(stderr,"anrop = %s\n",anrop);
//			status=system(anrop);
//			break;
		case '9':
			i=strlen(tmpfilepath);
			strncpy(anrop,tmpfilepath,i-1);
//			fprintf(stderr,"anrop=%s len=%d\n",anrop,strlen(tmpfilepath));
			strcat(anrop,"ADMIN ");
			strcat(anrop,userid);
//			locate(22,1);
//			fprintf(stderr,"anrop = %s\n",anrop);
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
//		printf("%c\n",userid[i]);
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
	strcpy(filename,home);
	strcat(filename,resource);

	status=-1;

	if ((fil_pek = fopen(filename,"r")) != NULL){
		while (fgets(tmp,50,fil_pek) != NULL){
			if(strstr(tmp,"PATH=")){
				tmp_pek=(strstr(tmp,"PATH="))+5;
				strcpy(tmpfilepath,tmp_pek);
				status=0;
			}
		}
		fclose(fil_pek);
	}
	else{
	 	fprintf(stderr,"Error: Filen .olfixrc kan inte öppnas\n");
	}
//	fclose(fil_pek);
	return status;
}



