/****************************************************************************
** Form interface generated from reading ui file 'frmlistkonto.ui'
**
** Created: tor mar 20 08:22:49 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef FRMLISTKONTO_H
#define FRMLISTKONTO_H

#include <qvariant.h>
#include <qwidget.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QLabel;
class QLineEdit;
class QListBox;
class QListBoxItem;
class QPushButton;

class frmListKonto : public QWidget
{ 
    Q_OBJECT

public:
    frmListKonto( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~frmListKonto();

    QPushButton* PushButtonSluta;
    QLabel* TextLabel1;
    QListBox* ListBox1;
    QLineEdit* LineEditBar;
    QPushButton* PushButtonAgain;
    QPushButton* PushButtonLista;


public slots:
    virtual void PushButtonLista_clicked();
    virtual void slotDataOnStdout();
    virtual void slotEndOfProcess();
    virtual void slotLineEditBarEntered();
    virtual void slotDataOnStderr();
    virtual void slotReloadKonto();

protected slots:
    virtual void init();

};

#endif // FRMLISTKONTO_H
