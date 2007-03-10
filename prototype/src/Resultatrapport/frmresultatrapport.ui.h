/****************************************************************/
/**		RESRPTW					*/
/**		Ver 0.2                                                                               	 */
/**		Created:    2005-01-11				*/
/**		Modified: 2007-03-10				*/
/**   Copyright	Jan Pihlgren	jan@pihlgren.se		*/
/****************************************************************/
/*****************************************************************
 *					                                            *
 *   This program is free software; you can redistribute it and/or modify 	 *
 *   it under the terms of the GNU General Public License as published by       	 *
 *   the Free Software Foundation; either version 2 of the License, or     	 *
 *   (at your option) any later version.                                   		 	 *
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
#define VERSION "0.2"
#define MAXSTRING 5000

    QProcess* process;
    QString inrad;
    QString errorrad;
    QString inradPeriod;
    QString errorradPeriod;
    
    QString bar;		// Bokföringsår
    QString csvflag;
    QString delsumflag;
    QString datum;
    QString fromdate;
    QString tomdate;
    QString period;    
    QString ftgnamn;
    
    QString hjelpfil;
    QString reportpath;
    QString tmppath;
    QString kugarversion;
    QString kommando;
    
void frmResultatrapport::init()
{
    csvflag="N";		/*  Ska det vara en kommaseparerad rapport för Kspread. N=Nej 	*/
			/*  N = Gör en Kugarrapport 				*/
                                               /*  J = Gör en Kspreadrapport  				*/
    delsumflag="1";	               /* På vilken nivå ska delsummor göras. Default = nivå 1  	*/
    
    buttonGroup2->hide();
    textLabel1_2->hide();
    QDateTime dt = QDateTime::currentDateTime();
    datum=dt.toString("yyyy-MM-dd");
    textLabelDatum->setText(datum);
    frmResultatrapport::KugarVersion();
    frmResultatrapport::GetReportDir();
    frmResultatrapport::GetTmpDir();
    frmResultatrapport::getFortetagsnamn();
    frmResultatrapport::lineEditBar->setFocus();
}

void frmResultatrapport::slotlineEditBar_returnPressed()
{
    bar=lineEditBar->text();
    bar=bar.upper();
    lineEditBar->setText((bar));
    if (bar != ""){
	frmResultatrapport::GetBokfPeriod();	// Hämta fromdate och tomdate( datum för första och sista verifikationen)
    }else{
	lineEditBar->setText((bar));
    }
//    qDebug("fromdate=%s, tomdate=%s",fromdate.latin1(),tomdate.latin1());
//    period=fromdate+" -- "+tomdate;
//    qDebug("period=%s",period.latin1());
}

void frmResultatrapport::radioButtonKto1_toggled( bool )
{
    delsumflag="1";
}

void frmResultatrapport::radioButtonKto2_toggled( bool )
{
    delsumflag="2";
}

void frmResultatrapport::radioButtonKto3_toggled( bool )
{
    delsumflag="3";
}

void frmResultatrapport::radioButtonKto4_toggled( bool )
{
    delsumflag="4";
}

void frmResultatrapport::radioButtonCSV_toggled( bool )
{
    csvflag="J";
}

void frmResultatrapport::radioButtonPrint_toggled( bool )
{
    csvflag="N";
}

void frmResultatrapport::slotpushButtonOK_clicked()
{
    if (csvflag != "J"){
	slotFileRemove("Resultatrapport.kud");		// tag bort gammal datafil
	slotCreateHeader();
    }else{
	slotFileRemove("Resultatrapport.txt");		// tag bort gammal datafil	
    }
    slotGetData();
    pushButtonAvbryt->setFocus();
}

void frmResultatrapport::slotGetData()
{
	const char *userp = getenv("USER");
            QString usr(userp);

	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "KTORPT");	// OLFIX funktion
	process->addArgument(bar);		// Bokföringsår
	process->addArgument(fromdate);		// Från och med datum
	process->addArgument(tomdate);		// Till och med datum

	frmResultatrapport::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmResultatrapport::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
            frmResultatrapport::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );


	if (bar == "" ){
    	    QMessageBox::warning( this, "RESRPTW",
                      "Bokföringsår måste vara ifyllt!" );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		QMessageBox::warning( this, "RESRPTW",
                            "Kan inte starta STYRMAN/KTORPT! \n" );
	    }
	}
}

void frmResultatrapport::slotEndOfProcess()
{
    int i,j,m,n;
    int ant;
    int klassflag=0;

    QString antal;
    QString ktonr;
    QString ktonamn;
    QString dk;
    QString belopp;
    QString vernr;
    
    QString rubrik;
    QString ktotemp;
    QString ktonamntemp;
    int klasstemp=0;

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
    
//	Total
    QString totaldb;		// Total Debet
    QString totalkr;		// Total Kredit
    QString totalutgsaldo;		//  Total Utgående saldo
    double totaldebet=0;
    double totalkredit=0;
    double totalusaldo=0;
    
    
    QString fil;
    QString rapportrad;
    QString rubrikrad;
        
    if (csvflag == "J"){
	fil=tmppath+"Resultatrapport.txt";
    }else{
	fil=tmppath+"Resultatrapport.kud";
    }
    
    QFile filnamn( fil );
    utgsaldo="0.00";
//    qDebug("slotEndOfProcess() 1::inrad=%s",inrad.latin1());
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i == 0) {
	QMessageBox::critical( this, "OLFIX - RESRPTW",
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
	    ant=antal.toInt();		/* Antal verifikationsrader	*/
//	    qDebug("slotEndOfProcess() 2 ::antal=%s ant=%d",antal.latin1(),ant);	    
	    ktotemp="";	 
	    for (n=1;n<=ant+1;n++){
		i = j;
		 j = inrad.find(QRegExp("_:"),i+2);
		 m = j - (i+2);
		 ktonr = inrad.mid(i+2,m);	
//		 qDebug("ktonr=%s",ktonr.latin1());
		 i = j;
		 j = inrad.find(QRegExp("_:"),i+2);
		 m = j - (i+2);
		 ktonamn = inrad.mid(i+2,m);
		 i = j;
		 j = inrad.find(QRegExp("_:"),i+2);
		 m = j - (i+2);
		 dk = inrad.mid(i+2,m);		//dk = D  = Debet, dk =  K = Kredit 
		 i = j;
		 j = inrad.find(QRegExp("_:"),i+2);
		 m = j - (i+2);
		 belopp = inrad.mid(i+2,m);
		 i = j;
		 j = inrad.find(QRegExp("_:"),i+2);
		 m = j - (i+2);
		 vernr = inrad.mid(i+2,m);
//		 qDebug("n=%d ktonr=%s",n,ktonr.latin1());
//	qDebug("Debug nr 1: ktonr=%s, ktotemp=%s, rubrik=%s, klassflag=%d, klasstemp=%d",ktonr.latin1(),ktotemp.latin1(),rubrik.latin1(),klassflag,klasstemp); 
//		 qDebug("ktonr.mid(0,1)=%s",ktonr.mid(0,1).latin1());
		 if ((ktonr.mid(0,1).toInt()>2) && (ktonr != ktotemp) || (ktonr.find(QRegExp("END"),0) != -1)) {
//		     qDebug("kontonr=%s",ktonr.latin1());
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
		     }else{		 		// Skapa rapportrad för Kugar
//			 qDebug("ktonr=%s, ktotemp=%s, klassflag=%d, klasstemp=%d",ktonr.latin1(),ktotemp.latin1(),klassflag,klasstemp);
			 if (ktotemp==""){
			     rapportrad="<Rubrik1 level=\"1\" ";
			     rapportrad.append("klass1=\"");
			     rapportrad.append("3");
			     rapportrad.append("\" klassnamn=\"");
			     rapportrad.append("RÖRELSEINTÄKTER");
			     rapportrad.append("\"/>\n");
			     stream << rapportrad;
			     klassflag=2999;			  
			 }
			 
			 if (ktotemp.mid(0,2).toInt()==30 && klassflag != 3000){
			     rubrik="Försäljning";
			     rapportrad="<Rubrik2 level=\"2\" ";
			     rapportrad.append("klass1=\"");
			     rapportrad.append("30");
			     rapportrad.append("\" klassnamn=\"");
			     rapportrad.append(rubrik);
			     rapportrad.append("\"/>\n");
			     stream << rapportrad;
			     klassflag=3000;			     
			 }
			 			 
			 if(ktotemp.mid(0,1).toInt() == 4 && klassflag < 4000){
			     rubrik="RÖRELSEKOSTNADER";	     
			     rapportrad="<Rubrik1 level=\"1\" ";
			     rapportrad.append("klass1=\"");
			     rapportrad.append("4");
			     rapportrad.append("\" klassnamn=\"");
			     rapportrad.append(rubrik);
			     rapportrad.append("\"/>\n");
			     stream << rapportrad;
			     klassflag=3999;			     
			 }
			 
			 if (ktotemp.mid(0,2).toInt()==40 && klassflag != 4000){
			     rubrik="Material och varor";
			     rubrikrad="<Rubrik2 level=\"2\" ";
			     rubrikrad.append("klass1=\"");
			     rubrikrad.append("40");
			     rubrikrad.append("\" klassnamn=\"");
			     rubrikrad.append(rubrik);
			     rubrikrad.append("\"/>\n");
			     stream << rubrikrad;
			     klassflag=4000;
			 }
			 
			 if (ktotemp.mid(0,1).toInt() >= 5 && ktotemp.mid(0,1).toInt() < 7 && klassflag != 5000){
			     rubrik="Övriga externa rörelseutgifter";			     
			     rapportrad="<Rubrik2 level=\"2\" ";
			     rapportrad.append("klass1=\"");
			     rapportrad.append("50-69");
			     rapportrad.append("\" klassnamn=\"");
			     rapportrad.append(rubrik);
			     rapportrad.append("\"/>\n");
			     stream << rapportrad;
			     klassflag=5000;
			 }
			 
			 if (ktotemp.mid(0,1).toInt() > 7 && ktotemp.mid(0,2).toInt() < 78 && klassflag != 7000){
			     rubrik="Utgifter för personal";
			     rapportrad="<Rubrik2 level=\"2\" ";
			     rapportrad.append("klass1=\"");
			     rapportrad.append("70-77");
			     rapportrad.append("\" klassnamn=\"");
			     rapportrad.append(rubrik);
			     rapportrad.append("\"/>\n");
			     stream << rapportrad;
			     klassflag=7000;
			 }
			 
			 if (ktotemp.mid(0,2).toInt() >= 78 && ktotemp.mid(0,1).toInt() < 8 && klassflag != 7800){
			     rubrik="Avskrivningar/nedskrivningar";
			     rapportrad="<Rubrik2 level=\"2\" ";
			     rapportrad.append("klass1=\"");
			     rapportrad.append("78");
			     rapportrad.append("\" klassnamn=\"");
			     rapportrad.append(rubrik);
			     rapportrad.append("\"/>\n");
			     stream << rapportrad;
			     klassflag=7800;
			 }
			 
//qDebug("Debug nr 2: ktotemp=%s, ktonr=%s, rubrik=%s, klassflag=%d, klasstemp=%d n=%d",ktotemp.latin1(),ktonr.latin1(),rubrik.latin1(),klassflag,klasstemp,n); 		
//			 if ((ktonr.mid(0,1).toInt() > 6) || (ktonr=="END")){
/*                                     if (ktonr.find(QRegExp("END"),0)>=0) {
			     qDebug("ktotemp=%s, ktonr=%s, klasstemp=%d, ant=%d, n=%d",ktotemp.latin1(),ktonr.latin1(),klasstemp,ant,n);
			 }
*/			 
			 if ((ktotemp.mid(0,2).toInt() >= 80 && klassflag != 8000) || ktonr == "END" ) {
//			     qDebug("Finansiella inkomster och utgifter. n=%d",n);
			     rubrik="Finansiella inkomster och utgifter";
			     rapportrad="<Rubrik2 level=\"2\" ";
			     rapportrad.append("klass1=\"");
			     rapportrad.append("80");
			     rapportrad.append("\" klassnamn=\"");
			     rapportrad.append(rubrik);
			     rapportrad.append("\"/>\n");
			     stream << rapportrad;
			     klassflag=8000;
			 }
/*			 if (ktotemp.mid(0,2).toInt()==27 && klassflag != 2700){
			     rubrik="PERSONALENS KÄLLSKATT MM";
			     rapportrad="<Rubrik2 level=\"2\" ";
			     rapportrad.append("klass1=\"");
			     rapportrad.append("27");
			     rapportrad.append("\" klassnamn=\"");
			     rapportrad.append(rubrik);
			     rapportrad.append("\"/>\n");
			     stream << rapportrad;
			     klassflag=2700;
*/			 			 
			 rapportrad="<Row level=\"3\" ";
			 rapportrad.append(" kontonr=\"");
			 rapportrad.append(ktotemp);
			 rapportrad.append("\" kontonamn=\"");
			 ktonamntemp="  "+ktonamntemp;
			 rapportrad.append(ktonamntemp);
			 rapportrad.append("\" debet=\"");
			 rapportrad.append(debetsum);
			 rapportrad.append("\" kredit=\"");
			 rapportrad.append(kreditsum);
			 rapportrad.append("\" utgsaldo=\"");
			 rapportrad.append(utgsaldo);
			 rapportrad.append("\"/>\n");
			  
//			 qDebug("slotEndOfProcess() 3d ::rapportrad=%s klassflag=%d, klasstemp=%d",rapportrad.latin1(),klassflag,klasstemp);
			 if (ktotemp != ""){			  
			     stream << rapportrad;
			 }		    
			 
//	  	   	 qDebug("ktotemp=%s mid=%s",ktotemp.latin1(),ktotemp.mid(0,1).latin1());
			 if (ktonr.mid(0,1) != ktotemp.mid(0,1) && ktotemp !=""){
			     delsumdebet.setNum(deldebet,'f',2);
			     delsumkredit.setNum(delkredit,'f',2);
			     delsumutgsaldo.setNum(delusaldo,'f',2);			
			 
			     rapportrad="<Delsumma level=\"4\" ";
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
		     klasstemp=klassflag;
		     debet=0;
		     kredit=0;
		     usaldo=0;	     
		 }
		 if (ktonr.mid(0,1).toInt()>2){
		 if (dk == "D"){
		     debet=debet+belopp.toDouble();
		     deldebet=deldebet+belopp.toDouble();
		     totaldebet=totaldebet+belopp.toDouble();
		 }
		 if (dk == "K"){
		     kredit=kredit+belopp.toDouble();
		     delkredit=delkredit+belopp.toDouble();
		     totalkredit=totalkredit+belopp.toDouble();
		 }
		 usaldo=debet -kredit;
		 delusaldo=deldebet-delkredit;
		 totalusaldo=totaldebet-totalkredit;
	     }
	     }
	}
	
	if (csvflag != "J"){
/********************************************************/	    
/*		Här läggs totalen in			*/
/********************************************************/	    
	    totaldb.setNum(totaldebet,'f',2);
	    totalkr.setNum(totalkredit,'f',2);
	    totalutgsaldo.setNum(totalusaldo,'f',2);
	    
	    rapportrad="<Total level=\"5\" ";
	    rapportrad.append(" delsumdebet=\"");
	    rapportrad.append(totaldb);
	    rapportrad.append("\" delsumkredit=\"");
	    rapportrad.append(totalkr);
	    rapportrad.append("\" delsumutgsaldo=\"");
	    rapportrad.append(totalutgsaldo);
	    rapportrad.append("\"/>\n");
	    stream << rapportrad;
/********************************************************/
/*	Avslutande XML-rad	    			*/
/********************************************************/	    
	    rapportrad="</KugarData>";
	    stream << rapportrad;
	}
    }
    filnamn.close();
    QMessageBox::information( this, "RESRPTW","Rapport skapad!\n");
    if (csvflag == "J"){
	frmResultatrapport::slotRunPrinting("Resultatrapport.txt","" );
    }else{
	frmResultatrapport::slotRunPrinting("Resultatrapport.kud","Resultatrapport.kut" );
    }    
    errorrad="";
     inrad="";
}

void frmResultatrapport::slotCreateHeader()
{
    int i;
    int antrad=55;
    QString rad[antrad];
    QString rapportrad;

    QFile filnamn(tmppath+"Resultatrapport.kud");
    QTextStream stream(&filnamn);

    slotFileRemove(tmppath+"Resultatrapport.kud");	// radera gammal fil

    rad[1]="<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n";
    rad[2]="<!DOCTYPE KugarData [\n";
    rad[3]="   <!ELEMENT KugarData (Rowhead* )>\n";
    rad[4]="   <!ATTLIST KugarData\n";
    rad[5]="      Template CDATA #REQUIRED>\n\n";
    rad[6]="   <!ELEMENT Rowhead EMPTY>\n";
    rad[7]="   <!ATTLIST Rowhead\n";
    rad[8]="      level CDATA #REQUIRED\n";
    rad[9]="      ftgnamn CDATA #REQUIRED\n";
    rad[10]="      period CDATA #REQUIRED\n";
    rad[11]="      datum CDATA #REQUIRED\n";
    rad[12]=">\n";
    rad[13]="   <!ELEMENT KugarData (Rubrik1* )>\n";
    rad[14]="   <!ATTLIST KugarData\n";
    rad[15]="      Template CDATA #REQUIRED>\n\n";
    rad[16]="   <!ELEMENT Rubrik1 EMPTY>\n";
    rad[17]="   <!ATTLIST Rubrik1\n";
    rad[18]="      level CDATA #REQUIRED\n";
    rad[19]="      klass1 CDATA #REQUIRED\n";
    rad[20]="      klassnamn CDATA #REQUIRED\n";
    rad[21]=">\n";
    rad[22]="   <!ELEMENT KugarData (Rubrik2* )>\n";
    rad[23]="   <!ATTLIST KugarData\n";
    rad[24]="      Template CDATA #REQUIRED>\n\n";
    rad[25]="   <!ELEMENT Rubrik2 EMPTY>\n";
    rad[26]="   <!ATTLIST Rubrik2\n";
    rad[27]="      level CDATA #REQUIRED\n";
    rad[28]="      klass1 CDATA #REQUIRED\n";
    rad[29]="      klassnamn CDATA #REQUIRED\n";
    rad[30]=">\n";
    rad[31]="   <!ELEMENT KugarData (Row* )>\n";
    rad[32]="   <!ATTLIST KugarData\n";
    rad[33]="      Template CDATA #REQUIRED>\n\n";
    rad[34]="   <!ELEMENT Row EMPTY>\n";
    rad[35]="   <!ATTLIST Row\n";
    rad[36]="      level CDATA #REQUIRED\n";
    rad[37]="      kontonr CDATA #REQUIRED\n";
    rad[38]="      kontonamn CDATA #REQUIRED\n";
    rad[39]="      debet CDATA #REQUIRED\n";
    rad[40]="      kredit CDATA #REQUIRED\n";
    rad[41]="      utgsaldo CDATA #REQUIRED";
    rad[42]=">\n";
    rad[43]="   <!ELEMENT KugarData (Delsumma* )>\n";
    rad[44]="   <!ATTLIST KugarData\n";
    rad[45]="      Template CDATA #REQUIRED>\n\n";
    rad[46]="   <!ELEMENT Delsumma EMPTY>\n";
    rad[47]="   <!ATTLIST Delsumma\n";
    rad[48]="      level CDATA #REQUIRED\n";
    rad[49]="      delsumdebet CDATA #REQUIRED\n";
    rad[50]="      delsumkredit CDATA #REQUIRED\n";
    rad[51]="      delsumutgsaldo CDATA #REQUIRED\n";    
    rad[52]=">\n";       
    rad[53]="]>\n\n";
    rad[54]="<KugarData Template=\"";
    rad[54].append(reportpath);
    rad[54].append("Resultatrapport.kut\">\n");	// ange rätt template, absolut path

//    qDebug("slotCreateHeader::rapportrad = \n%s",rapportrad.latin1());
    rapportrad=rad[1];
    for (i=2;i<(antrad);i++){
	rapportrad.append(rad[i]);
    }
    rapportrad.append("<Rowhead level=\"0");
    rapportrad.append("\" ftgnamn=\"");
    rapportrad.append(ftgnamn);
    rapportrad.append("\" period=\"");
    rapportrad.append(period);
    rapportrad.append("\" datum=\"");
    rapportrad.append(datum);
    rapportrad.append("\"/>\n");    

//    qDebug("slotCreateHeader::rapportrad = \n%s",rapportrad.latin1());
    
    filnamn.open( IO_WriteOnly | IO_Append );
    stream << rapportrad;
}

void frmResultatrapport::slotFileRemove(QString filnamn)
{
//  Ta bort temporärfilen /tmp/Resultatrapport.kud eller filen /tmp/Resultatrapport.txt
    bool status;
    QDir d = QDir::root();                   // "/"
    if ( !d.cd("tmp") ) {                       // "/tmp"
        qWarning( "Cannot find the \"/tmp\" directory" );
    }
    status=d.remove(filnamn,FALSE);
}

void frmResultatrapport::KugarVersion()
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
   frmResultatrapport::slotFileRemove("kugarversion.txt");
}

void frmResultatrapport::GetReportDir()
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

void frmResultatrapport::GetTmpDir()
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
	i = inrad.find( QRegExp("VTMP="), 0 );
	if(i == 0){
	    tmppath=inrad.mid(5,inrad.length()-5);
	    i= -1;
	}
    }
    file.close ();
//    qDebug("tmppath=%s",tmppath.latin1());
}

void frmResultatrapport::getFortetagsnamn()
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

	frmResultatrapport::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmResultatrapport::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
            frmResultatrapport::connect( process, SIGNAL(processExited() ),this, SLOT(slotFtgnamnEndOfProcess() ) );


	if ( !process->start() ) {
		QMessageBox::warning( this, "RESRPTW",
                            "Kan inte starta STYRMAN/FTGDSP! \n" );
	}
}

void frmResultatrapport::slotFtgnamnEndOfProcess()
{
    int i,j,m;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i == 0) {
	QMessageBox::critical( this, "OLFIX - RESRPTW",
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
//	qDebug("inrad=%s ",inrad.latin1());
//	qDebug("ftgnamn=%s, j=%d, m=%d, lengd=%d",ftgnamn.latin1(),j,m,inrad.length());
}

QString frmResultatrapport::CheckDatum( QString datumet )
{
    /*      Kontrollera och formatera datum enligt 20ÅÅ-MM-DD */
    int i;
    int j,k;
    QString tempdatum;
    QString millenium;
//    QString tmp;

    i = datumet.length();
    k = datumet.find( QRegExp("-"), 0 );
    j = datumet.find( QRegExp("-"), k+1 );
    millenium=datum.mid(0,2);

//    qDebug("millenium=%s, datumet=%s, datumetlängd=%d, datumet 1:a - =%d, datumet 2:a - %d",millenium.latin1(),datumet.latin1(),i,k,j);

    tempdatum=datumet;
    if (i < 7 && k < 0 && j < 0){
	tempdatum = millenium+datumet.mid(0,2)+"-"+datumet.mid(2,2)+"-"+datumet.mid(4,2);
    }
    if (i == 7 && k < 0 && j < 0){
	tempdatum = millenium+datumet.mid(1,2)+"-"+datumet.mid(3,2)+"-"+datumet.mid(5,2);
    }
    if (i == 8 && k < 0 && j < 0){
	tempdatum = millenium+datumet.mid(2,2)+"-"+datumet.mid(4,2)+"-"+datumet.mid(6,2);
    }
    if (i == 9 && k < 0 && j < 0){
	tempdatum = millenium+datumet.mid(3,2)+"-"+datumet.mid(5,2)+"-"+datumet.mid(7,2);
    }
    if (i < 10 && k > 0 ){
	if (k > 0 && k <5){
	    if ( j < 0){
		tempdatum =datumet.mid(0,k+1)+datumet.mid(k+1,2)+"-"+datumet.mid(k+3,2);
	    }
	    if (j > 0){
		tempdatum ="20"+datumet.mid(0,k+1)+datumet.mid(k+1,2)+datumet.mid(j,3);
	    }
	}
	if (k > 4 && k <7){
	    if ( j < 0){
		tempdatum =datumet.mid(0,4)+"-"+datumet.mid(4,2)+"-"+datumet.mid(k+1,2);
	    }
	    if (j > 0){
		tempdatum =datumet.mid(0,4)+"-"+datumet.mid(4,2)+datumet.mid(j,3);
	    }
	}
    }
//    qDebug("tempdatum=%s, ",tempdatum.latin1());
        return tempdatum;
}

void frmResultatrapport::GetBokfPeriod()
{
	const char *userp = getenv("USER");
                QString usr(userp);
	errorrad="";
	inrad="";

	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "VERHDSP");	// OLFIX funktion
	process->addArgument(bar);		// Bokföringsår

	if (bar==""){
	    QMessageBox::warning( this, "RESRPTW",
				  "Bokföringsår måste fyllas i! \n" );
	    lineEditBar->setFocus();
	    return;
	}

	frmResultatrapport::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotPeriodDataOnStderr() ) );
	frmResultatrapport::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotPeriodDataOnStdout() ) );
                frmResultatrapport::connect( process, SIGNAL(processExited() ),this, SLOT(slotGetBokfPeriodEndOfProcess() ) );


	if ( !process->start() ) {
		QMessageBox::warning( this, "RESRPTW",
                            "Kan inte starta STYRMAN/VERHDSP! \n" );
	}
}

void frmResultatrapport::slotGetBokfPeriodEndOfProcess()
{
    QString mindate;
    QString maxdate;
    int i,j,m;
    i = -1;
    i = errorradPeriod.find( QRegExp("Error:"), 0 );
    if (i == 0) {
	QMessageBox::critical( this, "OLFIX - RESRPTW",
		"ERROR!\n"+errorradPeriod
		);
	errorradPeriod="";
    }else{
	i = -1;
	i = inradPeriod.find( QRegExp("OK:"), 0 );
	if (i != -1) {
	    j =  inradPeriod.find( QRegExp("01:"), 0 );
	    m=10;
	    mindate = inradPeriod.mid(j+3,m);
	    j =  inradPeriod.find( QRegExp("02:"), 0 );
	    m=10;
	    maxdate = inradPeriod.mid(j+3,m);
	}
	period=mindate+" -- "+maxdate;
    }
    fromdate=mindate;
    tomdate=maxdate;
//   qDebug("period=%s|,m=%d",period.latin1(),m);
//    qDebug("fromdate=%s, tomdate=%s",fromdate.latin1(),tomdate.latin1());
}

void frmResultatrapport::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmResultatrapport::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmResultatrapport::slotPeriodDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inradPeriod.append(line);
	inradPeriod.append("\n");
    }
}

void frmResultatrapport::slotPeriodDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorradPeriod.append(line);
	errorradPeriod.append("\n");
    }
}

void frmResultatrapport::slotRunPrinting(QString rptfile,QString rpttemplate )
{
	inrad="";
	errorrad="";

	process = new QProcess();
	process->addArgument("./PRTAPI" );		// OLFIX program
	process->addArgument(csvflag);
	process->addArgument(rptfile);
	process->addArgument(rpttemplate);
//	qDebug("csvflag=%s, rptfile=%s, rpttemplate=%s",csvflag.latin1(),rptfile.latin1(),rpttemplate.latin1());
	frmResultatrapport::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnPrtStderr() ) );
	frmResultatrapport::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfPrtProcess() ) );

	if ( !process->start() ) {
	    // error handling
	    QMessageBox::warning( this, "OLFIX","Kan inte starta PRTAPI!\n" );
	}
    }

void frmResultatrapport::slotDataOnPrtStderr()
{
   while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmResultatrapport::slotEndOfPrtProcess()
{
    int i;
    i = -1;
    i = inrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "OLFIXW",
		"ERROR!\n"+inrad
	);
	inrad="";
	i = -1;
     }
}

void frmResultatrapport::pushBtnHelp_clicked()
{
	inrad="";
	frmResultatrapport::readResursFil();		// Hämta path till hjälpfilen

	int i1 = hjelpfil.find( QRegExp(".html"), 0 );
//	int i2 = hjelpfil.length();
	hjelpfil=hjelpfil.left(i1);
	hjelpfil=hjelpfil+"_RAPPORTER.html";
	hjelpfil=hjelpfil+"#RESULTATRAPPORT";		// Lägg till position
//	qDebug("hjelpfil=%s",hjelpfil.latin1());

	process = new QProcess();
	process->addArgument( "./OLFIXHLP" );		// OLFIX program  (20061213)
	process->addArgument(hjelpfil);

	if ( !process->start() ) {
	    // error handling
	    QMessageBox::warning( this, "RESRPTW","Kan inte starta OLFIXHLP!\n" );
	}
	lineEditBar->setFocus();
}

void frmResultatrapport::readResursFil()
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
