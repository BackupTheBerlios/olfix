/***************************************************************************
                          KTODSP.c  -  description
                             -------------------
    begin                : Fre  31  jan	2003
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
 ***************************************************************************/
/*
	INPUT: 2 st arg. ARID, KTONR

	Kommando: ./KTODSP arid ktonr

	Function: Visa all information på ett konto i tabell KTOPLAN

	OUTPUT: ARID, KTONR, BENAMNING, MANUELL, MOMSKOD, SRUNR,
		KSTALLE, PROJEKT, SUBKTO, KTOPLAN, IB, UB
		samt errornb och error (text)

***************************************************************************/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/KTODSP.c,v 1.1 2003/05/08 08:54:08 frazze Exp $ " ;

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
  int res;
  int num_rows;
  int num_fields;
  int field_count;

  char temp1[]="SELECT * FROM KTOPLAN WHERE (ARID = \"";
  char temp1b[]=" AND KTONR = \"";
  char temp2[]="\"";
  char temp3[]=",";
  char temp4[]=")";
  char temp5[200]="";
  char arid[3];
  char ktonr[5];

//  for (i=0;i< argc;i++){
//  	fprintf(stderr,"KTODSPmain argv%d = %s\n",i,argv[i]);
//  }

  strcpy(arid,argv[1]);
  strcpy(ktonr,argv[2]);

  strcat(temp5,temp1);
/* SELECT * FROM KTOPLAN WHERE (ARID = "	*/
  strcat(temp5,arid);/* AC */
/* SELECT * FROM KTOPLAN WHERE (ARID = "AC	*/
  strcat(temp5,temp2); /*  "     */
/* SELECT * FROM KTOPLAN WHERE (ARID = "AC"	*/
  strcat(temp5,temp1b);
/* SELECT * FROM KTOPLAN WHERE (ARID = "AC" AND KTONR = "	*/
  strcat(temp5,ktonr);/* 1020 */
/* SELECT * FROM KTOPLAN WHERE (ARID = "AC" AND KTONR = "1020	*/
  strcat(temp5,temp2); /*  "     */
/* SELECT * FROM KTOPLAN WHERE (ARID = "AC" AND KTONR = "1020"	*/
  strcat(temp5,temp4); /*  )     */
/* SELECT * FROM KTOPLAN WHERE (ARID = "AC" AND KTONR = "1020")	*/
  strcat(temp5,"\n");
//  fprintf(stderr,"KTODSP temp5 = %s\n",temp5);

  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", "olfix", 0, NULL, 0)){
//  	fprintf(stdout,"KTODSP_Connection success\n");
  	res = mysql_query(&my_connection,temp5);
//	res = mysql_query(&my_connection,"SELECT ARID,KTONR,BENAMNING,MANUELL,MOMSKOD,SRUNR,KSTALLE,PROJEKT,SUBKTO,KTOPLAN,IB,UB FROM KTOPLAN WHERE (ARID=\"AC\" AND KTONR=\"1030\")");
//  	fprintf(stderr,"KTODSP hit res=%d\n",res);
  	if (res){
//  		fprintf(stderr,"KTODSP ERROR\n");
		fprintf(stderr,"Error: KTODSP_SELECT errno: %d\n",mysql_errno(&my_connection));
		fprintf(stderr,"Error: KTODSP_SELECT error: %s\n",mysql_error(&my_connection));
        }
	else{
		res_ptr=mysql_store_result(&my_connection);
		num_rows = mysql_affected_rows(&my_connection);
//		fprintf(stderr,"num_rows=%d\n",num_rows);
//		if (res_ptr){
		if(num_rows != 0){
			sqlrow=mysql_fetch_row(res_ptr);
			fprintf(stdout,"1:%s  ",sqlrow[0]);
			fprintf(stdout,"2:%s  ",sqlrow[1]);
			fprintf(stdout,"3:%s  ",sqlrow[2]);
			fprintf(stdout,"4:%s  ",sqlrow[3]);
			fprintf(stdout,"5:%s  ",sqlrow[4]);
			fprintf(stdout,"6:%s  ",sqlrow[5]);
			fprintf(stdout,"7:%s  ",sqlrow[6]);
			fprintf(stdout,"8:%s  ",sqlrow[7]);
			fprintf(stdout,"9:%s  ",sqlrow[8]);
			fprintf(stdout,"10:%s  ",sqlrow[9]);
			fprintf(stdout,"11:%s  ",sqlrow[10]);
			fprintf(stdout,"12:%s  ",sqlrow[11]);
			fprintf(stdout,"\n");
		}
		else{
			fprintf(stderr,"Error: KTODSP_Data saknas:  %s\n", mysql_error(&my_connection));
		}
		if (mysql_errno(&my_connection))  {
		fprintf(stderr,"Error: KTODSP_Retriev error:  %s\n", mysql_error(&my_connection));
		}
	}
	mysql_free_result(res_ptr);
    	mysql_close(&my_connection);
  }
  else {
    	fprintf(stderr,"Error: KTODSP_Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: KTODSP_Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
	}
    }
  return EXIT_SUCCESS;
}
