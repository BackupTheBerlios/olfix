/****************************************************************************
** Form implementation generated from reading ui file 'frmdspvaluta.ui'
**
** Created: tor mar 20 08:19:03 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "frmdspvaluta.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "frmdspvaluta.ui.h"

/* 
 *  Constructs a frmDspValuta which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
frmDspValuta::frmDspValuta( QWidget* parent,  const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "frmDspValuta" );
    resize( 356, 190 ); 
    setCaption( trUtf8( "DSPVALW Visa information för en valuta" ) );

    TextLabel1 = new QLabel( this, "TextLabel1" );
    TextLabel1->setGeometry( QRect( 10, 10, 42, 21 ) ); 
    TextLabel1->setText( trUtf8( "Valuta:" ) );

    TextLabel2 = new QLabel( this, "TextLabel2" );
    TextLabel2->setGeometry( QRect( 10, 40, 69, 21 ) ); 
    TextLabel2->setText( trUtf8( "Beteckning:" ) );

    TextLabel3 = new QLabel( this, "TextLabel3" );
    TextLabel3->setGeometry( QRect( 10, 70, 40, 21 ) ); 
    TextLabel3->setText( trUtf8( "Land:" ) );

    TextLabel4 = new QLabel( this, "TextLabel4" );
    TextLabel4->setGeometry( QRect( 10, 100, 41, 21 ) ); 
    TextLabel4->setText( trUtf8( "Köp:" ) );

    TextLabel4_2 = new QLabel( this, "TextLabel4_2" );
    TextLabel4_2->setGeometry( QRect( 10, 130, 41, 21 ) ); 
    TextLabel4_2->setText( trUtf8( "Sälj:" ) );

    PushButtonQuit = new QPushButton( this, "PushButtonQuit" );
    PushButtonQuit->setGeometry( QRect( 5, 160, 61, 21 ) ); 
    PushButtonQuit->setText( trUtf8( "Sluta" ) );

    LineEditBeteck = new QLineEdit( this, "LineEditBeteck" );
    LineEditBeteck->setGeometry( QRect( 80, 40, 221, 22 ) ); 

    LineEditLand = new QLineEdit( this, "LineEditLand" );
    LineEditLand->setGeometry( QRect( 80, 70, 220, 22 ) ); 

    LineEditKop = new QLineEdit( this, "LineEditKop" );
    LineEditKop->setGeometry( QRect( 80, 100, 55, 22 ) ); 

    LineEditSalj = new QLineEdit( this, "LineEditSalj" );
    LineEditSalj->setGeometry( QRect( 80, 130, 55, 22 ) ); 

    LineEditValuta = new QLineEdit( this, "LineEditValuta" );
    LineEditValuta->setGeometry( QRect( 80, 10, 50, 22 ) ); 

    PushButtonGet = new QPushButton( this, "PushButtonGet" );
    PushButtonGet->setGeometry( QRect( 160, 10, 61, 21 ) ); 
    PushButtonGet->setText( trUtf8( "Hämta" ) );
    PushButtonGet->setDefault( TRUE );

    // signals and slots connections
    connect( PushButtonQuit, SIGNAL( clicked() ), this, SLOT( close() ) );
    connect( LineEditValuta, SIGNAL( returnPressed() ), PushButtonGet, SLOT( setFocus() ) );
    connect( PushButtonGet, SIGNAL( clicked() ), PushButtonQuit, SLOT( setFocus() ) );
    connect( LineEditValuta, SIGNAL( returnPressed() ), this, SLOT( LineEditValuta_returnPressed() ) );
    connect( PushButtonGet, SIGNAL( clicked() ), this, SLOT( PushButtonGet_clicked() ) );

    // tab order
    setTabOrder( LineEditValuta, PushButtonGet );
    setTabOrder( PushButtonGet, PushButtonQuit );
    setTabOrder( PushButtonQuit, LineEditBeteck );
    setTabOrder( LineEditBeteck, LineEditKop );
    setTabOrder( LineEditKop, LineEditLand );
    init();
}

/*  
 *  Destroys the object and frees any allocated resources
 */
frmDspValuta::~frmDspValuta()
{
    // no need to delete child widgets, Qt does it all for us
}

