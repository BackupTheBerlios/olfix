/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
/***************************************************************************
                          LEVFAKTW  -  description
                             -------------------
	              version 0.2
    begin                : Lör 9 aug 2003
    copyright          : (C) 2003 by Jan Pihlgren
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
#include <qdatetime.h>
// #include <qthread.h> 

#define MAXSTRING 5000


    QProcess* process;
    QProcess *Betprocess;
    QString inrad;
    QString inradbetvilk;
    QString inradbar;
    QString errorrad;
    int status=0;
    QString field;
    int  kontosemafor;
    
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

    QString autokonto;	// Automatkontering J/N
    
    QString bar;		// bokföringsår
    QString vernr;		// verifikationnummer
    QString datum;	// registreringsdatum
    QString kundnr;	// mitt kundnummer hos leverantören
    QString regdatum;	// registreringsdatum
    QString fakturanr;	// fakturanummer
    QString faktdatum;	// fakturadatum
    QString expiredatum;	// förfallodatum
    QString fakttext;	// fakturatext
    QString betvilk;	// betalningsvillkor, dagar netto
    QString faktbelopp;	// fakturabelopp i SEK
    QString momsktonr;	// kontonr för moms
    QString momsprocent;	// momsens procentsats
    QString momsbelopp;	// moms i kr
    QString debetkto;	// konto att debitera
    QString debetbelopp;	// belopp att debitera
    QString valutakurs;	// Köpkurs
    QString valutabelopp;	// Belopp i angiven valuta
    QString ocrnr;		// OCR nummer

void frmLevFakt::init()
{
    textLabelAutokonto->hide();
    QDateTime dt = QDateTime::currentDateTime();
    datum=dt.toString("yyyy-MM-dd");
    lineEditRegDatum->setText(datum);
    lineEditLevNr->setFocus();
    slotFindBar(datum);
//    qDebug("init::TRUE=%d FALSE=%d",TRUE,FALSE);
}

void frmLevFakt::slotlineEditLevNr_returnPressed()
{
    QDateTime dt = QDateTime::currentDateTime();
    datum=dt.toString("yyyy-MM-dd");
    lineEditRegDatum->setText(datum);
//    qDebug("regdatum=%s",datum.latin1());
//    slotFindBar(datum);
//    qDebug("bar=%s",bar.latin1());    
    levnr=lineEditLevNr->text();
    slotGetLev();
    lineEditLevKundNr->setFocus();
}

    
void frmLevFakt::slotlineEditLevKundNr_returnPressed()
{
    kundnr=lineEditLevKundNr->text();
    lineEditRegDatum->setFocus();
}

void frmLevFakt::slotlineEditRegDatum_returnPressed()
{
    regdatum=lineEditRegDatum->text();
    lineEditLevFakturaNr->setFocus();
}

void frmLevFakt::slotlineEditFaktNr_returnPressed()
{
    fakturanr=lineEditLevFakturaNr->text();
    lineEditFakturadatum->setFocus();
}

void frmLevFakt::slotlineEditFakturadatum_returnPressed()
{
    faktdatum=lineEditFakturadatum->text();
    if (faktdatum == ""){
	faktdatum=regdatum;
	lineEditFakturadatum->setText(faktdatum); 
    }
//    qDebug("regdatum=%s",regdatum.latin1());
//    qDebug("faktdatum=%s",faktdatum.latin1());
    QDate dt = QDate::fromString(faktdatum,Qt::ISODate);
    dt=dt.addMonths(1);
    expiredatum=dt.toString("yyyy-MM-dd");
//    qDebug("expiredatum=%s",expiredatum.latin1());
    lineEditLevBetDatum->setText(expiredatum);    
    lineEditBetalningsvilkor->setFocus();
}

void frmLevFakt::slotlineEditBetvilk_returnPressed()
{
    int dag;
    bool ok;
    betvilk=lineEditBetalningsvilkor->text();
    dag = betvilk.toInt(&ok,10);
    QDate dt = QDate::fromString(faktdatum,Qt::ISODate);
    dt=dt.addDays(dag);
    expiredatum=dt.toString("yyyy-MM-dd");
//    qDebug("expiredatum=%s",expiredatum.latin1());
    lineEditLevBetDatum->setText(expiredatum);    
    
    lineEditLevBetDatum->setFocus();
}

void frmLevFakt::slotlineEditLevBetDatum_returnPressed()
{
    // som default anges expiredatum = fakturadatum + 1 månad 
    expiredatum=lineEditLevBetDatum->text();
    lineEditOCRnr->setFocus();
}

void frmLevFakt::slotlineEditOCRnr_returnPressed()
{
    ocrnr=lineEditOCRnr->text();
    lineEditLevFakturaText->setFocus();
}

void frmLevFakt::slotlineEditLevFakturaText_returnPressed()
{
    fakttext=lineEditLevFakturaText->text();
    lineEditBar->setFocus();
}

void frmLevFakt::slotlineEditBar_returnPressed()
{
    bar=lineEditBar->text();		// bar = bokföringsår
    bar=bar.upper();
    lineEditBar->setText(bar);
//    slotFindBar(datum);
    slotCheckBar();
}

void frmLevFakt::slotlineEditLevMomskod_returnPressed()
{
    levmomskod=lineEditLevMomskod->text();
    slotGetMoms(levmomskod);
    lineEditValuta->setFocus();
}

void frmLevFakt::slotlineEditValuta_returnPressed()
{
    levvaluta=lineEditValuta->text();
    levvaluta=levvaluta.upper();
    lineEditValuta->setText(levvaluta);
    slotGetValuta();
    lineEditValutaKurs->setFocus();
}

void frmLevFakt::slotlineEditValutaKurs_returnPressed()
{
    valutakurs=lineEditValutaKurs->text();
    lineEditFaktBelopp->setFocus();
}

void frmLevFakt::slotlineEditFaktBelopp_returnPressed()
{
    int i;
    double tmpbelopp;
    double tmpvalutakurs;
    double tmpsumma;
    valutabelopp=lineEditFaktBelopp->text();
    tmpbelopp=valutabelopp.toDouble();
    tmpvalutakurs=valutakurs.toDouble();
    tmpsumma=tmpbelopp * tmpvalutakurs;
    faktbelopp=faktbelopp.setNum(tmpsumma,'f',2);
    lineEditKreditBelopp->setText(faktbelopp);
    i = -1;
    i = autokonto.find( QRegExp("J"), 0 );
    if (i != 0){
	pushButtonOK->setFocus();
// 	qDebug("slotlineEditFaktBelopp_returnPressed::Automatkontering=%s=",autokonto.latin1());	
    }else{
	lineEditKreditKontoNr->setFocus();
	kontosemafor=1;
    }
}

void frmLevFakt::slotlineEditKreditKontoNr_returnPressed()
{
    levkontonr=lineEditKreditKontoNr->text();
    status = 1;
    field = "KRKTONR";    
    slotCheckKontoNr(levkontonr);
    kontosemafor=2;
}

void frmLevFakt::slotlineEditKreditBelopp_returnPressed()
{
    double temp;
    double procent;
    double momskr;
    double debetkronor;
    if (status != 0){
	lineEditKreditBelopp->setFocus();
    }    
    faktbelopp=lineEditKreditBelopp->text();
    temp = faktbelopp.toDouble();
    faktbelopp = faktbelopp.setNum(temp,'f',2);
    // Beräkna momsen i kronor
    procent = momsprocent.toDouble()/100;
    momskr = temp * procent;
    momsbelopp = momsbelopp.setNum(momskr,'f',2);
    // Beräkna belopp exklusive moms
    debetkronor = temp - momskr;
    debetbelopp = debetbelopp.setNum(debetkronor,'f',2);
    // ...
    lineEditKreditBelopp->setText(faktbelopp);
    lineEditMomsBelopp->setText(momsbelopp);
    lineEditDebetBelopp->setText(debetbelopp);
    lineEditMomsKontoNr->setFocus();
}

void frmLevFakt::slotlineEditMomsKtoNr_returnPressed()
{
    momsktonr=lineEditMomsKontoNr->text();
    status=1;    
    field = "MOMSKTONR";
    slotCheckKontoNr(momsktonr);	// Finns momsktonr?
    kontosemafor=3;
}

void frmLevFakt::slotlineEditMomsBelopp_returnPressed()
{
    double temp;
    momsbelopp=lineEditMomsBelopp->text();
    temp = momsbelopp.toDouble();
    momsbelopp = momsbelopp.setNum(temp,'f',2);
    lineEditMomsBelopp->setText(momsbelopp);
    lineEditDebetKontoNr->setFocus();
}

void frmLevFakt::slotlineEditDebetKontoNr_returnPressed()
{
    debetkto=lineEditDebetKontoNr->text();
    status=1;    
    field = "DBKTONR";
   slotCheckKontoNr(debetkto);
}

void frmLevFakt::slotlineEditDebetBelopp_returnPressed()
{
    double temp;
    if (status != 0){
	lineEditDebetBelopp->setFocus();
    }
    debetbelopp=lineEditDebetBelopp->text();
    temp = debetbelopp.toDouble();
    debetbelopp = debetbelopp.setNum(temp,'f',2);
    lineEditDebetBelopp->setText(debetbelopp);
    pushButtonOK->setFocus();
}

void frmLevFakt::checkSemafor()
{
//   qDebug("status (efter) = %d",status);
    if (field == "KRKTONR"){
	if (status != 0){
	    lineEditKreditKontoNr->setFocus();
	}else{
	    lineEditKreditBelopp->setFocus();
	}
    }
    if (field == "MOMSKTONR"){
	if (status != 0){
	    lineEditMomsKontoNr->setFocus();
	}else{
	    lineEditMomsBelopp->setFocus();
	}
    }
     if (field == "DBKTONR"){
	 if (status != 0){
	     lineEditDebetKontoNr->setFocus();
	 }else{
	     lineEditDebetBelopp->setFocus();
	 } 
     }   
}

void frmLevFakt::slotGetLev()
{
/************************************************************************/
/*	Hämta leverantörsdata från databasen				*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);


//	qDebug("levnr=%s",levnr.latin1());

	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "LEVDSP");	// OLFIX funktion
	process->addArgument(levnr);

	frmLevFakt::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmLevFakt::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmLevFakt::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfGetProcess() ) );

	if (levnr == ""){
    	    QMessageBox::warning( this, "LEVFAKTW",
                      "Leverantörsnummer %s saknas. \n",levnr );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/LEVDSP!\n");
		QMessageBox::warning( this, "LEVFAKTW",
                            "Kan inte starta STYRMAN/LEVDSP! \n" );
	    }
	}
}

void frmLevFakt::slotDataOnStdout()
{
     while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
//     qDebug("slotDataOnStdout::inrad=%s",inrad.latin1());
}

void frmLevFakt::slotDataOnStderr()
{
      while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmLevFakt::slotEndOfGetProcess()
{
    int i,m;

    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
 //   qDebug("Error:",errorrad);
         if (i != -1) {
	QMessageBox::critical( this, "LEVFAKTW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
     }
     i = -1;

     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	 int i1 = inrad.find( QRegExp("1:"), 0 );	// levnr
	 int i2 = inrad.find( QRegExp("2:"), 0 );	// levorgnr
	 int i3 = inrad.find( QRegExp("3:"), 0 );	// levnamn	
	 int i4 = inrad.find( QRegExp("4:"), 0 );	// levadress
	 int i5 = inrad.find( QRegExp("5:"), 0 );	// levpostnr
	 int i6 = inrad.find( QRegExp("6:"), 0 );	// levpostadr
	 int i7 = inrad.find( QRegExp("7:"), 0 );	// levland
	 int i8 = inrad.find( QRegExp("8:"), 0 );	// levtfnnr
	 int i9 = inrad.find( QRegExp("9:"), 0 );	// levfaxnr
	 int i10 = inrad.find( QRegExp("10:"), 0 );	// levtelexnr
	 int i11 = inrad.find( QRegExp("11:"), 0 );	// levemail
	 int i12 = inrad.find( QRegExp("12:"), 0 );	// levpgnr
	 int i13 = inrad.find( QRegExp("13:"), 0 );	// levbgnr
	 int i14 = inrad.find( QRegExp("14:"), 0 );	// levref
	 int i15 = inrad.find( QRegExp("15:"), 0 );	// levreftfnnr
	 int i16 = inrad.find( QRegExp("16:"), 0 );	// levmomskod
	 int i17 = inrad.find( QRegExp("17:"), 0 );	// levskuld
	 int i18 = inrad.find( QRegExp("18:"), 0 );	// levkontonr
	 int i19 = inrad.find( QRegExp("19:"), 0 );	// levkundnr
	 int i20 = inrad.find( QRegExp("20:"), 0 );	// levvaluta
	 int i21 = inrad.find( QRegExp("21:"), 0 );	// levbetvilk, betalningsvillkor
//	 int i22 = inrad.find( QRegExp("22:"), 0 );
//	 int i23 = inrad.find( QRegExp("23:"), 0 );
	 int i22 = inrad.length();

	 m=i2-i1;
	 if (i1 != -1){
	     levnr=inrad.mid(i1+2,m-4);
	     lineEditLevNr->setText(levnr);
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
	     lineEditLevPostNr->setText(levpostnr);
	 }
	 
 	 m=i7-i6;
	 if (i6 != -1){
	     levpostadr=inrad.mid(i6+2,m-4);
	     lineEditLevPostAdr->setText(levpostadr);
	 }
	 
	 m=i8-i7;
	 if (i7 != -1){
	     levland=inrad.mid(i7+2,m-4);
	     lineEditLevLand->setText(levland);
	 }
	 
	  m=i17-i16;
	 if (i16 != -1){
	     levmomskod=inrad.mid(i16+3,m-5);	// skala av mellanslag
	     lineEditLevMomskod->setText(levmomskod);
	 }

 	  m=i19-i18;
	 if (i18 != -1){
	     levkontonr=inrad.mid(i18+3,m-5);
	     lineEditKreditKontoNr->setText(levkontonr);
	 }

	 m=i20-i19;
	 if (i19 != -1){
	     levkundnr=inrad.mid(i19+3,m-4);
	     lineEditLevKundNr->setText(levkundnr);
	 }
	 
	 m=i21-i20;
	 if (i20 != -1){
	     levvaluta=inrad.mid(i20+3,m-4);
	     levvaluta.remove( " " );
	     lineEditValuta->setText(levvaluta);
	 }
	 
	 m=i22-i21;
	 if (i21 != -1){
	     levbetvilk=inrad.mid(i21+3,m-4);
	     levbetvilk.remove( " " );
	 }
	 
	inrad="";
	errorrad="";
	i = -1;
     }
     slotGetValuta();
//     qDebug("slotEndOfGetProcess::levbetvilk=%s",levbetvilk.latin1());
//     slotGetBetvilkor(levbetvilk);
 }

void frmLevFakt::slotCheckBar()
{
/************************************************************************/
/*	Hämta bokföringsår från databasen					*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);
            errorrad="";
	    
//	qDebug("levnr=%s",levnr.latin1());

	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "BARCHK");	// OLFIX funktion
	process->addArgument(bar);

	frmLevFakt::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmLevFakt::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmLevFakt::connect( process, SIGNAL(processExited() ),this, SLOT(slotBARCHKEndOfProcess() ) );

	if (levnr == ""){
    	    QMessageBox::warning( this, "LEVFAKTW",
                      "Bokföringsår %s saknas. \n",bar );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/BARCHK!\n");
		QMessageBox::warning( this, "LEVFAKTW",
                            "Kan inte starta STYRMAN/BARCHK! \n" );
	    }
	}
}

void frmLevFakt::slotBARCHKEndOfProcess() 
{
    int i;

    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
 //   qDebug("Error:",errorrad);
    if (i != -1) {
	QMessageBox::critical( this, "LEVFAKTW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
            lineEditBar->setFocus();
     }else{
	    lineEditLevMomskod->setFocus();
     }
     errorrad="";
     inrad="";
     slotGetNextVernr();
}


void frmLevFakt::slotCheckKontoNr( QString ktonr )
{
/************************************************************************/
/*	Hämta kontonr från databasen					*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);
            errorrad="";
	    
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "KTOCHK");	// OLFIX funktion
	process->addArgument(bar);
	process->addArgument(ktonr);

	frmLevFakt::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmLevFakt::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmLevFakt::connect( process, SIGNAL(processExited() ),this, SLOT(slotKTOCHKEndOfProcess() ) );

	if (levnr == ""){
    	    QMessageBox::warning( this, "LEVFAKTW",
                      "Bokföringsår %s saknas. \n",bar );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/KTOCHK!\n");
		QMessageBox::warning( this, "LEVFAKTW",
                            "Kan inte starta STYRMAN/KTOCHK! \n" );
	    }
	}
}

void frmLevFakt::slotKTOCHKEndOfProcess() 
{
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
 //   qDebug("Error:",errorrad);
    if (i != -1) {
	status = -1;
	QMessageBox::critical( this, "LEVFAKTW",
		"ERROR!\n"+errorrad
	);
    }else{
	status = 0;
    }
    errorrad="";
    inrad="";
//    qDebug("Status = %d",status);
    checkSemafor();
}


void frmLevFakt::slotGetMoms(QString momskod)
{
/************************************************************************/
/*	Hämta momssats (procent) från databasen				*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);
            QString posttyp;
            errorrad="";
//	qDebug("momskod=%s",momskod.latin1());
	if (momskod == "1"){
	    posttyp="MOMS1";
	}
	if (momskod == "2"){
	    posttyp="MOMS2";
	}
	if (momskod == "3"){
	    posttyp="MOMS3";
	}
	if (momskod == "4"){
	    posttyp="MOMS4";
	}
	if (momskod == "5"){
	    posttyp="MOMS5";
	}
//	qDebug("posttyp=%s",posttyp.latin1());
	
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "FTGDSP");	// OLFIX funktion
	process->addArgument(posttyp);

	frmLevFakt::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmLevFakt::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmLevFakt::connect( process, SIGNAL(processExited() ),this, SLOT(slotFTGDSPEndOfProcess() ) );

	if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/KTOCHK!\n");
		QMessageBox::warning( this, "LEVFAKTW",
                            "Kan inte starta STYRMAN/FTGDSP! \n" );
	}
}

void frmLevFakt::slotFTGDSPEndOfProcess()
{
    int i,j,m;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
 //   qDebug("Error:",errorrad);
    if (i != -1) {
	QMessageBox::critical( this, "LEVFAKTW",
		"ERROR!\n"+errorrad
	);
    }else{
	i = inrad.find( QRegExp("2:"), 0 );
	j = inrad.length();	
	m=j-i;
	if (i != -1){
	    momsprocent=inrad.mid(i+2,m-4);
	    lineEditMoms->setText(momsprocent);
	 }
    }
    errorrad="";
    inrad="";
}


void frmLevFakt::slotUpdateLevresk()
{
/************************************************************************/
/*	Uppdater leverantörsrekontran					*/
/*	Insert into LEVRESK						*/    
/************************************************************************/
    int i;
    const char *userp = getenv("USER");
    QString usr(userp);
    errorrad="";
/*
    QString levnr;		// leverantörsnummer
    QString fakturanr;	// fakturanummer
    QString datum;		// registreringsdatum
    QString kundnr;		// mitt kundnummer hos leverantören
    QString regdatum;	// registreringsdatum
    QString faktdatum;	// fakturadatum
    QString expiredatum;	// förfallodatum
    QString fakttext;		// fakturatext
    QString bar;		// bokföringsår
    QString momsprocent;	// momsens procentsats    
    QString levkontonr;	// debet kontonr för fakturan
    QString faktbelopp;	// fakturabelopp
    QString momsktonr;	// kontonr för moms
    QString momsbelopp;	// moms i kr
//    QString kreditkto;	// konto att kreditera
//    QString kreditbelopp;	// belopp att kreditera
    QString debetkto;	// konto att debitera
    QString debetbelopp;	// belopp att debitera
    QString valutakurs;	// Köpkurs
    QString valutabelopp;	// Belopp i angiven valuta
    QString ocrnr;		// OCR nummer
*/  
	i = -1;
	i = autokonto.find(QRegExp("J"),0);
	// Om autokonto inte = J sätt vernr = blank
//  	qDebug("slotUpdateLevresk::i=%d",i);	
	if (i == -1){
	    vernr="0";
	}	 
//            qDebug("slotUpdateLevresk::vernr=%s\n",vernr.latin1());	    
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "LRESADD");	// OLFIX funktion
	process->addArgument(levnr);		// primary key
	process->addArgument(fakturanr);		// primary key
	process->addArgument(regdatum);
	process->addArgument(faktdatum);
	process->addArgument(expiredatum);	// förfallodatum
	process->addArgument(fakttext);
	process->addArgument(bar);		// bokföringsår
	process->addArgument(momsprocent);
	process->addArgument(levkontonr);
	process->addArgument(faktbelopp);
	process->addArgument(momsktonr);
	process->addArgument(momsbelopp);
//	process->addArgument(kreditkto);
//	process->addArgument(kreditbelopp);
	process->addArgument(debetkto);
	process->addArgument(debetbelopp);
	process->addArgument(usr);		// userid
	process->addArgument(levvaluta);
	process->addArgument(valutakurs);
	process->addArgument(valutabelopp);	// fakturans belopp i angiven valuta
	process->addArgument(ocrnr);		// OCR nummer
	process->addArgument(vernr);		// verifikationsnummer

	frmLevFakt::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmLevFakt::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmLevFakt::connect( process, SIGNAL(processExited() ),this, SLOT(slotLEVRESKEndOfProcess() ) );
	
	if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/LRESADD!\n");
		QMessageBox::warning( this, "LEVFAKTW",
                            "Kan inte starta STYRMAN/LRESADD! \n" );
	}
}

void frmLevFakt::slotLEVRESKEndOfProcess()
{
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
 //   qDebug("Error:",errorrad);
    if (i != -1) {
	QMessageBox::critical( this, "LEVFAKTW",
		"ERROR!\n"+errorrad
	);
    }else{
//   	qDebug("slotLEVRESKEndOfProcess::autokonto=%s",autokonto.latin1());
	i = -1;
	i = autokonto.find(QRegExp("J"),0);
	// Om autokonto = J uppdatera bokföringen
//  	qDebug("slotLEVRESKEndOfProcess::i=%d",i);	
	if (i != -1){
	    slotSaveVerHuvud();
	}else{
	    slotVerRemove();
    	    QMessageBox::information( this, "LEVFAKTW", "Uppdatering OK!\n"+errorrad);
	}
    }
    errorrad="";
    inrad="";
}

void frmLevFakt::slotGetNextVernr()
{
	const char *userp = getenv("USER");
            QString usr(userp);

	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "BARDSP");	// OLFIX funktion
	process->addArgument(bar);
	inrad="";

	frmLevFakt::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmLevFakt::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmLevFakt::connect( process, SIGNAL(processExited() ),this, SLOT(slotBARDSPEndOfProcess() ) );

	if ( !process->start() ) {
	    // error handling
	    fprintf(stderr,"Problem starta STYRMAN/BARDSP!\n");
	    QMessageBox::warning( this, "BOKFORSW",
                            "Kan inte starta STYRMAN/BARDSP! \n" );
	    }
}

void frmLevFakt::slotBARDSPEndOfProcess()
{
    int i = -1;
    int j = 0;

    i = errorrad.find( QRegExp("Error:"), 0 );
//	qDebug("errorrad=%s i=%d\n",errorrad.latin1(),i);
            if (i == 0) {
		QMessageBox::critical( this, "OLFIX - BARDSP",
			"ERROR!\n"+errorrad
		);
	            errorrad="";
		i = -1;
		status = -1;
		lineEditBar->clear();
	    }
	    else{
		i = -1;
		i = inrad.find( QRegExp("OK:"), 0 );
		if(i == 0){
		    i = -1;
		    i = inrad.find(QRegExp("VERNR:"), 0 );
		    i = i + 6;				// positionen efter VERNR:
		    j = inrad.find(QRegExp("KTOPLAN:"), 0 );
		    vernr = inrad.mid(i,j-2-i);
		    while (vernr.length()<8){
			vernr.prepend("0");
		    }
//		    qDebug("slotBARDSPEndOfProcess::inrad=%s\n i=%d  j = %d vernr=%s\n",inrad.latin1(),i,j,vernr.latin1());
//    		    LineEditVernr->setFocus();
		    lineEditVernr->setText(vernr);
		    status = 0;
		    inrad="";
		    errorrad="";
		}
	    }
	    listViewKtonr->clear();
	    slotGetKontoLista();
}

void frmLevFakt::slotSaveVerHuvud()
{
    /*
     QString bar;		// bokföringsår
    QString vernr;		// verifikationnummer
    QString datum;		// registreringsdatum
    QString kundnr;		// mitt kundnummer hos leverantören
    QString regdatum;	// registreringsdatum
    QString fakturanr;	// fakturanummer
    QString faktdatum;	// fakturadatum
    QString expiredatum;	// förfallodatum
    QString fakttext;		// fakturatext
    QString levkontonr;	// debet kontonr för fakturan
    QString faktbelopp;	// fakturabelopp
    QString momsktonr;	// kontonr för moms
    QString momsprocent;	// momsens procentsats
    QString momsbelopp;	// moms i kr
    QString kreditkto;	// konto att kreditera
    QString kreditbelopp;	// belopp att kreditera

      */
	const char *userp = getenv("USER");
            QString usr(userp);
	QString posttyp="H";	// H = Huvudpost
	QString kstalle;
	QString subkto;
	if (kstalle == "")
	    kstalle="    ";
	if(subkto == "")
	    subkto="    ";
	while (usr.length()<8){
	    usr.append(" ");
	}
	while (faktbelopp.length()<12){
	    faktbelopp.prepend(" ");
	}
//	qDebug("vernr=%s",vernr.latin1());
	process = new QProcess();
	process->addArgument( "./WRREC");	// OLFIX funktion
	process->addArgument(posttyp);
	process->addArgument(bar);
	process->addArgument(vernr);
	process->addArgument("001");
	process->addArgument(levkontonr);
	process->addArgument("K");
	process->addArgument(faktbelopp);
	process->addArgument(kstalle);
	process->addArgument(subkto);
	process->addArgument(regdatum);
	process->addArgument(usr);
	process->addArgument(fakttext);

	frmLevFakt::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmLevFakt::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmLevFakt::connect( process, SIGNAL(processExited() ),this, SLOT(slotWRRECEndOfProcess() ) );

	if ( !process->start() ) {
	    // error handling
	    fprintf(stderr,"Problem starta WRREC!\n");
	    QMessageBox::warning( this, "LEVFAKTW",
                            "Kan inte starta WRREC! \n" );
	    }
}

void frmLevFakt::slotSaveVerRad(QString ktonummer, QString belopp, QString radnr)
{
//	const char *userp = getenv("USER");
//            QString usr(userp);
	QString posttyp="D";	// D = Detaljrad, detaljpost
	QString kstalle;
	QString subkto;
	kstalle="    ";
	subkto="    ";
	while (belopp.length()<12){
	    belopp.prepend(" ");
	}
	process = new QProcess();
	process->addArgument( "./WRREC");	// OLFIX funktion
	process->addArgument(posttyp);
	process->addArgument(bar);
	process->addArgument(vernr);
	process->addArgument(radnr);
	process->addArgument(ktonummer);
	if (radnr == "001"){
	    process->addArgument("K");		// K=Kredit
	}else{
	    process->addArgument("D");		// D=Debet
	}
	process->addArgument(belopp);
	process->addArgument(kstalle);
	process->addArgument(subkto);

	if ( !process->start() ) {
	    // error handling
	    fprintf(stderr,"Problem starta WRREC!\n");
	    QMessageBox::warning( this, "LEVFAKTW",
                            "Kan inte starta WRREC! \n" );
	    }
}


void frmLevFakt::slotWRRECEndOfProcess()
{
    QString radnr;
//    radnr = "001";
//    slotSaveVerRad(levkontonr, faktbelopp, radnr);
    radnr = "002";
    slotSaveVerRad(momsktonr, momsbelopp, radnr);
    radnr = "003";
    slotSaveVerRad(debetkto, debetbelopp, radnr);
    slotUppdateraVer();
}

void frmLevFakt::slotUppdateraVer()
{
    /****************************************************************/
    /*	Uppdatera bokföringen. Tabellerna VERHUVUD, VERRAD, TRHAD   */
    /****************************************************************/
    
            const char *userp = getenv("USER");
            QString usr(userp);
            QString filnamn;

//	filnamn.append("/tmp/");
	filnamn.append(vernr);
//	filnamn.append(".txt");

	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "VERUPD");	// OLFIX funktion
	process->addArgument(filnamn);
//	fprintf(stderr,"filnamn=%s\n",filnamn.latin1());

	frmLevFakt::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmLevFakt::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmLevFakt::connect( process, SIGNAL(processExited() ),this, SLOT(slotVERUPDEndOfProcess() ) );

	if ( !process->start() ) {
	    // error handling
	    fprintf(stderr,"Problem starta STYRMAN/VERUPD!\n");
	    QMessageBox::warning( this, "LEVFAKTW",
                            "Kan inte starta STYRMAN/VERUPD! \n" );
	    }
}

void frmLevFakt::slotVERUPDEndOfProcess()
{
    int i = -1;

    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i == 0) {
	QMessageBox::critical( this, "OLFIX - VERUPD",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
	status = -1;
	frmLevFakt::slotVerRemove();
    }
    else{
	i = -1;
	i = inrad.find( QRegExp("OK: Databasen"), 0 );
	if (i != -1) {
	    QMessageBox::information( this, "LEVFAKTW",
		"Uppdatering OK!\n"+errorrad
		);
	    slotClearVariabler();				// Rensa variabler och fält.
	    status = 0;
	    inrad="";
	    errorrad="";
	}
    }
}

void frmLevFakt::slotVerRemove()
{
// Rensa alla fält samt ta bort temporärfilen /tmp/vernr.txt
    bool status;
    QString filnamn;
    QDir d = QDir::root();                      // "/"
    if ( !d.cd("tmp") ) {                       // "/tmp"
        qWarning( "Cannot find the \"/tmp\" directory" );
    }

    filnamn=vernr;
    filnamn.append(".txt");

    status=d.remove(filnamn,FALSE);
    frmLevFakt::slotClearVariabler();
}

void frmLevFakt::slotClearVariabler()
{
    levnr="";
    levorgnr="";
    levnamn="";
    levadress="";
    levpostnr="";
    levpostadr="";
    levland="";
    levtfnnr="";
    levfaxnr="";
    levtelexnr="";
    levemail="";
    levref="";
    levreftfnnr="";
    levmomskod="";
    levkontonr="";
    levpgnr="";
    levbgnr="";
    levkundnr="";
    
//    bar="";		// bokföringsår
    vernr="";		// verifikationnummer
    datum="";		// registreringsdatum
    kundnr="";		// mitt kundnummer hos leverantören
    regdatum="";		// registreringsdatum
    fakturanr="";		// fakturanummer
    faktdatum="";		// fakturadatum
    expiredatum="";	// förfallodatum
    fakttext="";		// fakturatext
    ocrnr="";		// OCR nummer
    faktbelopp="";		// fakturabelopp
    momsktonr="";		// kontonr för moms
    momsprocent="";	// momsens procentsats
    momsbelopp="";	// moms i kr
    debetkto="";		// konto att debitera
    debetbelopp="";	//belopp att debitera
    valutakurs="";		// valutakurs
    valutabelopp="";	// fakturabelopp i angiven valuta
    
    lineEditLevNr->clear();
    lineEditLevOrgNr->clear();
    lineEditLevNamn->clear();
    lineEditLevAdress->clear();
    lineEditLevPostNr->clear();
    lineEditLevPostAdr->clear();
    lineEditLevLand->clear();
    lineEditLevKundNr->clear();
    lineEditRegDatum->clear();
    lineEditLevFakturaNr->clear();
    lineEditFakturadatum->clear();
    lineEditLevBetDatum->clear();
    lineEditLevFakturaText->clear();
    lineEditOCRnr->clear();
//    lineEditBar->clear();
    lineEditVernr->clear();
    lineEditLevMomskod->clear();
    lineEditKreditKontoNr->clear();
    lineEditKreditBelopp->clear();
    lineEditMoms->clear();
    lineEditMomsKontoNr->clear();
    lineEditMomsBelopp->clear();
    lineEditDebetKontoNr->clear();
    lineEditDebetBelopp->clear(); 
    lineEditBetalningsvilkor->clear();
    lineEditValuta->clear();
    lineEditValutaKurs->clear();
    lineEditFaktBelopp->clear();
    lineEditLevNr->setFocus();
}




void frmLevFakt::slotGetValuta()
{
/************************************************************************/
/*	Hämta valutakurs (köpkurs) från databasen				*/
/************************************************************************/
	    
            const char *userp = getenv("USER");
            QString usr(userp);
//            QString filnamn;

	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "VALDSP");	// OLFIX funktion
	process->addArgument(levvaluta);
//	qDebug("levvaluta=%s",levvaluta.latin1());
	frmLevFakt::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmLevFakt::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmLevFakt::connect( process, SIGNAL(processExited() ),this, SLOT(slotVALDSPEndOfProcess() ) );

	if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/VALDSP!\n");
		QMessageBox::warning( this, "LEVFAKTW",
                            "Kan inte starta STYRMAN/VALDSP! \n" );
	}
}

void frmLevFakt::slotVALDSPEndOfProcess()
{
    int i = -1;
    int j = 0;

    i = errorrad.find( QRegExp("Error:"), 0 );
//	qDebug("errorrad=%s i=%d\n",errorrad.latin1(),i);
            if (i != -1) {
		QMessageBox::critical( this, "OLFIX - VALDSP",
			"ERROR!\n"+errorrad
		);
	            errorrad="";
		i = -1;
	    }
	    else{
		i = -1;
		i = inrad.find( QRegExp("1:"), 0 );
		if(i != -1){
		    i = -1;
		    i = inrad.find(QRegExp("4:"), 0 );	// Köpkurs
		    j = inrad.find(QRegExp("5:"), 0 );
		    valutakurs = inrad.mid(i+2,j-2-i);
//		    qDebug("valutakurs=%s",valutakurs.latin1());
		    lineEditValutaKurs->setText(valutakurs);
		    inrad="";
		    errorrad="";
		}
	    }
//	    qDebug("slotVALDSPEndOfProcess::levbetvilk=%s",levbetvilk.latin1());	    
	    slotGetBetvilkor(levbetvilk);
}


void frmLevFakt::slotGetBetvilkor( QString betvilkor )
{
/************************************************************************/
/*	Hämta betalningsvillkor (antal dagar) från databasen			*/
/************************************************************************/
            const char *userp = getenv("USER");
            QString usr(userp);
	QString villkor;
	int vilk;
//	villkor="";
            errorrad="";
	inradbetvilk="";
	betvilkor=betvilkor.remove( " " );
	villkor=betvilkor;
	villkor=villkor.remove(" ");
//	int le=villkor.length();
	vilk=villkor.toInt();
	villkor=villkor.number(vilk,10);
//	qDebug("slotGetBetvilkor::villkor=%s le=%d vilk=%d",villkor.latin1(),le,vilk);
	
	Betprocess = new QProcess();
	Betprocess->addArgument("./STYRMAN");	// OLFIX styrprogram
	Betprocess->addArgument(usr);		// userid
	Betprocess->addArgument("BETDSP");	// OLFIX funktion
	Betprocess->addArgument(villkor);
	
	frmLevFakt::connect( Betprocess, SIGNAL(readyReadStdout() ),this, SLOT(slotBETDSPDataOnStdout() ) );
	frmLevFakt::connect( Betprocess, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmLevFakt::connect( Betprocess, SIGNAL(processExited() ),this, SLOT(slotBETDSPEndOfProcess() ) );
	    
//	qDebug("slotGetBetvilkor::betvilkor=%s",betvilkor.latin1());
	    
	if ( !Betprocess->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/BETDSP!\n");
		QMessageBox::warning( this, "LEVFAKTW",
                            "Kan inte starta STYRMAN/BETDSP! \n" );
	}
}

void frmLevFakt::slotBETDSPDataOnStdout()
{
     while (Betprocess->canReadLineStdout() ) {
	QString line = Betprocess->readStdout();
	inradbetvilk.append(line);
	inradbetvilk.append("\n");
    }
}

void frmLevFakt::slotBETDSPEndOfProcess()
{
    int i,j,m;

    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
//    qDebug("slotBETDSPEndOfProcess::errorrad=%s",errorrad.latin1());
//    qDebug("slotBETDSPEndOfProcess::inradbetvilk (1) = %s",inradbetvilk.latin1());
    
    if (i != -1) {
	QMessageBox::critical( this, "LEVFAKTW",
		"ERROR!\n"+errorrad
	);
    }else{
	i = -1;
	i = inradbetvilk.find( QRegExp("OK:"), 0 );
	if(i != -1){
	    i = -1;
	    i = inradbetvilk.find( QRegExp("DAGAR:"), 0 );
	    j = inradbetvilk.find(QRegExp("BESKRIVNING:"),0);
	    m=j-(i+6);
//	    qDebug("slotBETDSPEndOfProcess::i=%d  j=%d  m=%d",i,j,m);
	    betvilk=inradbetvilk.mid(i+6,m);
	    betvilk.remove(" ");
	    lineEditBetalningsvilkor->setText(betvilk);
	 }
    }
//    qDebug("slotBETDSPEndOfProcess::inradbetvilk (2) = %s",inradbetvilk.latin1());
    errorrad="";
    inradbetvilk="";
    slotGetMomsKonto();
}


void frmLevFakt::slotFindBar(QString datum)
{
/************************************************************************/
/*	Hämta aktuellt bokföringsår från databasen				*/
/************************************************************************/
	    
            const char *userp = getenv("USER");
            QString usr(userp);
//            QString filnamn;
	    
	inradbar="";
	errorrad="";
	
//	qDebug("slotFindBar::datum=%s",datum.latin1());
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "BARFND");	// OLFIX funktion
	process->addArgument(datum);

	frmLevFakt::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotBARFNDDataOnStdout() ) );
	frmLevFakt::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmLevFakt::connect( process, SIGNAL(processExited() ),this, SLOT(slotBARFNDEndOfProcess() ) );

	if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/BARFND!\n");
		QMessageBox::warning( this, "LEVFAKTW",
                            "Kan inte starta STYRMAN/BARFND! \n" );
	}
}

void frmLevFakt::slotBARFNDDataOnStdout()
{
     while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inradbar.append(line);
	inradbar.append("\n");
    }
//     qDebug("slotBARFNDataOnStdout::inradbar=%s",inradbar.latin1());
}

void frmLevFakt::slotBARFNDEndOfProcess()
{
    int i = -1;

    i = errorrad.find( QRegExp("Error:"), 0 );
//   qDebug("errorrad=%s i=%d\n",errorrad.latin1(),i);
    if (i != -1) {
	QMessageBox::critical( this, "OLFIX - BARFND",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
    }
    else{
	i = -1;
	i = inradbar.find( QRegExp("1:"), 0 );
	if(i != -1){
	    bar = inradbar.mid(i+2,i+4);
	    bar = bar.left(2);
//	    qDebug("bokföringsår=%s",bar.latin1());
	    lineEditBar->setText(bar);
	    inradbar="";
	    errorrad="";
	}
    }
    slotGetLevLista();
}

void frmLevFakt::slotGetMomsKonto()
{
/************************************************************************/
/*	Hämta momskonto från databasen					*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);
            QString posttyp;
            errorrad="";
            posttyp="MOMSI";	// Momskonto, ingående moms
	    
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "FTGDSP");	// OLFIX funktion
	process->addArgument(posttyp);

	frmLevFakt::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmLevFakt::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmLevFakt::connect( process, SIGNAL(processExited() ),this, SLOT(slotGetMomsKtoEndOfProcess() ) );

	if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/FTGDSP!\n");
		QMessageBox::warning( this, "LEVFAKTW",
                            "Kan inte starta STYRMAN/FTGDSP! \n" );
	}
}

void frmLevFakt::slotGetMomsKtoEndOfProcess()
{
    int i,j,m;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
 //   qDebug("Error:",errorrad);
    if (i != -1) {
	QMessageBox::critical( this, "LEVFAKTW",
		"ERROR!\n"+errorrad
	);
    }else{
	i = inrad.find( QRegExp("2:"), 0 );
	j = inrad.length();	
	m=j-i;
	if (i != -1){
	    momsktonr=inrad.mid(i+2,m-4);
	    lineEditMomsKontoNr->setText(momsktonr);
	 }
    }
    errorrad="";
    inrad="";
}


void frmLevFakt::slotGetLevLista()
{
/************************************************************************/
/*	Hämta leverantörslista (levnr, levnamn) från databasen			*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);
            errorrad="";
	    
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "LEVLST");	// OLFIX funktion

	frmLevFakt::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmLevFakt::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmLevFakt::connect( process, SIGNAL(processExited() ),this, SLOT(slotGetLevlistaEndOfProcess() ) );

	if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/LEVLST!\n");
		QMessageBox::warning( this, "LEVFAKTW",
                            "Kan inte starta STYRMAN/LEVLST! \n" );
	}

}

void frmLevFakt::slotGetLevlistaEndOfProcess()
{
  QListViewItem* item;
  QString antrad;
  QString data1;
  QString data2;
  int i,j,k,m,n,rader;
 
//  qDebug("slotGetLevlistaEndOfProcess::errorrad=%s",errorrad.latin1());
//  qDebug("slotGetLevlistaEndOfProcess::inrad = %s",inrad.latin1());
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "LEVFAKTW",
		"ERROR!\n"+errorrad );
	 errorrad="";
     }else{
	i = inrad.find( QRegExp("NR_"), 0 );
	j = inrad.find( QRegExp("_:"), 0 );
	m=j-(i+3);
	if (i != -1){
	    antrad = inrad.mid(i+3,m);
                rader=antrad.toInt();
//                qDebug("slotGetLevlistaEndOfProcess::rader = %d",rader);
// 	  qDebug("slotGetLevlistaEndOfProcess (1)::j = %d   m=%d",j,m);		
	    for ( n = 0 ; n < rader ; n++){
		k=j;
		j = inrad.find( QRegExp("_:"), k+2 );	// Leverantörsnummer
		m=j-(k+2);
		data1=inrad.mid(k+2,m);
//		qDebug("slotGetLevlistaEndOfProcess (2)::j = %d   k=%d  m=%d",j,k,m);
//		qDebug("slotGetLevlistaEndOfProcess::data = %s",data.latin1());
		k=j;
		j = inrad.find( QRegExp("_:"), k+2 );	// Leverantörsnamn
		m=j-(k+2);
		data2=inrad.mid(k+2,m);
		item = new QListViewItem(listViewLev,data1,data2);
	    }
	}
     }
     slotGetKontoLista();
}

void frmLevFakt::slotPickupLevnr( QListViewItem * item)
{
    char levnummer[11]="";
//    qDebug("PickupKtonr\n");
    if(!item){
	return;
    }
     listViewLev->setCurrentItem(item);
     if(!item->key(0,TRUE)){
	 return;
     }

     strcpy(levnummer,item->key(0,TRUE));
     levnr=levnummer;
     lineEditLevNr->setText((levnr));
     lineEditLevNr->setFocus();
}

void frmLevFakt::slotGetKontoLista()
{
    	const char *userp = getenv("USER");
            QString usr(userp);
	inrad="";
	errorrad="";

	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "KTOVIEW");	// OLFIX funktion
	process->addArgument(bar);
	//	fprintf(stderr,"slotGetKontoLista::Bokföringsår=%s\n",bar.latin1());
	frmLevFakt::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmLevFakt::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmLevFakt::connect( process, SIGNAL(processExited() ),this, SLOT(slotKTOVIEWEndOfProcess() ) );

	if ( !process->start() ) {
	    // error handling
	    fprintf(stderr,"Problem starta STYRMAN/KTOVIEW!\n");
	    QMessageBox::warning( this, "LEVFAKTW",
                            "Kan inte starta STYRMAN/KTOVIEW! \n" );
	    }
}

void frmLevFakt::slotKTOVIEWEndOfProcess()
{
  QListViewItem* item;
  QString antrad;
  QString data1;
  QString data2;
  int i,j,k,m,n,rader;
 
//  qDebug("slotKTOVIEWEndOfProcess::errorrad=%s",errorrad.latin1());
//  qDebug("slotKTOVIEWEndOfProcess::inrad = %s",inrad.latin1());
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "LEVFAKTW",
		"ERROR!\n"+errorrad );
	 errorrad="";
     }else{
	i = inrad.find( QRegExp("NR_"), 0 );
	j = inrad.find( QRegExp("_:"), 0 );
	m=j-(i+3);
	if (i != -1){
	    antrad = inrad.mid(i+3,m);
                rader=antrad.toInt();
//                qDebug("slotKTOVIEWEndOfProcess::rader = %d",rader);
// 	  qDebug("slotKTOVIEWEndOfProcess (1)::j = %d   m=%d",j,m);		
	    for ( n = 0 ; n < rader ; n++){
		k=j;
		j = inrad.find( QRegExp("_:"), k+2 );	// Kontonummer
		m=j-(k+2);
		data1=inrad.mid(k+2,m);
//		qDebug("slotKTOVIEWEndOfProcess (2)::j = %d   k=%d  m=%d",j,k,m);
//		qDebug("slotKTOVIEWEndOfProcess (3)::data1 = %s",data1.latin1());
		k=j;
		j = inrad.find( QRegExp("_:"), k+2 );	// Kontonamn
		m=j-(k+2);
		data2=inrad.mid(k+2,m);
//		qDebug("slotKTOVIEWEndOfProcess (4)::data2 = %s",data2.latin1());		
		item = new QListViewItem(listViewKtonr,data1,data2);
	    }
	}
     }
     slotGetAutokonto();
}

void frmLevFakt::slotPickupKtonr( QListViewItem * item)
{
    QString ktonr;
    char kontonummer[11]="";

    if(!item){
	return;
    }
     listViewKtonr->setCurrentItem(item);
     if(!item->key(0,TRUE)){
	 return;
     }

     strcpy(kontonummer,item->key(0,TRUE));
     ktonr=kontonummer;
     if (kontosemafor==1){
	 lineEditKreditKontoNr->setText((ktonr));
	 lineEditKreditKontoNr->setFocus();
     }
     if (kontosemafor==2){
	 lineEditMomsKontoNr->setText((ktonr));
	 lineEditMomsKontoNr->setFocus();
     }
     if (kontosemafor==3){
	 lineEditDebetKontoNr->setText((ktonr));
	 lineEditDebetKontoNr->setFocus();
     }

}

void frmLevFakt::slotGetAutokonto()
{
/************************************************************************/
/*	Hämta momskonto från databasen					*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);
            QString posttyp;
            errorrad="";
            posttyp="AUTOK";	// Momskonto, ingående moms
	    
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "FTGDSP");	// OLFIX funktion
	process->addArgument(posttyp);

	frmLevFakt::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmLevFakt::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmLevFakt::connect( process, SIGNAL(processExited() ),this, SLOT(slotGetAutokontoEndOfProcess() ) );

	if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/FTGDSP!\n");
		QMessageBox::warning( this, "LEVFAKTW",
                            "Kan inte starta STYRMAN/FTGDSP! \n" );
	}
}

void frmLevFakt::slotGetAutokontoEndOfProcess()
{
    int i,j,m;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
 //   qDebug("Error:",errorrad);
    if (i != -1) {
	QMessageBox::critical( this, "LEVFAKTW",
		"ERROR!\n"+errorrad
	);
    }else{
	i = inrad.find( QRegExp("2:"), 0 );
	j = inrad.length();	
	m=j-i;
	if (i != -1){
	    autokonto=inrad.mid(i+2,m-4);
//   	   qDebug("slotGetAutokontoEndOfProcess::Automatkontering=%s=",autokonto.latin1());
	   i = -1;
	   i = autokonto.find( QRegExp("J"), 0 );
	   if (i != 0){
	       textLabel1_3->hide();	// text för kontonr och belopp
	       textLabel3_3->hide();
	       textLabel5_3->hide();
	       textLabel2_3->hide();
	       textLabel4_2->hide();
	       textLabel6_2->hide();
	       lineEditKreditKontoNr->hide();
	       lineEditMomsKontoNr->hide();
	       lineEditDebetKontoNr->hide();
	       lineEditKreditBelopp->hide();
	       lineEditMomsBelopp->hide();
	       lineEditDebetBelopp->hide();
	       listViewKtonr->hide();
	       textLabelAutokonto->show();
	   }
	 }
    }
    errorrad="";
    inrad="";
}
