/***************************************************************************
                          FTGUPD.c  -  description
                             -------------------
    begin                : mån 18 nov
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
	INPUT:

	Kommando: ./FTGUPD posttyp fdata

	Function: Uppdatera fältet FDATA i tabellen FTGDATA


	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/FTGUPD.c,v 1.1 2003/05/08 08:54:07 frazze Exp $ " ;

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

  char temp1a[]="UPDATE FTGDATA SET FDATA = ";
  char temp2[]=" WHERE POSTTYP = ";
  char temp3[]=",";
  char temp4[]=")";
  char temp5[TEXTSIZE+200]="";

  char ptyp[5];		/* posttyp */
  char txt[61];		/* ftgdata */
  int status=-15;

   strcpy(ptyp,argv[1]);
   strcpy(txt,argv[2]);

//    fprintf(stderr,"FTGUPDmain1: argv1 = %s argv2 = %s len text=%d\n",ptyp,txt,strlen(txt));
//    fprintf(stderr,"FTGUPDmain: argv2 = %s\n",txt);

  strcpy(temp5,temp1a);
/* UPDATE FTGDATA SET FDATA =  */
  strcat(temp5,"'");
  strcat(temp5,txt);
  strcat(temp5,"'");
//  fprintf(stderr,"FTGUPDmain2: temp5=%s\n",temp5);
/* UPDATE FTGDATA SET FDATA = 'txt' */
  strcat(temp5,temp2); /* WHERE POSTTYP =  */
/* UPDATE FTGDATA SET FDATA = 'txt, WHERE POSTTYP =    */
  strcat(temp5,"'");
//  fprintf(stderr,"FTGUPDmain3: temp5=%s\n",temp5);
  strcat(temp5,ptyp);
//  fprintf(stderr,"FTGUPDmain4: temp5=%s\n",temp5);
/* UPDATE FTGDATA SET FDATA = 'txt' WHERE POSTTYP = 'ADR1' */
  strcat(temp5,"'");

//fprintf(stderr,"FTGUPDmain: temp5=%s\n",temp5);

  mysql_init(&my_connection);

  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", "olfix", 0, NULL, 0)){
//    fprintf(stderr,"FTGUPD:Connection success\n");
    res = mysql_query(&my_connection,temp5);
  	if (!res){
		fprintf(stderr,"OK: FTGUPD Inserted %lu rows\n",
			(unsigned long)mysql_affected_rows(&my_connection));
        }else{
	fprintf(stderr,"Error: FTGUPD UPDATE error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
	}
	mysql_close(&my_connection);

 } else {
	fprintf(stderr,"Error: FTGUPD Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: FTGUPD Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
	}
    }
  return EXIT_SUCCESS;
}


