/***************************************************************************
                          ARCHGLL.c  -  description
                             -------------------
    Version		 : 0.1
    Modified		 :
    begin                : Tis 18 nov 2003
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
 ***************************************************************************/

/*
	INPUT: artikeldata userid flag transid [databas]
		artikeldataformat=_:_1_:_2345_:_ABC001_:_100_:_001_:_A_:_SEK_:_
		125.50_:_50_:_75_:_50_:_198.00_:_202.50_:_195.00_:_60_:_125_:_26.50_:_

	F?ltavskiljare = _:_

	Function: g?r  UPDATE LAGERSTELLEREG SET (ARLAGHYLLA="ABC001",ARLAGSALDO="100",
	ARINVGRP="001",ARABC="A",ARVALUTA="SEK",ARIPRIS="125.50",
	ARIKVANT0="50",ARIKVANT1="75",ARIKVANT2="50",
	ARKALKPRIS="198.00",ARPLANKPRIS="202.50",ARFRYSTKPRIS="195.00",
	ARBESTKVANT="60",ARBESTPUNKT="125",AROMKOST="26.50")
	WHERE ARTIKELNR"2345" AND ARLAGST="1"

	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/C/Attic/ARCHGL.c,v 1.1 2004/05/03 04:42:57 janpihlgren Exp $ " ;

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "mysql.h"
#define MAXSIZE 200
#define MAXSTRING 1000
#define FORMAT_STR "%Y-%m-%d_%H:%M:%S"
#define FILEPATH 100
#define ANTARG 6
#define ANTFELT 17		/*	Antal datafält i LAGERSTELLEREG	*/

  MYSQL my_connection;
  MYSQL_RES *res_ptr;
  MYSQL_ROW sqlrow;

  int do_TRHD(char *transid, char *tid ,char *userid, char *trnsdata);
  int find_tmp_path(char *envp[]);
  int which_database(char *envp[]);
  void getTime();

  char tid[22]="";
  char database[15]="";
  char *felpek;
  char tmpfilepath[FILEPATH]="";
  char datastr[MAXSTRING]="";

int main(int argc, char *argv[], char *envp[])
{
  int res,status;
  char databas[25]="olfix";
  const char *userp = getenv("USER");	/* vem ?r inloggad?	*/
  char usr[15];				/* userid		*/

  static char *temp1[ANTFELT]={"","","UPDATE LAGERSTELLEREG SET ARLAGHYLLA=\"",
  ",ARLAGSALDO=\"",",ARINVGRP=\"",",ARABC=\"",",ARVALUTA=\"",",ARIPRIS=\"",
  ",ARIKVANT0=\"",",ARIKVANT1=\"",",ARIKVANT2=\"",
  ",ARKALKPRIS=\"",",ARPLANKPRIS=\"",",ARFRYSTKPRIS=\"",
  ",ARBESTKVANT=\"",",ARBESTPUNKT=\"",",AROMKOST=\""};

  char temp1b[]=" WHERE ARTIKELNR = \"";
  char temp1c[]=" AND ARLAGST = \"";
  char temp2[]="\"";
  char temp5[1500]="";
  char artikeldata[2000];
  char artikelnr[31]="";
  char lagerst[2]="";
  char userid[9]="";
  char flag[3]="";
  int flagint;
  char transid[9]="";

  char *pos1;
  char *pos2;
  int tmp,lenght,ant,i,j,k,n;
  if (argv[1] != NULL){
  	strncpy(artikeldata,argv[1],strlen(argv[1]));
  }
  else{
  	fprintf(stderr,"Error: ARCHGL: Data saknas!\n");
	exit(-1);
  }

/*  fprintf(stderr,"argv[1]=%s\n",argv[1]);	*/

  strncpy(userid,argv[2],strlen(argv[2]));
  strncpy(flag,argv[3],strlen(argv[3]));
  strncpy(transid,argv[4],strlen(argv[4]));
/*  fprintf(stderr,"userid=%s flag=%s| transid=%s argc=%d\n",userid,flag,transid,argc);		*/
  flagint=atoi(flag);
/*  fprintf(stderr,"flagint=%d\n",flagint);	*/
  if (flagint==0){
  	status = find_tmp_path(envp);
  	if (status != 0){
		exit(status);
	}
  }
/* ================================================================================ 	*/
/* 		Val av databas, START							*/
/* ================================================================================	*/
  status = which_database(envp);

  if (status != 0)
	exit(status);

  strncpy(usr,userp,15);				// Den inloggades userid

 if (argc<ANTARG){
    	if (strlen(database)!= 0){
		strncpy(databas,database,15);
	}else{
  		strncpy(databas,"olfixtst",15);	// olfixtst = testf?retag
	}
  }else{
	if (strlen(argv[ANTARG]) != 0){
  		if (strncmp(argv[ANTARG],"99",2)==0){
			strncpy(databas,"olfixtst",15);
		}else{
  			strncpy(databas,argv[ANTARG],strlen(argv[ANTARG]));
  		}
  	}
  }
  /* Om usr (userid) b?rjar p? 'test' eller 'prov' anv?nd databas 'olfixtst' */
  if (strncmp(usr,"test",4)==0 || strncmp(usr,"prov",4)==0 ) {
  	strncpy(databas,"olfixtst",15);
  }
/* ================================================================================	*/
/* 		Val av databas, END!							*/
/* ================================================================================	*/


  lenght=strlen(artikeldata);
/*  fprintf(stderr,"lenght=%d\n",lenght);	*/
/*  strncpy(temp5,temp1a,strlen(temp1a));	*/
/*  fprintf(stderr,"artikeldata=%s\n",artikeldata);	*/
  pos1=strstr(artikeldata,"_:_")+3;
  k=3;
  n=0;
  ant=ANTFELT;		/* antal f?lt att uppdatera	*/
  for (i=0;i<ant;i++){
  	for (j=k;j<lenght;j++){
/*		fprintf(stderr,"j=%d\n",j);	*/
  		if (artikeldata[j]== 95 && artikeldata[j+1]== 58 && artikeldata[j+2]== 95){
			j=lenght;
		}
		n=n+1;
  	}
	k=k+(n-1)+3;
	pos2=pos1+3+(n-1);
	tmp=pos2-pos1-3;
	if (i==0){
		strncpy(lagerst,pos1,tmp);
	}
	if (i==1){
		strncpy(artikelnr,pos1,tmp);
	}
	if (i>1){
  		strcat(temp5,temp1[i]);
  		strncat(temp5,pos1,tmp);
  		strncat(temp5,temp2,strlen(temp2));
	}
	pos1=pos2;
/*	fprintf(stderr,"i=%d, k=%d, n=%d, tmp=%d\n",i,k,n,tmp);	*/
	n=0;
/*	fprintf(stderr,"temp5 = %s\n",temp5);			*/
  }
  strncat(temp5,temp1b,strlen(temp1b));
  strncat(temp5,artikelnr,strlen(artikelnr));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp1c,strlen(temp1c));
  strncat(temp5,lagerst,strlen(lagerst));
  strncat(temp5,temp2,strlen(temp2));

/* fprintf(stderr,"ARCHGL: temp5 = %s\n",temp5);		*/
/* exit(0);						*/


  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
/*  	fprintf(stderr,"ARCHGL:Connection success\n");		*/

  res = mysql_query(&my_connection,temp5);

  if (!res){
   	if ((unsigned long)mysql_affected_rows(&my_connection) > 0){
 		fprintf(stdout,"OK: ARCHGL Updated %lu rows\n",
			(unsigned long)mysql_affected_rows(&my_connection));
	}else{
		fprintf(stdout,"Error: ARCHGL Updated %lu rows\n",
		(unsigned long)mysql_affected_rows(&my_connection));
	}
  }else{
	fprintf(stderr,"Error: ARCHGL UPDATE error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
  }
	mysql_close(&my_connection);
 }else {
	fprintf(stderr,"Error: ARCHGL Connection failed\n");
 	if (mysql_errno(&my_connection))   {
 		fprintf(stderr,"Error: ARCHGL Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
	}
  }
 	fprintf(stdout,"\n");
	if (flagint==0){
		getTime();		/* Hämta systemtid	*/
		status=do_TRHD(transid, tid ,userid, artikeldata);
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
/*			fprintf(stderr,"temp=%s\n",temp);		*/
			status=strcmp(temp,"HOME");
/*			fprintf(stderr,"status=%d\n",status);		*/
			if (status == 0){
				home_pek=(strstr(envp[i],"HOME="));
				home_pek=home_pek+5;
				strcpy(home,home_pek);
			}
/*			fprintf(stderr,"home_pek=%d %s\n",home_pek,home_pek);	*/
/*			fprintf(stderr,"home_pek=%d %s\n",home_pek,home_pek);	*/
		}
	}
/*	fprintf(stderr,"home=%s\n",home);				*/
	strcpy(filename,home);
	strncat(filename,resource,strlen(resource));

/*	fprintf(stderr,"filename=%s\n",filename);			*/
	status=-1;

	if ((fil_pek = fopen(filename,"r")) != NULL){
		while (fgets(tmp,150,fil_pek) != NULL){
/*			fprintf(stderr,"tmp=%s\n",tmp);			*/
			if(strstr(tmp,"DATABASE=")){
				tmp_pek=(strstr(tmp,"DATABASE="))+9;
				strncpy(database,tmp_pek,strlen(tmp_pek));
				status=0;
			}
		}
/*		fprintf(stderr,"database=%s_len=%d\n",database,strlen(database));	*/
		fclose(fil_pek);
	}
	else{
	 	fprintf(stderr,"Error: Filen .olfixrc kan inte ?ppnas\n");
	}
	for (i=0;i < strlen(database);i++){
		tmp[i]=database[i];
	}
	tmp[i-1]=0;
/*	fprintf(stderr,"tmp=%s, i=%d len tmp=%d\n",tmp,i,strlen(tmp));			*/
	strncpy(database,tmp,strlen(tmp));
	database[strlen(tmp)]=0;

	return status;
}


int do_TRHD(char *transid, char *tid ,char *userid, char *trnsdata)
{
	int i;
	int status=-15;
	int fds[2];
	char tmp[FILEPATH]="";
	char func[FILEPATH]="";
	char trhd[]="TRHDADD";

  	i=strlen(tmpfilepath);
  	strncpy(tmp,tmpfilepath,i-1);
  	strncat(tmp,trhd,strlen(trhd));
  	strncpy(func,tmp,strlen(tmp));
/*	fprintf(stderr,"func=%s\n",func);		*/
	pid_t pid;

	pipe(fds);
	pid =fork();
        if (pid == (pid_t) 0) {		/* Child */
		close (fds[0]);
		dup2 (fds[1], STDERR_FILENO);
		status=execl(func, func, transid, tid, userid, trnsdata, (char *) 0);
 }
	else{				/* Parent (Denna process) */
		FILE* stream;
		close (fds[1]);
		stream = fdopen (fds[0],"r");

		status = fread(datastr,MAXSTRING,MAXSTRING,stream);
		fflush (stream);
		close (fds[0]);
		waitpid (pid, NULL,0);
		felpek=strstr(datastr,"Error:");	/* Error: */
		if (felpek !=NULL){
/*			fprintf(stderr,"%s\n",felpek);		*/
			return -1;
		}
		else{
/*			fprintf(stdout,"%s\n",&datastr);	*/ /* returnera data till anropande program. */
			return 0;
		}
	}
	return 0;
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
	 	fprintf(stderr,"Error: Filen .olfixrc kan inte Öppnas\n");
	}
	return status;
}

void getTime()
{
  time_t t;
  struct tm *tm_t;
  char *str;
  t = time(NULL);
  tm_t = localtime(&t);

  str = malloc(MAXSIZE + 1);
  strftime(str, 25, FORMAT_STR, tm_t);
  strncpy(tid,str,20);
  free(str);
/*  fprintf(stderr,"tid nr 5= %s\n",tid);	*/
  return;
}
