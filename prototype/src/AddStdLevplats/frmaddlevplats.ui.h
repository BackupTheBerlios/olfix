/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
/***************************************************************************
                          ADDLEVPW  -  description
                             -------------------
		     version 0.1
    begin                : Sön 7 aug 2003
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
 *****************************************************************/

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

    QString kundid;
    QString levplatsnr;
    QString levadress;
    QString postnr;
    QString postadr;
    QString land;


void frmAddLevplats::init()
{
    lineEditKundID->setFocus();
//    lineEditLevPlatsNr->setFocus();
}

void frmAddLevplats::lineEditKundID_returnPressed()
{
    kundid=lineEditKundID->text();
    if (kundid == "" ){
	QMessageBox::warning( this, "ADDLEVPW","KundID måste fyllas i! \n" );
	lineEditKundID->setFocus();
   }else{
//       qDebug("lineEditKundID::kundid=%s",kundid.latin1());
       lineEditLevPlatsNr->setFocus();
   }        
}

void frmAddLevplats::lineEditLevPlatsNr_returnPressed()
{
    levplatsnr=lineEditLevPlatsNr->text();
    if (levplatsnr == "" ){
    	    QMessageBox::warning( this, "ADDLEVPW", "Platsnummer måste fyllas i! \n" );
	    lineEditLevPlatsNr->setFocus();
	}else{
	    lineEditLevAdress->setFocus();
	}                
}

void frmAddLevplats::lineEditLevAdress_returnPressed()
{
    levadress=lineEditLevAdress->text();
    if (levadress == "" ){
    	    QMessageBox::warning( this, "ADDLEVPW", "Leveransadress måste fyllas i! \n" );
	    lineEditLevAdress->setFocus();
	}else{
	    lineEditPostnr->setFocus();
	}
}

void frmAddLevplats::lineEditPostnr_returnPressed()
{
    postnr=lineEditPostnr->text();
    if (postnr == "" ){
    	    QMessageBox::warning( this, "ADDLEVPW", "Postnummer måste fyllas i! \n" );
	    lineEditPostnr->setFocus();
	}else{
	    lineEditPostAdress->setFocus();
	}    
}

void frmAddLevplats::lineEditPostAdress_returnPressed()
{
    postadr=lineEditPostAdress->text();
    if (postadr == "" ){
    	    QMessageBox::warning( this, "ADDLEVPW", "Postadressen måste fyllas i! \n" );
	    lineEditPostAdress->setFocus();
	}else{
	    lineEditLand->setFocus();
	}
}

void frmAddLevplats::lineEditLand_returnPressed()
{
    land=lineEditLand->text();
    pushButtonOK->setFocus();
}

void frmAddLevplats::pushButtonOK_clicked()
{
//    qDebug("pushButtonOK_clicked::kundid=%s",kundid.latin1());
    AddStandardLevPlats();
}

void frmAddLevplats::AddStandardLevPlats()
{
/************************************************************************/
/*	Skapa leveransplats 001, den första leveransadressen för en kund.		*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);

	process = new QProcess();
	process->addArgument( "STYRMAN");	// OLFIX funktion
	process->addArgument(usr);
	process->addArgument("SLPADD");	
	process->addArgument(kundid);
	process->addArgument(levplatsnr);
	process->addArgument(levadress);
	process->addArgument(postnr);
	process->addArgument(postadr);
	process->addArgument(land);
	frmAddLevplats::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmAddLevplats::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
            frmAddLevplats::connect( process, SIGNAL(processExited() ),this, SLOT(slotPlatsEndOfProcess() ) );

	if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta ADDLEVPW!\n");
		QMessageBox::warning( this, "",
                            "Kan inte starta STYRMAN/SLPADD! \n" );
	}
}

void frmAddLevplats::slotPlatsEndOfProcess()
{
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "ADDLEVPW",
		"ERROR!\n"+errorrad
	);
     }
     i = -1;
     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	QMessageBox::information( this, "ADDLEVPW",
		"Uppdatering OK!\n"+errorrad
	);
	lineEditKundID->clear();
	lineEditLevPlatsNr->clear();
	lineEditLevAdress->clear();
	lineEditPostnr->clear();
	lineEditPostAdress->clear();
	lineEditLand->clear();
	fprintf(stdout,"OK: \n ");
    }
     errorrad="";
     inrad="";
     lineEditKundID->setFocus();
}

void frmAddLevplats::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
    qDebug("inrad=%s",inrad.latin1());
}

void frmAddLevplats::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}
