/****************************************************************************
** Form interface generated from reading ui file 'frmdsplev.ui'
**
** Created: fre aug 15 11:15:28 2003
**      by: The User Interface Compiler ($Id: frmdsplev.h,v 1.1 2003/09/28 07:57:07 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef FRMDSPLEV_H
#define FRMDSPLEV_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QLabel;
class QLineEdit;
class QPushButton;

class frmDspLev : public QWidget
{
    Q_OBJECT

public:
    frmDspLev( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~frmDspLev();

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
    QLineEdit* lineEditLevTelexNr;
    QLineEdit* lineEditLevKontoNr;
    QLineEdit* lineEditLevPgNr;
    QLineEdit* lineEditLevBgNr;
    QLabel* textLabel3_2;
    QLineEdit* lineEditLevSkuld;
    QLabel* textLabel15_2;
    QLabel* textLabel2_2;
    QLabel* textLabel1_2;
    QLineEdit* lineEditLevKundNr;
    QPushButton* pushButtonOK;
    QLabel* textLabel2_3;
    QLabel* textLabel1_3;
    QLabel* textLabel4_2;
    QLabel* textLabel3_3;
    QLineEdit* lineEditBetvilk;
    QLineEdit* lineEditValuta;
    QLineEdit* lineEditBetvilkDag;
    QLabel* textLabel1;

public slots:
    virtual void slotLevNr_returnPressed();
    virtual void slotGetLev();
    virtual void slotDataOnStdout();
    virtual void slotDataOnStderr();
    virtual void slotEndOfProcess();
    virtual void slotGetFtgData( QString posttyp );
    virtual void slotFtgEndOfProcess();

protected:

protected slots:
    virtual void languageChange();
private:
    void init();

};

#endif // FRMDSPLEV_H
