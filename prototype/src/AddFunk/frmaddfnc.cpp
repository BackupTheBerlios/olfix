/****************************************************************************
** Form implementation generated from reading ui file 'frmaddfnc.ui'
**
** Created: ons apr 2 07:08:01 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "frmaddfnc.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "frmaddfnc.ui.h"

/* 
 *  Constructs a frmAddFnc which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
frmAddFnc::frmAddFnc( QWidget* parent,  const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "frmAddFnc" );
    resize( 462, 148 ); 
    setCaption( trUtf8( "ADDFNCW  Lägga upp ny funktion" ) );

    TextLabel1 = new QLabel( this, "TextLabel1" );
    TextLabel1->setGeometry( QRect( 10, 30, 81, 21 ) ); 
    TextLabel1->setFrameShape( QLabel::NoFrame );
    TextLabel1->setFrameShadow( QLabel::Plain );
    TextLabel1->setText( trUtf8( "Funktion:" ) );

    TextLabel1_2 = new QLabel( this, "TextLabel1_2" );
    TextLabel1_2->setGeometry( QRect( 10, 60, 70, 21 ) ); 
    TextLabel1_2->setText( trUtf8( "Ledtext:" ) );

    LineEditLedtext = new QLineEdit( this, "LineEditLedtext" );
    LineEditLedtext->setGeometry( QRect( 90, 60, 365, 22 ) ); 

    PushButtonOK = new QPushButton( this, "PushButtonOK" );
    PushButtonOK->setGeometry( QRect( 10, 120, 51, 21 ) ); 
    PushButtonOK->setText( trUtf8( "OK" ) );
    PushButtonOK->setDefault( TRUE );

    LineEditFunc = new QLineEdit( this, "LineEditFunc" );
    LineEditFunc->setGeometry( QRect( 91, 30, 80, 22 ) ); 

    PushButtonQuit = new QPushButton( this, "PushButtonQuit" );
    PushButtonQuit->setGeometry( QRect( 70, 120, 61, 21 ) ); 
    PushButtonQuit->setText( trUtf8( "Avsluta" ) );
    PushButtonQuit->setDefault( TRUE );

    // signals and slots connections
    connect( LineEditFunc, SIGNAL( returnPressed() ), LineEditLedtext, SLOT( setFocus() ) );
    connect( LineEditLedtext, SIGNAL( returnPressed() ), PushButtonOK, SLOT( setFocus() ) );
    connect( PushButtonOK, SIGNAL( clicked() ), LineEditLedtext, SLOT( clear() ) );
    connect( PushButtonOK, SIGNAL( clicked() ), LineEditFunc, SLOT( setFocus() ) );
    connect( PushButtonOK, SIGNAL( clicked() ), LineEditFunc, SLOT( clear() ) );
    connect( PushButtonOK, SIGNAL( clicked() ), this, SLOT( slotAddFnc() ) );
    connect( PushButtonQuit, SIGNAL( clicked() ), this, SLOT( close() ) );
    connect( LineEditFunc, SIGNAL( returnPressed() ), this, SLOT( slotFuncEntered() ) );
    connect( LineEditLedtext, SIGNAL( returnPressed() ), this, SLOT( slotLedTextEntered() ) );
    init();
}

/*  
 *  Destroys the object and frees any allocated resources
 */
frmAddFnc::~frmAddFnc()
{
    // no need to delete child widgets, Qt does it all for us
}

