/***************************************************************************
                          LRESADD.c  -  description
                             -------------------
    Version		 : 0.4
    begin                : Sön 10 aug 2003
    modified		 : Fre  7 nov 2003
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
	INPUT: LEVNR, FAKTURANR, REGDATUM, FAKTDATUM, EXPIREDATUM, FAKTTEXT, BAR, MOMSPROCENT, LEVKTONR, FAKTBELOPP, MOMSKTONR, MOMSBELOPP, KREDITKONTONR, KREDITBELOPP, USERID VALUTA VALUTAKURS VALUTABELOPP OCRNR VERNR

	Function: gör  INSERT INTO LEVRESK(LEVNR, FAKTURANR, REGDATUM, FAKTDATUM, EXPIREDATUM, FAKTTEXT, BAR, MOMSPROCENT, LEVKTONR, FAKTBELOPP, MOMSKTONR, MOMSBELOPP, KREDITKONTONR, KREDITBELOPP, USERID, VALUTA, VALUTAKURS, VALUTABELOPP,OCRNR) VALUES ("123","1239955","2003-06-24","2003-06-17","2003-07-17","Inköp av skrivbord","AC","25","2110","2500.00","1470","625.00","1810","1875.00","JAN","EUR","9.08","22700","9660000032831","00000021")i databasen olfix

	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/LRESADD.c,v 1.2 2003/11/07 06:23:42 janpihlgren Exp $ " ;

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
  int status;
  const char *userp = getenv("USER");	/* vem är inloggad?	*/
  char databas[25]="olfix";
  char usr[15];				/* userid		*/

/*	int i;
	for (i=0;i<argc;i++){
	fprintf(stderr,"argv[%d]=%s\n",i,argv[i]);
	}
*/
  char temp1a[]="INSERT INTO LEVRESK(LEVNR, FAKTURANR, REGDATUM, FAKTDATUM, EXPIREDATUM, FAKTTEXT, BAR, MOMSPROCENT, LEVKTONR, FAKTBELOPP, MOMSKTONR, MOMSBELOPP, DEBETKONTONR, DEBETBELOPP, USERID,VALUTA,VALUTAKURS,VALUTABELOPP,OCRNR,VERNR) VALUES (";
  char temp2[]="\"";
  char temp3[]=",";
  char temp4[]=")";
  char temp5[500]="";
  char levnr[11]="";		/* nr 1		*/
  char fakturanr[21]="";	/* nr 2		*/
  char regdatum[11]="";		/* nr 3		*/
  char faktdatum[11]="";	/* nr 4		*/
  char expiredatum[11]="";	/* nr 5		*/
  char fakttext[101]="";	/* nr 6		*/
  char bar[3]="";		/* nr 7		*/
  char momsprocent[8]="";	/* nr 8		*/
  char levkontonr[5]="";	/* nr 9		*/
  char faktbelopp[14]="";	/* nr 10	*/
  char momsktonr[5]="";		/* nr 11	*/
  char momsbelopp[14]="";	/* nr 12	*/
  char debetktonr[5]="";	/* nr 13	*/
  char debetbelopp[14]="";	/* nr 14	*/
  char userid[9]="";		/* nr 15	*/
  char valuta[4]="";		/* nr 16	*/
  char valutakurs[6]="";	/* nr 17	*/
  char valutabelopp[14]="";	/* nr 18	*/
  char ocrnr[21]="";		/* nr 19	*/
  char vernr[9]="";		/* nr 20	*/

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
  	fprintf(stderr,"Error: LRESADD: Ange leverantörsnummer!\n");
	exit(-1);
  }

  if (argv[2] != NULL){
  	strncpy(fakturanr,argv[2],strlen(argv[2]));
  }
  else{
  	fprintf(stderr,"Error: LRESADD: Ange fakturanummer!\n");
	exit(-1);
  }

  strncpy(regdatum,argv[3],strlen(argv[3]));
  strncpy(faktdatum,argv[4],strlen(argv[4]));
  strncpy(expiredatum,argv[5],strlen(argv[5]));
  strncpy(fakttext,argv[6],strlen(argv[6]));
  strncpy(bar,argv[7],strlen(argv[7]));
  strncpy(momsprocent,argv[8],strlen(argv[8]));
  strncpy(levkontonr,argv[9],strlen(argv[9]));
  strncpy(faktbelopp,argv[10],strlen(argv[10]));
  strncpy(momsktonr,argv[11],strlen(argv[11]));
  strncpy(momsbelopp,argv[12],strlen(argv[12]));
  strncpy(debetktonr,argv[13],strlen(argv[13]));
  strncpy(debetbelopp,argv[14],strlen(argv[14]));
  strncpy(userid,argv[15],strlen(argv[15]));
  strncpy(valuta,argv[16],strlen(argv[16]));
  strncpy(valutakurs,argv[17],strlen(argv[17]));
  strncpy(valutabelopp,argv[18],strlen(argv[18]));
  strncpy(ocrnr,argv[19],strlen(argv[19]));
  strncpy(vernr,argv[20],strlen(argv[20]));

  strncpy(temp5,temp1a,strlen(temp1a));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,levnr,strlen(levnr));			/* 1	*/
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,fakturanr,strlen(fakturanr));		/* 2	*/
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,regdatum,strlen(regdatum));		/* 3	*/
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,faktdatum,strlen(faktdatum));		/* 4	*/
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,expiredatum,strlen(expiredatum));	/* 5	*/
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,fakttext,strlen(fakttext));		/* 6	*/
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,bar,strlen(bar));			/* 7	*/
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,momsprocent,strlen(momsprocent));	/* 8	*/
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,levkontonr,strlen(levkontonr));		/* 9	*/
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,faktbelopp,strlen(faktbelopp));		/* 10	*/
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,momsktonr,strlen(momsktonr));		/* 11	*/
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,momsbelopp,strlen(momsbelopp));		/* 12	*/
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,debetktonr,strlen(debetktonr));		/* 13	*/
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,debetbelopp,strlen(debetbelopp));	/* 14	*/
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,userid,strlen(userid));			/* 15	*/
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,valuta,strlen(valuta));			/* 16	*/
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,valutakurs,strlen(valutakurs));		/* 17	*/
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,valutabelopp,strlen(valutabelopp));	/* 18	*/
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,ocrnr,strlen(ocrnr));			/* 19	*/
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp3,strlen(temp3));
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,vernr,strlen(vernr));			/* 20	*/
  strncat(temp5,temp2,strlen(temp2));
  strncat(temp5,temp4,strlen(temp4));

  /* INSERT INTO LEVRESK(LEVNR, FAKTURANR, REGDATUM, FAKTDATUM, EXPIREDATUM, FAKTTEXT, BAR, MOMSPROCENT, LEVKTONR, FAKTBELOPP, MOMSKTONR, MOMSBELOPP, KREDITKONTONR, KREDITBELOPP, USERID,VALUTA,VALUTAKURS,VALUTABELOPP) VALUES ("123","1239955","2003-06-24","2003-06-17","2003-07-17","Inköp av skrivbord","AC","25","2110","2500.00","1470","625.00","1810","1875.00","JAN","EUR","9.08","22700.00","9660000032831","00000021")) */

/*  fprintf(stderr,"LRESADD: temp5 = %s\n",temp5);	*/
/*  exit (0);	*/
  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
/*  	fprintf(stderr,"LRESADD:Connection success\n");		*/

  res = mysql_query(&my_connection,temp5);

  if (!res){
 	fprintf(stdout,"OK: LRESADD Inserted %lu rows\n",
		(unsigned long)mysql_affected_rows(&my_connection));
        }else{
	fprintf(stderr,"Error: LRESADD INSERT error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
	}
	mysql_close(&my_connection);
 }else {
	fprintf(stderr,"Error: LRESADD Connection failed\n");
 	if (mysql_errno(&my_connection))   {
 		fprintf(stderr,"Error: LRESADD Connection error %d:  %s\n",
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
