/****************************************************************/
/**		ATTBETW					*/
/**		2003-08-18					*/
/**		Ver 0.1                                                                                    */
/**   Copyright	Jan Pihlgren	jan@pihlgren.se			*/
/****************************************************************/
/*****************************************************************
 *					                                                 *
 *   This program is free software; you can redistribute it and/or modify 	 *
 *   it under the terms of the GNU General Public License as published by       *
 *   the Free Software Foundation; either version 2 of the License, or     	 *
 *   (at your option) any later version.                                   		 *
 *                                                                         				 *
 *********************************************** *****************/
/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
#include <qmessagebox.h>
#include <qprocess.h>
#include <qdir.h>
#include <stdlib.h>
#include <qstring.h>
#include <qfile.h>
#include <qiodevice.h> 
#include <qregexp.h>
#define VERSION "0.1"
#define MAXSTRING 15000

    QProcess* process;
    QString errorrad;
    QString inrad;
    QString datum;

void frmLevFaktAttBetala::init()
{
    QDateTime dt = QDateTime::currentDateTime();
    datum=dt.toString("yyyy-MM-dd");
    lineEditExpireDate->setText(datum);
    lineEditExpireDate->setFocus();
}

void frmLevFaktAttBetala::slotlineEditExpireDate_returnPressed()
{
    datum=lineEditExpireDate->text();
    pushButtonOK->setFocus();    
}

void frmLevFaktAttBetala::slotpushButtonOK_clicked()
{
//    slotFileRemove("AttBetala.txt");	// Tag bort gammal fil, /tmp/AttBatala.txt    
    slotCreateHeader();
    slotSkapRapportfil();
}

void frmLevFaktAttBetala::slotSkapRapportfil()
{
            const char *userp = getenv("USER");
            QString usr(userp);
            QString filnamn;

	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "ATTBET");	// OLFIX funktion
	process->addArgument(datum);

	frmLevFaktAttBetala::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmLevFaktAttBetala::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmLevFaktAttBetala::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );

	if ( !process->start() ) {
	    // error handling
	    fprintf(stderr,"Problem starta STYRMAN/ATTBET!\n");
	    QMessageBox::warning( this, "ATTBETW",
                            "Kan inte starta STYRMAN/ATTBET! \n" );
	    }
}

void frmLevFaktAttBetala::slotEndOfProcess()
{
    int i,j,m,n;
    int ant;
    QString antal;
    QString expdatum;
    QString levnr;
    QString faktnr;
    QString belopp;
    QString valuta;
    
    QFile filnamn( "/tmp/attBetala.kud" );
    QString rapportrad;
    
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
 //   qDebug("Error:",errorrad);
    if (i != -1) {
	QMessageBox::critical( this, "LEVFAKTW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
     }else{
	filnamn.open( IO_WriteOnly | IO_Append );
	QTextStream stream(&filnamn);
		
//	 qDebug("slotEndOfProcess()::inrad=%s",inrad.latin1());
	 i = -1;
	 i = inrad.find( QRegExp("OK:"), 0 );
	 if (i != -1) {
	     i = -1;
	     i = inrad.find( QRegExp("NR_"), 0 );
	     if (i != -1) {
		 j =  inrad.find( QRegExp("_:"), i );
		 m = j - (i + 3);
		 antal = inrad.mid(i +3,m);
		 if (antal == "0") {
		     QMessageBox::information( this, "ATTBETW","Inga fakturor att betala!\n");
		 }else{
		     ant=antal.toInt();		     
		     for (n=0;n<ant;n++){
			 i = j;
			 j = inrad.find(QRegExp("_:"),i+2);
			 m = j - (i+2);
			 expdatum = inrad.mid(i+2,m);
			 i = j;
			 j = inrad.find(QRegExp("_:"),i+2);
			 m = j - (i+2);
			 levnr = inrad.mid(i+2,m);
			 i = j;
			 j = inrad.find(QRegExp("_:"),i+2);
			 m = j - (i+2);
			 faktnr = inrad.mid(i+2,m);
			 i = j;
			 j = inrad.find(QRegExp("_:"),i+2);
			 m = j - (i+2);
			 belopp = inrad.mid(i+2,m);
			 i = j;
			 j = inrad.find(QRegExp("_:"),i+2);
			 m = j - (i+2);
			 valuta = inrad.mid(i+2,m);
//			 qDebug("slotEndOfProcess() ::datum=%s levnr=%s faktnr=%s belopp=%s valuta=%s",datum.latin1(),levnr.latin1(),faktnr.latin1(),belopp.latin1(),valuta.latin1());
//     rad15="<Row level=\"0\" betaldatum=\"2003-08-30\" levnr=\"123\" fakturanr=\"1399087\" belopp=\"2500.00\" valuta=\"SEK\" />\n";
			 
			 rapportrad="<Row level=\"0\" ";
			 rapportrad.append(" betaldatum=\"");
			 rapportrad.append(expdatum);
			 rapportrad.append("\" levnr=\"");
			 rapportrad.append(levnr);
			 rapportrad.append("\" fakturanr=\"");
			 rapportrad.append(faktnr);
			 rapportrad.append("\" belopp=\"");
			 rapportrad.append(belopp);
			 rapportrad.append("\" valuta=\"");
			 rapportrad.append(valuta);
			 rapportrad.append("\"/>\n");
//			 qDebug("slotEndOfProcess()::rapportrad=%s",rapportrad.latin1());	
			 stream << rapportrad;
		     }
		 }
		 rapportrad="</KugarData>";
		 stream << rapportrad;
	     }
	 }	 
     }
     filnamn.close();
     QMessageBox::information( this, "ATTBETW","Rapport skapad!\n");
     system("kugar -d /tmp/attBetala.kud -r /usr/local/olfix/data/AttBet.kut");
     
     errorrad="";
     inrad="";
}

void frmLevFaktAttBetala::slotFileRemove(QString filnamn)
{
//  Ta bort temporärfilen /tmp/AttBetalar.txt
    bool status;
//    QString filnamn;
    QDir d = QDir::root();                      // "/"
    if ( !d.cd("tmp") ) {                       // "/tmp"
        qWarning( "Cannot find the \"/tmp\" directory" );
    }

//    filnamn="AttBetala.txt";
    status=d.remove(filnamn,FALSE);
    
//    qDebug("slotFileRemove()::TRUE=%d FALSE=%d",TRUE,FALSE);
//    qDebug("slotFileRemove()::filnamn=%s",filnamn.latin1());    
//    qDebug("slotFileRemove()::status=%d",status);   
}

void frmLevFaktAttBetala::slotDataOnStdout()
{
     while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
//     qDebug("slotDataOnStdout::inrad=%s",inrad.latin1());
}

void frmLevFaktAttBetala::slotDataOnStderr()
{
      while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}


void frmLevFaktAttBetala::slotCreateHeader()
{
    QString rad1;
    QString rad2;
    QString rad3;
    QString rad4;
    QString rad5;
    QString rad6;
    QString rad7;
    QString rad8;
    QString rad9;
    QString rad10;
    QString rad11;
    QString rad12;
    QString rad12b;
    QString rad13;
    QString rad14;
    QString rad15;
    QString rad16;
    QString rapportrad;
    
//    QFile filnamn( "/tmp/AttBetalaHeader.txt" );	// ändra till .kud  
    QFile filnamn("/tmp/attBetala.kud");
    QTextStream stream(&filnamn);
    
    slotFileRemove("attBetala.kud");	// radera gammal fil. Ändra till .kud

    rad1="<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    rad2="<!DOCTYPE KugarData [\n";
    rad3="   <!ELEMENT KugarData (Row* )>\n";
    rad4="   <!ATTLIST KugarData\n";
    rad5="      Template CDATA #REQUIRED>\n\n";
    rad6="   <!ELEMENT Row EMPTY>\n";
    rad7="   <!ATTLIST Row\n";
    rad8="      level CDATA #REQUIRED\n";
    rad9="      betaldatum CDATA #REQUIRED\n";
    rad10="      levnr CDATA #REQUIRED\n";
    rad11="      fakturanr CDATA #REQUIRED\n";
    rad12="      belopp CDATA #REQUIRED\n";
    rad12b="      valuta CDATA #REQUIRED>\n";
    rad13="]>\n\n";
    rad14="<KugarData Template=\"attBetalaTemplate.kut\">\n";	// ange rätt template
    // Datarader
//    rad15="<Row level=\"0\" betaldatum=\"2003-08-30\" levnr=\"123\" fakturanr=\"1399087\" belopp=\"2500.00\" valuta=\"SEK\" />\n";
//    rad16="</KugarData>";
	  
    rapportrad=rad1;
    rapportrad.append(rad2);
    rapportrad.append(rad3);
    rapportrad.append(rad4);
    rapportrad.append(rad5);
    rapportrad.append(rad6);
    rapportrad.append(rad7);
    rapportrad.append(rad8);
    rapportrad.append(rad9);
    rapportrad.append(rad10);
    rapportrad.append(rad11);
    rapportrad.append(rad12);
    rapportrad.append(rad12b);
    rapportrad.append(rad13);    
    rapportrad.append(rad14);    
//    rapportrad.append(rad15);
//    rapportrad.append(rad16);
    
    filnamn.open( IO_WriteOnly | IO_Append );
    stream << rapportrad;
//    filnamn.close();
}
