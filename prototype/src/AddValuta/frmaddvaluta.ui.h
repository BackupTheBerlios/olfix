/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                          ADDVALW  -  description
                             -------------------
		     version 0.02
    begin                : Fre 6 juni 2003
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
    QString valuta;
    QString beteckning;
    QString land;
    QString kop;
    QString salj;
    
    
void frmAddValuta::init()
{
LineEditValuta->setFocus();
}

void frmAddValuta::slotAddValuta()
{
/************************************************************************/
/*	Uppdatera databasen						*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);
	   
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "VALADD");	// OLFIX funktion
	process->addArgument(valuta);
	process->addArgument(land);
	process->addArgument(salj);
	process->addArgument(kop);	
	process->addArgument(beteckning);
	
	frmAddValuta::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmAddValuta::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmAddValuta::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );
 
	if (valuta == "" || beteckning ==""){
    	    QMessageBox::warning( this, "ADDVALW",
                      "Valuta och/eller beteckning saknas \n" );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/VALADD!\n");
		QMessageBox::warning( this, "ADDVALW",
                            "Kan inte starta STYRMAN/VALADD! \n" );
	    }   
	}
}



void frmAddValuta::slotValuta_lostFocus()
{
    slotValutaEntered();
}

void frmAddValuta::slotValutaEntered()
{
    valuta=LineEditValuta->text();
    valuta=valuta.upper();
    LineEditValuta->setText((valuta));
    LineEditBeteck->setFocus();
}

void frmAddValuta::slotBeteckning_lostFocus()
{
    slotBeteckningEntered();
}

void frmAddValuta::slotBeteckningEntered()
{
    beteckning=LineEditBeteck->text();
    LineEditLand->setFocus();
}

void frmAddValuta::slotLand_lostFocus()
{
    slotLandEntered();
}

void frmAddValuta::slotLandEntered()
{
    land=LineEditLand->text();
    LineEditKop->setFocus();
}

void frmAddValuta::slotKop_lostFocus()
{
    slotKopEntered();
}

void frmAddValuta::slotKopEntered()
{
    kop=LineEditKop->text();
    LineEditSalj->setFocus();
}

void frmAddValuta::slotSalj_lostFocus()
{
    slotSaljEntered();
}

void frmAddValuta::slotSaljEntered()
{
    salj=LineEditSalj->text();
}

void frmAddValuta::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmAddValuta::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmAddValuta::slotEndOfProcess()
{
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
 //   qDebug("Error:",errorrad);
         if (i != -1) {
	QMessageBox::critical( this, "ADDVALW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
     }
     i = -1;
     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	QMessageBox::information( this, "ADDVALW",
		"Uppdatering OK!\n"+errorrad
	);
	LineEditValuta->clear();
	LineEditBeteck->clear();
	LineEditLand->clear();
	LineEditKop->clear();
	LineEditSalj->clear();
	LineEditLand->setFocus();
	inrad="";
	i = -1;
     }
}

