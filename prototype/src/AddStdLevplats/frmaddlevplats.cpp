/****************************************************************************
** Form implementation generated from reading ui file 'frmaddlevplats.ui'
**
** Created: ons sep 10 10:54:21 2003
**      by: The User Interface Compiler ($Id: frmaddlevplats.cpp,v 1.1 2003/09/28 06:21:29 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "frmaddlevplats.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "frmaddlevplats.ui.h"

/* 
 *  Constructs a frmAddLevplats as a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
frmAddLevplats::frmAddLevplats( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "frmAddLevplats" );

    textLabel1_2_3 = new QLabel( this, "textLabel1_2_3" );
    textLabel1_2_3->setGeometry( QRect( 95, 75, 16, 16 ) );
    textLabel1_2_3->setPaletteForegroundColor( QColor( 255, 0, 0 ) );

    textLabel2_2 = new QLabel( this, "textLabel2_2" );
    textLabel2_2->setGeometry( QRect( 35, 15, 96, 16 ) );

    pushButtonAvbryt = new QPushButton( this, "pushButtonAvbryt" );
    pushButtonAvbryt->setGeometry( QRect( 80, 205, 61, 20 ) );
    pushButtonAvbryt->setDefault( TRUE );

    pushButtonOK = new QPushButton( this, "pushButtonOK" );
    pushButtonOK->setGeometry( QRect( 15, 205, 56, 20 ) );
    pushButtonOK->setDefault( TRUE );

    lineEditKundID = new QLineEdit( this, "lineEditKundID" );
    lineEditKundID->setGeometry( QRect( 135, 45, 65, 23 ) );

    lineEditLevPlatsNr = new QLineEdit( this, "lineEditLevPlatsNr" );
    lineEditLevPlatsNr->setGeometry( QRect( 135, 70, 65, 23 ) );

    lineEditLevAdress = new QLineEdit( this, "lineEditLevAdress" );
    lineEditLevAdress->setGeometry( QRect( 135, 95, 301, 23 ) );

    textLabel1_2 = new QLabel( this, "textLabel1_2" );
    textLabel1_2->setGeometry( QRect( 15, 15, 16, 16 ) );
    textLabel1_2->setPaletteForegroundColor( QColor( 255, 0, 0 ) );

    textLabel1_2_5 = new QLabel( this, "textLabel1_2_5" );
    textLabel1_2_5->setGeometry( QRect( 115, 100, 16, 16 ) );
    textLabel1_2_5->setPaletteForegroundColor( QColor( 255, 0, 0 ) );

    lineEditPostnr = new QLineEdit( this, "lineEditPostnr" );
    lineEditPostnr->setGeometry( QRect( 135, 120, 65, 23 ) );

    lineEditPostAdress = new QLineEdit( this, "lineEditPostAdress" );
    lineEditPostAdress->setGeometry( QRect( 135, 145, 301, 23 ) );

    lineEditLand = new QLineEdit( this, "lineEditLand" );
    lineEditLand->setGeometry( QRect( 135, 170, 301, 23 ) );

    textLabel6 = new QLabel( this, "textLabel6" );
    textLabel6->setGeometry( QRect( 15, 175, 115, 16 ) );

    textLabel1_2_7 = new QLabel( this, "textLabel1_2_7" );
    textLabel1_2_7->setGeometry( QRect( 115, 150, 16, 16 ) );
    textLabel1_2_7->setPaletteForegroundColor( QColor( 255, 0, 0 ) );

    textLabel5 = new QLabel( this, "textLabel5" );
    textLabel5->setGeometry( QRect( 15, 150, 95, 16 ) );

    textLabel1_2_6 = new QLabel( this, "textLabel1_2_6" );
    textLabel1_2_6->setGeometry( QRect( 115, 125, 16, 16 ) );
    textLabel1_2_6->setPaletteForegroundColor( QColor( 255, 0, 0 ) );

    textLabel4 = new QLabel( this, "textLabel4" );
    textLabel4->setGeometry( QRect( 15, 125, 95, 16 ) );

    textLabel3 = new QLabel( this, "textLabel3" );
    textLabel3->setGeometry( QRect( 15, 100, 102, 16 ) );

    textLabel1_2_4 = new QLabel( this, "textLabel1_2_4" );
    textLabel1_2_4->setGeometry( QRect( 115, 75, 16, 16 ) );
    textLabel1_2_4->setPaletteForegroundColor( QColor( 255, 0, 0 ) );

    textLabel2 = new QLabel( this, "textLabel2" );
    textLabel2->setGeometry( QRect( 15, 75, 90, 16 ) );

    textLabel1_2_2 = new QLabel( this, "textLabel1_2_2" );
    textLabel1_2_2->setGeometry( QRect( 115, 50, 16, 16 ) );
    textLabel1_2_2->setPaletteForegroundColor( QColor( 255, 0, 0 ) );

    textLabel1 = new QLabel( this, "textLabel1" );
    textLabel1->setGeometry( QRect( 15, 50, 95, 16 ) );
    languageChange();
    resize( QSize(444, 238).expandedTo(minimumSizeHint()) );

    // signals and slots connections
    connect( lineEditKundID, SIGNAL( returnPressed() ), this, SLOT( lineEditKundID_returnPressed() ) );
    connect( lineEditLevPlatsNr, SIGNAL( returnPressed() ), this, SLOT( lineEditLevPlatsNr_returnPressed() ) );
    connect( lineEditLevAdress, SIGNAL( returnPressed() ), this, SLOT( lineEditLevAdress_returnPressed() ) );
    connect( lineEditPostnr, SIGNAL( returnPressed() ), this, SLOT( lineEditPostnr_returnPressed() ) );
    connect( lineEditPostAdress, SIGNAL( returnPressed() ), this, SLOT( lineEditPostAdress_returnPressed() ) );
    connect( lineEditLand, SIGNAL( returnPressed() ), this, SLOT( lineEditLand_returnPressed() ) );
    connect( pushButtonOK, SIGNAL( clicked() ), this, SLOT( pushButtonOK_clicked() ) );
    connect( pushButtonAvbryt, SIGNAL( clicked() ), this, SLOT( close() ) );

    // tab order
    setTabOrder( lineEditKundID, lineEditLevPlatsNr );
    setTabOrder( lineEditLevPlatsNr, lineEditLevAdress );
    setTabOrder( lineEditLevAdress, lineEditPostnr );
    setTabOrder( lineEditPostnr, lineEditPostAdress );
    setTabOrder( lineEditPostAdress, lineEditLand );
    setTabOrder( lineEditLand, pushButtonOK );
    setTabOrder( pushButtonOK, pushButtonAvbryt );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
frmAddLevplats::~frmAddLevplats()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void frmAddLevplats::languageChange()
{
    setCaption( tr( "ADDLEVPW - Ny standardleveransplats" ) );
    textLabel1_2_3->setText( tr( "<p align=\"center\">*</p>" ) );
    textLabel2_2->setText( tr( "= Obligatoriskt." ) );
    pushButtonAvbryt->setText( tr( "Avbryt" ) );
    pushButtonOK->setText( tr( "OK" ) );
    lineEditLevPlatsNr->setText( tr( "001" ) );
    textLabel1_2->setText( tr( "<p align=\"center\">*</p>" ) );
    textLabel1_2_5->setText( tr( "<p align=\"center\">*</p>" ) );
    lineEditLand->setText( QString::null );
    textLabel6->setText( tr( "Land:" ) );
    textLabel1_2_7->setText( tr( "<p align=\"center\">*</p>" ) );
    textLabel5->setText( tr( "Postadress:" ) );
    textLabel1_2_6->setText( tr( "<p align=\"center\">*</p>" ) );
    textLabel4->setText( tr( "Postnummer:" ) );
    textLabel3->setText( tr( "Leveransadress:" ) );
    textLabel1_2_4->setText( tr( "<p align=\"center\">*</p>" ) );
    textLabel2->setText( tr( "Platsnummer:" ) );
    textLabel1_2_2->setText( tr( "<p align=\"center\">*</p>" ) );
    textLabel1->setText( tr( "KundID:" ) );
}

