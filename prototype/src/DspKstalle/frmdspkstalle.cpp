/****************************************************************************
** Form implementation generated from reading ui file 'frmdspkstalle.ui'
**
** Created: tor mar 20 08:17:11 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "frmdspkstalle.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "frmdspkstalle.ui.h"

/* 
 *  Constructs a frmDspKstalle which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
frmDspKstalle::frmDspKstalle( QWidget* parent,  const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "frmDspKstalle" );
    resize( 396, 190 ); 
    setCaption( trUtf8( "DSPKSTW Visa information för ett kostnadsställe" ) );

    PushButtonQuit = new QPushButton( this, "PushButtonQuit" );
    PushButtonQuit->setGeometry( QRect( 5, 160, 61, 21 ) ); 
    PushButtonQuit->setText( trUtf8( "Sluta" ) );

    TextLabel1 = new QLabel( this, "TextLabel1" );
    TextLabel1->setGeometry( QRect( 5, 10, 76, 21 ) ); 
    TextLabel1->setText( trUtf8( "Bokföringsår:" ) );

    TextLabel2 = new QLabel( this, "TextLabel2" );
    TextLabel2->setGeometry( QRect( 5, 40, 80, 21 ) ); 
    TextLabel2->setText( trUtf8( "Kostnadsställe:" ) );

    TextLabel3 = new QLabel( this, "TextLabel3" );
    TextLabel3->setGeometry( QRect( 5, 70, 69, 21 ) ); 
    TextLabel3->setText( trUtf8( "Benämning:" ) );

    LineEditBar = new QLineEdit( this, "LineEditBar" );
    LineEditBar->setGeometry( QRect( 90, 10, 35, 22 ) ); 

    LineEditBenamn = new QLineEdit( this, "LineEditBenamn" );
    LineEditBenamn->setGeometry( QRect( 90, 70, 300, 22 ) ); 

    LineEditKstalle = new QLineEdit( this, "LineEditKstalle" );
    LineEditKstalle->setGeometry( QRect( 90, 40, 60, 22 ) ); 

    PushButtonGet = new QPushButton( this, "PushButtonGet" );
    PushButtonGet->setGeometry( QRect( 165, 40, 61, 21 ) ); 
    PushButtonGet->setText( trUtf8( "Hämta" ) );
    PushButtonGet->setDefault( TRUE );

    // signals and slots connections
    connect( PushButtonQuit, SIGNAL( clicked() ), this, SLOT( close() ) );
    connect( LineEditBar, SIGNAL( returnPressed() ), PushButtonGet, SLOT( setFocus() ) );
    connect( PushButtonGet, SIGNAL( clicked() ), PushButtonQuit, SLOT( setFocus() ) );
    connect( LineEditBar, SIGNAL( returnPressed() ), this, SLOT( LineEditBar_returnPressed() ) );
    connect( LineEditKstalle, SIGNAL( returnPressed() ), this, SLOT( LineEditKstalle_returnPressed() ) );
    connect( PushButtonGet, SIGNAL( clicked() ), this, SLOT( slotGetKstalle() ) );

    // tab order
    setTabOrder( LineEditBar, LineEditKstalle );
    setTabOrder( LineEditKstalle, PushButtonGet );
    setTabOrder( PushButtonGet, PushButtonQuit );
    setTabOrder( PushButtonQuit, LineEditBenamn );
    init();
}

/*  
 *  Destroys the object and frees any allocated resources
 */
frmDspKstalle::~frmDspKstalle()
{
    // no need to delete child widgets, Qt does it all for us
}

