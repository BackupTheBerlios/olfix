/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                          BOKFORSW  -  description	BOKFORS=BokföringStandard
                             -------------------
		     version 0.42
    begin                : Sön 10 aug 2003
    modified	: Fre 2 jan 2004
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
#include <qlistview.h>
#include <qdatetime.h>
#include <qfileinfo.h>
#include <qdir.h>

#define MAXSTRING 15000
#define VERSION "0.42"

    QProcess* process;
    QString inrad;
    QString* rad;
    QString errorrad;
    int status = 0;
    QString inradktolist;
    
    QString datum;
    QString arid;		// Bokföringsår.
    QString vernr;
    QString vertext;
    QString radnr;
    QString kontonr;
    QString dk;
    QString belopp;
    QString kstalle;
    QString subkto;
    
    QString diff;
    double differ = 0;  
    
void frmBokfstd::init()
{
    QDateTime dt = QDateTime::currentDateTime();
    
//    QString version;
//    version="Version: ";
//    version.append(VERSION);
//    textLabelVersion->setText(version);
    datum=dt.toString("yyyy-MM-dd");
    TextLabelDate->setText(datum);
    frmBokfstd::formatRegRader();
    LineEditBar->setFocus();
    radnr="0";				// ver. 0.4
}

void frmBokfstd::slotLineEditBar_lostFocus()
{
    arid=LineEditBar->text();
    if (arid != "")
	slotLineEditBar_returnPressed();
}

void frmBokfstd::slotLineEditBar_returnPressed()
{
    arid=LineEditBar->text();
    arid=arid.upper();
    LineEditBar->setText((arid));
    if (arid==""){
	QMessageBox::warning( this, "BOKFORSW",
                      "Bokföringsår måste fyllas i! \n" );
	LineEditBar->setFocus();
    }
    else{
	frmBokfstd::slotCheckBar();
    }
}

void frmBokfstd::slotLineEditVerText_returnPressed()
{
    vertext=LineEditVerText->text();
    frmBokfstd::slotUpdateRadnr();
}

void frmBokfstd::slotLineEditKtonr_textChanged()
{
    QString temp;
    temp = LineEditKtonr->text();
    
    QListViewItem *item = ListViewKto->findItem( temp, 0, BeginsWith );
    ListViewKto->setCurrentItem(item);
}

void frmBokfstd::slotLineEditKtonr_lostFocus()
{
    kontonr=LineEditKtonr->text();
    if (kontonr != "")
	slotLineEditKtonr_returnPressed();
}

void frmBokfstd::slotLineEditKtonr_returnPressed()
{
    kontonr=LineEditKtonr->text();
    frmBokfstd::slotCheckKonto();
    LineEditDK->setFocus();
}

void frmBokfstd::slotLineEditDK_lostFocus()
{
    dk=LineEditDK->text();
    if (dk != "")
	slotLineEditDK_returnPressed();
}

void frmBokfstd::slotLineEditDK_returnPressed()
{
    dk=LineEditDK->text();
    if (dk == "+"){				// japi 20030520
	dk="D";
    }
    if (dk == "-"){				// japi 20030520
	dk="K";
    }
    dk=dk.upper();
    LineEditDK->setText((dk));
    LineEditBelopp->setFocus();
}

void frmBokfstd::slotLineEditBelopp_returnPressed()
{
    int i = -1;
    belopp=LineEditBelopp->text();
    i = belopp.find( QRegExp(","), 0 );
    if ( i != -1){
	 belopp = belopp.replace( i, 1, "." );
    }
    
    i = -1;    
    i = belopp.findRev(".");
    if ( i == -1){
	belopp = belopp.append(".00");
    }    
    while (belopp.length()<12){
	belopp.prepend(" ");
    }
    LineEditBelopp->setText(belopp); 
    LineEditKst->setFocus();
}

void frmBokfstd::slotLineEditKst_returnPressed()
{
    kstalle=LineEditKst->text();
    if ( !kstalle.isEmpty() ){
	// kolla om kstalle finns
	frmBokfstd::slotCheckKstalle();
    }else{
	LineEditSubKto->setFocus();
    }
}

void frmBokfstd::slotLineEditSubKto_returnPressed()
{
    subkto=LineEditSubKto->text();
    // Här ska i framtiden kontroll göras att subkonto finns. Nu finns ingen tabell för subkonto (japi 2003-03-01)
    PushButtonRadOK->setFocus();
}

void frmBokfstd::slotRadOK()
{
    QListViewItem * item;
    int i = 0;
// Visa verifikationsraden som registrerad rad    
    item = new QListViewItem(ListViewVerrader,radnr,kontonr,dk,belopp,kstalle,subkto);
// Beräkna och vissa differensen på registrerade rader (Vad som återstår att registrera)    
    i = radnr.toInt();
    if (i == 1){
	if (dk == "D"){
	    differ = belopp.toDouble();
	}
	else{
	    differ = 0 - belopp.toDouble();
	}
    }else{
	if (dk == "K"){
	    differ = differ - belopp.toDouble();
	}
	else{
	    differ = differ + belopp.toDouble();
	}		
    }
    diff = diff.setNum(differ,'f',2);
    LineEditDiff->setText(diff);
// ===========================================================    
//  Här ska verifikationsraden sparas 
//     i = radnr.toInt();
// Om det är radnr 1 ska VERHUVUD sparas
// Annars ska VERRAD spara.    
// ===========================================================    
//  qDebug("i = %d\n",i);
/*    
    if (i == 1){
	 frmBokfstd::slotSaveVerHuvud();
     }else{
	 frmBokfstd::slotSaveVerRad();
     }
*/     
//    qDebug("Radnr = %s\n",radnr.latin1()); 
// ===========================================================    
    LineEditRadnr->clear();
    LineEditKtonr->clear();
    LineEditDK->clear();
    LineEditBelopp->clear();
    LineEditKst->clear();
    LineEditSubKto->clear();
// Kolla om verifikatet är färdigt.    
    if (differ != 0){
	frmBokfstd::slotUpdateRadnr();
	LineEditKtonr->setFocus();
    }else{
	PushButtonVerOK->setFocus();
    }   
}

void frmBokfstd::slotUpdateRadnr()
{
    int rad=0;
    bool ok;
    rad = radnr.toInt(&ok,10);
    rad = rad + 1;
    radnr = QString::number(rad,10);
    while (radnr.length()<3){
	radnr.prepend("0");
    }
    LineEditRadnr->setText((radnr));
    LineEditKtonr->setFocus();
}


void frmBokfstd::slotPickupKtonr( QListViewItem * item)
{
    char kontonummer[9]="";
    if(!item){
	return;
    }
     ListViewKto->setCurrentItem(item);
     if(!item->key(0,TRUE)){
	 return;
     }

     strcpy(kontonummer,item->key(0,TRUE));
     kontonr=kontonummer;
     LineEditKtonr->setText((kontonr));
     LineEditDK->setFocus();
}

void frmBokfstd::slotGetKontoLista()
{
    	const char *userp = getenv("USER");
            QString usr(userp);
	inradktolist="";
	errorrad="";
	
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "KTOVIEW");	// OLFIX funktion
	process->addArgument(arid);
	
	frmBokfstd::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotKTOVIEWDataOnStdout() ) );
	frmBokfstd::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmBokfstd::connect( process, SIGNAL(processExited() ),this, SLOT(slotKTOVIEWEndOfProcess() ) );

	if ( !process->start() ) {
	    // error handling
	    fprintf(stderr,"Problem starta STYRMAN/KTOVIEW!\n");
	    QMessageBox::warning( this, "BOKFORSW",
                            "Kan inte starta STYRMAN/KTOVIEW! \n" );
	    }
}

void frmBokfstd::slotKTOVIEWDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inradktolist.append(line);
	inradktolist.append("\n");
    }
}

void frmBokfstd::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmBokfstd::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmBokfstd::slotBARCHKEndOfProcess()
{
    int i = -1;

    i = errorrad.find( QRegExp("Error:"), 0 );
//	qDebug("errorrad=%s i=%d\n",errorrad.latin1(),i);
            if (i == 0) {
		QMessageBox::critical( this, "OLFIX - BARCHK",
			"ERROR!\n"+errorrad
		);
	            errorrad="";
		i = -1;
		status = -1;
		LineEditBar->clear();
	    }
	    else{
		i = -1;    
		i = inrad.find( QRegExp("OK:"), 0 );  
		if(i == 0){
		    status = 0;
		    inrad="";
		    errorrad="";
		    LineEditVernr->setFocus();
		    ListViewKto->clear();
		    frmBokfstd::slotGetKontoLista();
		}
	    }
}

void frmBokfstd::slotCheckBar()
{
	const char *userp = getenv("USER");
            QString usr(userp);

	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "BARCHK");	// OLFIX funktion
	process->addArgument(arid);
	
	frmBokfstd::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmBokfstd::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmBokfstd::connect( process, SIGNAL(processExited() ),this, SLOT(slotBARCHKEndOfProcess() ) );

	if ( !process->start() ) {
	    // error handling
	    fprintf(stderr,"Problem starta STYRMAN/BARCHK!\n");
	    QMessageBox::warning( this, "BOKFORSW",
                            "Kan inte starta STYRMAN/BARCHK! \n" );
	    }
}

void frmBokfstd::slotGetNextVernr()
{
	const char *userp = getenv("USER");
            QString usr(userp);

	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "BARDSP");	// OLFIX funktion
	process->addArgument(arid);
	inrad="";
	
	frmBokfstd::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmBokfstd::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmBokfstd::connect( process, SIGNAL(processExited() ),this, SLOT(slotBARDSPEndOfProcess() ) );

	if ( !process->start() ) {
	    // error handling
	    fprintf(stderr,"Problem starta STYRMAN/BARDSP!\n");
	    QMessageBox::warning( this, "BOKFORSW",
                            "Kan inte starta STYRMAN/BARDSP! \n" );
	    }
}

void frmBokfstd::slotBARDSPEndOfProcess()
{
    int i = -1;
    int j = 0;

    i = errorrad.find( QRegExp("Error:"), 0 );
//	qDebug("errorrad=%s i=%d\n",errorrad.latin1(),i);
            if (i == 0) {
		QMessageBox::critical( this, "OLFIX - BARDSP",
			"ERROR!\n"+errorrad
		);
	            errorrad="";
		i = -1;
		status = -1;
		LineEditBar->clear();
	    }
	    else{
		i = -1;    
		i = inrad.find( QRegExp("OK:"), 0 );  
		if(i == 0){
		    i = -1;
		    i = inrad.find(QRegExp("VERNR:"), 0 );
		    i = i + 6;				// positionen efter VERNR:
		    j = inrad.find(QRegExp("KTOPLAN:"), 0 );
		    vernr = inrad.mid(i,j-2-i);
		    while (vernr.length()<8){
			vernr.prepend("0");
		    }
//		    qDebug("\n%s\n i=%d  j = %d vernr=%s\n",inrad.latin1(),i,j,vernr.latin1());
		    LineEditVernr->setText(vernr);
		    status = 0;
		    inrad="";
		    errorrad="";
		    LineEditVerText->setFocus();
		}
	    }
}

void frmBokfstd::slotKTOVIEWEndOfProcess()
{
    QListViewItem* item;
  int i;
  int j,k,l,m;
  char *pos1;
  char *pos2;
  char tmp[MAXSTRING];
  char *tmppek;
  char antrad[6]="";
  char ktonr[5]="";
  char benamn[61]="";

    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "BOKFORSW",
		"ERROR!\n"+errorrad );
	 errorrad="";
	 arid="";
	 LineEditBar->setFocus();
     }else{
	     //    rad=&inrad;
	 inradktolist.latin1();
//	 qDebug("inradktolist=%s\n",inradktolist.latin1());
	 tmppek=tmp;
	 qstrcpy(tmp,inradktolist);
	 pos1=strstr(tmp,"NR_");
	 pos2=strstr(tmp,"_:");
	 i = pos2 - pos1;
	 m=i+2;		// startposition för första ktonr.
//	 qDebug("i=%d m=%d\n",i,m);
	 k=0;
	 for (j=3;j<i;j++){
	     antrad[k]=tmp[j];
	     k++;
	 };
	 i = atoi(antrad);		// i = antal poster
	 for (k = 1;k <= i; k++){	// gå igenom alla raderna / posterna
	     l=0;
	     for(j = m; j < sizeof(ktonr) + m; j++){
		 if(tmp[j] != *("_")){
		     ktonr[l]=tmp[j];
		     l++;
		  }else{
		      ktonr[l] = *("\0");
		      j=sizeof(ktonr) + m;
		  }
	      }
		 //	fprintf(stdout,"%s  ",ktonr);
	     m=m+l+2;	// position för benamn
	     l=0;
	     for(j = m; j < sizeof(benamn) + m; j++){
		 if(tmp[j] != *("_")){
		     benamn[l]=tmp[j];
		     l++;
		  }else{
		      benamn[l] = *("\0");
		      j=sizeof(benamn) + m;
		  }
	      }
		 //	fprintf(stdout,"%s  ",benamn);
	     m=m+l+2;
	     
	     item = new QListViewItem(ListViewKto,ktonr,benamn);
		 /* rensa ktonr,benamn */
	     for (l=0;l<sizeof(ktonr);l++){
		 ktonr[l]=*("\0");
	     }
	     for (l=0;l<sizeof(benamn);l++){
		     benamn[l]=*("\0");
	     }
	 }
     }
    frmBokfstd::slotGetNextVernr();
}

void frmBokfstd::slotCheckKstalle()
{
	const char *userp = getenv("USER");
            QString usr(userp);

	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "KSTCHK");	// OLFIX funktion
	process->addArgument(arid);
	process->addArgument(kstalle);
	
	frmBokfstd::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmBokfstd::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmBokfstd::connect( process, SIGNAL(processExited() ),this, SLOT(slotKSTCHKEndOfProcess() ) );

	if ( !process->start() ) {
	    // error handling
	    fprintf(stderr,"Problem starta STYRMAN/KSTCHK!\n");
	    QMessageBox::warning( this, "BOKFORSW",
                            "Kan inte starta STYRMAN/KSTCHK! \n" );
	    }
}

void frmBokfstd::slotKSTCHKEndOfProcess()
{
    int i = -1;

    i = errorrad.find( QRegExp("Error:"), 0 );
//	qDebug("errorrad=%s i=%d\n",errorrad.latin1(),i);
            if (i == 0) {
		QMessageBox::critical( this, "OLFIX - KSTCHK",
			"ERROR!\n"+errorrad
		);
	            errorrad="";
		i = -1;
		status = -1;
		LineEditKst->clear();
	    }
	    else{
		i = -1;    
		i = inrad.find( QRegExp("OK:"), 0 );  
		if(i == 0){
		    status = 0;
		    inrad="";
		    errorrad="";
		    LineEditSubKto->setFocus();
		}
	    }
}

void frmBokfstd::slotCheckKonto()
{
	const char *userp = getenv("USER");
            QString usr(userp);

	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "KTOCHK");	// OLFIX funktion
	process->addArgument(arid);
	process->addArgument(kontonr);
	
	frmBokfstd::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmBokfstd::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmBokfstd::connect( process, SIGNAL(processExited() ),this, SLOT(slotKTOCHKEndOfProcess() ) );

	if ( !process->start() ) {
	    // error handling
	    fprintf(stderr,"Problem starta STYRMAN/KTOCHK!\n");
	    QMessageBox::warning( this, "BOKFORSW",
                            "Kan inte starta STYRMAN/KTOCHK! \n" );
	    }
}

void frmBokfstd::slotKTOCHKEndOfProcess()
{
    int i = -1;

    i = errorrad.find( QRegExp("Error:"), 0 );
//	qDebug("errorrad=%s i=%d\n",errorrad.latin1(),i);
            if (i == 0) {
		QMessageBox::critical( this, "OLFIX - KTOCHK",
			"ERROR!\n"+errorrad
		);
	            errorrad="";
		i = -1;
		status = -1;
		LineEditKtonr->clear();
		LineEditKtonr->setFocus();
	    }
	    else{
		i = -1;    
		i = inrad.find( QRegExp("OK:"), 0 );  
		if(i == 0){
		    status = 0;
		    inrad="";
		    errorrad="";
                            LineEditDK->setFocus();
		}
	    }
}

void frmBokfstd::slotSaveVerHuvud()
{
	const char *userp = getenv("USER");
            QString usr(userp);
	QString posttyp="H";
	if (kstalle == "")
	    kstalle="    ";
	if(subkto == "")
	    subkto="    ";
	while (usr.length()<8){
	    usr.append(" ");
	}
	process = new QProcess();
	process->addArgument( "./WRREC");	// OLFIX funktion
	process->addArgument(posttyp);
	process->addArgument(arid);
	process->addArgument(vernr);
	process->addArgument(radnr);
	process->addArgument(kontonr);
	process->addArgument(dk);
	process->addArgument(belopp);
	process->addArgument(kstalle);
	process->addArgument(subkto);
	process->addArgument(datum);
	process->addArgument(usr);
	process->addArgument(vertext);
	
//	qDebug("posttyp=%s",posttyp.latin1());
	
	frmBokfstd::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmBokfstd::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmBokfstd::connect( process, SIGNAL(processExited() ),this, SLOT(slotWRRECEndOfProcess() ) );

	if ( !process->start() ) {
	    // error handling
	    fprintf(stderr,"Problem starta WRREC!\n");
	    QMessageBox::warning( this, "BOKFORSW",
                            "Kan inte starta WRREC! \n" );
	    }
}

void frmBokfstd::slotSaveVerRad()
{
//	const char *userp = getenv("USER");
//            QString usr(userp);
	QString posttyp="D";

	process = new QProcess();
	process->addArgument( "./WRREC");	// OLFIX funktion
	process->addArgument(posttyp);
	process->addArgument(arid);
	process->addArgument(vernr);
	process->addArgument(radnr);
	process->addArgument(kontonr);
	process->addArgument(dk);
	process->addArgument(belopp);
	process->addArgument(kstalle);
	process->addArgument(subkto);
	
	if ( !process->start() ) {
	    // error handling
//	    fprintf(stderr,"Problem starta WRREC!\n");
	    QMessageBox::warning( this, "BOKFORSW",
                            "Kan inte starta WRREC! \n" );
	    }
}

void frmBokfstd::slotWRRECEndOfProcess()
{
    int i = -1;

    i = errorrad.find( QRegExp("Error:"), 0 );
//	qDebug("errorrad=%s i=%d\n",errorrad.latin1(),i);
            if (i == 0) {
		QMessageBox::critical( this, "OLFIX - WRREC",
			"ERROR!\n"+errorrad
		);
	            errorrad="";
		i = -1;
		status = -1;
	    }
}

void frmBokfstd::slotVerOK()
{
// Starta uppdatering av databasen 
	const char *userp = getenv("USER");
            QString usr(userp);
            QString filnamn;
	    
	filnamn.append(vernr);
		
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "VERUPD");	// OLFIX funktion
	process->addArgument(filnamn);
	
	frmBokfstd::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmBokfstd::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmBokfstd::connect( process, SIGNAL(processExited() ),this, SLOT(slotVERUPDEndOfProcess() ) );

	if ( !process->start() ) {
	    // error handling
	    fprintf(stderr,"Problem starta STYRMAN/VERUPD!\n");
	    QMessageBox::warning( this, "BOKFORSW",
                            "Kan inte starta STYRMAN/VERUPD! \n" );
	    }
}


void frmBokfstd::slotVerRemove()
{
// Rensa alla fält samt ta bort temporärfilen /tmp/vernr.txt
// Ändrad 2003-05-20 japi    
    bool status;    
    QString filnamn;
    QDir d = QDir::root();                      // "/"
    if ( !d.cd("tmp") ) {                       // "/tmp"
        qWarning( "Cannot find the \"/tmp\" directory" );
    }
    
    filnamn=vernr;
    filnamn.append(".txt");
    
//    qDebug("filnamn=%s",filnamn.latin1());
    status=d.remove(filnamn,FALSE);
//    qDebug("status=%d",status);
    frmBokfstd::slotCleanUp();  
    frmBokfstd::slotGetNextVernr();
}


void frmBokfstd::slotVERUPDEndOfProcess()
{
    int i = -1;

    i = errorrad.find( QRegExp("Error:"), 0 );
//	qDebug("errorrad=%s i=%d\n",errorrad.latin1(),i);
    if (i == 0) {
	QMessageBox::critical( this, "OLFIX - VERUPD",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
	status = -1;
	frmBokfstd::slotVerRemove();
    }
    else{
	i = -1;    
	i = inrad.find( QRegExp("OK: Databasen"), 0 );  		
	if (i != -1) {
	    QMessageBox::information( this, "BOKFORSW",
		"Uppdatering OK!\n"+errorrad
		);
	    status = 0;
	    inrad="";
	    errorrad="";
	}
    }
    frmBokfstd::slotCleanUp();
    if (status == 0){
	frmBokfstd::slotGetNextVernr();
    }
}


void frmBokfstd::slotCleanUp()
{
    LineEditVernr->clear();
    LineEditVerText->clear();
    LineEditRadnr->clear();
    LineEditKtonr->clear();
    LineEditDK->clear();
    LineEditBelopp->clear();
    LineEditKst->clear();
    LineEditSubKto->clear();
    LineEditDiff->clear();
    ListViewVerrader->clear();
    inrad="";
    errorrad="";
    status = 0;
    inradktolist="";
//    datum="";
//    arid="";
    vernr="";
    vertext="";
    radnr="";
    kontonr="";
    dk="";
    belopp="";
    kstalle="";
    subkto="";
    diff="";
    differ = 0;  
}

void frmBokfstd::formatRegRader()			// 2004-01-02
{
    ListViewVerrader->setColumnWidth(0,45);	// Radnr
    ListViewVerrader->setColumnAlignment( 0, Qt::AlignRight );
    ListViewVerrader->setColumnWidth(1,55);	// Kontonr
    ListViewVerrader->setColumnAlignment( 1, Qt::AlignRight );
    ListViewVerrader->setColumnWidth(2,35);	// D/K
    ListViewVerrader->setColumnAlignment( 2, Qt::AlignCenter );
    ListViewVerrader->setColumnWidth(3,100);	// Belopp
    ListViewVerrader->setColumnAlignment( 3, Qt::AlignRight );
    ListViewVerrader->setColumnWidth(4,65);	// Kställe
    ListViewVerrader->setColumnAlignment( 4, Qt::AlignRight );
    ListViewVerrader->setColumnWidth(5,65);	// Subkto
    ListViewVerrader->setColumnAlignment( 5, Qt::AlignRight );   
}

void frmBokfstd::SaveVerifikat()			// 2004-01-02
{
    int i=0;
    int rad=0;
    QListViewItemIterator it( ListViewVerrader);
    QString rnr;
    for ( ; it.current(); ++it ){
       i++;
       QString temp0=it.current()->text(0);	// radnr
       QString temp1=it.current()->text(1);	// kontonr
       QString temp2=it.current()->text(2);	// D/K
       QString temp3=it.current()->text(3);	// belopp
       QString temp4=it.current()->text(4);	// Kställe
       QString temp5=it.current()->text(5);	// Subkto
       radnr=temp0;
       kontonr=temp1;
       dk=temp2;
       belopp=temp3;
       kstalle=temp4;
       subkto=temp5;

       rad = radnr.toInt();
       if (rad == 1){
//	   qDebug("radnr=%s kontonr=%s d/k=%s belopp=%s kstalle=%s subkto=%s",radnr.latin1(),kontonr.latin1(),dk.latin1(),belopp.latin1(),kstalle.latin1(),subkto.latin1());
	   frmBokfstd::slotSaveVerHuvud();	   
       }else{
	   frmBokfstd::slotSaveVerRad();
//	   qDebug("radnr=%s kontonr=%s d/k=%s belopp=%s kstalle=%s subkto=%s",radnr.latin1(),kontonr.latin1(),dk.latin1(),belopp.latin1(),kstalle.latin1(),subkto.latin1());
       }
   }
   ListViewVerrader->clear();
   frmBokfstd::slotVerOK();
}

void frmBokfstd::ListViewVerrader_clicked( QListViewItem * )
{
    double tmpbelopp;
    double tmpdiff;
    QString difference;
    QListViewItem *item =  ListViewVerrader->currentItem();
    if ( !item )
        return;
    item->setSelected( TRUE );
    QString temp0=item->text(0);	// radnr
    QString temp1=item->text(1);	// kontonr
    QString temp2=item->text(2);	// d/k
    QString temp3=item->text(3);	// belopp
    QString temp4=item->text(4);	// kställe
    QString temp5=item->text(5);	// subkto

    LineEditRadnr->setText(temp0);
    radnr=temp0;
    LineEditKtonr->setText(temp1);
    LineEditDK->setText(temp2);
    LineEditBelopp->setText(temp3);
    tmpbelopp=temp3.toDouble();
    LineEditKst->setText(temp4);
    LineEditSubKto->setText(temp4);
    difference=LineEditDiff->text();
    tmpdiff=difference.toDouble();
    if (temp2 == "K"){			// D/K
	tmpdiff = tmpdiff + tmpbelopp;	//  -
    }
    else{
	tmpdiff = tmpdiff - tmpbelopp;	// +
    }
    differ=tmpdiff;
    diff=diff.setNum(tmpdiff,'f',2);
    LineEditDiff->setText(diff);
    delete ListViewVerrader->currentItem();
    LineEditKtonr->setFocus();
}
