/****************************************************************************
** Form implementation generated from reading ui file 'frmdspusr.ui'
**
** Created: tor mar 20 08:14:48 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "frmdspusr.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qlistbox.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "frmdspusr.ui.h"

/* 
 *  Constructs a frmDspUsr which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
frmDspUsr::frmDspUsr( QWidget* parent,  const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "frmDspUsr" );
    resize( 508, 265 ); 
    setCaption( trUtf8( "DSPUSRW Visa information för en användare" ) );

    TextLabel1 = new QLabel( this, "TextLabel1" );
    TextLabel1->setGeometry( QRect( 10, 10, 42, 21 ) ); 
    TextLabel1->setText( trUtf8( "UserId:" ) );

    TextLabel2 = new QLabel( this, "TextLabel2" );
    TextLabel2->setGeometry( QRect( 10, 40, 40, 21 ) ); 
    TextLabel2->setText( trUtf8( "Namn:" ) );

    TextLabel3 = new QLabel( this, "TextLabel3" );
    TextLabel3->setGeometry( QRect( 10, 70, 40, 21 ) ); 
    TextLabel3->setText( trUtf8( "Avd:" ) );

    TextLabel4 = new QLabel( this, "TextLabel4" );
    TextLabel4->setGeometry( QRect( 10, 100, 41, 21 ) ); 
    TextLabel4->setText( trUtf8( "Grupp:" ) );

    TextLabel5 = new QLabel( this, "TextLabel5" );
    TextLabel5->setGeometry( QRect( 380, 10, 80, 20 ) ); 
    TextLabel5->setText( trUtf8( "Behörigheter" ) );

    LineEditUserid = new QLineEdit( this, "LineEditUserid" );
    LineEditUserid->setGeometry( QRect( 60, 10, 61, 22 ) ); 

    PushButtonQuit = new QPushButton( this, "PushButtonQuit" );
    PushButtonQuit->setGeometry( QRect( 80, 230, 61, 21 ) ); 
    PushButtonQuit->setText( trUtf8( "Sluta" ) );

    LineEditNamn = new QLineEdit( this, "LineEditNamn" );
    LineEditNamn->setGeometry( QRect( 60, 40, 221, 22 ) ); 

    LineEditAvd = new QLineEdit( this, "LineEditAvd" );
    LineEditAvd->setGeometry( QRect( 60, 70, 220, 22 ) ); 

    LineEditGrupp = new QLineEdit( this, "LineEditGrupp" );
    LineEditGrupp->setGeometry( QRect( 60, 100, 121, 22 ) ); 

    ListBoxBehor = new QListBox( this, "ListBoxBehor" );
    ListBoxBehor->setGeometry( QRect( 341, 41, 150, 210 ) ); 

    PushButtonOK = new QPushButton( this, "PushButtonOK" );
    PushButtonOK->setGeometry( QRect( 10, 230, 61, 21 ) ); 
    PushButtonOK->setText( trUtf8( "OK" ) );
    PushButtonOK->setDefault( TRUE );

    // signals and slots connections
    connect( PushButtonQuit, SIGNAL( clicked() ), this, SLOT( close() ) );
    connect( LineEditUserid, SIGNAL( returnPressed() ), this, SLOT( slotUseridEntered() ) );
    connect( LineEditUserid, SIGNAL( returnPressed() ), PushButtonOK, SLOT( setFocus() ) );
    connect( PushButtonOK, SIGNAL( clicked() ), PushButtonQuit, SLOT( setFocus() ) );
    connect( PushButtonOK, SIGNAL( clicked() ), this, SLOT( slotPushButtonOK_clicked() ) );
    connect( PushButtonOK, SIGNAL( pressed() ), this, SLOT( slotPushButtonOK_clicked() ) );

    // tab order
    setTabOrder( LineEditUserid, PushButtonOK );
    setTabOrder( PushButtonOK, PushButtonQuit );
    setTabOrder( PushButtonQuit, LineEditNamn );
    setTabOrder( LineEditNamn, LineEditGrupp );
    setTabOrder( LineEditGrupp, LineEditAvd );
    setTabOrder( LineEditAvd, ListBoxBehor );
}

/*  
 *  Destroys the object and frees any allocated resources
 */
frmDspUsr::~frmDspUsr()
{
    // no need to delete child widgets, Qt does it all for us
}

