/****************************************************************/
/**		SDOLISW					*/
/**		Ver 0.4                                                                                    */
/**		Created    2003-08-21				*/
/**		Modified 2004-03-14				*/
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
#include <qdatetime.h>
#define VERSION "0.1"
#define MAXSTRING 5000

    QProcess* process;
    QString inrad;
    QString errorrad;
    QString bar;		// Bokföringsår
    QString csvflag;
    QString datum;
    QString ftgnamn;

    QString reportpath;
    QString kugarversion;
    QString kommando;
    
void frmSaldolista::init()
{
    csvflag="N";		/*  Ska det vara en kommaseparerad rapport för Kspread. N=Nej 	*/
			/*  N = Gör en Kugarrapport 					*/
                                    /*  J = Gör en Kspreadrapport  				*/
    
    QDateTime dt = QDateTime::currentDateTime();
//    dag= QDate::currentDate().dayOfWeek();
    datum=dt.toString("yyyy-MM-dd");
    textLabelDatum->setText(datum);
    frmSaldolista::KugarVersion();
    frmSaldolista::GetReportDir();
    frmSaldolista::getFortetagsnamn();
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

//	Summa per konto    
    QString debetsum;		// Summa Debet
    QString kreditsum;		// Summa Kredit
    QString utgsaldo;		// Utgående saldo
    double debet=0;
    double kredit=0;
    double usaldo=0;
    
//	Summa per kontoklass    
    QString delsumdebet;
    QString delsumkredit;
    QString delsumutgsaldo;
    double deldebet=0;
    double delkredit=0;
    double delusaldo=0;
    
    QString fil;
    QString rapportrad;
        
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
		     debetsum.setNum(debet,'f',2);
		     kreditsum.setNum(kredit,'f',2);
		     utgsaldo.setNum(usaldo,'f',2);
//		     qDebug("slotEndOfProcess()  3b ::cvsflag=%s",csvflag.latin1());
		     if (csvflag =="J"){			// Skapa rapportrad för Kspread
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
 			 if (ktonr.mid(0,1) != ktotemp.mid(0,1) && ktotemp !=""){
     			     delsumdebet.setNum(deldebet,'f',2);
			     delsumkredit.setNum(delkredit,'f',2);
			     delsumutgsaldo.setNum(delusaldo,'f',2);			
			     rapportrad="Delsumma";
			     rapportrad.append(",");
			     rapportrad.append("");		// Blankt kontonamnsfält
			     rapportrad.append(",");
			     rapportrad.append(delsumdebet);
			     rapportrad.append(",");
			     rapportrad.append(delsumkredit);
			     rapportrad.append(",");
			     rapportrad.append(delsumutgsaldo);
			     rapportrad.append("\n");
			     stream << rapportrad;
			     deldebet=0;
			     delkredit=0;
			     delusaldo=0;
			 }
		     }else{		 		// Skapa raportrad för Kugar
			 rapportrad="<Row level=\"1\" ";
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
//	  	   	 qDebug("ktotemp=%s mid=%s",ktotemp.latin1(),ktotemp.mid(0,1).latin1());
			 if (ktonr.mid(0,1) != ktotemp.mid(0,1) && ktotemp !=""){
			     delsumdebet.setNum(deldebet,'f',2);
			     delsumkredit.setNum(delkredit,'f',2);
			     delsumutgsaldo.setNum(delusaldo,'f',2);			
			 
			     rapportrad="<Delsumma level=\"2\" ";
			     rapportrad.append(" delsumdebet=\"");
			     rapportrad.append(delsumdebet);
			     rapportrad.append("\" delsumkredit=\"");
			     rapportrad.append(delsumkredit);
			     rapportrad.append("\" delsumutgsaldo=\"");
			     rapportrad.append(delsumutgsaldo);
//			     qDebug("%s, %s, %s",delsumdebet.latin1(),delsumkredit.latin1(),delsumutgsaldo.latin1());
			     rapportrad.append("\"/>\n");
			     stream << rapportrad;
			     deldebet=0;
			     delkredit=0;
			     delusaldo=0;
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
		     deldebet=deldebet+belopp.toDouble();
		 }
		 if (dk == "K"){
		     kredit=kredit+belopp.toDouble();
		     delkredit=delkredit+belopp.toDouble();
		 }
		 usaldo=debet -kredit;
		 delusaldo=deldebet-delkredit;
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
	frmSaldolista::CallKugar();
    }
     errorrad="";
     inrad="";
}

void frmSaldolista::slotCreateHeader()
{
    int i;
    int antrad=36;
    QString rad[antrad];
    QString rapportrad;

    QFile filnamn("/tmp/Saldolista.kud");
    QTextStream stream(&filnamn);

    slotFileRemove("Saldolista.kud");	// radera gammal fil. Ändra till .kud

    rad[1]="<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n";
    rad[2]="<!DOCTYPE KugarData [\n";
    rad[3]="   <!ELEMENT KugarData (Rowhead* )>\n";
    rad[4]="   <!ATTLIST KugarData\n";
    rad[5]="      Template CDATA #REQUIRED>\n\n";
    rad[6]="   <!ELEMENT Rowhead EMPTY>\n";
    rad[7]="   <!ATTLIST Rowhead\n";
    rad[8]="      level CDATA #REQUIRED\n";
    rad[9]="      ftgnamn CDATA #REQUIRED\n";
    rad[10]="      datum CDATA #REQUIRED\n";
    rad[11]=">\n";
    rad[12]="   <!ELEMENT KugarData (Row* )>\n";
    rad[13]="   <!ATTLIST KugarData\n";
    rad[14]="      Template CDATA #REQUIRED>\n\n";
    rad[15]="   <!ELEMENT Row EMPTY>\n";
    rad[16]="   <!ATTLIST Row\n";
    rad[17]="      level CDATA #REQUIRED\n";
    rad[18]="      kontonr CDATA #REQUIRED\n";
    rad[19]="      kontonamn CDATA #REQUIRED\n";
    rad[20]="      debet CDATA #REQUIRED\n";
    rad[21]="      kredit CDATA #REQUIRED\n";
    rad[22]="      utgsaldo CDATA #REQUIRED";
    rad[23]=">\n";
    rad[24]="   <!ELEMENT KugarData (Delsumma* )>\n";
    rad[25]="   <!ATTLIST KugarData\n";
    rad[26]="      Template CDATA #REQUIRED>\n\n";
    rad[27]="   <!ELEMENT Delsumma EMPTY>\n";
    rad[28]="   <!ATTLIST Delsumma\n";
    rad[29]="      level CDATA #REQUIRED\n";
    rad[30]="      delsumdebet CDATA #REQUIRED\n";
    rad[31]="      delsumkredit CDATA #REQUIRED\n";
    rad[32]="      delsumutgsaldo CDATA #REQUIRED\n";    
    rad[33]=">\n";       
    rad[34]="]>\n\n";
    rad[35]="<KugarData Template=\"";
    rad[35].append(reportpath);
    rad[35].append("Saldolista.kut\">\n");	// ange rätt template, absolut path
;
//    qDebug("slotCreateHeader::rapportrad = \n%s",rapportrad.latin1());
    rapportrad=rad[1];
    for (i=2;i<(antrad);i++){
	rapportrad.append(rad[i]);
    }
    
//    qDebug("i=%d,antrad=%d",i,antrad);
    rapportrad.append("<Rowhead level=\"0");
    rapportrad.append("\" ftgnamn=\"");
    rapportrad.append(ftgnamn);    
    rapportrad.append("\" datum=\"");
    rapportrad.append(datum);
    rapportrad.append("\"/>\n");    

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
}

void frmSaldolista::KugarVersion()
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
   frmSaldolista::slotFileRemove("kugarversion.txt");
}

void frmSaldolista::GetReportDir()
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

void frmSaldolista::CallKugar()
{
    if (kugarversion<"1.2.92"){
	kommando="kugar -d /tmp/Saldolista.kud -r "+reportpath+"Saldolista.kut";
//	qDebug("kommando=%s",kommando.latin1());
	system(kommando);
    }else{
	system("kugar  /tmp/Saldolista.kud");
    }
}

void frmSaldolista::getFortetagsnamn()
{
	const char *userp = getenv("USER");
            QString usr(userp);
	errorrad="";
	inrad="";
	
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "FTGDSP");	// OLFIX funktion
	process->addArgument("FNAMN");	// Företagsnamn

	frmSaldolista::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmSaldolista::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
            frmSaldolista::connect( process, SIGNAL(processExited() ),this, SLOT(slotFtgnamnEndOfProcess() ) );


	if ( !process->start() ) {
		QMessageBox::warning( this, "SDOLISW",
                            "Kan inte starta STYRMAN/FTGDSP! \n" );
	}
}

void frmSaldolista::slotFtgnamnEndOfProcess()
{
    int i,j,m;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i == 0) {
	QMessageBox::critical( this, "OLFIX - SDOLISW",
		"ERROR!\n"+errorrad
		);
	errorrad="";
    }else{	
	i = -1;
	i = inrad.find( QRegExp("OK:"), 0 );
	if (i != -1) {
	    j =  inrad.find( QRegExp("2:"), 0 );
	    m=inrad.length()-j;
	    ftgnamn = inrad.mid(j+2,m-4);
	}
    }
//	qDebug("inrad=%s j=%d m=%d length=%d",inrad.latin1(),j,m,inrad.length());
//	qDebug("ftgnamn=%s|,m=%d",ftgnamn.latin1(),m);
}
