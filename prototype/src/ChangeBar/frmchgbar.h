/****************************************************************************
** Form interface generated from reading ui file 'frmchgbar.ui'
**
** Created: fre jun 6 06:43:51 2003
**      by: The User Interface Compiler ($Id: frmchgbar.h,v 1.2 2003/09/28 06:38:37 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef FRMCHGBAR_H
#define FRMCHGBAR_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QLabel;
class QLineEdit;
class QPushButton;

class frmChgBar : public QWidget
{
    Q_OBJECT

public:
    frmChgBar( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~frmChgBar();

    QLabel* TextLabel5;
    QLabel* TextLabel02;
    QLabel* TextLabel03;
    QLabel* TextLabel1;
    QPushButton* PushButtonOK;
    QPushButton* PushButtonQuit;
    QLabel* TextLabel2;
    QLabel* TextLabel3;
    QLineEdit* LineEditNestaVerNr;
    QLineEdit* LineEditSenVerDat;
    QLineEdit* LineEditKontoplan;
    QLabel* TextLabel9_5_2;
    QLineEdit* LineEditBeskattAr;
    QLabel* TextLabel9_4;
    QLineEdit* LineEditSlutdatum;
    QLabel* TextLabel9_5;
    QLabel* TextLabel9_3;
    QLineEdit* LineEditStartdatum;
    QLineEdit* LineEditBenamn;
    QLineEdit* LineEditBar;
    QLabel* TextLabel9;
    QLabel* TextLabel01;
    QLabel* TextLabel4;

public slots:
    virtual void init();
    virtual void LineEditBar_returnPressed();
    virtual void slotChgBar();
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
    virtual void slotGetBar();
    virtual void slotGetDataOnStderr();
    virtual void slotGetDataOnStdout();
    virtual void slotGetEndOfProcess();

protected:

protected slots:
    virtual void languageChange();
};

#endif // FRMCHGBAR_H
