/***************************************************************************
                          RGTCHK.c  -  description
                             -------------------
    begin                : Ons 6  nov	2002
    version		 : 0.2
    			 : Fre 9 april 2003
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
	INPUT: 2 st arg. USERID och TRNSID

	Kommando: ./RGTCHK userid funktion

	Function: Visa behörghet för userid och funktion i tabell RIGHTS

	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/RGTCHK.c,v 1.2 2003/05/13 03:51:51 janpihlgren Exp $ " ;

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

int main(int argc, char *argv[])
{
  MYSQL my_connection;
  int res;

  char temp1[]="SELECT USERID,TRNSID FROM RIGHTS WHERE USERID = \"";
  char temp2[]="\"";
  char temp3[]=",";
  char temp4[]=")";
  char temp5[200]="";
  char temp6[14]=" AND TRNSID =\"";
  char userid[9];		// 2003-05-09 japi
  char trnsid[9];		// 2003-05-09 japi
  int status;

//  fprintf(stderr,"RGTCHKmain: argv1 = %s, argv2 = %s\n",argv[1],argv[2]);

  strcpy(userid,argv[1]);
  strcpy(trnsid,argv[2]);

  strcat(temp5,temp1);
/* SELECT USERID,TRNSID FROM RIGHTS WHERE USERID = "  */
  strcat(temp5,userid);/* KALLE */
/* SELECT USERID,TRNSID FROM RIGHTS WHERE USERID = "KALLE  */
  strcat(temp5,temp2); /*  "     */
/* SELECT USERID,TRNSID FROM RIGHTS WHERE USERID = "KALLE" */
  strcat(temp5,temp6);
/*  SELECT USERID,TRNSID FROM RIGHTS WHERE USERID = "KALLE" AND TRNSID ="  */
  strcat(temp5,trnsid); /* USERADD */
/* SELECT USERID,TRNSID FROM RIGHTS WHERE USERID = "KALLE" AND TRNSID ="USERADD  */
  strcat(temp5,temp2);
/* SELECT USERID,TRNSID FROM RIGHTS WHERE USERID = "KALLE" AND TRNSID ="USERADD"  */
//  fprintf(stderr,"RGTCHKmain: temp5 = %s\n",temp5);

  mysql_init(&my_connection);

if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", "olfix", 0, NULL, 0)){
//	fprintf(stdout,"RGTCHKmain:Connection success\n");
	res = mysql_query(&my_connection,temp5);
//  	fprintf(stderr,"RGTCHKmain: res= %d\n",res);
  	if (res){
		fprintf(stderr,"Error: RGTCHK_Selection error: %s\n", mysql_error(&my_connection));
	}
	else {
		res_ptr = mysql_store_result(&my_connection);
		if (res_ptr){
//			fprintf(stderr,"RGTCHKmain:Retrieved %lu rows\n",(unsigned long)mysql_num_rows(res_ptr));
			if((unsigned long)mysql_num_rows(res_ptr) > 0){ /* En rad har hittats */
				status=0;
			}else{						/* Ingen rad hittades */
				status=-1;
			}
    			if (mysql_errno(&my_connection)) {
    				fprintf(stderr,"Error: RGTCHK_Retrieve error  %s\n",mysql_error(&my_connection));
			}
		}
		mysql_free_result(res_ptr);
	}
	mysql_close(&my_connection);
}
else{
	fprintf(stderr,"Error: RGTCHK_Connection faild\n");
	if (mysql_errno(&my_connection))  {
		fprintf(stderr,"Error: RGTCHK_Connection error: %d  %s\n",
			mysql_errno(&my_connection),mysql_error(&my_connection));
	}
}
if(status == 0){
	fprintf(stdout,"OK: RGTCHK Status = %d\n",status);
}
if(status != 0){
	fprintf(stderr,"Error: RGTCHK %s har inte behörighet till %s\n",userid,trnsid); //2003-05-09 japi
}
  return status;
}
