/****************************************************************************
** Form implementation generated from reading ui file 'Bokfstd.ui'
**
** Created: ons aug 13 08:41:21 2003
**      by: The User Interface Compiler ($Id: Bokfstd.cpp,v 1.2 2003/09/28 06:37:16 janpihlgren Exp $)
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
 *  Constructs a frmBokfstd as a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
frmBokfstd::frmBokfstd( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "frmBokfstd" );
    QFont f( font() );
    f.setFamily( "Helvetica" );
    setFont( f ); 

    TextLabel3 = new QLabel( this, "TextLabel3" );
    TextLabel3->setGeometry( QRect( 15, 100, 73, 21 ) );

    TextLabel2 = new QLabel( this, "TextLabel2" );
    TextLabel2->setGeometry( QRect( 15, 160, 94, 21 ) );

    TextLabel1_3 = new QLabel( this, "TextLabel1_3" );
    TextLabel1_3->setGeometry( QRect( 15, 435, 131, 21 ) );

    TextLabel1_2 = new QLabel( this, "TextLabel1_2" );
    TextLabel1_2->setGeometry( QRect( 15, 130, 71, 21 ) );

    TextLabel11 = new QLabel( this, "TextLabel11" );
    TextLabel11->setGeometry( QRect( 470, 80, 131, 21 ) );

    TextLabel1 = new QLabel( this, "TextLabel1" );
    TextLabel1->setGeometry( QRect( 15, 80, 42, 16 ) );
    TextLabel1->setFrameShape( QLabel::NoFrame );
    TextLabel1->setFrameShadow( QLabel::Plain );

    TextLabel4_2 = new QLabel( this, "TextLabel4_2" );
    TextLabel4_2->setGeometry( QRect( 350, 15, 120, 35 ) );
    QFont TextLabel4_2_font(  TextLabel4_2->font() );
    TextLabel4_2_font.setFamily( "Times [Adobe]" );
    TextLabel4_2_font.setPointSize( 18 );
    TextLabel4_2_font.setBold( TRUE );
    TextLabel4_2->setFont( TextLabel4_2_font ); 
    TextLabel4_2->setAlignment( int( QLabel::AlignBottom | QLabel::AlignLeft ) );
    TextLabel4_2->setIndent( 0 );

    TextLabel3_2 = new QLabel( this, "TextLabel3_2" );
    TextLabel3_2->setGeometry( QRect( 240, 15, 104, 35 ) );
    QFont TextLabel3_2_font(  TextLabel3_2->font() );
    TextLabel3_2_font.setFamily( "Times [Adobe]" );
    TextLabel3_2_font.setPointSize( 24 );
    TextLabel3_2_font.setBold( TRUE );
    TextLabel3_2->setFont( TextLabel3_2_font ); 
    TextLabel3_2->setScaledContents( FALSE );
    TextLabel3_2->setAlignment( int( QLabel::AlignBottom | QLabel::AlignLeft ) );
    TextLabel3_2->setIndent( 0 );

    LineEditVernr = new QLineEdit( this, "LineEditVernr" );
    LineEditVernr->setGeometry( QRect( 115, 130, 91, 22 ) );

    LineEditVerText = new QLineEdit( this, "LineEditVerText" );
    LineEditVerText->setGeometry( QRect( 115, 160, 345, 22 ) );

    TextLabelDate = new QLabel( this, "TextLabelDate" );
    TextLabelDate->setGeometry( QRect( 65, 80, 75, 16 ) );

    textLabelVersion = new QLabel( this, "textLabelVersion" );
    textLabelVersion->setGeometry( QRect( 15, 25, 95, 21 ) );

    LineEditBar = new QLineEdit( this, "LineEditBar" );
    LineEditBar->setGeometry( QRect( 115, 100, 41, 22 ) );

    PushButtonSluta = new QPushButton( this, "PushButtonSluta" );
    PushButtonSluta->setGeometry( QRect( 95, 460, 50, 20 ) );
    PushButtonSluta->setDefault( TRUE );

    PushButtonVerNej = new QPushButton( this, "PushButtonVerNej" );
    PushButtonVerNej->setGeometry( QRect( 55, 460, 31, 21 ) );
    PushButtonVerNej->setDefault( TRUE );

    PushButtonVerOK = new QPushButton( this, "PushButtonVerOK" );
    PushButtonVerOK->setGeometry( QRect( 15, 460, 31, 21 ) );
    PushButtonVerOK->setDefault( TRUE );

    PushButtonRadNej = new QPushButton( this, "PushButtonRadNej" );
    PushButtonRadNej->setGeometry( QRect( 415, 210, 30, 22 ) );
    PushButtonRadNej->setDefault( TRUE );

    TextLabel2_2 = new QLabel( this, "TextLabel2_2" );
    TextLabel2_2->setGeometry( QRect( 15, 190, 37, 16 ) );

    PushButtonRadOK = new QPushButton( this, "PushButtonRadOK" );
    PushButtonRadOK->setGeometry( QRect( 375, 210, 30, 21 ) );
    PushButtonRadOK->setDefault( TRUE );

    LineEditKst = new QLineEdit( this, "LineEditKst" );
    LineEditKst->setGeometry( QRect( 255, 210, 51, 22 ) );

    TextLabel3_3 = new QLabel( this, "TextLabel3_3" );
    TextLabel3_3->setGeometry( QRect( 55, 190, 50, 16 ) );

    TextLabel6 = new QLabel( this, "TextLabel6" );
    TextLabel6->setGeometry( QRect( 255, 190, 58, 16 ) );

    LineEditDK = new QLineEdit( this, "LineEditDK" );
    LineEditDK->setGeometry( QRect( 115, 210, 31, 22 ) );

    TextLabel7 = new QLabel( this, "TextLabel7" );
    TextLabel7->setGeometry( QRect( 315, 190, 53, 16 ) );

    LineEditKtonr = new QLineEdit( this, "LineEditKtonr" );
    LineEditKtonr->setGeometry( QRect( 55, 210, 51, 22 ) );

    LineEditBelopp = new QLineEdit( this, "LineEditBelopp" );
    LineEditBelopp->setGeometry( QRect( 155, 210, 91, 22 ) );

    TextLabel5 = new QLabel( this, "TextLabel5" );
    TextLabel5->setGeometry( QRect( 155, 190, 91, 16 ) );

    LineEditDiff = new QLineEdit( this, "LineEditDiff" );
    LineEditDiff->setGeometry( QRect( 155, 245, 91, 22 ) );

    LineEditRadnr = new QLineEdit( this, "LineEditRadnr" );
    LineEditRadnr->setGeometry( QRect( 15, 210, 31, 22 ) );

    TextLabel9 = new QLabel( this, "TextLabel9" );
    TextLabel9->setGeometry( QRect( 375, 190, 76, 16 ) );

    TextLabel4_3 = new QLabel( this, "TextLabel4_3" );
    TextLabel4_3->setGeometry( QRect( 115, 190, 30, 16 ) );

    LineEditSubKto = new QLineEdit( this, "LineEditSubKto" );
    LineEditSubKto->setGeometry( QRect( 315, 210, 51, 22 ) );

    TextLabel10 = new QLabel( this, "TextLabel10" );
    TextLabel10->setGeometry( QRect( 125, 245, 25, 21 ) );

    line5 = new QFrame( this, "line5" );
    line5->setGeometry( QRect( 10, 270, 441, 10 ) );
    line5->setFrameShape( QFrame::HLine );
    line5->setFrameShadow( QFrame::Sunken );
    line5->setFrameShape( QFrame::HLine );

    TextLabel12 = new QLabel( this, "TextLabel12" );
    TextLabel12->setGeometry( QRect( 15, 285, 173, 15 ) );

    ListViewVerrader = new QListView( this, "ListViewVerrader" );
    ListViewVerrader->addColumn( tr( "Radnr" ) );
    ListViewVerrader->addColumn( tr( "Kontonr" ) );
    ListViewVerrader->addColumn( tr( "D/K" ) );
    ListViewVerrader->addColumn( tr( "Belopp" ) );
    ListViewVerrader->addColumn( trUtf8( "KSTÄLLE" ) );
    ListViewVerrader->addColumn( tr( "SUBKTO" ) );
    ListViewVerrader->setGeometry( QRect( 15, 300, 445, 104 ) );

    ListViewKto = new QListView( this, "ListViewKto" );
    ListViewKto->addColumn( tr( "Kontonr" ) );
    ListViewKto->addColumn( tr( "Kontotext" ) );
    ListViewKto->setGeometry( QRect( 465, 100, 330, 380 ) );
    ListViewKto->setShowSortIndicator( TRUE );
    languageChange();
    resize( QSize(797, 488).expandedTo(minimumSizeHint()) );

    // signals and slots connections
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
    connect( LineEditBar, SIGNAL( lostFocus() ), this, SLOT( slotLineEditBar_lostFocus() ) );
    connect( LineEditKtonr, SIGNAL( lostFocus() ), this, SLOT( slotLineEditKtonr_lostFocus() ) );
    connect( LineEditDK, SIGNAL( lostFocus() ), this, SLOT( slotLineEditDK_lostFocus() ) );
    connect( LineEditKtonr, SIGNAL( textChanged(const QString&) ), this, SLOT( slotLineEditKtonr_textChanged() ) );
    connect( LineEditKst, SIGNAL( returnPressed() ), this, SLOT( slotLineEditKst_returnPressed() ) );
    connect( ListViewKto, SIGNAL( clicked(QListViewItem*) ), this, SLOT( slotPickupKtonr(QListViewItem*) ) );

    // tab order
    setTabOrder( LineEditBar, LineEditVernr );
    setTabOrder( LineEditVernr, LineEditVerText );
    setTabOrder( LineEditVerText, LineEditRadnr );
    setTabOrder( LineEditRadnr, LineEditKtonr );
    setTabOrder( LineEditKtonr, LineEditDK );
    setTabOrder( LineEditDK, LineEditBelopp );
    setTabOrder( LineEditBelopp, LineEditKst );
    setTabOrder( LineEditKst, LineEditSubKto );
    setTabOrder( LineEditSubKto, PushButtonRadOK );
    setTabOrder( PushButtonRadOK, PushButtonRadNej );
    setTabOrder( PushButtonRadNej, PushButtonVerOK );
    setTabOrder( PushButtonVerOK, PushButtonVerNej );
    setTabOrder( PushButtonVerNej, PushButtonSluta );
    setTabOrder( PushButtonSluta, LineEditDiff );
    setTabOrder( LineEditDiff, ListViewVerrader );
    setTabOrder( ListViewVerrader, ListViewKto );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
frmBokfstd::~frmBokfstd()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void frmBokfstd::languageChange()
{
    setCaption( tr( "BOKFORSW  Registrering av verifikationer. Standardversion. (0.41)" ) );
    QWhatsThis::add( this, tr( "Version: 0.3\n"
"2003-06-03" ) );
    TextLabel3->setText( trUtf8( "Bokföringsår" ) );
    TextLabel2->setText( tr( "Verifikationstext:" ) );
    TextLabel1_3->setText( trUtf8( "Godkänn verifikation" ) );
    TextLabel1_2->setText( tr( "Vernummer:" ) );
    TextLabel11->setText( trUtf8( "Kontoförteckning" ) );
    TextLabel1->setText( tr( "Datum:" ) );
    TextLabel4_2->setText( trUtf8( "Bokföring" ) );
    TextLabel3_2->setText( tr( "OLFIX" ) );
    QToolTip::add( LineEditVernr, trUtf8( "Verifikationsnummer sätts automatiskt. Senaste verifikationsnummer + 1." ) );
    QToolTip::add( LineEditVerText, trUtf8( "Beskrivande text vad verifikationen gäller." ) );
    TextLabelDate->setText( tr( "1988-07-31" ) );
    QToolTip::add( TextLabelDate, trUtf8( "Registreringsdatum för verifikationen." ) );
    textLabelVersion->setText( QString::null );
    QToolTip::add( textLabelVersion, tr( "Programmets versionsnummer." ) );
    QToolTip::add( LineEditBar, trUtf8( "Ange id för bokföringsår, två bokstäver." ) );
    QWhatsThis::add( LineEditBar, QString::null );
    PushButtonSluta->setText( tr( "Sluta" ) );
    PushButtonVerNej->setText( tr( "Nej" ) );
    PushButtonVerOK->setText( tr( "Ja" ) );
    PushButtonRadNej->setText( tr( "Nej" ) );
    TextLabel2_2->setText( tr( "Radnr" ) );
    PushButtonRadOK->setText( tr( "Ja" ) );
    QToolTip::add( LineEditKst, trUtf8( "Kostnadsställe. Ifylles vid behov." ) );
    TextLabel3_3->setText( tr( "Kontonr" ) );
    TextLabel6->setText( trUtf8( "KSTÄLLE" ) );
    QToolTip::add( LineEditDK, trUtf8( "D eller + för DEBET. K eller - för KREDIT" ) );
    TextLabel7->setText( tr( "SUBKTO" ) );
    QToolTip::add( LineEditKtonr, tr( "Kontonummer som ska konteras" ) );
    QToolTip::add( LineEditBelopp, trUtf8( "Belopp som ska konteras på aktuellt konto." ) );
    TextLabel5->setText( tr( "Belopp" ) );
    QToolTip::add( LineEditDiff, trUtf8( "Belopp som återstår att kontera" ) );
    QToolTip::add( LineEditRadnr, trUtf8( "Verifikationens radnr. Sätts automatiskt." ) );
    TextLabel9->setText( trUtf8( "Godkänn rad" ) );
    TextLabel4_3->setText( tr( "D/K" ) );
    QToolTip::add( LineEditSubKto, tr( "Underkonto. Ifylles vid behov." ) );
    TextLabel10->setText( tr( "Diff:" ) );
    TextLabel12->setText( tr( "Registrerade verifikationsrader" ) );
    ListViewVerrader->header()->setLabel( 0, tr( "Radnr" ) );
    ListViewVerrader->header()->setLabel( 1, tr( "Kontonr" ) );
    ListViewVerrader->header()->setLabel( 2, tr( "D/K" ) );
    ListViewVerrader->header()->setLabel( 3, tr( "Belopp" ) );
    ListViewVerrader->header()->setLabel( 4, trUtf8( "KSTÄLLE" ) );
    ListViewVerrader->header()->setLabel( 5, tr( "SUBKTO" ) );
    QToolTip::add( ListViewVerrader, trUtf8( "Visar redan utförda konteringar." ) );
    ListViewKto->header()->setLabel( 0, tr( "Kontonr" ) );
    ListViewKto->header()->setLabel( 1, tr( "Kontotext" ) );
    QToolTip::add( ListViewKto, trUtf8( "Kontoplan för aktuellt bokföringsår. Kan sorteras på Kontotext eller Kontonr (default)" ) );
}

