/****************************************************************************
** Form implementation generated from reading ui file 'frmchgftgdata.ui'
**
** Created: tis apr 22 07:08:04 2003
**      by:  The User Interface Compiler (uic)
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
 *  Constructs a frmChgFtgData which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
frmChgFtgData::frmChgFtgData( QWidget* parent,  const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "frmChgFtgData" );
    resize( 678, 296 ); 
    setCaption( trUtf8( "CHGFTGW - Ändra företagsdata" ) );

    TextLabel1 = new QLabel( this, "TextLabel1" );
    TextLabel1->setGeometry( QRect( 10, 15, 50, 16 ) ); 
    TextLabel1->setText( trUtf8( "Posttyp:" ) );

    PushButtonGet = new QPushButton( this, "PushButtonGet" );
    PushButtonGet->setGeometry( QRect( 125, 10, 51, 21 ) ); 
    PushButtonGet->setText( trUtf8( "Hämta" ) );
    PushButtonGet->setDefault( TRUE );

    PushButtonOK = new QPushButton( this, "PushButtonOK" );
    PushButtonOK->setGeometry( QRect( 5, 265, 65, 25 ) ); 
    PushButtonOK->setText( trUtf8( "OK" ) );
    PushButtonOK->setDefault( TRUE );

    ListView1 = new QListView( this, "ListView1" );
    ListView1->addColumn( trUtf8( "Posttyp" ) );
    ListView1->addColumn( trUtf8( "Benämning" ) );
    ListView1->setGeometry( QRect( 465, 6, 210, 285 ) ); 

    PushButtonUpdate = new QPushButton( this, "PushButtonUpdate" );
    PushButtonUpdate->setGeometry( QRect( 80, 265, 71, 26 ) ); 
    PushButtonUpdate->setText( trUtf8( "Uppdatera" ) );
    PushButtonUpdate->setDefault( TRUE );

    LineEditPosttyp = new QLineEdit( this, "LineEditPosttyp" );
    LineEditPosttyp->setGeometry( QRect( 65, 10, 51, 22 ) ); 

    // signals and slots connections
    connect( PushButtonOK, SIGNAL( clicked() ), this, SLOT( close() ) );
    connect( LineEditPosttyp, SIGNAL( returnPressed() ), this, SLOT( slotGetPosttyp() ) );
    connect( PushButtonGet, SIGNAL( clicked() ), this, SLOT( PushButtonGet_clicked() ) );
    connect( ListView1, SIGNAL( clicked(QListViewItem*) ), this, SLOT( ListView1_clicked(QListViewItem*) ) );
    connect( PushButtonUpdate, SIGNAL( clicked() ), this, SLOT( PushButtonUpdate_clicked() ) );
    init();
}

/*  
 *  Destroys the object and frees any allocated resources
 */
frmChgFtgData::~frmChgFtgData()
{
    // no need to delete child widgets, Qt does it all for us
}

