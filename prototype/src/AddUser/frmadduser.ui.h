/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                          ADDUSRW  -  description
                             -------------------
		     version 0.01
    begin                : Fre 21 febr 2003
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
    QString Userid;
    QString Namn="";
    QString Avd;
    QString Grupp;
    QString inrad;
    QString errorrad;
    QString* rad;


void frmAddUser::slotAddUser()
{
/************************************************************************/
/*	Uppdatera databasen						*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);
	   
	    
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "USERADD");	// OLFIX funktion
	process->addArgument(Userid);
	process->addArgument(Namn);
	process->addArgument(Avd);
	process->addArgument(Grupp);
	
	frmAddUser::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmAddUser::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmAddUser::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );

	// qWarning( "AddUser: Userid=%s  Namn=%s  Avd=%s  Grupp=%s\n", Userid.latin1(),Namn.latin1() ,Avd.latin1(),Grupp.latin1());

	if (Userid == "" || Namn ==""){
    	    QMessageBox::warning( this, "ADDUSRW",
                      "USERID och/eller Namn saknas \n" );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/USRADD!\n");
		QMessageBox::warning( this, "ADDUSRW",
                            "Kan inte starta STYRMAN/USRADD! \n" );
	    }   
	}
}

void frmAddUser::slotUserIdEntered()
{
    Userid=LineEditUserId->text();
    Userid=Userid.upper();
    LineEditUserId->setText((Userid));
}

void frmAddUser::slotNameEntered()
{
    Namn=LineEditName->text();
}

void frmAddUser::slotAvdEntered()
{
     Avd=LineEditAvd->text();
}

void frmAddUser::slotGruppEntered()
{
    Grupp=LineEditGrupp->text();
}

void frmAddUser::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmAddUser::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmAddUser::slotEndOfProcess()
{
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "OLFIX - ADDUSRW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
     }
     i = -1;
     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	QMessageBox::information( this, "OLFIX - ADDUSRW",
		"Uppdatering OK!\n"+errorrad
	);
	LineEditUserId->clear();
	LineEditName->clear();
	LineEditAvd->clear();
	LineEditGrupp->clear();
	LineEditUserId->setFocus();
	inrad="";
	i = -1;
     }
}

