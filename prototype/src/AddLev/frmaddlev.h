/****************************************************************************
** Form interface generated from reading ui file 'frmaddlev.ui'
**
** Created: fre aug 15 11:17:46 2003
**      by: The User Interface Compiler ($Id: frmaddlev.h,v 1.1 2003/09/28 06:12:19 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef FRMADDLEV_H
#define FRMADDLEV_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QLabel;
class QLineEdit;
class QPushButton;

class frmAddLev : public QWidget
{
    Q_OBJECT

public:
    frmAddLev( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~frmAddLev();

    QLabel* textLabel2;
    QLabel* textLabel3;
    QLabel* textLabel4;
    QLabel* textLabel7;
    QLabel* textLabel5;
    QLabel* textLabel8;
    QLabel* textLabel6;
    QLabel* textLabel9;
    QLabel* textLabel10;
    QLabel* textLabel11;
    QLabel* textLabel12;
    QLabel* textLabel13;
    QLabel* textLabel15;
    QLabel* textLabel14;
    QLabel* textLabel1_2;
    QLabel* textLabel1_2_2;
    QLabel* textLabel1_2_3;
    QLineEdit* lineditLevNr;
    QLineEdit* lineEditLevOrgNr;
    QLineEdit* lineEditLevNamn;
    QLineEdit* lineEditLevAdress;
    QLineEdit* lineEditLevPostnr;
    QLineEdit* lineEditLevPostAdress;
    QLineEdit* lineEditLevLand;
    QLineEdit* lineEditLevTftnNr;
    QLineEdit* lineEditLevFaxNr;
    QLineEdit* lineEditLevTelexNr;
    QLineEdit* lineEditLevEmail;
    QLineEdit* lineEditLevRef;
    QLineEdit* lineEditLevRefTfnNr;
    QLineEdit* lineEditLevKontoNr;
    QLabel* textLabel1_3;
    QLabel* textLabel4_2;
    QLabel* textLabel5_2;
    QLineEdit* lineEditLevBgNr;
    QLineEdit* lineEditLevPgNr;
    QLineEdit* lineEditLevKundNr;
    QPushButton* pushButtonOK;
    QPushButton* pushButtonAvbryt;
    QLabel* textLabel14_2;
    QLabel* textLabel3_2;
    QLabel* textLabel4_3;
    QLineEdit* lineEditValuta;
    QLineEdit* lineEditBetvilk;
    QLineEdit* lineEditLevMomskod;
    QLabel* textLabel1;

public slots:
    virtual void init();
    virtual void slotLevNr_returnPressed();
    virtual void slotLevOrgNr_returnPressed();
    virtual void slotLevNamn_returnPressed();
    virtual void slotLevAdress_returnPressed();
    virtual void slotLevPostNr_returnPressed();
    virtual void slotLevPostAdress_returnPressed();
    virtual void slotLevLand_returnPressed();
    virtual void slotLevTfnNr_returnPressed();
    virtual void slotLevFaxNr_returnPressed();
    virtual void slotLevTelexNr_returnPressed();
    virtual void slotLevEmail_returnPressed();
    virtual void slotLevRef_returnPressed();
    virtual void slotLevRefTfnNr_returnPressed();
    virtual void slotLevMomskod_returnPressed();
    virtual void slotLevKontoNr_returnPressed();
    virtual void slotLevPgNr_returnPressed();
    virtual void slotLevBgNr_returnPressed();
    virtual void slotLevKundNr_returnPressed();
    virtual void slotLevValuta_returnPressed();
    virtual void slotLevBetvilk_returnPressed();
    virtual void slotBtnOK_clicked();
    virtual void slotAddLev();
    virtual void slotDataOnStdout();
    virtual void slotDataOnStderr();
    virtual void slotEndOfProcess();

protected:

protected slots:
    virtual void languageChange();
};

#endif // FRMADDLEV_H
