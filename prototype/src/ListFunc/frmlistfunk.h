/****************************************************************************
** Form interface generated from reading ui file 'frmlistfunk.ui'
**
** Created: ons mar 19 09:58:54 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef FRMLISTFUNK_H
#define FRMLISTFUNK_H

#include <qvariant.h>
#include <qwidget.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QListView;
class QListViewItem;
class QPushButton;

class frmListFunk : public QWidget
{ 
    Q_OBJECT

public:
    frmListFunk( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~frmListFunk();

    QPushButton* PushButtonSluta;
    QListView* ListView1;
    QPushButton* PushButtonAgain;


public slots:
    virtual void GetFunc();
    virtual void init();
    virtual void slotDataOnStdout();
    virtual void slotEndOfProcess();
    virtual void slotDataOnStderr();
    virtual void slotReloadFunc();

};

#endif // FRMLISTFUNK_H
