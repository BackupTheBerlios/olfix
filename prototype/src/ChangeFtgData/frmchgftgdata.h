/****************************************************************************
** Form interface generated from reading ui file 'frmchgftgdata.ui'
**
** Created: tor aug 14 09:31:44 2003
**      by: The User Interface Compiler ($Id: frmchgftgdata.h,v 1.2 2003/09/28 06:40:16 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef FRMCHGFTGDATA_H
#define FRMCHGFTGDATA_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QLabel;
class QLineEdit;
class QListView;
class QListViewItem;
class QPushButton;

class frmChgFtgData : public QWidget
{
    Q_OBJECT

public:
    frmChgFtgData( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~frmChgFtgData();

    QLabel* TextLabel1;
    QPushButton* PushButtonOK;
    QPushButton* PushButtonUpdate;
    QListView* ListView1;
    QPushButton* PushButtonGet;
    QLineEdit* LineEditPosttyp;

public slots:
    virtual void init();
    virtual void slotGetPosttyp();
    virtual void PushButtonGet_clicked();
    virtual void slotGetFtgData( QString posttyp );
    virtual void slotDataOnStdout();
    virtual void slotDataOnStderr();
    virtual void slotEndOfProcess();
    virtual void slotGetADR1();
    virtual void slotLineEditAdr1_FtgNamn_returnPressed();
    virtual void slotLineEditAdr1_PostAdr_returnPressed();
    virtual void slotLineEditAdr1_PostNr_returnPressed();
    virtual void slotLineEditAdr1_Ort_returnPressed();
    virtual void slotGetADR4();
    virtual void slotLineEditAdr2_BesokAdr_returnPressed();
    virtual void slotLineEditAdr2_PostNr_returnPressed();
    virtual void slotLineEditAdr2_Ort_returnPressed();
    virtual void slotGetADR7();
    virtual void slotLineEditAdr3_GodsAdr_returnPressed();
    virtual void slotLineEditAdr3_PostNr_returnPressed();
    virtual void slotLineEditAdr3_Ort_returnPressed();
    virtual void slotGetFNAMN();
    virtual void slotLineEditFnamn_returnPressed();
    virtual void slotGetFTGNR();
    virtual void slotLineEditFtgnr_returnPressed();
    virtual void slotGetTFN1();
    virtual void slotLineEditTfnnr1_returnPressed();
    virtual void slotGetTFN2();
    virtual void slotLineEditTfnnr2_returnPressed();
    virtual void slotGetTFAX();
    virtual void slotLineEditTelefax_returnPressed();
    virtual void slotGetEML1();
    virtual void slotLineEditEmail_returnPressed();
    virtual void slotGetMOMS1();
    virtual void slotLineEditMoms1_returnPressed();
    virtual void slotGetMOMS2();
    virtual void slotLineEditMoms2_returnPressed();
    virtual void slotGetMOMS3();
    virtual void slotLineEditMoms3_returnPressed();
    virtual void slotGetBVLK1();
    virtual void slotLineEditBetvilk1_returnPressed();
    virtual void slotGetBVLK2();
    virtual void slotLineEditBetvilk2_returnPressed();
    virtual void slotGetBVLK3();
    virtual void slotLineEditBetvilk3_returnPressed();
    virtual void slotGetPosttyper();
    virtual void slotGetPostEndOfProcess();
    virtual void ListView1_clicked( QListViewItem * item );
    virtual void slotUpdFtgData( QString posttyp, QString ftgdata );
    virtual void slotUpdateEndOfProcess();
    virtual void PushButtonUpdate_clicked();
    virtual void slotGetAUTOK();
    virtual void slotLineEditAutokonto_returnPressed();

protected:

protected slots:
    virtual void languageChange();
};

#endif // FRMCHGFTGDATA_H
