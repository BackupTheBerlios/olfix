/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                          CHGLSW  -  description
                             -------------------
		     version 0.1
    begin                	: Ons  10 maj 2006
    copyright            	: (C) 2006 by Jan Pihlgren
    email                	: jan@pihlgren.se
 ***************************************************************************/
/*****************************************************************
 *					                                            *
 *   This program is free software; you can redistribute it and/or modify 	 *
 *   it under the terms of the GNU General Public License as published by       	 *
 *   the Free Software Foundation; either version 2 of the License, or     	 *
 *   (at your option) any later version.                                   		 	 *
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
    QProcess* proc;
    QString inrad;
    QString* rad;
    QString errorrad;
    QString artikelnr;
    QString lagerstelle;
    QString lagerhylla;
    QString lagersaldo;
    QString invgrupp;
    QString abckod;
    QString valuta;
    QString seninkpris;
    QString inkvant0;
    QString inkvant1;
    QString inkvant2;
    QString kalkylpris;
    QString plankpris;	// planerat kalkylpris
    QString frystkpris;	// fryst kalkylpris
    QString bestkvant;
    QString bestpunkt;	// beställningspunkt
    QString omkost;
    QString reserverat;	//
    
    QString lagerdata;
    QString flag="-1";	// Markera att TRHD ska uppdateras. -1 = ingen TRHD uppdatering
//    int changeflag=-1;
 
    
void frmChangeLagerstelle::init()
{
    flag="-1";
    LineEditArtikelnr->setFocus();
}

void frmChangeLagerstelle::LineEditArtikelnr_returnPressed()
{
    artikelnr=LineEditArtikelnr->text();
}

void frmChangeLagerstelle::LineEditlagerstelle_returnPressed()
{
    lagerstelle=LineEditLagerstelle->text();
    getLagerstelleData();
}

void frmChangeLagerstelle::LineEditLagerhylla_returnPressed()
{
    lagerhylla = LineEditLagerhylla->text();
}

void frmChangeLagerstelle::lineEditLagersaldo_returnPressed()
{
    lagersaldo = lineEditLagersaldo->text();
    flag="0";
}

void frmChangeLagerstelle::lineEditInvGrp_returnPressed()
{
    invgrupp = lineEditInvGrp->text();
}

void frmChangeLagerstelle::lineEditABCkod_returnPressed()
{
    abckod = lineEditABCkod->text();
}

void frmChangeLagerstelle::lineEditValuta_returnPressed()
{
    valuta = lineEditValuta->text();
}

void frmChangeLagerstelle::lineEditSenInkPris_returnPressed()
{
    seninkpris = lineEditSenInkPris->text();
    flag="0";
}

void frmChangeLagerstelle::lineEditSenInkopsKvantitet_returnPressed()
{
    inkvant0 = lineEditSenInkopsKvantitet->text();
    flag="0";
}

void frmChangeLagerstelle::lineEditNestSenInkopsKvantitet_returnPressed()
{
    inkvant1 =  lineEditNestSenInkopsKvantitet->text();
    flag="0";
}

void frmChangeLagerstelle::lineEditNestNestSenInkopsKvantitet_returnPressed()
{
    inkvant2 = lineEditNestNestSenInkopsKvantitet->text();
    flag="0";
}

void frmChangeLagerstelle::lineEditKalkylpris_returnPressed()
{
    kalkylpris = lineEditKalkylpris->text();
    flag="0";
}

void frmChangeLagerstelle::lineEditPlanKalkylPris_returnPressed()
{
    plankpris = lineEditPlanKalkylPris->text();
    flag="0";
}

void frmChangeLagerstelle::lineEditFrystKalkylPris_returnPressed()
{
    frystkpris = lineEditFrystKalkylPris->text();
    flag="0";
}

void frmChangeLagerstelle::lineEditBestKvantitet_returnPressed()
{
    bestkvant = lineEditBestKvantitet->text();
    flag="0";
}

void frmChangeLagerstelle::lineEditBestPunkt_returnPressed()
{
    bestpunkt = lineEditBestPunkt->text();
}

void frmChangeLagerstelle::lineEditOmkost_returnPressed()
{
    omkost = lineEditOmkost->text();
    flag="0";
}

void frmChangeLagerstelle::lineEditReserverat_returnPressed()
{
    reserverat = lineEditReserverat->text();
}

void frmChangeLagerstelle::getLagerstelleData()
{
/********************************************************************************/
/*	Hämta lagerställedata från databasen 	.				*/
/********************************************************************************/
	const char *userp = getenv("USER");
	QString usr(userp);
	 inrad="";
//	 qDebug("Till ARDSPL lagerstelle=%s artikelnr=%s",lagerstelle.latin1(),artikelnr.latin1());
	process = new QProcess();
	process->addArgument( "./STYRMAN");	// OLFIX funktion
	process->addArgument(usr);
	process->addArgument("ARDSPL");
	process->addArgument(lagerstelle);
	process->addArgument(artikelnr);
	
	frmChangeLagerstelle::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmChangeLagerstelle::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmChangeLagerstelle::connect( process, SIGNAL(processExited() ),this, SLOT(slotgetLaDataEndOfProcess() ) );

	if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta CHGLSW!\n");
		QMessageBox::warning( this, "",
                            "Kan inte starta ARDSPL! \n" );
	}
}

void frmChangeLagerstelle::slotgetLaDataEndOfProcess()
{
    int i,m;

    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
 //   qDebug("Error:",errorrad);
         if (i != -1) {
	QMessageBox::critical( this, "CHGLSW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
     }
     i = -1;
    
//    qDebug("inrad=%s",inrad.latin1());
    
    i = inrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "CHGLSW",
		"ERROR!\n"+inrad
	);
	inrad="";
	i = -1;
    }else{
	i = -1;
	    
	i = inrad.find( QRegExp("OK:"), 0 );
	if (i != -1) {
	    int i1 = inrad.find( QRegExp("01:"), 0 );	//	lagerställe
	    int i2 = inrad.find( QRegExp("02:"), 0 );	//	artikelnr
	    int i3 = inrad.find( QRegExp("03:"), 0 );	//	lagerhylla
	    int i4 = inrad.find( QRegExp("04:"), 0 );	//	lagersaldo
	    int i5 = inrad.find( QRegExp("05:"), 0 );	//	invgrupp		Inventeringsgrupp
	    int i6 = inrad.find( QRegExp("06:"), 0 );	//	abckod		ABC-kod
	    int i7 = inrad.find( QRegExp("07:"), 0 );	//	valuta
	    int i8 = inrad.find( QRegExp("08:"), 0 );	//	seninkpris		Senaste inköpspris
	    int i9 = inrad.find( QRegExp("09:"), 0 );	//	ikvant0		Senaste inköpskvvantitet
	    int i10 = inrad.find( QRegExp("10:"), 0 );	//	ikvant1		Näst senaste inköpskvvantitet
	    int i11 = inrad.find( QRegExp("11:"), 0 );	//	ikvant2		Näst näst senaste inköpskvvantitet
	    int i12 = inrad.find( QRegExp("12:"), 0 );	//	kalkylpris		Gällande kalkylpris
	    int i13 = inrad.find( QRegExp("13:"), 0 );	//	plankpris		Planerat kalkylpris
	    int i14 = inrad.find( QRegExp("14:"), 0 );	//	frystkpris		Fryst kalkylpris
	    int i15 = inrad.find( QRegExp("15:"), 0 );	//	bestkvant		Beställd kvantitet
	    int i16 = inrad.find( QRegExp("16:"), 0 );	//	bestpunkt		Beställningspunkt
	    int i17 = inrad.find( QRegExp("17:"), 0 );	//	omkost		Omkostnader
	    int i18 = inrad.find( QRegExp("18:"), 0 );	//	reserverat		Reserverad kvantitet
	    int i19 =inrad.find( QRegExp("END:"), 0 );// 	Slut på posten
	 
	    m=i2-i1;
	    if (i1 != -1){
		lagerstelle=inrad.mid(i1+3,m-5);
		LineEditLagerstelle->setText(lagerstelle);
	    }	
	 
	    m=i3-i2;
	    if (i2 != -1){
	    	 artikelnr=inrad.mid(i2+3,m-5);
	     	LineEditArtikelnr->setText(artikelnr);	// redan hämtat
	    }
	 
	    m=i4-i3;
	    if (i3 != -1){
		lagerhylla=inrad.mid(i3+3,m-5);
		LineEditLagerhylla->setText(lagerhylla);
	    }

	    m=i5-i4;
	    if (i4 != -1){
		lagersaldo=inrad.mid(i4+3,m-5);
		lineEditLagersaldo->setText(lagersaldo);
	    }

	    m=i6-i5;
	    if (i5 != -1){
		invgrupp=inrad.mid(i5+3,m-5);
		lineEditInvGrp->setText(invgrupp);
	    }

	    m=i7-i6;
	    if (i6 != -1){
		abckod=inrad.mid(i6+3,m-5);
		lineEditABCkod->setText(abckod);
	    }

	    m=i8-i7;
	    if (i7 != -1){
		valuta=inrad.mid(i7+3,m-5);
		lineEditValuta->setText(valuta);		
	    }
    
	    m=i9-i8;
	    if (i8 != -1){
		seninkpris=inrad.mid(i8+3,m-5);
		lineEditSenInkPris->setText(seninkpris);			
	    }
	    
	    m=i10-i9;
	    if (i9 != -1){
		inkvant0=inrad.mid(i9+3,m-5);
		lineEditSenInkopsKvantitet->setText(inkvant0);		
	    }
	    
	    m=i11-i10;
	    if (i10 != -1){
		inkvant1=inrad.mid(i10+3,m-5);
		lineEditNestSenInkopsKvantitet->setText(inkvant1);		
	    }
	    
	    m=i12-i11;
	    if (i11 != -1){
		inkvant2=inrad.mid(i11+3,m-5);
		lineEditNestNestSenInkopsKvantitet->setText(inkvant2);	
	    }
	    
	    m=i13-i12;
	    if (i12 != -1){
		kalkylpris=inrad.mid(i12+3,m-5);
		lineEditKalkylpris->setText(kalkylpris);	
	    }

	    m=i14-i13;
	    if (i13 != -1){
		plankpris=inrad.mid(i13+3,m-5);
		lineEditPlanKalkylPris->setText(plankpris);	// Ska inte visas kär
	    }

	    m=i15-i14;
	    if (i14 != -1){
		frystkpris=inrad.mid(i14+3,m-5);
		lineEditFrystKalkylPris->setText(frystkpris);	// Ska inte visas kär
	    }

	    
	    m=i16-i15;
	    if (i15 != -1){
		bestkvant=inrad.mid(i15+3,m-5);
		lineEditBestKvantitet->setText(bestkvant);
	    }
	    
	    m=i17-i16;
	    if (i16 != -1){
		bestpunkt=inrad.mid(i16+3,m-5);
		lineEditBestPunkt->setText(bestpunkt);
	    }
	    
	    m=i18-i17;
	    if (i17 != -1){
		omkost=inrad.mid(i17+3,m-9);
		lineEditOmkost->setText(omkost);		
	    }
	    
	    m=i19-i18;
	    if (i18 != -1){
		reserverat=inrad.mid(i18+3,m-5);
		lineEditReserverat->setText(reserverat);
	    }
	    
	inrad="";
	errorrad="";
	inrad="";
	i = -1;
          }
    }
}

void frmChangeLagerstelle::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmChangeLagerstelle::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmChangeLagerstelle::updateLagerstalleReg()
{
/************************************************************************/
/*	Uppdatera LAGERSTELLEREG med nya data på artikeln.		*/
/************************************************************************/
    
    QString skilj="_:_";

//    qDebug("artikeldata=%s",artikeldata.latin1());
    lagerdata=skilj;
    lagerdata.append(lagerstelle);
    lagerdata.append(skilj);
    lagerdata.append(artikelnr);
    lagerdata.append(skilj);
    lagerdata.append(lagerhylla);
    lagerdata.append(skilj);
    lagerdata.append(lagersaldo);
    lagerdata.append(skilj);
    lagerdata.append(invgrupp);
    lagerdata.append(skilj);
    lagerdata.append(abckod);
    lagerdata.append(skilj);
    lagerdata.append(valuta);
    lagerdata.append(skilj);
    lagerdata.append(seninkpris);
    lagerdata.append(skilj);
    lagerdata.append(inkvant0);
    lagerdata.append(skilj);
    lagerdata.append(inkvant1);
    lagerdata.append(skilj);
    lagerdata.append(inkvant2);
    lagerdata.append(skilj);
    lagerdata.append(kalkylpris);
    lagerdata.append(skilj);
    lagerdata.append(plankpris);
    lagerdata.append(skilj);
    lagerdata.append(frystkpris);
    lagerdata.append(skilj);
    lagerdata.append(bestkvant);
    lagerdata.append(skilj);
    lagerdata.append(bestpunkt);
    lagerdata.append(skilj);
    lagerdata.append(omkost);
    lagerdata.append(skilj);

    const char *userp = getenv("USER");
    QString usr(userp);
   
    process = new QProcess();
    process->addArgument( "./STYRMAN");	// OLFIX funktion
    process->addArgument(usr);
    process->addArgument("ARCHGL");
    process->addArgument(lagerdata);
    
/*  Data för TRHD (logga data som ger ekonomisk påverkan)	*/	
    process->addArgument(usr);		// vem som gjort ändringen (för TRHDADD)
    process->addArgument(flag);		// om en ekonomisk transaktion gjorts (för ARCHGL)
    process->addArgument("CHGLSW");		// i vilket program transaktionen gjorts (för TRHDADD)
    frmChangeLagerstelle::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
    frmChangeLagerstelle::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
    frmChangeLagerstelle::connect( process, SIGNAL(processExited() ),this, SLOT(slotUpdateEndOfProcess() ) );
    
    if ( !process->start() ) {
	// error handling
	QMessageBox::warning( this, "",
                       "Kan inte starta ARCHGL! \n" );
    }
}


void frmChangeLagerstelle::slotUpdateEndOfProcess()
{
    int i;
//    qDebug("slotUpdateEndOfProcess= %s  %s",errorrad.latin1(),inrad.latin1());
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "CHGLSW, Lagerplatsdata, Uppdatering ","ERROR!\n"+errorrad);
	errorrad="";
	return;
    }
    i = -1;
    i = inrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "CHGLSW, Lagerplats, Uppdatering ","ERROR!\n"+inrad);
	return;
    }

     i = -1;
     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	QMessageBox::information( this, "CHGLSW",
		"Uppdatering OK!\n"	);
	lagerdata="";
	LineEditArtikelnr->clear();
	LineEditLagerstelle->clear();
	LineEditLagerhylla->clear();
	lineEditLagersaldo->clear();
	lineEditInvGrp->clear();
	lineEditABCkod->clear();
	lineEditValuta->clear();
	lineEditSenInkPris->clear();
	lineEditSenInkopsKvantitet->clear();
	lineEditNestSenInkopsKvantitet->clear();
	lineEditNestNestSenInkopsKvantitet->clear();
	lineEditKalkylpris->clear();	
	lineEditPlanKalkylPris->clear();
	lineEditFrystKalkylPris->clear();
	lineEditBestKvantitet->clear();
	lineEditBestPunkt->clear();
	lineEditOmkost->clear();
	lineEditReserverat->clear();
	
    }
}
