/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
/****************************************************************************
                          KUFAKTBW  -  description
                             -------------------
		     version 0.1
    begin                	: Sön   4 dec    2005
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
 *****************************************************************/
// #include <qobject.h>
// #include <qnamespace.h> 
#include <qapplication.h>
#include <qmessagebox.h>
#include <qprocess.h>
#include <qdir.h>
#include <stdlib.h>
#include <qstring.h>
#include <qfile.h>
#include <qregexp.h>
#include <qdatetime.h>
#include <qcheckbox.h>
#include <qthread.h>
#include <qlistview.h>
#define MAXSTRING 15000

    int processnbr=0;
    QProcess*  processhelp;
    QProcess*  processresk;
    QProcess*  faktproc[200];
    QProcess*  updateproc[200]; 
    QProcess*  ftgdataproc;
    QProcess*  vernrproc;
    QProcess*  barproc;
    
    QString inrad;
    QString errorrad;    
    QString reskinrad;
    QString reskerrorrad;
    QString faktinrad;
    QString fakterrorrad;
    QString updateinrad;
    QString updateerrorrad;
    QString ftginrad;
    QString barinrad;

    QString hjelpfil;

    QString datum;				// = registreringsdatum för fakturan.
    QString bar;					// bar = bokföringsår
    QString fakturanummer;
    QString kundnr;
    QString belopp;				// fakturabelopp
    QString fakturadatum;				// datum då fakturan skapades
    QString betald;				// Är fakturan betald J/N
    QString debetkto;
    QString debetbelopp;
    QString kreditkto;
    QString kreditbelopp;
    QString vernr;					// verifikationsnummer för bokföring
    QString ordernr;
    QString faktnr;
    
    bool bokflag;
    QString val;					// Används för att checka fakturor
    int checkstatus=TRUE;
    
void frmKundfakturaBetald::init()
{
    QDateTime dt = QDateTime::currentDateTime();    
    datum=dt.toString("yyyy-MM-dd");
    textLabelDatum->setText(datum);    				/* = registreringsdatum för fakturan. */
    frameBokforing->hide();
    frmKundfakturaBetald::listView_format();				/* formater storleken på kolummerna i listorna */
    frmKundfakturaBetald::getKundReskontraLista();	  		/* Hämta obetalda kundfakturor, kundreskontra */
    frmKundfakturaBetald::getForetagsData("KFKTO"); 		/*  konto för kundfordringar i FTGDATA */
    lineEditFakturaNr->setFocus();
}

void frmKundfakturaBetald::lineEditFakturaNr_returnPressed()
{    
    QString tmp;
    checkstatus=TRUE;
    fakturanummer = lineEditFakturaNr->text();
    tmp = fakturanummer.stripWhiteSpace();
//    qDebug("lineEditFakturaNr::fakturanummer=%s tmp=%s",fakturanummer.latin1(),tmp.latin1());
    if (tmp == "") {
	QMessageBox::warning( 0,
			      tr("KUFAKTBW"),
			      tr("Fakturanummer får inte vara blank!"),
			      tr("OK") );
	lineEditFakturaNr->setFocus();
    }else{
	getKundFaktura();
	bokflag=checkBoxBokforing->isChecked();
	if (bokflag) {
	    lineEditDebetKto->setFocus();
	}else{
	    listViewKundFakturor->setFocus();
	}
    }
}

void frmKundfakturaBetald::pushButtonCancel_clicked()
{
    close() ;
}

void frmKundfakturaBetald::checkBoxBokforing_checked()
{
    bokflag=checkBoxBokforing->isChecked();
    if (!bokflag) {
	frameBokforing->hide();
    }
    if(bokflag) {
	frameBokforing->show();
    }
}

void frmKundfakturaBetald::lineEditBar_returnPressed()
{
    bar=lineEditBar->text();
    bar=bar.upper();
    bar=bar.stripWhiteSpace();
    if (bar==""){
	QMessageBox::critical( this, "KUFAKTBW","Bokföringsår får inte vara blank!\n");
	lineEditBar->setFocus();
    }else{
	lineEditBar->setText(bar);
	frmKundfakturaBetald::getVernr(bar);
	lineEditDebetKto->setFocus();
    }
}

void frmKundfakturaBetald::lineEditDebetKto_returnPressed()
{
    debetkto=lineEditDebetKto->text();
    lineEditDebetBelopp->setFocus();
}

void frmKundfakturaBetald::lineEditDebetBelopp_returnPressed()
{
    debetbelopp=lineEditDebetBelopp->text();
    lineEditKreditKto->setFocus();
}

void frmKundfakturaBetald::lineEditKreditKto_returnPressed()
{
    kreditkto=lineEditKreditKto->text();
    lineEditKreditBelopp->setFocus();
}

void frmKundfakturaBetald::lineEditKreditBelopp_returnPressed()
{
    kreditbelopp=lineEditKreditBelopp->text();
    listViewKundFakturor->setFocus();
}

void frmKundfakturaBetald::pushButtonRight_clicked()
{
//    qDebug("Right");
    fakturanummer=lineEditFakturaNr->text();
    getKundFaktura();				// Hämta fräsha data för fakturan

    QListViewItem *item =  listViewKundFakturor->currentItem();
    if ( !item ){
	return;
    }
    if (!item->isSelected()){
	QMessageBox::warning( this, "KUFAKTBW","Ingen faktura är vald!\n" );
	return;
    }
    QString temp0=item->text(0);			// fakturanr
    QString temp1=item->text(1);			// fakturadatum
    QString temp2=item->text(2);			// kundnr
    QString temp3=lineEditBelopp->text();		// belopp
    QString temp4=lineEditDebetKto->text();		// debetkonto
    QString temp5=lineEditDebetBelopp->text();	// debetbelopp
    QString temp6=lineEditKreditKto->text();		// kreditkonto
    QString temp7=lineEditKreditBelopp->text();	// kreditbelopp
    delete listViewKundFakturor->currentItem();
    bokflag=checkBoxBokforing->isChecked();
    if (!bokflag) {
//	qDebug("FALSE");
	bar="";
	vernr="";
	item = new QListViewItem(listViewBetalda,temp0,temp3,temp2,temp1,ordernr,datum);
    }else{
	item = new QListViewItem(listViewBetalda,temp0,temp3,temp2,temp1,ordernr,datum,bar,vernr);
	item->setText(8,temp4);
	item->setText(9,temp5);
	item->setText(10,temp6);
	item->setText(11,temp7);
    }
}

void frmKundfakturaBetald::pushButtonLeft_clicked()
{
//    QString message="Ingen faktura är utvald!\n";
    //    qDebug("Left");
    QListViewItem *item =  listViewBetalda->currentItem();
    if ( !item ){
	return;
    }
    if (!item->isSelected()){
	QMessageBox::warning( this, "KUFAKTBW","Ingen faktura är utvald!\n" );
	return;
    }
    QString temp0=item->text(0);	// fakturanr
    QString temp1=item->text(1);	// belopp
    QString temp2=item->text(2);	// kundnr
    QString temp3=item->text(3);	// fakturadatum
    delete listViewBetalda->currentItem();
    item = new QListViewItem(listViewKundFakturor,temp0,temp3,temp2);
}

void frmKundfakturaBetald::pushButtonOK_clicked()
{
    /**********************************************************************/
    /*	Uppdatera kundreskontran, bokföringen och historiken(TRHD)		*/
    /**********************************************************************/    
    QString record;
    QString fnr;
    QString fsumma;
    QString knr;
    QString fdatum;
    QString onr;
    QString bdatum;
    QString bokfar;
    QString vnr;
    QString dkto;
    QString dktosum;
    QString kkto;
    QString kktosum;
    
    pushButtonOK->setEnabled(FALSE);
    QListViewItem *myChild=listViewBetalda->firstChild ();
    while( myChild ) {
	fnr=myChild->text(0);
	fsumma=myChild->text(1);
	knr=myChild->text(2);
	fdatum=myChild->text(3);
	onr=myChild->text(4);
	bdatum=myChild->text(5);
	bokfar=myChild->text(6);
	vnr=myChild->text(7);
	dkto=myChild->text(8);
	dktosum=myChild->text(9);
	kkto=myChild->text(10);
	kktosum=myChild->text(11);
	
	record=";";
	record.append(fnr);
	record.append(";");
	record.append(fsumma);
	record.append(";");	
	record.append(knr);
	record.append(";");
	record.append(fdatum);
	record.append(";");	
	record.append(onr);
	record.append(";");	
	record.append(bdatum);
	record.append(";");	
	record.append(bokfar);
	record.append(";");	
	record.append(vnr);
	record.append(";");
	record.append(dkto);
	record.append(";");
	record.append(dktosum);
	record.append(";");
	record.append(kkto);
	record.append(";");
	record.append(kktosum);
	record.append(";END");
	qDebug("record=%s",record.latin1());
	listViewBetalda->setCurrentItem(myChild);
//	doSomething( myChild );
	myChild = myChild->nextSibling();
	delete listViewBetalda->currentItem();
	updateKundFaktura(record);
    }
    pushButtonOK->setEnabled(TRUE);
}

void frmKundfakturaBetald::getKundFaktura()
{
//    qDebug("getKundFaktura()  Start");
    /**********************************************************************/
    /*	Hämta vald faktura	  	 				*/
    /**********************************************************************/    
    const char *userp = getenv("USER");
    QString usr(userp);
    processnbr++;
    if (processnbr>175) {
	processnbr=1;
    }    
    if (fakturanummer==""){
	fakturanummer="1";
    }
    faktinrad="";
    fakterrorrad="";
    faktproc[processnbr] = new QProcess();
    faktproc[processnbr]->addArgument("./STYRMAN");	// OLFIX styrprogram
    faktproc[processnbr]->addArgument(usr);		// userid
    faktproc[processnbr]->addArgument( "FAKTDSP");	// OLFIX funktion
    faktproc[processnbr]->addArgument(fakturanummer);
//    qDebug("getKundFaktura()  Argument fakturanr=%s",fakturanummer.latin1());
    frmKundfakturaBetald::connect( faktproc[processnbr], SIGNAL(readyReadStdout() ),this, SLOT(FaktDataOnStdout() ) );
    frmKundfakturaBetald::connect( faktproc[processnbr], SIGNAL(readyReadStderr() ),this, SLOT(FaktDataOnStderr() ) );
    frmKundfakturaBetald::connect( faktproc[processnbr], SIGNAL(processExited() ),this, SLOT(FaktEndOfProcess() ) );
//    qDebug("getKundFaktura()  FAKTDSP start processnbr=%d",processnbr);
    
    if ( !faktproc[processnbr]->start() ) {
	    // error handling
	    QMessageBox::warning( this, "KUFAKTBW",
				  "Kan inte starta STYRMAN/FAKTDSP! \n" );
	}    
}

void frmKundfakturaBetald::FaktDataOnStderr()
{
//    qDebug("FaktDataOnStderr()   Start");
    while (faktproc[processnbr]->canReadLineStderr() ) {
	QString line = faktproc[processnbr]->readStderr();
	fakterrorrad.append(line);
	fakterrorrad.append("\n");
    }
//    qDebug("FaktDataOnStderr()   Slut errorrad=%s",errorrad.latin1());
}

void frmKundfakturaBetald::FaktDataOnStdout()
{
    while (faktproc[processnbr]->canReadLineStdout() ) {
	QString line = faktproc[processnbr]->readStdout();
	faktinrad.append(line);
	faktinrad.append("\n");
    }
}

void frmKundfakturaBetald::FaktEndOfProcess()
{
//    qDebug("FaktEndOfProcess()   Start");
    QString tmp;
    QString debetktonr;        
    int i,i1,m;

    tmp=faktinrad;
    tmp=tmp.stripWhiteSpace();
//    qDebug("faktinrad=|%s|",tmp.latin1());
    if (tmp==""){
		QMessageBox::critical( this, "KUFAKTBW",
			       "Finns inget data eller FAKTDSP saknas!\n"
			       );
	    }
    i = -1;
    i = fakterrorrad.find( QRegExp("Error:"), 0 );
    //   qDebug("Error: %s",fakterrorrad.latin1());
    if (i != -1) {
	QMessageBox::critical( this, "KUFAKTBW",
			       "ERROR!\n"+fakterrorrad
			       );
	lineEditFakturaNr->setFocus();
    }
    i = -1;
    i = faktinrad.find( QRegExp("OK:"), 0 );
    if (i != -1)  {
	i=-1;
	i = faktinrad.find( QRegExp("_:ORDERNR:"), 0 );
	if (i != -1)  {
	    i1= faktinrad.find( QRegExp("_:"), i+3 );
	    m=i1-(i+10);
	    ordernr=faktinrad.mid(i+10,m);
//	    qDebug("i=%d, i1=%d, m=%d, ordernr=%s",i,i1,m,ordernr.latin1());	    
	}
	i=-1;
	i = faktinrad.find( QRegExp("_:FAKTURADATUM:"), 0 );
	if (i != -1)  {
	    i1= faktinrad.find( QRegExp("_:"), i+3 );
	    m=i1-(i+10);
	    fakturadatum=faktinrad.mid(i+10,m);
//	    qDebug("i=%d, i1=%d, m=%d, ordernr=%s",i,i1,m,ordernr.latin1());
	}
	i=-1;
	i = faktinrad.find( QRegExp("_:FAKTURABELOPP:"), 0 ); 
	if (i != -1)  {
	    i1= faktinrad.find( QRegExp("_:"), i+3 );
	    m=i1-(i+16);
	    belopp=faktinrad.mid(i+16,m);
//	    qDebug("i=%d, i1=%d, m=%d, belopp=%s",i,i1,m,belopp.latin1());
	}
	i=-1;
	i = faktinrad.find( QRegExp("_:BETALD:"), 0 ); 
	if (i != -1)  {
	    i1= faktinrad.find( QRegExp("_:"), i+3 );
	    m=i1-(i+9);
	    betald=faktinrad.mid(i+9,m);
//	    qDebug("i=%d, i1=%d, m=%d, betald=%s",i,i1,m,betald.latin1());
	}	
	i=-1;
	i = faktinrad.find( QRegExp("_:KTONR:"), 0 ); 
	if (i != -1)  {
	    i1= faktinrad.find( QRegExp("_:"), i+3 );
	    m=i1-(i+8);
	    debetktonr=faktinrad.mid(i+8,m);
//	    qDebug("i=%d, i1=%d, m=%d, debetkto=%s",i,i1,m,debetkto.latin1());
	    if (debetktonr=="0000"){
		debetkto=debetktonr;
	    }
	}
	lineEditDebetKto->setFocus();
    }
    betald=betald.stripWhiteSpace();
    if (betald != "J"){			// Fakturan redan betald
	lineEditOrdernr->setText(ordernr);
	lineEditBelopp->setText(belopp);    
	lineEditDebetKto->setText(debetkto);
	lineEditDebetBelopp->setText(belopp);
	lineEditKreditBelopp->setText(belopp);
	tmp=lineEditKreditKto->text();
	if (tmp==""){
	    lineEditKreditKto->setText(kreditkto);
	}
    }else{
	QMessageBox::warning( 0,
	      tr("KUFAKTBW"),
	      tr("Fakturanummer är redan betald!"),
	      tr("OK") );
	lineEditOrdernr->clear();
	lineEditBelopp->clear();
	lineEditDebetKto->clear();
	lineEditDebetBelopp->clear();
	lineEditKreditKto->clear();
	lineEditKreditBelopp->clear();
	lineEditFakturaNr->setFocus();
    }
}

void frmKundfakturaBetald::getKundReskontraLista()
{
    /**********************************************************************/
    /*	Hämta kundreskontraposter	  	 				*/
    /**********************************************************************/
    const char *userp = getenv("USER");
    QString usr(userp);

    listViewKundFakturor->clear();
    reskinrad="";
    reskerrorrad="";
    
    processresk = new QProcess();
    processresk->addArgument("./STYRMAN");	// OLFIX styrprogram
    processresk->addArgument(usr);		// userid
    processresk->addArgument( "KRESLST");	// OLFIX funktion
    processresk->addArgument("2");		// 2 = använd fakturadatum i svaret

    frmKundfakturaBetald::connect( processresk, SIGNAL(readyReadStdout() ),this, SLOT(KreskDataOnStdout() ) );
    frmKundfakturaBetald::connect( processresk, SIGNAL(readyReadStderr() ),this, SLOT(KreskDataOnStderr() ) );
    frmKundfakturaBetald::connect( processresk, SIGNAL(processExited() ),this, SLOT(KreskEndOfProcess() ) );

    if ( !processresk->start() ) {
	    // error handling
	    QMessageBox::warning( this, "KUFAKTBW",
				  "Kan inte starta STYRMAN/KRESLST! \n" );
	}
}

void frmKundfakturaBetald::KreskDataOnStderr()
{
    while (processresk->canReadLineStderr() ) {
	QString line = processresk->readStderr();
	reskerrorrad.append(line);
	reskerrorrad.append("\n");
    }
}

void frmKundfakturaBetald::KreskDataOnStdout()
{
    while (processresk->canReadLineStdout() ) {
	QString line = processresk->readStdout();
	reskinrad.append(line);
	reskinrad.append("\n");
    }
}


void frmKundfakturaBetald::KreskEndOfProcess()
{
    QListViewItem* item;

    QString tmp = "";
    QString faktnr;
    QString kundnr;
    QString belopp;
    QString faktdatum;
    
    QString ordernr;
    QString status;
    QString antalrader;
    
    int i,i1,i2,i3,i4,l,m,n;
    int antrad;
    listViewKundFakturor->clear();    
    tmp = reskinrad.stripWhiteSpace();
    if (tmp == ""){
	QMessageBox::critical( this, "KUFAKTBW", "Finns inget data eller KRELST saknas!\n" );
    }else{
	tmp="";
	i = -1;
	i = reskerrorrad.find( QRegExp("Error:"), 0 );
//   	qDebug("Error:",errorrad.latin1());
	if (i != -1) {
	    QMessageBox::critical( this, "KUFAKTBW","ERROR!\n"+reskerrorrad);
	}
	i = -1;
	i = reskinrad.find( QRegExp("OK:"), 0 );
//	qDebug("inrad=%s",inrad.latin1());
	if (i != -1)  {
//	    qDebug("i=%d",i);
	    /****************************************/
	    /*  Hämta data från kundreskontran KURESK  */
	    /****************************************/	    
	    m = 0;
	    i1 = reskinrad.find( QRegExp("OK: NR_"), m); 		// startposition
	    i2 = reskinrad.find( QRegExp("_:"), m );			// slutposition för antal rader
	    l = i2 - (i1 + 7);
	    antalrader = reskinrad.mid(i1 + 7,l);
	    antrad = antalrader.toInt();
//	    qDebug("antalrader=%s antrad=%d",antalrader.latin1(),antrad);
	    m = i2;
//	    qDebug("i1=%d i2=%d l=%d m=%d",i1,i2,l,m);
	    i3 = reskinrad.find( QRegExp("_:_"), m );
	    for (n = 0 ; n < antrad ; n ++) {
		i4 = reskinrad.find( QRegExp("_:_"), i3 + 1 );
		l = i4 - i3 - 3;
		ordernr = reskinrad.mid(i3 + 3,l);
//		qDebug("m=%d i3=%d i4=%d l=%d ordernr=%s",m,i3,i4,l,ordernr.latin1());
		m = i4 + 3;
		i3 = i4;
		i4 = reskinrad.find( QRegExp("_:_"), i3 +1);
		l = i4 - i3 - 3;
		faktnr = reskinrad.mid(i3+3,l);
//		qDebug("faktnr=%s",faktnr.latin1());
//		qDebug("m=%d i3=%d i4=%d l=%d faktnr=%s",m,i3,i4,l,faktnr.latin1());
		m = i4 + 3;
		i3 = i4;
		i4 = reskinrad.find( QRegExp("_:_"),i3 +1);
		l = i4 - i3 - 3;
		kundnr = reskinrad.mid(i3+3,l);
//		qDebug("m=%d i3=%d i4=%d l=%d kundnr=%s",m,i3,i4,l,kundnr.latin1());
		m = i4 + 3;
		i3 = i4;
		i4 = reskinrad.find( QRegExp("_:_"), i3 +1);
		l = i4 - i3 - 3;
		belopp = reskinrad.mid(i3+3,l);
//		qDebug("m=%d i3=%d i4=%d l=%d belopp=%s",m,i3,i4,l,belopp.latin1());	
		m = i4 + 3;
		i3 = i4;
		i4 = reskinrad.find( QRegExp("_:_"), i3 +1);
		l = i4 - i3 - 3;
		faktdatum = reskinrad.mid(i3+3,l);
//		qDebug("m=%d i3=%d i4=%d l=%d faktdatum=%s",m,i3,i4,l,faktdatum.latin1());
		m = i4 + 3;
		i3 = i4;
		i4 = reskinrad.find( QRegExp("_:_"), i3 +1);
		l=i4-i3-3;
		status = reskinrad.mid(i3+3,l);
//		qDebug("m=%d i3=%d i4=%d l=%d status=%s",m,i3,i4,l,status.latin1());
		status=status.stripWhiteSpace();
		if ( status == "N"){
		    item = new QListViewItem(listViewKundFakturor,faktnr,faktdatum,kundnr);
		}
		m = i4 + 3;
		i3 = i4;
	    }
	}else{
	    QMessageBox::warning( this, "KUFAKTBW", "Felaktiga data från databasen!!\n");
	}
	lineEditFakturaNr->setFocus();
    }
}

void  frmKundfakturaBetald::listViewKundFakturor_clicked( QListViewItem * )
{
    lineEditFakturaNr->clear();
    lineEditOrdernr->clear();
    lineEditBelopp->clear();
    lineEditDebetKto->clear();
    lineEditDebetBelopp->clear();
    lineEditKreditKto->clear();
    lineEditKreditBelopp->clear();
    
    QListViewItem *item =  listViewKundFakturor->currentItem();
    if ( !item )
	return;
    item->setSelected( TRUE );
    QString temp0=item->text(0);	// fakturanr
    QString temp1=item->text(1);	// fakturadatum
    QString temp2=item->text(2);	// kundnr
/*    
    QString temp3=item->text(3);	// ?
    QString temp4=item->text(4);	// ?
    QString temp5=item->text(5);	// ?
    QString temp6=item->text(6);	// ?
    QString temp7=item->text(7);	// ?
    QString temp8=item->text(8);	// ?
*/
    fakturanummer=temp0;
    lineEditFakturaNr->setText(fakturanummer);
    getKundFaktura();
    lineEditFakturaNr->setFocus();
}
    
void frmKundfakturaBetald::listView_format()
{
    listViewKundFakturor->setColumnWidth(0,70);		// Fakturanr
    listViewKundFakturor->setColumnWidth(1,90);		// Fakturadatum
    listViewKundFakturor->setColumnWidth(2,70);		// Kundnr
/*    listViewKundFakturor->setColumnWidth(3,86);		// ?
    listViewKundFakturor->setColumnWidth(4,65);		// ?
    listViewKundFakturor->setColumnWidth(5,66);		// ?
    listViewKundFakturor->setColumnWidth(6,86);		// ?
    listViewKundFakturor->setColumnWidth(7,86);		// ?
*/
    listViewBetalda->setColumnWidth(0,70);			// Fakturanr
    listViewBetalda->setColumnWidth(1,90);			// Belopp
    listViewBetalda->setColumnAlignment ( 1 , 2);		// AlignRight
    listViewBetalda->setColumnAlignment ( 2 , 4);		// Kundnr, AlignCenter
}

void frmKundfakturaBetald::pushButtonHelp_clicked()
{
	inrad="";
	frmKundfakturaBetald::readResursFil();		// Hämta path till hjälpfilen

	int i1 = hjelpfil.find( QRegExp(".html"), 0 );
//	int i2 = hjelpfil.length();
	hjelpfil=hjelpfil.left(i1);
	hjelpfil=hjelpfil+"_KUNDORDER.html";
	hjelpfil=hjelpfil+"#FAKTURABETALD";		// Lägg till position
	qDebug("hjelpfil=%s",hjelpfil.latin1());

	processhelp = new QProcess();
	processhelp->addArgument( "OLFIXHLP" );	// OLFIX program
	processhelp->addArgument(hjelpfil);

	if ( !processhelp->start() ) {
	    // error handling
	    QMessageBox::warning( this, "OLFIX","Kan inte starta OLFIXHLP!\n" );
	}
	lineEditFakturaNr->setFocus();
}

void frmKundfakturaBetald::readResursFil()
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

void frmKundfakturaBetald::getForetagsData(QString posttyp)
{
    /**********************************************************************/
    /*	Hämta vald faktura	  	 				*/
    /**********************************************************************/    
    const char *userp = getenv("USER");
    QString usr(userp);

    ftginrad="";
    errorrad="";
    ftgdataproc = new QProcess();
    ftgdataproc->addArgument("./STYRMAN");	// OLFIX styrprogram
    ftgdataproc->addArgument(usr);		// userid
    ftgdataproc->addArgument( "FTGDSP");	// OLFIX funktion
    ftgdataproc->addArgument(posttyp);
    
    frmKundfakturaBetald::connect( ftgdataproc, SIGNAL(readyReadStdout() ),this, SLOT(FTGDataOnStdout() ) );
    frmKundfakturaBetald::connect( ftgdataproc, SIGNAL(readyReadStderr() ),this, SLOT(FTGDataOnStderr() ) );
    frmKundfakturaBetald::connect( ftgdataproc, SIGNAL(processExited() ),this, SLOT(FTGEndOfProcess() ) );
        
    if ( !ftgdataproc->start() ) {
	    // error handling
	    QMessageBox::warning( this, "KUFAKTBW",
				  "Kan inte starta STYRMAN/FTGDSP! \n" );
	}    
}

void frmKundfakturaBetald::FTGDataOnStderr()
{
    while (ftgdataproc->canReadLineStderr() ) {
	QString line = ftgdataproc->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmKundfakturaBetald::FTGDataOnStdout()
{
    while (ftgdataproc->canReadLineStdout() ) {
	QString line = ftgdataproc->readStdout();
	ftginrad.append(line);
	ftginrad.append("\n");
    }
}

void frmKundfakturaBetald::FTGEndOfProcess()
{
//    qDebug("Start FTGEndOfProcess()");
    
    QString recordtyp;
    int i,i1,m;
    i = -1;
    i = ftginrad.find( QRegExp("OK:"), 0 );
    if (i != -1)  {
	i=-1;
	i = ftginrad.find( QRegExp("1:"), 0 );
	if (i != -1)  {
	    i1= ftginrad.find( QRegExp("2:"), i+3 );
	    m=i1-(i+2);
	    recordtyp=ftginrad.mid(i+2,m);
	    recordtyp=recordtyp.stripWhiteSpace();
//	    qDebug("i=%d, i1=%d, m=%d, recordtyp=%s",i,i1,m,recordtyp.latin1());
	}
	i=-1;
	i = ftginrad.find( QRegExp("2:"), 0 );
	if (i != -1)  {
	    i1= ftginrad.length();
	    m=i1-(i+2);
	    if (recordtyp=="KFKTO"){
		debetkto=ftginrad.mid(i+2,m);
		debetkto=debetkto.stripWhiteSpace();
//		qDebug("i=%d, i1=%d, m=%d, dbetkto=%s",i,i1,m,debetkto.latin1());
		recordtyp="INKTO";
		frmKundfakturaBetald::getForetagsData(recordtyp);
	    }
	    if (recordtyp=="INKTO"){
		kreditkto=ftginrad.mid(i+2,m);
		kreditkto=kreditkto.stripWhiteSpace();
//		qDebug("i=%d, i1=%d, m=%d, dbetkto=%s",i,i1,m,debetkto.latin1());		
	    }
	}
    }
}

void frmKundfakturaBetald::getVernr(QString bokfaar)
{    
    const char *userp = getenv("USER");
    QString usr(userp);
//    qDebug("getVernr Start %s",bokfaar.latin1());
    barinrad="";
    errorrad="";
    barproc = new QProcess();
    barproc->addArgument("./STYRMAN");	// OLFIX styrprogram
    barproc->addArgument(usr);		// userid
    barproc->addArgument( "BARDSP");	// OLFIX funktion
    barproc->addArgument(bokfaar);
    
    frmKundfakturaBetald::connect( barproc, SIGNAL(readyReadStdout() ),this, SLOT(BarDataOnStdout() ) );
    frmKundfakturaBetald::connect( barproc, SIGNAL(readyReadStderr() ),this, SLOT(BarDataOnStderr() ) );
    frmKundfakturaBetald::connect( barproc, SIGNAL(processExited() ),this, SLOT(BarEndOfProcess() ) );
        
    if ( !barproc->start() ) {
	    // error handling
	    QMessageBox::warning( this, "KUFAKTBW",
				  "Kan inte starta STYRMAN/BARDSP! \n" );
	}    
}

void frmKundfakturaBetald::BarDataOnStderr()
{
    while (barproc->canReadLineStderr() ) {
	QString line = barproc->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmKundfakturaBetald::BarDataOnStdout()
{
    while (barproc->canReadLineStdout() ) {
	QString line = barproc->readStdout();
	barinrad.append(line);
	barinrad.append("\n");
//	qDebug("barinrad=%s",barinrad.latin1());
    }
}

void frmKundfakturaBetald::BarEndOfProcess()
{
//    qDebug("BarEndOfProcess() Start %s",barinrad.latin1());
    QString message;
    QString bokfar;					// bokföringsår
    QString arlast;
    QString ver;						// verifikationsnummer
    int vernum;
    int i,i1,m;
    message="Bokföringsåret ";
    message.append(bar.latin1());
    message.append("  finns inte! \n");
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i != -1)  {
	QMessageBox::warning( this, "KUFAKTBW",message );
	lineEditBar->setFocus();
    }
    i = -1;
    i = barinrad.find( QRegExp("OK:"), 0 );
    if (i != -1)  {
	i=-1;
	i = barinrad.find( QRegExp("ARID:"), 0 );		// bokföringsår
	if (i != -1)  {
	    i1= barinrad.find( QRegExp("BENAMN:"), 0 );
	    m=i1-(i+5);
	    bokfar=barinrad.mid(i+5,m);
	    bokfar=bar.stripWhiteSpace();
//	    qDebug("i=%d, i1=%d, m=%d, bokfar=%s",i,i1,m,bokfar.latin1());
	}
	i=-1;
	i = barinrad.find( QRegExp("ARLAST:"), 0 );		// är bokföringsåret låst
	if (i != -1)  {
	    i1= barinrad.find( QRegExp("SVERDAT:"), 0 );		// senaste verifikationsdatum
	    m=i1-(i+7);
	    arlast= barinrad.mid(i+7,m);
	    arlast=arlast.stripWhiteSpace();
//	    qDebug("i=%d, i1=%d, m=%d, arlast=%s",i,i1,m,arlast.latin1());
	    if (arlast == "N") {
		i=-1;
		i = barinrad.find( QRegExp("VERNR:"), 0 );			// Senast använda verifikationsnr
		if (i != -1)  {
		    i1= barinrad.find( QRegExp("KTOPLAN:"), 0 );		// kontoplan
		    m=i1-(i+6);
		    ver= barinrad.mid(i+6,m);
		    ver=ver.stripWhiteSpace();
//		    qDebug("i=%d, i1=%d, m=%d, ver=%s",i,i1,m,ver.latin1());
		    vernum=ver.toInt();
		    vernum=vernum+1;
		    vernr=vernr.setNum(vernum);
		    lineEditVernr->setText(vernr);
		}
	    }else{
		    QMessageBox::warning( this, "KUFAKTBW","Bokföringsåret är låst! \n" );
		    lineEditBar->setFocus();
		}
	}
    }
}

void frmKundfakturaBetald::updateKundFaktura( QString record )
{
    /**********************************************************************/
    /*	Uppdatera databasen	  	 				*/
    /**********************************************************************/    
    const char *userp = getenv("USER");
    QString usr(userp);
    processnbr++;
    if (processnbr>191) {
	processnbr=1;
    }    
    updateinrad="";
    updateerrorrad="";
    updateproc[processnbr] = new QProcess();
    updateproc[processnbr]->addArgument("./STYRMAN");	// OLFIX styrprogram
    updateproc[processnbr]->addArgument(usr);		// userid
    updateproc[processnbr]->addArgument( "KRESUPD");	// OLFIX funktion
    updateproc[processnbr]->addArgument(record);
    
    frmKundfakturaBetald::connect( updateproc[processnbr], SIGNAL(readyReadStdout() ),this, SLOT(UpdateDataOnStdout() ) );
    frmKundfakturaBetald::connect( updateproc[processnbr], SIGNAL(readyReadStderr() ),this, SLOT(UpdateDataOnStderr() ) );
    frmKundfakturaBetald::connect( updateproc[processnbr], SIGNAL(processExited() ),this, SLOT(UpdateEndOfProcess() ) );
    
    if ( !updateproc[processnbr]->start() ) {
	    // error handling
	    QMessageBox::warning( this, "KUFAKTBW",
				  "Kan inte starta STYRMAN/KRESUPD! \n" );
	}    
}

void frmKundfakturaBetald::UpdateDataOnStderr()
{
    while (updateproc[processnbr]->canReadLineStderr() ) {
	QString line = updateproc[processnbr]->readStderr();
	updateerrorrad.append(line);
	updateerrorrad.append("\n");
    }
}

void frmKundfakturaBetald::UpdateDataOnStdout()
{
    while (updateproc[processnbr]->canReadLineStdout() ) {
	QString line = updateproc[processnbr]->readStdout();
	updateinrad.append(line);
	updateinrad.append("\n");
    }
}

void frmKundfakturaBetald::UpdateEndOfProcess()
{

}
