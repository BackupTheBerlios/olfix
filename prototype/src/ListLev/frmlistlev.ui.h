/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                          LSTLEVW  -  description
                             -------------------
		     version 0.1
    begin                : S�n 7 dec 2003
    copyright            : (C) 2003 by Jan Pihlgren
    email                : jan@pihlgren.se
 ***************************************************************************/
/*****************************************************************
 *					                                                 *
 *   This program is free software; you can redistribute it and/or modify 	 *
 *   it under the terms of the GNU General Public License as published by       *
 *   the Free Software Foundation; either version 2 of the License, or     	 *
 *   (at your option) any later version.                                   		 *
 *                                                                         				 *
 *********************************************** *****************/

#include <qmessagebox.h>
#include <qprocess.h>
#include <qdir.h>
#include <stdlib.h>
#include <qstring.h>		
#include <qfile.h>
#include <qregexp.h>
#include <qfont.h>
#include <qlistview.h>
#include <qclipboard.h> 
#define MAXSTRING 5000

	QProcess* process;
	QString inrad;
	QString errorrad;
	QString* rad;
	
void frmListLev::GetLev()	
{
	const char *userp = getenv("USER");
            QString usr(userp);

	
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "LEVLST");	// OLFIX funktion
	
	frmListLev::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmListLev::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );	
	frmListLev::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );	    
 
	if ( !process->start() ) {
                // error handling
	    fprintf(stderr,"Problem starta STYRMAN/LEVLST!\n");
	    QMessageBox::warning( this, "Start av LEVLST ",
                            "Kan inte starta STYRMAN/LEVLST!\n"
                            );
        }
}

void frmListLev::init()
{
    PushButtonSluta->setFocus();
    frmListLev::GetLev();
}	
	
void frmListLev::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmListLev::slotEndOfProcess()
{
    QListViewItem* item;
    int i;
    ListView1->setSorting(1,TRUE);
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "LSTLEVW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
     }
	 
    i = inrad.find( QRegExp("OK: NR_0_"), 0 );
         if (i != -1) {
	QMessageBox::information( this, "LSTLEVW",
		"Leverant�rsregistret inneh�ller inga poster!\n"
	);
	i = -1;
     }
	 
    QString listrad;
    rad=&inrad;
    inrad.latin1();
    char *pos1;
    char *pos2;
    char tmp[MAXSTRING];
    char *tmppek;
    int j,k,l,m;
//    int antrad;
    char antrad[6]="";
    char levnr[11]="";
    char namn[61]="";

    tmppek=tmp;
    qstrcpy(tmp,inrad);
    pos1=strstr(tmp,"OK: NR_");	// 7 tecken l�ngt
    pos2=strstr(tmp,"_:");
    i=pos2-pos1;
    m=i+2;		// startposition f�r f�rsta levnr.
    
//    qDebug("i=%d  m=%d",i,m);
    
    k=0;
    for (j=7;j<i;j++){	
	antrad[k]=tmp[j];
	k++;
    };
    i=atoi(antrad);		// i = antal poster
    
//    qDebug("antrad=%s",antrad);
    
    for (k = 1;k <= i; k++){	// g� igenom alla raderna / posterna
	l=0;
	for(j = m; j < sizeof(levnr) + m; j++){
	    if(tmp[j] != *("_")){
		levnr[l]=tmp[j];
		l++;
	    }else{
		levnr[l] = *("\0");
		j=sizeof(levnr) + m;
	    }
	}
//	qDebug("%s  ",levnr);
	m=m+l+2;	// position f�r namn
	l=0;
	for(j = m; j < sizeof(namn) + m; j++){
	    if(tmp[j] != *("_")){
		namn[l]=tmp[j];
		l++;
	    }else{
		namn[l] = *("\0");
		j=sizeof(namn) + m;
	    }
	}
//	qDebug("%s  ",namn);
	m=m+l+2;
	item = new QListViewItem(ListView1,levnr,namn);
// 	 rensa levnr och namn 
  	for (l=0;l<sizeof(levnr);l++)
		levnr[l]=*("\0");
	for (l=0;l<sizeof(namn);l++)
		namn[l]=*("\0");
//	 rensa listrad 
	listrad.remove(0,80);
    }   
}

void frmListLev::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
//	qWarning( "slotDataOnErrout: Userid=%s \n", inrad.latin1() );
    }
}

void frmListLev::slotReloadLev()
{
    ListView1->clear();
    frmListLev::GetLev();
}



