/****************************************************************************
** Form interface generated from reading ui file 'levresk.ui'
**
** Created: mån jun 30 07:23:27 2003
**      by: The User Interface Compiler ($Id: levresk.h,v 1.1 2003/09/28 08:20:33 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef FRMLEVRESK_H
#define FRMLEVRESK_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QGroupBox;
class QLabel;
class QListView;
class QListViewItem;

class frmLevResk : public QWidget
{
    Q_OBJECT

public:
    frmLevResk( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~frmLevResk();

    QLabel* TextLabel2;
    QGroupBox* GroupBox1;
    QListView* ListView1;
    QLabel* TextLabel1;
    QLabel* TextLabelDatum;

public slots:
    virtual void slotGetLevReskPost();
    virtual void slotDataOnStdout();
    virtual void slotDataOnStderr();
    virtual void slotEndOfProcess();

protected:
    QGridLayout* frmLevReskLayout;
    QGridLayout* GroupBox1Layout;

protected slots:
    virtual void languageChange();
private:
    void init();

};

#endif // FRMLEVRESK_H
