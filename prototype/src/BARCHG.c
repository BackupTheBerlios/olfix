/***************************************************************************
                          BARCHG.c  -  description
                             -------------------
    Version		 : 0.1
    begin                : Ons 2 april 2003
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
	INPUT:	ARID,BENAMNING,ARSTART,ARSLUT,ARLAST,BESKATTNINGSAR,SENVERDAT,VERNR,KONTOPLAN
	Function: gör  UPDATE BOKFAR SET BENAMNING = "2003-01-01--2003-12-31",ARSTART = "2003-01-01",
			ARSLUT = "2003-12-31",ARLAST = "N",BESKATTNINGSAR = "2003",
			SENVERDAT = "2003-03-21",VERNR = "234987",KONTOPLAN = "AC"
			WHERE ARID = "AC"
  		i databasen olfix

	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/BARCHG.c,v 1.1 2003/05/08 08:54:04 frazze Exp $ " ;

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include "mysql.h"

  MYSQL my_connection;
  MYSQL_RES *res_ptr;
  MYSQL_ROW sqlrow;


void display_row();

int main(int argc, char *argv[])
{
  int res,i;


  char temp1a[]="UPDATE BOKFAR SET BENAMNING = ";
  char temp1b[]=",ARSTART = ";
  char temp1c[]=",ARSLUT = ";
  char temp1d[]=",ARLAST = ";
  char temp1e[]=",BESKATTNINGSAR = ";
  char temp1f[]=",SENVERDAT = ";
  char temp1g[]=",VERNR = ";
  char temp1h[]=",KONTOPLAN = ";
  char temp1k[]=" WHERE ARID = ";
  char temp2[]="\"";
  char temp3[]=",";
  char temp4[]=")";
  char temp5[200]="";
  char arid[5];
  char benamn[26];
  char arstart[11];
  char arslut[11];
  char arlast[2];
  char beskattar[5];
  char senverdat[11];
  char vernr[12];
  char ktoplan[16];

/*  fprintf(stderr,"BARCHGmain: argc = %d\n",argc);
  for (i=0;i<=argc;i++){
	fprintf(stderr,"argv%d = %s\n",i,argv[i]);
	}
*/
  if (argv[1] != NULL){
  	strcpy(arid,argv[1]);
  }
  else{
  	fprintf(stderr,"Error: BARCHG: Ange bokföringsår!\n");
	exit(-1);
  }
  strcpy(benamn,argv[2]);
  strcpy(arstart,argv[3]);
  strcpy(arslut,argv[4]);
  strcpy(arlast,argv[5]);
  strcpy(beskattar,argv[6]);
  strcpy(senverdat,argv[7]);
  strcpy(vernr,argv[8]);
  strcpy(ktoplan,argv[9]);

  strcpy(temp5,temp1a);
/* UPDATE BOKFAR SET BENAMNING = */
  strcat(temp5,temp2);
/* UPDATE BOKFAR SET BENAMNING = "*/
  strcat(temp5,benamn);
/* UPDATE BOKFAR SET BENAMNING = "2003-01-01--2003-12-31 */
  strcat(temp5,temp2);
/* UPDATE BOKFAR SET BENAMNING = "2003-01-01--2003-12-31" */
  strcat(temp5,temp1b);
/* UPDATE BOKFAR SET BENAMNING = "2003-01-01--2003-12-31",ARSTART =  */
  strcat(temp5,temp2);
  strcat(temp5,arstart);
  strcat(temp5,temp2);
/* UPDATE BOKFAR SET BENAMNING = "2003-01-01--2003-12-31",ARSTART = "2003-01-01" */
  strcat(temp5,temp1c);
/* UPDATE BOKFAR SET BENAMNING = "2003-01-01--2003-12-31",ARSTART = "2003-01-01",ARSLUT = */
  strcat(temp5,temp2);
  strcat(temp5,arslut);
  strcat(temp5,temp2);
/* UPDATE BOKFAR SET BENAMNING = "2003-01-01--2003-12-31",ARSTART = "2003-01-01",ARSLUT = "2003-12-31"*/
  strcat(temp5,temp1d);
/* UPDATE BOKFAR SET BENAMNING = "2003-01-01--2003-12-31",ARSTART = "2003-01-01",ARSLUT = "2003-12-31",ARLAST = */
  strcat(temp5,temp2);
  strcat(temp5,arlast);
  strcat(temp5,temp2);
/* UPDATE BOKFAR SET BENAMNING = "2003-01-01--2003-12-31",ARSTART = "2003-01-01",ARSLUT = "2003-12-31",ARLAST = "N" */
  strcat(temp5,temp1e);
/* UPDATE BOKFAR SET BENAMNING = "2003-01-01--2003-12-31",ARSTART = "2003-01-01",ARSLUT = "2003-12-31",ARLAST = "N" */
/* ,BESKATTNINGSAR = */
  strcat(temp5,temp2);
  strcat(temp5,beskattar);
  strcat(temp5,temp2);
/* UPDATE BOKFAR SET BENAMNING = "2003-01-01--2003-12-31",ARSTART = "2003-01-01",ARSLUT = "2003-12-31",ARLAST = "N" */
/* ,BESKATTNINGSAR = "2003"*/
  strcat(temp5,temp1f);
/* UPDATE BOKFAR SET BENAMNING = "2003-01-01--2003-12-31",ARSTART = "2003-01-01",ARSLUT = "2003-12-31",ARLAST = "N" */
/* ,BESKATTNINGSAR = "2003",SENVERDAT = */
  strcat(temp5,temp2);
  strcat(temp5,senverdat);
  strcat(temp5,temp2);
/* UPDATE BOKFAR SET BENAMNING = "2003-01-01--2003-12-31",ARSTART = "2003-01-01",ARSLUT = "2003-12-31",ARLAST = "N" */
/* ,BESKATTNINGSAR = "2003",SENVERDAT = "2003-03-21"*/
  strcat(temp5,temp1g);
/* UPDATE BOKFAR SET BENAMNING = "2003-01-01--2003-12-31",ARSTART = "2003-01-01",ARSLUT = "2003-12-31",ARLAST = "N" */
/* ,BESKATTNINGSAR = "2003",SENVERDAT = "2003-03-21",VERNR = */
  strcat(temp5,temp2);
  strcat(temp5,vernr);
  strcat(temp5,temp2);
/* UPDATE BOKFAR SET BENAMNING = "2003-01-01--2003-12-31",ARSTART = "2003-01-01",ARSLUT = "2003-12-31",ARLAST = "N" */
/* ,BESKATTNINGSAR = "2003",SENVERDAT = "2003-03-21",VERNR = "234987"*/
  strcat(temp5,temp1h);
/* UPDATE BOKFAR SET BENAMNING = "2003-01-01--2003-12-31",ARSTART = "2003-01-01",ARSLUT = "2003-12-31",ARLAST = "N" */
/* ,BESKATTNINGSAR = "2003",SENVERDAT = "2003-03-21",VERNR = "234987",KONTOPLAN = */
  strcat(temp5,temp2);
  strcat(temp5,ktoplan);
  strcat(temp5,temp2);
/* UPDATE BOKFAR SET BENAMNING = "2003-01-01--2003-12-31",ARSTART = "2003-01-01",ARSLUT = "2003-12-31",ARLAST = "N" */
/* ,BESKATTNINGSAR = "2003",SENVERDAT = "2003-03-21",VERNR = "234987",KONTOPLAN = "AC"*/
  strcat(temp5,temp1k);
/* UPDATE BOKFAR SET BENAMNING = "2003-01-01--2003-12-31",ARSTART = "2003-01-01",ARSLUT = "2003-12-31",ARLAST = "N" */
/* ,BESKATTNINGSAR = "2003",SENVERDAT = "2003-03-21",VERNR = "234987",KONTOPLAN = "AC" WHERE ARID = */
  strcat(temp5,temp2);
  strcat(temp5,arid);
  strcat(temp5,temp2);
/* UPDATE BOKFAR SET BENAMNING = "2003-01-01--2003-12-31",ARSTART = "2003-01-01",ARSLUT = "2003-12-31",ARLAST = "N" */
/* ,BESKATTNINGSAR = "2003",SENVERDAT = "2003-03-21",VERNR = "234987",KONTOPLAN = "AC" WHERE ARID = "AC"*/


//  fprintf(stderr,"Test: BARCHG: temp5 = %s\n",temp5);
  
  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", "olfix", 0, NULL, 0)){
//  	fprintf(stderr,"BARCHG:Connection success\n");

  res = mysql_query(&my_connection,temp5);

  if (!res){
 	fprintf(stderr,"OK: BARCHG Inserted %lu rows\n",
		(unsigned long)mysql_affected_rows(&my_connection));
        }else{
/*	fprintf(stderr,"stderr-BARCHG:INSERT error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
*/
	fprintf(stderr,"Error: BARCHG INSERT error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
	}
	mysql_close(&my_connection);
 }else {
	fprintf(stderr,"Error: BARCHG Connection failed\n");
 	if (mysql_errno(&my_connection))   {
 		fprintf(stderr,"Error: BARCHG Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
	}
  }
 	fprintf(stdout,"\n");
  return EXIT_SUCCESS;
}

