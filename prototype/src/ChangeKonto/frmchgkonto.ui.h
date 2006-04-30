/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                          CHGKTOW  -  description
                             -------------------
		     version 0.4.3
    begin                	: Lör 7 juni 2003
    Modified		: Sön 30 april 2006
    copyright            	: (C) 2003 by Jan Pihlgren
    email                	: jan@pihlgren.se
 ***************************************************************************/
/*****************************************************************
 *					                                            *
 *   This program is free software; you can redistribute it and/or modify 	 *
 *   it under the terms of the GNU General Public License as published by       	 *
 *   the Free Software Foundation; either version 2 of the License, or     	 *
 *   (at your option) any later version.                                   		 	 *
 *                                                                         				 *
 *********************************************** *****************/
#include <qmessagebox.h>
#include <qprocess.h>
#include <qdir.h>
#include <stdlib.h>
#include <qstring.h>		
#include <qfile.h>
#include <qregexp.h> 
#define MAXSTRING 5000

    QProcess* process;
    QString inrad;
    QString errorrad;
    QString arid;
    QString ktonr;
    QString benamn;
    QString manuell;
    QString momskod;
    QString srunr;
    QString kst;
    QString projekt;
    QString subkonto;
    QString ktoplan;


void frmChgKonto::slotChgKonto()
{
/************************************************************************/
/*	Uppdatera databasen						*/
/************************************************************************/
	const char *userp = getenv("USER");
	QString usr(userp);

	inrad="";
	errorrad="";
	
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "KTOCHG");	// OLFIX funktion
	process->addArgument(arid);
	process->addArgument(ktonr);
	process->addArgument(benamn);
	process->addArgument(manuell);
	process->addArgument(momskod);
	process->addArgument(srunr);
	process->addArgument(kst);
	process->addArgument(projekt);
	process->addArgument(subkonto);
	process->addArgument(ktoplan);
	
	frmChgKonto::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotPutDataOnStderr() ) );
	frmChgKonto::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotPutDataOnStdout() ) );
	frmChgKonto::connect( process, SIGNAL(processExited() ),this, SLOT(slotPutEndOfProcess() ) );	   

	if (manuell == ""){
	    manuell.append("J");
	}
//           qWarning(" Startar Chgkonto 1");

	if (arid == "" || ktonr =="" || momskod=="" || srunr =="" || ktoplan == "" ){
    	    QMessageBox::warning( this, "CHGKTOW",
                      "Ett eller flera av fälten \n Bokföringsår/Kontonumme/Momskod/SRUnr/Kontoplan\n saknas \n" );
	}
	else {
//	    qWarning(" Startar Addkonto 2");
	    if ( !process->start() ) {
		// error handling
		QMessageBox::warning( this, "CHGKTOW",
                            "Kan inte starta STYRMAN/KTOCHG! \n" );
	    }
	}
}

void frmChgKonto::LineEditBar_returnPressed()
{
    arid=LineEditBar->text();
    arid=arid.upper();
    LineEditBar->setText((arid));
    LineEditKontoNr->setFocus();
}

void frmChgKonto::LineEditKontoNr_returnPressed()
{
    ktonr=LineEditKontoNr->text();
    if (arid != "" && ktonr != ""){
	frmChgKonto::slotGetKonto();
	LineEditBenamn->setFocus();
    }else{
	QMessageBox::warning( this, "CHGKTOW",
                      "Både Bokföringsår och Kontonummer måste fyllas i! \n" );
	LineEditBar->setFocus();
	return;
    }
}

void frmChgKonto::LineEditBenamn_returnPressed()
{
    benamn=LineEditBenamn->text();
    LineEditManuell->setFocus();
}

void frmChgKonto::LineEditManuell_returnPressed()
{
    manuell=LineEditManuell->text();
    if (manuell == ""){
	manuell.append("J");
	LineEditManuell->setText((manuell));
	return;
     }
    LineEditMomskod->setFocus();
}

void frmChgKonto::LineEditMomskod_returnPressed()
{
    momskod=LineEditMomskod->text();
    if (momskod==""){
	QMessageBox::warning( this, "CHGKTOW",
                      "Momskod måste fyllas i! \n" );
	LineEditMomskod->setFocus();
	return;
    }
    LineEditSRU->setFocus();
}

void frmChgKonto::LineEditSRU_returnPressed()
{
    srunr=LineEditSRU->text();
    if (srunr==""){
	QMessageBox::warning( this, "CHGKTOW",
                      "SRUnummer måste fyllas i! \n" );
	LineEditSRU->setFocus();
	return;
    }    
    LineEditKst->setFocus();
}

void frmChgKonto::LineEditKst_returnPressed()
{
    kst=LineEditKst->text();
    LineEditProjekt->setFocus();
}

void frmChgKonto::LineEditProjekt_returnPressed()
{
    projekt=LineEditProjekt->text();
    LineEditSubkonto->setFocus();
}

void frmChgKonto::LineEditSubkonto_returnPressed()
{
    subkonto=LineEditSubkonto->text();
}

void frmChgKonto::LineEditKontoplan_returnPressed()
{
    ktoplan=LineEditKontoplan->text();
   if (ktoplan==""){
	QMessageBox::warning( this, "CHGKTOW",
                      "Kontoplan måste fyllas i! \n" );
	LineEditKontoplan->setFocus();
	return;
    }
   PushButtonOK->setFocus();
}

void frmChgKonto::PushButtonOK_clicked()
{
    LineEditBar->setEnabled(TRUE);
    LineEditKontoNr->setEnabled(TRUE);
    frmChgKonto::slotChgKonto();
}

void frmChgKonto::slotPutDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmChgKonto::slotPutDataOnStdout()
{
        while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmChgKonto::slotPutEndOfProcess()
{
    int i=-1;
    int j=-1;
    
//    qDebug("inrad=%s",inrad.latin1());
            i = -1;
            i = inrad.find( QRegExp("Error:"), 0 );
//	qDebug("frmChgKonto-inrad=%s i=%d\n",inrad.latin1(),i);
            if (i == 0) {
		QMessageBox::critical( this, "OLFIX - KTOCHG",
			"ERROR!\n"+inrad 
		);
	            inrad="";
		i = -1;
	    }
	j = -1;
	j = inrad.find( QRegExp("KTOCHG:INSERT error:"), 0 );
            if(j == 0){
		QMessageBox::information( this, "KTOCHG - Error!",
			"Felaktig kombination av Bokföringsår och Kontonummer\n" 
		);
		inrad="";
		j = -1;
	    }
            i = -1;
            i = inrad.find( QRegExp("OK: KTOCHG"), 0 );  
            if(i == 0){
		QMessageBox::information( this, "KTOCHG",
			"Uppdatering OK!\n" 
		);
	    LineEditBar->setEnabled(TRUE);
	    LineEditKontoNr->setEnabled(TRUE);		
	    LineEditBar->clear();
	    LineEditKontoNr->clear();
	    LineEditBenamn->clear();
	    LineEditManuell->setText("J");
	    LineEditMomskod->clear();
	    LineEditSRU->clear();
	    LineEditKst->clear();
	    LineEditProjekt->clear();
	    LineEditSubkonto->clear();
	    LineEditKontoplan->clear();
	    LineEditBar->setFocus();
	    inrad="";
	    i = -1;
    	    }
}


void frmChgKonto::slotGetEndOfProcess()
{
    int m;
    QString getarid;
    QString getktonr;
    QString getbenamn;
    QString getmanuell;
    QString getmomskod;
    QString getsrunr;
    QString getkst;
    QString getproj;
    QString getsubkto;
    QString getktoplan;
    QString getIB;
    QString getUB;
  
    int er = errorrad.find( QRegExp("Error:"), 0 );
    if (er != -1){
	QMessageBox::warning( this, "CHGKTOW",
                   "Felaktigt bokföringsår eller konto! \n"+errorrad
	);
	LineEditBar->setEnabled(TRUE);
	LineEditKontoNr->setEnabled(TRUE);
	LineEditBar->setFocus();
	errorrad="";
	arid="";
	ktonr="";
    }
    else{
    int ia = inrad.find( QRegExp("1:"), 0 );
    int ib = inrad.find( QRegExp("2:"), 0 );
    int ic = inrad.find( QRegExp("3:"), 0 );
    int id = inrad.find( QRegExp("4:"), 0 );
    int ie = inrad.find( QRegExp("5:"), 0 );
    int ig = inrad.find( QRegExp("6:"), 0 );
    int ih = inrad.find( QRegExp("7:"), 0 );
    int ij = inrad.find( QRegExp("8:"), 0 );
    int ik = inrad.find( QRegExp("9:"), 0 );
    int il = inrad.find( QRegExp("10:"), 0 );
    int im = inrad.find( QRegExp("11:"), 0 );
    int in = inrad.find( QRegExp("12:"), 0 );
    
    m=ib-ia;
    if (ia != -1){
	getarid=inrad.mid(ia+2,m-4);
	LineEditBar->setText(getarid);
    }
    m=ic-ib;
    if ( ib != -1){
	getktonr=inrad.mid(ib+2,m-4);
	LineEditKontoNr->setText(getktonr);
    }
    m=id-ic;
    if ( ic != -1){
	getbenamn=inrad.mid(ic+2,m-4);
	LineEditBenamn->setText(getbenamn);
    }

    m=ie-id;
    if ( id != -1){
	getmanuell=inrad.mid(id+2,m-4);
	LineEditManuell->setText(getmanuell);
    }
    
    m=ig-ie;
    if ( ie != -1){
	getmomskod=inrad.mid(ie+2,m-4);
	LineEditMomskod->setText(getmomskod);
    }
    m=ih-ig;
    if ( ig != -1){
	getsrunr=inrad.mid(ig+2,m-4);
	LineEditSRU->setText(getsrunr);
    }
    m=ij-ih;
    if ( ih != -1){
	getkst=inrad.mid(ih+2,m-4);
	LineEditKst->setText(getkst);
    }
    m=ik-ij;
    if ( ij != -1){
	getproj=inrad.mid(ij+2,m-4);
	LineEditProjekt->setText(getproj);
    }
    m=il-ik;
    if ( ik != -1){
	getsubkto=inrad.mid(ik+2,m-4);
	LineEditSubkonto->setText(getsubkto);
    }
    m=im-il;
    if ( il != -1){
	getktoplan=inrad.mid(il+3,m-4);
	LineEditKontoplan->setText(getktoplan);
    }
    m=in-im;
    if ( im != -1){
	getIB=inrad.mid(im+3,m-4);
	LineEditIB->setText(getIB);
    }  
    m=inrad.length() - in;
    if ( in != -1){
	getUB=inrad.mid(in+3,m-4);
	LineEditUB->setText(getUB);
    }
    inrad="";
    LineEditBenamn->setFocus();
  }
}

void frmChgKonto::slotGetDataOnStdout()
{
   while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
//	qWarning( "slotGetDataOnStdout: Userid=%s \n", inrad.latin1() );
    }
}

void frmChgKonto::slotGetDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmChgKonto::slotGetKonto()
{
/************************************************************************/
/*	Hämta uppgifter från databasen					*/
/************************************************************************/
	const char *userp = getenv("USER");
	QString usr(userp);

	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "KTODSP");	// OLFIX funktion
	process->addArgument(arid);
	process->addArgument(ktonr);
	
	frmChgKonto::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotGetDataOnStderr() ) );
	frmChgKonto::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotGetDataOnStdout() ) );
            frmChgKonto::connect( process, SIGNAL(processExited() ),this, SLOT(slotGetEndOfProcess() ) );	   

	if (arid == "" || ktonr =="" ){
    	    QMessageBox::warning( this, "CHGKTOW",
                      "Ett eller båda av fälten \n Bokföringsår/Kontonummer\n saknas \n" );
	}
	else {
//	    qWarning(" Startar Chgkonto 2");
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/KTODSP!\n");
		QMessageBox::warning( this, "CHGKTOW",
                            "Kan inte starta STYRMAN/KTODSP! \n" );
	    }
	}

}

void frmChgKonto::PushButtonGet_clicked()
{
    arid=LineEditBar->text();
    arid=arid.upper();
    LineEditBar->setText((arid));
    ktonr=LineEditKontoNr->text();
    LineEditBar->setEnabled(FALSE);
    LineEditKontoNr->setEnabled(FALSE);
    frmChgKonto::slotGetKonto();
}

void frmChgKonto::PushButtonGet_returnPressed()
{
    frmChgKonto::PushButtonGet_clicked();
}

