/****************************************************************/
/**		DAGBOKW					*/
/**		Ver 0.1                                                                                    */
/**		Created    2004-04-10				*/
/**		Modified 					*/ 
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
    
void frmDagbok::init()
{
    csvflag="N";		/*  Ska det vara en kommaseparerad rapport fˆr Kspread. N=Nej 	*/
			/*  N = Gˆr en Kugarrapport 					*/
                                    /*  J = Gˆr en Kspreadrapport  				*/
    
    QDateTime dt = QDateTime::currentDateTime();
    datum=dt.toString("yyyy-MM-dd");
    textLabelDatum->setText(datum);
    frmDagbok::KugarVersion();
    frmDagbok::GetReportDir();
    frmDagbok::GetTmpDir();
    frmDagbok::getFortetagsnamn();
}

void frmDagbok::slotlineEditBar_returnPressed()
{
    bar=lineEditBar->text();
    bar=bar.upper();
    lineEditBar->setText((bar));
    if (bar==""){
	QMessageBox::warning( this, "DAGBOKW",
                      "BokfˆringsÂr mÂste fyllas i! \n" );
	lineEditBar->setFocus();
    }else{
	frmDagbok::GetBokfPeriod();	
	lineEditFromDatum->setFocus();
    }
}

void frmDagbok::lineEditFromDatum_returnPressed()
{
    fromdatum=lineEditFromDatum->text();
    if (fromdatum==""){
	fromdatum=fromdate;
    }
    fromdatum=frmDagbok::CheckDatum(fromdatum ); 		// Kontrollera datumformat ≈≈≈≈-MM-DD
    lineEditFromDatum->setText(fromdatum);
    lineEditTomDatum->setFocus();
}

void frmDagbok::lineEditTomDatum_returnPressed()
{
    tomdatum=lineEditTomDatum->text();
    if(tomdatum==""){
	tomdatum=tomdate;
    }
    tomdatum=frmDagbok::CheckDatum(tomdatum );  		// Kontrollera datumformat ≈≈≈≈-MM-DD  
    lineEditTomDatum->setText(tomdatum);
    period=fromdatum+" -- "+tomdatum;
    pushButtonOK->setFocus();
}

void frmDagbok::radioButtonCSV_toggled( bool )
{
    csvflag="J";
    slotFileRemove("Dagbok.txt");
}

void frmDagbok::radioButtonPrint_toggled( bool )
{
    csvflag="N";
}

void frmDagbok::slotpushButtonOK_clicked()
{
    frmDagbok::slotCreateHeader();		// D‰rifrÂn call slotGetData
    pushButtonAvbryt->setFocus();
}

void frmDagbok::slotGetData()
{
	const char *userp = getenv("USER");
            QString usr(userp);

	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "DBOKRPT");	// OLFIX funktion
	process->addArgument(bar);		// BokfˆringsÂr
	process->addArgument(fromdatum);
	process->addArgument(tomdatum);

	frmDagbok::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmDagbok::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
            frmDagbok::connect( process, SIGNAL(processExited() ),this, SLOT(slotGetDataEndOfProcess() ) );


	if (bar == "" ){
    	    QMessageBox::warning( this, "DAGBOKW",
                      "BokfˆringsÂr mÂste vara ifyllt!" );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		QMessageBox::warning( this, "DAGBOKW",
                            "Kan inte starta STYRMAN/KTORPT! \n" );
	    }
	}
}


void frmDagbok::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmDagbok::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmDagbok::slotGetDataEndOfProcess()
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
	fil=tmppath+"Dagbok.txt";
    }else{
	fil=tmppath+"Dagbok.kud";
    }
    QFile filnamn( fil );
    ackumulerat="0.00";
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i == 0) {
	QMessageBox::critical( this, "OLFIX - DAGBOKW",
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
		 verdatum = inrad.mid(i+2,m);
//		 ktonr = inrad.mid(i+2,m);
		 i = j;
		 j = inrad.find(QRegExp("_:"),i+2);
		 m = j - (i+2);
		 vernr = inrad.mid(i+2,m);	
//		 verdatum = inrad.mid(i+2,m);
		 i = j;
		 j = inrad.find(QRegExp("_:"),i+2);
		 m = j - (i+2);
		 vertext = inrad.mid(i+2,m);
//		 vernr = inrad.mid(i+2,m);		 
		 i = j;
		 j = inrad.find(QRegExp("_:"),i+2);
		 m = j - (i+2);
		 ktonr = inrad.mid(i+2,m);
//		 vertext = inrad.mid(i+2,m);
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
		     rapportrad=(verdatum);			 
		     rapportrad.append(",");			 
		     rapportrad.append(vernr);			 
		     rapportrad.append(",");
		     rapportrad.append("\"");
		     rapportrad.append(vertext);
		     rapportrad.append("\"");		     
		     rapportrad.append(",");
		     rapportrad.append(ktonr);			 
		     rapportrad.append(",");			 		     
		     rapportrad.append(ktonamn);						 
		     rapportrad.append(",");			 
		     rapportrad.append(debetsum);
		     rapportrad.append(",");
		     rapportrad.append(kreditsum);
		     rapportrad.append("\n");
		     stream << rapportrad;
		 }else{		 		// Skapa raportrad fˆr Kugar
		     if (vernr != vernrtemp){
			 rapportrad="<Verifikation level=\"1\" ";
			 rapportrad.append(" vernr=\"");
			 rapportrad.append(vernr);
			 rapportrad.append("\" verdatum=\"");
			 rapportrad.append(verdatum);
			 rapportrad.append("\" vertext=\"");
			 rapportrad.append(vertext);			 
			 rapportrad.append("\"/>\n");
			 stream << rapportrad;
		     }
//			 qDebug("n=%d, rapportrad=%s",n,rapportrad.latin1());
		     rapportrad="<Row level=\"2\" ";
		     rapportrad.append(" kontonr=\"");
		     rapportrad.append(ktonr);
		     rapportrad.append("\" ktonamn=\"");
		     rapportrad.append(ktonamn);
		     rapportrad.append("\" debet=\"");
		     rapportrad.append(debetsum);
		     rapportrad.append("\" kredit=\"");
		     rapportrad.append(kreditsum);
		     rapportrad.append("\"/>\n");
//			 qDebug("n=%d, rapportrad=%s",n,rapportrad.latin1());
		     stream << rapportrad;			 
		 }
		 ktotemp=ktonr;
		 ktonamntemp=ktonamn;
		 verdatumtemp=verdatum;
		 vernrtemp=vernr;
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
    QMessageBox::information( this, "DAGBOKW","Rapport skapad!\n");
    
    if (csvflag == "J"){
	frmDagbok::slotRunPrinting("Dagbok.txt","" );   	
    }else{
	frmDagbok::slotRunPrinting("Dagbok.kud","Dagbok.kut" ); 
    }    
     errorrad="";
     inrad="";
}

void frmDagbok::slotCreateHeader()
{
    int i;
    int antrad=54;
    QString rad[antrad];
    QString rapportrad;

    QFile filnamn(tmppath+"Dagbok.kud");
    
    QTextStream stream(&filnamn);

    slotFileRemove("Dagbok.kud");	// radera gammal fil. ƒndra till .kud

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
    rad[13]="   <!ELEMENT KugarData (Verifikation* )>\n";
    rad[14]="   <!ATTLIST KugarData\n";
    rad[15]="      Template CDATA #REQUIRED>\n\n";
    rad[16]="   <!ELEMENT Verifikation EMPTY>\n";
    rad[17]="   <!ATTLIST verifikation\n";
    rad[18]="      level CDATA #REQUIRED\n";
    rad[19]="      vernrnr CDATA #REQUIRED\n";
    rad[20]="      verdatum CDATA #REQUIRED\n";    
    rad[21]="      vertext CDATA #REQUIRED\n";
    rad[22]=">\n";
    rad[23]="   <!ELEMENT KugarData (Rad* )>\n";
    rad[24]="   <!ATTLIST KugarData\n";
    rad[25]="      Template CDATA #REQUIRED>\n\n";
    rad[26]="   <!ELEMENT Rad EMPTY>\n";
    rad[27]="   <!ATTLIST Rad\n";
    rad[28]="      level CDATA #REQUIRED\n";
    rad[29]="      kontonr CDATA #REQUIRED\n";
    rad[30]="      ktonamn CDATA #REQUIRED\n";
    rad[31]="      debet CDATA #REQUIRED\n";
    rad[32]="      kredit CDATA #REQUIRED\n";
    rad[33]=">\n";
    rad[34]="   <!ELEMENT KugarData (Blankrad* )>\n";
    rad[35]="   <!ATTLIST KugarData\n";
    rad[36]="      Template CDATA #REQUIRED>\n\n";
    rad[37]="   <!ELEMENT Blankrad EMPTY>\n";
    rad[38]="   <!ATTLIST Blankrad\n";
    rad[39]="      level CDATA #REQUIRED\n";
    rad[40]="      blank CDATA #REQUIRED\n";
    rad[41]=">\n";           
    rad[42]="   <!ELEMENT KugarData (Totalsumma* )>\n";
    rad[43]="   <!ATTLIST KugarData\n";
    rad[44]="      Template CDATA #REQUIRED>\n\n";
    rad[45]="   <!ELEMENT Totalsumma EMPTY>\n";
    rad[46]="   <!ATTLIST Totalsumma\n";
    rad[47]="      level CDATA #REQUIRED\n";
    rad[48]="      totaldebet CDATA #REQUIRED\n";
    rad[49]="      totalkredit CDATA #REQUIRED\n";
    rad[50]="      totalack CDATA #REQUIRED\n";    
    rad[51]=">\n";            
    rad[52]="]>\n\n";
    rad[53]="<KugarData Template=\"";
    rad[53].append(reportpath);
    rad[53].append("Dagbok.kut\">\n");	// ange r‰tt template, absolut path
    
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
    
    filnamn.open( IO_WriteOnly | IO_Append );
    stream << rapportrad;
    frmDagbok::slotGetData();
}

void frmDagbok::slotFileRemove(QString filnamn)
{
//  Ta bort tempor‰rfilen /tmp/Dagbok.kud eller filen /tmp/Dagbok.txt
    bool status;
    QDir d = QDir::root();                   // "/"
    filnamn=tmppath+filnamn;
    status=remove(filnamn);
}

void frmDagbok::KugarVersion()
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
    frmDagbok::slotFileRemove("kugarversion.txt");
}

void frmDagbok::GetReportDir()
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

void frmDagbok::GetTmpDir()
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

void frmDagbok::getFortetagsnamn()
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

	frmDagbok::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmDagbok::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
            frmDagbok::connect( process, SIGNAL(processExited() ),this, SLOT(slotFtgnamnEndOfProcess() ) );


	if ( !process->start() ) {
		QMessageBox::warning( this, "DAGBOKW",
                            "Kan inte starta STYRMAN/FTGDSP! \n" );
	}
}

void frmDagbok::slotFtgnamnEndOfProcess()
{
    int i,j,m;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i == 0) {
	QMessageBox::critical( this, "OLFIX - DAGBOKW",
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


void frmDagbok::GetBokfPeriod()
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

	frmDagbok::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmDagbok::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
            frmDagbok::connect( process, SIGNAL(processExited() ),this, SLOT(slotGetBokfPeriodEndOfProcess() ) );


	if ( !process->start() ) {
		QMessageBox::warning( this, "DAGBOKW",
                            "Kan inte starta STYRMAN/VERHDSP! \n" );
	}
}

void frmDagbok::slotGetBokfPeriodEndOfProcess()
{
    QString mindate;
    QString maxdate;
    int i,j,m;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i == 0) {
	QMessageBox::critical( this, "OLFIX - DAGBOKW",
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

QString frmDagbok::CheckDatum( QString datumet )
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

void frmDagbok::slotRunPrinting(QString rptfile,QString rpttemplate )
{
	inrad="";
	errorrad="";

	process = new QProcess();
	process->addArgument("./PRTAPI" );		// OLFIX program
	process->addArgument(csvflag);
	process->addArgument(rptfile);
	process->addArgument(rpttemplate);
//	qDebug("csvflag=%s, rptfile=%s, rpttemplate=%s",csvflag.latin1(),rptfile.latin1(),rpttemplate.latin1());
	frmDagbok::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnPrtStderr() ) );
	frmDagbok::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfPrtProcess() ) );

	if ( !process->start() ) {
	    // error handling
	    QMessageBox::warning( this, "OLFIX","Kan inte starta PRTAPI!\n" );
	}
    }

void frmDagbok::slotDataOnPrtStderr()
{
   while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmDagbok::slotEndOfPrtProcess()
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
