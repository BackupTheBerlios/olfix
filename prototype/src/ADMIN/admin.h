/****************************************************************************
** Form interface generated from reading ui file 'admin.ui'
**
** Created: tis jan 7 07:02:25 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef ADMIN_H
#define ADMIN_H

#include <qvariant.h>
#include <qmainwindow.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QAction;
class QActionGroup;
class QToolBar;
class QPopupMenu;

class ADMIN : public QMainWindow
{ 
    Q_OBJECT

public:
    ADMIN( QWidget* parent = 0, const char* name = 0, WFlags fl = WType_TopLevel );
    ~ADMIN();

    QMenuBar *menubar;
    QPopupMenu *fileMenu;
    QPopupMenu *editMenu;
    QAction* userAddAction;
    QAction* userChangeAction;
    QAction* userDeleteAction;
    QAction* userListAction;
    QAction* rightAddAction;
    QAction* rightDeleteAction;
    QAction* rightListAction;
    QAction* rightListOneUserAction;


public slots:
    virtual void rightAddSlot();
    virtual void rightDeleteSlot();
    virtual void rightListSlot();
    virtual void userAddSlot();
    virtual void userChangeSlot();
    virtual void userDeleteSlot();
    virtual void userListSlot();

};

#endif // ADMIN_H
