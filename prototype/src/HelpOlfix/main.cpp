/****************************************************************************
** $Id: main.cpp,v 1.3 2005/03/12 06:59:33 janpihlgren Exp $
**
** Copyright (C) 1992-2000 Trolltech AS.  All rights reserved.
**
** This file is part of an example program for Qt.  This example
** program may be used, distributed and modified without limitation.
**
**  Modifierad: 2005-03-11	Jan Pihlgren
**  main.cpp	OLFIXHLP
*****************************************************************************/

#include "helpwindow.h"
#include <qapplication.h>
#include <qwindowsstyle.h>
#include <qstylesheet.h>
#include <stdlib.h>
#include <qregexp.h>
#include <qmessagebox.h>

void readResursFil();

QString hjelpfil;

int main( int argc, char ** argv )
{
    QApplication::setColorSpec( QApplication::ManyColor );
    QApplication a(argc, argv);

  QString rcfil;
  QString bibl;
  QStringList lines;
  QString homeDir( QDir::homeDirPath() );
   rcfil.append(homeDir);
   rcfil.append("/.olfixrc");	/*  configfil			*/
   /******************************************************/
   /* Läs in config filen här				               */
   /******************************************************/
   QFile file(rcfil);
   if ( file.open( IO_ReadOnly ) ) {
	QTextStream stream( &file );
	QString line;
        while ( !stream.eof() ) {
            line = stream.readLine(); /*  line of text excluding '\n'	*/
            int i = line.find( QRegExp("PATH="), 0 );    /* i == 1*/
	    if ( i == 0){
	    	int l =line.length();
	    	bibl = line.mid(5,l);
	    }
            lines += line;
        }
	file.close();
    }

   QDir::setCurrent ( bibl );
   readResursFil();
    QString home;
    if (argc > 1) {
        home = argv[1];
    } else {
       home = hjelpfil;
        } 

 QString path;
   path=hjelpfil.left(hjelpfil.length() - 15);
/*  qDebug("path=%s",path.latin1());			*/
/*   qDebug("main::hjelpfil=%s",hjelpfil.latin1());	*/
/*    qDebug("main::home=%s",home.latin1());		*/
 
    HelpWindow *help = new HelpWindow(home, ".", 0, "help viewer");
    help->setCaption("OLFIX - Användarmanual");
    if ( QApplication::desktop()->width() > 500
         && QApplication::desktop()->height() > 500 )
        help->show();
    else
        help->showMaximized();

    QObject::connect( &a, SIGNAL(lastWindowClosed()),
                      &a, SLOT(quit()) );

    return a.exec();
}

void readResursFil()
{
    /*****************************************************/
    /*  Läs in .olfixrc filen här			               */
    /* Plocka fram var hjälpfilen finns				*/
    /******************************************************/

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
