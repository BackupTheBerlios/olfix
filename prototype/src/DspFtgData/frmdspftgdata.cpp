/****************************************************************************
** Form implementation generated from reading ui file 'frmdspftgdata.ui'
**
** Created: fre aug 15 11:09:06 2003
**      by: The User Interface Compiler ($Id: frmdspftgdata.cpp,v 1.2 2003/09/28 07:49:24 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "frmdspftgdata.h"

#include <qvariant.h>
#include <qframe.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "frmdspftgdata.ui.h"

/* 
 *  Constructs a frmDspFtgData as a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
frmDspFtgData::frmDspFtgData( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "frmDspFtgData" );

    Line1_2 = new QFrame( this, "Line1_2" );
    Line1_2->setGeometry( QRect( 10, 200, 696, 10 ) );
    Line1_2->setFrameShape( QFrame::HLine );
    Line1_2->setFrameShadow( QFrame::Sunken );
    Line1_2->setFrameShape( QFrame::HLine );

    LineEdit1Telex = new QLineEdit( this, "LineEdit1Telex" );
    LineEdit1Telex->setGeometry( QRect( 590, 170, 116, 26 ) );

    LineEditMoms5 = new QLineEdit( this, "LineEditMoms5" );
    LineEditMoms5->setGeometry( QRect( 660, 215, 46, 22 ) );

    LineEditMoms4 = new QLineEdit( this, "LineEditMoms4" );
    LineEditMoms4->setGeometry( QRect( 520, 215, 46, 22 ) );

    LineEditFtgNr = new QLineEdit( this, "LineEditFtgNr" );
    LineEditFtgNr->setGeometry( QRect( 515, 10, 191, 25 ) );

    LineEditTfnnr = new QLineEdit( this, "LineEditTfnnr" );
    LineEditTfnnr->setGeometry( QRect( 100, 140, 116, 26 ) );

    LineEditTelefax = new QLineEdit( this, "LineEditTelefax" );
    LineEditTelefax->setGeometry( QRect( 590, 140, 116, 26 ) );

    LineEditMoms1 = new QLineEdit( this, "LineEditMoms1" );
    LineEditMoms1->setGeometry( QRect( 100, 215, 46, 22 ) );

    PushButton5 = new QPushButton( this, "PushButton5" );
    PushButton5->setGeometry( QRect( 90, 535, 70, 21 ) );
    PushButton5->setDefault( TRUE );

    LineEditFtgNamn = new QLineEdit( this, "LineEditFtgNamn" );
    LineEditFtgNamn->setGeometry( QRect( 100, 10, 290, 25 ) );

    TextLabel4_3 = new QLabel( this, "TextLabel4_3" );
    TextLabel4_3->setGeometry( QRect( 315, 105, 74, 20 ) );

    TextLabel4_2 = new QLabel( this, "TextLabel4_2" );
    TextLabel4_2->setGeometry( QRect( 315, 75, 74, 20 ) );

    TextLabel4 = new QLabel( this, "TextLabel4" );
    TextLabel4->setGeometry( QRect( 315, 41, 74, 20 ) );

    TextLabel6_3 = new QLabel( this, "TextLabel6_3" );
    TextLabel6_3->setGeometry( QRect( 485, 105, 25, 20 ) );

    TextLabel6 = new QLabel( this, "TextLabel6" );
    TextLabel6->setGeometry( QRect( 485, 45, 25, 20 ) );

    Line1 = new QFrame( this, "Line1" );
    Line1->setGeometry( QRect( 10, 130, 696, 10 ) );
    Line1->setFrameShape( QFrame::HLine );
    Line1->setFrameShadow( QFrame::Sunken );
    Line1->setFrameShape( QFrame::HLine );

    TextLabel6_2 = new QLabel( this, "TextLabel6_2" );
    TextLabel6_2->setGeometry( QRect( 485, 75, 25, 20 ) );

    TextLabel8_2 = new QLabel( this, "TextLabel8_2" );
    TextLabel8_2->setGeometry( QRect( 530, 145, 55, 20 ) );

    TextLabel10 = new QLabel( this, "TextLabel10" );
    TextLabel10->setGeometry( QRect( 530, 175, 55, 20 ) );

    TextLabel8 = new QLabel( this, "TextLabel8" );
    TextLabel8->setGeometry( QRect( 225, 141, 75, 20 ) );

    LineEditPostAdress = new QLineEdit( this, "LineEditPostAdress" );
    LineEditPostAdress->setGeometry( QRect( 100, 41, 211, 25 ) );

    LineEditPostOrt = new QLineEdit( this, "LineEditPostOrt" );
    LineEditPostOrt->setGeometry( QRect( 515, 40, 191, 25 ) );

    LineEditBesoksAdress = new QLineEdit( this, "LineEditBesoksAdress" );
    LineEditBesoksAdress->setGeometry( QRect( 100, 70, 211, 25 ) );

    LineEditBesoksOrt = new QLineEdit( this, "LineEditBesoksOrt" );
    LineEditBesoksOrt->setGeometry( QRect( 515, 70, 191, 25 ) );

    LineEditGodsAdress = new QLineEdit( this, "LineEditGodsAdress" );
    LineEditGodsAdress->setGeometry( QRect( 100, 100, 211, 25 ) );

    LineEditGodsOrt = new QLineEdit( this, "LineEditGodsOrt" );
    LineEditGodsOrt->setGeometry( QRect( 515, 100, 191, 25 ) );

    LineEditMoms2 = new QLineEdit( this, "LineEditMoms2" );
    LineEditMoms2->setGeometry( QRect( 240, 215, 46, 22 ) );

    lineEditMomktoIng = new QLineEdit( this, "lineEditMomktoIng" );
    lineEditMomktoIng->setGeometry( QRect( 240, 245, 46, 23 ) );

    lineEditMomktoUtg = new QLineEdit( this, "lineEditMomktoUtg" );
    lineEditMomktoUtg->setGeometry( QRect( 520, 245, 46, 23 ) );

    TextLabel14 = new QLabel( this, "TextLabel14" );
    TextLabel14->setGeometry( QRect( 300, 220, 80, 16 ) );

    Line1_3 = new QFrame( this, "Line1_3" );
    Line1_3->setGeometry( QRect( 10, 275, 696, 10 ) );
    Line1_3->setFrameShape( QFrame::HLine );
    Line1_3->setFrameShadow( QFrame::Sunken );
    Line1_3->setFrameShape( QFrame::HLine );

    TextLabel16 = new QLabel( this, "TextLabel16" );
    TextLabel16->setGeometry( QRect( 580, 220, 80, 16 ) );

    TextLabel15 = new QLabel( this, "TextLabel15" );
    TextLabel15->setGeometry( QRect( 440, 220, 80, 16 ) );

    TextLabel13 = new QLabel( this, "TextLabel13" );
    TextLabel13->setGeometry( QRect( 155, 220, 81, 16 ) );

    LineEditMobilTfn = new QLineEdit( this, "LineEditMobilTfn" );
    LineEditMobilTfn->setGeometry( QRect( 305, 140, 125, 26 ) );

    LineEditemailadress = new QLineEdit( this, "LineEditemailadress" );
    LineEditemailadress->setGeometry( QRect( 100, 170, 330, 25 ) );

    LineEditMoms3 = new QLineEdit( this, "LineEditMoms3" );
    LineEditMoms3->setGeometry( QRect( 380, 215, 50, 23 ) );

    LineEditPostnr1 = new QLineEdit( this, "LineEditPostnr1" );
    LineEditPostnr1->setGeometry( QRect( 396, 41, 80, 25 ) );

    LineEditPostnr2 = new QLineEdit( this, "LineEditPostnr2" );
    LineEditPostnr2->setGeometry( QRect( 396, 70, 80, 25 ) );

    LineEditPostnr3 = new QLineEdit( this, "LineEditPostnr3" );
    LineEditPostnr3->setGeometry( QRect( 396, 100, 80, 25 ) );

    TextLabel2 = new QLabel( this, "TextLabel2" );
    TextLabel2->setGeometry( QRect( 5, 45, 90, 16 ) );

    TextLabel1 = new QLabel( this, "TextLabel1" );
    TextLabel1->setGeometry( QRect( 5, 15, 93, 16 ) );

    TextLabel5 = new QLabel( this, "TextLabel5" );
    TextLabel5->setGeometry( QRect( 5, 101, 90, 20 ) );

    TextLabel7 = new QLabel( this, "TextLabel7" );
    TextLabel7->setGeometry( QRect( 3, 141, 98, 20 ) );

    TextLabel9 = new QLabel( this, "TextLabel9" );
    TextLabel9->setGeometry( QRect( 5, 175, 90, 16 ) );

    TextLabel12 = new QLabel( this, "TextLabel12" );
    TextLabel12->setGeometry( QRect( 5, 220, 90, 16 ) );

    TextLabel3 = new QLabel( this, "TextLabel3" );
    TextLabel3->setGeometry( QRect( 3, 75, 95, 20 ) );

    textLabel1 = new QLabel( this, "textLabel1" );
    textLabel1->setGeometry( QRect( 1, 250, 230, 20 ) );

    textLabel1_2 = new QLabel( this, "textLabel1_2" );
    textLabel1_2->setGeometry( QRect( 300, 250, 215, 20 ) );

    textLabel2 = new QLabel( this, "textLabel2" );
    textLabel2->setGeometry( QRect( 5, 295, 138, 16 ) );

    lineEditAutokont = new QLineEdit( this, "lineEditAutokont" );
    lineEditAutokont->setGeometry( QRect( 145, 290, 26, 23 ) );

    PushButtonOK = new QPushButton( this, "PushButtonOK" );
    PushButtonOK->setGeometry( QRect( 10, 535, 71, 20 ) );
    PushButtonOK->setDefault( TRUE );

    TextLabel11 = new QLabel( this, "TextLabel11" );
    TextLabel11->setGeometry( QRect( 402, 15, 107, 20 ) );
    languageChange();
    resize( QSize(715, 565).expandedTo(minimumSizeHint()) );

    // signals and slots connections
    connect( PushButtonOK, SIGNAL( clicked() ), this, SLOT( close() ) );
    connect( PushButton5, SIGNAL( pressed() ), this, SLOT( init() ) );

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
    setTabOrder( LineEditemailadress, LineEdit1Telex );
    setTabOrder( LineEdit1Telex, LineEditMoms1 );
    setTabOrder( LineEditMoms1, LineEditMoms2 );
    setTabOrder( LineEditMoms2, LineEditMoms3 );
    setTabOrder( LineEditMoms3, LineEditMoms4 );
    setTabOrder( LineEditMoms4, LineEditMoms5 );
    setTabOrder( LineEditMoms5, PushButtonOK );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
frmDspFtgData::~frmDspFtgData()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void frmDspFtgData::languageChange()
{
    setCaption( trUtf8( "DSPFTGW Visa företagsdata" ) );
    PushButton5->setText( tr( "Uppdatera" ) );
    TextLabel4_3->setText( tr( "Postnummer:" ) );
    TextLabel4_2->setText( tr( "Postnummer:" ) );
    TextLabel4->setText( tr( "Postnummer:" ) );
    TextLabel6_3->setText( tr( "Ort:" ) );
    TextLabel6->setText( tr( "Ort:" ) );
    TextLabel6_2->setText( tr( "Ort:" ) );
    TextLabel8_2->setText( tr( "Telefax:" ) );
    TextLabel10->setText( tr( "Telex:" ) );
    TextLabel8->setText( tr( "Mobiltelefon:" ) );
    TextLabel14->setText( tr( "Momssats 3:" ) );
    TextLabel16->setText( tr( "Momssats 5:" ) );
    TextLabel15->setText( tr( "Momssats 4:" ) );
    TextLabel13->setText( tr( "Momssats 2:" ) );
    TextLabel2->setText( tr( "Postadress:" ) );
    TextLabel1->setText( trUtf8( "Företagsnamn:" ) );
    TextLabel5->setText( tr( "Godsadress:" ) );
    TextLabel7->setText( tr( "Telefonnummer:" ) );
    TextLabel9->setText( tr( "e-mailadress:" ) );
    TextLabel12->setText( tr( "Momssats 1:" ) );
    TextLabel3->setText( trUtf8( "Besöksadress:" ) );
    textLabel1->setText( trUtf8( "Momskonto, ingående moms: ............." ) );
    textLabel1_2->setText( trUtf8( "Momskonto, utgående moms: ......." ) );
    textLabel2->setText( tr( "Automatkontering J/N :" ) );
    PushButtonOK->setText( tr( "OK" ) );
    TextLabel11->setText( tr( "Organisationsnr:" ) );
}

