/****************************************************************************
** Form interface generated from reading ui file 'frmchgkonto.ui'
**
** Created: lör jun 7 05:46:39 2003
**      by: The User Interface Compiler ($Id: frmchgkonto.h,v 1.2 2003/09/28 06:41:43 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef FRMCHGKONTO_H
#define FRMCHGKONTO_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QLabel;
class QLineEdit;
class QPushButton;

class frmChgKonto : public QWidget
{
    Q_OBJECT

public:
    frmChgKonto( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~frmChgKonto();

    QLabel* TextLabelUserID;
    QLabel* TextLabelNamn;
    QLabel* TextLabelGrupp;
    QLabel* TextLabel1;
    QLabel* TextLabel2;
    QLabel* TextLabelAvd;
    QLabel* TextLabel3;
    QLabel* TextLabel5;
    QLabel* TextLabel6;
    QLabel* TextLabel9;
    QLabel* TextLabel9_2;
    QLabel* TextLabel9_3;
    QLabel* TextLabel9_4;
    QLabel* TextLabel9_5;
    QLabel* TextLabel9_6;
    QLineEdit* LineEditUB;
    QLabel* TextLabel7;
    QLineEdit* LineEditBar;
    QLineEdit* LineEditMomskod;
    QLineEdit* LineEditSRU;
    QLineEdit* LineEditKst;
    QLineEdit* LineEditProjekt;
    QLineEdit* LineEditSubkonto;
    QLineEdit* LineEditKontoplan;
    QLineEdit* LineEditIB;
    QLineEdit* LineEditManuell;
    QLineEdit* LineEditBenamn;
    QLineEdit* LineEditKontoNr;
    QPushButton* PushButtonOK;
    QPushButton* PushButtonQuit;
    QPushButton* PushButtonGet;
    QLabel* TextLabel4;
    QLabel* TextLabel8;

public slots:
    virtual void slotChgKonto();
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
    virtual void slotPutDataOnStderr();
    virtual void slotPutDataOnStdout();
    virtual void slotPutEndOfProcess();
    virtual void slotGetEndOfProcess();
    virtual void slotGetDataOnStdout();
    virtual void slotGetDataOnStderr();
    virtual void slotGetKonto();
    virtual void PushButtonGet_clicked();
    virtual void PushButtonGet_returnPressed();

protected:

protected slots:
    virtual void languageChange();
};

#endif // FRMCHGKONTO_H
