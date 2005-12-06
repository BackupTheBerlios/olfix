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

#include <qmessagebox.h>
#include <qprocess.h>
#include <qdir.h>
#include <stdlib.h>
#include <qstring.h>
#include <qfile.h>
#include <qregexp.h>
#include <qvalidator.h>
#define MAXSTRING 15000


    QProcess*  processhelp;
    QProcess*  processresk;
    QProcess*  faktproc;
    QProcess*  ftgdataproc;
    
    QString inrad;
    QString faktinrad;
    QString ftginrad;
    QString errorrad;
    QString hjelpfil;

    QString datum;				// = registreringsdatum för fakturan.
    QString fakturanummer;
    QString debetkto;

void frmKundfakturaBetald::init()
{
    QString ktopost;
    QDateTime dt = QDateTime::currentDateTime();
    datum=dt.toString("yyyy-MM-dd");
    textLabelDatum->setText(datum);    		// = registreringsdatum för fakturan.

    frmKundfakturaBetald::listViewKundFakturor_format();
    frmKundfakturaBetald::getKundReskontraLista();
    ktopost="KFKTO";				// konto för kundfordringar i FTGDATA
    frmKundfakturaBetald::getForetagsData(ktopost);
    lineEditFakturaNr->setFocus();
}

void frmKundfakturaBetald::lineEditFakturaNr_returnPressed()
{
    fakturanummer=lineEditFakturaNr->text();
    getKundFaktura();
    lineEditDebetKto->setFocus();
}

void frmKundfakturaBetald::lineEditDebetKto_returnPressed()
{

}

void frmKundfakturaBetald::lineEditDebetBelopp_returnPressed()
{

}

void frmKundfakturaBetald::lineEditKreditKto_returnPressed()
{

}

void frmKundfakturaBetald::lineEditKreditBelopp_returnPressed()
{

}

void frmKundfakturaBetald::pushButtonOK_clicked()
{

}

void frmKundfakturaBetald::getKundFaktura()
{
    /**********************************************************************/
    /*	Hämta vald faktura	  	 				*/
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
	lineEditKreditKto->setText("1511");
    }
}



void frmKundfakturaBetald::getKundReskontraLista()
{
    /**********************************************************************/
    /*	Hämta kundreskontraposter	  	 				*/
    /**********************************************************************/
    const char *userp = getenv("USER");
    QString usr(userp);

    inrad="";
    errorrad="";
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
	inrad.append(line);
	inrad.append("\n");
    }
}


void frmKundfakturaBetald::KreskEndOfProcess()
{
    QListViewItem* item;

    QString tmp;
    QString faktnr;
    QString kundnr;
    QString belopp;
    QString faktdatum;
    
    QString ordernr;
    QString status;
    QString antalrader;
    QString sum;
    
    int i1,i2,i3,i4,l,m;
    int antrad;
    double summa=0;
    tmp=inrad;
    tmp=tmp.stripWhiteSpace();
//    qDebug("inrad=|%s|",tmp.latin1());
    if (tmp==""){
		QMessageBox::critical( this, "KUFAKTBW",
			       "Finns inget data eller KRESLST saknas!\n"
			       );
	    }
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    //   qDebug("Error:",errorrad);
    if (i != -1) {
	QMessageBox::critical( this, "KUFAKTBW",
			       "ERROR!\n"+errorrad
			       );
    }
    i = -1;
    i = inrad.find( QRegExp("OK:"), 0 );
    if (i != -1)  {
	// Hämta data från kundreskontran KURESK
	     m=0;
	     i1=inrad.find( QRegExp("OK: NR_"), m); 		// startposition
	     i2=inrad.find( QRegExp("_:"), m );			// slutposition för antal rader
	     l=i2-(i1+7);
	    antalrader=inrad.mid(i1+7,l);
	    antrad=antalrader.toInt();
//	    qDebug("antalrader=%s antrad=%d",antalrader.latin1(),antrad);
	    m=i2;
//	    qDebug("i1=%d i2=%d l=%d m=%d",i1,i2,l,m);
	    i3=inrad.find( QRegExp("_:_"), m );
	    for (i=0;i<antrad;i++){

		i4=inrad.find( QRegExp("_:_"), i3+1 );
		l=i4-i3-3;
		ordernr=inrad.mid(i3+3,l);
//		qDebug("m=%d i3=%d i4=%d l=%d ordernr=%s",m,i3,i4,l,ordernr.latin1());
		m=i4+3;
		i3=i4;
		i4=inrad.find( QRegExp("_:_"), i3 +1);
		l=i4-i3-3;
		faktnr=inrad.mid(i3+3,l);
//		qDebug("m=%d i3=%d i4=%d l=%d faktnr=%s",m,i3,i4,l,faktnr.latin1());
		m=i4+3;
		i3=i4;
		i4=inrad.find( QRegExp("_:_"),i3 +1);
		l=i4-i3-3;
		kundnr=inrad.mid(i3+3,l);
//		qDebug("m=%d i3=%d i4=%d l=%d kundnr=%s",m,i3,i4,l,kundnr.latin1());
		m=i4+3;
		i3=i4;
		i4=inrad.find( QRegExp("_:_"), i3 +1);
		l=i4-i3-3;
		belopp=inrad.mid(i3+3,l);
//		qDebug("m=%d i3=%d i4=%d l=%d belopp=%s",m,i3,i4,l,belopp.latin1());	
		m=i4+3;
		i3=i4;
		summa=summa+belopp.toDouble();
		i4=inrad.find( QRegExp("_:_"), i3 +1);
		l=i4-i3-3;
		faktdatum=inrad.mid(i3+3,l);
//		qDebug("m=%d i3=%d i4=%d l=%d faktdatum=%s",m,i3,i4,l,faktdatum.latin1());
		m=i4+3;
		i3=i4;
		i4=inrad.find( QRegExp("_:_"), i3 +1);
		l=i4-i3-3;
		status=inrad.mid(i3+3,l);
//		qDebug("m=%d i3=%d i4=%d l=%d status=%s",m,i3,i4,l,status.latin1());
		item = new QListViewItem(listViewKundFakturor,faktnr,faktdatum,kundnr);
		m=i4+3;
		i3=i4;
	    }
	    sum=sum.setNum(summa,'f',2);
//	    lineEditSumma->setText(sum);
    }else{
	QMessageBox::warning( this, "KUFAKTBW",
			       "Felaktiga data från databasen!!\n"
			       );
    }
    lineEditFakturaNr->setFocus();
}

void  frmKundfakturaBetald::listViewKundFakturor_clicked( QListViewItem * )
{
    lineEditFakturaNr->clear();
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
    lineEditFakturaNr->setFocus();
}
    
void frmKundfakturaBetald::listViewKundFakturor_format()
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
	    }
	}
    }
}
