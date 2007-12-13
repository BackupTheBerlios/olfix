/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                          DELRGTW  -  description
                             -------------------
		     version 0.3
    begin                : Lör    22 febr 2003
    modified           : Tors 13 dec   2007
    copyright         : (C) 2003 by Jan Pihlgren
    email                : jan@pihlgren.se
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
    QProcess* proc;
    QString inrad;
    QString* rad;
    QString errorrad;
    QString userid;
    QString funk;
    QString hjelpfil;
    QString host;

void frmDelRights::init()
{
    getHost();
    LineEditUserid->setFocus();
}

void frmDelRights::slotUseridEntered()
{
    userid=LineEditUserid->text();
    userid=userid.upper();
    LineEditUserid->setText(userid);
}

void frmDelRights::slotTransidEntered()
{
    funk=LineEditTransid->text();
    funk=funk.upper();
    LineEditTransid->setText(funk);
    PushButtonGet->setFocus();
}

void frmDelRights::slotGetRights()
{
	const char *userp = getenv("USER");
                QString usr(userp);
		
//	qDebug("userid=%s och funk=%s",userid.latin1(),funk.latin1());
	
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "RGTCHK");	// OLFIX funktion
	process->addArgument(userid);
	process->addArgument(funk);

	frmDelRights::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotGetDataOnStdout() ) );
	frmDelRights::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotGetDataOnStderr() ) );
                frmDelRights::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfGetProcess() ) );

	if (userid == "" || funk ==""){
    	    QMessageBox::warning( this, "DELRGTW",
                      "Användar-ID och/eller Behörighet saknas! \n" );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		QMessageBox::warning( this, "DELRGTW",
                            "Kan inte starta STYRMAN/RGTCHK! \n" );
	    }   
	}
}

void frmDelRights::slotGetDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmDelRights::slotGetDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmDelRights::slotEndOfGetProcess()
{
       int i = -1;
       i = inrad.find( QRegExp("OK:"), 0 );
       if(i != -1){
	PushButtonOK->setFocus();
       }

      i = -1;
      i = errorrad.find( QRegExp("Error:"), 0 );
      if (i == 0) {
	QMessageBox::critical( this, "OLFIX - RGTCHK",
		"ERROR!\n"+errorrad
		);
	errorrad="";
	i = -1;
	LineEditUserid->clear();
	LineEditTransid->clear();
	PushButtonOK->setFocus();
	userid="";
	funk="";
      }
}

void frmDelRights::slotDelRgt( )
{
	const char *userp = getenv("USER");
                QString usr(userp);
	inrad="";
		
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "RGTDEL");	// OLFIX funktion
	process->addArgument(userid);
	process->addArgument(funk);

	frmDelRights::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDelDataOnStdout() ) );
	frmDelRights::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDelDataOnStderr() ) );
                frmDelRights::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfDelProcess() ) );

	if (userid == "" || funk ==""){
    	    QMessageBox::warning( this, "DELRGTW",
                      "Användar-ID och/eller Behörighet saknas \n" );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		QMessageBox::warning( this, "DELRGTW",
                            "Kan inte starta STYRMAN/RGTDEL! \n" );
	    }   
	}
}

void frmDelRights::slotDelDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmDelRights::slotDelDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmDelRights::slotEndOfDelProcess()
{
       int i = -1;
       i = inrad.find( QRegExp("OK:"), 0 );
       qDebug("i=%d",i);
       if(i != -1){
	QMessageBox::information( this, " RGTDEL",
		"Uppdatering OK!\n" 
		);
	LineEditUserid->clear();
	LineEditTransid->clear();
	userid="";
	funk="";
	inrad="";
	errorrad="";
	LineEditUserid->setFocus();
       }

      i = -1;
      i = errorrad.find( QRegExp("Error:"), 0 );
      if (i == 0) {
	QMessageBox::critical( this, "OLFIX - RGTDEL",
		"ERROR!\n"+errorrad
		);
	errorrad="";
	i = -1;
	LineEditUserid->setFocus();
	userid="";
	funk="";
      }
}

void frmDelRights::getHost()
{
  QString rcfil;
  QStringList lines;
  QString homeDir( QDir::homeDirPath() );
   rcfil.append(homeDir);
   rcfil.append("/.olfixrc");	// configfil
// Läs in config filen här
   QFile file(rcfil);
   if ( file.open( IO_ReadOnly ) ) {
	QTextStream stream( &file );
	QString line;
	while ( !stream.eof() ) {
	    line = stream.readLine(); // line of text excluding '\n'
	    int i = line.find( QRegExp("HOST="), 0 );    // i == 1
	    if ( i == 0){
	    	int l =line.length();
	    	host = line.mid(5,l);
	    }
            lines += line;
	}
    file.close();
   }
       /*                                                   Start     2007-12-13                                         */    
    if(host != "127.0.0.1 "){
	 if(host != "localhost "){
	     textLabel1->setText("<u><b>Host</b></u>\n");
	     textLabelHostName->setText(host);
	 }
    }else{
	textLabel1->setText("");
    }
    /*                                                End         2007-12-13                                         */
}

void frmDelRights::slotHelp()
{
	inrad="";
	frmDelRights::readResursFil();			// Hämta path till hjälpfilen
	
	int i1 = hjelpfil.find( QRegExp(".html"), 0 );
	hjelpfil=hjelpfil.left(i1);
	hjelpfil=hjelpfil+"_DATABASER.html";
	hjelpfil=hjelpfil+"#CHANGEHOST";			// Lägg till position

	proc = new QProcess();
	proc->addArgument( "./OLFIXHLP" );			// OLFIX program
	proc->addArgument(hjelpfil);

	if ( !proc->start() ) {
	    // error handling
	    QMessageBox::warning( this, "OLFIX","Kan inte starta OLFIXHLP!\n" );
	}
}

void frmDelRights::readResursFil()
{
    /*****************************************************/
    /*  Läs in .olfixrc filen här			                     */
    /* Plocka fram var hjälpfilen finns		                     */
    /*****************************************************/

    QStringList lines;
    QString homepath;
    homepath=QDir::homeDirPath();
 
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
	    hjelpfil=(hjelpfil.right(hjelpfil.length() - 9));
	}
            lines += line;
        }
    }
    f1.close();
}
