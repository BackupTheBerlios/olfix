/****************************************************************************
** Form interface generated from reading ui file 'frmlevfakt.ui'
**
** Created: mån aug 18 06:08:46 2003
**      by: The User Interface Compiler ($Id: frmlevfakt.h,v 1.1 2003/09/28 08:14:58 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef FRMLEVFAKT_H
#define FRMLEVFAKT_H

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

class frmLevFakt : public QWidget
{
    Q_OBJECT

public:
    frmLevFakt( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~frmLevFakt();

    QLabel* textLabel8;
    QLabel* textLabel10;
    QLabel* textLabel11;
    QLabel* textLabel3;
    QLabel* textLabel5;
    QLabel* textLabel2;
    QLabel* textLabel13;
    QLabel* textLabel4;
    QLabel* textLabel5_2;
    QLabel* textLabel12;
    QLineEdit* lineEditLevOrgNr;
    QLineEdit* lineEditLevNamn;
    QLineEdit* lineEditLevAdress;
    QLineEdit* lineEditLevPostNr;
    QLineEdit* lineEditLevPostAdr;
    QLineEdit* lineEditLevLand;
    QLineEdit* lineEditLevKundNr;
    QLineEdit* lineEditLevFakturaNr;
    QLineEdit* lineEditFakturadatum;
    QLineEdit* lineEditRegDatum;
    QLabel* textLabel6;
    QLineEdit* lineEditLevFakturaText;
    QLabel* textLabel7;
    QLabel* textLabel5_4;
    QLabel* textLabel6_3;
    QLineEdit* lineEditLevBetDatum;
    QFrame* line1;
    QPushButton* pushButtonOK;
    QPushButton* pushButtonQuit;
    QLabel* textLabel2_3;
    QLabel* textLabel7_2;
    QLineEdit* lineEditLevMomskod;
    QLineEdit* lineEditValutaKurs;
    QLineEdit* lineEditValuta;
    QFrame* line2;
    QLabel* textLabel9;
    QLineEdit* lineEditVernr;
    QLabel* textLabel3_2;
    QFrame* line3;
    QLabel* textLabel2_2;
    QLabel* textLabel1_2;
    QLineEdit* lineEditMoms;
    QLabel* textLabel3_3;
    QLabel* textLabel1_4;
    QLabel* textLabel4_2;
    QLabel* textLabel8_2;
    QLabel* textLabel10_2;
    QLabel* textLabel1_5;
    QLineEdit* lineEditOCRnr;
    QLabel* textLabel1_3;
    QLabel* textLabel5_3;
    QLabel* textLabel6_2;
    QLineEdit* lineEditBar;
    QLineEdit* lineEditBetalningsvilkor;
    QLineEdit* lineEditLevNr;
    QListView* listViewLev;
    QListView* listViewKtonr;
    QLineEdit* lineEditFaktBelopp;
    QLineEdit* lineEditKreditKontoNr;
    QLineEdit* lineEditKreditBelopp;
    QLineEdit* lineEditMomsKontoNr;
    QLineEdit* lineEditMomsBelopp;
    QLineEdit* lineEditDebetKontoNr;
    QLineEdit* lineEditDebetBelopp;
    QLabel* textLabel1;
    QLabel* textLabelAutokonto;

public slots:
    virtual void slotlineEditLevNr_returnPressed();
    virtual void slotlineEditLevKundNr_returnPressed();
    virtual void slotlineEditRegDatum_returnPressed();
    virtual void slotlineEditFaktNr_returnPressed();
    virtual void slotlineEditFakturadatum_returnPressed();
    virtual void slotlineEditBetvilk_returnPressed();
    virtual void slotlineEditLevBetDatum_returnPressed();
    virtual void slotlineEditOCRnr_returnPressed();
    virtual void slotlineEditLevFakturaText_returnPressed();
    virtual void slotlineEditBar_returnPressed();
    virtual void slotlineEditLevMomskod_returnPressed();
    virtual void slotlineEditValuta_returnPressed();
    virtual void slotlineEditValutaKurs_returnPressed();
    virtual void slotlineEditFaktBelopp_returnPressed();
    virtual void slotlineEditKreditKontoNr_returnPressed();
    virtual void slotlineEditKreditBelopp_returnPressed();
    virtual void slotlineEditMomsKtoNr_returnPressed();
    virtual void slotlineEditMomsBelopp_returnPressed();
    virtual void slotlineEditDebetKontoNr_returnPressed();
    virtual void slotlineEditDebetBelopp_returnPressed();
    virtual void checkSemafor();
    virtual void slotGetLev();
    virtual void slotDataOnStdout();
    virtual void slotDataOnStderr();
    virtual void slotEndOfGetProcess();
    virtual void slotCheckBar();
    virtual void slotBARCHKEndOfProcess();
    virtual void slotCheckKontoNr( QString ktonr );
    virtual void slotKTOCHKEndOfProcess();
    virtual void slotGetMoms( QString momskod );
    virtual void slotFTGDSPEndOfProcess();
    virtual void slotUpdateLevresk();
    virtual void slotLEVRESKEndOfProcess();
    virtual void slotGetNextVernr();
    virtual void slotBARDSPEndOfProcess();
    virtual void slotSaveVerHuvud();
    virtual void slotSaveVerRad( QString ktonummer, QString belopp, QString radnr );
    virtual void slotWRRECEndOfProcess();
    virtual void slotUppdateraVer();
    virtual void slotVERUPDEndOfProcess();
    virtual void slotVerRemove();
    virtual void slotClearVariabler();
    virtual void slotGetValuta();
    virtual void slotVALDSPEndOfProcess();
    virtual void slotGetBetvilkor( QString betvilkor );
    virtual void slotBETDSPDataOnStdout();
    virtual void slotBETDSPEndOfProcess();
    virtual void slotFindBar( QString datum );
    virtual void slotBARFNDDataOnStdout();
    virtual void slotBARFNDEndOfProcess();
    virtual void slotGetMomsKonto();
    virtual void slotGetMomsKtoEndOfProcess();
    virtual void slotGetLevLista();
    virtual void slotGetLevlistaEndOfProcess();
    virtual void slotPickupLevnr( QListViewItem * item );
    virtual void slotGetKontoLista();
    virtual void slotKTOVIEWEndOfProcess();
    virtual void slotPickupKtonr( QListViewItem * item );
    virtual void slotGetAutokonto();
    virtual void slotGetAutokontoEndOfProcess();

protected:

protected slots:
    virtual void languageChange();
private:
    void init();

};

#endif // FRMLEVFAKT_H
