/****************************************************************************
** Form interface generated from reading ui file 'frmsaldolista.ui'
**
** Created: lör aug 23 09:52:02 2003
**      by: The User Interface Compiler ($Id: frmsaldolista.h,v 1.1 2003/09/28 08:39:42 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef FRMSALDOLISTA_H
#define FRMSALDOLISTA_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QButtonGroup;
class QLabel;
class QLineEdit;
class QPushButton;
class QRadioButton;

class frmSaldolista : public QWidget
{
    Q_OBJECT

public:
    frmSaldolista( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~frmSaldolista();

    QLabel* textLabel1;
    QLabel* textLabel2;
    QLabel* textLabelDatum;
    QLabel* textLabel4;
    QPushButton* pushButtonOK;
    QPushButton* pushButtonAvbryt;
    QLineEdit* lineEditBar;
    QButtonGroup* buttonGroup1;
    QLabel* textLabel2_2;
    QLabel* textLabel3;
    QRadioButton* radioButtonCSV;
    QRadioButton* radioButtonPrint;
    QLabel* textLabel4_2;
    QLabel* textLabel5;

public slots:
    virtual void slotlineEditBar_returnPressed();
    virtual void radioButtonCSV_toggled( bool );
    virtual void radioButtonPrint_toggled( bool );
    virtual void slotpushButtonOK_clicked();
    virtual void slotGetData();
    virtual void slotDataOnStdout();
    virtual void slotDataOnStderr();
    virtual void slotEndOfProcess();
    virtual void slotCreateHeader();
    virtual void slotFileRemove( QString filnamn );

protected:

protected slots:
    virtual void languageChange();
private:
    void init();

};

#endif // FRMSALDOLISTA_H
