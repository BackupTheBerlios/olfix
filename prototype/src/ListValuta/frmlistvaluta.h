/****************************************************************************
** Form interface generated from reading ui file 'frmlistvaluta.ui'
**
** Created: tor mar 20 08:26:28 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef FRMLISTVALUTA_H
#define FRMLISTVALUTA_H

#include <qvariant.h>
#include <qwidget.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QListView;
class QListViewItem;
class QPushButton;

class frmListValuta : public QWidget
{ 
    Q_OBJECT

public:
    frmListValuta( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~frmListValuta();

    QPushButton* PushButtonSluta;
    QListView* ListView1;
    QPushButton* PushButtonAgain;


public slots:
    virtual void GetValuta();
    virtual void init();
    virtual void slotDataOnStdout();
    virtual void slotDataOnStderr();
    virtual void slotEndOfProcess();
    virtual void slotReloadValuta();

};

#endif // FRMLISTVALUTA_H
