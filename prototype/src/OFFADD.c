/***************************************************************************
                          OFFADD.c  -  description
                             -------------------
			     Uppdatera OFFERTREG med kundoffert.
			     Offerthuvud.
    Version		 : 0.4.3
    begin                : L�r  22 april  2006
    Modified		 :
    copyright            : (C) 2006 by Jan Pihlgren
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
	INPUT: offerthuvuddata databas
	_:_1_:_0_:_2005-03-12_:_4376_:_Nya Test AB _:_Provgatan 2 _:_199 99 _:_LILLEBY _:_Sverige _:_
	Karl Andersson _:_Bokh�llargatan 3 _:_199 19 _:_LILLEBY _:_Sverige _:_
	Lars Seller_:_2005-03-15_:_25_:_SEK_:_1 _:_001 _:_002 _:_Godsm�rke_:_
	5117.00_:_90.00_:_22.50_:_1279.52_:_6509.02_:_END

F�ltavskiljare = _:_
Ordernr alltid 0

	Function: g�r
	INSERT INTO OFFERTREG (OFFERTNR,ORDERNR,ORDERDATUM,KUNDNR,KUNDNAMN,KUNDADRESS,KUNDPOSTNR,KUNDPOSTADR,KUNDLAND, 	  ERREF,LEVADRESS,LEVPOSTNR,LEVPOSTADR,LEVLAND, SELJARE,LEVDATUM,MOMS,VALUTA,BETVILLKOR,LEVVILLKOR,LEVSETT,GODSMERKE,  ORDERSUMMA,FRAKTSUMMA,FRAKTMOMSKR,ORDERMOMS,ORDERTOTAL) VALUES
	(1,0,"2005-03-12","4376","Nya Test AB","Provgatan 2","199 99","LILLEBY","Sverige",
	"Karl Andersson","Bokh�llargatan 3","199 19","LILLEBY","Sverige",
	"Lars Seller","2005-03-15","25","SEK","1","001","002","Godsm�rke",
	"5117.00","90.00","22.50","1279.52","6509.02") i databasen olfix

	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/OFFADD.c,v 1.1 2006/04/26 04:30:29 janpihlgren Exp $ " ;

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql.h"
#define ANTARG 2
#define ANTFELT 27

  MYSQL my_connection;
  MYSQL_RES *res_ptr;
  MYSQL_ROW sqlrow;

  int which_database(char *envp[]);
  char database[15]="";

int main(int argc, char *argv[], char *envp[])
{
  int res,status;
  char databas[25]="olfix";
  const char *userp = getenv("USER");	// vem �r inloggad?
  char usr[15];				// userid

  char temp1a[]="INSERT INTO OFFERTREG (OFFERTNR,ORDERNR,ORDERDATUM,KUNDNR,KUNDNAMN,KUNDADRESS,KUNDPOSTNR,KUNDPOSTADR,KUNDLAND,ERREF,LEVADRESS,LEVPOSTNR,LEVPOSTADR,LEVLAND,SELJARE,LEVDATUM,MOMS,VALUTA,BETVILLKOR,LEVVILLKOR,LEVSETT,GODSMERKE,ORDERSUMMA,FRAKTSUMMA,FRAKTMOMSKR,ORDERMOMS,ORDERTOTAL) VALUES (";
  char temp2[]="\"";
  char temp3[]=",";
  char temp4[]=")";
  char temp5[1500]="";
  char offertdata[2000]="";

  char *pos1;
  char *pos2;
  int tmp,lenght,ant,i,j,k,n;

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
  		strncpy(databas,"olfixtst",15);	/* olfixtst = testf�retag	*/
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
/* Om usr (userid) b�rjar p� 'test' eller 'prov' anv�nd databas 'olfixtst' */
  if (strncmp(usr,"test",4)==0 || strncmp(usr,"prov",4)==0 ) {
  	strncpy(databas,"olfixtst",15);
  } /* fprintf(stderr,"Databas=%s\n",databas);	*/

/* ================================================================================ */
/* 		Val av databas, END!						    */
/* ================================================================================ */

  if (argv[1] != NULL){
  	strncpy(offertdata,argv[1],sizeof(offertdata));	
  }
  else{
  	fprintf(stderr,"Error: OFFADD: Ange kundordernummer!\n");
	exit(-1);
  }


  lenght=strlen(offertdata);
/*  fprintf(stderr,"lenght=%d\n",lenght);	*/
  strncpy(temp5,temp1a,strlen(temp1a));
/*  fprintf(stderr,"offertdata=%s\n",offertdata);	*/
  pos1=strstr(offertdata,"_:_")+3;
  k=3;
  n=0;
  ant=ANTFELT;		/* antal f�lt	*/
  for (i=0;i<ant;i++){
  	for (j=k;j<lenght;j++){
/*		fprintf(stderr,"j=%d\n",j);	*/
  		if (offertdata[j]== 95 && offertdata[j+1]== 58 && offertdata[j+2]== 95){
			j=lenght;
		}
		n=n+1;
  	}
	k=k+(n-1)+3;

	pos2=pos1+3+(n-1);

	tmp=pos2-pos1-3;
  	strncat(temp5,temp2,strlen(temp2));
  	strncat(temp5,pos1,tmp);
  	strncat(temp5,temp2,strlen(temp2));
	if (i<(ant-1)){
  		strncat(temp5,temp3,strlen(temp3));
	}
	pos1=pos2;
/*	fprintf(stderr,"i=%d, k=%d, n=%d, tmp=%d\n",i,k,n,tmp);	*/
	n=0;
/*	fprintf(stderr,"temp5 = %s\n",temp5);	*/
  }
  strncat(temp5,temp4,strlen(temp4));

 //fprintf(stderr,"\nOFFADD: temp5 = %s\n\n",temp5);
 //exit(0);


  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){

  res = mysql_query(&my_connection,temp5);

  if (!res){
 	fprintf(stdout,"OK: OFFADD Inserted %lu rows\n",
		(unsigned long)mysql_affected_rows(&my_connection));
        }else{
	fprintf(stderr,"Error: OFFADD INSERT error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
	}
	mysql_close(&my_connection);
 }else {
	fprintf(stderr,"Error: OFFADD Connection failed\n");
 	if (mysql_errno(&my_connection))   {
 		fprintf(stderr,"Error: OFFADD Connection error %d:  %s\n",
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
		while (fgets(tmp,150,fil_pek) != NULL){
			if(strstr(tmp,"DATABASE=")){
				tmp_pek=(strstr(tmp,"DATABASE="))+9;
				strncpy(database,tmp_pek,strlen(tmp_pek));
				status=0;
			}
		}
		fclose(fil_pek);
	}
	else{
	 	fprintf(stderr,"Error: Filen .olfixrc kan inte �ppnas\n");
	}
	for (i=0;i < strlen(database);i++){
		tmp[i]=database[i];
	}
	tmp[i-1]=0;
	strncpy(database,tmp,strlen(tmp));
	database[strlen(tmp)]=0;

	return status;
}
