/****************************************************************/
/**		main.cpp		OLFIXW				*/
/**		2003-02-05					*/
/**		modified 2003-11-11				*/
/**		Jan Pihlgren	jan@pihlgren.se			*/
/****************************************************************/
/*****************************************************************
 *					                                                 *
 *   This program is free software; you can redistribute it and/or modify 	 *
 *   it under the terms of the GNU General Public License as published by       *
 *   the Free Software Foundation; either version 2 of the License, or     	 *
 *   (at your option) any later version.                                   		 *
 *                                                                         				 *
 *********************************************** *****************/
#include <qmessagebox.h>
#include <qdir.h>
#include <qfile.h>
#include <qstring.h>

#include <qapplication.h>
#include <qpushbutton.h>
#include <qfont.h>
#include "frmolfix.h"
#include <qregexp.h>

#include <qprocess.h>
#include <qlineedit.h>

int which_database(char *envp[]);
char database[15]="";

int main( int argc, char* argv[] , char *envp[])
{
   which_database(envp);

  QApplication myapp( argc, argv );
//  frmOlfix* mywidget = new frmOlfix();
  
/*  fprintf(stderr,"databas=%s\n",database);
    qDebug("databas=%s",database);
*/    
 // mywidget->lineEditDatabase->setText(database);
  
  QString rcfil;
  QString bibl;
  QStringList lines;
  QString homeDir( QDir::homeDirPath() );
  rcfil.append(homeDir);
  rcfil.append("/.olfixrc");	// configfil
// Läs in config filen här
  QFile file(rcfil);
  if ( file.open( IO_ReadOnly ) ) {
	QTextStream stream( &file );
	QString line;
        while ( !stream.eof() ) {
            line = stream.readLine(); // line of text excluding '\n'
            int i = line.find( QRegExp("PATH="), 0 );    // i == 1
	    if ( i == 0){
	    	int l =line.length();
	    	bibl = line.mid(5,l);
	    }
            lines += line;
        }
	file.close();
//	fprintf(stdout,"Bibliotek=%s\n",bibl.latin1() );
  }else{
      	qWarning( "Cannot find the $HOME/.olfixrc file" );
 	fprintf(stderr,"%s\n", rcfil.latin1() );
  }
  QDir::setCurrent ( bibl );
 
  frmOlfix* mywidget = new frmOlfix();
  mywidget->lineEditDatabase->setText(database);
//  frmOlfix Olfix;
  
//  myapp.setMainWidget( &Olfix );
  myapp.setMainWidget( mywidget);
//  Olfix.show();
  mywidget->show();
  return myapp.exec();
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
/*	for (i=0;i < strlen(database);i++){	*/
	for (i=0;i < 15;i++){
		tmp[i]=database[i];
	}
	tmp[i-1]=0;
/*	fprintf(stderr,"tmp=%s, i=%d len(tmp)=%d\n",tmp,i,strlen(tmp));	*/
	strncpy(database,tmp,strlen(tmp));
	database[strlen(tmp)]=0;
/*	fprintf(stderr,"databas=%s\n",database);	*/

	return status;
}
