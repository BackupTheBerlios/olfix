/***************************************************************************
                          KUCHG.c  -  description
                             -------------------
    Version		 : 0.1
    begin                : Lör 4 okt 2003
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
	INPUT: kunddata
		format=_:_4376_:_Test AB_:_Provgatan 2_:_199 99_:_LILLEBY_:_Sverige_:_
		09-999990_:_09-999999_:_info@test.se_:_Karl Andersson _:_09-999991_:_
		karl.a@test.se_:_Caroline Seljare_:_KalmarSoftware_:_001_:_001_:_001_:_1_:_
		SEK_:_sv_:_J_:_J_:_J_:_J_:_J_:_J_:_2000_:_J_:_J_:_Fritt textfält_:_
		30_:_001_:_001_:_001_:_001_:_J_:_

	Fältavskiljare = _:_

	Function: gör  UPDATE KUNDREG SET NAMN="TestAB",ADRESS="Provgatan 2",
	POSTNR="199 99",POSTADR="LILLEBY",LAND="Sverige",TFNNR="09-999990",
	FAXNR="09-999999",EMAILADR="info@test.se",
	ERREFERENT="Karl Andersson",ERREFTFNNR="09-999991",ERREFEMAIL="karl.a@test.se",
	SELJARE="Caroline Seljare",DISTRIKT="Kal",KUNDKATEGORI="Sto",STDLEVPLATS="002",
	LEVVILLKOR="001",LEVSETT="001",BETALVILLKOR="001",VALUTA="SEK",SPRAKKOD="sv",
	ORDERERKENNANDE="J",PLOCKLISTA="J",FOLJESEDEL="J",EXPAVGIFT="J",
	FRAKTAVG="J",KRAVBREV="J",KREDITLIMIT="2000",DROJMALSRTA="J",DROJMALSFAKTURA="J",
	FRITEXT="Fritt textfält",
	KREDITDAGAR="30",KREDITKOD="001",EXPORTKOD="001",SKATTEKOD="001",RABATTKOD="001",
	SAMLINGSFAKT="J"
	WHERE KUNDNR="kundnr"
	i databasen olfix

	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/KUCHG.c,v 1.1 2003/10/04 15:15:43 janpihlgren Exp $ " ;

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include "mysql.h"
#define ANTAL 37	// antal fält = 37 inklusive kundnr

  MYSQL my_connection;
  MYSQL_RES *res_ptr;
  MYSQL_ROW sqlrow;

int main(int argc, char *argv[])
{
  int res;

  static char *temp1[ANTAL]={"","UPDATE KUNDREG SET NAMN=\"",
  ",ADRESS=\"",",POSTNR=\"",",POSTADR=\"",",LAND=\"",
  ",TFNNR=\"",",FAXNR=\"",",EMAILADR=\"",",ERREFERENT=\"",
  ",ERREFTFNNR=\"",",ERREFEMAIL=\"",",SELJARE=\"",",DISTRIKT=\"",
  ",KUNDKATEGORI=\"",",STDLEVPLATS=\"",",LEVVILLKOR=\"",
  ",LEVSETT=\"",",BETALVILLKOR=\"",",VALUTA=\"",",SPRAKKOD=\"",
  ",ORDERERKENNANDE=\"",",PLOCKLISTA=\"",",FOLJESEDEL=\"",",EXPAVGIFT=\"",
  ",FRAKTAVG=\"",",KRAVBREV=\"",",KREDITLIMIT=\"",",DROJMALSRTA=\"",
  ",DROJMALSFAKTURA=\"",",FRITEXT=\"",",KREDITDAGAR=\"",",KREDITKOD=\"",
  ",EXPORTKOD=\"",",SKATTEKOD=\"",",RABATTKOD=\"",",SAMLINGSFAKT=\""};

  char temp1b[]=" WHERE KUNDNR=\"";
  char temp2[]="\"";
//  char temp3[]=",";
//  char temp4[]=")";
  char temp5[1500]="";
  char kunddata[2000];
  char kundnr[11];

  char *pos1;
  char *pos2;
  int tmp,lenght,i,j,k,n;
  int ant;

  if (argv[1] != NULL){
  	strcpy(kunddata,argv[1]);
  }
  else{
  	fprintf(stderr,"Error: KUCHG: Data saknas!\n");
	exit(-1);
  }

//  fprintf(stderr,"KUCHG kunddata=%s\n",kunddata);

  lenght=strlen(kunddata);
//  strcpy(temp5,temp1[0]);
//  fprintf(stderr,"temp5 = %s\n",temp5);
  pos1=strstr(kunddata,"_:_")+3;
  k=3;
  n=0;
  ant=ANTAL;		// antal fält = 37 inklusive kundnr
  for (i=0;i<ant-1;i++){
  	for (j=k;j<lenght;j++){
//		fprintf(stderr,"j=%d\n",j);
  		if (kunddata[j]== 95 && kunddata[j+1]== 58 && kunddata[j+2]== 95){
			j=lenght;
		}
		n=n+1;
  	}
	k=k+(n-1)+3;

	pos2=pos1+3+(n-1);
	tmp=pos2-pos1-3;
	if (i==0){
		strncpy(kundnr,pos1,tmp);
	}else{
		strcat(temp5,temp1[i]);
  		strncat(temp5,pos1,tmp);
  		strcat(temp5,temp2);
	}
	pos1=pos2;
//	fprintf(stderr,"i=%d, k=%d, n=%d, tmp=%d\n",i,k,n,tmp);
	n=0;
//	fprintf(stderr,"temp5 = %s\n",temp5);
  }

  strcat(temp5,temp1b);
  strcat(temp5,kundnr);
  strcat(temp5,temp2);
//  fprintf(stderr,"\nKUCHG: temp5 = %s\n",temp5);
//  exit(0);

  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", "olfix", 0, NULL, 0)){
//  	fprintf(stderr,"KUCHG:Connection success\n");

  res = mysql_query(&my_connection,temp5);

  if (!res){
 	fprintf(stdout,"OK: KUCHG Uppdated %lu rows\n",
		(unsigned long)mysql_affected_rows(&my_connection));
        }else{
	fprintf(stderr,"Error: KUCHG UPDATE error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
	}
	mysql_close(&my_connection);
 }else {
	fprintf(stderr,"Error: KUCHG Connection failed\n");
 	if (mysql_errno(&my_connection))   {
 		fprintf(stderr,"Error: KUCHG Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
	}
  }
 	fprintf(stdout,"\n");
  return EXIT_SUCCESS;
}

