/***************************************************************************
                          USERADD.c  -  description
                             -------------------
    begin                : tis 8 okt 
    update		 : mars 19 2003
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
	INPUT: 4 st arg. USERID, NAMN, AVD och GRUPP (f�lten i tabellen USR)

	Kommando: ./USERADD JAPI "Jan Pihlgren" Ekonomi Redov

	Function: Add record i tabell USR

	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/USERADD.c,v 1.1 2003/05/08 08:54:11 frazze Exp $ " ;

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

  char temp1[]="INSERT INTO USR(USERID,NAMN,AVD,GRUPP) VALUES (\"";
  char temp2[]="\"";
  char temp3[]=",";
  char temp4[]=")";
  char temp5[200]="";
  char userid[8];
  char namn[30];
  char avd[10];
  char grupp[10];

  strcpy(userid,argv[1]);
  strcpy(namn,argv[2]);
  strcpy(avd,argv[3]);
  strcpy(grupp,argv[4]);

  strcat(temp5,temp1);
/* INSERT INTO USR(USERID,NAMN,AVD,GRUPP) VALUES ("  */
  strcat(temp5,userid);/* KALLE */
/* INSERT INTO USR(USERID,NAMN,AVD,GRUPP) VALUES ("JAPI  */
  strcat(temp5,temp2); /*  "     */
  strcat(temp5,temp3); /*  ,     */
  strcat(temp5,temp2); /*  "     */
/* INSERT INTO USR(USERID,NAMN,AVD,GRUPP) VALUES ("JAPI","  */
  strcat(temp5,namn);/* Jan Pihlgren  */
/* INSERT INTO  USR(USERID,NAMN,AVD,GRUPP) VALUES ("JAPI","Jan Pihlgren  */
  strcat(temp5,temp2); /*  "     */
  strcat(temp5,temp3); /*  ,     */
  strcat(temp5,temp2); /*  "     */
/* INSERT INTO  USR(USERID,NAMN,AVD,GRUPP) VALUES ("JAPI","Jan Pihlgren","  */
  strcat(temp5,avd);
/* INSERT INTO  USR(USERID,NAMN,AVD,GRUPP) VALUES ("JAPI","Jan Pihlgren","Ekonomi   */
  strcat(temp5,temp2); /*  "     */
  strcat(temp5,temp3); /*  ,     */
  strcat(temp5,temp2); /*  "     */
/* INSERT INTO  USR(USERID,NAMN,AVD,GRUPP) VALUES ("JAPI","Jan Pihlgren","Ekonomi","  */
  strcat(temp5,grupp);
/* INSERT INTO  USR(USERID,NAMN,AVD,GRUPP) VALUES ("JAPI","Jan Pihlgren","Ekonomi","Redov  */
  strcat(temp5,temp2); /*  "     */
  strcat(temp5,temp4); /*  )     */
/* INSERT INTO  USR(USERID,NAMN,AVD,GRUPP) VALUES ("JAPI","Jan Pihlgren","Ekonomi","Redov")  */

  mysql_init(&my_connection);

  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", "olfix", 0, NULL, 0)){
  // fprintf(stderr,"OK: USERADD Connection success\n");

    res = mysql_query(&my_connection,temp5);

  	if (!res){
		fprintf(stdout,"OK: USERADD Inserted %lu rows\n",
			(unsigned long)mysql_affected_rows(&my_connection));
        }else{
/*	fprintf(stderr,"Error: USERADD INSERT error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
*/
	fprintf(stderr,"Error: USERADD INSERT error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
	}
	mysql_close(&my_connection);

 } else {
	fprintf(stderr,"Error: USERADD Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: USERADD Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
	}
    }
  return EXIT_SUCCESS;
}


