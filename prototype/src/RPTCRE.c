/***************************************************************************
                          RPTCRE.c  -  description
                             -------------------
    begin                : Mån 25 aug  2003
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
	INPUT: 1 argument med en sqlfråga
	Function: en sqlfråga till databasen olfix

	OUTPUT: errornb och error (text)
*/

 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/RPTCRE.c,v 1.1 2003/09/28 04:46:39 janpihlgren Exp $ " ;

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

    FILE *fp;

void display_header();
void display_row();

int main(int argc, char *argv[])
{
  int res;
//  int i;
  char sqlquery[1000]="SELECT * FROM VERRAD";

// FILE *fp;

  strcpy(sqlquery,argv[1]);

  fp = fopen ("/tmp/rptcre.txt","a");		// skapa och öppna resultatfilen
  mysql_init(&my_connection);

  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", "olfix", 0, NULL, 0)){
//  fprintf(stderr,"RPTCRE:Connection success\n");
	res = mysql_query(&my_connection,sqlquery);

  	if (res){
		fprintf(stderr,"Error: RPTCRE SELECT error: %s\n",mysql_error(&my_connection));
        }else{
		res_ptr=mysql_use_result(&my_connection);
		if (res_ptr){
//			i=1;
//			fprintf(stderr,"RPTCRE:Retrieved %lu rows\n",(unsigned long)mysql_num_rows(res_ptr));
//			fprintf(stdout,"NR_%lu_:",(unsigned long)mysql_num_rows(res_ptr));
			display_header();
			while ((sqlrow=mysql_fetch_row(res_ptr)))  {
		 		//fprintf(stderr,"RPTCRE:Fetched data....}");
//				fprintf(stdout,"%d ",i);
				display_row();
//				i++;
			}
			if (mysql_errno(&my_connection))  {
				fprintf(stderr,"Error: RPTCRE Retriev error:  %s\n", mysql_error(&my_connection));
			}
		}
		mysql_free_result(res_ptr);
	}
	mysql_close(&my_connection);

  } else {
    	fprintf(stderr,"Error: RPTCRE Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: RPTCRE Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
	}
    }
  fprintf(stdout,"\n");
  fclose(fp);			//Stäng resultatfilen
  return EXIT_SUCCESS;
}

void display_header()
{
	MYSQL_FIELD *field_ptr;
	while((field_ptr = mysql_fetch_field(res_ptr)) != NULL){
//		fprintf(stdout,"%s,",field_ptr->name);
		fputs(field_ptr->name,fp);
		fputs(",",fp);
	}
//	fprintf(stdout,"\n");
   	fputs("\n",fp);
}


void display_row()
{
   unsigned int field_count;
   field_count=0;
   while (field_count < mysql_field_count(&my_connection)){
//		fprintf(stdout,"%s,",sqlrow[field_count]);
		fputs(sqlrow[field_count],fp);
		fputs(",",fp);
		field_count++;
   }
   	fputs("\n",fp);
//	fprintf(stdout,"\n");
}
