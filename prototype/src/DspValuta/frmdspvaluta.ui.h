/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                          DSPVALW  -  description
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

void frmDspValuta::init()
{
    LineEditValuta->setFocus();
}

void frmDspValuta::slotGetValuta()
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

	frmDspValuta::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmDspValuta::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmDspValuta::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );

	if (valuta == "" ){
    	    QMessageBox::warning( this, "DSPVALW",
                      "Valuta saknas \n" );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/VALDSP!\n");
		QMessageBox::warning( this, "DSPVALW",
                            "Kan inte starta STYRMAN/VALDSP! \n" );
	    }   
	}
}

void frmDspValuta::LineEditValuta_returnPressed()
{
    valuta=LineEditValuta->text();
    valuta=valuta.upper();
    LineEditValuta->setText((valuta));
    PushButtonGet->setFocus();
}


void frmDspValuta::PushButtonGet_clicked()
{
    inrad="";
    errorrad="";
    land="";
    beteckning="";
    kop="";
    salj="";
/*   LineEditValuta->clear();
   LineEditBeteck->clear();
   LineEditLand->clear();
   LineEditKop->clear();
   LineEditSalj->clear();
*/ 
    LineEditValuta->setFocus();

    frmDspValuta::slotGetValuta();
}

void frmDspValuta::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmDspValuta::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmDspValuta::slotEndOfProcess()
{
    int h;
    h = -1;
    h = errorrad.find( QRegExp("Error:"), 0 );
//    qDebug("Error:",errorrad);
         if (h != -1) {
	QMessageBox::critical( this, "DSPVALW",
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
        LineEditValuta->setFocus();
}


