/***************************************************************************
                          PICKDSP.c  -  description
                             -------------------
			     Visa en plocklistas information. Kundorder.
			     Ver: 0.
    begin                : Sön  23 okt  2005
    modified		 : Sön  18 febr 2007
    copyright            : (C) 2005 by Jan Pihlgren
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
	INPUT: 1 st arg. ORDERNR

	Kommando: ./PICKDSP ordernr

	Function: Visa samtliga plock på en kundorder i tabell PLOCKLISTEREG

	OUTPUT: PLOCKNR ORDERNR ORDERRAD KUNDNR ARTIKELNR BENEMNING
	LEVERANSVECKA BESTELLT ATTLEVERERA LEVERERAT PLOCKAT RESTNOTERAT LEVDATUM ENHET
	PLOCKSTATUS PLOCKDATUM
	samt errornb och error (text)

	ex:
OK: 2_:_ 01:15  02_:_ 63_:_03_:_ 10_:_04_:_ 4378_:_05_:_ 1000-1016_:_06_:_  Seagate Baracuda 7200+7 160GB_:_07_:_  5134_:_08_:_ 3.00_:_09_:_ 1.00_:_10_:_ -0.00_:_11_:_ 1.00_:_12_:_ 0.00_:_13_:_ 2005-03-31_:_14_:_ ST_:_15_:_ P_:_16_:_ 2005-10-23_:_NEXT_:_
         01:20  02_:_ 63_:_03_:_ 20_:_04_:_ 4378_:_05_:_ 1000-1017_:_06_:_  Deskstar 7K400_250_:_07_:_  5134_:_08_:_ 3.00_:_09_:_ 1.00_:_10_:_ -0.00_:_11_:_ 1.00_:_12_:_ 0.00_:_13_:_ 2005-03-31_:_14_:_ ST_:_15_:_ P_:_16_:_ 2005-10-23_:_NEXT_:_
END

***************************************************************************/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/PICKDSP.c,v 1.2 2007/02/18 10:49:45 janpihlgren Exp $ " ;

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "mysql.h"
#define ANTARG 4

  MYSQL my_connection;
  MYSQL_RES *res_ptr;
  MYSQL_ROW sqlrow;

int which_database(char *envp[]);
int getDatum();
char database[15]="";
char dagensdatum[11];			/* dagen datum*/


int main(int argc, char *argv[], char *envp[])
{
  int i,res;
  int status;
  const char *userp = getenv("USER");	/* vem är inloggad?	*/
  char databas[25]="olfix";
  char usr[21];				/* userid 20070218 utökat från 15 till 21 tecken */
  char datum[11];			/* plockdatum		*/
  int num_rows;
  getDatum();
/* ================================================================================ */
/* 		Val av databas, START						    */
/* ================================================================================ */

  status = which_database(envp);

  if (status != 0)
	exit(status);

  strncpy(usr,userp,sizeof(usr));			/* Den inloggades userid 20070218 */
/*  fprintf(stderr,"status=%d ANTARG=%d len(database)=%d\n",status,ANTARG,strlen(database));	*/
  if (argc < ANTARG+1){
    	if (strlen(database)!= 0){
		strncpy(databas,database,15);
	}else{
  		strncpy(databas,"olfixtst",15);	/* olfixtst = testföretag	*/
	}
  }else{
	if (strlen(argv[ANTARG]) != 0){
  		if (strncmp(argv[ANTARG],"99",2)==0){
			strncpy(databas,"olfixtst",15);
		}else{
  			strncpy(databas,argv[ANTARG],15);
  		}
  	}
  }
/*  fprintf(stderr,"ANTARG=%d,argv[ANTARG]=%s\n",ANTARG,argv[ANTARG]);	*/
/* Om usr (userid) börjar på 'test' eller 'prov' använd databas 'olfixtst' */
  if (strncmp(usr,"test",4)==0 || strncmp(usr,"prov",4)==0 ) {
  	strncpy(databas,"olfixtst",15);
  }
/*  fprintf(stderr,"Databas=%s\n",databas);	*/
/* ================================================================================ */
/* 		Val av databas, END!						    */
/* ================================================================================ */
/*										    */

  char temp1a[]="SELECT * FROM PLOCKLISTEREG WHERE ORDERNR = \"";
  char temp1b[]=" and PLOCKSTATUS <> \"";
  char temp1c[]=" and PLOCKDATUM = \"";
  char temp1d[]=" order by PLOCKDATUM,ORDERRAD";
  char temp2[]="\"";
//  char temp4[]=")";
  char temp5[200]="";
  char ordernr[11]="";
  char plockstatus[2]="B";

/*  fprintf(stderr,"PICKDSP argc = %d\n",argc);
  for (i=0;i< argc;i++){
  	fprintf(stderr,"PICKDSP argv%d = %s\n",i,argv[i]);
  }
*/
  strncpy(ordernr,argv[1],sizeof(ordernr));
  strncpy(datum,dagensdatum,sizeof(datum));
  if (argc>2){
  	strncpy(datum,argv[2],sizeof(datum));
  }
  if (argc>3){
	strncpy(plockstatus,argv[3],sizeof(plockstatus));
  }

/*  fprintf(stderr,"input= %s och %s och %s\n",ordernr,datum,plockstatus);	*/

  strncat(temp5,temp1a,strlen(temp1a));
/* SELECT * FROM PLOCKLISTEREG WHERE ORDERNR = "	*/
  strncat(temp5,ordernr,strlen(ordernr));/* 1234 */
/* SELECT * FROM PLOCKLISTEREG WHERE ORDERNR = "1234	*/
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
/* SELECT * FROM PLOCKLISTEREG WHERE ORDERNR = "1234"	*/
  strncat(temp5,temp1b,strlen(temp1b));
/* SELECT * FROM PLOCKLISTEREG WHERE ORDERNR = "1234" and PLOCKSTATUS <> "	*/
  strncat(temp5,plockstatus,strlen(plockstatus));/* P */
/* SELECT * FROM PLOCKLISTEREG WHERE ORDERNR = "1234" and PLOCKSTATUS <> "P	*/
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
/* SELECT * FROM PLOCKLISTEREG WHERE ORDERNR = "1234" and PLOCKSTATUS <> "P"	*/
  strncat(temp5,temp1c,strlen(temp1c));
/* SELECT * FROM PLOCKLISTEREG WHERE ORDERNR = "1234" and PLOCKSTATUS <> "P" and PLOCKDATUM = "	*/
  strncat(temp5,datum,strlen(datum));/* 2005-10-23 */
/* SELECT * FROM PLOCKLISTEREG WHERE ORDERNR = "1234" and PLOCKSTATUS <> "P" and PLOCKDATUM = "2005-10-23	*/
  strncat(temp5,temp2,strlen(temp2)); /*  "     */
/* SELECT * FROM PLOCKLISTEREG WHERE ORDERNR = "1234" and PLOCKSTATUS <> "P" and PLOCKDATUM = "2005-10-23"	*/
  strncat(temp5,temp1d,strlen(temp1d));/*  order by PLOCKDATUM,ORDERRAD */
/* SELECT * FROM PLOCKLISTEREG WHERE ORDERNR = "1234" and PLOCKSTATUS <> "P" and PLOCKDATUM = "2005-10-23" order by PLOCKDATUM,ORDERRAD	*/

  strncat(temp5,"\n",1);
/*  fprintf(stderr,"PICKDSP temp5 = %s\n",temp5);	*/

  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
/*  	fprintf(stdout,"PICKDSP_Connection success\n");		*/
  	res = mysql_query(&my_connection,temp5);
/*  	fprintf(stderr,"PICKDSP hit res=%d\n",res);		*/
  	if (res){
/*  		fprintf(stderr,"PICKDSP ERROR\n");		*/
		fprintf(stderr,"Error: PICKDSP SELECT errno: %d\n",mysql_errno(&my_connection));
        }
	else{
		res_ptr=mysql_store_result(&my_connection);
		num_rows = mysql_affected_rows(&my_connection);
/*		fprintf(stderr,"num_rows=%d\n",num_rows);		*/
		if(num_rows != 0){
/*			fprintf(stdout,"OK: ");				*/
			fprintf(stdout,"OK: %d_:_ ",num_rows);

			for (i=0;i<num_rows;i++){
				sqlrow=mysql_fetch_row(res_ptr);
/*				fprintf(stdout,"OK: ");				*/
				fprintf(stdout,"01:%s  ",sqlrow[0]);
				fprintf(stdout,"02_:_ %s_:_",sqlrow[1]);
				fprintf(stdout,"03_:_ %s_:_",sqlrow[2]);
				fprintf(stdout,"04_:_ %s_:_",sqlrow[3]);
				fprintf(stdout,"05_:_ %s_:_",sqlrow[4]);
				fprintf(stdout,"06_:_ %s_:_",sqlrow[5]);
				fprintf(stdout,"07_:_ %s_:_",sqlrow[6]);
				fprintf(stdout,"08_:_ %s_:_",sqlrow[7]);
				fprintf(stdout,"09_:_ %s_:_",sqlrow[8]);
				fprintf(stdout,"10_:_ %s_:_",sqlrow[9]);
				fprintf(stdout,"11_:_ %s_:_",sqlrow[10]);
				fprintf(stdout,"12_:_ %s_:_",sqlrow[11]);
				fprintf(stdout,"13_:_ %s_:_",sqlrow[12]);
				fprintf(stdout,"14_:_ %s_:_",sqlrow[13]);
				fprintf(stdout,"15_:_ %s_:_",sqlrow[14]);
				fprintf(stdout,"16_:_ %s_:_",sqlrow[15]);
/*				fprintf(stdout,"17_:_ %s_:_",sqlrow[16]);
*/				fprintf(stdout,"NEXT_:_");

				fprintf(stdout,"\n");
			}
			fprintf(stdout,"END");
			fprintf(stdout,"\n");
		}
		else{
			fprintf(stderr,"Error: PICKDSP Data saknas:  %s\n", mysql_error(&my_connection));
		}
		if (mysql_errno(&my_connection))  {
			fprintf(stderr,"Error: PICKDSP Retriev error:  %s\n", mysql_error(&my_connection));
		}
	}
	mysql_free_result(res_ptr);
    	mysql_close(&my_connection);
  }
  else {
    	fprintf(stderr,"Error: PICKDSP Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: PICKDSP Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
	}
    }
  return EXIT_SUCCESS;
}

int which_database(char *envp[])
{
	FILE *fil_pek;

	char home[50];
	char *home_pek;
	char resource[]="/.olfixrc";
	char filename[50]="";
	char tmp[20]="";
	char temp[10]="";
	char *tmp_pek;
	int i,status;

	for (i = 0;envp[i]!=NULL;i++){
		if(strstr(envp[i],"HOME=") != NULL){
			strncpy(temp,envp[i],4);
/*			fprintf(stderr,"temp=%s\n",temp); */
			status=strcmp(temp,"HOME");
/*			fprintf(stderr,"status=%d\n",status); */
			if (status == 0){
				home_pek=(strstr(envp[i],"HOME="));
				home_pek=home_pek+5;
				strcpy(home,home_pek);
			}
/*			fprintf(stderr,"home_pek=%d %s\n",home_pek,home_pek);	*/
		}
	}
/*	fprintf(stderr,"home=%s\n",home);	*/
	strncpy(filename,home,strlen(home));
	strncat(filename,resource,strlen(resource));

/*	fprintf(stderr,"filename=%s\n",filename);	*/
	status=-1;

	if ((fil_pek = fopen(filename,"r")) != NULL){
		while (fgets(tmp,150,fil_pek) != NULL){
/*			fprintf(stderr,"tmp=%s\n",tmp); */
			if(strstr(tmp,"DATABASE=")){
				tmp_pek=(strstr(tmp,"DATABASE="))+9;
				strncpy(database,tmp_pek,strlen(tmp_pek));
				status=0;
			}
		}
/*		fprintf(stderr,"database=%s_len=%d\n",database,strlen(database)); */
		fclose(fil_pek);
	}
	else{
/*		fprintf(stderr,"database=%s_len=%d\n",database,strlen(database)); */
	 	fprintf(stderr,"Error: Filen .olfixrc kan inte öppnas\n");
	}
	for (i=0;i < strlen(database);i++){
		tmp[i]=database[i];
	}
	tmp[i-1]=0;
/*	fprintf(stderr,"tmp=%s, i=%d len(tmp)=%d\n",tmp,i,strlen(tmp));	*/
	strncpy(database,tmp,strlen(tmp));
	database[strlen(tmp)]=0;
/*	fprintf(stderr,"databas=%s\n",database);	*/

	return status;
}

int getDatum()
{
	char dagens[30]="";

	struct tm *newtime;
	time_t aclock;
	time( &aclock ); 		// Get time in seconds
	newtime = localtime( &aclock ); // Convert time to struct tm form
	sprintf(dagens,"%d-%d-%d",newtime->tm_year+1900,newtime->tm_mon+1,newtime->tm_mday);
/*
	sprintf (dagens, "i is %i", ar);
	itoa(ar,*dagens,10);
*/

	strncpy(dagensdatum,dagens,sizeof(dagensdatum));
	//fprintf(stderr,"dagens=%s dagensdatum=%s\n",dagens,dagensdatum);
	return 0;
}
