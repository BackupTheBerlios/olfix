/****************************************************************************
** Form implementation generated from reading ui file 'frmdspftgdata.ui'
**
** Created: ons apr 16 16:19:44 2003
**      by:  The User Interface Compiler (uic)
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
 *  Constructs a frmDspFtgData which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
frmDspFtgData::frmDspFtgData( QWidget* parent,  const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "frmDspFtgData" );
    resize( 715, 565 ); 
    setCaption( trUtf8( "DSPFTGW Visa företagsdata" ) );

    TextLabel2 = new QLabel( this, "TextLabel2" );
    TextLabel2->setGeometry( QRect( 10, 45, 86, 21 ) ); 
    TextLabel2->setText( trUtf8( "Postadress:" ) );

    TextLabel1 = new QLabel( this, "TextLabel1" );
    TextLabel1->setGeometry( QRect( 10, 15, 86, 21 ) ); 
    TextLabel1->setText( trUtf8( "Företagsnamn:" ) );

    TextLabel3 = new QLabel( this, "TextLabel3" );
    TextLabel3->setGeometry( QRect( 10, 75, 90, 25 ) ); 
    TextLabel3->setText( trUtf8( "Besöksadress:" ) );

    TextLabel4_2 = new QLabel( this, "TextLabel4_2" );
    TextLabel4_2->setGeometry( QRect( 315, 75, 74, 25 ) ); 
    TextLabel4_2->setText( trUtf8( "Postnummer:" ) );

    TextLabel4 = new QLabel( this, "TextLabel4" );
    TextLabel4->setGeometry( QRect( 315, 41, 74, 25 ) ); 
    TextLabel4->setText( trUtf8( "Postnummer:" ) );

    TextLabel4_3 = new QLabel( this, "TextLabel4_3" );
    TextLabel4_3->setGeometry( QRect( 315, 105, 74, 25 ) ); 
    TextLabel4_3->setText( trUtf8( "Postnummer:" ) );

    TextLabel6 = new QLabel( this, "TextLabel6" );
    TextLabel6->setGeometry( QRect( 485, 45, 30, 25 ) ); 
    TextLabel6->setText( trUtf8( "Ort:" ) );

    TextLabel6_2 = new QLabel( this, "TextLabel6_2" );
    TextLabel6_2->setGeometry( QRect( 485, 75, 30, 25 ) ); 
    TextLabel6_2->setText( trUtf8( "Ort:" ) );

    TextLabel6_3 = new QLabel( this, "TextLabel6_3" );
    TextLabel6_3->setGeometry( QRect( 485, 105, 30, 25 ) ); 
    TextLabel6_3->setText( trUtf8( "Ort:" ) );

    TextLabel5 = new QLabel( this, "TextLabel5" );
    TextLabel5->setGeometry( QRect( 10, 101, 90, 25 ) ); 
    TextLabel5->setText( trUtf8( "Godsadress:" ) );

    LineEditPostAdress = new QLineEdit( this, "LineEditPostAdress" );
    LineEditPostAdress->setGeometry( QRect( 100, 41, 211, 25 ) ); 

    LineEditBesoksAdress = new QLineEdit( this, "LineEditBesoksAdress" );
    LineEditBesoksAdress->setGeometry( QRect( 100, 70, 211, 25 ) ); 

    LineEditGodsAdress = new QLineEdit( this, "LineEditGodsAdress" );
    LineEditGodsAdress->setGeometry( QRect( 100, 100, 211, 25 ) ); 

    LineEditPostnr1 = new QLineEdit( this, "LineEditPostnr1" );
    LineEditPostnr1->setGeometry( QRect( 390, 41, 86, 25 ) ); 

    LineEditPostnr2 = new QLineEdit( this, "LineEditPostnr2" );
    LineEditPostnr2->setGeometry( QRect( 390, 70, 86, 25 ) ); 

    LineEditPostnr3 = new QLineEdit( this, "LineEditPostnr3" );
    LineEditPostnr3->setGeometry( QRect( 390, 100, 86, 25 ) ); 

    LineEditBesoksOrt = new QLineEdit( this, "LineEditBesoksOrt" );
    LineEditBesoksOrt->setGeometry( QRect( 515, 70, 191, 25 ) ); 

    LineEditGodsOrt = new QLineEdit( this, "LineEditGodsOrt" );
    LineEditGodsOrt->setGeometry( QRect( 515, 100, 191, 25 ) ); 

    TextLabel7 = new QLabel( this, "TextLabel7" );
    TextLabel7->setGeometry( QRect( 10, 141, 91, 20 ) ); 
    TextLabel7->setText( trUtf8( "Telefonnummer:" ) );

    TextLabel8 = new QLabel( this, "TextLabel8" );
    TextLabel8->setGeometry( QRect( 225, 141, 80, 20 ) ); 
    TextLabel8->setText( trUtf8( "Mobiltelefon:" ) );

    TextLabel9 = new QLabel( this, "TextLabel9" );
    TextLabel9->setGeometry( QRect( 10, 170, 91, 21 ) ); 
    TextLabel9->setText( trUtf8( "e-mailadress:" ) );

    LineEditemailadress = new QLineEdit( this, "LineEditemailadress" );
    LineEditemailadress->setGeometry( QRect( 100, 170, 321, 25 ) ); 

    TextLabel11 = new QLabel( this, "TextLabel11" );
    TextLabel11->setGeometry( QRect( 415, 10, 99, 26 ) ); 
    TextLabel11->setText( trUtf8( "Företagsnummer:" ) );

    LineEditPostOrt = new QLineEdit( this, "LineEditPostOrt" );
    LineEditPostOrt->setGeometry( QRect( 515, 40, 191, 25 ) ); 

    LineEditMoms1 = new QLineEdit( this, "LineEditMoms1" );
    LineEditMoms1->setGeometry( QRect( 100, 215, 46, 22 ) ); 

    TextLabel12 = new QLabel( this, "TextLabel12" );
    TextLabel12->setGeometry( QRect( 10, 215, 90, 21 ) ); 
    TextLabel12->setText( trUtf8( "Momssats 1:" ) );

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

    Line1_3 = new QFrame( this, "Line1_3" );
    Line1_3->setGeometry( QRect( 10, 245, 696, 10 ) ); 
    Line1_3->setFrameShape( QFrame::HLine );
    Line1_3->setFrameShadow( QFrame::Sunken );
    Line1_3->setFrameShape( QFrame::HLine );

    LineEdit1Telex = new QLineEdit( this, "LineEdit1Telex" );
    LineEdit1Telex->setGeometry( QRect( 590, 170, 116, 26 ) ); 

    TextLabel8_2 = new QLabel( this, "TextLabel8_2" );
    TextLabel8_2->setGeometry( QRect( 530, 145, 60, 20 ) ); 
    TextLabel8_2->setText( trUtf8( "Telefax:" ) );

    TextLabel10 = new QLabel( this, "TextLabel10" );
    TextLabel10->setGeometry( QRect( 530, 175, 45, 20 ) ); 
    TextLabel10->setText( trUtf8( "Telex:" ) );

    LineEditMoms5 = new QLineEdit( this, "LineEditMoms5" );
    LineEditMoms5->setGeometry( QRect( 660, 215, 46, 22 ) ); 

    TextLabel16 = new QLabel( this, "TextLabel16" );
    TextLabel16->setGeometry( QRect( 585, 215, 75, 21 ) ); 
    TextLabel16->setText( trUtf8( "Momssats 5:" ) );

    LineEditMoms4 = new QLineEdit( this, "LineEditMoms4" );
    LineEditMoms4->setGeometry( QRect( 520, 215, 46, 22 ) ); 

    TextLabel15 = new QLabel( this, "TextLabel15" );
    TextLabel15->setGeometry( QRect( 445, 215, 75, 21 ) ); 
    TextLabel15->setText( trUtf8( "Momssats 4:" ) );

    LineEditMoms3 = new QLineEdit( this, "LineEditMoms3" );
    LineEditMoms3->setGeometry( QRect( 380, 215, 46, 22 ) ); 

    TextLabel14 = new QLabel( this, "TextLabel14" );
    TextLabel14->setGeometry( QRect( 310, 215, 75, 21 ) ); 
    TextLabel14->setText( trUtf8( "Momssats 3:" ) );

    LineEditMoms2 = new QLineEdit( this, "LineEditMoms2" );
    LineEditMoms2->setGeometry( QRect( 245, 215, 46, 22 ) ); 

    TextLabel13 = new QLabel( this, "TextLabel13" );
    TextLabel13->setGeometry( QRect( 170, 215, 75, 21 ) ); 
    TextLabel13->setText( trUtf8( "Momssats 2:" ) );

    LineEditFtgNamn = new QLineEdit( this, "LineEditFtgNamn" );
    LineEditFtgNamn->setGeometry( QRect( 100, 10, 290, 25 ) ); 

    LineEditFtgNr = new QLineEdit( this, "LineEditFtgNr" );
    LineEditFtgNr->setGeometry( QRect( 515, 10, 191, 25 ) ); 

    PushButtonOK = new QPushButton( this, "PushButtonOK" );
    PushButtonOK->setGeometry( QRect( 10, 535, 71, 20 ) ); 
    PushButtonOK->setText( trUtf8( "OK" ) );
    PushButtonOK->setDefault( TRUE );

    LineEditTfnnr = new QLineEdit( this, "LineEditTfnnr" );
    LineEditTfnnr->setGeometry( QRect( 100, 140, 116, 26 ) ); 

    LineEditMobilTfn = new QLineEdit( this, "LineEditMobilTfn" );
    LineEditMobilTfn->setGeometry( QRect( 305, 140, 116, 26 ) ); 

    LineEditTelefax = new QLineEdit( this, "LineEditTelefax" );
    LineEditTelefax->setGeometry( QRect( 590, 140, 116, 26 ) ); 

    // signals and slots connections
    connect( PushButtonOK, SIGNAL( clicked() ), this, SLOT( close() ) );

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

