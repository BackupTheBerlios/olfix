/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
/***************************************************************************
                          DSPINKW  -  description
                             -------------------
		     version 0.4
    begin     	: Sön 21 dec 2003
    modified	: Tis 3 dec 2004
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
#include <qdatetime.h>
#define MAXSTRING 5000


    QProcess* process;
    QString inrad;
    QString* rad;
    QString errorrad;

    QString inkordernr;
    
void frmDspInk::init()
{
    frmDspInk::listViewRader_format();
    lineEditInkOrderNbr->setFocus();
}

void frmDspInk::lineEditInkOrderNbr_returnPressed()
{
    inkordernr=lineEditInkOrderNbr->text();
//    qDebug("inkordernr=%s",inkordernr.latin1());
    frmDspInk::cleanOrderHuvud();
    listViewRader->clear();
    frmDspInk::DspOrder();
}

void frmDspInk::DspOrder()
{
/************************************************************************/
/*	Hämta order, INKREG och INKRADREG				*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);
	    
	inrad="";   
	errorrad="";
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "INKHDSP");	// OLFIX funktion
	process->addArgument(inkordernr);
	
	frmDspInk::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmDspInk::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmDspInk::connect( process, SIGNAL(processExited() ),this, SLOT(slotOrderHuvudEndOfProcess() ) );
	    
	if (inkordernr == ""){
    	    QMessageBox::warning( this, "DSPINKW",
                      "Inköpsordernr saknas! \n" );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/INKDSP!\n");
		QMessageBox::warning( this, "DSPINKW",
                            "Kan inte starta STYRMAN/INKHDSP! \n" );
	    }
	}
}

void frmDspInk::slotOrderHuvudEndOfProcess()
{
    int i,m;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
 //   qDebug("Error:",errorrad);
    if (i != -1) {
	QMessageBox::critical( this, "ADDINKW",
		"ERROR!\n"+errorrad
	);
    }else{
	i = -1;
	i = inrad.find( QRegExp("OK:"), 0 );
	if (i != -1) {
	    int i1 = inrad.find( QRegExp("01:"), 0 );		// inköpsordernr
	    int i2 = inrad.find( QRegExp("02:"), 0 );		// beställningstyp
	    int i3 = inrad.find( QRegExp("03:"), 0 );		// orderdatum
	    int i4 = inrad.find( QRegExp("04:"), 0 );		// leverantörsnr
	    int i5 = inrad.find( QRegExp("05:"), 0 );		// leverantörsnamn
	    int i6 = inrad.find( QRegExp("06:"), 0 );		// leverantörsadress
	    int i7 = inrad.find( QRegExp("07:"), 0 );		// lev. postnr
	    int i8 = inrad.find( QRegExp("08:"), 0 );		// lev. postadr
	    int i9 = inrad.find( QRegExp("09:"), 0 );		// lev. land
	    int i10 = inrad.find( QRegExp("10:"), 0 );		// lev. valuta
	    int i11 = inrad.find( QRegExp("11:"), 0 );		// betalningsvillkor
	    int i12 = inrad.find( QRegExp("12:"), 0 );		// leveransvillkor
	    int i13 = inrad.find( QRegExp("13:"), 0 );		// leveranssätt
	    int i14 = inrad.find( QRegExp("14:"), 0 );		// godsmärke
	    int i15 = inrad.find( QRegExp("15:"), 0 );		// kommentar
	    int i16 = inrad.find( QRegExp("16:"), 0 );		// text
	    int i17 = inrad.find( QRegExp("17:"), 0 );		// varref
	    int i18 = inrad.find( QRegExp("18:"), 0 );		// varreftfn
	    int i19 = inrad.find( QRegExp("19:"), 0 );		// varreffax
	    int i20 = inrad.find( QRegExp("20:"), 0 );		// erref
	    int i21 = inrad.find( QRegExp("21:"), 0 );		// leveransdatum
	    int i22 = inrad.find( QRegExp("22:"), 0 );		// kundnr
	    int i23 = inrad.find( QRegExp("23:"), 0 );		// ftgnamn
	    int i24 = inrad.find( QRegExp("24:"), 0 );		// ftgadr
	    int i25 = inrad.find( QRegExp("25:"), 0 );		// ftgpostnr
	    int i26 = inrad.find( QRegExp("26:"), 0 );		// ftgpostadr
	    int i27 = inrad.find( QRegExp("27:"), 0 );		// sprakkod
	    int i28 = inrad.find( QRegExp("28:"), 0 );		// bekreftkod
	    int i29 = inrad.find( QRegExp("29:"), 0 );		// orderstatus
	    int i30 = inrad.find( QRegExp("30:"), 0 );		// utskriftskod
	    int i31 = inrad.find( QRegExp("31:"), 0 );		// ordersumma
	    int i32 = inrad.find( QRegExp("END:"), 0 );
/*	
	    m=i2-i1;
	    if (i1 != -1){
		QString ordernr=inrad.mid(i1+3,m-4);
		lineEditBestLevNr->setText(ordernr);
	    }
*/	    
	    m=i3-i2;
	    if (i2 != -1){
	  	QString besttyp=inrad.mid(i2+3,m-4);
		lineEditBesttyp->setText(besttyp);
	    }

	    m=i4-i3;
	    if (i3 != -1){
		QString orderdatum=inrad.mid(i3+3,m-4);
		lineEditBestDatum->setText(orderdatum);
	    }

	    m=i5-i4;
	    if (i4 != -1){
		QString levid=inrad.mid(i4+3,m-4);
		lineEditBestLevNr->setText(levid);
	    }

	    m=i6-i5;
	    if (i5 != -1){
		QString levnamn=inrad.mid(i5+3,m-4);
		lineEditLevNamn->setText(levnamn);
	    }

	    m=i7-i6;
	    if (i6 != -1){
		QString levadr=inrad.mid(i6+3,m-4);
		lineEditLevAdress->setText(levadr);
	    }

	    m=i8-i7;
	    if (i7 != -1){
		QString levpostnr=inrad.mid(i7+3,m-4);
		lineEditLevPostnr->setText(levpostnr);
	    }

	    m=i9-i8;
	    if (i8 != -1){
		QString levpostadr=inrad.mid(i8+3,m-4);
		lineEditLevPostAdress->setText( levpostadr);
	    }

	    m=i10-i9;
	    if (i9 != -1){
		QString levland=inrad.mid(i9+3,m-4);
		lineEditLevLand->setText(levland);
	    }

	    m=i11-i10;
	    if (i10 != -1){
		QString valuta=inrad.mid(i10+3,m-4);
		lineEditValuta->setText(valuta);
	    }

	    m=i12-i11;
	    if (i11 != -1){
		QString betvillkor=inrad.mid(i11+3,m-4);
		lineEditBetvilk->setText(betvillkor);
	    }

	    m=i13-i12;
	    if (i12 != -1){
		QString levvillkor=inrad.mid(i12+3,m-4);
		lineEditLevvillkor->setText(levvillkor);
	    }

	    m=i14-i13;
	    if (i13 != -1){
		QString levsett=inrad.mid(i13+3,m-4);
		lineEditLevsett->setText(levsett);
	    }

	    m=i15-i14;
	    if (i14 != -1){
		QString godsmerke=inrad.mid(i14+3,m-4);
		lineEditGodsmarke->setText(godsmerke);
	    }

	    m=i16-i15;
	    if (i15 != -1){
		QString kommentar=inrad.mid(i15+3,m-4);
		lineEditKommentar->setText(kommentar);
	    }

	    m=i17-i16;
	    if (i16 != -1){
		QString besttext=inrad.mid(i16+3,m-4);
//		lineEditText->setText(besttext);
		textEditBestText->setText(besttext);
	    }

	    m=i18-i17;
	    if (i17 != -1){
		QString varref=inrad.mid(i17+3,m-4);
		lineEditVarRef->setText(varref);
	    }

	    m=i19-i18;
	    if (i18 != -1){
		QString varreftfn=inrad.mid(i18+3,m-4);
		lineEditFtgAdress->setText(varreftfn);
	    }

	    m=i20-i19;
	    if (i19 != -1){
		QString varreffax=inrad.mid(i19+3,m-4);
		lineEditFtgPostnr->setText(varreffax);
	    }

	    m=i21-i20;
	    if (i20 != -1){
		QString erref=inrad.mid(i20+3,m-4);
		lineEditErref->setText(erref);
	    }

	    m=i22-i21;
	    if (i21 != -1){
		QString levdatum=inrad.mid(i21+3,m-4);
		lineEditLeveransDatum ->setText(levdatum);
	    }

	    m=i23-i22;
	    if (i22 != -1){
		QString kundnr=inrad.mid(i22+3,m-4);
		lineEditKundnr->setText(kundnr);
	    }
	    
	    m=i24-i23;
	    if (i23 != -1){
		QString ftgnamn=inrad.mid(i23+3,m-4);
		lineEditFtgNamn ->setText(ftgnamn);
	    }

	    m=i25-i24;
	    if (i24 != -1){
		QString ftglevadr=inrad.mid(i24+3,m-4);
		lineEditFtgAdress->setText(ftglevadr);
	    }
	    
	    m=i26-i25;
	    if (i25 != -1){
		QString ftglevpostnr=inrad.mid(i25+3,m-4);
		lineEditFtgPostnr ->setText(ftglevpostnr);
	    }
	    
	    m=i27-i26;
	    if (i26 != -1){
		QString ftglevpostadr=inrad.mid(i26+3,m-4);
		lineEditFtgPostAdress ->setText(ftglevpostadr);
	    }
	    
	    m=i28-i27;
	    if (i27 != -1){
		QString sprakkod=inrad.mid(i27+3,m-4);
//		lineEditx ->setText(sprakkod);
	    }
	    
	    m=i29-i28;
	    if (i28 != -1){
		QString bekreftkod=inrad.mid(i28+3,m-4);
		lineEditBekreft ->setText(bekreftkod);
	    }
	    
	    m=i30-i29;
	    if (i29 != -1){
		QString orderstatus=inrad.mid(i29+3,m-4);
		lineEditStatus ->setText(orderstatus);
	    }
	    
	    m=i31-i30;
	    if (i30 != -1){
		QString utskriftskod=inrad.mid(i30+3,m-4);
//		lineEdity ->setText(utskriftskod);
	    }
	    
	    m=i32-i31;
	    if (i31 != -1){
		QString ordersumma=inrad.mid(i31+3,m-4);
		lineEditTotal ->setText(ordersumma);
	    }
	    
	    inrad="";
	    errorrad="";
	    inrad="";
	    i = -1;
	}	
	frmDspInk::DspOrderRader();
    }
    errorrad="";
    lineEditInkOrderNbr->setFocus();
}

void frmDspInk::DspOrderRader()
{
/************************************************************************/
/*	Hämta orderrader, INKRADREG					*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);
	    
	inrad="";   
	errorrad="";
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "INKRLST");	// OLFIX funktion
	process->addArgument(inkordernr);
	
	frmDspInk::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmDspInk::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmDspInk::connect( process, SIGNAL(processExited() ),this, SLOT(slotRaderEndOfProcess() ) );
	    
	if (inkordernr == ""){
    	    QMessageBox::warning( this, "DSPINKW",
                      "inkällningsnr saknas \n" );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		QMessageBox::warning( this, "DSPINKW",
                            "Kan inte starta STYRMAN/INKRDSP! \n" );
	    }
	}
}

void frmDspInk::slotDataOnStdout()
{
     while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmDspInk::slotDataOnStderr()
{
      while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmDspInk::listViewRader_format()
{
    listViewRader->setColumnWidth(0,36);		// Radnr
     listViewRader->setColumnAlignment( 0, Qt::AlignRight );
    listViewRader->setColumnWidth(1,185);		// Artikelnr
    listViewRader->setColumnWidth(2,185);		// Benämning
    listViewRader->setColumnWidth(3,55);		// Lev.vecka
    listViewRader->setColumnAlignment( 3, Qt::AlignRight );
    listViewRader->setColumnWidth(4,80);		// Beställt Antal
    listViewRader->setColumnAlignment( 4, Qt::AlignRight );
    listViewRader->setColumnWidth(5,80);		// Levererat Antal
    listViewRader->setColumnAlignment( 5, Qt::AlignRight );
    listViewRader->setColumnWidth(6,80);		// Resterande Antal
    listViewRader->setColumnAlignment( 6, Qt::AlignRight );
    listViewRader->setColumnWidth(7,80);		// Pris
    listViewRader->setColumnAlignment( 7, Qt::AlignRight );
    listViewRader->setColumnWidth(8,80);		// Summa    
    listViewRader->setColumnAlignment( 8, Qt::AlignRight ); 
}


void frmDspInk::slotRaderEndOfProcess()
{
    QListViewItem* item;
    bool ok;
    int i,j,k,m,n,p;
    QString tmp;
    QString radnr;
    QString artikelnr;
    QString benemning;
    QString bestantal;
    QString levantal="0";
    QString rest="0";
    QString inkpris;
    QString levvecka;
    QString radsumma;
    QString ordersumma;
    double pris=0;
    double bestelltant=0;
    double levant=0;
    double restant=0;
    double summa=0;
    double ordersum=0;
    
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
 //   qDebug("Error:",errorrad);
    if (i != -1) {
	QMessageBox::critical( this, "DSPINKW",
		"ERROR!\n"+errorrad
	);
    }else{
	i = inrad.find( QRegExp("OK: NR_0_"), 0 );
	if (i != -1) {
	    QMessageBox::information( this, "DSPINKW",
		"Inköpsregistret innehåller inga orderrader!\n"
		);
	}else{
	    i = inrad.find( QRegExp("OK: NR_"), 0 )+7;
	    j=inrad.find(QRegExp("_:"),0);
	    k=j-i;
//	    qDebug("i=%d j=%d k=%d",i,j,k);
	    tmp=inrad.mid(i,k);
//	    qDebug("tmp=%s",tmp.latin1());
	    m=tmp.toInt(&ok,10);
//	    qDebug("m=%d",m);
	    for (n=0;n<m;n++){
		for (p=0;p<12;p++){	// 11 = antal fält i INKRADREG
		    i=j;
		    j=j=inrad.find(QRegExp("_:"),i+2);
		    k=j-i-2;
		    tmp=inrad.mid(i+2,k);
		    if(p==1)
			radnr=tmp;
		    if(p==2)
			artikelnr=tmp;
		    if(p==4){
			bestantal=tmp;
			bestelltant=tmp.toDouble();
		    }
		    if(p==5){
			levantal=tmp;
			levant=tmp.toDouble();
//			qDebug("levantal=%s",levantal.latin1());
		    }
		    if(p==6){
			rest=tmp;
			restant=tmp.toDouble();
		    }		    
		    
		    if(p==7){
			inkpris=tmp;
			pris=tmp.toDouble();
		    }
		    if(p==8)
			levvecka=tmp;
		    if(p==11)
			benemning=tmp;
//		    qDebug("tmp=%s    p=%d",tmp.latin1(),p);
		}
//		summa=bestelltant*pris;
		summa=(bestelltant-levant)*pris;
		ordersum=ordersum+summa;
		radsumma=radsumma.setNum(summa,'f',2 );
		item = new QListViewItem(listViewRader,radnr,artikelnr,benemning,levvecka,bestantal,levantal,rest,inkpris);
		item->setText(8,radsumma);
	    }
	    ordersumma=ordersumma.setNum(ordersum,'f',2);
	    lineEditOrderSumma->setText(ordersumma);
	}
    }
}

void frmDspInk::cleanOrderHuvud()
{
    lineEditBestLevNr->clear();
    lineEditBestDatum->clear();
    lineEditLevNamn->clear();
    lineEditLevAdress->clear();
    lineEditLevPostnr->clear();
    lineEditLevPostAdress->clear();
    lineEditLevLand->clear();
    lineEditFtgNamn->clear();
    lineEditFtgAdress->clear();
    lineEditFtgPostnr->clear();
    lineEditFtgPostAdress->clear();
    lineEditValuta->clear();
    lineEditBetvilk->clear();
    lineEditGodsmarke->clear();
    textEditBestText->clear();
    lineEditVarRef->clear();
    lineEditKundnr->clear();
    lineEditLeveransDatum->clear();
    lineEditBesttyp->clear();
    lineEditOrderSumma->clear();
    lineEditTotal->clear();
}
