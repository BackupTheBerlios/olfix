/****************************************************************************
** Form interface generated from reading ui file 'frmrapportgen.ui'
**
** Created: ons aug 27 09:53:53 2003
**      by: The User Interface Compiler ($Id: frmrapportgen.h,v 1.1 2003/09/28 08:35:04 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef FRMRAPPORTGEN_H
#define FRMRAPPORTGEN_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QLabel;
class QPushButton;
class QTextEdit;

class frmRapportGen : public QDialog
{
    Q_OBJECT

public:
    frmRapportGen( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~frmRapportGen();

    QLabel* textLabel1;
    QPushButton* pushButtonOK;
    QPushButton* pushButtonQuit;
    QLabel* textLabel2;
    QLabel* textLabel3;
    QLabel* textLabel1_2;
    QLabel* textLabelExempel;
    QTextEdit* textEditSQL;
    QPushButton* pushButtonGetFile;
    QPushButton* pushButtonSaveFile;
    QPushButton* pushButtonHelp;
    QPushButton* pushButtonClear;

public slots:
    virtual void init();
    virtual void slottextEditSQL_returnPressed();
    virtual void slottextEditSQL_TextChanged();
    virtual void slotpushButtonOK_clicked();
    virtual void slotCreateTmpFile();
    virtual void slotEndOfProcess();
    virtual void slotDataOnStdout();
    virtual void slotDataOnStderr();
    virtual void slotFileRemove( QString filnamn );
    virtual void GetFileDialog();
    virtual void slotGetQueryFile();
    virtual void SaveFileDialog();
    virtual void slotClearSqlQuery();
    virtual void slotHelp();

protected:

protected slots:
    virtual void languageChange();
};

#endif // FRMRAPPORTGEN_H
