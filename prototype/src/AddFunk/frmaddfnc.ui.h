/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                          ADDFNCW  -  description
                             -------------------
		     version 0.1
    begin                : Ons 2 april 2003
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
#include <qwhatsthis.h> 
#define MAXSTRING 5000
#define VERSION "Version: 0.1\n 2003-06-03"

    QProcess* process;
    QString inrad;
    QString errorrad;
    QString* rad;
    QString Func;
    QString LedText;

    
    
void frmAddFnc::init()
{
    LineEditFunc->clear();
    LineEditLedtext->clear();
    LineEditFunc->setFocus();
}
   
void frmAddFnc::slotFuncEntered()
{
    Func=LineEditFunc->text();
    Func=Func.upper();
    LineEditFunc->setText((Func));
}

void frmAddFnc::slotLedTextEntered()
{
    LedText=LineEditLedtext->text();
}

void frmAddFnc::slotAddFnc()
{
/************************************************************************/
/*	Uppdatera databasen						*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);
	   
//	 frmAddFnc::slotFuncEntered();
//	 frmAddFnc::slotLedTextEntered();
	    
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// Userid
	process->addArgument( "TRNSADD");	// OLFIX funktion
	process->addArgument(Func);
	process->addArgument(LedText);
	
	frmAddFnc::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmAddFnc::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmAddFnc::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );
 
	
	if (Func == "" || LedText ==""){
    	    QMessageBox::warning( this, "ADDFNCW",
                      "Funktion och/eller Ledtext saknas \n" );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/TRNSADD!\n");
		QMessageBox::warning( this, "ADDFNCW",
                            "Kan inte starta STYRMAN/TRNSADD! \n" );
	    }   
	}
}

void frmAddFnc::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
//	qWarning( "slotDataOnStdout: Userid=%s \n", inrad.latin1() );
    }
}

void frmAddFnc::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
//	qWarning( "slotDataOnErrout: Userid=%s \n", inrad.latin1() );
    }

}

void frmAddFnc::slotEndOfProcess()
{
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "ADDFNCW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
     }
     i = -1;
     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	QMessageBox::information( this, "ADDFNCW",
		"Uppdatering OK!\n"+errorrad
	);
	LineEditFunc->clear();
	LineEditLedtext->clear();
	LineEditFunc->setFocus();
	inrad="";
	i = -1;
     }
}
