/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
/***************************************************************************
                          PRTINKW  -  description
                             -------------------
		     version 0.1
    begin     	: Fre 30 jan 2004
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

    QString inkordernr;
    QString reportpath;
    QString kugarversion;
    QString kommando;

//	Orderhuvud    
    QString ordernr;	// 01
    QString besttyp;	// 02
    QString orderdatum;	// 03
    QString levid;		// 04
    QString levnamn;	// 05
    QString levadr;	// 06
    QString levpostnr;	// 07
    QString levpostadr;	// 08
    QString levland;	// 09
    QString valuta;	// 10
    QString betvillkor;	// 11
    QString levvillkor;	// 12
    QString levsett;	// 13
    QString godsmerke;	// 14
    QString kommentar;	// 15    
    QString besttext;	// 16
    QString varref;	// 17
    QString tfnnr;		// 18
    QString faxnr;		// 19
    QString erref;		// 20
    QString levdatum;	// 21
    QString kundnr;	// 22
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
    QString ftgland;
//    QString kundkat;    
    
    
void frmPrtInk::init()
{
    //	Hämta sökvägen till kugar template. Default /usr/local/olfix/report
    frmPrtInk::GetReportDir();
    frmPrtInk::KugarVersion();
    lineEditBestNr->setFocus();
}

void frmPrtInk::lineEditBestNr_returnPressed()
{
    inkordernr=lineEditBestNr->text();
    if (inkordernr == ""){
        QMessageBox::warning( this, "PRTINKW",
                     "Inköpsordernr saknas! \n" );
	lineEditBestNr->setFocus();
    }
    pushButtonOK->setFocus();
}

void frmPrtInk::pushButtonOK_clicked()
{
    frmPrtInk::GetOrderHeader();
}

void frmPrtInk::CreateReportHeader()
{
    int i;
    QString rad[59];
    QString rapportrad;

    QFile filnamn("/tmp/Bestellning.kud");
    QTextStream stream(&filnamn);

    FileRemove("Bestellning.kud");	// radera gammal fil.

    rad[1]="<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    rad[2]="<!DOCTYPE KugarData [\n";
    rad[3]="   <!ELEMENT KugarData (namn* )>\n";
    rad[4]="   <!ATTLIST KugarData\n";
    rad[5]="      Template CDATA #REQUIRED>\n\n";
    rad[6]="   <!ELEMENT namn EMPTY>\n";
    rad[7]="   <!ATTLIST namn\n";
    rad[8]="      level CDATA #REQUIRED\n";
    rad[9]="      ftgnamn CDATA #REQUIRED\n";
    rad[10]="      datum CDATA #REQUIRED\n";
    rad[11]="      bestnr CDATA #REQUIRED\n";
    rad[12]="      sida CDATA #REQUIRED\n";
    rad[13]="      levnr CDATA #REQUIRED\n";
    rad[14]="      levnamn CDATA #REQUIRED\n";
    rad[15]="      levpostbox CDATA #REQUIRED\n";
    rad[16]="      levpostnr CDATA #REQUIRED\n";
    rad[17]="      levpostadr CDATA #REQUIRED\n";
    rad[18]="      levland CDATA #REQUIRED\n";
    rad[19]="      fortag CDATA #REQUIRED\n";
    rad[20]="      ftglevadr CDATA #REQUIRED\n";
    rad[21]="      ftgpostnr CDATA #REQUIRED\n";
    rad[22]="      ftgpostadr CDATA #REQUIRED\n";
    rad[23]="      ftgland CDATA #REQUIRED\n";
    rad[24]="      kommentar CDATA #REQUIRED\n";
    rad[25]="      betvillkor CDATA #REQUIRED\n";
    rad[26]="      Tfn CDATA #REQUIRED\n";
    rad[27]="      Fax CDATA #REQUIRED\n";
    rad[28]="      levvillkor CDATA #REQUIRED\n";
    rad[29]="      valuta CDATA #REQUIRED\n";
    rad[30]="      levsett CDATA #REQUIRED\n";
    rad[31]="      erref CDATA #REQUIRED\n";
    rad[32]="      varref CDATA #REQUIRED\n";
    rad[33]="      godsmerke CDATA #REQUIRED\n";
    rad[34]=">\n";
    rad[35]="  <!ELEMENT KugarData (Rad*)>\n";
    rad[36]="  <!ATTLIST KugarData\n";
    rad[37]="      Template CDATA #REQUIRED>\n\n";
    rad[38]="  <!ELEMENT Rad EMPTY>\n";
    rad[39]="  <!ATTLIST Rad\n";
    rad[40]="      level CDATA #REQUIRED\n";
    rad[41]="      pos CDATA #REQUIRED\n";
    rad[42]="      vartnr CDATA #REQUIRED\n";
    rad[43]="      erartnr CDATA #REQUIRED\n";
    rad[44]="      antal CDATA #REQUIRED\n";
    rad[45]="      sort CDATA #REQUIRED\n";
    rad[46]="      pris CDATA #REQUIRED\n";
    rad[47]="      levtid CDATA #REQUIRED\n";
    rad[48]=">\n";
    rad[49]="  <!ELEMENT KugarData (txt*)>\n";
    rad[50]="  <!ATTLIST KugarData\n";
    rad[51]="      Template CDATA #REQUIRED>\n\n";
    rad[52]="  <!ELEMENT txt EMPTY>\n";
    rad[53]="  <!ATTLIST txt\n";
    rad[54]="      level CDATA #REQUIRED\n";
    rad[55]="      ordertext CDATA #REQUIRED\n";
    rad[56]=">\n";
    rad[57]="]>\n\n";
    rad[58]="<KugarData Template=\"";
    rad[58].append(reportpath);
    rad[58].append("Bestellning.kut\">\n");	// ange rätt template, absolut path
//    qDebug("CreateReportHeader::template=%s",rad[58].latin1());
    rapportrad=rad[1];
    for (i=2;i<59;i++){
	rapportrad.append(rad[i]);
    }
//    qDebug("CreateHeader::rapportrad = \n%s",rapportrad.latin1());
    rapportrad.append("<namn level=\"0");
    rapportrad.append("\" ftgnamn=\"");
    rapportrad.append(ftgnamn);
    rapportrad.append("\" datum=\"");
    rapportrad.append(orderdatum);
    rapportrad.append("\" bestnr=\"");
    rapportrad.append(ordernr);
    rapportrad.append("\" sida=\"");
    rapportrad.append(" 1");
    rapportrad.append("\" levnr=\"");
    rapportrad.append(levid);
    rapportrad.append("\" levnamn=\"");
    rapportrad.append(levnamn);
    rapportrad.append("\" levpostbox=\"");
    rapportrad.append(levadr);
    rapportrad.append("\" levpostnr=\"");
    rapportrad.append(levpostnr);
    rapportrad.append("\" levpostadr=\"");
    rapportrad.append(levpostadr);
    rapportrad.append("\" levland=\"");
    rapportrad.append(levland);
    rapportrad.append("\" fortag=\"");
    rapportrad.append(ftgnamn);
    rapportrad.append("\" ftglevadr=\"");
    rapportrad.append(ftgadr);
    rapportrad.append("\" ftgpostnr=\"");
    rapportrad.append(ftgpostnr);
    rapportrad.append("\" ftgpostadr=\"");
    rapportrad.append(ftgpostadr);
    rapportrad.append("\" ftgland=\"");
    rapportrad.append(ftgland);
    rapportrad.append("\" kommentar=\"");
    rapportrad.append(kommentar);
    rapportrad.append("\" betvillkor=\"");
    rapportrad.append(betvillkor);
    rapportrad.append("\" Tfn=\"");
    rapportrad.append(tfnnr);
    rapportrad.append("\" Fax=\"");
    rapportrad.append(faxnr);
    
//      Tfn="09-199992" Fax="09-199998"
    rapportrad.append("\" levvillkor=\"");
    rapportrad.append(levvillkor);
    rapportrad.append("\" valuta=\"");
    rapportrad.append(valuta);
    rapportrad.append("\" levsett=\"");
    rapportrad.append(levsett);
    rapportrad.append("\" erref=\"");
    rapportrad.append(erref);
    rapportrad.append("\" varref=\"");
    rapportrad.append(varref);
    rapportrad.append("\" godsmerke=\"");
    rapportrad.append(godsmerke);
    rapportrad.append("\"/>\n");
    
    filnamn.open( IO_WriteOnly | IO_Append );
    stream << rapportrad;
//    qDebug("CreateHeader::ordernr=  %s",ordernr.latin1());
    filnamn.close();
}


void frmPrtInk::GetOrderHeader()
{
/************************************************************************/
/*	Hämta orderhuvud, INKREG	 				*/
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

	frmPrtInk::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(DataOnStdout() ) );
	frmPrtInk::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(DataOnStderr() ) );
            frmPrtInk::connect( process, SIGNAL(processExited() ),this, SLOT(OrderHuvudEndOfProcess() ) );
	    
	if (inkordernr == ""){
    	    QMessageBox::warning( this, "PRTINKW",
                      "Inköpsordernr saknas! \n" );
	    lineEditBestNr->setFocus();
	}
	else {
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/INKDSP!\n");
		QMessageBox::warning( this, "PRTINKW",
                            "Kan inte starta STYRMAN/INKHDSP! \n" );
	    }
	}
}

void frmPrtInk::GetOrderRow()
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

	frmPrtInk::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(DataOnStdout() ) );
	frmPrtInk::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(DataOnStderr() ) );
            frmPrtInk::connect( process, SIGNAL(processExited() ),this, SLOT(RaderEndOfProcess() ) );

	if (inkordernr == ""){
    	    QMessageBox::warning( this, "PRTINKW",
                      "inkällningsnr saknas \n" );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		QMessageBox::warning( this, "PRTINKW",
                            "Kan inte starta STYRMAN/INKRDSP! \n" );
	    }
	}
}

void frmPrtInk::OrderHuvudEndOfProcess()
{
    int i,m;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
 //   qDebug("Error:",errorrad);
    if (i != -1) {
	QMessageBox::critical( this, "PRTINKW",
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

	    m=i2-i1;
	    if (i1 != -1){
		ordernr=inrad.mid(i1+3,m-4);
	    }

	    m=i3-i2;
	    if (i2 != -1){
	  	besttyp=inrad.mid(i2+3,m-4);
	    }

	    m=i4-i3;
	    if (i3 != -1){
		orderdatum=inrad.mid(i3+3,m-4);
	    }

	    m=i5-i4;
	    if (i4 != -1){
		levid=inrad.mid(i4+3,m-4);
	    }

	    m=i6-i5;
	    if (i5 != -1){
		levnamn=inrad.mid(i5+3,m-4);
	    }

	    m=i7-i6;
	    if (i6 != -1){
		levadr=inrad.mid(i6+3,m-4);
	    }

	    m=i8-i7;
	    if (i7 != -1){
		levpostnr=inrad.mid(i7+3,m-4);
	    }

	    m=i9-i8;
	    if (i8 != -1){
		levpostadr=inrad.mid(i8+3,m-4);
	    }

	    m=i10-i9;
	    if (i9 != -1){
		levland=inrad.mid(i9+3,m-4);
	    }

	    m=i11-i10;
	    if (i10 != -1){
		valuta=inrad.mid(i10+3,m-4);
	    }

	    m=i12-i11;
	    if (i11 != -1){
		betvillkor=inrad.mid(i11+3,m-4);
	    }

	    m=i13-i12;
	    if (i12 != -1){
		levvillkor=inrad.mid(i12+3,m-4);
	    }

	    m=i14-i13;
	    if (i13 != -1){
		levsett=inrad.mid(i13+3,m-4);
	    }

	    m=i15-i14;
	    if (i14 != -1){
		godsmerke=inrad.mid(i14+3,m-4);
	    }

	    m=i16-i15;
	    if (i15 != -1){
		kommentar=inrad.mid(i15+3,m-4);
	    }

	    m=i17-i16;
	    if (i16 != -1){
		besttext=inrad.mid(i16+3,m-4);
	    }

	    m=i18-i17;
	    if (i17 != -1){
		varref=inrad.mid(i17+3,m-4);
	    }

	    m=i19-i18;
	    if (i18 != -1){
		tfnnr=inrad.mid(i18+3,m-4);
	    }

	    m=i20-i19;
	    if (i19 != -1){
		faxnr=inrad.mid(i19+3,m-4);
	    }

	    m=i21-i20;
	    if (i20 != -1){
		erref=inrad.mid(i20+3,m-4);
	    }
	    
	    m=i22-i21;
	    if (i21 != -1){
		levdatum=inrad.mid(i21+3,m-4);
	    }

	    m=i23-i22;
	    if (i22 != -1){
		kundnr=inrad.mid(i22+3,m-4);
	    }
	    
	    m=i24-i23;
	    if (i23 != -1){
		ftgnamn=inrad.mid(i23+3,m-4);
	    }

	    m=i25-i24;
	    if (i24 != -1){
		ftgadr=inrad.mid(i24+3,m-4);
	    }
	    
	    m=i26-i25;
	    if (i25 != -1){
		ftgpostnr=inrad.mid(i25+3,m-4);
	    }
	    	    
	    m=i27-i26;
	    if (i26 != -1){
		ftgpostadr=inrad.mid(i26+3,m-4);
	    }
	    
	    m=i28-i27;
	    if (i27 != -1){
		sprakkod=inrad.mid(i27+3,m-4);
	    }
	    
	    m=i29-i28;
	    if (i28 != -1){
		bekreftad=inrad.mid(i28+3,m-4);
	    }
	    
	    m=i30-i29;
	    if (i29 != -1){
		orderstatus=inrad.mid(i29+3,m-4);
	    }
	    
	    m=i31-i30;
	    if (i30 != -1){
		utskriftkod=inrad.mid(i30+3,m-4);
	    }
	    
	    m=i32-i31;
	    if (i31 != -1){
		total=inrad.mid(i31+3,m-4);
	    }
	    
	    inrad="";
	    errorrad="";
	    inrad="";
	    i = -1;
	}	
    }
    errorrad="";
//********************************************************    
//	Skapa orderhuvud
//********************************************************        
    frmPrtInk::CreateReportHeader();
//********************************************************    
//	Hämta orderrader    
//********************************************************    
    frmPrtInk::GetOrderRow();
}

void frmPrtInk::RaderEndOfProcess()
{
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
//  ---------------------------
    QFile filnamn("/tmp/Bestellning.kud");
    QTextStream stream(&filnamn);
    QString bestrad;	// beställningsrad
    
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
 //   qDebug("Error:",errorrad);
    if (i != -1) {
	QMessageBox::critical( this, "PRTINKW",
		"ERROR!\n"+errorrad
	);
    }else{
	i = inrad.find( QRegExp("OK: NR_0_"), 0 );
	if (i != -1) {
	    QMessageBox::information( this, "PRTINKW",
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
// ----------------------------------------------------------------
//	Öppna filen Bestellning.kud
// ----------------------------------------------------------------
	    filnamn.open( IO_WriteOnly | IO_Append );
// -----------------------------------------------------------------
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
		bestrad="<Rad level=\"1\" ";
		bestrad.append(" pos=\"");
		bestrad.append(radnr);
		bestrad.append("\" vartnr=\"");
		bestrad.append(artikelnr);
		bestrad.append(" \n");
		bestrad.append(benemning);
		bestrad.append("\" erartnr=\"");
		bestrad.append("");
		bestrad.append("\" antal=\"");
		bestrad.append(bestantal);
		bestrad.append("\" sort=\"");
		bestrad.append("");
		bestrad.append("\" pris=\"");
		bestrad.append(inkpris);
		bestrad.append("\" levtid=\"");
		bestrad.append(levvecka);	    
		bestrad.append("\"/>\n");
//		qDebug("slotEndOfProcess() 3d ::bestrad=%s",bestrad.latin1());
		stream << bestrad;		
	    }
	}
//	stream << bestrad;
	filnamn.close();
	CreateReportFot();
    }
}

void frmPrtInk::CreateReportFot()
{
    QFile filnamn("/tmp/Bestellning.kud");
    QTextStream stream(&filnamn);
    QString bestrad;	// beställningsrad

    filnamn.open( IO_WriteOnly | IO_Append );
    
    bestrad="<txt level=\"2\" ";
    bestrad.append(" ordertext=\"");
    bestrad.append(besttext);
    bestrad.append("\"/>\n");
    bestrad.append("</KugarData>");
    
    stream << bestrad;
    filnamn.close();
    frmPrtInk::CallKugar();
}

void frmPrtInk::DataOnStdout()
{
     while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmPrtInk::DataOnStderr()
{
      while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmPrtInk::GetReportDir()
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
	    i= -1;
	}
    }   
    file.close ();
//    qDebug("reportpath=  %s",reportpath.latin1());
}

void frmPrtInk::FileRemove(QString filnamn)
{
//  Ta bort temporärfilen /tmp/Bestellning.kud eller filen /tmp/Bestellning.txt
    bool status;
    QDir d = QDir::root();                   // "/"
    if ( !d.cd("tmp") ) {                       // "/tmp"
        qWarning( "Cannot find the \"/tmp\" directory" );
    }
//    qDebug("filnamn=%s",filnamn.latin1());
    status=d.remove(filnamn,FALSE);
}

void frmPrtInk::KugarVersion()
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
   frmPrtInk::FileRemove("kugarversion.txt");
}

void frmPrtInk::CallKugar()
{
    if (kugarversion<"1.2.92"){
	kommando="kugar -d /tmp/Bestellning.kud -r "+reportpath+"Bestellning.kut";
//	qDebug("kommando=%s",kommando.latin1());
	system(kommando);
    }else{
	system("kugar  /tmp/Bestellning.kud");
    }
    
}
