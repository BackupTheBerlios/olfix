/***************************************************************************
                          SLPADD.c  -  description
                             -------------------
    Vesrsion		0.1
    begin                : Ons 10 aug 2003
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
 *********************************************** ****************************/

/*
	INPUT: KUNDNR, STDLEVPLATS, ADRESS, POSTNR, POSTADR och LAND (fälten i tabellen STDLEVPLATS)

	Kommando: ./SLPADD kundnr stdlevplats adress postnr postadr land

	Function: Add record i tabell STDLEVPLATS

	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/SLPADD.c,v 1.1 2003/09/28 08:52:50 janpihlgren Exp $ " ;

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mysql.h"


int main(int argc, char *argv[])
{
  MYSQL my_connection;
  int res;

  char temp1[]="INSERT INTO STDLEVPLATS(KUNDNR,STDLEVPLATS,ADRESS,POSTNR,POSTADR,LAND) VALUES (\"";
  char temp2[]="\"";
  char temp3[]=",";
  char temp4[]=")";
  char temp5[200]="";
  char kundnr[11];
  char stdlevplats[4];
  char adress[31];
  char postnr[7];
  char postadr[31];
  char land[31];

  strcpy(kundnr,argv[1]);
  strcpy(stdlevplats,argv[2]);
  strcpy(adress,argv[3]);
  strcpy(postnr,argv[4]);
  strcpy(postadr,argv[5]);
  strcpy(land,argv[6]);


  strcat(temp5,temp1);
/* INSERT INTO STDLEVPLATS(KUNDNR,STDLEVPLATS,ADRESS,POSTNR,POSTADR,LAND) VALUES ("  */
  strcat(temp5,kundnr);/* 4376 */
/* INSERT INTO STDLEVPLATS(KUNDNR,STDLEVPLATS,ADRESS,POSTNR,POSTADR,LAND) VALUES ("4376  */
  strcat(temp5,temp2); /*  "     */
  strcat(temp5,temp3); /*  ,     */
  strcat(temp5,temp2); /*  "     */
  strcat(temp5,stdlevplats);/* 001  */
/* INSERT INTO STDLEVPLATS(KUNDNR,STDLEVPLATS,ADRESS,POSTNR,POSTADR,LAND) VALUES ("4376","001 */
  strcat(temp5,temp2); /*  "     */
  strcat(temp5,temp3); /*  ,     */
  strcat(temp5,temp2); /*  "     */
/* INSERT INTO STDLEVPLATS(KUNDNR,STDLEVPLATS,ADRESS,POSTNR,POSTADR,LAND) VALUES ("4376","001","  */
  strcat(temp5,adress);
  strcat(temp5,temp2); /*  "     */
  strcat(temp5,temp3); /*  ,     */
  strcat(temp5,temp2); /*  "     */
/* INSERT INTO STDLEVPLATS(KUNDNR,STDLEVPLATS,ADRESS,POSTNR,POSTADR,LAND) VALUES ("4376","001","Provstigen 1","  */
  strcat(temp5,postnr);
  strcat(temp5,temp2); /*  "     */
  strcat(temp5,temp3); /*  ,     */
  strcat(temp5,temp2); /*  "     */
/* INSERT INTO STDLEVPLATS(KUNDNR,STDLEVPLATS,ADRESS,POSTNR,POSTADR,LAND) VALUES ("4376","001","Provstigen 1","199 99","  */
  strcat(temp5,postadr);
  strcat(temp5,temp2); /*  "     */
  strcat(temp5,temp3); /*  ,     */
  strcat(temp5,temp2); /*  "     */
/* INSERT INTO STDLEVPLATS(KUNDNR,STDLEVPLATS,ADRESS,POSTNR,POSTADR,LAND) VALUES ("4376","001","Provstigen 1","199 99","LILLEBY","  */
  strcat(temp5,land);
  strcat(temp5,temp2); /*  "     */
  strcat(temp5,temp4); /*  )     */
/* INSERT INTO STDLEVPLATS(KUNDNR,STDLEVPLATS,ADRESS,POSTNR,POSTADR,LAND) VALUES ("4376","001","Provstigen 1","199 99","LILLEBY","Svberige")  */

 // fprintf(stderr,"temp5=%s\n",temp5);

  mysql_init(&my_connection);

  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", "olfix", 0, NULL, 0)){
  // fprintf(stdout,"SLPADD:Connection success\n");

    res = mysql_query(&my_connection,temp5);

  	if (!res){
		fprintf(stdout,"OK: SLPADD Inserted %lu rows\n",
			(unsigned long)mysql_affected_rows(&my_connection));
        }else{
/*	fprintf(stderr,"stderr-SLPADD:INSERT error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
*/
	fprintf(stderr,"Error: SLPADD INSERT error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
	}
	mysql_close(&my_connection);

 } else {
	fprintf(stderr,"Error: SLPADD Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: SLPADD Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
	}
    }

  return EXIT_SUCCESS;
}
