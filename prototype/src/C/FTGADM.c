/***************************************************************************
                          FTGADM.c  -  description
                             -------------------
			     version 0.4
			     ersätter FOREG.c
			     ersätter FORADM.c (2003-04-15)
    begin                : Fre 22 nov 2002
    copyright            : (C) 2002 by Jan Pihlgren
    email                : jan@pihlgren.se
 ***************************************************************************/
/* 	INPUT: userid [databas]						   */

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *********************************************** ****************************/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/C/Attic/FTGADM.c,v 1.1 2004/05/03 04:42:57 janpihlgren Exp $ " ;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "vt220.h"
#include "getrad.h"
#include "unpad.h"
#define MAXRAD 30
#define MAXSTRING 5000
#define ANTARG 1

int which_database(char *envp[]);
  char database[15]="";

char userid[9]="";
char foretagsnamn[30]="";
char adr1adr[30]="";
char adr1postnr[9]="";
char adr1ort[15]="";
char adr2adr[30]="";
char adr2postnr[9]="";
char adr2ort[15]="";
char adr3adr[30]="";
char adr3postnr[9]="";
char adr3ort[15]="";


void meny(void);
int getAdress(char *adr);
void updateAdress(void);
void updateTfn(void);
int getBokfPeriod(char *adr);
void updateBokfPeriod(void);

int updateForadm(char *rectyp);		/* rectyp = posttyp. */
int trim(void);
int clearAdresser(void);

 int main(int argc, char *argv[], char *envp[])
{
/*  int i;	*/
  int status;
  const char *userp = getenv("USER");	/* vem är inloggad?	*/
  char databas[25]="olfix";
  char usr[15];				/* userid		*/
  fprintf(stderr,"argc=%d\n",argc);
  /* ================================================================================ */
/* 		Val av databas, START						    */
/* ================================================================================ */

  status = which_database(envp);
fprintf(stderr,"database=%s\n",database);
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
  fprintf(stderr,"ANTARG=%d,argv[ANTARG]=%s\n",ANTARG,argv[ANTARG]);
/* Om usr (userid) börjar på 'test' eller 'prov' använd databas 'olfixtst' */
  if (strncmp(usr,"test",4)==0 || strncmp(usr,"prov",4)==0 ) {
  	strncpy(databas,"olfixtst",15);
  }
/* fprintf(stderr,"Databas=%s\n",databas);	*/
/* ================================================================================ */
/* 		Val av databas, END!						    */
/* ================================================================================ */
fprintf(stderr,"argv[1]=%s\n",argv[1]);
  strncpy(userid,argv[1],strlen(argv[1]));
  meny();
  return 0;
  meny();
}

void meny(void)
{
	char rad[2];
	int status;
	char svar;
	char anrop[30]="";
start:
	status=0;
	cls();
	locate(1,35);
	fprintf(stdout,"*** OLFIX ***");
	locate(1,60);
	fprintf(stdout,"UserID: %s",userid);
	locate(2,20);
	fprintf(stdout,"Företagsdata");
	locate(4,25);
	fprintf(stdout,"1. Adresser");
	locate(5,25);
	fprintf(stdout,"2. Telefonnummer");
	locate(6,25);
	fprintf(stdout,"3. vadå");
	locate(7,25);
	fprintf(stdout,"4. vadå");
	locate(8,25);
	fprintf(stdout,"5. vadå");
	locate(9,25);
	fprintf(stdout,"6. vadå");
	locate(10,25);
	fprintf(stdout,"7. Bokföringsperioder");
	locate(11,25);
	fprintf(stdout,"8. vadå");
	locate(12,25);
	fprintf(stdout,"9. vadå");
	locate(13,25);
	fprintf(stdout,"0. SLUTA");
	locate(16,25);
	fprintf(stdout,"Vad v\xE4ljer du? ");
	getrad(rad,MAXRAD);
	svar = rad[0];

/*	fprintf(stderr,"svaret är %c",svar);	*/

	switch (svar){
		case '0':
			status = -1;
			cls();
			break;
		case '1':
			updateAdress();
			break;
		case '2':
			updateTfn();
			break;
		case '7':
			updateBokfPeriod();
			break;

		case '9':
			break;
		default:
			bell();
			break;
	}
	if(status == 0){
 		goto start;
	}
	else{
		strncpy(anrop,"./OLFIX ",strlen(anrop));
		strncat(anrop,userid,strlen(userid));
		status=system(anrop);
	}
}

void updateAdress(void)
{
	char rad[2]="";
	int status,dummy,i;
/*	char tmp[10]="";	*/
	char svar;
	char adr[6]="";
	static char adr1[]="ADR1";
	static char adr2[]="ADR2";
	static char adr3[]="ADR3";

/*	cls();	*/
	status=clearAdresser();
	strncpy(adr,adr1,strlen(adr1));
	status = getAdress(adr);
	strncpy(adr,adr2,strlen(adr2));
	status = getAdress(adr);
	strncpy(adr,adr3,strlen(adr3));
	status = getAdress(adr);
/*	fprintf(stderr,"start\n");	*/
start:
	status=0;
	cls();
	locate(1,35);
	fprintf(stdout,"*** OLFIX ***");
	locate(1,60);
	fprintf(stdout,"UserID: %s",userid);
	locate(2,30);
	fprintf(stdout,"Företagsdata, Adresser");

	locate(4,1);
	fprintf(stdout,"A. Företagsnamn:");
	locate(4,18);
	fprintf(stdout,foretagsnamn);
	locate(5,30);
	fprintf(stdout,"Företagets postadress");
	locate(6,30);
	fprintf(stdout,"---------------------");

	locate(7,1);
	fprintf(stdout,"1. Postadr:");
	locate(7,13);
	fprintf(stdout,adr1adr);
	locate(7,44);
	fprintf(stdout,"2. Postnr:");
	locate(7,55);
	fprintf(stdout,adr1postnr);
	locate(7,62);
	fprintf(stdout,"3. Ort");
	locate(7,69);
	fprintf(stdout,adr1ort);

	locate(9,30);
	fprintf(stdout,"Besöksadress");
	locate(10,30);
	fprintf(stdout,"------------");
	locate(11,1);
	fprintf(stdout,"4. Gatuadr:");
	locate(11,13);
	fprintf(stdout,adr2adr);
	locate(11,44);
	fprintf(stdout,"5. Postnr:");
	locate(11,55);
	fprintf(stdout,adr2postnr);
	locate(11,62);
	fprintf(stdout,"6. Ort");
	locate(11,69);
	fprintf(stdout,adr2ort);

	locate(13,30);
	fprintf(stdout,"Leveransadress");
	locate(14,30);
	fprintf(stdout,"--------------");
	locate(15,1);
	fprintf(stdout,"7. Gatuadr:");
	locate(15,13);
	fprintf(stdout,adr3adr);
	locate(15,44);
	fprintf(stdout,"8. Postnr:");
	locate(15,55);
	fprintf(stdout,adr3postnr);
	locate(15,62);
	fprintf(stdout,"9. Ort");
	locate(15,69);
	fprintf(stdout,adr3ort);

	locate(17,30);
	fprintf(stdout,"0. SLUTA");

	locate(19,30);
	fprintf(stdout,"Vilket f\xE4lt v\xE4ljer du? ");
	getrad(rad,MAXRAD);
	rad[0]=toupper(rad[0]);
	svar = rad[0];

	switch (svar){
		case '0':
			status = -1;
			locate(21,10);
			fprintf(stdout,"Uppdatera? <J>/N ");
			dummy = getrad(rad,3);
			if (rad[0] == 'J' || rad[0] == 'j' || rad[0] == '\0'){
				updateForadm("ADR");
			}
			break;
		case '1':
			locate(7,13);
			getrad(adr1adr,30);
			break;
		case '2':
			locate(7,55);
			getrad(adr1postnr,8);
			break;
		case '3':
			locate(7,69);
			getrad(adr1ort,15);
			break;
		case '4':
			locate(11,13);
			getrad(adr2adr,30);
			break;
		case '5':
			locate(11,55);
			getrad(adr2postnr,8);
			break;
		case '6':
			locate(11,69);
			getrad(adr2ort,15);
			break;
		case '7':
			locate(15,13);
			getrad(adr3adr,30);
			break;
		case '8':
			locate(15,55);
			getrad(adr3postnr,8);
			break;
		case '9':
			locate(15,69);
			for(i=0;i<15;i++)
				adr3ort[i]=0x00;
			getrad(adr3ort,15);
			break;
		case 'A':
			locate(4,18);
			getrad(foretagsnamn,15);
			break;
		default:
			bell();
			break;
	}
	if(status == 0){
 		goto start;
	}
}

void updateTfn(void)
{
	char rad[2]="";
	int status;
	char svar;
/*	char anrop[30]="";	*/
start:
	status=0;
	cls();
	locate(1,35);
	fprintf(stdout,"*** OLFIX ***");
	locate(1,60);
	fprintf(stdout,"UserID: %s",userid);
	locate(2,30);
	fprintf(stdout,"Företagsdata, Telfonnummer");

	locate(4,1);
	fprintf(stdout,"Företagssvar:");
	locate(5,30);
	fprintf(stdout,"Företagets Telefonnummer");
	locate(6,30);
	fprintf(stdout,"---------------------");

	locate(7,1);
	fprintf(stdout,"1. Tfnnr:");
	locate(7,25);
	fprintf(stdout,"2. Mobiltelefonnr:");
	locate(7,55);
	fprintf(stdout,"3. Faxnummer");

/*	locate(9,30);
	fprintf(stdout,"Besöksadress");
	locate(10,30);
	fprintf(stdout,"------------");
	locate(11,1);
	fprintf(stdout,"5. Gatuadr:");
	locate(11,44);
	fprintf(stdout,"6. Postnr:");
	locate(11,62);
	fprintf(stdout,"7. Ort");

	locate(13,30);
	fprintf(stdout,"Leveransadress");
	locate(14,30);
	fprintf(stdout,"--------------");
	locate(15,1);
	fprintf(stdout,"8. Gatuadr:");
	locate(15,45);
	fprintf(stdout,"9. Postnr:");
	locate(15,62);
	fprintf(stdout,"10. Ort");
*/

	locate(17,30);
	fprintf(stdout,"0. SLUTA");
	locate(21,10);
	fprintf(stdout,"Uppdatera? <J>/N ");

	locate(19,30);
	fprintf(stdout,"Vilket f\xE4lt v\xE4ljer du? ");
	getrad(rad,MAXRAD);
	svar = rad[0];

/*	fprintf(stderr,"svaret är %c",svar);	*/

	switch (svar){
		case '0':
			status = -1;
			cls();
			break;
		case '1':
			break;
		case '9':
			break;
		default:
			bell();
			break;
	}
	if(status == 0){
 		goto start;
	}
}

int getAdress(char *adr)
{
	char *datastr;
	char *felpek;
	int fds[2];
	int status=-15;
	int i,j,k,l,m;
	char *pos;
	char *pos1;
	char *pos2;
	char ptyp[5]="";	/* posttyp	*/

	pid_t pid;

/*	int dummy;	*/
/*	char rad[3];	*/
	char tmp[MAXSTRING]="";

/*	fprintf(stderr,"getAdress_adr=%s\n",adr);	*/

	pipe(fds);
	pid=fork();

	if (pid == (pid_t) 0) {		/* Child */
		close (fds[0]);
		dup2 (fds[1], STDOUT_FILENO);
		status=execl("STYRMAN", "STYRMAN", userid, "FORDSP", adr, (char *) 0);
/*		fprintf(stderr,"status=%d\n",status);	*/
/*		fprintf(stdout,"Child uppdatering OK? (<J>/N) ");	*/
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
			fprintf(stderr,"FORADMgetAdressParent:Felmeddelande:\n%s\n",felpek-7);
			free(datastr);
			return -1;
		}
		else{
/*			fprintf(stdout,"FORADMgetAdressParent: datstr= %s\n",datastr);	*/
			pos=strstr(datastr,". Status =");
			if (pos != 0){
				status=atoi(strncpy(datastr,pos+11,2));
				fprintf(stdout,"FORADMgetAdress: Status2 = %d\n",status);
			}
			pos=strstr(datastr,"1:ADR");
			if (pos != 0){
				strncpy(tmp,datastr,strlen(datastr));
/*				fprintf(stdout,"FORADMgetAdressParent2:%s\n",tmp);	*/
			}
			free(datastr);
/*			fprintf(stdout,"Parent lista OK? (<J>/N) ");	*/
/*			dummy = getrad(rad,3);	*/
		}
	}
/********************************************************************************/
/*		Selektera ut userdata		      				*/
/* Position 1-2="1:". pos 3-x ="POSTTYP"					*/
/* Sedan kommer "2:" och därefter kommer data som innehåller:			*/
/* Företagsnamn, adress, postnummer, ort åtskilda av " : ".			*/
/********************************************************************************/
/*	fprintf(stdout,"%s\n",tmp);				*/
/*	Plocka ut posttyp					*/
	pos1=strstr(tmp,"ADR");
	pos2=strstr(tmp,"2:");
	i=pos2-pos1;
	k=0;
/*		Hämta posttyp					*/
	for (j=2;j < i; j++){
		ptyp[k]=tmp[j];
		k++;
	}
	l=atoi(&ptyp[3]);
/*	fprintf(stderr,"l=%d\n",l);				*/
/*		Plocka ut data ur den hämtade strängen		*/
	switch (l){
		case 1:
			pos1 = pos2+2;
			pos2 = strstr(pos1,":");
			if (pos2 == NULL)
				return -1;
			i = pos2 - pos1;
			for (j = 0;j < i; j++){
				foretagsnamn[j] = pos1[j];
			}
/*			fprintf(stderr,"företagsnamn=%s\n",foretagsnamn);	*/
			pos1 = pos2+2;
			pos2=strstr(pos1,":");
			i=pos2-pos1;
			for (j = 0;j < i; j++){
				adr1adr[j] = pos1[j];
			}
/*			fprintf(stderr,"adr1adr=%s\n",adr1adr);			*/
			pos1 = pos2+2;
			pos2=strstr(pos1,":");
			i=pos2-pos1;
			for (j = 0;j < i; j++){
				adr1postnr[j] = pos1[j];
			}
/*			fprintf(stderr,"ad1postnr=%s\n",adr1postnr);		*/
			pos1 = pos2+2;
			m=strlen(pos1);
			/* i=pos2-pos1;		*/
			for (j = 0;j < m; j++){
				adr1ort[j] = pos1[j];
			}
/*			fprintf(stderr,"ad1ort=%s\n",adr1ort);			*/
			break;
		case 2:
			pos1 = pos2+2;
			pos2 = strstr(pos1,":");
			if (pos2 == NULL)
				return -1;
			i = pos2 - pos1;
			for (j = 0;j < i; j++){
				foretagsnamn[j] = pos1[j];
			}
			fprintf(stderr,"företagsnamn=%s\n",foretagsnamn);
			pos1 = pos2+2;
			pos2=strstr(pos1,":");
			i=pos2-pos1;
			for (j = 0;j < i; j++){
				adr2adr[j] = pos1[j];
			}
			fprintf(stderr,"adr2adr=%s\n",adr2adr);
			pos1 = pos2+2;
			pos2=strstr(pos1,":");
			i=pos2-pos1;
			for (j = 0;j < i; j++){
				adr2postnr[j] = pos1[j];
			}
			fprintf(stderr,"ad2postnr=%s\n",adr2postnr);
			pos1 = pos2+2;
			m=strlen(pos1);
			if (m < 1)
				return -1;
/*			fprintf(stderr,"m=%d\n",m);		*/
			for (j = 0;j < m; j++){
				adr2ort[j] = pos1[j];
			}
/*			fprintf(stderr,"ad2ort=%s\n",adr2ort);		*/
			break;
		case 3:
			pos1 = pos2+2;
			pos2 = strstr(pos1,":");
			if (pos2 == NULL)
				return -1;
			i = pos2 - pos1;
			for (j = 0;j < i; j++){
				foretagsnamn[j] = pos1[j];
			}
/*			fprintf(stderr,"företagsnamn=%s\n",foretagsnamn);		*/
			pos1 = pos2+2;
			pos2=strstr(pos1,":");
			i=pos2-pos1;
			for (j = 0;j < i; j++){
				adr3adr[j] = pos1[j];
			}
/*			fprintf(stderr,"adr3adr=%s\n",adr3adr);		*/
			pos1 = pos2+2;
			pos2=strstr(pos1,":");
			i=pos2-pos1;
			for (j = 0;j < i; j++){
				adr3postnr[j] = pos1[j];
			}
/*			fprintf(stderr,"adr3postnr=%s\n",adr3postnr);	*/
			pos1 = pos2+2;
			m=strlen(pos1);
			for (j = 0;j < m; j++){
				adr3ort[j] = pos1[j];
			}
/*			fprintf(stderr,"ad3ort=%s\n",adr3ort);		*/
			break;
		default:
			break;
	}

	return 0;
}

int updateForadm(char *rectyp)
{

	char *datastr;
	char *felpek;
	int fds[2];

	pid_t pid;

	int status=0;
	char data[200]="";
	char tmp[]=" : ";
	char adr[6]="";
	static char adr1[]="ADR1";
	static char adr2[]="ADR2";
	static char adr3[]="ADR3";
	char *pos;

	status=trim();
/*	fprintf(stderr,"FORADMupdateFORADM:rectyp=%s\n",rectyp);	*/

	status=strcmp(rectyp,"ADR");
	if (status == 0){
		strncpy(adr,adr1,strlen(adr1));
		strncpy(data,foretagsnamn,strlen(foretagsnamn));
		strncat(data,tmp,strlen(tmp));
		strncat(data,adr1adr,strlen(adr1adr));
		strncat(data,tmp,strlen(tmp));
		strncat(data,adr1postnr,strlen(adr1postnr));
		strncat(data,tmp,strlen(tmp));
		strncat(data,adr1ort,strlen(adr1ort));
/*		fprintf(stderr,"FORADMupdateFORADM:adr=%s data=%s\n",adr,data);	*/
/************************************************/
/*	 Skicka data för ADR1 			*/
/************************************************/
		strncpy(adr,adr1,strlen(adr1));
		pipe(fds);
		pid=fork();

		if (pid == (pid_t) 0) {		/* Child */
			close (fds[0]);
			dup2 (fds[1], STDOUT_FILENO);
			status=execl("STYRMAN", "STYRMAN", userid, "FTGUPD", adr, data, (char *) 0);
/*			fprintf(stderr,"status=%d\n",status);			*/
/*			fprintf(stdout,"Child uppdatering OK? (<J>/N) ");	*/
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
				fprintf(stderr,"FORADMupdateFORADMParent:Felmeddelande:\n%s\n",felpek-7);
				free(datastr);
				return -1;
			}
			else{
/*				fprintf(stdout,"FORADMupdateFORADMParent: datstr= %s\n",datastr);	*/
				pos=strstr(datastr,". Status =");
				if (pos != 0){
					status=atoi(strncpy(datastr,pos+11,2));
					fprintf(stdout,"FORADMupdateFORADM: Status2 = %d\n",status);
				}
				free(datastr);
/*				fprintf(stdout,"Parent lista OK? (<J>/N) ");	*/
			}
		}
		strncpy(adr,adr2,strlen(adr2));
		strncpy(data,foretagsnamn,strlen(foretagsnamn));
		strncat(data,tmp,strlen(tmp));
		strncat(data,adr2adr,strlen(adr2adr));
		strncat(data,tmp,strlen(tmp));
		strncat(data,adr2postnr,strlen(adr2postnr));
		strncat(data,tmp,strlen(tmp));
		strncat(data,adr2ort,strlen(adr2ort));
/*		fprintf(stderr,"FORADMupdateFORADM:adr=%s data=%s\n",adr,data);		*/
/************************************************/
/*	 Skicka data för ADR2 			*/
/************************************************/
		pipe(fds);
		pid=fork();

		if (pid == (pid_t) 0) {		/* Child */
			close (fds[0]);
			dup2 (fds[1], STDOUT_FILENO);
			status=execl("STYRMAN", "STYRMAN", userid, "FTGUPD", adr, data,(char *) 0);
/*			fprintf(stderr,"status=%d\n",status);			*/
/*			fprintf(stdout,"Child uppdatering OK? (<J>/N) ");	*/
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
				fprintf(stderr,"FORADMupdateFORADMParent:Felmeddelande:\n%s\n",felpek-7);
				free(datastr);
				return -1;
			}
			else{
/*				fprintf(stdout,"FORADMupdateFORADMParent: datstr= %s\n",datastr);	*/
				pos=strstr(datastr,". Status =");
				if (pos != 0){
					status=atoi(strncpy(datastr,pos+11,2));
					fprintf(stdout,"FORADMupdateFORADM: Status2 = %d\n",status);
				}
				free(datastr);
/*				fprintf(stdout,"Parent lista OK? (<J>/N) ");	*/
			}
		}

		strncpy(adr,adr3,strlen(adr3));
		strncpy(data,foretagsnamn,strlen(foretagsnamn));
		strncat(data,tmp,strlen(tmp));
		strncat(data,adr3adr,strlen(adr3adr));
		strncat(data,tmp,strlen(tmp));
		strncat(data,adr3postnr,strlen(adr3postnr));
		strncat(data,tmp,strlen(tmp));
		strncat(data,adr3ort,strlen(adr3ort));
/*		fprintf(stderr,"FORADMupdateFORADM:adr3=%s data=%s\n",adr,data);	*/
/************************************************/
/*	 Skicka data för ADR3 			*/
/************************************************/
		pipe(fds);
		pid=fork();

		if (pid == (pid_t) 0) {		/* Child */
			close (fds[0]);
			dup2 (fds[1], STDOUT_FILENO);
			status=execl("STYRMAN", "STYRMAN", userid, "FTGUPD", adr, data, (char *) 0);
/*			fprintf(stderr,"status=%d\n",status);			*/
/*			fprintf(stdout,"Child uppdatering OK? (<J>/N) ");	*/
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
				fprintf(stderr,"FORADMupdateFORADMParent:Felmeddelande:\n%s\n",felpek-7);
				free(datastr);
				return -1;
			}
			else{
/*				fprintf(stdout,"FORADMupdateFORADMParent: datstr= %s\n",datastr);	*/
				pos=strstr(datastr,". Status =");
				if (pos != 0){
					status=atoi(strncpy(datastr,pos+11,2));
					fprintf(stdout,"FORADMupdateFORADM: Status2 = %d\n",status);
				}
				free(datastr);
/*				fprintf(stdout,"Parent lista OK? (<J>/N) ");	*/
			}
		}
	}
/*	exit(0);		*/
	return status;
}


int getBokfPeriod(char *adr)
{
}

void updateBokfPeriod(void)
{
	char rad[2]="";
	int status;
/*	int dummy;	*/
/*	int i;		*/
/*	char tmp[10]="";	*/
	char svar;
	char adr[6]="";
	static char per1[]="BF1";
	static char per2[]="BF2";
	static char per3[]="BF3";
	static char per4[]="BF4";
	static char per5[]="BF5";
	static char per6[]="BF6";
	static char per7[]="BF7";
	static char per8[]="BF8";
	static char per9[]="BF9";
	static char per10[]="BF10";
	static char per11[]="BF11";
	static char per12[]="BF12";
	static char per13[]="BF13";
	static char per14[]="BF14";
	static char per15[]="BF15";

/********************************************************/
/*	Hämta bokföringsperioder frånm databasen	*/
/********************************************************/
/*	status=clearPerioder();		*/
	strncpy(adr,per1,strlen(per1));
	status = getBokfPeriod(adr);
	strncpy(adr,per2,strlen(per2));
	status=getBokfPeriod(adr);
	strncpy(adr,per3,strlen(per3));
	status = getBokfPeriod(adr);
	strncpy(adr,per4,strlen(per4));
	status = getBokfPeriod(adr);
	strncpy(adr,per5,strlen(per5));
	status=getBokfPeriod(adr);
	strncpy(adr,per6,strlen(per6));
	status = getBokfPeriod(adr);
	strncpy(adr,per7,strlen(per7));
	status = getBokfPeriod(adr);
	strncpy(adr,per8,strlen(per8));
	status=getBokfPeriod(adr);
	strncpy(adr,per9,strlen(per9));
	status = getBokfPeriod(adr);
	strncpy(adr,per10,strlen(per10));
	status = getBokfPeriod(adr);
	strncpy(adr,per11,strlen(per11));
	status=getBokfPeriod(adr);
	strncpy(adr,per12,strlen(per12));
	status = getBokfPeriod(adr);
	strncpy(adr,per13,strlen(per13));
	status = getBokfPeriod(adr);
	strncpy(adr,per14,strlen(per14));
	status=getBokfPeriod(adr);
	strncpy(adr,per15,strlen(per15));
	status = getBokfPeriod(adr);

/*	fprintf(stderr,"start\n");	*/
/*start:*/
	status=0;
	cls();
	locate(1,35);
	fprintf(stdout,"*** OLFIX ***");
	locate(1,60);
	fprintf(stdout,"UserID: %s",userid);
	locate(2,25);
	fprintf(stdout,"Företagsdata, Bokföringsperioder");

	locate(4,1);
	fprintf(stdout,"Period 1:");
	locate(4,18);
/*	fprintf(stdout,foretagsnamn);		*/
	locate(5,1);
	fprintf(stdout,"Period 2:");
	locate(6,1);
	fprintf(stdout,"Period 3:");


	locate(17,30);
	fprintf(stdout,"0. SLUTA");

	locate(19,30);
	fprintf(stdout,"Vilket f\xE4lt v\xE4ljer du? ");
	getrad(rad,MAXRAD);
	rad[0]=toupper(rad[0]);
	svar = rad[0];
}

int trim(void){

	int status;
	char *pek;

	pek=foretagsnamn;
	status=unpad(pek);
	pek=adr1adr;
	status=unpad(pek);
	pek=adr1postnr;
	status=unpad(pek);
	pek=adr1ort;
	pek=adr2adr;
	status=unpad(pek);
	pek=adr2postnr;
	status=unpad(pek);
	pek=adr2ort;
	pek=adr3adr;
	status=unpad(pek);
	pek=adr3postnr;
	status=unpad(pek);
	pek=adr3ort;
}

int clearAdresser(void)
{
	int i;

	for (i=0;i<30;i++)
		foretagsnamn[i]=0x00;
	for (i=0;i<30;i++)
		adr1adr[i]=0x00;
	for (i=0;i<9;i++)
		adr1postnr[i]=0x00;
	for (i=0;i<15;i++)
		adr1ort[i]=0x00;
	for (i=0;i<30;i++)
		adr2adr[i]=0x00;
	for (i=0;i<9;i++)
		adr2postnr[i]=0x00;
	for (i=0;i<15;i++)
		adr2ort[i]=0x00;
	for (i=0;i<30;i++)
		adr3adr[i]=0x00;
	for (i=0;i<9;i++)
		adr3postnr[i]=0x00;
	for (i=0;i<15;i++)
		adr3ort[i]=0x00;
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
