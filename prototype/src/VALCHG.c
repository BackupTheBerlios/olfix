/***************************************************************************
                          VALCHG.c  -  description
                             -------------------
			     Ver. 0.1
    begin                : Fre 21 Fre
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
	INPUT: 4 st arg. VALUTAID, LAND, SALJ, KOP och BETECKNING (fälten i tabellen VALUTA)

	Kommando: ./VALCHG SEK Sverige 1.01 1.02 Kronor

	Function: Ändra record i tabell VALUTA

	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/VALCHG.c,v 1.1 2003/05/08 08:54:13 frazze Exp $ " ;

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

  char temp1a[]="UPDATE VALUTA SET LAND = ";
  char temp1b[]=" WHERE VALUTAID = ";
  char temp1c[]="SALJ = ";
  char temp1d[]="KOP = ";
  char temp1e[]="BETECKNING = ";
  char temp2[]="\"";
  char temp3[]=",";
  char temp4[]=")";
  char temp5[200]="";
  char valuta[4];
  char land[16];
  char kop[15];
  char salj[15];
  char beteck[16];

  strcpy(valuta,argv[1]);
  strcpy(land,argv[2]);
  strcpy(salj,argv[3]);
  strcpy(kop,argv[4]);
  strcpy(beteck,argv[5]);

  strcat(temp5,temp1a);
/* UPDATE VALUTA SET LAND =   */
  strcat(temp5,temp2);
/* UPDATE VALUTA SET LAND = "   */
  strcat(temp5,land);
/* UPDATE VALUTA SET LAND ="Sverige   */
  strcat(temp5,temp2); /*  "     */
  strcat(temp5,temp3); /*  ,     */
/* UPDATE VALUTA SET LAND ="Sverige", */
  strcat(temp5,temp1c);
/* UPDATE VALUTA SET LAND ="Sverige",SALJ =    */
  strcat(temp5,temp2); /*  "     */
  strcat(temp5,salj);
/* UPDATE VALUTA SET LAND ="Sverige",SALJ = "1.01    */
  strcat(temp5,temp2);  /*  "     */
  strcat(temp5,temp3); /*  ,     */
  strcat(temp5,temp1d);
/* UPDATE VALUTA SET LAND ="Sverige",SALJ = "1.01",KOP =   */
  strcat(temp5,temp2); /*  "     */
  strcat(temp5,kop);
/* UPDATE VALUTA SET LAND = "Sverige",SALJ = "1.01",KOP = "1.02 */
  strcat(temp5,temp2); /*  "     */
  strcat(temp5,temp3); /*  ,     */
/* UPDATE VALUTA SET LAND = "Sverige",SALJ = "1.01",KOP = "1.02", */
  strcat(temp5,temp1e);
  strcat(temp5,temp2); /*  "     */
/* UPDATE VALUTA SET LAND = "Sverige",SALJ = "1.01",KOP = "1.02",BETECKNING = "  */
  strcat(temp5,beteck);
/* UPDATE VALUTA SET LAND = "Sverige",SALJ = "1.01",KOP = "1.02",BETECKNING = "Kronor  */
  strcat(temp5,temp2); /*  "     */
  strcat(temp5,temp1b);
/* UPDATE VALUTA SET LAND = "Sverige",SALJ = "1.01",KOP = "1.02",BETECKNING = "Kronor" WHERE VALUTAID = */
  strcat(temp5,temp2); /*  "     */
  strcat(temp5,valuta);
  strcat(temp5,temp2); /*  "     */
/* UPDATE VALUTA SET LAND = "Sverige",SALJ = "1.01",KOP = "1.02",BETECKNING = "Kronor" WHERE VALUTAID = "SEK"*/

//  fprintf(stderr,"VALCHG temp5=%s\n",temp5);

  mysql_init(&my_connection);

  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", "olfix", 0, NULL, 0)){
  //fprintf(stdout,"VALCHG_Connection success\n");

    res = mysql_query(&my_connection,temp5);

  	if (!res){
		fprintf(stdout,"OK: VALCHG Inserted %lu rows\n",
			(unsigned long)mysql_affected_rows(&my_connection));
        }else{
/*	fprintf(stderr,"stderr-VALCHG:INSERT error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
*/
	fprintf(stderr,"Error: VALCHG INSERT error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
	}
	mysql_close(&my_connection);

 } else {
	fprintf(stderr,"Error: VALCHG Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: VALCHG Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
	}
    }
  fprintf(stdout,"\n");
  return EXIT_SUCCESS;
}


