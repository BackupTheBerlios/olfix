/***************************************************************************
                          BARCHK.c  -  description
                             -------------------
    begin                : Tors 27 febr	2003
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
	INPUT: arid

	Kommando: ./BARCHK arid

	Function: Kontrollera att angivet bokföringsår finns.

	OUTPUT: data, errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/BARCHK.c,v 1.1 2003/05/08 08:54:04 frazze Exp $ " ;

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
  int res,status;

  char temp1[]="SELECT ARID FROM BOKFAR WHERE ARID = \"";
  char temp2[]="\"";
  char temp3[]=",";
  char temp4[]=")";
  char temp5[200]="";
  char arid[8];
  char vernr[10];

  strcpy(arid,argv[1]);

  strcat(temp5,temp1);
/* SELECT ARID FROM BOKFAR WHERE ARID = "  */
  strcat(temp5,arid);/* AC */
/* SELECT ARID FROM BOKFAR WHERE ARID = "AC  */
  strcat(temp5,temp2); /*  "     */
/* SELECT ARID FROM BOKFAR WHERE ARID = "AC" */
//  fprintf(stderr,"BARCHKmain: temp5 = %s\n",temp5);

  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", "olfix", 0, NULL, 0)){
//  fprintf(stdout,"BARCHKmain:Connection success\n");
  	res = mysql_query(&my_connection,temp5);
  	if (res){
		printf("Error: BARCHK_SELECT error: %s\n",mysql_error(&my_connection));
  	}
  	else{
		res_ptr=mysql_store_result(&my_connection);
		if (res_ptr){
//			fprintf(stderr,"BARCHK_Retrieved %lu rows\n",(unsigned long)mysql_num_rows(res_ptr));
			if((unsigned long)mysql_num_rows(res_ptr) > 0){ /* En rad har hittats */
				status=0;
			}else{						/* Ingen rad hittades */
				status=-1;
			}

			if (mysql_errno(&my_connection)){
				fprintf(stderr,"Error: BARCHK_Retriev error:  %s\n", mysql_error(&my_connection));
			}
		}
		mysql_free_result(res_ptr);
	}
  	mysql_close(&my_connection);
 }
  else {
  	fprintf(stderr,"Error: BARCHK_Connection failed\n");
	if (mysql_errno(&my_connection)){
		fprintf(stderr,"Error: BARCHK_Connection error %d:  %s\n",
		mysql_errno(&my_connection), mysql_error(&my_connection));
	}
  }
if(status == 0){
	fprintf(stdout,"OK: BARCHK_Status = %d\n",status);
}
if(status != 0){
	fprintf(stderr,"Error: BARCHK Bokföringsår %s finns inte!\n",arid);
}
  return status;
}

