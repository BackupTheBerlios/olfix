/***************************************************************************
                          TRHDADD.c  -  description
                             -------------------
    begin                : fre 1 nov
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
	INPUT: 2 st arg. TRNSID, TID, USERID och TRNSDATA (fälten i tabellen TRHD)
	Function: Add record i tabell TRHD

	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/TRHDADD.c,v 1.1 2003/05/08 08:54:11 frazze Exp $ " ;

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mysql.h"
#define TRNSSIZE 255


int main(int argc, char *argv[])
{
  MYSQL my_connection;
  int res;

  char temp1[]="INSERT INTO TRHD(TRNSID,TID,USERID,TRNSDATA) VALUES (\"";
  char temp2[]="\"";
  char temp3[]=",";
  char temp4[]=")";
  char temp5[TRNSSIZE+200]="";
  char trnsid[8];
  char trnstid[21];
  char userid[8];
  char trnstxt[TRNSSIZE];


//  fprintf(stderr,"TRHDADD:argv0=%s\n",argv[0]);
//  fprintf(stderr,"TRHDADD:argv1=%s\n",argv[1]);
//  fprintf(stderr,"TRHDADD:argv2=%s\n",argv[2]);
//  fprintf(stderr,"TRHDADD:argv3=%s\n",argv[3]);
//  fprintf(stderr,"TRHDADD:argv4=%s\n",argv[4]);
//  fprintf(stderr,"TRHDADD:argv5=%s\n",argv[5]);



  strcpy(trnsid,argv[1]);
  strcpy(trnstid,argv[2]);
  strcpy(userid,argv[3]);
  strcpy(trnstxt,argv[4]);

  strcat(temp5,temp1);
/* INSERT INTO TRHD(TRNSID,TID,USERID,TRNSDATA) VALUES ("  */
  strcat(temp5,trnsid);/* VERADD */
/* INSERT INTO TRHD(TRNSID,TID,USERID,TRNSDATA) VALUES ("VERADD  */
  strcat(temp5,temp2); /*  "     */
  strcat(temp5,temp3); /*  ,     */
  strcat(temp5,temp2); /*  "     */
/* INSERT INTO TRHD(TRNSID,TID,USERID,TRNSDATA) VALUES ("VERADD","  */
  strcat(temp5,trnstid);/* timestamp  */
  strcat(temp5,temp2); /*  "     */
  strcat(temp5,temp3); /*  ,     */
  strcat(temp5,temp2); /*  "     */
/* INSERT INTO TRHD(TRNSID,TID,USERID,TRNSDATA) VALUES ("VERADD","2002-11-01_08:56:51"," */
  strcat(temp5,userid);
/* INSERT INTO TRHD(TRNSID,TID,USERID,TRNSDATA) VALUES ("VERADD","2002-11-01_08:56:51","olfix */
  strcat(temp5,temp2); /*  "     */
  strcat(temp5,temp3); /*  ,     */
  strcat(temp5,temp2); /*  "     */
/* INSERT INTO TRHD(TRNSID,TID,USERID,TRNSDATA) VALUES ("VERADD","2002-11-01_08:56:51","olfix"," */
  strcat(temp5,trnstxt);
/* INSERT INTO TRHD(TRNSID,TID,USERID,TRNSDATA) VALUES ("VERADD","2002-11-01_08:56:51","olfix","1120 -:- K -:- 2500 */
//  strcat(temp5,temp2);/*  "     */
  strcat(temp5,temp4);/*  )     */
/* INSERT INTO TRHD(TRNSID,TID,USERID,TRNSDATA) VALUES ("VERADD","2002-11-01_08:56:51","olfix","1120 -:- K -:- 2500") */
//  fprintf(stderr,"TRHDADD:temp5=%s\n",temp5);
  mysql_init(&my_connection);

  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", "olfix", 0, NULL, 0)){
  //fprintf(stdout,"OK: TRHDADD Connection success\n");
  //fprintf(stderr,"SQLfråga  %s\n TRNSID = %s\n TRNSTXT = %s\n",temp5,trnsid,trnstxt);
    res = mysql_query(&my_connection,temp5);

  	if (!res){
		fprintf(stdout,"OK: TRHDADD Inserted %lu rows\n",
			(unsigned long)mysql_affected_rows(&my_connection));
        }else{
	fprintf(stderr,"Error: TRHDADD INSERT error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
        }
	mysql_close(&my_connection);

 } else {
	fprintf(stderr,"Error: TRHDADD Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: TRHDADD Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
	}
    }
  return EXIT_SUCCESS;
}

