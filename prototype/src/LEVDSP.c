/***************************************************************************
                          LEVDSP.c  -  description
                             -------------------
			     Ver: 0.02
    begin                : Mån  30  juni 2003
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
	INPUT: 1 st arg. LEVNR

	Kommando: ./LEVDSP levnr

	Function: Visa all information på ett konto i tabell KTOPLAN

	OUTPUT: LEVNR LEVORGNR LEVNAMN LEVADRESS LEVPOSTNR LEVPOSTADR LEVLAND LEVTFNNR LEVFAXNR LEVTELEX LEVEMAIL LEVREFERENT LEVREFTFN LEVMOMSKOD LEVSKULD LEVKONTO LEVVALUTA BETALVILKOR
	samt errornb och error (text)

***************************************************************************/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/LEVDSP.c,v 1.1 2003/09/28 04:30:50 janpihlgren Exp $ " ;

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
//  int num_fields;
//  int field_count;

  char temp1[]="SELECT * FROM LEVREG WHERE (LEVNR = \"";
  char temp2[]="\"";
//  char temp3[]=",";
  char temp4[]=")";
  char temp5[200]="";
  char levnr[11];

//  for (i=0;i< argc;i++){
//  	fprintf(stderr,"LEVDSP argv%d = %s\n",i,argv[i]);
//  }

  strcpy(levnr,argv[1]);
  strcat(temp5,temp1);
/* SELECT * FROM LEVREG WHERE (LEVNR = "	*/
  strcat(temp5,levnr);/* 1234 */
/* SELECT * FROM LEVREG WHERE (LEVNR = "1234	*/
  strcat(temp5,temp2); /*  "     */
/* SELECT * FROM LEVREG WHERE (LEVNR = "1234"	*/
  strcat(temp5,temp4); /*  )     */
/* SELECT * FROM LEVREG WHERE (LEVNR = "1234")	*/
  strcat(temp5,"\n");
//  fprintf(stderr,"LEVDSP temp5 = %s\n",temp5);

  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", "olfix", 0, NULL, 0)){
//  	fprintf(stdout,"LEVDSP_Connection success\n");
  	res = mysql_query(&my_connection,temp5);
//  	fprintf(stderr,"LEVDSP hit res=%d\n",res);
  	if (res){
//  		fprintf(stderr,"LEVDSP ERROR\n");
		fprintf(stderr,"Error: LEVDSP SELECT errno: %d\n",mysql_errno(&my_connection));
        }
	else{
		res_ptr=mysql_store_result(&my_connection);
		num_rows = mysql_affected_rows(&my_connection);
//		fprintf(stderr,"num_rows=%d\n",num_rows);
//		if (res_ptr){
		if(num_rows != 0){
			sqlrow=mysql_fetch_row(res_ptr);
			fprintf(stdout,"OK: ");
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
			fprintf(stdout,"13:%s  ",sqlrow[12]);
			fprintf(stdout,"14:%s  ",sqlrow[13]);
			fprintf(stdout,"15:%s  ",sqlrow[14]);
			fprintf(stdout,"16:%s  ",sqlrow[15]);
			fprintf(stdout,"17:%s  ",sqlrow[16]);
			fprintf(stdout,"18:%s  ",sqlrow[17]);
			fprintf(stdout,"19:%s  ",sqlrow[18]);
			fprintf(stdout,"20:%s  ",sqlrow[19]);
			fprintf(stdout,"21:%s  ",sqlrow[20]);
//			fprintf(stdout,"22:%s  ",sqlrow[21]);
//			fprintf(stdout,"23:%s  ",sqlrow[22]);
			fprintf(stdout,"\n");
		}
		else{
			fprintf(stderr,"Error: LEVDSP Data saknas:  %s\n", mysql_error(&my_connection));
		}
		if (mysql_errno(&my_connection))  {
		fprintf(stderr,"Error: LEVDSP Retriev error:  %s\n", mysql_error(&my_connection));
		}
	}
	mysql_free_result(res_ptr);
    	mysql_close(&my_connection);
  }
  else {
    	fprintf(stderr,"Error: LEVDSP Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: LEVDSP Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
	}
    }
  return EXIT_SUCCESS;
}
