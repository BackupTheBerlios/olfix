/****************************************************************************
** Form implementation generated from reading ui file 'frmchgvaluta.ui'
**
** Created: tor mar 20 08:07:48 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "frmchgvaluta.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "frmchgvaluta.ui.h"

/* 
 *  Constructs a frmChgValuta which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
frmChgValuta::frmChgValuta( QWidget* parent,  const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "frmChgValuta" );
    resize( 307, 210 ); 
    setCaption( trUtf8( "CHGVALW  Ändra valuta" ) );

    TextLabelBeteck = new QLabel( this, "TextLabelBeteck" );
    TextLabelBeteck->setGeometry( QRect( 10, 60, 70, 21 ) ); 
    TextLabelBeteck->setText( trUtf8( "Beteckning:" ) );

    LineEditBeteck = new QLineEdit( this, "LineEditBeteck" );
    LineEditBeteck->setGeometry( QRect( 90, 60, 210, 22 ) ); 

    PushButtonQuit = new QPushButton( this, "PushButtonQuit" );
    PushButtonQuit->setGeometry( QRect( 145, 180, 61, 21 ) ); 
    PushButtonQuit->setText( trUtf8( "Avsluta" ) );

    LineEditLand = new QLineEdit( this, "LineEditLand" );
    LineEditLand->setGeometry( QRect( 90, 90, 210, 22 ) ); 

    LineEditKop = new QLineEdit( this, "LineEditKop" );
    LineEditKop->setGeometry( QRect( 90, 120, 55, 22 ) ); 

    LineEditSalj = new QLineEdit( this, "LineEditSalj" );
    LineEditSalj->setGeometry( QRect( 90, 150, 55, 22 ) ); 

    TextLabelValuta = new QLabel( this, "TextLabelValuta" );
    TextLabelValuta->setGeometry( QRect( 10, 30, 45, 21 ) ); 
    TextLabelValuta->setText( trUtf8( "Valuta:" ) );

    TextLabelLand = new QLabel( this, "TextLabelLand" );
    TextLabelLand->setGeometry( QRect( 10, 90, 40, 21 ) ); 
    TextLabelLand->setText( trUtf8( "Land:" ) );

    TextLabelKop = new QLabel( this, "TextLabelKop" );
    TextLabelKop->setGeometry( QRect( 10, 120, 40, 21 ) ); 
    TextLabelKop->setText( trUtf8( "Köp:" ) );

    TextLabelSalj = new QLabel( this, "TextLabelSalj" );
    TextLabelSalj->setGeometry( QRect( 10, 150, 40, 21 ) ); 
    TextLabelSalj->setText( trUtf8( "Sälj:" ) );

    LineEditValuta = new QLineEdit( this, "LineEditValuta" );
    LineEditValuta->setGeometry( QRect( 91, 30, 45, 22 ) ); 

    PushButtonGet = new QPushButton( this, "PushButtonGet" );
    PushButtonGet->setGeometry( QRect( 5, 180, 51, 21 ) ); 
    PushButtonGet->setText( trUtf8( "Hämta" ) );
    PushButtonGet->setDefault( TRUE );

    PushButtonUpdate = new QPushButton( this, "PushButtonUpdate" );
    PushButtonUpdate->setGeometry( QRect( 65, 180, 70, 21 ) ); 
    PushButtonUpdate->setText( trUtf8( "Uppdatera" ) );
    PushButtonUpdate->setDefault( TRUE );

    // signals and slots connections
    connect( LineEditBeteck, SIGNAL( returnPressed() ), PushButtonGet, SLOT( setFocus() ) );
    connect( PushButtonGet, SIGNAL( clicked() ), LineEditBeteck, SLOT( clear() ) );
    connect( PushButtonGet, SIGNAL( clicked() ), LineEditValuta, SLOT( setFocus() ) );
    connect( PushButtonGet, SIGNAL( clicked() ), LineEditValuta, SLOT( clear() ) );
    connect( LineEditBeteck, SIGNAL( returnPressed() ), LineEditLand, SLOT( setFocus() ) );
    connect( LineEditValuta, SIGNAL( returnPressed() ), LineEditBeteck, SLOT( setFocus() ) );
    connect( LineEditLand, SIGNAL( returnPressed() ), LineEditKop, SLOT( setFocus() ) );
    connect( LineEditKop, SIGNAL( returnPressed() ), PushButtonUpdate, SLOT( setFocus() ) );
    connect( LineEditValuta, SIGNAL( returnPressed() ), this, SLOT( slotValutaEntered() ) );
    connect( LineEditBeteck, SIGNAL( returnPressed() ), this, SLOT( slotBeteckningEntered() ) );
    connect( LineEditLand, SIGNAL( returnPressed() ), this, SLOT( slotLandEntered() ) );
    connect( LineEditKop, SIGNAL( returnPressed() ), this, SLOT( slotKopEntered() ) );
    connect( LineEditSalj, SIGNAL( returnPressed() ), this, SLOT( slotSaljEntered() ) );
    connect( PushButtonGet, SIGNAL( clicked() ), this, SLOT( slotPushButtonGet_clicked() ) );
    connect( PushButtonQuit, SIGNAL( clicked() ), this, SLOT( close() ) );
    connect( PushButtonUpdate, SIGNAL( clicked() ), this, SLOT( slotChgValuta() ) );

    // tab order
    setTabOrder( LineEditValuta, PushButtonGet );
    setTabOrder( PushButtonGet, LineEditBeteck );
    setTabOrder( LineEditBeteck, LineEditLand );
    setTabOrder( LineEditLand, LineEditKop );
    setTabOrder( LineEditKop, PushButtonUpdate );
    setTabOrder( PushButtonUpdate, PushButtonQuit );
    init();
}

/*  
 *  Destroys the object and frees any allocated resources
 */
frmChgValuta::~frmChgValuta()
{
    // no need to delete child widgets, Qt does it all for us
}

