/****************************************************************************
** Form implementation generated from reading ui file 'frmdelusr.ui'
**
** Created: tor mar 20 08:11:40 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "frmdelusr.h"

#include <qvariant.h>
#include <qheader.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qlistview.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "frmdelusr.ui.h"

/* 
 *  Constructs a frmDelUsr which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
frmDelUsr::frmDelUsr( QWidget* parent,  const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "frmDelUsr" );
    resize( 508, 265 ); 
    setCaption( trUtf8( "DELUSRW Ta bort  en användare och dennes behörigheter" ) );

    TextLabel1 = new QLabel( this, "TextLabel1" );
    TextLabel1->setGeometry( QRect( 10, 10, 42, 21 ) ); 
    TextLabel1->setText( trUtf8( "UserId:" ) );

    TextLabel2 = new QLabel( this, "TextLabel2" );
    TextLabel2->setGeometry( QRect( 10, 40, 40, 21 ) ); 
    TextLabel2->setText( trUtf8( "Namn:" ) );

    TextLabel3 = new QLabel( this, "TextLabel3" );
    TextLabel3->setGeometry( QRect( 10, 70, 40, 21 ) ); 
    TextLabel3->setText( trUtf8( "Avd:" ) );

    TextLabel4 = new QLabel( this, "TextLabel4" );
    TextLabel4->setGeometry( QRect( 10, 100, 41, 21 ) ); 
    TextLabel4->setText( trUtf8( "Grupp:" ) );

    TextLabel5 = new QLabel( this, "TextLabel5" );
    TextLabel5->setGeometry( QRect( 380, 10, 80, 20 ) ); 
    TextLabel5->setText( trUtf8( "Behörigheter" ) );

    LineEditNamn = new QLineEdit( this, "LineEditNamn" );
    LineEditNamn->setGeometry( QRect( 60, 40, 221, 22 ) ); 

    LineEditAvd = new QLineEdit( this, "LineEditAvd" );
    LineEditAvd->setGeometry( QRect( 60, 70, 220, 22 ) ); 

    LineEditGrupp = new QLineEdit( this, "LineEditGrupp" );
    LineEditGrupp->setGeometry( QRect( 60, 100, 121, 22 ) ); 

    TextLabel1_2 = new QLabel( this, "TextLabel1_2" );
    TextLabel1_2->setGeometry( QRect( 10, 210, 111, 16 ) ); 
    TextLabel1_2->setText( trUtf8( "Radera användare" ) );

    PushButtonQuit = new QPushButton( this, "PushButtonQuit" );
    PushButtonQuit->setGeometry( QRect( 160, 230, 61, 21 ) ); 
    PushButtonQuit->setText( trUtf8( "Sluta" ) );

    LineEditUserid = new QLineEdit( this, "LineEditUserid" );
    LineEditUserid->setGeometry( QRect( 60, 10, 61, 22 ) ); 

    ListViewBehor = new QListView( this, "ListViewBehor" );
    ListViewBehor->addColumn( trUtf8( "Userid" ) );
    ListViewBehor->addColumn( trUtf8( "Behörighet" ) );
    ListViewBehor->setGeometry( QRect( 351, 31, 140, 220 ) ); 

    PushButtonGet = new QPushButton( this, "PushButtonGet" );
    PushButtonGet->setGeometry( QRect( 150, 10, 71, 21 ) ); 
    PushButtonGet->setText( trUtf8( "Hämta" ) );
    PushButtonGet->setDefault( TRUE );

    PushButtonOK = new QPushButton( this, "PushButtonOK" );
    PushButtonOK->setGeometry( QRect( 30, 230, 61, 21 ) ); 
    PushButtonOK->setText( trUtf8( "OK" ) );
    PushButtonOK->setDefault( TRUE );

    // signals and slots connections
    connect( PushButtonQuit, SIGNAL( clicked() ), this, SLOT( close() ) );
    connect( LineEditUserid, SIGNAL( returnPressed() ), this, SLOT( slotUseridEntered() ) );
    connect( PushButtonOK, SIGNAL( clicked() ), this, SLOT( slotPushButtonOK_clicked() ) );
    connect( PushButtonGet, SIGNAL( clicked() ), this, SLOT( slotPushButtonGet_clicked() ) );
    connect( LineEditUserid, SIGNAL( returnPressed() ), PushButtonGet, SLOT( setFocus() ) );

    // tab order
    setTabOrder( LineEditUserid, PushButtonGet );
    setTabOrder( PushButtonGet, PushButtonOK );
    setTabOrder( PushButtonOK, PushButtonQuit );
    setTabOrder( PushButtonQuit, LineEditNamn );
    setTabOrder( LineEditNamn, LineEditGrupp );
    setTabOrder( LineEditGrupp, LineEditAvd );
}

/*  
 *  Destroys the object and frees any allocated resources
 */
frmDelUsr::~frmDelUsr()
{
    // no need to delete child widgets, Qt does it all for us
}

