/****************************************************************************
** Form interface generated from reading ui file 'frmdspftgdata.ui'
**
** Created: ons apr 16 16:19:33 2003
**      by:  The User Interface Compiler (uic)
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

    QLabel* TextLabel2;
    QLabel* TextLabel1;
    QLabel* TextLabel3;
    QLabel* TextLabel4_2;
    QLabel* TextLabel4;
    QLabel* TextLabel4_3;
    QLabel* TextLabel6;
    QLabel* TextLabel6_2;
    QLabel* TextLabel6_3;
    QLabel* TextLabel5;
    QLineEdit* LineEditPostAdress;
    QLineEdit* LineEditBesoksAdress;
    QLineEdit* LineEditGodsAdress;
    QLineEdit* LineEditPostnr1;
    QLineEdit* LineEditPostnr2;
    QLineEdit* LineEditPostnr3;
    QLineEdit* LineEditBesoksOrt;
    QLineEdit* LineEditGodsOrt;
    QLabel* TextLabel7;
    QLabel* TextLabel8;
    QLabel* TextLabel9;
    QLineEdit* LineEditemailadress;
    QLabel* TextLabel11;
    QLineEdit* LineEditPostOrt;
    QLineEdit* LineEditMoms1;
    QLabel* TextLabel12;
    QFrame* Line1_2;
    QFrame* Line1;
    QFrame* Line1_3;
    QLineEdit* LineEdit1Telex;
    QLabel* TextLabel8_2;
    QLabel* TextLabel10;
    QLineEdit* LineEditMoms5;
    QLabel* TextLabel16;
    QLineEdit* LineEditMoms4;
    QLabel* TextLabel15;
    QLineEdit* LineEditMoms3;
    QLabel* TextLabel14;
    QLineEdit* LineEditMoms2;
    QLabel* TextLabel13;
    QLineEdit* LineEditFtgNamn;
    QLineEdit* LineEditFtgNr;
    QPushButton* PushButtonOK;
    QLineEdit* LineEditTfnnr;
    QLineEdit* LineEditMobilTfn;
    QLineEdit* LineEditTelefax;


public slots:
    virtual void init();
    virtual void slotGetFtgData( QString posttyp );
    virtual void slotDataOnStdout();
    virtual void slotDataOnStderr();
    virtual void slotEndOfProcess();
    virtual void slotGetADR1();
    virtual void slotGetADR2();
    virtual void slotGetADR3();
    virtual void slotGetFTGNR();
    virtual void slotGetTFN1();
    virtual void slotGetTFN2();
    virtual void slotGetTFAX();
    virtual void slotGetEML1();

};

#endif // FRMDSPFTGDATA_H
