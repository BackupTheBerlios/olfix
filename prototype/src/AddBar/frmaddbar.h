/****************************************************************************
** Form interface generated from reading ui file 'frmaddbar.ui'
**
** Created: ons maj 28 05:28:30 2003
**      by: The User Interface Compiler ($Id: frmaddbar.h,v 1.2 2003/09/28 05:45:57 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef FRMADDBAR_H
#define FRMADDBAR_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QLabel;
class QLineEdit;
class QPushButton;

class frmAddBar : public QWidget
{
    Q_OBJECT

public:
    frmAddBar( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~frmAddBar();

    QLabel* TextLabel5;
    QLabel* TextLabel01;
    QLabel* TextLabel02;
    QLabel* TextLabel03;
    QLabel* TextLabel1;
    QLineEdit* LineEditBenamn;
    QLineEdit* LineEditStartdatum;
    QLabel* TextLabel9_3;
    QLineEdit* LineEditSlutdatum;
    QLineEdit* LineEditBeskattAr;
    QLineEdit* LineEditSenVerDat;
    QLabel* TextLabel3;
    QLabel* TextLabel2;
    QLineEdit* LineEditNestaVerNr;
    QLabel* TextLabel4;
    QLineEdit* LineEditKontoplan;
    QLabel* TextLabel9_5_2;
    QLabel* TextLabel9_4;
    QLabel* TextLabel9_5;
    QPushButton* PushButtonOK;
    QPushButton* PushButtonQuit;
    QLineEdit* LineEditBar;
    QLabel* TextLabel9;
    QPushButton* pushButton3;

public slots:
    virtual void slotAddBar();
    virtual void LineEditBar_returnPressed();
    virtual void LineEditBenamn_returnPressed();
    virtual void LineEditStartdatum_returnPressed();
    virtual void LineEditSlutdatum_returnPressed();
    virtual void LineEditBeskattAr_returnPressed();
    virtual void LineEditNestaVerNr_returnPressed();
    virtual void LineEditKontoplan_returnPressed();
    virtual void PushButtonOK_clicked();
    virtual void slotDataOnStderr();
    virtual void slotDataOnStdout();
    virtual void slotEndOfProcess();
    virtual void slotAbout();

protected:

protected slots:
    virtual void languageChange();
};

#endif // FRMADDBAR_H
