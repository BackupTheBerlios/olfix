/****************************************************************************
** Form interface generated from reading ui file 'frmaddkonto.ui'
**
** Created: ons aug 6 06:11:12 2003
**      by: The User Interface Compiler ($Id: frmaddkonto.h,v 1.2 2003/09/28 05:50:08 janpihlgren Exp $)
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

    QPushButton* PushButtonOK;
    QPushButton* PushButtonQuit;
    QLineEdit* LineEditUB;
    QLineEdit* LineEditIB;
    QLabel* TextLabel6;
    QLineEdit* LineEditSubkonto;
    QLabel* TextLabel5;
    QLabel* TextLabel4;
    QLineEdit* LineEditProjekt;
    QLineEdit* LineEditKst;
    QLabel* TextLabel3;
    QLabel* TextLabel2;
    QLabel* TextLabel1;
    QLabel* TextLabelGrupp;
    QLineEdit* LineEditManuell;
    QLabel* TextLabelAvd;
    QLabel* TextLabelNamn;
    QLabel* TextLabelUserID;
    QLabel* textLabel1;
    QLabel* TextLabel7;
    QLabel* TextLabel8;
    QLabel* TextLabel9;
    QLabel* TextLabel9_2;
    QLabel* TextLabel9_3;
    QLabel* TextLabel9_4;
    QLabel* TextLabel9_5;
    QLabel* TextLabel9_6;
    QLineEdit* LineEditBar;
    QLineEdit* LineEditKontoNr;
    QLineEdit* LineEditBenamn;
    QLineEdit* LineEditMomskod;
    QLineEdit* LineEditSRU;
    QLineEdit* LineEditKontoplan;

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

protected:

protected slots:
    virtual void languageChange();
};

#endif // FRMADDKONTO_H
