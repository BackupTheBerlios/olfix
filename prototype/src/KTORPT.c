/***************************************************************************
                          KTORPT.c  -  description
                             -------------------
    begin                : Lör 8 mars
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
	INPUT: arid	(Bokföringsår)
	Function: gör  SELECT KTONR,DK,BELOPP FROM VERRAD WHERE ARID = "AC" ORDER BY KTONR;

	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/KTORPT.c,v 1.1 2003/05/08 08:54:08 frazze Exp $ " ;

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
  char temp1[]="SELECT KTONR,DK,BELOPP FROM VERRAD WHERE ARID = \"";
  char temp1b[]=" ORDER BY KTONR";
  char temp2[]="\"";
  char temp3[]=",";
  char temp4[]=")";
  char temp5[200]="";
  char vernr[10];
  char arid[3]="";

  strcpy(arid,argv[1]);

  strcpy(temp5,temp1);
/* SELECT KTONR,DK,BELOPP FROM VERRAD WHERE ARID = "	*/
  strcat(temp5,arid);
/* SELECT KTONR,DK,BELOPP FROM VERRAD WHERE ARID = "AC	*/
  strcat(temp5,temp2);
  strcat(temp5,temp1b);
/* SELECT KTONR,DK,BELOPP FROM VERRAD WHERE ARID = "AC" ORDER BY KTONR	*/

  mysql_init(&my_connection);

  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", "olfix", 0, NULL, 0)){
//  fprintf(stderr,"KTORPT:Connection success\n");

  res = mysql_query(&my_connection,temp5);

  if (res){
	fprintf(stderr,"Error: KTORPT SELECT error: %s\n",mysql_error(&my_connection));
        }else{
	res_ptr=mysql_store_result(&my_connection);
	if (res_ptr){
		i=1;
//		fprintf(stderr,"KTORPT:Retrieved %lu rows\n",(unsigned long)mysql_num_rows(res_ptr));
		fprintf(stdout,"NR_%lu_:",(unsigned long)mysql_num_rows(res_ptr));
		while ((sqlrow=mysql_fetch_row(res_ptr)))  {
		 	//fprintf(stderr,"KTORPT:Fetched data....}");
//			fprintf(stdout,"%d ",i);
			display_row();
			i++;
		}
	if (mysql_errno(&my_connection))  {
		fprintf(stderr,"Error: KTORPT Retriev error:  %s\n", mysql_error(&my_connection));
		}
	}
	mysql_free_result(res_ptr);
	}
	mysql_close(&my_connection);

  	} else {
    	fprintf(stderr,"Error: KTORPT Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: KTORPT Connection error %d:  %s\n",
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
//	fprintf(stdout,"\n");
}
