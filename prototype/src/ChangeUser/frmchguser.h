/****************************************************************************
** Form interface generated from reading ui file 'frmchguser.ui'
**
** Created: sön mar 23 14:33:29 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef FRMCHGUSER_H
#define FRMCHGUSER_H

#include <qvariant.h>
#include <qwidget.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QLabel;
class QLineEdit;
class QPushButton;

class frmChgUser : public QWidget
{ 
    Q_OBJECT

public:
    frmChgUser( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~frmChgUser();

    QLabel* TextLabelAvd;
    QLabel* TextLabelGrupp;
    QLabel* TextLabelNamn;
    QLabel* TextLabelUserID;
    QLineEdit* LineEditNamn;
    QLineEdit* LineEditAvd;
    QLineEdit* LineEditGrupp;
    QPushButton* PushButtonGet;
    QPushButton* PushButtonUpdate;
    QLineEdit* LineEditUserid;
    QPushButton* PushButtonQuit;


public slots:
    virtual void slotGetUser();
    virtual void slotChgUser();
    virtual void slotUseridEntered();
    virtual void slotNameEntered();
    virtual void slotAvdEntered();
    virtual void slotGruppEntered();
    virtual void slotPushButtonGet_clicked();
    virtual void slotPushButtonUpdate_clicked();
    virtual void slotUsrDataOnStdout();
    virtual void slotEndOfUsrProcess();
    virtual void slotChgDataOnStdout();
    virtual void slotChgDataOnStderr();
    virtual void slotEndOfChgProcess();

};

#endif // FRMCHGUSER_H
