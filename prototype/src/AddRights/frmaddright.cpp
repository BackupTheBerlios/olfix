/****************************************************************************
** Form implementation generated from reading ui file 'frmaddright.ui'
**
** Created: tis maj 27 06:34:51 2003
**      by: The User Interface Compiler ($Id: frmaddright.cpp,v 1.2 2003/09/28 06:13:38 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "frmaddright.h"

#include <qvariant.h>
#include <qheader.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qlistview.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "frmaddright.ui.h"

/* 
 *  Constructs a frmAddRight as a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
frmAddRight::frmAddRight( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "frmAddRight" );
    QFont f( font() );
    f.setFamily( "Helvetica" );
    f.setPointSize( 10 );
    setFont( f ); 
    frmAddRightLayout = new QGridLayout( this, 1, 1, 11, 6, "frmAddRightLayout"); 

    ListViewBehor_2 = new QListView( this, "ListViewBehor_2" );
    ListViewBehor_2->addColumn( tr( "Funktion" ) );
    ListViewBehor_2->addColumn( tr( "Beskrivning" ) );
    ListViewBehor_2->setRootIsDecorated( FALSE );
    ListViewBehor_2->setResizeMode( QListView::NoColumn );

    frmAddRightLayout->addMultiCellWidget( ListViewBehor_2, 0, 2, 2, 2 );

    LineEditFunk = new QLineEdit( this, "LineEditFunk" );
    LineEditFunk->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, LineEditFunk->sizePolicy().hasHeightForWidth() ) );
    LineEditFunk->setAlignment( int( QLineEdit::AlignAuto ) );

    frmAddRightLayout->addWidget( LineEditFunk, 1, 1 );

    LineEditUserid = new QLineEdit( this, "LineEditUserid" );
    LineEditUserid->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, LineEditUserid->sizePolicy().hasHeightForWidth() ) );

    frmAddRightLayout->addWidget( LineEditUserid, 0, 1 );

    PushButtonQuit = new QPushButton( this, "PushButtonQuit" );
    PushButtonQuit->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, PushButtonQuit->sizePolicy().hasHeightForWidth() ) );
    PushButtonQuit->setDefault( TRUE );

    frmAddRightLayout->addWidget( PushButtonQuit, 2, 1 );

    PushButtonOK = new QPushButton( this, "PushButtonOK" );
    PushButtonOK->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, PushButtonOK->sizePolicy().hasHeightForWidth() ) );
    PushButtonOK->setDefault( TRUE );

    frmAddRightLayout->addWidget( PushButtonOK, 2, 0 );

    TextLabel1 = new QLabel( this, "TextLabel1" );
    TextLabel1->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, TextLabel1->sizePolicy().hasHeightForWidth() ) );
    TextLabel1->setFrameShape( QLabel::NoFrame );
    TextLabel1->setFrameShadow( QLabel::Plain );

    frmAddRightLayout->addWidget( TextLabel1, 0, 0 );

    TextLabel1_2 = new QLabel( this, "TextLabel1_2" );
    TextLabel1_2->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, TextLabel1_2->sizePolicy().hasHeightForWidth() ) );

    frmAddRightLayout->addWidget( TextLabel1_2, 1, 0 );
    languageChange();
    resize( QSize(432, 151).expandedTo(minimumSizeHint()) );

    // signals and slots connections
    connect( PushButtonOK, SIGNAL( clicked() ), this, SLOT( slotAddRight() ) );
    connect( LineEditUserid, SIGNAL( returnPressed() ), LineEditFunk, SLOT( setFocus() ) );
    connect( LineEditFunk, SIGNAL( returnPressed() ), PushButtonOK, SLOT( setFocus() ) );
    connect( LineEditFunk, SIGNAL( returnPressed() ), this, SLOT( slotRightEntered() ) );
    connect( PushButtonOK, SIGNAL( clicked() ), LineEditFunk, SLOT( clear() ) );
    connect( PushButtonOK, SIGNAL( clicked() ), LineEditUserid, SLOT( setFocus() ) );
    connect( PushButtonOK, SIGNAL( clicked() ), LineEditUserid, SLOT( clear() ) );
    connect( LineEditUserid, SIGNAL( returnPressed() ), this, SLOT( slotUseridEntered() ) );
    connect( ListViewBehor_2, SIGNAL( clicked(QListViewItem*) ), this, SLOT( slotPickupFunc(QListViewItem*) ) );
    connect( PushButtonQuit, SIGNAL( clicked() ), this, SLOT( close() ) );
    connect( LineEditUserid, SIGNAL( lostFocus() ), this, SLOT( slotUseridEntered() ) );
    connect( LineEditFunk, SIGNAL( lostFocus() ), this, SLOT( slotRightEntered() ) );

    // tab order
    setTabOrder( LineEditUserid, LineEditFunk );
    setTabOrder( LineEditFunk, PushButtonOK );
    setTabOrder( PushButtonOK, PushButtonQuit );
    setTabOrder( PushButtonQuit, ListViewBehor_2 );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
frmAddRight::~frmAddRight()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void frmAddRight::languageChange()
{
    setCaption( trUtf8( "ADDRGTW  Lägga upp ny behörighet" ) );
    ListViewBehor_2->header()->setLabel( 0, tr( "Funktion" ) );
    ListViewBehor_2->header()->setLabel( 1, tr( "Beskrivning" ) );
    PushButtonQuit->setText( tr( "Avsluta" ) );
    PushButtonOK->setText( tr( "OK" ) );
    TextLabel1->setText( trUtf8( "Användar-ID:" ) );
    TextLabel1_2->setText( trUtf8( "Behörighet:" ) );
}

