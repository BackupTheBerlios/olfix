/****************************************************************************
** Form interface generated from reading ui file 'frmdelvaluta.ui'
**
** Created: tor mar 20 08:13:17 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef FRMDELVALUTA_H
#define FRMDELVALUTA_H

#include <qvariant.h>
#include <qwidget.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QLabel;
class QLineEdit;
class QPushButton;

class frmDelValuta : public QWidget
{ 
    Q_OBJECT

public:
    frmDelValuta( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~frmDelValuta();

    QLabel* TextLabel1;
    QLabel* TextLabel3;
    QLabel* TextLabel4;
    QLabel* TextLabel5;
    QLabel* TextLabel6;
    QPushButton* PushButtonQuit;
    QLabel* TextLabel2;
    QLineEdit* LineEditBeteck;
    QLineEdit* LineEditLand;
    QLineEdit* LineEditValuta;
    QLineEdit* LineEditSalj;
    QLineEdit* LineEditKop;
    QPushButton* PushButtonGet;
    QPushButton* PushButtonOK;


public slots:
    virtual void init();
    virtual void slotPushButtonGet_clicked();
    virtual void slotGetValuta();
    virtual void slotValutaEntered();
    virtual void slotGetDataOnStdout();
    virtual void slotGetDataOnStderr();
    virtual void slotEndOfGetProcess();
    virtual void slotPushButtonOK_clicked();
    virtual void slotDelValData( QString mynt );
    virtual void slotEndOfDelProcess();
    virtual void slotDelDataOnStderr();
    virtual void slotDelDataOnStdout();

};

#endif // FRMDELVALUTA_H
