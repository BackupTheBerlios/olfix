/****************************************************************************
** Form interface generated from reading ui file 'frmaddkund.ui'
**
** Created: tor sep 11 04:33:07 2003
**      by: The User Interface Compiler ($Id: frmaddkund.h,v 1.1 2003/09/28 06:06:24 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef FRMADDKUND_H
#define FRMADDKUND_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QLabel;
class QLineEdit;
class QPushButton;

class frmAddKund : public QWidget
{
    Q_OBJECT

public:
    frmAddKund( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~frmAddKund();

    QPushButton* pushButtonAvbryt;
    QLabel* textLabel1_5;
    QLabel* textLabel1_2;
    QLabel* textLabel1;
    QLabel* textLabel12;
    QLabel* textLabel5_2_3;
    QLabel* textLabel6_2_4;
    QLabel* textLabel3;
    QLabel* textLabel4;
    QLabel* textLabel6_2;
    QLabel* textLabel8_2_2_2;
    QLabel* textLabel7;
    QLabel* textLabel7_2;
    QLabel* textLabel8_2_2_3;
    QLabel* textLabel5;
    QLabel* textLabel3_3;
    QLabel* textLabel3_2;
    QLabel* textLabel5_2_2;
    QLabel* textLabel9;
    QLabel* textLabel1_4;
    QLabel* textLabel11;
    QLabel* textLabel6_2_3;
    QLabel* textLabel8;
    QLabel* textLabel1_5_3;
    QLabel* textLabel2_2;
    QLabel* textLabel6_2_2;
    QLabel* textLabel7_2_2;
    QLabel* textLabel6;
    QLabel* textLabel13;
    QLabel* textLabel4_2_2;
    QLabel* textLabel8_2_2;
    QLabel* textLabel4_2;
    QLabel* textLabel8_2;
    QLabel* textLabel1_3;
    QLabel* textLabel1_5_2;
    QLineEdit* lineEditKundAdress;
    QLineEdit* lineEditKundBetvilk;
    QLineEdit* lineEditValuta;
    QLineEdit* lineEditSprakkod;
    QLineEdit* lineEditOrdererk;
    QLineEdit* lineEditPlocklista;
    QLineEdit* lineEditFoljesedel;
    QLineEdit* lineEditExpAvgift;
    QLineEdit* lineEditFraktAvgift;
    QLineEdit* lineEditKravbrev;
    QLineEdit* lineEditDrojRenta;
    QLineEdit* lineEditDrojFaktura;
    QPushButton* pushButtonOK;
    QLineEdit* lineEditKundLevsett;
    QLabel* textLabel5_2;
    QLineEdit* lineEditKundLevvilk;
    QLabel* textLabel1_6;
    QLineEdit* lineEditKundNr;
    QLineEdit* lineEditKundNamn;
    QLineEdit* lineEditKundPostnr;
    QLineEdit* lineEditKundPostAdress;
    QLineEdit* lineEditKundLand;
    QLineEdit* lineEditKundTftnNr;
    QLineEdit* lineEditKundFaxNr;
    QLineEdit* lineEditKundEmail;
    QLineEdit* lineEditKundErRef;
    QLineEdit* lineEditErRefTfnNr;
    QLineEdit* lineEditKundErRefEmail;
    QLineEdit* lineEditKundSeljare;
    QLineEdit* lineEditKundDistrikt;
    QLineEdit* lineEditKundKategori;
    QLineEdit* lineEditKreditlimit;
    QLineEdit* lineEditFriText;
    QLineEdit* lineEditKundStdLevplats;

public slots:
    virtual void init();
    virtual void lineEditKundNr_returnPressed();
    virtual void lineEditKundNamn_returnPressed();
    virtual void lineEditKundAdress_returnPressed();
    virtual void lineEditKundPostnr_returnPressed();
    virtual void lineEditKundPostAdress_returnPressed();
    virtual void lineEditKundLand_returnPressed();
    virtual void lineEditKundTftnNr_returnPressed();
    virtual void lineEditKundFaxNr_returnPressed();
    virtual void lineEditKundEmail_returnPressed();
    virtual void lineEditKundErRef_returnPressed();
    virtual void lineEditErRefTfnNr_returnPressed();
    virtual void lineEditKundErRefEmail_returnPressed();
    virtual void lineEditKundSeljare_returnPressed();
    virtual void lineEditKundDistrikt_returnPressed();
    virtual void lineEditKundKategori_returnPressed();
    virtual void lineEditKundStdLevplats_returnPressed();
    virtual void lineEditKundLevvilk_returnPressed();
    virtual void lineEditKundLevsett_returnPressed();
    virtual void lineEditKundBetvilk_returnPressed();
    virtual void lineEditValuta_returnPressed();
    virtual void lineEditSprakkod_returnPressed();
    virtual void lineEditOrdererk_returnPressed();
    virtual void lineEditPlocklista_returnPressed();
    virtual void lineEditFoljesedel_returnPressed();
    virtual void lineEditExpAvgift_returnPressed();
    virtual void lineEditFraktAvgift_returnPressed();
    virtual void lineEditKravbrev_returnPressed();
    virtual void lineEditKreditlimit_returnPressed();
    virtual void lineEditDrojRenta_returnPressed();
    virtual void lineEditDrojFaktura_returnPressed();
    virtual void lineEditFriText_returnPressed();
    virtual void pushButtonOK_clicked();
    virtual void updateKundreg();
    virtual void slotUpdateEndOfProcess();
    virtual void CheckKundnr();
    virtual void slotCheckEndOfProcess();
    virtual void createStandardLevPlats();
    virtual void slotPlatsEndOfProcess();
    virtual void AddLevplats001();
    virtual void slotPlats001EndOfProcess();
    virtual void slotDataOnStderr();
    virtual void slotDataOnStdout();

protected:

protected slots:
    virtual void languageChange();
};

#endif // FRMADDKUND_H
