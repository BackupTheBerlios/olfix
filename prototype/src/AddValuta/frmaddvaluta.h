/****************************************************************************
** Form interface generated from reading ui file 'frmaddvaluta.ui'
**
** Created: fre jun 6 06:33:01 2003
**      by: The User Interface Compiler ($Id: frmaddvaluta.h,v 1.2 2003/09/28 06:25:24 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef FRMADDVALUTA_H
#define FRMADDVALUTA_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QLabel;
class QLineEdit;
class QPushButton;

class frmAddValuta : public QWidget
{
    Q_OBJECT

public:
    frmAddValuta( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~frmAddValuta();

    QLabel* TextLabelSalj;
    QLabel* TextLabelKop;
    QLabel* TextLabelBeteckn;
    QLabel* TextLabelValuta;
    QLabel* TextLabelLand;
    QLineEdit* LineEditKop;
    QLineEdit* LineEditLand;
    QLineEdit* LineEditValuta;
    QLineEdit* LineEditSalj;
    QPushButton* PushButtonOK;
    QLineEdit* LineEditBeteck;
    QPushButton* PushButtonQuit;

public slots:
    virtual void init();
    virtual void slotAddValuta();
    virtual void slotValuta_lostFocus();
    virtual void slotValutaEntered();
    virtual void slotBeteckning_lostFocus();
    virtual void slotBeteckningEntered();
    virtual void slotLand_lostFocus();
    virtual void slotLandEntered();
    virtual void slotKop_lostFocus();
    virtual void slotKopEntered();
    virtual void slotSalj_lostFocus();
    virtual void slotSaljEntered();
    virtual void slotDataOnStdout();
    virtual void slotDataOnStderr();
    virtual void slotEndOfProcess();

protected:

protected slots:
    virtual void languageChange();
};

#endif // FRMADDVALUTA_H
