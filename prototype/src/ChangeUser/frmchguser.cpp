/****************************************************************************
** Form implementation generated from reading ui file 'frmchguser.ui'
**
** Created: sön mar 23 14:33:29 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "frmchguser.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "frmchguser.ui.h"

/* 
 *  Constructs a frmChgUser which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
frmChgUser::frmChgUser( QWidget* parent,  const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "frmChgUser" );
    resize( 319, 190 ); 
    setCaption( trUtf8( "CHGUSRW  Ändra användare" ) );

    TextLabelAvd = new QLabel( this, "TextLabelAvd" );
    TextLabelAvd->setGeometry( QRect( 10, 90, 70, 21 ) ); 
    TextLabelAvd->setText( trUtf8( "Avd:" ) );

    TextLabelGrupp = new QLabel( this, "TextLabelGrupp" );
    TextLabelGrupp->setGeometry( QRect( 10, 120, 70, 21 ) ); 
    TextLabelGrupp->setText( trUtf8( "Grupp:" ) );

    TextLabelNamn = new QLabel( this, "TextLabelNamn" );
    TextLabelNamn->setGeometry( QRect( 10, 60, 70, 21 ) ); 
    TextLabelNamn->setText( trUtf8( "Namn:" ) );

    TextLabelUserID = new QLabel( this, "TextLabelUserID" );
    TextLabelUserID->setGeometry( QRect( 10, 30, 81, 21 ) ); 
    TextLabelUserID->setText( trUtf8( "Användar-ID:" ) );

    LineEditNamn = new QLineEdit( this, "LineEditNamn" );
    LineEditNamn->setGeometry( QRect( 90, 60, 210, 22 ) ); 

    LineEditAvd = new QLineEdit( this, "LineEditAvd" );
    LineEditAvd->setGeometry( QRect( 90, 90, 80, 22 ) ); 

    LineEditGrupp = new QLineEdit( this, "LineEditGrupp" );
    LineEditGrupp->setGeometry( QRect( 90, 120, 80, 22 ) ); 

    PushButtonGet = new QPushButton( this, "PushButtonGet" );
    PushButtonGet->setGeometry( QRect( 10, 160, 51, 21 ) ); 
    PushButtonGet->setText( trUtf8( "Hämta" ) );
    PushButtonGet->setDefault( TRUE );

    PushButtonUpdate = new QPushButton( this, "PushButtonUpdate" );
    PushButtonUpdate->setGeometry( QRect( 70, 160, 70, 21 ) ); 
    PushButtonUpdate->setText( trUtf8( "Uppdatera" ) );
    PushButtonUpdate->setDefault( TRUE );

    LineEditUserid = new QLineEdit( this, "LineEditUserid" );
    LineEditUserid->setGeometry( QRect( 91, 30, 80, 22 ) ); 

    PushButtonQuit = new QPushButton( this, "PushButtonQuit" );
    PushButtonQuit->setGeometry( QRect( 150, 160, 61, 21 ) ); 
    PushButtonQuit->setText( trUtf8( "Avsluta" ) );
    PushButtonQuit->setDefault( TRUE );

    // signals and slots connections
    connect( PushButtonQuit, SIGNAL( clicked() ), this, SLOT( close() ) );
    connect( LineEditNamn, SIGNAL( returnPressed() ), PushButtonGet, SLOT( setFocus() ) );
    connect( PushButtonGet, SIGNAL( clicked() ), LineEditNamn, SLOT( clear() ) );
    connect( PushButtonGet, SIGNAL( clicked() ), LineEditUserid, SLOT( setFocus() ) );
    connect( PushButtonGet, SIGNAL( clicked() ), LineEditUserid, SLOT( clear() ) );
    connect( LineEditGrupp, SIGNAL( returnPressed() ), this, SLOT( slotGruppEntered() ) );
    connect( LineEditNamn, SIGNAL( returnPressed() ), LineEditAvd, SLOT( setFocus() ) );
    connect( LineEditUserid, SIGNAL( returnPressed() ), LineEditNamn, SLOT( setFocus() ) );
    connect( LineEditNamn, SIGNAL( returnPressed() ), this, SLOT( slotNameEntered() ) );
    connect( LineEditAvd, SIGNAL( returnPressed() ), LineEditGrupp, SLOT( setFocus() ) );
    connect( LineEditAvd, SIGNAL( returnPressed() ), this, SLOT( slotAvdEntered() ) );
    connect( LineEditUserid, SIGNAL( returnPressed() ), this, SLOT( slotUseridEntered() ) );
    connect( PushButtonGet, SIGNAL( clicked() ), this, SLOT( slotPushButtonGet_clicked() ) );
    connect( PushButtonUpdate, SIGNAL( clicked() ), this, SLOT( slotPushButtonUpdate_clicked() ) );
    connect( LineEditGrupp, SIGNAL( returnPressed() ), PushButtonUpdate, SLOT( setFocus() ) );

    // tab order
    setTabOrder( LineEditUserid, PushButtonGet );
    setTabOrder( PushButtonGet, LineEditNamn );
    setTabOrder( LineEditNamn, LineEditAvd );
    setTabOrder( LineEditAvd, LineEditGrupp );
    setTabOrder( LineEditGrupp, PushButtonUpdate );
    setTabOrder( PushButtonUpdate, PushButtonQuit );
}

/*  
 *  Destroys the object and frees any allocated resources
 */
frmChgUser::~frmChgUser()
{
    // no need to delete child widgets, Qt does it all for us
}

