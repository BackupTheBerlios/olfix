/****************************************************************************
** Form interface generated from reading ui file 'Bokfstd.ui'
**
** Created: tor mar 20 08:01:32 2003
**      by:  The User Interface Compiler (uic)
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

    QLabel* TextLabel1;
    QLabel* TextLabel3;
    QLabel* TextLabel1_2;
    QLabel* TextLabel3_2;
    QLabel* TextLabel4_2;
    QLabel* TextLabel12;
    QLabel* TextLabel2;
    QLabel* TextLabel11;
    QLabel* TextLabel10;
    QPushButton* PushButtonVerNej;
    QPushButton* PushButtonSluta;
    QLabel* TextLabel1_3;
    QPushButton* PushButtonRadNej;
    QFrame* Line2;
    QLabel* TextLabel9;
    QLabel* TextLabel7;
    QLabel* TextLabel6;
    QLabel* TextLabel5;
    QLabel* TextLabel4_3;
    QLabel* TextLabel3_3;
    QLabel* TextLabel2_2;
    QLabel* TextLabel1_4;
    QLineEdit* LineEditBar;
    QLabel* TextLabelDate;
    QListView* ListViewKto;
    QLineEdit* LineEditVernr;
    QLineEdit* LineEditVerText;
    QLineEdit* LineEditRadnr;
    QLineEdit* LineEditKtonr;
    QLineEdit* LineEditDK;
    QLineEdit* LineEditBelopp;
    QLineEdit* LineEditKst;
    QLineEdit* LineEditSubKto;
    QLineEdit* LineEditDiff;
    QListView* ListViewVerrader;
    QPushButton* PushButtonRadOK;
    QPushButton* PushButtonVerOK;


public slots:
    virtual void slotLineEditBar_returnPressed();
    virtual void slotLineEditVerText_returnPressed();
    virtual void slotLineEditKtonr_returnPressed();
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

protected slots:
    virtual void init();

protected:
};

#endif // FRMBOKFSTD_H
