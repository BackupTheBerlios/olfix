/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                          DSPKSTW  -  description
                             -------------------
		     version 0.01
    begin                : Sön 22 febr 2003
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
    QString bar;
    QString kstalle;
    QString benamn;


void frmDspKstalle::init()
{
    LineEditBar->setFocus();
}


void frmDspKstalle::LineEditBar_returnPressed()
{
    bar=LineEditBar->text();
    bar=bar.upper();
    LineEditBar->setText(bar);
    LineEditKstalle->setFocus();
}

void frmDspKstalle::LineEditKstalle_returnPressed()
{
    kstalle=LineEditKstalle->text();
    PushButtonGet->setFocus();
}


void frmDspKstalle::slotGetKstalle()
{
	const char *userp = getenv("USER");
            QString usr(userp);
	 benamn="";
	 inrad="";
	 errorrad="";
	 LineEditBar->clear();
	 LineEditKstalle->clear();
	 LineEditBenamn->clear();
	 
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "KSTDSP");	// OLFIX funktion
	process->addArgument(bar);
	process->addArgument(kstalle);
	
	frmDspKstalle::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmDspKstalle::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmDspKstalle::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );

	if (bar == "" || kstalle == "" ){
    	    QMessageBox::warning( this, "DSPKSTW",
                      "Bokföringsår och/eller kostnadsställe saknas \n" );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/KSTDSP!\n");
		QMessageBox::warning( this, "DSPKSTW",
                            "Kan inte starta STYRMAN/KSTDSP! \n" );
	    }
	}
}

void frmDspKstalle::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmDspKstalle::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmDspKstalle::slotEndOfProcess()
{
    int h;
    h = -1;
    h = errorrad.find( QRegExp("Error:"), 0 );
//    qDebug("Error:",errorrad);
         if (h != -1) {
	QMessageBox::critical( this, "DSPKSTW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	h = -1;
     }
    int m;
    int i = inrad.find( QRegExp("1:"), 0 );
    int j = inrad.find( QRegExp("2:"), 0 );
    int k = inrad.find( QRegExp("3:"), 0 );

    m=j-i;
    if (i != -1){
	bar=inrad.mid(i+2,m-2);
	LineEditBar->setText(bar);
    }
    m=k-j;
    if ( j != -1){
	kstalle=inrad.mid(j+2,m-2);
	LineEditKstalle->setText(kstalle);
    }
    m=inrad.length();
    if ( k != -1){
	benamn=inrad.mid(k+2,m-2);
	LineEditBenamn->setText(benamn);
    }
        LineEditBar->setFocus();
}
