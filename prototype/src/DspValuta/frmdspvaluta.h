/****************************************************************************
** Form interface generated from reading ui file 'frmdspvaluta.ui'
**
** Created: tor mar 20 08:18:51 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef FRMDSPVALUTA_H
#define FRMDSPVALUTA_H

#include <qvariant.h>
#include <qwidget.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QLabel;
class QLineEdit;
class QPushButton;

class frmDspValuta : public QWidget
{ 
    Q_OBJECT

public:
    frmDspValuta( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~frmDspValuta();

    QLabel* TextLabel1;
    QLabel* TextLabel2;
    QLabel* TextLabel3;
    QLabel* TextLabel4;
    QLabel* TextLabel4_2;
    QPushButton* PushButtonQuit;
    QLineEdit* LineEditBeteck;
    QLineEdit* LineEditLand;
    QLineEdit* LineEditKop;
    QLineEdit* LineEditSalj;
    QLineEdit* LineEditValuta;
    QPushButton* PushButtonGet;


public slots:
    virtual void init();
    virtual void slotGetValuta();
    virtual void LineEditValuta_returnPressed();
    virtual void PushButtonGet_clicked();
    virtual void slotDataOnStdout();
    virtual void slotDataOnStderr();
    virtual void slotEndOfProcess();

};

#endif // FRMDSPVALUTA_H
