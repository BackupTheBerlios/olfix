/****************************************************************************
** Form implementation generated from reading ui file 'frmlevfaktattbetala.ui'
**
** Created: ons aug 20 21:36:12 2003
**      by: The User Interface Compiler ($Id: frmlevfaktattbetala.cpp,v 1.1 2003/09/28 08:09:37 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "frmlevfaktattbetala.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "frmlevfaktattbetala.ui.h"

/* 
 *  Constructs a frmLevFaktAttBetala as a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
frmLevFaktAttBetala::frmLevFaktAttBetala( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "frmLevFaktAttBetala" );

    textLabel1 = new QLabel( this, "textLabel1" );
    textLabel1->setGeometry( QRect( 15, 25, 91, 16 ) );

    pushButtonOK = new QPushButton( this, "pushButtonOK" );
    pushButtonOK->setGeometry( QRect( 15, 180, 100, 21 ) );
    pushButtonOK->setDefault( TRUE );

    pushButtonAvbryt = new QPushButton( this, "pushButtonAvbryt" );
    pushButtonAvbryt->setGeometry( QRect( 125, 180, 66, 21 ) );
    pushButtonAvbryt->setDefault( TRUE );

    lineEditExpireDate = new QLineEdit( this, "lineEditExpireDate" );
    lineEditExpireDate->setGeometry( QRect( 115, 20, 106, 23 ) );
    languageChange();
    resize( QSize(463, 207).expandedTo(minimumSizeHint()) );

    // signals and slots connections
    connect( pushButtonOK, SIGNAL( clicked() ), this, SLOT( slotpushButtonOK_clicked() ) );
    connect( pushButtonAvbryt, SIGNAL( clicked() ), this, SLOT( close() ) );
    connect( lineEditExpireDate, SIGNAL( returnPressed() ), this, SLOT( slotlineEditExpireDate_returnPressed() ) );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
frmLevFaktAttBetala::~frmLevFaktAttBetala()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void frmLevFaktAttBetala::languageChange()
{
    setCaption( trUtf8( "ATTBETW - Rapport över leverantörsfakturor att betala" ) );
    textLabel1->setText( trUtf8( "Förfallodatum:" ) );
    pushButtonOK->setText( tr( "Skapa rapport" ) );
    pushButtonAvbryt->setText( tr( "Avbryt" ) );
}

