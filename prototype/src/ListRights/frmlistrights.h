/****************************************************************************
** Form interface generated from reading ui file 'frmlistrights.ui'
**
** Created: tor mar 20 15:14:06 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef FRMLISTRIGHTS_H
#define FRMLISTRIGHTS_H

#include <qvariant.h>
#include <qwidget.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QListView;
class QListViewItem;
class QPushButton;

class frmListRights : public QWidget
{ 
    Q_OBJECT

public:
    frmListRights( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~frmListRights();

    QListView* ListView1;
    QPushButton* PushButtonAgain;
    QPushButton* PushButtonSluta;


public slots:
    virtual void GetRights();
    virtual void slotDataOnStdout();
    virtual void slotEndOfProcess();
    virtual void slotReloadRights();

protected slots:
    virtual void init();

};

#endif // FRMLISTRIGHTS_H
