/***************************************************************************
                          KULST.c  -  description
                             -------------------
			     Ver: 0.1
    begin                : Mån  13  aug 2003
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
	INPUT: inga argument

	Kommando: ./KULST levnr

	Function: Visa all information på ett konto i tabell KTOPLAN

	OUTPUT: LEVNR LEVNAMN 
	samt errornb och error (text)

***************************************************************************/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/KULST.c,v 1.1 2003/10/07 06:40:13 janpihlgren Exp $ " ;

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mysql.h"
  void display_row();
  MYSQL my_connection;
  MYSQL_RES *res_ptr;
  MYSQL_ROW sqlrow;

int main(int argc, char *argv[])
{
  int res,i;
//  int num_rows;
//  int num_fields;
//  int field_count;

  char temp1[]="SELECT KUNDNR,NAMN FROM KUNDREG ORDER BY NAMN";
//  char temp2[]="\"";
//  char temp3[]=",";
//  char temp4[]=")";
  char temp5[200]="";
//  char levnr[11];

//  for (i=0;i< argc;i++){
//  	fprintf(stderr,"KULST argv%d = %s\n",i,argv[i]);
//  }

  strcpy(temp5,temp1);
/* "SELECT LEVNR,LEVNAMN FROM LEVREG ORDER BY LEVNAMN"	*/

  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", "olfix", 0, NULL, 0)){
//  	fprintf(stdout,"KULST_Connection success\n");
  	res = mysql_query(&my_connection,temp5);
//  	fprintf(stderr,"KULST hit res=%d\n",res);
  	if (res){
//  		fprintf(stderr,"KULST ERROR\n");
		fprintf(stderr,"Error: KULST SELECT errno: %d\n",mysql_errno(&my_connection));
        }else{
		res_ptr=mysql_store_result(&my_connection);
		if (res_ptr){
			i=1;
//			fprintf(stdout,"KULST:Retrieved %lu rows\n",(unsigned long)mysql_num_rows(res_ptr));
			fprintf(stdout,"OK: NR_%lu_:",(unsigned long)mysql_num_rows(res_ptr));
			while ((sqlrow=mysql_fetch_row(res_ptr)))  {
		 		//printf("KULST:Fetched data....}");
				display_row();
				i++;
			}
			fprintf(stdout,"\n");
			if (mysql_errno(&my_connection))  {
				fprintf(stderr,"Error: KULST Retriev error:  %s\n", mysql_error(&my_connection));
			}
		}
	mysql_free_result(res_ptr);
	}
    	mysql_close(&my_connection);
  }
  else {
    	fprintf(stderr,"Error: KULST Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: KULST Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
	}
    }
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
//	fprintf(stdout,"\n");
}
