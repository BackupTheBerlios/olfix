/****************************************************************************
** Form implementation generated from reading ui file 'ktorapport.ui'
**
** Created: fre maj 16 08:47:24 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "ktorapport.h"

#include <qvariant.h>
#include <qgroupbox.h>
#include <qheader.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qlistview.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "ktorapport.ui.h"

/* 
 *  Constructs a frmKtoRapport which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
frmKtoRapport::frmKtoRapport( QWidget* parent,  const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "frmKtoRapport" );
    resize( 433, 461 ); 
    setCaption( trUtf8( "RPTKTOW  Kontorapport" ) );
    frmKtoRapportLayout = new QGridLayout( this, 1, 1, 11, 6, "frmKtoRapportLayout"); 

    TextLabel2 = new QLabel( this, "TextLabel2" );
    TextLabel2->setText( trUtf8( "Datum:" ) );

    frmKtoRapportLayout->addWidget( TextLabel2, 1, 0 );

    GroupBox1 = new QGroupBox( this, "GroupBox1" );
    GroupBox1->setTitle( trUtf8( "" ) );
    GroupBox1->setColumnLayout(0, Qt::Vertical );
    GroupBox1->layout()->setSpacing( 6 );
    GroupBox1->layout()->setMargin( 11 );
    GroupBox1Layout = new QGridLayout( GroupBox1->layout() );
    GroupBox1Layout->setAlignment( Qt::AlignTop );

    ListView1 = new QListView( GroupBox1, "ListView1" );
    ListView1->addColumn( trUtf8( "Kontonr" ) );
    ListView1->addColumn( trUtf8( "Kontonamn" ) );
    ListView1->addColumn( trUtf8( "Debet" ) );
    ListView1->addColumn( trUtf8( "Kredit" ) );
    ListView1->addColumn( trUtf8( "Summa" ) );
    ListView1->setFrameShape( QListView::StyledPanel );
    ListView1->setFrameShadow( QListView::Sunken );
    ListView1->setShowSortIndicator( FALSE );

    GroupBox1Layout->addWidget( ListView1, 0, 0 );

    frmKtoRapportLayout->addMultiCellWidget( GroupBox1, 3, 3, 0, 4 );

    TextLabel1_2 = new QLabel( this, "TextLabel1_2" );
    TextLabel1_2->setText( trUtf8( "Bokföringsår:" ) );

    frmKtoRapportLayout->addMultiCellWidget( TextLabel1_2, 2, 2, 0, 1 );

    TextLabel1 = new QLabel( this, "TextLabel1" );
    QFont TextLabel1_font(  TextLabel1->font() );
    TextLabel1_font.setFamily( "Times [Adobe]" );
    TextLabel1_font.setPointSize( 16 );
    TextLabel1_font.setBold( TRUE );
    TextLabel1->setFont( TextLabel1_font ); 
    TextLabel1->setText( trUtf8( "Kontorapport" ) );

    frmKtoRapportLayout->addMultiCellWidget( TextLabel1, 0, 0, 0, 2 );

    LineEditBar = new QLineEdit( this, "LineEditBar" );

    frmKtoRapportLayout->addMultiCellWidget( LineEditBar, 2, 2, 2, 3 );

    TextLabelDatum = new QLabel( this, "TextLabelDatum" );
    TextLabelDatum->setText( trUtf8( "1998-01-01" ) );

    frmKtoRapportLayout->addMultiCellWidget( TextLabelDatum, 1, 1, 1, 3 );
    QSpacerItem* spacer = new QSpacerItem( 315, 0, QSizePolicy::Expanding, QSizePolicy::Minimum );
    frmKtoRapportLayout->addMultiCell( spacer, 0, 0, 3, 4 );
    QSpacerItem* spacer_2 = new QSpacerItem( 300, 0, QSizePolicy::Expanding, QSizePolicy::Minimum );
    frmKtoRapportLayout->addItem( spacer_2, 1, 4 );
    QSpacerItem* spacer_3 = new QSpacerItem( 300, 0, QSizePolicy::Expanding, QSizePolicy::Minimum );
    frmKtoRapportLayout->addItem( spacer_3, 2, 4 );

    // signals and slots connections
    connect( LineEditBar, SIGNAL( returnPressed() ), this, SLOT( slotLineEditBar_returnPressed() ) );
    init();
}

/*  
 *  Destroys the object and frees any allocated resources
 */
frmKtoRapport::~frmKtoRapport()
{
    // no need to delete child widgets, Qt does it all for us
}

