/****************************************************************************
** Form implementation generated from reading ui file 'frmadduser.ui'
**
** Created: tor mar 20 07:56:47 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "frmadduser.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "frmadduser.ui.h"

/* 
 *  Constructs a frmAddUser which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
frmAddUser::frmAddUser( QWidget* parent,  const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "frmAddUser" );
    resize( 337, 190 ); 
    setCaption( trUtf8( "ADDUSRW  Lägga upp ny användare" ) );

    TextLabelNamn = new QLabel( this, "TextLabelNamn" );
    TextLabelNamn->setGeometry( QRect( 10, 60, 70, 21 ) ); 
    TextLabelNamn->setText( trUtf8( "Namn:" ) );

    TextLabelUserID = new QLabel( this, "TextLabelUserID" );
    TextLabelUserID->setGeometry( QRect( 10, 30, 81, 21 ) ); 
    TextLabelUserID->setFrameShape( QLabel::NoFrame );
    TextLabelUserID->setFrameShadow( QLabel::Plain );
    TextLabelUserID->setText( trUtf8( "Användar-ID:" ) );

    TextLabelAvd = new QLabel( this, "TextLabelAvd" );
    TextLabelAvd->setGeometry( QRect( 10, 90, 70, 21 ) ); 
    TextLabelAvd->setText( trUtf8( "Avd:" ) );

    TextLabelGrupp = new QLabel( this, "TextLabelGrupp" );
    TextLabelGrupp->setGeometry( QRect( 10, 120, 70, 21 ) ); 
    TextLabelGrupp->setText( trUtf8( "Grupp:" ) );

    PushButtonQuit = new QPushButton( this, "PushButtonQuit" );
    PushButtonQuit->setGeometry( QRect( 70, 160, 61, 21 ) ); 
    PushButtonQuit->setText( trUtf8( "Avsluta" ) );

    LineEditUserId = new QLineEdit( this, "LineEditUserId" );
    LineEditUserId->setGeometry( QRect( 91, 30, 80, 22 ) ); 

    LineEditName = new QLineEdit( this, "LineEditName" );
    LineEditName->setGeometry( QRect( 90, 60, 240, 22 ) ); 

    LineEditAvd = new QLineEdit( this, "LineEditAvd" );
    LineEditAvd->setGeometry( QRect( 90, 90, 80, 22 ) ); 

    LineEditGrupp = new QLineEdit( this, "LineEditGrupp" );
    LineEditGrupp->setGeometry( QRect( 90, 120, 80, 22 ) ); 

    PushButtonOK = new QPushButton( this, "PushButtonOK" );
    PushButtonOK->setGeometry( QRect( 10, 160, 51, 21 ) ); 
    PushButtonOK->setText( trUtf8( "OK" ) );
    PushButtonOK->setDefault( TRUE );

    // signals and slots connections
    connect( PushButtonQuit, SIGNAL( clicked() ), this, SLOT( close() ) );
    connect( LineEditName, SIGNAL( returnPressed() ), PushButtonOK, SLOT( setFocus() ) );
    connect( PushButtonOK, SIGNAL( clicked() ), LineEditUserId, SLOT( setFocus() ) );
    connect( LineEditGrupp, SIGNAL( returnPressed() ), this, SLOT( slotGruppEntered() ) );
    connect( LineEditName, SIGNAL( returnPressed() ), LineEditAvd, SLOT( setFocus() ) );
    connect( LineEditUserId, SIGNAL( returnPressed() ), LineEditName, SLOT( setFocus() ) );
    connect( LineEditName, SIGNAL( returnPressed() ), this, SLOT( slotNameEntered() ) );
    connect( LineEditAvd, SIGNAL( returnPressed() ), LineEditGrupp, SLOT( setFocus() ) );
    connect( LineEditAvd, SIGNAL( returnPressed() ), this, SLOT( slotAvdEntered() ) );
    connect( LineEditGrupp, SIGNAL( returnPressed() ), PushButtonOK, SLOT( setFocus() ) );
    connect( LineEditUserId, SIGNAL( returnPressed() ), this, SLOT( slotUserIdEntered() ) );
    connect( PushButtonOK, SIGNAL( clicked() ), this, SLOT( slotAddUser() ) );

    // tab order
    setTabOrder( LineEditUserId, LineEditName );
    setTabOrder( LineEditName, LineEditAvd );
    setTabOrder( LineEditAvd, LineEditGrupp );
    setTabOrder( LineEditGrupp, PushButtonOK );
    setTabOrder( PushButtonOK, PushButtonQuit );
}

/*  
 *  Destroys the object and frees any allocated resources
 */
frmAddUser::~frmAddUser()
{
    // no need to delete child widgets, Qt does it all for us
}

