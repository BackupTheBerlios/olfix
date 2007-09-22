/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                          LSTBARW  -  description
	         Lista bokföringsår
                             -------------------
		     version 0.2
    begin                : Tis 1 mars 2005
    modified	          : Fre 27 juli 2007
    copyright          : (C) 2003 by Jan Pihlgren
    email                : jan@pihlgren.se
 ***************************************************************************/

/*****************************************************************
 *					                                                 *
 *   This program is free software; you can redistribute it and/or modify 	 *
 *   it under the terms of the GNU General Public License as published by       *
 *   the Free Software Foundation; either version 2 of the License, or     	 *
 *   (at your option) any later version.                                   		 *
 *                                                                         				 *
 *********************************************** *****************/

#include <qmessagebox.h>
#include <qprocess.h>
#include <qdir.h>
#include <stdlib.h>
#include <qstring.h>		
#include <qfile.h>
#include <qregexp.h>
#include <qlistview.h>
#define MAXSTRING 15000	

	QProcess* process;
	QString inrad;
	QString errorrad;
	QString hjelpfil;

void frmListBar::init()
{
    listView1->clear();
    frmListBar::GetLista();
    PushButtonSluta->setFocus();
}
	
void frmListBar::GetLista()
{	     
	const char *userp = getenv("USER");
                QString usr(userp);
	
	QString bibl;
	errorrad="";
	inrad="";
	
	process = new QProcess();
	process->addArgument("./STYRMAN");
	process->addArgument(usr);		// userid
	process->addArgument( "BARLST");	// OLFIX funktion
	
	frmListBar::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmListBar::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );	
	frmListBar::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );
		
            if ( !process->start() ) {
                     // error handling
	         QMessageBox::warning( this, "Start av BARLST ",
                            "Kan inte starta STYRMAN/BARLST!\n"
                            );
	     }
}	    

void frmListBar::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmListBar::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmListBar::slotEndOfProcess()
{
  QString arid;
  QString benamning;
  QString kontoplan;
  QListViewItem* item;
  QString listrad;
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "LSTBARW","ERROR!\n"+errorrad );
	errorrad="";
	i = -1;
	exit(-1);
    }
    i = inrad.find( QRegExp("OK: NR_0_"), 0 );
    if (i != -1) {
	QMessageBox::information( this, "LSTBARW","Det finns inget bokföringsår registrerat!\n");
	i = -1;
	exit(-1);
    }else{
	     char *pos1;
	     char *pos2;
	     char tmp[MAXSTRING];
	     char *tmppek;
	     int j,k,m;
	     char antrad[6]="";
	     
	     tmppek=tmp;
	     qstrcpy(tmp,inrad);
	     pos1=strstr(tmp,"OK: NR_");
	     pos2=strstr(tmp,"_:");
	     i=pos2-pos1;
	     m=i+2;		// startposition för första arid
	     k=0;
	     for (j=7;j<i;j++){
		 antrad[k]=tmp[j];
		 k++;
	     };
/*	     fprintf(stderr,"antrad=%s\n",antrad);		*/
	     i=atoi(antrad);		// i = antal poster
	     int ant=i;
	     for (k = 1;k <= ant; k++){	            // gå igenom alla raderna / posterna
		 i = j;
		 j = inrad.find(QRegExp("_:"),i+2);
		 if (j < i){
		     k=ant;
		 }
		 m = j - (i+2);
		 arid=inrad.mid(i+2,m);
		 i = j;
		 j = inrad.find(QRegExp("_:"),i+2);
		 m = j - (i+2);
		 benamning=inrad.mid(i+2,m);
		 i = j;
		 j = inrad.find(QRegExp("_:"),i+2);
		 m = j - (i+2);
		 kontoplan=inrad.mid(i+2,m);
		 item = new QListViewItem(listView1,arid,benamning,kontoplan);		 
	     }
	 }	    
}

void frmListBar::slotReloadKonto()
{
    listView1->clear();
     frmListBar::GetLista();
}

void frmListBar::pushBtnHelp_clicked()
{
	inrad="";
	frmListBar::readResursFil();		// Hämta path till hjälpfilen
	
	int i1 = hjelpfil.find( QRegExp(".html"), 0 );
	hjelpfil=hjelpfil.left(i1);
	hjelpfil=hjelpfil+"_EKONOMI.html";
	hjelpfil=hjelpfil+"#REKENSKAPSAR";		// Lägg till position

	process = new QProcess();
	process->addArgument( "./OLFIXHLP" );		// OLFIX program
	process->addArgument(hjelpfil);

	if ( !process->start() ) {
	    // error handling
	    QMessageBox::warning( this, "OLFIX","Kan inte starta OLFIXHLP!\n" );
	}
	PushButtonSluta->setFocus();
}

void frmListBar::readResursFil()
{
    /*****************************************************/
    /*  Läs in .olfixrc filen här			               */
    /* Plocka fram var hjälpfilen finns			               */
    /*****************************************************/

    QStringList lines;
    QString homepath;
    homepath=QDir::homeDirPath();

    QFile f1( homepath+"/.olfixrc" );
   if ( f1.open( IO_ReadOnly ) ) {
        QTextStream stream( &f1 );
        QString line;
        int rad = -1;
        while ( !stream.eof() ) {
            line = stream.readLine(); /* line of text excluding '\n'	*/
	rad=line.find( QRegExp("HELPFILE="), 0 );
	if(rad == 0){
	    hjelpfil=line;
	    hjelpfil=(hjelpfil.right(hjelpfil.length() - 9));
	}
            lines += line;
        }
    }
    f1.close();
}
