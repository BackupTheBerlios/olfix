/****************************************************************************
** Form interface generated from reading ui file 'frmchglev.ui'
**
** Created: fre aug 15 11:21:12 2003
**      by: The User Interface Compiler ($Id: frmchglev.h,v 1.1 2003/09/28 06:48:00 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef FRMCHGLEV_H
#define FRMCHGLEV_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QLabel;
class QLineEdit;
class QPushButton;

class frmChgLev : public QWidget
{
    Q_OBJECT

public:
    frmChgLev( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~frmChgLev();

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
    QPushButton* pushButtonGet;
    QLineEdit* lineEditLevOrgNr;
    QLineEdit* lineEditLevNamn;
    QLineEdit* lineEditLevAdress;
    QLineEdit* lineEditLevPostnr;
    QLineEdit* lineEditLevPostAdress;
    QLineEdit* lineditLevNr;
    QLineEdit* lineEditLevLand;
    QLineEdit* lineEditLevTfnNr;
    QLineEdit* lineEditLevFaxNr;
    QLineEdit* lineEditLevEmail;
    QLineEdit* lineEditLevRef;
    QLineEdit* lineEditLevRefTfnNr;
    QLineEdit* lineEditLevMomskod;
    QLineEdit* lineEditLevKontoNr;
    QLineEdit* lineEditLevTelexNr;
    QLabel* textLabel1_2;
    QLabel* textLabel2_2;
    QLineEdit* lineEditLevPgNr;
    QLineEdit* lineEditLevBgNr;
    QLineEdit* lineEditLevKundNr;
    QPushButton* pushButtonOK;
    QPushButton* pushButtonSluta;
    QLabel* textLabel16;
    QLabel* textLabel16_2;
    QLabel* textLabel2_3;
    QLineEdit* lineEditBetvilk;
    QLineEdit* lineEditValuta;
    QLabel* textLabel1;

public slots:
    virtual void slotLevNr_returnPressed();
    virtual void slotGetLev();
    virtual void slotDataOnStdout();
    virtual void slotDataOnStderr();
    virtual void slotEndOfGetProcess();
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
    virtual void slotValuta_returnPressed();
    virtual void slotBetvillkor_returnPressed();
    virtual void slotUpdateLev();
    virtual void slotEndOfUpdateProcess();

protected:

protected slots:
    virtual void languageChange();
private:
    void init();

};

#endif // FRMCHGLEV_H
