/****************************************************************************
** Form implementation generated from reading ui file 'frmchgbar.ui'
**
** Created: ons apr 2 14:17:37 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "frmchgbar.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "frmchgbar.ui.h"

/* 
 *  Constructs a frmChgBar which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
frmChgBar::frmChgBar( QWidget* parent,  const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "frmChgBar" );
    resize( 450, 319 ); 
    setCaption( trUtf8( "CHGBARW  Ändra bokföringsår" ) );

    TextLabel2 = new QLabel( this, "TextLabel2" );
    TextLabel2->setGeometry( QRect( 10, 150, 81, 21 ) ); 
    TextLabel2->setText( trUtf8( "Beskattningsår:" ) );

    TextLabel3 = new QLabel( this, "TextLabel3" );
    TextLabel3->setGeometry( QRect( 10, 180, 110, 21 ) ); 
    TextLabel3->setText( trUtf8( "Senaste ver.datum:" ) );

    TextLabel9_3 = new QLabel( this, "TextLabel9_3" );
    TextLabel9_3->setGeometry( QRect( 220, 90, 71, 21 ) ); 
    TextLabel9_3->setText( trUtf8( "Obligatoriskt." ) );

    TextLabel9_4 = new QLabel( this, "TextLabel9_4" );
    TextLabel9_4->setGeometry( QRect( 220, 120, 71, 21 ) ); 
    TextLabel9_4->setText( trUtf8( "Obligatoriskt." ) );

    TextLabel4 = new QLabel( this, "TextLabel4" );
    TextLabel4->setGeometry( QRect( 10, 210, 107, 21 ) ); 
    TextLabel4->setText( trUtf8( "Nästa ver.nummer:" ) );

    TextLabel9 = new QLabel( this, "TextLabel9" );
    TextLabel9->setGeometry( QRect( 220, 20, 71, 21 ) ); 
    TextLabel9->setText( trUtf8( "Obligatoriskt." ) );

    TextLabel9_5 = new QLabel( this, "TextLabel9_5" );
    TextLabel9_5->setGeometry( QRect( 220, 150, 71, 21 ) ); 
    TextLabel9_5->setText( trUtf8( "Obligatoriskt." ) );

    TextLabel9_5_2 = new QLabel( this, "TextLabel9_5_2" );
    TextLabel9_5_2->setGeometry( QRect( 280, 240, 71, 21 ) ); 
    TextLabel9_5_2->setText( trUtf8( "Obligatoriskt." ) );

    TextLabel5 = new QLabel( this, "TextLabel5" );
    TextLabel5->setGeometry( QRect( 10, 240, 81, 21 ) ); 
    TextLabel5->setText( trUtf8( "Kontoplan:" ) );

    TextLabel01 = new QLabel( this, "TextLabel01" );
    TextLabel01->setGeometry( QRect( 10, 21, 81, 30 ) ); 
    TextLabel01->setText( trUtf8( "Bokföringsår:\n"
"(arid, 2 teck.)" ) );

    TextLabel02 = new QLabel( this, "TextLabel02" );
    TextLabel02->setGeometry( QRect( 10, 60, 90, 21 ) ); 
    TextLabel02->setText( trUtf8( "Benämning:" ) );

    TextLabel03 = new QLabel( this, "TextLabel03" );
    TextLabel03->setGeometry( QRect( 10, 90, 84, 21 ) ); 
    TextLabel03->setText( trUtf8( "Startdatum:" ) );

    TextLabel1 = new QLabel( this, "TextLabel1" );
    TextLabel1->setGeometry( QRect( 10, 120, 81, 21 ) ); 
    TextLabel1->setText( trUtf8( "Slutdatum:" ) );

    PushButtonOK = new QPushButton( this, "PushButtonOK" );
    PushButtonOK->setGeometry( QRect( 10, 290, 51, 21 ) ); 
    PushButtonOK->setText( trUtf8( "OK" ) );
    PushButtonOK->setDefault( TRUE );

    PushButtonQuit = new QPushButton( this, "PushButtonQuit" );
    PushButtonQuit->setGeometry( QRect( 80, 290, 61, 21 ) ); 
    PushButtonQuit->setText( trUtf8( "Avsluta" ) );
    PushButtonQuit->setDefault( TRUE );

    LineEditBar = new QLineEdit( this, "LineEditBar" );
    LineEditBar->setGeometry( QRect( 120, 20, 30, 22 ) ); 

    LineEditBenamn = new QLineEdit( this, "LineEditBenamn" );
    LineEditBenamn->setGeometry( QRect( 120, 60, 310, 22 ) ); 

    LineEditStartdatum = new QLineEdit( this, "LineEditStartdatum" );
    LineEditStartdatum->setGeometry( QRect( 120, 90, 90, 22 ) ); 
    LineEditStartdatum->setText( trUtf8( "" ) );

    LineEditSlutdatum = new QLineEdit( this, "LineEditSlutdatum" );
    LineEditSlutdatum->setGeometry( QRect( 120, 120, 90, 22 ) ); 

    LineEditSenVerDat = new QLineEdit( this, "LineEditSenVerDat" );
    LineEditSenVerDat->setEnabled( FALSE );
    LineEditSenVerDat->setGeometry( QRect( 120, 180, 90, 22 ) ); 

    LineEditNestaVerNr = new QLineEdit( this, "LineEditNestaVerNr" );
    LineEditNestaVerNr->setGeometry( QRect( 120, 210, 90, 22 ) ); 
    LineEditNestaVerNr->setText( trUtf8( "" ) );

    LineEditKontoplan = new QLineEdit( this, "LineEditKontoplan" );
    LineEditKontoplan->setGeometry( QRect( 120, 240, 150, 22 ) ); 

    LineEditBeskattAr = new QLineEdit( this, "LineEditBeskattAr" );
    LineEditBeskattAr->setGeometry( QRect( 120, 150, 60, 22 ) ); 

    // signals and slots connections
    connect( PushButtonQuit, SIGNAL( clicked() ), this, SLOT( close() ) );
    connect( LineEditSlutdatum, SIGNAL( returnPressed() ), LineEditBeskattAr, SLOT( setFocus() ) );
    connect( PushButtonOK, SIGNAL( clicked() ), LineEditBar, SLOT( setFocus() ) );
    connect( LineEditBenamn, SIGNAL( returnPressed() ), LineEditStartdatum, SLOT( setFocus() ) );
    connect( LineEditBeskattAr, SIGNAL( returnPressed() ), LineEditSenVerDat, SLOT( setFocus() ) );
    connect( LineEditNestaVerNr, SIGNAL( returnPressed() ), LineEditKontoplan, SLOT( setFocus() ) );
    connect( LineEditKontoplan, SIGNAL( returnPressed() ), PushButtonOK, SLOT( setFocus() ) );
    connect( LineEditStartdatum, SIGNAL( returnPressed() ), LineEditSlutdatum, SLOT( setFocus() ) );
    connect( LineEditBar, SIGNAL( returnPressed() ), this, SLOT( LineEditBar_returnPressed() ) );
    connect( LineEditBenamn, SIGNAL( returnPressed() ), this, SLOT( LineEditBenamn_returnPressed() ) );
    connect( LineEditBeskattAr, SIGNAL( returnPressed() ), this, SLOT( LineEditBeskattAr_returnPressed() ) );
    connect( LineEditNestaVerNr, SIGNAL( returnPressed() ), this, SLOT( LineEditNestaVerNr_returnPressed() ) );
    connect( LineEditKontoplan, SIGNAL( returnPressed() ), this, SLOT( LineEditKontoplan_returnPressed() ) );
    connect( LineEditStartdatum, SIGNAL( returnPressed() ), this, SLOT( LineEditStartdatum_returnPressed() ) );
    connect( LineEditSlutdatum, SIGNAL( returnPressed() ), this, SLOT( LineEditSlutdatum_returnPressed() ) );
    connect( PushButtonOK, SIGNAL( clicked() ), this, SLOT( slotChgBar() ) );

    // tab order
    setTabOrder( LineEditBar, LineEditBenamn );
    setTabOrder( LineEditBenamn, LineEditStartdatum );
    setTabOrder( LineEditStartdatum, LineEditSlutdatum );
    setTabOrder( LineEditSlutdatum, LineEditBeskattAr );
    setTabOrder( LineEditBeskattAr, LineEditSenVerDat );
    setTabOrder( LineEditSenVerDat, LineEditNestaVerNr );
    setTabOrder( LineEditNestaVerNr, LineEditKontoplan );
    setTabOrder( LineEditKontoplan, PushButtonOK );
    setTabOrder( PushButtonOK, PushButtonQuit );
    init();
}

/*  
 *  Destroys the object and frees any allocated resources
 */
frmChgBar::~frmChgBar()
{
    // no need to delete child widgets, Qt does it all for us
}

