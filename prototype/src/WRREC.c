/***************************************************************************
                          WRREC.c  -  description
                             -------------------
			     version 0.02
    begin                : Tis 25 mars 2003
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
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/WRREC.c,v 1.1 2003/05/08 08:54:14 frazze Exp $ " ;

#include <string.h>
#include <stdio.h>
#define POSTSIZE 178		// lika med post


int find_tmp_path(char *envp[]);
int reg_post(char *rec,char *vrnr,char *typpek);

char tmpfilepath[50];

int main (int argc, char *argv[], char *envp[])
{
	int i;
	int status=0;
	char posttyp[2];
	char *typpek;
	char bar[3];
	char vernr[9];
	char *vrnrpek;
	char radnr[4];
	char ktonr[5];
	char dk[2];
	char belopp[13];
	char kst[5];
	char subkto[5];

	char datum[11];
	char userid[9];
	char vertext[101];

	char filler1[11];
	char filler2[9];
	char filler3[101];

	char post[POSTSIZE];
	char *recpek;

	status = find_tmp_path(envp);
//	fprintf(stderr,"status=%d tmp path=%s\n",status,tmpfilepath);
//	exit(0);

	if (argc < 10){
		fprintf(stderr,"Error: För få argument till WRREC!\n");
		exit (-1);
	}
//	for (i=0;i<argc;i++){
//		fprintf(stderr,"argv[%d]=%s\n",i,argv[i]);
//	}
	recpek=post;
	typpek=posttyp;
	vrnrpek=vernr;

	strcpy(filler1," ");
	for ( i = 0; i < sizeof(filler1)-1 ; i++){
		strcat(filler1," ");
	}
	strcpy(filler2," ");
	for ( i = 0; i < sizeof(filler2)-1; i++){
		strcat(filler2," ");
	}
	strcpy(filler3," ");
	for ( i = 0; i < sizeof(filler3)-1; i++){
		strcat(filler3," ");
	}

	strcpy(posttyp,argv[1]);
	strcpy(bar,argv[2]);
	strcpy(vernr,argv[3]);
	strcpy(radnr,argv[4]);
	strcpy(ktonr,argv[5]);
	strcpy(dk,argv[6]);
	strcpy(belopp,argv[7]);
	strcpy(kst,argv[8]);
	strcpy(subkto,argv[9]);

	if (argc == 10){
		strcpy(datum,filler1);
		strcpy(userid,filler2);
		strcpy(vertext,filler3);
	}else{
		strcpy(datum,argv[10]);
		strcpy(userid,argv[11]);
		strcpy(vertext,argv[12]);
	}
	for (i = 0; i < sizeof(post); i++){
		strcat(recpek+i," ");
	}

	strcpy(post,posttyp);
	strcat(post," ");
	strcat(post,bar);
	strcat(post," ");
	strcat(post,vernr);
	strcat(post," ");
	strcat(post,radnr);
	strcat(post," ");
	strcat(post,ktonr);
	strcat(post," ");
	strcat(post,dk);
	strcat(post," ");
	strcat(post,belopp);
	strcat(post," ");
	strcat(post,kst);
	strcat(post," ");
	strcat(post,subkto);
	strcat(post," ");
	strcat(post,datum);
	strcat(post," ");
	strcat(post,userid);
	strcat(post," ");
	strcat(post,vertext);
//	fprintf(stderr,"post=%s\n",post);
//	exit(0);
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
//	char path[]="/tmp/";
	char ext[]=".txt";
	char filnamn[23]="";
	char tmp[46]=" ";

	char post[POSTSIZE+1]="";
	char *postpek;

	int i;

	postpek=post;

	for (i = 0;i < sizeof(post); i++){
		strcpy(postpek+i,rec+i);
	}
	strcpy(filnamn,tmpfilepath);
	if (strlen(vrnr) == 0){
		strcat(filnamn,"fel_fil");
	}else{
		strcat(filnamn,vrnr);
	}
	strcat(filnamn,ext);

//	fprintf(stderr,"posttyp=%s\n",typpek);
//	fprintf(stderr,"postlengd=%d\n",strlen(post));
	for (i=strlen(post);i< sizeof(post)-2;i++)
		strcat(post," ");
//	fprintf(stderr,"filnamn=%s\n",filnamn);
//	strcat(post,":");
	strcat(post,"\n");

	if (typpek == "H"){
		fil_pek = fopen(filnamn,"w");
	}else{
		fil_pek = fopen(filnamn,"a");
	}

	status = fwrite(post,POSTSIZE,1,fil_pek);
//	fprintf(stderr,"post=%s\n",post);
	fclose(fil_pek);
//	fprintf(stderr,"status=%d\n",status);
	return status;
}

int find_tmp_path(char *envp[])
{
	FILE *fil_pek;

//	char home[]="$HOME";
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

	fil_pek = fopen(filename,"r");
	while (fgets(tmp,50,fil_pek) != NULL){
//		fprintf(stderr,"tmp=%s\n",tmp);
		if(strstr(tmp,"VTMP=")){
			tmp_pek=(strstr(tmp,"VTMP="))+5;
			strcpy(tmpfilepath,tmp_pek);
			status=0;
		}
	}
//	fprintf(stderr,"tmpfilepath=%s\n",tmpfilepath);
	fclose(fil_pek);
	return status;
}
