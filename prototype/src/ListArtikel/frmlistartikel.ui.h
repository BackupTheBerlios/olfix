/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                          LSTARW  -  description
                             -------------------
		     version 0.1
    begin                : Sön 22 nov 2003
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
	

void frmListArtikel::init()
{
    PushButtonSluta->setFocus();
    frmListArtikel::GetArtikel();
}	
	
void frmListArtikel::GetArtikel()	
{
	const char *userp = getenv("USER");
            QString usr(userp);
	
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX huvudprogram
	process->addArgument(usr);		// userid
	process->addArgument( "ARLST");	// OLFIX funktion
	
//	fprintf(stderr,"Starta STYRMAN/ARLST! %s\n",user);
	
	frmListArtikel::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmListArtikel::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );	
	frmListArtikel::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );	    
 
	if ( !process->start() ) {
                // error handling
	    fprintf(stderr,"Problem starta STYRMAN/ARLST!\n");
	    QMessageBox::warning( this, "Start av ARLST ",
                            "Kan inte starta STYRMAN/ARLST!\n"
                            );
        }
}
	
void frmListArtikel::slotEndOfProcess()
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
  char artikelnr[31]="";
  char benemn1[31]="";
  char benemn2[31]="";

//    qDebug("inrad=%s",inrad.latin1());
    QListViewItem* item;
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "LSTARW","ERROR!\n"+errorrad);
	errorrad="";
	i = -1;
    }
	 
    i = inrad.find( QRegExp("OK: NR_0_"), 0 );
    if (i != -1) {
	QMessageBox::information( this, "LSTARW","Betalningsvillkorregistret innehåller inga poster!\n");
	i = -1;
    }else{	 
	tmppek=tmp;
	qstrcpy(tmp,inrad);
	pos1=strstr(tmp,"OK: NR_");
	pos2=strstr(tmp,"_:");
	i=pos2-pos1;
	m=i+2;		// startposition för artikelnr
	k=0;
	for (j=7;j<i;j++){
	    antrad[k]=tmp[j];
	    k++;
	};
	i=atoi(antrad);				// i = antal poster
	//    qDebug("antalrader=%d",i);
    
	for (k = 1;k <= i; k++){			// gå igenom alla raderna / posterna
	    l=0;
	    for(j = m; j < sizeof(artikelnr) + m; j++){
		if(tmp[j] != *("_")){
		    artikelnr[l]=tmp[j];
		    l++;
		}else{
		    artikelnr[l] = *("\0");
		    j=sizeof(artikelnr) + m;
		}
	    }
	    m=m+l+2;			// position för dagar
	    l=0;
	    for(j = m; j < sizeof(benemn1) + m; j++){
		if(tmp[j] != *("_")){
		    benemn1[l]=tmp[j];
		    l++;
		}else{
		    benemn1[l] = *("\0");
		    j=sizeof(benemn1) + m;
		}
	    }
	    m=m+l+2;			// position för beskrivning
	    l=0;
	    for(j = m; j < sizeof(benemn2) + m; j++){
		if(tmp[j] != *("_")){
		    benemn2[l]=tmp[j];
		    l++;
		}else{
		    benemn2[l] = *("\0");
		    j=sizeof(benemn2) + m;
		}
	    }
	    m=m+l+2;
	    item = new QListViewItem(ListView1,artikelnr,benemn1,benemn2);
// 	 	rensa artikelnr, benemn1 och benemn2
	    for (l=0;l<sizeof(artikelnr);l++)
		artikelnr[l]=*("\0");
	    for (l=0;l<sizeof(benemn1);l++)
		benemn1[l]=*("\0");
	    for (l=0;l<sizeof(benemn2);l++)
		benemn2[l]=*("\0");	
//	 	rensa listrad 
	}
    }
	    listrad.remove(0,70);   
}

void frmListArtikel::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmListArtikel::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmListArtikel::slotReloadArtikel()
{
    ListView1->clear();
    frmListArtikel::GetArtikel();
}
