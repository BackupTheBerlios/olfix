/****************************************************************************
** Form implementation generated from reading ui file 'frmaddlev.ui'
**
** Created: fre aug 15 11:17:57 2003
**      by: The User Interface Compiler ($Id: frmaddlev.cpp,v 1.1 2003/09/28 06:12:19 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "frmaddlev.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "frmaddlev.ui.h"

/* 
 *  Constructs a frmAddLev as a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
frmAddLev::frmAddLev( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "frmAddLev" );

    textLabel2 = new QLabel( this, "textLabel2" );
    textLabel2->setGeometry( QRect( 10, 30, 125, 16 ) );

    textLabel3 = new QLabel( this, "textLabel3" );
    textLabel3->setGeometry( QRect( 10, 55, 125, 16 ) );

    textLabel4 = new QLabel( this, "textLabel4" );
    textLabel4->setGeometry( QRect( 10, 80, 125, 16 ) );

    textLabel7 = new QLabel( this, "textLabel7" );
    textLabel7->setGeometry( QRect( 10, 155, 125, 16 ) );

    textLabel5 = new QLabel( this, "textLabel5" );
    textLabel5->setGeometry( QRect( 10, 105, 125, 16 ) );

    textLabel8 = new QLabel( this, "textLabel8" );
    textLabel8->setGeometry( QRect( 10, 180, 125, 16 ) );

    textLabel6 = new QLabel( this, "textLabel6" );
    textLabel6->setGeometry( QRect( 10, 130, 125, 16 ) );

    textLabel9 = new QLabel( this, "textLabel9" );
    textLabel9->setGeometry( QRect( 10, 205, 125, 16 ) );

    textLabel10 = new QLabel( this, "textLabel10" );
    textLabel10->setGeometry( QRect( 10, 230, 125, 16 ) );

    textLabel11 = new QLabel( this, "textLabel11" );
    textLabel11->setGeometry( QRect( 10, 255, 125, 16 ) );

    textLabel12 = new QLabel( this, "textLabel12" );
    textLabel12->setGeometry( QRect( 10, 280, 124, 16 ) );

    textLabel13 = new QLabel( this, "textLabel13" );
    textLabel13->setGeometry( QRect( 10, 305, 125, 16 ) );

    textLabel15 = new QLabel( this, "textLabel15" );
    textLabel15->setGeometry( QRect( 10, 330, 125, 16 ) );

    textLabel14 = new QLabel( this, "textLabel14" );
    textLabel14->setGeometry( QRect( 10, 355, 125, 16 ) );

    textLabel1_2 = new QLabel( this, "textLabel1_2" );
    textLabel1_2->setGeometry( QRect( 370, 5, 84, 16 ) );

    textLabel1_2_2 = new QLabel( this, "textLabel1_2_2" );
    textLabel1_2_2->setGeometry( QRect( 370, 55, 84, 16 ) );

    textLabel1_2_3 = new QLabel( this, "textLabel1_2_3" );
    textLabel1_2_3->setGeometry( QRect( 370, 330, 84, 16 ) );

    lineditLevNr = new QLineEdit( this, "lineditLevNr" );
    lineditLevNr->setGeometry( QRect( 145, 0, 75, 23 ) );

    lineEditLevOrgNr = new QLineEdit( this, "lineEditLevOrgNr" );
    lineEditLevOrgNr->setGeometry( QRect( 145, 25, 111, 23 ) );

    lineEditLevNamn = new QLineEdit( this, "lineEditLevNamn" );
    lineEditLevNamn->setGeometry( QRect( 145, 50, 201, 23 ) );

    lineEditLevAdress = new QLineEdit( this, "lineEditLevAdress" );
    lineEditLevAdress->setGeometry( QRect( 145, 75, 201, 23 ) );

    lineEditLevPostnr = new QLineEdit( this, "lineEditLevPostnr" );
    lineEditLevPostnr->setGeometry( QRect( 145, 100, 75, 23 ) );

    lineEditLevPostAdress = new QLineEdit( this, "lineEditLevPostAdress" );
    lineEditLevPostAdress->setGeometry( QRect( 145, 125, 201, 23 ) );

    lineEditLevLand = new QLineEdit( this, "lineEditLevLand" );
    lineEditLevLand->setGeometry( QRect( 145, 150, 201, 23 ) );

    lineEditLevTftnNr = new QLineEdit( this, "lineEditLevTftnNr" );
    lineEditLevTftnNr->setGeometry( QRect( 145, 175, 111, 23 ) );

    lineEditLevFaxNr = new QLineEdit( this, "lineEditLevFaxNr" );
    lineEditLevFaxNr->setGeometry( QRect( 145, 200, 111, 23 ) );

    lineEditLevTelexNr = new QLineEdit( this, "lineEditLevTelexNr" );
    lineEditLevTelexNr->setGeometry( QRect( 145, 225, 110, 23 ) );

    lineEditLevEmail = new QLineEdit( this, "lineEditLevEmail" );
    lineEditLevEmail->setGeometry( QRect( 145, 250, 206, 23 ) );

    lineEditLevRef = new QLineEdit( this, "lineEditLevRef" );
    lineEditLevRef->setGeometry( QRect( 145, 275, 206, 23 ) );

    lineEditLevRefTfnNr = new QLineEdit( this, "lineEditLevRefTfnNr" );
    lineEditLevRefTfnNr->setGeometry( QRect( 145, 300, 110, 23 ) );

    lineEditLevKontoNr = new QLineEdit( this, "lineEditLevKontoNr" );
    lineEditLevKontoNr->setGeometry( QRect( 145, 350, 75, 23 ) );

    textLabel1_3 = new QLabel( this, "textLabel1_3" );
    textLabel1_3->setGeometry( QRect( 225, 5, 95, 16 ) );

    textLabel4_2 = new QLabel( this, "textLabel4_2" );
    textLabel4_2->setGeometry( QRect( 10, 380, 125, 16 ) );

    textLabel5_2 = new QLabel( this, "textLabel5_2" );
    textLabel5_2->setGeometry( QRect( 10, 405, 125, 16 ) );

    lineEditLevBgNr = new QLineEdit( this, "lineEditLevBgNr" );
    lineEditLevBgNr->setGeometry( QRect( 145, 400, 110, 23 ) );

    lineEditLevPgNr = new QLineEdit( this, "lineEditLevPgNr" );
    lineEditLevPgNr->setGeometry( QRect( 145, 375, 110, 23 ) );

    lineEditLevKundNr = new QLineEdit( this, "lineEditLevKundNr" );
    lineEditLevKundNr->setGeometry( QRect( 145, 425, 110, 23 ) );

    pushButtonOK = new QPushButton( this, "pushButtonOK" );
    pushButtonOK->setGeometry( QRect( 10, 550, 56, 21 ) );
    pushButtonOK->setDefault( TRUE );

    pushButtonAvbryt = new QPushButton( this, "pushButtonAvbryt" );
    pushButtonAvbryt->setGeometry( QRect( 75, 550, 60, 21 ) );
    pushButtonAvbryt->setDefault( TRUE );

    textLabel14_2 = new QLabel( this, "textLabel14_2" );
    textLabel14_2->setGeometry( QRect( 10, 430, 125, 16 ) );

    textLabel3_2 = new QLabel( this, "textLabel3_2" );
    textLabel3_2->setGeometry( QRect( 10, 455, 125, 16 ) );

    textLabel4_3 = new QLabel( this, "textLabel4_3" );
    textLabel4_3->setGeometry( QRect( 10, 480, 124, 16 ) );

    lineEditValuta = new QLineEdit( this, "lineEditValuta" );
    lineEditValuta->setGeometry( QRect( 145, 450, 36, 23 ) );

    lineEditBetvilk = new QLineEdit( this, "lineEditBetvilk" );
    lineEditBetvilk->setGeometry( QRect( 145, 475, 19, 23 ) );

    lineEditLevMomskod = new QLineEdit( this, "lineEditLevMomskod" );
    lineEditLevMomskod->setGeometry( QRect( 145, 325, 21, 23 ) );

    textLabel1 = new QLabel( this, "textLabel1" );
    textLabel1->setGeometry( QRect( 10, 5, 123, 16 ) );
    textLabel1->setFrameShape( QLabel::NoFrame );
    textLabel1->setFrameShadow( QLabel::Plain );
    languageChange();
    resize( QSize(600, 578).expandedTo(minimumSizeHint()) );

    // signals and slots connections
    connect( lineditLevNr, SIGNAL( returnPressed() ), this, SLOT( slotLevNr_returnPressed() ) );
    connect( lineEditLevOrgNr, SIGNAL( returnPressed() ), this, SLOT( slotLevOrgNr_returnPressed() ) );
    connect( lineEditLevNamn, SIGNAL( returnPressed() ), this, SLOT( slotLevNamn_returnPressed() ) );
    connect( lineEditLevAdress, SIGNAL( returnPressed() ), this, SLOT( slotLevAdress_returnPressed() ) );
    connect( lineEditLevPostnr, SIGNAL( returnPressed() ), this, SLOT( slotLevPostNr_returnPressed() ) );
    connect( lineEditLevPostnr, SIGNAL( returnPressed() ), this, SLOT( slotLevPostNr_returnPressed() ) );
    connect( lineEditLevPostAdress, SIGNAL( returnPressed() ), this, SLOT( slotLevPostAdress_returnPressed() ) );
    connect( lineEditLevLand, SIGNAL( returnPressed() ), this, SLOT( slotLevLand_returnPressed() ) );
    connect( lineEditLevTftnNr, SIGNAL( returnPressed() ), this, SLOT( slotLevTfnNr_returnPressed() ) );
    connect( lineEditLevFaxNr, SIGNAL( returnPressed() ), this, SLOT( slotLevFaxNr_returnPressed() ) );
    connect( lineEditLevTelexNr, SIGNAL( returnPressed() ), this, SLOT( slotLevTelexNr_returnPressed() ) );
    connect( lineEditLevEmail, SIGNAL( returnPressed() ), this, SLOT( slotLevEmail_returnPressed() ) );
    connect( lineEditLevRef, SIGNAL( returnPressed() ), this, SLOT( slotLevRef_returnPressed() ) );
    connect( lineEditLevRefTfnNr, SIGNAL( returnPressed() ), this, SLOT( slotLevRefTfnNr_returnPressed() ) );
    connect( lineEditLevMomskod, SIGNAL( returnPressed() ), this, SLOT( slotLevMomskod_returnPressed() ) );
    connect( lineEditLevKontoNr, SIGNAL( returnPressed() ), this, SLOT( slotLevKontoNr_returnPressed() ) );
    connect( pushButtonOK, SIGNAL( clicked() ), this, SLOT( slotBtnOK_clicked() ) );
    connect( pushButtonAvbryt, SIGNAL( clicked() ), this, SLOT( close() ) );
    connect( lineditLevNr, SIGNAL( lostFocus() ), this, SLOT( slotLevNr_returnPressed() ) );
    connect( lineEditLevOrgNr, SIGNAL( lostFocus() ), this, SLOT( slotLevOrgNr_returnPressed() ) );
    connect( lineEditLevNamn, SIGNAL( lostFocus() ), this, SLOT( slotLevNamn_returnPressed() ) );
    connect( lineEditLevAdress, SIGNAL( lostFocus() ), this, SLOT( slotLevAdress_returnPressed() ) );
    connect( lineEditLevPostnr, SIGNAL( lostFocus() ), this, SLOT( slotLevPostNr_returnPressed() ) );
    connect( lineEditLevPostAdress, SIGNAL( lostFocus() ), this, SLOT( slotLevPostAdress_returnPressed() ) );
    connect( lineEditLevLand, SIGNAL( lostFocus() ), this, SLOT( slotLevLand_returnPressed() ) );
    connect( lineEditLevTftnNr, SIGNAL( lostFocus() ), this, SLOT( slotLevTfnNr_returnPressed() ) );
    connect( lineEditLevFaxNr, SIGNAL( lostFocus() ), this, SLOT( slotLevFaxNr_returnPressed() ) );
    connect( lineEditLevTelexNr, SIGNAL( lostFocus() ), this, SLOT( slotLevTelexNr_returnPressed() ) );
    connect( lineEditLevEmail, SIGNAL( lostFocus() ), this, SLOT( slotLevEmail_returnPressed() ) );
    connect( lineEditLevRef, SIGNAL( lostFocus() ), this, SLOT( slotLevRef_returnPressed() ) );
    connect( lineEditLevRefTfnNr, SIGNAL( lostFocus() ), this, SLOT( slotLevRefTfnNr_returnPressed() ) );
    connect( lineEditLevMomskod, SIGNAL( lostFocus() ), this, SLOT( slotLevMomskod_returnPressed() ) );
    connect( lineEditLevKontoNr, SIGNAL( lostFocus() ), this, SLOT( slotLevKontoNr_returnPressed() ) );
    connect( lineEditLevPgNr, SIGNAL( lostFocus() ), this, SLOT( slotLevPgNr_returnPressed() ) );
    connect( lineEditLevPgNr, SIGNAL( returnPressed() ), this, SLOT( slotLevPgNr_returnPressed() ) );
    connect( lineEditLevBgNr, SIGNAL( lostFocus() ), this, SLOT( slotLevBgNr_returnPressed() ) );
    connect( lineEditLevBgNr, SIGNAL( returnPressed() ), this, SLOT( slotLevBgNr_returnPressed() ) );
    connect( lineEditLevKundNr, SIGNAL( lostFocus() ), this, SLOT( slotLevKundNr_returnPressed() ) );
    connect( lineEditLevKundNr, SIGNAL( returnPressed() ), this, SLOT( slotLevKundNr_returnPressed() ) );
    connect( lineEditValuta, SIGNAL( lostFocus() ), this, SLOT( slotLevValuta_returnPressed() ) );
    connect( lineEditValuta, SIGNAL( returnPressed() ), this, SLOT( slotLevValuta_returnPressed() ) );
    connect( lineEditBetvilk, SIGNAL( lostFocus() ), this, SLOT( slotLevBetvilk_returnPressed() ) );
    connect( lineEditBetvilk, SIGNAL( returnPressed() ), this, SLOT( slotLevBetvilk_returnPressed() ) );

    // tab order
    setTabOrder( lineditLevNr, lineEditLevOrgNr );
    setTabOrder( lineEditLevOrgNr, lineEditLevNamn );
    setTabOrder( lineEditLevNamn, lineEditLevAdress );
    setTabOrder( lineEditLevAdress, lineEditLevPostnr );
    setTabOrder( lineEditLevPostnr, lineEditLevPostAdress );
    setTabOrder( lineEditLevPostAdress, lineEditLevLand );
    setTabOrder( lineEditLevLand, lineEditLevTftnNr );
    setTabOrder( lineEditLevTftnNr, lineEditLevFaxNr );
    setTabOrder( lineEditLevFaxNr, lineEditLevTelexNr );
    setTabOrder( lineEditLevTelexNr, lineEditLevEmail );
    setTabOrder( lineEditLevEmail, lineEditLevRef );
    setTabOrder( lineEditLevRef, lineEditLevRefTfnNr );
    setTabOrder( lineEditLevRefTfnNr, lineEditLevMomskod );
    setTabOrder( lineEditLevMomskod, lineEditLevKontoNr );
    setTabOrder( lineEditLevKontoNr, lineEditLevPgNr );
    setTabOrder( lineEditLevPgNr, lineEditLevBgNr );
    setTabOrder( lineEditLevBgNr, pushButtonOK );
    setTabOrder( pushButtonOK, pushButtonAvbryt );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
frmAddLev::~frmAddLev()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void frmAddLev::languageChange()
{
    setCaption( trUtf8( "ADDLEVW - Lägga upp en ny leverantör." ) );
    textLabel2->setText( tr( "Organisationsnr:" ) );
    textLabel3->setText( trUtf8( "Leverantörsnamn:" ) );
    textLabel4->setText( trUtf8( "Leverantörsadress:" ) );
    textLabel7->setText( tr( "Land: ....................." ) );
    textLabel5->setText( tr( "Postnummer: .........." ) );
    textLabel8->setText( tr( "Telefonnummer: ......" ) );
    textLabel6->setText( tr( "Postadress: ............" ) );
    textLabel9->setText( tr( "Faxnummer: ..........." ) );
    textLabel10->setText( tr( "Telex: ...................." ) );
    textLabel11->setText( tr( "E-mail: ..................." ) );
    textLabel12->setText( tr( "Referent: ................" ) );
    textLabel13->setText( tr( "Ref's telefonnr: ......." ) );
    textLabel15->setText( tr( "Momskod: ............." ) );
    textLabel14->setText( tr( "Kontonummer: ........" ) );
    textLabel1_2->setText( tr( "Obligatoriskt." ) );
    textLabel1_2_2->setText( tr( "Obligatoriskt." ) );
    textLabel1_2_3->setText( tr( "Obligatoriskt." ) );
    textLabel1_3->setText( tr( "Max 10 tecken." ) );
    textLabel4_2->setText( tr( "Postgironummer: ...." ) );
    textLabel5_2->setText( tr( "Bankgironummer: ..." ) );
    pushButtonOK->setText( tr( "OK" ) );
    pushButtonAvbryt->setText( tr( "Avbryt" ) );
    textLabel14_2->setText( tr( "Kundnr: .................." ) );
    QToolTip::add( textLabel14_2, trUtf8( "Mitt kundnummer hos leverantören." ) );
    textLabel3_2->setText( tr( "Valuta: ..................." ) );
    textLabel4_3->setText( tr( "Betalningsvillkor: ...." ) );
    lineEditBetvilk->setText( tr( "1" ) );
    lineEditLevMomskod->setText( tr( "1" ) );
    QToolTip::add( lineEditLevMomskod, trUtf8( "Momskod 1 är den normala för inköp i Sverige." ) );
    textLabel1->setText( trUtf8( "LeverantörsID: ......." ) );
}

