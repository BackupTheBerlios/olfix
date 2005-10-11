/****************************************************************/
/**		main.cpp		PLCHGW			*/
/**		Version 0.1					*/
/**				2005-04-25			*/
/**		Modifierad:				*/
/**		Jan Pihlgren	jan@pihlgren.se			*/
/****************************************************************/
/*****************************************************************
 *					                                         *
 *   This program is free software; you can redistribute it and/or modify 	 *
 *   it under the terms of the GNU General Public License as published by        *
 *   the Free Software Foundation; either version 2 of the License, or     	 *
 *   (at your option) any later version.                                   	 *
 *                                                                         	 *
 *********************************************** *****************/

#include <qapplication.h>
#include <qpushbutton.h>
#include <qfont.h>
#include "chgplkuord.h"

#include <qprocess.h>
#include <qmessagebox.h>
#include <qlistbox.h>
#include <qlabel.h>
#include <qstring.h>
#include <qlineedit.h>
#include <qstringlist.h>
#include <qfile.h>
#include <qdir.h>
#include <qregexp.h>

int main( int argc, char* argv[] )
{
  QApplication myapp( argc, argv );

  frmChgPlKundOrder* mywidget = new frmChgPlKundOrder();

  // mywidget->lineEditBestNr->setText(QString(argv[1]));

  QString rcfil;
  QString bibl;
  QStringList lines;
  QString homeDir( QDir::homeDirPath() );
   rcfil.append(homeDir);
   rcfil.append("/.olfixrc");	// configfil
// L�s in config filen h�r
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
	QMessageBox::warning( mywidget, "OLFIX - PRTINKW",
 	"Kan inte hitta filen $HOME/.olfixrc.\n PRTINKW kommer inte att fungera!\n");
	qWarning( "Cannot find the $HOME/.olfixrc file" );
    }
   QDir::setCurrent ( bibl );

  myapp.setMainWidget( mywidget );
  mywidget->show();
  return myapp.exec();
}