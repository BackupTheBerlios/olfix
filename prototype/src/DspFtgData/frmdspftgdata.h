/****************************************************************************
** Form interface generated from reading ui file 'frmdspftgdata.ui'
**
** Created: fre aug 15 11:08:55 2003
**      by: The User Interface Compiler ($Id: frmdspftgdata.h,v 1.2 2003/09/28 07:49:24 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef FRMDSPFTGDATA_H
#define FRMDSPFTGDATA_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QFrame;
class QLabel;
class QLineEdit;
class QPushButton;

class frmDspFtgData : public QWidget
{
    Q_OBJECT

public:
    frmDspFtgData( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~frmDspFtgData();

    QFrame* Line1_2;
    QLineEdit* LineEdit1Telex;
    QLineEdit* LineEditMoms5;
    QLineEdit* LineEditMoms4;
    QLineEdit* LineEditFtgNr;
    QLineEdit* LineEditTfnnr;
    QLineEdit* LineEditTelefax;
    QLineEdit* LineEditMoms1;
    QPushButton* PushButton5;
    QLineEdit* LineEditFtgNamn;
    QLabel* TextLabel4_3;
    QLabel* TextLabel4_2;
    QLabel* TextLabel4;
    QLabel* TextLabel6_3;
    QLabel* TextLabel6;
    QFrame* Line1;
    QLabel* TextLabel6_2;
    QLabel* TextLabel8_2;
    QLabel* TextLabel10;
    QLabel* TextLabel8;
    QLineEdit* LineEditPostAdress;
    QLineEdit* LineEditPostOrt;
    QLineEdit* LineEditBesoksAdress;
    QLineEdit* LineEditBesoksOrt;
    QLineEdit* LineEditGodsAdress;
    QLineEdit* LineEditGodsOrt;
    QLineEdit* LineEditMoms2;
    QLineEdit* lineEditMomktoIng;
    QLineEdit* lineEditMomktoUtg;
    QLabel* TextLabel14;
    QFrame* Line1_3;
    QLabel* TextLabel16;
    QLabel* TextLabel15;
    QLabel* TextLabel13;
    QLineEdit* LineEditMobilTfn;
    QLineEdit* LineEditemailadress;
    QLineEdit* LineEditMoms3;
    QLineEdit* LineEditPostnr1;
    QLineEdit* LineEditPostnr2;
    QLineEdit* LineEditPostnr3;
    QLabel* TextLabel2;
    QLabel* TextLabel1;
    QLabel* TextLabel5;
    QLabel* TextLabel7;
    QLabel* TextLabel9;
    QLabel* TextLabel12;
    QLabel* TextLabel3;
    QLabel* textLabel1;
    QLabel* textLabel1_2;
    QLabel* textLabel2;
    QLineEdit* lineEditAutokont;
    QPushButton* PushButtonOK;
    QLabel* TextLabel11;

public slots:
    virtual void init();
    virtual void slotGetFtgData( QString posttyp );
    virtual void slotDataOnStdout();
    virtual void slotDataOnStderr();
    virtual void slotEndOfProcess();
    virtual void slotGetFNAMN();
    virtual void slotGetADR1();
    virtual void slotGetADR2();
    virtual void slotGetADR3();
    virtual void slotGetADR4();
    virtual void slotGetADR5();
    virtual void slotGetADR6();
    virtual void slotGetADR7();
    virtual void slotGetADR8();
    virtual void slotGetADR9();
    virtual void slotGetFTGNR();
    virtual void slotGetTFN1();
    virtual void slotGetTFN2();
    virtual void slotGetTFAX();
    virtual void slotGetEML1();
    virtual void slotGetMOMS1();
    virtual void slotGetMOMS2();
    virtual void slotGetMOMS3();
    virtual void slotGetMOMS4();
    virtual void slotGetMOMS5();
    virtual void slotGetMOMSI();
    virtual void slotGetMOMSU();
    virtual void slotGetAUTOK();

protected:

protected slots:
    virtual void languageChange();
};

#endif // FRMDSPFTGDATA_H
