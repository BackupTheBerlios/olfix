/****************************************************************************
** Form interface generated from reading ui file 'frmdelusr.ui'
**
** Created: tor mar 20 08:11:29 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef FRMDELUSR_H
#define FRMDELUSR_H

#include <qvariant.h>
#include <qwidget.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QLabel;
class QLineEdit;
class QListView;
class QListViewItem;
class QPushButton;

class frmDelUsr : public QWidget
{ 
    Q_OBJECT

public:
    frmDelUsr( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~frmDelUsr();

    QLabel* TextLabel1;
    QLabel* TextLabel2;
    QLabel* TextLabel3;
    QLabel* TextLabel4;
    QLabel* TextLabel5;
    QLineEdit* LineEditNamn;
    QLineEdit* LineEditAvd;
    QLineEdit* LineEditGrupp;
    QLabel* TextLabel1_2;
    QPushButton* PushButtonQuit;
    QLineEdit* LineEditUserid;
    QListView* ListViewBehor;
    QPushButton* PushButtonGet;
    QPushButton* PushButtonOK;


public slots:
    virtual void slotPushButtonGet_clicked();
    virtual void slotGetUserData();
    virtual void slotGetRightData();
    virtual void slotUseridEntered();
    virtual void slotRightDataOnStdout();
    virtual void slotEndOfRightProcess();
    virtual void slotUsrDataOnStdout();
    virtual void slotEndOfUsrProcess();
    virtual void slotPushButtonOK_clicked();
    virtual void slotDelRightData( QString anvID, QString fncID );
    virtual void slotEndOfRgtDelProcess();
    virtual void slotRgtDelDataOnStderr();
    virtual void slotRgtDelDataOnStdout();
    virtual void slotDelUsrData( QString anvID );
    virtual void slotUsrDelDataOnStdout();
    virtual void slotUsrDelDataOnStderr();
    virtual void slotEndOfUsrDelProcess();

};

#endif // FRMDELUSR_H
