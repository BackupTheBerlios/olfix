/***************************************************************************
                          RGTDSP.c  -  description
                             -------------------
			     Ver: 0.2
    begin                : Mån  20  jan	2003
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
	INPUT: 1 st arg. USERID

	Kommando: ./RGTDSP userid

	Function: Visa behörgheter för userid i tabell RIGHTS

	OUTPUT: USERID och TRNSID eller errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/RGTDSP.c,v 1.1 2003/05/08 08:54:10 frazze Exp $ " ;

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

void display_row();

int main(int argc, char *argv[])
{

//  MYSQL my_connection;
  int res,i;

  char temp1[]="SELECT USERID,TRNSID FROM RIGHTS WHERE USERID = \"";
  char temp2[]="\"";
  char temp3[]=",";
  char temp4[]=")";
  char temp5[200]="";
  char userid[8];

  strcpy(userid,argv[1]);

  strcat(temp5,temp1);
/* SELECT USERID,TRNSID FROM RIGHTS WHERE USERID = "  */
  strcat(temp5,userid);/* KALLE */
/* SELECT USERID,TRNSID FROM RIGHTS WHERE USERID = "KALLE  */
  strcat(temp5,temp2); /*  "     */
/* SELECT USERID,TRNSID FROM RIGHTS WHERE USERID = "KALLE" */
//  fprintf(stderr,"RGTDSP: temp5 = %s\n",temp5);

  mysql_init(&my_connection);

  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", "olfix", 0, NULL, 0)){
//  fprintf(stdout,"RGTDSP:Connection success\n");

  res = mysql_query(&my_connection,temp5);

  if (res){
	fprintf(stderr,"Error: RGTDSP SELECT error: %s\n",mysql_error(&my_connection));
        }else{
	res_ptr=mysql_store_result(&my_connection);
	if (res_ptr){
		i=1;
		fprintf(stdout,"NR_%lu_:",(unsigned long)mysql_num_rows(res_ptr));
		while ((sqlrow=mysql_fetch_row(res_ptr)))  {
		 	//printf("RGTDSP:Fetched data....}");
			display_row();
			i++;
		}
	if (mysql_errno(&my_connection))  {
		fprintf(stderr,"Error: RGTDSP Retriev error:  %s\n", mysql_error(&my_connection));
		}
	}
	mysql_free_result(res_ptr);
	}
	mysql_close(&my_connection);

  	} else {
    	fprintf(stderr,"Error: RGTDSP Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: RGTDSP Connection error %d:  %s\n",
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


