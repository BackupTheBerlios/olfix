/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                          DELTXTW  -  description
                             -------------------
		     version 0.1
    begin                : Fre 12 dec 2003
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
#define VERSION "Version: 0.1\n 2003-12-12"

    QProcess* process;
    QString inrad;
    QString errorrad;
    QString* rad;
    QString textnr;
    QString text;

    
    
void frmDelTxt::init()
{
    LineEditTextNr->clear();
    textEditText->clear();
    LineEditTextNr->setFocus();
}
   
void frmDelTxt::slotTextNr_returnPressed()
{
    textnr=LineEditTextNr->text();
    pushButtonGetText->setFocus();
}

void frmDelTxt::slotDelTxt()
{
/************************************************************************/
/*	Uppdatera databasen						*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);
	   	    
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// Userid
	process->addArgument( "TXTDEL");	// OLFIX funktion
	process->addArgument(textnr);
	
	frmDelTxt::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmDelTxt::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmDelTxt::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );
 
	
	if (textnr == "") {
    	    QMessageBox::warning( this, "DELTXTW","Textnr saknas! \n" );
	}else {
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/TXTDEL!\n");
		QMessageBox::warning( this, "DELTXTW",
                            "Kan inte starta STYRMAN/TXTDEL! \n" );
	    }   
	}
}

void frmDelTxt::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
//	qWarning( "slotDataOnStdout: Userid=%s \n", inrad.latin1() );
    }
}

void frmDelTxt::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
//	qWarning( "slotDataOnErrout: Userid=%s \n", inrad.latin1() );
    }

}

void frmDelTxt::slotEndOfProcess()
{
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "DELTXTW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
     }
     i = -1;
     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	QMessageBox::information( this, "DELTXTW",
		"Uppdatering OK!\n"+errorrad
	);
	LineEditTextNr->clear();
	textEditText->clear();
	LineEditTextNr->setFocus();
	inrad="";
	i = -1;
     }
}

void frmDelTxt::GetText()
{
	const char *userp = getenv("USER");
            QString usr(userp);
	   	    
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// Userid
	process->addArgument( "TXTDSP");	// OLFIX funktion
	process->addArgument(textnr);
	
	frmDelTxt::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmDelTxt::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmDelTxt::connect( process, SIGNAL(processExited() ),this, SLOT(slotGetTextEndOfProcess() ) );
 
	
	if (textnr == "") {
    	    QMessageBox::warning( this, "DELTXTW","Textnr saknas! \n" );
	}else {
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/TXTDEL!\n");
		QMessageBox::warning( this, "DELTXTW",
                            "Kan inte starta STYRMAN/TXTDEL! \n" );
	    }   
	}
}


void frmDelTxt::slotGetTextEndOfProcess()
{
   int i,m;

    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
 //   qDebug("Error:",errorrad);
    if (i != -1) {
	QMessageBox::critical( this, "DELTXTW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
	text="";
	LineEditTextNr->clear();
	LineEditTextNr->setFocus();
    }else{
	i = -1;
//     qDebug("slotTxtEndOfProcess()::inrad=%s",inrad.latin1());
	i = inrad.find( QRegExp("OK:"), 0 );
	if (i != -1) {
//	    int i1 = inrad.find( QRegExp("01:"), 0 );	//	textnr
	    int i2 = inrad.find( QRegExp("02:"), 0 );	//	text (TXT)
	    int i3 = inrad.find( QRegExp("03:"), 0 );	//	
	    m=i3-i2;
	    if (i2 != -1){
		text=inrad.mid(i2+3,m-4);
		textEditText->setText(text);
		PushButtonOK->setFocus();
	    }
	}
    }
}
