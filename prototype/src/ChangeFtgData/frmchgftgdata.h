/****************************************************************************
** Form interface generated from reading ui file 'frmchgftgdata.ui'
**
** Created: tis apr 22 07:07:53 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef FRMCHGFTGDATA_H
#define FRMCHGFTGDATA_H

#include <qvariant.h>
#include <qwidget.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QLabel;
class QLineEdit;
class QListView;
class QListViewItem;
class QPushButton;

class frmChgFtgData : public QWidget
{ 
    Q_OBJECT

public:
    frmChgFtgData( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~frmChgFtgData();

    QLabel* TextLabel1;
    QPushButton* PushButtonGet;
    QPushButton* PushButtonOK;
    QListView* ListView1;
    QPushButton* PushButtonUpdate;
    QLineEdit* LineEditPosttyp;


public slots:
    virtual void init();
    virtual void slotGetPosttyp();
    virtual void PushButtonGet_clicked();
    virtual void slotGetFtgData( QString posttyp );
    virtual void slotDataOnStdout();
    virtual void slotDataOnStderr();
    virtual void slotEndOfProcess();
    virtual void slotGetADR1();
    virtual void slotGetADR2();
    virtual void slotGetADR3();
    virtual void slotGetFTGNR();
    virtual void slotGetTFN1();
    virtual void slotGetTFN2();
    virtual void slotGetTFAX();
    virtual void slotGetEML1();
    virtual void slotGetMOMS1();
    virtual void slotLineEditMoms1_returnPressed();
    virtual void slotGetPosttyper();
    virtual void slotGetPostEndOfProcess();
    virtual void ListView1_clicked( QListViewItem * item );
    virtual void slotUpdFtgData( QString posttyp, QString ftgdata );
    virtual void slotUpdateEndOfProcess();
    virtual void PushButtonUpdate_clicked();

};

#endif // FRMCHGFTGDATA_H
