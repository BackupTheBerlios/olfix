/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
/***************************************************************************
                          ADDPKDW  -  description
                             -------------------
		     version 0.1
    begin                : Mån 29 november 2004
    Modified         : 
    copyright            : (C) 2004 by Jan Pihlgren
    email                : jan@pihlgren.se
 ***************************************************************************/
/*****************************************************************
 *					                                                 *
 *   This program is free software; you can redistribute it and/or modify 	 *
 *   it under the terms of the GNU General Public License as published by       *
 *   the Free Software Foundation; either version 2 of the License, or     	 *
 *   (at your option) any later version.                                   		 *
 *                                                                         				 *
 *****************************************************************/

#include <qmessagebox.h>
#include <qprocess.h>
#include <qdir.h>
#include <stdlib.h>
#include <qstring.h>
#include <qfile.h>
#include <qregexp.h>
#include <qvalidator.h> 		// 2003-10-21
#define MAXSTRING 5000


    QProcess* process;
    QString inrad;
    QString* rad;
    QString errorrad;

    QString prodkodnr;
    QString beskrivning="";

void frmAddProdkod::lineEditProduktkod_returnPressed()
{
    prodkodnr=lineEditProduktkod->text();
    lineEditBeskrivning->setFocus();
}

void frmAddProdkod::lineEditBeskrivning_returnPressed()
{
    beskrivning=lineEditBeskrivning->text();
    pushButtonOK->setFocus();
}


void frmAddProdkod::pushButtonOK_clicked()
{
    int status=0;
    if (prodkodnr == "" ){
	QMessageBox::warning( this, "ADDPKDW","Produktkod måste fyllas i! \n" );
	status=-1;
	lineEditProduktkod->setFocus();
    }
  if (status==0){
//    qDebug("pushButtonOK_clicked::prodkodnr=%s",prodkodnr.latin1());
      slotAddProduktkod();
  }
}

void frmAddProdkod::slotAddProduktkod()
{
   /************************************************************************/
/*	Uppdatera databasen						*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);
	   	    
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// Userid
	process->addArgument( "PKDADD");	// OLFIX funktion
	process->addArgument(prodkodnr);
	process->addArgument(beskrivning);
	
	frmAddProdkod::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmAddProdkod::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmAddProdkod::connect( process, SIGNAL(processExited() ),this, SLOT(slotPKodEndOfProcess() ) );
 
	
	if (prodkodnr == "") {
    	    QMessageBox::warning( this, "ADDPKDW","Produktkod saknas! \n" );
	}else {
	    if ( !process->start() ) {
		// error handling
		QMessageBox::warning( this, "ADDPKDW",
                            "Kan inte starta STYRMAN/PKDADD! \n" );
	    }   
	}
}

void frmAddProdkod::slotPKodEndOfProcess()
{
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "ADDPKDW",
		"ERROR!\n"+errorrad
	);
     }
     i = -1;
     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	QMessageBox::information( this, "ADDPKDW",
		"Uppdatering OK!\n"+errorrad
	);
	lineEditProduktkod->clear();
	lineEditBeskrivning->clear();
	fprintf(stdout,"OK: \n ");
    }
     errorrad="";
     inrad="";
     lineEditProduktkod->setFocus();
}

void frmAddProdkod::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
    qDebug("inrad=%s",inrad.latin1());
}

void frmAddProdkod::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}
