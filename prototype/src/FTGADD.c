/***************************************************************************
                          FTGADD.c  -  description
                             -------------------
    begin                : Ons 16 april
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
	INPUT:

	Kommando: ./FTGADD posttyp text

	Function: Lägga upp ny post i tabellen FTGDATA


	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/FTGADD.c,v 1.1 2003/05/08 08:54:04 frazze Exp $ " ;

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


#include "mysql.h"

#define FORMAT_STR "%Y-%m-%d_%H:%M:%S"    /* YYYY-MM-DD */
#define MAXSIZE 20
#define MAXSTRING 5000
#define TEXTSIZE 255


int main(int argc, char *argv[])
{
  MYSQL my_connection;
  int res;

  char temp1a[]="INSERT INTO FTGDATA (POSTTYP,POSTBESKR,FDATA) VALUES( ";
//  char temp1b[]="POSTBESKR  = ";
//  char temp1c[]="FDATA = ";
  char temp2[]="'";
  char temp3[]=",";
  char temp4[]=")";
  char temp5[TEXTSIZE+200]="";

  char ptyp[5];		/* posttyp */
  char beskr[61];	/* postbeskrivning */
  char txt[61];		/* ftgdata */
  int status=-15;

   strcpy(ptyp,argv[1]);
   strcpy(beskr,argv[2]);
   strcpy(txt,argv[3]);

//    fprintf(stderr,"FTGADD: argv1 = %s argv3 = %s len text=%d\n",ptyp,txt,strlen(txt));
//    fprintf(stderr,"FTGADD: argv2 = %s\n",beskr);
//    fprintf(stderr,"FTGADD: argv3 = %s\n",txt);

  strcpy(temp5,temp1a);
/* INSERT INTO FTGDATA (POSTTYP,POSTBESKR,FDATA) VALUES(  */
  strcat(temp5,temp2);
  strcat(temp5,ptyp);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
/* INSERT INTO FTGDATA (POSTTYP,POSTBESKR,FDATA) VALUES('FNUM',   */
  strcat(temp5,temp2);
  strcat(temp5,beskr);
  strcat(temp5,temp2);
  strcat(temp5,temp3);
/* INSERT INTO FTGDATA (POSTTYP,POSTBESKR,FDATA) VALUES('FNUM','Företagsnummer', */
  strcat(temp5,temp2);
  strcat(temp5,txt);
  strcat(temp5,temp2);
  strcat(temp5,temp4);
/* INSERT INTO FTGDATA (POSTTYP,POSTBESKR,FDATA) VALUES('FNUM','Företagsnummer','553411-9555') */

// fprintf(stderr,"FTGADD: temp5=%s\n",temp5);

  mysql_init(&my_connection);

  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", "olfix", 0, NULL, 0)){
//    fprintf(stderr,"FTGADD:Connection success\n");
    res = mysql_query(&my_connection,temp5);
  	if (!res){
		fprintf(stderr,"OK: FTGADD Inserted %lu rows\n",
			(unsigned long)mysql_affected_rows(&my_connection));
        }else{
	fprintf(stderr,"Error: FTGADD UPDATE error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
	}
	mysql_close(&my_connection);

 } else {
	fprintf(stderr,"Error: FTGADD Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: FTGADD Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
	}
    }
  return EXIT_SUCCESS;
}


