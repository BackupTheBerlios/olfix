/****************************************************************************
** Form implementation generated from reading ui file 'frmolfix.ui'
**
** Created: tis maj 27 07:00:12 2003
**      by: The User Interface Compiler ($Id: frmolfix.cpp,v 1.2 2003/09/28 08:30:05 janpihlgren Exp $)
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
 *  Constructs a frmOlfix as a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
frmOlfix::frmOlfix( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "frmOlfix" );
    setPaletteBackgroundColor( QColor( 0, 255, 255 ) );
    QFont f( font() );
    f.setFamily( "Helvetica" );
    f.setPointSize( 10 );
    setFont( f ); 
    frmOlfixLayout = new QGridLayout( this, 1, 1, 11, 6, "frmOlfixLayout"); 

    PushButton4 = new QPushButton( this, "PushButton4" );

    frmOlfixLayout->addWidget( PushButton4, 0, 1 );

    PushButton2 = new QPushButton( this, "PushButton2" );

    frmOlfixLayout->addWidget( PushButton2, 0, 3 );

    PushButton3 = new QPushButton( this, "PushButton3" );

    frmOlfixLayout->addWidget( PushButton3, 0, 2 );

    ListView1 = new QListView( this, "ListView1" );
    ListView1->addColumn( tr( "Funktioner" ) );
    ListView1->addColumn( tr( "Program" ) );
    ListView1->setRootIsDecorated( TRUE );

    frmOlfixLayout->addMultiCellWidget( ListView1, 1, 2, 1, 3 );

    PushButtonQuit = new QPushButton( this, "PushButtonQuit" );
    PushButtonQuit->setDefault( TRUE );

    frmOlfixLayout->addWidget( PushButtonQuit, 2, 0 );
    QSpacerItem* spacer = new QSpacerItem( 0, 385, QSizePolicy::Minimum, QSizePolicy::Expanding );
    frmOlfixLayout->addMultiCell( spacer, 0, 1, 0, 0 );
    languageChange();
    resize( QSize(371, 421).expandedTo(minimumSizeHint()) );

    // signals and slots connections
    connect( PushButtonQuit, SIGNAL( clicked() ), this, SLOT( close() ) );
    connect( ListView1, SIGNAL( clicked(QListViewItem*) ), this, SLOT( ListView1_clicked(QListViewItem*) ) );
    connect( PushButton2, SIGNAL( clicked() ), this, SLOT( slotOmOlfix() ) );
    connect( PushButton3, SIGNAL( clicked() ), this, SLOT( slotLicensvillkor() ) );
    connect( PushButton4, SIGNAL( clicked() ), this, SLOT( slotHelp() ) );

    // tab order
    setTabOrder( PushButton4, PushButton3 );
    setTabOrder( PushButton3, PushButton2 );
    setTabOrder( PushButton2, PushButtonQuit );
    setTabOrder( PushButtonQuit, ListView1 );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
frmOlfix::~frmOlfix()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void frmOlfix::languageChange()
{
    setCaption( trUtf8( "OLFIX - Order/Lager/Fakturering för Linuxsystem" ) );
    setIconText( tr( "OLFIX" ) );
    PushButton4->setText( trUtf8( "Hjälp" ) );
    PushButton2->setText( tr( "Om OLFIX" ) );
    PushButton3->setText( tr( "Licensvillkor" ) );
    ListView1->header()->setLabel( 0, tr( "Funktioner" ) );
    ListView1->header()->setLabel( 1, tr( "Program" ) );
    PushButtonQuit->setText( tr( "Slut" ) );
}

