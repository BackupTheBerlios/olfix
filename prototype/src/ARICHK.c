/***************************************************************************
                          ARICHK.c  -  description
                             -------------------
    begin                : Mån 2  dec	2002
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
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/ARICHK.c,v 1.1 2003/05/08 08:54:03 frazze Exp $ " ;

/*
	INPUT: 2 st arg. ARID

	Kommando: ./ARCHK arid

	Function: Kontrollera om bokföringsår arid existerar i tabell BOKFAR

	OUTPUT: errornb och error (text)

*/
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

  char temp1[]="SELECT ARID FROM BOKFAR WHERE ARID = \"";
  char temp2[]="\"";
  char temp3[]=",";
  char temp4[]=")";
  char temp5[200]="";
  char arid[4];
  int status;

//  fprintf(stderr,"ARICHKmain: argv1 = %s, argv2 = %s\n",argv[1],argv[2]);
  strcpy(arid,argv[1]);
//  fprintf(stderr,ARICHKmain: ari = %s\n",ari);

  strcat(temp5,temp1);
/* SELECT ARID FROM BOKFAR WHERE ARID = "  */
//  fprintf(stderr,"ARICHKmain: temp5 (1) = %s\n",temp5);
  strcat(temp5,arid);/* AC */
/* SELECT ARID FROM BOKFAR WHERE ARID = "AC */
//  fprintf(stderr,"ARICHKmain: temp5 (2) = %s\n",temp5);

  strcat(temp5,temp2); /*  "     */
/* SELECT ARID FROM BOKFAR WHERE ARID = "AC" */
//  fprintf(stderr,"ARICHKmain: temp5 = %s\n",temp5);

  mysql_init(&my_connection);
if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", "olfix", 0, NULL, 0)){
//	fprintf(stdout,"ARICHKmain:Connection success\n");
	res = mysql_query(&my_connection,temp5);
//  	fprintf(stderr,"ARICHKmain: res= %d\n",res);
  	if (res){
		fprintf(stderr,"ARICHKmain: Selection error: %s\n", mysql_error(&my_connection));
	}
	else {
		res_ptr = mysql_store_result(&my_connection);
		if (res_ptr){
//			fprintf(stderr,"ARICHKmain:Retrieved %lu rows\n",(unsigned long)mysql_num_rows(res_ptr));
			if((unsigned long)mysql_num_rows(res_ptr) > 0){ /* En rad har hittats */
				status=0;
			}else{						/* Ingen rad hittades */
				status=-1;
			}
    			if (mysql_errno(&my_connection)) {
    				fprintf(stderr,"ARICHKmain: Retrieve error  %s\n",mysql_error(&my_connection));
			}
		}
		mysql_free_result(res_ptr);
	}
	mysql_close(&my_connection);
}
else {
	fprintf(stderr,"ARICHKmain: Connection faild\n");
	if (mysql_errno(&my_connection))  {
		fprintf(stderr,"ARICHKmain: Connection error: %d  %s\n",
			mysql_errno(&my_connection),mysql_error(&my_connection));
	}
}
  fprintf(stdout,"ARICHKmain:Jobb klart. Status = %d\n",status);
  return status;
}
