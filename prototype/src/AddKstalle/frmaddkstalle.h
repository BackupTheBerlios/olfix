/****************************************************************************
** Form interface generated from reading ui file 'frmaddkstalle.ui'
**
** Created: tor mar 20 07:53:29 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef FRMADDKSTALLE_H
#define FRMADDKSTALLE_H

#include <qvariant.h>
#include <qwidget.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QLabel;
class QLineEdit;
class QPushButton;

class frmAddKstalle : public QWidget
{ 
    Q_OBJECT

public:
    frmAddKstalle( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~frmAddKstalle();

    QLabel* TextLabelArid;
    QLabel* TextLabelKstalle;
    QLabel* TextLabelBenamn;
    QPushButton* PushButtonQuit;
    QLineEdit* LineEditBar;
    QLineEdit* LineEditKstalle;
    QLineEdit* LineEditBenamn;
    QPushButton* PushButtonOK;


public slots:
    virtual void init();
    virtual void slotBarEntered();
    virtual void slotKstalleEntered();
    virtual void slotBenamnEntered();
    virtual void slotPushButtonOK_clicked();
    virtual void slotAddKstalle();
    virtual void slotDataOnStdout();
    virtual void slotDataOnStderr();
    virtual void slotEndOfProcess();

};

#endif // FRMADDKSTALLE_H
