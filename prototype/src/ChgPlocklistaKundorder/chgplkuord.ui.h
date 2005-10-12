/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
/***************************************************************************
                          PLCHGW  -  Skapa plocklista för kundorder
                         ChgPlocklistaKundorder
                             -------------------
		     version 0.1
    begin     	: Mån  25 april 2005
    modified	: 
    copyright            : (C) 2005 by Jan Pihlgren
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

#include <qdir.h> 

    QProcess* process;
    QString inrad;
    QString* rad;
    QString errorrad;
    QString hjelpfil;
    int varv=0;

    QString kundordernr;
    QString reportpath;
    QString kugarversion;
    QString kommando;

//	Orderhuvud    
    QString ordernr;	// 01
    QString ordertyp;	// 02
    QString orderdatum;	// 03
    QString leveransdatum;
    QString kundnr;	// 04
    QString kundnamn;	// 05
    QString kundadr;	// 06
    QString kundpostnr;	// 07
    QString kundpostadr;	// 08
    QString kundland;	// 09
    QString erref;		// 20
    QString leveransadress;
    QString leveranspostnr;
    QString leveranspostadress;
    QString leveransland;
    QString valuta;	// 10
    QString betvillkor;	// 11
    QString levvillkor;	// 12
    QString levsett;	// 13
    QString godsmerke;	// 14
    QString besttext;	// 16
    QString varref;	// 17
    QString seljare;
    QString exportkod;
    QString moms;
    QString levdatum;	// 21
    QString kundnum;	// 22
    QString ftgnamn;	// 23
    QString ftgadr;	// 24
    QString ftgpostnr;	// 25
    QString ftgpostadr;	// 26
    QString sprakkod;	// 27
    QString bekreftad;	// 28
    QString orderstatus;	// 29
    QString utskriftkod;	// 30
    QString total;		// 31
//  -----------------------------
    QString temp;
    QString ftgland;
    QString restnoterat;
//  -----------------------------    
    bool radnrflag=FALSE;
    QString orderartikelnr;
    QString orderbenamn;
    QString radleveransvecka;
    QString orderantal;
    QString attleverera;
    QString plockatantal;
    QString orderradnr="";
    QString oldradnr;

    
void frmChgPlKundOrder::init()
{
    frmChgPlKundOrder::listViewRader_format();
    frmChgPlKundOrder::GetReportDir();
    pushButtonOK->setEnabled(TRUE);
    lineEditOrderNr->setFocus();
}

void frmChgPlKundOrder::lineEditOrderNr_returnPressed()
{
    listViewRader->clear();
    kundordernr=lineEditOrderNr->text();
    if (kundordernr == ""){
        QMessageBox::warning( this, "PLCHGW",
                     "Kundorder saknas! \n" );
	lineEditOrderNr->setFocus();
    }else{
	frmChgPlKundOrder::checkStatus();
//	GetOrderHeader();
	listViewRader->setFocus();
	listViewRader->firstChild ();
	listViewRader->setSelected(listViewRader->firstChild (),TRUE);
    }
}

void frmChgPlKundOrder::lineEditPlockatAntal_returnPressed()
{
    plockatantal=lineEditPlockatAntal->text();
    pushBtnOKRad->setFocus();
}

void frmChgPlKundOrder::pushButtonOK_clicked()
{
/*****************************************/    
/*                        Godkänn plockningen 	 */
/*   Uppdataera kundorder och artikelregister      */    
/*   Skapa följesedel            			*/     
/*****************************************/     
    frmChgPlKundOrder::updateOrder();
}

void frmChgPlKundOrder::pushButtonNext_clicked()
{
    pushButtonOK->setEnabled(TRUE);
    lineEditOrderNr->setFocus();
}

void frmChgPlKundOrder::GetOrderHeader()
{
/************************************************************************/
/*	Hämta orderhuvud, ORDERREG	 				*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);

	inrad="";
	errorrad="";
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "ORDDSP");	// OLFIX funktion
	process->addArgument(kundordernr);

	frmChgPlKundOrder::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(DataOnStdout() ) );
	frmChgPlKundOrder::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(DataOnStderr() ) );
            frmChgPlKundOrder::connect( process, SIGNAL(processExited() ),this, SLOT(OrderHuvudEndOfProcess() ) );
	    
	if (kundordernr == ""){
    	    QMessageBox::warning( this, "PLCHGW",
                      "Inköpsordernr saknas! \n" );
	    lineEditOrderNr->setFocus();
	}else {
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/ORDDSP!\n");
		QMessageBox::warning( this, "PLCHGW",
                            "Kan inte starta STYRMAN/ORDDSP! \n" );
	    }
	}
}

void frmChgPlKundOrder::GetOrderRow()
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
	process->addArgument( "ORDRDSP");	// OLFIX funktion
	process->addArgument(kundordernr);

	frmChgPlKundOrder::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(DataOnStdout() ) );
	frmChgPlKundOrder::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(DataOnStderr() ) );
            frmChgPlKundOrder::connect( process, SIGNAL(processExited() ),this, SLOT(RaderEndOfProcess() ) );

	if (kundordernr == ""){
    	    QMessageBox::warning( this, "PLCHGW",
                      "Kundorder saknas! \n" );
	}else {
	    if ( !process->start() ) {
		// error handling
		QMessageBox::warning( this, "PLCHGW",
                            "Kan inte starta STYRMAN/ORDRDSP! \n" );
	    }
	}
}

void frmChgPlKundOrder::OrderHuvudEndOfProcess()
{
    int i,m;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
 //   qDebug("Error:",errorrad);
    if (i != -1) {
	QMessageBox::critical( this, "PLCHGW",
		"ERROR!\n"+errorrad
	);
    }else{
	i = -1;
	i = inrad.find( QRegExp("OK:"), 0 );
	if (i != -1) {
	    int i1 = inrad.find( QRegExp("01:"), 0 );		// kundordernr
	    int i2 = inrad.find( QRegExp("02:"), 0 );		// kundnr
	    int i3 = inrad.find( QRegExp("03:"), 0 );		// ordertyp
	    int i4 = inrad.find( QRegExp("04:"), 0 );		// orderstatus
	    int i5 = inrad.find( QRegExp("05:"), 0 );		// orderdatum
	    int i6 = inrad.find( QRegExp("06:"), 0 );		// leveransdatum
	    int i7 = inrad.find( QRegExp("07:"), 0 );		// kundnamn
	    int i8 = inrad.find( QRegExp("08:"), 0 );		// kundadr
	    int i9 = inrad.find( QRegExp("09:"), 0 );		// kundpostnr
	    int i10 = inrad.find( QRegExp("10:"), 0 );		// kundpostadress
	    int i11 = inrad.find( QRegExp("11:"), 0 );		// kundland
	    int i12 = inrad.find( QRegExp("12:"), 0 );		// erref
	    int i13 = inrad.find( QRegExp("13:"), 0 );		// leveransadress
	    int i14 = inrad.find( QRegExp("14:"), 0 );		// leveranspostnr
	    int i15 = inrad.find( QRegExp("15:"), 0 );		// leveranspostadress
	    int i16 = inrad.find( QRegExp("16:"), 0 );		// leveransland
	    int i17 = inrad.find( QRegExp("17:"), 0 );		// varref
	    int i18 = inrad.find( QRegExp("18:"), 0 );		// seljare
	    int i19 = inrad.find( QRegExp("19:"), 0 );		// godsmärke
	    int i20 = inrad.find( QRegExp("20:"), 0 );		// betalningsvillkorstyp
	    int i21 = inrad.find( QRegExp("21:"), 0 );		// betalningsvillkor
	    int i22 = inrad.find( QRegExp("22:"), 0 );		// leveransvillkor
	    int i23 = inrad.find( QRegExp("23:"), 0 );		// leveranssätt
	    int i24 = inrad.find( QRegExp("24:"), 0 );		// plocklista (J/N)
	    int i25 = inrad.find( QRegExp("25:"), 0 );		// följesedel (J/N)
	    int i26 = inrad.find( QRegExp("26:"), 0 );		// frasktavgift (J/N)
	    int i27 = inrad.find( QRegExp("27:"), 0 );		// skattekod
	    int i28 = inrad.find( QRegExp("28:"), 0 );		// moms i %
	    int i29 = inrad.find( QRegExp("29:"), 0 );		// valuta
	    int i30 = inrad.find( QRegExp("30:"), 0 );		// exportkod
	    int i31 = inrad.find( QRegExp("31:"), 0 );		// språkkod
	    int i32 = inrad.find( QRegExp("32:"), 0 );		// ordersumms exklusive moms
	    int i33 = inrad.find( QRegExp("33:"), 0 );		// fraktsumma exklusive moms
	    int i34 = inrad.find( QRegExp("34:"), 0 );		// moms på fraktsumma
	    int i35 = inrad.find( QRegExp("35:"), 0 );		// moms totalt på order
	    int i36 = inrad.find( QRegExp("36:"), 0 );		// ordersumma inklusive moms
	    int i37 = inrad.find( QRegExp("END:"), 0 );

	    m=i2-i1;
	    if (i1 != -1){
		ordernr=inrad.mid(i1+3,m-4);		// kundordernr
	    }

	    m=i3-i2;
	    if (i2 != -1){
	  	kundnr=inrad.mid(i2+3,m-4);		// kundnr
	    }

	    m=i4-i3;
	    if (i3 != -1){
		ordertyp=inrad.mid(i3+3,m-4);		// ordertyp
	    }

	    m=i5-i4;
	    if (i4 != -1){
		orderstatus=inrad.mid(i4+3,m-4);		// orderstatus
		lineEditOrderstatus->setText(orderstatus);
	    }

	    m=i6-i5;
	    if (i5 != -1){
		orderdatum=inrad.mid(i5+3,m-4);		// orderdatum
	    }

	    m=i7-i6;
	    if (i6 != -1){
		leveransdatum=inrad.mid(i6+3,m-4);	// leveransdatum
	    }
/*************************************************************************/
/*	    kundnamn, kundadress, kundpostnr, kundpostadress och kundland 	*/
/*	    är faktura adress och skrivs inte ut på plocklistan.                                         */
/*************************************************************************/	    
	    m=i8-i7;
	    if (i7 != -1){
		kundnamn=inrad.mid(i7+3,m-4);		// kundnamn
	    }

	    m=i9-i8;
	    if (i8 != -1){
		kundadr=inrad.mid(i8+3,m-4);		// kundadress
	    }

	    m=i10-i9;
	    if (i9 != -1){
		kundpostnr=inrad.mid(i9+3,m-4);		// kundpostnr
	    }

	    m=i11-i10;
	    if (i10 != -1){
		kundpostadr=inrad.mid(i10+3,m-4);	// kundpostadress
	    }

	    m=i12-i11;
	    if (i11 != -1){
		kundland=inrad.mid(i11+3,m-4);		// kundland
	    }

	    m=i13-i12;
	    if (i12 != -1){
		erref=inrad.mid(i12+3,m-4);		// erref
	    }

	    m=i14-i13;
	    if (i13 != -1){
		leveransadress=inrad.mid(i13+3,m-4);	// leveransadress
	    }

	    m=i15-i14;
	    if (i14 != -1){
		leveranspostnr=inrad.mid(i14+3,m-4);	// leveranspostnr
	    }

	    m=i16-i15;
	    if (i15 != -1){
		leveranspostadress=inrad.mid(i15+3,m-4);	// leveranspostadress
	    }

	    m=i17-i16;
	    if (i16 != -1){
		leveransland=inrad.mid(i16+3,m-4);	// leveransland
	    }

	    m=i18-i17;
	    if (i17 != -1){
		varref=inrad.mid(i17+3,m-4);		// vår referent, används inte, använder seljare istället
	    }

	    m=i19-i18;
	    if (i18 != -1){
		seljare=inrad.mid(i18+3,m-4);		// placeras som vår referent på blanketten
	    }

	    m=i20-i19;
	    if (i19 != -1){
		godsmerke=inrad.mid(i19+3,m-4);		// Godsmärke
	    }

/*************************************************************************/
/*	    betalningsvillkorstyp, betalningsvillkor, leveransvillkor, leveranssätt,	*/
/*	    plocklista, följesedel, fraktavgift, skattekod, moms, valuta, exportkod,	*/	    
/*	    språkkod, ordersumma, fraktsumma, fraktmoms, moms och ordertotal	*/	    	    
/*	    skrivs inte ut på plocklistan			                                 */
/*************************************************************************/	    
	    
	    
	    m=i21-i20;
	    if (i20 != -1){
//		temp=inrad.mid(i20+3,m-4);		// Betalningsvillkorstyp
	    }
	    
	    m=i22-i21;
	    if (i21 != -1){
//		betvillkor=inrad.mid(i21+3,m-4);		// Betalningsvillkor
	    }

	    m=i23-i22;
	    if (i22 != -1){					// Leveransvillkor
//		levvillkor=inrad.mid(i22+3,m-4);
	    }
	    
	    m=i24-i23;
	    if (i23 != -1){					// Leveranssätt
//		levsett=inrad.mid(i23+3,m-4);
	    }

	    m=i25-i24;
	    if (i24 != -1){					// Plocklista (J/N)
//		temp=inrad.mid(i24+3,m-4);
	    }
	    
	    m=i26-i25;
	    if (i25 != -1){					// Följesedel (J/N)
//		temp=inrad.mid(i25+3,m-4);
	    }
	    	    
	    m=i27-i26;				
	    if (i26 != -1){					// Fraktavgift (J/N)
//		temp=inrad.mid(i26+3,m-4);
	    }
	    
	    m=i28-i27;
	    if (i27 != -1){					// Skattekod
//		temp=inrad.mid(i27+3,m-4);
	    }
	    
	    m=i29-i28;
	    if (i28 != -1){
//		moms=inrad.mid(i28+3,m-4);		// Moms i procent
	    }
	    
	    m=i30-i29;
	    if (i29 != -1){					// Valuta
//		valuta=inrad.mid(i29+3,m-4);
	    }
	    
	    m=i31-i30;
	    if (i30 != -1){
//		exportkod=inrad.mid(i30+3,m-4);		// Exportkod
	    }
	    
	    m=i32-i31;
	    if (i31 != -1){					// Språkkod
//		temp=inrad.mid(i31+3,m-4);
	    }
	    
	    m=i33-i32;
	    if (i32 != -1){					// Ordersumma exklusive moms
//		temp=inrad.mid(i32+3,m-4);
	    }
	    
	    m=i34-i33;
	    if (i33 != -1){					// Fraktsumma exklusive moms
//		temp=inrad.mid(i33+3,m-4);
	    }
	    
	    m=i35-i34;
	    if (i34 != -1){					// Moms i kronor på fraktkostnaden
//		temp=inrad.mid(i34+3,m-4);
	    }
	    
	    m=i36-i35;
	    if (i35 != -1){					// Moms totalt på ordern
//		temp=inrad.mid(i35+3,m-4);
	    }
	    
	    m=i37-i36;
	    if (i36 != -1){					// Ordersumma inklusive moms
//		temp=inrad.mid(i36+3,m-4);
	    }
	    
	    inrad="";
	    errorrad="";
	    inrad="";
	    i = -1;
	}	
    }
    errorrad="";
    
    frmChgPlKundOrder::GetOrderRow();
}

void frmChgPlKundOrder::RaderEndOfProcess()
{
    QListViewItem * item;
    QString orderradnr;
    QString orderartikelnr;
    QString prodklass;
    QString orderbenamn;
    QString radleveransvecka;
    QString orderantal;
    QString orderradpris;
    QString radbelopp;
    QString radmoms;		/*  Moms på radbelopp */
    QString attlev;
    int attleverera;			/* Temporär variabel för beräkning */

    varv=varv+1;			/* varv används enbart för felsökning */
//   qDebug("RaderEndOfProcess::inrad=%s",inrad.latin1());
    int i,m,n;
    QString tmp;

    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "PLCHGW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
    }else{
     i = -1;
     i = inrad.find( QRegExp("OK:"), 0 );
//     qDebug("RaderEndOfProcess:: i=%d, varv=%d",i,varv);
     if (i != -1) {
	 
	 int p1 = inrad.find( QRegExp("OK:"), 0 );
	 int p2 = inrad.find( QRegExp("_:_ 02"), 0 );
	 int n1=(p2)-(p1+3);
	 tmp=inrad.mid(p1+3,n1);
	 int n2=tmp.toInt();
	 int m1=0;
//	 qDebug("m1=%d",m1);
//	 qDebug("p1=%d p2=%d n1=%d tmp=%s n2=%d",p1,p2,n1,tmp.latin1(),n2);
	 for (n=1;n<=n2;n++){
//	     qDebug("m1=%d",m1);
	     int i2 = inrad.find( QRegExp("02_:_ "), m1 );		// radnr
//	     qDebug("i2=%d",i2);
	     int i3 = inrad.find( QRegExp("_:_03_:_"), m1 );		// kundnr
	     int i4 = inrad.find( QRegExp("_:_04_:_"), m1 );		// radtyp
	     int i5 = inrad.find( QRegExp("_:_05_:_"), m1 );		// artikelnr
	     int i6 = inrad.find( QRegExp("_:_06_:_"), m1 );		// benämning
	     int i7 = inrad.find( QRegExp("_:_07_:_"), m1 );		// leveransvecka
	     int i8 = inrad.find( QRegExp("_:_08_:_"), m1 );		// antal
	     int i9 = inrad.find( QRegExp("_:_09_:_"), m1 );		// apris
	     int i10 = inrad.find( QRegExp("_:_10_:_"), m1 );		// summa rad, belopp exklusive moms
//	     qDebug("i10=%d",i10);
	     int i11 = inrad.find( QRegExp("_:_11_:_"), m1 );
	     int i12 = inrad.find( QRegExp("_:_12_:"), m1 );
	     int i13 = inrad.find( QRegExp("_:_13_:"), m1 );
	     int i14 = inrad.find( QRegExp("_:_14_:"), m1 );
	     int i15 = inrad.find( QRegExp("_:_15_:_"), m1 );
	     int i16 = inrad.find( QRegExp("_:_16_:_"), m1 );
	     int i17 = inrad.find( QRegExp("_:_17_:_"), m1 );
	     int i18 = inrad.find( QRegExp("_:_NEXT_:_"), m1 );
//	     qDebug("i18 /next/=%d",i18);
//	     int i19 = inrad.find( QRegExp("END"), 0 );
	     m1=i18+10;
	     m=(i3)-(i2+5);
	     orderradnr=inrad.mid(i2+5,m);
//	     qDebug("i2=%d i3=%d m=%d  i18=%d\n m1=%d",i2,i3,m,i18,m1);
//	     qDebug("orderradnr=%s ",orderradnr.latin1());
	     m=(i4-3)-(i3+5);
	     tmp=inrad.mid(i3+8,m);
//	     qDebug("kundnr=%s ",tmp.latin1());
	     m=(i5-3)-(i4+5);
	     tmp=inrad.mid(i4+8,m);
//	     qDebug("radordertyp=%s ",tmp.latin1());
	     m=(i6-3)-(i5+5);
	     orderartikelnr=inrad.mid(i5+8,m);
//	     qDebug("orderartikelnr=%s ",orderartikelnr.latin1());
	     m=(i7-3)-(i6+5);
	     orderbenamn=inrad.mid(i6+8,m);
//	     qDebug("benämning=%s",orderbenamn.latin1());
	     m=(i8-3)-(i7+5);
	     radleveransvecka=inrad.mid(i7+8,m);
//	     qDebug("radleveransvecka=%s",radleveransvecka.latin1());
	     m=(i9-3)-(i8+8);
	     orderantal=inrad.mid(i8+8,m);				// antal
//	     qDebug("orderantal=%s",orderantal.latin1());
	     m=(i10)-(i9+8);
	     orderradpris=inrad.mid(i9+8,m);			// apris
//	     qDebug("orderradpris=%s",orderradpris.latin1());
	     m=(i11)-(i10 + 8);
	     radbelopp=inrad.mid(i10 + 8,m);			// summa exklusive moms
//	     qDebug("radbelopp=%s",radbelopp.latin1());
	     m=(i12 - 3)-(i11 + 8);
	     radmoms=inrad.mid(i11 + 8,m);				// moms i kronor
//	     qDebug("radmoms=%s",radmoms.latin1());
	     m=(i13 - 3)-(i12 + 8);
	     tmp=inrad.mid(i12 + 8,m);				// levererat antal
//	     qDebug("levererat antal=%s",tmp.latin1());
	     m=(i14 - 3)-(i13 + 8);					// restnoterat
	     restnoterat=inrad.mid(i13 + 8,m);
	     if(restnoterat.toInt() > 0){
		  attleverera=restnoterat.toInt()-tmp.toInt();
	      }else{
		  attleverera=orderantal.toInt()-tmp.toInt();
	      }
	     attlev=attlev.setNum(attleverera);
//	     qDebug("orderantal=%s restnoterat antal=%s attleverera=%d attlev=%s",orderantal.latin1(),tmp.latin1(),attleverera,attlev.latin1());
	     m=(i15 )-(i14 + 8);					// radrabatt
	     tmp=inrad.mid(i14 + 8,m);
//	     qDebug("radrabatt=%s",tmp.latin1());
	     m=(i16)-(i15 + 8);					// kalkylpris
	     tmp=inrad.mid(i15 + 8,m);
//	     qDebug("kalkylpris=%s",tmp.latin1());
	     m=(i17)-(i16 + 8);					// leveransdatum för orderrad
	     tmp=inrad.mid(i16 + 8,m);
//	     qDebug("leveransdatum=%s",tmp.latin1());
	     m=(i18 - 3)-(i17 +8);					// enhet
	     tmp=inrad.mid(i17 + 8,m);
//	     qDebug("enhet=%s",tmp.latin1());
	     
//               item = new QListViewItem(listViewRader,orderradnr,orderartikelnr,orderbenamn,radleveransvecka,orderantal,restnoterat);
	      item = new QListViewItem(listViewRader,orderradnr,orderartikelnr,orderbenamn,radleveransvecka,orderantal,attlev);
	    }
	}
 }
}

void frmChgPlKundOrder::DataOnStdout()
{
     while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmChgPlKundOrder::DataOnStderr()
{
      while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmChgPlKundOrder::GetReportDir()
{
    QString hemkatalog;
    QString olfixrcfile;	// filen $HOME/.olfixrc

    bool status;
    int i = -1;
    //	Hämta sökvägen till kugar template. Default /usr/local/olfix/report
    //	Hämtas från .olfixrc
    hemkatalog=QDir::homeDirPath ();
    olfixrcfile=hemkatalog+"/.olfixrc";
    QFile file(olfixrcfile);
    status=file.open(IO_ReadOnly);
    QTextStream stream( &file );
    while ( !stream.eof() ) {
	inrad = stream.readLine();
	i = inrad.find( QRegExp("REPORT="), 0 );
	if(i == 0){
	    reportpath=inrad.mid(7,inrad.length()-7);
//	    qDebug("reportpath=%s",reportpath.latin1());
	    i= -1;
	}
    }   
    file.close ();
//    qDebug("reportpath=  %s",reportpath.latin1());
}

void frmChgPlKundOrder::checkStatus()
{
/************************************************************************/
/*	Kontrollera vilken staus en order har	 				*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);

	inrad="";
	errorrad="";
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "ORDCHK");	// OLFIX funktion
	process->addArgument("2");		// check orderstatus
	process->addArgument(kundordernr);

	frmChgPlKundOrder::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(DataOnStdout() ) );
	frmChgPlKundOrder::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(DataOnStderr() ) );
            frmChgPlKundOrder::connect( process, SIGNAL(processExited() ),this, SLOT(CheckOrderEndOfProcess() ) );
	    
	if (kundordernr == ""){
    	    QMessageBox::warning( this, "PLCHGW",
                      "Kundordernummer saknas! \n" );
	    lineEditOrderNr->setFocus();
	}else {
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/ORDCHK!\n");
		QMessageBox::warning( this, "PLCHGW",
                            "Kan inte starta STYRMAN/ORDCHK! \n" );
	    }
	}
}

void frmChgPlKundOrder::CheckOrderEndOfProcess()
{
    int i,m;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
 //   qDebug("Error:",errorrad);
    if (i != -1) {
	QMessageBox::critical( this, "PLCHGW",
		"ERROR!\n"+errorrad
	);
    }else{
	i = -1;
	i = inrad.find( QRegExp("OK:"), 0 );
	if (i != -1) {
	    int i1 = inrad.find( QRegExp("_:_1_:_"), 0 );		
	    int i2 = inrad.find( QRegExp("_:_"), 13 );			 
	    m=i2-(i1+7);
	    if (i1 != -1){
		orderstatus=inrad.mid(i1+7,m);			// orderstatus
		lineEditOrderstatus->setText(orderstatus);
//		qDebug("i1=%d i2=%d m=%d",i1,i2,m);
	    }
	}
    }
    if (orderstatus=="B"){
	    	    QMessageBox::warning( this, "PLCHGW",
                      "Ordern är avslutad! \n" );
	    lineEditOrderNr->setSelection(0,kundordernr.length());
	    lineEditOrderNr->setFocus();
    }else{
	    frmChgPlKundOrder::GetOrderHeader();
    }
}

void frmChgPlKundOrder::listViewRader_format()
{
    listViewRader->setColumnWidth(0,44);		// Radnr
    listViewRader->setColumnWidth(1,180);		// Artikelnr
    listViewRader->setColumnWidth(2,295);		// Benämning
    listViewRader->setColumnWidth(3,100);		// Leveransvecka
    listViewRader->setColumnWidth(4,90);		// Beställt antal
    listViewRader->setColumnWidth(5,75);		// Antal att leverera
    listViewRader->setColumnWidth(6,86);		// Plockat antal
//    listViewRader->setColumnWidth(7,86);		// Moms
}

void frmChgPlKundOrder::listViewRader_clicked( QListViewItem * )
{
    radnrflag=TRUE;
    oldradnr=orderradnr;
    QListViewItem *item =  listViewRader->currentItem();
    if ( !item )
	return;
    item->setSelected( TRUE );
    QString temp0=item->text(0);	// radnr
    QString temp1=item->text(1);	// artikelnr
    QString temp2=item->text(2);	// artikelbenämning
    QString temp3=item->text(3);	// leveransvecka
    QString temp4=item->text(4);	// Beställt antal
    QString temp5=item->text(5);	// Antal att leverera
    QString temp6=item->text(6);	// Plockat antal
    //    qDebug("temp=%s, %s, %s, %s, %s, %s",temp0.latin1(),temp1.latin1(),temp2.latin1(),temp3.latin1(),temp4.latin1(),temp5.latin1());
    // --------------------------------------------------------------
    lineEditRadnr->setText(temp0);
    orderradnr=temp0;
    lineEditArtikelNr->setText(temp1);
    lineEditBenamn->setText(temp2);
    lineEditLeveransvecka->setText(temp3);
    lineEditAntal->setText(temp4);
    lineEditAntalAtt_Leverera->setText(temp5);
    lineEditPlockatAntal->setText(temp6);
    lineEditPlockatAntal->setFocus();
    delete listViewRader->currentItem();
}

void frmChgPlKundOrder::pushBtnOKRad_clicked()
{
    QListViewItem * item;
    int i;
    orderartikelnr=lineEditArtikelNr->text();
    orderbenamn=lineEditBenamn->text();
    radleveransvecka=lineEditLeveransvecka->text();
    orderantal=lineEditAntal->text();
    attleverera=lineEditAntalAtt_Leverera->text();
    plockatantal=lineEditPlockatAntal->text();
    
//    qDebug("rad=%s %s %s %s %s",orderradnr.latin1(),orderartikelnr.latin1(),orderbenamn.latin1(),radleveransvecka.latin1(),orderantal.latin1());
    
    item = new QListViewItem(listViewRader,orderradnr,orderartikelnr,orderbenamn,radleveransvecka,orderantal,attleverera,plockatantal);
    if (radnrflag == FALSE){
	i = orderradnr.toInt();
	i = i+10;
	orderradnr=QString::number(i,10);
	if (orderradnr.length() <3){
	    orderradnr="0"+orderradnr;
	}
    }else{
	orderradnr=oldradnr;
	radnrflag=FALSE;
    }
    
    /* Nästa orderrad 	*/
    lineEditRadnr->setText("000");
    lineEditArtikelNr->clear();
    lineEditBenamn->clear();
    lineEditLeveransvecka->clear();    
    lineEditAntal->clear();
    lineEditAntalAtt_Leverera->clear();
    lineEditPlockatAntal->clear();
    orderartikelnr="";
    orderbenamn="";
    orderantal="";
    
//    lineEditArtikelNr->setFocus();
}

void frmChgPlKundOrder::pushBtnHelp_clicked()
{
	inrad="";
	frmChgPlKundOrder::readResursFil();		// Hämta path till hjälpfilen

	int i1 = hjelpfil.find( QRegExp(".html"), 0 );
//	int i2 = hjelpfil.length();
	hjelpfil=hjelpfil.left(i1);
	hjelpfil=hjelpfil+"_KUNDORDER.html";
	hjelpfil=hjelpfil+"#PLOCK2";		// Lägg till position
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

void frmChgPlKundOrder::readResursFil()
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

void frmChgPlKundOrder::updateOrder()
{
    QString ordernum;
    QString artikelnr;
    QString radnum;
    QString levantal;
    QString restantal;
    QString trhddata;
    double rest;
    double lev;
    
    
   QListViewItem *item =  listViewRader->firstChild();
   while(item){
       ordernum= ordernr;
       radnum=item->text(0); 
       artikelnr=item->text(1);
       artikelnr = artikelnr.stripWhiteSpace();
       levantal=item->text(6);
       restantal=item->text(5);
       rest=restantal.toDouble();
       lev=levantal.toDouble();
       rest=rest-lev;
       restantal=restantal.setNum(rest,'f',2);
//       qDebug("ordernum=%s, radnum=%s, levantal=%s, restantal=%s",ordernum.latin1(),radnum.latin1(),levantal.latin1(),restantal.latin1());
       changeOrder(ordernum,radnum,levantal,restantal);
       ARregUpdate("4",artikelnr,levantal);	/* minska lagersaldo med plockat antal  */
       trhddata="lagersaldo - "+levantal;
       TRHDregAdd(trhddata );
       ARregUpdate("2",artikelnr,levantal);	/* minska reserverat antal med plockat antal  */
       trhddata="reserverat antal - "+levantal;
       TRHDregAdd(trhddata );
       item=item->nextSibling ();
   }
   pushButtonOK->setEnabled(FALSE);  /* Kan inte uppdatera samma order flera gånger */
}

void frmChgPlKundOrder::changeOrder( QString ordernum,QString radnum,QString levantal,QString restantal)
{
	const char *userp = getenv("USER");
            QString usr(userp);
/*            qDebug("ordernum=%s, radnum=%s, levantal=%s, restantal=%s",ordernum.latin1(),radnum.latin1(),levantal.latin1(),restantal.latin1());  */

	inrad="";
	errorrad="";
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "ORDRUPD");	// OLFIX funktion
	process->addArgument(ordernum);
	process->addArgument(radnum);
	process->addArgument(levantal);
	process->addArgument(restantal);

	frmChgPlKundOrder::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(DataOnStdout() ) );
	frmChgPlKundOrder::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(DataOnStderr() ) );
            frmChgPlKundOrder::connect( process, SIGNAL(processExited() ),this, SLOT(OrderUpdateEndOfProcess() ) );
	    
	if ( !process->start() ) {
		// error handling
		QMessageBox::warning( this, "PLCHGW",
                            "Kan inte starta STYRMAN/ORDRUPD! \n" );
	    }
}

void frmChgPlKundOrder::OrderUpdateEndOfProcess()
{
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
 //   qDebug("Error:",errorrad);
    if (i != -1) {
	QMessageBox::critical( this, "PLCHGW",
		"ERROR!\n"+errorrad
	);
    } 
}
 

void frmChgPlKundOrder::ARregUpdate( QString val, QString artikelnr, QString data )
{
	/* Uppdatera artikelregistret, ARTIKELREG */
	const char *userp = getenv("USER");
            QString usr(userp);

//	qDebug("val=%s, artikelnr=%s, data=%s",val.latin1(),artikelnr.latin1(),data.latin1());
	 
	inrad="";
	errorrad="";
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "AR2UPD");	// OLFIX funktion
	process->addArgument(val);
	process->addArgument(artikelnr);
	process->addArgument(data);

	frmChgPlKundOrder::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(DataOnStdout() ) );
	frmChgPlKundOrder::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(DataOnStderr() ) );
            frmChgPlKundOrder::connect( process, SIGNAL(processExited() ),this, SLOT(ARregUpdateEndOfProcess() ) );
	    
	if ( !process->start() ) {
		// error handling
		QMessageBox::warning( this, "PLCHGW",
                            "Kan inte starta STYRMAN/AR2UPD! \n" );
	    }
}

void frmChgPlKundOrder::ARregUpdateEndOfProcess()
{
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
 //   qDebug("Error:",errorrad);
    if (i != -1) {
	QMessageBox::critical( this, "PLCHGW",
		"ERROR!\n"+errorrad
	);
    } 
}

void frmChgPlKundOrder::TRHDregAdd(QString trnsdata )
{
	/* Uppdatera artikelregistret, TRHD, historikregistret*/
	const char *userp = getenv("USER");
            QString usr(userp);
	QString tidpunkt;
	QDateTime dt = QDateTime::currentDateTime();
	tidpunkt=dt.toString ( "yyyy-MM-dd hh:mm:ss" );
	
//	qDebug("val=%s, artikelnr=%s, data=%s",val.latin1(),artikelnr.latin1(),data.latin1());
	 
	inrad="";
	errorrad="";
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "TRHDADD");	// OLFIX funktion
	process->addArgument("AR2UPD");	// TRNSID
	process->addArgument(tidpunkt);
	process->addArgument(usr);
	process->addArgument(trnsdata);

	frmChgPlKundOrder::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(DataOnStdout() ) );
	frmChgPlKundOrder::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(DataOnStderr() ) );
            frmChgPlKundOrder::connect( process, SIGNAL(processExited() ),this, SLOT(TRHDregAddEndOfProcess() ) );
	    
	if ( !process->start() ) {
		// error handling
		QMessageBox::warning( this, "PLCHGW",
                            "Kan inte starta STYRMAN/TRHDADD! \n" );
	    }
}

void frmChgPlKundOrder::TRHDregAddEndOfProcess()
{
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
 //   qDebug("Error:",errorrad);
    if (i != -1) {
	QMessageBox::critical( this, "PLCHGW",
		"ERROR!\n"+errorrad
	);
    } 
}
