/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                          LSTKUW  -  description
                             -------------------
		     version 0.1
    begin                : Tis 7 okt 2003
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
	
void frmListKund::GetKund()	
{
	const char *userp = getenv("USER");
            QString usr(userp);

	
	process = new QProcess();
	process->addArgument("STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "KULST");	// OLFIX funktion
	
//	fprintf(stderr,"Starta STYRMAN/USERLST! %s\n",user);
	
	frmListKund::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmListKund::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );	
	frmListKund::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );	    
 
	if ( !process->start() ) {
                // error handling
	    fprintf(stderr,"Problem starta STYRMAN/KULST!\n");
	    QMessageBox::warning( this, "Start av KULST ",
                            "Kan inte starta STYRMAN/KULST!\n"
                            );
        }
}

void frmListKund::init()
{
    PushButtonSluta->setFocus();
    frmListKund::GetKund();
}	
	
void frmListKund::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmListKund::slotEndOfProcess()
{
    QListViewItem* item;
    int i;
    ListView1->setSorting(1,TRUE);
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "LSTKUW",
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
//    int antrad;
    char antrad[6]="";
    char kundnr[11]="";
    char namn[61]="";

    tmppek=tmp;
    qstrcpy(tmp,inrad);
    pos1=strstr(tmp,"OK: NR_");	// 7 tecken l�ngt
    pos2=strstr(tmp,"_:");
    i=pos2-pos1;
    m=i+2;		// startposition f�r f�rsta kundnr.
    
//    qDebug("i=%d  m=%d",i,m);
    
    k=0;
    for (j=7;j<i;j++){	// j = f�rsta positionen f�r antal poster,(OK: NR_4_:4377_:Kund AB_:4379_:Sm�kund AB_:4378_:Storkund AB_:4376_:Test AB_:)
	antrad[k]=tmp[j];
	k++;
    };
    i=atoi(antrad);		// i = antal poster
    
//    qDebug("antrad=%s",antrad);
    
    for (k = 1;k <= i; k++){	// g� igenom alla raderna / posterna
	l=0;
	for(j = m; j < sizeof(kundnr) + m; j++){
	    if(tmp[j] != *("_")){
		kundnr[l]=tmp[j];
		l++;
	    }else{
		kundnr[l] = *("\0");
		j=sizeof(kundnr) + m;
	    }
	}
//	qDebug("%s  ",kundnr);
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
	item = new QListViewItem(ListView1,kundnr,namn);
// 	 rensa kundnr och namn 
  	for (l=0;l<sizeof(kundnr);l++)
		kundnr[l]=*("\0");
	for (l=0;l<sizeof(namn);l++)
		namn[l]=*("\0");
//	 rensa listrad 
	listrad.remove(0,80);
    }   
}


void frmListKund::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
//	qWarning( "slotDataOnErrout: Userid=%s \n", inrad.latin1() );
    }
}




void frmListKund::slotReloadKund()
{
    ListView1->clear();
    frmListKund::GetKund();
}
