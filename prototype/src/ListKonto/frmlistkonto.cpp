/****************************************************************************
** Form implementation generated from reading ui file 'frmlistkonto.ui'
**
** Created: tor mar 20 08:23:00 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "frmlistkonto.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qlistbox.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "frmlistkonto.ui.h"

/* 
 *  Constructs a frmListKonto which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
frmListKonto::frmListKonto( QWidget* parent,  const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "frmListKonto" );
    resize( 500, 277 ); 
    setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, sizePolicy().hasHeightForWidth() ) );
    setMinimumSize( QSize( 500, 250 ) );
    setMaximumSize( QSize( 500, 280 ) );
    setBaseSize( QSize( 500, 270 ) );
    setCaption( trUtf8( "LSTKTOW  Lista konton" ) );

    PushButtonSluta = new QPushButton( this, "PushButtonSluta" );
    PushButtonSluta->setGeometry( QRect( 10, 240, 70, 30 ) ); 
    PushButtonSluta->setText( trUtf8( "Sluta" ) );

    TextLabel1 = new QLabel( this, "TextLabel1" );
    TextLabel1->setGeometry( QRect( 10, 10, 80, 20 ) ); 
    TextLabel1->setText( trUtf8( "Bokföringsår:" ) );

    ListBox1 = new QListBox( this, "ListBox1" );
    ListBox1->setGeometry( QRect( 90, 40, 400, 230 ) ); 

    LineEditBar = new QLineEdit( this, "LineEditBar" );
    LineEditBar->setGeometry( QRect( 90, 10, 40, 22 ) ); 

    PushButtonAgain = new QPushButton( this, "PushButtonAgain" );
    PushButtonAgain->setGeometry( QRect( 10, 206, 71, 30 ) ); 
    PushButtonAgain->setText( trUtf8( "Uppdatera" ) );

    PushButtonLista = new QPushButton( this, "PushButtonLista" );
    PushButtonLista->setGeometry( QRect( 10, 40, 71, 31 ) ); 
    PushButtonLista->setText( trUtf8( "Lista" ) );
    PushButtonLista->setDefault( TRUE );

    // signals and slots connections
    connect( PushButtonSluta, SIGNAL( clicked() ), this, SLOT( close() ) );
    connect( PushButtonLista, SIGNAL( clicked() ), this, SLOT( PushButtonLista_clicked() ) );
    connect( LineEditBar, SIGNAL( returnPressed() ), PushButtonLista, SLOT( setFocus() ) );
    connect( LineEditBar, SIGNAL( returnPressed() ), this, SLOT( slotLineEditBarEntered() ) );
    connect( PushButtonAgain, SIGNAL( clicked() ), this, SLOT( slotReloadKonto() ) );
    init();
}

/*  
 *  Destroys the object and frees any allocated resources
 */
frmListKonto::~frmListKonto()
{
    // no need to delete child widgets, Qt does it all for us
}

