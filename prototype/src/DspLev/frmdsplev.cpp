/****************************************************************************
** Form implementation generated from reading ui file 'frmdsplev.ui'
**
** Created: fre aug 15 11:15:39 2003
**      by: The User Interface Compiler ($Id: frmdsplev.cpp,v 1.1 2003/09/28 07:57:07 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "frmdsplev.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "frmdsplev.ui.h"

/* 
 *  Constructs a frmDspLev as a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
frmDspLev::frmDspLev( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "frmDspLev" );

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

    pushButtonGet = new QPushButton( this, "pushButtonGet" );
    pushButtonGet->setGeometry( QRect( 270, 0, 56, 21 ) );
    pushButtonGet->setDefault( TRUE );

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

    lineditLevNr = new QLineEdit( this, "lineditLevNr" );
    lineditLevNr->setGeometry( QRect( 145, 0, 75, 23 ) );

    lineEditLevLand = new QLineEdit( this, "lineEditLevLand" );
    lineEditLevLand->setGeometry( QRect( 145, 150, 201, 23 ) );

    lineEditLevTfnNr = new QLineEdit( this, "lineEditLevTfnNr" );
    lineEditLevTfnNr->setGeometry( QRect( 145, 175, 111, 23 ) );

    lineEditLevFaxNr = new QLineEdit( this, "lineEditLevFaxNr" );
    lineEditLevFaxNr->setGeometry( QRect( 145, 200, 111, 23 ) );

    lineEditLevEmail = new QLineEdit( this, "lineEditLevEmail" );
    lineEditLevEmail->setGeometry( QRect( 145, 250, 206, 23 ) );

    lineEditLevRef = new QLineEdit( this, "lineEditLevRef" );
    lineEditLevRef->setGeometry( QRect( 145, 275, 206, 23 ) );

    lineEditLevRefTfnNr = new QLineEdit( this, "lineEditLevRefTfnNr" );
    lineEditLevRefTfnNr->setGeometry( QRect( 145, 300, 110, 23 ) );

    lineEditLevMomskod = new QLineEdit( this, "lineEditLevMomskod" );
    lineEditLevMomskod->setGeometry( QRect( 145, 325, 21, 23 ) );

    lineEditLevTelexNr = new QLineEdit( this, "lineEditLevTelexNr" );
    lineEditLevTelexNr->setGeometry( QRect( 145, 225, 110, 23 ) );

    lineEditLevKontoNr = new QLineEdit( this, "lineEditLevKontoNr" );
    lineEditLevKontoNr->setGeometry( QRect( 145, 350, 75, 23 ) );

    lineEditLevPgNr = new QLineEdit( this, "lineEditLevPgNr" );
    lineEditLevPgNr->setGeometry( QRect( 145, 375, 91, 23 ) );

    lineEditLevBgNr = new QLineEdit( this, "lineEditLevBgNr" );
    lineEditLevBgNr->setGeometry( QRect( 145, 400, 91, 23 ) );

    textLabel3_2 = new QLabel( this, "textLabel3_2" );
    textLabel3_2->setGeometry( QRect( 10, 455, 126, 16 ) );

    lineEditLevSkuld = new QLineEdit( this, "lineEditLevSkuld" );
    lineEditLevSkuld->setGeometry( QRect( 145, 450, 91, 23 ) );

    textLabel15_2 = new QLabel( this, "textLabel15_2" );
    textLabel15_2->setGeometry( QRect( 10, 430, 125, 16 ) );

    textLabel2_2 = new QLabel( this, "textLabel2_2" );
    textLabel2_2->setGeometry( QRect( 10, 405, 125, 16 ) );

    textLabel1_2 = new QLabel( this, "textLabel1_2" );
    textLabel1_2->setGeometry( QRect( 10, 380, 125, 16 ) );

    lineEditLevKundNr = new QLineEdit( this, "lineEditLevKundNr" );
    lineEditLevKundNr->setGeometry( QRect( 145, 425, 91, 23 ) );

    pushButtonOK = new QPushButton( this, "pushButtonOK" );
    pushButtonOK->setGeometry( QRect( 5, 545, 56, 21 ) );
    pushButtonOK->setDefault( TRUE );

    textLabel2_3 = new QLabel( this, "textLabel2_3" );
    textLabel2_3->setGeometry( QRect( 10, 505, 130, 16 ) );

    textLabel1_3 = new QLabel( this, "textLabel1_3" );
    textLabel1_3->setGeometry( QRect( 10, 480, 126, 16 ) );

    textLabel4_2 = new QLabel( this, "textLabel4_2" );
    textLabel4_2->setGeometry( QRect( 165, 505, 16, 16 ) );

    textLabel3_3 = new QLabel( this, "textLabel3_3" );
    textLabel3_3->setGeometry( QRect( 240, 505, 76, 16 ) );

    lineEditBetvilk = new QLineEdit( this, "lineEditBetvilk" );
    lineEditBetvilk->setGeometry( QRect( 145, 500, 19, 23 ) );

    lineEditValuta = new QLineEdit( this, "lineEditValuta" );
    lineEditValuta->setGeometry( QRect( 145, 475, 40, 23 ) );

    lineEditBetvilkDag = new QLineEdit( this, "lineEditBetvilkDag" );
    lineEditBetvilkDag->setGeometry( QRect( 185, 500, 50, 23 ) );

    textLabel1 = new QLabel( this, "textLabel1" );
    textLabel1->setGeometry( QRect( 10, 5, 123, 16 ) );
    languageChange();
    resize( QSize(357, 575).expandedTo(minimumSizeHint()) );

    // signals and slots connections
    connect( pushButtonOK, SIGNAL( clicked() ), this, SLOT( close() ) );
    connect( pushButtonGet, SIGNAL( clicked() ), this, SLOT( slotGetLev() ) );
    connect( lineditLevNr, SIGNAL( returnPressed() ), this, SLOT( slotLevNr_returnPressed() ) );
    connect( lineditLevNr, SIGNAL( lostFocus() ), this, SLOT( slotLevNr_returnPressed() ) );

    // tab order
    setTabOrder( lineditLevNr, pushButtonGet );
    setTabOrder( pushButtonGet, pushButtonOK );
    setTabOrder( pushButtonOK, lineEditLevOrgNr );
    setTabOrder( lineEditLevOrgNr, lineEditLevNamn );
    setTabOrder( lineEditLevNamn, lineEditLevAdress );
    setTabOrder( lineEditLevAdress, lineEditLevPostnr );
    setTabOrder( lineEditLevPostnr, lineEditLevPostAdress );
    setTabOrder( lineEditLevPostAdress, lineEditLevLand );
    setTabOrder( lineEditLevLand, lineEditLevTfnNr );
    setTabOrder( lineEditLevTfnNr, lineEditLevFaxNr );
    setTabOrder( lineEditLevFaxNr, lineEditLevTelexNr );
    setTabOrder( lineEditLevTelexNr, lineEditLevEmail );
    setTabOrder( lineEditLevEmail, lineEditLevRef );
    setTabOrder( lineEditLevRef, lineEditLevRefTfnNr );
    setTabOrder( lineEditLevRefTfnNr, lineEditLevMomskod );
    setTabOrder( lineEditLevMomskod, lineEditLevKontoNr );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
frmDspLev::~frmDspLev()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void frmDspLev::languageChange()
{
    setCaption( trUtf8( "DSPLEVW - Visa leverantörsdata." ) );
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
    pushButtonGet->setText( trUtf8( "Hämta" ) );
    lineEditLevMomskod->setText( QString::null );
    QToolTip::add( lineEditLevMomskod, trUtf8( "Momskod 1 är den normala för inköp i Sverige." ) );
    textLabel3_2->setText( trUtf8( "Leverantörsskuld:" ) );
    textLabel15_2->setText( tr( "Kundnr: .................." ) );
    textLabel2_2->setText( tr( "Bangironr: ............." ) );
    textLabel1_2->setText( tr( "Postgironr: ............." ) );
    pushButtonOK->setText( tr( "OK" ) );
    textLabel2_3->setText( tr( "Betalningsvillkor: ....." ) );
    textLabel1_3->setText( tr( "Valuta: ...................." ) );
    textLabel4_2->setText( tr( " =" ) );
    textLabel3_3->setText( tr( "dagar netto." ) );
    textLabel1->setText( trUtf8( "LeverantörsID:" ) );
}

