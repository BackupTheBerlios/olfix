/****************************************************************************
** Form interface generated from reading ui file 'ktorapport.ui'
**
** Created: tor mar 20 08:20:43 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef FRMKTORAPPORT_H
#define FRMKTORAPPORT_H

#include <qvariant.h>
#include <qwidget.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QGroupBox;
class QLabel;
class QLineEdit;
class QListView;
class QListViewItem;

class frmKtoRapport : public QWidget
{ 
    Q_OBJECT

public:
    frmKtoRapport( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~frmKtoRapport();

    QLabel* TextLabel2;
    QGroupBox* GroupBox1;
    QListView* ListView1;
    QLabel* TextLabel1_2;
    QLabel* TextLabel1;
    QLineEdit* LineEditBar;
    QLabel* TextLabelDatum;


public slots:
    virtual void init();
    virtual void slotLineEditBar_returnPressed();
    virtual void slotGetVerrader();
    virtual void slotCheckBar();
    virtual void slotBARCHKEndOfProcess();
    virtual void slotDataOnStdout();
    virtual void slotDataOnStderr();
    virtual void slotKTORPTEndOfProcess();

protected:
    QGridLayout* frmKtoRapportLayout;
    QGridLayout* GroupBox1Layout;
};

#endif // FRMKTORAPPORT_H
