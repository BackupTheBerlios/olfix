/****************************************************************************
** Form implementation generated from reading ui file 'frmdelvaluta.ui'
**
** Created: tor mar 20 08:13:28 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "frmdelvaluta.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "frmdelvaluta.ui.h"

/* 
 *  Constructs a frmDelValuta which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
frmDelValuta::frmDelValuta( QWidget* parent,  const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "frmDelValuta" );
    resize( 311, 219 ); 
    setCaption( trUtf8( "DELVALW Ta bort  en valuta" ) );

    TextLabel1 = new QLabel( this, "TextLabel1" );
    TextLabel1->setGeometry( QRect( 10, 10, 42, 21 ) ); 
    TextLabel1->setText( trUtf8( "Valuta:" ) );

    TextLabel3 = new QLabel( this, "TextLabel3" );
    TextLabel3->setGeometry( QRect( 10, 70, 40, 21 ) ); 
    TextLabel3->setText( trUtf8( "Land:" ) );

    TextLabel4 = new QLabel( this, "TextLabel4" );
    TextLabel4->setGeometry( QRect( 10, 100, 41, 21 ) ); 
    TextLabel4->setText( trUtf8( "Köp:" ) );

    TextLabel5 = new QLabel( this, "TextLabel5" );
    TextLabel5->setGeometry( QRect( 10, 130, 41, 21 ) ); 
    TextLabel5->setText( trUtf8( "Sälj:" ) );

    TextLabel6 = new QLabel( this, "TextLabel6" );
    TextLabel6->setGeometry( QRect( 10, 165, 111, 16 ) ); 
    TextLabel6->setText( trUtf8( "Radera valuta" ) );

    PushButtonQuit = new QPushButton( this, "PushButtonQuit" );
    PushButtonQuit->setGeometry( QRect( 85, 190, 61, 21 ) ); 
    PushButtonQuit->setText( trUtf8( "Sluta" ) );

    TextLabel2 = new QLabel( this, "TextLabel2" );
    TextLabel2->setGeometry( QRect( 10, 40, 69, 21 ) ); 
    TextLabel2->setText( trUtf8( "Beteckning:" ) );

    LineEditBeteck = new QLineEdit( this, "LineEditBeteck" );
    LineEditBeteck->setGeometry( QRect( 85, 40, 165, 22 ) ); 

    LineEditLand = new QLineEdit( this, "LineEditLand" );
    LineEditLand->setGeometry( QRect( 85, 70, 220, 22 ) ); 

    LineEditValuta = new QLineEdit( this, "LineEditValuta" );
    LineEditValuta->setGeometry( QRect( 85, 10, 40, 22 ) ); 

    LineEditSalj = new QLineEdit( this, "LineEditSalj" );
    LineEditSalj->setGeometry( QRect( 85, 130, 55, 22 ) ); 

    LineEditKop = new QLineEdit( this, "LineEditKop" );
    LineEditKop->setGeometry( QRect( 85, 100, 55, 22 ) ); 

    PushButtonGet = new QPushButton( this, "PushButtonGet" );
    PushButtonGet->setGeometry( QRect( 140, 10, 71, 21 ) ); 
    PushButtonGet->setText( trUtf8( "Hämta" ) );
    PushButtonGet->setDefault( TRUE );

    PushButtonOK = new QPushButton( this, "PushButtonOK" );
    PushButtonOK->setGeometry( QRect( 10, 190, 61, 21 ) ); 
    PushButtonOK->setText( trUtf8( "OK" ) );
    PushButtonOK->setDefault( TRUE );

    // signals and slots connections
    connect( PushButtonQuit, SIGNAL( clicked() ), this, SLOT( close() ) );
    connect( LineEditValuta, SIGNAL( returnPressed() ), PushButtonGet, SLOT( setFocus() ) );
    connect( PushButtonGet, SIGNAL( clicked() ), this, SLOT( slotPushButtonGet_clicked() ) );
    connect( LineEditValuta, SIGNAL( returnPressed() ), this, SLOT( slotValutaEntered() ) );
    connect( PushButtonOK, SIGNAL( clicked() ), this, SLOT( slotPushButtonOK_clicked() ) );

    // tab order
    setTabOrder( LineEditValuta, PushButtonGet );
    setTabOrder( PushButtonGet, PushButtonOK );
    setTabOrder( PushButtonOK, PushButtonQuit );
    setTabOrder( PushButtonQuit, LineEditBeteck );
    setTabOrder( LineEditBeteck, LineEditLand );
    setTabOrder( LineEditLand, LineEditKop );
    setTabOrder( LineEditKop, LineEditSalj );
    init();
}

/*  
 *  Destroys the object and frees any allocated resources
 */
frmDelValuta::~frmDelValuta()
{
    // no need to delete child widgets, Qt does it all for us
}

