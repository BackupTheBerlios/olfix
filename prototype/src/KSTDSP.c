/***************************************************************************
                          KSTDSP.c  -  description
                             -------------------
    begin                : Sön 23 febr
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
	INPUT:
	Function: gör  SELECT * FROM KSTALLE WHERE ARID = "AC" AND KSTALLE = 9037" i databasen olfix

	OUTPUT: ARID, KSTALLE, BENAMNING från tabellen KSTALLE samt
	errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/KSTDSP.c,v 1.1 2003/05/08 08:54:07 frazze Exp $ " ;

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
  char temp1[]="SELECT * FROM KSTALLE WHERE (ARID = \"";
  char temp1b[]=" AND KSTALLE = \"";
  char temp2[]="\"";
  char temp3[]=",";
  char temp4[]=")";
  char temp5[200]="";
  char arid[3];
  char kstalle[5];

  strcpy(arid,argv[1]);
  strcpy(kstalle,argv[2]);


    strcpy(temp5,temp1);
/* SELECT * FROM KSTALLE WHERE (ARID = "  */
  strcat(temp5,arid);/* AC */
/* SELECT * FROM KSTALLE WHERE (ARID = "AC  */
  strcat(temp5,temp2); /*  "     */
/* SELECT * FROM KSTALLE WHERE (ARID = "AC" */
  strcat(temp5,temp1b);
/* SELECT * FROM KSTALLE WHERE (ARID = "AC" AND KSTALLE = " */
  strcat(temp5,kstalle);
/* SELECT * FROM KSTALLE WHERE (ARID = "AC" AND KSTALLE = "9037 */
  strcat(temp5,temp2);
  strcat(temp5,temp4);
/* SELECT * FROM KSTALLE WHERE (ARID = "AC" AND KSTALLE = "9037") */

//  fprintf(stderr,"KSTDSPmain: temp5 = %s\n",temp5);

  mysql_init(&my_connection);

  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", "olfix", 0, NULL, 0)){
//  fprintf(stderr,"KSTDSP:Connection success\n");

  res = mysql_query(&my_connection,temp5);

  if (res){
	fprintf(stderr,"Error: KSTDSP SELECT error: %s\n",mysql_error(&my_connection));
        }else{
	res_ptr=mysql_store_result(&my_connection);
	if (res_ptr){
		sqlrow=mysql_fetch_row(res_ptr);
//	 	fprintf(stdout,"Fetched data....}");
		fprintf(stdout,"1:%s  ",sqlrow[0]);
		fprintf(stdout,"2:%s  ",sqlrow[1]);
		fprintf(stdout,"3:%s  ",sqlrow[2]);
		fprintf(stdout,"\n");
	if (mysql_errno(&my_connection))  {
		fprintf(stderr,"Error: KSTDSP Retriev error:  %s\n", mysql_error(&my_connection));
		}
	}
	mysql_free_result(res_ptr);
	}
	mysql_close(&my_connection);

  	} else {
    	fprintf(stderr,"Error: KSTDSP Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: KSTDSP Connection error %d:  %s\n",
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
