/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
/***************************************************************************
                          ADDLEVW  -  description
                             -------------------
		     version 0.02
    begin                : Tis 1 juli 2003
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

    QString levnr;
    QString levorgnr;
    QString levnamn;
    QString levadress;
    QString levpostnr;
    QString levpostadr;
    QString levland;
    QString levtfnnr;
    QString levfaxnr;
    QString levtelexnr;
    QString levemail;
    QString levref;
    QString levreftfnnr;
    QString levmomskod;
    QString levkontonr;
    QString levpgnr;
    QString levbgnr;
    QString levkundnr;
    QString levvaluta;
    QString levbetvilk;
    
void frmAddLev::init()
{
    levmomskod="1";
    lineEditLevMomskod->setText(levmomskod);
    lineditLevNr->setFocus();
}


void frmAddLev::slotLevNr_returnPressed()
{
    levnr=lineditLevNr->text();
    lineEditLevOrgNr->setFocus();
}

void frmAddLev::slotLevOrgNr_returnPressed()
{
    levorgnr=lineEditLevOrgNr->text();
    lineEditLevNamn->setFocus();
}

void frmAddLev::slotLevNamn_returnPressed()
{
    levnamn=lineEditLevNamn->text();
    lineEditLevAdress->setFocus();
}


void frmAddLev::slotLevAdress_returnPressed()
{
    levadress=lineEditLevAdress->text();
    lineEditLevPostnr->setFocus();
}

void frmAddLev::slotLevPostNr_returnPressed()
{
    levpostnr=lineEditLevPostnr->text();
    lineEditLevPostAdress->setFocus();
}

void frmAddLev::slotLevPostAdress_returnPressed()
{
    levpostadr=lineEditLevPostAdress->text();
    lineEditLevLand->setFocus();
}

void frmAddLev::slotLevLand_returnPressed()
{
    levland=lineEditLevLand->text();
    lineEditLevTftnNr->setFocus();
}

void frmAddLev::slotLevTfnNr_returnPressed()
{
     levtfnnr=lineEditLevTftnNr->text();
     lineEditLevFaxNr->setFocus();
}


void frmAddLev::slotLevFaxNr_returnPressed()
{
    levfaxnr=lineEditLevFaxNr->text();
    lineEditLevTelexNr->setFocus();
}

void frmAddLev::slotLevTelexNr_returnPressed()
{
    levtelexnr=lineEditLevTelexNr->text();
    lineEditLevEmail->setFocus();
}

void frmAddLev::slotLevEmail_returnPressed()
{
    levemail=lineEditLevEmail->text();
    lineEditLevRef->setFocus();
}

void frmAddLev::slotLevRef_returnPressed()
{
    levref=lineEditLevRef->text();
    lineEditLevRefTfnNr->setFocus();
}

void frmAddLev::slotLevRefTfnNr_returnPressed()
{
    levreftfnnr=lineEditLevRefTfnNr->text();
    lineEditLevMomskod->setFocus();
}

void frmAddLev::slotLevMomskod_returnPressed()
{
     levmomskod=lineEditLevMomskod->text();
     lineEditLevKontoNr->setFocus();
}

void frmAddLev::slotLevKontoNr_returnPressed()
{
    levkontonr=lineEditLevKontoNr->text();
    lineEditLevPgNr->setFocus();
}

void frmAddLev::slotLevPgNr_returnPressed()
{
    levpgnr=lineEditLevPgNr->text();
    lineEditLevBgNr->setFocus();
}

void frmAddLev::slotLevBgNr_returnPressed()
{
    levbgnr=lineEditLevBgNr->text();
    lineEditLevKundNr->setFocus();
}

void frmAddLev::slotLevKundNr_returnPressed()
{
    levkundnr=lineEditLevKundNr->text();
    lineEditValuta->setFocus();
}

void frmAddLev::slotLevValuta_returnPressed()
{
    levvaluta=lineEditValuta->text();
    lineEditBetvilk->setFocus();
}	

void frmAddLev::slotLevBetvilk_returnPressed()
{
    levbetvilk=lineEditBetvilk->text();
    pushButtonOK->setFocus();
}

void frmAddLev::slotBtnOK_clicked()
{
    slotAddLev();
}


void frmAddLev::slotAddLev()
{
/************************************************************************/
/*	Uppdatera databasen						*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);
	    
	if (levmomskod == ""){
	    levmomskod = "1";
	 }
	if (levbetvilk == ""){
	    levbetvilk ="1";
	}
	
//	qDebug("levnr=%s",levnr.latin1());
//	qDebug("levnamn=%s",levnamn.latin1());
	    
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "LEVADD");	// OLFIX funktion
	process->addArgument(levnr);
	process->addArgument(levorgnr);
	process->addArgument(levnamn);
	process->addArgument(levadress);
	process->addArgument(levpostnr);
	process->addArgument(levpostadr);
	process->addArgument(levland);
	process->addArgument(levtfnnr);
	process->addArgument(levfaxnr);
	process->addArgument(levtelexnr);
	process->addArgument(levemail);
	process->addArgument(levpgnr);
	process->addArgument(levbgnr);
	process->addArgument(levref);
	process->addArgument(levreftfnnr);
	process->addArgument(levmomskod);
	process->addArgument(levkontonr);
	process->addArgument(levkundnr);
	process->addArgument(levvaluta);
	process->addArgument(levbetvilk);
	
	frmAddLev::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmAddLev::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmAddLev::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );
	    
	if (levnr == "" || levnamn ==""){
    	    QMessageBox::warning( this, "ADDVALW",
                      "Leverantörsnummer och/eller leverantörsnamn saknas \n" );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/LEVADD!\n");
		QMessageBox::warning( this, "ADDLEVW",
                            "Kan inte starta STYRMAN/LEVADD! \n" );
	    }
	}
}

void frmAddLev::slotDataOnStdout()
{
     while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }   
}

void frmAddLev::slotDataOnStderr()
{
      while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }  
}

void frmAddLev::slotEndOfProcess()
{
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
//   qDebug("Error:%s",errorrad.latin1());
//   qDebug("Inrad:%s",inrad.latin1());
         if (i != -1) {
	QMessageBox::critical( this, "ADDLEVW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
     }
     i = -1;
     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	QMessageBox::information( this, "ADDLEVW",
		"Uppdatering OK!\n"+errorrad
	);
	lineditLevNr->clear();
	lineEditLevOrgNr->clear();
	lineEditLevNamn->clear();
	lineEditLevAdress->clear();
	lineEditLevPostnr->clear();
	lineEditLevPostAdress->clear();
	lineEditLevLand->clear();
	lineEditLevTftnNr->clear();
	lineEditLevFaxNr->clear();
	lineEditLevTelexNr->clear();
	lineEditLevEmail->clear();
	lineEditLevRef->clear();
	lineEditLevRefTfnNr->clear();
	lineEditLevMomskod->clear();
	lineEditLevKontoNr->clear();
	lineEditLevPgNr->clear();
	lineEditLevBgNr->clear();
	lineEditLevKundNr->clear();
	lineditLevNr->setFocus();
	levmomskod="1";
	lineEditLevMomskod->setText(levmomskod);

	inrad="";
	i = -1;
     } 
}
