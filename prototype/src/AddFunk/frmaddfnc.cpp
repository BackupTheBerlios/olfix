/****************************************************************************
** Form implementation generated from reading ui file 'frmaddfnc.ui'
**
** Created: tis jun 3 06:57:41 2003
**      by: The User Interface Compiler ($Id: frmaddfnc.cpp,v 1.2 2003/09/28 05:49:13 janpihlgren Exp $)
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
 *  Constructs a frmAddFnc as a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
frmAddFnc::frmAddFnc( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "frmAddFnc" );

    TextLabel1 = new QLabel( this, "TextLabel1" );
    TextLabel1->setGeometry( QRect( 10, 30, 81, 21 ) );
    TextLabel1->setFrameShape( QLabel::NoFrame );
    TextLabel1->setFrameShadow( QLabel::Plain );

    TextLabel1_2 = new QLabel( this, "TextLabel1_2" );
    TextLabel1_2->setGeometry( QRect( 10, 60, 70, 21 ) );

    LineEditLedtext = new QLineEdit( this, "LineEditLedtext" );
    LineEditLedtext->setGeometry( QRect( 90, 60, 365, 22 ) );

    PushButtonOK = new QPushButton( this, "PushButtonOK" );
    PushButtonOK->setGeometry( QRect( 10, 120, 51, 21 ) );
    PushButtonOK->setDefault( TRUE );

    LineEditFunc = new QLineEdit( this, "LineEditFunc" );
    LineEditFunc->setGeometry( QRect( 91, 30, 80, 22 ) );

    PushButtonQuit = new QPushButton( this, "PushButtonQuit" );
    PushButtonQuit->setGeometry( QRect( 70, 120, 61, 21 ) );
    PushButtonQuit->setDefault( TRUE );
    languageChange();
    resize( QSize(462, 148).expandedTo(minimumSizeHint()) );

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
    connect( LineEditFunc, SIGNAL( lostFocus() ), this, SLOT( slotFuncEntered() ) );
    connect( LineEditLedtext, SIGNAL( lostFocus() ), this, SLOT( slotLedTextEntered() ) );

    // tab order
    setTabOrder( LineEditFunc, LineEditLedtext );
    setTabOrder( LineEditLedtext, PushButtonOK );
    setTabOrder( PushButtonOK, PushButtonQuit );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
frmAddFnc::~frmAddFnc()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void frmAddFnc::languageChange()
{
    setCaption( trUtf8( "ADDFNCW  Lägga upp ny funktion" ) );
    QWhatsThis::add( this, tr( "Version: 0.1\n"
"2003-06-03" ) );
    TextLabel1->setText( tr( "Funktion:" ) );
    TextLabel1_2->setText( tr( "Ledtext:" ) );
    PushButtonOK->setText( tr( "OK" ) );
    PushButtonQuit->setText( tr( "Avsluta" ) );
}

