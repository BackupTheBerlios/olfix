/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
/***************************************************************************
                          CHGHOSTW  -  description
                             -------------------
		     version 0.1
    begin                   	: Tors   29 nov      2007
    modified:   	: 
    copyright            	: (C) 2003 by Jan Pihlgren
    email                	: jan@pihlgren.se
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
#include <qfont.h>
#include <qlistview.h>
#define MAXSTRING 5000

	QProcess* process;
	QProcess* proc;
	QString inrad;
	QString errorrad;
	QString* rad;

	QString foretag;
	QString dbnr;
	QString host;
	QString newhost="";
	QString hjelpfil;
	QString usr;
	QString val;		/* Vilken funktion i programmet DATABASE skall exekveras */
	int flag;
	
	
void frmChangeHost::init()
{
    const char *userp = getenv("USER");
    QString usr(userp);
    frmChangeHost::getHost();
    val = "3";			// Lista befintliga databaser utom databasen mysql
    lineEditHost->setText(host);
}

void frmChangeHost::lineEditNyHost_returnPressed()	
{
    newhost=lineEditNyHost->text();
}

void frmChangeHost::getHost()
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
}

void frmChangeHost::setHost()
{
    QString command;
    command="sed -e s/HOST=";
    command.append(host);
    command.append("/HOST=");
    command.append(newhost);
    command.append("/ $HOME/.olfixrc > $HOME/olfixtst.tmp");	
    system(command);
    command="mv $HOME/olfixtst.tmp $HOME/.olfixrc";
    system(command);
    QMessageBox::information( this, "CHGHOST\n","Byte klart!\n");
    pushButtonOK->setFocus();
/*  
    val="2";
    process = new QProcess();
    process->addArgument("./CHGHOSTW"); 
    if ( !process->start() ) {
	// error handling
	    QMessageBox::warning( this, "Kan inte starta OLFIXW!\n","ERROR\n"+errorrad);
	}
    exit(0);
    */
}

void frmChangeHost::slotHelp()
{
	inrad="";
	frmChangeHost::readResursFil();			// Hämta path till hjälpfilen
	
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

void frmChangeHost::readResursFil()
{
    /*****************************************************/
    /*  Läs in .olfixrc filen h�r			                     */
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

void frmChangeHost::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmChangeHost::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

