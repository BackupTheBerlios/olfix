/***************************************************************************
                          TRNSADD.c  -  description
                             -------------------
    begin                : sön 20 okt 
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
	INPUT: 2 st arg. TRNSID och TRNSTXT (fälten i tabellen TRANSID)
	Function: Add record i tabell TRANSID

	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/TRNSADD.c,v 1.1 2003/05/08 08:54:11 frazze Exp $ " ;

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

  char temp1[]="INSERT INTO TRANSID(TRNSID,TRNSTXT) VALUES (\"";
  char temp2[]="\"";
  char temp3[]=",";
  char temp4[]=")";
  char temp5[200]="";
  char trnsid[8];
  char trnstxt[60];

  strcpy(trnsid,argv[1]);
  strcpy(trnstxt,argv[2]);

  strcat(temp5,temp1);
/* INSERT INTO TRANSID(TRNSID,TRNSTXT) VALUES (TRNSID,TRNSTXT) VALUES ("  */
  strcat(temp5,trnsid);/* VERADD */
/* INSERT INTO TRANSID(TRNSID,TRNSTXT) VALUES (TRNSID,TRNSTXT) VALUES ("VERADD  */
  strcat(temp5,temp2); /*  "     */
  strcat(temp5,temp3); /*  ,     */
  strcat(temp5,temp2); /*  "     */
/* INSERT INTO TRANSID(TRNSID,TRNSTXT) VALUES (TRNSID,TRNSTXT) VALUES ("VERADD","  */
  strcat(temp5,trnstxt);/* förklarande text  */
/* INSERT INTO TRANSID(TRNSID,TRNSTXT) VALUES (TRNSID,TRNSTXT) VALUES ("VERADD","add rec ...  */
  strcat(temp5,temp2); /*  "     */
  strcat(temp5,temp4); /*  )     */
/*  strcat(temp5,temp2); /*  "     */
/* INSERT INTO TRANSID(TRNSID,TRNSTXT) VALUES (TRNSID,TRNSTXT) VALUES ("VERADD","add rec ...")  */

  mysql_init(&my_connection);

  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", "olfix", 0, NULL, 0)){
//  fprintf(stdout,"OK: TRNSADD Connection success\n");
  //fprintf(stderr,"TRNSADD SQLfråga  %s\n TRNSID = %s\n TRNSTXT = %s\n",temp5,trnsid,trnstxt);
/*  res = mysql_query(&my_connection,"INSERT INTO TRANSID(TRNSID,TRNSTXT) VALUES ("); */
    res = mysql_query(&my_connection,temp5);

  	if (!res){
		fprintf(stdout,"OK: Inserted %lu rows\n",
			(unsigned long)mysql_affected_rows(&my_connection));
        }else{
	fprintf(stderr,"Error: TRNSADD INSERT error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
        }
	mysql_close(&my_connection);

 } else {
	fprintf(stderr,"Error: TRNSADD Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: TRNSADD Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
	}
    }
  return EXIT_SUCCESS;
}

