/****************************************************************************
** Form implementation generated from reading ui file 'frmaddright.ui'
**
** Created: tis mar 25 16:09:38 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "frmaddright.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "frmaddright.ui.h"

/* 
 *  Constructs a frmAddRight which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
frmAddRight::frmAddRight( QWidget* parent,  const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "frmAddRight" );
    resize( 319, 148 ); 
    setCaption( trUtf8( "ADDRGTW  Lägga upp ny behörighet" ) );

    TextLabel1 = new QLabel( this, "TextLabel1" );
    TextLabel1->setGeometry( QRect( 10, 30, 81, 21 ) ); 
    TextLabel1->setFrameShape( QLabel::NoFrame );
    TextLabel1->setFrameShadow( QLabel::Plain );
    TextLabel1->setText( trUtf8( "Användar-ID:" ) );

    PushButtonQuit = new QPushButton( this, "PushButtonQuit" );
    PushButtonQuit->setGeometry( QRect( 70, 120, 61, 21 ) ); 
    PushButtonQuit->setText( trUtf8( "Avsluta" ) );

    TextLabel1_2 = new QLabel( this, "TextLabel1_2" );
    TextLabel1_2->setGeometry( QRect( 10, 60, 70, 21 ) ); 
    TextLabel1_2->setText( trUtf8( "Behörighet:" ) );

    LineEditFunk = new QLineEdit( this, "LineEditFunk" );
    LineEditFunk->setGeometry( QRect( 90, 60, 80, 22 ) ); 

    PushButtonOK = new QPushButton( this, "PushButtonOK" );
    PushButtonOK->setGeometry( QRect( 10, 120, 51, 21 ) ); 
    PushButtonOK->setText( trUtf8( "OK" ) );
    PushButtonOK->setDefault( TRUE );

    LineEditUserid = new QLineEdit( this, "LineEditUserid" );
    LineEditUserid->setGeometry( QRect( 91, 30, 80, 22 ) ); 

    // signals and slots connections
    connect( PushButtonQuit, SIGNAL( clicked() ), this, SLOT( close() ) );
    connect( PushButtonOK, SIGNAL( clicked() ), this, SLOT( slotAddRight() ) );
    connect( LineEditUserid, SIGNAL( returnPressed() ), LineEditFunk, SLOT( setFocus() ) );
    connect( LineEditFunk, SIGNAL( returnPressed() ), PushButtonOK, SLOT( setFocus() ) );
    connect( LineEditFunk, SIGNAL( returnPressed() ), this, SLOT( slotRightEntered() ) );
    connect( PushButtonOK, SIGNAL( clicked() ), LineEditFunk, SLOT( clear() ) );
    connect( PushButtonOK, SIGNAL( clicked() ), LineEditUserid, SLOT( setFocus() ) );
    connect( PushButtonOK, SIGNAL( clicked() ), LineEditUserid, SLOT( clear() ) );
    connect( LineEditUserid, SIGNAL( returnPressed() ), this, SLOT( slotUseridEntered() ) );
    init();
}

/*  
 *  Destroys the object and frees any allocated resources
 */
frmAddRight::~frmAddRight()
{
    // no need to delete child widgets, Qt does it all for us
}

