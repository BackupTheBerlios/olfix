/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
/***************************************************************************
                          CHGLEVW  -  description
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
    QString levpgnr;
    QString levbgnr;
    QString levref;
    QString levreftfnnr;
    QString levmomskod;
    QString levkontonr;
    QString levkundnr;
    QString valuta;
    QString betvilk;

void frmChgLev::init()
{
    lineditLevNr->setFocus();
}

void frmChgLev::slotLevNr_returnPressed()
{
    levnr=lineditLevNr->text();
    slotGetLev();
}

void frmChgLev::slotGetLev()
{
/************************************************************************/
/*	Hämta data från databasen						*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);


//	qDebug("levnr=%s",levnr.latin1());

	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "LEVDSP");	// OLFIX funktion
	process->addArgument(levnr);

	frmChgLev::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmChgLev::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmChgLev::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfGetProcess() ) );

	if (levnr == ""){
    	    QMessageBox::warning( this, "CHGLEVW",
                      "Leverantörsnummer %s saknas. \n",levnr );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/CHGDSP!\n");
		QMessageBox::warning( this, "CHGLEVW",
                            "Kan inte starta STYRMAN/LEVCHG! \n" );
	    }
	}
}

void frmChgLev::slotDataOnStdout()
{
     while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmChgLev::slotDataOnStderr()
{
      while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmChgLev::slotEndOfGetProcess()
{
    int i,m;

    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
 //   qDebug("Error:",errorrad);
     if (i != -1) {
	QMessageBox::critical( this, "CHGLEVW",
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
	 int i3 = inrad.find( QRegExp("3:"), 0 );
	 int i4 = inrad.find( QRegExp("4:"), 0 );
	 int i5 = inrad.find( QRegExp("5:"), 0 );
	 int i6 = inrad.find( QRegExp("6:"), 0 );
	 int i7 = inrad.find( QRegExp("7:"), 0 );
	 int i8 = inrad.find( QRegExp("8:"), 0 );
	 int i9 = inrad.find( QRegExp("9:"), 0 );
	 int i10 = inrad.find( QRegExp("10:"), 0 );
	 int i11 = inrad.find( QRegExp("11:"), 0 );
	 int i12 = inrad.find( QRegExp("12:"), 0 );
	 int i13 = inrad.find( QRegExp("13:"), 0 );
	 int i14 = inrad.find( QRegExp("14:"), 0 );
	 int i15 = inrad.find( QRegExp("15:"), 0 );
	 int i16 = inrad.find( QRegExp("16:"), 0 );
	 int i17 = inrad.find( QRegExp("17:"), 0 );
	 int i18 = inrad.find( QRegExp("18:"), 0 );
	 int i19 = inrad.find( QRegExp("19:"), 0 );
	 int i20 = inrad.find( QRegExp("20:"), 0 );
	 int i21 = inrad.find( QRegExp("21:"), 0 );
//	 int i22 = inrad.find( QRegExp("22:"), 0 );
//	 int i23 = inrad.find( QRegExp("23:"), 0 );
	 int i22 = inrad.length();

	 m=i2-i1;
	 if (i1 != -1){
	     levnr=inrad.mid(i1+2,m-4);
	     lineditLevNr->setText(levnr);
	 }

 	 m=i3-i2;
	 if (i2 != -1){
	     levorgnr=inrad.mid(i2+2,m-4);
	     lineEditLevOrgNr->setText(levorgnr);
	 }
	 
	 m=i4-i3;
	 if (i3 != -1){
	     levnamn=inrad.mid(i3+2,m-4);
	     lineEditLevNamn->setText(levnamn);
	 }
	 
	 m=i5-i4;
	 if (i4 != -1){
	     levadress=inrad.mid(i4+2,m-4);
	     lineEditLevAdress->setText(levadress);
	 }

 	 m=i6-i5;
	 if (i5 != -1){
	     levpostnr=inrad.mid(i5+2,m-4);
	     lineEditLevPostnr->setText(levpostnr);
	 }
	 
	 m=i7-i6;
	 if (i6 != -1){
	     levpostadr=inrad.mid(i6+2,m-4);
	     lineEditLevPostAdress->setText(levpostadr);
	 }

 	 m=i8-i7;
	 if (i7 != -1){
	     levland=inrad.mid(i7+2,m-4);
	     lineEditLevLand->setText(levland);
	 }

 	 m=i9-i8;
	 if (i8 != -1){
	     levtfnnr=inrad.mid(i8+2,m-4);
	     lineEditLevTfnNr->setText(levtfnnr);
	 }
	 
	 m=i10-i9;
	 if (i9 != -1){
	     levfaxnr=inrad.mid(i9+2,m-4);
	     lineEditLevFaxNr->setText(levfaxnr);
	 }

 	 m=i11-i10;
	 if (i10 != -1){
	     levtelexnr=inrad.mid(i10+3,m-4);
	     lineEditLevTelexNr->setText(levtelexnr);
	 }
	 
 	 m=i12-i11;
	 if (i11 != -1){
	     levemail=inrad.mid(i11+3,m-4);
	     lineEditLevEmail->setText(levemail);
	 }

 	 m=i13-i12;
	 if (i12 != -1){
	     levpgnr=inrad.mid(i12+3,m-4);
	     lineEditLevPgNr->setText(levpgnr);
	 }
	 
 	 m=i14-i13;
	 if (i13 != -1){
	     levbgnr=inrad.mid(i13+3,m-4);
	     lineEditLevBgNr->setText(levbgnr);
	 }
	 
 	 m=i15-i14;
	 if (i12 != -1){
	     levref=inrad.mid(i14+3,m-4);
	     lineEditLevRef->setText(levref);
	 }
	 m=i16-i15;
	 if (i15 != -1){
	     levreftfnnr=inrad.mid(i15+3,m-4);
	     lineEditLevRefTfnNr->setText(levreftfnnr);
	 }

 	 m=i17-i16;
	 if (i16 != -1){
	     levmomskod=inrad.mid(i16+3,m-4);
	     lineEditLevMomskod->setText(levmomskod);
	 }
	 
	 m=i19-i18;
	 if (i18 != -1){
	     levkontonr=inrad.mid(i18+3,m-4);
	     lineEditLevKontoNr->setText(levkontonr);
	 }
	 
	 m=i20-i19;
	 if (i19 != -1){
	     levkundnr=inrad.mid(i19+3,m-4);
	     lineEditLevKundNr->setText(levkundnr);
	 }
	 
	 m=i21-i20;
	 if (i20 != -1){
	     valuta=inrad.mid(i20+3,m-5);
	     lineEditValuta->setText(valuta);
	 }
 	
	 m=i22-i21;
	 if (i21 != -1){
	     betvilk=inrad.mid(i21+3,2);
	     lineEditBetvilk->setText(betvilk);
	 }
	 
	inrad="";
	errorrad="";
	i = -1;
     } 
}

void frmChgLev::slotLevOrgNr_returnPressed()
{
    levorgnr=lineEditLevOrgNr->text();
    lineEditLevNamn->setFocus();
}

void frmChgLev::slotLevNamn_returnPressed()
{
    levnamn=lineEditLevNamn->text();
    lineEditLevAdress->setFocus();
}


void frmChgLev::slotLevAdress_returnPressed()
{
    levadress=lineEditLevAdress->text();
    lineEditLevPostnr->setFocus();
}

void frmChgLev::slotLevPostNr_returnPressed()
{
    levpostnr=lineEditLevPostnr->text();
    lineEditLevPostAdress->setFocus();
}

void frmChgLev::slotLevPostAdress_returnPressed()
{
    levpostadr=lineEditLevPostAdress->text();
    lineEditLevLand->setFocus();
}

void frmChgLev::slotLevLand_returnPressed()
{
    levland=lineEditLevLand->text();
    lineEditLevTfnNr->setFocus();
}

void frmChgLev::slotLevTfnNr_returnPressed()
{
     levtfnnr=lineEditLevTfnNr->text();
     lineEditLevFaxNr->setFocus();
}


void frmChgLev::slotLevFaxNr_returnPressed()
{
    levfaxnr=lineEditLevFaxNr->text();
    lineEditLevTelexNr->setFocus();
}

void frmChgLev::slotLevTelexNr_returnPressed()
{
    levtelexnr=lineEditLevTelexNr->text();
    lineEditLevEmail->setFocus();
}

void frmChgLev::slotLevEmail_returnPressed()
{
    levemail=lineEditLevEmail->text();
    lineEditLevRef->setFocus();
}

void frmChgLev::slotLevRef_returnPressed()
{
    levref=lineEditLevRef->text();
    lineEditLevRefTfnNr->setFocus();
}

void frmChgLev::slotLevRefTfnNr_returnPressed()
{
    levreftfnnr=lineEditLevRefTfnNr->text();
    lineEditLevMomskod->setFocus();
}

void frmChgLev::slotLevMomskod_returnPressed()
{
     levmomskod=lineEditLevMomskod->text();
     lineEditLevKontoNr->setFocus();
}

void frmChgLev::slotLevKontoNr_returnPressed()
{
    levkontonr=lineEditLevKontoNr->text();
    lineEditLevPgNr->setFocus();
}

void frmChgLev::slotLevPgNr_returnPressed()
{
     levpgnr=lineEditLevPgNr->text();
     lineEditLevBgNr->setFocus();
}

void frmChgLev::slotLevBgNr_returnPressed()
{
     levbgnr=lineEditLevBgNr->text();
     lineEditLevKundNr->setFocus();
}

void frmChgLev::slotLevKundNr_returnPressed()
{
     levkundnr=lineEditLevKundNr->text();
     lineEditValuta->setFocus();
}

void frmChgLev::slotValuta_returnPressed()
{
     valuta=lineEditValuta->text();
     lineEditBetvilk->setFocus();
}

void frmChgLev::slotBetvillkor_returnPressed()
{
     betvilk=lineEditBetvilk->text();
     pushButtonOK->setFocus();
}

void frmChgLev::slotUpdateLev()
{
/************************************************************************/
/*	Uppdatera databasen						*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);

	if (levmomskod == ""){
		levmomskod = "1";
	 }

//	qDebug("levnr=%s",levnr.latin1());
//	qDebug("levnamn=%s",levnamn.latin1());
	    
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "LEVCHG");	// OLFIX funktion
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
	process->addArgument(valuta);
	process->addArgument(betvilk);

	frmChgLev::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmChgLev::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmChgLev::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfUpdateProcess() ) );

	if (levnr == "" || levnamn ==""){
    	    QMessageBox::warning( this, "CHGVALW",
                      "Leverantörsnummer och/eller leverantörsnamn saknas \n" );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/LEVCHG!\n");
		QMessageBox::warning( this, "CHGLEVW",
                            "Kan inte starta STYRMAN/LEVCHG! \n" );
	    }
	}
}

void frmChgLev::slotEndOfUpdateProcess()
{
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
 //   qDebug("Error:",errorrad);
         if (i != -1) {
	QMessageBox::critical( this, "CHGLEVW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
     }
     i = -1;
     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	QMessageBox::information( this, "CHGLEVW",
		"Uppdatering OK!\n"+errorrad
	);
	lineditLevNr->clear();
	lineEditLevOrgNr->clear();
	lineEditLevNamn->clear();
	lineEditLevAdress->clear();
	lineEditLevPostnr->clear();
	lineEditLevPostAdress->clear();
	lineEditLevLand->clear();
	lineEditLevTfnNr->clear();
	lineEditLevFaxNr->clear();
	lineEditLevTelexNr->clear();
	lineEditLevEmail->clear();
	lineEditLevRef->clear();
	lineEditLevRefTfnNr->clear();
	lineEditLevMomskod->clear();
	lineEditLevKontoNr->clear();
	lineEditLevAdress->clear();
	lineEditLevPgNr->clear();
	lineEditLevBgNr->clear();
	lineEditLevKundNr->clear();
	lineEditValuta->clear();
	lineEditBetvilk->clear();
	lineditLevNr->setFocus();
	
	inrad="";
	errorrad="";
	i = -1;
     }
}
