/****************************************************************************
** $Id: helpwindow.h,v 1.2 2004/11/07 07:33:45 janpihlgren Exp $
**
** Copyright (C) 1992-2000 Trolltech AS.  All rights reserved.
**
** This file is part of an example program for Qt.  This example
** program may be used, distributed and modified without limitation.
**
** Modified: 2004-11-07 Jan Pihlgren
*****************************************************************************/

#ifndef HELPWINDOW_H
#define HELPWINDOW_H

#include <qmainwindow.h>
#include <qtextbrowser.h>
#include <qstringlist.h>
#include <qmap.h>
#include <qdir.h>
#include <qfile.h> 

class QComboBox;
class QPopupMenu;

class HelpWindow : public QMainWindow
{
    Q_OBJECT
public:
    HelpWindow( const QString& home_,  const QString& path, QWidget* parent = 0, const char *name=0 );
    ~HelpWindow();

private slots:
    void sourceChanged( const QString& );

private:
    QTextBrowser* browser;
    QComboBox *pathCombo;
};

#endif
