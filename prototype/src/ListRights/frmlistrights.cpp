/****************************************************************************
** Form implementation generated from reading ui file 'frmlistrights.ui'
**
** Created: tor mar 20 15:14:17 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "frmlistrights.h"

#include <qvariant.h>
#include <qheader.h>
#include <qlistview.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "frmlistrights.ui.h"

/* 
 *  Constructs a frmListRights which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
frmListRights::frmListRights( QWidget* parent,  const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "frmListRights" );
    resize( 290, 278 ); 
    setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, sizePolicy().hasHeightForWidth() ) );
    setMinimumSize( QSize( 250, 250 ) );
    setMaximumSize( QSize( 500, 280 ) );
    setBaseSize( QSize( 500, 270 ) );
    setCaption( trUtf8( "LSTRGTW  Lista behörigheter" ) );

    ListView1 = new QListView( this, "ListView1" );
    ListView1->addColumn( trUtf8( "Userid" ) );
    ListView1->addColumn( trUtf8( "Behörighet" ) );
    ListView1->setGeometry( QRect( 80, 10, 200, 261 ) ); 

    PushButtonAgain = new QPushButton( this, "PushButtonAgain" );
    PushButtonAgain->setGeometry( QRect( 6, 205, 65, 31 ) ); 
    PushButtonAgain->setText( trUtf8( "Uppdatera" ) );

    PushButtonSluta = new QPushButton( this, "PushButtonSluta" );
    PushButtonSluta->setGeometry( QRect( 6, 240, 65, 30 ) ); 
    PushButtonSluta->setText( trUtf8( "Sluta" ) );

    // signals and slots connections
    connect( PushButtonSluta, SIGNAL( clicked() ), this, SLOT( close() ) );
    connect( PushButtonAgain, SIGNAL( clicked() ), this, SLOT( slotReloadRights() ) );
    init();
}

/*  
 *  Destroys the object and frees any allocated resources
 */
frmListRights::~frmListRights()
{
    // no need to delete child widgets, Qt does it all for us
}

