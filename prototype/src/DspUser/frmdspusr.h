/****************************************************************************
** Form interface generated from reading ui file 'frmdspusr.ui'
**
** Created: tor mar 20 08:14:47 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef FRMDSPUSR_H
#define FRMDSPUSR_H

#include <qvariant.h>
#include <qwidget.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QLabel;
class QLineEdit;
class QListBox;
class QListBoxItem;
class QPushButton;

class frmDspUsr : public QWidget
{ 
    Q_OBJECT

public:
    frmDspUsr( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~frmDspUsr();

    QLabel* TextLabel1;
    QLabel* TextLabel2;
    QLabel* TextLabel3;
    QLabel* TextLabel4;
    QLabel* TextLabel5;
    QLineEdit* LineEditUserid;
    QPushButton* PushButtonQuit;
    QLineEdit* LineEditNamn;
    QLineEdit* LineEditAvd;
    QLineEdit* LineEditGrupp;
    QListBox* ListBoxBehor;
    QPushButton* PushButtonOK;


public slots:
    virtual void slotPushButtonOK_clicked();
    virtual void slotGetUserData();
    virtual void slotGetRightData();
    virtual void slotUseridEntered();
    virtual void slotRightDataOnStdout();
    virtual void slotEndOfRightProcess();
    virtual void slotUsrDataOnStdout();
    virtual void slotEndOfUsrProcess();

};

#endif // FRMDSPUSR_H
