/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                          LSTBETVW  -  description
                             -------------------
		     version 0.2
    begin                : Lör 22 nov 2003
    modified          : Fre 16 febr 2007
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
	

void frmListBetalvillkor::init()
{
    qDebug("Start 1");
    PushButtonSluta->setFocus();
    frmListBetalvillkor::GetBetalvillkor();
    qDebug("Start 2");
}	
	
void frmListBetalvillkor::GetBetalvillkor()	
{
	const char *userp = getenv("USER");
               QString usr(userp);
	
                inrad="";
	errorrad="";
	
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX huvudprogram
	process->addArgument(usr);		// userid
	process->addArgument( "BETLST");	// OLFIX funktion
	
//	fprintf(stderr,"Starta STYRMAN/BETLST! %s\n",usr.latin1());
	
	frmListBetalvillkor::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmListBetalvillkor::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );	
	frmListBetalvillkor::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );	    
 
	if ( !process->start() ) {
                // error handling
	    fprintf(stderr,"Problem starta STYRMAN/BETLST!\n");
	    QMessageBox::warning( this, "Start av BETLST ",
                            "Kan inte starta STYRMAN/BETLST!\n"
                            );
        }
}
	
void frmListBetalvillkor::slotEndOfProcess()
{
    QString listrad="";
//	rad=&inrad;
//	inrad.latin1();
  char *pos1;
  char *pos2;
  char tmp[MAXSTRING];
  char *tmppek;
  int j,k,l,m;
  char antrad[6]="";
  char betvilkor[4]="";
  char dagar[4]="";
  char beskrivning[41]="";

//    qDebug("inrad=%s",inrad.latin1());
    QListViewItem* item;
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "LSTBETVW","ERROR!\n"+errorrad);
	errorrad="";
	i = -1;
    }
	 
    i = inrad.find( QRegExp("OK: NR_0_"), 0 );
    if (i != -1) {
	QMessageBox::information( this, "LSTBETVW","Betalningsvillkorregistret innehåller inga poster!\n");
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
	    for(j = m; j < sizeof(betvilkor) + m; j++){
		if(tmp[j] != *("_")){
		    betvilkor[l]=tmp[j];
		    l++;
		}else{
		    betvilkor[l] = *("\0");
		    j=sizeof(betvilkor) + m;
		}
	    }
	    m=m+l+2;			// position för dagar
	    l=0;
	    for(j = m; j < sizeof(dagar) + m; j++){
		if(tmp[j] != *("_")){
		    dagar[l]=tmp[j];
		    l++;
		}else{
		    dagar[l] = *("\0");
		    j=sizeof(dagar) + m;
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
	    item = new QListViewItem(ListView1,betvilkor,dagar,beskrivning);
// 	 	rensa betalvilkor,  dagar  och beskrivning
	    for (l=0;l<sizeof(betvilkor);l++)
		betvilkor[l]=*("\0");
	    for (l=0;l<sizeof(dagar);l++)
		dagar[l]=*("\0");
	    for (l=0;l<sizeof(beskrivning);l++)
		beskrivning[l]=*("\0");	
//	 	rensa listrad 
	}
    }
	    listrad.remove(0,70);   
}

void frmListBetalvillkor::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmListBetalvillkor::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmListBetalvillkor::slotReloadBetalvillkor()
{
    ListView1->clear();
    frmListBetalvillkor::GetBetalvillkor();
}
