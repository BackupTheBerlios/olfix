/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
/***************************************************************************
                          KURESKW  -  description
                             -------------------
		     version 0.1
    begin     	: Tis   15 nov  2005
    Modified	: 
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
#include <qlistview.h>
#include <qdatetime.h>
#define MAXSTRING 5000

    QProcess* process;
    
    QString inrad;
    QString errorrad;

void frmKundReskontra::init()
{
    QDateTime dt = QDateTime::currentDateTime();
    QString datum=dt.toString("yyyy-MM-dd");
    textLabelDatum->setText(datum);
    frmKundReskontra::listView1_format();
    frmKundReskontra::getReskontra();
}

void frmKundReskontra::getReskontra()
{
    /**********************************************************************/
    /*	Hämta kundreskontraposter	  	 				*/
    /**********************************************************************/
    const char *userp = getenv("USER");
    QString usr(userp);

    inrad="";
    errorrad="";
    process = new QProcess();
    process->addArgument("./STYRMAN");	// OLFIX styrprogram
    process->addArgument(usr);		// userid
    process->addArgument( "KRESLST");	// OLFIX funktion

    frmKundReskontra::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(DataOnStdout() ) );
    frmKundReskontra::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(DataOnStderr() ) );
    frmKundReskontra::connect( process, SIGNAL(processExited() ),this, SLOT(EndOfProcess() ) );
    
    if ( !process->start() ) {
	    // error handling
	    QMessageBox::warning( this, "KURESKW",
				  "Kan inte starta STYRMAN/KRESLST! \n" );
	}
    }

void frmKundReskontra::EndOfProcess()
{
    QListViewItem* item;

    QString tmp;
    QString ordernr;
    QString faktnr;
    QString kundnr;
    QString belopp;
    QString faktdatum;
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
		QMessageBox::critical( this, "KURESKW",
			       "Finns inget data eller KRESLST saknas!\n"
			       );
	    }
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    //   qDebug("Error:",errorrad);
    if (i != -1) {
	QMessageBox::critical( this, "KURESKW",
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
		item = new QListViewItem(listView1,ordernr,faktnr,kundnr,belopp,faktdatum,status);
		m=i4+3;
		i3=i4;
	    }
	    sum=sum.setNum(summa,'f',2);
	    lineEditSumma->setText(sum);
    }else{
	QMessageBox::warning( this, "KURESKW",
			       "Felaktiga data från databasen!!\n"
			       );
    }
}

void frmKundReskontra::listView1_format()
{
    listView1->setColumnWidth(0,55);		// Ordernr
    listView1->setColumnWidth(1,65);		// Fakturanr
    listView1->setColumnWidth(2,55);		// Kundnr
    listView1->setColumnWidth(3,100);		// Fakturabelopp
    listView1->setColumnWidth(4,100);		// Förfallodatum
    listView1->setColumnWidth(5,45);		// Status
}

void frmKundReskontra::DataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmKundReskontra::DataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}
