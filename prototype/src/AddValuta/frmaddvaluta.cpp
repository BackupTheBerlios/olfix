/****************************************************************************
** Form implementation generated from reading ui file 'frmaddvaluta.ui'
**
** Created: tor mar 20 07:58:24 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "frmaddvaluta.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "frmaddvaluta.ui.h"

/* 
 *  Constructs a frmAddValuta which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
frmAddValuta::frmAddValuta( QWidget* parent,  const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "frmAddValuta" );
    resize( 316, 214 ); 
    setCaption( trUtf8( "ADDVALW  Lägga upp ny valuta" ) );

    TextLabelSalj = new QLabel( this, "TextLabelSalj" );
    TextLabelSalj->setGeometry( QRect( 10, 150, 70, 21 ) ); 
    TextLabelSalj->setText( trUtf8( "Sälj:" ) );

    TextLabelKop = new QLabel( this, "TextLabelKop" );
    TextLabelKop->setGeometry( QRect( 10, 120, 70, 21 ) ); 
    TextLabelKop->setText( trUtf8( "Köp:" ) );

    TextLabelBeteckn = new QLabel( this, "TextLabelBeteckn" );
    TextLabelBeteckn->setGeometry( QRect( 10, 60, 70, 21 ) ); 
    TextLabelBeteckn->setText( trUtf8( "Beteckning:" ) );

    TextLabelValuta = new QLabel( this, "TextLabelValuta" );
    TextLabelValuta->setGeometry( QRect( 10, 30, 81, 21 ) ); 
    TextLabelValuta->setText( trUtf8( "Valuta:" ) );

    TextLabelLand = new QLabel( this, "TextLabelLand" );
    TextLabelLand->setGeometry( QRect( 10, 90, 70, 21 ) ); 
    TextLabelLand->setText( trUtf8( "Land:" ) );

    LineEditKop = new QLineEdit( this, "LineEditKop" );
    LineEditKop->setGeometry( QRect( 90, 120, 80, 22 ) ); 

    LineEditLand = new QLineEdit( this, "LineEditLand" );
    LineEditLand->setGeometry( QRect( 90, 90, 210, 22 ) ); 

    PushButtonQuit = new QPushButton( this, "PushButtonQuit" );
    PushButtonQuit->setGeometry( QRect( 65, 185, 61, 21 ) ); 
    PushButtonQuit->setText( trUtf8( "Avsluta" ) );

    LineEditBeteck = new QLineEdit( this, "LineEditBeteck" );
    LineEditBeteck->setGeometry( QRect( 90, 60, 210, 22 ) ); 

    LineEditValuta = new QLineEdit( this, "LineEditValuta" );
    LineEditValuta->setGeometry( QRect( 91, 30, 45, 22 ) ); 

    LineEditSalj = new QLineEdit( this, "LineEditSalj" );
    LineEditSalj->setGeometry( QRect( 90, 150, 80, 22 ) ); 

    PushButtonOK = new QPushButton( this, "PushButtonOK" );
    PushButtonOK->setGeometry( QRect( 5, 185, 51, 21 ) ); 
    PushButtonOK->setText( trUtf8( "OK" ) );
    PushButtonOK->setDefault( TRUE );

    // signals and slots connections
    connect( PushButtonQuit, SIGNAL( clicked() ), this, SLOT( close() ) );
    connect( PushButtonOK, SIGNAL( clicked() ), LineEditValuta, SLOT( setFocus() ) );
    connect( LineEditValuta, SIGNAL( returnPressed() ), this, SLOT( slotValutaEntered() ) );
    connect( LineEditBeteck, SIGNAL( returnPressed() ), this, SLOT( slotBeteckningEntered() ) );
    connect( LineEditLand, SIGNAL( returnPressed() ), this, SLOT( slotLandEntered() ) );
    connect( LineEditKop, SIGNAL( returnPressed() ), this, SLOT( slotKopEntered() ) );
    connect( LineEditSalj, SIGNAL( returnPressed() ), this, SLOT( slotSaljEntered() ) );
    connect( LineEditSalj, SIGNAL( returnPressed() ), PushButtonOK, SLOT( setFocus() ) );
    connect( PushButtonOK, SIGNAL( clicked() ), this, SLOT( slotPushButtonOK_clicked() ) );

    // tab order
    setTabOrder( LineEditValuta, LineEditBeteck );
    setTabOrder( LineEditBeteck, LineEditLand );
    setTabOrder( LineEditLand, LineEditKop );
    setTabOrder( LineEditKop, PushButtonOK );
    setTabOrder( PushButtonOK, PushButtonQuit );
    init();
}

/*  
 *  Destroys the object and frees any allocated resources
 */
frmAddValuta::~frmAddValuta()
{
    // no need to delete child widgets, Qt does it all for us
}

