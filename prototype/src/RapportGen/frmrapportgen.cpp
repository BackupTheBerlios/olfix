/****************************************************************************
** Form implementation generated from reading ui file 'frmrapportgen.ui'
**
** Created: ons aug 27 09:54:04 2003
**      by: The User Interface Compiler ($Id: frmrapportgen.cpp,v 1.1 2003/09/28 08:35:04 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "frmrapportgen.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qtextedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "frmrapportgen.ui.h"

/* 
 *  Constructs a frmRapportGen as a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
frmRapportGen::frmRapportGen( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )

{
    if ( !name )
	setName( "frmRapportGen" );

    textLabel1 = new QLabel( this, "textLabel1" );
    textLabel1->setGeometry( QRect( 10, 5, 120, 16 ) );

    pushButtonOK = new QPushButton( this, "pushButtonOK" );
    pushButtonOK->setGeometry( QRect( 10, 445, 101, 25 ) );
    pushButtonOK->setDefault( TRUE );

    pushButtonQuit = new QPushButton( this, "pushButtonQuit" );
    pushButtonQuit->setGeometry( QRect( 120, 445, 66, 25 ) );
    pushButtonQuit->setDefault( TRUE );

    textLabel2 = new QLabel( this, "textLabel2" );
    textLabel2->setGeometry( QRect( 10, 170, 148, 16 ) );

    textLabel3 = new QLabel( this, "textLabel3" );
    textLabel3->setGeometry( QRect( 170, 170, 95, 16 ) );

    textLabel1_2 = new QLabel( this, "textLabel1_2" );
    textLabel1_2->setGeometry( QRect( 10, 235, 55, 16 ) );

    textLabelExempel = new QLabel( this, "textLabelExempel" );
    textLabelExempel->setGeometry( QRect( 10, 255, 428, 84 ) );
    textLabelExempel->setPaletteBackgroundColor( QColor( 255, 255, 0 ) );

    textEditSQL = new QTextEdit( this, "textEditSQL" );
    textEditSQL->setGeometry( QRect( 6, 25, 585, 136 ) );

    pushButtonGetFile = new QPushButton( this, "pushButtonGetFile" );
    pushButtonGetFile->setGeometry( QRect( 10, 190, 150, 25 ) );

    pushButtonSaveFile = new QPushButton( this, "pushButtonSaveFile" );
    pushButtonSaveFile->setGeometry( QRect( 165, 190, 100, 25 ) );

    pushButtonHelp = new QPushButton( this, "pushButtonHelp" );
    pushButtonHelp->setGeometry( QRect( 520, 190, 66, 25 ) );

    pushButtonClear = new QPushButton( this, "pushButtonClear" );
    pushButtonClear->setGeometry( QRect( 270, 190, 96, 25 ) );
    languageChange();
    resize( QSize(600, 480).expandedTo(minimumSizeHint()) );

    // signals and slots connections
    connect( pushButtonQuit, SIGNAL( clicked() ), this, SLOT( close() ) );
    connect( textEditSQL, SIGNAL( returnPressed() ), this, SLOT( slottextEditSQL_returnPressed() ) );
    connect( pushButtonOK, SIGNAL( clicked() ), this, SLOT( slotpushButtonOK_clicked() ) );
    connect( pushButtonQuit, SIGNAL( pressed() ), this, SLOT( close() ) );
    connect( pushButtonGetFile, SIGNAL( clicked() ), this, SLOT( GetFileDialog() ) );
    connect( pushButtonSaveFile, SIGNAL( clicked() ), this, SLOT( SaveFileDialog() ) );
    connect( pushButtonClear, SIGNAL( clicked() ), this, SLOT( slotClearSqlQuery() ) );
    connect( textEditSQL, SIGNAL( textChanged() ), this, SLOT( slottextEditSQL_TextChanged() ) );
    connect( pushButtonHelp, SIGNAL( clicked() ), this, SLOT( slotHelp() ) );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
frmRapportGen::~frmRapportGen()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void frmRapportGen::languageChange()
{
    setCaption( tr( "RPTGENW - Rapportgenerator" ) );
    textLabel1->setText( trUtf8( "Skriv en SQL-fråga" ) );
    pushButtonOK->setText( tr( "Skapa rapport" ) );
    pushButtonQuit->setText( tr( "Avbryt" ) );
    textLabel2->setText( trUtf8( "Hämta sparad sqlfråga." ) );
    textLabel3->setText( trUtf8( "Spara sqlfråga" ) );
    textLabel1_2->setText( tr( "Exempel" ) );
    textLabelExempel->setText( tr( "SELECT EXPIREDATUM,LEVNR,FAKTURANR,FAKTBELOPP,VALUTA \n"
"FROM LEVRESK \n"
"where EXPIREDATUM < '2003-09-09' and BETALD = 'N'\n"
"order by LEVNR,EXPIREDATUM,FAKTURANR\n"
"" ) );
    QToolTip::add( textEditSQL, trUtf8( "Skriv en SQL-fråga" ) );
    pushButtonGetFile->setText( trUtf8( "Hämta fil" ) );
    pushButtonSaveFile->setText( tr( "Spara fil" ) );
    pushButtonHelp->setText( trUtf8( "Hjälp" ) );
    pushButtonClear->setText( tr( "Rensa text" ) );
}

