/****************************************************************************
** Form implementation generated from reading ui file 'frmaddkund.ui'
**
** Created: tor sep 11 04:33:18 2003
**      by: The User Interface Compiler ($Id: frmaddkund.cpp,v 1.1 2003/09/28 06:06:24 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "frmaddkund.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "frmaddkund.ui.h"

/* 
 *  Constructs a frmAddKund as a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
frmAddKund::frmAddKund( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "frmAddKund" );

    pushButtonAvbryt = new QPushButton( this, "pushButtonAvbryt" );
    pushButtonAvbryt->setGeometry( QRect( 75, 615, 60, 21 ) );
    pushButtonAvbryt->setDefault( TRUE );

    textLabel1_5 = new QLabel( this, "textLabel1_5" );
    textLabel1_5->setGeometry( QRect( 10, 5, 16, 20 ) );
    textLabel1_5->setPaletteForegroundColor( QColor( 255, 0, 0 ) );

    textLabel1_2 = new QLabel( this, "textLabel1_2" );
    textLabel1_2->setGeometry( QRect( 25, 5, 167, 16 ) );

    textLabel1 = new QLabel( this, "textLabel1" );
    textLabel1->setGeometry( QRect( 10, 40, 110, 16 ) );
    textLabel1->setFrameShape( QLabel::NoFrame );
    textLabel1->setFrameShadow( QLabel::Plain );

    textLabel12 = new QLabel( this, "textLabel12" );
    textLabel12->setGeometry( QRect( 10, 265, 124, 16 ) );

    textLabel5_2_3 = new QLabel( this, "textLabel5_2_3" );
    textLabel5_2_3->setGeometry( QRect( 195, 440, 125, 16 ) );

    textLabel6_2_4 = new QLabel( this, "textLabel6_2_4" );
    textLabel6_2_4->setGeometry( QRect( 380, 490, 110, 16 ) );

    textLabel3 = new QLabel( this, "textLabel3" );
    textLabel3->setGeometry( QRect( 10, 65, 110, 16 ) );

    textLabel4 = new QLabel( this, "textLabel4" );
    textLabel4->setGeometry( QRect( 10, 90, 125, 16 ) );

    textLabel6_2 = new QLabel( this, "textLabel6_2" );
    textLabel6_2->setGeometry( QRect( 10, 465, 125, 16 ) );

    textLabel8_2_2_2 = new QLabel( this, "textLabel8_2_2_2" );
    textLabel8_2_2_2->setGeometry( QRect( 195, 540, 125, 16 ) );

    textLabel7 = new QLabel( this, "textLabel7" );
    textLabel7->setGeometry( QRect( 10, 165, 125, 16 ) );

    textLabel7_2 = new QLabel( this, "textLabel7_2" );
    textLabel7_2->setGeometry( QRect( 10, 490, 125, 16 ) );

    textLabel8_2_2_3 = new QLabel( this, "textLabel8_2_2_3" );
    textLabel8_2_2_3->setGeometry( QRect( 10, 565, 125, 16 ) );

    textLabel5 = new QLabel( this, "textLabel5" );
    textLabel5->setGeometry( QRect( 10, 115, 125, 16 ) );

    textLabel3_3 = new QLabel( this, "textLabel3_3" );
    textLabel3_3->setGeometry( QRect( 10, 365, 125, 16 ) );

    textLabel3_2 = new QLabel( this, "textLabel3_2" );
    textLabel3_2->setGeometry( QRect( 10, 440, 125, 16 ) );

    textLabel5_2_2 = new QLabel( this, "textLabel5_2_2" );
    textLabel5_2_2->setGeometry( QRect( 380, 390, 110, 16 ) );

    textLabel9 = new QLabel( this, "textLabel9" );
    textLabel9->setGeometry( QRect( 10, 215, 125, 16 ) );

    textLabel1_4 = new QLabel( this, "textLabel1_4" );
    textLabel1_4->setGeometry( QRect( 10, 315, 125, 16 ) );

    textLabel11 = new QLabel( this, "textLabel11" );
    textLabel11->setGeometry( QRect( 10, 240, 125, 16 ) );

    textLabel6_2_3 = new QLabel( this, "textLabel6_2_3" );
    textLabel6_2_3->setGeometry( QRect( 380, 465, 110, 16 ) );

    textLabel8 = new QLabel( this, "textLabel8" );
    textLabel8->setGeometry( QRect( 10, 190, 125, 16 ) );

    textLabel1_5_3 = new QLabel( this, "textLabel1_5_3" );
    textLabel1_5_3->setGeometry( QRect( 115, 65, 16, 20 ) );
    textLabel1_5_3->setPaletteForegroundColor( QColor( 255, 0, 0 ) );

    textLabel2_2 = new QLabel( this, "textLabel2_2" );
    textLabel2_2->setGeometry( QRect( 10, 340, 125, 16 ) );

    textLabel6_2_2 = new QLabel( this, "textLabel6_2_2" );
    textLabel6_2_2->setGeometry( QRect( 195, 465, 125, 16 ) );

    textLabel7_2_2 = new QLabel( this, "textLabel7_2_2" );
    textLabel7_2_2->setGeometry( QRect( 195, 490, 125, 16 ) );

    textLabel6 = new QLabel( this, "textLabel6" );
    textLabel6->setGeometry( QRect( 10, 140, 125, 16 ) );

    textLabel13 = new QLabel( this, "textLabel13" );
    textLabel13->setGeometry( QRect( 10, 290, 125, 16 ) );

    textLabel4_2_2 = new QLabel( this, "textLabel4_2_2" );
    textLabel4_2_2->setGeometry( QRect( 10, 390, 125, 16 ) );

    textLabel8_2_2 = new QLabel( this, "textLabel8_2_2" );
    textLabel8_2_2->setGeometry( QRect( 10, 540, 125, 16 ) );

    textLabel4_2 = new QLabel( this, "textLabel4_2" );
    textLabel4_2->setGeometry( QRect( 10, 415, 125, 16 ) );

    textLabel8_2 = new QLabel( this, "textLabel8_2" );
    textLabel8_2->setGeometry( QRect( 10, 515, 125, 16 ) );

    textLabel1_3 = new QLabel( this, "textLabel1_3" );
    textLabel1_3->setGeometry( QRect( 220, 35, 95, 16 ) );

    textLabel1_5_2 = new QLabel( this, "textLabel1_5_2" );
    textLabel1_5_2->setGeometry( QRect( 115, 40, 16, 20 ) );
    textLabel1_5_2->setPaletteForegroundColor( QColor( 255, 0, 0 ) );

    lineEditKundAdress = new QLineEdit( this, "lineEditKundAdress" );
    lineEditKundAdress->setGeometry( QRect( 140, 85, 201, 23 ) );

    lineEditKundBetvilk = new QLineEdit( this, "lineEditKundBetvilk" );
    lineEditKundBetvilk->setGeometry( QRect( 140, 410, 36, 23 ) );

    lineEditValuta = new QLineEdit( this, "lineEditValuta" );
    lineEditValuta->setGeometry( QRect( 140, 435, 36, 23 ) );

    lineEditSprakkod = new QLineEdit( this, "lineEditSprakkod" );
    lineEditSprakkod->setGeometry( QRect( 325, 435, 36, 23 ) );

    lineEditOrdererk = new QLineEdit( this, "lineEditOrdererk" );
    lineEditOrdererk->setGeometry( QRect( 140, 460, 19, 23 ) );

    lineEditPlocklista = new QLineEdit( this, "lineEditPlocklista" );
    lineEditPlocklista->setGeometry( QRect( 325, 460, 19, 23 ) );

    lineEditFoljesedel = new QLineEdit( this, "lineEditFoljesedel" );
    lineEditFoljesedel->setGeometry( QRect( 495, 460, 19, 23 ) );

    lineEditExpAvgift = new QLineEdit( this, "lineEditExpAvgift" );
    lineEditExpAvgift->setGeometry( QRect( 140, 485, 19, 23 ) );

    lineEditFraktAvgift = new QLineEdit( this, "lineEditFraktAvgift" );
    lineEditFraktAvgift->setGeometry( QRect( 325, 485, 19, 23 ) );

    lineEditKravbrev = new QLineEdit( this, "lineEditKravbrev" );
    lineEditKravbrev->setGeometry( QRect( 495, 485, 19, 23 ) );

    lineEditDrojRenta = new QLineEdit( this, "lineEditDrojRenta" );
    lineEditDrojRenta->setGeometry( QRect( 140, 535, 19, 23 ) );

    lineEditDrojFaktura = new QLineEdit( this, "lineEditDrojFaktura" );
    lineEditDrojFaktura->setGeometry( QRect( 325, 535, 19, 23 ) );

    pushButtonOK = new QPushButton( this, "pushButtonOK" );
    pushButtonOK->setGeometry( QRect( 10, 615, 56, 21 ) );
    pushButtonOK->setDefault( TRUE );

    lineEditKundLevsett = new QLineEdit( this, "lineEditKundLevsett" );
    lineEditKundLevsett->setGeometry( QRect( 495, 385, 36, 23 ) );

    textLabel5_2 = new QLabel( this, "textLabel5_2" );
    textLabel5_2->setGeometry( QRect( 195, 390, 125, 16 ) );

    lineEditKundLevvilk = new QLineEdit( this, "lineEditKundLevvilk" );
    lineEditKundLevvilk->setGeometry( QRect( 325, 385, 35, 23 ) );

    textLabel1_6 = new QLabel( this, "textLabel1_6" );
    textLabel1_6->setGeometry( QRect( 195, 365, 125, 16 ) );

    lineEditKundNr = new QLineEdit( this, "lineEditKundNr" );
    lineEditKundNr->setGeometry( QRect( 140, 35, 75, 23 ) );

    lineEditKundNamn = new QLineEdit( this, "lineEditKundNamn" );
    lineEditKundNamn->setGeometry( QRect( 140, 60, 201, 23 ) );

    lineEditKundPostnr = new QLineEdit( this, "lineEditKundPostnr" );
    lineEditKundPostnr->setGeometry( QRect( 140, 110, 75, 23 ) );

    lineEditKundPostAdress = new QLineEdit( this, "lineEditKundPostAdress" );
    lineEditKundPostAdress->setGeometry( QRect( 140, 135, 201, 23 ) );

    lineEditKundLand = new QLineEdit( this, "lineEditKundLand" );
    lineEditKundLand->setGeometry( QRect( 140, 160, 201, 23 ) );

    lineEditKundTftnNr = new QLineEdit( this, "lineEditKundTftnNr" );
    lineEditKundTftnNr->setGeometry( QRect( 140, 185, 111, 23 ) );

    lineEditKundFaxNr = new QLineEdit( this, "lineEditKundFaxNr" );
    lineEditKundFaxNr->setGeometry( QRect( 140, 210, 111, 23 ) );

    lineEditKundEmail = new QLineEdit( this, "lineEditKundEmail" );
    lineEditKundEmail->setGeometry( QRect( 140, 235, 206, 23 ) );

    lineEditKundErRef = new QLineEdit( this, "lineEditKundErRef" );
    lineEditKundErRef->setGeometry( QRect( 140, 260, 206, 23 ) );

    lineEditErRefTfnNr = new QLineEdit( this, "lineEditErRefTfnNr" );
    lineEditErRefTfnNr->setGeometry( QRect( 140, 285, 110, 23 ) );

    lineEditKundErRefEmail = new QLineEdit( this, "lineEditKundErRefEmail" );
    lineEditKundErRefEmail->setGeometry( QRect( 140, 310, 206, 23 ) );

    lineEditKundSeljare = new QLineEdit( this, "lineEditKundSeljare" );
    lineEditKundSeljare->setGeometry( QRect( 140, 335, 206, 23 ) );

    lineEditKundDistrikt = new QLineEdit( this, "lineEditKundDistrikt" );
    lineEditKundDistrikt->setGeometry( QRect( 140, 360, 35, 23 ) );

    lineEditKundKategori = new QLineEdit( this, "lineEditKundKategori" );
    lineEditKundKategori->setGeometry( QRect( 325, 360, 35, 23 ) );

    lineEditKreditlimit = new QLineEdit( this, "lineEditKreditlimit" );
    lineEditKreditlimit->setGeometry( QRect( 140, 510, 101, 23 ) );

    lineEditFriText = new QLineEdit( this, "lineEditFriText" );
    lineEditFriText->setGeometry( QRect( 140, 560, 395, 23 ) );

    lineEditKundStdLevplats = new QLineEdit( this, "lineEditKundStdLevplats" );
    lineEditKundStdLevplats->setGeometry( QRect( 140, 385, 36, 23 ) );
    languageChange();
    resize( QSize(545, 649).expandedTo(minimumSizeHint()) );

    // signals and slots connections
    connect( pushButtonAvbryt, SIGNAL( clicked() ), this, SLOT( close() ) );
    connect( lineEditKundNr, SIGNAL( returnPressed() ), this, SLOT( lineEditKundNr_returnPressed() ) );
    connect( lineEditKundNamn, SIGNAL( returnPressed() ), this, SLOT( lineEditKundNamn_returnPressed() ) );
    connect( lineEditKundAdress, SIGNAL( returnPressed() ), this, SLOT( lineEditKundAdress_returnPressed() ) );
    connect( lineEditKundPostnr, SIGNAL( returnPressed() ), this, SLOT( lineEditKundPostnr_returnPressed() ) );
    connect( lineEditKundPostAdress, SIGNAL( returnPressed() ), this, SLOT( lineEditKundPostAdress_returnPressed() ) );
    connect( lineEditKundLand, SIGNAL( returnPressed() ), this, SLOT( lineEditKundLand_returnPressed() ) );
    connect( lineEditKundTftnNr, SIGNAL( returnPressed() ), this, SLOT( lineEditKundTftnNr_returnPressed() ) );
    connect( lineEditKundFaxNr, SIGNAL( returnPressed() ), this, SLOT( lineEditKundFaxNr_returnPressed() ) );
    connect( lineEditKundEmail, SIGNAL( returnPressed() ), this, SLOT( lineEditKundEmail_returnPressed() ) );
    connect( lineEditKundErRef, SIGNAL( returnPressed() ), this, SLOT( lineEditKundErRef_returnPressed() ) );
    connect( lineEditErRefTfnNr, SIGNAL( returnPressed() ), this, SLOT( lineEditErRefTfnNr_returnPressed() ) );
    connect( lineEditKundErRefEmail, SIGNAL( returnPressed() ), this, SLOT( lineEditKundErRefEmail_returnPressed() ) );
    connect( lineEditKundSeljare, SIGNAL( returnPressed() ), this, SLOT( lineEditKundSeljare_returnPressed() ) );
    connect( lineEditKundDistrikt, SIGNAL( returnPressed() ), this, SLOT( lineEditKundDistrikt_returnPressed() ) );
    connect( lineEditKundStdLevplats, SIGNAL( returnPressed() ), this, SLOT( lineEditKundStdLevplats_returnPressed() ) );
    connect( lineEditKundLevvilk, SIGNAL( returnPressed() ), this, SLOT( lineEditKundLevvilk_returnPressed() ) );
    connect( lineEditKundLevsett, SIGNAL( returnPressed() ), this, SLOT( lineEditKundLevsett_returnPressed() ) );
    connect( lineEditKundBetvilk, SIGNAL( returnPressed() ), this, SLOT( lineEditKundBetvilk_returnPressed() ) );
    connect( lineEditOrdererk, SIGNAL( returnPressed() ), this, SLOT( lineEditOrdererk_returnPressed() ) );
    connect( lineEditPlocklista, SIGNAL( returnPressed() ), this, SLOT( lineEditPlocklista_returnPressed() ) );
    connect( lineEditFoljesedel, SIGNAL( returnPressed() ), this, SLOT( lineEditFoljesedel_returnPressed() ) );
    connect( lineEditExpAvgift, SIGNAL( returnPressed() ), this, SLOT( lineEditExpAvgift_returnPressed() ) );
    connect( lineEditFraktAvgift, SIGNAL( returnPressed() ), this, SLOT( lineEditFraktAvgift_returnPressed() ) );
    connect( lineEditKravbrev, SIGNAL( returnPressed() ), this, SLOT( lineEditKravbrev_returnPressed() ) );
    connect( lineEditKreditlimit, SIGNAL( returnPressed() ), this, SLOT( lineEditKreditlimit_returnPressed() ) );
    connect( lineEditDrojRenta, SIGNAL( returnPressed() ), this, SLOT( lineEditDrojRenta_returnPressed() ) );
    connect( lineEditDrojFaktura, SIGNAL( returnPressed() ), this, SLOT( lineEditDrojFaktura_returnPressed() ) );
    connect( lineEditFriText, SIGNAL( returnPressed() ), this, SLOT( lineEditFriText_returnPressed() ) );
    connect( pushButtonOK, SIGNAL( clicked() ), this, SLOT( pushButtonOK_clicked() ) );
    connect( lineEditValuta, SIGNAL( returnPressed() ), this, SLOT( lineEditValuta_returnPressed() ) );
    connect( lineEditSprakkod, SIGNAL( returnPressed() ), this, SLOT( lineEditSprakkod_returnPressed() ) );
    connect( lineEditKundKategori, SIGNAL( returnPressed() ), this, SLOT( lineEditKundKategori_returnPressed() ) );

    // tab order
    setTabOrder( lineEditKundNr, lineEditKundNamn );
    setTabOrder( lineEditKundNamn, lineEditKundAdress );
    setTabOrder( lineEditKundAdress, lineEditKundPostnr );
    setTabOrder( lineEditKundPostnr, lineEditKundPostAdress );
    setTabOrder( lineEditKundPostAdress, lineEditKundLand );
    setTabOrder( lineEditKundLand, lineEditKundTftnNr );
    setTabOrder( lineEditKundTftnNr, lineEditKundFaxNr );
    setTabOrder( lineEditKundFaxNr, lineEditKundEmail );
    setTabOrder( lineEditKundEmail, lineEditKundErRef );
    setTabOrder( lineEditKundErRef, lineEditErRefTfnNr );
    setTabOrder( lineEditErRefTfnNr, lineEditKundErRefEmail );
    setTabOrder( lineEditKundErRefEmail, lineEditKundSeljare );
    setTabOrder( lineEditKundSeljare, lineEditKundDistrikt );
    setTabOrder( lineEditKundDistrikt, lineEditKundStdLevplats );
    setTabOrder( lineEditKundStdLevplats, lineEditKundLevvilk );
    setTabOrder( lineEditKundLevvilk, lineEditKundLevsett );
    setTabOrder( lineEditKundLevsett, lineEditKundBetvilk );
    setTabOrder( lineEditKundBetvilk, lineEditValuta );
    setTabOrder( lineEditValuta, lineEditSprakkod );
    setTabOrder( lineEditSprakkod, lineEditOrdererk );
    setTabOrder( lineEditOrdererk, lineEditPlocklista );
    setTabOrder( lineEditPlocklista, lineEditFoljesedel );
    setTabOrder( lineEditFoljesedel, lineEditExpAvgift );
    setTabOrder( lineEditExpAvgift, lineEditFraktAvgift );
    setTabOrder( lineEditFraktAvgift, lineEditKravbrev );
    setTabOrder( lineEditKravbrev, lineEditKreditlimit );
    setTabOrder( lineEditKreditlimit, lineEditDrojRenta );
    setTabOrder( lineEditDrojRenta, lineEditDrojFaktura );
    setTabOrder( lineEditDrojFaktura, lineEditFriText );
    setTabOrder( lineEditFriText, pushButtonOK );
    setTabOrder( pushButtonOK, pushButtonAvbryt );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
frmAddKund::~frmAddKund()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void frmAddKund::languageChange()
{
    setCaption( trUtf8( "ADDKUW - Lägga upp en ny kund." ) );
    pushButtonAvbryt->setText( tr( "Avbryt" ) );
    textLabel1_5->setText( tr( "<p align=\"center\">*</p>" ) );
    textLabel1_2->setText( tr( " = Obligatorisk information." ) );
    textLabel1->setText( tr( "KundID: .............." ) );
    textLabel12->setText( tr( "Er Referent: .............." ) );
    textLabel5_2_3->setText( trUtf8( "Språkkod: .............." ) );
    textLabel6_2_4->setText( tr( "Kravbrev: .........." ) );
    textLabel3->setText( tr( "Kundnamn: ........." ) );
    textLabel4->setText( tr( "Kundadress: .........." ) );
    textLabel6_2->setText( trUtf8( "Ordererkännande: .." ) );
    textLabel8_2_2_2->setText( trUtf8( "Dröjsmålsfaktura: .." ) );
    textLabel7->setText( tr( "Land: ....................." ) );
    textLabel7_2->setText( tr( "Expeditionsavgift: ..." ) );
    textLabel8_2_2_3->setText( tr( "Fri text (100 tkn): ...." ) );
    textLabel5->setText( tr( "Postnummer: .........." ) );
    textLabel3_3->setText( tr( "Distrikt: .................." ) );
    textLabel3_2->setText( tr( "Valuta: ..................." ) );
    textLabel5_2_2->setText( trUtf8( "Leveranssätt: ......" ) );
    textLabel9->setText( tr( "Faxnummer: ..........." ) );
    textLabel1_4->setText( tr( "Er Ref's e-mailadr: .." ) );
    textLabel11->setText( tr( "E-mail: ..................." ) );
    textLabel6_2_3->setText( trUtf8( "Följesedel: ........" ) );
    textLabel8->setText( tr( "Telefonnummer: ......" ) );
    textLabel1_5_3->setText( tr( "<p align=\"center\">*</p>" ) );
    textLabel2_2->setText( trUtf8( "Vår säljare: ............" ) );
    textLabel6_2_2->setText( tr( "Plocklista : ............." ) );
    textLabel7_2_2->setText( tr( "Fraktavgift: ............." ) );
    textLabel6->setText( tr( "Postadress: ............" ) );
    textLabel13->setText( tr( "Er Ref's telefonnr: ...." ) );
    textLabel4_2_2->setText( tr( "Leveransplats: ....." ) );
    textLabel8_2_2->setText( trUtf8( "Dröjsmålsränta: ....." ) );
    textLabel4_2->setText( tr( "Betalningsvillkor:" ) );
    textLabel8_2->setText( tr( "Kreditlimit: .............." ) );
    textLabel1_3->setText( tr( "Max 10 tecken." ) );
    textLabel1_5_2->setText( tr( "<p align=\"center\">*</p>" ) );
    lineEditKundBetvilk->setText( tr( "1" ) );
    lineEditValuta->setText( tr( "SEK" ) );
    lineEditSprakkod->setText( tr( "sv" ) );
    lineEditOrdererk->setText( tr( "J" ) );
    lineEditPlocklista->setText( tr( "J" ) );
    lineEditFoljesedel->setText( tr( "J" ) );
    lineEditExpAvgift->setText( tr( "J" ) );
    lineEditFraktAvgift->setText( tr( "J" ) );
    lineEditKravbrev->setText( tr( "J" ) );
    lineEditDrojRenta->setText( tr( "J" ) );
    lineEditDrojFaktura->setText( tr( "J" ) );
    pushButtonOK->setText( tr( "OK" ) );
    lineEditKundLevsett->setText( tr( "001" ) );
    textLabel5_2->setText( tr( "Leveransvillkor: ......" ) );
    lineEditKundLevvilk->setText( tr( "001" ) );
    textLabel1_6->setText( tr( "Kundkategori: ........" ) );
    QToolTip::add( lineEditKundNr, trUtf8( "Du kan använda valfritt sätt att ange KundID, siffror eller bokstäver eller en blandning av bägge." ) );
    QToolTip::add( lineEditKundNamn, trUtf8( "Namnet kan innehålla maximalt 60 tecken." ) );
    QToolTip::add( lineEditKundDistrikt, tr( "3 tecken" ) );
    QToolTip::add( lineEditKundKategori, tr( "3 tecken" ) );
    QToolTip::add( lineEditFriText, trUtf8( "Här kan du lägga in extra information om kunden." ) );
    lineEditKundStdLevplats->setText( tr( "002" ) );
    QToolTip::add( lineEditKundStdLevplats, trUtf8( "Leveransplats 002 är en extra leveransplats." ) );
}

