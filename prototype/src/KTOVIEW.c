/***************************************************************************
                          KTOVIEW.c  -  description
                             -------------------
    Version		 : 0.02
    begin                : Tors 28 nov
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
 ***************************************************************************/

/*
	INPUT:	ARID
	Function: gör  SELECT KTONR, BENAMNING FROM KTOPLAN i databasen olfix

	OUTPUT: KTONR, BENAMNING, errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/KTOVIEW.c,v 1.1 2003/05/08 08:54:09 frazze Exp $ " ;

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
/*	for(i=0;i<=argc;i++){
		fprintf(stderr,"argv[%d]=%s\n",i,argv[i]);
	}
*/
  char temp1a[]="SELECT KTONR, BENAMNING FROM KTOPLAN WHERE ARID=\"";
  char temp1b[]=" ORDER BY KTONR";
  char temp2[]="\"";
  char temp3[]=",";
  char temp4[]=")";
  char temp5[200]="";
  char arid[5];
  
  if (argv[1] != NULL){
  	strcpy(arid,argv[1]);
  }
  else{
  	fprintf(stderr,"Error: KTOVIEW_ARID Ange årtal!\n");
	exit(-1);
  }

  strcpy(temp5,temp1a);
/* SELECT KTONR, BENAMNING FROM KTOPLAN WHERA ARID="   */
  strcat(temp5,arid);			/* 2002 */
/* SELECT KTONR, BENAMNING FROM KTOPLAN WHERA ARID="2002  */
  strcat(temp5,temp2); /*  "     */
/* SELECT KTONR, BENAMNING FROM KTOPLAN WHERA ARID="2002"   */
  strcat(temp5,temp1b);
/* SELECT KTONR, BENAMNING FROM KTOPLAN WHERA ARID="2002" ORDER BY KTONR   */
//  fprintf(stderr,"KTOVIEWmain: temp5 = %s\n",temp5);



  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", "olfix", 0, NULL, 0)){
//  	fprintf(stderr,"KTOVIEW:Connection success\n");

  res = mysql_query(&my_connection,temp5);

  if (res){
	fprintf(stderr,"Error: KTOVIEW_SELECT error: %s\n",mysql_error(&my_connection));
        }else{
	res_ptr=mysql_store_result(&my_connection);
	if (res_ptr){
		i=1;
//		fprintf(stderr,"KTOVIEW:Retrieved %lu rows\n",(unsigned long)mysql_num_rows(res_ptr));
		if ( (unsigned long)mysql_num_rows(res_ptr) > 0){
			fprintf(stdout,"NR_%lu_:",(unsigned long)mysql_num_rows(res_ptr));
			while ((sqlrow=mysql_fetch_row(res_ptr)))  {
		 		//printf("KTOVIEW:Fetched data....}");
				display_row();
				i++;
			}
		}
		else{
			fprintf(stderr,"Error: KTOVIEW Felaktigt årtal!\n");
		}

	if (mysql_errno(&my_connection))  {
		fprintf(stderr,"Error: KTOVIEW_Retriev error:  %s\n", mysql_error(&my_connection));
		}
	}
	mysql_free_result(res_ptr);
	}
	mysql_close(&my_connection);
  	}
	else {
    		fprintf(stderr,"Error: KTOVIEW_Connection failed\n");
    		if (mysql_errno(&my_connection))   {
    			fprintf(stderr,"Error: KTOVIEW_Connection error %d:  %s\n",
				mysql_errno(&my_connection), mysql_error(&my_connection));
		}
    	}
	fprintf(stdout,"\n");
  return EXIT_SUCCESS;
}

void display_row()
{
   unsigned int field_count;
   field_count=0;
	while (field_count < mysql_field_count(&my_connection))
	{
		fprintf(stdout,"%s_:",sqlrow[field_count]);
		field_count++;
	}
}

