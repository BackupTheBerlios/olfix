/****************************************************************************
** Form implementation generated from reading ui file 'frmaddvaluta.ui'
**
** Created: fre jun 6 06:33:12 2003
**      by: The User Interface Compiler ($Id: frmaddvaluta.cpp,v 1.2 2003/09/28 06:25:24 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "frmaddvaluta.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "frmaddvaluta.ui.h"

/* 
 *  Constructs a frmAddValuta as a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
frmAddValuta::frmAddValuta( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "frmAddValuta" );

    TextLabelSalj = new QLabel( this, "TextLabelSalj" );
    TextLabelSalj->setGeometry( QRect( 10, 150, 70, 21 ) );

    TextLabelKop = new QLabel( this, "TextLabelKop" );
    TextLabelKop->setGeometry( QRect( 10, 120, 70, 21 ) );

    TextLabelBeteckn = new QLabel( this, "TextLabelBeteckn" );
    TextLabelBeteckn->setGeometry( QRect( 10, 60, 70, 21 ) );

    TextLabelValuta = new QLabel( this, "TextLabelValuta" );
    TextLabelValuta->setGeometry( QRect( 10, 30, 81, 21 ) );

    TextLabelLand = new QLabel( this, "TextLabelLand" );
    TextLabelLand->setGeometry( QRect( 10, 90, 70, 21 ) );

    LineEditKop = new QLineEdit( this, "LineEditKop" );
    LineEditKop->setGeometry( QRect( 90, 120, 80, 22 ) );

    LineEditLand = new QLineEdit( this, "LineEditLand" );
    LineEditLand->setGeometry( QRect( 90, 90, 210, 22 ) );

    LineEditValuta = new QLineEdit( this, "LineEditValuta" );
    LineEditValuta->setGeometry( QRect( 91, 30, 45, 22 ) );

    LineEditSalj = new QLineEdit( this, "LineEditSalj" );
    LineEditSalj->setGeometry( QRect( 90, 150, 80, 22 ) );

    PushButtonOK = new QPushButton( this, "PushButtonOK" );
    PushButtonOK->setGeometry( QRect( 5, 185, 51, 21 ) );
    PushButtonOK->setDefault( TRUE );

    LineEditBeteck = new QLineEdit( this, "LineEditBeteck" );
    LineEditBeteck->setGeometry( QRect( 90, 60, 210, 22 ) );

    PushButtonQuit = new QPushButton( this, "PushButtonQuit" );
    PushButtonQuit->setGeometry( QRect( 65, 185, 61, 21 ) );
    languageChange();
    resize( QSize(316, 214).expandedTo(minimumSizeHint()) );

    // signals and slots connections
    connect( PushButtonQuit, SIGNAL( clicked() ), this, SLOT( close() ) );
    connect( PushButtonOK, SIGNAL( clicked() ), LineEditValuta, SLOT( setFocus() ) );
    connect( LineEditValuta, SIGNAL( returnPressed() ), this, SLOT( slotValutaEntered() ) );
    connect( LineEditBeteck, SIGNAL( returnPressed() ), this, SLOT( slotBeteckningEntered() ) );
    connect( LineEditLand, SIGNAL( returnPressed() ), this, SLOT( slotLandEntered() ) );
    connect( LineEditKop, SIGNAL( returnPressed() ), this, SLOT( slotKopEntered() ) );
    connect( LineEditSalj, SIGNAL( returnPressed() ), this, SLOT( slotSaljEntered() ) );
    connect( LineEditSalj, SIGNAL( returnPressed() ), PushButtonOK, SLOT( setFocus() ) );
    connect( PushButtonOK, SIGNAL( clicked() ), this, SLOT( slotAddValuta() ) );
    connect( LineEditValuta, SIGNAL( lostFocus() ), this, SLOT( slotValuta_lostFocus() ) );
    connect( LineEditBeteck, SIGNAL( lostFocus() ), this, SLOT( slotBeteckning_lostFocus() ) );
    connect( LineEditLand, SIGNAL( lostFocus() ), this, SLOT( slotLand_lostFocus() ) );
    connect( LineEditKop, SIGNAL( lostFocus() ), this, SLOT( slotKop_lostFocus() ) );
    connect( LineEditSalj, SIGNAL( lostFocus() ), this, SLOT( slotSalj_lostFocus() ) );

    // tab order
    setTabOrder( LineEditValuta, LineEditBeteck );
    setTabOrder( LineEditBeteck, LineEditLand );
    setTabOrder( LineEditLand, LineEditKop );
    setTabOrder( LineEditKop, LineEditSalj );
    setTabOrder( LineEditSalj, PushButtonOK );
    setTabOrder( PushButtonOK, PushButtonQuit );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
frmAddValuta::~frmAddValuta()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void frmAddValuta::languageChange()
{
    setCaption( trUtf8( "ADDVALW  Lägga upp ny valuta" ) );
    TextLabelSalj->setText( trUtf8( "Sälj:" ) );
    TextLabelKop->setText( trUtf8( "Köp:" ) );
    TextLabelBeteckn->setText( tr( "Beteckning:" ) );
    TextLabelValuta->setText( tr( "Valuta:" ) );
    TextLabelLand->setText( tr( "Land:" ) );
    PushButtonOK->setText( tr( "OK" ) );
    PushButtonQuit->setText( tr( "Avsluta" ) );
}

