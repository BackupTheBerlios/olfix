/***************************************************************************
                          LEVADD.c  -  description
                             -------------------
    Version		 : 0.3
    begin                : Mån 30 juni 2003
    modified		 : Tors 6 nov 2003
    copyright            : (C) 2003 by Jan Pihlgren
    email                : jan@pihlgren.se
 ***************************************************************************/
/*	Modifierad 2003-06-30: Lagt till VALUTA				   */
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

/*
	INPUT: LEVNR, LEVORGNR, LEVNAMN, LEVADRESS, LEVPOSTNR, LEVPOSTADR, LEVLAND, LEVTFNNR, LEVFAXNR, LEVTELEX, LEVEMAIL, LEVPOSTGIRONER, LEVBANKGIRONR, LEVREFERENT, LEVREFTFN, LEVMOMSKOD, LEVKONTO LEVKUNDNR VALUTA BETALVILKOR

	Function: gör  INSERT INTO LEVREG(LEVNR,LEVORGNR,LEVNAMN,LEVADRESS,LEVPOSTNR,LEVPOSTADR,LEVLAND,LEVTFNNR,LEVFAXNR,LEVTELEX,LEVEMAIL,LEVPOSTGIRONR,LEVBANKGIRONR,LEVREFERENT,LEVREFTFN,LEVMOMSKOD,LEVSKULD,LEVKONTO, LEVKUNDNR, LEVVALUTA, BETALVILKOR) VALUES ("2345","559999-9999","Leverantör AB","Postgatan 33","199 99","DATABY","SVERIGE","09-999999","09-999998","99999","kundtj@leverantor.se","4559999-9","5999-9999","Per Josefsson","09-999997","1","0.00","2110","12345678","SEK","1")i databasen olfix

	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/C/Attic/LEVADD.c,v 1.1 2004/05/03 04:42:57 janpihlgren Exp $ " ;

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql.h"
#define ANTARG 21

  MYSQL my_connection;
  MYSQL_RES *res_ptr;
  MYSQL_ROW sqlrow;

int which_database(char *envp[]);
void display_row();

char database[15]="";

int main(int argc, char *argv[], char *envp[])
{
  int res;
/* int i;
   for (i=0;i<argc;i++){
	fprintf(stderr,"argv[%d]=%s\n",i,argv[i]);
   }
*/
  int status;
  const char *userp = getenv("USER");	/* vem är inloggad?	*/
  char databas[25]="olfix";
  char usr[15];				/* userid		*/

  char temp1a[]="INSERT INTO LEVREG(LEVNR,LEVORGNR,LEVNAMN,LEVADRESS,LEVPOSTNR,LEVPOSTADR,LEVLAND,LEVTFNNR,LEVFAXNR,LEVTELEX,LEVEMAIL,LEVPOSTGIRONR,LEVBANKGIRONR,LEVREFERENT,LEVREFTFN,LEVMOMSKOD,LEVSKULD,LEVKONTO,LEVKUNDNR,LEVVALUTA,BETALVILKOR) VALUES (";
  char temp2[]="\"";
  char temp3[]=",";
  char temp4[]=")";
  char temp5[1500]="";
  char levnr[11]="";		/* nr 1		*/
  char levorgnr[13]="";		/* nr 2		*/
  char levnamn[31]="";		/* nr 3		*/
  char levadr[31]="";		/* nr 4		*/
  char levpostnr[7]="";		/* nr 5		*/
  char levpostadr[31]="";	/* nr 6		*/
  char levland[31]="";		/* nr 7		*/
  char levtfnnr[16]="";		/* nr 8		*/
  char levfaxnr[16]="";		/* nr 9		*/
  char levtelex[11]="";		/* nr 10	*/
  char levemail[31]="";		/* nr 11	*/
  char levpostgironr[11]="";	/* nr 12	*/
  char levbankgironr[11]="";	/* nr 13	*/
  char levref[21]="";		/* nr 14	*/
  char levreftfn[16]="";	/* nr 15	*/
  char levmomskod[2]="";	/* nr 16	*/
  char levskuld[]="0.00";	/*		*/
  char levkonto[5]="";		/* nr 17	*/
  char levkundnr[31]="";	/* nr 18	*/
  char levvaluta[4]="";		/* nr 19	*/
  char betalvilkor[4]="";	/* nr 20	*/

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
/* fprintf(stderr,"Databas=%s\n",databas);	*/
/* ================================================================================ */
/* 		Val av databas, END!						    */
/* ================================================================================ */


  if (argv[1] != NULL){
  	strncpy(levnr,argv[1],strlen(argv[1]));
  }
  else{
  	fprintf(stderr,"Error: LEVADD: Ange kundnummer!\n");
	exit(-1);
  }

  strncpy(levorgnr,argv[2],strlen(argv[2]));
  strncpy(levnamn,argv[3],strlen(argv[3]));
  strncpy(levadr,argv[4],strlen(argv[4]));
  strncpy(levpostnr,argv[5],strlen(argv[5]));
  strncpy(levpostadr,argv[6],strlen(argv[6]));
  strncpy(levland,argv[7],strlen(argv[7]));
  strncpy(levtfnnr,argv[8],strlen(argv[8]));
  strncpy(levfaxnr,argv[9],strlen(argv[9]));
  strncpy(levtelex,argv[10],strlen(argv[10]));
  strncpy(levemail,argv[11],strlen(argv[11]));
  strncpy(levpostgironr,argv[12],strlen(argv[12]));
  strncpy(levbankgironr,argv[13],strlen(argv[13]));
  strncpy(levref,argv[14],strlen(argv[14]));
  strncpy(levreftfn,argv[15],strlen(argv[15]));
  strncpy(levmomskod,argv[16],strlen(argv[16]));
  strncpy(levkonto,argv[17],strlen(argv[17]));
  strncpy(levkundnr,argv[18],strlen(argv[18]));
  strncpy(levvaluta,argv[19],strlen(argv[19]));
  strncpy(betalvilkor,argv[20],strlen(argv[20]));
  strncpy(temp5,temp1a,strlen(temp1a));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,levnr,strlen(levnr));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,levorgnr,strlen(levorgnr));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,levnamn,strlen(levnamn));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,levadr,strlen(levadr));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,levpostnr,strlen(levpostnr));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,levpostadr,strlen(levpostadr));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,levland,strlen(levland));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,levtfnnr,strlen(levtfnnr));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,levfaxnr,strlen(levfaxnr));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,levtelex,strlen(levtelex));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,levemail,strlen(levemail));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,levpostgironr,strlen(levpostgironr));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,levbankgironr,strlen(levbankgironr));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,levref,strlen(levref));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,levreftfn,strlen(levreftfn));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,levmomskod,strlen(levmomskod));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,levskuld,strlen(levskuld));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,levkonto,strlen(levkonto));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,levkundnr,strlen(levkundnr));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,levvaluta,strlen(levvaluta));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,betalvilkor,strlen(betalvilkor));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp4,strlen(temp4));
  /* INSERT INTO LEVREG(LEVNR,LEVORGNR,LEVNAMN,LEVADRESS,LEVPOSTNR,LEVPOSTADR,LEVLAND,LEVTFNNR,LEVFAXNR,LEVTELEX,LEVEMAIL,LEVPOSTGIRONR,LEVBANKGIRONR,LEVREFERENT,LEVREFTFN,LEVMOMSKOD,LEVSKULD,LEVKONTO,LEVKUNDNR,LEVVALUTA,BETALVILKOR) VALUES ("2345","559999-9999","Leverantör AB","Postgatan 33","199 99","DATABY","SVERIGE","09-999999","09-999998","99999","kundtj@leverantor.se","4559999-9","5999-9999","Per Josefsson","09-999997","1","0.00","2110","12345678","SEK","1") */

/* fprintf(stderr,"LEVADD: temp5 = %s\n",temp5);	*/

  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
/*  	fprintf(stderr,"LEVADD:Connection success\n");	*/

  res = mysql_query(&my_connection,temp5);

  if (!res){
 	fprintf(stdout,"OK: LEVADD Inserted %lu rows\n",
		(unsigned long)mysql_affected_rows(&my_connection));
        }else{
	fprintf(stderr,"Error: LEVADD INSERT error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
	}
	mysql_close(&my_connection);
 }else {
	fprintf(stderr,"Error: LEVADD Connection failed\n");
 	if (mysql_errno(&my_connection))   {
 		fprintf(stderr,"Error: LEVADD Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
	}
  }
 	fprintf(stdout,"\n");
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
