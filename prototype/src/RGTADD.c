/***************************************************************************
                          RGTADD.c  -  description
                             -------------------
    				Ver 0.2
    begin                : fre 24 jan
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
	Tabellen RIGHTS är korsreferens mellan tabellerna USR och TRANSID
	och bestämmer vem som har behörighet (rights) till viss transaktionstyp */

/*	INPUT: 2 st arg. TRNSID och USERID (fälten i tabellen RIGHTS)
	Function: Add record i tabell RIGHTS

	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/RGTADD.c,v 1.1 2003/05/08 08:54:10 frazze Exp $ " ;

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

  char temp1[]="INSERT INTO RIGHTS(USERID,TRNSID) VALUES (\"";
  char temp2[]="\"";
  char temp3[]=",";
  char temp4[]=")";
  char temp5[200]="";
  char userid[9];
  char trnsid[9];

  strcpy(userid,argv[1]);
  strcpy(trnsid,argv[2]);
  fprintf(stderr,"argv1=%s argv2=%s\n",argv[1],argv[2]);
  strcat(temp5,temp1);
/* INSERT INTO RIGHTS(USERID,TRNSID) VALUES (USERID,TRNSID) VALUES ("  */
  strcat(temp5,userid);/* KALLE */
/* INSERT INTO RIGHTS(USERID,TRNSID) VALUES (USERID,TRNSID) VALUES ("KALLE  */
  strcat(temp5,temp2); /*  "     */
  strcat(temp5,temp3); /*  ,     */
  strcat(temp5,temp2); /*  "     */
/* INSERT INTO RIGHTS(USERID,TRNSID) VALUES (USERID,TRNSID) VALUES ("KALLE","  */
  strcat(temp5,trnsid);/* KTOADD  */
/* INSERT INTO RIGHTS(USERID,TRNSID) VALUES (USERID,TRNSID) VALUES ("KALLE","KTOADD  */
  strcat(temp5,temp2); /*  "     */
  strcat(temp5,temp4); /*  )     */
/* INSERT INTO RIGHTS(USERID,TRNSID) VALUES (USERID,TRNSID) VALUES ("KALLE","KTOADD")  */

  mysql_init(&my_connection);

  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", "olfix", 0, NULL, 0)){
//  fprintf(stdout,"OK: RGTADD_Connection success\n");
//  printf("SQLfråga  %s\n USERID = %s\n TRNSID = %s\n",temp5,userid,trnsid);
    res = mysql_query(&my_connection,temp5);

  	if (!res){
		fprintf(stdout,"OK: RGTADD_Inserted %lu rows\n",
			(unsigned long)mysql_affected_rows(&my_connection));
        }else{
	fprintf(stderr,"Error: RGTADD_INSERT error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
        }
	mysql_close(&my_connection);

 } else {
	fprintf(stderr,"Error: RGTADD_Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: RGTADD_Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
	}
    }
  return EXIT_SUCCESS;
}

