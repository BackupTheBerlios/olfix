/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                          LSTLEVSW -  description
                             -------------------
		     version 0.1
    begin                : Mån 9  febr 2004
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
#define MAXSTRING 5000

	QProcess* process;
	QString inrad;
	QString errorrad;
	QString* rad;
	

void frmListLevsett::init()
{
    PushButtonSluta->setFocus();
    frmListLevsett::GetLevsett();
}	
	
void frmListLevsett::GetLevsett()	
{
	const char *userp = getenv("USER");
            QString usr(userp);
	
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX huvudprogram
	process->addArgument(usr);		// userid
	process->addArgument( "LEVSLST");	// OLFIX funktion
	
//	fprintf(stderr,"Starta STYRMAN/BETLST! %s\n",user);
	
	frmListLevsett::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmListLevsett::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );	
	frmListLevsett::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );	    
 
	if ( !process->start() ) {
                // error handling
	    QMessageBox::warning( this, "Start av LEVSLST ",
                            "Kan inte starta STYRMAN/LEVSLST!\n"
                            );
        }
}
	
void frmListLevsett::slotEndOfProcess()
{
    QString listrad;
//	rad=&inrad;
//	inrad.latin1();
  char *pos1;
  char *pos2;
  char tmp[MAXSTRING];
  char *tmppek;
  int j,k,l,m;
  char antrad[6]="";
  char levsett[4]="";
  char beskrivning[41]="";

//    qDebug("inrad=%s",inrad.latin1());
    QListViewItem* item;
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "LSTLEVSW","ERROR!\n"+errorrad);
	errorrad="";
	i = -1;
    }
	 
    i = inrad.find( QRegExp("OK: NR_0_"), 0 );
    if (i != -1) {
	QMessageBox::information( this, "LSTLEVSW","Leveranssättsregistret innehåller inga poster!\n");
	i = -1;
    }else{	 
	tmppek=tmp;
	qstrcpy(tmp,inrad);
	pos1=strstr(tmp,"OK: NR_");
	pos2=strstr(tmp,"_:");
	i=pos2-pos1;
	m=i+2;		// startposition för betalningsvillkor
	k=0;
	for (j=7;j<i;j++){
	    antrad[k]=tmp[j];
	    k++;
	};
	i=atoi(antrad);				// i = antal poster
	//    qDebug("antalrader=%d",i);
    
	for (k = 1;k <= i; k++){			// gå igenom alla raderna / posterna
	    l=0;
	    for(j = m; j < sizeof(levsett) + m; j++){
		if(tmp[j] != *("_")){
		    levsett[l]=tmp[j];
		    l++;
		}else{
		    levsett[l] = *("\0");
		    j=sizeof(levsett) + m;
		}
	    }
	    m=m+l+2;			// position för beskrivning
	    l=0;
	    for(j = m; j < sizeof(beskrivning) + m; j++){
		if(tmp[j] != *("_")){
		    beskrivning[l]=tmp[j];
		    l++;
		}else{
		    beskrivning[l] = *("\0");
		    j=sizeof(beskrivning) + m;
		}
	    }
	    m=m+l+2;
	    item = new QListViewItem(ListView1,levsett,beskrivning);
// 	 	rensa betalvilkor,  dagar  och beskrivning
	    for (l=0;l<sizeof(levsett);l++)
		levsett[l]=*("\0");
	    for (l=0;l<sizeof(beskrivning);l++)
		beskrivning[l]=*("\0");	
//	 	rensa listrad 
	}
    }
	    listrad.remove(0,70);   
}

void frmListLevsett::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmListLevsett::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmListLevsett::slotReloadLevsett()
{
    ListView1->clear();
    frmListLevsett::GetLevsett();
}
