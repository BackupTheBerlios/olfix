/****************************************************************************
** Form implementation generated from reading ui file 'frmchgkonto.ui'
**
** Created: lör jun 7 05:46:53 2003
**      by: The User Interface Compiler ($Id: frmchgkonto.cpp,v 1.2 2003/09/28 06:41:43 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "frmchgkonto.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "frmchgkonto.ui.h"

/* 
 *  Constructs a frmChgKonto as a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
frmChgKonto::frmChgKonto( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "frmChgKonto" );

    TextLabelUserID = new QLabel( this, "TextLabelUserID" );
    TextLabelUserID->setGeometry( QRect( 10, 21, 81, 30 ) );

    TextLabelNamn = new QLabel( this, "TextLabelNamn" );
    TextLabelNamn->setGeometry( QRect( 10, 60, 82, 21 ) );

    TextLabelGrupp = new QLabel( this, "TextLabelGrupp" );
    TextLabelGrupp->setGeometry( QRect( 10, 120, 84, 21 ) );

    TextLabel1 = new QLabel( this, "TextLabel1" );
    TextLabel1->setGeometry( QRect( 10, 150, 81, 21 ) );

    TextLabel2 = new QLabel( this, "TextLabel2" );
    TextLabel2->setGeometry( QRect( 10, 180, 81, 21 ) );

    TextLabelAvd = new QLabel( this, "TextLabelAvd" );
    TextLabelAvd->setGeometry( QRect( 10, 90, 90, 21 ) );

    TextLabel3 = new QLabel( this, "TextLabel3" );
    TextLabel3->setGeometry( QRect( 10, 210, 91, 21 ) );

    TextLabel5 = new QLabel( this, "TextLabel5" );
    TextLabel5->setGeometry( QRect( 10, 270, 81, 21 ) );

    TextLabel6 = new QLabel( this, "TextLabel6" );
    TextLabel6->setGeometry( QRect( 10, 300, 81, 21 ) );

    TextLabel9 = new QLabel( this, "TextLabel9" );
    TextLabel9->setGeometry( QRect( 170, 20, 71, 21 ) );

    TextLabel9_2 = new QLabel( this, "TextLabel9_2" );
    TextLabel9_2->setGeometry( QRect( 170, 60, 71, 21 ) );

    TextLabel9_3 = new QLabel( this, "TextLabel9_3" );
    TextLabel9_3->setGeometry( QRect( 170, 120, 71, 21 ) );

    TextLabel9_4 = new QLabel( this, "TextLabel9_4" );
    TextLabel9_4->setGeometry( QRect( 170, 150, 71, 21 ) );

    TextLabel9_5 = new QLabel( this, "TextLabel9_5" );
    TextLabel9_5->setGeometry( QRect( 170, 180, 71, 21 ) );

    TextLabel9_6 = new QLabel( this, "TextLabel9_6" );
    TextLabel9_6->setGeometry( QRect( 260, 300, 71, 21 ) );

    LineEditUB = new QLineEdit( this, "LineEditUB" );
    LineEditUB->setEnabled( FALSE );
    LineEditUB->setGeometry( QRect( 100, 360, 111, 22 ) );

    TextLabel7 = new QLabel( this, "TextLabel7" );
    TextLabel7->setGeometry( QRect( 10, 330, 81, 21 ) );

    LineEditBar = new QLineEdit( this, "LineEditBar" );
    LineEditBar->setGeometry( QRect( 100, 20, 30, 22 ) );

    LineEditMomskod = new QLineEdit( this, "LineEditMomskod" );
    LineEditMomskod->setGeometry( QRect( 100, 150, 41, 22 ) );

    LineEditSRU = new QLineEdit( this, "LineEditSRU" );
    LineEditSRU->setGeometry( QRect( 100, 180, 41, 22 ) );

    LineEditKst = new QLineEdit( this, "LineEditKst" );
    LineEditKst->setGeometry( QRect( 100, 210, 51, 22 ) );

    LineEditProjekt = new QLineEdit( this, "LineEditProjekt" );
    LineEditProjekt->setGeometry( QRect( 100, 239, 51, 22 ) );

    LineEditSubkonto = new QLineEdit( this, "LineEditSubkonto" );
    LineEditSubkonto->setGeometry( QRect( 100, 270, 51, 22 ) );

    LineEditKontoplan = new QLineEdit( this, "LineEditKontoplan" );
    LineEditKontoplan->setGeometry( QRect( 100, 300, 151, 22 ) );

    LineEditIB = new QLineEdit( this, "LineEditIB" );
    LineEditIB->setEnabled( FALSE );
    LineEditIB->setGeometry( QRect( 100, 330, 111, 22 ) );

    LineEditManuell = new QLineEdit( this, "LineEditManuell" );
    LineEditManuell->setGeometry( QRect( 100, 120, 30, 22 ) );

    LineEditBenamn = new QLineEdit( this, "LineEditBenamn" );
    LineEditBenamn->setGeometry( QRect( 100, 90, 310, 22 ) );

    LineEditKontoNr = new QLineEdit( this, "LineEditKontoNr" );
    LineEditKontoNr->setGeometry( QRect( 100, 60, 50, 22 ) );

    PushButtonOK = new QPushButton( this, "PushButtonOK" );
    PushButtonOK->setGeometry( QRect( 10, 400, 51, 21 ) );
    PushButtonOK->setDefault( TRUE );

    PushButtonQuit = new QPushButton( this, "PushButtonQuit" );
    PushButtonQuit->setGeometry( QRect( 80, 400, 61, 21 ) );
    PushButtonQuit->setDefault( TRUE );

    PushButtonGet = new QPushButton( this, "PushButtonGet" );
    PushButtonGet->setGeometry( QRect( 250, 60, 61, 21 ) );
    PushButtonGet->setDefault( TRUE );

    TextLabel4 = new QLabel( this, "TextLabel4" );
    TextLabel4->setGeometry( QRect( 10, 240, 85, 21 ) );

    TextLabel8 = new QLabel( this, "TextLabel8" );
    TextLabel8->setGeometry( QRect( 10, 360, 85, 21 ) );
    languageChange();
    resize( QSize(419, 436).expandedTo(minimumSizeHint()) );

    // signals and slots connections
    connect( PushButtonQuit, SIGNAL( clicked() ), this, SLOT( close() ) );
    connect( LineEditKontoNr, SIGNAL( returnPressed() ), LineEditBenamn, SLOT( setFocus() ) );
    connect( LineEditBar, SIGNAL( returnPressed() ), LineEditKontoNr, SLOT( setFocus() ) );
    connect( LineEditManuell, SIGNAL( returnPressed() ), LineEditMomskod, SLOT( setFocus() ) );
    connect( LineEditMomskod, SIGNAL( returnPressed() ), LineEditSRU, SLOT( setFocus() ) );
    connect( LineEditKst, SIGNAL( returnPressed() ), LineEditProjekt, SLOT( setFocus() ) );
    connect( LineEditProjekt, SIGNAL( returnPressed() ), LineEditSubkonto, SLOT( setFocus() ) );
    connect( LineEditSubkonto, SIGNAL( returnPressed() ), LineEditKontoplan, SLOT( setFocus() ) );
    connect( PushButtonOK, SIGNAL( clicked() ), LineEditBar, SLOT( setFocus() ) );
    connect( LineEditKontoplan, SIGNAL( returnPressed() ), PushButtonOK, SLOT( setFocus() ) );
    connect( LineEditBenamn, SIGNAL( returnPressed() ), LineEditManuell, SLOT( setFocus() ) );
    connect( LineEditSRU, SIGNAL( returnPressed() ), LineEditKst, SLOT( setFocus() ) );
    connect( LineEditBar, SIGNAL( returnPressed() ), this, SLOT( LineEditBar_returnPressed() ) );
    connect( LineEditKontoNr, SIGNAL( returnPressed() ), this, SLOT( LineEditKontoNr_returnPressed() ) );
    connect( LineEditBenamn, SIGNAL( returnPressed() ), this, SLOT( LineEditBenamn_returnPressed() ) );
    connect( LineEditManuell, SIGNAL( returnPressed() ), this, SLOT( LineEditManuell_returnPressed() ) );
    connect( LineEditMomskod, SIGNAL( returnPressed() ), this, SLOT( LineEditMomskod_returnPressed() ) );
    connect( LineEditSRU, SIGNAL( returnPressed() ), this, SLOT( LineEditSRU_returnPressed() ) );
    connect( LineEditKst, SIGNAL( returnPressed() ), this, SLOT( LineEditKst_returnPressed() ) );
    connect( LineEditProjekt, SIGNAL( returnPressed() ), this, SLOT( LineEditProjekt_returnPressed() ) );
    connect( LineEditSubkonto, SIGNAL( returnPressed() ), this, SLOT( LineEditSubkonto_returnPressed() ) );
    connect( LineEditKontoplan, SIGNAL( returnPressed() ), this, SLOT( LineEditKontoplan_returnPressed() ) );
    connect( PushButtonOK, SIGNAL( clicked() ), this, SLOT( PushButtonOK_clicked() ) );
    connect( PushButtonGet, SIGNAL( clicked() ), this, SLOT( PushButtonGet_clicked() ) );
    connect( LineEditBar, SIGNAL( lostFocus() ), this, SLOT( LineEditBar_returnPressed() ) );
    connect( LineEditKontoNr, SIGNAL( lostFocus() ), this, SLOT( LineEditKontoNr_returnPressed() ) );
    connect( LineEditBenamn, SIGNAL( lostFocus() ), this, SLOT( LineEditBenamn_returnPressed() ) );
    connect( LineEditManuell, SIGNAL( lostFocus() ), this, SLOT( LineEditManuell_returnPressed() ) );
    connect( LineEditMomskod, SIGNAL( lostFocus() ), this, SLOT( LineEditMomskod_returnPressed() ) );
    connect( LineEditSRU, SIGNAL( lostFocus() ), this, SLOT( LineEditSRU_returnPressed() ) );
    connect( LineEditKst, SIGNAL( lostFocus() ), this, SLOT( LineEditKst_returnPressed() ) );
    connect( LineEditProjekt, SIGNAL( lostFocus() ), this, SLOT( LineEditProjekt_returnPressed() ) );
    connect( LineEditSubkonto, SIGNAL( lostFocus() ), this, SLOT( LineEditSubkonto_returnPressed() ) );
    connect( LineEditKontoplan, SIGNAL( lostFocus() ), this, SLOT( LineEditKontoplan_returnPressed() ) );

    // tab order
    setTabOrder( LineEditBar, LineEditKontoNr );
    setTabOrder( LineEditKontoNr, LineEditBenamn );
    setTabOrder( LineEditBenamn, LineEditManuell );
    setTabOrder( LineEditManuell, LineEditMomskod );
    setTabOrder( LineEditMomskod, LineEditSRU );
    setTabOrder( LineEditSRU, LineEditKst );
    setTabOrder( LineEditKst, LineEditProjekt );
    setTabOrder( LineEditProjekt, LineEditSubkonto );
    setTabOrder( LineEditSubkonto, LineEditKontoplan );
    setTabOrder( LineEditKontoplan, LineEditIB );
    setTabOrder( LineEditIB, LineEditUB );
    setTabOrder( LineEditUB, PushButtonOK );
    setTabOrder( PushButtonOK, PushButtonQuit );
}

/*
 *  Destroys the object and frees any allocated resources
 */
frmChgKonto::~frmChgKonto()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void frmChgKonto::languageChange()
{
    setCaption( trUtf8( "CHGKTOW  Ändra konto" ) );
    TextLabelUserID->setText( trUtf8( "Bokföringsår:\n"
"(arid, 2 teck.)" ) );
    TextLabelNamn->setText( tr( "Kontonummer:" ) );
    TextLabelGrupp->setText( tr( "Manuell (J/N):" ) );
    TextLabel1->setText( tr( "Momskod:" ) );
    TextLabel2->setText( tr( "SRUnr:" ) );
    TextLabelAvd->setText( trUtf8( "Benämning:" ) );
    TextLabel3->setText( trUtf8( "Kostnadsställe:" ) );
    TextLabel5->setText( tr( "Subkonto:" ) );
    TextLabel6->setText( tr( "Kontoplan:" ) );
    TextLabel9->setText( tr( "Obligatoriskt." ) );
    TextLabel9_2->setText( tr( "Obligatoriskt." ) );
    TextLabel9_3->setText( tr( "Obligatoriskt." ) );
    TextLabel9_4->setText( tr( "Obligatoriskt." ) );
    TextLabel9_5->setText( tr( "Obligatoriskt." ) );
    TextLabel9_6->setText( tr( "Obligatoriskt." ) );
    TextLabel7->setText( tr( "IB:" ) );
    LineEditManuell->setText( QString::null );
    PushButtonOK->setText( tr( "OK" ) );
    PushButtonQuit->setText( tr( "Avsluta" ) );
    PushButtonGet->setText( trUtf8( "Hämta" ) );
    TextLabel4->setText( tr( "Projekt:" ) );
    TextLabel8->setText( tr( "UB:" ) );
}

