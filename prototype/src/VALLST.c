/***************************************************************************
                          VALLST.c  -  description
                             -------------------
    begin                : Sön 1 juni
    Version		 : 0.02
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
	INPUT:
	Function: gör  SELECT * FROM VALUTA i databasen olfix

	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/VALLST.c,v 1.2 2003/09/28 04:53:45 janpihlgren Exp $ " ;

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>
//#include <string.h>
//#include <ctype.h>
#include "mysql.h"
#define HOST 100

  MYSQL my_connection;
  MYSQL_RES *res_ptr;
  MYSQL_ROW sqlrow;

	char tmphost[HOST];
	char host[15];
	char databas[15];
	char databasuser[15];
	char losenord[15];

int find_host(char *envp[]);
void display_row();

int main(int argc, char *argv[], char *envp[])
{
  int res,i,status;

  status = find_host(envp);
  if (status != 0)
	exit(status);
//  fprintf(stderr,"host=%s\n",host);
//  fprintf(stderr,"VALLST\n");
  mysql_init(&my_connection);


//  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", "olfix", 0, NULL, 0)){
  if (mysql_real_connect(&my_connection, host,  databas, databasuser, losenord, 0, NULL, 0)){
//  fprintf(stderr,"VALLST:Connection success\n");

  res = mysql_query(&my_connection,"SELECT * FROM VALUTA ORDER BY VALUTAID");

  if (res){
	fprintf(stderr,"Error: VALLST SELECT error: %s\n",mysql_error(&my_connection));
        }else{
	res_ptr=mysql_store_result(&my_connection);
	if (res_ptr){
		i=1;
//		fprintf(stderr,"VALLST:Retrieved %lu rows\n",(unsigned long)mysql_num_rows(res_ptr));
		fprintf(stdout,"NR_%lu_:",(unsigned long)mysql_num_rows(res_ptr));
		while ((sqlrow=mysql_fetch_row(res_ptr)))  {
		 	//fprintf(stderr,"VALLST:Fetched data....}");
//			fprintf(stdout,"%d ",i);
			display_row();
			i++;
		}
	if (mysql_errno(&my_connection))  {
		fprintf(stderr,"Error: VALLST Retriev error:  %s\n", mysql_error(&my_connection));
		}
	}
	mysql_free_result(res_ptr);
	}
	mysql_close(&my_connection);

  	} else {
    	fprintf(stderr,"Error: VALLST Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: VALLST_Connection error %d:  %s\n",
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
//	fprintf(stdout,"\n");
}

int find_host(char *envp[])
{
	FILE *fil_pek;

	char home[50];
	char *home_pek;
	char resource[]="/.olfixrc";
	char filename[50]="";
	char tmp[50]="";
	char temp[10]="";
	char *tmp_pek;
	char *tmp_pek2;
	int i,status;

	for (i = 0;envp[i]!=NULL;i++){
		if(strstr(envp[i],"HOME=") != NULL){
			strncpy(temp,envp[i],4);
			status=strcmp(temp,"HOME");
			if (status == 0){
				home_pek=(strstr(envp[i],"HOME="));
				home_pek=home_pek+5;
				strcpy(home,home_pek);
			}
		}
	}
	strcpy(filename,home);
	strcat(filename,resource);

	status=-1;

	if ((fil_pek = fopen(filename,"r")) != NULL){
		while (fgets(tmp,50,fil_pek) != NULL){
			if(strstr(tmp,"HOST=")){
			//	tmp_pek=(strstr(tmp,"HOST="))+5;
			//	fprintf(stderr,"tmp_pek=%d\n",tmp_pek);
			//	strcpy(tmphost,tmp_pek);
			//	fprintf(stderr,"tmphost=%s\n",tmphost);
				tmp_pek=(strstr(tmp,"1:"))+2;
				tmp_pek2=strstr(tmp,"2:");
				strncpy(host,tmp_pek,(tmp_pek2-tmp_pek)-1);
			//	fprintf(stderr,"host=%s\n",host);
				tmp_pek=(strstr(tmp,"2:"))+2;										tmp_pek2=strstr(tmp,"3:");
				strncpy(databas,tmp_pek,(tmp_pek2-tmp_pek)-1);
			//	fprintf(stderr,"databas=%s längd=%d\n",databas,strlen(databas));
				tmp_pek=(strstr(tmp,"3:"))+2;
				tmp_pek2=strstr(tmp,"4:");
				strncpy(databasuser,tmp_pek,(tmp_pek2-tmp_pek)-1);
			//	fprintf(stderr,"user=%s längd=%d\n",databasuser,strlen(databasuser));
				tmp_pek=(strstr(tmp,"4:"))+2;
				tmp_pek2=strstr(tmp,"end");
				strncpy(losenord,tmp_pek,(tmp_pek2-tmp_pek)-1);
			//	fprintf(stderr,"losen=%s längd=%d\n",losenord,strlen(losenord));
				status=0;
			}
		}
		fclose(fil_pek);
	}
	else{
	 	fprintf(stderr,"Error: Filen .olfixrc kan inte öppnas\n");
	}
	return status;
}
