/****************************************************************************
** Form implementation generated from reading ui file 'frmaddftgdata.ui'
**
** Created: lör aug 16 05:44:17 2003
**      by: The User Interface Compiler ($Id: frmaddftgdata.cpp,v 1.1 2003/09/28 08:56:48 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "frmaddftgdata.h"

#include <qvariant.h>
#include <qframe.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "frmaddftgdata.ui.h"

/* 
 *  Constructs a frmAddFtgData as a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
frmAddFtgData::frmAddFtgData( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "frmAddFtgData" );

    Line1_2 = new QFrame( this, "Line1_2" );
    Line1_2->setGeometry( QRect( 10, 200, 696, 10 ) );
    Line1_2->setFrameShape( QFrame::HLine );
    Line1_2->setFrameShadow( QFrame::Sunken );
    Line1_2->setFrameShape( QFrame::HLine );

    Line1 = new QFrame( this, "Line1" );
    Line1->setGeometry( QRect( 10, 130, 696, 10 ) );
    Line1->setFrameShape( QFrame::HLine );
    Line1->setFrameShadow( QFrame::Sunken );
    Line1->setFrameShape( QFrame::HLine );

    textLabel3_2 = new QLabel( this, "textLabel3_2" );
    textLabel3_2->setGeometry( QRect( 5, 275, 185, 16 ) );

    TextLabel13 = new QLabel( this, "TextLabel13" );
    TextLabel13->setGeometry( QRect( 155, 220, 81, 16 ) );

    TextLabel14_2 = new QLabel( this, "TextLabel14_2" );
    TextLabel14_2->setGeometry( QRect( 440, 220, 80, 16 ) );

    TextLabel14 = new QLabel( this, "TextLabel14" );
    TextLabel14->setGeometry( QRect( 300, 220, 80, 16 ) );

    TextLabel14_3 = new QLabel( this, "TextLabel14_3" );
    TextLabel14_3->setGeometry( QRect( 580, 220, 80, 16 ) );

    TextLabel12 = new QLabel( this, "TextLabel12" );
    TextLabel12->setGeometry( QRect( 5, 220, 90, 16 ) );

    TextLabel4 = new QLabel( this, "TextLabel4" );
    TextLabel4->setGeometry( QRect( 315, 45, 81, 16 ) );

    TextLabel4_2 = new QLabel( this, "TextLabel4_2" );
    TextLabel4_2->setGeometry( QRect( 315, 75, 81, 16 ) );

    TextLabel4_3 = new QLabel( this, "TextLabel4_3" );
    TextLabel4_3->setGeometry( QRect( 315, 105, 81, 16 ) );

    TextLabel1 = new QLabel( this, "TextLabel1" );
    TextLabel1->setGeometry( QRect( 5, 15, 93, 16 ) );

    TextLabel5 = new QLabel( this, "TextLabel5" );
    TextLabel5->setGeometry( QRect( 5, 105, 90, 16 ) );

    TextLabel2 = new QLabel( this, "TextLabel2" );
    TextLabel2->setGeometry( QRect( 5, 45, 86, 16 ) );

    TextLabel7 = new QLabel( this, "TextLabel7" );
    TextLabel7->setGeometry( QRect( 5, 149, 98, 16 ) );

    TextLabel9 = new QLabel( this, "TextLabel9" );
    TextLabel9->setGeometry( QRect( 5, 175, 91, 16 ) );

    TextLabel8 = new QLabel( this, "TextLabel8" );
    TextLabel8->setGeometry( QRect( 225, 149, 80, 16 ) );

    TextLabel8_2 = new QLabel( this, "TextLabel8_2" );
    TextLabel8_2->setGeometry( QRect( 530, 149, 60, 16 ) );

    TextLabel10 = new QLabel( this, "TextLabel10" );
    TextLabel10->setGeometry( QRect( 530, 179, 45, 16 ) );

    TextLabel6 = new QLabel( this, "TextLabel6" );
    TextLabel6->setGeometry( QRect( 485, 45, 30, 20 ) );

    TextLabel6_2 = new QLabel( this, "TextLabel6_2" );
    TextLabel6_2->setGeometry( QRect( 485, 75, 30, 16 ) );

    TextLabel6_3 = new QLabel( this, "TextLabel6_3" );
    TextLabel6_3->setGeometry( QRect( 485, 105, 30, 16 ) );

    textLabel3 = new QLabel( this, "textLabel3" );
    textLabel3->setGeometry( QRect( 5, 250, 185, 16 ) );

    textLabel4 = new QLabel( this, "textLabel4" );
    textLabel4->setGeometry( QRect( 5, 325, 138, 16 ) );

    Line1_3 = new QFrame( this, "Line1_3" );
    Line1_3->setGeometry( QRect( 10, 305, 700, 10 ) );
    Line1_3->setFrameShape( QFrame::HLine );
    Line1_3->setFrameShadow( QFrame::Sunken );
    Line1_3->setFrameShape( QFrame::HLine );

    LineEditTfnnr = new QLineEdit( this, "LineEditTfnnr" );
    LineEditTfnnr->setGeometry( QRect( 106, 140, 110, 26 ) );

    LineEditMobilTfn = new QLineEdit( this, "LineEditMobilTfn" );
    LineEditMobilTfn->setGeometry( QRect( 305, 140, 116, 26 ) );

    LineEditTelefax = new QLineEdit( this, "LineEditTelefax" );
    LineEditTelefax->setGeometry( QRect( 590, 140, 116, 26 ) );

    LineEditemailadress = new QLineEdit( this, "LineEditemailadress" );
    LineEditemailadress->setGeometry( QRect( 106, 170, 315, 25 ) );

    LineEditTelex = new QLineEdit( this, "LineEditTelex" );
    LineEditTelex->setGeometry( QRect( 590, 170, 116, 26 ) );

    LineEditMoms2 = new QLineEdit( this, "LineEditMoms2" );
    LineEditMoms2->setGeometry( QRect( 240, 215, 46, 22 ) );

    LineEditMoms3 = new QLineEdit( this, "LineEditMoms3" );
    LineEditMoms3->setGeometry( QRect( 380, 215, 46, 22 ) );

    LineEditMoms4 = new QLineEdit( this, "LineEditMoms4" );
    LineEditMoms4->setGeometry( QRect( 520, 215, 46, 22 ) );

    LineEditMoms5 = new QLineEdit( this, "LineEditMoms5" );
    LineEditMoms5->setGeometry( QRect( 660, 215, 46, 22 ) );

    lineEditMomsKtoIng = new QLineEdit( this, "lineEditMomsKtoIng" );
    lineEditMomsKtoIng->setGeometry( QRect( 190, 245, 46, 23 ) );

    lineEditMomsKtoUtg = new QLineEdit( this, "lineEditMomsKtoUtg" );
    lineEditMomsKtoUtg->setGeometry( QRect( 190, 275, 46, 23 ) );

    lineEditAutokonto = new QLineEdit( this, "lineEditAutokonto" );
    lineEditAutokonto->setGeometry( QRect( 145, 320, 25, 23 ) );

    LineEditMoms1 = new QLineEdit( this, "LineEditMoms1" );
    LineEditMoms1->setGeometry( QRect( 100, 215, 46, 22 ) );

    pushButtonQuit = new QPushButton( this, "pushButtonQuit" );
    pushButtonQuit->setGeometry( QRect( 90, 390, 66, 21 ) );

    LineEditPostAdress = new QLineEdit( this, "LineEditPostAdress" );
    LineEditPostAdress->setGeometry( QRect( 106, 41, 205, 25 ) );

    LineEditPostnr1 = new QLineEdit( this, "LineEditPostnr1" );
    LineEditPostnr1->setGeometry( QRect( 395, 40, 86, 25 ) );

    LineEditPostOrt = new QLineEdit( this, "LineEditPostOrt" );
    LineEditPostOrt->setGeometry( QRect( 515, 40, 191, 25 ) );

    LineEditFtgNamn = new QLineEdit( this, "LineEditFtgNamn" );
    LineEditFtgNamn->setGeometry( QRect( 105, 10, 280, 25 ) );

    LineEditFtgNr = new QLineEdit( this, "LineEditFtgNr" );
    LineEditFtgNr->setGeometry( QRect( 515, 10, 191, 25 ) );

    TextLabel3 = new QLabel( this, "TextLabel3" );
    TextLabel3->setGeometry( QRect( 5, 79, 93, 16 ) );

    LineEditBesoksAdress = new QLineEdit( this, "LineEditBesoksAdress" );
    LineEditBesoksAdress->setGeometry( QRect( 106, 70, 205, 25 ) );

    LineEditPostnr2 = new QLineEdit( this, "LineEditPostnr2" );
    LineEditPostnr2->setGeometry( QRect( 395, 70, 86, 25 ) );

    LineEditBesoksOrt = new QLineEdit( this, "LineEditBesoksOrt" );
    LineEditBesoksOrt->setGeometry( QRect( 515, 70, 191, 25 ) );

    LineEditGodsAdress = new QLineEdit( this, "LineEditGodsAdress" );
    LineEditGodsAdress->setGeometry( QRect( 106, 100, 205, 25 ) );

    LineEditPostnr3 = new QLineEdit( this, "LineEditPostnr3" );
    LineEditPostnr3->setGeometry( QRect( 395, 100, 86, 25 ) );

    LineEditGodsOrt = new QLineEdit( this, "LineEditGodsOrt" );
    LineEditGodsOrt->setGeometry( QRect( 515, 100, 191, 25 ) );

    TextLabel11 = new QLabel( this, "TextLabel11" );
    TextLabel11->setGeometry( QRect( 400, 15, 107, 20 ) );

    PushButtonOK = new QPushButton( this, "PushButtonOK" );
    PushButtonOK->setGeometry( QRect( 10, 390, 71, 20 ) );
    PushButtonOK->setDefault( TRUE );
    languageChange();
    resize( QSize(717, 416).expandedTo(minimumSizeHint()) );

    // signals and slots connections
    connect( PushButtonOK, SIGNAL( clicked() ), this, SLOT( slotPushButtonOK_clicked() ) );
    connect( LineEditFtgNamn, SIGNAL( returnPressed() ), this, SLOT( slotLineEditFtgNamn_returnPressed() ) );
    connect( LineEditFtgNr, SIGNAL( returnPressed() ), this, SLOT( slotLineEditFtgNr_returnPressed() ) );
    connect( LineEditPostAdress, SIGNAL( returnPressed() ), this, SLOT( slotLineEditPostAdress_returnPressed() ) );
    connect( LineEditPostnr1, SIGNAL( returnPressed() ), this, SLOT( slotLineEditPostnr1_returnPressed() ) );
    connect( LineEditPostOrt, SIGNAL( returnPressed() ), this, SLOT( slotLineEditPostOrt_returnPressed() ) );
    connect( LineEditBesoksAdress, SIGNAL( returnPressed() ), this, SLOT( slotLineEditBesoksAdress_returnPressed() ) );
    connect( LineEditPostnr2, SIGNAL( returnPressed() ), this, SLOT( slotLineEditPostnr2_returnPressed() ) );
    connect( LineEditBesoksOrt, SIGNAL( returnPressed() ), this, SLOT( slotLineEditBesoksOrt_returnPressed() ) );
    connect( LineEditGodsAdress, SIGNAL( returnPressed() ), this, SLOT( slotLineEditGodsAdress_returnPressed() ) );
    connect( LineEditPostnr3, SIGNAL( returnPressed() ), this, SLOT( slotLineEditPostnr3_returnPressed() ) );
    connect( LineEditGodsOrt, SIGNAL( returnPressed() ), this, SLOT( slotLineEditGodsOrt_returnPressed() ) );
    connect( LineEditTfnnr, SIGNAL( returnPressed() ), this, SLOT( slotLineEditTfnnr_returnPressed() ) );
    connect( LineEditMobilTfn, SIGNAL( returnPressed() ), this, SLOT( slotLineEditMobilTfn_returnPressed() ) );
    connect( LineEditTelefax, SIGNAL( returnPressed() ), this, SLOT( slotLineEditTelefax_returnPressed() ) );
    connect( LineEditemailadress, SIGNAL( returnPressed() ), this, SLOT( slotLineEditemailadress_returnPressed() ) );
    connect( LineEditTelex, SIGNAL( returnPressed() ), this, SLOT( slotLineEditTelex_returnPressed() ) );
    connect( LineEditMoms1, SIGNAL( returnPressed() ), this, SLOT( slotLineEditMoms1_returnPressed() ) );
    connect( LineEditMoms2, SIGNAL( returnPressed() ), this, SLOT( slotLineEditMoms2_returnPresse() ) );
    connect( LineEditMoms3, SIGNAL( returnPressed() ), this, SLOT( slotLineEditMoms3_returnPressed() ) );
    connect( LineEditMoms4, SIGNAL( returnPressed() ), this, SLOT( slotLineEditMoms4_returnPressed() ) );
    connect( LineEditMoms5, SIGNAL( returnPressed() ), this, SLOT( slotLineEditMoms5_returnPressed() ) );
    connect( lineEditMomsKtoIng, SIGNAL( returnPressed() ), this, SLOT( slotlineEditMomsKtoIng_returnPressed() ) );
    connect( lineEditMomsKtoUtg, SIGNAL( returnPressed() ), this, SLOT( slotlineEditMomsKtoUtg_returnPressed() ) );
    connect( lineEditAutokonto, SIGNAL( returnPressed() ), this, SLOT( slotlineEditAutokonto_returnPressed() ) );
    connect( pushButtonQuit, SIGNAL( clicked() ), this, SLOT( close() ) );

    // tab order
    setTabOrder( LineEditFtgNamn, LineEditFtgNr );
    setTabOrder( LineEditFtgNr, LineEditPostAdress );
    setTabOrder( LineEditPostAdress, LineEditPostnr1 );
    setTabOrder( LineEditPostnr1, LineEditPostOrt );
    setTabOrder( LineEditPostOrt, LineEditBesoksAdress );
    setTabOrder( LineEditBesoksAdress, LineEditPostnr2 );
    setTabOrder( LineEditPostnr2, LineEditBesoksOrt );
    setTabOrder( LineEditBesoksOrt, LineEditGodsAdress );
    setTabOrder( LineEditGodsAdress, LineEditPostnr3 );
    setTabOrder( LineEditPostnr3, LineEditGodsOrt );
    setTabOrder( LineEditGodsOrt, LineEditTfnnr );
    setTabOrder( LineEditTfnnr, LineEditMobilTfn );
    setTabOrder( LineEditMobilTfn, LineEditTelefax );
    setTabOrder( LineEditTelefax, LineEditemailadress );
    setTabOrder( LineEditemailadress, LineEditTelex );
    setTabOrder( LineEditTelex, LineEditMoms1 );
    setTabOrder( LineEditMoms1, LineEditMoms2 );
    setTabOrder( LineEditMoms2, LineEditMoms3 );
    setTabOrder( LineEditMoms3, LineEditMoms4 );
    setTabOrder( LineEditMoms4, LineEditMoms5 );
    setTabOrder( LineEditMoms5, lineEditMomsKtoIng );
    setTabOrder( lineEditMomsKtoIng, lineEditMomsKtoUtg );
    setTabOrder( lineEditMomsKtoUtg, lineEditAutokonto );
    setTabOrder( lineEditAutokonto, PushButtonOK );
    setTabOrder( PushButtonOK, pushButtonQuit );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
frmAddFtgData::~frmAddFtgData()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void frmAddFtgData::languageChange()
{
    setCaption( trUtf8( "ADDFTGW - Nya företagsdata" ) );
    textLabel3_2->setText( trUtf8( "Momskonto, utgående moms: " ) );
    TextLabel13->setText( tr( "Momssats 2:" ) );
    TextLabel14_2->setText( tr( "Momssats 4:" ) );
    TextLabel14->setText( tr( "Momssats 3:" ) );
    TextLabel14_3->setText( tr( "Momssats 5:" ) );
    TextLabel12->setText( tr( "Momssats 1:" ) );
    TextLabel4->setText( tr( "Postnummer:" ) );
    TextLabel4_2->setText( tr( "Postnummer:" ) );
    TextLabel4_3->setText( tr( "Postnummer:" ) );
    TextLabel1->setText( trUtf8( "Företagsnamn:" ) );
    TextLabel5->setText( tr( "Godsadress:" ) );
    TextLabel2->setText( tr( "Postadress:" ) );
    TextLabel7->setText( tr( "Telefonnummer:" ) );
    TextLabel9->setText( tr( "e-mailadress:" ) );
    TextLabel8->setText( tr( "Mobiltelefon:" ) );
    TextLabel8_2->setText( tr( "Telefax:" ) );
    TextLabel10->setText( tr( "Telex:" ) );
    TextLabel6->setText( tr( "Ort:" ) );
    TextLabel6_2->setText( tr( "Ort:" ) );
    TextLabel6_3->setText( tr( "Ort:" ) );
    textLabel3->setText( trUtf8( "Momskonto, ingående moms: " ) );
    textLabel4->setText( tr( "Automatkontering J/N :" ) );
    lineEditAutokonto->setText( tr( "J" ) );
    pushButtonQuit->setText( tr( "Avbryt" ) );
    TextLabel3->setText( trUtf8( "Besöksadress:" ) );
    TextLabel11->setText( tr( "Organisationsnr:" ) );
    PushButtonOK->setText( tr( "Spara" ) );
}

