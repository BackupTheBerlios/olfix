/****************************************************************************
** Form implementation generated from reading ui file 'frmsaldolista.ui'
**
** Created: lör aug 23 09:52:02 2003
**      by: The User Interface Compiler ($Id: frmsaldolista.cpp,v 1.1 2003/09/28 08:39:42 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "frmsaldolista.h"

#include <qvariant.h>
#include <qbuttongroup.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qradiobutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "frmsaldolista.ui.h"

/* 
 *  Constructs a frmSaldolista as a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
frmSaldolista::frmSaldolista( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "frmSaldolista" );

    textLabel1 = new QLabel( this, "textLabel1" );
    textLabel1->setGeometry( QRect( 10, 5, 85, 19 ) );
    QFont textLabel1_font(  textLabel1->font() );
    textLabel1_font.setFamily( "Times" );
    textLabel1_font.setPointSize( 16 );
    textLabel1_font.setBold( TRUE );
    textLabel1->setFont( textLabel1_font ); 

    textLabel2 = new QLabel( this, "textLabel2" );
    textLabel2->setGeometry( QRect( 10, 30, 46, 16 ) );

    textLabelDatum = new QLabel( this, "textLabelDatum" );
    textLabelDatum->setGeometry( QRect( 60, 30, 80, 16 ) );

    textLabel4 = new QLabel( this, "textLabel4" );
    textLabel4->setGeometry( QRect( 10, 50, 85, 16 ) );

    pushButtonOK = new QPushButton( this, "pushButtonOK" );
    pushButtonOK->setGeometry( QRect( 20, 210, 100, 21 ) );
    pushButtonOK->setDefault( TRUE );

    pushButtonAvbryt = new QPushButton( this, "pushButtonAvbryt" );
    pushButtonAvbryt->setGeometry( QRect( 130, 210, 76, 21 ) );
    pushButtonAvbryt->setDefault( TRUE );

    lineEditBar = new QLineEdit( this, "lineEditBar" );
    lineEditBar->setGeometry( QRect( 95, 50, 46, 23 ) );

    buttonGroup1 = new QButtonGroup( this, "buttonGroup1" );
    buttonGroup1->setGeometry( QRect( 5, 80, 135, 60 ) );

    textLabel2_2 = new QLabel( buttonGroup1, "textLabel2_2" );
    textLabel2_2->setGeometry( QRect( 10, 10, 100, 16 ) );

    textLabel3 = new QLabel( buttonGroup1, "textLabel3" );
    textLabel3->setGeometry( QRect( 10, 35, 96, 16 ) );

    radioButtonCSV = new QRadioButton( buttonGroup1, "radioButtonCSV" );
    radioButtonCSV->setGeometry( QRect( 110, 10, 16, 16 ) );
    radioButtonCSV->setChecked( TRUE );

    radioButtonPrint = new QRadioButton( buttonGroup1, "radioButtonPrint" );
    radioButtonPrint->setGeometry( QRect( 110, 35, 16, 20 ) );
    radioButtonPrint->setChecked( FALSE );

    textLabel4_2 = new QLabel( this, "textLabel4_2" );
    textLabel4_2->setGeometry( QRect( 145, 85, 237, 21 ) );

    textLabel5 = new QLabel( this, "textLabel5" );
    textLabel5->setGeometry( QRect( 145, 110, 301, 26 ) );
    languageChange();
    resize( QSize(550, 240).expandedTo(minimumSizeHint()) );

    // signals and slots connections
    connect( lineEditBar, SIGNAL( returnPressed() ), this, SLOT( slotlineEditBar_returnPressed() ) );
    connect( pushButtonOK, SIGNAL( clicked() ), this, SLOT( slotpushButtonOK_clicked() ) );
    connect( pushButtonAvbryt, SIGNAL( clicked() ), this, SLOT( close() ) );
    connect( radioButtonCSV, SIGNAL( toggled(bool) ), this, SLOT( radioButtonCSV_toggled(bool) ) );
    connect( radioButtonPrint, SIGNAL( toggled(bool) ), this, SLOT( radioButtonPrint_toggled(bool) ) );

    // tab order
    setTabOrder( lineEditBar, pushButtonOK );
    setTabOrder( pushButtonOK, pushButtonAvbryt );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
frmSaldolista::~frmSaldolista()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void frmSaldolista::languageChange()
{
    setCaption( tr( "SDOLISW - Saldolista" ) );
    textLabel1->setText( tr( "Saldolista" ) );
    textLabel2->setText( tr( "Datum:" ) );
    textLabelDatum->setText( tr( "2003-08-01" ) );
    textLabel4->setText( trUtf8( "Bokföringsår:" ) );
    pushButtonOK->setText( tr( "Skapa rapport" ) );
    pushButtonAvbryt->setText( tr( "Avbryt" ) );
    QToolTip::add( lineEditBar, trUtf8( "Ange bokföringsår med 2 bokstäver" ) );
    buttonGroup1->setTitle( QString::null );
    textLabel2_2->setText( tr( "CSV-format:" ) );
    textLabel3->setText( tr( "Utskriftsformat:" ) );
    radioButtonCSV->setText( tr( "radioButtonCSV" ) );
    QToolTip::add( radioButtonCSV, tr( "Skapar en rapport i kommaseparerat format och startar Kspread" ) );
    radioButtonPrint->setText( tr( "radioButtonPrint" ) );
    QToolTip::add( radioButtonPrint, trUtf8( "Skapar en rapport för Kugar" ) );
    textLabel4_2->setText( tr( "Startar Kspread med importerade data." ) );
    textLabel5->setText( trUtf8( "Skapar en rapport  med Kugar färdig att skriva ut." ) );
}

