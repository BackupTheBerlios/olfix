/***************************************************************************
                          BARDSP.c  -  description
                             -------------------
    begin                : Tis  3  dec	2002
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
	INPUT: arid

	Kommando: ./BARDSP arid

	Function: Hämta data för angivet bokföringsår från BOKFAR

	OUTPUT: data, errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/BARDSP.c,v 1.1 2003/05/08 08:54:04 frazze Exp $ " ;

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

  char temp1[]="SELECT * FROM BOKFAR WHERE ARID = \"";
  char temp2[]="\"";
  char temp3[]=",";
  char temp4[]=")";
  char temp5[200]="";
  char arid[8];
  char vernr[10];

  strcpy(arid,argv[1]);

  strcat(temp5,temp1);
/* SELECT VERNR FROM BOKFAR WHERE ARID = "  */
  strcat(temp5,arid);/* AC */
/* SELECT VERNR FROM BOKFAR WHERE ARID = "AC  */
  strcat(temp5,temp2); /*  "     */
/* SELECT VERNR FROM BOKFAR WHERE ARID = "AC" */
//  fprintf(stderr,"BARDSPmain: temp5 = %s\n",temp5);

  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", "olfix", 0, NULL, 0)){
//  fprintf(stdout,"BARDSPmain:Connection success\n");
  	res = mysql_query(&my_connection,temp5);
  	if (res){
		fprintf(stderr,"Error: BARDSP SELECT error: %s\n",mysql_error(&my_connection));
  	}
  	else{
		res_ptr=mysql_store_result(&my_connection);
		if (res_ptr){
//			fprintf(stderr,"Retrieved %lu rows\n",(unsigned long)mysql_num_rows(res_ptr));
			if(mysql_num_rows(res_ptr)>0){
				sqlrow=mysql_fetch_row(res_ptr);
				fprintf(stdout,"OK: Status = 0  ");
				fprintf(stdout,"ARID:%s  ",sqlrow[0]);
				fprintf(stdout,"BENAMN:%s  ",sqlrow[1]);
				fprintf(stdout,"ARSTART:%s  ",sqlrow[2]);
				fprintf(stdout,"ARSLUT:%s  ",sqlrow[3]);
				fprintf(stdout,"ARLAST:%s  ",sqlrow[4]);
				fprintf(stdout,"SVERDAT:%s  ",sqlrow[5]);
				fprintf(stdout,"VERNR:%s  ",sqlrow[6]);
				fprintf(stdout,"KTOPLAN:%s  ",sqlrow[7]);
				fprintf(stdout,"BESKATT:%s  ",sqlrow[8]);
				fprintf(stdout,"\n");
			}
			else{
				fprintf(stderr,"Error: Status = -1\n");
			}
			if (mysql_errno(&my_connection)){
				fprintf(stderr,"Error: BARDSP Retriev error:  %s\n", mysql_error(&my_connection));
			}
		}
		mysql_free_result(res_ptr);
	}
  	mysql_close(&my_connection);
  	}
  else {
  	fprintf(stderr,"Error: BARDSP Connection failed\n");
	if (mysql_errno(&my_connection)){
		fprintf(stderr,"Error: BARDSP Connection error %d:  %s\n",
		mysql_errno(&my_connection), mysql_error(&my_connection));
	}
  }
  return EXIT_SUCCESS;
}

