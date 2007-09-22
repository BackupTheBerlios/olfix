/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
/***************************************************************************
                          ADDPKDW  -  description
                             -------------------
		     version 0.2
    begin                : Mån 29 november 2004
    Modified         :  Mån 18 juni           2007
    copyright            : (C) 2004 by Jan Pihlgren
    email                : jan@pihlgren.se
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
#include <qprocess.h>
#include <qdir.h>
#include <stdlib.h>
#include <qstring.h>
#include <qfile.h>
#include <qregexp.h>
#include <qvalidator.h> 		// 2003-10-21
#define MAXSTRING 5000


    QProcess* process;
    QString inrad;
    QString* rad;
    QString errorrad;
    QString hjelpfil;

    QString prodkodnr;
    QString beskrivning="";

void frmAddProdkod::lineEditProduktkod_returnPressed()
{
    prodkodnr=lineEditProduktkod->text();
    lineEditBeskrivning->setFocus();
}

void frmAddProdkod::lineEditBeskrivning_returnPressed()
{
    beskrivning=lineEditBeskrivning->text();
    pushButtonOK->setFocus();
}


void frmAddProdkod::pushButtonOK_clicked()
{
    int status=0;
    if (prodkodnr == "" ){
	QMessageBox::warning( this, "ADDPKDW","Produktkod måste fyllas i! \n" );
	status=-1;
	lineEditProduktkod->setFocus();
    }
  if (status==0){
//    qDebug("pushButtonOK_clicked::prodkodnr=%s",prodkodnr.latin1());
      slotAddProduktkod();
  }
}

void frmAddProdkod::slotAddProduktkod()
{
   /************************************************************************/
/*	Uppdatera databasen						*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);
	   	    
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// Userid
	process->addArgument( "PKDADD");	// OLFIX funktion
	process->addArgument(prodkodnr);
	process->addArgument(beskrivning);
	
	frmAddProdkod::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmAddProdkod::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmAddProdkod::connect( process, SIGNAL(processExited() ),this, SLOT(slotPKodEndOfProcess() ) );
 
	
	if (prodkodnr == "") {
    	    QMessageBox::warning( this, "ADDPKDW","Produktkod saknas! \n" );
	}else {
	    if ( !process->start() ) {
		// error handling
		QMessageBox::warning( this, "ADDPKDW",
                            "Kan inte starta STYRMAN/PKDADD! \n" );
	    }   
	}
}

void frmAddProdkod::slotPKodEndOfProcess()
{
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "ADDPKDW",
		"ERROR!\n"+errorrad
	);
     }
     i = -1;
     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	QMessageBox::information( this, "ADDPKDW",
		"Uppdatering OK!\n"+errorrad
	);
	lineEditProduktkod->clear();
	lineEditBeskrivning->clear();
	fprintf(stdout,"OK: \n ");
    }
     errorrad="";
     inrad="";
     lineEditProduktkod->setFocus();
}

void frmAddProdkod::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
    qDebug("inrad=%s",inrad.latin1());
}

void frmAddProdkod::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmAddProdkod::pushButtonHelp_clicked()
{
    	inrad="";				// töm inputbuffer
	frmAddProdkod::readResursFil();		// Hämta path till hjälpfilen
	int i1 = hjelpfil.find( QRegExp(".html"), 0 );
	hjelpfil=hjelpfil.left(i1);
	hjelpfil=hjelpfil+"_ARTIKLAR.html";
	hjelpfil=hjelpfil+"#BEGREPP03";		// Lägg till position

	process = new QProcess();
	process->addArgument( "./OLFIXHLP");	// OLFIX funktion
	process->addArgument(hjelpfil);
	
	frmAddProdkod::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmAddProdkod::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmAddProdkod::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );	    
 
	if ( !process->start() ) {
                // error handling
	    QMessageBox::warning( this, "Start av ADDKUW ", "Kan inte starta OLFIXHLP!\n" );
	}
	lineEditProduktkod->setFocus();
}

void frmAddProdkod::readResursFil()
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
