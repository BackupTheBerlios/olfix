/****************************************************************************
** Form interface generated from reading ui file 'frmlevfaktattbetala.ui'
**
** Created: ons aug 20 21:36:01 2003
**      by: The User Interface Compiler ($Id: frmlevfaktattbetala.h,v 1.1 2003/09/28 08:09:37 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef FRMLEVFAKTATTBETALA_H
#define FRMLEVFAKTATTBETALA_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QLabel;
class QLineEdit;
class QPushButton;

class frmLevFaktAttBetala : public QWidget
{
    Q_OBJECT

public:
    frmLevFaktAttBetala( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~frmLevFaktAttBetala();

    QLabel* textLabel1;
    QPushButton* pushButtonOK;
    QPushButton* pushButtonAvbryt;
    QLineEdit* lineEditExpireDate;

public slots:
    virtual void slotlineEditExpireDate_returnPressed();
    virtual void slotpushButtonOK_clicked();
    virtual void slotSkapRapportfil();
    virtual void slotEndOfProcess();
    virtual void slotFileRemove( QString filnamn );
    virtual void slotDataOnStdout();
    virtual void slotDataOnStderr();
    virtual void slotCreateHeader();

protected:

protected slots:
    virtual void languageChange();
private:
    void init();

};

#endif // FRMLEVFAKTATTBETALA_H
