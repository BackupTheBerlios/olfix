/***************************************************************************
                          RGTDEL.c  -  description
                             -------------------
			     ver 0.003			Felhantering
    begin                : Mån 3 febr	2003
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
	INPUT: 2 st arg. USERID och TRNSID

	Kommando: ./RGTDEL JAPI USERADD

	Function: Radera record i tabell RIGHTS

	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/RGTDEL.c,v 1.1 2003/05/08 08:54:10 frazze Exp $ " ;

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
//  int i;

//  for(i=0;i<argc;i++){
//  	fprintf(stderr,"argv%d = %s\n",i,argv[i]);
//  }



  char temp1[]="DELETE FROM RIGHTS WHERE USERID = \"";
  char temp2[]="\"";
  char temp3[]=",";
  char temp4[]=")";
  char temp5[200]="";
  char temp6[]=" AND TRNSID =\"";
  char userid[9];
  char trnsid[9];

  strcpy(userid,argv[1]);
  strcpy(trnsid,argv[2]);

  strcpy(temp5,temp1);
/* DELETE FROM RIGHTS WHERE USERID = "  */
  strcat(temp5,userid);/* KALLE */
/* DELETE FROM RIGHTS WHERE USERID = "KALLE  */
  strcat(temp5,temp2); /*  "     */
/* DELETE FROM RIGHTS WHERE USERID = "KALLE" */
  strcat(temp5,temp6);
/* DELETE FROM RIGHTS WHERE USERID = "KALLE" AND TRNSID ="  */
  strcat(temp5,trnsid); /* USERADD */
/* DELETE FROM RIGHTS WHERE USERID = "KALLE" AND TRNSID ="USERADD  */
  strcat(temp5,temp2);
/* DELETE FROM RIGHTS WHERE USERID = "KALLE" AND TRNSID ="USERADD"  */
//  fprintf(stderr,"SQLkommando= %s\n",temp5);

  mysql_init(&my_connection);

  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", "olfix", 0, NULL, 0)){
//  fprintf(stdout,"RGTDEL_Connection success\n");

    res = mysql_query(&my_connection,temp5);

  	if (!res){
		fprintf(stdout,"OK: RGTDEL_Deleted %lu rows\n",
			(unsigned long)mysql_affected_rows(&my_connection));
        }else{
	fprintf(stderr,"Error: RGTDEL_INSERT error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
        }
	mysql_close(&my_connection);

 } else {
	fprintf(stderr,"Error: RGTDEL_Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: RGTDEL_Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
	}
    }
  return EXIT_SUCCESS;
}



