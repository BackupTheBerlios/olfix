/****************************************************************************
** Form interface generated from reading ui file 'frmlistuser.ui'
**
** Created: tis maj 27 06:52:02 2003
**      by: The User Interface Compiler ($Id: frmlistuser.h,v 1.2 2003/09/28 08:27:53 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef FRMLISTUSER_H
#define FRMLISTUSER_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QListView;
class QListViewItem;
class QPushButton;

class frmListUser : public QWidget
{
    Q_OBJECT

public:
    frmListUser( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~frmListUser();

    QPushButton* PushButtonSluta;
    QPushButton* PushButtonAgain;
    QListView* ListView1;

public slots:
    virtual void GetUser();
    virtual void init();
    virtual void slotDataOnStdout();
    virtual void slotEndOfProcess();
    virtual void slotDataOnStderr();
    virtual void slotReloadUser();

protected:

protected slots:
    virtual void languageChange();
};

#endif // FRMLISTUSER_H
