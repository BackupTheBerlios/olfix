/****************************************************************/
/**		main.cpp		RPTGENW			*/
/**		2003-08-25					*/
/**		Jan Pihlgren	jan@pihlgren.se			*/
/****************************************************************/
/*****************************************************************
 *					                                        *
 *   This program is free software; you can redistribute it and/or modify	*
 *   it under the terms of the GNU General Public License as published by	*
 *   the Free Software Foundation; either version 2 of the License, or		*
 *   (at your option) any later version.                              		*
 *                                                                         	*
 *********************************************** *****************/

#include <qapplication.h>
#include <qpushbutton.h>
#include <qfont.h>
#include "frmrapportgen.h"

#include <qprocess.h>
#include <qmessagebox.h>
#include <qlabel.h>
#include <qlistbox.h>
#include <qstring.h>
#include <qstringlist.h>
#include <qfile.h>
#include <qdir.h>
#include <qlineedit.h>
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
    }else{
	qWarning( "Cannot find the $HOME/.olfixrc file" );
 	fprintf(stdout,"%s\n", rcfil.latin1() );
    }
   QDir::setCurrent ( bibl );

  frmRapportGen RapportGen;

  myapp.setMainWidget( &RapportGen );
  RapportGen.show();
  myapp.exec();
}
