/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
/***************************************************************************
                          LSTINKW  -  description
                             -------------------
		     version 0.2
    begin     	: Mån 29 dec 2003
    modified	: Lör 31 jan 2004 (stretching i frmlstink.ui)
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
    
void frmLstInk::init()
{
    frmLstInk::listViewRader_format();
    pushButtonClose->setFocus();
    frmLstInk::LstOrderRader();
}

void frmLstInk::LstOrderRader()
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
	process->addArgument( "INKLST");	// OLFIX funktion
	
	frmLstInk::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmLstInk::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmLstInk::connect( process, SIGNAL(processExited() ),this, SLOT(slotRaderEndOfProcess() ) );
	    
	    if ( !process->start() ) {
		// error handling
		QMessageBox::warning( this, "LSTINKW",
                            "Kan inte starta STYRMAN/INKLST! \n" );
	    }
}

void frmLstInk::slotDataOnStdout()
{
     while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmLstInk::slotDataOnStderr()
{
      while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmLstInk::listViewRader_format()
{
//    qDebug("frmLstInk::listViewRader_format()");
    listViewRader->setColumnWidth(0,50);		// Ordernr
    listViewRader->setColumnAlignment( 0, Qt::AlignRight );
    listViewRader->setColumnWidth(1,36);		// Radnr
    listViewRader->setColumnAlignment( 1, Qt::AlignRight );
    listViewRader->setColumnWidth(2,60);		// Leverantörsnr
    listViewRader->setColumnAlignment( 2, Qt::AlignRight );
    listViewRader->setColumnWidth(3,185);		// Artikelnr
    listViewRader->setColumnWidth(4,185);		// Benämning
    listViewRader->setColumnWidth(5,55);		// Lev.vecka
    listViewRader->setColumnAlignment( 5, Qt::AlignRight );
    listViewRader->setColumnWidth(6,35);		// Bekräftelsekod
    listViewRader->setColumnAlignment( 6, Qt::AlignHCenter );    
    listViewRader->setColumnWidth(7,80);		// Beställt Antal
    listViewRader->setColumnAlignment( 7, Qt::AlignRight );
    listViewRader->setColumnWidth(8,80);		// Levererat Antal
    listViewRader->setColumnAlignment( 8, Qt::AlignRight );
    listViewRader->setColumnWidth(9,80);		// Resterande Antal
    listViewRader->setColumnAlignment( 9, Qt::AlignRight );
    listViewRader->setColumnWidth(10,80);		// Pris
    listViewRader->setColumnAlignment( 10, Qt::AlignRight );
    listViewRader->setColumnWidth(11,80);		// Summa    
    listViewRader->setColumnAlignment( 11, Qt::AlignRight ); 
}


void frmLstInk::slotRaderEndOfProcess()
{
    QListViewItem* item;
    bool ok;
    int i,j,k,m,n,p;
    QString tmp;
    QString ordernr;
    QString radnr;
    QString levnr;
    QString artikelnr;
    QString benemning;
    QString bestantal;
    QString levantal="0";
    QString rest="0";
    QString inkpris;
    QString levvecka;
    QString bkod;
    QString radsumma;
    QString ordersumma;
    double summa=0;
    double ordersum=0;
    
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
 //   qDebug("Error:",errorrad);
    if (i != -1) {
	QMessageBox::critical( this, "LSTINKW",
		"ERROR!\n"+errorrad
	);
    }else{
	i = inrad.find( QRegExp("OK: NR_0_"), 0 );
	if (i != -1) {
	    QMessageBox::information( this, "LSTINKW",
		"Inköpsregistret innehåller inga orderrader!\n"
		);
	}else{
	    i = inrad.find( QRegExp("OK: NR_"), 0 )+7;
	    j=inrad.find(QRegExp("_:"),0);
	    k=j-i;
	    tmp=inrad.mid(i,k);
	    m=tmp.toInt(&ok,10);
	    for (n=0;n<m;n++){
		for (p=0;p<12;p++){	// 12 = antal fält från INKLST
		    i=j;
		    j=j=inrad.find(QRegExp("_:"),i+2);
		    k=j-i-2;
		    tmp=inrad.mid(i+2,k);
		    if(p==0)
			ordernr=tmp;
		    if(p==1)
			radnr=tmp;
		    if(p==2)
			levnr=tmp;		    
		    if(p==3)
			artikelnr=tmp;
		    if(p==4)
			benemning=tmp;
		    if(p==5)
			bkod=tmp;
		    if(p==6)
			bestantal=tmp;
		    if(p==7)
			levantal=tmp;
		    if(p==8)
			rest=tmp;
		    if(p==9)
			inkpris=tmp;
		    if(p==10)
			levvecka=tmp;		    		    
		    if(p==11){
			radsumma=tmp;
			summa=tmp.toDouble();
		    }
		}
		ordersum=ordersum+summa;
		item = new QListViewItem(listViewRader,ordernr,radnr,levnr,artikelnr,benemning,levvecka,bkod,bestantal);
		item->setText(8,levantal);
		item->setText(9,rest);
		item->setText(10,inkpris);
		item->setText(11,radsumma);
	    }
	    ordersumma=ordersumma.setNum(ordersum,'f',2);
	    lineEditOrderSumma->setText(ordersumma);
	}
    }
}
