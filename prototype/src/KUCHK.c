/***************************************************************************
                          KUCHK.c  -  description
                             -------------------
    begin                : Tis 9 sept	2003
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
	INPUT: kundid

	Kommando: ./KUCHK kundid

	Function: Kontrollera om angivet kundid finns.

	OUTPUT: data, errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/KUCHK.c,v 1.1 2003/09/28 04:25:11 janpihlgren Exp $ " ;

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

  char temp1[]="SELECT KUNDNR FROM KUNDREG WHERE KUNDNR = \"";
  char temp2[]="\"";
//  char temp3[]=",";
//  char temp4[]=")";
  char temp5[200]="";
  char kundnr[11];

  if (argv[1] != NULL){
  	strcpy(kundnr,argv[1]);
  }else{
  	fprintf(stderr,"Error: KUCHK: Ange kundnummer!\n");
	exit(-1);
  }

  strcpy(temp5,temp1);
/* SELECT KUNDNR FROM KUNDREG WHERE KUNDNR = "  */
  strcat(temp5,kundnr);/* AC */
/* SELECT KUNDNR FROM KUNDREG WHERE KUNDNR = "AC  */
  strcat(temp5,temp2); /*  "     */
/* SELECT KUNDNR FROM KUNDREG WHERE KUNDNR = "AC" */
//  fprintf(stderr,"KUCHKmain: temp5 = %s\n",temp5);

  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", "olfix", 0, NULL, 0)){
//  fprintf(stdout,"KUCHKmain:Connection success\n");
  	res = mysql_query(&my_connection,temp5);
  	if (res){
		printf("Error: KUCHK_SELECT error: %s\n",mysql_error(&my_connection));
  	}
  	else{
		res_ptr=mysql_store_result(&my_connection);
		if (res_ptr){
//			fprintf(stderr,"KUCHK_Retrieved %lu rows\n",(unsigned long)mysql_num_rows(res_ptr));
			if((unsigned long)mysql_num_rows(res_ptr) > 0){ /* En rad har hittats */
				status=0;
			}else{						/* Ingen rad hittades */
				status=-1;
			}

			if (mysql_errno(&my_connection)){
				fprintf(stderr,"Error: KUCHK_Retriev error:  %s\n", mysql_error(&my_connection));
			}
		}
		mysql_free_result(res_ptr);
	}
  	mysql_close(&my_connection);
 }
  else {
  	fprintf(stderr,"Error: KUCHK_Connection failed\n");
	if (mysql_errno(&my_connection)){
		fprintf(stderr,"Error: KUCHK_Connection error %d:  %s\n",
		mysql_errno(&my_connection), mysql_error(&my_connection));
	}
  }
if(status == 0){
	fprintf(stdout,"OK: KUCHK_Status = %d\n",status);
}
if(status != 0){
	fprintf(stderr,"Error: KUCHK Kundnr %s finns inte!\n",kundnr);
}
  return status;
}

