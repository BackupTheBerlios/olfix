/****************************************************************************
** Form implementation generated from reading ui file 'levresk.ui'
**
** Created: mån jun 30 07:23:36 2003
**      by: The User Interface Compiler ($Id: levresk.cpp,v 1.1 2003/09/28 08:20:33 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "levresk.h"

#include <qvariant.h>
#include <qgroupbox.h>
#include <qheader.h>
#include <qlabel.h>
#include <qlistview.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "levresk.ui.h"

/* 
 *  Constructs a frmLevResk as a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
frmLevResk::frmLevResk( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "frmLevResk" );
    frmLevReskLayout = new QGridLayout( this, 1, 1, 11, 6, "frmLevReskLayout"); 

    TextLabel2 = new QLabel( this, "TextLabel2" );

    frmLevReskLayout->addWidget( TextLabel2, 1, 0 );

    GroupBox1 = new QGroupBox( this, "GroupBox1" );
    GroupBox1->setColumnLayout(0, Qt::Vertical );
    GroupBox1->layout()->setSpacing( 6 );
    GroupBox1->layout()->setMargin( 11 );
    GroupBox1Layout = new QGridLayout( GroupBox1->layout() );
    GroupBox1Layout->setAlignment( Qt::AlignTop );

    ListView1 = new QListView( GroupBox1, "ListView1" );
    ListView1->addColumn( trUtf8( "Förfallodag" ) );
    ListView1->addColumn( tr( "Levnr" ) );
    ListView1->addColumn( trUtf8( "Leverantörsnamn" ) );
    ListView1->addColumn( tr( "Fakturanr" ) );
    ListView1->addColumn( tr( "Belopp" ) );
    ListView1->addColumn( tr( "Summa" ) );
    ListView1->setFrameShape( QListView::StyledPanel );
    ListView1->setFrameShadow( QListView::Sunken );
    ListView1->setShowSortIndicator( FALSE );

    GroupBox1Layout->addWidget( ListView1, 0, 0 );

    frmLevReskLayout->addMultiCellWidget( GroupBox1, 3, 3, 0, 4 );

    TextLabel1 = new QLabel( this, "TextLabel1" );
    QFont TextLabel1_font(  TextLabel1->font() );
    TextLabel1_font.setFamily( "Times [Adobe]" );
    TextLabel1_font.setPointSize( 16 );
    TextLabel1_font.setBold( TRUE );
    TextLabel1->setFont( TextLabel1_font ); 

    frmLevReskLayout->addMultiCellWidget( TextLabel1, 0, 0, 0, 2 );

    TextLabelDatum = new QLabel( this, "TextLabelDatum" );

    frmLevReskLayout->addMultiCellWidget( TextLabelDatum, 1, 1, 1, 3 );
    QSpacerItem* spacer = new QSpacerItem( 315, 0, QSizePolicy::Expanding, QSizePolicy::Minimum );
    frmLevReskLayout->addMultiCell( spacer, 0, 0, 3, 4 );
    QSpacerItem* spacer_2 = new QSpacerItem( 300, 0, QSizePolicy::Expanding, QSizePolicy::Minimum );
    frmLevReskLayout->addItem( spacer_2, 1, 4 );
    QSpacerItem* spacer_3 = new QSpacerItem( 300, 0, QSizePolicy::Expanding, QSizePolicy::Minimum );
    frmLevReskLayout->addItem( spacer_3, 2, 4 );
    languageChange();
    resize( QSize(433, 461).expandedTo(minimumSizeHint()) );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
frmLevResk::~frmLevResk()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void frmLevResk::languageChange()
{
    setCaption( trUtf8( "LEVRESKW  Leverantörsreskontrarapport" ) );
    TextLabel2->setText( tr( "Datum:" ) );
    GroupBox1->setTitle( QString::null );
    ListView1->header()->setLabel( 0, trUtf8( "Förfallodag" ) );
    ListView1->header()->setLabel( 1, tr( "Levnr" ) );
    ListView1->header()->setLabel( 2, trUtf8( "Leverantörsnamn" ) );
    ListView1->header()->setLabel( 3, tr( "Fakturanr" ) );
    ListView1->header()->setLabel( 4, tr( "Belopp" ) );
    ListView1->header()->setLabel( 5, tr( "Summa" ) );
    TextLabel1->setText( trUtf8( "Obetalda leverantörsfakturor" ) );
    TextLabelDatum->setText( tr( "1998-01-01" ) );
}

