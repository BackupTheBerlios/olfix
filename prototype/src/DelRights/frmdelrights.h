/****************************************************************************
** Form interface generated from reading ui file 'frmdelrights.ui'
**
** Created: tor mar 20 08:09:44 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef FRMDELRIGHTS_H
#define FRMDELRIGHTS_H

#include <qvariant.h>
#include <qwidget.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QLabel;
class QLineEdit;
class QPushButton;

class frmDelRights : public QWidget
{ 
    Q_OBJECT

public:
    frmDelRights( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~frmDelRights();

    QLabel* TextLabel1;
    QLabel* TextLabel2;
    QPushButton* PushButtonQuit;
    QLabel* TextLabel6;
    QLineEdit* LineEditTransid;
    QLineEdit* LineEditUserid;
    QPushButton* PushButtonGet;
    QPushButton* PushButtonOK;


public slots:
    virtual void init();
    virtual void slotUseridEntered();
    virtual void slotTransidEntered();
    virtual void slotGetRights();
    virtual void slotGetDataOnStdout();
    virtual void slotGetDataOnStderr();
    virtual void slotEndOfGetProcess();
    virtual void slotDelRgt();
    virtual void slotDelDataOnStdout();
    virtual void slotDelDataOnStderr();
    virtual void slotEndOfDelProcess();

};

#endif // FRMDELRIGHTS_H
