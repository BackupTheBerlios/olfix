/****************************************************************************
** Form interface generated from reading ui file 'frmaddftgdata.ui'
**
** Created: lör aug 16 05:44:06 2003
**      by: The User Interface Compiler ($Id: frmaddftgdata.h,v 1.1 2003/09/28 08:56:48 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef FRMADDFTGDATA_H
#define FRMADDFTGDATA_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QFrame;
class QLabel;
class QLineEdit;
class QPushButton;

class frmAddFtgData : public QWidget
{
    Q_OBJECT

public:
    frmAddFtgData( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~frmAddFtgData();

    QFrame* Line1_2;
    QFrame* Line1;
    QLabel* textLabel3_2;
    QLabel* TextLabel13;
    QLabel* TextLabel14_2;
    QLabel* TextLabel14;
    QLabel* TextLabel14_3;
    QLabel* TextLabel12;
    QLabel* TextLabel4;
    QLabel* TextLabel4_2;
    QLabel* TextLabel4_3;
    QLabel* TextLabel1;
    QLabel* TextLabel5;
    QLabel* TextLabel2;
    QLabel* TextLabel7;
    QLabel* TextLabel9;
    QLabel* TextLabel8;
    QLabel* TextLabel8_2;
    QLabel* TextLabel10;
    QLabel* TextLabel6;
    QLabel* TextLabel6_2;
    QLabel* TextLabel6_3;
    QLabel* textLabel3;
    QLabel* textLabel4;
    QFrame* Line1_3;
    QLineEdit* LineEditTfnnr;
    QLineEdit* LineEditMobilTfn;
    QLineEdit* LineEditTelefax;
    QLineEdit* LineEditemailadress;
    QLineEdit* LineEditTelex;
    QLineEdit* LineEditMoms2;
    QLineEdit* LineEditMoms3;
    QLineEdit* LineEditMoms4;
    QLineEdit* LineEditMoms5;
    QLineEdit* lineEditMomsKtoIng;
    QLineEdit* lineEditMomsKtoUtg;
    QLineEdit* lineEditAutokonto;
    QLineEdit* LineEditMoms1;
    QPushButton* pushButtonQuit;
    QLineEdit* LineEditPostAdress;
    QLineEdit* LineEditPostnr1;
    QLineEdit* LineEditPostOrt;
    QLineEdit* LineEditFtgNamn;
    QLineEdit* LineEditFtgNr;
    QLabel* TextLabel3;
    QLineEdit* LineEditBesoksAdress;
    QLineEdit* LineEditPostnr2;
    QLineEdit* LineEditBesoksOrt;
    QLineEdit* LineEditGodsAdress;
    QLineEdit* LineEditPostnr3;
    QLineEdit* LineEditGodsOrt;
    QLabel* TextLabel11;
    QPushButton* PushButtonOK;

public slots:
    virtual void init();
    virtual void slotLineEditFtgNamn_returnPressed();
    virtual void slotLineEditFtgNr_returnPressed();
    virtual void slotLineEditPostAdress_returnPressed();
    virtual void slotLineEditPostnr1_returnPressed();
    virtual void slotLineEditPostOrt_returnPressed();
    virtual void slotLineEditBesoksAdress_returnPressed();
    virtual void slotLineEditPostnr2_returnPressed();
    virtual void slotLineEditBesoksOrt_returnPressed();
    virtual void slotLineEditGodsAdress_returnPressed();
    virtual void slotLineEditPostnr3_returnPressed();
    virtual void slotLineEditGodsOrt_returnPressed();
    virtual void slotLineEditTfnnr_returnPressed();
    virtual void slotLineEditMobilTfn_returnPressed();
    virtual void slotLineEditTelefax_returnPressed();
    virtual void slotLineEditemailadress_returnPressed();
    virtual void slotLineEditTelex_returnPressed();
    virtual void slotLineEditMoms1_returnPressed();
    virtual void slotLineEditMoms2_returnPresse();
    virtual void slotLineEditMoms3_returnPressed();
    virtual void slotLineEditMoms4_returnPressed();
    virtual void slotLineEditMoms5_returnPressed();
    virtual void slotlineEditMomsKtoIng_returnPressed();
    virtual void slotlineEditMomsKtoUtg_returnPressed();
    virtual void slotlineEditAutokonto_returnPressed();
    virtual void slotPushButtonOK_clicked();
    virtual void slotUpdateFtgdata( QString posttyp, QString ftgdata );
    virtual void slotDataOnStdout();
    virtual void slotDataOnStderr();
    virtual void slotUpdateEndOfProcess();
    virtual void slotGetFtgdata();
    virtual void slotGetEndOfProcess();

protected:

protected slots:
    virtual void languageChange();
};

#endif // FRMADDFTGDATA_H
