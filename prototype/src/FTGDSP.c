/***************************************************************************
                          FTGDSP.c  -  description
                             -------------------
    begin                : Tis  19  nov	2002
    modified		 : Tis 15 april 2003
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
	INPUT: 1 st arg = posttyp

	Kommando: ./FTGDSP posttyp

	Function: Visa information för önskad posttyp

	OUTPUT: POSTTYP, FDATA samt errornb och error (text)

*/

 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/FTGDSP.c,v 1.1 2003/05/08 08:54:06 frazze Exp $ " ;

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
//  int i;

  char temp1[]="SELECT POSTTYP, FDATA FROM FTGDATA WHERE POSTTYP = \"";
  char temp2[]="\"";
  char temp3[]=",";
  char temp4[]=")";
  char temp5[200]="";
  char posttyp[5];

//  for (i=0;i< argc;i++){
//  	fprintf(stderr,"FTGDSPmain argv%d = %s\n",i,argv[i]);
//  }


  strcpy(posttyp,argv[1]);

  strcat(temp5,temp1);
/* SELECT POSTTYP, FDATA FROM FTGDATA WHERE POSTTYP = \"   */
  strcat(temp5,posttyp);/* ADR1 */
/* SELECT POSTTYP, FDATA FROM FTGDATA WHERE POSTTYP = "ADR1   */
  strcat(temp5,temp2); /*  "     */
/* SELECT POSTTYP, FDATA FROM FTGDATA WHERE POSTTYP = "ADR1"   */
//  fprintf(stderr,"FTGDSPmain: temp5 = %s\n",temp5);

  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", "olfix", 0, NULL, 0)){
//  fprintf(stdout,"FTGDSPmain:Connection success\n");

  res = mysql_query(&my_connection,temp5);

  if (res){
	fprintf(stderr,"Error: FTGDSP SELECT error: %s\n",mysql_error(&my_connection));
        }else{
	res_ptr=mysql_store_result(&my_connection);
	if (res_ptr){
		sqlrow=mysql_fetch_row(res_ptr);
//	 	fprintf(stdout,"Fetched data....}");
		fprintf(stdout,"OK: 1:%s  2:%s",sqlrow[0],sqlrow[1]);
//		fprintf(stdout,"2:%s  ",sqlrow[1]);
//		fprintf(stdout,"3:%s  ",sqlrow[2]);
//		fprintf(stdout,"4:%s  ",sqlrow[3]);
//		fprintf(stdout,"\n");
	if (mysql_errno(&my_connection))  {
		fprintf(stderr,"Error: FTGDSP Retriev error:  %s\n", mysql_error(&my_connection));
		}
	}
	mysql_free_result(res_ptr);
	}
	mysql_close(&my_connection);

  	} else {
    	fprintf(stderr,"Error: FTGDSP Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: FTGDSP Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
	}
    }
  return EXIT_SUCCESS;
}

