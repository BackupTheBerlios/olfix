/***************************************************************************
                          STYRMAN.c  -  description
                             -------------------
			     ver 0.13
    begin                : Mån  30 juni  2003
    Modified		 : Tis  31 jan   2006
    copyright            : (C) 2003 by Jan Pihlgren
    email                : jan@pihlgren.se
 ***************************************************************************/

/*****************************************************************************
                  INPUT:     USERID, TRNSID, trnsdata1, trnsdata2,trnsdata....
                  Function:  Dirigera dataflödet i applikationen OLFIX
                                 Kontrollera behörighet till transaktioner
                  OUTPUT:  errno, error (text)
****************************************************************************/
 /*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/STYRMAN.c,v 1.9 2006/01/31 09:10:03 janpihlgren Exp $ " ;

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>		/* 20060131 */
#include <sys/wait.h>		/* 20060131 */
#include "mysql.h"
#define MAXSTRING 10000
#define FILEPATH 100
#define ANTARG 10

  MYSQL my_connection;
  MYSQL_RES *res_ptr;
  MYSQL_ROW sqlrow;

  char *felpek;
  char datastr[MAXSTRING]="";
  char tmpfilepath[FILEPATH];

  char database[15]="";
  char databas[15]="olfix";	/* 2004-11-11	*/

void display_row();
int which_database(char *envp[]);
int check_Transtyp(char *trnstyp);
int check_User(char *user);
int check_Rights(char *usr, char *tr);
int do_Trans(int argnbr, char *trans[]);
int find_tmp_path(char *envp[]);


/* argv[1] = USERID, argv[2] = TRANSID, argv[3 ...] = data till funktion TRANSID */
int main(int argc, char *argv[], char *envp[])
{
  int status=-15;
  int i;
  char anv[9]="";			/* 2004-11-11		*/
  const char *userp = getenv("USER");	/* vem är inloggad?	*/
/*  char databas[25]="olfix";	*/
  char usr[15];		/* userid	*/
  char transid[9]="";			/* 2004-11-11	*/

  status = find_tmp_path(envp);
  if (status != 0)
	exit(status);
/*
  for (i=0; i<= argc;i++){
	fprintf(stderr,"styrman arg = %d %s\n",i,argv[i]);
	 }
*/
/* ================================================================================	*/
/* 		Val av databas, START							*/
/* ================================================================================	*/

  status = which_database(envp);

  if (status != 0)
	exit(status);

  strncpy(usr,userp,15);			/* Den inloggades userid	*/

  if (strlen(database)!= 0){
	strncpy(databas,database,sizeof(databas));	/* 2005-02-24	*/
  }else{
  	strncpy(databas,"olfixtst",15);		/* olfixtst = testföretag	*/
  }
  /* Om usr (userid) börjar på 'test' eller 'prov' använd databas 'olfixtst' */
  if (strncmp(usr,"test",4)==0 || strncmp(usr,"prov",4)==0 ) {
  	strcpy(databas,"olfixtst");
  }
/*  fprintf(stderr,"KUDSP database = %s databas=%s\n",database,databas);	*/

/* ================================================================================	*/
/* 		Val av databas, END!							*/
/* ================================================================================	*/
  /* Start 		2004-11-11		*/

/*	fprintf(stderr,"argv[3]=%s\n",argv[3]);		*/

      strncpy(anv,argv[1],sizeof(anv));			/* 2005-02-24	*/
/*      fprintf(stderr,"argv[1]=%s\n",argv[1]);	*/
/*	strncpy(anv,argv[1],strlen(anv));	*/
/*      for (i = 0;i <= 8;i++){			*/
	for (i = 0;i <= strlen(argv[1]);i++){		/* 2004-11-11	*/
		anv[i]=toupper(anv[i]);
      }
      anv[strlen(argv[1])+1]='\0';
/*	fprintf(stderr,"anv=%s| anv= %d tecken  argv[1]=%d tecken\n",anv,strlen(anv),strlen(argv[1]));	*/

	strncpy(transid,argv[2],sizeof(transid));	/* 2005-02-24	*/
/*	fprintf(stderr,"argv[2]=%s\n",argv[2]);		*/
	for (i = 0;i <= strlen(argv[2]);i++){
		transid[i]=toupper(transid[i]);
      }
/*	fprintf(stderr,"transid=%s| transid= %d tecken  argv[2]=%d	 tecken\n",transid,strlen(transid),strlen(argv[2]));			*/

  /* Slut 		2004-11-11		*/

  status=check_User(anv);		/* Finns användaren(USERID)?		*/
  if(status != 0){
     fprintf(stderr,"Error: STYRMAN(1). Användare %s finns ej\n",anv);	/* 2004-11-11	*/
     exit(-1);
  }

  status=-15;
  status=check_Transtyp(transid);	/* Finns transaktionstypen(TRANSID)?	*/
  if(status != 0){
     fprintf(stderr,"Error: STYRMAN(2). Function %s finns ej\n",transid);
     exit(-1);
  }

  status=-15;
  status=check_Rights(anv,transid);	/* Har USERID behörighet till TRANSID ?	*/
/*  fprintf(stderr,"STYRMANmain_check_Rights status=%d\n",status);		*/
  if(status != 0){
/*     strncpy(argv[1],anv,strlen(anv));	2004-11-11	*/
     fprintf(stderr,"Error: STYRMAN(3). User %s har ej behörighet till %s\n",anv,transid);
     exit(-1);
  }

  status=-15;
/*  fprintf(stderr,"argv[2]=%s\n",argv[2]);					*/
  status=do_Trans(argc, argv);		/* Genomför transaktionen.		*/
  if(status != 0){
  	fprintf(stderr,"%s\n",felpek);
	exit (-1);
  }
  else{
  	fprintf(stdout,"%s\n",datastr);
/*  	fprintf(stdout,"OK: STYRMAN_main. Status: = %d  Antal argument = %d\n",status,argc);	*/
  }
  return EXIT_SUCCESS;
}

/* 				Slut på main					*/
/* ============================================================================ */
/*				Början på funktioner				*/

int do_Trans(int argnbr, char *trans[])
{
	int i;
	int status=-15;
	int fds[2];
	char tmp[FILEPATH]="";
	char func[FILEPATH]="";

/*	fprintf(stderr,"\npath=%s\n",tmpfilepath);		*/
  	i=strlen(tmpfilepath);
  	strncpy(tmp,tmpfilepath,i-1);
  	strncat(tmp,trans[2],strlen(trans[2]));
  	strncpy(func,tmp,strlen(tmp));
/*	fprintf(stderr,"\n\nfunc=%s\n",func);			*/
	pid_t pid;
/*	fprintf(stderr,"1) argnr=%d\n",argnbr);			*/
/*	for (i=0;i<=argnbr;i++){				*/
/*		fprintf(stderr,"trans[%d] = %s\n",i,trans[i]);	*/
/*	}							*/
/*	fprintf(stderr,"func=%s\n",func);			*/

	pipe(fds);
	pid =fork();
        if (pid == (pid_t) 0) {		/* Child */
		close (fds[0]);
		dup2 (fds[1], STDERR_FILENO);
		if (argnbr==3){
			status=execl(func, func,(char *) 0);
		}
		if (argnbr==4){
			status=execl(func, func, trans[3],(char *) 0);
		}
		if (argnbr==5){
			status=execl(func, func, trans[3], trans[4],(char *) 0);
		}
		if (argnbr==6){
			status=execl(func, func, trans[3], trans[4],trans[5],(char *) 0);
		}
		if (argnbr==7){
			status=execl(func, func, trans[3], trans[4],trans[5],trans[6],(char *) 0);
		}
		if (argnbr==8){
			status=execl(func, func, trans[3], trans[4],trans[5],trans[6],trans[7],(char *) 0);
		}
		if (argnbr==9){
			status=execl(func, func, trans[3], trans[4],trans[5],trans[6],trans[7],trans[8],(char *) 0);
		}
		if (argnbr==10){
			status=execl(func, func, trans[3], trans[4],trans[5],trans[6],trans[7],trans[8],trans[9],(char *) 0);
		}
		if (argnbr==11){
			status=execl(func, func, trans[3], trans[4],trans[5],trans[6],trans[7],trans[8],trans[9],trans[10],(char *) 0);
		}
		if (argnbr==12){
			status=execl(func, func, trans[3], trans[4],trans[5],trans[6],trans[7],trans[8],trans[9],trans[10],trans[11],(char *) 0);
		}
		if (argnbr==13){
			status=execl(func, func, trans[3], trans[4],trans[5],trans[6],trans[7],trans[8],trans[9],trans[10],trans[11],trans[12],(char *) 0);
		}
		if (argnbr==14){
			status=execl(func, func, trans[3], trans[4],trans[5],trans[6],trans[7],trans[8],trans[9],trans[10],trans[11],trans[12],trans[13],(char *) 0);
		}
		if (argnbr==15){
			status=execl(func, func, trans[3], trans[4],trans[5],trans[6],trans[7],trans[8],trans[9],trans[10],trans[11],trans[12],trans[13],trans[14],(char *) 0);
		}
		if (argnbr==16){
			status=execl(func, func, trans[3], trans[4],trans[5],trans[6],trans[7],trans[8],trans[9],trans[10],trans[11],trans[12],trans[13],trans[14],trans[15],(char *) 0);
		}
		if (argnbr==17){
			status=execl(func, func, trans[3], trans[4],trans[5],trans[6],trans[7],trans[8],trans[9],trans[10],trans[11],trans[12],trans[13],trans[14],trans[15],trans[16],(char *) 0);
		}
		if (argnbr==18){
			status=execl(func, func, trans[3], trans[4],trans[5],trans[6],trans[7],trans[8],trans[9],trans[10],trans[11],trans[12],trans[13],trans[14],trans[15],trans[16],trans[17],(char *) 0);
		}
		if (argnbr==19){
			status=execl(func, func, trans[3], trans[4],trans[5],trans[6],trans[7],trans[8],trans[9],trans[10],trans[11],trans[12],trans[13],trans[14],trans[15],trans[16],trans[17],trans[18],(char *) 0);
		}
		if (argnbr==20){
			status=execl(func, func, trans[3], trans[4],trans[5],trans[6],trans[7],trans[8],trans[9],trans[10],trans[11],trans[12],trans[13],trans[14],trans[15],trans[16],trans[17],trans[18],trans[19],(char *) 0);
		}
		if (argnbr==21){
			status=execl(func, func, trans[3], trans[4],trans[5],trans[6],trans[7],trans[8],trans[9],trans[10],trans[11],trans[12],trans[13],trans[14],trans[15],trans[16],trans[17],trans[18],trans[19],trans[20],(char *) 0);
		}
		if (argnbr==22){
			status=execl(func, func, trans[3], trans[4],trans[5],trans[6],trans[7],trans[8],trans[9],trans[10],trans[11],trans[12],trans[13],trans[14],trans[15],trans[16],trans[17],trans[18],trans[19],trans[20],trans[21],(char *) 0);
		}
		if (argnbr==23){
			status=execl(func, func, trans[3], trans[4],trans[5],trans[6],trans[7],trans[8],trans[9],trans[10],trans[11],trans[12],trans[13],trans[14],trans[15],trans[16],trans[17],trans[18],trans[19],trans[20],trans[21],trans[22],(char *) 0);
		}
		if (argnbr==24){
			status=execl(func, func, trans[3], trans[4],trans[5],trans[6],trans[7],trans[8],trans[9],trans[10],trans[11],trans[12],trans[13],trans[14],trans[15],trans[16],trans[17],trans[18],trans[19],trans[20],trans[21],trans[22],trans[23],(char *) 0);
		}
 }
	else{				/* Parent (Denna process) */
		FILE* stream;
		close (fds[1]);
		stream = fdopen (fds[0],"r");

		status = fread(datastr,MAXSTRING,MAXSTRING,stream);
		fflush (stream);
		close (fds[0]);
		waitpid (pid, NULL,0);
		felpek=strstr(datastr,"Error:");	/* Error: */
		if (felpek !=NULL){
/*			fprintf(stderr,"%s\n",felpek);		*/
			return -1;
		}
		else{
/*			fprintf(stdout,"%s\n",&datastr);	*/ /* returnera data till anropande program. */
			return 0;
		}
	}
	return 0;
}



int check_Transtyp(char *trnstyp)
{

  int res;
  static char sql1[] = "SELECT TRNSID FROM TRANSID WHERE TRNSID=\"";
  static char sql2[] = "\"";
  char sqlcommand[50]="";	/* 50 */
  int status=-15;

  strncpy(sqlcommand,sql1,strlen(sql1));
  strncat(sqlcommand,trnstyp,strlen(trnstyp));
  strncat(sqlcommand,sql2,strlen(sql2));


  mysql_init(&my_connection);

  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
/*	fprintf(stderr,"Connection success\n");		*/

  res = mysql_query(&my_connection,sqlcommand);
  if (res){
	fprintf(stderr,"Error: STYRMAN_check_Transtyp_SELECT error: %s\n",mysql_error(&my_connection));
        }else{
	res_ptr=mysql_store_result(&my_connection);
	if (res_ptr){
		if((unsigned long)mysql_num_rows(res_ptr) > 0){ /* En rad har hittats */
		status=0;
		}else{						/* Ingen rad hittades */
		status=-1;
		}
	if (mysql_errno(&my_connection))  {
		fprintf(stderr,"Error: STYRMAN_check_Transtyp_Retriev error:  %s\n", mysql_error(&my_connection));
		}
	}
	mysql_free_result(res_ptr);
	}
	mysql_close(&my_connection);

  	} else {
    	fprintf(stderr,"Error: STYRMAN_check_Transtyp_Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: STYRMAN_check_Transtyp_Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
	}
    }

  return status;
}

int check_User(char *user)
{
  int res;
  static char sql1[] = "SELECT USERID FROM USR WHERE USERID=\"";
  static char sql2[] = "\"";
  char sqlcommand[50]="";	/* 50 */
  int status=15;
/* Start	2004-11-11			*/
  int i;
  char anv[9]="";
  strncpy(anv,user,strlen(user));
/*  fprintf(stderr,"1.anv=%s\n",anv);		*/
  for (i = 0;i <= strlen(anv);i++){
		anv[i]=toupper(anv[i]);
      }
/*  fprintf(stderr,"2.anv=%s\n",anv);		*/
/* Slut		2004-11-11			*/

  strncpy(sqlcommand,sql1,strlen(sql1));
  strncat(sqlcommand,anv,strlen(anv));
  strncat(sqlcommand,sql2,strlen(sql2));

/*  fprintf(stderr,"sqlkommando=%s\n",sqlcommand);	 2004-11-11	*/
  mysql_init(&my_connection);

  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
/*	fprintf(stderr,"Connection success\n");		*/

  	res = mysql_query(&my_connection,sqlcommand);
/*	fprintf(stderr,"sqlcommand=%s res=%d\n",sqlcommand,res);	*/
  	if (res){
		fprintf(stderr,"Error: STYRMAN_check-User_SELECT error: %s\n",mysql_error(&my_connection));
  	}
  	else{
		res_ptr=mysql_store_result(&my_connection);
		if (res_ptr){
/*		fprintf(stderr,"Retrieved %lu rows\n",(unsigned long)mysql_num_rows(res_ptr));	*/
			if((unsigned long)mysql_num_rows(res_ptr) > 0){ /* En rad har hittats */
				status=0;
			}
			else{						/* Ingen rad hittades */
				status=-1;
			}
			if (mysql_errno(&my_connection))  {
				fprintf(stderr,"Error: STYRMAN_check_User_Retriev error:  %s\n", mysql_error(&my_connection));
			}
		}
		mysql_free_result(res_ptr);
  	}
  	mysql_close(&my_connection);
  }
  else{
    	fprintf(stderr,"Error: STYRMAN_check_User_Connection failed\n");
    	if (mysql_errno(&my_connection))   {
    		fprintf(stderr,"Error: STYRMAN_check_User_Connection error %d:  %s\n",
			mysql_errno(&my_connection), mysql_error(&my_connection));
	}
  }
  return status;
}

int check_Rights(char *usr, char *tr)
{
  int status=-15;
  int res;
  static char sql1[] = "SELECT USERID,TRNSID FROM RIGHTS WHERE USERID=\"";
  static char sql2[]="\"";
  char sqlcommand[200]="";
  static char sql6[14]=" AND TRNSID=\"";

  strncpy(sqlcommand,sql1,strlen(sql1));
/* SELECT FROM RIGHTS WHERE USERID = "  */
  strncat(sqlcommand,usr,strlen(usr));/* KALLE */
/* SELECT FROM RIGHTS WHERE USERID = "KALLE  */
  strncat(sqlcommand,sql2,strlen(sql2)); /*  "     */
/* SELECT FROM RIGHTS WHERE USERID = "KALLE" */
  strncat(sqlcommand,sql6,strlen(sql6));
/* SELECT FROM RIGHTS WHERE USERID = "KALLE" AND TRNSID ="  */
  strncat(sqlcommand,tr,strlen(tr)); /* USERADD */
/* SELECT FROM RIGHTS WHERE USERID = "KALLE" AND TRNSID ="USERADD  */
  strncat(sqlcommand,sql2,strlen(sql2));
/* SELECT FROM RIGHTS WHERE USERID = "KALLE" AND TRNSID ="USERADD"  */
/* fprintf(stderr,"STYRMANcheck_Rights SQL = %s\n",sqlcommand);		*/

  mysql_init(&my_connection);

  if (mysql_real_connect(&my_connection, "localhost",  "olfix", "olfix", databas, 0, NULL, 0)){
/*	fprintf(stderr,"Connection success\n");		*/
  	res = mysql_query(&my_connection,sqlcommand);
  	if (res){
		fprintf(stderr,"Error: STYRMAN_check_Rights_SELECT error: %s\n",mysql_error(&my_connection));
        }
	else{
		res_ptr=mysql_store_result(&my_connection);
		if (res_ptr){
/*			fprintf(stderr,"STYRMANcheck_Rights:Retrieved %lu rows\n",(unsigned long)mysql_num_rows(res_ptr));	*/
			if((unsigned long)mysql_num_rows(res_ptr) > 0){ /* En rad har hittats */
				status=0;
			}else{						/* Ingen rad hittades */
				status=-1;
			}
			if (mysql_errno(&my_connection))  {
				fprintf(stderr,"Error: STYRMAN_check_Rights_Retriev error:  %s\n", mysql_error(&my_connection));
			}
		}
		mysql_free_result(res_ptr);
	}
	mysql_close(&my_connection);
  	} else {
    		fprintf(stderr,"Error: STYRMAN_check_Rights_Connection failed\n");
    		if (mysql_errno(&my_connection))   {
    			fprintf(stderr,"Error: STYRMAN_checkRights_Connection error %d:  %s\n",
				mysql_errno(&my_connection), mysql_error(&my_connection));
		}
    	}
/*  fprintf(stdout,"STYRMANcheck_Rights:Jobb klart. Status = %d\n",status);	*/
  return status;
}

int find_tmp_path(char *envp[])
{
	FILE *fil_pek;

	char home[50];
	char *home_pek;
	char resource[]="/.olfixrc";
	char filename[50]="";
	char tmp[50]="";
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
	strncpy(filename,home,strlen(home));
	strncat(filename,resource,strlen(resource));

	status=-1;

	if ((fil_pek = fopen(filename,"r")) != NULL){
		while (fgets(tmp,50,fil_pek) != NULL){
			if(strstr(tmp,"PATH=")){
				tmp_pek=(strstr(tmp,"PATH="))+5;
				strncpy(tmpfilepath,tmp_pek,strlen(tmp_pek));
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

int which_database(char *envp[])
{
	FILE *fil_pek;

/*	char home[]="$HOME";	*/
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
/*			fprintf(stderr,"temp=%s\n",temp);		*/
			status=strcmp(temp,"HOME");
/*			fprintf(stderr,"status=%d\n",status);		*/
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
/*			fprintf(stderr,"tmp=%s\n",tmp);		*/
			if(strstr(tmp,"DATABASE=")){
				tmp_pek=(strstr(tmp,"DATABASE="))+9;
				strncpy(database,tmp_pek,strlen(tmp_pek));
				status=0;
			}
		}
/*		fprintf(stderr,"database=%s_len=%d\n",database,strlen(database));	*/
		fclose(fil_pek);
	}
	else{
	 	fprintf(stderr,"Error: Filen .olfixrc kan inte öppnas\n");
	}
	for (i=0;i < strlen(database);i++){
		tmp[i]=database[i];
	}
	tmp[i-1]=0;
/*	fprintf(stderr,"tmp=%s, i=%d len tmp=%d\n",tmp,i,strlen(tmp));		*/
	strncpy(database,tmp,strlen(tmp));
	database[strlen(tmp)]=0;

	return status;
}
