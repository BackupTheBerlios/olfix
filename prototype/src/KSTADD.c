/***************************************************************************
                          KSTADD.c  -  description
                             -------------------
    begin                : Fre 22 febr
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
	INPUT: 3 st arg. ARID, KSTALLE, och BENAMNING (fälten i tabellen KSTALLE)

	Kommando: ./KSTADD AC 9038 "Projekt Titan"

	Function: Add record i tabell KSTALLE

	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/KSTADD.c,v 1.1 2003/05/08 08:54:07 frazze Exp $ " ;

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

  char temp1[]="INSERT INTO KSTALLE(ARID,KSTALLE,BENAMNING) VALUES (\"";
  char temp2[]="\"";
  char temp3[]=",";
  char temp4[]=")";
  char temp5[200]="";
  char arid[4];
  char kstalle[5];
  char benamn[101];

  strcpy(arid,argv[1]);
  strcpy(kstalle,argv[2]);
  strcpy(benamn,argv[3]);


  strcat(temp5,temp1);
/* INSERT INTO KSTALLE(ARID,KSTALLE,BENAMNING) VALUES ("  */
  strcat(temp5,arid);/* AD */
/* INSERT INTO KSTALLE(ARID,KSTALLE,BENAMNING) VALUES ("AD  */
  strcat(temp5,temp2); /*  "     */
  strcat(temp5,temp3); /*  ,     */
  strcat(temp5,temp2); /*  "     */
/* INSERT INTO KSTALLE(ARID,KSTALLE,BENAMNING) VALUES ("AD","  */
  strcat(temp5,kstalle);/* 9038  */
/* INSERT INTO KSTALLE(ARID,KSTALLE,BENAMNING) VALUES ("SEK","9038  */
  strcat(temp5,temp2); /*  "     */
  strcat(temp5,temp3); /*  ,     */
  strcat(temp5,temp2); /*  "     */
/* INSERT INTO KSTALLE(ARID,KSTALLE,BENAMNING) VALUES ("SEK","9038","  */
  strcat(temp5,benamn);
  strcat(temp5,temp2); /*  "     */
  strcat(temp5,temp4); /*  )     */
/* INSERT INTO KSTALLE(ARID,KSTALLE,BENAMNING) VALUES ("SEK","9038","Projekt Titan")  */

  mysql_init(&my_connection);

  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", "olfix", 0, NULL, 0)){
  // fprintf(stdout,"KSTADD:Connection success\n");

    res = mysql_query(&my_connection,temp5);

  	if (!res){
		fprintf(stdout,"OK: KSTADD Inserted %lu rows\n",
			(unsigned long)mysql_affected_rows(&my_connection));
        }else{
/*	fprintf(stderr,"stderr-KSTADD:INSERT error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
*/
	fprintf(stderr,"Error: KSTADD INSERT error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
	}
	mysql_close(&my_connection);

 } else {
	fprintf(stderr,"Error: KSTADD Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: KSTADD Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
	}
    }

  return EXIT_SUCCESS;
}

