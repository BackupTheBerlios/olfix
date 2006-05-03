/****************************************************************/
/**		ADDKTOW					*/
/**		2003-01-17				*/
/**	Modifierad 2006-05-03	Jan Pihlgren		*/
/**	Version 0.4.4					*/
/**		Jan Pihlgren	jan@pihlgren.se		*/
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
    QString ktonr;
    QString benamn;
    QString manuell;
    QString momskod;
    QString srunr;
    QString kst;
    QString projekt;
    QString subkonto;
    QString ktoplan;

void frmAddKonto::slotAddKonto()
{
/**************************************************************************/
/*	Uppdatera databasen						 */
/**************************************************************************/
	const char *userp = getenv("USER");
	QString usr(userp);

	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "KTOADD");	// OLFIX funktion
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
	
	frmAddKonto::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmAddKonto::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmAddKonto::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );	   

	if (manuell == ""){
	    manuell.append("J");
	}

	if (arid == "" || ktonr =="" || srunr =="" || ktoplan == "" ){
    	    QMessageBox::warning( this, "ADDKTOW",
                      "Ett eller flera av fälten \n Bokföringsår/Kontonummer/SRUnr/Kontoplan\n saknas \n" );
	    LineEditBar->setFocus();
	}
	else {
//	    qWarning(" Startar Addkonto 2");
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/KTOADD!\n");
		QMessageBox::warning( this, "ADDKTOW",
                            "Kan inte starta STYRMAN/KTOADD! \n" );
	    }
	}
}

void frmAddKonto::LineEditBar_returnPressed()
{
    arid=LineEditBar->text();
    arid=arid.upper();
    LineEditBar->setText((arid));
/*    if (arid==""){
	QMessageBox::warning( this, "ADDKTOW",
                      "Bokföringsår måste fyllas i! \n" );
	LineEditBar->setFocus();
	    }
*/	    
}

void frmAddKonto::LineEditKontoNr_returnPressed()
{
    ktonr=LineEditKontoNr->text();
/*    if (ktonr==""){
	QMessageBox::warning( this, "ADDKTOW",
                      "Kontonummer måste fyllas i! \n" );
	LineEditKontoNr->setFocus();
	    }
*/	    
}

void frmAddKonto::LineEditBenamn_returnPressed()
{
    benamn=LineEditBenamn->text();
}

void frmAddKonto::LineEditManuell_returnPressed()
{
    manuell=LineEditManuell->text();
    if (manuell == ""){
	manuell.append("J");
	LineEditManuell->setText((manuell));
     }
}

void frmAddKonto::LineEditMomskod_returnPressed()
{
    momskod=LineEditMomskod->text();
/*    if (momskod==""){
	QMessageBox::warning( this, "ADDKTOW",
                      "Momskod måste fyllas i! \n" );
	LineEditMomskod->setFocus();
	    }
*/	    
}

void frmAddKonto::LineEditSRU_returnPressed()
{
    srunr=LineEditSRU->text();
/*    if (srunr==""){
	QMessageBox::warning( this, "ADDKTOW",
                      "SRUnummer måste fyllas i! \n" );
	LineEditSRU->setFocus();
	    }    
*/
}

void frmAddKonto::LineEditKst_returnPressed()
{
    kst=LineEditKst->text();
}

void frmAddKonto::LineEditProjekt_returnPressed()
{
    projekt=LineEditProjekt->text();
}

void frmAddKonto::LineEditSubkonto_returnPressed()
{
    subkonto=LineEditSubkonto->text();
}

void frmAddKonto::LineEditKontoplan_returnPressed()
{
    ktoplan=LineEditKontoplan->text();
/*   if (ktoplan==""){
	QMessageBox::warning( this, "ADDKTOW",
                      "Kontoplan måste fyllas i! \n" );
	LineEditKontoplan->setFocus();
	    }
*/	    
}

void frmAddKonto::PushButtonOK_clicked()
{
//    qWarning( "AddKonto: arid=%s  Ktonr=%s  Benamn.=%s  Manuell=%s Momskod=%s SRUnr=%s Kst=%s Projekt=%s Subkonto=%s Kontoplan=%s\n", arid.latin1(),ktonr.latin1() ,benamn.latin1(),manuell.latin1(),momskod.latin1(),srunr.latin1(),kst.latin1(),projekt.latin1(),subkonto.latin1(),ktoplan.latin1());
    
    frmAddKonto::slotAddKonto();
}

void frmAddKonto::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmAddKonto::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmAddKonto::slotEndOfProcess()
{
    int i=-1;
    int j=-1;
    
//    qDebug("inrad=%s",inrad.latin1());
            i = -1;
            i = inrad.find( QRegExp("Error:"), 0 );
//	qDebug("frmAddKonto-inrad=%s i=%d\n",inrad.latin1(),i);
            if (i == 0) {
		QMessageBox::critical( this, "OLFIX - KTOADD",
			"ERROR!\n"+inrad 
		);
	            inrad="";
		i = -1;
	    }
	j = -1;
	j = inrad.find( QRegExp("KTOADD:INSERT error:"), 0 );
            if(j == 0){
		QMessageBox::information( this, "KTOADD - Error!",
			"Felaktig kombination av Bokföringsår och Kontonummer\n" 
		);
		inrad="";
		j = -1;
	    }
            i = -1;
	    i = inrad.find( QRegExp("OK:"), 0 );  
            if(i == 0){
		QMessageBox::information( this, "KTOADD",
			"Uppdatering OK!\n" 
		);
	    LineEditBar->clear();
	    LineEditKontoNr->clear();
	    LineEditBenamn->clear();
	    LineEditManuell->setText("J");
	    LineEditMomskod->clear();
	    LineEditSRU->clear();
	    LineEditKst->clear();
	    LineEditProjekt->clear();
	    LineEditSubkonto->clear();
	    inrad="";
	    i = -1;
    	    }
}
