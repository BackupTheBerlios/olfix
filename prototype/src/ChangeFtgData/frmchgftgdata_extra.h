/****************************************************************************
**	frmchgdata_extra.h
** Created: Sön apr 20
**      by: Jan Pihlgren, jan@pihlgren.se
**
****************************************************************************/
#ifndef FRMCHGFTGDATA_EXTRA_H
#define FRMCHGFTGDATA_EXTRA_H

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

    QLabel* TextLabelEmail;
    QLineEdit* LineEditMoms1;


public slots:

};

#endif // FRMCHGFTGDATA_EXTRA_H
