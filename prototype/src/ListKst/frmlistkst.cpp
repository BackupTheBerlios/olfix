/****************************************************************************
** Form implementation generated from reading ui file 'frmlistkst.ui'
**
** Created: ons mar 19 09:56:05 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "frmlistkst.h"

#include <qvariant.h>
#include <qheader.h>
#include <qlistview.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "frmlistkst.ui.h"

/* 
 *  Constructs a frmListKst which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
frmListKst::frmListKst( QWidget* parent,  const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "frmListKst" );
    resize( 500, 277 ); 
    setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, sizePolicy().hasHeightForWidth() ) );
    setMinimumSize( QSize( 500, 250 ) );
    setMaximumSize( QSize( 500, 280 ) );
    setBaseSize( QSize( 500, 270 ) );
    setCaption( trUtf8( "OLFIX - LSTKSTW. Lista kostnadsställen" ) );
    setIconText( trUtf8( "OLFIX" ) );

    PushButtonSluta = new QPushButton( this, "PushButtonSluta" );
    PushButtonSluta->setGeometry( QRect( 10, 240, 70, 30 ) ); 
    PushButtonSluta->setText( trUtf8( "Sluta" ) );

    ListView1 = new QListView( this, "ListView1" );
    ListView1->addColumn( trUtf8( "Bokf.år" ) );
    ListView1->addColumn( trUtf8( "Kställe" ) );
    ListView1->addColumn( trUtf8( "Benämning" ) );
    ListView1->setGeometry( QRect( 90, 10, 401, 261 ) ); 

    PushButtonAgain = new QPushButton( this, "PushButtonAgain" );
    PushButtonAgain->setGeometry( QRect( 10, 205, 71, 31 ) ); 
    PushButtonAgain->setText( trUtf8( "Uppdatera" ) );

    // signals and slots connections
    connect( PushButtonSluta, SIGNAL( clicked() ), this, SLOT( close() ) );
    connect( PushButtonAgain, SIGNAL( clicked() ), this, SLOT( slotReloadKstalle() ) );
    init();
}

/*  
 *  Destroys the object and frees any allocated resources
 */
frmListKst::~frmListKst()
{
    // no need to delete child widgets, Qt does it all for us
}

