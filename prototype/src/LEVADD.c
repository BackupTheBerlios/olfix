/***************************************************************************
                          LEVADD.c  -  description
                             -------------------
    Version		 : 0.02
    begin                : Mån 30 juni
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
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/LEVADD.c,v 1.1 2003/09/28 04:29:58 janpihlgren Exp $ " ;

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include "mysql.h"

  MYSQL my_connection;
  MYSQL_RES *res_ptr;
  MYSQL_ROW sqlrow;


void display_row();

int main(int argc, char *argv[])
{
  int res,i;
//	for (i=0;i<argc;i++){
//	fprintf(stderr,"argv[%d]=%s\n",i,argv[i]);
//	}

  char temp1a[]="INSERT INTO LEVREG(LEVNR,LEVORGNR,LEVNAMN,LEVADRESS,LEVPOSTNR,LEVPOSTADR,LEVLAND,LEVTFNNR,LEVFAXNR,LEVTELEX,LEVEMAIL,LEVPOSTGIRONR,LEVBANKGIRONR,LEVREFERENT,LEVREFTFN,LEVMOMSKOD,LEVSKULD,LEVKONTO,LEVKUNDNR,LEVVALUTA,BETALVILKOR) VALUES (";
  char temp2[]="\"";
  char temp3[]=",";
  char temp4[]=")";
  char temp5[1500]="";
  char levnr[11];		// nr 1
  char levorgnr[13];		// nr 2
  char levnamn[31];		// nr 3
  char levadr[31];		// nr 4
  char levpostnr[7];		// nr 5
  char levpostadr[31];		// nr 6
  char levland[31];		// nr 7
  char levtfnnr[16];		// nr 8
  char levfaxnr[16];		// nr 9
  char levtelex[11];		// nr 10
  char levemail[31];		// nr 11
  char levpostgironr[11];	// nr 12
  char levbankgironr[11];	// nr 13
  char levref[21];		// nr 14
  char levreftfn[16];		// nr 15
  char levmomskod[2];		// nr 16
  char levskuld[]="0.00";	//
  char levkonto[5];		// nr 17
  char levkundnr[31];		// nr 18
  char levvaluta[4];		// nr 19
  char betalvilkor[4];		// nr 20

  if (argv[1] != NULL){
  	strcpy(levnr,argv[1]);
  }
  else{
  	fprintf(stderr,"Error: LEVADD: Ange kundnummer!\n");
	exit(-1);
  }

  strcpy(levorgnr,argv[2]);
  strcpy(levnamn,argv[3]);
  strcpy(levadr,argv[4]);
  strcpy(levpostnr,argv[5]);
  strcpy(levpostadr,argv[6]);
  strcpy(levland,argv[7]);
  strcpy(levtfnnr,argv[8]);
  strcpy(levfaxnr,argv[9]);
  strcpy(levtelex,argv[10]);
  strcpy(levemail,argv[11]);
  strcpy(levpostgironr,argv[12]);
  strcpy(levbankgironr,argv[13]);
  strcpy(levref,argv[14]);
  strcpy(levreftfn,argv[15]);
  strcpy(levmomskod,argv[16]);
  strcpy(levkonto,argv[17]);
  strcpy(levkundnr,argv[18]);
  strcpy(levvaluta,argv[19]);
  strcpy(betalvilkor,argv[20]);
  strcpy(temp5,temp1a);
  strcat(temp5,temp2);
  strcat(temp5,levnr);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,levorgnr);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,levnamn);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,levadr);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,levpostnr);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,levpostadr);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,levland);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,levtfnnr);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,levfaxnr);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,levtelex);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,levemail);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,levpostgironr);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,levbankgironr);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,levref);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,levreftfn);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,levmomskod);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,levskuld);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,levkonto);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,levkundnr);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,levvaluta);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,betalvilkor);
  strcat(temp5,temp2);
  strcat(temp5,temp4);
  /* INSERT INTO LEVREG(LEVNR,LEVORGNR,LEVNAMN,LEVADRESS,LEVPOSTNR,LEVPOSTADR,LEVLAND,LEVTFNNR,LEVFAXNR,LEVTELEX,LEVEMAIL,LEVPOSTGIRONR,LEVBANKGIRONR,LEVREFERENT,LEVREFTFN,LEVMOMSKOD,LEVSKULD,LEVKONTO,LEVKUNDNR,LEVVALUTA,BETALVILKOR) VALUES ("2345","559999-9999","Leverantör AB","Postgatan 33","199 99","DATABY","SVERIGE","09-999999","09-999998","99999","kundtj@leverantor.se","4559999-9","5999-9999","Per Josefsson","09-999997","1","0.00","2110","12345678","SEK","1") */

//fprintf(stderr,"LEVADD: temp5 = %s\n",temp5);

  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", "olfix", 0, NULL, 0)){
//  	fprintf(stderr,"LEVADD:Connection success\n");

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

