/***************************************************************************
                          LEVCHG.c  -  description
                             -------------------
    Version		 : 0.02
    begin                : Mån 30 juni
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
	INPUT: LEVNR, LEVORGNR, LEVNAMN, LEVADRESS, LEVPOSTNR, LEVPOSTADR,
	LEVLAND, LEVTFNNR, LEVFAXNR, LEVTELEX, LEVEMAIL, LEVREFERENT, LEVREFTFN,
	LEVMOMSKOD, LEVKONTO, LEVKUNDNR VALUTA BETALVILKOR

	Function: gör  UPDATE  LEVREG SET
	LEVORGNR="levorgnr",LEVNAMN="levnamn",LEVADRESS="levadress",
	LEVPOSTNR="levpostnr",LEVPOSTADR="levpostadr", LEVLAND="levland",
	LEVTFNNR="levtfnnr", LEVFAXNR="levfaxnr", LEVTELEX="levfaxnr",
	LEVEMAIL="levemail",LEVREFERENT="levref",LEVREFTFN="levreftfn",
	LEVMOMSKOD="levmomskod",LEVKONTO="levkontonr",LEVKUNDNR="12345678",
	LEVVALUTA="SEK",BETALVILKOR="2"
	WHERE LEVNR="levnr"

	i databasen olfix

	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/LEVCHG.c,v 1.1 2003/09/28 04:30:24 janpihlgren Exp $ " ;

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

  char temp1a[]="UPDATE LEVREG SET LEVORGNR = \'";
  char temp1b[]="\' WHERE LEVNR = \'";
  char temp2[]="\'";
//  char temp3[]=",";
//  char temp4[]=")";
  char temp5[1000]="";
  char levnr[11];
  char levorgnr[13];
  char levnamn[31];
  char levadr[31];
  char levpostnr[7];
  char levpostadr[31];
  char levland[31];
  char levtfnnr[16];
  char levfaxnr[16];
  char levtelex[11];
  char levemail[31];
  char levpostgironr[11];
  char levbankgironr[11];
  char levref[21];
  char levreftfn[16];
  char filler[16];
  char levmomskod[2];
  char levkonto[5];
  char levkundnr[31];
  char levvaluta[4];
  char betalvilkor[4];
//  char filler[16];

  if (argv[1] != NULL){
  	strcpy(levnr,argv[1]);
  }
  else{
  	fprintf(stderr,"Error: LEVCHG: Ange kundnummer!\n");
	exit(-1);
  }

  strcpy(levorgnr,argv[2]);		// nr 2
  strcpy(levnamn,argv[3]);		// nr 3
  strcpy(levadr,argv[4]);		// nr 4
  strcpy(levpostnr,argv[5]);		// nr 5
  strcpy(levpostadr,argv[6]);		// nr 6
  strcpy(levland,argv[7]);		// nr 7
  strcpy(levtfnnr,argv[8]);		// nr 8
  strcpy(levfaxnr,argv[9]);		// nr 9
  strcpy(levtelex,argv[10]);		// nr 10
  strcpy(levemail,argv[11]);		// nr 11
  strcpy(levpostgironr,argv[12]);	// nr 12
  strcpy(levbankgironr,argv[13]);	// nr 13
  strcpy(levref,argv[14]);		// nr 14
  strcpy(levreftfn,argv[15]);		// nr 15
  strcpy(levmomskod,argv[16]);		// nr 16
  strcpy(levkonto,argv[17]);		// nr 17
  strcpy(levkundnr,argv[18]);		// nr 18
  strcpy(levvaluta,argv[19]);		// nr 19
  strcpy(betalvilkor,argv[20]);		// nr 20

//  strcpy(filler,argv[13]);
//    fprintf(stderr,"argv13 = %s levreftfn=%s filler=%s \n",argv[13],levreftfn,filler);

//,LEVNAMN,LEVADRESS,LEVPOSTNR,LEVPOSTADR,LEVLAND,LEVTFNNR,LEVFAXNR,LEVTELEX,LEVEMAIL,LEVREFERENT,LEVREFTFN,LEVMOMSKOD,LEVSKULD,LEVKONTO,LEVVALUTA,BETALVILKOR) VALUES (";

  strcpy(temp5,temp1a);
  strcat(temp5,levorgnr);		// nr 2
  strcat(temp5,"\',LEVNAMN = \'");
  strcat(temp5,levnamn);		// nr 3
  strcat(temp5,"\',LEVADRESS = \'");
  strcat(temp5,levadr);			// nr 4
  strcat(temp5,"\',LEVPOSTNR = \'");
  strcat(temp5,levpostnr);		// nr 5
  strcat(temp5,"\',LEVPOSTADR = \'");
  strcat(temp5,levpostadr);		// nr 6
  strcat(temp5,"\',LEVLAND = \'");
  strcat(temp5,levland);		// nr 7
  strcat(temp5,"\',LEVTFNNR = \'");
  strcat(temp5,levtfnnr);		// nr 8
  strcat(temp5,"\',LEVFAXNR = \'");
  strcat(temp5,levfaxnr);		// nr 9
  strcat(temp5,"\',LEVTELEX = \'");
  strcat(temp5,levtelex);		// nr 10
  strcat(temp5,"\',LEVEMAIL = \'");
  strcat(temp5,levemail);		// nr 11
  strcat(temp5,"\',LEVPOSTGIRONR = \'");
  strcat(temp5,levpostgironr);		// nr 12
  strcat(temp5,"\',LEVBANKGIRONR = \'");
  strcat(temp5,levbankgironr);		// nr 13
  strcat(temp5,"\',LEVREFERENT = \'");
  strcat(temp5,levref);			// nr 14
  strcat(temp5,"\',LEVREFTFN = \'");
  strcat(temp5,levreftfn);		// nr 15
  strcat(temp5,"\',LEVMOMSKOD = \'");
  strcat(temp5,levmomskod);		// nr 16
  strcat(temp5,"\',LEVKONTO = \'");
  strcat(temp5,levkonto);		// nr 17
  strcat(temp5,"\',LEVKUNDNR = \'");
  strcat(temp5,levkundnr);		// nr 18
  strcat(temp5,"\',LEVVALUTA = \'");
  strcat(temp5,levvaluta);		// nr 19
  strcat(temp5,"\',BETALVILKOR = \'");
  strcat(temp5,betalvilkor);		// nr 20
  strcat(temp5,temp1b);
  strcat(temp5,levnr);
  strcat(temp5,temp2);
//  strcat(temp5,temp4);

//  fprintf(stderr,"LEVCHG: temp5 = %s\n",temp5);
//  exit(0);
  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", "olfix", 0, NULL, 0)){
//  	fprintf(stderr,"LEVCHG:Connection success\n");

  res = mysql_query(&my_connection,temp5);

  if (!res){
 	fprintf(stdout,"OK: LEVCHG Inserted %lu rows\n",
		(unsigned long)mysql_affected_rows(&my_connection));
        }else{
	fprintf(stderr,"Error: LEVCHG INSERT error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
	}
	mysql_close(&my_connection);
 }else {
	fprintf(stderr,"Error: LEVCHG Connection failed\n");
 	if (mysql_errno(&my_connection))   {
 		fprintf(stderr,"Error: LEVCHG Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
	}
  }
 	fprintf(stdout,"\n");
  return EXIT_SUCCESS;
}

