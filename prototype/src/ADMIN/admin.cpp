/****************************************************************************
** Form implementation generated from reading ui file 'admin.ui'
**
** Created: tis jan 7 07:02:34 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "admin.h"

#include <qvariant.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qaction.h>
#include <qmenubar.h>
#include <qpopupmenu.h>
#include <qtoolbar.h>
#include "admin.ui.h"

/* 
 *  Constructs a ADMIN which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 *
 */
ADMIN::ADMIN( QWidget* parent,  const char* name, WFlags fl )
    : QMainWindow( parent, name, fl )
{
    (void)statusBar();
    if ( !name )
	setName( "ADMIN" );
    resize( 300, 220 ); 
    setMinimumSize( QSize( 21, 64 ) );
    setMaximumSize( QSize( 300, 220 ) );
    setBaseSize( QSize( 300, 220 ) );
    setCaption( trUtf8( "OLFIX Administration" ) );

    // actions
    userAddAction = new QAction( this, "userAddAction" );
    userAddAction->setText( trUtf8( "userAdd" ) );
    userAddAction->setMenuText( trUtf8( "Lägga till användare" ) );
    userChangeAction = new QAction( this, "userChangeAction" );
    userChangeAction->setText( trUtf8( "userChange" ) );
    userChangeAction->setMenuText( trUtf8( "Ändra användare" ) );
    userDeleteAction = new QAction( this, "userDeleteAction" );
    userDeleteAction->setText( trUtf8( "userDelete" ) );
    userDeleteAction->setMenuText( trUtf8( "Ta bort användare" ) );
    userListAction = new QAction( this, "userListAction" );
    userListAction->setText( trUtf8( "userList" ) );
    userListAction->setMenuText( trUtf8( "Lista användare" ) );
    rightAddAction = new QAction( this, "rightAddAction" );
    rightAddAction->setText( trUtf8( "rightAdd" ) );
    rightAddAction->setMenuText( trUtf8( "Lägga till behörighet" ) );
    rightDeleteAction = new QAction( this, "rightDeleteAction" );
    rightDeleteAction->setText( trUtf8( "rightDelete" ) );
    rightDeleteAction->setMenuText( trUtf8( "Ta bort behörighet" ) );
    rightListAction = new QAction( this, "rightListAction" );
    rightListAction->setText( trUtf8( "Lista behörigheter" ) );
    rightListAction->setMenuText( trUtf8( "Lista behörigheter" ) );
    rightListOneUserAction = new QAction( this, "rightListOneUserAction" );
    rightListOneUserAction->setText( trUtf8( "Visa en användares behörighet" ) );
    rightListOneUserAction->setMenuText( trUtf8( "Visa en användares behörighet" ) );


    // toolbars


    // menubar
    menubar = new QMenuBar( this, "menubar" );

    fileMenu = new QPopupMenu( this ); 
    userAddAction->addTo( fileMenu );
    userChangeAction->addTo( fileMenu );
    userListAction->addTo( fileMenu );
    userDeleteAction->addTo( fileMenu );
    fileMenu->insertSeparator();
    fileMenu->insertSeparator();
    menubar->insertItem( trUtf8( "&Användare" ), fileMenu );

    editMenu = new QPopupMenu( this ); 
    rightAddAction->addTo( editMenu );
    editMenu->insertSeparator();
    rightListAction->addTo( editMenu );
    rightListOneUserAction->addTo( editMenu );
    editMenu->insertSeparator();
    rightDeleteAction->addTo( editMenu );
    menubar->insertItem( trUtf8( "&Behörigheter" ), editMenu );



    // signals and slots connections
    connect( userAddAction, SIGNAL( activated() ), this, SLOT( userAddSlot() ) );
    connect( userChangeAction, SIGNAL( activated() ), this, SLOT( userChangeSlot() ) );
    connect( userDeleteAction, SIGNAL( activated() ), this, SLOT( userDeleteSlot() ) );
    connect( userListAction, SIGNAL( activated() ), this, SLOT( userListSlot() ) );
    connect( rightListAction, SIGNAL( activated() ), this, SLOT( rightListSlot() ) );
    connect( rightDeleteAction, SIGNAL( activated() ), this, SLOT( rightDeleteSlot() ) );
    connect( rightAddAction, SIGNAL( activated() ), this, SLOT( rightAddSlot() ) );
}

/*  
 *  Destroys the object and frees any allocated resources
 */
ADMIN::~ADMIN()
{
    // no need to delete child widgets, Qt does it all for us
}

