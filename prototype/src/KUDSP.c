/***************************************************************************
                          KUDSP.c  -  description
                             -------------------
    begin                : Tors  2  okt	2003
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
	INPUT: 1 st arg.

	Kommando: ./KUDSP kundnr

	Function: Visa all information på ett konto i tabell KTOPLAN

	OUTPUT:	41 st fält,
		KUNDNR, KUNDORGNR, NAMN, ADRESS, POSTNR, POSTADR, LAND, TFNNR, EMAILADR, FAXNR,
		ERREFERENT, ERREFTFNNR, ERREFEMAIL, SELJARE, FRITEXT, VALUTA, BETALVILLKOR,
		LEVVILLKOR, LEVSETT, DISTRIKT, KUNDKATEGORI, STDLEVPLATS, ORDERERKENNANDE,
		PLOCKLISTA, FOLJESEDEL, KRAVBREV, SPRAKKOD, EXPAVGIFT, FRAKTAVG, KREDITLIMIT,
		KREDITDAGAR, KREDITKOD, EXPORTKOD, SKATTEKOD, RABATTKOD, DROJSMALSRTA,
		DROJSMALSFAKTURA, SAMLINGSFAKT, SENASTEKRAVDATUM, SKULD, ORDERSTOCK
		samt errornb och error (text)

***************************************************************************/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/KUDSP.c,v 1.1 2003/10/03 11:25:13 janpihlgren Exp $ " ;

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

  char temp1[]="SELECT * FROM KUNDREG WHERE (KUNDNR = \"";
  char temp2[]="\"";
//  char temp3[]=",";
  char temp4[]=")";
  char temp5[200]="";
  char kundnr[11];

//  for (i=0;i< argc;i++){
//  	fprintf(stderr,"KUDSP main argv%d = %s\n",i,argv[i]);
//  }

  strcpy(kundnr,argv[1]);

  strcat(temp5,temp1);
/* SELECT * FROM KUNDREG WHERE (KUNDNR = "	*/
  strcat(temp5,kundnr);/* 12334 */
/* SELECT * FROM KUNDREG WHERE (KUNDNR = "12334	*/
  strcat(temp5,temp2); /*  "     */
/* SELECT * FROM KUNDREG WHERE (KUNDNR = "12334"	*/
  strcat(temp5,temp4); /*  )     */
/* SELECT * FROM KUNDREG WHERE (KUNDNR = "12334")	*/
  strcat(temp5,"\n");
//  fprintf(stderr,"KUDSP temp5 = %s\n",temp5);

  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", "olfix", 0, NULL, 0)){
//  	fprintf(stdout,"KUDSP_Connection success\n");
  	res = mysql_query(&my_connection,temp5);
  	if (res){
//  		fprintf(stderr,"KUDSP ERROR\n");
		fprintf(stderr,"Error: KUDSP_SELECT errno: %d\n",mysql_errno(&my_connection));
        }
	else{
		res_ptr=mysql_store_result(&my_connection);
		num_rows = mysql_affected_rows(&my_connection);
//		fprintf(stderr,"num_rows=%d\n",num_rows);
//		if (res_ptr){
		if(num_rows != 0){
			sqlrow=mysql_fetch_row(res_ptr);
			fprintf(stdout,"OK: ");
			fprintf(stdout,"01:%s  ",sqlrow[0]);
			fprintf(stdout,"02:%s  ",sqlrow[1]);
			fprintf(stdout,"03:%s  ",sqlrow[2]);
			fprintf(stdout,"04:%s  ",sqlrow[3]);
			fprintf(stdout,"05:%s  ",sqlrow[4]);
			fprintf(stdout,"06:%s  ",sqlrow[5]);
			fprintf(stdout,"07:%s  ",sqlrow[6]);
			fprintf(stdout,"08:%s  ",sqlrow[7]);
			fprintf(stdout,"09:%s  ",sqlrow[8]);
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
			fprintf(stdout,"22:%s  ",sqlrow[21]);
			fprintf(stdout,"23:%s  ",sqlrow[22]);
			fprintf(stdout,"24:%s  ",sqlrow[23]);
			fprintf(stdout,"25:%s  ",sqlrow[24]);
			fprintf(stdout,"26:%s  ",sqlrow[25]);
			fprintf(stdout,"27:%s  ",sqlrow[26]);
			fprintf(stdout,"28:%s  ",sqlrow[27]);
			fprintf(stdout,"29:%s  ",sqlrow[28]);
			fprintf(stdout,"30:%s  ",sqlrow[29]);
			fprintf(stdout,"31:%s  ",sqlrow[30]);
			fprintf(stdout,"32:%s  ",sqlrow[31]);
			fprintf(stdout,"33:%s  ",sqlrow[32]);
			fprintf(stdout,"34:%s  ",sqlrow[33]);
			fprintf(stdout,"35:%s  ",sqlrow[34]);
			fprintf(stdout,"36:%s  ",sqlrow[35]);
			fprintf(stdout,"37:%s  ",sqlrow[36]);
			fprintf(stdout,"38:%s  ",sqlrow[37]);
			fprintf(stdout,"39:%s  ",sqlrow[38]);
			fprintf(stdout,"40:%s  ",sqlrow[39]);
			fprintf(stdout,"41:%s  ",sqlrow[40]);
			fprintf(stdout,"\n");
		}
		else{
			fprintf(stderr,"Error: KUDSP Data saknas:  %s\n", mysql_error(&my_connection));
		}
		if (mysql_errno(&my_connection))  {
		fprintf(stderr,"Error: KUDSP Retriev error:  %s\n", mysql_error(&my_connection));
		}
	}
	mysql_free_result(res_ptr);
    	mysql_close(&my_connection);
  }
  else {
    	fprintf(stderr,"Error: KUDSP Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: KUDSP Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
	}
    }
  return EXIT_SUCCESS;
}
