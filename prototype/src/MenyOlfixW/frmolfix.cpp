/****************************************************************************
** Form implementation generated from reading ui file 'frmolfix.ui'
**
** Created: tis mar 25 05:38:23 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "frmolfix.h"

#include <qvariant.h>
#include <qheader.h>
#include <qlistview.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "frmolfix.ui.h"

/* 
 *  Constructs a frmOlfix which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
frmOlfix::frmOlfix( QWidget* parent,  const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "frmOlfix" );
    resize( 371, 421 ); 
    setPaletteBackgroundColor( QColor( 0, 255, 255 ) );
    setCaption( trUtf8( "OLFIX - Order/Lager/Fakturering för Linuxsystem" ) );
    setIconText( trUtf8( "OLFIX" ) );
    frmOlfixLayout = new QGridLayout( this, 1, 1, 11, 6, "frmOlfixLayout"); 

    PushButton4 = new QPushButton( this, "PushButton4" );
    PushButton4->setText( trUtf8( "Hjälp" ) );

    frmOlfixLayout->addWidget( PushButton4, 0, 1 );

    PushButton2 = new QPushButton( this, "PushButton2" );
    PushButton2->setText( trUtf8( "Om OLFIX" ) );

    frmOlfixLayout->addWidget( PushButton2, 0, 3 );

    PushButton3 = new QPushButton( this, "PushButton3" );
    PushButton3->setText( trUtf8( "Licensvillkor" ) );

    frmOlfixLayout->addWidget( PushButton3, 0, 2 );

    ListView1 = new QListView( this, "ListView1" );
    ListView1->addColumn( trUtf8( "Funktioner" ) );
    ListView1->addColumn( trUtf8( "Program" ) );
    ListView1->setRootIsDecorated( TRUE );

    frmOlfixLayout->addMultiCellWidget( ListView1, 1, 2, 1, 3 );

    PushButtonQuit = new QPushButton( this, "PushButtonQuit" );
    PushButtonQuit->setText( trUtf8( "Slut" ) );

    frmOlfixLayout->addWidget( PushButtonQuit, 2, 0 );
    QSpacerItem* spacer = new QSpacerItem( 0, 385, QSizePolicy::Minimum, QSizePolicy::Expanding );
    frmOlfixLayout->addMultiCell( spacer, 0, 1, 0, 0 );

    // signals and slots connections
    connect( PushButtonQuit, SIGNAL( clicked() ), this, SLOT( close() ) );
    connect( ListView1, SIGNAL( clicked(QListViewItem*) ), this, SLOT( ListView1_clicked(QListViewItem*) ) );
    connect( PushButton2, SIGNAL( clicked() ), this, SLOT( slotOmOlfix() ) );
    connect( PushButton3, SIGNAL( clicked() ), this, SLOT( slotLicensvillkor() ) );
    connect( PushButton4, SIGNAL( clicked() ), this, SLOT( slotHelp() ) );
    init();
}

/*  
 *  Destroys the object and frees any allocated resources
 */
frmOlfix::~frmOlfix()
{
    // no need to delete child widgets, Qt does it all for us
}

