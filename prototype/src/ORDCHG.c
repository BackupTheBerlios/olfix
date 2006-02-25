/***************************************************************************
                          ORDCHG.c  -  description
                             -------------------
			     Uppdatera/Ändra ORDERREG från kundorder.
			     Orderhuvud.
    Version		 : 0.1
    begin                : Lör  25 febr  2006
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
	INPUT: oderhuvuddata databas
	_:_1_:_Nya Test AB_:_Provgatan 2_:_199 99_:_LILLEBY_:_Sverige _:_
	Karl Andersson_:_Bokhållargatan 3_:_199 19_:_LILLEBY_:_Sverige_:_
	Lars Seller_:_2005-03-15_:_25_:_SEK_:_1 _:_001 _:_002 _:_Godsmärke_:_
	5117.00_:_90.00_:_22.50_:_1279.52_:_6509.02_:_END

Fältavskiljare = _:_

	Function: gör

	UPDATE ORDERREG SET KUNDNAMN="Nya Test AB
	", KUNDADRESS="Provgatan 2
	", KUNDPOSTNR="199 99
	", KUNDPOSTADR="LILLEBY
	", KUNDLAND="Sverige
	", ERREF="Karl Andersson
	", LEVADRESS="Bokhållargatan 3
	", LEVPOSTNR="199 19
	", LEVPOSTADR="LILLEBY
	", LEVLAND="Sverige
	", SELJARE="Lars Seller
	", LEVDATUM="2006-02-15
	", MOMS="25
	", VALUTA="SEK
	", BETVILLKOR="1
	", LEVVILLKOR="001
	", LEVSETT="002
	", GODSMERKE="Godsmärke
	", ORDERSUMMA="5117.00
	", FRAKTSUMMA="90.00
	", FRAKTMOMSKR="22.50
	", ORDERMOMS="1279.52
	", ORDERTOTAL="6509.02
	" WHERE ORDERNR="1"
	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/ORDCHG.c,v 1.1 2006/02/25 07:44:46 janpihlgren Exp $ " ;

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql.h"
#define ANTARG 2
#define ANTFELT 24

  MYSQL my_connection;
  MYSQL_RES *res_ptr;
  MYSQL_ROW sqlrow;

  int which_database(char *envp[]);
  char database[15]="";

int main(int argc, char *argv[], char *envp[])
{
  int res,status;
  char databas[25]="olfix";
  const char *userp = getenv("USER");	// vem är inloggad?
  char usr[15];				// userid

  char temp1a[]="UPDATE ORDERREG SET KUNDNAMN=\"";
  char temp1b[]="\", KUNDADRESS=\"";
  char temp1c[]="\", KUNDPOSTNR=\"";
  char temp1d[]="\", KUNDPOSTADR=\"";
  char temp1e[]="\", KUNDLAND=\"";
  char temp1f[]="\", ERREF=\"";
  char temp1g[]="\", LEVADRESS=\"";
  char temp1h[]="\", LEVPOSTNR=\"";
  char temp1i[]="\", LEVPOSTADR=\"";
  char temp1j[]="\", LEVLAND=\"";
  char temp1k[]="\", SELJARE=\"";
  char temp1l[]="\", LEVDATUM=\"";
  char temp1m[]="\", MOMS=\"";
  char temp1n[]="\", VALUTA=\"";
  char temp1o[]="\", BETVILLKOR=\"";
  char temp1p[]="\", LEVVILLKOR=\"";
  char temp1q[]="\", LEVSETT=\"";
  char temp1r[]="\", GODSMERKE=\"";
  char temp1s[]="\", ORDERSUMMA=\"";
  char temp1t[]="\", FRAKTSUMMA=\"";
  char temp1u[]="\", FRAKTMOMSKR=\"";
  char temp1v[]="\", ORDERMOMS=\"";
  char temp1w[]="\", ORDERTOTAL=\"";
  char temp1x[]="\" WHERE ORDERNR=\"";

  char temp2[]="\"";
  char temp5[1500]="";
  char kundorderdata[2000]="";

  char *pos1;
  char *pos2;
  int tmp,lenght,ant,i,j,k,n;

  char ordernr[11]="";
/*  char knamn[61]="";
  char kadress[31]="";
  char kpostnr[7]="";
  char kpostadr[31]="";
  char kland[31]="";
  char kerref[31]="";
  char levadress[31]="";
  char levpostnr[7]="";
  char levpostadr[31]="";
  char levland[31]="";
  char seljare[21]="";
  char levdatum[11]="";
  char moms[7]="";
  char valuta[4]="";
  char betvillkor[4]="";
  char levvillkor[4]="";
  char levsett[4]="";
  char godsmerke[101]="";
  char ordersumma[13]="";
  char fraktsumma[13]="";
  char fraktmomskr[13]="";
  char ordermoms[13]="";
  char ordertotal[13]="";
*/

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
  } /* fprintf(stderr,"Databas=%s\n",databas);	*/

/* ================================================================================ */
/* 		Val av databas, END!						    */
/* ================================================================================ */

  if (argv[1] != NULL){
  	strncpy(kundorderdata,argv[1],sizeof(kundorderdata));	/* 2005-02-23	*/
  }
  else{
  	fprintf(stderr,"Error: ORDCHG: Ange kundordernummer!\n");
	exit(-1);
  }


  lenght=strlen(kundorderdata);
/*  fprintf(stderr,"lenght=%d\n",lenght);	*/
  strncpy(temp5,temp1a,strlen(temp1a));
/*  fprintf(stderr,"kundorderdata=%s\n",kundorderdata);	*/
  pos1=strstr(kundorderdata,"_:_")+3;
  k=3;
  n=0;
  ant=ANTFELT;					/* antal fält	*/
  for (i=0;i<ant;i++){
  	for (j=k;j<lenght;j++){
/*		fprintf(stderr,"j=%d\n",j);	*/
  		if (kundorderdata[j]== 95 && kundorderdata[j+1]== 58 && kundorderdata[j+2]== 95){
			j=lenght;
		}
		n=n+1;
  	}
	k=k+(n-1)+3;

	pos2=pos1+3+(n-1);

	tmp=pos2-pos1-3;
//  	strncat(temp5,temp2,strlen(temp2));
//  	strncat(temp5,pos1,tmp);
        if (i == 0){
		strncpy(ordernr,pos1,tmp);
//		fprintf(stderr,"ordernr=%s\n",ordernr);
	}
        if (i == 1){
		strncat(temp5,pos1,tmp);		/* kundnamn*/
//		strncpy(knamn,pos1,tmp);
	}
	if (i == 2){
		strncat(temp5,temp1b,sizeof temp1b);
		strncat(temp5,pos1,tmp);		/* kundadress*/
	}
	if (i == 3){
		strncat(temp5,temp1c,sizeof temp1c);
		strncat(temp5,pos1,tmp);		/* kundpostnr*/
	}
	if (i == 4){
		strncat(temp5,temp1d,sizeof temp1d);
		strncat(temp5,pos1,tmp);		/* kundpostadr*/
	}
	if (i == 5){
		strncat(temp5,temp1e,sizeof temp1e);
		strncat(temp5,pos1,tmp);		/* kundland*/
	}
	if (i == 6){
		strncat(temp5,temp1f,sizeof temp1f);
		strncat(temp5,pos1,tmp);		/* erref*/
	}
	if (i == 7){
		strncat(temp5,temp1g,sizeof temp1g);
		strncat(temp5,pos1,tmp);		/* levadress*/
	}
	if (i == 8){
		strncat(temp5,temp1h,sizeof temp1h);
		strncat(temp5,pos1,tmp);		/* levpostnr*/
	}
	if (i == 9){
		strncat(temp5,temp1i,sizeof temp1i);
		strncat(temp5,pos1,tmp);		/* levpostadr*/
	}
	if (i == 10){
		strncat(temp5,temp1j,sizeof temp1j);
		strncat(temp5,pos1,tmp);		/* levland*/
	}
	if (i == 11){
		strncat(temp5,temp1k,sizeof temp1k);
		strncat(temp5,pos1,tmp);		/* seljare*/
	}
	if (i == 12){
		strncat(temp5,temp1l,sizeof temp1l);
		strncat(temp5,pos1,tmp);		/* levdatum*/
	}
	if (i == 13){
		strncat(temp5,temp1m,sizeof temp1m);
		strncat(temp5,pos1,tmp);		/* moms*/
	}
	if (i == 14){
		strncat(temp5,temp1n,sizeof temp1n);
		strncat(temp5,pos1,tmp);		/* valuta*/
	}
	if (i == 15){
		strncat(temp5,temp1o,sizeof temp1o);
		strncat(temp5,pos1,tmp);		/* betvillkor*/
	}
	if (i == 16){
		strncat(temp5,temp1p,sizeof temp1p);
		strncat(temp5,pos1,tmp);		/* levvillkor*/
	}
	if (i == 17){
		strncat(temp5,temp1q,sizeof temp1q);
		strncat(temp5,pos1,tmp);		/* levsett*/
	}
	if (i == 18){
		strncat(temp5,temp1r,sizeof temp1r);
		strncat(temp5,pos1,tmp);		/* godsmärke*/
	}
	if (i == 19){
		strncat(temp5,temp1s,sizeof temp1s);
		strncat(temp5,pos1,tmp);		/* ordersumma*/
	}
	if (i == 20){
		strncat(temp5,temp1t,sizeof temp1t);
		strncat(temp5,pos1,tmp);		/* fraktsumma*/
	}
	if (i == 21){
		strncat(temp5,temp1u,sizeof temp1u);
		strncat(temp5,pos1,tmp);		/* fraktmoms*/
	}
	if (i == 22){
		strncat(temp5,temp1v,sizeof temp1v);
		strncat(temp5,pos1,tmp);		/* ordermoms*/
	}
	if (i == 23){
		strncat(temp5,temp1w,sizeof temp1w);
		strncat(temp5,pos1,tmp);		/* ordertotal*/
	}

	pos1=pos2;
//	fprintf(stderr,"i=%d, k=%d, n=%d, tmp=%d\n",i,k,n,tmp);	
	n=0;
//	fprintf(stderr,"temp5[%d] = %s\n",i,temp5);	
  }
  strncat(temp5,temp1x,sizeof temp1x);
  strncat(temp5,ordernr,sizeof ordernr);
  strncat(temp5,temp2,sizeof temp2);

// fprintf(stderr,"\nORDCHG: temp5 = %s\n\n",temp5);
// exit(0);


  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
/*  	fprintf(stderr,"ORDCHG:Connection success\n");	*/

  res = mysql_query(&my_connection,temp5);

  if (!res){
 	fprintf(stdout,"OK: ORDCHG Inserted %lu rows\n",
		(unsigned long)mysql_affected_rows(&my_connection));
        }else{
	fprintf(stderr,"Error: ORDCHG INSERT error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
	}
	mysql_close(&my_connection);
 }else {
	fprintf(stderr,"Error: ORDCHG Connection failed\n");
 	if (mysql_errno(&my_connection))   {
 		fprintf(stderr,"Error: ORDCHG Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
	}
  }
 	fprintf(stdout,"\n");
  return EXIT_SUCCESS;
}

int which_database(char *envp[])
{
	FILE *fil_pek;

//	char home[]="$HOME";
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

	if ((fil_pek = fopen(filename,"r")) != NULL){
		while (fgets(tmp,150,fil_pek) != NULL){
//			fprintf(stderr,"tmp=%s\n",tmp);
			if(strstr(tmp,"DATABASE=")){
				tmp_pek=(strstr(tmp,"DATABASE="))+9;
				strncpy(database,tmp_pek,strlen(tmp_pek));
				status=0;
			}
		}
//		fprintf(stderr,"database=%s_len=%d\n",database,strlen(database));
		fclose(fil_pek);
	}
	else{
	 	fprintf(stderr,"Error: Filen .olfixrc kan inte öppnas\n");
	}
	for (i=0;i < strlen(database);i++){
		tmp[i]=database[i];
	}
	tmp[i-1]=0;
//	fprintf(stderr,"tmp=%s, i=%d len tmp=%d\n",tmp,i,strlen(tmp));
	strncpy(database,tmp,strlen(tmp));
	database[strlen(tmp)]=0;

	return status;
}
