/****************************************************************************
** Form interface generated from reading ui file 'frmolfix.ui'
**
** Created: tis mar 25 05:38:13 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef FRMOLFIX_H
#define FRMOLFIX_H

#include <qvariant.h>
#include <qwidget.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QListView;
class QListViewItem;
class QPushButton;

class frmOlfix : public QWidget
{ 
    Q_OBJECT

public:
    frmOlfix( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~frmOlfix();

    QPushButton* PushButton4;
    QPushButton* PushButton2;
    QPushButton* PushButton3;
    QListView* ListView1;
    QPushButton* PushButtonQuit;


public slots:
    virtual void init();
    virtual void slotGetProgram();
    virtual void slotDataOnStdout();
    virtual void slotDataOnStderr();
    virtual void slotEndOfProcess();
    virtual void ListView1_clicked( QListViewItem * item );
    virtual void slotRunProgram( QString prg );
    virtual void slotDataOnPrgStderr();
    virtual void slotEndOfPrgProcess();
    virtual void CheckBehor( QString prog );
    virtual void slotEndOfCheckProcess();
    virtual void slotDataOnCheckStdout();
    virtual void slotDataOnCheckStderr();
    virtual void slotOmOlfix();
    virtual void slotLicensvillkor();
    virtual void slotHelp();

protected:
    QGridLayout* frmOlfixLayout;
};

#endif // FRMOLFIX_H
