/****************************************************************/
/**		ADDBARW					*/
/**		2003-05-28					*/
/**		Ver 0.3                                                                                    */
/**    Modified:	2005-02-28					*/
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
#define VERSION "0.3\n  2005-02-28"
#define MAXSTRING 5000

    QProcess* process;
    QString inrad;
    QString errorrad;	// 2005-02-28
    QString arid;
    QString benamn;
    QString arstart;
    QString arslut;
    QString arlast;		// Låst bokföringsår, default N
    QString beskattar;
    QString senverdat;
    QString vernr;		// Nästa verifikationsnummer, default 1
    QString ktoplan;

    QString hjelpfil;	// 2005-02-28
    
void frmAddBar::init()	// 2005-02-28
{
    LineEditBar->setFocus();
}   

void frmAddBar::slotAddBar()
{
/************************************************************************/
/*	Kontrollera att alla fälten är ifyllda					*/
/************************************************************************/
       if (arid==""){
	QMessageBox::warning( this, "ADDBARW",
                      "Bokföringsår måste fyllas i! \n" );
	LineEditBar->setFocus();
	    }
    if (arstart == ""){
	QMessageBox::warning( this, "ADDBARW",
                      "Startdatum måste fyllas i! \n" );
	LineEditStartdatum->setFocus();
     }
    if (arslut==""){
	QMessageBox::warning( this, "ADDBARW",
                      "Slutdatum måste fyllas i! \n" );
	LineEditSlutdatum->setFocus();
	    }
   if (beskattar==""){
	QMessageBox::warning( this, "ADDBARW",
                      "Beskattningsår måste fyllas i! \n" );
	LineEditBeskattAr->setFocus();
	    }
   if (ktoplan==""){
	QMessageBox::warning( this, "ADDBARW",
                      "Kontoplan måste fyllas i! \n" );
	LineEditKontoplan->setFocus();
	    }

    
    
    
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
/*    if (arid==""){
	QMessageBox::warning( this, "ADDKTOW",
                      "Bokföringsår måste fyllas i! \n" );
	LineEditBar->setFocus();
	    } */
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
/*    if (arstart == ""){
	QMessageBox::warning( this, "ADDBARW",
                      "Startdatum måste fyllas i! \n" );
	LineEditStartdatum->setFocus();
     } */
    LineEditSlutdatum->setFocus();
}

void frmAddBar::LineEditSlutdatum_returnPressed()
{
    arslut=LineEditSlutdatum->text();
/*    if (arslut==""){
	QMessageBox::warning( this, "ADDBARW",
                      "Slutdatum måste fyllas i! \n" );
	LineEditSlutdatum->setFocus();
	    } */
    LineEditBeskattAr->setFocus();
}

void frmAddBar::LineEditBeskattAr_returnPressed()
{
    beskattar=LineEditBeskattAr->text();
/*    if (beskattar==""){
	QMessageBox::warning( this, "ADDBARW",
                      "Beskattningsår måste fyllas i! \n" );
	LineEditBeskattAr->setFocus();
	    } */
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
/*   if (ktoplan==""){
	QMessageBox::warning( this, "ADDBARW",
                      "Kontoplan måste fyllas i! \n" );
	LineEditKontoplan->setFocus();
	    } */
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
	errorrad.append(line);
	errorrad.append("\n");
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
    
//    qDebug("inrad=%s",inrad.latin1());
            i = -1;
            i = errorrad.find( QRegExp("Error:"), 0 );
//	qDebug("frmAddBar-inrad=%s i=%d\n",inrad.latin1(),i);
            if (i == 0) {
		QMessageBox::critical( this, "OLFIX - BARADD",
			"ERROR!\n"+errorrad
		);
	            errorrad="";
		i = -1;
	    }
	j = -1;
	j = inrad.find( QRegExp("OK:"), 0 );
//	qDebug("frmAddBar-inrad=%s j=%d\n",inrad.latin1(),j);
            if ( j != -1 ){
		QMessageBox::information( this, "BARADD - OK!",
			"Databasen updaterad!\n" 
		);
		inrad="";
		j = -1;
	    }
	    
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
	    PushButtonQuit->setFocus();
}

void frmAddBar::slotHelp()
{
	inrad="";
//	errorrad="";

	frmAddBar::readResursFil();		// Hämta path till hjälpfilen
	hjelpfil=hjelpfil+"#NYTTBAR";		// Lägg till position
//	qDebug("hjelpfil=%s",hjelpfil.latin1());
	
	process = new QProcess();
	process->addArgument( "OLFIXHLP" );	// OLFIX program
	process->addArgument(hjelpfil);

	if ( !process->start() ) {
	    // error handling
	    QMessageBox::warning( this, "OLFIX","Kan inte starta OLFIXHLP!\n" );
	}
	LineEditBar->setFocus();
}

void frmAddBar::slotAbout()
{
    QString meddelande;
    meddelande="OLFIX - ADDBARW\n Version: ";
    meddelande.append(VERSION);
	QMessageBox::information( this, "Om BARADD",
				  meddelande
		);
    LineEditBar->setFocus();
}

void frmAddBar::readResursFil()
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
