/****************************************************************/
/**		HUVBOKW					*/
/**		Ver 0.2                                                                                    */
/**		Created    2004-03-30				*/
/**		Modified 2004-04-09				*/ 
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
    QString bar;		// BokfˆringsÂr
    QString csvflag;
    QString datum;
    QString fromdatum;
    QString fromdate;
    QString fromvernr;
    QString tomdatum;
    QString tomdate;
    QString tomvernr;
    QString period;
    QString ftgnamn;

    QString reportpath;
    QString tmppath;
    QString kugarversion;
    QString kommando;
    
void frmHuvudbok::init()
{
    csvflag="N";		/*  Ska det vara en kommaseparerad rapport fˆr Kspread. N=Nej 	*/
			/*  N = Gˆr en Kugarrapport 					*/
                                    /*  J = Gˆr en Kspreadrapport  				*/
    
    QDateTime dt = QDateTime::currentDateTime();
    datum=dt.toString("yyyy-MM-dd");
    textLabelDatum->setText(datum);
    frmHuvudbok::KugarVersion();
    frmHuvudbok::GetReportDir();
    frmHuvudbok::GetTmpDir();
    frmHuvudbok::getFortetagsnamn();
}

void frmHuvudbok::slotlineEditBar_returnPressed()
{
    bar=lineEditBar->text();
    bar=bar.upper();
    lineEditBar->setText((bar));
    if (bar==""){
	QMessageBox::warning( this, "HUVBOKW",
                      "BokfˆringsÂr mÂste fyllas i! \n" );
	lineEditBar->setFocus();
    }else{
	frmHuvudbok::GetBokfPeriod();	
	lineEditFromDatum->setFocus();
    }
}

void frmHuvudbok::lineEditFromDatum_returnPressed()
{
    fromdatum=lineEditFromDatum->text();
    if (fromdatum==""){
	fromdatum=fromdate;
    }
    fromdatum=frmHuvudbok::CheckDatum(fromdatum ); 		// Kontrollera datumformat ≈≈≈≈-MM-DD
    lineEditFromDatum->setText(fromdatum);
    lineEditTomDatum->setFocus();
}

void frmHuvudbok::lineEditTomDatum_returnPressed()
{
    tomdatum=lineEditTomDatum->text();
    if(tomdatum==""){
	tomdatum=tomdate;
    }
    tomdatum=frmHuvudbok::CheckDatum(tomdatum );  		// Kontrollera datumformat ≈≈≈≈-MM-DD  
    lineEditTomDatum->setText(tomdatum);
    period=fromdatum+" -- "+tomdatum;
    pushButtonOK->setFocus();
}

void frmHuvudbok::radioButtonCSV_toggled( bool )
{
    csvflag="J";
    slotFileRemove("Huvudbok.txt");
}

void frmHuvudbok::radioButtonPrint_toggled( bool )
{
    csvflag="N";
}

void frmHuvudbok::slotpushButtonOK_clicked()
{
    frmHuvudbok::slotCreateHeader();		// D‰rifrÂn call slotGetData
    pushButtonAvbryt->setFocus();
}

void frmHuvudbok::slotGetData()
{
	const char *userp = getenv("USER");
            QString usr(userp);

	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "HBOKRPT");	// OLFIX funktion
	process->addArgument(bar);		// BokfˆringsÂr
	process->addArgument(fromdatum);
	process->addArgument(tomdatum);

	frmHuvudbok::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmHuvudbok::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
            frmHuvudbok::connect( process, SIGNAL(processExited() ),this, SLOT(slotGetDataEndOfProcess() ) );


	if (bar == "" ){
    	    QMessageBox::warning( this, "HUVBOKW",
                      "BokfˆringsÂr mÂste vara ifyllt!" );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/HUVBOK!\n");
		QMessageBox::warning( this, "HUVBOKW",
                            "Kan inte starta STYRMAN/KTORPT! \n" );
	    }
	}
}


void frmHuvudbok::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmHuvudbok::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmHuvudbok::slotGetDataEndOfProcess()
{
    int i,j,m,n;
    int ant;
    int endflag;

    QString antal;
    QString ktonr;
    QString verdatum;
    QString vertext;
    QString ktonamn;
    QString dk;
    QString belopp;
    QString vernr;
    
    QString ktotemp;
    QString verdatumtemp;
    QString vertexttemp;
    QString ktonamntemp;
    QString dktemp;
    QString belopptemp;
    QString vernrtemp;

//	Summa per verifikation    
    QString debetsum;		// Summa Debet
    QString kreditsum;		// Summa Kredit
    QString ackumulerat;		// Summa Ackumulerat
    double debet=0;
    double kredit=0;
    double acksaldo=0;
    
//	Summa per konto    
    QString ktosumdebet;
    QString ktosumkredit;
    QString ktosumackumulerat;
    double ktodelsumdebet=0;
    double ktodelsumkredit=0;
    double ktodelsumackumulerat=0;
    
//	Summa totalt
    QString totaldebet;
    QString totalkredit;
    QString totalackumulerat;
    double debettotal=0;
    double kredittotal=0;
    double acksaldototal=0;
    
    QString fil;
    QString rapportrad;
        
    if (csvflag == "J"){
	fil=tmppath+"Huvudbok.txt";
    }else{
	fil=tmppath+"Huvudbok.kud";
    }
    QFile filnamn( fil );
    ackumulerat="0.00";
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i == 0) {
	QMessageBox::critical( this, "OLFIX - HUVBOKW",
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
	    ktotemp="";	 
	    for (n=0;n<ant;n++){
		i = j;
		 j = inrad.find(QRegExp("_:"),i+2);
		 m = j - (i+2);
		 ktonr = inrad.mid(i+2,m);
		 i = j;
		 j = inrad.find(QRegExp("_:"),i+2);
		 m = j - (i+2);
		 verdatum = inrad.mid(i+2,m);
		 i = j;
		 j = inrad.find(QRegExp("_:"),i+2);
		 m = j - (i+2);
		 vernr = inrad.mid(i+2,m);		 
		 i = j;
		 j = inrad.find(QRegExp("_:"),i+2);
		 m = j - (i+2);
		 vertext = inrad.mid(i+2,m);
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
		 endflag=inrad.find(QRegExp("END:"),i+2);
//		 qDebug("i=%d, j=%d, m=%d, endflag=%d",i,j,m,endflag);
//		 qDebug("ktonr=%s, verdatum=%s, vernr=%s, vertext=%s, ktonamn=%s, dk=%s, belopp=%s",ktonr.latin1(),verdatum.latin1(),vernr.latin1(),vertext.latin1(),ktonamn.latin1(),dk.latin1(),belopp.latin1());
     		 // =========================================================
		 if (dk == "D"){
		     debet=belopp.toDouble();
		 }
		 if (dk == "K"){
		     kredit=belopp.toDouble();
		 }
		 acksaldo=debet-kredit;		 
		 debetsum.setNum(debet,'f',2);
		 kreditsum.setNum(kredit,'f',2);
		 ackumulerat.setNum(acksaldo,'f',2);
		 
		 if (csvflag =="J"){			// Skapa rapportrad fˆr Kspread
		     rapportrad=(ktonr);			 
		     rapportrad.append(",");			 
		     rapportrad.append(verdatum);			 
		     rapportrad.append(",");			 
		     rapportrad.append(vernr);			 
		     rapportrad.append(",");
		     rapportrad.append("\"");
		     rapportrad.append(vertext);
		     rapportrad.append("\"");		     
		     rapportrad.append(",");			 
		     rapportrad.append(ktonamn);						 
		     rapportrad.append(",");			 
		     rapportrad.append(debetsum);
		     rapportrad.append(",");
		     rapportrad.append(kreditsum);
		     rapportrad.append(",");			 
		     rapportrad.append(ackumulerat);
		     rapportrad.append("\n");
//		     if (ktotemp != ""){
			 stream << rapportrad;
//		     }
		 }else{		 		// Skapa raportrad fˆr Kugar
		     if (ktonr != ktotemp && ktotemp !=""){
			 ktosumdebet.setNum(ktodelsumdebet,'f',2);
			 ktosumkredit.setNum(ktodelsumkredit,'f',2);
			 ktosumackumulerat.setNum(ktodelsumackumulerat,'f',2);						 
			 rapportrad="<Delsumma level=\"3\" ";
			 rapportrad.append(" ktosumdebet=\"");
			 rapportrad.append(ktosumdebet);
			 rapportrad.append("\" ktosumkredit=\"");
			 rapportrad.append(ktosumkredit);
			 rapportrad.append("\" ktosumackumulerat=\"");
			 rapportrad.append(ktosumackumulerat);
			 rapportrad.append("\"/>\n");
			 stream << rapportrad;
			 // Blankrad
			 rapportrad="<Blankrad level=\"4\" ";
			 rapportrad.append("blank=\"");
			 rapportrad.append(" ");
			 rapportrad.append("\"/>\n");
			 stream << rapportrad;
			     
			 ktodelsumdebet=0;
			 ktodelsumkredit=0;
			 ktodelsumackumulerat=0;			     
		     }			 
		     if (ktonr != ktotemp){
			 rapportrad="<Konto level=\"1\" ";
			 rapportrad.append(" kontonr=\"");
			 rapportrad.append(ktonr);
			 rapportrad.append("\" ktonamn=\"");
			 rapportrad.append(ktonamn);
			 rapportrad.append("\"/>\n");
			 stream << rapportrad;
		     }
//			 qDebug("n=%d, rapportrad=%s",n,rapportrad.latin1());
		     rapportrad="<Row level=\"2\" ";
		     rapportrad.append(" verdatum=\"");
		     rapportrad.append(verdatum);
		     rapportrad.append("\" vernr=\"");
		     vernr=vernr+" ";
		     rapportrad.append(vernr);
		     rapportrad.append("\" vertext=\"");
		     vertext=" "+vertext;
		     rapportrad.append(vertext);			 
		     rapportrad.append("\" debet=\"");
		     rapportrad.append(debetsum);
		     rapportrad.append("\" kredit=\"");
		     rapportrad.append(kreditsum);
		     rapportrad.append("\" ack=\"");
		     rapportrad.append(ackumulerat);
		     rapportrad.append("\"/>\n");
//			 qDebug("n=%d, rapportrad=%s",n,rapportrad.latin1());
		     stream << rapportrad;			 
		 }
		 ktotemp=ktonr;
		 ktonamntemp=ktonamn;
		 verdatumtemp=verdatum;
		 vertexttemp=vertext;
		 vernr=vernrtemp;
		 debet=0;
		 kredit=0;
		 acksaldo=0;	         
		 debetsum="";
		 kreditsum="";
		 ackumulerat="";
		 if (dk == "D"){
		     ktodelsumdebet=ktodelsumdebet+belopp.toDouble();
		     debettotal=debettotal+belopp.toDouble();
		 }
		 if (dk == "K"){
		     ktodelsumkredit=ktodelsumkredit+belopp.toDouble();
		     kredittotal=kredittotal+belopp.toDouble();
		 }
		 ktodelsumackumulerat=ktodelsumdebet-ktodelsumkredit;
		 acksaldototal=debettotal-kredittotal;
// =====================================================================
	     }
	} 
	if (csvflag != "J"){
	    // ========================================
	    // Totaler fˆr sista kontot
	    ktosumdebet.setNum(ktodelsumdebet,'f',2);
	    ktosumkredit.setNum(ktodelsumkredit,'f',2);
	    ktosumackumulerat.setNum(ktodelsumackumulerat,'f',2);		
	    rapportrad="<Delsumma level=\"3\" ";
	    rapportrad.append(" ktosumdebet=\"");
	    rapportrad.append(ktosumdebet);
	    rapportrad.append("\" ktosumkredit=\"");
	    rapportrad.append(ktosumkredit);
	    rapportrad.append("\" ktosumackumulerat=\"");
	    rapportrad.append(ktosumackumulerat);
	    rapportrad.append("\"/>\n");
	    stream << rapportrad;
	    // Blankrad
	    rapportrad="<Blankrad level=\"4\" ";
	    rapportrad.append("blank=\"");
	    rapportrad.append(" ");
	    rapportrad.append("\"/>\n");
	    stream << rapportrad;
	    // ===========================================
	    
	     totaldebet.setNum(debettotal,'f',2);
	     totalkredit.setNum(kredittotal,'f',2);
	     totalackumulerat.setNum(acksaldototal,'f',2);			
	    
  	     rapportrad="<Totalsumma level=\"5\" ";
	     rapportrad.append(" totaldebet=\"");
	     rapportrad.append(totaldebet);
	     rapportrad.append("\" totalkredit=\"");
	     rapportrad.append(totalkredit);
	     rapportrad.append("\" totalackumulerat=\"");
	     rapportrad.append(totalackumulerat);
	     rapportrad.append("\"/>\n");
	     stream << rapportrad;
	     rapportrad="</KugarData>";
	     stream << rapportrad;
	 }
    }
    filnamn.close();
    QMessageBox::information( this, "HUVBOKW","Rapport skapad!\n");
    
    if (csvflag == "J"){
	frmHuvudbok::slotRunPrinting("Huvudbok.txt","" );   	
    }else{
	frmHuvudbok::slotRunPrinting("Huvudbok.kud","Huvudbok.kut" ); 
    }    
     errorrad="";
     inrad="";
}

void frmHuvudbok::slotCreateHeader()
{
    int i;
    int antrad=65;
    QString rad[antrad];
    QString rapportrad;

    QFile filnamn(tmppath+"Huvudbok.kud");
    
    QTextStream stream(&filnamn);

    slotFileRemove("Huvudbok.kud");	// radera gammal fil. ƒndra till .kud

    rad[1]="<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n";
    rad[2]="<!DOCTYPE KugarData [\n";
    rad[3]="   <!ELEMENT KugarData (Sidhuvud* )>\n";
    rad[4]="   <!ATTLIST KugarData\n";
    rad[5]="      Template CDATA #REQUIRED>\n\n";
    rad[6]="   <!ELEMENT Sidhuvud EMPTY>\n";
    rad[7]="   <!ATTLIST Sidhuvud\n";
    rad[8]="      level CDATA #REQUIRED\n";
    rad[9]="      ftgnamn CDATA #REQUIRED\n";
    rad[10]="      period CDATA #REQUIRED\n";
    rad[11]="      datum CDATA #REQUIRED\n";
    rad[12]=">\n";
    rad[13]="   <!ELEMENT KugarData (Konto* )>\n";
    rad[14]="   <!ATTLIST KugarData\n";
    rad[15]="      Template CDATA #REQUIRED>\n\n";
    rad[16]="   <!ELEMENT Konto EMPTY>\n";
    rad[17]="   <!ATTLIST Konto\n";
    rad[18]="      level CDATA #REQUIRED\n";
    rad[19]="      kontonr CDATA #REQUIRED\n";
    rad[20]="      ktonamn CDATA #REQUIRED\n";    
    rad[21]=">\n";
    rad[22]="   <!ELEMENT KugarData (Rad* )>\n";
    rad[23]="   <!ATTLIST KugarData\n";
    rad[24]="      Template CDATA #REQUIRED>\n\n";
    rad[25]="   <!ELEMENT Rad EMPTY>\n";
    rad[26]="   <!ATTLIST Rad\n";
    rad[27]="      level CDATA #REQUIRED\n";
    rad[28]="      verdatum CDATA #REQUIRED\n";
    rad[29]="      vernr CDATA #REQUIRED\n";
    rad[30]="      vertext CDATA #REQUIRED\n";
    rad[31]="      debet CDATA #REQUIRED\n";
    rad[32]="      kredit CDATA #REQUIRED\n";
    rad[33]="      ack CDATA #REQUIRED\n";
    rad[34]=">\n";
    rad[35]="   <!ELEMENT KugarData (Delsumma* )>\n";
    rad[36]="   <!ATTLIST KugarData\n";
    rad[37]="      Template CDATA #REQUIRED>\n\n";
    rad[38]="   <!ELEMENT Delsumma EMPTY>\n";
    rad[39]="   <!ATTLIST Delsumma\n";
    rad[40]="      level CDATA #REQUIRED\n";
    rad[41]="      ktosumdebet CDATA #REQUIRED\n";
    rad[42]="      ktosumkredit CDATA #REQUIRED\n";
    rad[43]="      delsumack CDATA #REQUIRED\n"; 
    rad[44]=">\n"; 
    rad[45]="   <!ELEMENT KugarData (Blankrad* )>\n";
    rad[46]="   <!ATTLIST KugarData\n";
    rad[47]="      Template CDATA #REQUIRED>\n\n";
    rad[48]="   <!ELEMENT Blankrad EMPTY>\n";
    rad[49]="   <!ATTLIST Blankrad\n";
    rad[50]="      level CDATA #REQUIRED\n";
    rad[51]="      blank CDATA #REQUIRED\n";
    rad[52]=">\n";           
    rad[53]="   <!ELEMENT KugarData (Totalsumma* )>\n";
    rad[54]="   <!ATTLIST KugarData\n";
    rad[55]="      Template CDATA #REQUIRED>\n\n";
    rad[56]="   <!ELEMENT Totalsumma EMPTY>\n";
    rad[57]="   <!ATTLIST Totalsumma\n";
    rad[58]="      level CDATA #REQUIRED\n";
    rad[59]="      totaldebet CDATA #REQUIRED\n";
    rad[60]="      totalkredit CDATA #REQUIRED\n";
    rad[61]="      totalack CDATA #REQUIRED\n";    
    rad[62]=">\n";            
    rad[63]="]>\n\n";
    rad[64]="<KugarData Template=\"";
    rad[64].append(reportpath);
    rad[64].append("Huvudbok.kut\">\n");	// ange r‰tt template, absolut path
    
    rapportrad=rad[1];
    for (i=2;i<(antrad);i++){
	rapportrad.append(rad[i]);
    }
    
//    qDebug("i=%d,antrad=%d",i,antrad);
//    qDebug("slotCreateHeader::rapportrad_1 = \n%s",rapportrad.latin1());
    
    rapportrad.append("<Rowhead level=\"0");
    rapportrad.append("\" ftgnamn=\"");
    rapportrad.append(ftgnamn); 
    rapportrad.append("\" period=\"");
    rapportrad.append(period);    
    rapportrad.append("\" datum=\"");
    rapportrad.append(datum);
    rapportrad.append("\"/>\n");    

//   qDebug("slotCreateHeader::rapportrad_2 = \n%s",rapportrad.latin1());
    
    filnamn.open( IO_WriteOnly | IO_Append );
    stream << rapportrad;
    frmHuvudbok::slotGetData();
}

void frmHuvudbok::slotFileRemove(QString filnamn)
{
//  Ta bort tempor‰rfilen /tmp/Huvudbok.kud eller filen /tmp/Huvudbok.txt
    bool status;
    QDir d = QDir::root();                   // "/"
/*    if ( !d.cd("tmp") ) {                       // "/tmp"
        qWarning( "Cannot find the \"/tmp\" directory" );
    } */
    filnamn=tmppath+filnamn;
//    status=d.remove(filnamn,FALSE);
    status=remove(filnamn);
//    qDebug("filnamn=%s, status=%d",filnamn.latin1(),status);
}

void frmHuvudbok::KugarVersion()
{
//  H‰mta aktuell version av kugar
//  Anrop av kugar skiljer sig mellan version 1.2.1 och version 1.2.92 ->
    bool status;
    int i = -1;
    
    QString command;
    QString filename;

    command="kugar -v >"+tmppath+"kugarversion.txt";
    system(command);
    filename=tmppath+"kugarversion.txt";
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
    frmHuvudbok::slotFileRemove("kugarversion.txt");
}

void frmHuvudbok::GetReportDir()
{
    QString hemkatalog;
    QString olfixrcfile;	// filen $HOME/.olfixrc

    bool status;
    int i = -1;
    //	H‰mta sˆkv‰gen till kugar template. Default /usr/local/olfix/report
    //	H‰mtas frÂn .olfixrc
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
}

void frmHuvudbok::GetTmpDir()
{
    QString hemkatalog;
    QString olfixrcfile;	// filen $HOME/.olfixrc

    bool status;
    int i = -1;
    //	H‰mta sˆkv‰gen till kugar template. Default /usr/local/olfix/report
    //	H‰mtas frÂn .olfixrc
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

void frmHuvudbok::getFortetagsnamn()
{
	const char *userp = getenv("USER");
            QString usr(userp);
	errorrad="";
	inrad="";
	
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "FTGDSP");	// OLFIX funktion
	process->addArgument("FNAMN");	// Fˆretagsnamn

	frmHuvudbok::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmHuvudbok::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
            frmHuvudbok::connect( process, SIGNAL(processExited() ),this, SLOT(slotFtgnamnEndOfProcess() ) );


	if ( !process->start() ) {
		QMessageBox::warning( this, "HUVBOKW",
                            "Kan inte starta STYRMAN/FTGDSP! \n" );
	}
}

void frmHuvudbok::slotFtgnamnEndOfProcess()
{
    int i,j,m;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i == 0) {
	QMessageBox::critical( this, "OLFIX - HUVBOKW",
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
}


void frmHuvudbok::GetBokfPeriod()
{
	const char *userp = getenv("USER");
            QString usr(userp);
	errorrad="";
	inrad="";
	
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "VERHDSP");	// OLFIX funktion
	process->addArgument(bar);		// BokfˆringsÂr

	frmHuvudbok::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmHuvudbok::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
            frmHuvudbok::connect( process, SIGNAL(processExited() ),this, SLOT(slotGetBokfPeriodEndOfProcess() ) );


	if ( !process->start() ) {
		QMessageBox::warning( this, "HUVBOKW",
                            "Kan inte starta STYRMAN/VERHDSP! \n" );
	}
}

void frmHuvudbok::slotGetBokfPeriodEndOfProcess()
{
    QString mindate;
    QString maxdate;
    int i,j,m;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i == 0) {
	QMessageBox::critical( this, "OLFIX - HUVBOKW",
		"ERROR!\n"+errorrad
		);
	errorrad="";
    }else{	
	i = -1;
	i = inrad.find( QRegExp("OK:"), 0 );
	if (i != -1) {
	    j =  inrad.find( QRegExp("01:"), 0 );
	    m=10;
	    mindate = inrad.mid(j+3,m);
	    j =  inrad.find( QRegExp("02:"), 0 );
	    m=10;
	    maxdate = inrad.mid(j+3,m);	    	    
	}
    }
    fromdate=mindate;
    tomdate=maxdate;
}

QString frmHuvudbok::CheckDatum( QString datumet )
{
    /*      Kontrollera och formatera datum enligt 20≈≈-MM-DD */
    int i;
    int j,k;
    QString tempdatum;
    QString millenium;
    
    i = datumet.length();
    k = datumet.find( QRegExp("-"), 0 );
    j = datumet.find( QRegExp("-"), k+1 );
    millenium=datum.mid(0,2);
        
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
        return tempdatum;
}

void frmHuvudbok::slotRunPrinting(QString rptfile,QString rpttemplate )
{
	inrad="";
	errorrad="";

	process = new QProcess();
	process->addArgument("./PRTAPI" );		// OLFIX program
	process->addArgument(csvflag);
	process->addArgument(rptfile);
	process->addArgument(rpttemplate);
//	qDebug("csvflag=%s, rptfile=%s, rpttemplate=%s",csvflag.latin1(),rptfile.latin1(),rpttemplate.latin1());
	frmHuvudbok::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnPrtStderr() ) );
	frmHuvudbok::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfPrtProcess() ) );

	if ( !process->start() ) {
	    // error handling
	    QMessageBox::warning( this, "OLFIX","Kan inte starta PRTAPI!\n" );
	}
    }

void frmHuvudbok::slotDataOnPrtStderr()
{
   while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmHuvudbok::slotEndOfPrtProcess()
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
