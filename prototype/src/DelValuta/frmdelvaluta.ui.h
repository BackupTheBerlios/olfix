/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                          DELVALW  -  description
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

void frmDelValuta::init()
{
    LineEditValuta->setFocus();
}

    
void frmDelValuta::slotPushButtonGet_clicked()
{
    PushButtonOK->setFocus();
    frmDelValuta::slotGetValuta();
}

void frmDelValuta::slotGetValuta()
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

	frmDelValuta::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotGetDataOnStdout() ) );
	frmDelValuta::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotGetDataOnStderr() ) );
            frmDelValuta::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfGetProcess() ) );

	if (valuta == "" ){
    	    QMessageBox::warning( this, "DDSPVALW",
                      "Valuta saknas \n" );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/VALDSP!\n");
		QMessageBox::warning( this, "DELVALW",
                            "Kan inte starta STYRMAN/VALDSP! \n" );
	    }   
	}
}

void frmDelValuta::slotValutaEntered()
{
    valuta=LineEditValuta->text();
    valuta=valuta.upper();
    LineEditValuta->setText((valuta));
    PushButtonGet->setFocus();
}

void frmDelValuta::slotGetDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmDelValuta::slotGetDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmDelValuta::slotEndOfGetProcess()
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


void frmDelValuta::slotPushButtonOK_clicked()
{
    QString val;
    val=valuta;
     frmDelValuta::slotDelValData(val);
}

void frmDelValuta::slotDelValData(QString mynt )
{
    	const char *userp = getenv("USER");
            QString usr(userp);
	    
	 inrad="";
	 errorrad="";
//	fprintf(stderr,"Valuta=%s\n",mynt.latin1());
            process = new QProcess();
	process->addArgument("./STYRMAN");
	process->addArgument(usr.latin1());	
	process->addArgument( "VALDEL");	// OLFIX program
	process->addArgument( mynt.latin1() );
	frmDelValuta::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDelDataOnStdout() ) );
	frmDelValuta::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDelDataOnStderr() ) );
            frmDelValuta::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfDelProcess() ) );

            if ( !process->start() ) {
                // error handling
	QMessageBox::warning( this, "OLFIX - VALDEL",
                            "Kan inte starta VALDEL!\n"
                            );
	}
}

void frmDelValuta::slotEndOfDelProcess()
{
    int i=-1;
    int j=-1;

//    qDebug("inrad=%s",inrad.latin1());
      i = -1;
      i = errorrad.find( QRegExp("Error:"), 0 );
      if (i == 0) {
	QMessageBox::critical( this, "OLFIX - VALDEL",
		"ERROR!\n"+inrad
		);
	            inrad="";
		i = -1;
      }
      j = -1;
      j = errorrad.find( QRegExp("Error: VALDEL_Deleted error:"), 0 );
      if(j == 0){
	QMessageBox::information( this, "VALDEL - Error!",
		"Borttagningen av valuta misslyckades\n"
		);
	inrad="";
	j = -1;
       }
       i = -1;
       i = inrad.find( QRegExp("OK:"), 0 );
       if(i == 0){
	QMessageBox::information( this, "VALDEL",
		"Uppdatering OK!\n" 
		);
    }
}

void frmDelValuta::slotDelDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmDelValuta::slotDelDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}
