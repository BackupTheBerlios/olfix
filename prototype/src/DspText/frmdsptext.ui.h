/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
/***************************************************************************
                          DSPTXTW  -  description
                             -------------------
		     version 0.1
    begin                : Tors 24 nov 2005
    copyright            : (C) 2005 by Jan Pihlgren
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
#define MAXSTRING 10000


    QProcess* process;
    QString inrad;
    QString* rad;
    QString errorrad;

    QString textnr;
    QString text;
    
void frmDspText::init()
{
    linEditTextNr->setFocus();
    pushButtonGet->hide();
}

void frmDspText::linEditTextNr_returnPressed()
{
    textnr=linEditTextNr->text();
    textnr=textnr.stripWhiteSpace();
    getText();
}

void frmDspText::getText()
{
/************************************************************************/
/*	Uppdatera databasen						*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);


//	qDebug("textnr=%s",textnr.latin1());

	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "TXTDSP");	// OLFIX funktion
	process->addArgument(textnr);

	frmDspText::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmDspText::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmDspText::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );

	if (textnr == ""){
    	    QMessageBox::warning( this, "DSPTXTW",
                      "Textnummer %s saknas. \n",textnr );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		QMessageBox::warning( this, "DSPTXTW",
                            "Kan inte starta STYRMAN/TXTDSP! \n" );
	    }
	}
}

void frmDspText::slotDataOnStdout()
{
     while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmDspText::slotDataOnStderr()
{
      while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmDspText::slotEndOfProcess()
{
    int i,m;
    QString posttyp;
    
    QString gettextnr;
    QString gettext;
   i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
 //   qDebug("Error:",errorrad);
         if (i != -1) {
	QMessageBox::critical( this, "DSPLEVW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
     }
     i = -1;
     
     i = inrad.find( QRegExp("OK:"), 0 );     
     if (i != -1) {
	 int i1 = inrad.find( QRegExp("1:"), 0 );
	 int i2 = inrad.find( QRegExp("2:"), 0 );
	 int i3 = inrad.length();
		 
	 m=i2-i1;
	 if (i1 != -1){
	     gettextnr=inrad.mid(i1+2,m-4);
	     gettextnr=gettextnr.stripWhiteSpace();
	     linEditTextNr->setText(gettextnr);
	 }

 	 m=i3-i2;
	 if (i2 != -1){
	     gettext=inrad.mid(i2+2,m-4);
//	     lineEditText->setText(gettext);
	     textEdit1->setText(gettext);
	 }
//	 qDebug("posttyp = %s i=%d",posttyp.latin1(),i);
	 inrad="";
	errorrad="";
	inrad="";
	i = -1;
     } 
}

