/***************************************************************************
                          LEVRESKW  -  description
                             -------------------
	              version 0.01
    begin                : Sön 29 juni 2003
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

#define MAXSTRING 5000

    QProcess* process;
    QString inrad;
    QString* rad;
    QString errorrad;
    int status=0;
    QString field;

    
void frmLevResk::init()
{
   QString datum;	
   QDateTime dt = QDateTime::currentDateTime();
    datum=dt.toString("yyyy-MM-dd");
    TextLabelDatum->setText(datum);
    slotGetLevReskPost();
}

void frmLevResk::slotGetLevReskPost()
{
	const char *userp = getenv("USER");
            QString usr(userp);
	    inrad="";
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "LRESRPT");	// OLFIX funktion

	frmLevResk::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmLevResk::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmLevResk::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );

	if ( !process->start() ) {
	    // error handling
	    QMessageBox::warning( this, "LEVRESKW",
                            "Kan inte starta STYRMAN/LRESRPT! \n" );
	    }
}

void frmLevResk::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmLevResk::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmLevResk::slotEndOfProcess()
{
    QListViewItem* item;    
    QString levnr;		// leverantörsnummer
    QString levnamn;	// leverantörsnamn    
//    QString bar;		// bokföringsår
//    QString vernr;		// verifikationnummer
//    QString datum;		// registreringsdatum
//    QString kundnr;	// mitt kundnummer hos leverantören
//    QString regdatum;	// registreringsdatum
    QString fakturanr;	// fakturanummer
//    QString faktdatum;	// fakturadatum
    QString expiredatum;	// förfallodatum
//    QString fakttext;	// fakturatext
    QString faktbelopp;	// fakturabelopp
//    QString momsktonr;	// kontonr för moms
//    QString momsprocent;	// momsens procentsats
//    QString momsbelopp;	// moms i kr
//    QString kreditkto;	// konto att kreditera
//    QString kreditbelopp;	// belopp att kreditera
    
  int i,antrad;
  int j,k,l,m;

  double dbbelopp=0;
  double dbtotal=0;
  double krbelopp=0;
  double krtotal=0;
  double summa=0;
  double total=0;

    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "LEVRESKW",
		"ERROR!\n"+errorrad );
	 errorrad="";
     }
    
//    qDebug("inrad=%s",inrad.latin1());
    
    i = inrad.find(QRegExp("NR_"),0);
    j = inrad.find(QRegExp("_:"),0);
    m = j - i;
//   qDebug("i=%d, j=%d, m=%d",i,j,m);
   antrad = (inrad.mid(i+3,m-3)).toInt();
//   qDebug("antrad=%d,",antrad);
 
   for (l = 0;l < antrad; l++){
	  k = inrad.find(QRegExp("_:"),j+3);  // j+2
	  m = k - j;
	  expiredatum = inrad.mid(j+2,m-2);
//               qDebug("l=%d, expiredatum=%s",l,expiredatum.latin1());

	  j = k;
	  k = inrad.find(QRegExp("_:"),j+2);
	  m = k - j;
	  levnr = inrad.mid(j+2,m-2);
//               qDebug("levnr=%s",levnr.latin1());

	  j = k;
	  k = inrad.find(QRegExp("_:"),j+2);
	  m = k - j;
	  levnamn = inrad.mid(j+2,m-2);
//               qDebug("levnamn=%s",levnamn.latin1());

	  j = k;
	  k = inrad.find(QRegExp("_:"),j+2);
	  m = k - j;
	  fakturanr = inrad.mid(j+2,m-2);
//               qDebug("fakturanr=%s",fakturanr.latin1());    
	
	  j = k;
	  k = inrad.find(QRegExp("_:"),j+2);
	  m = k - j;
	  faktbelopp = inrad.mid(j+2,m-2);
//	  while (faktbelopp.length()<12){
//	      faktbelopp.prepend(" ");
//	  }
	  faktbelopp = faktbelopp.rightJustify( 12, '_' );
//               qDebug("faktbelopp=%s",faktbelopp.latin1());    
	  
             item = new QListViewItem(ListView1,expiredatum,levnr,levnamn,fakturanr,faktbelopp);
             j = k;
   }
   
}
