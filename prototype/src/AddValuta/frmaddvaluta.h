/****************************************************************************
** Form interface generated from reading ui file 'frmaddvaluta.ui'
**
** Created: tor mar 20 07:58:13 2003
**      by:  The User Interface Compiler (uic)
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
    QPushButton* PushButtonQuit;
    QLineEdit* LineEditBeteck;
    QLineEdit* LineEditValuta;
    QLineEdit* LineEditSalj;
    QPushButton* PushButtonOK;


public slots:
    virtual void init();
    virtual void slotAddValuta();
    virtual void slotValutaEntered();
    virtual void slotBeteckningEntered();
    virtual void slotLandEntered();
    virtual void slotKopEntered();
    virtual void slotSaljEntered();
    virtual void slotDataOnStdout();
    virtual void slotDataOnStderr();
    virtual void slotEndOfProcess();
    virtual void slotPushButtonOK_clicked();

};

#endif // FRMADDVALUTA_H
