/****************************************************************************
** Form interface generated from reading ui file 'frmaddkonto.ui'
**
** Created: tor mar 20 07:51:26 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef FRMADDKONTO_H
#define FRMADDKONTO_H

#include <qvariant.h>
#include <qwidget.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QLabel;
class QLineEdit;
class QPushButton;

class frmAddKonto : public QWidget
{ 
    Q_OBJECT

public:
    frmAddKonto( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~frmAddKonto();

    QLabel* TextLabelUserID;
    QLabel* TextLabelNamn;
    QLabel* TextLabelGrupp;
    QLabel* TextLabel1;
    QLabel* TextLabel2;
    QLabel* TextLabelAvd;
    QLabel* TextLabel3;
    QLabel* TextLabel4;
    QLabel* TextLabel5;
    QLabel* TextLabel6;
    QLabel* TextLabel9;
    QLabel* TextLabel9_2;
    QLabel* TextLabel9_3;
    QLabel* TextLabel9_4;
    QLabel* TextLabel9_5;
    QLabel* TextLabel9_6;
    QLineEdit* LineEditIB;
    QLineEdit* LineEditUB;
    QLineEdit* LineEditBar;
    QLineEdit* LineEditKontoNr;
    QLineEdit* LineEditBenamn;
    QLineEdit* LineEditManuell;
    QLineEdit* LineEditMomskod;
    QLineEdit* LineEditSRU;
    QLineEdit* LineEditKst;
    QLineEdit* LineEditProjekt;
    QLineEdit* LineEditSubkonto;
    QLineEdit* LineEditKontoplan;
    QPushButton* PushButtonQuit;
    QLabel* TextLabel8;
    QLabel* TextLabel7;
    QPushButton* PushButtonOK;


public slots:
    virtual void slotAddKonto();
    virtual void LineEditBar_returnPressed();
    virtual void LineEditKontoNr_returnPressed();
    virtual void LineEditBenamn_returnPressed();
    virtual void LineEditManuell_returnPressed();
    virtual void LineEditMomskod_returnPressed();
    virtual void LineEditSRU_returnPressed();
    virtual void LineEditKst_returnPressed();
    virtual void LineEditProjekt_returnPressed();
    virtual void LineEditSubkonto_returnPressed();
    virtual void LineEditKontoplan_returnPressed();
    virtual void PushButtonOK_clicked();
    virtual void slotDataOnStderr();
    virtual void slotDataOnStdout();
    virtual void slotEndOfProcess();

};

#endif // FRMADDKONTO_H
