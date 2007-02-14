/***************************************************************************
                          KRESUPD.c  -  description
                             -------------------
    Version		 : 0.2
    begin                : Ons 14 dec  2005
    modified		 : Ons 14 febr 2007
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
 *********************************************** ****************************/

/*
	INPUT: FAKTURANR antpost data

	Kommando: ./KRESUPD "100004 ; 990.50 ; 4335 ; 2005-08-11 ; 316491 ; 2005-09-11 ; AF ; 102 ;
	 1911 ; 990.50 ; 1511 ; 990.50 ;END"

	( fakturanummer;belopp;kundnur;fakturadatum;ordernr;betaldatum;bokföringsår;vernr;
	debetkto;debetbelopp;kreditkto;kreditbelopp;END)

	Function: Uppdatera tabellen KURESK

	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/KRESUPD.c,v 1.2 2007/02/14 14:56:28 janpihlgren Exp $ " ;

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "mysql.h"

#define FORMAT_STR "%Y-%m-%d_%H:%M:%S"    /* YYYY-MM-DD */
#define MAXSIZE 20
#define MAXSTRING 5000
#define TEXTSIZE 500
#define ANTARG 3
#define ANTFELT 13

  MYSQL my_connection;
  MYSQL_RES *res_ptr;
  MYSQL_ROW sqlrow;

int which_database(char *envp[]);
char database[15]="";

int main(int argc, char *argv[], char *envp[])
{
  int res;
  int status;
  int flag=-1;
  int i,l,j,k,n,m;
  int anttecken;
  char *pos1;

  const char *userp = getenv("USER");	/* vem är inloggad?	*/
  char databas[25]="olfix";
  char usr[21]="";			/* userid 20070214 utökat från 15 till 21 tecken */

  char temp1a[]="UPDATE KURESK SET BETALD = \"J\" , BETALDATUM = \"";
//  char temp1b[]=" , BETALDATUM = \"";
  char temp1c[]=" , BETALTBELOPP = \"";
  char temp1d[]=" , BAR = \"";
  char temp1e[]=" , VERNR = \"";
  char temp2a[]=" WHERE FAKTURANR = \"";
  char temp3[]="\"";
  char temp5[TEXTSIZE]="";

  int antalposter;
  char data[MAXSTRING]="";			/* data, radinformation		*/

  char fakturanr[21]="";
  char belopp[14]="";
  char ordernr[11]="";
  char kundnr[11]="";
  char fakturadatum[11]="";
/*  char betald[2]="";	*/
  char betaldatum[11]="";
/*  char betaltbelopp[14]="";	*/
  char bar[3]="";
  char vernr[12]="";
/*  char ktonr[5]="";	*/
  char temp[5]="";

  status=-15;
/* ================================================================================ */
/* 		Val av databas, START						    */
/* ================================================================================ */

  status = which_database(envp);

  if (status != 0)
	exit(status);

  strncpy(usr,userp,sizeof(usr));			/* Den inloggades userid 20070214 */
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
/*  fprintf(stderr,"ANTARG=%d,argv[ANTARG]=%s\n",ANTARG,argv[ANTARG]);	*/
/* Om usr (userid) börjar på 'test' eller 'prov' använd databas 'olfixtst' */
  if (strncmp(usr,"test",4)==0 || strncmp(usr,"prov",4)==0 ) {
  	strncpy(databas,"olfixtst",15);
  }
/* fprintf(stderr,"Databas=%s\n",databas);		*/
/* ================================================================================ */
/* 		Val av databas, END!						    */
/* ================================================================================ */
  strncpy(temp,argv[1],sizeof(temp));
/*  fprintf(stderr,"temp=%s\n",temp);		*/
  antalposter=atoi(temp);
/*  fprintf(stderr,"antalposter=%d\n",antalposter);	*/
/*  fprintf(stderr,"argc=%d argv[0]=%s argv[1]=%s argv[2]=%s \n",argc,argv[0],argv[1],argv[2]);		*/
  strncpy(data,argv[2],sizeof(data));
/*  fprintf(stderr,"data=%s\n",data);	*/
  l=strlen(data);
/*  fprintf(stderr,"l=%d\n",l);		*/
//	exit(0);
  pos1=strstr(data,";");
  k=2;
  n=1;
  m=0;
  for(i=0;i<antalposter;i++){
/*  	fprintf(stderr,"n=%d\n",n);	*/
	for (j=n;j<l;j++){
		if(data[j] == 59){
			anttecken=j-n;
			strncpy(fakturanr,pos1+n,anttecken);
/*			fprintf(stderr,"1.  fakturanr=%s j=%d n=%d anttecken=%d\n",fakturanr,j,n,anttecken);	*/
			n=j+1;
			m=j;
			j=l;
		}
	}
/*	fprintf(stderr,"n=%d\n",n);	*/
	for (j=n;j<l;j++){
		if(data[j] == 59){
			anttecken=j-n;
			strncpy(belopp,pos1+n,anttecken);
/*			fprintf(stderr,"2.  belopp=%s j=%d n=%d anttecken=%d\n",belopp,j,n,anttecken);	*/
			n=j+1;
			m=j;
			j=l;
		}
	}
/*	fprintf(stderr,"n=%d\n",n);	*/
	for (j=n;j<l;j++){
		if(data[j] == 59){
			anttecken=j-n;
			strncpy(kundnr,pos1+n,anttecken);
/*			fprintf(stderr,"3.  kundnr=%s j=%d n=%d anttecken=%d\n",kundnr,j,n,anttecken);	*/
			n=j+1;
			m=j;
			j=l;
		}
	}
	for (j=n;j<l;j++){
		if(data[j] == 59){
			anttecken=j-n;
			strncpy(fakturadatum,pos1+n,anttecken);
/*			fprintf(stderr,"3.  fakturadatum=%s j=%d n=%d anttecken=%d\n",fakturadatum,j,n,anttecken);	*/
			n=j+1;
			m=j;
			j=l;
		}
	}
	for (j=n;j<l;j++){
		if(data[j] == 59){
			anttecken=j-n;
			strncpy(ordernr,pos1+n,anttecken);
/*			fprintf(stderr,"3.  ordernr=%s j=%d n=%d anttecken=%d\n",ordernr,j,n,anttecken);	*/
			n=j+1;
			m=j;
			j=l;
		}
	}
	for (j=n;j<l;j++){
		if(data[j] == 59){
			anttecken=j-n;
			strncpy(betaldatum,pos1+n,anttecken);
/*			fprintf(stderr,"3.  betaldatum=%s j=%d n=%d anttecken=%d\n",betaldatum,j,n,anttecken);	*/
			n=j+1;
			m=j;
			j=l;
		}
	}
	for (j=n;j<l;j++){
		if(data[j] == 59){
			anttecken=j-n;
			strncpy(bar,pos1+n,anttecken);
/*			fprintf(stderr,"3.  bar=%s j=%d n=%d anttecken=%d\n",bar,j,n,anttecken);	*/
			n=j+1;
			m=j;
			j=l;
		}
	}
	for (j=n;j<l;j++){
		if(data[j] == 59){
			anttecken=j-n;
			strncpy(vernr,pos1+n,anttecken);
/*			fprintf(stderr,"3.  ver=%s j=%d n=%d anttecken=%d\n",vernr,j,n,anttecken);	*/
			n=j+1;
			m=j;
			j=l;
		}
	}

	strncpy(temp5,temp1a,sizeof(temp1a));
/*  UPDATE KURESK SET BETALD = "N" , BETALDATUM = "  */
  	strncat(temp5,betaldatum,sizeof(betaldatum));
  	strncat(temp5,temp3,sizeof(temp3));
/*  UPDATE KURESK SET BETALD = "N" , BETALDATUM = "2005-08-11"    */
  	strncat(temp5,temp1c,sizeof(temp1c));
/*  UPDATE KURESK SET BETALD = "N" , BETALDATUM = "2005-08-11" , BETALTBELOPP = " */
        strncat(temp5,belopp,sizeof(belopp));
	strncat(temp5,temp3,sizeof(temp3));
/*  UPDATE KURESK SET BETALD = "N" , BETALDATUM = "2005-08-11" , BETALTBELOPP = "990.50" */
  	strncat (temp5,temp1d,sizeof(temp1d));
/*  UPDATE KURESK SET BETALD = "N" , BETALDATUM = "2005-08-11" , BETALTBELOPP = "990.50", BAR = "  */
  	strncat(temp5,bar,sizeof(bar));
  	strncat(temp5,temp3,sizeof(temp3));
/*  UPDATE KURESK SET BETALD = "N" , BETALDATUM = "2005-08-11" , BETALTBELOPP = "990.50", BAR = "AF"  */
  	strncat(temp5,temp1e,sizeof(temp1e));
/*  UPDATE KURESK SET BETALD = "N" , BETALDATUM = "2005-08-11" , BETALTBELOPP = "990.50", BAR = "AF" , VERNR = " */
  	strncat(temp5,vernr,sizeof(vernr));
  	strncat(temp5,temp3,sizeof(temp3));
/*  UPDATE KURESK SET BETALD = "N" , BETALDATUM = "2005-08-11" , BETALTBELOPP = "990.50", BAR = "AF" , VERNR = "102" */
	strncat(temp5,temp2a,sizeof(temp2a));
/*  UPDATE KURESK SET BETALD = "N" , BETALDATUM = "2005-08-11" , BETALTBELOPP = "990.50", BAR = "AF" , VERNR = "102"  WHERE FAKTURANR = "*/
  	strncat(temp5,fakturanr,sizeof(fakturanr));
  	strncat(temp5,temp3,sizeof(temp3));
/*  UPDATE KURESK SET BETALD = "N" , BETALDATUM = "2005-08-11" , BETALTBELOPP = "990.50", BAR = "AF" , VERNR = "102"  WHERE FAKTURANR = "100004" */

/* 	fprintf(stderr,"KRESUPDmain: temp5=%s\n",temp5);	*/
	i=i+4;

	mysql_init(&my_connection);

  	if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
/*    fprintf(stderr,"KRESUPD:Connection success\n");	*/
    		res = mysql_query(&my_connection,temp5);
  		if (!res){
			if ((unsigned long)mysql_affected_rows(&my_connection) < 1){
				fprintf(stderr,"Error: KRESUPD Updated %lu rows\n",(unsigned long)mysql_affected_rows(&my_connection));
				flag=0;
			}else{
				flag=-1;
//				fprintf(stderr,"OK: KRESUPD Updated %lu rows\n",
//				(unsigned long)mysql_affected_rows(&my_connection));
			}
        	}else{
			fprintf(stderr,"Error: KRESUPD UPDATE error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
		}
		mysql_close(&my_connection);
 	} else {
		fprintf(stderr,"Error: KRESUPD Connection failed\n");
    		if (mysql_errno(&my_connection))   {
    			fprintf(stderr,"Error: KRESUPD Connection error %d:  %s\n",
				mysql_errno(&my_connection), mysql_error(&my_connection));
		}
    	}
    }
    if(flag==-1){
	fprintf(stdout,"OK: KRESUPD Updated %d poster\n",antalposter);
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

