/***************************************************************************
                          PRTAPI.c  -  description
                             -------------------
			     version 0.3
    begin                : Lör 3 april 2004
    modified		 : Ons 19 jan 2005
    copyright            : (C) 2004 by Jan Pihlgren
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

/****************************************************************************
	INPUT: csvflag printfil [prttemplate]
	(csvflag flagga "J" eller "N". cvs = kommaseparerad fil)

	Function: Anropa Kugar eller Kspread med parametrar om var datafilen finns

	OUTPUT:
 *****************************************************************************/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/PRTAPI.c,v 1.3 2005/01/19 12:15:45 janpihlgren Exp $ " ;

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int find_tmp_path(char *envp[]);
int ReportPath(char *envp[]);
int KugarVersion();

char tmpfilepath[50]="";
char reportpath[50]="";
char kugarversion[10]="";

int main (int argc, char *argv[], char *envp[])
{
/*	int i;		*/
	int status=0;
	char csvflag[2]="";
	char printfil[50]="";
	char prttemplate[50]="";
	char temp[50]="";
	char command[100]="";
	char command_c[]="kspread ";
	char command_d[]="kugar -d ";
	char command_e[]=" -r ";

/*	fprintf(stderr,"argc=%d\n",argc);				*/

/*	for (i=0;i<argc;i++){
		fprintf(stderr,"argv[%d]=%s\n",i,argv[i]);
	}
*/
	if (argc < 3){
		fprintf(stderr,"Error: För få argument till PRTAPI!\n");
		exit (-1);
	}

	status = find_tmp_path(envp);
	if (status != 0)
		exit(status);
	status = ReportPath(envp);
	if (status != 0)
		exit(status);

	strncpy(csvflag,argv[1],strlen(argv[1]));
	strncpy(printfil,argv[2],strlen(argv[2]));
	if (argc>3){
		strncpy(prttemplate,argv[3],strlen(argv[3]));
	}
	strncpy(temp,tmpfilepath,strlen(tmpfilepath));
	strncat(temp,printfil,strlen(printfil));
/*	fprintf(stderr,"cvs=%s, printfil=%s, prttemplate=%s,temp=%s\n",csvflag,printfil,prttemplate,temp);	*/
	status=KugarVersion();
	if (status != 0)
		exit(status);

/*	fprintf(stderr,"csvflag=%s\n",csvflag);		*/
	if(strcmp(csvflag,"J")==0){
		strncpy(command,command_c,strlen(command_c));
		strncat(command,tmpfilepath,strlen(tmpfilepath));
		strncat(command,printfil,strlen(printfil));
/*	fprintf(stderr,"printfil=%s tmpfilepath=%s command=%s\n",printfil,tmpfilepath,command);	*/
	}else{
/*		fprintf(stderr,"kugarversion=%s, len=%d\n",kugarversion,strlen(kugarversion));		*/
		if (strcmp(kugarversion,"1.2.92")<0){
			strncpy(command,command_d,strlen(command_d));
			strncat(command,tmpfilepath,strlen(tmpfilepath));
			strncat(command,printfil,strlen(printfil));
			strncat(command,command_e,strlen(command_e));
			strncat(command,reportpath,strlen(reportpath));
			strncat(command,prttemplate,strlen(prttemplate));
			/* EX: kugar -d /tmp/Saldolista.txt -r /opt/olfix/report/Saldolista.kut		*/
		}else{
			strcpy(command,"kugar ");
			strncat(command,tmpfilepath,strlen(tmpfilepath)-1);
			strncat(command,printfil,strlen(printfil));
		}
	}
/*	fprintf(stderr,"command_3=%s\n",command);	*/
	system(command);
	return status;
}

int find_tmp_path(char *envp[])
{
	FILE *fil_pek;

	char home[50]="";
	char *home_pek;
	char resource[]="/.olfixrc";
	char filename[50]="";
	char tmp[50]="";
	char tmp2[50]="";
	char temp[10]="";
	char *tmp_pek;
	int i,j,status;

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
/*				strncpy(tmpfilepath,tmp_pek,strlen(tmp_pek));		*/
				strcpy(tmpfilepath,tmp_pek);
				status=0;
			}
		}
/*		fprintf(stderr,"tmpfilepath=%s\n",tmpfilepath);		*/
		fclose(fil_pek);
	}
	else{
	 	fprintf(stderr,"Error: Filen .olfixrc kan inte öppnas\n");
	}
	j=strlen(tmpfilepath);
/*	fprintf(stderr,"tmpfilepath=%s j=%d\n",tmpfilepath,j);	*/
	if (strchr(tmpfilepath,10)){
		strncpy(tmp2,tmpfilepath,j-1);
		strcpy(tmpfilepath,tmp2);
/*		j=strlen(tmpfilepath);					*/
/*		fprintf(stderr,"tmpfilepath=%s j=%d\n",tmpfilepath,j);	*/
	}
	return status;
}

int KugarVersion()
{
	int status=-1;
	char command[50]="";
	char command_a[]="kugar -v >";
	char command_b[]="kugarversion.txt";
	char filnamn[50]="";
	char tmp[50]="";
	char *tmp_pek;
	FILE *fil_pek;

	strncpy(command,command_a,strlen(command_a));
	strncat(command,tmpfilepath,strlen(tmpfilepath));
	strncat(command,command_b,strlen(command_b));
/*	fprintf(stderr,"command_1=%s\n",command);		*/
	system(command);

	strncpy(filnamn,tmpfilepath,strlen(tmpfilepath));
	strncat(filnamn,command_b,strlen(command_b));

/*	Ex: kugar -v /tmp/kugarverssion.txt	*/
/*	fprintf(stderr,"command_2=%s\n",command);	*/

	if ((fil_pek = fopen(filnamn,"r")) != NULL){
		while (fgets(tmp,50,fil_pek) != NULL){
/*			fprintf(stderr,"tmp=%s\n",tmp);		*/
			if(strstr(tmp,"Kugar:")){
				tmp_pek=(strstr(tmp,"Kugar:"))+7;
				strcpy(kugarversion,tmp_pek);
				status=0;
			}
		}
/*		fprintf(stderr,"kugarversion=%s\n",kugarversion);		*/
		fclose(fil_pek);
	}
	else{
	 	fprintf(stderr,"Error: Filen %skugarversion.txt kan inte öppnas\n",tmpfilepath);
	}
	return status;
}

int ReportPath(char *envp[])
{
	FILE *fil_pek;

	char home[50]="";
	char *home_pek;
	char resource[]="/.olfixrc";
	char filename[50]="";
	char tmp[50]="";
	char temppath[50]="";
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
			if(strstr(tmp,"REPORT=")){
				tmp_pek=(strstr(tmp,"REPORT="))+7;
/*				strncpy(tmpfilepath,tmp_pek,strlen(tmp_pek));		*/
				strcpy(temppath,tmp_pek);
				status=0;
			}
		}
/*		fprintf(stderr,"reportpath=%s\n",reportpath);		*/
		fclose(fil_pek);
	}
	else{
	 	fprintf(stderr,"Error: Filen .olfixrc kan inte öppnas\n");
	}
	strncpy(reportpath,temppath,strlen(temppath)-1);
	return status;
}
