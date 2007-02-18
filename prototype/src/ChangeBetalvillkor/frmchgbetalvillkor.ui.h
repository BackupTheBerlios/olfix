/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                          CHGBETVW  -  description
                             ---------------
    version	            : 0.2
    begin                   : Fre 28 nov  2003
    modified	            : Sön 18 febr 2007
    copyright            : (C) 2003 by Jan Pihlgren
    email                   : jan@pihlgren.se
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
     QProcess* proc;
    QString inrad;
    QString* rad;
    QString errorrad;
    QString betvillk;
    QString dagar;
    QString beskrivning;
    QString hjelpfil;
    
    
void frmChgBetalvillkor::init()
{
    LineEditBetvillkor->setFocus();
}

void frmChgBetalvillkor::slotChgBetvillkor()
{
/************************************************************************/
/*	Uppdatera databasen						*/
/************************************************************************/
	const char *userp = getenv("USER");
               QString usr(userp);
	   
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "BETCHG");	// OLFIX funktion
	process->addArgument(betvillk);
	process->addArgument(dagar);
	process->addArgument(beskrivning);
	
	frmChgBetalvillkor::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmChgBetalvillkor::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmChgBetalvillkor::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );
 
	if (betvillk == "" || dagar ==""){
    	    QMessageBox::warning( this, "CHGBETVW",
                      "Betalningsvillkor och/eller dagar saknas \n" );
	    LineEditBetvillkor->setFocus();
	}
	else {
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/BETCHG!\n");
		QMessageBox::warning( this, "CHGBETVW",
                            "Kan inte starta STYRMAN/BETCHG! \n" );
	    }   
	}
}

void frmChgBetalvillkor::slotBetvillkorEntered()
{
    betvillk=LineEditBetvillkor->text();
    frmChgBetalvillkor::GetData();
    LineEditDagar->setFocus();
}

void frmChgBetalvillkor::slotDagarEntered()
{
    dagar=LineEditDagar->text();
    LineEditBeskrivning->setFocus();
}

void frmChgBetalvillkor::slotBeskrivningEntered()
{
    beskrivning=LineEditBeskrivning->text();
    PushButtonOK->setFocus();
}


void frmChgBetalvillkor::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmChgBetalvillkor::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmChgBetalvillkor::slotEndOfProcess()
{
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
 //   qDebug("Error:",errorrad);
         if (i != -1) {
	QMessageBox::critical( this, "CHGBETVW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
     }
    i = inrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::information( this, "CHGBETVW",
		"Ingen förändring har gjorts!\n"+inrad
		);
	inrad="";
	i = -1;
    }	 
     i = -1;
     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	QMessageBox::information( this, "CHGBETVW",
		"Uppdatering OK!\n"+errorrad
	);
	LineEditBetvillkor->clear();
	LineEditDagar->clear();
	LineEditBeskrivning->clear();
	LineEditBetvillkor->setFocus();
	inrad="";
	i = -1;
     }
}

void frmChgBetalvillkor::PushButtonOK_clicked()
{
    frmChgBetalvillkor::slotChgBetvillkor();
}


void frmChgBetalvillkor::GetData()
{
/************************************************************************/
/*	Hämta data från databasen						*/
/************************************************************************/
	const char *userp = getenv("USER");
	QString usr(userp);
	
	inrad="";
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "BETDSP");	// OLFIX funktion
	process->addArgument(betvillk);
	
	frmChgBetalvillkor::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmChgBetalvillkor::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmChgBetalvillkor::connect( process, SIGNAL(processExited() ),this, SLOT(slotGetDataEndOfProcess() ) );
 
	    if (betvillk == ""){
    	    QMessageBox::warning( this, "CHGBETVW",
                      "Betalningsvillkor måste anges! \n" );
	    LineEditBetvillkor->setFocus();
	    return;
	}
	else {
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/BETCHG!\n");
		QMessageBox::warning( this, "CHGBETVW",
                            "Kan inte starta STYRMAN/BETDSP! \n" );
	    }   
	}

}

void frmChgBetalvillkor::slotGetDataEndOfProcess()
{
    int i,j,m;
//   qDebug("inrad=%s",inrad.latin1());
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "CHGBETVW",
		"ERROR!\n"+errorrad
		);
	errorrad="";
	i = -1;
    }
     i = -1;
     i = inrad.find( QRegExp("DAGAR:"), 0 );
     if (i != -1) {
	 dagar=inrad.mid(i+6,3);
	 dagar=dagar.stripWhiteSpace();
	 LineEditDagar->setText(dagar);
     }
     j = -1;
     i = -1;
     m=0;
     j = inrad.find( QRegExp("BESKRIVNING:"), 0 );
     i = inrad.find(QRegExp("END:"),0);
     if (j != -1) {
//	 inrad=inrad.stripWhiteSpace();
//	 m = inrad.length();
	 m = i-(j+13);
	 beskrivning=inrad.mid(j+12,m);
	 beskrivning=beskrivning.stripWhiteSpace();
	 LineEditBeskrivning->setText(beskrivning);
//	 qDebug("m=%d  j=%d j+beskr=%d",m,j,j+12);          
     }
//     qDebug("m=%d  j=%d j+beskr=%d",m,j,j+12);          
     inrad="";
}

void frmChgBetalvillkor::slotHelp()			// 2007-01-31
{
	inrad="";
	frmChgBetalvillkor::readResursFil();			// Hämta path till hjälpfilen
	
	int i1 = hjelpfil.find( QRegExp(".html"), 0 );
	hjelpfil=hjelpfil.left(i1);
	hjelpfil=hjelpfil+"_ADMINISTRATION.html";
	hjelpfil=hjelpfil+"#CHGBETV";			// Lägg till position
/*	qDebug("hjelpfil=%s",hjelpfil.latin1());	*/

	proc = new QProcess();
	proc->addArgument( "./OLFIXHLP" );			// OLFIX program
	proc->addArgument(hjelpfil);

	if ( !proc->start() ) {
	    // error handling
	    QMessageBox::warning( this, "OLFIX","Kan inte starta OLFIXHLP!\n" );
	}
}

void frmChgBetalvillkor::readResursFil()			// 2007-01-31
{
    /*****************************************************/
    /*  Läs in .olfixrc filen här			            	*/
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

