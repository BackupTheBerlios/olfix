/****************************************************************/
/**		main.cpp		OLFIXW				*/
/**		2003-02-05					*/
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
#include <qmessagebox.h>
#include <qdir.h>
#include <qfile.h>
#include <qstring.h>

#include <qapplication.h>
#include <qpushbutton.h>
#include <qfont.h>
#include "frmolfix.h"
#include <qregexp.h>

int main( int argc, char* argv[] )
{
  QApplication myapp( argc, argv );
  
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
//	fprintf(stdout,"Bibliotek=%s\n",bibl.latin1() );
  }else{
      	qWarning( "Cannot find the $HOME/.olfixrc file" );
 	fprintf(stderr,"%s\n", rcfil.latin1() );
  }
  QDir::setCurrent ( bibl );
  
  frmOlfix Olfix;
  
  myapp.setMainWidget( &Olfix );
  Olfix.show();
  myapp.exec();
}
