/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
/***************************************************************************
                          ADDAREW  -  description
                             -------------------
		     version 0.1
    begin                	: Lör 14 nov 2003
    modified	: 
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
   
void frmDspArtikelEkonomidata::init()
{    
    lineEditArtikelNr->setFocus();
}

void frmDspArtikelEkonomidata::lineEditArtikelNr_returnPressed()
{
    artikelnr=lineEditArtikelNr->text();
    frmDspArtikelEkonomidata::getGrunddata();
    pushButtonOK->setFocus();
}

void frmDspArtikelEkonomidata::getGrunddata()
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
	frmDspArtikelEkonomidata::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmDspArtikelEkonomidata::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
            frmDspArtikelEkonomidata::connect( process, SIGNAL(processExited() ),this, SLOT(slotGetGrDataEndOfProcess() ) );

	if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta DSPAREW!\n");
		QMessageBox::warning( this, "",
                            "Kan inte starta ARDSP! \n" );
	}
}


void frmDspArtikelEkonomidata::getLagerdata()
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
	frmDspArtikelEkonomidata::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmDspArtikelEkonomidata::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
            frmDspArtikelEkonomidata::connect( process, SIGNAL(processExited() ),this, SLOT(slotgetLaDataEndOfProcess() ) );

	if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta DSPAREW!\n");
		QMessageBox::warning( this, "",
                            "Kan inte starta ARDSPL! \n" );
	}
}

void frmDspArtikelEkonomidata::slotGetGrDataEndOfProcess()
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
//	     lineEditProdklass->setText(prodklass);	// Visas inte i detta program
	 }

 	 m=i9-i8;
	 if (i8 != -1){
	     prodkto=inrad.mid(i8+3,m-5);
//	     lineEditProdkonto->setText(prodkto);	// Visas inte i detta program
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
//	     lineEditNettovikt->setText(nettovikt);	// Visas inte i detta program
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
//	     lineEditTulltaxenr->setText(tulltaxenr);		// Visas inte i detta program
	 }
	 
	 m=i20-i19;
	 if (i19 != -1){
	     volym=inrad.mid(i19+3,m-5);
//	     lineEditVolym->setText(volym);			// Visas inte i detta program
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
   frmDspArtikelEkonomidata::getLagerdata();
    }
}

void frmDspArtikelEkonomidata::slotgetLaDataEndOfProcess()
{
    int i,m;

    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
 //   qDebug("Error:",errorrad);
         if (i != -1) {
	QMessageBox::critical( this, "DSPAREW",
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
//		lineEditLagerhylla_2->setText(lagerhylla);	// Visas inte i detta program
	    }

	    m=i5-i4;
	    if (i4 != -1){
		lagersaldo=inrad.mid(i4+3,m-5);
		lineEditLagersaldo_2->setText(lagersaldo);
	    }

	    m=i6-i5;
	    if (i5 != -1){
		invgrupp=inrad.mid(i5+3,m-5);
//		lineEditInvGrp_2->setText(invgrupp);	// Visas inte i detta program
	    }

	    m=i7-i6;
	    if (i6 != -1){
		abckod=inrad.mid(i6+3,m-5);
//		lineEditABCkod_2->setText(abckod);		// Visas inte i detta program
	    }

	    m=i8-i7;
	    if (i7 != -1){
		valuta=inrad.mid(i7+3,m-5);
//		lineEditValuta_2->setText(valuta);		// Visas inte i detta program
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
		lineEditKalkylPris_2->setText(kalkylpris);
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
		lineEditOmkostnader_2->setText(omkost);
	    }

	inrad="";
	errorrad="";
	inrad="";
	i = -1;
          }
    }
}

void frmDspArtikelEkonomidata::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmDspArtikelEkonomidata::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}




