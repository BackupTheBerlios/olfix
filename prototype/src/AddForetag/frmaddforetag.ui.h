/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                          ADDFORW  -  description
                             -------------------
		     version 0.1
    begin                 : Tis 9 nov 2004
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
#include <qwhatsthis.h> 
#define MAXSTRING 5000
#define VERSION "Version: 0.1\n 2004-11-09"

    QProcess* process;
    QString inrad;
    QString errorrad;
    QString* rad;
    QString dbnr;
    QString dbnamn;

    
    
void frmAddForetag::init()
{
    LineEditdbnr->clear();
    LineEditdbnamn->clear();
    slottInformation();
    LineEditdbnr->setFocus();
}
   
void frmAddForetag::slotdbnrEntered()
{
    errorrad="";
    inrad="";
    dbnr=LineEditdbnr->text();
    slotCheckIfExist();
}

void frmAddForetag::slotdbnamnEntered()
{
    dbnamn=LineEditdbnamn->text();
    dbnamn=dbnamn.lower();
    LineEditdbnamn->setText(dbnamn);
    PushButtonOK->setFocus();
}

void frmAddForetag::slotAddForetag()
{
/************************************************************************/
/*	Uppdatera databasen						*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);
	   	    
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// Userid
	process->addArgument( "FORADD");	// OLFIX funktion
	process->addArgument(dbnr);
	process->addArgument(dbnamn);
	
	frmAddForetag::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmAddForetag::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmAddForetag::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );
 
	
	if (dbnr == "" || dbnamn ==""){
    	    QMessageBox::warning( this, "ADDFORW",
                      "Databasnummer och/eller databasnamn saknas \n" );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/FORADD!\n");
		QMessageBox::warning( this, "ADDFORW",
                            "Kan inte starta STYRMAN/FORADD! \n" );
	    }   
	}
}

void frmAddForetag::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmAddForetag::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }

}

void frmAddForetag::slotEndOfProcess()
{
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "ADDFORW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
     }
     i = -1;
     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	QMessageBox::information( this, "ADDFORW",
		"Uppdatering OK!\n"+errorrad
	);
	LineEditdbnr->clear();
	LineEditdbnamn->clear();
	LineEditdbnr->setFocus();
	inrad="";
	i = -1;
     }
}

void frmAddForetag::slottInformation()
{
	QMessageBox::information( this, "ADDFORW",
                   "Databasen MÅSTE fysiskt finnas upplagd! \n\n Denna fuktion uppdaterar bara databasen så att man vet att det \n nya företaget existerar samt möjliggör för användarna att arbeta \n med olika företag." );
}


void frmAddForetag::slotCheckIfExist()
{
	const char *userp = getenv("USER");
            QString usr(userp);
	   	    
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// Userid
	process->addArgument( "FORCHK");	// OLFIX funktion
	process->addArgument(dbnr);

	frmAddForetag::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmAddForetag::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmAddForetag::connect( process, SIGNAL(processExited() ),this, SLOT(slotCheckEndOfProcess() ) );
	
	if (dbnr == ""){
    	    QMessageBox::warning( this, "ADDFORW",
                      "Databasnummer och/eller databasnamn saknas \n" );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/FORCHK!\n");
		QMessageBox::warning( this, "ADDFORW",
                            "Kan inte starta STYRMAN/FORCHK! \n" );
	    }   
	}

}

void frmAddForetag::slotCheckEndOfProcess()
{
    int i;
    QString message;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
/*    message=errorrad.mid(14,errorrad.length()-14);	*/
     if (i != -1) {
/*	QMessageBox::critical( this, "ADDFORW",
		"ERROR! \n\n"+message
	);	
*/
	errorrad="";
	i = -1;
	LineEditdbnamn->setFocus();
     }
     i = -1;
     
     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	QMessageBox::critical( this, "ADDFORW",
		"Databasen finns redan!\n"
	);
	inrad="";
	i = -1;
	LineEditdbnr->clear();
	LineEditdbnr->setFocus();
     }
}
