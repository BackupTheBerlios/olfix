/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                          LSTPKDW -  description
                             -------------------
		     version 0.2
    begin                   : Ons  1 dec   2004
    Modified	: Tis  8 mars 2005
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
	

void frmListProdkod::init()
{
    PushButtonSluta->setFocus();
    frmListProdkod::GetProdkod();
}	
	
void frmListProdkod::GetProdkod()	
{
	const char *userp = getenv("USER");
            QString usr(userp);
	
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX huvudprogram
	process->addArgument(usr);		// userid
	process->addArgument( "PKDLST");	// OLFIX funktion
	
//	fprintf(stderr,"Starta STYRMAN/BETLST! %s\n",user);
	
	frmListProdkod::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmListProdkod::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );	
	frmListProdkod::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );	    
 
	if ( !process->start() ) {
                // error handling
	    QMessageBox::warning( this, "Start av PKDLST ",
                            "Kan inte starta STYRMAN/PKDLST!\n"
                            );
        }
}
	
void frmListProdkod::slotEndOfProcess()
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
  char prodkod[6]="";
  char beskrivning[31]="";
  char momskod[6]="";

//    qDebug("inrad=%s",inrad.latin1());
    QListViewItem* item;
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "LSTPKDW","ERROR!\n"+errorrad);
	errorrad="";
	i = -1;
    }
	 
    i = inrad.find( QRegExp("OK: NR_0_"), 0 );
    if (i != -1) {
	QMessageBox::information( this, "LSTPKDW","Produkgruppsregistret innehåller inga poster!\n");
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
	    for(j = m; j < sizeof(prodkod) + m; j++){
		if(tmp[j] != *("_")){
		    prodkod[l]=tmp[j];
		    l++;
		}else{
		    prodkod[l] = *("\0");
		    j=sizeof(prodkod) + m;
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
	    m=m+l+2;			// position för momskod
	    l=0;
	    for(j = m; j < sizeof(momskod) + m; j++){
		if(tmp[j] != *("_")){
		    momskod[l]=tmp[j];
		    l++;
		}else{
		    momskod[l] = *("\0");
		    j=sizeof(momskod) + m;
		}
	    }
	
	    m=m+l+2;
	    item = new QListViewItem(ListView1,prodkod,beskrivning,momskod);
// 	 	rensa produktkod, beskrivning  och momskod
	    for (l=0;l<sizeof(prodkod);l++)
		prodkod[l]=*("\0");
	    for (l=0;l<sizeof(beskrivning);l++)
		beskrivning[l]=*("\0");	
	    for (l=0;l<sizeof(momskod);l++)
		momskod[l]=*("\0");	
	    
	    //	 	rensa listrad 
	}
    }
	    listrad.remove(0,70);   
}

void frmListProdkod::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmListProdkod::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmListProdkod::slotReloadProdkod()
{
    ListView1->clear();
/*    qDebug("Kör Reload");		*/
    inrad="";
    errorrad="";
    frmListProdkod::GetProdkod();
}
