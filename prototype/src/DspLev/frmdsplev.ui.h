/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
/***************************************************************************
                          DSPLEVW  -  description
                             -------------------
		     version 0.3
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
#define MAXSTRING 10000


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
    QString levskuld;
    QString levkundnr;
    QString valuta;
    QString betvilk;
    QString betalvillkor;	// antal dagar
    
    QString ftgdata;	// För antal dagar i betalningsvillkor
    QString beskrivning;	// beskrivning av betalningsvillkor

void frmDspLev::init()
{
    lineditLevNr->setFocus();
}

void frmDspLev::slotLevNr_returnPressed()
{
    levnr=lineditLevNr->text();
    slotGetLev();
}

void frmDspLev::slotGetLev()
{
/************************************************************************/
/*	Uppdatera databasen						*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);


//	qDebug("levnr=%s",levnr.latin1());

	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "LEVDSP");	// OLFIX funktion
	process->addArgument(levnr);

	frmDspLev::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmDspLev::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmDspLev::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );

	if (levnr == ""){
    	    QMessageBox::warning( this, "DSPLEVW",
                      "Leverantörsnummer %s saknas. \n",levnr );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/LEVDSP!\n");
		QMessageBox::warning( this, "DSPLEVW",
                            "Kan inte starta STYRMAN/LEVDSP! \n" );
	    }
	}
}

void frmDspLev::slotDataOnStdout()
{
     while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmDspLev::slotDataOnStderr()
{
      while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmDspLev::slotEndOfProcess()
{
    int i,m;
    QString posttyp;
    
    QString getlevnr;
    QString getlevorgnr;
    QString getlevnamn;
    QString getlevadress;
    QString getlevpostnr;
    QString getlevpostadr;
    QString getlevland;
    QString getlevtfnnr;
    QString getlevfaxnr;
    QString getlevtelexnr;
    QString getlevemail;
    QString getlevpgnr;
    QString getlevbgnr;
    QString getlevref;
    QString getlevreftfnnr;
    QString getlevmomskod;
    QString getlevkontonr;
    QString getlevskuld;
    QString getlevkundnr;
    QString getlevvaluta;
    QString getbetvilk;
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
	     getlevnr=inrad.mid(i1+2,m-4);
	     lineditLevNr->setText(getlevnr);
	 }

 	 m=i3-i2;
	 if (i2 != -1){
	     getlevorgnr=inrad.mid(i2+2,m-4);
	     lineEditLevOrgNr->setText(getlevorgnr);
	 }
	 
	 m=i4-i3;
	 if (i3 != -1){
	     getlevnamn=inrad.mid(i3+2,m-4);
	     lineEditLevNamn->setText(getlevnamn);
	 }
	 
	 m=i5-i4;
	 if (i4 != -1){
	     getlevadress=inrad.mid(i4+2,m-4);
	     lineEditLevAdress->setText(getlevadress);
	 }

 	 m=i6-i5;
	 if (i5 != -1){
	     getlevpostnr=inrad.mid(i5+2,m-4);
	     lineEditLevPostnr->setText(getlevpostnr);
	 }
	 
	 m=i7-i6;
	 if (i6 != -1){
	     getlevpostadr=inrad.mid(i6+2,m-4);
	     lineEditLevPostAdress->setText(getlevpostadr);
	 }

 	 m=i8-i7;
	 if (i7 != -1){
	     getlevland=inrad.mid(i7+2,m-4);
	     lineEditLevLand->setText(getlevland);
	 }

 	 m=i9-i8;
	 if (i8 != -1){
	     getlevtfnnr=inrad.mid(i8+2,m-4);
	     lineEditLevTfnNr->setText(getlevtfnnr);
	 }
	 
	 m=i10-i9;
	 if (i9 != -1){
	     getlevfaxnr=inrad.mid(i9+2,m-4);
	     lineEditLevFaxNr->setText(getlevfaxnr);
	 }

 	 m=i11-i10;
	 if (i10 != -1){
	     getlevtelexnr=inrad.mid(i10+3,m-4);
	     lineEditLevTelexNr->setText(getlevtelexnr);
	 }
	 
 	 m=i12-i11;
	 if (i11 != -1){
	     getlevemail=inrad.mid(i11+3,m-4);
	     lineEditLevEmail->setText(getlevemail);
	 }

 	 m=i13-i12;
	 if (i12 != -1){
	     getlevpgnr=inrad.mid(i12+3,m-4);
	     lineEditLevPgNr->setText(getlevpgnr);
	 }
 
 	 m=i14-i13;
	 if (i13 != -1){
	     getlevbgnr=inrad.mid(i13+3,m-4);
	     lineEditLevBgNr->setText(getlevbgnr);
	 }
	 
 	 m=i15-i14;
	 if (i14 != -1){
	     getlevref=inrad.mid(i14+3,m-4);
	     lineEditLevRef->setText(getlevref);
	 }
	 
	 m=i16-i15;
	 if (i15 != -1){
	     getlevreftfnnr=inrad.mid(i15+3,m-4);
	     lineEditLevRefTfnNr->setText(getlevreftfnnr);
	 }

 	 m=i17-i16;
	 if (i16 != -1){
	     getlevmomskod=inrad.mid(i16+3,m-4);
	     lineEditLevMomskod->setText(getlevmomskod);
	 }
	 
	 m=i18-i17;
	 if (i17 != -1){
	     getlevskuld=inrad.mid(i17+3,m-4);
	     lineEditLevSkuld->setText(getlevskuld);
	 }
	 
	 m=i19-i18;
	 if (i18 != -1){
	     getlevkontonr=inrad.mid(i18+3,m-4);
	     lineEditLevKontoNr->setText(getlevkontonr);
	 }
	 
	 m=i20-i19;
	 if (i19 != -1){
	     getlevkundnr=inrad.mid(i19+3,m-4);
	     lineEditLevKundNr->setText(getlevkundnr);
	 }

	 m=i21-i20;
	 if (i20 != -1){
	     getlevvaluta=inrad.mid(i20+3,m-5);
	     lineEditValuta->setText(getlevvaluta);
	 }
	 
	 m=i22-i21;
	 if (i21 != -1){
	     getbetvilk=inrad.mid(i21+3,2);
	     lineEditBetvilk->setText(getbetvilk);
	 }
//	 qDebug("posttyp = %s i=%d",posttyp.latin1(),i);
	 inrad="";
	errorrad="";
	inrad="";
	i = -1;
     } 
//     slotGetBetvilkorData(posttyp);
      slotGetBetvilkorData(getbetvilk);
}

void frmDspLev::slotGetBetvilkorData(QString betvilk)
{
	const char *userp = getenv("USER");
            QString usr(userp);

	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "BETDSP");	// OLFIX funktion
	process->addArgument(betvilk);
//	qDebug("betvilk=%s",betvilk.latin1());
	frmDspLev::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmDspLev::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmDspLev::connect( process, SIGNAL(processExited() ),this, SLOT(slotBetvilkEndOfProcess() ) );

            if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/BETDSP!\n");
		QMessageBox::warning( this, "DSPLEVW",
                            "Kan inte starta STYRMAN/BETDSP! \n" );
	    }
}


void frmDspLev::slotBetvilkEndOfProcess()
{
    int i,j,m;
    
//    qDebug("inrad=%s",inrad.latin1());
    
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
    
     j = -1;
     j = inrad.find( QRegExp("BESKRIVNING:"), 0 );     
     if (j != -1) {
	 m = inrad.length();
	 beskrivning=inrad.mid(i+6,m-2);
	 lineEditBetvilkDag->setText(betalvillkor);
     }
    
     i = -1;
     i = inrad.find( QRegExp("DAGAR:"), 0 );     
     if (i != -1) {
	 m = j-i;
	 betalvillkor=inrad.mid(i+6,m-6);
	 lineEditBetvilkDag->setText(betalvillkor);
     }
//     qDebug("i=%d, j=%d",i,j);
     inrad="";
     i=-1;
}
