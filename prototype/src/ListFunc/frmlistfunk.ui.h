/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                          LSTFNCW  -  description
                             -------------------
		     version 0.2
    begin                : Sön 23 febr 2003
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
#include <qstring.h>		// 2002-12-31 japi
#include <qfile.h>
#include <qregexp.h>
#include <qfont.h>
#include <qlistview.h>
#define MAXSTRING 5000	// 2003-01-04 japi

	QProcess* process;
	QString inrad;
	QString errorrad;
	QString* rad;
	
void frmListFunk::GetFunc()	
{
	const char *userp = getenv("USER");
            QString usr(userp);
	QString bibl;

	bibl.append("./STYRMAN");		// OLFIX huvudprogram
	
	process = new QProcess();
	process->addArgument(bibl);
	process->addArgument(usr);		// userid
	process->addArgument( "TRNSLST");	// OLFIX funktion
	
//	fprintf(stderr,"Starta STYRMAN/USERLST! %s\n",user);
	
	frmListFunk::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmListFunk::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );	
	frmListFunk::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );	    
 
	if ( !process->start() ) {
                // error handling
	    fprintf(stderr,"Problem starta STYRMAN/USERLST!\n");
	    QMessageBox::warning( this, "Start av TRNSLST ",
                            "Kan inte starta STYRMAN/TRNSLST!\n"
                            );
        }
}

void frmListFunk::init()
{
    PushButtonSluta->setFocus();
    frmListFunk::GetFunc();
}	
	
void frmListFunk::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
//      fprintf(stdout,"2 .Läser från STYRMAN/TRNSLST! %s\n",inrad.latin1());
}

void frmListFunk::slotEndOfProcess()
{
       QListViewItem* item;
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "LSTFNCW",
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
    char trnsid[9]="";
    char benamn[61]="";
//    char listrad[90]="";

    tmppek=tmp;
    qstrcpy(tmp,inrad);
    pos1=strstr(tmp,"NR_");
    pos2=strstr(tmp,"_:");
    i=pos2-pos1;
    m=i+2;		// startposition för första trnsid.
//    fprintf(stdout,"i=%d  m=%d",i,m);
    k=0;
    for (j=3;j<i;j++){
	antrad[k]=tmp[j];
	k++;
    };
    i=atoi(antrad);		// i = antal poster
    for (k = 1;k <= i; k++){	// gå igenom alla raderna / posterna
	l=0;
	for(j = m; j < sizeof(trnsid) + m; j++){
	    if(tmp[j] != *("_")){
		trnsid[l]=tmp[j];
		l++;
	    }else{
		trnsid[l] = *("\0");
		j=sizeof(trnsid) + m;
	    }
	}
//	fprintf(stdout,"%s  ",user);
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
	item = new QListViewItem(ListView1,trnsid,benamn);
// 	 rensa user,namn,avd och grupp 
  	for (l=0;l<sizeof(trnsid);l++)
		trnsid[l]=*("\0");
	for (l=0;l<sizeof(benamn);l++)
		benamn[l]=*("\0");
//	 rensa listrad 
	listrad.remove(0,70);
    }   
}


void frmListFunk::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
//	qWarning( "slotDataOnErrout: Userid=%s \n", inrad.latin1() );
    }
}




void frmListFunk::slotReloadFunc()
{
    ListView1->clear();
    frmListFunk::GetFunc();
}
