/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                          ADDBETVW  -  description
                             ---------------
    version	: 0.1
    begin                   : Lör 22 nov 2003
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
    QString betvillk;
    QString dagar;
    QString beskrivning;
    
    
void frmAddBetalvillkor::init()
{
    LineEditBetvillkor->setFocus();
}

void frmAddBetalvillkor::slotAddBetvillkor()
{
/************************************************************************/
/*	Uppdatera databasen						*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);
	   
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "BETADD");	// OLFIX funktion
	process->addArgument(betvillk);
	process->addArgument(dagar);
	process->addArgument(beskrivning);
	
	frmAddBetalvillkor::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmAddBetalvillkor::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmAddBetalvillkor::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );
 
	if (betvillk == "" || dagar ==""){
    	    QMessageBox::warning( this, "ADDBETVW",
                      "Betalningsvillkor och/eller dagar saknas \n" );
	    LineEditBetvillkor->setFocus();
	}
	else {
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/BETADD!\n");
		QMessageBox::warning( this, "ADDBETVW",
                            "Kan inte starta STYRMAN/BETADD! \n" );
	    }   
	}
}

void frmAddBetalvillkor::slotBetvillkorEntered()
{
    betvillk=LineEditBetvillkor->text();
//    betvillk=betvillk.upper();
//    LineEditBetvillkor->setText((betvillk));
    LineEditDagar->setFocus();
}

void frmAddBetalvillkor::slotDagarEntered()
{
    dagar=LineEditDagar->text();
    LineEditBeskrivning->setFocus();
}

void frmAddBetalvillkor::slotBeskrivningEntered()
{
    beskrivning=LineEditBeskrivning->text();
    PushButtonOK->setFocus();
}


void frmAddBetalvillkor::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmAddBetalvillkor::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmAddBetalvillkor::slotEndOfProcess()
{
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
 //   qDebug("Error:",errorrad);
         if (i != -1) {
	QMessageBox::critical( this, "ADDBETVW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
     }
     i = -1;
     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	QMessageBox::information( this, "ADDBETVW",
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

void frmAddBetalvillkor::PushButtonOK_clicked()
{
    frmAddBetalvillkor::slotAddBetvillkor();
}
