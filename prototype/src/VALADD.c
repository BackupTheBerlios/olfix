/***************************************************************************
                          VALADD.c  -  description
                             -------------------
    begin                : Fre 21 febr
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
	INPUT: 5 st arg. VALUTAID, LAND, SALJ, KOP och BETECKNING (fälten i tabellen VALUTA)

	Kommando: ./VALADD SEK Sverige 1.22 1.23 Kronor

	Function: Add record i tabell VALUTA

	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/VALADD.c,v 1.1 2003/05/08 08:54:12 frazze Exp $ " ;

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

  char temp1[]="INSERT INTO VALUTA(VALUTAID,LAND,SALJ,KOP,BETECKNING) VALUES (\"";
  char temp2[]="\"";
  char temp3[]=",";
  char temp4[]=")";
  char temp5[200]="";
  char valuta[4];
  char land[16];
  char salj[15];
  char kop[15];
  char beteckning[16];

  strcpy(valuta,argv[1]);
  strcpy(land,argv[2]);
  strcpy(salj,argv[3]);
  strcpy(kop,argv[4]);
  strcpy(beteckning,argv[5]);


  strcat(temp5,temp1);
/* INSERT INTO VALUTA(VALUTAID,LAND,SALJ,KOP,BETECKNING) VALUES ("  */
  strcat(temp5,valuta);/* SEK */
/* INSERT INTO VALUTA(VALUTAID,LAND,SALJ,KOP,BETECKNING) VALUES ("SEK  */
  strcat(temp5,temp2); /*  "     */
  strcat(temp5,temp3); /*  ,     */
  strcat(temp5,temp2); /*  "     */
/* INSERT INTO VALUTA(VALUTAID,LAND,SALJ,KOP,BETECKNING) VALUES ("SEK","  */
  strcat(temp5,land);/* Sverige  */
/* INSERT INTO VALUTA(VALUTAID,LAND,SALJ,KOP,BETECKNING) VALUES ("SEK","Sverige  */
  strcat(temp5,temp2); /*  "     */
  strcat(temp5,temp3); /*  ,     */
  strcat(temp5,temp2); /*  "     */
/* INSERT INTO VALUTA(VALUTAID,LAND,SALJ,KOP,BETECKNING) VALUES ("SEK","Sverige","  */
  strcat(temp5,salj);
/* INSERT INTO VALUTA(VALUTAID,LAND,SALJ,KOP,BETECKNING) VALUES ("SEK","Sverige","1.22   */
  strcat(temp5,temp2); /*  "     */
  strcat(temp5,temp3); /*  ,     */
  strcat(temp5,temp2); /*  "     */
/* INSERT INTO VALUTA(VALUTAID,LAND,SALJ,KOP,BETECKNING) VALUES ("SEK","Sverige","1.22","  */
  strcat(temp5,kop);
/* INSERT INTO VALUTA(VALUTAID,LAND,SALJ,KOP,BETECKNING) VALUES ("SEK","Sverige","1.22","1.23  */
  strcat(temp5,temp2); /*  "     */
  strcat(temp5,temp3); /*  ,     */
  strcat(temp5,temp2); /*  "     */
/* INSERT INTO VALUTA(VALUTAID,LAND,SALJ,KOP,BETECKNING) VALUES ("SEK","Sverige","1.22","1.23"," */
  strcat(temp5,beteckning);
  strcat(temp5,temp2); /*  "     */
  strcat(temp5,temp4); /*  )     */
/* INSERT INTO VALUTA(VALUTAID,LAND,SALJ,KOP,BETECKNING) VALUES ("SEK","Sverige","1.22","1.23","Kronor")  */

  mysql_init(&my_connection);

  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", "olfix", 0, NULL, 0)){
  // fprintf(stdout,"USERADD:Connection success\n");

    res = mysql_query(&my_connection,temp5);

  	if (!res){
		fprintf(stdout,"OK: VALADD Inserted %lu rows\n",
			(unsigned long)mysql_affected_rows(&my_connection));
        }else{
	fprintf(stderr,"Error: VALADD INSERT error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
	}
	mysql_close(&my_connection);

 } else {
	fprintf(stderr,"Error: VALADD Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: VALADD Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
	}
    }

  return EXIT_SUCCESS;
}


