/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
/***************************************************************************
                          ADDARW  -  description
                             -------------------
		     version 0.4
    begin                	: Tis 28 okt    2003
    modified	: Sön 24 april 2005
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
#include <qvalidator.h> 
#define MAXSTRING 5000


    QProcess* process;
    QString inrad;
    QString errorrad;
    QString hjelpfil;

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
    QString bestkvant="0.00";
    QString bestpunkt="0.00";
    QString lagerdata;		// Summan av lagerplatsdata

    
    QRegExp rx1( "[A-Za-z0-9ÅÄÖåäö-]{1,29}" );
    QRegExp rx2( "[0-9]{0,3}" );
    QRegExp rx3( "[A-Za-z0-9ÅÄÖåäö/_ - ]{0,29}" );
    QRegExp rx4( "[0-9,.]{1,6}" );
    QRegExp rx5( "\\w{0,5}" );
    QRegExp rx6( "[0-9,.]{0,12}" );
    QRegExp rx7( "[A-Za-z0-9ÅÄÖåäö]{0,10}" );
    QRegExp rx8( "[0-4]{1}" );
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
    
void frmAddArtikel::init()
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
    lineEditUrArtikelnr->setValidator(&validator3);
    
    lineEditArtikelNr->setFocus();
}


void frmAddArtikel::lineEditArtikelNr_returnPressed()
{
    artikelnr=lineEditArtikelNr->text();
    CheckArtikelNr();			// Kontrollera om artikelnummer redan finns eller ej.
    lineEditBenamning1->setFocus();
}

void frmAddArtikel::lineEditBenamning1_returnPressed()
{
    benamn1=lineEditBenamning1->text();
    lineEditBenamning2->setFocus();
}

void frmAddArtikel::lineEditBenamning2_returnPressed()
{
    benamn2=lineEditBenamning2->text();
    if (benamn2==""){
	benamn2=" ";
    }
    lineEditEnhet->setFocus();
}

void frmAddArtikel::lineEditEnhet_returnPressed()
{
    enhet=lineEditEnhet->text();
    if (enhet==""){
	enhet="ST";
	lineEditEnhet->setText(enhet);
    }
    lineEditOmrFaktor->setFocus();
}

void frmAddArtikel::lineEditOmrFaktor_returnPressed()
{
    omrfaktor=lineEditOmrFaktor->text();
    if (omrfaktor==""){
	omrfaktor="1";
	lineEditOmrFaktor->setText(omrfaktor);
    }
    lineEditFpris->setFocus();
}

void frmAddArtikel::lineEditFpris_returnPressed()
{
    int i;
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

void frmAddArtikel::lineEditNettovikt_returnPressed()
{
    int i;
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

void frmAddArtikel::lineEditVolym_returnPressed()
{
    int i;
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

void frmAddArtikel::lineEditLedtid_returnPressed()
{
    ledtid=lineEditLedtid->text();
    if (ledtid==""){
	ledtid="0";
	lineEditLedtid->setText(ledtid);
    }
    lineEditProdklass->setFocus();
}

void frmAddArtikel::lineEditProdklass_returnPressed()
{
    prodklass=lineEditProdklass->text();
    if (prodklass==""){
	prodklass=" ";
    }
    lineEditProdkonto->setFocus();
}

void frmAddArtikel::lineEditProdkonto_returnPressed()
{
    prodkto=lineEditProdkonto->text();
    if (prodkto==""){
	prodkto=" ";
    }
    lineEditArtikeltyp->setFocus();
}

void frmAddArtikel::lineEditArtikeltyp_returnPressed()
{
    artikeltyp=lineEditArtikeltyp->text();
    if (artikeltyp==""){
	artikeltyp="2";
	lineEditArtikeltyp->setText(artikeltyp);
    }
    lineEditStruktur->setFocus();
}

void frmAddArtikel::lineEditStruktur_returnPressed()
{
    struktur=lineEditStruktur->text();
    if (struktur==""){
	struktur=" ";
    }
    lineEditTulltaxenr->setFocus();
}

void frmAddArtikel::lineEditTulltaxenr_returnPressed()
{
    tulltaxenr=lineEditTulltaxenr->text();
    if (tulltaxenr==""){
	tulltaxenr=" ";
    }
    lineEditLev1->setFocus();
}

void frmAddArtikel::lineEditLev1_returnPressed()
{
    lev1=lineEditLev1->text();
    if (lev1==""){
	lev1=" ";
    }
    lineEditLev2->setFocus();
}

void frmAddArtikel::lineEditLev2_returnPressed()
{
    lev2=lineEditLev2->text();    
    if (lev2==""){
	lev2=" ";
    }
    lineEditLev3->setFocus();
}

void frmAddArtikel::lineEditLev3_returnPressed()
{
    lev3=lineEditLev3->text();    
    if (lev3==""){
	lev3=" ";
    }
    lineEditUrBenamning->setFocus();
}

void frmAddArtikel::lineEditUrBenamning_returnPressed()
{
    urbenamn=lineEditUrBenamning->text();
    if (urbenamn==""){
	urbenamn=" ";
    }
    lineEditUrsprungsland->setFocus();
}

void frmAddArtikel::lineEditUrsprungsland_returnPressed()
{
    urland=lineEditUrsprungsland->text();
    if (urland==""){
	urland=" ";
    }
    lineEditUrArtikelnr->setFocus();
}


void frmAddArtikel::lineEditUrArtikelnr_returnPressed()
{
    levartnr=lineEditUrArtikelnr->text();
    if (levartnr==""){
	levartnr=" ";
    }
//    pushButtonOK->setFocus();			//  OBS! OBS!
    lineEditLagerplats_2->setFocus();
}

void frmAddArtikel::pushBtnHelp_clicked()
{
	inrad="";
	frmAddArtikel::readResursFil();		// Hämta path till hjälpfilen

	int i1 = hjelpfil.find( QRegExp(".html"), 0 );
//	int i2 = hjelpfil.length();
	hjelpfil=hjelpfil.left(i1);
	hjelpfil=hjelpfil+"_ARTIKLAR.html";
	hjelpfil=hjelpfil+"#ARTIKEL01";		// Lägg till position
//	qDebug("hjelpfil=%s",hjelpfil.latin1());

	process = new QProcess();
	process->addArgument( "OLFIXHLP" );	// OLFIX program
	process->addArgument(hjelpfil);

	if ( !process->start() ) {
	    // error handling
	    QMessageBox::warning( this, "OLFIX","Kan inte starta OLFIXHLP!\n" );
	}
	lineEditArtikelNr->setFocus();

}
void frmAddArtikel::pushButtonOK_clicked()
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

    qDebug("artikeldata=%s",artikeldata.latin1());
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
    lagerdata.append(bestkvant);
    lagerdata.append(skilj);    
    lagerdata.append(bestpunkt);
    lagerdata.append(skilj);

    updateArtikelReg();
}


void frmAddArtikel::updateArtikelReg()
{
/************************************************************************/
/*	Uppdatera databasen med den nya artikeln.				*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);

	process = new QProcess();
	process->addArgument( "./STYRMAN");	// OLFIX funktion
	process->addArgument(usr);
	process->addArgument("ARADD");
	process->addArgument(artikeldata);
	frmAddArtikel::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmAddArtikel::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
            frmAddArtikel::connect( process, SIGNAL(processExited() ),this, SLOT(slotARUpdateEndOfProcess() ) );

	if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta ADDARW!\n");
		QMessageBox::warning( this, "",
                            "Kan inte starta ARADD! \n" );
	}
}

void frmAddArtikel::slotARUpdateEndOfProcess()
{
    int i;
//    qDebug("slotUpdateEndOfProcess= %s  %s",errorrad.latin1(),inrad.latin1());
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "ADDARW, Grunddata ","ERROR!\n"+errorrad);
	errorrad="";
    }
    i = -1;
    i = inrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "ADDARW, Grunddata ","ERROR!\n"+inrad);
    }
 /*
    i = -1;
     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	QMessageBox::information( this, "ADDARW",
		"Uppdatering OK!\n"+errorrad
	);
    }
*/	
	artikeldata="";
	lineEditArtikelNr->clear();
	lineEditBenamning1->clear();
	lineEditBenamning2->clear();
	lineEditEnhet->setText("ST");
	lineEditNettovikt->clear();
	lineEditVolym->clear();
	lineEditFpris->clear();
	lineEditLedtid->clear();
	lineEditProdklass->clear();
	lineEditProdkonto->clear();
	lineEditArtikeltyp->setText("0");
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
     frmAddArtikel::updateLagerstalleReg();
//     lineEditArtikelNr->setFocus();
}

void frmAddArtikel::updateLagerstalleReg()
{
/************************************************************************/
/*	Uppdatera databasen med den nya artikeln.				*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);

	process = new QProcess();
	process->addArgument( "./STYRMAN");	// OLFIX funktion
	process->addArgument(usr);
	process->addArgument("AR2ADD");
	process->addArgument(lagerdata);
	frmAddArtikel::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmAddArtikel::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
            frmAddArtikel::connect( process, SIGNAL(processExited() ),this, SLOT(slotLSUpdateEndOfProcess() ) );

	if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta ADDARW!\n");
		QMessageBox::warning( this, "",
                            "Kan inte starta AR2ADD! \n" );
	}
}

void frmAddArtikel::slotLSUpdateEndOfProcess()
{
    int i;
//    qDebug("slotUpdateEndOfProcess= %s  %s",errorrad.latin1(),inrad.latin1());
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "ADDARW, Lagerplatsdata ","ERROR!\n"+errorrad);
	errorrad="";
    }
    i = -1;
    i = inrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "ADDARW, Lagerplats ","ERROR!\n"+inrad);
    }

     i = -1;
     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	QMessageBox::information( this, "ADDARW",
		"Uppdatering OK!\n"+errorrad
	);
	lagerdata="";
	lineEditLagerplats_2->setText("1");
	lineEditLagerhylla_2->clear();
	lineEditBenamning2->clear();
	lineEditLagersaldo_2->setText("0");
	lineEditInvGrp_2->clear();
	lineEditABCkod_2->clear();
	lineEditValuta_2->setText("SEK");
	lineEditSenInkopsPris_2->setText("0.00");
	lineEditSenKalkylPris_2->setText("0.00");
	lineEditBestPunkt_2->setText("0.00");
	lineEditArtikeltyp->setText("0");
    }
     errorrad="";
     inrad="";
     lineEditArtikelNr->setFocus();
}

void frmAddArtikel::CheckArtikelNr()
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
	frmAddArtikel::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmAddArtikel::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
            frmAddArtikel::connect( process, SIGNAL(processExited() ),this, SLOT(slotCheckEndOfProcess() ) );

	if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta ADDARW!\n");
		QMessageBox::warning( this, "",
                            "Kan inte starta ADDARW/ARCHK! \n" );
	}
}

void frmAddArtikel::slotCheckEndOfProcess()
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
	    QMessageBox::warning( this, "ADDARW",inrad);
	    lineEditArtikelNr->setFocus();
	}else{
	    i = -1;
	    i = inrad.find( QRegExp("OK:"), 0 );
	    if (i != -1) {
		QMessageBox::warning( this, "ADDARW","Artikelnummer finns redan\n"+errorrad);
		lineEditArtikelNr->setFocus();
		lineEditArtikelNr->selectAll();
	    }
	}
    }
    inrad="";
    errorrad="";
}

void frmAddArtikel::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmAddArtikel::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}




void frmAddArtikel::lineEditLagerplats_2_returnPressed()
{
    lagerplats=lineEditLagerplats_2->text();
    if (lagerplats==""){
	lagerplats="1";
	lineEditLagerplats_2->setText(lagerplats);
    }
    lineEditLagerhylla_2->setFocus();
}

void frmAddArtikel::lineEditLagerhylla_2_returnPressed()
{
    lagerhylla=lineEditLagerhylla_2->text();
    if (lagerhylla==""){
	lagerhylla=" ";
    }
    lineEditLagersaldo_2->setFocus();
}

void frmAddArtikel::lineEditLagersaldo_2_returnPressed()
{
    int i;
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

void frmAddArtikel::lineEditInvGrp_2_returnPressed()
{
    invgrupp=lineEditInvGrp_2->text();
    if (invgrupp==""){
	invgrupp=" ";
    }
    lineEditABCkod_2->setFocus();
}

void frmAddArtikel::lineEditABCkod_2_returnPressed()
{
    abckod=lineEditABCkod_2->text();
    if (abckod==""){
	abckod=" ";
    }
    lineEditValuta_2->setFocus();
}

void frmAddArtikel::lineEditValuta_2_returnPressed()
{
    valuta=lineEditValuta_2->text();
    if (valuta==""){
	valuta="SEK";
	lineEditValuta_2->setText(valuta);
    }
    lineEditSenInkopsPris_2->setFocus();
}

void frmAddArtikel::lineEditSenInkopsPris_2_returnPressed()
{
    int i;
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
    lineEditSenKalkylPris_2->setFocus();
}


void frmAddArtikel::lineEditSenKalkylPris_2_returnPressed()
{
    int i;    
    kalkylpris=lineEditSenKalkylPris_2->text();
    if (kalkylpris==""){
	kalkylpris="0.00";
	lineEditSenKalkylPris_2->setText(kalkylpris);
    }
    i = -1;
    i = kalkylpris.find( QRegExp(","), 0 );
    if (i != -1){
	 kalkylpris.replace( QChar(','), "." );
	 lineEditSenKalkylPris_2->setText(kalkylpris);
     }
    lineEditBestPunkt_2->setFocus();
}

void frmAddArtikel::lineEditBestPunkt_2_returnPressed()
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

void frmAddArtikel::readResursFil()
{
    /*****************************************************/
    /*  Läs in .olfixrc filen här			               */
    /* Plocka fram var hjälpfilen finns			               */
    /*****************************************************/

    QStringList lines;
    QString homepath;
    homepath=QDir::homeDirPath();
/*    qDebug("Home Path=%s",homepath.latin1());		*/

    QFile f1( homepath+"/.olfixrc" );
   if ( f1.open( IO_ReadOnly ) ) {
        QTextStream stream( &f1 );
        QString line;
        int rad = -1;
        while ( !stream.eof() ) {
            line = stream.readLine(); /* line of text excluding '\n'	*/
	rad=line.find( QRegExp("HELPFILE="), 0 );
	if(rad == 0){
	    hjelpfil=line;
/*	    qDebug("hjelpfil=%s",hjelpfil.latin1());		*/
	    hjelpfil=(hjelpfil.right(hjelpfil.length() - 9));
/*	    qDebug("hjelpfil=%s",hjelpfil.latin1());		*/
	}
            lines += line;
        }
    }
    f1.close();
}

