/****************************************************************************
** Form interface generated from reading ui file 'frmaddbar.ui'
**
** Created: tor mar 20 07:49:44 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef FRMADDBAR_H
#define FRMADDBAR_H

#include <qvariant.h>
#include <qwidget.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QLabel;
class QLineEdit;
class QPushButton;

class frmAddBar : public QWidget
{ 
    Q_OBJECT

public:
    frmAddBar( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~frmAddBar();

    QLabel* TextLabel2;
    QLabel* TextLabel3;
    QLabel* TextLabel9_3;
    QLabel* TextLabel9_4;
    QLabel* TextLabel4;
    QLabel* TextLabel9;
    QPushButton* PushButtonQuit;
    QLineEdit* LineEditBar;
    QLineEdit* LineEditBenamn;
    QLineEdit* LineEditSenVerDat;
    QLabel* TextLabel9_5;
    QLabel* TextLabel9_5_2;
    QLineEdit* LineEditStartdatum;
    QLineEdit* LineEditKontoplan;
    QLabel* TextLabel5;
    QLineEdit* LineEditNestaVerNr;
    QLineEdit* LineEditBeskattAr;
    QLineEdit* LineEditSlutdatum;
    QLabel* TextLabel01;
    QLabel* TextLabel02;
    QLabel* TextLabel03;
    QLabel* TextLabel1;
    QPushButton* PushButtonOK;


public slots:
    virtual void slotAddBar();
    virtual void LineEditBar_returnPressed();
    virtual void LineEditBenamn_returnPressed();
    virtual void LineEditStartdatum_returnPressed();
    virtual void LineEditSlutdatum_returnPressed();
    virtual void LineEditBeskattAr_returnPressed();
    virtual void LineEditNestaVerNr_returnPressed();
    virtual void LineEditKontoplan_returnPressed();
    virtual void PushButtonOK_clicked();
    virtual void slotDataOnStderr();
    virtual void slotDataOnStdout();
    virtual void slotEndOfProcess();

};

#endif // FRMADDBAR_H
