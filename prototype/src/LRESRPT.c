/***************************************************************************
                          LRESPT.c  -  description
                             -------------------
    begin                : Sön 29 jun
    ver			 : 0.1
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
 ***************************************************************************/

/*
	INPUT: inget
	Function: gör  	SELECT LEVRESK.EXPIREDATUM,LEVRESK.LEVNR,LEVREG.LEVNAMN,LEVRESK.FAKTBELOPP
			FROM LEVRESK
                        LEFT JOIN LEVREG ON LEVREG.LEVNR = LEVRESK.LEVNR
			WHERE LEVRESK.BETALD = "N"
			ORDER BY LEVRESK.EXPIREDATUM;

	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/LRESRPT.c,v 1.1 2003/09/28 04:34:24 janpihlgren Exp $ " ;

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include "mysql.h"

  MYSQL my_connection;
  MYSQL_RES *res_ptr;
  MYSQL_ROW sqlrow;


void display_row();

int main(int argc, char *argv[])
{
  int res,i;
  char temp1[]="SELECT LEVRESK.EXPIREDATUM,LEVRESK.LEVNR,LEVREG.LEVNAMN,LEVRESK.FAKTURANR,LEVRESK.FAKTBELOPP FROM LEVRESK ";
  char temp1b[]="LEFT JOIN LEVREG ON LEVREG.LEVNR = LEVRESK.LEVNR ";
  char temp1c[]="WHERE LEVRESK.BETALD = \"N\"" ;
  char temp1d[]="ORDER BY LEVRESK.EXPIREDATUM, LEVRESK.FAKTURANR";
//  char temp2[]="\"";
//  char temp3[]=",";
//  char temp4[]=")";
  char temp5[200]="";

  strcpy(temp5,temp1);
  strcat(temp5,temp1b);
  strcat(temp5,temp1c);
  strcat(temp5,temp1d);

//  fprintf(stderr,"temp5 = %s\n",temp5);

  mysql_init(&my_connection);

  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", "olfix", 0, NULL, 0)){
//  fprintf(stderr,"LRESRPT:Connection success\n");

  res = mysql_query(&my_connection,temp5);

  if (res){
	fprintf(stderr,"Error: LRESRPT SELECT error: %s\n",mysql_error(&my_connection));
        }else{
	res_ptr=mysql_store_result(&my_connection);
	if (res_ptr){
		i=1;
//		fprintf(stderr,"LRESRPT:Retrieved %lu rows\n",(unsigned long)mysql_num_rows(res_ptr));
		fprintf(stdout,"NR_%lu_:",(unsigned long)mysql_num_rows(res_ptr));
		while ((sqlrow=mysql_fetch_row(res_ptr)))  {
		 	//fprintf(stderr,"LRESRPT:Fetched data....}");
//			fprintf(stdout,"%d ",i);
			display_row();
			i++;
		}
	if (mysql_errno(&my_connection))  {
		fprintf(stderr,"Error: LRESRPT Retriev error:  %s\n", mysql_error(&my_connection));
		}
	}
	mysql_free_result(res_ptr);
	}
	mysql_close(&my_connection);

  	} else {
    	fprintf(stderr,"Error: LRESRPT Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: LRESRPT Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
	}
    }
  fprintf(stdout,"\n");
  return EXIT_SUCCESS;
}

void display_row()
{
   unsigned int field_count;
   field_count=0;
	while (field_count < mysql_field_count(&my_connection))
	{
		fprintf(stdout,"%s_:",sqlrow[field_count]);
		field_count++;
	}
}
