/***************************************************************************
                          ADMIN.c  -  description
                             -------------------
			     version 0.03
    begin                : Tis 29 april 2003
    copyright            : (C) 2002 by Jan Pihlgren
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
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/ADMIN.c,v 1.2 2003/05/13 03:51:28 janpihlgren Exp $ " ;


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "vt220.h"
#include "getrad.h"
//#include "itoa.h"
#define MAXRAD 30
#define MAXSTRING 5000
#define FILEPATH 100

void meny(void);
void inloggning(void);
void menyUser(void);
int UserAdd(void);
int UserDelete(void);
int UserList(void);
int UserChange(void);
int UserRightsAdd(void);
int UserRightsDel(void);
int find_tmp_path(char *envp[]);

char userid[9];
char tmpfilepath[FILEPATH];

main(int argc, char *argv[], char *envp[])
{
	int status;
	status = find_tmp_path(envp);
	if (status != 0)
		exit(status);

	strcat(userid,argv[1]);

	meny();
	return -1;
}

void meny(void)
{
	char rad[2];
	int status,i;
	char svar;
	char anrop[FILEPATH]="";
//	cls();
start:
	status=0;
	cls();
	locate(1,20);
	fprintf(stdout,"*** OLFIX ADMINISTRATION ***");
	locate(1,60);
	fprintf(stdout,"UserID: %s",userid);
	locate(3,20);
	fprintf(stdout,"1. Administrera användare");
	locate(4,20);
	fprintf(stdout,"2. vadå");
	locate(5,20);
	fprintf(stdout,"3. vadå");
	locate(6,20);
	fprintf(stdout,"4. Lägga till behörighet");
	locate(7,20);
	fprintf(stdout,"5. Ta bort behörighet");
	locate(8,20);
	fprintf(stdout,"6. Lägga till funktion");
	locate(9,20);
	fprintf(stdout,"7. Ta bort funktion");
	locate(10,20);
	fprintf(stdout,"8. Företagsdata");
	locate(11,20);
	fprintf(stdout,"9. Hjälptexter");
	locate(12,20);
	fprintf(stdout,"0. SLUTA");
	locate(16,20);
	fprintf(stdout,"Vad v\xE4ljer du? ");
	getrad(rad,MAXRAD);
	svar = rad[0];

//	fprintf(stderr,"svaret är %c",svar);

	switch (svar){
		case '0':
			status = -1;
//			cls();
			break;
		case '1':
			menyUser();
			break;
		case '4':
			UserRightsAdd();
			break;
		case '5':
			UserRightsDel();
			break;
		case '9':
			//regvard();
			break;
		default:
			bell();
			break;
	}
	if(status == 0){
 		goto start;
 	}
	else{
		i=strlen(tmpfilepath);
		strncpy(anrop,tmpfilepath,i-1);
		strcat(anrop,"OLFIX ");
		strcat(anrop,userid);
//		fprintf(stderr,"anrop = %s\n",anrop);
		status=system(anrop);
	}
}

void menyUser(void)
{
	char rad[2];
	int status;
	char svar;
	char anrop[30]="";
//	cls();
start:
	status=0;
	cls();
	locate(1,20);
	fprintf(stdout,"*** OLFIX ADMINISTRATION ***");
	locate(2,20);
	fprintf(stdout,"1. Användaradministration");
	locate(1,60);
	fprintf(stdout,"UserID: %s",userid);
	locate(4,20);
	fprintf(stdout,"1. Lägga till användare");
	locate(5,20);
	fprintf(stdout,"2. Ta bort användare");
	locate(6,20);
	fprintf(stdout,"3. Ändra användaruppgifter");
	locate(7,20);
	fprintf(stdout,"4. Lista användarinformation");
	locate(8,20);
	fprintf(stdout,"0. SLUTA");
	locate(10,20);
	fprintf(stdout,"Vad v\xE4ljer du? ");
	getrad(rad,MAXRAD);
	svar = rad[0];

	switch (svar){
		case '0':
//			status = -1;
			cls();
			break;
		case '1':
			UserAdd();
			break;
		case '2':
			UserDelete();
			break;
		case '3':
			UserChange();
			break;
		case '4':
			UserList();
			break;
		default:
			bell();
			break;
	}
	return;
}

int UserAdd(void)
{
	char *datastr;
	char *felpek;
	int fds[2];
	int status=-15;
	int i;
	char *pos;
	pid_t pid;

	char usr[9]="";
	char namn[31]="";
	char avd[11]="";
	char grp[11]="";
	int dummy;
	char rad[3];
	char tmp[33]="";

	cls();
	locate(1,20);
	fprintf(stdout,"*** OLFIX ADMINISTRATION ***");
	locate(1,60);
	fprintf(stdout,"UserID: %s",userid);
	locate(2,22);
	fprintf(stdout,"1. Registrera ny användare");
	locate(5,15);
	fprintf(stdout,"UserID:....");
	locate(6,15);
	fprintf(stdout,"Namn:......");
	locate(7,15);
	fprintf(stdout,"Avdelning:.");
	locate(8,15);
	fprintf(stdout,"Grupp:.....");
	locate(5,27);
	getrad(usr,8);
	for (i = 0;i < strlen(usr); i++){
		usr[i]=toupper(usr[i]);
	}
	locate(5,27);
	fprintf(stdout,"%s",usr);
	locate(6,27);
	getrad(namn,30);
	locate(7,27);
	getrad(avd,10);
	locate(8,27);
	getrad(grp,10);


	locate(10,27);
/************************************************************************/
/*	Godkänn verifikationsrad					*/
/* 	eller avbryt registrering? Det går med Ctrl-C			*/
/************************************************************************/
	fprintf(stdout,"OK? (<J>/N) ");
	dummy = getrad(rad,3);
	if (rad[0] == 'J' || rad[0] == 'j' || rad[0] == '\0'){
//		fprintf(stderr,"datasträng %s %s %s %s userid=%s\n",usr,namn,avd,grp,userid);
//		dummy = getrad(rad,3);
/************************************************************************/
/*	Uppdatera databasen						*/
/************************************************************************/
		pipe(fds);
		pid=fork();

		if (pid == (pid_t) 0) {		/* Child */
			close (fds[0]);
			dup2 (fds[1], STDOUT_FILENO);
			status=execl("STYRMAN", "STYRMAN", userid,"USERADD", usr, namn, avd, grp, (char *) 0);
//			fprintf(stderr,"status=%d\n",status);
//			fprintf(stdout,"Child uppdatering OK? (<J>/N) ");
//			dummy = getrad(rad,3);
		}
		else{				/* Parent (Denna process) */
			FILE* stream;
			close (fds[1]);
			stream = fdopen (fds[0],"r");

			datastr = malloc(MAXSTRING);

			status = fread(datastr,MAXSTRING,MAXSTRING,stream);
			fflush (stream);
			close (fds[0]);
			waitpid (pid, NULL,0);
			felpek=strstr(datastr,"error:");
			if (felpek !=0){
				fprintf(stderr,"ADMINupdateDatabaseParent:Felmeddelande:\n%s\n",felpek-7);
				free(datastr);
				return -1;
			}
			else{
//				fprintf(stdout,"ADMINupdateDatabaseParent: datstr= %s\n",datastr);
				pos=strstr(datastr,". Status =");
				if (pos != 0){
					status=atoi(strncpy(datastr,pos+11,2));
					fprintf(stdout,"ADMINupdateDatabase: Status2 = %d\n",status);
				}
				free(datastr);
//				fprintf(stdout,"Parent uppdatering OK? (<J>/N) ");
//				dummy = getrad(rad,3);
//				exit(0);
				return status;
			}
		}
		fprintf(stdout,"ADMINupdateDatabase: Status = %d\n",status);
		fprintf(stdout,"ADMIN slut uppdatering OK? (<J>/N) ");
		dummy = getrad(rad,3);

		return status;
	}
	fprintf(stdout,"uppdatering OK? (<J>/N) ");
	dummy = getrad(rad,3);

}

int UserList(void)
{
	char *datastr;
	char *felpek;
	int fds[2];
	int status=-15;
	int i,j,k,l,m;
	char *pos;
	char *pos1;
	char *pos2;
//	char *tempstring;
	char antrad[6]="";
//	char numtmp[10];
	pid_t pid;

	char usr[9]="";
	char namn[32]="";
	char avd[11]="";
	char grp[11]="";
	int dummy;
	char rad[3];
	char tmp[MAXSTRING]="";

	cls();
	locate(1,20);
	fprintf(stdout,"*** OLFIX ADMINISTRATION ***");
	locate(1,60);
	fprintf(stdout,"UserID: %s",userid);
	locate(2,22);
	fprintf(stdout,"4. Lista användare");
	locate(3,2);
	fprintf(stdout,"UserID    Namn                            Avd       Grupp");
	locate(4,2);
	fprintf(stdout,"--------------------------------------------------------------");
	locate(5,1);
/************************************************************************/
/*	Hämta data från databasen					*/
/************************************************************************/
	pipe(fds);
	pid=fork();

	if (pid == (pid_t) 0) {		/* Child */
		close (fds[0]);
		dup2 (fds[1], STDOUT_FILENO);
		status=execl("STYRMAN", "STYRMAN", userid,"USERLST", (char *) 0);
//		fprintf(stderr,"status=%d\n",status);
//		fprintf(stdout,"Child uppdatering OK? (<J>/N) ");
//		dummy = getrad(rad,3);
	}
	else{				/* Parent (Denna process) */
		FILE* stream;
		close (fds[1]);
		stream = fdopen (fds[0],"r");
		datastr = malloc(MAXSTRING);
		status = fread(datastr,MAXSTRING,MAXSTRING,stream);
		fflush (stream);
		close (fds[0]);
		waitpid (pid, NULL,0);
		felpek=strstr(datastr,"error:");
		if (felpek !=0){
			fprintf(stderr,"ADMINUserListParent:Felmeddelande:\n%s\n",felpek-7);
			free(datastr);
			return -1;
		}
		else{
//			fprintf(stdout,"ADMINUserListParent: datstr= %s\n",datastr);
			pos=strstr(datastr,". Status =");
			if (pos != 0){
				status=atoi(strncpy(datastr,pos+11,2));
				fprintf(stdout,"ADMINUserList: Status2 = %d\n",status);
			}
			pos=strstr(datastr,"NR_");
			if (pos != 0){
				strcpy(tmp,datastr);
//				fprintf(stdout,"%s\n",tmp);
			}
			free(datastr);
//			fprintf(stdout,"Parent lista OK? (<J>/N) ");
//			dummy = getrad(rad,3);
		}
	}
/********************************************************************************/
/*		Selektera ut userdata		      				*/
/* Antalet poster som läses ut med USERLST skickas med inledande tecknen NR_ 	*/
/********************************************************************************/
//	fprintf(stdout,"%s\n",tmp);

/*	Plocka ut antal poster				*/
	pos1=strstr(tmp,"NR_");
	pos2=strstr(tmp,"_:");
	i=pos2-pos1;
	k=0;
	for (j=3;j < i; j++){
		antrad[k]=tmp[j];
		k++;
	}
	i=atoi(antrad);		/* i = antal poster */
	fprintf(stderr,"Antal poster = i =%d\n",i);
/* -----------------------------------------------------------------------------*/
//	fprintf(stderr,"tmp=%d\n",strlen(tmp));
	m=5;
	l=0;

	for (k = 1; k <= i; k++){	/*  bearbeta i antal rader */
//		fprintf(stderr,"k=%d\n",k);
//		fprintf(stderr,"size usr=%d\n",sizeof(usr));
		l=0;
		for (j = m; j < sizeof(usr) + m; j++){
//			fprintf(stderr,"j=%d tmp[%d]=%c\n",j,j,tmp[j]);
			if (tmp[j] != *("_")){
				usr[l]=tmp[j];
//				fprintf(stderr,"usr=%c \n",usr[l]);
				l++;
			}else
			{
				usr[l]=*("\0");
				j=sizeof(usr) + m;
			}
		}
//		fprintf(stderr,"usr=%s l=%d m=%d\n",usr,l,m);
		locate(4+k,2);
		fprintf(stdout,"%s",usr);

		m=m+l+2;
		l=0;
		for (j = m; j < sizeof(namn) + m; j++){
			if (tmp[j] != *("_")){
				namn[l]=tmp[j];
				l++;
			}else
			{
				namn[l]=*("\0");
				j=sizeof(namn) + m;
			}
		}
//		fprintf(stderr,"namn=%s l=%d m=%d\n",namn,l,m);
		locate(4+k,12);
		fprintf(stdout,"%s",namn);

		m=m+l+2;
		l=0;
		for (j = m; j < sizeof(avd) + m; j++){
			if (tmp[j] != *("_")){
				avd[l]=tmp[j];
				l++;
			}else
			{
				avd[l]=*("\0");
				j=sizeof(avd) + m;
			}
		}
//		fprintf(stderr,"avd=%s l=%d m=%d\n",avd,l,m);
		locate(4+k,44);
		fprintf(stdout,"%s",avd);

		m=m+l+2;
		l=0;
		for (j = m; j < sizeof(grp) + m; j++){
			if (tmp[j] != *("_")){
				grp[l]=tmp[j];
				l++;
			}else
			{
				grp[l]=*("\0");
				j=sizeof(grp) + m;
			}
		}
//		fprintf(stderr,"grp=%s l=%d m=%d\n",grp,l,m);
		locate(4+k,54);
		fprintf(stdout,"%s",grp);

		m=m+l+2;

		for (l=0;l<sizeof(usr);l++)
			usr[l]=*("\0");
		for (l=0;l<sizeof(namn);l++)
			namn[l]=*("\0");
		for (l=0;l<sizeof(avd);l++)
			avd[l]=*("\0");
		for (l=0;l<sizeof(grp);l++)
			grp[l]=*("\0");
//exit(0);
	}
	fprintf(stdout,"%s\n");
	locate(23,10);
	fprintf(stdout,"OK? (<J>/N) ");
	dummy = getrad(rad,3);
//exit(0);
}


int UserDelete(void)
{
	char *datastr;
	char *felpek;
	int fds[2];
	int status=-15;
	int i;
	char *pos;
	pid_t pid;


	char usr[9]="";
	char namn[31]="";
	char avd[11]="";
	char grp[11]="";
	int dummy;
	char rad[3];

	cls();
	locate(1,20);
	fprintf(stdout,"*** OLFIX ADMINISTRATION ***");
	locate(1,60);
	fprintf(stdout,"UserID: %s",userid);
	locate(2,22);
	fprintf(stdout,"2. Ta bort användare");
	locate(5,15);
	fprintf(stdout,"UserID:....");
	locate(5,27);
	getrad(usr,8);
	for (i = 0;i < strlen(usr); i++){
		usr[i]=toupper(usr[i]);
	}
	locate(5,27);
	fprintf(stdout,"%s",usr);

	locate(10,27);
/************************************************************************/
/*	Godkänn bort tab aav användare					*/
/* 	eller avbryt. Det går med Ctrl-C				*/
/************************************************************************/
	fprintf(stdout,"OK? (<J>/N) ");
	dummy = getrad(rad,3);
	if (rad[0] == 'J' || rad[0] == 'j' || rad[0] == '\0'){

/************************************************************************/
/*	Uppdatera databasen						*/
/************************************************************************/
		pipe(fds);
		pid=fork();

		if (pid == (pid_t) 0) {		/* Child */
			close (fds[0]);
			dup2 (fds[1], STDOUT_FILENO);
			status=execl("STYRMAN", "STYRMAN", userid,"USERDEL", usr, (char *) 0);
		}
		else{				/* Parent (Denna process) */
			FILE* stream;
			close (fds[1]);
			stream = fdopen (fds[0],"r");

			datastr = malloc(MAXSTRING);

			status = fread(datastr,MAXSTRING,MAXSTRING,stream);
			fflush (stream);
			close (fds[0]);
			waitpid (pid, NULL,0);
			felpek=strstr(datastr,"error:");
			if (felpek !=0){
				fprintf(stderr,"ADMINupdateDatabaseParent:Felmeddelande:\n%s\n",felpek-7);
				free(datastr);
				return -1;
			}
			else{
//				fprintf(stdout,"ADMINupdateDatabaseParent: datstr= %s\n",datastr);
				pos=strstr(datastr,". Status =");
				if (pos != 0){
					status=atoi(strncpy(datastr,pos+11,2));
//					fprintf(stdout,"ADMINupdateDatabase: Status2 = %d\n",status);
				}
				free(datastr);
				return status;
			}
		}
		fprintf(stdout,"ADMINupdateDatabase: Status = %d\n",status);
		return status;
	}
}

int UserChange(void)
{
	char *datastr;
	char *felpek;
	int fds[2];
	int status=-15;
	int i,j,k,l;
	char *pos;
	char *pos1;	/* userid	*/
	char *pos2;	/* namn		*/
	char *pos3;	/* avd		*/
	char *pos4;	/* grupp	*/

	pid_t pid;

	char usr[9]="";
	char namn[31]="";
	char avd[11]="";
	char grp[11]="";
	int dummy;
	char rad[3];
	char tmp[62]="";
	char svar;

	cls();
	locate(1,20);
	fprintf(stdout,"*** OLFIX ADMINISTRATION ***");
	locate(1,60);
	fprintf(stdout,"UserID: %s",userid);
	locate(2,22);
	fprintf(stdout,"3. Ändra användardata");
	locate(5,15);
	fprintf(stdout,"   UserID:....");
	locate(6,15);
	fprintf(stdout,"1. Namn:......");
	locate(7,15);
	fprintf(stdout,"2. Avdelning:.");
	locate(8,15);
	fprintf(stdout,"3. Grupp:.....");
	locate(9,15);
	fprintf(stdout,"9. Avsluta");
	locate(11,15);
	fprintf(stdout,"Ange userid: ");

	locate(11,28);
	getrad(usr,8);
	for (i = 0;i < strlen(usr); i++){
		usr[i]=toupper(usr[i]);
	}
	locate(11,28);
	fprintf(stdout,"%s",usr);

/******************************************************/
/*		Hämta userdata			      */
/******************************************************/

		pipe(fds);
		pid=fork();

		if (pid == (pid_t) 0) {		/* Child */
			close (fds[0]);
			dup2 (fds[1], STDOUT_FILENO);
			status=execl("STYRMAN", "STYRMAN", userid,"USERDSP", usr, (char *) 0);
//			fprintf(stderr,"status=%d\n",status);
//			fprintf(stdout,"Child uppdatering OK? (<J>/N) ");
//			dummy = getrad(rad,3);
		}
		else{				/* Parent (Denna process) */
			FILE* stream;
			close (fds[1]);
			stream = fdopen (fds[0],"r");

			datastr = malloc(MAXSTRING);

			status = fread(datastr,MAXSTRING,MAXSTRING,stream);
			fflush (stream);
			close (fds[0]);
			waitpid (pid, NULL,0);
			felpek=strstr(datastr,"error:");
			if (felpek !=0){
				fprintf(stderr,"ADMINuserChangeGetParent:Felmeddelande:\n%s\n",felpek-7);
				free(datastr);
				return -1;
			}
			else{
//				fprintf(stdout,"ADMINuserChangeGetParent: datstr= %s\n",datastr);
				pos=strstr(datastr,". Status =");
				if (pos != 0){
					status=atoi(strncpy(datastr,pos+11,2));
					fprintf(stdout,"ADMINuserChangeGet: Status2 = %d\n",status);
				}
				pos=strstr(datastr,"1:");
				if (pos != 0){
					strcpy(tmp,datastr);
//					fprintf(stderr,"namn=%s\n",tmp);
				}


				free(datastr);
//				fprintf(stdout,"Parent uppdatering OK? (<J>/N) ");
//				dummy = getrad(rad,3);
				//return status;
			}
		}
//		fprintf(stdout,"ADMINuserChange: Status = %d\n",status);
//		fprintf(stdout,"ADMIN slut uppdatering OK? (<J>/N) ");
//		dummy = getrad(rad,3);
//		return status;

//	fprintf(stdout,"\nHämtning OK? (<J>/N) ",0);
//	dummy = getrad(rad,3);

/******************************************************/
/*		Selektera ut userdata		      */
/******************************************************/
//	fprintf(stderr,"tmp=%s\n",tmp);
/* 	userid mellan :1 och :2 i tmp */
	pos1=strstr(tmp,"1:");	/* userid 	*/
	pos2=strstr(tmp,"2:");	/* namn		*/
	pos3=strstr(tmp,"3:");	/* avd		*/
	pos4=strstr(tmp,"4:");	/* grupp	*/
	i=pos2-pos1;
	l=i;
	k=0;
	for (j=2;j < i;j++){
		usr[k]=tmp[j];
		k++;
	}
//	fprintf(stderr,"Userid=%s\n",usr);

	l=i;
	i=pos3-pos2;
	k=0;
	for (j=l+2;j < l+i;j++){
		namn[k]=tmp[j];
		k++;
	}
//	fprintf(stderr,"Namn=%s\n",namn);

	l=l+i;
	i=pos4-pos3;
	k=0;
	for (j=l+2;j < l+i;j++){
		avd[k]=tmp[j];
		k++;
	}
//	fprintf(stderr,"Avd=%s\n",avd);

	l=l+i;
	i=strlen(tmp);
//	fprintf(stderr,"i=%d l=%d\n",i,l);
	k=0;
	for (j=l+2;j < i-1;j++){
		grp[k]=tmp[j];
		k++;
	}
//	fprintf(stderr,"Grupp=%s\n",grp);
/******************************************************/
/*		Visa userdata			      */
/******************************************************/
	locate(5,30);
	fprintf(stdout,"%s",usr);
	locate(6,30);
	fprintf(stdout,"%s",namn);
	locate(7,30);
	fprintf(stdout,"%s",avd);
	locate(8,30);
	fprintf(stdout,"%s",grp);
/******************************************************/
/*		Ändra userdata			      */
/******************************************************/
radChange:
	status=0;
//	locate(12,15);
//	fprintf(stdout,"Avsluta med 9");
	locate(13,15);
	fprintf(stdout,"Vilken rad vill du ändra? ");
	locate(13,41);
	getrad(rad,MAXRAD);
	svar = rad[0];

	locate(13,41);
	radera_rad();
	switch (svar){
		case '1':
			locate(6,30);
			radera_rad();
			locate(6,30);
			getrad(namn,30);
			break;
		case '2':
			locate(7,30);
			radera_rad();
			locate(7,30);
			getrad(avd,10);
			break;
		case '3':
			locate(8,30);
			radera_rad();
			locate(8,30);
			getrad(grp,10);
			break;
		case '9':
			status=-1;
			break;
		default:
			bell();
			break;
	}
	if (status == 0)
		goto radChange;

/************************************************************************/
/*	Godkänn användardata						*/
/* 	eller avbryt registrering? Det går med Ctrl-C			*/
/************************************************************************/
	locate(15,15);
	fprintf(stdout,"Godkänna uppdatering? (<J>/N) ");
	dummy = getrad(rad,3);

	if (rad[0] == 'J' || rad[0] == 'j' || rad[0] == '\0'){
//		fprintf(stderr,"datasträng %s %s %s %s userid=%s\n",usr,namn,avd,grp,userid);
//		dummy = getrad(rad,3);

/************************************************************************/
/*	Uppdatera användardata						*/
/************************************************************************/

		pipe(fds);
		pid=fork();

		if (pid == (pid_t) 0) {		/* Child */
			close (fds[0]);
			dup2 (fds[1], STDOUT_FILENO);
			status=execl("STYRMAN", "STYRMAN", userid,"USERCHG", usr, namn, avd, grp, (char *) 0);
//			fprintf(stderr,"status=%d\n",status);
//			fprintf(stdout,"Child uppdatering OK? (<J>/N) ");
//			dummy = getrad(rad,3);
		}
		else{				/* Parent (Denna process) */
			FILE* stream;
			close (fds[1]);
			stream = fdopen (fds[0],"r");

			datastr = malloc(MAXSTRING);

			status = fread(datastr,MAXSTRING,MAXSTRING,stream);
			fflush (stream);
			close (fds[0]);
			waitpid (pid, NULL,0);
			felpek=strstr(datastr,"error:");
			if (felpek !=0){
				fprintf(stderr,"ADMINuserChangeParent:Felmeddelande:\n%s\n",felpek-7);
				free(datastr);
				return -1;
			}
			else{
//				fprintf(stdout,"ADMINupdateDatabaseParent: datstr= %s\n",datastr);
				pos=strstr(datastr,". Status =");
				if (pos != 0){
					status=atoi(strncpy(datastr,pos+11,2));
					fprintf(stdout,"ADMINuserChange: Status2 = %d\n",status);
				}
				free(datastr);
//				fprintf(stdout,"Parent uppdatering OK? (<J>/N) ");
//				dummy = getrad(rad,3);
//				exit(0);
				return status;
			}
		}
//		fprintf(stdout,"ADMINuserChange: Status = %d\n",status);
//		fprintf(stdout,"ADMIN slut uppdatering OK? (<J>/N) ");
//		dummy = getrad(rad,3);
		return status;
	}
//	fprintf(stdout,"uppdatering OK? (<J>/N) ");
	dummy = getrad(rad,3);
}

int UserRightsAdd(void)
{
	char *datastr;
	char *felpek;
	int fds[2];
	int status=-15;
	int i;
	char *pos;
	pid_t pid;

	char usr[9]="";
	char func[9]="";
	int dummy;
	char rad[3];
	char tmp[33]="";

	cls();
	locate(1,20);
	fprintf(stdout,"*** OLFIX ADMINISTRATION ***");
	locate(1,60);
	fprintf(stdout,"UserID: %s",userid);
	locate(2,22);
	fprintf(stdout,"3. Ange användares behörighet");
	locate(5,15);
	fprintf(stdout,"UserID:....");
	locate(6,15);
	fprintf(stdout,"Funktion:..");
	locate(5,27);
	getrad(usr,8);
	for (i = 0;i < strlen(usr); i++){
		usr[i]=toupper(usr[i]);
	}
	locate(5,27);
	fprintf(stdout,"%s",usr);
	locate(6,27);
	getrad(func,8);
	for (i = 0;i < strlen(func); i++){
		func[i]=toupper(func[i]);
	}
	locate(6,27);
	fprintf(stdout,"%s",func);
	locate(10,27);
/************************************************************************/
/*	Godkänn verifikationsrad					*/
/* 	eller avbryt registrering? Det går med Ctrl-C			*/
/************************************************************************/
	fprintf(stdout,"OK? (<J>/N) ");
	dummy = getrad(rad,3);
	if (rad[0] == 'J' || rad[0] == 'j' || rad[0] == '\0'){
//		fprintf(stderr,"datasträng %s %s %s %s userid=%s\n",usr,func,userid);
//		dummy = getrad(rad,3);
/************************************************************************/
/*	Uppdatera databasen						*/
/************************************************************************/
		pipe(fds);
		pid=fork();

		if (pid == (pid_t) 0) {		/* Child */
			close (fds[0]);
			dup2 (fds[1], STDOUT_FILENO);
			status=execl("STYRMAN", "STYRMAN", userid,"RGTADD", usr, func, (char *) 0);
//			fprintf(stderr,"status=%d\n",status);
//			fprintf(stdout,"Child uppdatering OK? (<J>/N) ");
//			dummy = getrad(rad,3);
		}
		else{				/* Parent (Denna process) */
			FILE* stream;
			close (fds[1]);
			stream = fdopen (fds[0],"r");

			datastr = malloc(MAXSTRING);

			status = fread(datastr,MAXSTRING,MAXSTRING,stream);
			fflush (stream);
			close (fds[0]);
			waitpid (pid, NULL,0);
			felpek=strstr(datastr,"error:");
			if (felpek !=0){
				fprintf(stderr,"ADMINupdateDatabaseParent:Felmeddelande:\n%s\n",felpek-7);
				free(datastr);
				return -1;
			}
			else{
//				fprintf(stdout,"ADMINupdateDatabaseParent: datstr= %s\n",datastr);
				pos=strstr(datastr,". Status =");
				if (pos != 0){
					status=atoi(strncpy(datastr,pos+11,2));
					fprintf(stdout,"ADMINUserRightsAddupdateDatabase: Status2 = %d\n",status);
				}
				free(datastr);
//				fprintf(stdout,"Parent uppdatering OK? (<J>/N) ");
//				dummy = getrad(rad,3);
//				exit(0);
				return status;
			}
		}
//		fprintf(stdout,"ADMINupdateDatabase: Status = %d\n",status);
//		fprintf(stdout,"ADMIN slut uppdatering OK? (<J>/N) ");
		return status;
	}
	//fprintf(stdout,"uppdatering OK? (<J>/N) ");
	//dummy = getrad(rad,3);

}

int UserRightsDel(void)
{
	char *datastr;
	char *felpek;
	int fds[2];
	int status=-15;
	int i;
	char *pos;
	pid_t pid;

	char usr[9]="";
	char func[9]="";
	int dummy;
	char rad[3];
	char tmp[33]="";
	char errmsg[50]="";

	cls();
	locate(1,20);
	fprintf(stdout,"*** OLFIX ADMINISTRATION ***");
	locate(1,60);
	fprintf(stdout,"UserID: %s",userid);
	locate(2,22);
	fprintf(stdout,"4. Ta bort användares behörighet");
	locate(5,15);
	fprintf(stdout,"UserID:....");
	locate(6,15);
	fprintf(stdout,"Funktion:..");
	locate(5,27);
	getrad(usr,8);
	for (i = 0;i < strlen(usr); i++){
		usr[i]=toupper(usr[i]);
	}
	locate(5,27);
	fprintf(stdout,"%s",usr);
	locate(6,27);
	getrad(func,8);
	for (i = 0;i < strlen(func); i++){
		func[i]=toupper(func[i]);
	}
	locate(6,27);
	fprintf(stdout,"%s",func);
	locate(10,27);
/************************************************************************/
/*	Godkänn verifikationsrad					*/
/* 	eller avbryt registrering? Det går med Ctrl-C			*/
/************************************************************************/
	fprintf(stdout,"OK? (<J>/N) ");
	dummy = getrad(rad,3);
	if (rad[0] == 'J' || rad[0] == 'j' || rad[0] == '\0'){
//		fprintf(stderr,"datasträng %s %s %s %s userid=%s\n",usr,namn,avd,grp,userid);
//		dummy = getrad(rad,3);
/************************************************************************/
/*	Uppdatera databasen						*/
/************************************************************************/
		pipe(fds);
		pid=fork();

		if (pid == (pid_t) 0) {		/* Child */
			close (fds[0]);
			dup2 (fds[1], STDOUT_FILENO);
			status=execl("STYRMAN", "STYRMAN", userid,"RGTDEL", usr, func, (char *) 0);
//			fprintf(stderr,"status=%d\n",status);
//			fprintf(stdout,"Child uppdatering OK? (<J>/N) ");
//			dummy = getrad(rad,3);
		}
		else{				/* Parent (Denna process) */
			FILE* stream;
			close (fds[1]);
			stream = fdopen (fds[0],"r");

			datastr = malloc(MAXSTRING);

			status = fread(datastr,MAXSTRING,MAXSTRING,stream);
			fflush (stream);
			close (fds[0]);
			waitpid (pid, NULL,0);
			felpek=strstr(datastr,"error:");
			if (felpek !=0){
				fprintf(stderr,"ADMINupdateDatabaseParent:Felmeddelande:\n%s\n",felpek-7);
				free(datastr);
				return -1;
			}
			else{
//				fprintf(stdout,"ADMINupdateDatabaseParent: datstr= %s\n",datastr);
				pos=strstr(datastr,"ej behör");
				if (pos != 0){
					locate(23,2);
					fprintf(stdout,"Felmeddelande: %s\n",datastr);
//					fprintf(stdout,"ADMINUserRightsDelupdateDatabase: Status2 = %d\n",status);
				}
				free(datastr);
//				fprintf(stdout,"Parent uppdatering OK? (<J>/N) ");
//				dummy = getrad(rad,3);
//				exit(0);
				return status;
			}
		}
//		fprintf(stdout,"ADMINupdateDatabase: Status = %d\n",status);
//		fprintf(stdout,"ADMIN slut uppdatering OK? (<J>/N) ");
		return status;
	}
	//fprintf(stdout,"uppdatering OK? (<J>/N) ");
	//dummy = getrad(rad,3);
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
	int i,j,status;

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
	return status;
}

