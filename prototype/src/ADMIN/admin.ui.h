/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
#include <qmessagebox.h>
#include <qprocess.h>
#include <qdir.h>
#include <stdlib.h>


void ADMIN::rightAddSlot()
{

}

void ADMIN::rightDeleteSlot()
{

}


	QProcess* process;

void ADMIN::rightListSlot()
{
	process = new QProcess();
	process->addArgument( "/home/jan/Utveckling/OLFIX_W/bin/LSTRGTW");
        if ( !process->start() ) {
            // error handling
	    fprintf(stderr,"Problem starta LSTRGTW!\n");
	    QMessageBox::warning( this, "Start av LSTRGTW ",
                            "Kan inte starta LSTRGTW!\n"
                            );
        }

}

void ADMIN::userAddSlot()
{

}

void ADMIN::userChangeSlot()
{

}

void ADMIN::userDeleteSlot()
{

}

void ADMIN::userListSlot()
{
	process = new QProcess();
	process->addArgument( "/home/jan/Utveckling/OLFIX_W/bin/LSTUSRW");
        if ( !process->start() ) {
            // error handling
//	    fprintf(stderr,"Problem starta ListRights!\n");
	    QMessageBox::warning( this, "Start av LSTUSRW ",
                            "Kan inte starta LSTUSRW!\n"
                            );
        }

}
