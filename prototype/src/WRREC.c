/***************************************************************************
                          WRREC.c  -  description
                             -------------------
			     version 0.04
    begin                : Sön 10 aug 2003
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

/****************************************************************************
	INPUT: posttyp bar vernr radnr ktonr dk belopp kst subkto datum userid vertext
		eller
	       posttyp bar vernr radnr ktonr dk belopp kst subkto


	Function: Skapa filen /tmp/vernr.txt

	OUTPUT: filen /tmp/vernr.txt
 *****************************************************************************/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/WRREC.c,v 1.4 2003/11/11 08:26:04 janpihlgren Exp $ " ;

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define POSTSIZE 178		// lika med post

int which_database(char *envp[]);
int find_tmp_path(char *envp[]);
int reg_post(char *rec,char *vrnr,char *typpek);

char tmpfilepath[50]="";
char database[15]="";

int main (int argc, char *argv[], char *envp[])
{
	int i;
	int status=0;
	char posttyp[2]="";
	char *typpek;
	char bar[3]="";
	char vernr[9]="";
	char *vrnrpek;
	char radnr[4]="";
	char ktonr[5]="";
	char dk[2]="";
	char belopp[13]="";
	char kst[5]="";
	char subkto[5]="";

	char datum[11]="";
	char userid[9]="";
	char vertext[101]="";

	char filler1[11]="";
	char filler2[9]="";
	char filler3[101]="";

	char post[POSTSIZE]="";
	char *recpek;

	status = find_tmp_path(envp);
/*	fprintf(stderr,"status=%d tmp path=%s\n",status,tmpfilepath);		*/
/*	exit(0);		*/
	if (status != 0)
		exit(status);

	if (argc < 10){
		fprintf(stderr,"Error: För få argument till WRREC!\n");
		exit (-1);
	}
/*	for (i=0;i<argc;i++){		*/
/*		fprintf(stderr,"argv[%d]=%s\n",i,argv[i]);			*/
/*	}				*/
	recpek=post;
	typpek=posttyp;
	vrnrpek=vernr;

	strncpy(filler1," ",1);
	for ( i = 0; i < sizeof(filler1)-1 ; i++){
		strncat(filler1," ",1);
	}
	strncpy(filler2," ",1);
	for ( i = 0; i < sizeof(filler2)-1; i++){
		strncat(filler2," ",1);
	}
	strncpy(filler3," ",1);
	for ( i = 0; i < sizeof(filler3)-1; i++){
		strncat(filler3," ",1);
	}

	strncpy(posttyp,argv[1],strlen(argv[1]));
	strncpy(bar,argv[2],strlen(argv[2]));
	strncpy(vernr,argv[3],strlen(argv[3]));
	strncpy(radnr,argv[4],strlen(argv[4]));
	strncpy(ktonr,argv[5],strlen(argv[5]));
	strncpy(dk,argv[6],strlen(argv[6]));
	strncpy(belopp,argv[7],strlen(argv[7]));
	strncpy(kst,argv[8],strlen(argv[8]));
	strncpy(subkto,argv[9],strlen(argv[9]));

	if (argc == 10){
		strncpy(datum,filler1,strlen(filler1));
		strncpy(userid,filler2,strlen(filler2));
		strncpy(vertext,filler3,strlen(filler3));
	}else{
		strncpy(datum,argv[10],strlen(argv[10]));
		strncpy(userid,argv[11],strlen(argv[11]));
		strncpy(vertext,argv[12],strlen(argv[12]));
	}
	for (i = 0; i < sizeof(post); i++){
		strncat(recpek+i," ",1);
	}

	strncpy(post,posttyp,strlen(posttyp));
	strncat(post," ",1);
	strncat(post,bar,strlen(bar));
	strncat(post," ",1);
	strncat(post,vernr,strlen(vernr));
	strncat(post," ",1);
	strncat(post,radnr,strlen(radnr));
	strncat(post," ",1);
	strncat(post,ktonr,strlen(ktonr));
	strncat(post," ",1);
	strncat(post,dk,strlen(dk));
	strncat(post," ",1);
	strncat(post,belopp,strlen(belopp));
	strncat(post," ",1);
	strncat(post,kst,strlen(kst));
	strncat(post," ",1);
	strncat(post,subkto,strlen(subkto));
	strncat(post," ",1);
	strncat(post,datum,strlen(datum));
	strncat(post," ",1);
	strncat(post,userid,strlen(userid));
	strncat(post," ",1);
	strncat(post,vertext,strlen(vertext));
/*	fprintf(stderr,"post=%s\n",post);	*/
/*	exit(0);				*/
	status=reg_post(recpek,vrnrpek,typpek);
	return status;
}

int reg_post(char *rec,char *vrnr,char *typpek)
{
/********************************************************/
/* Om posttyp = H så är det en huvupost			*/
/* Om posttyp = D så är det en detaljpost		*/
/********************************************************/
	FILE *fil_pek;

	int status;
/*	char path[]="/tmp/";		*/
	char ext[]=".txt";
	char filnamn[23]="";
/*	char tmp[46]=" ";		*/

	char post[POSTSIZE+1]="";
	char *postpek;

	int i;

	postpek=post;

	for (i = 0;i < sizeof(post); i++){
		strcpy(postpek+i,rec+i);
	}
	strncpy(filnamn,tmpfilepath,strlen(tmpfilepath));
	if (strlen(vrnr) == 0){
		strncat(filnamn,"fel_fil",7);
	}else{
		strncat(filnamn,vrnr,strlen(vrnr));
	}
	strncat(filnamn,ext,strlen(ext));

/*	fprintf(stderr,"posttyp=%s\n",typpek);		*/
/*	fprintf(stderr,"postlengd=%d\n",strlen(post));	*/
	for (i=strlen(post);i< sizeof(post)-2;i++)
		strncat(post," ",1);
/*	fprintf(stderr,"filnamn=%s\n",filnamn);		*/
/*	strcat(post,":");				*/
	strncat(post,"\n",1);

	if (typpek == "H"){
		fil_pek = fopen(filnamn,"w");
	}else{
		fil_pek = fopen(filnamn,"a");
	}

	status = fwrite(post,POSTSIZE,1,fil_pek);
/*	fprintf(stderr,"post=%s\n",post);		*/
	fclose(fil_pek);
/*	fprintf(stderr,"status=%d\n",status);		*/
	return status;
}

int find_tmp_path(char *envp[])
{
	FILE *fil_pek;

/*	char home[]="$HOME";				*/
	char home[50]="";
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
/*			fprintf(stderr,"temp=%s\n",temp);	*/
			status=strcmp(temp,"HOME");
/*			fprintf(stderr,"status=%d\n",status);	*/
			if (status == 0){
				home_pek=(strstr(envp[i],"HOME="));
				home_pek=home_pek+5;
				strcpy(home,home_pek);
			}
/*			fprintf(stderr,"home_pek=%d %s\n",home_pek,home_pek);		*/
/*			fprintf(stderr,"home_pek=%d %s\n",home_pek,home_pek);		*/
		}
	}
/*	fprintf(stderr,"home=%s\n",home);			*/
	strncpy(filename,home,strlen(home));
	strncat(filename,resource,strlen(resource));

/*	fprintf(stderr,"filename=%s\n",filename);		*/
	status=-1;

	if ((fil_pek = fopen(filename,"r")) != NULL){
		while (fgets(tmp,50,fil_pek) != NULL){
/*			fprintf(stderr,"tmp=%s\n",tmp);		*/
			if(strstr(tmp,"VTMP=")){
				tmp_pek=(strstr(tmp,"VTMP="))+5;
				strncpy(tmpfilepath,tmp_pek,strlen(tmp_pek));
				status=0;
			}
		}
/*		fprintf(stderr,"tmpfilepath=%s\n",tmpfilepath);		*/
		fclose(fil_pek);
	}
	else{
	 	fprintf(stderr,"Error: Filen .olfixrc kan inte öppnas\n");
	}
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
