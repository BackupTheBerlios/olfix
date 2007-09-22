/****************************************************************/
/**		DSPBARW					*/
/**		Ver 0.3                                                                                    	*/
/**		2004-12-05				*/
/**	Modified:	2007-07-16				*/
/**   Copyright	Jan Pihlgren	jan@pihlgren.se		*/
/****************************************************************/
/*****************************************************************
 *					                                                 *
 *   This program is free software; you can redistribute it and/or modify 	 *
 *   it under the terms of the GNU General Public License as published by       *
 *   the Free Software Foundation; either version 2 of the License, or     	 *
 *   (at your option) any later version.                                   		 *
 *                                                                         				 *
 *********************************************** *****************/
/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
#include <qmessagebox.h>
#include <qprocess.h>
#include <qdir.h>
#include <stdlib.h>
#include <qstring.h>		
#include <qfile.h>
#include <qregexp.h> 
#define VERSION "0.3"
#define MAXSTRING 5000

    QProcess* process;
    QString inrad;
    QString errorrad;
    
    QString arid;		// RäkenskapsårsID
    QString benamn;
    QString arstart;
    QString arslut;
    QString arlast;		// Låst bokföringsår, default N
    QString beskattar;
    QString senverdat;
    QString vernr;		// Nästa verifikationsnummer, default 1
    QString ktoplan;

void frmDspBar::init()
{
    LineEditBar->setFocus();
}    
    
void frmDspBar::LineEditBar_returnPressed()
{
    arid=LineEditBar->text();
    arid=arid.upper();
    LineEditBar->setText((arid));
    if (arid==""){
	QMessageBox::warning( this, "DSPBARW",
                      "Bokföringsår måste fyllas i! \n" );
	LineEditBar->setFocus();
	    }
    pushBtnGet->setFocus();
    slotDspBar();
}

void frmDspBar::PushBtnGet_clicked()
{
    frmDspBar::slotDspBar();
    PushButtonOK->setFocus();
}


void frmDspBar::slotEndOfProcess()
{
    int i,m;
    
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
//	qDebug("frmDspBar-errorrad=%s i=%d\n",errorrad.latin1(),i);
    if (i !=-1) {
	QMessageBox::critical( this, "OLFIX - BARDSP",
		"ERROR!\n"+errorrad+"Räkenskapsår "+arid+" finns ej!"
	);
	LineEditBar->setFocus();
            errorrad="";
	i = -1;
    }
    i=-1;
    i = inrad.find( QRegExp("OK:"), 0 );
    if (i != -1) {
	int i1 = inrad.find( QRegExp("ARID:"), 0 );
	int i2 = inrad.find( QRegExp("BENAMN:"), 0 );
	int i3 = inrad.find( QRegExp("ARSTART:"), 0 );
	int i4 = inrad.find( QRegExp("ARSLUT:"), 0 );
	int i5 = inrad.find( QRegExp("ARLAST:"), 0 );
	int i6 = inrad.find( QRegExp("SVERDAT:"), 0 );
	int i7 = inrad.find( QRegExp("VERNR:"), 0 );
	int i8 = inrad.find( QRegExp("KTOPLAN:"), 0 );
	int i9 = inrad.find( QRegExp("BESKATT:"), 0 );	
	int i10 = inrad.length();
	
	m=i2-i1;
//	qDebug("m=%d i2=%d i1=%d",m,i2,i1);
	 if (i1 != -1){
	     arid=inrad.mid(i1+5,m-7);
	     LineEditBar->setText(arid);
	 }

	 m=i3-i2;
	 if (i2 != -1){
	     benamn=inrad.mid(i2+7,m-9);
	     LineEditBenamn->setText(benamn);
	 }
	 
	 m=i4-i3;
	 if (i3 != -1){
	     arstart=inrad.mid(i3+8,m-10);
	     LineEditStartdatum->setText(arstart);
	 }
	 
	 m=i5-i4;
	 if (i4 != -1){
	     arslut=inrad.mid(i4+7,m-9);
	     LineEditSlutdatum->setText(arslut);
	 }
	 
	 m=i6-i5;
	 if (i5 != -1){
	     arlast=inrad.mid(i5+7,m-9);
	 }
	 
	 m=i7-i6;
	 if (i6 != -1){
	     senverdat=inrad.mid(i6+8,m-10);
	     LineEditSenVerDat->setText(senverdat);
	 }
	 
	 m=i8-i7;
	 if (i7 != -1){
	     vernr=inrad.mid(i7+6,m-8);
	     LineEditNestaVerNr->setText(vernr);
	 }
	 
	 m=i9-i8;
	 if (i8 != -1){
	     ktoplan=inrad.mid(i8+8,m-10);
	     LineEditKontoplan->setText(ktoplan);
	 }
	 
	 m=i10-i9;
	 if (i9 != -1){
	     beskattar=inrad.mid(i9+8,m-10);
	     LineEditBeskattAr->setText(beskattar);
	 } 
    }
    
    inrad="";
    errorrad="";
    i = -1;
}

void frmDspBar::slotAbout()
{
    QString meddelande;
    meddelande="OLFIX - BARDSPW\n Version: ";
    qDebug("VERSION=%s",VERSION);
    meddelande.append(VERSION);
	QMessageBox::information( this, "Om BARDSP",
				  meddelande
		);

}

void frmDspBar::slotDspBar()
{
/************************************************************************/
/*	Hämta data från databasen						*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);
	 arlast.append("N");
	 		    
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "BARDSP");	// OLFIX funktion
	process->addArgument(arid);
	frmDspBar::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmDspBar::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
            frmDspBar::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );	   

	if (arid == "" ){
    	    QMessageBox::warning( this, "DSPBARW",
                      "Bokföringsår måste vara ifyllt!" );
	}
	else {
//	    qWarning(" Startar Addkonto 2");
	    if ( !process->start() ) {
		// error handling
		QMessageBox::warning( this, "DSPBARW",
                            "Kan inte starta STYRMAN/BARDSP! \n" );
	    }
	}
}

void frmDspBar::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmDspBar::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

