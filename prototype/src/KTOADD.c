/***************************************************************************
                          KTOADD.c  -  description
                             -------------------
    Version		 : 0.01
    begin                : Tors 16 jan
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
	INPUT:	ARID,KTONR,BENAMNING,MANUELL,MOMSKOD,SRUNR,KSTALLE,PROJEKT,SUBKTO,KTOPLAN,IB,IB
	Function: gör  INSERT INTO KTOPLAN(ARID,KTONR,BENAMNING,MANUELL,MOMSKOD,SRUNR,KSTALLE,PROJEKT,
		SUBKTO,KTOPLAN,IB,IB) VALUES ("SS","1020","Testkonto","J","1","100","2000","3000",
		"4000","EUBAS97","0.00","0.00")  i databasen olfix

	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/KTOADD.c,v 1.1 2003/05/08 08:54:07 frazze Exp $ " ;

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


  char temp1a[]="INSERT INTO KTOPLAN(ARID,KTONR,BENAMNING,MANUELL,MOMSKOD,SRUNR,KSTALLE,PROJEKT,SUBKTO,KTOPLAN,IB,UB) VALUES (";
  char temp2[]="\"";
  char temp3[]=",";
  char temp4[]=")";
  char temp5[200]="";
  char arid[5];
  char ktonr[5];
  char benamn[101];
  char manuell[2];
  char momskod[5];
  char srunr[4];
  char kstalle[5];
  char projekt[5];
  char subkto[5];
  char ktoplan[16];
  char ib[]="0.00";
  char ub[]="0.00";


  if (argv[1] != NULL){
  	strcpy(arid,argv[1]);
  }
  else{
  	fprintf(stderr,"Error: KTOADD: Ange årtal!\n");
	exit(-1);
  }
  strcpy(ktonr,argv[2]);
  strcpy(benamn,argv[3]);
  strcpy(manuell,argv[4]);
  strcpy(momskod,argv[5]);
  strcpy(srunr,argv[6]);
  strcpy(kstalle,argv[7]);
  strcpy(projekt,argv[8]);
  strcpy(subkto,argv[9]);
  strcpy(ktoplan,argv[10]);

  strcpy(temp5,temp1a);
/* INSERT INTO KTOPLAN(ARID,KTONR,BENAMNING,MANUELL,MOMSKOD,SRUNR,KSTALLE,PROJEKT,SUBKTO,KTOPLAN,IB,IB) VALUES (   */
  strcat(temp5,temp2);			/* 2002 */
/* INSERT INTO KTOPLAN(ARID,KTONR,BENAMNING,MANUELL,MOMSKOD,SRUNR,KSTALLE,PROJEKT,SUBKTO,KTOPLAN,IB,IB) VALUES ("  */
  strcat(temp5,arid);
/* INSERT INTO KTOPLAN(ARID,KTONR,BENAMNING,MANUELL,MOMSKOD,SRUNR,KSTALLE,PROJEKT,SUBKTO,KTOPLAN,IB,IB) VALUES ("AC   */
  strcat(temp5,temp2);
/* INSERT INTO KTOPLAN(ARID,KTONR,BENAMNING,MANUELL,MOMSKOD,SRUNR,KSTALLE,PROJEKT,SUBKTO,KTOPLAN,IB,IB) VALUES ("AC"   */
  strcat(temp5,temp3);
/* INSERT INTO KTOPLAN(ARID,KTONR,BENAMNING,MANUELL,MOMSKOD,SRUNR,KSTALLE,PROJEKT,SUBKTO,KTOPLAN,IB,IB) VALUES ("AC",   */
  strcat(temp5,temp2);
/* INSERT INTO KTOPLAN(ARID,KTONR,BENAMNING,MANUELL,MOMSKOD,SRUNR,KSTALLE,PROJEKT,SUBKTO,KTOPLAN,IB,IB) VALUES ("AC"," */
  strcat(temp5,ktonr);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
/* INSERT INTO KTOPLAN(ARID,KTONR,BENAMNING,MANUELL,MOMSKOD,SRUNR,KSTALLE,PROJEKT,SUBKTO,KTOPLAN,IB,IB) VALUES ("AC","1200"," */
  strcat(temp5,benamn);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
/* INSERT INTO KTOPLAN(ARID,KTONR,BENAMNING,MANUELL,MOMSKOD,SRUNR,KSTALLE,PROJEKT,SUBKTO,KTOPLAN,IB,IB) VALUES ("AC","1200",
"Testkonto"," */
  strcat(temp5,manuell);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
/* INSERT INTO KTOPLAN(ARID,KTONR,BENAMNING,MANUELL,MOMSKOD,SRUNR,KSTALLE,PROJEKT,SUBKTO,KTOPLAN,IB,IB) VALUES ("AC","1200",
"Testkonto","J"," */
  strcat(temp5,momskod);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
/* INSERT INTO KTOPLAN(ARID,KTONR,BENAMNING,MANUELL,MOMSKOD,SRUNR,KSTALLE,PROJEKT,SUBKTO,KTOPLAN,IB,IB) VALUES ("AC","1200",
"Testkonto","J","1"," */
  strcat(temp5,srunr);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
/* INSERT INTO KTOPLAN(ARID,KTONR,BENAMNING,MANUELL,MOMSKOD,SRUNR,KSTALLE,PROJEKT,SUBKTO,KTOPLAN,IB,IB) VALUES ("AC","1200",
"Testkonto","J","1","100"," */
  strcat(temp5,kstalle);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
/* INSERT INTO KTOPLAN(ARID,KTONR,BENAMNING,MANUELL,MOMSKOD,SRUNR,KSTALLE,PROJEKT,SUBKTO,KTOPLAN,IB,IB) VALUES ("AC","1200",
"Testkonto","J","1","100","2000"," */
  strcat(temp5,projekt);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
/* INSERT INTO KTOPLAN(ARID,KTONR,BENAMNING,MANUELL,MOMSKOD,SRUNR,KSTALLE,PROJEKT,SUBKTO,KTOPLAN,IB,IB) VALUES ("AC","1200",
"Testkonto","J","1","100","2000","3000"," */
  strcat(temp5,subkto);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
/* INSERT INTO KTOPLAN(ARID,KTONR,BENAMNING,MANUELL,MOMSKOD,SRUNR,KSTALLE,PROJEKT,SUBKTO,KTOPLAN,IB,IB) VALUES ("AC","1200",
"Testkonto","J","1","100","2000","3000","4000"," */
  strcat(temp5,ktoplan);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
/* INSERT INTO KTOPLAN(ARID,KTONR,BENAMNING,MANUELL,MOMSKOD,SRUNR,KSTALLE,PROJEKT,SUBKTO,KTOPLAN,IB,IB) VALUES ("AC","1200",
"Testkonto","J","1","100","2000","3000","4000","EUBAS97"," */
  strcat(temp5,ib);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
  strcat(temp5,temp2);
/* INSERT INTO KTOPLAN(ARID,KTONR,BENAMNING,MANUELL,MOMSKOD,SRUNR,KSTALLE,PROJEKT,SUBKTO,KTOPLAN,IB,IB) VALUES ("AC","1200",
"Testkonto","J","1","100","2000","3000","4000","EUBAS97","0.00"," */
  strcat(temp5,ub);
  strcat(temp5,temp2);
  strcat(temp5,temp4);
  /* INSERT INTO KTOPLAN(ARID,KTONR,BENAMNING,MANUELL,MOMSKOD,SRUNR,KSTALLE,PROJEKT,SUBKTO,KTOPLAN,IB,IB) VALUES ("AC","1200",
"Testkonto","J","1","100","2000","3000","4000","EUBAS97","0.00","0.00") */

//  fprintf(stderr,"KTOADDmain: temp5 = %s\n",temp5);

  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", "olfix", 0, NULL, 0)){
//  	fprintf(stderr,"KTOVIEW:Connection success\n");

  res = mysql_query(&my_connection,temp5);

  if (!res){
 	fprintf(stdout,"OK: KTOADD Inserted %lu rows\n",
		(unsigned long)mysql_affected_rows(&my_connection));
        }else{
	fprintf(stderr,"Error: KTOADD INSERT error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
	}
	mysql_close(&my_connection);
 }else {
	fprintf(stderr,"Error: KTOADD Connection failed\n");
 	if (mysql_errno(&my_connection))   {
 		fprintf(stderr,"Error: KTOADD Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
	}
  }
 	fprintf(stdout,"\n");
  return EXIT_SUCCESS;
}

