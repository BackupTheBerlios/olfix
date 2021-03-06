/***************************************************************************
                          ORDRCHG.c  -  description
                             -------------------
			     Spara �ndrade kunorderrader i ORDERRADREG
    Version		 : 0.1
    begin                : M�n 20 febr  2006
    Modified		 :
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
	INPUT: kundorderraddata databas
		format=":_33_:_020_:_4377_:_1000-1016_:_Seagate Baracuda 7200+7 160GB _:_5111_:_4_:_650.00 _:_2600.00_:_650.00_:_END"

F�ltavskiljare = _:_

	Function: g�r  	REPLACE INTO ORDERRADREG
		(ORDERNR,ORDERRAD,KUNDNR,ARTIKELNR,BENEMNING,LEVERANSVECKA,BESTELLT,APRIS,SUMMA,MOMSKR,LEVERERAT,RESTNOTERAT,RADRABATT,KALKYLPRIS,LEVDATUM,ENHET,FAKTURERAT,RADORDERTYP)VALUES
		(_:_33_:_020_:_4377_:_1000-1016_:_Seagate Baracuda 7200+7 160GB_:_5111_:_4_:_650.00_:_2600.00_:_650.00_:_2.00_:_ 13.00_:_ 14.0_:_ 15.00_:_ 2006-02-20_:_ ST_:_ 18.00_:_:_END)
 		i databasen olfix

	OUTPUT: errornb och error (text)

*/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/ORDRCHG.c,v 1.1 2006/02/23 03:50:00 janpihlgren Exp $ " ;

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql.h"
#define ANTARG 2
#define ANTFELT 18

  MYSQL my_connection;
  MYSQL_RES *res_ptr;
  MYSQL_ROW sqlrow;

  int which_database(char *envp[]);
  char database[15]="";

int main(int argc, char *argv[], char *envp[])
{
  int res,status;
  char databas[25]="olfix";
  const char *userp = getenv("USER");	// vem �r inloggad?
  char usr[15];				// userid

  char temp1a[]="REPLACE INTO ORDERRADREG (ORDERNR,ORDERRAD,KUNDNR,ARTIKELNR,BENEMNING,LEVERANSVECKA,BESTELLT,APRIS,SUMMA,MOMSKR,LEVERERAT,RESTNOTERAT,RADRABATT,KALKYLPRIS,LEVDATUM,ENHET,FAKTURERAT,RADORDERTYP) VALUES (";
  char temp2[]="\"";
  char temp3[]=",";
  char temp4[]=")";
  char temp5[1500]="";
  char kundorderraddata[2000]="";

  char *pos1;
  char *pos2;
  int tmp,lenght,ant,i,j,k,n;

  /* ================================================================================ */
/* 		Val av databas, START						    */
/* ================================================================================ */

  status = which_database(envp);

  if (status != 0)
	exit(status);

  strncpy(usr,userp,15);			/* Den inloggades userid	*/
/*  fprintf(stderr,"status=%d ANTARG=%d len(database)=%d\n",status,ANTARG,strlen(database));	*/
  if (argc < ANTARG+1){
    	if (strlen(database)!= 0){
		strncpy(databas,database,15);
	}else{
  		strncpy(databas,"olfixtst",15);	/* olfixtst = testf�retag	*/
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
/* Om usr (userid) b�rjar p� 'test' eller 'prov' anv�nd databas 'olfixtst' */
  if (strncmp(usr,"test",4)==0 || strncmp(usr,"prov",4)==0 ) {
  	strncpy(databas,"olfixtst",15);
  } /* fprintf(stderr,"Databas=%s\n",databas);	*/

/* ================================================================================ */
/* 		Val av databas, END!						    */
/* ================================================================================ */

  if (argv[1] != NULL){
  	strncpy(kundorderraddata,argv[1],sizeof(kundorderraddata));	/* 2005-02-23	*/
  }
  else{
  	fprintf(stderr,"Error: ORDRCHG: Ange ordernummer!\n");
	exit(-1);
  }


  lenght=strlen(kundorderraddata);
/*  fprintf(stderr,"lenght=%d\n",lenght);	*/
  strncpy(temp5,temp1a,strlen(temp1a));
/*  fprintf(stderr,"kundorderraddata=%s\n",kundorderraddata);	*/
  pos1=strstr(kundorderraddata,"_:_")+3;
  k=3;
  n=0;
  ant=ANTFELT;		/* antal f�lt	*/
  for (i=0;i<ant;i++){
  	for (j=k;j<lenght;j++){
/*		fprintf(stderr,"j=%d\n",j);	*/
  		if (kundorderraddata[j]== 95 && kundorderraddata[j+1]== 58 && kundorderraddata[j+2]== 95){
			j=lenght;
		}
		n=n+1;
  	}
	k=k+(n-1)+3;

	pos2=pos1+3+(n-1);

	tmp=pos2-pos1-3;
  	strncat(temp5,temp2,strlen(temp2));
  	strncat(temp5,pos1,tmp);
  	strncat(temp5,temp2,strlen(temp2));
	if (i<(ant-1)){
  		strncat(temp5,temp3,strlen(temp3));
	}
	pos1=pos2;
/*	fprintf(stderr,"i=%d, k=%d, n=%d, tmp=%d\n",i,k,n,tmp);	*/
	n=0;
/*	fprintf(stderr,"temp5 = %s\n",temp5);	*/
  }
  strncat(temp5,temp4,strlen(temp4));

 fprintf(stderr,"\nORDRCHG: temp5 = %s\n\n",temp5);	
// exit(0);	


  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
/*  	fprintf(stderr,"ORDRCHG:Connection success\n");	*/

  res = mysql_query(&my_connection,temp5);

  if (!res){
 	fprintf(stdout,"OK: ORDRCHG Inserted %lu rows\n",
		(unsigned long)mysql_affected_rows(&my_connection));
        }else{
	fprintf(stderr,"Error: ORDRCHG INSERT error: %d  %s\n", mysql_errno(&my_connection),
					mysql_error(&my_connection));
	}
	mysql_close(&my_connection);
 }else {
	fprintf(stderr,"Error: ORDRCHG Connection failed\n");
 	if (mysql_errno(&my_connection))   {
 		fprintf(stderr,"Error: ORDRCHG Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
	}
  }
 	fprintf(stdout,"\n");
  return EXIT_SUCCESS;
}

int which_database(char *envp[])
{
	FILE *fil_pek;

//	char home[]="$HOME";
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
//			fprintf(stderr,"temp=%s\n",temp);
			status=strcmp(temp,"HOME");
//			fprintf(stderr,"status=%d\n",status);
			if (status == 0){
				home_pek=(strstr(envp[i],"HOME="));
				home_pek=home_pek+5;
				strcpy(home,home_pek);
			}
//			fprintf(stderr,"home_pek=%d %s\n",home_pek,home_pek);
//			fprintf(stderr,"home_pek=%d %s\n",home_pek,home_pek);
		}
	}
//	fprintf(stderr,"home=%s\n",home);
	strcpy(filename,home);
	strcat(filename,resource);

//	fprintf(stderr,"filename=%s\n",filename);
	status=-1;

	if ((fil_pek = fopen(filename,"r")) != NULL){
		while (fgets(tmp,150,fil_pek) != NULL){
//			fprintf(stderr,"tmp=%s\n",tmp);
			if(strstr(tmp,"DATABASE=")){
				tmp_pek=(strstr(tmp,"DATABASE="))+9;
				strncpy(database,tmp_pek,strlen(tmp_pek));
				status=0;
			}
		}
//		fprintf(stderr,"database=%s_len=%d\n",database,strlen(database));
		fclose(fil_pek);
	}
	else{
	 	fprintf(stderr,"Error: Filen .olfixrc kan inte �ppnas\n");
	}
	for (i=0;i < strlen(database);i++){
		tmp[i]=database[i];
	}
	tmp[i-1]=0;
//	fprintf(stderr,"tmp=%s, i=%d len tmp=%d\n",tmp,i,strlen(tmp));
	strncpy(database,tmp,strlen(tmp));
	database[strlen(tmp)]=0;

	return status;
}
