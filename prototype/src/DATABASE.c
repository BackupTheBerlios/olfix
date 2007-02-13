/***************************************************************************
                          DATABASE.c  -  description
                             -------------------
			     Uppdatera RIGHTS med fullst�ndiga r�ttigheter f�r en anv�ndare.
			     Offerthuvud.
    Version		 : 1.1
    begin                : M�n   11 dec  2006
    Modified		 : Tis   13 febr 2007
    copyright            : (C) 2006 by Jan Pihlgren
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
	INPUT: val [data]
		Val = vilken funktion i programmet som skall k�ras.
		

	F�ltavskiljare = 

	val = 1; Skapa tempor�rfilen OLFIXpid.tmp
		Function: skapar en tempor�rfil av komandot "ps -C OLFIXW > path/tmp/OLFIXpid.tmp"

	val = 2; Starta om OLFIXW

	val = 3; show databases, lista befintliga mysqldatabaser

	val = 4; kontrollera att det �r en olfixdatabas, finns tabellen RIGHTS?


	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/DATABASE.c,v 1.2 2007/02/13 07:34:08 janpihlgren Exp $ " ;

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql.h"
#define ANTARG 2

  MYSQL my_connection;
  MYSQL_RES *res_ptr;
  MYSQL_ROW sqlrow;

  int where_tempdir(char *envp[]);
  int where_bindir(char *envp[]);
  int create_tmpfile(char *envp[]);
  int which_database(char *envp[]);
  int restart_olfixw(char *envp[]);
  int listDatabases(char *databasorg);			/* Vilka databaser finns? */
  int checkDatabases(char *databasorg);			/* Inneh�ller databasen tabellen RIGHTS? */
  void display_row();

  char database[25]="";
  char tempdir[15]="";
  char tempfile[25]="";
  char datafile[25]="";
  char bindir[50]="";

int main(int argc, char *argv[], char *envp[])
{
  char databas[25]="olfix";
  const char *userp = getenv("USER");	// vem �r inloggad?
  char usr[21];				/* userid 20070213 ut�kat fr�n 15 till 21 tecken */


  char val[2]="";
  int funktion=0;
  int status;

/* ================================================================================ */
/* 		Val av databas, START						    */
/* ================================================================================ */

  status = which_database(envp);
  if (status != 0)
	exit(status);

  status = where_tempdir(envp);
  if (status != 0)
	exit(status);


  strncpy(usr,userp,sizeof(usr));			/* Den inloggades userid 20070213 */
/*  fprintf(stderr,"status=%d ANTARG=%d len(database)=%d\n",status,ANTARG,strlen(database));	*/
  if (argc < ANTARG+1){
    	if (strlen(database)!= 0){
		strncpy(databas,database,25);
	}else{
  		strncpy(databas,"olfixtst",10);	/* olfixtst = testf�retag	*/
	}
  }else{
	if (strlen(argv[ANTARG]) != 0){
  		if (strncmp(argv[ANTARG],"99",2)==0){
			strncpy(databas,"olfixtst",10);
		}else{
  			strncpy(databas,argv[ANTARG],25);
  		}
  	}
  }
/*  fprintf(stderr,"ANTARG=%d,argv[ANTARG]=%s\n",ANTARG,argv[ANTARG]);	*/
/* Om usr (userid) b�rjar p� 'test' eller 'prov' anv�nd databas 'olfixtst' */
//	2006-12-13
/*  if (strncmp(usr,"test",4)==0 || strncmp(usr,"prov",4)==0 ) {
  	strncpy(databas,"olfixtst",10);
  }  fprintf(stderr,"Databas=%s\n",databas);	
*/
/* ================================================================================ */
/* 		Val av databas, END!						    */
/* ================================================================================ */


  strncpy(val,argv[1],sizeof(val));
  funktion=atoi(val);
/*  fprintf(stderr,"val=%s\n",val);	*/

  if (funktion==1){
  	status=create_tmpfile(envp);
  }
  if (funktion==2){
/*	fprintf(stderr,"restart_olfixw!\n");	*/
	status=create_tmpfile(envp);
	status=restart_olfixw(envp);
  }
  if (funktion==3){
/*	fprintf(stderr,"K�r listDatabases!\n");	*/
	status=listDatabases(databas);
  }
  if (funktion==4){
/*	fprintf(stderr,"K�r listDatabases!\n");	*/
	status=checkDatabases(databas);
  }
  return EXIT_SUCCESS;
}

int create_tmpfile(char *envp[])
{
  int status;
  char commando[75]="";
  char commando1[]="ps -C OLFIXW > ";
  char commando2[]="OLFIXpid.tmp";

  status = where_tempdir(envp);
  if (status != 0){
/*	fprintf(stderr,"Error: Katalogen /tmp finns inte!\n");	*/
	exit(status);
  }else{
/*  	fprintf(stdout,"Katalogen %s finns!\n",tempdir);	*/
//	fprintf(stdout,"OK: ");	
  }
//  status = where_bindir(envp);

  strncpy(commando,commando1,sizeof(commando1));
  strncat(commando,tempdir,sizeof(tempdir));
  strncat(commando,commando2,sizeof(commando2));
  fprintf(stderr,"Kommando = %s\n",commando);
//  fprintf(stderr,"Kommando:com_check = %s\n",com_check);

  status=system(commando);

  if (status != 0){
	fprintf(stderr,"Error: OLFIXpid.tmp kunde inte skapats!\n");
	exit(status);
  }else{
  	fprintf(stdout,"OK: OLFIXpid.tmp har skapats!\n");
        return EXIT_SUCCESS;
  }
}
/* ================================================================================ */
/*		Starta om OLFIXW						    */
/* ================================================================================ */
int restart_olfixw(char *envp[])
{
	char datfil[]="OLFIXpid.dat";
	char tmpfil[]="OLFIXpid.tmp";
	char olfixfil[]="OLFIXW &";

	FILE *fil_pek;

	char inputfile[50]="";
	char outputfile[50]="";

	char tmp[20]="";
	char temp[10]="";
	int status;

	char commando[75]="";
  	char commando1[]="kill ";

	strncpy(inputfile,tempdir,sizeof(tempdir));
	strncat(inputfile,tmpfil,sizeof(tmpfil));

	strncpy(outputfile,tempdir,sizeof(tempdir));
	strncat(outputfile,datfil,sizeof(datfil));
		
	status=-1;

	if ((fil_pek = fopen(inputfile,"r")) != NULL){
		while (fgets(tmp,150,fil_pek) != NULL){
/*			fprintf(stderr,"tmp = %s\n",tmp);		*/
			if(strstr(tmp,"OLFIXW")){
				strncpy(temp,tmp,6);
				status=0;
			}
		}
/*		fprintf(stderr,"temp=%s len=%d\n",temp,strlen(temp));	*/
		fclose(fil_pek);
	}
	else{
/*		fprintf(stderr,"tmp=%s_len=%d\n",tmp,strlen(tmp)); */
	 	fprintf(stderr,"Error: Filen .olfixrc kan inte �ppnas\n");
		exit(-1);
	}
/*	fprintf(stderr,"tmp=%s\n",tmp);					*/
/*	strncpy(temp,tmp,6);						*/
/*	fprintf(stderr,"temp=%s\n",temp);				*/
	if (strlen(temp) > 0){
		strncpy(commando,commando1,sizeof(commando1));
		strncat(commando,temp,sizeof(temp));
/*		fprintf(stderr,"commando=%s\n",commando);		*/
		system(commando);
	}
	status = where_bindir(envp);
	strncpy(commando,bindir,sizeof(bindir));
	strncat(commando,olfixfil,sizeof(olfixfil));
/*	fprintf(stderr,"commando=%s\n",commando);			*/
	system(commando);
	return status;
}

int listDatabases(char *databasorg)
{
	char temp5[25]="show databases";
	char databas[15]="";
	int res,i;

	strncpy(databas,databasorg,sizeof(databas));
/*	fprintf(stderr,"databas=%s\n",databas);		*/

	mysql_init(&my_connection);
  	if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){

  	res = mysql_query(&my_connection,temp5);
  	if (res){
/*  		fprintf(stderr,"DATABASE ERROR\n");	*/
		fprintf(stderr,"Error: DATABASE SELECT errno: %d\n",mysql_errno(&my_connection));
	}else{
		res_ptr=mysql_store_result(&my_connection);
		if (res_ptr){
			i=1;
/*			fprintf(stdout,"DATABASE:Retrieved %lu rows\n",(unsigned long)mysql_num_rows(res_ptr));	*/
			fprintf(stdout,"OK: NR_%lu",(unsigned long)mysql_num_rows(res_ptr));
			while ((sqlrow=mysql_fetch_row(res_ptr)))  {
/*				fprintf(stderr,"DATABASE:Fetched data....}");		*/
				fprintf(stdout,"_:_%i_:_",i);
				display_row();
				i++;
			}
			fprintf(stdout,"_:_\n");
			if (mysql_errno(&my_connection))  {
				fprintf(stderr,"Error: DATABASE Retriev error:  %s\n", mysql_error(&my_connection));
			}
		}
	mysql_free_result(res_ptr);
	}
    	mysql_close(&my_connection);
  	}else {
   	 	fprintf(stderr,"Error: DATABASE Connection failed\n");
    		if (mysql_errno(&my_connection))   {
    			fprintf(stderr,"Error: DATABASE Connection error %d:  %s\n",
				mysql_errno(&my_connection), mysql_error(&my_connection));
		}
    	}
 //	fprintf(stderr,"temp5=%s\n",temp5);
  	return EXIT_SUCCESS;
}

int checkDatabases(char *databasorg)
{
	char temp5[25]="select * from RIGHTS";
	char databas[15]="";
	int res,i;

	strncpy(databas,databasorg,sizeof(databas));
/*	fprintf(stderr,"databas=%s\n",databas);		*/

	mysql_init(&my_connection);
  	if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){

  	res = mysql_query(&my_connection,temp5);
  	if (res){
/*  		fprintf(stderr,"DATABASE ERROR\n");	*/
//		fprintf(stderr,"Error: DATABASE SELECT errno: %d\n",mysql_errno(&my_connection));
		if (mysql_errno(&my_connection) == 1146){
			fprintf(stderr,"Error: DATABASE. Databasen \"%s\" �r inte en olfixdatabas!\n",databas);
		}else{
			fprintf(stderr,"Error: DATABASE SELECT errno: %d\n",mysql_errno(&my_connection));
		} 
	}else{
		res_ptr=mysql_store_result(&my_connection);
		if (res_ptr){
			i=1;
/*			fprintf(stdout,"DATABASE:Retrieved %lu rows\n",(unsigned long)mysql_num_rows(res_ptr));	*/
			fprintf(stdout,"OK: NR_%lu\n",(unsigned long)mysql_num_rows(res_ptr));
			if (mysql_errno(&my_connection))  {
				fprintf(stderr,"Error: DATABASE Retriev error:  %s\n", mysql_error(&my_connection));
			}
		}
	mysql_free_result(res_ptr);
	}
    	mysql_close(&my_connection);
  	}else {
   	 	fprintf(stderr,"Error: DATABASE Connection failed\n");
    		if (mysql_errno(&my_connection))   {
    			fprintf(stderr,"Error: DATABASE Connection error %d:  %s\n",
				mysql_errno(&my_connection), mysql_error(&my_connection));
		}
    	}
 //	fprintf(stderr,"temp5=%s\n",temp5);
  	return EXIT_SUCCESS;
}

int where_tempdir(char *envp[])
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

/*	fprintf(stderr,"filename=%s\n",filename);		*/
	status=-1;

	if ((fil_pek = fopen(filename,"r")) != NULL){
		while (fgets(tmp,150,fil_pek) != NULL){
/*			fprintf(stderr,"tmp = %s\n",tmp);	*/
			if(strstr(tmp,"VTMP=")){
				tmp_pek=(strstr(tmp,"VTMP="))+5;
				strncpy(tempdir,tmp_pek,strlen(tmp_pek));
				status=0;
			}
		}
/*		fprintf(stderr,"tempdir=%s_len=%d\n",tempdir,strlen(tempdir)); 	*/
		fclose(fil_pek);
	}
	else{
/*		fprintf(stderr,"tempdir=%s_len=%d\n",tempdir,strlen(tempdir)); */
	 	fprintf(stderr,"Error: Filen .olfixrc kan inte �ppnas\n");
	}
	for (i=0;i < strlen(tempdir);i++){
		tmp[i]=tempdir[i];
	}
	tmp[i-1]=0;
/*	fprintf(stderr,"tmp=%s, i=%d len(tmp)=%d\n",tmp,i,strlen(tmp));		*/
	strncpy(tempdir,tmp,strlen(tmp));
	tempdir[strlen(tmp)]=0;
/*	fprintf(stderr,"tempdir=%s\n",tempdir);		*/

	return status;
}

int where_bindir(char *envp[])
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

/*	fprintf(stderr,"filename=%s\n",filename);		*/
	status=-1;

	if ((fil_pek = fopen(filename,"r")) != NULL){
		while (fgets(tmp,150,fil_pek) != NULL){
/*			fprintf(stderr,"tmp = %s\n",tmp);	*/
			if(strstr(tmp,"PATH=")){
				tmp_pek=(strstr(tmp,"PATH="))+5;
				strncpy(bindir,tmp_pek,strlen(tmp_pek));
				status=0;
			}
		}
/*		fprintf(stderr,"bindir=%s len=%d\n",bindir,strlen(bindir)); 	*/
		fclose(fil_pek);
	}
	else{
/*		fprintf(stderr,"bindir=%s_len=%d\n",bindir,strlen(bindir)); */
	 	fprintf(stderr,"Error: Filen .olfixrc kan inte �ppnas\n");
	}
	for (i=0;i < strlen(bindir);i++){
		tmp[i]=bindir[i];
	}
	tmp[i-1]=0;
/*	fprintf(stderr,"tmp=%s, i=%d len(tmp)=%d\n",tmp,i,strlen(tmp));		*/
	strncpy(bindir,tmp,strlen(tmp));
	bindir[strlen(tmp)]=0;
/*	fprintf(stderr,"databas=%s\n",bindir);	*/

	return status;
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
		while (fgets(tmp,150,fil_pek) != NULL){
			if(strstr(tmp,"DATABASE=")){
				tmp_pek=(strstr(tmp,"DATABASE="))+9;
				strncpy(database,tmp_pek,strlen(tmp_pek));
				status=0;
			}
		}
		fclose(fil_pek);
	}
	else{
	 	fprintf(stderr,"Error: Filen .olfixrc kan inte �ppnas\n");
	}
	for (i=0;i < strlen(database);i++){
		tmp[i]=database[i];
	}
	tmp[i-1]=0;
	strncpy(database,tmp,strlen(tmp));
	database[strlen(tmp)]=0;

	return status;
}

void display_row()
{
   unsigned int field_count;
   field_count=0;
	while (field_count < mysql_field_count(&my_connection))
	{
//		fprintf(stdout,"%s_:",sqlrow[field_count]);
		fprintf(stdout,"%s",sqlrow[field_count]);
		field_count++;
	}
/*	fprintf(stdout,"\n");	*/
}
