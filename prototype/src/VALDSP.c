/***************************************************************************
                          VALDSP.c  -  description
                             -------------------
    begin                : Fre  21  febr	2003
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
	INPUT: 2 st arg. VALUTAID

	Kommando: ./VALDSP valutaid

	Function: Visa all information för valutaid i tabell VALUTA

	OUTPUT: VALUTAID, LAND, BETECKNING, SALJ, KOP samt errornb och error (text)

*/

 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/VALDSP.c,v 1.1 2003/05/08 08:54:13 frazze Exp $ " ;

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
//  int i;

  char temp1[]="SELECT VALUTAID, LAND, BETECKNING, KOP, SALJ FROM VALUTA WHERE VALUTAID = \"";
  char temp2[]="\"";
  char temp3[]=",";
  char temp4[]=")";
  char temp5[200]="";
  char valuta[4];

//  for (i=0;i< argc;i++){
//  	fprintf(stderr,"VALDSPmain argv%d = %s\n",i,argv[i]);
//  }


  strcpy(valuta,argv[1]);

  strcat(temp5,temp1);
/* SELECT VALUTAID, LAND, BETECKNING, KOP, SALJ FROM VALUTA WHERE VALUTAID = "  */
  strcat(temp5,valuta);/* SEK */
/* SELECT VALUTAID, LAND, BETECKNING, KOP, SALJ FROM VALUTA WHERE VALUTAID = "SEK  */
  strcat(temp5,temp2); /*  "     */
/* SELECT VALUTAID, LAND, BETECKNING, KOP, SALJ FROM VALUTA WHERE VALUTAID = "SEK" */
//  fprintf(stderr,"VALDSPmain: temp5 = %s\n",temp5);

  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", "olfix", 0, NULL, 0)){
//  fprintf(stdout,"RGTDSPmain:Connection success\n");

  res = mysql_query(&my_connection,temp5);

  if (res){
	fprintf(stderr,"Error: VALDSP SELECT error: %s\n",mysql_error(&my_connection));
        }else{
	res_ptr=mysql_store_result(&my_connection);
	if (res_ptr){
		sqlrow=mysql_fetch_row(res_ptr);
//	 	fprintf(stdout,"Fetched data....}");
		fprintf(stdout,"1:%s  ",sqlrow[0]);
		fprintf(stdout,"2:%s  ",sqlrow[1]);
		fprintf(stdout,"3:%s  ",sqlrow[2]);
		fprintf(stdout,"4:%s  ",sqlrow[3]);
		fprintf(stdout,"5:%s  ",sqlrow[4]);
		fprintf(stdout,"\n");
	if (mysql_errno(&my_connection))  {
		fprintf(stderr,"Error: VALDSP Retriev error:  %s\n", mysql_error(&my_connection));
		}
	}
	mysql_free_result(res_ptr);
	}
	mysql_close(&my_connection);

  	} else {
    	fprintf(stderr,"Error: VALDSP Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: VALDSP Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
	}
    }
  return EXIT_SUCCESS;
}

