/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                          ADDKSTW  -  description
                             -------------------
		     version 0.01
    begin                : Fre 22 febr 2003
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
    QString arid;
    QString benamn;
    QString kstalle;


void frmAddKstalle::init()
{
    LineEditBar->setFocus();
}

void frmAddKstalle::slotBarEntered()
{
    arid=LineEditBar->text();
    arid=arid.upper();
    LineEditBar->setText(arid);
    LineEditKstalle->setFocus();
}

void frmAddKstalle::slotKstalleEntered()
{
    kstalle=LineEditKstalle->text();
    LineEditBenamn->setFocus();
}

void frmAddKstalle::slotBenamnEntered()
{
    benamn=LineEditBenamn->text();
    PushButtonOK->setFocus();
}

void frmAddKstalle::slotPushButtonOK_clicked()
{
    frmAddKstalle::slotAddKstalle();
    LineEditKstalle->setFocus();
}

void frmAddKstalle::slotAddKstalle()
{
/************************************************************************/
/*	Uppdatera databasen						*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);

            errorrad="";
	inrad="";
	
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "KSTADD");	// OLFIX funktion
	process->addArgument(arid);
	process->addArgument(kstalle);
	process->addArgument(benamn);

	frmAddKstalle::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmAddKstalle::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmAddKstalle::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );

	if (arid == "" || kstalle ==""){
    	    QMessageBox::warning( this, "ADDKSTW",
                      "Bokföringsår och/eller kostnadsställe saknas \n" );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/KSTADD!\n");
		QMessageBox::warning( this, "ADDKSTW",
                            "Kan inte starta STYRMAN/KSTADD! \n" );
	    }
	}   
}

void frmAddKstalle::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmAddKstalle::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmAddKstalle::slotEndOfProcess()
{
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "ADDKSTW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
     }
     i = -1;
     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	QMessageBox::information( this, "ADDKSTW",
		"Uppdatering OK!\n"+errorrad
	);
	LineEditKstalle->clear();
	LineEditBenamn->clear();
	LineEditKstalle->setFocus();
	inrad="";
	i = -1;
	arid="";
	kstalle="";
	benamn="";
     }
}

