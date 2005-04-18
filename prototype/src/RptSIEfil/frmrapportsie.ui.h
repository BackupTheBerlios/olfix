/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
/***************************************************************************
                          RPTSIEW  -  description
                             -------------------
		     version 0.3
    begin                   : Tors 18 nov   2004
    modified	: Lör  16 april 2005
    copyright             : (C) 2004 by Jan Pihlgren
    email                   : jan@pihlgren.se
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
#include <qregexp.h>
#include <qprocess.h>
#include <qdatetime.h>
#include <qfile.h>
#include <qstring.h>
#include <stdlib.h>
#define MAXSTRING 5000

    QString rapporttyp;
    QProcess* process;
    QString inrad;
    QString inrad2;
    QString errorrad;
    QString hjelpfil;
    
    
/*	Data från företagsregistret, tabell  FTGDATA  		*/        
    QString ftgnr;
    QString fnamn;
    QString postadr;
    QString postnr;
    QString ort;
    QString tfnnr;   
    QString snikd;
    
/*	Data från företagsregistret, tabell  BOKFAR  		*/
    QString arid;		// Bokföringsårests ID
    QString benamn;	// Bokföringsårets benämning  ÅÅÅÅMMDD-ÅÅÅÅMMDD 
    QString arstart;	// Bokföringsårets början
    QString arslut;		// Bokföringsårests slut
    QString arlast;		// Låst bokföringsår, default N
    QString beskattar;	// Beskattningsår
    QString senverdat;	// Senaste verifikationsdatum
    QString vernr;		// Nästa verifikationsnummer, default 1
    QString ktoplan;	// Kontoplan
 
    
/*	Data från $HOME/.olfixrc, från vilken databas hämtas information	*/
    QString databas;	// Från vilken databas data hämtas
 
    QString sienamn="SIEtyp";
    QString reportfile;
    QString tmppath;
    QString datum;
    
void frmRapportSIE::init()
{
    QDateTime dt = QDateTime::currentDateTime();
    datum=dt.toString("yyyy-MM-dd");
    datum.remove("-");
    radioButton4->setChecked(TRUE);
    rapporttyp="4";
    frmRapportSIE::GetTmpDir();
    reportfile=tmppath+sienamn+rapporttyp+".txt";
//    qDebug("reportfile=%s",reportfile.latin1());
    lineEditBar->setFocus();
}

void frmRapportSIE::radioButtonSIE_Typ1_pressed()
{
    radioButton1->setChecked(TRUE);
    radioButton2->setChecked(FALSE);    
    radioButton3->setChecked(FALSE);
    radioButton4->setChecked(FALSE);
    rapporttyp="1";
    reportfile=tmppath+sienamn+rapporttyp+".txt";
}

void frmRapportSIE::radioButtonSIE_Typ2_pressed()
{
    radioButton1->setChecked(FALSE);
    radioButton2->setChecked(TRUE);    
    radioButton3->setChecked(FALSE);
    radioButton4->setChecked(FALSE);
    rapporttyp="2";
    reportfile=tmppath+sienamn+rapporttyp+".txt";
}

void frmRapportSIE::radioButtonSIE_Typ3_pressed()
{
    radioButton1->setChecked(FALSE);
    radioButton2->setChecked(FALSE);    
    radioButton3->setChecked(TRUE);
    radioButton4->setChecked(FALSE);
    rapporttyp="3";    
    reportfile=tmppath+sienamn+rapporttyp+".txt";
}

void frmRapportSIE::radioButtonSIE_Typ4_pressed()
{
    radioButton1->setChecked(FALSE);    
    radioButton2->setChecked(FALSE);    
    radioButton3->setChecked(FALSE);
    radioButton4->setChecked(TRUE);
    rapporttyp="4";    
    reportfile=tmppath+sienamn+rapporttyp+".txt";
}

void frmRapportSIE::GetInfo()
{
    GetForetagsdata("FNAMN");
}

void frmRapportSIE::CreateSIE_file()
{
    int val;
    bool ok;
    val = rapporttyp.toInt( &ok , 10);
//	 qDebug("rapporttyp=%s val=%d",rapporttyp.latin1(),val);
 switch (val){
 case 1:
       	QMessageBox::warning( this, "",
                "SIE-exportfil typ 1 är ännu inte implementerad\n" );
	break;
 case 2:
           	QMessageBox::warning( this, "",
                "SIE-exportfil typ 2 är ännu inte implementerad\n" );
	break;
 case 3:
           	QMessageBox::warning( this, "",
                "SIE-exportfil typ 3 är ännu inte implementerad\n" );
	break;
 case 4:
  	QMessageBox::warning( this, "",
                "Du har valt att skapa en SIE-exportfil typ 4 \n" );
	break;
 default:
	 QMessageBox::warning( this, "",
                "Du har valt fel!! \n" );
	break;
 }
 
 
    const char *userp = getenv("USER");
    QString usr(userp);

    int i;
    int antrad=55;
    QString rad[antrad];
    QString rapportrad;

    QString flagga="0";
    QString pc8="PC8";
    QString programnamn="\"OLFIX\" ";
    QString versionsnr="0.15";
    QString lag="BFL";
//    QString file="/tmp/SIEtyp4.txt";
    QString file;
    file=reportfile;
    QFile filnamn(file);
    slotFileRemove(file);	// radera gammal fil i /tmp
    QTextStream stream(&filnamn);
    
    rad[0]="#FLAGGA "+flagga+"\n";
    rad[1]="#FORMAT "+pc8+"\n";    
    rad[2]="#SIETYP "+rapporttyp+"\n";
    rad[3]="#PROGRAM "+ programnamn+" "+versionsnr+"\n";
    rad[4]="#GEN "+datum+" "+usr+"\n";    
    rad[5]="#FNAMN \"";
    rad[5].append(fnamn);
    rad[5].remove("\n");
    rad[5].append("\"\n");
    rad[6]="#FNR "+databas+"\n";    
    rad[7]="#ORGNR "+ftgnr;    
    rad[7].remove("\n");
    rad[7].append("\n");   
    rad[8]="#BKOD "+snikd;
    rad[8].remove("\n");
    rad[8].append("\n");    
    rad[9]="#ADRESS \""+fnamn+ "\" "+"\"" +postadr+"\" "+"\""+postnr+"\" "+"\""+ ort + "\" "+ "\"" + tfnnr;
    rad[9].remove("\n");
    rad[9].append("\"\n");
    rad[10]="#RAR "+LineEditStartdatum->text()+" "+LineEditSlutdatum->text()+"\n";        
    rad[11]="#TAXAR "+beskattar+" "+lag+"\n";
// ------------------------------------------------------------------    
    rad[12]="#KPTYP "+ktoplan+"\n";
    
    rapportrad=rad[0];
//    for (i=2;i<(antrad);i++){
    for (i=1;i<=(12);i++){
	rapportrad.append(rad[i]);
    }
    filnamn.open( IO_WriteOnly | IO_Append );
    stream << rapportrad;
    filnamn.close();
    /* Hämta kontoplanen */
    reportfile=file;
    frmRapportSIE::GetKontoplan();
}

void frmRapportSIE::lineEditBar_returned()
{
    arid = lineEditBar->text();
    arid = arid.upper();
    lineEditBar->setText(arid);
//    pushButton_OK->setFocus();
    pushButtonGetData->setFocus();
}

void frmRapportSIE::GetForetagsdata(QString posttyp)
{
	const char *userp = getenv("USER");
            QString usr(userp);

	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "FTGDSP");	// OLFIX funktion
	process->addArgument(posttyp);

	frmRapportSIE::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmRapportSIE::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmRapportSIE::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );

	 if ( !process->start() ) {
		// error handling
		QMessageBox::warning( this, "RPTSIEW",
                            "Kan inte starta STYRMAN/FTGDSP! \n" );
	    }
}

void frmRapportSIE::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmRapportSIE::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmRapportSIE::slotEndOfProcess()
{
    int h,i,j,k,m;
   QString posttyp;
//    qDebug("frmRapportSIE-inrad=%s",inrad.latin1());
    h= -1;
    h = errorrad.find( QRegExp("Error:"), 0 );
    if (h != -1) {
	QMessageBox::critical( this, "RPTSIEW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	h = -1;
     }
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = k - j;
    posttyp = inrad.mid(j+2,m-2);

//    qDebug("posttyp=%s",posttyp.latin1());
    i = -1;
    i = posttyp.find( QRegExp("FNAMN"), 0 );
    if (i != -1){
	slotGetFNAMN();
    }
    i = -1;
    i = posttyp.find( QRegExp("ADR1"), 0 );
    if (i != -1){
	slotGetADR1();
    }
    i = -1;
    i = posttyp.find( QRegExp("ADR2"), 0 );
    if (i != -1){
	slotGetADR2();
    }
    i = -1;
    i = posttyp.find( QRegExp("ADR3"), 0 );
    if (i != -1){
	slotGetADR3();
    }
    i = -1;
    i = posttyp.find( QRegExp("FTGNR"), 0 );
    if (i != -1){
	slotGetFTGNR();
    }
    i = -1;
    i = posttyp.find( QRegExp("TFN1"), 0 );
    if (i != -1){
	slotGetTFN1();
    }
    i = -1;
    i = posttyp.find( QRegExp("SNIKD"), 0 );
    if (i != -1){
	slotGetSNIKKOD();
    }   
}

void frmRapportSIE::slotGetFNAMN()
{
   int i,j,k,m;

    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = inrad.length();
    fnamn = inrad.mid(k+2,m-2);
    LineEditFtgNamn->setText(fnamn);
    inrad="";
    GetForetagsdata("ADR1");
}

void frmRapportSIE::slotGetADR1()
{
    //	Postadressen
   int i,j,k,m;

    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = inrad.length();
    postadr = inrad.mid(k+2,m-2);
    LineEditPostAdress->setText(postadr);
    inrad="";
    GetForetagsdata("ADR2");
}

void frmRapportSIE::slotGetADR2()
{
   //	Postnummer
   int i,j,k,m;
  
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = inrad.length();;
    postnr = inrad.mid(k+2,m-2);
    LineEditPostnr1->setText(postnr);    
    inrad="";
    GetForetagsdata("ADR3");
}

void frmRapportSIE::slotGetADR3()
{
    //	Ort
   int i,j,k,m;
 
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = inrad.length();
    ort = inrad.mid(k+2,m-2);
    LineEditPostOrt->setText(ort);
    inrad="";
    GetForetagsdata("FTGNR");
}

void frmRapportSIE::slotGetFTGNR()
{
   int i,j,k,m;

    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = inrad.length();
    ftgnr = inrad.mid(k+2,m-2);
    LineEditFtgNr->setText(ftgnr);
    inrad="";
    GetForetagsdata("TFN1");
}

void frmRapportSIE::slotGetTFN1()
{
   int i,j,k,m;
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = inrad.length();
    tfnnr = inrad.mid(k+2,m-2);
    LineEditTfnnr->setText(tfnnr);
    inrad="";
    GetForetagsdata("SNIKD");
}

void frmRapportSIE::slotGetSNIKKOD()
{
   int i,j,k,m;
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = inrad.length();
    snikd = inrad.mid(k+2,m-2);
    LineEditSnikd->setText(snikd);
    inrad="";
    slotGetBar();
}


void frmRapportSIE::slotGetBar()
{
	const char *userp = getenv("USER");
            QString usr(userp);
	inrad="";
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "BARDSP");	// OLFIX funktion
	process->addArgument(arid);
	
//	qDebug("slotGetBar::arid=%s",arid.latin1());
	
	frmRapportSIE::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmRapportSIE::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
            frmRapportSIE::connect( process, SIGNAL(processExited() ),this, SLOT(slotGetBarEndOfProcess() ) );

	if (arid == "" ){
    	    QMessageBox::warning( this, "RPTSIEW",
                      "Bokföringsår måste vara ifyllt!" );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		QMessageBox::warning( this, "RPTSIEW",
                            "Kan inte starta STYRMAN/BARDSP! \n" );
	    }
	}
}

void frmRapportSIE::slotGetBarEndOfProcess()
{
    int i=-1;
    int j1,j2;
    
//    qDebug("slotGetBarEndOfProcess::inrad=%s",inrad.latin1());    
    
     i = errorrad.find( QRegExp("Error:"), 0 );
     if (i == 0) {
		QMessageBox::critical( this, "OLFIX - BARDSP",
			"ERROR!\n"+errorrad
		);
	            errorrad="";
		i = -1;
     }
     i = inrad.find(QRegExp("OK:"),0);
     if (i == 0){
	 arid="";
	 benamn="";
	 j1 = inrad.find(QRegExp("ARID:"),0);
	 j2 = inrad.find(QRegExp("BENAMN:"),0);
//	 qDebug("BARDSP=%s\n",inrad.mid(i+5,2).latin1());
	 arid=inrad.mid(j1+5,j2-j1-7);
//	 qDebug("arid=%s",arid.latin1());
//             LineEditBar->setText((arid));
	 j1 = inrad.find(QRegExp("BENAMN:"),0);
 	 j2 = inrad.find(QRegExp("ARSTART:"),0);
	 benamn=inrad.mid(j1+7,j2-j1-9);
//	 LineEditBenamn->setText(benamn);
	 j1 = inrad.find(QRegExp("ARSTART:"),0);
	 j2 = inrad.find(QRegExp("ARSLUT:"),0);
	 arstart=inrad.mid(j1+8,j2-j1-10);
	 LineEditStartdatum->setText(arstart);
 	 j1 = inrad.find(QRegExp("ARSLUT:"),0);
 	 j2 = inrad.find(QRegExp("ARLAST:"),0);
	 arslut=inrad.mid(j1+7,j2-j1-9);
	 LineEditSlutdatum->setText(arslut);
	 j1 = inrad.find(QRegExp("SVERDAT:"),0);
	 j2 = inrad.find(QRegExp("VERNR:"),0);
	 senverdat=inrad.mid(j1+8,j2-j1-10);
//	 LineEditSenVerDat->setText(senverdat);
	 j1 = inrad.find(QRegExp("VERNR:"),0);
	 j2 = inrad.find(QRegExp("KTOPLAN:"),0);
	 vernr=inrad.mid(j1+6,j2-j1-8);
//	 LineEditNestaVerNr->setText(vernr);
	 j1 = inrad.find(QRegExp("KTOPLAN:"),0);
	 j2 = inrad.find(QRegExp("BESKATT:"),0);
	 ktoplan=inrad.mid(j1+8,j2-j1-10);
	 LineEditKontoplan->setText(ktoplan);
	 j1 = inrad.find(QRegExp("BESKATT:"),0);
	 beskattar=inrad.mid(j1+8,4);
	 LineEditBeskattAr->setText(beskattar);
	 }
     GetDatabase();
}

void frmRapportSIE::GetDatabase()
{
  QString rcfil;
  QStringList lines;
  QString homeDir( QDir::homeDirPath() );
   rcfil.append(homeDir);
   rcfil.append("/.olfixrc");				 // configfil
// Läs in config filen här
   QFile file(rcfil);
   file.open( IO_ReadOnly );
   QTextStream stream( &file );
   QString line;
   while ( !stream.eof() ) {
       line = stream.readLine();			   // line of text excluding '\n'
       int i = line.find( QRegExp("DATABASE="), 0 );    // i == 1
       if ( i == 0){
	   int l =line.length();
	   databas = line.mid(9,l);
       }
       lines += line;
   }
   file.close(); 
   lineEditDatabas->setText(databas);
}

void frmRapportSIE::slotFileRemove(QString filnamn)
{
//  Ta bort temporärfilen /tmp/SIEtyp4.txt
//    qDebug("rapportfilen=%s",filnamn.latin1());
    bool status;
    QDir d = QDir::root();                   // "/"
    if ( !d.cd("tmp") ) {                       // "/tmp"
        qWarning( "Cannot find the \"/tmp\" directory" );
    }
    status=d.remove(filnamn,TRUE);
//    qDebug("status=%d",status);
}

void frmRapportSIE::GetKontoplan()
{
	const char *userp = getenv("USER");
            QString usr(userp);
	inrad="";
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "SIEEXPK");	// OLFIX funktion
	process->addArgument(arid);
	
//	qDebug("slotGetBar::arid=%s",arid.latin1());
	
	frmRapportSIE::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmRapportSIE::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
            frmRapportSIE::connect( process, SIGNAL(processExited() ),this, SLOT(slotGetKontoplanEndOfProcess() ) );

	if (arid == "" ){
    	    QMessageBox::warning( this, "RPTSIEW",
                      "Bokföringsår måste vara ifyllt!" );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		QMessageBox::warning( this, "RPTSIEW",
                            "Kan inte starta STYRMAN/SIEEXPK! \n" );
	    }
	}
}

void frmRapportSIE::slotGetKontoplanEndOfProcess()
{
    int i=-1;
    int j1,j2;
    QFile filnamn(reportfile);
    QTextStream stream(&filnamn);    
    QString kontoplan;
//    qDebug("slotGetKontoplanEndOfProcess::reportfile=%s",reportfile.latin1());
//    qDebug("slotGetKontoplanEndOfProcess::inrad=%s",inrad.latin1());    
    
     i = errorrad.find( QRegExp("Error:"), 0 );
     if (i == 0) {
		QMessageBox::critical( this, "OLFIX - SIEEXPK",
			"ERROR!\n"+errorrad
		);
	            errorrad="";
		i = -1;
     }
     i = inrad.find(QRegExp("OK:"),0);
     if (i == 0){
	 j1 = inrad.find(QRegExp("#KONTO"),0);
	 j2 = inrad.find(QRegExp("END:"),0);
//	 qDebug("SIEEXPK: j1=%d j2=%d längd=%d\n",j1,j2,inrad.length());
	 kontoplan=inrad.mid(j1,j2-j1);
     }
//     qDebug("Kontoplan=\n%s",kontoplan.latin1());
    filnamn.open( IO_WriteOnly | IO_Append );
    stream << kontoplan;
    filnamn.close();
    frmRapportSIE::GetResultat();
}

void frmRapportSIE::GetResultat()
{
	const char *userp = getenv("USER");
            QString usr(userp);
	inrad="";
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "SIEEXPR");	// OLFIX funktion
	process->addArgument(arid);
	
//	qDebug("slotGetBar::arid=%s",arid.latin1());
	
	frmRapportSIE::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmRapportSIE::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
            frmRapportSIE::connect( process, SIGNAL(processExited() ),this, SLOT(slotGetResultatEndOfProcess() ) );

	if (arid == "" ){
    	    QMessageBox::warning( this, "RPTSIEW",
                      "Bokföringsår måste vara ifyllt!" );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		QMessageBox::warning( this, "RPTSIEW",
                            "Kan inte starta STYRMAN/SIEEXPR! \n" );
	    }
	}
}

void frmRapportSIE::slotGetResultatEndOfProcess()
{
    int i=-1;
    int j1,j2;
    QFile filnamn(reportfile);
    QTextStream stream(&filnamn);    
    QString resultat;
//    qDebug("slotGetResultatEndOfProcess::reportfile=%s",reportfile.latin1());
//    qDebug("slotGetResultatEndOfProcess::inrad=%s",inrad.latin1());    
    
     i = errorrad.find( QRegExp("Error:"), 0 );
     if (i == 0) {
		QMessageBox::critical( this, "OLFIX - SIEEXPR",
			"ERROR!\n"+errorrad
		);
	            errorrad="";
		i = -1;
     }
     i = inrad.find(QRegExp("OK:"),0);
     if (i == 0){
	 j1 = inrad.find(QRegExp("#UB"),0);
	 j2 = inrad.find(QRegExp("END:"),0);
//	 qDebug("SIEEXPR: j1=%d j2=%d längd=%d\n",j1,j2,inrad.length());
	  resultat=inrad.mid(j1,j2-j1);
     }
//     qDebug("Kontoplan=\n%s",kontoplan.latin1());
    filnamn.open( IO_WriteOnly | IO_Append );
    stream << resultat;
    filnamn.close();
    frmRapportSIE::GetVerifikationer();
}

void frmRapportSIE::GetVerifikationer()
{
	const char *userp = getenv("USER");
            QString usr(userp);
	inrad="";
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "SIEEXPV");	// OLFIX funktion
	process->addArgument(arid);
	process->addArgument("0");		// serie
	
//	qDebug("slotGetBar::arid=%s",arid.latin1());
	
	frmRapportSIE::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmRapportSIE::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
            frmRapportSIE::connect( process, SIGNAL(processExited() ),this, SLOT(slotGetVerifikationerEndOfProcess() ) );

	if (arid == "" ){
    	    QMessageBox::warning( this, "RPTSIEW",
                      "Bokföringsår måste vara ifyllt!" );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		QMessageBox::warning( this, "RPTSIEW",
                            "Kan inte starta STYRMAN/SIEEXPV! \n" );
	    }
	}
}

void frmRapportSIE::slotGetVerifikationerEndOfProcess()
{
   int i=-1;
    int j1,j2;
    QFile filnamn(reportfile);
    QTextStream stream(&filnamn);    
    QString verifikat;
//    qDebug("slotGetVerifikationerEndOfProcess::reportfile=%s",reportfile.latin1());
//    qDebug("slotGetVerifikationerEndOfProcess::inrad=%s",inrad.latin1());    
    
     i = errorrad.find( QRegExp("Error:"), 0 );
     if (i == 0) {
		QMessageBox::critical( this, "OLFIX - SIEEXPV",
			"ERROR!\n"+errorrad
		);
	            errorrad="";
		i = -1;
     }
     i = inrad.find(QRegExp("OK:"),0);
     if (i == 0){
	 j1 = inrad.find(QRegExp("#VER"),0);
	 j2 = inrad.find(QRegExp("END:"),0);
//	 qDebug("SIEEXPV: j1=%d j2=%d längd=%d\n",j1,j2,inrad.length());
	 verifikat=inrad.mid(j1,j2-j1);
     }
//     qDebug("Verifikat=\n%s",kontoplan.latin1());
    filnamn.open( IO_WriteOnly | IO_Append );
    stream << verifikat;
    filnamn.close();
}

void frmRapportSIE::pushBtnHelp_clicked()
{
	inrad="";
	frmRapportSIE::readResursFil();		// Hämta path till hjälpfilen

	int i1 = hjelpfil.find( QRegExp(".html"), 0 );
//	int i2 = hjelpfil.length();
	hjelpfil=hjelpfil.left(i1);
	hjelpfil=hjelpfil+"_RAPPORTER.html";
	hjelpfil=hjelpfil+"#SIERAPPORT4";		// Lägg till position
//	qDebug("hjelpfil=%s",hjelpfil.latin1());

	process = new QProcess();
	process->addArgument( "OLFIXHLP" );	// OLFIX program
	process->addArgument(hjelpfil);

	if ( !process->start() ) {
	    // error handling
	    QMessageBox::warning( this, "OLFIX","Kan inte starta OLFIXHLP!\n" );
	}

}

void frmRapportSIE::readResursFil()
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

void frmRapportSIE::GetTmpDir()
{
    /*****************************************************/
    /*  Läs in .olfixrc filen här			               */
    /* Plocka fram var mappen tmp finns		               */
    /*****************************************************/

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
