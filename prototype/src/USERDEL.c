/***************************************************************************
                          USERDEL.c  -  description
                             -------------------
			     Ver: 0.002
    begin                : tis  4  febr	2003
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
	INPUT: 1 st arg. USERID  

	Kommando: ./USERDEL JAPI 

	Function: Radera record i tabell USR

	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/USERDEL.c,v 1.1 2003/05/08 08:54:12 frazze Exp $ " ;

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mysql.h"


int main(int argc, char *argv[])
{
  MYSQL my_connection;
  int res;

  char temp1[]="DELETE FROM USR WHERE USERID = \"";
  char temp2[]="\"";
  char temp3[]=",";
  char temp4[]=")";
  char temp5[200]="";
  char userid[8];
  char namn[30];
  char avd[10];
  char grupp[10];

  strcpy(userid,argv[1]);

  strcat(temp5,temp1);
/* DELETE FROM USR WHERE USERID = "  */
  strcat(temp5,userid);/* KALLE */
/* DELETE FROM USR WHERE USERID = "KALLE  */
  strcat(temp5,temp2); /*  "     */
/* DELETE FROM USR WHERE USERID = "KALLE" */

  mysql_init(&my_connection);

  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", "olfix", 0, NULL, 0)){
//  fprintf("USERDEL_Connection success\n");

    res = mysql_query(&my_connection,temp5);

  	if (!res){
		printf("OK: USERDEL_Deleted %lu rows\n",
			(unsigned long)mysql_affected_rows(&my_connection));
        }else{
	fprintf(stderr,"Error: USERDEL_INSERT error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
        }
	mysql_close(&my_connection);

 } else {
	fprintf(stderr,"Error: USERDEL_Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: USERDEL_Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
	}
    }
  return EXIT_SUCCESS;
}



