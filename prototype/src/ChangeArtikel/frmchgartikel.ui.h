/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
/***************************************************************************
                          CHGARW  -  description
                             -------------------
    Version 	: 0.2
    begin                	: Sön 16 nov 2003
    modified	:Mån 24 nov 2003
    copyright             : (C) 2003 by Jan Pihlgren
    email    	: jan@pihlgren.se
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
#include <qvalidator.h> 
#define MAXSTRING 5000


    QProcess* process;
    QString inrad;
    QString errorrad;

    // Artikelgrunddata
    QString artikelnr;
    QString benamn1;
    QString benamn2;
    QString enhet;
    QString omrfaktor;
    QString nettovikt;
    QString volym;
    QString fpris;
    QString ledtid;
    QString prodklass;
    QString prodkto;
    QString artikeltyp;
    QString struktur;
    QString tulltaxenr;
    QString lev1;
    QString lev2;
    QString lev3;
    QString urbenamn;
    QString urland;
    QString levartnr;
    QString artikeldata;		// Summan av ovanstående.
    
    // Lagerplatsdata
    QString lagerplats="1";    
    QString lagerhylla;
    QString lagersaldo="0";
    QString invgrupp;
    QString abckod;
    QString valuta;
    QString seninkpris="0.00";
    QString ikvant0="0.00";
    QString ikvant1="0.00";
    QString ikvant2="0.00";    
    QString kalkylpris="0.00";
    QString plankpris="0.00";
    QString frystkpris="0.00";    
    QString bestkvant="0.00";
    QString bestpunkt="0.00";
    QString omkost="0.00";
    QString lagerdata;		// Summan av lagerplatsdata

    int changeflag=-1;
    int changeflagG=-1;
    
    QRegExp rx1( "[A-Za-z0-9ÅÄÖåäö-]{1,29}" );
    QRegExp rx2( "[0-9]{0,3}" );
    QRegExp rx3( "[A-Za-z0-9ÅÄÖåäö/_ -]{0,29}" );
    QRegExp rx4( "[0-9,.]{1,6}" );
    QRegExp rx5( "\\w{0,5}" );
    QRegExp rx6( "[0-9,.]{0,12}" );
    QRegExp rx7( "[A-Za-z0-9ÅÄÖåäö]{0,10}" );
    QRegExp rx8( "[0-3]{1}" );
    QRegExp rx9( "[BFIT ]{0,1}" );
    QRegExp rx10( "\\d{0,7}" );
    QRegExp rx11( "[A-Za-z0-9ÅÄÖåäö/_ -]{1,29}" );
	
    QRegExpValidator validator1( rx1, 0 );
    QRegExpValidator validator2( rx2, 0 );
    QRegExpValidator validator3( rx3, 0 );
    QRegExpValidator validator4( rx4, 0 );
    QRegExpValidator validator5( rx5, 0 );
    QRegExpValidator validator6( rx6, 0 );
    QRegExpValidator validator7( rx7, 0 );
    QRegExpValidator validator8( rx8, 0 );
    QRegExpValidator validator9( rx9, 0 );
    QRegExpValidator validator10( rx10, 0 );
    QRegExpValidator validator11( rx11, 0 );
    
void frmChgArtikel::init()
{
    lineEditArtikelNr->setValidator(&validator1);
    lineEditBenamning1->setValidator(&validator11);
    lineEditBenamning2->setValidator(&validator3);
    lineEditEnhet->setValidator(&validator5);
    lineEditNettovikt->setValidator(&validator4);
    lineEditVolym->setValidator(&validator4);
    lineEditFpris->setValidator(&validator6);
    lineEditLedtid->setValidator(&validator2);
    lineEditProdklass->setValidator(&validator5);
    lineEditProdkonto->setValidator(&validator5);
    lineEditLev1->setValidator(&validator7);
    lineEditLev2->setValidator(&validator7);
    lineEditLev3->setValidator(&validator7);
    lineEditArtikeltyp->setValidator(&validator8);
    lineEditStruktur->setValidator(&validator9);
    lineEditTulltaxenr->setValidator(&validator10);
    lineEditUrBenamning->setValidator(&validator3);
    lineEditUrsprungsland->setValidator(&validator3);
//    lineEditUrArtikelnr->setValidator(&validator3);
    changeflagG=-1;
    changeflag=-1;
    
    lineEditArtikelNr->setFocus();
}


void frmChgArtikel::lineEditArtikelNr_returnPressed()
{
    artikelnr=lineEditArtikelNr->text();
    frmChgArtikel::getGrunddata();
    lineEditBenamning1->setFocus();
}

void frmChgArtikel::lineEditBenamning1_returnPressed()
{
    if (lineEditBenamning1->text() != benamn1){
	changeflagG=0;
    }
    benamn1=lineEditBenamning1->text();
    lineEditBenamning2->setFocus();
}

void frmChgArtikel::lineEditBenamning2_returnPressed()
{
    if (lineEditBenamning2->text() != benamn2){
	changeflagG=0;
    }
    benamn2=lineEditBenamning2->text();
    if (benamn2==""){
	benamn2=" ";
    }
    lineEditEnhet->setFocus();
}

void frmChgArtikel::lineEditEnhet_returnPressed()
{
    if (lineEditEnhet->text() != enhet){
	changeflagG=0;
    }
    enhet=lineEditEnhet->text();
    if (enhet==""){
	enhet="ST";
	lineEditEnhet->setText(enhet);
    }
    lineEditOmrFaktor->setFocus();
}

void frmChgArtikel::lineEditOmrFaktor_returnPressed()
{
    if (lineEditOmrFaktor->text() !=omrfaktor){
	changeflagG=0;
    }
    omrfaktor=lineEditOmrFaktor->text();
    if (omrfaktor==""){
	omrfaktor="1";
	lineEditOmrFaktor->setText(omrfaktor);
    }
    lineEditFpris->setFocus();
}

void frmChgArtikel::lineEditFpris_returnPressed()
{
    int i;
    if (lineEditFpris->text() != fpris){
	changeflagG=0;
    }
    fpris=lineEditFpris->text();
    if (fpris==""){
	fpris="0.00";	
    }
    i = -1;
    i = fpris.find( QRegExp(","), 0 );
    if (i != -1){
	 fpris.replace( QChar(','), "." );
     }    
    lineEditFpris->setText(fpris);
//    qDebug("Fpris=%s",fpris.latin1());
    lineEditNettovikt->setFocus();
}

void frmChgArtikel::lineEditNettovikt_returnPressed()
{
    int i;
    if (lineEditNettovikt->text() != nettovikt){
	changeflagG=0;
    }
    nettovikt=lineEditNettovikt->text();
    if (nettovikt==""){
	nettovikt="0";
    }
    i = -1;
    i = nettovikt.find( QRegExp(","), 0 );
    if (i != -1){
	 nettovikt.replace( QChar(','), "." );
     }    
    lineEditNettovikt->setText(nettovikt);
//    qDebug("Nettovikt=%s",nettovikt.latin1());
    lineEditVolym->setFocus();
}

void frmChgArtikel::lineEditVolym_returnPressed()
{
    int i;
    if (lineEditVolym->text() != volym){
	changeflagG=0;
    }
    volym=lineEditVolym->text();
    if (volym == ""){
	volym="0.0";
    }
    i = -1;
    i = volym.find( QRegExp(","), 0 );
    if (i != -1){
	 volym.replace( QChar(','), "." );
     }    
    lineEditVolym->setText(volym);
//    qDebug("Volym=%s",volym.latin1());
    lineEditLedtid->setFocus();
}

void frmChgArtikel::lineEditLedtid_returnPressed()
{
    if (lineEditLedtid->text() != ledtid){
	changeflagG=0;
    }
    ledtid=lineEditLedtid->text();
    if (ledtid==""){
	ledtid="0";
	lineEditLedtid->setText(ledtid);
    }
    lineEditProdklass->setFocus();
}

void frmChgArtikel::lineEditProdklass_returnPressed()
{
    if (lineEditProdklass->text() != prodklass){
	changeflagG=0;
    }
    prodklass=lineEditProdklass->text();
    if (prodklass==""){
	prodklass=" ";
    }
    lineEditProdkonto->setFocus();
}

void frmChgArtikel::lineEditProdkonto_returnPressed()
{
    if (lineEditProdkonto->text() != prodkto){
	changeflagG=0;
    }
    prodkto=lineEditProdkonto->text();
    if (prodkto==""){
	prodkto=" ";
    }
    lineEditArtikeltyp->setFocus();
}

void frmChgArtikel::lineEditArtikeltyp_returnPressed()
{
    if (lineEditArtikeltyp->text() != artikeltyp){
	changeflagG=0;
    }
    artikeltyp=lineEditArtikeltyp->text();
    if (artikeltyp==""){
	artikeltyp="2";
	lineEditArtikeltyp->setText(artikeltyp);
    }
    lineEditStruktur->setFocus();
}

void frmChgArtikel::lineEditStruktur_returnPressed()
{
    if (lineEditStruktur->text() != struktur){
	changeflagG=0;
    }
    struktur=lineEditStruktur->text();
    if (struktur==""){
	struktur=" ";
    }
    lineEditTulltaxenr->setFocus();
}

void frmChgArtikel::lineEditTulltaxenr_returnPressed()
{
    if (lineEditTulltaxenr->text() != tulltaxenr){
	changeflagG=0;
    }
    tulltaxenr=lineEditTulltaxenr->text();
    if (tulltaxenr==""){
	tulltaxenr=" ";
    }
    lineEditLev1->setFocus();
}

void frmChgArtikel::lineEditLev1_returnPressed()
{
    if (lineEditLev1->text() != lev1){
	changeflagG=0;
    }
    lev1=lineEditLev1->text();
    if (lev1==""){
	lev1=" ";
    }
    lineEditLev2->setFocus();
}

void frmChgArtikel::lineEditLev2_returnPressed()
{
    if (lineEditLev2->text() != lev2){
	changeflagG=0;
    }    
    lev2=lineEditLev2->text();    
    if (lev2==""){
	lev2=" ";
    }
    lineEditLev3->setFocus();
}

void frmChgArtikel::lineEditLev3_returnPressed()
{
    if (lineEditLev3->text() != lev3){
	changeflagG=0;
    }    
    lev3=lineEditLev3->text();    
    if (lev3==""){
	lev3=" ";
    }
    lineEditUrBenamning->setFocus();
}

void frmChgArtikel::lineEditUrBenamning_returnPressed()
{
    if ( lineEditUrBenamning->text() != urbenamn){
	changeflagG=0;
    }
    urbenamn=lineEditUrBenamning->text();
    if (urbenamn==""){
	urbenamn=" ";
    }
    lineEditUrsprungsland->setFocus();
}

void frmChgArtikel::lineEditUrsprungsland_returnPressed()
{
    if (lineEditUrsprungsland->text() != urland){
	changeflagG=0;
    }
    urland=lineEditUrsprungsland->text();
    if (urland==""){
	urland=" ";
    }
    lineEditUrArtikelnr->setFocus();
}

void frmChgArtikel::lineEditUrArtikelnr_returnPressed()
{
    if (lineEditUrArtikelnr->text() != levartnr){
	changeflagG=0;
    }
    levartnr=lineEditUrArtikelnr->text();
    if (levartnr==""){
	levartnr=" ";
    }
    lineEditLagerhylla_2->setFocus();
}

void frmChgArtikel::pushButtonOK_clicked()
{
    QString skilj;
    skilj="_:_";
    artikeldata=skilj;
    artikeldata.append(artikelnr);
    artikeldata.append(skilj);
    artikeldata.append(benamn1);
    artikeldata.append(skilj);
    artikeldata.append(benamn2);
    artikeldata.append(skilj);
    artikeldata.append(enhet);
    artikeldata.append(skilj);
    artikeldata.append(omrfaktor);
    artikeldata.append(skilj);
    artikeldata.append(nettovikt);
    artikeldata.append(skilj);
    artikeldata.append(fpris);
    artikeldata.append(skilj);
    artikeldata.append(ledtid);
    artikeldata.append(skilj);
    artikeldata.append(prodklass);
    artikeldata.append(skilj);
    artikeldata.append(prodkto);
    artikeldata.append(skilj);
    artikeldata.append(artikeltyp);
    artikeldata.append(skilj);
    artikeldata.append(struktur);
    artikeldata.append(skilj);
    artikeldata.append(tulltaxenr);
    artikeldata.append(skilj);
    artikeldata.append(lev1);
    artikeldata.append(skilj);
    artikeldata.append(lev2);
    artikeldata.append(skilj);
    artikeldata.append(lev3);
    artikeldata.append(skilj);
    artikeldata.append(urbenamn);
    artikeldata.append(skilj);
    artikeldata.append(urland);
    artikeldata.append(skilj);
    artikeldata.append(levartnr);
    artikeldata.append(skilj);
    artikeldata.append(volym);
    artikeldata.append(skilj);

//    qDebug("artikeldata=%s",artikeldata.latin1());
    lagerdata=skilj;
    lagerdata.append(lagerplats);
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
    lagerdata.append(ikvant0);
    lagerdata.append(skilj);
    lagerdata.append(ikvant1);
    lagerdata.append(skilj);
    lagerdata.append(ikvant2);
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

    if (changeflagG == 0){
	updateArtikelReg();
    }else{
	updateLagerstalleReg();
    }
}

void frmChgArtikel::updateArtikelReg()
{
/************************************************************************/
/*	Uppdatera databasen med förändrade data på artikeln.			*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);

	process = new QProcess();
	process->addArgument( "./STYRMAN");	// OLFIX funktion
	process->addArgument(usr);
	process->addArgument("ARCHG");
	process->addArgument(artikeldata);
	frmChgArtikel::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmChgArtikel::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
            frmChgArtikel::connect( process, SIGNAL(processExited() ),this, SLOT(slotARUpdateEndOfProcess() ) );

	if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta CHGARW!\n");
		QMessageBox::warning( this, "",
                            "Kan inte starta ARCHG! \n" );
	}
}

void frmChgArtikel::slotARUpdateEndOfProcess()
{
    int i;
//    qDebug("slotUpdateEndOfProcess= %s  %s",errorrad.latin1(),inrad.latin1());
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "CHGARW, Grunddata ","ERROR!\n"+errorrad);
	errorrad="";
    }
    i = -1;
    i = inrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "CHGARW, Grunddata ","ERROR!\n"+inrad);
    }
 /*
    i = -1;
     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	QMessageBox::information( this, "CHGARW",
		"Uppdatering OK!\n"+errorrad
	);
    }
*/	
	artikeldata="";
	lineEditArtikelNr->clear();
	lineEditBenamning1->clear();
	lineEditBenamning2->clear();
	lineEditEnhet->clear();
	lineEditNettovikt->clear();
	lineEditVolym->clear();
	lineEditFpris->clear();
	lineEditLedtid->clear();
	lineEditProdklass->clear();
	lineEditProdkonto->clear();
	lineEditArtikeltyp->clear();
	lineEditStruktur->clear();
	lineEditTulltaxenr->clear();
	lineEditLev1->clear();
	lineEditLev2->clear();
	lineEditLev3->clear();
	lineEditUrBenamning->clear();
	lineEditUrsprungsland->clear();
	lineEditUrArtikelnr->clear();
    
     errorrad="";
     inrad="";
     if (changeflag==0){
	 frmChgArtikel::updateLagerstalleReg();
     }
     changeflagG=-1;
}

void frmChgArtikel::updateLagerstalleReg()
{
/************************************************************************/
/*	Uppdatera LAGERSTELLEREG med nya data på artikeln.		*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);
            QString flag;
	    if (changeflag == 0){			// Har någon ekonomisk förändring gjorts
		flag="0";
	    }else{
		flag="-1";
	    }
	    
	process = new QProcess();
	process->addArgument( "./STYRMAN");	// OLFIX funktion
	process->addArgument(usr);
	process->addArgument("ARCHGL");
	process->addArgument(lagerdata);
/*						// Data för TRHD (logga data som ger ekonomisk påverkan)
                                                                                                // om changeflag = 0 så anropar ARCHGL funktionen TRHDADD
*/	
	process->addArgument(usr);		// vem som gjort ändringen (för TRHDADD)
	process->addArgument(flag);		// om en ekonomisk transaktion gjorts (för ARCHGL)
	process->addArgument("CHGARW");	// i vilket program transaktionen gjorts (för TRHDADD)
	frmChgArtikel::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmChgArtikel::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
            frmChgArtikel::connect( process, SIGNAL(processExited() ),this, SLOT(slotLSUpdateEndOfProcess() ) );

	if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta CHGARW!\n");
		QMessageBox::warning( this, "",
                            "Kan inte starta ARCHGL! \n" );
	}
}

void frmChgArtikel::slotLSUpdateEndOfProcess()
{
    int i;
//    qDebug("slotUpdateEndOfProcess= %s  %s",errorrad.latin1(),inrad.latin1());
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "CHGARW, Lagerplatsdata ","ERROR!\n"+errorrad);
	errorrad="";
    }
    i = -1;
    i = inrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "CHGARW, Lagerplats ","ERROR!\n"+inrad);
    }

     i = -1;
     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	QMessageBox::information( this, "CHGARW",
		"Uppdatering OK!\n"+errorrad
	);
	lagerdata="";
	lineEditLagerplats_2->setText("1");
	lineEditLagerhylla_2->clear();
	lineEditLagersaldo_2->clear();
	lineEditInvGrp_2->clear();
	lineEditABCkod_2->clear();
	lineEditValuta_2->clear();
	lineEditOmkostnad_2->clear();
	lineEditSenInkopsPris_2->clear();
	lineEditKalkylPris->clear();
	lineEditSenInkopsKvantitet_2->clear();
	lineEditPlanKalkylPris->clear();
	lineEditNestSenInkopsKvantitet_2->clear();
	lineEditFrystKalkylPris->clear();
	lineEditNestNestSenInkopsKvantitet_2->clear();
	lineEditBestKvantitet_2->clear();
	lineEditBestPunkt_2->clear();
// ========================================
	artikeldata="";
	lineEditArtikelNr->clear();
	lineEditBenamning1->clear();
	lineEditBenamning2->clear();
	lineEditEnhet->clear();
	lineEditOmrFaktor->clear();
	lineEditNettovikt->clear();
	lineEditVolym->clear();
	lineEditFpris->clear();
	lineEditLedtid->clear();
	lineEditProdklass->clear();
	lineEditProdkonto->clear();
	lineEditArtikeltyp->clear();
	lineEditStruktur->clear();
	lineEditTulltaxenr->clear();
	lineEditLev1->clear();
	lineEditLev2->clear();
	lineEditLev3->clear();
	lineEditUrBenamning->clear();
	lineEditUrsprungsland->clear();
	lineEditUrArtikelnr->clear();   
    }
     errorrad="";
     inrad="";
     lineEditArtikelNr->setFocus();
     changeflag=-1;
}

void frmChgArtikel::CheckArtikelNr()
{
/************************************************************************/
/*	Kontrollera om artikelnr redan finns					*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);

	process = new QProcess();
	process->addArgument( "./STYRMAN");	// OLFIX funktion
	process->addArgument(usr);
	process->addArgument("ARCHK");
	process->addArgument(artikelnr);
	frmChgArtikel::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmChgArtikel::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
            frmChgArtikel::connect( process, SIGNAL(processExited() ),this, SLOT(slotCheckEndOfProcess() ) );

	if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta CHGARW!\n");
		QMessageBox::warning( this, "",
                            "Kan inte starta CHGARW/ARCHK! \n" );
	}
}

void frmChgArtikel::slotCheckEndOfProcess()
{
    int i,j;
//    qDebug("checkstart: %s  %s",errorrad.latin1(),inrad.latin1());
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	// Artikelnummer finns ej, kan användas!
	lineEditBenamning1->setFocus();
	errorrad="";
    }else{
	j = -1;
	j = inrad.find(QRegExp("STYRMAN"),0);
	if (j != -1){
	    QMessageBox::warning( this, "CHGARW",inrad);
	    lineEditArtikelNr->setFocus();
	}else{
	    i = -1;
	    i = inrad.find( QRegExp("OK:"), 0 );
	    if (i != -1) {
		QMessageBox::warning( this, "CHGARW","Artikelnummer finns redan\n"+errorrad);
		lineEditArtikelNr->setFocus();
		lineEditArtikelNr->selectAll();
	    }
	}
    }
    inrad="";
    errorrad="";
}

void frmChgArtikel::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmChgArtikel::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmChgArtikel::lineEditLagerplats_2_returnPressed()
{
    lagerplats=lineEditLagerplats_2->text();
    if (lagerplats==""){
	lagerplats="1";
	lineEditLagerplats_2->setText(lagerplats);
    }
    lineEditLagerhylla_2->setFocus();
}

void frmChgArtikel::lineEditLagerhylla_2_returnPressed()
{
    lagerhylla=lineEditLagerhylla_2->text();
    if (lagerhylla==""){
	lagerhylla=" ";
    }
    lineEditLagersaldo_2->setFocus();
}

void frmChgArtikel::lineEditLagersaldo_2_returnPressed()
{
    int i;
    if (lineEditLagersaldo_2->text() != lagersaldo){
	    changeflag=0;
    }
//    qDebug("changeflag=%d",changeflag);
    lagersaldo=lineEditLagersaldo_2->text();
    if (lagersaldo==""){
	lagersaldo="0.00";
	lineEditLagersaldo_2->setText(lagersaldo);
    }
    i = -1;
    i = lagersaldo.find( QRegExp(","), 0 );
    if (i != -1){
	 lagersaldo.replace( QChar(','), "." );
	 lineEditLagersaldo_2->setText(lagersaldo);
     }
    lineEditInvGrp_2->setFocus();
}

void frmChgArtikel::lineEditInvGrp_2_returnPressed()
{
    invgrupp=lineEditInvGrp_2->text();
    if (invgrupp==""){
	invgrupp=" ";
    }
    lineEditABCkod_2->setFocus();
}

void frmChgArtikel::lineEditABCkod_2_returnPressed()
{
    abckod=lineEditABCkod_2->text();
    if (abckod==""){
	abckod=" ";
    }
    lineEditValuta_2->setFocus();
}

void frmChgArtikel::lineEditValuta_2_returnPressed()
{
    valuta=lineEditValuta_2->text();
    if (valuta==""){
	valuta="SEK";
	lineEditValuta_2->setText(valuta);
    }
    lineEditOmkostnad_2->setFocus();
}

void frmChgArtikel::lineEditOmkostnad_2_returnPressed()
{
    int i;
    if (lineEditOmkostnad_2->text() != omkost){
	changeflag=0;
    }
    omkost=lineEditOmkostnad_2->text();
    if(omkost==""){
	omkost="0.00";
	lineEditOmkostnad_2->setText(omkost);
    }
   i = -1;
    i = omkost.find( QRegExp(","), 0 );
    if (i != -1){
	 omkost.replace( QChar(','), "." );
	 lineEditOmkostnad_2->setText(omkost);
     }    
    lineEditSenInkopsPris_2->setFocus();
}

void frmChgArtikel::lineEditSenInkopsPris_2_returnPressed()
{
    int i;
    if (lineEditSenInkopsPris_2->text() != seninkpris){
	changeflag=0;
    }
    seninkpris=lineEditSenInkopsPris_2->text();
    if (seninkpris==""){
	seninkpris="0.00";
	lineEditSenInkopsPris_2->setText(seninkpris);
    }
    i = -1;
    i = seninkpris.find( QRegExp(","), 0 );
    if (i != -1){
	 seninkpris.replace( QChar(','), "." );
	 lineEditSenInkopsPris_2->setText(seninkpris);
     }
    lineEditKalkylPris->setFocus();
}

void frmChgArtikel::lineEditSenKalkylPris_2_returnPressed()
{
    int i;
    if (lineEditKalkylPris->text() != kalkylpris){
	changeflag=0;
    }
    kalkylpris=lineEditKalkylPris->text();
    if (kalkylpris==""){
	kalkylpris="0.00";
	lineEditKalkylPris->setText(kalkylpris);
    }
    i = -1;
    i = kalkylpris.find( QRegExp(","), 0 );
    if (i != -1){
	 kalkylpris.replace( QChar(','), "." );
	 lineEditKalkylPris->setText(kalkylpris);
     }
    lineEditSenInkopsKvantitet_2->setFocus();
}

void frmChgArtikel::lineEditSenInkopsKvantitet_2_returnPressed()
{
    int i;
    if (lineEditSenInkopsKvantitet_2->text() != ikvant0){
	changeflag=0;
    }
    ikvant0=lineEditSenInkopsKvantitet_2->text();
    if (ikvant0==""){
	ikvant0="0.00";
	lineEditSenInkopsKvantitet_2->setText(ikvant0);
    }
    i = -1;
    i = ikvant0.find( QRegExp(","), 0 );
    if (i != -1){
	 ikvant0.replace( QChar(','), "." );
	 lineEditSenInkopsKvantitet_2->setText(ikvant0);
     }
    lineEditPlanKalkylPris->setFocus();
}

void frmChgArtikel::lineEditPlanKalkylPris_returnPressed()
{
    int i;
    if (lineEditPlanKalkylPris->text() != plankpris){
	changeflag=0;
    }
    plankpris=lineEditPlanKalkylPris->text();
    if (plankpris==""){
	plankpris="0.00";
	lineEditPlanKalkylPris->setText(plankpris);
    }
    i = -1;
    i = plankpris.find( QRegExp(","), 0 );
    if (i != -1){
	 plankpris.replace( QChar(','), "." );
	 lineEditPlanKalkylPris->setText(plankpris);
     }
    lineEditNestSenInkopsKvantitet_2->setFocus();
}

void frmChgArtikel::lineEditNestSenInkopsKvantitet_2_returnPressed()
{
    int i;
    if (lineEditNestSenInkopsKvantitet_2->text() != ikvant1){
	changeflag=0;
    }
    ikvant1=lineEditNestSenInkopsKvantitet_2->text();
    if (ikvant1==""){
	ikvant1="0.00";
	lineEditNestSenInkopsKvantitet_2->setText(ikvant1);
    }
    i = -1;
    i = ikvant1.find( QRegExp(","), 0 );
    if (i != -1){
	 ikvant1.replace( QChar(','), "." );
	 lineEditNestSenInkopsKvantitet_2->setText(ikvant1);
     }
    lineEditFrystKalkylPris->setFocus();
}

void frmChgArtikel::lineEditFrystKalkylPris_returnPressed()
{
    int i;
    if (lineEditFrystKalkylPris->text() != frystkpris){
	changeflag=0;
    }
    frystkpris=lineEditKalkylPris->text();
    if (frystkpris==""){
	frystkpris="0.00";
	lineEditFrystKalkylPris->setText(frystkpris);
    }
    i = -1;
    i = frystkpris.find( QRegExp(","), 0 );
    if (i != -1){
	 frystkpris.replace( QChar(','), "." );
	 lineEditFrystKalkylPris->setText(frystkpris);
     }
    lineEditNestNestSenInkopsKvantitet_2->setFocus();
}

void frmChgArtikel::lineEditNestNestSenInkopsKvantitet_2_returnPressed()
{
    int i;
    if (lineEditNestNestSenInkopsKvantitet_2->text() != ikvant1){
	changeflag=0;
    }
    ikvant2=lineEditNestNestSenInkopsKvantitet_2->text();
    if (ikvant2==""){
	ikvant2="0.00";
	lineEditNestNestSenInkopsKvantitet_2->setText(ikvant2);
    }
    i = -1;
    i = ikvant2.find( QRegExp(","), 0 );
    if (i != -1){
	 ikvant2.replace( QChar(','), "." );
	 lineEditNestNestSenInkopsKvantitet_2->setText(ikvant2);
     }
    lineEditBestKvantitet_2->setFocus();
}

void frmChgArtikel::lineEditBestKvantitet_2_returnPressed()
{
    int i;
    bestkvant=lineEditBestKvantitet_2->text();
    if (bestkvant==""){
	bestkvant="0";
	lineEditBestKvantitet_2->setText(bestkvant);
    }
    i = -1;
    i = bestkvant.find( QRegExp(","), 0 );
    if (i != -1){
	 bestkvant.replace( QChar(','), "." );
	 lineEditBestKvantitet_2->setText(bestkvant);
     }    
    lineEditBestPunkt_2->setFocus();
}
void frmChgArtikel::lineEditBestPunkt_2_returnPressed()
{
    int i;
    bestpunkt=lineEditBestPunkt_2->text();
    if (bestpunkt==""){
	bestpunkt="0";
	lineEditBestPunkt_2->setText(bestpunkt);
    }
    i = -1;
    i = bestpunkt.find( QRegExp(","), 0 );
    if (i != -1){
	 bestpunkt.replace( QChar(','), "." );
	 lineEditBestPunkt_2->setText(bestpunkt);
     }
    
    pushButtonOK->setFocus();
}

void frmChgArtikel::getGrunddata()
{
/************************************************************************/
/*	Hämta grunddata från databasen 					*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);

//            qDebug("Anropa ARDSP, artikelnr=%s",artikelnr.latin1());
	process = new QProcess();
	process->addArgument( "./STYRMAN");	// OLFIX funktion
	process->addArgument(usr);
	process->addArgument("ARDSP");
	process->addArgument(artikelnr);
	frmChgArtikel::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmChgArtikel::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
            frmChgArtikel::connect( process, SIGNAL(processExited() ),this, SLOT(slotGetGrDataEndOfProcess() ) );

	if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta CHGARW!\n");
		QMessageBox::warning( this, "",
                            "Kan inte starta ARDSP! \n" );
	}
}

void frmChgArtikel::slotGetGrDataEndOfProcess()
{
    int i,m;

    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
 //   qDebug("Error:",errorrad);
         if (i != -1) {
	QMessageBox::critical( this, "DSPARW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
     }
     i = -1;

//    qDebug("inrad=%s",inrad.latin1());

    i = inrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "DSPARW",
		"ERROR!\n"+inrad
	);
	inrad="";
	i = -1;
    }else{
	i = -1;

	i = inrad.find( QRegExp("OK:"), 0 );
	if (i != -1) {
	    int i1 = inrad.find( QRegExp("01:"), 0 );	//	artikelnr
	    int i2 = inrad.find( QRegExp("02:"), 0 );	//	benamn1		Artikelbenämning 1
	    int i3 = inrad.find( QRegExp("03:"), 0 );	//	benamn2		Artikelbenämning 2
	    int i4 = inrad.find( QRegExp("04:"), 0 );	//	enhet
	    int i5 = inrad.find( QRegExp("05:"), 0 );	//	fpris		Försäljningspris
	    int i6 = inrad.find( QRegExp("06:"), 0 );	//	ledtid
	    int i7 = inrad.find( QRegExp("07:"), 0 );	//	prodklass 	Produktklass
	    int i8 = inrad.find( QRegExp("08:"), 0 );	//	prodkto 		Produktkonto
	    int i9 = inrad.find( QRegExp("09:"), 0 );	//	lev1 		Leverantör nr 1
	    int i10 = inrad.find( QRegExp("10:"), 0 );	//	lev2 		Leverantör nr 2
	    int i11 = inrad.find( QRegExp("11:"), 0 );	//	lev3 		Leverantör nr 3
	    int i12 = inrad.find( QRegExp("12:"), 0 );	//	nettovikt
	    int i13 = inrad.find( QRegExp("13:"), 0 );	//	artikeltyp
	    int i14 = inrad.find( QRegExp("14:"), 0 );	//	struktur
	    int i15 = inrad.find( QRegExp("15:"), 0 );	//	urbenamn 	Ursprungsbenämning
	    int i16 = inrad.find( QRegExp("16:"), 0 );	// 	urland 		Ursprungsland
	    int i17 = inrad.find( QRegExp("17:"), 0 );	//	levartnr 		Leverantörens artikelnr
	    int i18 = inrad.find( QRegExp("18:"), 0 );	//	tulltaxenr 	Tulltaxekod
	    int i19 = inrad.find( QRegExp("19:"), 0 );	//	volym
	    int i20 = inrad.find( QRegExp("20:"), 0 );	//	omrfaktor 	Omräkningsfaktor
	    int i21 = inrad.length();

//	    qDebug("inrad=%s",inrad.latin1());

	    m=i2-i1;
	    if (i1 != -1){
	     artikelnr=inrad.mid(i1+3,m-5);
	     lineEditArtikelNr->setText(artikelnr);
	 }

 	 m=i3-i2;
	 if (i2 != -1){
	     benamn1=inrad.mid(i2+3,m-5);
	     lineEditBenamning1->setText(benamn1);
	 }

 	 m=i4-i3;
	 if (i3 != -1){
	     benamn2=inrad.mid(i3+3,m-5);
	     lineEditBenamning2->setText(benamn2);
	 }

 	 m=i5-i4;
	 if (i4 != -1){
	     enhet=inrad.mid(i4+3,m-5);
	     lineEditEnhet->setText(enhet);
	 }

  	 m=i6-i5;
	 if (i5 != -1){
	     fpris=inrad.mid(i5+3,m-5);
	     lineEditFpris->setText(fpris);	
	 }

 	 m=i7-i6;
	 if (i6 != -1){
	     ledtid=inrad.mid(i6+3,m-5);
	     lineEditLedtid->setText(ledtid);
	 }

 	 m=i8-i7;
	 if (i7 != -1){
	     prodklass=inrad.mid(i7+3,m-5);
	     lineEditProdklass->setText(prodklass);	
	 }

 	 m=i9-i8;
	 if (i8 != -1){
	     prodkto=inrad.mid(i8+3,m-5);
	     lineEditProdkonto->setText(prodkto);
	 }

 	 m=i10-i9;
	 if (i9 != -1){
	     lev1=inrad.mid(i9+3,m-5);
	     lineEditLev1->setText(lev1);
	 }

 	 m=i11-i10;
	 if (i10 != -1){
	     lev2=inrad.mid(i10+3,m-5);
	     lineEditLev2->setText(lev2);
	 }

	 m=i12-i11;
	 if (i11 != -1){
	     lev3=inrad.mid(i11+3,m-5);
	     lineEditLev3->setText(lev3);
	 }

	 m=i13-i12;
	 if (i12 != -1){
	     nettovikt=inrad.mid(i12+3,m-5);
	     lineEditNettovikt->setText(nettovikt);
	 }

	 m=i14-i13;
	 if (i13 != -1){
	     artikeltyp=inrad.mid(i13+3,m-5);
	     lineEditArtikeltyp->setText(artikeltyp);
	 }

	 m=i15-i14;
	 if (i14 != -1){
	     struktur=inrad.mid(i14+3,m-5);
//	     lineEditStruktur->setText(struktur);	// Visas inte i detta program
	 }

	 m=i16-i15;
	 if (i15 != -1){
	     urbenamn=inrad.mid(i15+3,m-5);
	     lineEditUrBenamning->setText(urbenamn);
	 }

	 m=i17-i16;
	 if (i16 != -1){
	     urland=inrad.mid(i16+3,m-5);
	     lineEditUrsprungsland->setText(urland);
	 }

	 m=i18-i17;
	 if (i17 != -1){
	     levartnr =inrad.mid(i17+3,m-5);
	     lineEditUrArtikelnr->setText(levartnr );
	 }

	 m=i19-i18;
	 if (i18 != -1){
	     tulltaxenr=inrad.mid(i18+3,m-5);
	     lineEditTulltaxenr->setText(tulltaxenr);	
	 }

	 m=i20-i19;
	 if (i19 != -1){
	     volym=inrad.mid(i19+3,m-5);
	     lineEditVolym->setText(volym);	
	 }

	 m=i21-i20;
	 if (i20 != -1){
	     omrfaktor =inrad.mid(i20+3,m-9);
	     lineEditOmrFaktor->setText(omrfaktor );
	 }

	 inrad="";
	errorrad="";
	inrad="";
	i = -1;
     }

    // ========================
   frmChgArtikel::getLagerdata();
    }
}


void frmChgArtikel::getLagerdata()
{
/************************************************************************/
/*	Hämta lagerdata från databasen 	.				*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);


	process = new QProcess();
	process->addArgument( "./STYRMAN");	// OLFIX funktion
	process->addArgument(usr);
	process->addArgument("ARDSPL");
	process->addArgument(lagerplats);
	process->addArgument(artikelnr);
	frmChgArtikel::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmChgArtikel::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
            frmChgArtikel::connect( process, SIGNAL(processExited() ),this, SLOT(slotgetLaDataEndOfProcess() ) );

	if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta CHGARW!\n");
		QMessageBox::warning( this, "",
                            "Kan inte starta ARDSPL! \n" );
	}
}

void  frmChgArtikel::slotgetLaDataEndOfProcess()
{
    int i,m;

    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
 //   qDebug("Error:",errorrad);
         if (i != -1) {
	QMessageBox::critical( this, "CHGARW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
     }
     i = -1;

//    qDebug("inrad=%s",inrad.latin1());

    i = inrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "DSPAREW",
		"ERROR!\n"+inrad
	);
	inrad="";
	i = -1;
    }else{
	i = -1;

	i = inrad.find( QRegExp("OK:"), 0 );
	if (i != -1) {
	    int i1 = inrad.find( QRegExp("01:"), 0 );	//	lagerplats
	    int i2 = inrad.find( QRegExp("02:"), 0 );	//	artikelnr
	    int i3 = inrad.find( QRegExp("03:"), 0 );	//	lagerhylla
	    int i4 = inrad.find( QRegExp("04:"), 0 );	//	lagersaldo
	    int i5 = inrad.find( QRegExp("05:"), 0 );	//	invgrupp		Inventeringsgrupp
	    int i6 = inrad.find( QRegExp("06:"), 0 );	//	abckod		ABC-kod
	    int i7 = inrad.find( QRegExp("07:"), 0 );	//	valuta
	    int i8 = inrad.find( QRegExp("08:"), 0 );	//	seninkpris	Senaste inköpspris
	    int i9 = inrad.find( QRegExp("09:"), 0 );	//	ikvant0		Senaste inköpskvvantitet
	    int i10 = inrad.find( QRegExp("10:"), 0 );	//	ikvant1		Näst senaste inköpskvvantitet
	    int i11 = inrad.find( QRegExp("11:"), 0 );	//	ikvant2		Näst näst senaste inköpskvvantitet
	    int i12 = inrad.find( QRegExp("12:"), 0 );	//	kalkylpris	Gällande kalkylpris
	    int i13 = inrad.find( QRegExp("13:"), 0 );	//	plankpris		Planerat kalkylpris
	    int i14 = inrad.find( QRegExp("14:"), 0 );	//	frystkpris	Fryst kalkylpris
	    int i15 = inrad.find( QRegExp("15:"), 0 );	//	bestkvant	Beställd kvantitet
	    int i16 = inrad.find( QRegExp("16:"), 0 );	//	bestpunkt	Beställningspunkt
	    int i17 = inrad.find( QRegExp("17:"), 0 );	//	omkost		Omkostnader
	    int i18 = inrad.length();

	    m=i2-i1;
	    if (i1 != -1){
		lagerplats=inrad.mid(i1+3,m-5);
		lineEditLagerplats_2->setText(lagerplats);
	    }

	    m=i3-i2;
	    if (i2 != -1){
//	    	 artikelnr=inrad.mid(i2+3,m-5);
//	     	lineEditArtikelNr->setText(artikelnr);	// redan hämtat
	    }

	    m=i4-i3;
	    if (i3 != -1){
		lagerhylla=inrad.mid(i3+3,m-5);
		lineEditLagerhylla_2->setText(lagerhylla);	
	    }

	    m=i5-i4;
	    if (i4 != -1){
		lagersaldo=inrad.mid(i4+3,m-5);
		lineEditLagersaldo_2->setText(lagersaldo);
	    }

	    m=i6-i5;
	    if (i5 != -1){
		invgrupp=inrad.mid(i5+3,m-5);
		lineEditInvGrp_2->setText(invgrupp);	
	    }

	    m=i7-i6;
	    if (i6 != -1){
		abckod=inrad.mid(i6+3,m-5);
		lineEditABCkod_2->setText(abckod);
	    }

	    m=i8-i7;
	    if (i7 != -1){
		valuta=inrad.mid(i7+3,m-5);
		lineEditValuta_2->setText(valuta);	
	    }

	    m=i9-i8;
	    if (i8 != -1){
		seninkpris=inrad.mid(i8+3,m-5);
		lineEditSenInkopsPris_2->setText(seninkpris);
	    }

	    m=i10-i9;
	    if (i9 != -1){
		ikvant0=inrad.mid(i9+3,m-5);
		lineEditSenInkopsKvantitet_2->setText(ikvant0);
	    }

	    m=i11-i10;
	    if (i10 != -1){
		ikvant1=inrad.mid(i10+3,m-5);
		lineEditNestSenInkopsKvantitet_2->setText(ikvant1);
	    }

	    m=i12-i11;
	    if (i11 != -1){
		ikvant2=inrad.mid(i11+3,m-5);
		lineEditNestNestSenInkopsKvantitet_2->setText(ikvant2);
	    }

	    m=i13-i12;
	    if (i12 != -1){
		kalkylpris=inrad.mid(i12+3,m-5);
		lineEditKalkylPris->setText(kalkylpris);
	    }

	    m=i14-i13;
	    if (i13 != -1){
		plankpris=inrad.mid(i13+3,m-5);
		lineEditPlanKalkylPris->setText(plankpris);
	    }

	    m=i15-i14;
	    if (i14 != -1){
		frystkpris=inrad.mid(i14+3,m-5);
		lineEditFrystKalkylPris->setText(frystkpris);
	    }

	    m=i16-i15;
	    if (i15 != -1){
		bestkvant=inrad.mid(i15+3,m-5);
		lineEditBestKvantitet_2->setText(bestkvant);
	    }

	    m=i17-i16;
	    if (i16 != -1){
		bestpunkt=inrad.mid(i16+3,m-5);
		lineEditBestPunkt_2->setText(bestpunkt);
	    }

	    m=i18-i17;
	    if (i17 != -1){
		omkost=inrad.mid(i17+3,m-9);
		lineEditOmkostnad_2->setText(omkost);
	    }

	inrad="";
	errorrad="";
	inrad="";
	i = -1;
          }
    }
}
