/****************************************************************************
** Form interface generated from reading ui file 'frmadduser.ui'
**
** Created: tis maj 27 06:38:09 2003
**      by: The User Interface Compiler ($Id: frmadduser.h,v 1.2 2003/09/28 06:24:08 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef FRMADDUSER_H
#define FRMADDUSER_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QLabel;
class QLineEdit;
class QPushButton;

class frmAddUser : public QWidget
{
    Q_OBJECT

public:
    frmAddUser( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~frmAddUser();

    QLabel* TextLabelNamn;
    QLabel* TextLabelUserID;
    QLabel* TextLabelAvd;
    QLabel* TextLabelGrupp;
    QPushButton* PushButtonQuit;
    QLineEdit* LineEditName;
    QLineEdit* LineEditAvd;
    QLineEdit* LineEditGrupp;
    QPushButton* PushButtonOK;
    QLineEdit* LineEditUserId;

public slots:
    virtual void slotAddUser();
    virtual void slotUserIdEntered();
    virtual void slotNameEntered();
    virtual void slotAvdEntered();
    virtual void slotGruppEntered();
    virtual void slotDataOnStdout();
    virtual void slotDataOnStderr();
    virtual void slotEndOfProcess();

protected:

protected slots:
    virtual void languageChange();
};

#endif // FRMADDUSER_H
