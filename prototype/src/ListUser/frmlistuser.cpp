/****************************************************************************
** Form implementation generated from reading ui file 'frmlistuser.ui'
**
** Created: tis maj 27 06:52:03 2003
**      by: The User Interface Compiler ($Id: frmlistuser.cpp,v 1.2 2003/09/28 08:27:53 janpihlgren Exp $)
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
 *  Constructs a frmListUser as a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
frmListUser::frmListUser( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "frmListUser" );
    setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, sizePolicy().hasHeightForWidth() ) );
    setMinimumSize( QSize( 500, 250 ) );
    setMaximumSize( QSize( 500, 280 ) );
    setBaseSize( QSize( 500, 270 ) );
    QFont f( font() );
    f.setFamily( "Helvetica" );
    f.setPointSize( 10 );
    setFont( f ); 

    PushButtonSluta = new QPushButton( this, "PushButtonSluta" );
    PushButtonSluta->setGeometry( QRect( 10, 240, 70, 30 ) );
    PushButtonSluta->setDefault( TRUE );

    PushButtonAgain = new QPushButton( this, "PushButtonAgain" );
    PushButtonAgain->setGeometry( QRect( 10, 205, 71, 31 ) );
    PushButtonAgain->setDefault( TRUE );

    ListView1 = new QListView( this, "ListView1" );
    ListView1->addColumn( tr( "Userid" ) );
    ListView1->addColumn( tr( "Namn" ) );
    ListView1->addColumn( tr( "Avd" ) );
    ListView1->addColumn( tr( "Grupp" ) );
    ListView1->setGeometry( QRect( 90, 10, 401, 261 ) );
    languageChange();
    resize( QSize(500, 277).expandedTo(minimumSizeHint()) );

    // signals and slots connections
    connect( PushButtonSluta, SIGNAL( clicked() ), this, SLOT( close() ) );
    connect( PushButtonAgain, SIGNAL( clicked() ), this, SLOT( slotReloadUser() ) );

    // tab order
    setTabOrder( PushButtonAgain, PushButtonSluta );
    setTabOrder( PushButtonSluta, ListView1 );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
frmListUser::~frmListUser()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void frmListUser::languageChange()
{
    setCaption( trUtf8( "LSTUSRW Lista användare" ) );
    setIconText( tr( "OLFIX" ) );
    PushButtonSluta->setText( tr( "Sluta" ) );
    PushButtonAgain->setText( tr( "Uppdatera" ) );
    ListView1->header()->setLabel( 0, tr( "Userid" ) );
    ListView1->header()->setLabel( 1, tr( "Namn" ) );
    ListView1->header()->setLabel( 2, tr( "Avd" ) );
    ListView1->header()->setLabel( 3, tr( "Grupp" ) );
}

