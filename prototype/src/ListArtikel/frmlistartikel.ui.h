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
		     version 0.3
    begin                : Sön 22 nov 2003
    modified	: Mån  15 febr 2005
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
#include <qclipboard.h> 			// 2003-12-07
#include <qapplication.h>		// 2003-12-07
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
	    inrad="";				// töm inputbuffer
	
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
//    QString listrad;
  char *pos1;
  char *pos2;
  char tmp[MAXSTRING];
  char *tmppek;
  int j,k,m;
  char antrad[6]="";
  QString artikelnr;
  QString benemn1;
  QString benemn2;
  QListViewItem* item;
   int i;
   
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "LSTARW","ERROR!\n"+errorrad);
	errorrad="";
	i = -1;
	exit(-1);
    }
//	qDebug("inrad=%s",inrad.latin1()); 
    i = inrad.find( QRegExp("OK: NR_0_"), 0 );
    if (i != -1) {
	QMessageBox::information( this, "LSTARW","Betalningsvillkorregistret innehåller inga poster!\n");
	i = -1;
	exit(-1);
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
	int ant=i;
//	qDebug("antalrader=%d",i);
	j =  inrad.find( QRegExp("_:"), 0); 
//	qDebug("j=%d",j);
	for (k = 0;k < ant; k++){			// gå igenom alla raderna / posterna
	    i = j;
	    j = inrad.find(QRegExp("_:"),i+2);
	    if (j < i){
		k=ant;
	    }
	    m = j - (i+2);
	    artikelnr=inrad.mid(i+2,m);   
//	    qDebug("artikelnr=%s",artikelnr.latin1());
	    i = j;
	    j = inrad.find(QRegExp("_:"),i+2);
	    m = j - (i+2);
	    benemn1=inrad.mid(i+2,m);   
//	    qDebug("benemn1=%s",benemn1.latin1());
	    i = j;
	    j = inrad.find(QRegExp("_:"),i+2);
	    m = j - (i+2);
	    benemn2=inrad.mid(i+2,m);   
//	    qDebug("benemn2=%s",benemn2.latin1());
	    item = new QListViewItem(ListView1,artikelnr,benemn1,benemn2);	    
	}
    }
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
    inrad="";
    frmListArtikel::GetArtikel();
}

void frmListArtikel::PickupArtikelnr(QListViewItem * item)	// 2003-12-07
{
    QString artikelnr;
    char artikelnummer[31]="";
//    qDebug("PickupArtikelnr\n");
    if(!item){
	return;
    }
     ListView1->setCurrentItem(item);
     if(!item->key(0,TRUE)){
	 return;
     }

     strcpy(artikelnummer,item->key(0,TRUE));
     artikelnr=artikelnummer;
//     qDebug("artikelnr=%s",artikelnr.latin1());
     QClipboard *cb = QApplication::clipboard();     
     cb->setText( artikelnr);
}
