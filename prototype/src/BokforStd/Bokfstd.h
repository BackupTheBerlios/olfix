/****************************************************************************
** Form interface generated from reading ui file 'Bokfstd.ui'
**
** Created: ons aug 13 08:41:21 2003
**      by: The User Interface Compiler ($Id: Bokfstd.h,v 1.2 2003/09/28 06:37:16 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef FRMBOKFSTD_H
#define FRMBOKFSTD_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QFrame;
class QLabel;
class QLineEdit;
class QListView;
class QListViewItem;
class QPushButton;

class frmBokfstd : public QWidget
{
    Q_OBJECT

public:
    frmBokfstd( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~frmBokfstd();

    QLabel* TextLabel3;
    QLabel* TextLabel2;
    QLabel* TextLabel1_3;
    QLabel* TextLabel1_2;
    QLabel* TextLabel11;
    QLabel* TextLabel1;
    QLabel* TextLabel4_2;
    QLabel* TextLabel3_2;
    QLineEdit* LineEditVernr;
    QLineEdit* LineEditVerText;
    QLabel* TextLabelDate;
    QLabel* textLabelVersion;
    QLineEdit* LineEditBar;
    QPushButton* PushButtonSluta;
    QPushButton* PushButtonVerNej;
    QPushButton* PushButtonVerOK;
    QPushButton* PushButtonRadNej;
    QLabel* TextLabel2_2;
    QPushButton* PushButtonRadOK;
    QLineEdit* LineEditKst;
    QLabel* TextLabel3_3;
    QLabel* TextLabel6;
    QLineEdit* LineEditDK;
    QLabel* TextLabel7;
    QLineEdit* LineEditKtonr;
    QLineEdit* LineEditBelopp;
    QLabel* TextLabel5;
    QLineEdit* LineEditDiff;
    QLineEdit* LineEditRadnr;
    QLabel* TextLabel9;
    QLabel* TextLabel4_3;
    QLineEdit* LineEditSubKto;
    QLabel* TextLabel10;
    QFrame* line5;
    QLabel* TextLabel12;
    QListView* ListViewVerrader;
    QListView* ListViewKto;

public slots:
    virtual void slotLineEditBar_lostFocus();
    virtual void slotLineEditBar_returnPressed();
    virtual void slotLineEditVerText_returnPressed();
    virtual void slotLineEditKtonr_textChanged();
    virtual void slotLineEditKtonr_lostFocus();
    virtual void slotLineEditKtonr_returnPressed();
    virtual void slotLineEditDK_lostFocus();
    virtual void slotLineEditDK_returnPressed();
    virtual void slotLineEditBelopp_returnPressed();
    virtual void slotLineEditKst_returnPressed();
    virtual void slotLineEditSubKto_returnPressed();
    virtual void slotRadOK();
    virtual void slotUpdateRadnr();
    virtual void slotPickupKtonr( QListViewItem * item );
    virtual void slotGetKontoLista();
    virtual void slotKTOVIEWDataOnStdout();
    virtual void slotDataOnStdout();
    virtual void slotDataOnStderr();
    virtual void slotBARCHKEndOfProcess();
    virtual void slotCheckBar();
    virtual void slotGetNextVernr();
    virtual void slotBARDSPEndOfProcess();
    virtual void slotKTOVIEWEndOfProcess();
    virtual void slotCheckKstalle();
    virtual void slotKSTCHKEndOfProcess();
    virtual void slotCheckKonto();
    virtual void slotKTOCHKEndOfProcess();
    virtual void slotSaveVerHuvud();
    virtual void slotSaveVerRad();
    virtual void slotWRRECEndOfProcess();
    virtual void slotVerOK();
    virtual void slotVerRemove();
    virtual void slotVERUPDEndOfProcess();
    virtual void slotCleanUp();

protected:

protected slots:
    virtual void languageChange();

    virtual void init();

};

#endif // FRMBOKFSTD_H
