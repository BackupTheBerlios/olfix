/****************************************************************************
** Form implementation generated from reading ui file 'frmlevfakt.ui'
**
** Created: mån aug 18 06:08:57 2003
**      by: The User Interface Compiler ($Id: frmlevfakt.cpp,v 1.2 2004/02/09 07:18:45 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "frmlevfakt.h"

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
#include "frmlevfakt.ui.h"

/* 
 *  Constructs a frmLevFakt as a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
frmLevFakt::frmLevFakt( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "frmLevFakt" );

    textLabel8 = new QLabel( this, "textLabel8" );
    textLabel8->setGeometry( QRect( 210, 10, 222, 16 ) );

    textLabel10 = new QLabel( this, "textLabel10" );
    textLabel10->setGeometry( QRect( 10, 35, 125, 16 ) );

    textLabel11 = new QLabel( this, "textLabel11" );
    textLabel11->setGeometry( QRect( 10, 60, 121, 16 ) );

    textLabel3 = new QLabel( this, "textLabel3" );
    textLabel3->setGeometry( QRect( 10, 160, 121, 16 ) );

    textLabel5 = new QLabel( this, "textLabel5" );
    textLabel5->setGeometry( QRect( 10, 185, 125, 16 ) );

    textLabel2 = new QLabel( this, "textLabel2" );
    textLabel2->setGeometry( QRect( 10, 135, 125, 16 ) );

    textLabel13 = new QLabel( this, "textLabel13" );
    textLabel13->setGeometry( QRect( 10, 85, 125, 16 ) );

    textLabel4 = new QLabel( this, "textLabel4" );
    textLabel4->setGeometry( QRect( 285, 130, 125, 21 ) );

    textLabel5_2 = new QLabel( this, "textLabel5_2" );
    textLabel5_2->setGeometry( QRect( 390, 85, 45, 16 ) );

    textLabel12 = new QLabel( this, "textLabel12" );
    textLabel12->setGeometry( QRect( 390, 60, 45, 16 ) );

    lineEditLevOrgNr = new QLineEdit( this, "lineEditLevOrgNr" );
    lineEditLevOrgNr->setEnabled( FALSE );
    lineEditLevOrgNr->setGeometry( QRect( 440, 5, 126, 23 ) );
    lineEditLevOrgNr->setPaletteForegroundColor( QColor( 0, 0, 0 ) );

    lineEditLevNamn = new QLineEdit( this, "lineEditLevNamn" );
    lineEditLevNamn->setEnabled( FALSE );
    lineEditLevNamn->setGeometry( QRect( 140, 30, 241, 23 ) );
    lineEditLevNamn->setPaletteForegroundColor( QColor( 0, 0, 0 ) );

    lineEditLevAdress = new QLineEdit( this, "lineEditLevAdress" );
    lineEditLevAdress->setEnabled( FALSE );
    lineEditLevAdress->setGeometry( QRect( 140, 55, 241, 23 ) );
    lineEditLevAdress->setPaletteForegroundColor( QColor( 0, 0, 0 ) );

    lineEditLevPostNr = new QLineEdit( this, "lineEditLevPostNr" );
    lineEditLevPostNr->setEnabled( FALSE );
    lineEditLevPostNr->setGeometry( QRect( 440, 55, 81, 23 ) );
    lineEditLevPostNr->setPaletteForegroundColor( QColor( 0, 0, 0 ) );

    lineEditLevPostAdr = new QLineEdit( this, "lineEditLevPostAdr" );
    lineEditLevPostAdr->setEnabled( FALSE );
    lineEditLevPostAdr->setGeometry( QRect( 140, 80, 241, 23 ) );
    lineEditLevPostAdr->setPaletteForegroundColor( QColor( 0, 0, 0 ) );

    lineEditLevLand = new QLineEdit( this, "lineEditLevLand" );
    lineEditLevLand->setEnabled( FALSE );
    lineEditLevLand->setGeometry( QRect( 440, 80, 126, 23 ) );
    lineEditLevLand->setPaletteForegroundColor( QColor( 0, 0, 0 ) );

    lineEditLevKundNr = new QLineEdit( this, "lineEditLevKundNr" );
    lineEditLevKundNr->setGeometry( QRect( 140, 130, 135, 23 ) );

    lineEditLevFakturaNr = new QLineEdit( this, "lineEditLevFakturaNr" );
    lineEditLevFakturaNr->setGeometry( QRect( 140, 155, 135, 23 ) );

    lineEditFakturadatum = new QLineEdit( this, "lineEditFakturadatum" );
    lineEditFakturadatum->setGeometry( QRect( 140, 180, 135, 23 ) );

    lineEditRegDatum = new QLineEdit( this, "lineEditRegDatum" );
    lineEditRegDatum->setGeometry( QRect( 416, 130, 105, 23 ) );

    textLabel6 = new QLabel( this, "textLabel6" );
    textLabel6->setGeometry( QRect( 10, 235, 125, 16 ) );

    lineEditLevFakturaText = new QLineEdit( this, "lineEditLevFakturaText" );
    lineEditLevFakturaText->setGeometry( QRect( 140, 255, 430, 23 ) );

    textLabel7 = new QLabel( this, "textLabel7" );
    textLabel7->setGeometry( QRect( 10, 260, 125, 16 ) );

    textLabel5_4 = new QLabel( this, "textLabel5_4" );
    textLabel5_4->setGeometry( QRect( 10, 210, 125, 16 ) );

    textLabel6_3 = new QLabel( this, "textLabel6_3" );
    textLabel6_3->setGeometry( QRect( 200, 210, 72, 16 ) );

    lineEditLevBetDatum = new QLineEdit( this, "lineEditLevBetDatum" );
    lineEditLevBetDatum->setGeometry( QRect( 140, 230, 135, 23 ) );

    line1 = new QFrame( this, "line1" );
    line1->setGeometry( QRect( 10, 110, 556, 16 ) );
    line1->setFrameShape( QFrame::HLine );
    line1->setFrameShadow( QFrame::Sunken );
    line1->setFrameShape( QFrame::HLine );

    pushButtonOK = new QPushButton( this, "pushButtonOK" );
    pushButtonOK->setGeometry( QRect( 10, 530, 51, 20 ) );
    pushButtonOK->setDefault( TRUE );

    pushButtonQuit = new QPushButton( this, "pushButtonQuit" );
    pushButtonQuit->setGeometry( QRect( 70, 530, 56, 21 ) );
    pushButtonQuit->setDefault( TRUE );

    textLabel2_3 = new QLabel( this, "textLabel2_3" );
    textLabel2_3->setGeometry( QRect( 200, 400, 131, 16 ) );

    textLabel7_2 = new QLabel( this, "textLabel7_2" );
    textLabel7_2->setGeometry( QRect( 10, 335, 125, 16 ) );

    lineEditLevMomskod = new QLineEdit( this, "lineEditLevMomskod" );
    lineEditLevMomskod->setGeometry( QRect( 495, 305, 45, 23 ) );

    lineEditValutaKurs = new QLineEdit( this, "lineEditValutaKurs" );
    lineEditValutaKurs->setGeometry( QRect( 300, 330, 51, 23 ) );

    lineEditValuta = new QLineEdit( this, "lineEditValuta" );
    lineEditValuta->setGeometry( QRect( 140, 330, 51, 23 ) );

    line2 = new QFrame( this, "line2" );
    line2->setGeometry( QRect( 10, 285, 560, 16 ) );
    line2->setFrameShape( QFrame::HLine );
    line2->setFrameShadow( QFrame::Sunken );
    line2->setFrameShape( QFrame::HLine );

    textLabel9 = new QLabel( this, "textLabel9" );
    textLabel9->setGeometry( QRect( 6, 360, 125, 16 ) );

    lineEditVernr = new QLineEdit( this, "lineEditVernr" );
    lineEditVernr->setEnabled( FALSE );
    lineEditVernr->setGeometry( QRect( 300, 305, 106, 23 ) );
    lineEditVernr->setPaletteForegroundColor( QColor( 0, 0, 0 ) );

    textLabel3_2 = new QLabel( this, "textLabel3_2" );
    textLabel3_2->setGeometry( QRect( 415, 310, 75, 16 ) );

    line3 = new QFrame( this, "line3" );
    line3->setGeometry( QRect( 6, 385, 565, 10 ) );
    line3->setFrameShape( QFrame::HLine );
    line3->setFrameShadow( QFrame::Sunken );
    line3->setFrameShape( QFrame::HLine );

    textLabel2_2 = new QLabel( this, "textLabel2_2" );
    textLabel2_2->setGeometry( QRect( 200, 310, 91, 16 ) );

    textLabel1_2 = new QLabel( this, "textLabel1_2" );
    textLabel1_2->setGeometry( QRect( 6, 310, 125, 16 ) );

    lineEditMoms = new QLineEdit( this, "lineEditMoms" );
    lineEditMoms->setEnabled( FALSE );
    lineEditMoms->setGeometry( QRect( 495, 330, 45, 23 ) );
    lineEditMoms->setPaletteForegroundColor( QColor( 0, 0, 0 ) );

    textLabel3_3 = new QLabel( this, "textLabel3_3" );
    textLabel3_3->setGeometry( QRect( 10, 425, 105, 16 ) );

    textLabel1_4 = new QLabel( this, "textLabel1_4" );
    textLabel1_4->setGeometry( QRect( 411, 335, 75, 16 ) );

    textLabel4_2 = new QLabel( this, "textLabel4_2" );
    textLabel4_2->setGeometry( QRect( 200, 425, 135, 16 ) );

    textLabel8_2 = new QLabel( this, "textLabel8_2" );
    textLabel8_2->setGeometry( QRect( 195, 335, 100, 16 ) );

    textLabel10_2 = new QLabel( this, "textLabel10_2" );
    textLabel10_2->setGeometry( QRect( 250, 360, 115, 16 ) );

    textLabel1_5 = new QLabel( this, "textLabel1_5" );
    textLabel1_5->setGeometry( QRect( 285, 235, 89, 16 ) );

    lineEditOCRnr = new QLineEdit( this, "lineEditOCRnr" );
    lineEditOCRnr->setGeometry( QRect( 376, 230, 195, 23 ) );

    textLabel1_3 = new QLabel( this, "textLabel1_3" );
    textLabel1_3->setGeometry( QRect( 10, 400, 101, 16 ) );

    textLabel5_3 = new QLabel( this, "textLabel5_3" );
    textLabel5_3->setGeometry( QRect( 10, 450, 105, 16 ) );

    textLabel6_2 = new QLabel( this, "textLabel6_2" );
    textLabel6_2->setGeometry( QRect( 200, 450, 135, 16 ) );

    lineEditBar = new QLineEdit( this, "lineEditBar" );
    lineEditBar->setGeometry( QRect( 140, 305, 51, 23 ) );

    lineEditBetalningsvilkor = new QLineEdit( this, "lineEditBetalningsvilkor" );
    lineEditBetalningsvilkor->setGeometry( QRect( 140, 205, 56, 23 ) );

    lineEditLevNr = new QLineEdit( this, "lineEditLevNr" );
    lineEditLevNr->setGeometry( QRect( 140, 5, 61, 23 ) );

    listViewLev = new QListView( this, "listViewLev" );
    listViewLev->addColumn( tr( "Levnummer" ) );
    listViewLev->addColumn( tr( "Levnamn" ) );
    listViewLev->setGeometry( QRect( 575, 5, 241, 275 ) );

    listViewKtonr = new QListView( this, "listViewKtonr" );
    listViewKtonr->addColumn( tr( "Kontonr" ) );
    listViewKtonr->addColumn( tr( "Kontonamn" ) );
    listViewKtonr->setGeometry( QRect( 575, 390, 245, 165 ) );

    lineEditFaktBelopp = new QLineEdit( this, "lineEditFaktBelopp" );
    lineEditFaktBelopp->setGeometry( QRect( 140, 355, 106, 23 ) );

    lineEditKreditKontoNr = new QLineEdit( this, "lineEditKreditKontoNr" );
    lineEditKreditKontoNr->setGeometry( QRect( 140, 395, 45, 23 ) );

    lineEditKreditBelopp = new QLineEdit( this, "lineEditKreditBelopp" );
    lineEditKreditBelopp->setGeometry( QRect( 340, 395, 106, 23 ) );

    lineEditMomsKontoNr = new QLineEdit( this, "lineEditMomsKontoNr" );
    lineEditMomsKontoNr->setGeometry( QRect( 140, 420, 45, 23 ) );

    lineEditMomsBelopp = new QLineEdit( this, "lineEditMomsBelopp" );
    lineEditMomsBelopp->setGeometry( QRect( 340, 420, 106, 23 ) );

    lineEditDebetKontoNr = new QLineEdit( this, "lineEditDebetKontoNr" );
    lineEditDebetKontoNr->setGeometry( QRect( 140, 445, 45, 23 ) );

    lineEditDebetBelopp = new QLineEdit( this, "lineEditDebetBelopp" );
    lineEditDebetBelopp->setGeometry( QRect( 340, 445, 106, 23 ) );

    textLabel1 = new QLabel( this, "textLabel1" );
    textLabel1->setGeometry( QRect( 10, 10, 123, 16 ) );
    textLabel1->setFrameShape( QLabel::NoFrame );
    textLabel1->setFrameShadow( QLabel::Plain );

    textLabelAutokonto = new QLabel( this, "textLabelAutokonto" );
    textLabelAutokonto->setEnabled( TRUE );
    textLabelAutokonto->setGeometry( QRect( 140, 471, 430, 75 ) );
    textLabelAutokonto->setAlignment( int( QLabel::WordBreak | QLabel::AlignCenter ) );
    languageChange();
    resize( QSize(826, 560).expandedTo(minimumSizeHint()) );

    // signals and slots connections
    connect( lineEditLevFakturaNr, SIGNAL( returnPressed() ), this, SLOT( slotlineEditFaktNr_returnPressed() ) );
    connect( lineEditFakturadatum, SIGNAL( returnPressed() ), this, SLOT( slotlineEditFakturadatum_returnPressed() ) );
    connect( lineEditLevBetDatum, SIGNAL( returnPressed() ), this, SLOT( slotlineEditLevBetDatum_returnPressed() ) );
    connect( lineEditLevFakturaText, SIGNAL( returnPressed() ), this, SLOT( slotlineEditLevFakturaText_returnPressed() ) );
    connect( lineEditLevKundNr, SIGNAL( returnPressed() ), this, SLOT( slotlineEditLevKundNr_returnPressed() ) );
    connect( lineEditRegDatum, SIGNAL( returnPressed() ), this, SLOT( slotlineEditRegDatum_returnPressed() ) );
    connect( lineEditLevMomskod, SIGNAL( returnPressed() ), this, SLOT( slotlineEditLevMomskod_returnPressed() ) );
    connect( lineEditKreditKontoNr, SIGNAL( returnPressed() ), this, SLOT( slotlineEditKreditKontoNr_returnPressed() ) );
    connect( lineEditKreditBelopp, SIGNAL( returnPressed() ), this, SLOT( slotlineEditKreditBelopp_returnPressed() ) );
    connect( lineEditMomsKontoNr, SIGNAL( returnPressed() ), this, SLOT( slotlineEditMomsKtoNr_returnPressed() ) );
    connect( lineEditMomsBelopp, SIGNAL( returnPressed() ), this, SLOT( slotlineEditMomsBelopp_returnPressed() ) );
    connect( lineEditDebetKontoNr, SIGNAL( returnPressed() ), this, SLOT( slotlineEditDebetKontoNr_returnPressed() ) );
    connect( lineEditLevNr, SIGNAL( returnPressed() ), this, SLOT( slotlineEditLevNr_returnPressed() ) );
    connect( lineEditBar, SIGNAL( returnPressed() ), this, SLOT( slotlineEditBar_returnPressed() ) );
    connect( pushButtonQuit, SIGNAL( clicked() ), this, SLOT( close() ) );
    connect( lineEditDebetBelopp, SIGNAL( returnPressed() ), this, SLOT( slotlineEditDebetBelopp_returnPressed() ) );
    connect( pushButtonOK, SIGNAL( clicked() ), this, SLOT( slotUpdateLevresk() ) );
    connect( lineEditBetalningsvilkor, SIGNAL( returnPressed() ), this, SLOT( slotlineEditBetvilk_returnPressed() ) );
    connect( lineEditValuta, SIGNAL( returnPressed() ), this, SLOT( slotlineEditValuta_returnPressed() ) );
    connect( lineEditValutaKurs, SIGNAL( returnPressed() ), this, SLOT( slotlineEditValutaKurs_returnPressed() ) );
    connect( lineEditFaktBelopp, SIGNAL( returnPressed() ), this, SLOT( slotlineEditFaktBelopp_returnPressed() ) );
    connect( lineEditOCRnr, SIGNAL( returnPressed() ), this, SLOT( slotlineEditOCRnr_returnPressed() ) );
    connect( listViewLev, SIGNAL( clicked(QListViewItem*) ), this, SLOT( slotPickupLevnr(QListViewItem*) ) );
    connect( listViewKtonr, SIGNAL( clicked(QListViewItem*) ), this, SLOT( slotPickupKtonr(QListViewItem*) ) );

    // tab order
    setTabOrder( lineEditLevNr, lineEditLevKundNr );
    setTabOrder( lineEditLevKundNr, lineEditRegDatum );
    setTabOrder( lineEditRegDatum, lineEditLevFakturaNr );
    setTabOrder( lineEditLevFakturaNr, lineEditFakturadatum );
    setTabOrder( lineEditFakturadatum, lineEditLevBetDatum );
    setTabOrder( lineEditLevBetDatum, lineEditLevFakturaText );
    setTabOrder( lineEditLevFakturaText, lineEditBar );
    setTabOrder( lineEditBar, lineEditLevMomskod );
    setTabOrder( lineEditLevMomskod, lineEditKreditKontoNr );
    setTabOrder( lineEditKreditKontoNr, lineEditKreditBelopp );
    setTabOrder( lineEditKreditBelopp, lineEditMomsKontoNr );
    setTabOrder( lineEditMomsKontoNr, lineEditMomsBelopp );
    setTabOrder( lineEditMomsBelopp, lineEditDebetKontoNr );
    setTabOrder( lineEditDebetKontoNr, lineEditDebetBelopp );
    setTabOrder( lineEditDebetBelopp, pushButtonOK );
    setTabOrder( pushButtonOK, pushButtonQuit );
    setTabOrder( pushButtonQuit, lineEditLevOrgNr );
    setTabOrder( lineEditLevOrgNr, lineEditLevNamn );
    setTabOrder( lineEditLevNamn, lineEditLevAdress );
    setTabOrder( lineEditLevAdress, lineEditLevPostNr );
    setTabOrder( lineEditLevPostNr, lineEditLevPostAdr );
    setTabOrder( lineEditLevPostAdr, lineEditVernr );
    setTabOrder( lineEditVernr, lineEditLevLand );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
frmLevFakt::~frmLevFakt()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void frmLevFakt::languageChange()
{
    setCaption( trUtf8( "LEVFAKTW - Registrera leverantörsfaktura." ) );
    textLabel8->setText( trUtf8( "Leverantörens organisationsnummer:" ) );
    textLabel10->setText( trUtf8( "Leverantörsnamn:" ) );
    textLabel11->setText( tr( "Adress:" ) );
    textLabel3->setText( tr( "Fakturanummer:" ) );
    textLabel5->setText( tr( "Fakturadatum:" ) );
    textLabel2->setText( tr( "Kundnummer:" ) );
    textLabel13->setText( tr( "Postadress:" ) );
    textLabel4->setText( tr( "Registreringsdatum:" ) );
    textLabel5_2->setText( tr( "Land:" ) );
    textLabel12->setText( tr( "Postnr:" ) );
    QToolTip::add( lineEditLevKundNr, trUtf8( "Mitt kundnummer hos leverantören." ) );
    textLabel6->setText( trUtf8( "Förfallodatum:" ) );
    textLabel7->setText( tr( "Fakturatext:" ) );
    textLabel5_4->setText( tr( "Betalningsvillkor:" ) );
    textLabel6_3->setText( tr( "dagar netto" ) );
    pushButtonOK->setText( tr( "OK" ) );
    pushButtonQuit->setText( tr( "Avsluta" ) );
    textLabel2_3->setText( trUtf8( "Bokfört belopp (SEK):" ) );
    textLabel7_2->setText( tr( "Valuta:" ) );
    textLabel9->setText( tr( " Fakturabelopp:" ) );
    textLabel3_2->setText( tr( "Momskod:" ) );
    textLabel2_2->setText( tr( "Verifikationsnr:" ) );
    textLabel1_2->setText( trUtf8( " Bokföringsår:" ) );
    textLabel3_3->setText( tr( "Momskontonr:" ) );
    textLabel1_4->setText( tr( " Moms %" ) );
    textLabel4_2->setText( tr( "Momsbelopp   (SEK):" ) );
    textLabel8_2->setText( tr( "Valutakurs:" ) );
    textLabel10_2->setText( tr( "i fakturans valuta." ) );
    textLabel1_5->setText( tr( "OCR nummer:" ) );
    textLabel1_3->setText( tr( "Kontonr: (Kredit)" ) );
    textLabel5_3->setText( tr( "Kontonr: (Debet)" ) );
    textLabel6_2->setText( tr( "Debetbelopp    (SEK):" ) );
    listViewLev->header()->setLabel( 0, tr( "Levnummer" ) );
    listViewLev->header()->setLabel( 1, tr( "Levnamn" ) );
    listViewKtonr->header()->setLabel( 0, tr( "Kontonr" ) );
    listViewKtonr->header()->setLabel( 1, tr( "Kontonamn" ) );
    textLabel1->setText( trUtf8( "LeverantörsID:" ) );
    textLabelAutokonto->setText( trUtf8( "<font color=\"#0000ff\" size=\"+3\"><b>Ingen kontering till bokföringen kommer att ske!</b>\n"
"</font>" ) );
}

