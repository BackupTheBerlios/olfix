/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
/***************************************************************************
                          BYTFTGW  -  description
                             -------------------
		     version 0.2
    begin                : Sön 19 okt 2003
    modified:	: Lör 11 dec 2004
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
#include <qfont.h>
#include <qlistview.h>
#define MAXSTRING 5000

	QProcess* process;
	QString inrad;
	QString errorrad;

	QString foretag;
	QString newforetag;
	QString database;
	QString newdatabase;
	
	void which_database();
	
void frmBytForetag::init()
{
    getDatabase();
    lineEditForetag->setText(foretag);
    lineEditDatabas->setText(database);
}

void frmBytForetag::lineEditNyttForetag_returnPressed()
{
    newforetag=lineEditNyttForetag->text();
    if (newforetag == "99"){
	newdatabase="olfixtst";
    }
    if (newforetag == "01"){
	newdatabase="olfix";
    }
    if (newforetag != "99" and newforetag != "01"){
	newdatabase="olfix";
	newdatabase.append(newforetag);
    }
/*    qDebug("newdatabase= %s        newforetag=%s",newdatabase.latin1(),newforetag.latin1());	*/
    lineEditNyDatabas->setText(newdatabase);
    pushButtonDo->setFocus();
}

void frmBytForetag::pushButtonDo_clicked()
{
    lineEditForetag->setText(newforetag);
    lineEditDatabas->setText(newdatabase);
    setDatabase();
    init();
    pushButtonOK->setFocus();
}

void frmBytForetag::getDatabase()
{
  QString rcfil;
//  QString bibl;
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
	    int i = line.find( QRegExp("DATABASE="), 0 );    // i == 1
	    if ( i == 0){
	    	int l =line.length();
	    	database = line.mid(9,l);
	    }
            lines += line;
	}
    file.close();
   }
/*   qDebug("getDatabase::databas=%s",database.latin1());	*/
   if (database=="olfix"){
       foretag="01";
   }
   if (database=="olfixtst"){
       foretag="99";
   }
   if (database != "olfix" and database != "olfixtst"){
       foretag = database.right(2);
   }
}

void frmBytForetag::setDatabase()
{
    QString command;
    command="sed -e s/DATABASE=";
    command.append(database);
    command.append("/DATABASE=");
    command.append(newdatabase);
    command.append("/ $HOME/.olfixrc > $HOME/olfixtst.txt");
/*    qDebug("command=%s",command.latin1());			*/
    system(command);
    command="mv $HOME/olfixtst.txt $HOME/.olfixrc";
/*    qDebug("command=%s",command.latin1());			*/
    system(command);
}

