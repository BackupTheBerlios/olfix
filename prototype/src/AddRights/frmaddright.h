/****************************************************************************
** Form interface generated from reading ui file 'frmaddright.ui'
**
** Created: tis mar 25 16:09:37 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef FRMADDRIGHT_H
#define FRMADDRIGHT_H

#include <qvariant.h>
#include <qwidget.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QLabel;
class QLineEdit;
class QPushButton;

class frmAddRight : public QWidget
{ 
    Q_OBJECT

public:
    frmAddRight( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~frmAddRight();

    QLabel* TextLabel1;
    QPushButton* PushButtonQuit;
    QLabel* TextLabel1_2;
    QLineEdit* LineEditFunk;
    QPushButton* PushButtonOK;
    QLineEdit* LineEditUserid;


public slots:
    virtual void slotAddRight();
    virtual void slotUseridEntered();
    virtual void slotRightEntered();
    virtual void slotDataOnStdout();
    virtual void slotDataOnStderr();
    virtual void slotEndOfProcess();

protected slots:
    virtual void init();

};

#endif // FRMADDRIGHT_H
