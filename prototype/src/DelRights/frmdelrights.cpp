/****************************************************************************
** Form implementation generated from reading ui file 'frmdelrights.ui'
**
** Created: tor mar 20 08:09:56 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "frmdelrights.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "frmdelrights.ui.h"

/* 
 *  Constructs a frmDelRights which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
frmDelRights::frmDelRights( QWidget* parent,  const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "frmDelRights" );
    resize( 311, 219 ); 
    setCaption( trUtf8( "DELRGTW Ta bort  behörighet" ) );

    TextLabel1 = new QLabel( this, "TextLabel1" );
    TextLabel1->setGeometry( QRect( 10, 10, 79, 21 ) ); 
    TextLabel1->setText( trUtf8( "Användar-ID:" ) );

    TextLabel2 = new QLabel( this, "TextLabel2" );
    TextLabel2->setGeometry( QRect( 10, 40, 69, 21 ) ); 
    TextLabel2->setText( trUtf8( "Behörighet:" ) );

    PushButtonQuit = new QPushButton( this, "PushButtonQuit" );
    PushButtonQuit->setGeometry( QRect( 115, 190, 61, 21 ) ); 
    PushButtonQuit->setText( trUtf8( "Sluta" ) );

    TextLabel6 = new QLabel( this, "TextLabel6" );
    TextLabel6->setGeometry( QRect( 10, 165, 111, 16 ) ); 
    TextLabel6->setText( trUtf8( "Radera behörighet" ) );

    LineEditTransid = new QLineEdit( this, "LineEditTransid" );
    LineEditTransid->setGeometry( QRect( 90, 40, 90, 22 ) ); 

    LineEditUserid = new QLineEdit( this, "LineEditUserid" );
    LineEditUserid->setGeometry( QRect( 90, 10, 90, 22 ) ); 

    PushButtonGet = new QPushButton( this, "PushButtonGet" );
    PushButtonGet->setGeometry( QRect( 195, 40, 71, 21 ) ); 
    PushButtonGet->setText( trUtf8( "Hämta" ) );
    PushButtonGet->setDefault( TRUE );

    PushButtonOK = new QPushButton( this, "PushButtonOK" );
    PushButtonOK->setGeometry( QRect( 5, 190, 61, 21 ) ); 
    PushButtonOK->setText( trUtf8( "OK" ) );
    PushButtonOK->setDefault( TRUE );

    // signals and slots connections
    connect( LineEditUserid, SIGNAL( returnPressed() ), PushButtonGet, SLOT( setFocus() ) );
    connect( LineEditUserid, SIGNAL( returnPressed() ), this, SLOT( slotUseridEntered() ) );
    connect( LineEditTransid, SIGNAL( returnPressed() ), this, SLOT( slotTransidEntered() ) );
    connect( PushButtonGet, SIGNAL( clicked() ), this, SLOT( slotGetRights() ) );
    connect( PushButtonOK, SIGNAL( clicked() ), this, SLOT( slotDelRgt() ) );
    connect( PushButtonQuit, SIGNAL( clicked() ), this, SLOT( close() ) );

    // tab order
    setTabOrder( LineEditUserid, PushButtonGet );
    setTabOrder( PushButtonGet, PushButtonOK );
    setTabOrder( PushButtonOK, PushButtonQuit );
    setTabOrder( PushButtonQuit, LineEditTransid );
    init();
}

/*  
 *  Destroys the object and frees any allocated resources
 */
frmDelRights::~frmDelRights()
{
    // no need to delete child widgets, Qt does it all for us
}

