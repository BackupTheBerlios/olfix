/***************************************************************************
                          KTOCHK.c  -  description
                             -------------------
			     Ver. 0.2
    begin                : L�r 1  mars	2003
    copyright            : (C) 2002 by Jan Pihlgren
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
	INPUT: 2 st arg. KTONR

	Kommando: ./KTOCHK arid kontonr

	Function: Kontrollera om kontonummer existerar i tabell KONTOPLAN

	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/KTOCHK.c,v 1.1 2003/05/08 08:54:08 frazze Exp $ " ;

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mysql.h"

  MYSQL my_connection;
  MYSQL_RES *res_ptr;
  MYSQL_ROW sqlrow;

int main(int argc, char *argv[])
{
  MYSQL my_connection;
  int res;

  char temp1[]="SELECT KTONR FROM KTOPLAN WHERE (ARID = \"";
  char temp1b[]=" AND KTONR = \"";
  char temp2[]="\"";
  char temp3[]=",";
  char temp4[]=")";
  char temp5[200]="";
  char arid[3];
  char ktonr[5];
  int status;

  strcpy(arid,argv[1]);
  strcpy(ktonr,argv[2]);

  strcat(temp5,temp1);
/* SELECT KTONR FROM KTOPLAN WHERE (ARID = "	*/
  strcat(temp5,arid);/* AC */
/* SELECT KTONR FROM KTOPLAN WHERE (ARID = "AC	*/
  strcat(temp5,temp2); /*  "     */
/* SELECT KTONR FROM KTOPLAN WHERE (ARID = "AC"	*/
  strcat(temp5,temp1b);
/* SELECT * FROM KTOPLAN WHERE (ARID = "AC" AND KTONR = "	*/
  strcat(temp5,ktonr);/* 1020 */
/* SELECT KTONR FROM KTOPLAN WHERE (ARID = "AC" AND KTONR = "1020	*/
  strcat(temp5,temp2); /*  "     */
/* SELECT KTONR FROM KTOPLAN WHERE (ARID = "AC" AND KTONR = "1020"	*/
  strcat(temp5,temp4); /*  )     */
/* SELECT KTONR FROM KTOPLAN WHERE (ARID = "AC" AND KTONR = "1020")	*/
  strcat(temp5,"\n");
//  fprintf(stderr,"KTODSP temp5 = %s\n",temp5);

  mysql_init(&my_connection);
if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", "olfix", 0, NULL, 0)){
//	fprintf(stdout,"KTOCHKmain:Connection success\n");
	res = mysql_query(&my_connection,temp5);
//  	fprintf(stderr,"KTOCHKmain: res= %d\n",res);
  	if (res){
		fprintf(stderr,"Error: KTOCHK Selection error: %s\n", mysql_error(&my_connection));
	}
	else {
		res_ptr = mysql_store_result(&my_connection);
		if (res_ptr){
//			fprintf(stderr,"KTOCHKmain:Retrieved %lu rows\n",(unsigned long)mysql_num_rows(res_ptr));
			if((unsigned long)mysql_num_rows(res_ptr) > 0){ /* En rad har hittats */
				status=0;
			}else{						/* Ingen rad hittades */
				status=-1;
			}
    			if (mysql_errno(&my_connection)) {
    				fprintf(stderr,"Error: KTOCHK Retrieve error  %s\n",mysql_error(&my_connection));
			}
		}
		mysql_free_result(res_ptr);
	}
	mysql_close(&my_connection);
}
else {
	fprintf(stderr,"Error: KTOCHK Connection faild\n");
	if (mysql_errno(&my_connection))  {
		fprintf(stderr,"Error: KTOCHK Connection error: %d  %s\n",
			mysql_errno(&my_connection),mysql_error(&my_connection));
	}
}
//  fprintf(stdout,"KTOCHKmain:Jobb klart. Status = %d\n",status);
	if(status == 0){
		fprintf(stdout,"OK: KTOCHK Status = %d\n",status);
	}
	if(status != 0){
		fprintf(stderr,"Error: KTOCHK Konto %s finns inte!\n",ktonr);
	}
  return status;
}
