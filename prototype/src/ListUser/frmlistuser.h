/****************************************************************************
** Form interface generated from reading ui file 'frmlistuser.ui'
**
** Created: tis mar 25 05:33:18 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef FRMLISTUSER_H
#define FRMLISTUSER_H

#include <qvariant.h>
#include <qwidget.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QListView;
class QListViewItem;
class QPushButton;

class frmListUser : public QWidget
{ 
    Q_OBJECT

public:
    frmListUser( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~frmListUser();

    QListView* ListView1;
    QPushButton* PushButtonAgain;
    QPushButton* PushButtonSluta;


public slots:
    virtual void GetUser();
    virtual void init();
    virtual void slotDataOnStdout();
    virtual void slotEndOfProcess();
    virtual void slotDataOnStderr();
    virtual void slotReloadUser();

};

#endif // FRMLISTUSER_H
