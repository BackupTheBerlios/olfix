/****************************************************************/
/**		SDOLISW					*/
/**		Ver 0.2                                                                                    */
/**		2003-08-21					*/
/**		Modified 2004-01-30				*/
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
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
#include <qmessagebox.h>
#include <qprocess.h>
#include <qdir.h>
#include <stdlib.h>
#include <qstring.h>
#include <qfile.h>
#include <qregexp.h>
#define VERSION "0.1"
#define MAXSTRING 5000

    QProcess* process;
    QString inrad;
    QString errorrad;
    QString bar;		// Bokföringsår
    QString csvflag;

void frmSaldolista::init()
{
    csvflag="J";
}

void frmSaldolista::slotlineEditBar_returnPressed()
{
    bar=lineEditBar->text();
    bar=bar.upper();
    lineEditBar->setText((bar));
    if (bar==""){
	QMessageBox::warning( this, "SDOLISW",
                      "Bokföringsår måste fyllas i! \n" );
	lineEditBar->setFocus();
    }else{  
	pushButtonOK->setFocus();
    }
}

void frmSaldolista::radioButtonCSV_toggled( bool )
{
    csvflag="J";
}

void frmSaldolista::radioButtonPrint_toggled( bool )
{
    csvflag="N";
}

void frmSaldolista::slotpushButtonOK_clicked()
{
    if (csvflag != "J"){
	slotFileRemove("Saldolista.kud");		// tag bort gammal datafil
	slotCreateHeader();
    }else{
	slotFileRemove("Saldolista.txt");		// tag bort gammal datafil	
    }
    slotGetData();
    pushButtonAvbryt->setFocus();
}

void frmSaldolista::slotGetData()
{
	const char *userp = getenv("USER");
            QString usr(userp);

	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "KTORPT");	// OLFIX funktion
	process->addArgument(bar);		// Bokföringsår

	frmSaldolista::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmSaldolista::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
            frmSaldolista::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );


	if (bar == "" ){
    	    QMessageBox::warning( this, "SDOLISW",
                      "Bokföringsår måste vara ifyllt!" );
	}
	else {
//	    qWarning(" Startar Addkonto 2");
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/SDOLIS!\n");
		QMessageBox::warning( this, "SDOLISW",
                            "Kan inte starta STYRMAN/KTORPT! \n" );
	    }
	}
}


void frmSaldolista::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmSaldolista::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmSaldolista::slotEndOfProcess()
{
    int i,j,m,n;
    int ant;

    QString antal;
    QString ktonr;
    QString ktonamn;
    QString dk;
    QString belopp;
    
    QString ktotemp;
    QString ktonamntemp;

    QString debetsum;		// Summa Debet
    QString kreditsum;		// Summa Kredit
    QString utgsaldo;		// Utgående saldo
    QString fil;
    QString rapportrad;
    
    double debet=0;
    double kredit=0;
    double usaldo=0;
    
    if (csvflag == "J"){
	fil="/tmp/Saldolista.txt";
//	slotFileRemove("Saldolista.txt");		// tag bort gammal datafil
    }else{
	fil="/tmp/Saldolista.kud";
//	slotFileRemove("Saldolista.kud");		// tag bort gammal datafil	
    }
    QFile filnamn( fil );
    utgsaldo="0.00";
//    qDebug("slotEndOfProcess() 1::inrad=%s",inrad.latin1());
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i == 0) {
	QMessageBox::critical( this, "OLFIX - SDOLISW",
		"ERROR!\n"+errorrad
		);
	errorrad="";
    }else{
	filnamn.open( IO_WriteOnly | IO_Append );
	QTextStream stream(&filnamn);
	
	i = -1;
	i = inrad.find( QRegExp("NR_"), 0 );
	if (i != -1) {
	    j =  inrad.find( QRegExp("_:"), i );
	    m = j - (i + 3);
	    antal = inrad.mid(i +3,m);
	    ant=antal.toInt();
//	    qDebug("slotEndOfProcess() 2 ::antal=%s ant=%d",antal.latin1(),ant);	    
	    ktotemp="";	 
	    for (n=0;n<=ant;n++){
		i = j;
		 j = inrad.find(QRegExp("_:"),i+2);
		 m = j - (i+2);
		 ktonr = inrad.mid(i+2,m);		 		 
		 i = j;
		 j = inrad.find(QRegExp("_:"),i+2);
		 m = j - (i+2);
		 ktonamn = inrad.mid(i+2,m);
		 i = j;
		 j = inrad.find(QRegExp("_:"),i+2);
		 m = j - (i+2);
		 dk = inrad.mid(i+2,m);		//D = Debet, K = Kredit  dk
		 i = j;
		 j = inrad.find(QRegExp("_:"),i+2);
		 m = j - (i+2);
		 belopp = inrad.mid(i+2,m);
		 
		 if (ktonr != ktotemp){
//			 qDebug("slotEndOfProcess()  3 ::ktonr=%s ktonamn=%s dk=%s belopp=%s\n",ktonr.latin1(),ktonamn.latin1(),dk.latin1(),belopp.latin1());
		     debetsum.setNum(debet,'f',2);
		     kreditsum.setNum(kredit,'f',2);
		     utgsaldo.setNum(usaldo,'f',2);
//		     qDebug("slotEndOfProcess()  3b ::cvsflag=%s",csvflag.latin1());
		     if (csvflag =="J"){
			 rapportrad=(ktotemp);
			 rapportrad.append(",");
			 rapportrad.append(ktonamntemp);
			 rapportrad.append(",");			 
			 rapportrad.append(debetsum);
			 rapportrad.append(",");
			 rapportrad.append(kreditsum);
			 rapportrad.append(",");			 
			 rapportrad.append(utgsaldo);
			 rapportrad.append("\n");
//			 qDebug("slotEndOfProcess()::rapportrad=%s",rapportrad.latin1());
			 if (ktotemp != ""){
			     stream << rapportrad;
			 }
		     }else{		 
//		     qDebug("slotEndOfProcess()  3c ::cvsflag=%s",csvflag.latin1());			 
			 rapportrad="<Row level=\"0\" ";
			 rapportrad.append(" kontonr=\"");
			 rapportrad.append(ktotemp);
			 rapportrad.append("\" kontonamn=\"");
			 rapportrad.append(ktonamntemp);
			 rapportrad.append("\" debet=\"");
			 rapportrad.append(debetsum);
			 rapportrad.append("\" kredit=\"");
			 rapportrad.append(kreditsum);
			 rapportrad.append("\" utgsaldo=\"");
			 rapportrad.append(utgsaldo);
			 rapportrad.append("\"/>\n");
//			 qDebug("slotEndOfProcess() 3d ::rapportrad=%s",rapportrad.latin1());
			 if (ktotemp != ""){
			     stream << rapportrad;
			 }
		     }
     		     ktotemp=ktonr;
		     ktonamntemp=ktonamn;
		     debet=0;
		     kredit=0;
		     usaldo=0;	     
		 }
		 if (dk == "D"){
		     debet=debet+belopp.toDouble();
		 }
		 if (dk == "K"){
		     kredit=kredit+belopp.toDouble();
		 }
//		 qDebug("slotEndOfProcess()  4 ::ktonr=%s belopp=%s debet=%f kredit=%f\n",ktonr.latin1(),belopp.latin1(),debet,kredit);
		 usaldo=debet -kredit;		 
	     }		 
	} 
	    if (csvflag != "J"){
		rapportrad="</KugarData>";
		stream << rapportrad;
	    }
	}
	filnamn.close();
	QMessageBox::information( this, "ATTBETW","Rapport skapad!\n");
	if (csvflag == "J"){
	    system("kspread /tmp/Saldolista.txt");
	}else{
	    // ändrad för kugar 1.2.92 ->
   	   // system("kugar -d /tmp/Saldolista.kud -r /usr/local/olfix/report/Saldolista.kut");
	    system("kugar /tmp/Saldolista.kud");
	}
     errorrad="";
     inrad="";
}

void frmSaldolista::slotCreateHeader()
{
    int i;
    QString rad[16];
    QString rapportrad;

    QFile filnamn("/tmp/Saldolista.kud");
    QTextStream stream(&filnamn);

    slotFileRemove("Saldolista.kud");	// radera gammal fil. Ändra till .kud

    rad[1]="<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n";
    rad[2]="<!DOCTYPE KugarData [\n";
    rad[3]="   <!ELEMENT KugarData (Row* )>\n";
    rad[4]="   <!ATTLIST KugarData\n";
    rad[5]="      Template CDATA #REQUIRED>\n\n";
    rad[6]="   <!ELEMENT Row EMPTY>\n";
    rad[7]="   <!ATTLIST Row\n";
    rad[8]="      level CDATA #REQUIRED\n";
    rad[9]="      kontonr CDATA #REQUIRED\n";
    rad[10]="      kontonamn CDATA #REQUIRED\n";
    rad[11]="      debet CDATA #REQUIRED\n";
    rad[12]="      kredit CDATA #REQUIRED\n";
    rad[13]="      utgsaldo CDATA #REQUIRED>\n";
    rad[14]="]>\n\n";
    rad[15]="<KugarData Template=\"/usr/local/olfix/report/Saldolista.kut\">\n";	// ange rätt template, absolut path

    rapportrad=rad[1];
    for (i=2;i<16;i++){
	rapportrad.append(rad[i]);
    }

//    qDebug("slotCreateHeader::rapportrad = \n%s",rapportrad.latin1());
    
    filnamn.open( IO_WriteOnly | IO_Append );
    stream << rapportrad;
}

void frmSaldolista::slotFileRemove(QString filnamn)
{
//  Ta bort temporärfilen /tmp/Saldolista.kud eller filen /tmp/Saldolista.txt
    bool status;
    QDir d = QDir::root();                   // "/"
    if ( !d.cd("tmp") ) {                       // "/tmp"
        qWarning( "Cannot find the \"/tmp\" directory" );
    }
    status=d.remove(filnamn,FALSE);
//    qDebug("slotFileRemove()::TRUE=%d FALSE=%d",TRUE,FALSE);
//    qDebug("slotFileRemove()::filnamn=%s",filnamn.latin1());
//    qDebug("slotFileRemove()::status=%d",status);
}
