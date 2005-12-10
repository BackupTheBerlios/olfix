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
    begin                	: S�n   4 dec    2005
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
#include <qobject.h>
#include <qnamespace.h> 

#include <qmessagebox.h>
#include <qprocess.h>
#include <qdir.h>
#include <stdlib.h>
#include <qstring.h>
#include <qfile.h>
#include <qregexp.h>
// #include <qvalidator.h>
#include <qlistview.h>
#define MAXSTRING 15000


    QProcess*  processhelp;
    QProcess*  processresk;
    QProcess*  faktproc;
    QProcess*  ftgdataproc;
    QProcess*  vernrproc;
    QProcess*  barproc;
    
    QString inrad = "";
    QString reskinrad;
    QString faktinrad;
    QString ftginrad;
    QString barinrad;
    QString errorrad;
    QString hjelpfil;

    QString datum;				// = registreringsdatum f�r fakturan.
    QString bar;					// bar = bokf�rings�r
    QString fakturanummer;
    QString debetkto;
    QString debetbelopp;
    QString kreditkto;
    QString kreditbelopp;
    QString vernr;					// verifikationsnummer f�r bokf�ring

void frmKundfakturaBetald::init()
{
    QString ktopost;
    QDateTime dt = QDateTime::currentDateTime();    
    datum=dt.toString("yyyy-MM-dd");
    textLabelDatum->setText(datum);    		// = registreringsdatum f�r fakturan.
    frameBokforing->hide();
    frmKundfakturaBetald::listView_format();		// formater storleken p� kolummerna i listorna
    frmKundfakturaBetald::getKundReskontraLista();
    ktopost="KFKTO";				// konto f�r kundfordringar i FTGDATA
    frmKundfakturaBetald::getForetagsData(ktopost);
    lineEditFakturaNr->setFocus();
}

void frmKundfakturaBetald::lineEditFakturaNr_returnPressed()
{
    bool bokfor;
    bokfor=checkBoxBokforing->isChecked();
    fakturanummer=lineEditFakturaNr->text();
    getKundFaktura();
    if (bokfor) {
	lineEditDebetKto->setFocus();
//	qDebug("TRUE");
    }else{
//	QListViewItem *item =  listViewKundFakturor->currentItem();
//	item->setSelected( TRUE );
	listViewKundFakturor->setFocus();
//	qDebug("FALSE");
    }
}

void frmKundfakturaBetald::checkBoxBokforing_checked()
{
    bool bokfor;
    bokfor=checkBoxBokforing->isChecked();
    if (!bokfor) {
//	qDebug("FALSE");
	frameBokforing->hide();
    }
    if(bokfor) {
//	qDebug("TRUE");
	frameBokforing->show();
    }
}

void frmKundfakturaBetald::lineEditBar_returnPressed()
{
    bar=lineEditBar->text();
    bar=bar.upper();
    bar=bar.stripWhiteSpace();
    if (bar==""){
	QMessageBox::critical( this, "KUFAKTBW","Bokf�rings�r f�r inte vara blank!\n");
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
    getKundFaktura();

    QListViewItem *item =  listViewKundFakturor->currentItem();
    if ( !item )
	return;
    item->setSelected( TRUE );
    QString temp0=item->text(0);	// fakturanr
    QString temp1=item->text(1);	// fakturadatum
    QString temp2=item->text(2);	// kundnr
    QString temp3=lineEditBelopp->text();	// belopp
    delete listViewKundFakturor->currentItem();
    item = new QListViewItem(listViewBetalda,temp0,temp3,temp2,temp1);
}

void frmKundfakturaBetald::pushButtonLeft_clicked()
{
//    qDebug("Left");
       QListViewItem *item =  listViewBetalda->currentItem();
    if ( !item )
	return;
    item->setSelected( TRUE );
    QString temp0=item->text(0);	// fakturanr
    QString temp1=item->text(1);	// belopp
    QString temp2=item->text(2);	// kundnr
    QString temp3=item->text(3);	// fakturadatum
    delete listViewBetalda->currentItem();
     item = new QListViewItem(listViewKundFakturor,temp0,temp3,temp2);
    
}

void frmKundfakturaBetald::pushButtonOK_clicked()
{

}

void frmKundfakturaBetald::getKundFaktura()
{
    /**********************************************************************/
    /*	H�mta vald faktura	  	 				*/
    /**********************************************************************/    
    const char *userp = getenv("USER");
    QString usr(userp);

    faktinrad="";
    errorrad="";
    faktproc = new QProcess();
    faktproc->addArgument("./STYRMAN");	// OLFIX styrprogram
    faktproc->addArgument(usr);		// userid
    faktproc->addArgument( "FAKTDSP");	// OLFIX funktion
    faktproc->addArgument(fakturanummer);
    
    frmKundfakturaBetald::connect( faktproc, SIGNAL(readyReadStdout() ),this, SLOT(FaktDataOnStdout() ) );
    frmKundfakturaBetald::connect( faktproc, SIGNAL(readyReadStderr() ),this, SLOT(FaktDataOnStderr() ) );
    frmKundfakturaBetald::connect( faktproc, SIGNAL(processExited() ),this, SLOT(FaktEndOfProcess() ) );
        
    if ( !faktproc->start() ) {
	    // error handling
	    QMessageBox::warning( this, "KUFAKTBW",
				  "Kan inte starta STYRMAN/FAKTDSP! \n" );
	}    
}

void frmKundfakturaBetald::FaktDataOnStderr()
{
    while (faktproc->canReadLineStderr() ) {
	QString line = faktproc->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmKundfakturaBetald::FaktDataOnStdout()
{
    while (faktproc->canReadLineStdout() ) {
	QString line = faktproc->readStdout();
	faktinrad.append(line);
	faktinrad.append("\n");
    }
}

void frmKundfakturaBetald::FaktEndOfProcess()
{
    QString tmp;
    QString ordernr;
    QString faktnr;
    QString kundnr;
    QString belopp;
    QString debetktonr;
    QString faktdatum;
        
    int i,i1,m;

    tmp=faktinrad;
    tmp=tmp.stripWhiteSpace();
//    qDebug("inrad=|%s|",tmp.latin1());
    if (tmp==""){
		QMessageBox::critical( this, "KUFAKTBW",
			       "Finns inget data eller FAKTDSP saknas!\n"
			       );
	    }
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    //   qDebug("Error:",errorrad);
    if (i != -1) {
	QMessageBox::critical( this, "KUFAKTBW",
			       "ERROR!\n"+errorrad
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
	    lineEditOrdernr->setText(ordernr);
	}
	i=-1;
	i = faktinrad.find( QRegExp("_:FAKTURABELOPP:"), 0 ); 
	if (i != -1)  {
	    i1= faktinrad.find( QRegExp("_:"), i+3 );
	    m=i1-(i+16);
	    belopp=faktinrad.mid(i+16,m);
//	    qDebug("i=%d, i1=%d, m=%d, belopp=%s",i,i1,m,belopp.latin1());
	    lineEditBelopp->setText(belopp);
	}
	i=-1;
	i = faktinrad.find( QRegExp("_:KTONR:"), 0 ); 
	if (i != -1)  {
	    i1= faktinrad.find( QRegExp("_:"), i+3 );
	    m=i1-(i+8);
	    debetktonr=faktinrad.mid(i+8,m);
//	    qDebug("i=%d, i1=%d, m=%d, debetktonr=%s",i,i1,m,debetktonr.latin1());
	    if (debetktonr=="0000"){
		debetktonr=debetkto;
	    }
	    lineEditDebetKto->setText(debetktonr);
	    lineEditDebetBelopp->setText(belopp);
	    lineEditKreditBelopp->setText(belopp);
	}
	lineEditDebetKto->setFocus();
    }
    tmp=lineEditKreditKto->text();
    if (tmp==""){
	lineEditKreditKto->setText(kreditkto);
    }
}

void frmKundfakturaBetald::getKundReskontraLista()
{
    /**********************************************************************/
    /*	H�mta kundreskontraposter	  	 				*/
    /**********************************************************************/
    const char *userp = getenv("USER");
    QString usr(userp);

    listViewKundFakturor->clear();
    reskinrad = "";
    errorrad = "";
    
    processresk = new QProcess();
    processresk->addArgument("./STYRMAN");	// OLFIX styrprogram
    processresk->addArgument(usr);		// userid
    processresk->addArgument( "KRESLST");	// OLFIX funktion

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
	errorrad.append(line);
	errorrad.append("\n");
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
//    tmp = inrad;
    tmp = reskinrad.stripWhiteSpace();
//    qDebug("inrad=|%s|",tmp.latin1());
    if (tmp == ""){
	QMessageBox::critical( this, "KUFAKTBW", "Finns inget data eller KRESLST saknas!\n" );
    }else{
	tmp="";
	i = -1;
	i = errorrad.find( QRegExp("Error:"), 0 );
//   	qDebug("Error:",errorrad.latin1());
	if (i != -1) {
	    QMessageBox::critical( this, "KUFAKTBW","ERROR!\n"+errorrad);
	}
	i = -1;
	i = reskinrad.find( QRegExp("OK:"), 0 );
//	qDebug("inrad=%s",inrad.latin1());
	if (i != -1)  {
//	    qDebug("i=%d",i);
	    /****************************************/
	    /*  H�mta data fr�n kundreskontran KURESK  */
	    /****************************************/	    
	    m = 0;
	    i1 = reskinrad.find( QRegExp("OK: NR_"), m); 		// startposition
	    i2 = reskinrad.find( QRegExp("_:"), m );			// slutposition f�r antal rader
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
		item = new QListViewItem(listViewKundFakturor,faktnr,faktdatum,kundnr);
		m = i4 + 3;
		i3 = i4;
	    };
	}else{
	    QMessageBox::warning( this, "KUFAKTBW", "Felaktiga data fr�n databasen!!\n");
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
	frmKundfakturaBetald::readResursFil();		// H�mta path till hj�lpfilen

	int i1 = hjelpfil.find( QRegExp(".html"), 0 );
//	int i2 = hjelpfil.length();
	hjelpfil=hjelpfil.left(i1);
	hjelpfil=hjelpfil+"_KUNDORDER.html";
	hjelpfil=hjelpfil+"#FAKTURABETALD";		// L�gg till position
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
    /*  L�s in .olfixrc filen h�r			               */
    /* Plocka fram var hj�lpfilen finns			               */
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
    /*	H�mta vald faktura	  	 				*/
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

void frmKundfakturaBetald::getVernr(QString bar)
{
//    qDebug("Bokf�rings�r=%s",bar.latin1());
    
    const char *userp = getenv("USER");
    QString usr(userp);

    barinrad="";
    errorrad="";
    barproc = new QProcess();
    barproc->addArgument("./STYRMAN");	// OLFIX styrprogram
    barproc->addArgument(usr);		// userid
    barproc->addArgument( "BARDSP");	// OLFIX funktion
    barproc->addArgument(bar);
    
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
    }
}

void frmKundfakturaBetald::BarEndOfProcess()
{
    QString bokfar;					// bokf�rings�r
    QString arlast;
    QString ver;						// verifikationsnummer
    int vernum;
    int i,i1,m;
    
    i = -1;
    i = barinrad.find( QRegExp("OK:"), 0 );
    if (i != -1)  {
	i=-1;
	i = barinrad.find( QRegExp("ARID:"), 0 );		// bokf�rings�r
	if (i != -1)  {
	    i1= barinrad.find( QRegExp("BENAMN:"), 0 );
	    m=i1-(i+5);
	    bokfar=barinrad.mid(i+5,m);
	    bokfar=bar.stripWhiteSpace();
//	    qDebug("i=%d, i1=%d, m=%d, bokfar=%s",i,i1,m,bokfar.latin1());
	}
	i=-1;
	i = barinrad.find( QRegExp("ARLAST:"), 0 );		// �r bokf�rings�ret l�st
	if (i != -1)  {
	    i1= barinrad.find( QRegExp("SVERDAT:"), 0 );		// senaste verifikationsdatum
	    m=i1-(i+7);
	    arlast= barinrad.mid(i+7,m);
	    arlast=arlast.stripWhiteSpace();
//	    qDebug("i=%d, i1=%d, m=%d, arlast=%s",i,i1,m,arlast.latin1());
	    if (arlast == "N") {
		i=-1;
		i = barinrad.find( QRegExp("VERNR:"), 0 );			// Senast anv�nda verifikationsnr
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
		    QMessageBox::warning( this, "KUFAKTBW","Bokf�rings�ret �r l�st! \n" );
		    lineEditBar->setFocus();
		}
	}
    }
}
