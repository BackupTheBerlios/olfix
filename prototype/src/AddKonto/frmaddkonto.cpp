/****************************************************************************
** Form implementation generated from reading ui file 'frmaddkonto.ui'
**
** Created: ons aug 6 06:11:23 2003
**      by: The User Interface Compiler ($Id: frmaddkonto.cpp,v 1.2 2003/09/28 05:50:08 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "frmaddkonto.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "frmaddkonto.ui.h"

/* 
 *  Constructs a frmAddKonto as a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
frmAddKonto::frmAddKonto( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "frmAddKonto" );

    PushButtonOK = new QPushButton( this, "PushButtonOK" );
    PushButtonOK->setGeometry( QRect( 10, 425, 51, 21 ) );
    PushButtonOK->setDefault( TRUE );

    PushButtonQuit = new QPushButton( this, "PushButtonQuit" );
    PushButtonQuit->setGeometry( QRect( 80, 425, 61, 21 ) );

    LineEditUB = new QLineEdit( this, "LineEditUB" );
    LineEditUB->setEnabled( FALSE );
    LineEditUB->setGeometry( QRect( 120, 380, 111, 22 ) );

    LineEditIB = new QLineEdit( this, "LineEditIB" );
    LineEditIB->setEnabled( FALSE );
    LineEditIB->setGeometry( QRect( 120, 350, 111, 22 ) );

    TextLabel6 = new QLabel( this, "TextLabel6" );
    TextLabel6->setGeometry( QRect( 10, 320, 81, 21 ) );

    LineEditSubkonto = new QLineEdit( this, "LineEditSubkonto" );
    LineEditSubkonto->setGeometry( QRect( 120, 290, 51, 22 ) );

    TextLabel5 = new QLabel( this, "TextLabel5" );
    TextLabel5->setGeometry( QRect( 10, 290, 105, 21 ) );

    TextLabel4 = new QLabel( this, "TextLabel4" );
    TextLabel4->setGeometry( QRect( 10, 260, 105, 21 ) );

    LineEditProjekt = new QLineEdit( this, "LineEditProjekt" );
    LineEditProjekt->setGeometry( QRect( 120, 260, 51, 22 ) );

    LineEditKst = new QLineEdit( this, "LineEditKst" );
    LineEditKst->setGeometry( QRect( 120, 230, 51, 22 ) );

    TextLabel3 = new QLabel( this, "TextLabel3" );
    TextLabel3->setGeometry( QRect( 10, 230, 105, 21 ) );

    TextLabel2 = new QLabel( this, "TextLabel2" );
    TextLabel2->setGeometry( QRect( 10, 200, 81, 21 ) );

    TextLabel1 = new QLabel( this, "TextLabel1" );
    TextLabel1->setGeometry( QRect( 10, 170, 81, 21 ) );

    TextLabelGrupp = new QLabel( this, "TextLabelGrupp" );
    TextLabelGrupp->setGeometry( QRect( 10, 140, 84, 21 ) );

    LineEditManuell = new QLineEdit( this, "LineEditManuell" );
    LineEditManuell->setGeometry( QRect( 120, 140, 30, 22 ) );

    TextLabelAvd = new QLabel( this, "TextLabelAvd" );
    TextLabelAvd->setGeometry( QRect( 10, 110, 105, 21 ) );

    TextLabelNamn = new QLabel( this, "TextLabelNamn" );
    TextLabelNamn->setGeometry( QRect( 10, 80, 82, 21 ) );

    TextLabelUserID = new QLabel( this, "TextLabelUserID" );
    TextLabelUserID->setGeometry( QRect( 10, 45, 81, 30 ) );

    textLabel1 = new QLabel( this, "textLabel1" );
    textLabel1->setGeometry( QRect( 10, 15, 105, 16 ) );

    TextLabel7 = new QLabel( this, "TextLabel7" );
    TextLabel7->setGeometry( QRect( 10, 350, 105, 21 ) );

    TextLabel8 = new QLabel( this, "TextLabel8" );
    TextLabel8->setGeometry( QRect( 10, 380, 105, 21 ) );

    TextLabel9 = new QLabel( this, "TextLabel9" );
    TextLabel9->setGeometry( QRect( 95, 50, 20, 21 ) );

    TextLabel9_2 = new QLabel( this, "TextLabel9_2" );
    TextLabel9_2->setGeometry( QRect( 95, 80, 16, 21 ) );

    TextLabel9_3 = new QLabel( this, "TextLabel9_3" );
    TextLabel9_3->setGeometry( QRect( 95, 140, 16, 21 ) );

    TextLabel9_4 = new QLabel( this, "TextLabel9_4" );
    TextLabel9_4->setGeometry( QRect( 95, 170, 16, 21 ) );

    TextLabel9_5 = new QLabel( this, "TextLabel9_5" );
    TextLabel9_5->setGeometry( QRect( 95, 200, 20, 21 ) );

    TextLabel9_6 = new QLabel( this, "TextLabel9_6" );
    TextLabel9_6->setGeometry( QRect( 95, 320, 16, 21 ) );

    LineEditBar = new QLineEdit( this, "LineEditBar" );
    LineEditBar->setGeometry( QRect( 120, 50, 30, 22 ) );

    LineEditKontoNr = new QLineEdit( this, "LineEditKontoNr" );
    LineEditKontoNr->setGeometry( QRect( 120, 80, 50, 22 ) );

    LineEditBenamn = new QLineEdit( this, "LineEditBenamn" );
    LineEditBenamn->setGeometry( QRect( 120, 110, 290, 23 ) );

    LineEditMomskod = new QLineEdit( this, "LineEditMomskod" );
    LineEditMomskod->setGeometry( QRect( 120, 170, 41, 22 ) );

    LineEditSRU = new QLineEdit( this, "LineEditSRU" );
    LineEditSRU->setGeometry( QRect( 120, 200, 41, 22 ) );

    LineEditKontoplan = new QLineEdit( this, "LineEditKontoplan" );
    LineEditKontoplan->setGeometry( QRect( 120, 320, 151, 22 ) );
    languageChange();
    resize( QSize(419, 456).expandedTo(minimumSizeHint()) );

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
frmAddKonto::~frmAddKonto()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void frmAddKonto::languageChange()
{
    setCaption( trUtf8( "ADDKTOW  Lägga upp nytt konto" ) );
    PushButtonOK->setText( tr( "OK" ) );
    PushButtonQuit->setText( tr( "Avsluta" ) );
    TextLabel6->setText( tr( "Kontoplan:" ) );
    TextLabel5->setText( tr( "Subkonto:" ) );
    TextLabel4->setText( tr( "Projekt:" ) );
    TextLabel3->setText( trUtf8( "Kostnadsställe:" ) );
    TextLabel2->setText( tr( "SRUnr:" ) );
    TextLabel1->setText( tr( "Momskod:" ) );
    TextLabelGrupp->setText( tr( "Manuell (J/N):" ) );
    LineEditManuell->setText( tr( "J" ) );
    TextLabelAvd->setText( trUtf8( "Benämning:" ) );
    TextLabelNamn->setText( tr( "Kontonummer:" ) );
    TextLabelUserID->setText( trUtf8( "Bokföringsår:\n"
"(arid, 2 teck.)" ) );
    textLabel1->setText( tr( "  * = Obligatorisk" ) );
    TextLabel7->setText( tr( "IB:" ) );
    TextLabel8->setText( tr( "UB:" ) );
    TextLabel9->setText( tr( "  *" ) );
    TextLabel9_2->setText( tr( "  *" ) );
    TextLabel9_3->setText( tr( "  *" ) );
    TextLabel9_4->setText( tr( "  *" ) );
    TextLabel9_5->setText( tr( "  *" ) );
    TextLabel9_6->setText( tr( "  *" ) );
    QToolTip::add( LineEditBar, trUtf8( "Bokföringsår enligt CHGBARW" ) );
    QToolTip::add( LineEditKontoNr, tr( "Kontonr enligt aktuell kontoplan" ) );
    QToolTip::add( LineEditBenamn, trUtf8( "Förklarande text till kontonummer" ) );
    QToolTip::add( LineEditMomskod, trUtf8( "Momskod enligt företagsregistret. 1 - 5." ) );
    QToolTip::add( LineEditSRU, tr( "Enligt skattemyndighetens anvisningar." ) );
    QToolTip::add( LineEditKontoplan, trUtf8( "Namn på kontoplan, t ex EUBAS97" ) );
}

