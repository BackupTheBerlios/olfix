/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                          ADDRGTW  -  description
                             -------------------
		     version 0.02
    begin                : Tis 25 mars 2003
    copyright            : (C) 2003 by Jan Pihlgren
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
#define MAXSTRING 5000

    QProcess* process;
    QString inrad;
    QString errorrad;
    QString* rad;
    QString Userid;
    QString Funk;

void frmAddRight::slotAddRight()
{
/************************************************************************/
/*	Uppdatera databasen						*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);
	   
	 frmAddRight::slotUseridEntered();
	 frmAddRight::slotRightEntered();
	    
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// Userid
	process->addArgument( "RGTADD");	// OLFIX funktion
	process->addArgument(Userid);
	process->addArgument(Funk);
	
	frmAddRight::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmAddRight::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmAddRight::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );
 
	
	if (Userid == "" || Funk ==""){
    	    QMessageBox::warning( this, "ADDRGTW",
                      "Userid och/eller Behörighet saknas \n" );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/RGTADD!\n");
		QMessageBox::warning( this, "ADDRGTW",
                            "Kan inte starta STYRMAN/RGTADD! \n" );
	    }   
	}
}

void frmAddRight::slotUseridEntered()
{
    Userid=LineEditUserid->text();
    Userid=Userid.upper();
    LineEditUserid->setText((Userid));
}


void frmAddRight::slotRightEntered()
{
    Funk=LineEditFunk->text();
    Funk=Funk.upper();
    LineEditFunk->setText((Funk));
}


void frmAddRight::init()
{
    LineEditUserid->clear();
    LineEditFunk->clear();
    LineEditUserid->setFocus();
}


void frmAddRight::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
//	qWarning( "slotDataOnStdout: Userid=%s \n", inrad.latin1() );
    }
}

void frmAddRight::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
//	qWarning( "slotDataOnErrout: Userid=%s \n", inrad.latin1() );
    }

}


void frmAddRight::slotEndOfProcess()
{
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "ADDRGTW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
     }
     i = -1;
     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	QMessageBox::information( this, "ADDRGTW",
		"Uppdatering OK!\n"+errorrad
	);
	LineEditUserid->clear();
	LineEditFunk->clear();
	LineEditUserid->setFocus();
	inrad="";
	i = -1;
     }
}
