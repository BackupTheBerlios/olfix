/***************************************************************************
                          LRESADD.c  -  description
                             -------------------
    Version		 : 0.03
    begin                : Sön 10 aug 2003
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
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/LRESADD.c,v 1.1 2003/09/28 04:33:56 janpihlgren Exp $ " ;

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

  char temp1a[]="INSERT INTO LEVRESK(LEVNR, FAKTURANR, REGDATUM, FAKTDATUM, EXPIREDATUM, FAKTTEXT, BAR, MOMSPROCENT, LEVKTONR, FAKTBELOPP, MOMSKTONR, MOMSBELOPP, DEBETKONTONR, DEBETBELOPP, USERID,VALUTA,VALUTAKURS,VALUTABELOPP,OCRNR,VERNR) VALUES (";
  char temp2[]="\"";
  char temp3[]=",";
  char temp4[]=")";
  char temp5[500]="";
  char levnr[11];		// nr 1
  char fakturanr[21];		// nr 2
  char regdatum[11];		// nr 3
  char faktdatum[11];		// nr 4
  char expiredatum[11];		// nr 5
  char fakttext[101];		// nr 6
  char bar[3];			// nr 7
  char momsprocent[8];		// nr 8
  char levkontonr[5];		// nr 9
  char faktbelopp[14];		// nr 10
  char momsktonr[5];		// nr 11
  char momsbelopp[14];		// nr 12
  char debetktonr[5];		// nr 13
  char debetbelopp[14];	// nr 14
  char userid[9];		// nr 15
  char valuta[4];		// nr 16
  char valutakurs[6];		// nr 17
  char valutabelopp[14];	// nr 18
  char ocrnr[21];		// nr 19
  char vernr[9];		// nr 20

  if (argv[1] != NULL){
  	strcpy(levnr,argv[1]);
  }
  else{
  	fprintf(stderr,"Error: LRESADD: Ange leverantörsnummer!\n");
	exit(-1);
  }

  if (argv[2] != NULL){
  	strcpy(fakturanr,argv[2]);
  }
  else{
  	fprintf(stderr,"Error: LRESADD: Ange fakturanummer!\n");
	exit(-1);
  }

  strcpy(regdatum,argv[3]);
  strcpy(faktdatum,argv[4]);
  strcpy(expiredatum,argv[5]);
  strcpy(fakttext,argv[6]);
  strcpy(bar,argv[7]);
  strcpy(momsprocent,argv[8]);
  strcpy(levkontonr,argv[9]);
  strcpy(faktbelopp,argv[10]);
  strcpy(momsktonr,argv[11]);
  strcpy(momsbelopp,argv[12]);
  strcpy(debetktonr,argv[13]);
  strcpy(debetbelopp,argv[14]);
  strcpy(userid,argv[15]);
  strcpy(valuta,argv[16]);
  strcpy(valutakurs,argv[17]);
  strcpy(valutabelopp,argv[18]);
  strcpy(ocrnr,argv[19]);
  strcpy(vernr,argv[20]);

  strcpy(temp5,temp1a);
  strcat(temp5,temp2);
  strcat(temp5,levnr);			// 1
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,fakturanr);		// 2
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,regdatum);		// 3
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,faktdatum);		// 4
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,expiredatum);		// 5
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,fakttext);		// 6
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,bar);			// 7
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,momsprocent);		// 8
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,levkontonr);		// 9
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,faktbelopp);		// 10
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,momsktonr);		// 11
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,momsbelopp);		// 12
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,debetktonr);		// 13
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,debetbelopp);		// 14
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,userid);			// 15
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,valuta);			// 16
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,valutakurs);		// 17
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,valutabelopp);		// 18
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,ocrnr);			// 19
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
  strcat(temp5,vernr);			// 20
  strcat(temp5,temp2);
  strcat(temp5,temp4);
  /* INSERT INTO LEVRESK(LEVNR, FAKTURANR, REGDATUM, FAKTDATUM, EXPIREDATUM, FAKTTEXT, BAR, MOMSPROCENT, LEVKTONR, FAKTBELOPP, MOMSKTONR, MOMSBELOPP, KREDITKONTONR, KREDITBELOPP, USERID,VALUTA,VALUTAKURS,VALUTABELOPP) VALUES ("123","1239955","2003-06-24","2003-06-17","2003-07-17","Inköp av skrivbord","AC","25","2110","2500.00","1470","625.00","1810","1875.00","JAN","EUR","9.08","22700.00","9660000032831","00000021")) */

  fprintf(stderr,"LRESADD: temp5 = %s\n",temp5);
//  exit (0);
  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", "olfix", 0, NULL, 0)){
//  	fprintf(stderr,"LRESADD:Connection success\n");

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

