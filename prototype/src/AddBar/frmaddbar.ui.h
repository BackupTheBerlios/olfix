/****************************************************************/
/**		ADDBARW					*/
/**		20003-01-18					*/
/**		Jan Pihlgren	jan@pihlgren.se			*/
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
#include <qregexp.h> 
#define MAXSTRING 5000

    QProcess* process;
    QString inrad;
    QString arid;
    QString benamn;
    QString arstart;
    QString arslut;
    QString arlast;		// Låst bokföringsår, default N
    QString beskattar;
    QString senverdat;
    QString vernr;		// Nästa verifikationsnummer, default 1
    QString ktoplan;

void frmAddBar::slotAddBar()
{
/************************************************************************/
/*	Uppdatera databasen						*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);
	 arlast.append("N");
	 
//	 qDebug("Utgående data\n %s\n %s\n %s\n %s\n %s\n %s\n %s\n %s\n %s\n",arid.latin1(),benamn.latin1(),arstart.latin1(),arslut.latin1(),arlast.latin1(),beskattar.latin1(),senverdat.latin1(),vernr.latin1(),ktoplan.latin1());
		    
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "BARADD");	// OLFIX funktion
	process->addArgument(arid);
	process->addArgument(benamn);
	process->addArgument(arstart);
	process->addArgument(arslut);
	process->addArgument(arlast);
	process->addArgument(beskattar);
	process->addArgument(senverdat);
	process->addArgument(vernr);
	process->addArgument(ktoplan);
	
	frmAddBar::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmAddBar::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
            frmAddBar::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );	   

	if (vernr == ""){
	    vernr.append("1");
	}
//           qWarning(" Startar Addkonto 1");

	if (arid == "" ){
    	    QMessageBox::warning( this, "ADDBARW",
                      "Bokföringsår måste vara ifyllt!" );
	}
	else {
//	    qWarning(" Startar Addkonto 2");
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/BARADD!\n");
		QMessageBox::warning( this, "ADDBARW",
                            "Kan inte starta STYRMAN/BARADD! \n" );
	    }
	}
}

void frmAddBar::LineEditBar_returnPressed()
{
    arid=LineEditBar->text();
    arid=arid.upper();
    LineEditBar->setText((arid));
    if (arid==""){
	QMessageBox::warning( this, "ADDKTOW",
                      "Bokföringsår måste fyllas i! \n" );
	LineEditBar->setFocus();
	    }
    LineEditBenamn->setFocus();
}

void frmAddBar::LineEditBenamn_returnPressed()
{
    benamn=LineEditBenamn->text();
    LineEditStartdatum->setFocus();
}

void frmAddBar::LineEditStartdatum_returnPressed()
{
    arstart=LineEditStartdatum->text();
    if (arstart == ""){
	QMessageBox::warning( this, "ADDBARW",
                      "Startdatum måste fyllas i! \n" );
	LineEditStartdatum->setFocus();
     }
    LineEditSlutdatum->setFocus();
}

void frmAddBar::LineEditSlutdatum_returnPressed()
{
    arslut=LineEditSlutdatum->text();
    if (arslut==""){
	QMessageBox::warning( this, "ADDBARW",
                      "Slutdatum måste fyllas i! \n" );
	LineEditSlutdatum->setFocus();
	    }
    LineEditBeskattAr->setFocus();
}

void frmAddBar::LineEditBeskattAr_returnPressed()
{
    beskattar=LineEditBeskattAr->text();
    if (beskattar==""){
	QMessageBox::warning( this, "ADDBARW",
                      "Beskattningsår måste fyllas i! \n" );
	LineEditBeskattAr->setFocus();
	    }
    LineEditNestaVerNr->setFocus();
}

void frmAddBar::LineEditNestaVerNr_returnPressed()
{
    vernr=LineEditNestaVerNr->text();
    if (vernr==""){
	vernr.append("1");
    }
    LineEditKontoplan->setFocus();
}


void frmAddBar::LineEditKontoplan_returnPressed()
{
    ktoplan=LineEditKontoplan->text();
   if (ktoplan==""){
	QMessageBox::warning( this, "ADDBARW",
                      "Kontoplan måste fyllas i! \n" );
	LineEditKontoplan->setFocus();
	    }
   PushButtonOK->setFocus();
}

void frmAddBar::PushButtonOK_clicked()
{
//    arlast.append("N");
    frmAddBar::slotAddBar();
}


void frmAddBar::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmAddBar::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}


void frmAddBar::slotEndOfProcess()
{
    int i=-1;
    int j=-1;
    
    qDebug("inrad=%s",inrad.latin1());
            i = -1;
            i = inrad.find( QRegExp("Error:"), 0 );
	qDebug("frmAddBar-inrad=%s i=%d\n",inrad.latin1(),i);
            if (i == 0) {
		QMessageBox::critical( this, "OLFIX - BARADD",
			"ERROR!\n"+inrad 
		);
	            inrad="";
		i = -1;
	    }
	j = -1;
	j = inrad.find( QRegExp("BARADD:INSERT error:"), 0 );
            if(j == 0){
		QMessageBox::information( this, "BARADD - Error!",
			"Felaktigt  bokföringsår \n" 
		);
		inrad="";
		j = -1;
	    }
            i = -1;
            i = inrad.find( QRegExp("BARADD:Inserted"), 0 );  
            if(i == 0){
		QMessageBox::information( this, "BARADD",
			"Uppdatering OK!\n" 
		);
	    LineEditBar->clear();
	    LineEditBenamn->clear();
	    LineEditStartdatum->clear();
	    LineEditSlutdatum->clear();
	    LineEditBeskattAr->clear();
//	    LineEditNestaVerNr->clear();
	    LineEditKontoplan->clear();
	    arlast=("");
	    inrad="";
	    i = -1;
    	    }
}
