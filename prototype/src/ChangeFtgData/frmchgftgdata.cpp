/****************************************************************************
** Form implementation generated from reading ui file 'frmchgftgdata.ui'
**
** Created: tor aug 14 09:31:54 2003
**      by: The User Interface Compiler ($Id: frmchgftgdata.cpp,v 1.2 2003/09/28 06:40:16 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "frmchgftgdata.h"

#include <qvariant.h>
#include <qheader.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qlistview.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "frmchgftgdata.ui.h"

/* 
 *  Constructs a frmChgFtgData as a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
frmChgFtgData::frmChgFtgData( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "frmChgFtgData" );

    TextLabel1 = new QLabel( this, "TextLabel1" );
    TextLabel1->setGeometry( QRect( 10, 15, 50, 16 ) );

    PushButtonOK = new QPushButton( this, "PushButtonOK" );
    PushButtonOK->setGeometry( QRect( 5, 265, 65, 25 ) );
    PushButtonOK->setDefault( TRUE );

    PushButtonUpdate = new QPushButton( this, "PushButtonUpdate" );
    PushButtonUpdate->setGeometry( QRect( 80, 265, 71, 26 ) );
    PushButtonUpdate->setDefault( TRUE );

    ListView1 = new QListView( this, "ListView1" );
    ListView1->addColumn( tr( "Posttyp" ) );
    ListView1->addColumn( trUtf8( "Benämning" ) );
    ListView1->setGeometry( QRect( 465, 6, 210, 285 ) );

    PushButtonGet = new QPushButton( this, "PushButtonGet" );
    PushButtonGet->setGeometry( QRect( 130, 10, 51, 21 ) );
    PushButtonGet->setDefault( TRUE );

    LineEditPosttyp = new QLineEdit( this, "LineEditPosttyp" );
    LineEditPosttyp->setGeometry( QRect( 61, 10, 60, 22 ) );
    languageChange();
    resize( QSize(682, 300).expandedTo(minimumSizeHint()) );

    // signals and slots connections
    connect( PushButtonOK, SIGNAL( clicked() ), this, SLOT( close() ) );
    connect( LineEditPosttyp, SIGNAL( returnPressed() ), this, SLOT( slotGetPosttyp() ) );
    connect( PushButtonGet, SIGNAL( clicked() ), this, SLOT( PushButtonGet_clicked() ) );
    connect( ListView1, SIGNAL( clicked(QListViewItem*) ), this, SLOT( ListView1_clicked(QListViewItem*) ) );
    connect( PushButtonUpdate, SIGNAL( clicked() ), this, SLOT( PushButtonUpdate_clicked() ) );
    connect( LineEditPosttyp, SIGNAL( lostFocus() ), this, SLOT( slotGetPosttyp() ) );

    // tab order
    setTabOrder( LineEditPosttyp, PushButtonGet );
    setTabOrder( PushButtonGet, PushButtonOK );
    setTabOrder( PushButtonOK, PushButtonUpdate );
    setTabOrder( PushButtonUpdate, ListView1 );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
frmChgFtgData::~frmChgFtgData()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void frmChgFtgData::languageChange()
{
    setCaption( trUtf8( "CHGFTGW - Ändra företagsdata" ) );
    TextLabel1->setText( tr( "Posttyp:" ) );
    PushButtonOK->setText( tr( "OK" ) );
    PushButtonUpdate->setText( tr( "Uppdatera" ) );
    ListView1->header()->setLabel( 0, tr( "Posttyp" ) );
    ListView1->header()->setLabel( 1, trUtf8( "Benämning" ) );
    PushButtonGet->setText( trUtf8( "Hämta" ) );
}

