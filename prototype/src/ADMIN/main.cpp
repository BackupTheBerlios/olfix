/****************************************************************/
/**		main.cpp						*/
/**		2002-12-29					*/
/**		Jan Pihlgren	jan@pihlgren.se			*/
/****************************************************************/

#include <qapplication.h>
#include <qpushbutton.h>
#include <qfont.h>
#include "admin.h"

#include <qmessagebox.h>
#include <qdir.h>
#include <qfile.h>
#include <qstring.h>
#include <qregexp.h>

int main( int argc, char* argv[] )
{
  QApplication myapp( argc, argv );

  ADMIN* mywidget = new ADMIN();
  mywidget->setGeometry( 50, 50, 400, 400 );

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
	fprintf(stdout,"Bibliotek=%s\n",bibl.latin1() );
  }else{
	QMessageBox::warning( mywidget, "OLFIX",
 	"Kan inte hitta filen $HOME/.olfixrc.\n OLFIX kommer inte att fungera!\n");

	qWarning( "Kan inte hitta filen $HOME/.olfixrc." );
  }
  QDir::setCurrent ( bibl );


  myapp.setMainWidget( mywidget );
  mywidget->show();
  return myapp.exec();
}
