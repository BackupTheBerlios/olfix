/***************************************************************************
                          KUADD.c  -  description
                             -------------------
    Version		 : 0.1
    begin                : Mån 8 aug 2003
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
		format=_:_4376_:_Test AB_:_Provgatan 2_:_199 99_:_LILLEBY_:_Sverige_:_ 09-999990_:_09-999999_:_info@test.se_:_Karl Andersson _:_09-999991_:_karl.a@test.se_:_
Caroline Seljare_:_KalmarSoftware _:_001_:_001_:_001_:_1_:_SEK_:_sv_:_J_:_J_:_J_:_J_:_J_:_J_:_2000_:_J_:_J_:_Fritt textfält_:_

Fältavskiljare = _:_

	Function: gör  INSERT INTO KUNDREG(KUNDNR,KUNDORGNR,NAMN,ADRESS,POSTNR,POSTADR,LAND,TFNNR,FAXNR,EMAILADR,ERREFERENT,ERREFTFNNR,ERREFEMAIL,SELJARE,DISTRIKT,KUNDKATEGORI,STDLEVPLATS,LEVVILLKOR,LEVSETT,BETALVILLKOR,VALUTA,SPRAKKOD,ORDERERKENNANDE,PLOCKLISTA,FOLJESEDEL,EXPAVGIFT,FRAKTAVG,KRAVBREV,KREDITLIMIT,DROJMALSRTA,DROJMALSFAKTURA,FRITEXT) VALUES ("2345","Kund AB","PProvgatan 33","199 99","KUNDBY","SVERIGE","09-999999","09-999998","kund@kund.se","Karl Andersson","09-999997",
"karl.a@kund.se","Eva Seljare","Kalmar","001","001","001","001","1","SEK","sv",
"J","J","J","J","J","J","10000","J","J","Fritt textfält")i databasen olfix

	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/KUADD.c,v 1.1 2003/09/28 04:23:01 janpihlgren Exp $ " ;

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include "mysql.h"

  MYSQL my_connection;
  MYSQL_RES *res_ptr;
  MYSQL_ROW sqlrow;

int main(int argc, char *argv[])
{
  int res;

  char temp1a[]="INSERT INTO KUNDREG (KUNDNR,NAMN,ADRESS,POSTNR,POSTADR,LAND,TFNNR,FAXNR,EMAILADR,ERREFERENT,ERREFTFNNR,ERREFEMAIL,SELJARE,DISTRIKT,KUNDKATEGORI,STDLEVPLATS,LEVVILLKOR,LEVSETT,BETALVILLKOR,VALUTA,SPRAKKOD,ORDERERKENNANDE,PLOCKLISTA,FOLJESEDEL,EXPAVGIFT,FRAKTAVG,KRAVBREV,KREDITLIMIT,DROJMALSRTA,DROJMALSFAKTURA,FRITEXT) VALUES (";
  char temp2[]="\"";
  char temp3[]=",";
  char temp4[]=")";
  char temp5[1500]="";
  char kunddata[2000];

  char *pos1;
  char *pos2;
  int tmp,lenght,ant,i,j,k,n;

  if (argv[1] != NULL){
  	strcpy(kunddata,argv[1]);
  }
  else{
  	fprintf(stderr,"Error: KUADD: Ange kundnummer!\n");
	exit(-1);
  }

  lenght=strlen(kunddata);
//  fprintf(stderr,"lenght=%d\n",lenght);
  strcpy(temp5,temp1a);
//  fprintf(stderr,"kunddata=%s\n",kunddata);
  pos1=strstr(kunddata,"_:_")+3;
  k=3;
  n=0;
  ant=31;		// antal fält = 32
  for (i=0;i<ant;i++){
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
  	strcat(temp5,temp2);
  	strncat(temp5,pos1,tmp);
  	strcat(temp5,temp2);
	if (i<(ant-1)){
  		strcat(temp5,temp3);
	}
	pos1=pos2;
//	fprintf(stderr,"i=%d, k=%d, n=%d, tmp=%d\n",i,k,n,tmp);
	n=0;
//	fprintf(stderr,"temp5 = %s\n",temp5);
  }
  strcat(temp5,temp4);

// fprintf(stderr,"\nKUADD: temp5 = %s\n\n",temp5);
// exit(0);


  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", "olfix", 0, NULL, 0)){
//  	fprintf(stderr,"KUADD:Connection success\n");

  res = mysql_query(&my_connection,temp5);

  if (!res){
 	fprintf(stdout,"OK: KUADD Inserted %lu rows\n",
		(unsigned long)mysql_affected_rows(&my_connection));
        }else{
	fprintf(stderr,"Error: KUADD INSERT error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
	}
	mysql_close(&my_connection);
 }else {
	fprintf(stderr,"Error: KUADD Connection failed\n");
 	if (mysql_errno(&my_connection))   {
 		fprintf(stderr,"Error: KUADD Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
	}
  }
 	fprintf(stdout,"\n");
  return EXIT_SUCCESS;
}

