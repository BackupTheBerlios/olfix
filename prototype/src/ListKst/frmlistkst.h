/****************************************************************************
** Form interface generated from reading ui file 'frmlistkst.ui'
**
** Created: ons mar 19 09:55:51 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef FRMLISTKST_H
#define FRMLISTKST_H

#include <qvariant.h>
#include <qwidget.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QListView;
class QListViewItem;
class QPushButton;

class frmListKst : public QWidget
{ 
    Q_OBJECT

public:
    frmListKst( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~frmListKst();

    QPushButton* PushButtonSluta;
    QListView* ListView1;
    QPushButton* PushButtonAgain;


public slots:
    virtual void init();
    virtual void GetKstalle();
    virtual void slotDataOnStdout();
    virtual void slotDataOnStderr();
    virtual void slotEndOfProcess();
    virtual void slotReloadKstalle();

};

#endif // FRMLISTKST_H
