/****************************************************************************
** Form interface generated from reading ui file 'frmaddlevplats.ui'
**
** Created: ons sep 10 10:54:10 2003
**      by: The User Interface Compiler ($Id: frmaddlevplats.h,v 1.1 2003/09/28 06:21:29 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef FRMADDLEVPLATS_H
#define FRMADDLEVPLATS_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QLabel;
class QLineEdit;
class QPushButton;

class frmAddLevplats : public QWidget
{
    Q_OBJECT

public:
    frmAddLevplats( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~frmAddLevplats();

    QLabel* textLabel1_2_3;
    QLabel* textLabel2_2;
    QPushButton* pushButtonAvbryt;
    QPushButton* pushButtonOK;
    QLineEdit* lineEditKundID;
    QLineEdit* lineEditLevPlatsNr;
    QLineEdit* lineEditLevAdress;
    QLabel* textLabel1_2;
    QLabel* textLabel1_2_5;
    QLineEdit* lineEditPostnr;
    QLineEdit* lineEditPostAdress;
    QLineEdit* lineEditLand;
    QLabel* textLabel6;
    QLabel* textLabel1_2_7;
    QLabel* textLabel5;
    QLabel* textLabel1_2_6;
    QLabel* textLabel4;
    QLabel* textLabel3;
    QLabel* textLabel1_2_4;
    QLabel* textLabel2;
    QLabel* textLabel1_2_2;
    QLabel* textLabel1;

public slots:
    virtual void lineEditKundID_returnPressed();
    virtual void lineEditLevPlatsNr_returnPressed();
    virtual void lineEditLevAdress_returnPressed();
    virtual void lineEditPostnr_returnPressed();
    virtual void lineEditPostAdress_returnPressed();
    virtual void lineEditLand_returnPressed();
    virtual void pushButtonOK_clicked();
    virtual void AddStandardLevPlats();
    virtual void slotPlatsEndOfProcess();
    virtual void slotDataOnStdout();
    virtual void slotDataOnStderr();

protected:

protected slots:
    virtual void languageChange();
private:
    void init();

};

#endif // FRMADDLEVPLATS_H
