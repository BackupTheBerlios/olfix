/****************************************************************************
** Form implementation generated from reading ui file 'frmaddbar.ui'
**
** Created: ons maj 28 05:28:31 2003
**      by: The User Interface Compiler ($Id: frmaddbar.cpp,v 1.2 2003/09/28 05:45:57 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "frmaddbar.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "frmaddbar.ui.h"

/* 
 *  Constructs a frmAddBar as a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
frmAddBar::frmAddBar( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "frmAddBar" );

    TextLabel5 = new QLabel( this, "TextLabel5" );
    TextLabel5->setGeometry( QRect( 10, 240, 81, 21 ) );

    TextLabel01 = new QLabel( this, "TextLabel01" );
    TextLabel01->setGeometry( QRect( 10, 21, 81, 30 ) );

    TextLabel02 = new QLabel( this, "TextLabel02" );
    TextLabel02->setGeometry( QRect( 10, 60, 90, 21 ) );

    TextLabel03 = new QLabel( this, "TextLabel03" );
    TextLabel03->setGeometry( QRect( 10, 90, 84, 21 ) );

    TextLabel1 = new QLabel( this, "TextLabel1" );
    TextLabel1->setGeometry( QRect( 10, 120, 81, 21 ) );

    LineEditBenamn = new QLineEdit( this, "LineEditBenamn" );
    LineEditBenamn->setGeometry( QRect( 140, 60, 310, 22 ) );

    LineEditStartdatum = new QLineEdit( this, "LineEditStartdatum" );
    LineEditStartdatum->setGeometry( QRect( 140, 90, 90, 22 ) );

    TextLabel9_3 = new QLabel( this, "TextLabel9_3" );
    TextLabel9_3->setGeometry( QRect( 240, 90, 71, 21 ) );

    LineEditSlutdatum = new QLineEdit( this, "LineEditSlutdatum" );
    LineEditSlutdatum->setGeometry( QRect( 140, 120, 90, 22 ) );

    LineEditBeskattAr = new QLineEdit( this, "LineEditBeskattAr" );
    LineEditBeskattAr->setGeometry( QRect( 140, 150, 60, 22 ) );

    LineEditSenVerDat = new QLineEdit( this, "LineEditSenVerDat" );
    LineEditSenVerDat->setEnabled( FALSE );
    LineEditSenVerDat->setGeometry( QRect( 140, 180, 90, 22 ) );

    TextLabel3 = new QLabel( this, "TextLabel3" );
    TextLabel3->setGeometry( QRect( 10, 180, 120, 21 ) );

    TextLabel2 = new QLabel( this, "TextLabel2" );
    TextLabel2->setGeometry( QRect( 10, 150, 100, 21 ) );

    LineEditNestaVerNr = new QLineEdit( this, "LineEditNestaVerNr" );
    LineEditNestaVerNr->setGeometry( QRect( 140, 210, 90, 22 ) );

    TextLabel4 = new QLabel( this, "TextLabel4" );
    TextLabel4->setGeometry( QRect( 10, 210, 120, 21 ) );

    LineEditKontoplan = new QLineEdit( this, "LineEditKontoplan" );
    LineEditKontoplan->setGeometry( QRect( 140, 240, 150, 22 ) );

    TextLabel9_5_2 = new QLabel( this, "TextLabel9_5_2" );
    TextLabel9_5_2->setGeometry( QRect( 295, 240, 71, 21 ) );

    TextLabel9_4 = new QLabel( this, "TextLabel9_4" );
    TextLabel9_4->setGeometry( QRect( 240, 115, 71, 21 ) );

    TextLabel9_5 = new QLabel( this, "TextLabel9_5" );
    TextLabel9_5->setGeometry( QRect( 240, 150, 71, 21 ) );

    PushButtonOK = new QPushButton( this, "PushButtonOK" );
    PushButtonOK->setGeometry( QRect( 10, 290, 51, 21 ) );
    PushButtonOK->setDefault( TRUE );

    PushButtonQuit = new QPushButton( this, "PushButtonQuit" );
    PushButtonQuit->setGeometry( QRect( 80, 290, 61, 21 ) );
    PushButtonQuit->setDefault( TRUE );

    LineEditBar = new QLineEdit( this, "LineEditBar" );
    LineEditBar->setGeometry( QRect( 140, 25, 30, 22 ) );

    TextLabel9 = new QLabel( this, "TextLabel9" );
    TextLabel9->setGeometry( QRect( 190, 25, 71, 21 ) );

    pushButton3 = new QPushButton( this, "pushButton3" );
    pushButton3->setGeometry( QRect( 355, 5, 95, 21 ) );
    QFont pushButton3_font(  pushButton3->font() );
    pushButton3_font.setPointSize( 8 );
    pushButton3->setFont( pushButton3_font ); 
    languageChange();
    resize( QSize(459, 319).expandedTo(minimumSizeHint()) );

    // signals and slots connections
    connect( PushButtonQuit, SIGNAL( clicked() ), this, SLOT( close() ) );
    connect( LineEditSlutdatum, SIGNAL( returnPressed() ), LineEditBeskattAr, SLOT( setFocus() ) );
    connect( PushButtonOK, SIGNAL( clicked() ), LineEditBar, SLOT( setFocus() ) );
    connect( LineEditBenamn, SIGNAL( returnPressed() ), LineEditStartdatum, SLOT( setFocus() ) );
    connect( LineEditBeskattAr, SIGNAL( returnPressed() ), LineEditSenVerDat, SLOT( setFocus() ) );
    connect( PushButtonOK, SIGNAL( clicked() ), this, SLOT( PushButtonOK_clicked() ) );
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
    connect( LineEditBar, SIGNAL( lostFocus() ), this, SLOT( LineEditBar_returnPressed() ) );
    connect( LineEditBenamn, SIGNAL( lostFocus() ), this, SLOT( LineEditBenamn_returnPressed() ) );
    connect( LineEditStartdatum, SIGNAL( lostFocus() ), this, SLOT( LineEditStartdatum_returnPressed() ) );
    connect( LineEditSlutdatum, SIGNAL( lostFocus() ), this, SLOT( LineEditSlutdatum_returnPressed() ) );
    connect( LineEditBeskattAr, SIGNAL( lostFocus() ), this, SLOT( LineEditBeskattAr_returnPressed() ) );
    connect( LineEditNestaVerNr, SIGNAL( lostFocus() ), this, SLOT( LineEditNestaVerNr_returnPressed() ) );
    connect( LineEditKontoplan, SIGNAL( lostFocus() ), this, SLOT( LineEditKontoplan_returnPressed() ) );
    connect( pushButton3, SIGNAL( clicked() ), this, SLOT( slotAbout() ) );

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
}

/*
 *  Destroys the object and frees any allocated resources
 */
frmAddBar::~frmAddBar()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void frmAddBar::languageChange()
{
    setCaption( trUtf8( "ADDBARW  Lägga upp nytt bokföringsår" ) );
    TextLabel5->setText( tr( "Kontoplan:" ) );
    TextLabel01->setText( trUtf8( "Bokföringsår:\n"
"(arid, 2 teck.)" ) );
    TextLabel02->setText( trUtf8( "Benämning:" ) );
    TextLabel03->setText( tr( "Startdatum:" ) );
    TextLabel1->setText( tr( "Slutdatum:" ) );
    LineEditStartdatum->setText( QString::null );
    TextLabel9_3->setText( tr( "Obligatoriskt." ) );
    TextLabel3->setText( tr( "Senaste ver.datum:" ) );
    TextLabel2->setText( trUtf8( "Beskattningsår:" ) );
    LineEditNestaVerNr->setText( tr( "1" ) );
    TextLabel4->setText( trUtf8( "Nästa ver.nummer:" ) );
    TextLabel9_5_2->setText( tr( "Obligatoriskt." ) );
    TextLabel9_4->setText( tr( "Obligatoriskt." ) );
    TextLabel9_5->setText( tr( "Obligatoriskt." ) );
    PushButtonOK->setText( tr( "OK" ) );
    PushButtonQuit->setText( tr( "Avsluta" ) );
    TextLabel9->setText( tr( "Obligatoriskt." ) );
    pushButton3->setText( tr( "Om ADDBARW" ) );
}

