/***************************************************************************
                          FTGDSP.c  -  description
                             -------------------
    Version		: 0.2
    begin               : Tis 19 nov 2002
    modified		: Tis 14 okt 2003
    copyright           : (C) 2002 by Jan Pihlgren
    email               : jan@pihlgren.se
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
	INPUT: 2 st arg = posttyp database

	Kommando: ./FTGDSP posttyp database

	Function: Visa information för önskad posttyp

	OUTPUT: POSTTYP, FDATA samt errornb och error (text)

*/

 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/FTGDSP.c,v 1.2 2003/10/17 07:52:15 janpihlgren Exp $ " ;

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
  int num_rows;
//  int i;

  const char *userp = getenv("USER");	// vem är inloggad?

  char databas[]="olfix";
  char temp1[]="SELECT POSTTYP, FDATA FROM FTGDATA WHERE (POSTTYP = \"";
  char temp2[]="\"";
//  char temp3[]=",";
  char temp4[]=")";
  char temp5[200]="";
  char posttyp[5];
  char fornr[4];	// företag nr fornr, 99 = testföretag
  char usr[15];		// userid
//  fprintf(stderr,"FTGDSPmain argc = %d\n",argc);
//  for (i=0;i< argc;i++){
//	fprintf(stderr,"FTGDSPmain argv%d = %s\n",i,argv[i]);
//  }
//  fprintf(stderr,"FTGDSPmain argv[2] = %s\n",argv[2]);

  strcpy(usr,userp);			// Den inloggades userid
//  fprintf(stderr,"FTGDSPmain usr = %s\n",usr);

  if (argc<3){
  	strcpy(databas,"olfixtst");	// olfixtst = testföretag
  }else{
  	if (strncmp(argv[2],"99",2)==0){
		strcpy(databas,"olfixtst");
	}else{
  		strcpy(databas,argv[2]);
	}
  }
  /* Om usr (userid) börjar på 'test' eller 'prov' använd databas 'olfixtst' */
  if (strncmp(usr,"test",4)==0 || strncmp(usr,"prov",4)==0 ) {
  	strcpy(databas,"olfixtst");
  }

  if (argc<4){
  	strcpy(fornr,"99");	// 99 = testföretag
  }else{
  	strcpy(fornr,argv[3]);
  }
//  fprintf(stderr,"FTGDSPmain fornr = %s\n",fornr);
  strcpy(posttyp,argv[1]);

  strcat(temp5,temp1);
/* SELECT POSTTYP, FDATA FROM FTGDATA WHERE (POSTTYP = \"   */
  strcat(temp5,posttyp);/* ADR1 */
/* SELECT POSTTYP, FDATA FROM FTGDATA WHERE (POSTTYP = "ADR1   */
  strcat(temp5,temp2); /*  "    */
/* SELECT POSTTYP, FDATA FROM FTGDATA WHERE (POSTTYP = "ADR1"   */
  strcat(temp5,temp4); /*  )     */
/* SELECT POSTTYP, FDATA FROM FTGDATA WHERE (POSTTYP = "ADR1")  */

//  fprintf(stderr,"FTGDSPmain: temp5 = %s\n",temp5);

// exit(0);
  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
//  	fprintf(stdout,"FTGDSPmain:Connection success\n");
  	res = mysql_query(&my_connection,temp5);
  	if (res){
		fprintf(stderr,"Error: FTGDSP SELECT error: %s\n",mysql_error(&my_connection));
        }
	else{
		res_ptr=mysql_store_result(&my_connection);
		num_rows = mysql_affected_rows(&my_connection);
//		if (res_ptr){
		if(num_rows != 0){
			sqlrow=mysql_fetch_row(res_ptr);
//	 		fprintf(stdout,"Fetched data....}");
			fprintf(stdout,"OK: 1:%s  2:%s",sqlrow[0],sqlrow[1]);
//			fprintf(stdout,"\n");
		}
		else{
			fprintf(stderr,"Error: FTGDSP, Data saknas!  %s\n", mysql_error(&my_connection));
		}

		if (mysql_errno(&my_connection))  {
			fprintf(stderr,"Error: FTGDSP Retriev error:  %s\n", mysql_error(&my_connection));
		}
	}
	mysql_free_result(res_ptr);
	mysql_close(&my_connection);
  	}
	else {
    		fprintf(stderr,"Error: FTGDSP Connection failed\n");
    		if (mysql_errno(&my_connection))   {
    			fprintf(stderr,"Error: FTGDSP Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
		}
    	}
  return EXIT_SUCCESS;
}

