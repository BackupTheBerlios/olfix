/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                          LSTFORW  -  description
                             -------------------
		     version 0.1
    begin                : Ons 10 nov 2004
    copyright            : (C) 2004 by Jan Pihlgren
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
#define MAXSTRING 5000	

	QProcess* process;
	QString inrad;
	QString errorrad;
	QString* rad;
	

void frmListForetag::init()
{
    PushButtonSluta->setFocus();
    frmListForetag::GetForetag();
}	
	
void frmListForetag::GetForetag()	
{
	const char *userp = getenv("USER");
            QString usr(userp);
	
	process = new QProcess();
	process->addArgument("./STYRMAN");     // OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "FORLST");	// OLFIX funktion
/*            fprintf(stdout,"1 .Läser från STYRMAN/FORLST! %s\n",usr.latin1());	*/	
	frmListForetag::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmListForetag::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );	
	frmListForetag::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );	    
 
	if ( !process->start() ) {
                // error handling
	    fprintf(stderr,"Problem starta STYRMAN/FORLST!\n");
	    QMessageBox::warning( this, "Start av FORLST ",
                            "Kan inte starta STYRMAN/FORLST!\n"
                            );
        }
}
	
	
void frmListForetag::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
/*      fprintf(stdout,"2 .Läser från STYRMAN/FORLST! %s\n",inrad.latin1());	*/
}

void frmListForetag::slotEndOfProcess()
{
       QListViewItem* item;
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "LSTFORW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
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
    char antrad[6]="";
    char dbnr[9]="";
    char dbnamn[61]="";

    tmppek=tmp;
    qstrcpy(tmp,inrad);
    pos1=strstr(tmp,"NR_");
    pos2=strstr(tmp,"_:");
    i=pos2-pos1;
    m=i+2;		// startposition för första dbnr.
//    fprintf(stdout,"i=%d  m=%d",i,m);
    k=0;
    for (j=3;j<i;j++){
	antrad[k]=tmp[j];
	k++;
    };
    i=atoi(antrad);		// i = antal poster
    for (k = 1;k <= i; k++){	// gå igenom alla raderna / posterna
	l=0;
	for(j = m; j < sizeof(dbnr) + m; j++){
	    if(tmp[j] != *("_")){
		dbnr[l]=tmp[j];
		l++;
	    }else{
		dbnr[l] = *("\0");
		j=sizeof(dbnr) + m;
	    }
	}
//	fprintf(stdout,"%s  ",user);
	m=m+l+2;	// position för dbnamn
	l=0;
	for(j = m; j < sizeof(dbnamn) + m; j++){
	    if(tmp[j] != *("_")){
		dbnamn[l]=tmp[j];
		l++;
	    }else{
		dbnamn[l] = *("\0");
		j=sizeof(dbnamn) + m;
	    }
	}
//	fprintf(stdout,"%s  ",dbnamn);
	m=m+l+2;
	item = new QListViewItem(ListView1,dbnr,dbnamn);
// 	 rensa user,namn,avd och grupp 
  	for (l=0;l<sizeof(dbnr);l++)
		dbnr[l]=*("\0");
	for (l=0;l<sizeof(dbnamn);l++)
		dbnamn[l]=*("\0");
//	 rensa listrad 
	listrad.remove(0,70);
    }   
}


void frmListForetag::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
//	qWarning( "slotDataOnErrout: Userid=%s \n", inrad.latin1() );
    }
}

void frmListForetag::slotReloadForetag()
{
    ListView1->clear();
    frmListForetag::GetForetag();
}
