/****************************************************************************
** Form interface generated from reading ui file 'frmchgvaluta.ui'
**
** Created: tor mar 20 08:07:37 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef FRMCHGVALUTA_H
#define FRMCHGVALUTA_H

#include <qvariant.h>
#include <qwidget.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QLabel;
class QLineEdit;
class QPushButton;

class frmChgValuta : public QWidget
{ 
    Q_OBJECT

public:
    frmChgValuta( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~frmChgValuta();

    QLabel* TextLabelBeteck;
    QLineEdit* LineEditBeteck;
    QPushButton* PushButtonQuit;
    QLineEdit* LineEditLand;
    QLineEdit* LineEditKop;
    QLineEdit* LineEditSalj;
    QLabel* TextLabelValuta;
    QLabel* TextLabelLand;
    QLabel* TextLabelKop;
    QLabel* TextLabelSalj;
    QLineEdit* LineEditValuta;
    QPushButton* PushButtonGet;
    QPushButton* PushButtonUpdate;


public slots:
    virtual void init();
    virtual void slotGetValuta();
    virtual void slotChgValuta();
    virtual void slotValutaEntered();
    virtual void slotBeteckningEntered();
    virtual void slotLandEntered();
    virtual void slotKopEntered();
    virtual void slotSaljEntered();
    virtual void slotPushButtonGet_clicked();
    virtual void slotValDataOnStdout();
    virtual void slotValDataOnStderr();
    virtual void slotEndOfValProcess();
    virtual void slotChgDataOnStdout();
    virtual void slotChgDataOnStderr();
    virtual void slotEndOfChgProcess();

};

#endif // FRMCHGVALUTA_H
