/****************************************************************************
** Form interface generated from reading ui file 'frmaddright.ui'
**
** Created: tis maj 27 06:34:51 2003
**      by: The User Interface Compiler ($Id: frmaddright.h,v 1.2 2003/09/28 06:13:38 janpihlgren Exp $)
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
class QListView;
class QListViewItem;
class QPushButton;

class frmAddRight : public QWidget
{
    Q_OBJECT

public:
    frmAddRight( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~frmAddRight();

    QListView* ListViewBehor_2;
    QLineEdit* LineEditFunk;
    QLineEdit* LineEditUserid;
    QPushButton* PushButtonQuit;
    QPushButton* PushButtonOK;
    QLabel* TextLabel1;
    QLabel* TextLabel1_2;

public slots:
    virtual void slotAddRight();
    virtual void slotUseridEntered();
    virtual void slotRightEntered();
    virtual void slotDataOnStdout();
    virtual void slotDataOnStderr();
    virtual void slotEndOfProcess();
    virtual void slotGetFunc();
    virtual void slotEndOfGetFuncfProcess();
    virtual void slotPickupFunc( QListViewItem * item );

protected:
    QGridLayout* frmAddRightLayout;

protected slots:
    virtual void languageChange();

    virtual void init();

};

#endif // FRMADDRIGHT_H
