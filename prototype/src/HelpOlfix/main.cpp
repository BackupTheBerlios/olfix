/****************************************************************************
** $Id: main.cpp,v 1.1 2004/02/20 08:00:07 janpihlgren Exp $
**
** Copyright (C) 1992-2000 Trolltech AS.  All rights reserved.
**
** This file is part of an example program for Qt.  This example
** program may be used, distributed and modified without limitation.
**
**  Modifierad: 2004-02-20	Jan Pihlgren
**  main.cpp	OLFIXHLP
*****************************************************************************/

#include "helpwindow.h"
#include <qapplication.h>
#include <qwindowsstyle.h>
#include <qstylesheet.h>
#include <stdlib.h>
#include <qregexp.h>
#include <qmessagebox.h>


int main( int argc, char ** argv )
{
    QApplication::setColorSpec( QApplication::ManyColor );
    QApplication a(argc, argv);

  QString rcfil;
  QString bibl;
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
            int i = line.find( QRegExp("PATH="), 0 );    // i == 1
	    if ( i == 0){
	    	int l =line.length();
	    	bibl = line.mid(5,l);
	    }
            lines += line;
        }
	file.close();
    }

   QDir::setCurrent ( bibl );

    QString home;
    if (argc > 1) {
        home = argv[1];
    } else {
        home = QString( qInstallPathDocs() ) + "/html/index.html";

        // if $QTDIR is set, use that instead
        const char *qtdirenv = getenv( "QTDIR" );
        if ( qtdirenv ) {
            home = QString( qtdirenv ) + "/doc/html/index.html";
        }
    }

    HelpWindow *help = new HelpWindow(home, ".", 0, "help viewer");
    help->setCaption("OLFIX - Användarmanual");
    if ( QApplication::desktop()->width() > 400
         && QApplication::desktop()->height() > 500 )
        help->show();
    else
        help->showMaximized();

    QObject::connect( &a, SIGNAL(lastWindowClosed()),
                      &a, SLOT(quit()) );

    return a.exec();
}
