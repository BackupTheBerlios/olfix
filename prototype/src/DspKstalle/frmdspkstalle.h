/****************************************************************************
** Form interface generated from reading ui file 'frmdspkstalle.ui'
**
** Created: tor mar 20 08:17:00 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef FRMDSPKSTALLE_H
#define FRMDSPKSTALLE_H

#include <qvariant.h>
#include <qwidget.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QLabel;
class QLineEdit;
class QPushButton;

class frmDspKstalle : public QWidget
{ 
    Q_OBJECT

public:
    frmDspKstalle( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~frmDspKstalle();

    QPushButton* PushButtonQuit;
    QLabel* TextLabel1;
    QLabel* TextLabel2;
    QLabel* TextLabel3;
    QLineEdit* LineEditBar;
    QLineEdit* LineEditBenamn;
    QLineEdit* LineEditKstalle;
    QPushButton* PushButtonGet;


public slots:
    virtual void init();
    virtual void LineEditBar_returnPressed();
    virtual void LineEditKstalle_returnPressed();
    virtual void slotGetKstalle();
    virtual void slotDataOnStdout();
    virtual void slotDataOnStderr();
    virtual void slotEndOfProcess();

};

#endif // FRMDSPKSTALLE_H
