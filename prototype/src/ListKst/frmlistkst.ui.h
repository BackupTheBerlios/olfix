/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                          LSTKSTW  -  description
                             -------------------
		     version 0.02
    begin                : Ons 26 febr 2003
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


void frmListKst::init()
{
    PushButtonSluta->setFocus();
    frmListKst::GetKstalle();
}

void frmListKst::GetKstalle()
{
	const char *userp = getenv("USER");
            QString usr(userp);
	QString bibl;

//	bibl.append("./STYRMAN");		// OLFIX huvudprogram
	
	process = new QProcess();
//	process->addArgument(bibl);
	process->addArgument("./STYRMAN");
	process->addArgument(usr);		// userid
	process->addArgument( "KSTLST");	// OLFIX funktion
	
//	fprintf(stderr,"Starta STYRMAN/kstLST! %s\n",user);
	
	frmListKst::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmListKst::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );	
	frmListKst::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );	    
 
	if ( !process->start() ) {
                // error handling
	    fprintf(stderr,"Problem starta STYRMAN/KSTLST!\n");
	    QMessageBox::warning( this, "Start av KSTLST ",
                            "Kan inte starta STYRMAN/KSTLST!\n"
                            );
        }
}

void frmListKst::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmListKst::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmListKst::slotEndOfProcess()
{
    QListViewItem* item;
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "LSTKSTW",
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
    char bar[3]="";
    char kstalle[5]="";
    char benamn[101]="";

    tmppek=tmp;
    qstrcpy(tmp,inrad);
    pos1=strstr(tmp,"NR_");
    pos2=strstr(tmp,"_:");
    i=pos2-pos1;
    m=i+2;		// startposition för första userid.
//    fprintf(stdout,"i=%d  m=%d",i,m);
    k=0;
    for (j=3;j<i;j++){
	antrad[k]=tmp[j];
	k++;
    };
    i=atoi(antrad);		// i = antal poster
    for (k = 1;k <= i; k++){	// gå igenom alla raderna / posterna
	l=0;
	for(j = m; j < sizeof(bar) + m; j++){
	    if(tmp[j] != *("_")){
		bar[l]=tmp[j];
		l++;
	    }else{
		bar[l] = *("\0");
		j=sizeof(bar) + m;
	    }
	}
//	fprintf(stdout,"%s  ",bar);
	m=m+l+2;	// position för kstalle
	l=0;
	for(j = m; j < sizeof(kstalle) + m; j++){
	    if(tmp[j] != *("_")){
		kstalle[l]=tmp[j];
		l++;
	    }else{
		kstalle[l] = *("\0");
		j=sizeof(kstalle) + m;
	    }
	}
//	fprintf(stdout,"%s  ",kstalle);
	m=m+l+2;	// position för benamn
	l=0;
	for(j = m; j < sizeof(benamn) + m; j++){
	    if(tmp[j] != *("_")){
		benamn[l]=tmp[j];
		l++;
	    }else{
		benamn[l] = *("\0");
		j=sizeof(benamn) + m;
	    }
	}
//	fprintf(stdout,"%s  ",benamn);
	m=m+l+2;
	
	item = new QListViewItem(ListView1,bar,kstalle,benamn);
// 	 rensa bar,kstalle,benamn 
  	for (l=0;l<sizeof(bar);l++)
		bar[l]=*("\0");
	for (l=0;l<sizeof(kstalle);l++)
		kstalle[l]=*("\0");
	for (l=0;l<sizeof(benamn);l++)
		benamn[l]=*("\0");
//	 rensa listrad 
	listrad.remove(0,70);
    }   
//   fprintf(stderr,"%s",tmp);
//    fprintf(stderr,"Klart!\n");
}

void frmListKst::slotReloadKstalle()
{
//    fprintf(stderr,"Reload kostnadställe\n");
    ListView1->clear();
    inrad="";
    frmListKst::GetKstalle();
}
