/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                         CHGVALW  -  description
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
    QString inrad;
    QString* rad;
    QString errorrad;
    QString valuta;
    QString beteckning;
    QString land;
    QString kop;
    QString salj;


    
void frmChgValuta::init()
{
    LineEditValuta->setFocus();
}

void frmChgValuta::slotGetValuta()
{
	const char *userp = getenv("USER");
            QString usr(userp);

	 LineEditValuta->clear();
	 LineEditBeteck->clear();
	 LineEditLand->clear();
	 LineEditKop->clear();
	 LineEditSalj->clear();
   	    
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "VALDSP");	// OLFIX funktion
	process->addArgument(valuta);

	frmChgValuta::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotValDataOnStdout() ) );
	frmChgValuta::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotValDataOnStderr() ) );
            frmChgValuta::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfValProcess() ) );

	if (valuta == "" ){
    	    QMessageBox::warning( this, "CHGVALW",
                      "Valuta saknas \n" );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/VALDSP!\n");
		QMessageBox::warning( this, "CHGVALW",
                            "Kan inte starta STYRMAN/VALDSP! \n" );
	    }   
	}
}

void frmChgValuta::slotChgValuta()
{
 /************************************************************************/
/*	Uppdatera databasen						*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);

	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "VALCHG");	// OLFIX funktion
	process->addArgument(valuta);
	process->addArgument(land);
	process->addArgument(salj);
	process->addArgument(kop);
	process->addArgument(beteckning);

	frmChgValuta::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotChgDataOnStdout() ) );
	frmChgValuta::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotChgDataOnStderr() ) );
            frmChgValuta::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfChgProcess() ) );

	if (valuta == "" || beteckning ==""){
    	    QMessageBox::warning( this, "CHGVALW",
                      "Valuta och/eller beteckning saknas \n" );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/VALCHG!\n");
		QMessageBox::warning( this, "CHGVALW",
                            "Kan inte starta STYRMAN/VALCHG! \n" );
	    }
	}     
}

void frmChgValuta::slotValutaEntered()
{
    valuta=LineEditValuta->text();
    valuta=valuta.upper();
    LineEditValuta->setText((valuta));
    PushButtonGet->setFocus();
}

void frmChgValuta::slotBeteckningEntered()
{
    beteckning=LineEditBeteck->text();
    LineEditLand->setFocus();
}

void frmChgValuta::slotLandEntered()
{
    land=LineEditLand->text();
   LineEditKop->setFocus(); 
}

void frmChgValuta::slotKopEntered()
{
    kop=LineEditKop->text();
    LineEditSalj->setFocus();
}

void frmChgValuta::slotSaljEntered()
{
    salj=LineEditSalj->text();
    PushButtonUpdate->setFocus();
}

void frmChgValuta::slotPushButtonGet_clicked()
{
    frmChgValuta::slotGetValuta();
    LineEditValuta->setFocus();
}


void frmChgValuta::slotValDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmChgValuta::slotValDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmChgValuta::slotEndOfValProcess()
{
    int h;
    h = -1;
    h = errorrad.find( QRegExp("Error:"), 0 );
    if (h != -1) {
	QMessageBox::critical( this, "CHGVALW",
		"ERROR!\n"+errorrad
		);
	errorrad="";
	h = -1;
     }
    int m;
    QString valuta;
    QString land;
    QString beteckning;
    QString kop;
    QString salj;

    int i = inrad.find( QRegExp("1:"), 0 );
    int j = inrad.find( QRegExp("2:"), 0 );
    int k = inrad.find( QRegExp("3:"), 0 );
    int l = inrad.find( QRegExp("4:"), 0 );
    int n = inrad.find(QRegExp("5:"),0);

    m=j-i;
    if (i != -1){
	valuta=inrad.mid(i+2,m-2);
	LineEditValuta->setText(valuta);
    }
    m=k-j;
    if ( j != -1){
	land=inrad.mid(j+2,m-2);
	LineEditLand->setText(land);
    }
    m=l-k;
    if ( k != -1){
	beteckning=inrad.mid(k+2,m-2);
	LineEditBeteck->setText(beteckning);
    }
     m=n-l;
    if ( l != -1){
	kop=inrad.mid(l+2,m-2);
	LineEditKop->setText(kop);
    }
    m=inrad.length() - n;
    if ( n != -1){
	salj=inrad.mid(n+2,m-3);
	LineEditSalj->setText(salj);
    } 
        LineEditBeteck->setFocus();
}

void frmChgValuta::slotChgDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmChgValuta::slotChgDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmChgValuta::slotEndOfChgProcess()
{
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "CHGALW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
     }
     i = -1;
     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	QMessageBox::information( this, "CHGVALW",
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
            LineEditValuta->setFocus();
    }
}
