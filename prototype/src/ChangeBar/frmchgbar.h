/****************************************************************************
** Form interface generated from reading ui file 'frmchgbar.ui'
**
** Created: ons apr 2 14:17:25 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef FRMCHGBAR_H
#define FRMCHGBAR_H

#include <qvariant.h>
#include <qwidget.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QLabel;
class QLineEdit;
class QPushButton;

class frmChgBar : public QWidget
{ 
    Q_OBJECT

public:
    frmChgBar( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~frmChgBar();

    QLabel* TextLabel2;
    QLabel* TextLabel3;
    QLabel* TextLabel9_3;
    QLabel* TextLabel9_4;
    QLabel* TextLabel4;
    QLabel* TextLabel9;
    QLabel* TextLabel9_5;
    QLabel* TextLabel9_5_2;
    QLabel* TextLabel5;
    QLabel* TextLabel01;
    QLabel* TextLabel02;
    QLabel* TextLabel03;
    QLabel* TextLabel1;
    QPushButton* PushButtonOK;
    QPushButton* PushButtonQuit;
    QLineEdit* LineEditBar;
    QLineEdit* LineEditBenamn;
    QLineEdit* LineEditStartdatum;
    QLineEdit* LineEditSlutdatum;
    QLineEdit* LineEditSenVerDat;
    QLineEdit* LineEditNestaVerNr;
    QLineEdit* LineEditKontoplan;
    QLineEdit* LineEditBeskattAr;


public slots:
    virtual void init();
    virtual void LineEditBar_returnPressed();
    virtual void slotChgBar();
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
    virtual void slotGetBar();
    virtual void slotGetDataOnStderr();
    virtual void slotGetDataOnStdout();
    virtual void slotGetEndOfProcess();

};

#endif // FRMCHGBAR_H
