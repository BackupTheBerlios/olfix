/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                          DSPKTOW  -  description
                             -------------------
		     version 0.1
    begin                : Ons 5 aug 2003
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


void frmDspKonto::LineEditBar_returnPressed()
{
    arid=LineEditBar->text();
    arid=arid.upper();
    LineEditBar->setText(arid);
    if (arid==""){
	QMessageBox::warning( this, "DSPKTOW",
                      "Bokföringsår måste fyllas i! \n" );
	LineEditBar->setFocus();
	    }
    else{
    LineEditKontoNr->setFocus();
    }
}

void frmDspKonto::LineEditKontoNr_returnPressed()
{
    ktonr=LineEditKontoNr->text();
    if (ktonr != ""){
            slotGetKonto();
    }
    else{
	QMessageBox::warning( this, "DSPKTOW",
                      "Kontonummer måste fyllas i! \n" );
	LineEditKontoNr->setFocus();
	    }
}

void frmDspKonto::slotGetKonto()
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
	
	frmDspKonto::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotGetDataOnStderr() ) );
	frmDspKonto::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotGetDataOnStdout() ) );
            frmDspKonto::connect( process, SIGNAL(processExited() ),this, SLOT(slotGetEndOfProcess() ) );	   

	if (arid == "" || ktonr =="" ){
    	    QMessageBox::warning( this, "DSPKTOW",
                      "Ett eller båda av fälten \n Bokföringsår/Kontonummer\n saknas \n" );
	}
	else {
//	    qWarning(" Startar Chgkonto 2");
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/KTODSP!\n");
		QMessageBox::warning( this, "DSPKTOW",
                            "Kan inte starta STYRMAN/KTODSP! \n" );
	    }
	}

}

void frmDspKonto::slotGetEndOfProcess()
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
	QMessageBox::warning( this, "DSPKTOW",
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
    LineEditBar->setFocus();
  }
}



void frmDspKonto::slotGetDataOnStdout()
{
   while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
//	qWarning( "slotGetDataOnStdout: Userid=%s \n", inrad.latin1() );
    }
}

void frmDspKonto::slotGetDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}


void frmDspKonto::PushButtonGet_clicked()
{
    arid=LineEditBar->text();
    arid=arid.upper();
    LineEditBar->setText((arid));
    ktonr=LineEditKontoNr->text();
    LineEditBar->setEnabled(FALSE);
    LineEditKontoNr->setEnabled(FALSE);
    frmDspKonto::slotGetKonto();
}


