/****************************************************************************
** Form implementation generated from reading ui file 'frmaddkstalle.ui'
**
** Created: tor mar 20 07:53:40 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "frmaddkstalle.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "frmaddkstalle.ui.h"

/* 
 *  Constructs a frmAddKstalle which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
frmAddKstalle::frmAddKstalle( QWidget* parent,  const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "frmAddKstalle" );
    resize( 423, 152 ); 
    setCaption( trUtf8( "OLFIX - ADDKSTW  Lägga upp nytt kostnadsställe" ) );

    TextLabelArid = new QLabel( this, "TextLabelArid" );
    TextLabelArid->setGeometry( QRect( 10, 30, 81, 21 ) ); 
    TextLabelArid->setText( trUtf8( "Bokföringsår:" ) );

    TextLabelKstalle = new QLabel( this, "TextLabelKstalle" );
    TextLabelKstalle->setGeometry( QRect( 10, 60, 87, 21 ) ); 
    TextLabelKstalle->setText( trUtf8( "Kostnadsställe:" ) );

    TextLabelBenamn = new QLabel( this, "TextLabelBenamn" );
    TextLabelBenamn->setGeometry( QRect( 10, 90, 70, 21 ) ); 
    TextLabelBenamn->setText( trUtf8( "Benämning:" ) );

    PushButtonQuit = new QPushButton( this, "PushButtonQuit" );
    PushButtonQuit->setGeometry( QRect( 65, 125, 61, 21 ) ); 
    PushButtonQuit->setText( trUtf8( "Avsluta" ) );

    LineEditBar = new QLineEdit( this, "LineEditBar" );
    LineEditBar->setGeometry( QRect( 100, 30, 35, 22 ) ); 

    LineEditKstalle = new QLineEdit( this, "LineEditKstalle" );
    LineEditKstalle->setGeometry( QRect( 100, 60, 60, 22 ) ); 

    LineEditBenamn = new QLineEdit( this, "LineEditBenamn" );
    LineEditBenamn->setGeometry( QRect( 100, 90, 315, 22 ) ); 

    PushButtonOK = new QPushButton( this, "PushButtonOK" );
    PushButtonOK->setGeometry( QRect( 5, 125, 51, 21 ) ); 
    PushButtonOK->setText( trUtf8( "OK" ) );
    PushButtonOK->setDefault( TRUE );

    // signals and slots connections
    connect( PushButtonOK, SIGNAL( clicked() ), LineEditBar, SLOT( setFocus() ) );
    connect( PushButtonQuit, SIGNAL( clicked() ), this, SLOT( close() ) );
    connect( PushButtonOK, SIGNAL( clicked() ), this, SLOT( slotPushButtonOK_clicked() ) );
    connect( LineEditBar, SIGNAL( returnPressed() ), this, SLOT( slotBarEntered() ) );
    connect( LineEditKstalle, SIGNAL( returnPressed() ), this, SLOT( slotKstalleEntered() ) );
    connect( LineEditBenamn, SIGNAL( returnPressed() ), this, SLOT( slotBenamnEntered() ) );

    // tab order
    setTabOrder( LineEditBar, LineEditKstalle );
    setTabOrder( LineEditKstalle, LineEditBenamn );
    setTabOrder( LineEditBenamn, PushButtonOK );
    setTabOrder( PushButtonOK, PushButtonQuit );
    init();
}

/*  
 *  Destroys the object and frees any allocated resources
 */
frmAddKstalle::~frmAddKstalle()
{
    // no need to delete child widgets, Qt does it all for us
}

