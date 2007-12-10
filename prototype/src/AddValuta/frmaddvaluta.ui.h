/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                          ADDVALW  -  description
                             -------------------
		     version 0.1
    begin                	: Fre 6 juni 2003
    modified		: Sön 9 dec 2007
    copyright            	: (C) 2003 by Jan Pihlgren
    email                	: jan@pihlgren.se
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
#define MAXSTRING 5000

    QProcess* process;
    QString inrad;
    QString* rad;
    QString errorrad;
    QString valuta;
    QString beteckning;
    QString land;
    QString kop;
    QString salj;
    QString hjelpfil;
    
    
void frmAddValuta::init()
{
    showHost();
    LineEditValuta->setFocus();
}

void frmAddValuta::slotAddValuta()
{
/************************************************************************/
/*	Uppdatera databasen						*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);
	   
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "VALADD");	// OLFIX funktion
	process->addArgument(valuta);
	process->addArgument(land);
	process->addArgument(salj);
	process->addArgument(kop);	
	process->addArgument(beteckning);
	
	frmAddValuta::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmAddValuta::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmAddValuta::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );
 
	if (valuta == "" || beteckning ==""){
    	    QMessageBox::warning( this, "ADDVALW",
                      "Valuta och/eller beteckning saknas \n" );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/VALADD!\n");
		QMessageBox::warning( this, "ADDVALW",
                            "Kan inte starta STYRMAN/VALADD! \n" );
	    }   
	}
}

void frmAddValuta::slotValutaEntered()
{
    valuta=LineEditValuta->text();
    valuta=valuta.upper();
    LineEditValuta->setText((valuta));
//    LineEditBeteck->setFocus();
}

void frmAddValuta::slotBeteckningEntered()
{
    beteckning=LineEditBeteck->text();
//    LineEditLand->setFocus();
}

void frmAddValuta::slotLandEntered()
{
    land=LineEditLand->text();
//    LineEditKop->setFocus();
}

void frmAddValuta::slotKopEntered()
{
    kop=LineEditKop->text();
//    LineEditSalj->setFocus();
}

void frmAddValuta::slotSaljEntered()
{
    salj=LineEditSalj->text();
//    PushButtonOK->setFocus();
}

void frmAddValuta::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmAddValuta::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmAddValuta::slotEndOfProcess()
{
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
 //   qDebug("Error:",errorrad);
         if (i != -1) {
	QMessageBox::critical( this, "ADDVALW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
     }
     i = -1;
     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	QMessageBox::information( this, "ADDVALW",
		"Uppdatering OK!\n"+errorrad
	);
	LineEditValuta->clear();
	LineEditBeteck->clear();
	LineEditLand->clear();
	LineEditKop->clear();
	LineEditSalj->clear();
	LineEditValuta->setFocus();
	inrad="";
	i = -1;
     }
}

void frmAddValuta::showHost()
{
 /************************************************************************/
/*	Vilken host/server?						*/
/************************************************************************/
	const char *userp = getenv("USER");
	QString usr(userp);
	 inrad="";
	 
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "HOSTCHK");	// OLFIX funktion
	
	frmAddValuta::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmAddValuta::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
                frmAddValuta::connect( process, SIGNAL(processExited() ),this, SLOT(slotHostEndOfProcess() ) );
 
	if ( !process->start() ) {
	// error handling
	    fprintf(stderr,"Problem starta STYRMAN/HOSTCHK!\n");
		QMessageBox::warning( this, "ADDVALW",
                            "Kan inte starta STYRMAN/HOSTCHK! \n" );
	}
}

void frmAddValuta::slotHostEndOfProcess()
{
//    qDebug("inrad=%s",inrad.latin1());
    /*                                                   Start     2007-12-09                                         */    
    QString host="";
    int l1,l2,m1,m2;
    m1=inrad.find( QRegExp("host="), 0 );
    m2=inrad.find( QRegExp("NR_"), 0 );
    l1=m2-(m1+5);
    l2=m2-m1;
    host=inrad.mid(5,l1);
    inrad=inrad.mid(m2,inrad.length()-m2);
    
//  qDebug("host=%s m1=%d m2=%d l1=%d l2=%d\n",host.latin1(),m1,m2,l1,l2);
    if(host != "127.0.0.1 "){
	 if(host != "localhost "){
	     textLabel1->setText("<u><b>Host</b></u>\n");
	     textLabelHostName->setText(host);
	 }
    }else{
	textLabel1->setText("");
    }
    /*                                                End         2007-12-09                                         */
}

void frmAddValuta::pushBtnHelp_clicked()
{
	inrad="";
	frmAddValuta::readResursFil();		// Hämta path till hjälpfilen

	int i1 = hjelpfil.find( QRegExp(".html"), 0 );
//	int i2 = hjelpfil.length();
	hjelpfil=hjelpfil.left(i1);
	hjelpfil=hjelpfil+"_EKONOMI.html";
	hjelpfil=hjelpfil+"#ADDVALUTA";		// Lägg till position
//	qDebug("hjelpfil=%s",hjelpfil.latin1());

	process = new QProcess();
	process->addArgument( "./OLFIXHLP" );	// OLFIX program
	process->addArgument(hjelpfil);

	if ( !process->start() ) {
	    // error handling
	    QMessageBox::warning( this, "OLFIX","Kan inte starta OLFIXHLP!\n" );
	}
	LineEditValuta->setFocus();
}

void frmAddValuta::readResursFil()
{
    /*****************************************************/
    /*  Läs in .olfixrc filen här			               	*/
    /* Plocka fram var hjälpfilen finns			*/
    /*****************************************************/

    QStringList lines;
    QString homepath;
    homepath=QDir::homeDirPath();
/*    qDebug("Home Path=%s",homepath.latin1());		*/

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
/*	    qDebug("hjelpfil=%s",hjelpfil.latin1());		*/
	    hjelpfil=(hjelpfil.right(hjelpfil.length() - 9));
/*	    qDebug("hjelpfil=%s",hjelpfil.latin1());		*/
	}
            lines += line;
        }
    }
    f1.close();
}

