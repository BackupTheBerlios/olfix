/****************************************************************************
** $Id: helpwindow.cpp,v 1.2 2004/11/07 07:33:45 janpihlgren Exp $
**
** Copyright (C) 1992-2002 Trolltech AS.  All rights reserved.
**
** This file is part of an example program for Qt.  This example
** program may be used, distributed and modified without limitation.
**
** Modifierad: 2004-02-20	Jan Pihlgren
**                      2004-11-07  Jan Pihlgren
**		OLFIXHLP
*****************************************************************************/

#include "helpwindow.h"
#include <qstatusbar.h>
#include <qtextstream.h>
#include <qstylesheet.h>
#include <qapplication.h>
#include <qcombobox.h>
#include <qevent.h>
#include <qfile.h>
#include <qdatastream.h>
#include <qsimplerichtext.h>
#include <ctype.h>
#include <qregexp.h> 

QString helpfile;

HelpWindow::HelpWindow( const QString& home_, const QString& _path,
                        QWidget* parent, const char *name )
    : QMainWindow( parent, name, WDestructiveClose ),
      pathCombo( 0 )
{
    QString binpath;
    binpath=QDir::currentDirPath();
/*    qDebug("helpwindows::Current Path=%s",binpath.latin1());		*/
        
    QString temppath;

    int tmp;
    tmp=binpath.findRev("/",-1);
/*    qDebug("helpwindows::tmp=%d",tmp);				*/
    temppath=binpath.left(tmp);
/*    qDebug("helpwindows::temppath=%s",temppath.latin1());		*/
    QString helpfilepath;
    helpfilepath=temppath+home_;
    
/*    qDebug("helpwindows::helpfilepath=%s",helpfilepath.latin1());	*/

    browser = new QTextBrowser( this );

    browser->mimeSourceFactory()->setFilePath( _path );
/*    qDebug("helpwindows::Path=%s",_path.latin1());			*/
/*    qDebug("helpwindows::Home=%s",home_.latin1());			*/
    browser->setFrameStyle( QFrame::Panel | QFrame::Sunken );
    connect( browser, SIGNAL( sourceChanged(const QString& ) ),
             this, SLOT( sourceChanged( const QString&) ) );

    setCentralWidget( browser );
    if ( !home_.isEmpty() )
	browser->setSource( helpfilepath );
/*    qDebug("Home=%s",home_.latin1());				*/
    connect( browser, SIGNAL( highlighted( const QString&) ),
             statusBar(), SLOT( message( const QString&)) );

    resize( 640,700 );
    browser->setFocus();

}

void HelpWindow::sourceChanged( const QString& url )
{
    if ( !url.isEmpty() && pathCombo ) {
        bool exists = FALSE;
        int i;
        for ( i = 0; i < pathCombo->count(); ++i ) {
            if ( pathCombo->text( i ) == url ) {
                exists = TRUE;
                break;
            }
        }
        if ( !exists ) {
            pathCombo->insertItem( url, 0 );
            pathCombo->setCurrentItem( 0 );
        } else
            pathCombo->setCurrentItem( i );
    }
}

HelpWindow::~HelpWindow()
{
}
