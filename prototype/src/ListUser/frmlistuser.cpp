/****************************************************************************
** Form implementation generated from reading ui file 'frmlistuser.ui'
**
** Created: tis mar 25 05:33:19 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "frmlistuser.h"

#include <qvariant.h>
#include <qheader.h>
#include <qlistview.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "frmlistuser.ui.h"

/* 
 *  Constructs a frmListUser which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
frmListUser::frmListUser( QWidget* parent,  const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "frmListUser" );
    resize( 500, 277 ); 
    setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, sizePolicy().hasHeightForWidth() ) );
    setMinimumSize( QSize( 500, 250 ) );
    setMaximumSize( QSize( 500, 280 ) );
    setBaseSize( QSize( 500, 270 ) );
    setCaption( trUtf8( "LSTUSRW Lista användare" ) );
    setIconText( trUtf8( "OLFIX" ) );

    ListView1 = new QListView( this, "ListView1" );
    ListView1->addColumn( trUtf8( "Userid" ) );
    ListView1->addColumn( trUtf8( "Namn" ) );
    ListView1->addColumn( trUtf8( "Avd" ) );
    ListView1->addColumn( trUtf8( "Grupp" ) );
    ListView1->setGeometry( QRect( 90, 10, 401, 261 ) ); 

    PushButtonAgain = new QPushButton( this, "PushButtonAgain" );
    PushButtonAgain->setGeometry( QRect( 10, 205, 71, 31 ) ); 
    PushButtonAgain->setText( trUtf8( "Uppdatera" ) );
    PushButtonAgain->setDefault( TRUE );

    PushButtonSluta = new QPushButton( this, "PushButtonSluta" );
    PushButtonSluta->setGeometry( QRect( 10, 240, 70, 30 ) ); 
    PushButtonSluta->setText( trUtf8( "Sluta" ) );
    PushButtonSluta->setDefault( TRUE );

    // signals and slots connections
    connect( PushButtonSluta, SIGNAL( clicked() ), this, SLOT( close() ) );
    connect( PushButtonAgain, SIGNAL( clicked() ), this, SLOT( slotReloadUser() ) );
    init();
}

/*  
 *  Destroys the object and frees any allocated resources
 */
frmListUser::~frmListUser()
{
    // no need to delete child widgets, Qt does it all for us
}

