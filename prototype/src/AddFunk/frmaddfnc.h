/****************************************************************************
** Form interface generated from reading ui file 'frmaddfnc.ui'
**
** Created: tis jun 3 06:57:23 2003
**      by: The User Interface Compiler ($Id: frmaddfnc.h,v 1.2 2003/09/28 05:49:13 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef FRMADDFNC_H
#define FRMADDFNC_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QLabel;
class QLineEdit;
class QPushButton;

class frmAddFnc : public QWidget
{
    Q_OBJECT

public:
    frmAddFnc( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~frmAddFnc();

    QLabel* TextLabel1;
    QLabel* TextLabel1_2;
    QLineEdit* LineEditLedtext;
    QPushButton* PushButtonOK;
    QLineEdit* LineEditFunc;
    QPushButton* PushButtonQuit;

public slots:
    virtual void slotFuncEntered();
    virtual void slotLedTextEntered();
    virtual void slotAddFnc();
    virtual void slotDataOnStdout();
    virtual void slotDataOnStderr();
    virtual void slotEndOfProcess();

protected:

protected slots:
    virtual void languageChange();

    virtual void init();

};

#endif // FRMADDFNC_H
