/****************************************************************************
** Form implementation generated from reading ui file 'Bokfstd.ui'
**
** Created: tor mar 20 08:01:32 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "Bokfstd.h"

#include <qvariant.h>
#include <qframe.h>
#include <qheader.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qlistview.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "Bokfstd.ui.h"

/* 
 *  Constructs a frmBokfstd which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
frmBokfstd::frmBokfstd( QWidget* parent,  const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "frmBokfstd" );
    resize( 799, 426 ); 
    setCaption( trUtf8( "OLFIX - BOKFORSW  Registrering av verifikationer. Standardversion." ) );

    TextLabel1 = new QLabel( this, "TextLabel1" );
    TextLabel1->setGeometry( QRect( 10, 20, 42, 16 ) ); 
    TextLabel1->setFrameShape( QLabel::NoFrame );
    TextLabel1->setFrameShadow( QLabel::Plain );
    TextLabel1->setText( trUtf8( "Datum:" ) );

    TextLabel3 = new QLabel( this, "TextLabel3" );
    TextLabel3->setGeometry( QRect( 10, 40, 73, 21 ) ); 
    TextLabel3->setText( trUtf8( "Bokföringsår" ) );

    TextLabel1_2 = new QLabel( this, "TextLabel1_2" );
    TextLabel1_2->setGeometry( QRect( 10, 70, 71, 21 ) ); 
    TextLabel1_2->setText( trUtf8( "Vernummer:" ) );

    TextLabel3_2 = new QLabel( this, "TextLabel3_2" );
    TextLabel3_2->setGeometry( QRect( 201, 0, 84, 26 ) ); 
    QFont TextLabel3_2_font(  TextLabel3_2->font() );
    TextLabel3_2_font.setFamily( "Times [Adobe]" );
    TextLabel3_2_font.setPointSize( 24 );
    TextLabel3_2_font.setBold( TRUE );
    TextLabel3_2->setFont( TextLabel3_2_font ); 
    TextLabel3_2->setText( trUtf8( "OLFIX" ) );
    TextLabel3_2->setAlignment( int( QLabel::AlignBottom ) );

    TextLabel4_2 = new QLabel( this, "TextLabel4_2" );
    TextLabel4_2->setGeometry( QRect( 290, 4, 80, 20 ) ); 
    QFont TextLabel4_2_font(  TextLabel4_2->font() );
    TextLabel4_2_font.setFamily( "Times [Adobe]" );
    TextLabel4_2_font.setPointSize( 18 );
    TextLabel4_2_font.setBold( TRUE );
    TextLabel4_2->setFont( TextLabel4_2_font ); 
    TextLabel4_2->setText( trUtf8( "Bokföring" ) );
    TextLabel4_2->setAlignment( int( QLabel::AlignBottom ) );

    TextLabel12 = new QLabel( this, "TextLabel12" );
    TextLabel12->setGeometry( QRect( 10, 130, 173, 21 ) ); 
    TextLabel12->setText( trUtf8( "Registrerade verifikationsrader" ) );

    TextLabel2 = new QLabel( this, "TextLabel2" );
    TextLabel2->setGeometry( QRect( 10, 100, 94, 21 ) ); 
    TextLabel2->setText( trUtf8( "Verifikationstext:" ) );

    TextLabel11 = new QLabel( this, "TextLabel11" );
    TextLabel11->setGeometry( QRect( 465, 20, 131, 21 ) ); 
    TextLabel11->setText( trUtf8( "Kontoförteckning" ) );

    TextLabel10 = new QLabel( this, "TextLabel10" );
    TextLabel10->setGeometry( QRect( 120, 260, 25, 21 ) ); 
    TextLabel10->setText( trUtf8( "Diff:" ) );

    PushButtonVerNej = new QPushButton( this, "PushButtonVerNej" );
    PushButtonVerNej->setGeometry( QRect( 50, 400, 31, 21 ) ); 
    PushButtonVerNej->setText( trUtf8( "Nej" ) );

    PushButtonSluta = new QPushButton( this, "PushButtonSluta" );
    PushButtonSluta->setGeometry( QRect( 90, 400, 50, 20 ) ); 
    PushButtonSluta->setText( trUtf8( "Sluta" ) );

    TextLabel1_3 = new QLabel( this, "TextLabel1_3" );
    TextLabel1_3->setGeometry( QRect( 10, 375, 131, 21 ) ); 
    TextLabel1_3->setText( trUtf8( "Godkänn verifikation" ) );

    PushButtonRadNej = new QPushButton( this, "PushButtonRadNej" );
    PushButtonRadNej->setGeometry( QRect( 410, 335, 30, 22 ) ); 
    PushButtonRadNej->setText( trUtf8( "Nej" ) );

    Line2 = new QFrame( this, "Line2" );
    Line2->setGeometry( QRect( 5, 290, 445, 10 ) ); 
    Line2->setFrameShape( QFrame::HLine );
    Line2->setFrameShadow( QFrame::Sunken );
    Line2->setFrameShape( QFrame::HLine );

    TextLabel9 = new QLabel( this, "TextLabel9" );
    TextLabel9->setGeometry( QRect( 370, 315, 76, 16 ) ); 
    TextLabel9->setText( trUtf8( "Godkänn rad" ) );

    TextLabel7 = new QLabel( this, "TextLabel7" );
    TextLabel7->setGeometry( QRect( 310, 315, 53, 16 ) ); 
    TextLabel7->setText( trUtf8( "SUBKTO" ) );

    TextLabel6 = new QLabel( this, "TextLabel6" );
    TextLabel6->setGeometry( QRect( 250, 315, 58, 16 ) ); 
    TextLabel6->setText( trUtf8( "KSTÄLLE" ) );

    TextLabel5 = new QLabel( this, "TextLabel5" );
    TextLabel5->setGeometry( QRect( 150, 315, 91, 16 ) ); 
    TextLabel5->setText( trUtf8( "Belopp" ) );

    TextLabel4_3 = new QLabel( this, "TextLabel4_3" );
    TextLabel4_3->setGeometry( QRect( 110, 315, 30, 16 ) ); 
    TextLabel4_3->setText( trUtf8( "D/K" ) );

    TextLabel3_3 = new QLabel( this, "TextLabel3_3" );
    TextLabel3_3->setGeometry( QRect( 50, 315, 50, 16 ) ); 
    TextLabel3_3->setText( trUtf8( "Kontonr" ) );

    TextLabel2_2 = new QLabel( this, "TextLabel2_2" );
    TextLabel2_2->setGeometry( QRect( 10, 315, 37, 16 ) ); 
    TextLabel2_2->setText( trUtf8( "Radnr" ) );

    TextLabel1_4 = new QLabel( this, "TextLabel1_4" );
    TextLabel1_4->setGeometry( QRect( 10, 300, 80, 16 ) ); 
    TextLabel1_4->setText( trUtf8( "Registrering" ) );

    LineEditBar = new QLineEdit( this, "LineEditBar" );
    LineEditBar->setGeometry( QRect( 110, 40, 41, 22 ) ); 

    TextLabelDate = new QLabel( this, "TextLabelDate" );
    TextLabelDate->setGeometry( QRect( 50, 20, 75, 16 ) ); 
    TextLabelDate->setText( trUtf8( "1988-07-31" ) );

    ListViewKto = new QListView( this, "ListViewKto" );
    ListViewKto->addColumn( trUtf8( "Kontonr" ) );
    ListViewKto->addColumn( trUtf8( "Kontotext" ) );
    ListViewKto->setGeometry( QRect( 460, 40, 330, 380 ) ); 

    LineEditVernr = new QLineEdit( this, "LineEditVernr" );
    LineEditVernr->setGeometry( QRect( 110, 70, 91, 22 ) ); 

    LineEditVerText = new QLineEdit( this, "LineEditVerText" );
    LineEditVerText->setGeometry( QRect( 110, 100, 345, 22 ) ); 

    LineEditRadnr = new QLineEdit( this, "LineEditRadnr" );
    LineEditRadnr->setGeometry( QRect( 10, 335, 31, 22 ) ); 

    LineEditKtonr = new QLineEdit( this, "LineEditKtonr" );
    LineEditKtonr->setGeometry( QRect( 50, 335, 51, 22 ) ); 

    LineEditDK = new QLineEdit( this, "LineEditDK" );
    LineEditDK->setGeometry( QRect( 110, 335, 31, 22 ) ); 

    LineEditBelopp = new QLineEdit( this, "LineEditBelopp" );
    LineEditBelopp->setGeometry( QRect( 150, 335, 91, 22 ) ); 

    LineEditKst = new QLineEdit( this, "LineEditKst" );
    LineEditKst->setGeometry( QRect( 250, 335, 51, 22 ) ); 

    LineEditSubKto = new QLineEdit( this, "LineEditSubKto" );
    LineEditSubKto->setGeometry( QRect( 310, 335, 51, 22 ) ); 

    LineEditDiff = new QLineEdit( this, "LineEditDiff" );
    LineEditDiff->setGeometry( QRect( 150, 260, 91, 22 ) ); 

    ListViewVerrader = new QListView( this, "ListViewVerrader" );
    ListViewVerrader->addColumn( trUtf8( "Radnr" ) );
    ListViewVerrader->addColumn( trUtf8( "Kontonr" ) );
    ListViewVerrader->addColumn( trUtf8( "D/K" ) );
    ListViewVerrader->addColumn( trUtf8( "Belopp" ) );
    ListViewVerrader->addColumn( trUtf8( "KSTÄLLE" ) );
    ListViewVerrader->addColumn( trUtf8( "SUBKTO" ) );
    ListViewVerrader->setGeometry( QRect( 10, 150, 445, 104 ) ); 

    PushButtonRadOK = new QPushButton( this, "PushButtonRadOK" );
    PushButtonRadOK->setGeometry( QRect( 370, 335, 30, 21 ) ); 
    PushButtonRadOK->setText( trUtf8( "Ja" ) );
    PushButtonRadOK->setDefault( TRUE );

    PushButtonVerOK = new QPushButton( this, "PushButtonVerOK" );
    PushButtonVerOK->setGeometry( QRect( 10, 400, 31, 21 ) ); 
    PushButtonVerOK->setText( trUtf8( "Ja" ) );
    PushButtonVerOK->setDefault( TRUE );

    // signals and slots connections
    connect( ListViewKto, SIGNAL( clicked(QListViewItem*) ), this, SLOT( slotPickupKtonr(QListViewItem*) ) );
    connect( LineEditKst, SIGNAL( returnPressed() ), this, SLOT( slotLineEditKst_returnPressed() ) );
    connect( LineEditBar, SIGNAL( returnPressed() ), this, SLOT( slotLineEditBar_returnPressed() ) );
    connect( LineEditVerText, SIGNAL( returnPressed() ), this, SLOT( slotLineEditVerText_returnPressed() ) );
    connect( LineEditDK, SIGNAL( returnPressed() ), this, SLOT( slotLineEditDK_returnPressed() ) );
    connect( LineEditBelopp, SIGNAL( returnPressed() ), this, SLOT( slotLineEditBelopp_returnPressed() ) );
    connect( PushButtonSluta, SIGNAL( clicked() ), this, SLOT( close() ) );
    connect( LineEditSubKto, SIGNAL( returnPressed() ), this, SLOT( slotLineEditSubKto_returnPressed() ) );
    connect( LineEditKtonr, SIGNAL( returnPressed() ), this, SLOT( slotLineEditKtonr_returnPressed() ) );
    connect( PushButtonRadOK, SIGNAL( clicked() ), this, SLOT( slotRadOK() ) );
    connect( PushButtonVerOK, SIGNAL( clicked() ), this, SLOT( slotVerOK() ) );
    connect( PushButtonVerNej, SIGNAL( clicked() ), this, SLOT( slotVerRemove() ) );

    // tab order
    setTabOrder( LineEditBar, LineEditVernr );
    setTabOrder( LineEditVernr, LineEditVerText );
    setTabOrder( LineEditVerText, PushButtonSluta );
    init();
}

/*  
 *  Destroys the object and frees any allocated resources
 */
frmBokfstd::~frmBokfstd()
{
    // no need to delete child widgets, Qt does it all for us
}

