/***************************************************************************
                          USERCHG.c  -  description
                             -------------------
			     Ver. 0.2
    begin                : tis 21 jan
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
	INPUT: 4 st arg. USERID, NAMN, AVD och GRUPP (fälten i tabellen USR)

	Kommando: ./USERCHG JAPI "Jan Pihlgren" Ekonomi Redov

	Function: Ändra record i tabell USR

	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/USERCHG.c,v 1.1 2003/05/08 08:54:12 frazze Exp $ " ;

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

  char temp1a[]="UPDATE USR SET NAMN = ";
  char temp1b[]=" WHERE USERID = ";
  char temp1c[]="AVD = ";
  char temp1d[]="GRUPP = ";
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

  strcat(temp5,temp1a);
/* UPDATE USR SET NAMN =   */
  strcat(temp5,temp2);
/*   UPDATE USR SET NAMN = "   */
  strcat(temp5,namn);
/* UPDATE USR SET NAMN ="Karl Andersson   */
  strcat(temp5,temp2); /*  "     */
  strcat(temp5,temp3); /*  ,     */
/* UPDATE USR SET NAMN ="Karl Andersson", */
  strcat(temp5,temp1c);
/* UPDATE USR SET NAMN ="Karl Andersson",AVD =    */
  strcat(temp5,temp2); /*  "     */
  strcat(temp5,avd);
/* UPDATE USR SET NAMN ="Karl Andersson",AVD = "Ekonomi    */
  strcat(temp5,temp2);  /*  "     */
  strcat(temp5,temp3); /*  ,     */
  strcat(temp5,temp1d);
/* UPDATE USR SET NAMN ="Karl Andersson",AVD = "Ekonomi",GRUPP =   */
  strcat(temp5,temp2); /*  "     */
  strcat(temp5,grupp);
/* UPDATE USR SET NAMN = "Karl Andersson",AVD = "Ekonomi",GRUPP = "Stab */
  strcat(temp5,temp2); /*  "     */
/* UPDATE USR SET NAMN = "Karl Andersson",AVD = "Ekonomi",GRUPP = "Stab" */
  strcat(temp5,temp1b);
/* UPDATE USR SET NAMN = "Karl Andersson",AVD = "Ekonomi",GRUPP = "Stab" WHERE USERID = */
  strcat(temp5,temp2); /*  "     */
  strcat(temp5,userid);
  strcat(temp5,temp2); /*  "     */
/* UPDATE USR SET NAMN = "Karl Andersson",AVD = "Ekonomi",GRUPP = "Stab" WHERE USERID = "KALLE"*/

//  fprintf(stderr,"Error: USERCHG temp5=%s\n",temp5);

  mysql_init(&my_connection);

  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", "olfix", 0, NULL, 0)){
  //fprintf(stderr,"USERCHG Connection success\n");

    res = mysql_query(&my_connection,temp5);

  	if (!res){
		fprintf(stdout,"OK: USERCHG Inserted %lu rows\n",
			(unsigned long)mysql_affected_rows(&my_connection));
        }else{
	fprintf(stderr,"Error: USERCHG INSERT error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
	}
	mysql_close(&my_connection);
 } else {
	fprintf(stderr,"Error: USERCHG Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: USERCHG Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
	}
    }
//  fprintf(stdout,"\n");
  return EXIT_SUCCESS;
}


