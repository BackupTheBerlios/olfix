/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
/***************************************************************************
			  KUFAKTW  -  Fakturera kundorder
			 KundFaktura
			     -------------------
		     version 0.4.3
    begin     		: Mån  30 okt     2005
    modified		: Sön   16 april 2006
    copyright            	: (C) 2005 by Jan Pihlgren
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
#include <math.h>
#include <qstring.h>
#include <qfile.h>
#include <qregexp.h>
#include <qdatetime.h>
#include <qcheckbox.h>
#include <qthread.h> 
#define MAXSTRING 15000

QProcess* process;
QProcess* proctrhd;
QProcess* procfaktura;
QProcess* prockresk;
QProcess* procorder;
QProcess* procorad;

QString inradfaktura;
QString errorradfaktura;
QString inradtrhd;
QString errorradtrhd;
QString inradkresk;
QString errorradkresk;
QString inradorder;
QString errorradorder;
QString inradorderrad;
QString errorradorderrad;

QString inrad;
QString inradny;
QString* rad;
QString errorrad;
QString errorradny;
QString listerrorrad;
QString listinrad;
QString inradftg;
QString errorradftg;
QString betinrad;
QString beterrorrad;
QString faktinrad;
QString fakterrorrad;
QString hjelpfil;
int varv=0;

QString kundordernr;
QString reportpath;
QString tmppath="/tmp/";
QString kugarversion;
QString kommando;
QString fakturafil="KuOrderFaktura.kud";
QString templatefile="KuOrderFaktura.kut";

//	Orderhuvud    
QString ordernr;			// 01
QString ordertyp;			// 02
QString orderdatum;		// 03
QString leveransdatum;
QString fakturadatum;
QString expdatum;		// Förfallodatum (expiredate)
QString kundnr;			// 04
QString kundnamn;		// 05
QString kundadr;			// 06
QString kundpostnr;		// 07
QString kundpostadr;		// 08
QString kundland;		// 09
QString erref;			// 20
QString leveransadress;
QString leveranspostnr;
QString leveranspostadress;
QString leveransland;
QString valuta;			// 10
QString betvillkor;		// 11
QString betalningsdagar;
QString betvilkbeskriv;
QString levvillkor;		// 12
QString levsett;			// 13
QString godsmerke;		// 14
QString besttext;			// 16
QString varref;			// 17
QString seljare;
QString exportkod;
QString moms;			// 28 ******* 
QString levdatum;		// 21
QString kundnum;		// 22
QString ftgnamn;			// 23
QString ftgadr;			// 24
QString ftgpostnr;		// 25
QString ftgpostadr;		// 26
QString sprakkod;		// 27
QString bekreftad;		// 28
QString orderstatus;		// 29
QString utskriftkod;		// 30
QString total;			// 31
QString ftgtfn;
//  -----------------------------
QString temp;
QString ftgland;
QString restnoterat;
//  -----------------------------    
bool radnrflag=FALSE;
QString orderartikelnr;
QString orderbenamn;
QString radantal;
QString orderantal;
QString radprisperst;
QString radtotal;
QString orderradnr="";
QString oldradnr;
//  -----------------------------    
QString radrest;
QString radmomsprocent;
QString fakturanr;
QString fakturanrflag ="1" ;			// fakturanrflag = flagga för flera fakturanrserier  
QString kureskpost;

void frmKundFaktura::init()
{
    int dag;
    
    QDateTime dt = QDateTime::currentDateTime();
    dag= QDate::currentDate().dayOfWeek();
    fakturadatum=dt.toString("yyyy-MM-dd");
    textLabelFakturadatum->setText(fakturadatum);
    
//    QDateTime dt = QDateTime::currentDateTime();
    QDateTime nt = dt.addDays ( +30 );		// Dagens datum + 30 dagar    
    expdatum=nt.toString("yyyy-MM-dd");		// Förfallodatum
    lineEditExpiredate->setText(expdatum);
    
    radioButton1->setEnabled(FALSE);		// Sätts till TRUE om flera fakturanrserier
    radioButton2->setEnabled(FALSE);		// Sätts till TRUE om flera fakturanrserier

    frmKundFaktura::listViewRader_format();
    frmKundFaktura::GetReportDir();
    
    frmKundFaktura::listKundorder();		// Hämta alla icke avslutade kundordrar    
//    frmKundFaktura::getForetagsdata("FNAMN");	// Hämta företagsdata (bl a fakturanr
//   Måste ligga sist i  frmKundFaktura::ListaKundordrarEndOfProcess()  
    pushButtonOK->setEnabled(TRUE);
    lineEditOrderNr->setFocus();
}

void frmKundFaktura::lineEditOrderNr_returnPressed()
{
    listViewRader->clear();
    kundordernr=lineEditOrderNr->text();
    if (kundordernr != ""){
/*	QMessageBox::warning( this, "KUFAKTW",
			      "Kundorder saknas! \n" );
	lineEditOrderNr->setFocus();
    }else{
*/    
	frmKundFaktura::checkStatus();	//  Kontrollera status och hämta ordern.
	listViewRader->setFocus();
	listViewRader->firstChild ();
	listViewRader->setSelected(listViewRader->firstChild (),TRUE);
	pushButtonOK->setEnabled(TRUE);
    }else{
	lineEditOrderNr->setFocus();
    }
}

void frmKundFaktura::radioButton1_clicked()
{
    qDebug("radioButton1");
    fakturanrflag="1";
    frmKundFaktura::getForetagsdata("FAKNR");
    lineEditFakturanr->setText(fakturanr); 
}

void frmKundFaktura::radioButton2_clicked()
{
    qDebug("radioButton2");
    fakturanrflag="2";
    frmKundFaktura::getForetagsdata("FKNR2");
    lineEditFakturanr->setText(fakturanr); 
}

void frmKundFaktura::lineEditExpiredate_returnPressed()
{
 int flag=0;
 int i1,i2,i3;
 QString j1,j2;
 QString error="Felaktigt datumformat. YYYY-MM-DD";
    expdatum=lineEditExpiredate->text();
    i1=expdatum.mid(0,4).toInt();
    i2=expdatum.mid(5,2).toInt();
    i3=expdatum.mid(8,2).toInt();
    j1=expdatum.mid(4,1);
    j2=expdatum.mid(7,1);
    
    if (i1 < 2004){
	qDebug(error);
	flag=-1;
	lineEditExpiredate->setFocus();
    }
    if (i2>12){
	qDebug(error);
	flag=-1;
	lineEditExpiredate->setFocus();
    }
    if (i2<1){
	qDebug(error);
	flag=-1;
	lineEditExpiredate->setFocus();
    }
    if (i3>31){
	qDebug(error);
	flag=-1;
	lineEditExpiredate->setFocus();
    }
    if(i3<1){
	qDebug(error);
	flag=-1;
	lineEditExpiredate->setFocus();
    }
    if(j1 != "-"){
	qDebug(error);
	flag=-1;
	lineEditExpiredate->setFocus();
    }
    if (j2 != "-"){
	qDebug(error);
	flag=-1;
	lineEditExpiredate->setFocus();
    }
    if (flag == -1){
    	QMessageBox::warning( this, "KUFAKTW",
			      error+"! \n" );
	flag=0;
    }else{
	pushButtonKalkylera->setFocus();
    }
}

/*****************************************/
/*	Editering av fakturaadress                     */
/*****************************************/

void frmKundFaktura::lineEditKundNamn_returnPressed()
{
    kundnamn=lineEditKundNamn->text();
    lineEditKundNamn->setText(kundnamn);
}

void frmKundFaktura::lineEditKundAdress_returnPressed()
{
    kundadr=lineEditKundAdress->text();
    lineEditKundAdress->setText(kundadr);
}

void frmKundFaktura::lineEditKundPostnr_returnPressed()
{
    kundpostnr=lineEditKundPostnr->text();
    lineEditKundPostnr->setText(kundpostnr);
}

void frmKundFaktura::lineEditKundPostAdress_returnPressed()
{
    kundpostadr=lineEditKundPostAdress->text();
    lineEditKundPostAdress->setText(kundpostadr);
}

void frmKundFaktura::lineEditKundLand_returnPressed()
{
    kundland=lineEditKundLand->text();
    lineEditKundLand->setText(kundland);
}

void frmKundFaktura::lineEditKundRef_returnPressed()
{
    erref=lineEditKundRef->text();
    lineEditKundRef->setText(erref);
}

/*****************************************/
/*	Editering av fakturarader                       */
/*****************************************/
void frmKundFaktura::lineEditArtikelNr_returnPressed()
{
}

void frmKundFaktura::lineEditBenamn_returnPressed()
{
}

void frmKundFaktura::lineEditRadAntal_returnPressed()
{
    frmKundFaktura::CalculateRadtotal();
    pushBtnOKRad->setFocus();
//    lineEditRadRest->setFocus();
}

void frmKundFaktura::lineEditRadRest_returnPressed()
{
    frmKundFaktura::CalculateRadtotal();
    pushBtnOKRad->setFocus();
//    lineEditRadPris->setFocus();
}

void frmKundFaktura::lineEditRadPris_returnPressed()
{
    double belopp;
    QString kronor;
    belopp=lineEditRadPris->text().toDouble();
    kronor=kronor.setNum(belopp,'f',2);
    lineEditRadPris->setText(kronor);
    frmKundFaktura::CalculateRadtotal();
    lineEditRadMomsProcent->setFocus() ;
}

void frmKundFaktura::lineEditRadMomsProcent_returnPressed()
{
    double belopp;
    QString kronor;
    belopp=lineEditRadMomsProcent->text().toDouble();
    kronor=kronor.setNum(belopp,'f',2);
    lineEditRadMomsProcent->setText(kronor);
    frmKundFaktura::CalculateRadtotal();
    lineEditRadMomsKr->setFocus();
}

void frmKundFaktura::lineEditRadMomsKr_returnPressed()
{
    double belopp;
    QString kronor;
    belopp=lineEditRadMomsKr->text().toDouble();
    kronor=kronor.setNum(belopp,'f',2);
    lineEditRadMomsKr->setText(kronor);
    frmKundFaktura::CalculateRadtotal();
    lineEditRadtotal->setFocus();
}

void frmKundFaktura::lineEditRadtotal_returnPressed()
{
    double belopp;
    QString kronor;
    belopp=lineEditRadtotal->text().toDouble();
    kronor=kronor.setNum(belopp,'f',2);
    lineEditRadtotal->setText(kronor);
    //    frmKundFaktura::CalculateRadtotal();
    
    radtotal =lineEditRadtotal->text();
    pushBtnOKRad->setFocus();    
}

void frmKundFaktura::lineEditSumma_returnPressed()
{
    pushButtonKalkylera->setFocus();
}

void frmKundFaktura::lineEditFrakt_returnPressed()
{
    double belopp;
    QString kronor;
    belopp=lineEditFrakt->text().toDouble();
    kronor=kronor.setNum(belopp,'f',2);
    lineEditFrakt->setText(kronor);   
    lineEditFraktmoms->setFocus();
}

void frmKundFaktura::lineEditFraktmoms_returnPressed()
{
    double belopp;
    QString kronor;
    belopp=lineEditFraktmoms->text().toDouble();
    kronor=kronor.setNum(belopp,'f',2);
    lineEditFraktmoms->setText(kronor);
    pushButtonKalkylera->setFocus();
}

void frmKundFaktura::lineEditMoms_returnPressed()
{
    double belopp;
    QString kronor;
    belopp=lineEditFraktmoms->text().toDouble();
    kronor=kronor.setNum(belopp,'f',2);
    lineEditFraktmoms->setText(kronor);
    pushButtonKalkylera->setFocus();    
}

void frmKundFaktura::lineEditAvrundning_returnPressed()
{
    double belopp;
    QString kronor;
    belopp=lineEditAvrundning->text().toDouble();
    kronor=kronor.setNum(belopp,'f',2);
    lineEditAvrundning->setText(kronor);
    pushButtonKalkylera->setFocus();    
}


/*****************************************/
/*	Beräkning av radtotal                             */
/*****************************************/
void frmKundFaktura::CalculateRadtotal()
{
    QString summa;
    QString momskronor;				
    double pris,belopp,total,momskr;
    float momsproc,bestantal,levantal;
    
    bestantal=lineEditRadAntal->text().toFloat();
    levantal=lineEditRadRest->text().toFloat();	// ej fakturerat antal
    pris=lineEditRadPris->text().toDouble();
    momsproc=lineEditRadMomsProcent->text().toFloat();
    momskr=lineEditRadMomsKr->text().toDouble();
    belopp=(levantal * pris);
    momskronor=momskronor.setNum((belopp * momsproc / 100),'f',2);
    total=belopp+(belopp * momsproc / 100);
    summa=summa.setNum(total,'f',2);
    lineEditRadtotal->setText(summa);
    lineEditRadMomsKr->setText(momskronor);
}

void frmKundFaktura::pushButtonOK_clicked()
{
    /**********************************************/    
    /*                        Godkänn fakturan 		 	*/
    /*   Skapa fakturan            			*/
    /*   Uppdatera senast använda fakturanrserier	*/
    /*   Skapa post i Kundreskontraregistret KURESK	*/    
   /*   Skapa post i Kundreskontraregistret KURESK	*/
    /*   Uppdatera TRHD 				*/
    /*   Uppdataera kundorder, ORDERREG		*/    
    /*   Uppdataera kundorder, ORDERRADREG?	*/ 
    /*   Uppdataera kundorder, PLOCKLISTEREG	*/    
    /**********************************************/     
    qDebug("Start pushButtonOK_clicked()");
    frmKundFaktura::calculateFaktura();
    frmKundFaktura::createFaktura();		// Skapa och skriv ut en faktura med Kugar
//    qDebug("fakturanr=%s",fakturanr.latin1());
    frmKundFaktura::updateFakturanr();
    frmKundFaktura::createKURESKpost();		// Skapa en post i kundreskontran.
//						   Skapa en post i TRHD (görs efter createKURESKpost()
//						   KURESKposten måste vara klar först !  
    frmKundFaktura::updateOrderreg();		// Uppdatera ORDERSTATUS till F (fakturerat)
//
    qDebug("Slut pushButtonOK_clicked()");
}

void frmKundFaktura::pushButtonNext_clicked()
{
    pushButtonOK->setEnabled(TRUE);
    lineEditOrderNr->setFocus();
}

void frmKundFaktura::calculateFaktura()
{
    QString summa;
    QString antal;
    QString levant;
    QString styckpris;
    QString momsprocent;
    QString momstotal;
    QString fraktmoms;
    QString radsumma;
    QString netto;
    QString frakt;
 
    double moms;
    double momssumma=0;
    double radtotal=0;		// exkl moms
    double belopp;
    double nettosumma=0;
    double sum=0;
    double tmp;
   
    QListViewItem *myChild=listViewRader->firstChild ();    
    
    while( myChild ) {
	levant=myChild->text(4);
	styckpris=myChild->text(5);
	momsprocent=myChild->text(6);
	belopp=levant.toDouble() * styckpris.toDouble();
	moms=(momsprocent.toFloat() * belopp) / 100 ;
	momssumma=momssumma+moms;
	radtotal=radtotal+belopp;
	myChild=myChild->nextSibling();   
    }
    nettosumma=radtotal;				// nettobelopp, exkl moms
    netto=netto.setNum(nettosumma,'f',2);		// nettobelopp, exkl moms
    lineEditSumma->setText(netto);		            // nettobelopp, exkl moms	
    sum=sum+nettosumma;				// radsumma exkl moms
    frakt=lineEditFrakt->text();			// fraktkostnad exkl moms
    belopp=frakt.toDouble();    			// fraktkostnad exkl moms
    momsprocent=lineEditFraktmoms->text();		// moms i % för fraktkostnaden
    moms=(momsprocent.toFloat() * belopp) /100;     // moms i kr på frakten
    
    momssumma=momssumma+moms;		// fakturans totala moms i kr
    momstotal=momstotal.setNum(momssumma,'f',2);	// total moms för rader
    lineEditMoms->setText(momstotal);

    sum=sum+momssumma+belopp;			// totalbelopp på fakturan inkl moms
    tmp=sum-labs(sum);
    sum=sum-tmp;
//    qDebug("tmp=%f",tmp);
    lineEditAvrundning->setText(summa.setNum(-tmp,'f',2)); // Avrundning alltid negativ
    summa=summa.setNum(sum,'f',2);		// totalbelopp på fakturan inkl moms
    lineEditTotal->setText(summa);			// totalbelopp på fakturan inkl moms
    
}

void frmKundFaktura::createFaktura()
{
//    qDebug("tmppath=%s fakturafil=%s",tmppath.latin1(),fakturafil.latin1());
//    qDebug("ReportHeader");
    frmKundFaktura::CreateReportHeader();
//    qDebug("FakturaRad");
    frmKundFaktura::createFakturaRad();
//    qDebug("ReportFot");
    frmKundFaktura::CreateReportFot();
//    qDebug("KugarVersion");
    frmKundFaktura::KugarVersion();    
//    qDebug("CallKugar");
    frmKundFaktura::CallKugar();
}



void frmKundFaktura::GetOrderHeader()
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
    
    frmKundFaktura::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(DataOnStdout() ) );
    frmKundFaktura::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(DataOnStderr() ) );
    frmKundFaktura::connect( process, SIGNAL(processExited() ),this, SLOT(OrderHuvudEndOfProcess() ) );
    
    if (kundordernr == ""){
	QMessageBox::warning( this, "KUFAKTW",
			      "Inköpsordernr saknas! \n" );
	lineEditOrderNr->setFocus();
    }else {
	if ( !process->start() ) {
	    // error handling
	    fprintf(stderr,"Problem starta STYRMAN/ORDDSP!\n");
	    QMessageBox::warning( this, "KUFAKTW",
				  "Kan inte starta STYRMAN/ORDDSP! \n" );
	}
    }
}

void frmKundFaktura::GetOrderRow()
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
    
    frmKundFaktura::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(DataOnStdout() ) );
    frmKundFaktura::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(DataOnStderr() ) );
    frmKundFaktura::connect( process, SIGNAL(processExited() ),this, SLOT(RaderEndOfProcess() ) );
    
    if (kundordernr == ""){
	QMessageBox::warning( this, "KUFAKTW",
			      "Kundorder saknas! \n" );
    }else {
	if ( !process->start() ) {
	    // error handling
	    QMessageBox::warning( this, "KUFAKTW",
				  "Kan inte starta STYRMAN/ORDRDSP! \n" );
	}
    }
}

void frmKundFaktura::OrderHuvudEndOfProcess()
{
    int i,m;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    //   qDebug("Error:",errorrad);
    if (i != -1) {
	QMessageBox::critical( this, "KUFAKTW",
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
		lineEditKundnr->setText(kundnr);
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
		lineEditKundNamn->setText(kundnamn);
	    }
	    
	    m=i9-i8;
	    if (i8 != -1){
		kundadr=inrad.mid(i8+3,m-4);		// kundadress
		lineEditKundAdress->setText(kundadr);
	    }
	    
	    m=i10-i9;
	    if (i9 != -1){
		kundpostnr=inrad.mid(i9+3,m-4);		// kundpostnr
		lineEditKundPostnr->setText(kundpostnr);
	    }
	    
	    m=i11-i10;
	    if (i10 != -1){
		kundpostadr=inrad.mid(i10+3,m-4);	// kundpostadress
		lineEditKundPostAdress->setText(kundpostadr);
	    }
	    
	    m=i12-i11;
	    if (i11 != -1){
		kundland=inrad.mid(i11+3,m-4);		// kundland
		lineEditKundLand->setText(kundland);
	    }
	    
	    m=i13-i12;
	    if (i12 != -1){
		erref=inrad.mid(i12+3,m-4);		// erref
		lineEditKundRef->setText(erref);
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
		betvillkor=inrad.mid(i21+3,m-4);		// Betalningsvillkor
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
		moms=inrad.mid(i28+3,m-4);		// Moms i procent
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
//    qDebug("betvillkor=%s",betvillkor.latin1());
    frmKundFaktura::GetOrderRow();
}

void frmKundFaktura::RaderEndOfProcess()
{
    QListViewItem * item;
    QString orderradnr;
    QString orderartikelnr;
    QString prodklass;
    QString orderbenamn;
    QString radantal;
    QString orderantal;
    QString orderradpris;
    QString radbelopp;
    QString radmoms;		/*  Moms på radbelopp */
    QString levereratantal;
    QString attlev;
    QString levvecka;		/* ursprungligen lovad leveransvecka */
    QString faktureratantal;		/* tidigare fakturerat antal */
    QString momsprocent="25";
    QString fakturatotal;
    //    int radprisperst;		/* Temporär variabel för beräkning */
    double belopp;		/* Temporär variabel för beräkning */
    double momsen;		/* Temporär variabel för beräkning */
    double total=0;
    varv=varv+1;			/* varv används enbart för felsökning */
    //   qDebug("RaderEndOfProcess::inrad=%s",inrad.latin1());
    int i,m,n;
    QString tmp;
    
    momsprocent=moms;		/* moms från orderhuvudet */
    //    qDebug("moms=%s",moms.latin1());
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "KUFAKTW",
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
		int i8 = inrad.find( QRegExp("_:_08_:_"), m1 );		// beställt antal, ursprungligen
		int i9 = inrad.find( QRegExp("_:_09_:_"), m1 );		// apris
		int i10 = inrad.find( QRegExp("_:_10_:_"), m1 );		// summa rad, belopp exklusive moms
		int i11 = inrad.find( QRegExp("_:_11_:_"), m1 );
		int i12 = inrad.find( QRegExp("_:_12_:"), m1 );		// levererat antal
		int i13 = inrad.find( QRegExp("_:_13_:"), m1 );		// resterande antal
		int i14 = inrad.find( QRegExp("_:_14_:"), m1 );
		int i15 = inrad.find( QRegExp("_:_15_:_"), m1 );
		int i16 = inrad.find( QRegExp("_:_16_:_"), m1 );
		int i17 = inrad.find( QRegExp("_:_17_:_"), m1 );
		int i18 = inrad.find( QRegExp("_:_18_:_"),m1 );		//  fakturerat antal
		int i19 = inrad.find( QRegExp("_:_NEXT_:_"), m1 );	// postslut
		
		m1=i19+10;
		//	       2. radnummer	     	     
		m=(i3)-(i2+5);
		orderradnr=inrad.mid(i2+5,m);
		orderradnr=orderradnr.stripWhiteSpace();
		//	     qDebug("radnr: i2=%d, i3=%d, m=%d,radnr=%s,len=%d",i2,i3,m,inrad.mid(i2+5,m).latin1(),orderradnr.length());
		if (orderradnr.length()<3){
		    orderradnr="0"+orderradnr;
		}
		//	      3. kundnummer	     
		m=(i4-3)-(i3+5);
		tmp=inrad.mid(i3+8,m);
		//	      4. radordertyp	     
		m=(i5-3)-(i4+5);
		tmp=inrad.mid(i4+8,m);
		//	      5. artikelnr	     
		m=(i6-3)-(i5+5);
		orderartikelnr=inrad.mid(i5+8,m);
		//	      6. benämning
		m=(i7-3)-(i6+5);
		orderbenamn=inrad.mid(i6+8,m);
		//	      7. leveransvecka
		m=(i8-3)-(i7+5);
		levvecka=inrad.mid(i7+8,m);
		//	      8. antal						ursprungligen beställt antal 
		m=(i9-3)-(i8+8);
		orderantal=inrad.mid(i8+8,m);				// antal
		//	       9. pris per st
		m=(i10)-(i9+8);
		orderradpris=inrad.mid(i9+8,m);			// apris
		//	      10. radbelopp exkl moms
		m=(i11)-(i10 + 8);
		radbelopp=inrad.mid(i10 + 8,m);			// summa exklusive moms
		//	      11. radmoms i kr
		m=(i12 - 3)-(i11 + 8);
		radmoms=inrad.mid(i11 + 8,m);				// moms i kronor
		//	     momsen=radmoms.toDouble();
		//	     radmoms=radmoms.setNum(momsen,'f',2);		// få med ören
		//	      12. levererat antal
		m=(i13 - 3)-(i12 + 8);
		levereratantal=inrad.mid(i12 + 8,m);			// levererat antal
		//	      restnoterat antal
		m=(i14 - 3)-(i13 + 8);					// restnoterat
		restnoterat=inrad.mid(i13 + 8,m);
		
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
		//	      18. tidigare fakturerat antal 
		m=(i19 -3)-(i18 +8);
		faktureratantal=inrad.mid(i18 + 8,m);
		//	     tmp="?";
		/*****************************************************************************************/
		/*		Beräkningar								 */	     
		/*****************************************************************************************/
		/* Beräkning av (levererat antal - fakturerat antal) x apris */
		belopp=(levereratantal.toFloat() - faktureratantal.toInt()) * orderradpris.toFloat();
		radbelopp=radbelopp.setNum(belopp,'f',2);
		
		//	     QString momsprocent="25";
		/*  Beräkning av moms */
		momsen=momsprocent.toFloat()/100;
		radmoms=radmoms.setNum(momsen*belopp,'f',2);		// summa moms på raden
		
		/* Beräkning av radbelopp inkl moms */
		belopp=radbelopp.toDouble()+radmoms.toDouble();
		radbelopp=radbelopp.setNum(belopp,'f',2);
		
		item = new QListViewItem(listViewRader,orderradnr,orderartikelnr,orderbenamn,orderantal,levereratantal,orderradpris,momsprocent,radmoms);
		item->setText(8,radbelopp);
		total=total+radbelopp.toDouble();
	    }
	}
    }
    fakturatotal=fakturatotal.setNum(total,'f',2);
    lineEditSumma->setText( fakturatotal);
    frmKundFaktura::getBetalvillkor(betvillkor);
}

void frmKundFaktura::DataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmKundFaktura::DataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmKundFaktura::GetReportDir()
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

void frmKundFaktura::checkStatus()
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
    
    frmKundFaktura::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(DataOnStdout() ) );
    frmKundFaktura::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(DataOnStderr() ) );
    frmKundFaktura::connect( process, SIGNAL(processExited() ),this, SLOT(CheckOrderEndOfProcess() ) );
    
    if (kundordernr == ""){
	QMessageBox::warning( this, "KUFAKTW",
			      "Kundordernummer saknas! \n" );
	lineEditOrderNr->setFocus();
    }else {
	if ( !process->start() ) {
	    // error handling
	    fprintf(stderr,"Problem starta STYRMAN/ORDCHK!\n");
	    QMessageBox::warning( this, "KUFAKTW",
				  "Kan inte starta STYRMAN/ORDCHK! \n" );
	}
    }
}

void frmKundFaktura::CheckOrderEndOfProcess()
{
    int i,m;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    //   qDebug("Error:",errorrad);
    if (i != -1) {
	QMessageBox::critical( this, "KUFAKTW",
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
	QMessageBox::warning( this, "KUFAKTW",
			      "Ordern är avslutad! \n" );
	lineEditOrderNr->setSelection(0,kundordernr.length());
	lineEditOrderNr->setFocus();
    }else{
	frmKundFaktura::GetOrderHeader();
    }
}

void frmKundFaktura::listViewRader_format()
{
    listViewRader->setColumnWidth(0,35);		// Radnr
    listViewRader->setColumnWidth(1,180);		// Artikelnr
    listViewRader->setColumnWidth(2,295);		// Benämning
    listViewRader->setColumnWidth(3,60);		// Antal
    listViewRader->setColumnWidth(4,60);		// Rest
    listViewRader->setColumnWidth(5,60);		// Pris / st
    listViewRader->setColumnWidth(6,45);		// Moms %
    listViewRader->setColumnWidth(7,80);		// Moms Kr  
    listViewRader->setColumnWidth(8,80);		// Radtotal
}

void frmKundFaktura::listViewRader_clicked( QListViewItem * )
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
    QString temp3=item->text(3);	// Beställt antal
    QString temp4=item->text(4);	// Levererat antal, antal att fakturera
    QString temp5=item->text(5);	// Pris per styck
    QString temp6=item->text(6);	// Moms i procent
    QString temp7=item->text(7);	// Moms i kronor
    QString temp8=item->text(8);	// Radtotal
    //    qDebug("temp=%s, %s, %s, %s, %s, %s",temp0.latin1(),temp1.latin1(),temp2.latin1(),temp3.latin1(),temp4.latin1(),temp5.latin1());
    // --------------------------------------------------------------
    lineEditRadnr->setText(temp0);
    orderradnr=temp0;
    lineEditArtikelNr->setText(temp1);
    lineEditBenamn->setText(temp2);
    lineEditRadAntal->setText(temp3);
    lineEditRadRest->setText(temp4);
    lineEditRadPris->setText(temp5);
    lineEditRadMomsProcent->setText(temp6);
    lineEditRadMomsKr->setText(temp7);
    lineEditRadtotal->setText(temp8);
    pushBtnOKRad->setFocus();
    delete listViewRader->currentItem();
}

void frmKundFaktura::pushBtnOKRad_clicked()
{
    QListViewItem * item;
    int x;
    QString rad;
    QString orderradpris;
    QString momsprocent;
    QString radmoms;
    QString radbelopp;
    QString levereratantal;
    QString fakturatotal;
    QString momssumma;

    double total=0; 
    double moms=0;
    
 //    qDebug("Rad OK!");
    orderartikelnr=lineEditArtikelNr->text();
    orderbenamn=lineEditBenamn->text();
    orderantal =lineEditRadAntal->text();
    levereratantal=lineEditRadRest->text();
    orderradpris=lineEditRadPris->text();
    momsprocent=lineEditRadMomsProcent->text();
    radmoms=lineEditRadMomsKr->text();
    radbelopp=lineEditRadtotal->text();
    
    item = new QListViewItem(listViewRader,orderradnr,orderartikelnr,orderbenamn,orderantal,levereratantal,orderradpris,momsprocent,radmoms);
    item->setText(8,radbelopp);
    
    QListViewItem *myChild=listViewRader->firstChild ();
    
    x=listViewRader->childCount ();
    item =  listViewRader->currentItem();
//    qDebug("x=%d",x);
    while( myChild ) {
	rad=myChild->text(0);
	radbelopp=myChild->text(8);
	momssumma=myChild->text(7);
//	qDebug("rad=%s  radbelopp=%s",rad.latin1(),radbelopp.latin1());
	total=total+radbelopp.toDouble();
	moms=moms+momssumma.toDouble();
	myChild=myChild->nextSibling();
    }
    fakturatotal=fakturatotal.setNum(total,'f',2);
    lineEditSumma->setText( fakturatotal);
    momssumma=momssumma.setNum(moms,'f',2);
    lineEditMoms->setText(momssumma);
    
    if (radnrflag == FALSE){
	int i = orderradnr.toInt();
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
    lineEditRadAntal->clear();    
    lineEditRadRest->clear();
    lineEditRadPris->clear();
    lineEditRadMomsProcent->clear();
    lineEditRadMomsKr->clear();
    lineEditRadtotal->clear();
    orderartikelnr="";
    orderbenamn="";
    orderantal="";
    
    //    lineEditArtikelNr->setFocus();
}

void frmKundFaktura::pushBtnHelp_clicked()
{
    inrad="";
    frmKundFaktura::readResursFil();		// Hämta path till hjälpfilen
    
    int i1 = hjelpfil.find( QRegExp(".html"), 0 );
    hjelpfil=hjelpfil.left(i1);
    hjelpfil=hjelpfil+"_KUNDORDER.html";
    hjelpfil=hjelpfil+"#FAKTURA";		// Lägg till position
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

void frmKundFaktura::readResursFil()
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

void frmKundFaktura::TRHDregAdd(QString trhdData, QString data )
{
    /* Uppdatera artikelregistret, TRHD, historikregistret*/
    const char *userp = getenv("USER");
    QString usr(userp);
    QString tidpunkt;
    QDateTime dt = QDateTime::currentDateTime();
    tidpunkt=dt.toString ( "yyyy-MM-dd hh:mm:ss" );
    
//    qDebug("trhdData=%s data=%s",trhdData.latin1(),data.latin1());
    
    inradtrhd="";
    errorradtrhd="";
    proctrhd = new QProcess();
    proctrhd->addArgument("./STYRMAN");	// OLFIX styrprogram
    proctrhd->addArgument(usr);		// userid
    proctrhd->addArgument( "TRHDADD");	// OLFIX funktion
    proctrhd->addArgument(trhdData);	// TRNSID
    proctrhd->addArgument(tidpunkt);
    proctrhd->addArgument(usr);
    proctrhd->addArgument(data);
    
    frmKundFaktura::connect( proctrhd, SIGNAL(readyReadStdout() ),this, SLOT(TRHDregAddDataOnStdout() ) );
    frmKundFaktura::connect( proctrhd, SIGNAL(readyReadStderr() ),this, SLOT(TRHDregAddDataOnStderr() ) );
    frmKundFaktura::connect( proctrhd, SIGNAL(processExited() ),this, SLOT(TRHDregAddEndOfProcess() ) );
    
    if ( !proctrhd->start() ) {
	// error handling
	QMessageBox::warning( this, "KUFAKTW",
			      "Kan inte starta STYRMAN/TRHDADD! \n" );
    }
}

void frmKundFaktura::TRHDregAddEndOfProcess()
{
    int i;
    i = -1;
    i = errorradtrhd.find( QRegExp("Error:"), 0 );
    //   qDebug("Error:",errorrad);
    if (i != -1) {
	QMessageBox::critical( this, "KUFAKTW",
			       "ERROR!\n"+errorradtrhd
			       );
    }
    errorradtrhd="";
    inradtrhd="";
}

void frmKundFaktura::CreateReportHeader()
{
    int i;
    QString rad[70];
    QString rapportrad;
    
    QFile filnamn(tmppath+fakturafil);
    QTextStream stream(&filnamn);
    
    frmKundFaktura::FileRemove(fakturafil);	// radera gammal fil.
    rad[1]="<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n";
    rad[2]="<!DOCTYPE KugarData [\n";
    rad[3]="   <!ELEMENT KugarData (namn* )>\n";
    rad[4]="   <!ATTLIST KugarData\n";
    rad[5]="      Template CDATA #REQUIRED>\n\n";
    rad[6]="   <!ELEMENT namn EMPTY>\n";
    rad[7]="   <!ATTLIST namn\n";
    rad[8]="      level CDATA #REQUIRED\n";
    rad[9]="      ftgnamn CDATA #REQUIRED\n";
    rad[10]="      datum CDATA #REQUIRED\n";
    rad[11]="      fakturanr CDATA #REQUIRED\n";
    rad[12]="      ordernr CDATA #REQUIRED\n";
    rad[13]="      sida CDATA #REQUIRED\n";
    rad[14]="      kundnr CDATA #REQUIRED\n";
    rad[15]="      kundnamn CDATA #REQUIRED\n";
    rad[16]="      kundadr CDATA #REQUIRED\n";
    rad[17]="      kundpostnr CDATA #REQUIRED\n";
    rad[18]="      kundpostadr CDATA #REQUIRED\n";
    rad[19]="      kundland CDATA #REQUIRED\n";
    rad[20]="      levkundnamn CDATA #REQUIRED\n";
    rad[21]="      kundlevadr CDATA #REQUIRED\n";
    rad[22]="      levpostnr CDATA #REQUIRED\n";
    rad[23]="      leveranspostadr CDATA #REQUIRED\n";
    rad[24]="      leveransland CDATA #REQUIRED\n";
    rad[25]="      seljare CDATA #REQUIRED\n";
    rad[26]="      betvillkor CDATA #REQUIRED\n";
    rad[27]="      levvillkor CDATA #REQUIRED\n";
    rad[28]="      valuta CDATA #REQUIRED\n";
    rad[29]="      levsett CDATA #REQUIRED\n";
    rad[30]="      erref CDATA #REQUIRED\n";
    rad[31]="      godsmerke CDATA #REQUIRED\n";
    rad[32]="      foretagsnamn CDATA #REQUIRED\n";
    rad[33]="      adress1 CDATA #REQUIRED\n";
    rad[34]="      adress2 CDATA #REQUIRED\n";
    rad[35]="      adress3 CDATA #REQUIRED\n";
    rad[36]="      telefon CDATA #REQUIRED\n";
    rad[37]="      nettobelopp CDATA #REQUIRED\n";
    rad[38]="      frakt CDATA #REQUIRED\n";
    rad[39]="      moms CDATA #REQUIRED\n";
    rad[40]="      avrund CDATA #REQUIRED\n";
    rad[41]="      fakturatotal CDATA #REQUIRED\n";      
    rad[42]=">\n";
    rad[43]="  <!ELEMENT KugarData (Rad*)>\n";
    rad[44]="  <!ATTLIST KugarData\n";
    rad[45]="      Template CDATA #REQUIRED>\n\n";
    rad[46]="  <!ELEMENT Rad EMPTY>\n";
    rad[47]="  <!ATTLIST Rad\n";
    rad[48]="      level CDATA #REQUIRED\n";
    rad[49]="      pos CDATA #REQUIRED\n";
    rad[50]="      vartnr CDATA #REQUIRED\n";
    rad[51]="      antal CDATA #REQUIRED\n";
    rad[52]="      levant CDATA #REQUIRED\n";
    rad[53]="      radprisperst CDATA #REQUIRED\n";
    rad[54]="      radsumma CDATA #REQUIRED\n";
/*    rad[55]=">\n";
    rad[56]="  <!ELEMENT KugarData (Total*)>\n";
    rad[57]="  <!ATTLIST KugarData\n";
    rad[58]="      Template CDATA #REQUIRED>\n\n";
    rad[59]="  <!ELEMENT Total EMPTY>\n";
    rad[60]="  <!ATTLIST Total\n";
    rad[61]="      level CDATA #REQUIRED\n";
    rad[62]="      nettobelopp CDATA #REQUIRED\n";
    rad[63]="      frakt CDATA #REQUIRED\n";
    rad[64]="      moms CDATA #REQUIRED\n";
    rad[65]="      avrund CDATA #REQUIRED\n";
    rad[66]="      fakturatotal CDATA #REQUIRED\n";
*/    rad[67]=">\n";
    rad[68]="]>\n\n";
    
    rad[69]="<KugarData Template=\"";
    rad[69].append(reportpath);
    rad[69].append("KuOrderFaktura.kut\">\n");	// ange rätt template, absolut path
    rapportrad=rad[1];
    for (i=2;i<70;i++){
	rapportrad.append(rad[i]);
    }
    //    qDebug("CreateHeader::rapportrad = \n%s",rapportrad.latin1());
    rapportrad.append("\"<namn level=\"0");
    rapportrad.append("\" ftgnamn=\"");
    rapportrad.append(ftgnamn);
    rapportrad.append("\" datum=\"");
    rapportrad.append(fakturadatum);
    rapportrad.append("\" fakturanr=\"");
    rapportrad.append(fakturanr);
    rapportrad.append("\" ordernr=\"");
    rapportrad.append(ordernr);
    rapportrad.append("\" sida=\"");
    rapportrad.append(" 1");
    rapportrad.append("\" kundnr=\"");
    rapportrad.append(kundnr);
    rapportrad.append("\" kundnamn=\"");
    rapportrad.append(kundnamn);
    rapportrad.append("\" kundadr=\"");
    rapportrad.append(kundadr);
    rapportrad.append("\" kundpostnr=\"");
    rapportrad.append(kundpostnr);
    rapportrad.append("\" kundpostadr=\"");
    rapportrad.append(kundpostadr);
    rapportrad.append("\" kundland=\"");
    rapportrad.append(kundland);
    rapportrad.append("\" levkundnamn=\"");
    rapportrad.append(kundnamn);
    rapportrad.append("\" kundlevadr=\"");
    rapportrad.append(leveransadress);
    rapportrad.append("\" levpostnr=\"");
    rapportrad.append(leveranspostnr);
    rapportrad.append("\" leveranspostadr=\"");
    rapportrad.append(leveranspostadress);
    rapportrad.append("\" leveransland=\"");
    rapportrad.append(leveransland);
    rapportrad.append("\" betvillkor=\"");
    rapportrad.append(betvilkbeskriv);		// Betalningsvillkor i klartext
    rapportrad.append("\" levvillkor=\"");
    rapportrad.append(levvillkor);
    rapportrad.append("\" valuta=\"");
    rapportrad.append(valuta);
    rapportrad.append("\" levsett=\"");
    rapportrad.append(levsett);
    rapportrad.append("\" erref=\"");
    rapportrad.append(erref);
    rapportrad.append("\" seljare=\"");
    rapportrad.append(seljare);
    rapportrad.append("\" godsmerke=\"");
    rapportrad.append(godsmerke);
    //    rapportrad.append("\"/>\n");
    
    rapportrad.append("\" foretagsnamn=\"");
    rapportrad.append(ftgnamn);
    rapportrad.append("\" adress1=\"");
    rapportrad.append(ftgadr);
    rapportrad.append("\" adress2=\"");
    rapportrad.append(ftgpostnr);
    rapportrad.append("\" adress3=\"");
    rapportrad.append(ftgpostadr);
    rapportrad.append("\" telefon=\"");
    rapportrad.append(ftgtfn);
//    rapportrad.append("\"/>\n");
    
    QString netto=lineEditSumma->text();
    QString frakt=lineEditFrakt->text();
    QString moms=lineEditMoms->text();
    QString avrund=lineEditAvrundning->text();
    QString fakturatotal=lineEditTotal->text();
    rapportrad.append("\" expiredate=\"");
    rapportrad.append(expdatum);			// Förfallodatum
    rapportrad.append("\" nettobelopp=\"");
    rapportrad.append(netto);
    rapportrad.append("\" frakt=\"");
    rapportrad.append(frakt);
    rapportrad.append("\" moms=\"");
    rapportrad.append(moms);
    rapportrad.append("\" avrund=\"");
    rapportrad.append(avrund);
    rapportrad.append("\" fakturatotal=\"");
    rapportrad.append(fakturatotal);
//    qDebug("netto_huvud=%s",netto.latin1());
    
    rapportrad.append("\"/>\n");
    filnamn.open( IO_WriteOnly | IO_Append );
    stream << rapportrad;
    //    qDebug("CreateHeader::ordernr=  %s",ordernr.latin1());
    filnamn.close();
}

void frmKundFaktura::createFakturaRad()
{
    double total=0;
    QString fil;
    fil=tmppath+fakturafil;
    QFile filnamn(fil);
    //    qDebug("fil=%s",fil.latin1());
    QTextStream stream(&filnamn);
    QString fakturarad;	
    
    QString radnr="10";
    QString artikelnr="99-99";
    QString benemning="Test 99";
    QString antal="13";
    QString levereratantal="3";
    QString radprisperst="25.50";
    QString radsumma="76.50";
    
    filnamn.open( IO_WriteOnly | IO_Append );
    
    QListViewItem *myChild=listViewRader->firstChild ();    
    
    while( myChild ) {
	radnr=myChild->text(0);
	artikelnr=myChild->text(1);
	benemning=myChild->text(2);
	antal=myChild->text(3);
	levereratantal=myChild->text(4);
	radprisperst=myChild->text(5);
	radsumma=myChild->text(8);
//	qDebug("rad=%s  radbelopp=%s",rad.latin1(),radbelopp.latin1());
	total=total+radsumma.toDouble();
	myChild=myChild->nextSibling();
   
	fakturarad="<Rad level=\"1\" ";
	fakturarad.append(" pos=\"");
	fakturarad.append(radnr);
	fakturarad.append("\" vartnr=\"");
	fakturarad.append(artikelnr);
	fakturarad.append(" \n");
	fakturarad.append(benemning);
//	    fakturarad.append("\" erartnr=\"");
// 	   fakturarad.append("");
	fakturarad.append("\" antal=\"");
	fakturarad.append(antal);
	fakturarad.append("\" levant=\"");
	fakturarad.append(levereratantal);
	fakturarad.append("\" styckpris=\"");
	fakturarad.append(radprisperst);
	fakturarad.append("\" radsumma=\"");
	fakturarad.append(radsumma);
	fakturarad.append("\"/>\n");
//	qDebug("slotEndOfProcess() 3d ::bestrad=%s",bestrad.latin1());
	stream << fakturarad;
     }
    QString netto=lineEditSumma->text();
    QString frakt=lineEditFrakt->text();
    QString moms=lineEditMoms->text();
    QString avrund=lineEditAvrundning->text();
    QString fakturatotal=lineEditTotal->text();
    fakturarad="<Total level=\"2\" ";
    fakturarad.append(" nettobelopp=\"");
    fakturarad.append(netto);
    fakturarad.append("\" frakt=\"");
    fakturarad.append(frakt);
    fakturarad.append("\" moms=\"");
    fakturarad.append(moms);
    fakturarad.append("\" avrund=\"");
    fakturarad.append(avrund);
    fakturarad.append("\" fakturatotal=\"");
    fakturarad.append(fakturatotal);
    fakturarad.append("\"/>\n");
//    qDebug("netto=%s",netto.latin1());
    stream << fakturarad;
    filnamn.close();
}

void frmKundFaktura::CreateReportFot()
{
    QString fil;
    fil=tmppath+fakturafil;
    QFile filnamn(fil);
    //    qDebug("fil=%s",fil.latin1());
    QTextStream stream(&filnamn);
    QString footrad;	// rapportfot
   
    filnamn.open( IO_WriteOnly | IO_Append );
    
    // ------------------------------------------------------------
    //   Pagefoot
    // ------------------------------------------------------------        
    footrad=("<foot level=\"3");
    footrad.append("\" foretagsnamn=\"");
    footrad.append(ftgnamn);
    footrad.append("\" adress1=\"");
    footrad.append(ftgadr);
    footrad.append("\" adress2=\"");
    footrad.append(ftgpostnr);
    footrad.append("\" adress3=\"");
    footrad.append(ftgpostadr);
    footrad.append("\" telefon=\"");
    footrad.append(ftgtfn);
    // ------------------------------------------------------------
    footrad.append("\"/>\n");
    footrad.append("</KugarData>\n");
    
    stream << footrad;
    filnamn.close();
}

void frmKundFaktura::KugarVersion()
{
    //  Hämta aktuell version av kugar
    //  Anrop av kugar skiljer sig mellan version 1.2.1 och version 1.2.92 ->
    bool status;
    int i = -1;
    
    QString filename;
    
    system("kugar -v >/tmp/kugarversion.txt");
    filename="/tmp/kugarversion.txt";
    QFile file(filename);
    status=file.open(IO_ReadOnly);
    QTextStream stream( &file );
    while ( !stream.eof() ) {
	inrad = stream.readLine();
	i = inrad.find( QRegExp("Kugar:"), 0 );
	if(i == 0){
	    kugarversion=inrad.mid(7,inrad.length()-7);
	    i= -1;
	}
    }
    file.close ();
    //   qDebug("kugarversion=%s",kugarversion.latin1());
    frmKundFaktura::FileRemove("kugarversion.txt");
}

void frmKundFaktura::CallKugar()
{
    if (kugarversion<"1.2.92"){
	kommando="kugar -d ";
	kommando.append(tmppath);
	kommando.append(fakturafil);
	kommando.append(" -r ");
	kommando.append(reportpath);
	kommando.append(templatefile);
	system(kommando);
    }else{
	kommando="kugar ";
	kommando.append(tmppath);
	kommando.append(fakturafil);
	qDebug("kommando=%s",kommando.latin1());
	system(kommando);
    }
//    qDebug("kommando=%s",kommando.latin1());
    pushButtonSluta->setFocus();
}

void frmKundFaktura::FileRemove(QString filnamn)
{
    //  Ta bort temporärfilen /tmp/KuOrderFaktura.kud
    bool status;
    QDir d = QDir::root();                   // "/"
    if ( !d.cd("tmp") ) {                       // "/tmp"
	qWarning( "Cannot find the \"/tmp\" directory" );
    }
    //    qDebug("filnamn=%s",filnamn.latin1());
    status=d.remove(filnamn,FALSE);
}

void frmKundFaktura::getForetagsdata(QString posttyp)
{
    /************************************************************************/
    /*	Hämta företagsdata, FTGDATA	 				*/
    /************************************************************************/
    const char *userp = getenv("USER");
    QString usr(userp);
    
    inradftg="";
    errorradftg="";
    process = new QProcess();
    process->addArgument("./STYRMAN");	// OLFIX styrprogram
    process->addArgument(usr);		// userid
    process->addArgument( "FTGDSP");	// OLFIX funktion
    process->addArgument(posttyp);
    
    frmKundFaktura::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(ForetagsdataDataOnStdout() ) );
    frmKundFaktura::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(ForetagsdataDataOnStderr() ) );
    frmKundFaktura::connect( process, SIGNAL(processExited() ),this, SLOT(ForetagsdataEndOfProcess() ) );
    
    if ( !process->start() ) {
	// error handling
	QMessageBox::warning( this, "KUFAKTW",
			      "Kan inte starta STYRMAN/FTGDSP! \n" );
    }
}

void frmKundFaktura::ForetagsdataDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inradftg.append(line);
	inradftg.append("\n");
//	qDebug("ForetagsdataDataOnStdout=%s",inradftg.latin1());
    }
}

void frmKundFaktura::ForetagsdataDataOnStderr()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inradftg.append(line);
	inradftg.append("\n");
//	qDebug("ForetagsdataDataOnStderr=%s",errorradftg.latin1());
    }
}

void frmKundFaktura::ForetagsdataEndOfProcess()
{
    int i,m;
    double fnr=0;
    QString posttyp="";
    i = -1;
    i = errorradftg.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "KUFAKTW",
			       "ERROR!\n"+errorradftg
			       );
    }else{
	i = -1;
	i = inradftg.find( QRegExp("OK:"), 0 );
	if (i != -1) {
	    int i1 = inradftg.find( QRegExp("1:"), 0 );		// posttyp
	    int i2 = inradftg.find( QRegExp("2:"), 0 );		// ftgdata
	    int i3 = inradftg.length();
	    m=i2-i1;
	    if (i1 != -1){
		posttyp=inradftg.mid(i1+2,m-4);
	    }
//	    qDebug("posttyp=%s",posttyp.latin1());
	    m=i3-i2;
	    if (i2 != -1){
		if(posttyp=="FNAMN"){
		    ftgnamn=inradftg.mid(i2+2,m-2);
		    ftgnamn=ftgnamn.left(ftgnamn.length()-2); // plocka bort en radretur
		    frmKundFaktura::getForetagsdata("ADR1");
		}
		if(posttyp=="ADR1"){
		    ftgadr=inradftg.mid(i2+2,m-2);
		    ftgadr=ftgadr.left(ftgadr.length()-2);
		    frmKundFaktura::getForetagsdata("ADR2");
		}
		if(posttyp=="ADR2"){
		    ftgpostnr=inradftg.mid(i2+2,m-2);
		    ftgpostnr=ftgpostnr.left(ftgpostnr.length()-2);
		    frmKundFaktura::getForetagsdata("ADR3");
		}
		if(posttyp=="ADR3"){
		    ftgpostadr=inradftg.mid(i2+2,m-2);
		    ftgpostadr=ftgpostadr.left(ftgpostadr.length()-2);
		    frmKundFaktura::getForetagsdata("TFNVX");
		}
		if(posttyp=="TFNVX"){
		    ftgtfn=inradftg.mid(i2+2,m-2);
		    ftgtfn=ftgtfn.left(ftgtfn.length()-2); 
//		    qDebug("ftgtfn=%s",ftgtfn.latin1());
		    frmKundFaktura::getForetagsdata("FKNRS");
		}
		if(posttyp=="FKNRS"){
		    fakturanrflag=inradftg.mid(i2+2,m-2);
		    fakturanrflag=fakturanrflag.left(fakturanrflag.length()-2); 
		    fakturanrflag=fakturanrflag.stripWhiteSpace();
//		    qDebug("FKNRS_fakturanrflag=|%s|",fakturanrflag.latin1());
		    if (fakturanrflag=="1"){
			radioButton1->setEnabled(FALSE);			
			radioButton2->setEnabled(FALSE);
			inradftg="";
//			qDebug("Hämta FAKNR");
			frmKundFaktura::getForetagsdata("FAKNR");
		    }
		    if (fakturanrflag=="2"){
			radioButton1->setEnabled(TRUE);
			radioButton2->setEnabled(TRUE);
			radioButton2->setChecked(TRUE);
			inradftg="";
//			qDebug("Hämta FKNR2");
			frmKundFaktura::getForetagsdata("FKNR2");
		    }
		}
		if(posttyp=="FAKNR"){
//		    qDebug("inradftg=%s",inradftg.latin1());
		    fakturanr=inradftg.mid(i2+2,m-2);
		    fakturanr=fakturanr.left(fakturanr.length()-2); 
//		    qDebug("FAKNR_fakturanr=%s fakturanrflag=%s",fakturanr.latin1(),fakturanrflag.latin1());
		    fnr=fakturanr.toDouble(0)+1;			// Senaste fakturanr + 1
		    fakturanr=fakturanr.setNum(fnr);
		    lineEditFakturanr->setText(fakturanr);
		}
		if(posttyp=="FKNR2"){
//		    qDebug("FKNR2_inradftg=%s",inradftg.latin1());
		    fakturanr=inradftg.mid(i2+2,m-2);
		    fakturanr=fakturanr.left(fakturanr.length()-2); 
//		    qDebug("FKNR2_fakturanr=%s fakturanrflag=%s",fakturanr.latin1(),fakturanrflag.latin1());
		    fnr=fakturanr.toDouble(0)+1;			// Senaste fakturanr + 1
		    fakturanr=fakturanr.setNum(fnr);
		    lineEditFakturanr->setText(fakturanr);
		}		
	    }
	}
    }
}

void frmKundFaktura::listKundorder()
{
    listViewKundorder->clear();
    frmKundFaktura::listKundordrar();
    listViewKundorder->setFocus();
    listViewKundorder->firstChild ();
    listViewKundorder->setSelected(listViewRader->firstChild (),TRUE);
}

void frmKundFaktura::listKundordrar()
{
    /**********************************************************************/
    /*	Lista kundordrar från ORDERREG 	   				*/
    /**********************************************************************/
    const char *userp = getenv("USER");
    QString usr(userp);
    
    listinrad="";
    listerrorrad="";
    process = new QProcess();
    process->addArgument("./STYRMAN");	// OLFIX styrprogram
    process->addArgument(usr);		// userid
    process->addArgument( "ORDLST2");	// OLFIX funktion
    
    frmKundFaktura::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(ListaKundordrarDataOnStdout() ) );
    frmKundFaktura::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(ListaKundordrarDataOnStderr() ) );
    frmKundFaktura::connect( process, SIGNAL(processExited() ),this, SLOT(ListaKundordrarEndOfProcess() ) );
    
    if ( !process->start() ) {
	// error handling
	QMessageBox::warning( this, "KUFAKTW",
			      "Kan inte starta STYRMAN/ORDLST! \n" );
    }
}

void frmKundFaktura::ListaKundordrarEndOfProcess()
{
    QListViewItem* item;
    int i;
    listViewKundorder->setSorting(0,TRUE);
    i = -1;
    i = listerrorrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "LSTORDW",
		"ERROR!\n"+errorrad
	);
	listerrorrad="";
	i = -1;
    }
    i = listinrad.find( QRegExp("OK: NR_0_"), 0 );
    if (i != -1) {
	QMessageBox::information( this, "LSTORDW",
		"Kundorderregistret innehåller inga poster!\n"
		);
	i = -1;
    }

    QString listrad;
    QString antalrader;
    QString ordernr;
    QString kundnr;
    rad=&listinrad;
    listinrad.latin1();
    int antrad,l,m;
    int i1,i2,i3,i4;
    int tmp5,tmp6,tmp7;
    
    m=0;
    i1=listinrad.find( QRegExp("OK: NR_"), m); 		// startposition  = 0
    i2=listinrad.find( QRegExp("_:"), m );			// slutposition för antal rader
    l=i2-(i1+7);
    antalrader=listinrad.mid(i1+7,l);
//    qDebug("i1=%d i2=%d l=%d antalrader=%s",i1,i2,l,antalrader.latin1());
    antrad=antalrader.toInt();
//   qDebug("antalrader=%s antrad=%d",antalrader.latin1(),antrad);    
    // i2 + 2  = startposition för ordernr
    tmp7=i2;
    m=m+(i1+9);
//    qDebug("listinrad=%s",listinrad.latin1());
//    qDebug("1. m=%d i1=%d i2=%d",m,i1,i2);
    for (i=0;i<antrad;i++){
	i3=listinrad.find( QRegExp("_:"), m+1);		// slutposition for ordernr
	l=i3-(tmp7+2);
//	qDebug("2. m=%d i3=%d l=%d tmp7=%d",m,i3,l,tmp7);	
	ordernr=listinrad.mid(m+1,l);
//	qDebug("ordernr=%s",ordernr.latin1());	
	m=m+2+l;  
	i4=listinrad.find( QRegExp("_:"), m+1);		// slutposition för kundnr
	l=i4-(i3+2);
//	qDebug("l=%d  i1=%d m=%d i2=%d i3=%d i4=%d",l,i1,m,i2,i3,i4);
	kundnr=listinrad.mid(m+1,l);
//	qDebug("kundnr=%s",kundnr.latin1());
	m=m+2+l;
	tmp5=listinrad.find( QRegExp("_:"), m+1);
	l=tmp5-(i4+2);
	m=m+2+l;
	tmp6=listinrad.find( QRegExp("_:"), m+1);
	l=tmp6-(tmp5+2);
	m=m+2+l;
	tmp7=listinrad.find( QRegExp("_:"), m+1);
//	qDebug("tmp7=%d",tmp7);
	l=tmp7-(tmp6+2);
	m=m+2+l;
//	item = new QListViewItem(listViewKundorder,ordernr,kundnr,levdatum,orderstatus,ordersumma);
	item = new QListViewItem(listViewKundorder,ordernr,kundnr);	
    }
   frmKundFaktura::getForetagsdata("FNAMN");
}

void frmKundFaktura::ListaKundordrarDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	listerrorrad.append(line);
	listerrorrad.append("\n");
    }
}

void frmKundFaktura::ListaKundordrarDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	listinrad.append(line);
	listinrad.append("\n");
    }
}

void frmKundFaktura::slotPickupOrdernr( QListViewItem * item)
{
    char ordernummer[11]="";
//    qDebug("PickupOrdernr\n");
    if(!item){
	return;
    }
     listViewKundorder->setCurrentItem(item);
     if(!item->key(0,TRUE)){
	 return;
     }

     strcpy(ordernummer,item->key(0,TRUE));
     ordernr=ordernummer;
     lineEditOrderNr->setText((ordernr));
     lineEditOrderNr->setFocus();     
}

void frmKundFaktura::updateFakturanr()
{
//    qDebug("updateFakturanr(FTGUPD) fakturanr = %s",fakturanr.latin1());
    /**********************************************************************/
    /*	Uppdatera FTGDATA FAKNR eller FKNR2 berooende på fakturanrflag	*/
    /**********************************************************************/
    const char *userp = getenv("USER");
    QString usr(userp);
    
    inrad="";
    errorrad="";
    process = new QProcess();
    process->addArgument("./STYRMAN");	// OLFIX styrprogram
    process->addArgument(usr);		// userid
    process->addArgument( "FTGUPD");	// OLFIX funktion
    if (fakturanrflag=="2"){
	process->addArgument("FKNR2");
    }else{
	process->addArgument("FAKNR");
    }
    process->addArgument(fakturanr);
    
    frmKundFaktura::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(DataOnStdout() ) );
    frmKundFaktura::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(DataOnStderr() ) );
    frmKundFaktura::connect( process, SIGNAL(processExited() ),this, SLOT(EndOfProcess() ) );
    
    if ( !process->start() ) {
	// error handling
	QMessageBox::warning( this, "KUFAKTW",
			      "Kan inte starta STYRMAN/FTGUPD! \n" );
    }  
}

void frmKundFaktura::createKURESKpost()
{
//    qDebug("createKURESKpost");
/*
  (ORDERNR,FAKTURANR,KUNDNR,FAKTURADATUM,EXPIREDATUM,NETTOBELOPP,MOMSBELOPP,BETALD, BETALDATUM,USERID,VALUTA,VALUTAKURS,VALUTABELOPP,BAR,VERNR,MOMSKTONR,KTONR,DEBETBELOPP)
	_:_1093_:_1351_:_4376_:_2005-11-11_:_2005-12-11_:_1523.50_:_380.90_:_N_:_
	0000-00-00_:_JAPI_:_SEK_:_1.00_:_1904.40_:_AE_:_25341_:_2410_:_1210_:_1904.40_:_END  
*/  
    const char *userp = getenv("USER");
    QString usr(userp);

    QString skilje="_:_";		// skiljetecken mellan fält
    
    kureskpost=skilje;
    kureskpost.append(ordernr);
    kureskpost.append(skilje);
    kureskpost.append(lineEditFakturanr->text());
    kureskpost.append(skilje);
    kureskpost.append(kundnr);
    kureskpost.append(skilje);
    kureskpost.append(fakturadatum);
    kureskpost.append(skilje);
    kureskpost.append(expdatum);
    kureskpost.append(skilje);
    kureskpost.append(lineEditSumma->text());
    kureskpost.append(skilje);
    kureskpost.append(lineEditMoms->text());
    kureskpost.append(skilje);
    kureskpost.append(lineEditTotal->text());
    kureskpost.append(skilje);
    kureskpost.append("N");		// Fakturan är inte betald
    kureskpost.append(skilje);
    kureskpost.append("0000-00-00"); 	// Datum när fakturan ÄR betald
    kureskpost.append(skilje);
    kureskpost.append(usr);
    kureskpost.append(skilje);
    kureskpost.append("SEK");		// Valuta
    kureskpost.append(skilje);
    kureskpost.append("1");		// Valutakurs
    kureskpost.append(skilje);
    kureskpost.append("0");		// Valutabelopp
    kureskpost.append(skilje);
    kureskpost.append("XX");		// Bokföringsår
    kureskpost.append(skilje);
    kureskpost.append("0");		// vernr för bokföringen (ej implementerad)
    kureskpost.append(skilje);
    kureskpost.append("0000");		// momskontonummer
    kureskpost.append(skilje);	
    kureskpost.append("0000");		// debetkonto, kundfordringar
    kureskpost.append(skilje);
    kureskpost.append(lineEditTotal->text());
    kureskpost.append(skilje);
    kureskpost.append("END");
//    qDebug("KURESKpost = %s",kureskpost.latin1());
    
    inradkresk="";
    errorradkresk="";
    prockresk = new QProcess();
    prockresk->addArgument("./STYRMAN");	// OLFIX styrprogram
    prockresk->addArgument(usr);		// userid
    prockresk->addArgument( "KRESADD");	// OLFIX funktion
    prockresk->addArgument(kureskpost);
    
    frmKundFaktura::connect( prockresk, SIGNAL(readyReadStdout() ),this, SLOT(KresaddDataOnStdout() ) );
    frmKundFaktura::connect( prockresk, SIGNAL(readyReadStderr() ),this, SLOT(KresaddDataOnStderr() ) );
    frmKundFaktura::connect( prockresk, SIGNAL(processExited() ),this, SLOT(KresaddEndOfProcess() ) );
    
    if ( !prockresk->start() ) {
	// error handling
	QMessageBox::warning( this, "KUFAKTW",
			      "Kan inte starta STYRMAN/KRESADD! \n" );
    }  
}

void frmKundFaktura::KresaddEndOfProcess()
{
    int i;
    i = -1;
    i = errorradkresk.find( QRegExp("Error:"), 0 );
    //   qDebug("Error:",errorrad);
    if (i != -1) {
	QMessageBox::critical( this, "KUFAKTW",
			       "ERROR!\n"+errorradkresk
			       );
    } 
    i = -1;
    i = inradkresk.find( QRegExp("OK:"), 0 );
    //   qDebug("Error:",errorrad);
    if (i != -1) {
	frmKundFaktura::TRHDregAdd("KRESADD", kureskpost );
    } 
}

void frmKundFaktura::EndOfProcess()
{
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    //   qDebug("Error:",errorrad);
    if (i != -1) {
	QMessageBox::critical( this, "KUFAKTW",
			       "ERROR!\n"+errorrad
			       );
    } 
}

void frmKundFaktura::getBetalvillkor(QString villkor)
{
    const char *userp = getenv("USER");
    QString usr(userp);
    
    villkor = villkor.stripWhiteSpace();
//    qDebug("villkor=%s",villkor.latin1());

    process = new QProcess();
    process->addArgument("./STYRMAN");	// OLFIX styrprogram
    process->addArgument(usr);		// userid
    process->addArgument( "BETDSP");	// OLFIX funktion
    process->addArgument(villkor);
    
    frmKundFaktura::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(BetvillkorDataOnStdout() ) );
    frmKundFaktura::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(BetvillkorDataOnStderr() ) );
    frmKundFaktura::connect( process, SIGNAL(processExited() ),this, SLOT(BetvillkorEndOfProcess() ) );
    
    if ( !process->start() ) {
	// error handling
	QMessageBox::warning( this, "KUFAKTW",
			      "Kan inte starta STYRMAN/BETDSP! \n" );
    }  
}

void frmKundFaktura::BetvillkorDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	betinrad.append(line);
	betinrad.append("\n");
    }
}

void frmKundFaktura::BetvillkorDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	beterrorrad.append(line);
	beterrorrad.append("\n");
    }
}

void frmKundFaktura::BetvillkorEndOfProcess()
{
    int i,j,l,m;
    int betdag;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    //   qDebug("Error:",errorrad);
    if (i != -1) {
	QMessageBox::critical( this, "KUFAKTW",
			       "ERROR!\n"+errorrad
			       );
    } 
    i = -1;

    i = betinrad.find( QRegExp("OK:"), 0 );
    if (i != -1) {
	j=betinrad.find( QRegExp("DAGAR:"), 0 )+6;
	l=betinrad.find( QRegExp("BESKRIVNING:"), 0 );
	m=betinrad.find( QRegExp("END:"), 0 );
	betalningsdagar=betinrad.mid(j,l-j);
	betvilkbeskriv=betinrad.mid(l+13,m-(l+13));
//	qDebug("betvilkbeskr=%s",betvilkbeskriv.latin1());
    }else{
	betalningsdagar=30;
	betvilkbeskriv="30 dagar netto";
    }
	
    betalningsdagar = betalningsdagar.stripWhiteSpace();
//    qDebug("betalningsdagar=%s",betalningsdagar.latin1());
    betdag=betalningsdagar.toInt();
    QDateTime dt = QDateTime::currentDateTime();
    QDateTime nt = dt.addDays ( +betdag );			// Dagens datum + 30 dagar    
    expdatum=nt.toString("yyyy-MM-dd");			// Förfallodatum
    lineEditExpiredate->setText(expdatum);
}

void frmKundFaktura::nextFaktura()
{
//    qDebug("Start nextFaktura()");
    lineEditOrderNr->clear();
    lineEditOrderstatus->clear();
    lineEditFakturanr->clear();
    listViewRader->clear();
    lineEditRadnr->setText("000");
    lineEditArtikelNr->clear();
    lineEditBenamn->clear();
    lineEditRadAntal->clear();    
    lineEditRadRest->clear();
    lineEditRadPris->clear();
    lineEditRadMomsProcent->clear();
    lineEditRadMomsKr->clear();
    lineEditRadtotal->clear();
    orderartikelnr="";
    orderbenamn="";
    orderantal="";

    lineEditKundnr->clear();
    lineEditKundNamn->clear();
    lineEditKundAdress->clear();	    
    lineEditKundPostnr->clear();    
    lineEditKundPostAdress->clear();
    lineEditKundLand->clear();
    lineEditKundRef->clear();
    lineEditExpiredate->clear();
    
    lineEditSumma->clear();
    lineEditFrakt->clear();
    lineEditFraktmoms->clear();
    lineEditMoms->clear();
    lineEditAvrundning->clear();
    lineEditTotal->clear();
    
    frmKundFaktura::getForetagsdata("FKNRS");		// Hämta fakturanr
    pushButtonOK->setEnabled(FALSE);
    lineEditOrderNr->setFocus();
//    qDebug("Slut nextFaktura()");
}


void frmKundFaktura::updateOrderreg()
{
    const char *userp = getenv("USER");
    QString usr(userp);
    
//    qDebug("Start updateOrderreg");
    
    inradorder="";
    errorradorder="";

    procorder = new QProcess(this);
    procorder->addArgument("./STYRMAN");	// OLFIX styrprogram
    procorder->addArgument(usr);			// userid
    procorder->addArgument( "ORDUPD");		// OLFIX funktion
    procorder->addArgument("1");			// 1 = uppdatera fältet ORDERSTATUS
    procorder->addArgument(ordernr);		// för ordernr
    procorder->addArgument("F");			// med värdet F (fakturerat)
    
    frmKundFaktura::connect( procorder, SIGNAL(readyReadStdout() ),this, SLOT(updateOrderregDataOnStdout() ) );
    frmKundFaktura::connect( procorder, SIGNAL(readyReadStderr() ),this, SLOT(updateOrderregDataOnStderr() ) );
    frmKundFaktura::connect( procorder, SIGNAL(processExited() ),this, SLOT(updateOrderregEndOfProcess() ) );
    
    if ( !procorder->start() ) {
	// error handling
	QMessageBox::warning( this, "KUFAKTW",
			      "Kan inte starta STYRMAN/ORDUPD! \n" );
    }  
//    qDebug("Slut updateOrderreg");
}

void frmKundFaktura::updateOrderregDataOnStdout()
{
    while (procorder->canReadLineStdout() ) {
	QString line = procorder->readStdout();
	inradorder.append(line);
	inradorder.append("\n");
    }
}

void frmKundFaktura::updateOrderregDataOnStderr()
{
    while (procorder->canReadLineStderr() ) {
	QString line = procorder->readStderr();
	errorradorder.append(line);
	errorradorder.append("\n");
    }
}

void frmKundFaktura::updateOrderregEndOfProcess()
{
//     qDebug("Start updateOrderregEndOfProcess");
     
     int i;
    i = -1;
    i = errorradorder.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "KUFAKTW",
			       "ERROR!\n"+errorradorder
			       );
    } 
    i=-1;
    i = inradorder.find( QRegExp("OK:"), 0 );
    if (i != -1){
	frmKundFaktura::updateOrderradreg();

    }
//   qDebug("Slut updateOrderregEndOfProcess");    
}

void frmKundFaktura::updateOrderradreg()
{
//    qDebug("Start updateOrderradreg");
    
    const char *userp = getenv("USER");
    QString usr(userp);    
    int pr=0;
    QString radnum;
    QString antfakt;
    QString tmp,temp;
    tmp="";
    QListViewItem *mittBarn=listViewRader->firstChild (); 
    
    while( mittBarn ) {
	radnum=mittBarn->text(0);
	antfakt=mittBarn->text(4);
	tmp.append("|");
	tmp.append(ordernr.stripWhiteSpace());
	tmp.append("|");
	tmp.append(radnum);
	tmp.append("|");
	tmp.append(antfakt);
	pr ++;
	mittBarn=mittBarn->nextSibling();	
    }
    temp=temp.setNum(pr);
    tmp=tmp+"|";

    procorad = new QProcess(this);
    procorad->addArgument("./STYRMAN");	// OLFIX styrprogram
    procorad->addArgument(usr);			// userid
    procorad->addArgument( "ORADUPD");		// OLFIX funktion
    procorad->addArgument(temp);			// antal  orderrader
    procorad->addArgument(tmp);			// data

    frmKundFaktura::connect( procorad, SIGNAL(readyReadStdout() ),this, SLOT(updateOrRadDataOnStdout() ) );
    frmKundFaktura::connect( procorad, SIGNAL(readyReadStderr() ),this, SLOT(updateOrRadDataOnStderr() ) );
    frmKundFaktura::connect( procorad, SIGNAL(processExited() ),this, SLOT(updateOrRadEndOfProcess() ) );
    
//    qDebug("Start process, updateOrderradreg");
    
    if ( !procorad->start() ) {
	    QMessageBox::warning( this, "KUFAKTW",
			      "Kan inte starta STYRMAN/ORADUPD! \n" );
	}  
//    qDebug("tmp=%s  temp=%s",tmp.latin1(),temp.latin1());
//    qDebug("Slut updateOrderradreg");
}

void frmKundFaktura::updateOrRadEndOfProcess()
{
//    qDebug("Start updateOrRadEndOfProcess");
     
     int i;
    i = -1;
    i = errorradorderrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "KUFAKTW",
			       "ERROR!\n"+errorradorderrad
			       );
    } 
    i=-1;
    i = inradorderrad.find( QRegExp("OK:"), 0 );
    if (i != -1){
//	qDebug("inradorderrad=%s",inradorderrad.latin1());
    }    
     frmKundFaktura::nextFaktura();
//    qDebug("Slut updateOrRadEndOfProcess");    
}

void frmKundFaktura::updateFakturaDataOnStdout()
{
    while (procfaktura->canReadLineStdout() ) {
	QString line = procfaktura->readStdout();
	inradfaktura.append(line);
	inradfaktura.append("\n");
    }
}
/*
void frmKundFaktura::updateFakturaDataOnStderr()
{
    while (procfaktura->canReadLineStderr() ) {
	QString line = procfaktura->readStderr();
	errorradfaktura.append(line);
	errorradfaktura.append("\n");
    }
}
*/
void frmKundFaktura::TRHDregAddDataOnStderr()
{
    while (proctrhd->canReadLineStderr() ) {
	QString line = proctrhd->readStderr();
	errorradtrhd.append(line);
	errorradtrhd.append("\n");
    }
}

void frmKundFaktura::TRHDregAddDataOnStdout()
{
    while (proctrhd->canReadLineStdout() ) {
	QString line = proctrhd->readStdout();
	inradtrhd.append(line);
	inradtrhd.append("\n");
    }
}

void frmKundFaktura::KresaddDataOnStdout()
{
    while (prockresk->canReadLineStdout() ) {
	QString line = prockresk->readStdout();
	inradkresk.append(line);
	inradkresk.append("\n");
    }
}

void frmKundFaktura::KresaddDataOnStderr()
{
    while (prockresk->canReadLineStderr() ) {
	QString line = prockresk->readStderr();
	errorradkresk.append(line);
	errorradkresk.append("\n");
    }
}

void frmKundFaktura::updateOrRadDataOnStdout()
{
    while (procorad->canReadLineStdout() ) {
	QString line = procorad->readStdout();
	inradorderrad.append(line);
	inradorderrad.append("\n");
    }
}

void frmKundFaktura::updateOrRadDataOnStderr()
{
    while (procorad->canReadLineStderr() ) {
	QString line = procorad->readStderr();
	errorradorderrad.append(line);
	errorradorderrad.append("\n");
    }
}

