/****************************************************************************
** Form implementation generated from reading ui file 'frmaddkonto.ui'
**
** Created: tor mar 20 07:51:37 2003
**      by:  The User Interface Compiler (uic)
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
 *  Constructs a frmAddKonto which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
frmAddKonto::frmAddKonto( QWidget* parent,  const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "frmAddKonto" );
    resize( 419, 436 ); 
    setCaption( trUtf8( "ADDKTOW  Lägga upp nytt konto" ) );

    TextLabelUserID = new QLabel( this, "TextLabelUserID" );
    TextLabelUserID->setGeometry( QRect( 10, 21, 81, 30 ) ); 
    TextLabelUserID->setText( trUtf8( "Bokföringsår:\n"
"(arid, 2 teck.)" ) );

    TextLabelNamn = new QLabel( this, "TextLabelNamn" );
    TextLabelNamn->setGeometry( QRect( 10, 60, 82, 21 ) ); 
    TextLabelNamn->setText( trUtf8( "Kontonummer:" ) );

    TextLabelGrupp = new QLabel( this, "TextLabelGrupp" );
    TextLabelGrupp->setGeometry( QRect( 10, 120, 84, 21 ) ); 
    TextLabelGrupp->setText( trUtf8( "Manuell (J/N):" ) );

    TextLabel1 = new QLabel( this, "TextLabel1" );
    TextLabel1->setGeometry( QRect( 10, 150, 81, 21 ) ); 
    TextLabel1->setText( trUtf8( "Momskod:" ) );

    TextLabel2 = new QLabel( this, "TextLabel2" );
    TextLabel2->setGeometry( QRect( 10, 180, 81, 21 ) ); 
    TextLabel2->setText( trUtf8( "SRUnr:" ) );

    TextLabelAvd = new QLabel( this, "TextLabelAvd" );
    TextLabelAvd->setGeometry( QRect( 10, 90, 90, 21 ) ); 
    TextLabelAvd->setText( trUtf8( "Benämning:" ) );

    TextLabel3 = new QLabel( this, "TextLabel3" );
    TextLabel3->setGeometry( QRect( 10, 210, 91, 21 ) ); 
    TextLabel3->setText( trUtf8( "Kostnadsställe:" ) );

    TextLabel4 = new QLabel( this, "TextLabel4" );
    TextLabel4->setGeometry( QRect( 10, 240, 91, 21 ) ); 
    TextLabel4->setText( trUtf8( "Projekt:" ) );

    TextLabel5 = new QLabel( this, "TextLabel5" );
    TextLabel5->setGeometry( QRect( 10, 270, 81, 21 ) ); 
    TextLabel5->setText( trUtf8( "Subkonto:" ) );

    TextLabel6 = new QLabel( this, "TextLabel6" );
    TextLabel6->setGeometry( QRect( 10, 300, 81, 21 ) ); 
    TextLabel6->setText( trUtf8( "Kontoplan:" ) );

    TextLabel9 = new QLabel( this, "TextLabel9" );
    TextLabel9->setGeometry( QRect( 170, 20, 71, 21 ) ); 
    TextLabel9->setText( trUtf8( "Obligatoriskt." ) );

    TextLabel9_2 = new QLabel( this, "TextLabel9_2" );
    TextLabel9_2->setGeometry( QRect( 170, 60, 71, 21 ) ); 
    TextLabel9_2->setText( trUtf8( "Obligatoriskt." ) );

    TextLabel9_3 = new QLabel( this, "TextLabel9_3" );
    TextLabel9_3->setGeometry( QRect( 170, 120, 71, 21 ) ); 
    TextLabel9_3->setText( trUtf8( "Obligatoriskt." ) );

    TextLabel9_4 = new QLabel( this, "TextLabel9_4" );
    TextLabel9_4->setGeometry( QRect( 170, 150, 71, 21 ) ); 
    TextLabel9_4->setText( trUtf8( "Obligatoriskt." ) );

    TextLabel9_5 = new QLabel( this, "TextLabel9_5" );
    TextLabel9_5->setGeometry( QRect( 170, 180, 71, 21 ) ); 
    TextLabel9_5->setText( trUtf8( "Obligatoriskt." ) );

    TextLabel9_6 = new QLabel( this, "TextLabel9_6" );
    TextLabel9_6->setGeometry( QRect( 260, 300, 71, 21 ) ); 
    TextLabel9_6->setText( trUtf8( "Obligatoriskt." ) );

    LineEditIB = new QLineEdit( this, "LineEditIB" );
    LineEditIB->setEnabled( FALSE );
    LineEditIB->setGeometry( QRect( 100, 330, 111, 22 ) ); 

    LineEditUB = new QLineEdit( this, "LineEditUB" );
    LineEditUB->setEnabled( FALSE );
    LineEditUB->setGeometry( QRect( 100, 360, 111, 22 ) ); 

    LineEditBar = new QLineEdit( this, "LineEditBar" );
    LineEditBar->setGeometry( QRect( 100, 20, 30, 22 ) ); 

    LineEditKontoNr = new QLineEdit( this, "LineEditKontoNr" );
    LineEditKontoNr->setGeometry( QRect( 100, 60, 50, 22 ) ); 

    LineEditBenamn = new QLineEdit( this, "LineEditBenamn" );
    LineEditBenamn->setGeometry( QRect( 100, 90, 310, 22 ) ); 

    LineEditManuell = new QLineEdit( this, "LineEditManuell" );
    LineEditManuell->setGeometry( QRect( 100, 120, 30, 22 ) ); 
    LineEditManuell->setText( trUtf8( "J" ) );

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

    PushButtonQuit = new QPushButton( this, "PushButtonQuit" );
    PushButtonQuit->setGeometry( QRect( 80, 400, 61, 21 ) ); 
    PushButtonQuit->setText( trUtf8( "Avsluta" ) );

    TextLabel8 = new QLabel( this, "TextLabel8" );
    TextLabel8->setGeometry( QRect( 10, 360, 90, 21 ) ); 
    TextLabel8->setText( trUtf8( "UB:" ) );

    TextLabel7 = new QLabel( this, "TextLabel7" );
    TextLabel7->setGeometry( QRect( 10, 330, 81, 21 ) ); 
    TextLabel7->setText( trUtf8( "IB:" ) );

    PushButtonOK = new QPushButton( this, "PushButtonOK" );
    PushButtonOK->setGeometry( QRect( 10, 400, 51, 21 ) ); 
    PushButtonOK->setText( trUtf8( "OK" ) );
    PushButtonOK->setDefault( TRUE );

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

