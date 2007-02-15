/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                          ADDTXTW  -  description
                             -------------------
		     version 0.3
    begin                : Ons  2  april 2003
    modified           :Tors 15 febr 2007
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
#include <qwhatsthis.h> 
#define MAXSTRING 5000
#define VERSION "Version: 0.3\n 2007-02-15"

    QProcess* process;
    QProcess* proc;
    QProcess* proc2;   
    QString inrad;
    QString errorrad;
    QString* rad;
    QString textnr;
    QString text;
    QString hjelpfil;    
    
void frmAddTxt::init()
{
    LineEditTextNr->clear();
    textEditText->clear();
    LineEditTextNr->setFocus();
}
   
void frmAddTxt::slotTextNr_returnPressed()
{
    textnr=LineEditTextNr->text();
    textnr = textnr.stripWhiteSpace();
    frmAddTxt::checkTextnr(textnr);
    textEditText->setFocus();
}


void frmAddTxt::textEditText_Changed()
{
     text=textEditText->text();
}

void frmAddTxt::slotAddTxt()
{
/************************************************************************/
/*	Uppdatera databasen						*/
/************************************************************************/
	const char *userp = getenv("USER");
	QString usr(userp);
	   
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// Userid
	process->addArgument( "TXTADD");	// OLFIX funktion
	process->addArgument(textnr);
	process->addArgument(text);
	
	frmAddTxt::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmAddTxt::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
                frmAddTxt::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );
 
	
	if (textnr == "") {
    	    QMessageBox::warning( this, "ADDTXTW","Textnr saknas! \n" );
	}else {
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/TXTADD!\n");
		QMessageBox::warning( this, "ADDTXTW",
                            "Kan inte starta STYRMAN/TXTADD! \n" );
	    }   
	}
}

void frmAddTxt::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
//	qWarning( "slotDataOnStdout: Userid=%s \n", inrad.latin1() );
    }
}

void frmAddTxt::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
//	qWarning( "slotDataOnErrout: Userid=%s \n", inrad.latin1() );
    }

}

void frmAddTxt::slotEndOfProcess()
{
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "ADDTXTW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
     }
     i = -1;
     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	QMessageBox::information( this, "ADDTXTW",
		"Uppdatering OK!\n"+errorrad
	);
	LineEditTextNr->clear();
	textEditText->clear();
	LineEditTextNr->setFocus();
	inrad="";
	i = -1;
     }
}

void frmAddTxt::TestText()
{
    frmAddTxt::slotAddTxt();
//    qDebug("Text=%s",text.latin1());
}

void frmAddTxt::slotHelp()
{
	inrad="";
	frmAddTxt::readResursFil();			// Hämta path till hjälpfilen
	
	int i1 = hjelpfil.find( QRegExp(".html"), 0 );
	hjelpfil=hjelpfil.left(i1);
	hjelpfil=hjelpfil+"_FTGADMIN.html";
	hjelpfil=hjelpfil+"#NYATEXTER";			// Lägg till position
/*	qDebug("hjelpfil=%s",hjelpfil.latin1());	*/

	proc = new QProcess();
	proc->addArgument( "./OLFIXHLP" );			// OLFIX program
	proc->addArgument(hjelpfil);

	if ( !proc->start() ) {
	    // error handling
	    QMessageBox::warning( this, "OLFIX","Kan inte starta OLFIXHLP!\n" );
	}
}

void frmAddTxt::readResursFil()
{
    /*****************************************************/
    /*  Läs in .olfixrc filen här			            	*/
    /* Plocka fram var hjälpfilen finns			*/
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

void frmAddTxt::checkTextnr(QString txtnr)
{
 /************************************************************************/
/*	Kontroll om angivet textnr finns.  				                  */
/************************************************************************/
   
	const char *userp = getenv("USER");
	QString usr(userp);
	inrad="";
	
	proc2 = new QProcess();
	proc2->addArgument("./STYRMAN");	// OLFIX styrprogram
	proc2->addArgument(usr);		// Userid
	proc2->addArgument( "TXTDSP");	// OLFIX funktion
	proc2->addArgument(txtnr);
//	qDebug("Start process:txtnr=%s",txtnr.latin1());
	
	frmAddTxt::connect( proc2, SIGNAL(readyReadStdout() ),this, SLOT(slotCheckDataOnStdout() ) );
	frmAddTxt::connect( proc2, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmAddTxt::connect( proc2, SIGNAL(processExited() ),this, SLOT(slotCheckEndOfProcess() ) ); 
	
	if ( !proc2->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/TXTADD!\n");
		QMessageBox::warning( this, "ADDTXTW",
                            "Kan inte starta STYRMAN/TXTADD! \n" );
	}   
}

void frmAddTxt::slotCheckEndOfProcess()
{
    int i;
    i = -1;
//    qDebug("Endofprocess");
     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	QMessageBox::warning( this, "ADDTXTW",
		"Textnr finn redan!\n"
	);
	LineEditTextNr->setFocus();
	LineEditTextNr->selectAll();
   }
}

void frmAddTxt::slotCheckDataOnStdout()
{
    while (proc2->canReadLineStdout() ) {
	QString line = proc2->readStdout();
	inrad.append(line);
	inrad.append("\n");
//	qWarning( "slotDataOnStdout: Userid=%s \n", inrad.latin1() );
    }
}
