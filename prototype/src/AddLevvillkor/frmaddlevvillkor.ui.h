/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                          ADDLEVVW  -  description
                             ---------------
    version	: 0.1
    begin                   : Sön 2004
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
    QString* rad;
    QString errorrad;
    QString levvillk;
    QString dagar;
    QString beskrivning;
    
    
void frmAddLevvillkor::init()
{
    LineEditLevvillkor->setFocus();
}

void frmAddLevvillkor::LineEditLevvillkor_returnPressed()
{
    levvillk=LineEditLevvillkor->text();
    LineEditTextLevvillkor->setFocus();
}

void frmAddLevvillkor::LineEditTextLevvillkor_returnPressed()
{
    beskrivning=LineEditTextLevvillkor->text();
    PushButtonOK->setFocus();
}

void frmAddLevvillkor::PushButtonOK_clicked()
{
    frmAddLevvillkor::slotAddLevvillkor();
}

void frmAddLevvillkor::slotAddLevvillkor()
{
/************************************************************************/
/*	Uppdatera databasen						*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);
	   
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "LEVVADD");	// OLFIX funktion
	process->addArgument(levvillk);
	process->addArgument(beskrivning);
	
	frmAddLevvillkor::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmAddLevvillkor::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmAddLevvillkor::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );
 
	if (levvillk == "" ){
    	    QMessageBox::warning( this, "ADDLEVVW",
                      "Leveransvillkor saknas \n" );
	    LineEditLevvillkor->setFocus();
	}
	else {
	    if ( !process->start() ) {
		// error handling
		QMessageBox::warning( this, "ADDLEVVW",
                            "Kan inte starta STYRMAN/LEVVADD! \n" );
	    }   
	}
}

void frmAddLevvillkor::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmAddLevvillkor::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmAddLevvillkor::slotEndOfProcess()
{
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
 //   qDebug("Error:",errorrad);
         if (i != -1) {
	QMessageBox::critical( this, "ADDLEVVW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
     }
     i = -1;
     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	QMessageBox::information( this, "ADDLEVVW",
		"Uppdatering OK!\n"+errorrad
	);
	LineEditLevvillkor->clear();
	LineEditTextLevvillkor->clear();
	LineEditLevvillkor->setFocus();
	inrad="";
	i = -1;
     }
}
