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
    version	: 0.1
    begin                   : Fre 28 nov 2003
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
                      "Betalningsvillkor saknas! \n" );
	    LineEditBetvillkor->setFocus();
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
//    qDebug("inrad=%s",inrad.latin1());
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
	 dagar=inrad.mid(i+7,3);
	 LineEditDagar->setText(dagar);
     }
     j = -1;
     m=0;
     j = inrad.find( QRegExp("BESKRIVNING:"), 0 );
     if (j != -1) {
	 m = inrad.length();
	 beskrivning=inrad.mid(j+13,m-47);
	 LineEditBeskrivning->setText(beskrivning);
     }
//     qDebug("m=%d  j=%d j+beskr=%d",m,j,j+12);          
     inrad="";
}
