/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                          LSTFTGW  -  description
                             -------------------
		     version 0.1
    begin                : Fre 31 dec 2004
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
/*@unused@*/ static char RCS_id[] =
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/ListForetagsdata/frmlistftgdata.ui.h,v 1.1 2005/01/01 07:22:20 janpihlgren Exp $ " ;

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
	QString tabell[100][2];
	
void frmListFtgData::init()
{
/*   	Hämta postbeskrivningar 	*/  
    frmListFtgData::ListViewRadFormat();
    frmListFtgData::GetPostbeskrivning();
    PushButtonSluta->setFocus();
}	
		
void frmListFtgData::GetFtgData()	
{
	const char *userp = getenv("USER");
            QString usr(userp);
	inrad="";
	errorrad="";
	
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX huvudprogram
	process->addArgument(usr);		// userid
	process->addArgument( "FTGLIS");	// OLFIX funktion
		
	frmListFtgData::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmListFtgData::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );	
	frmListFtgData::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );	    
 
	if ( !process->start() ) {
                // error handling
	    QMessageBox::warning( this, "Start av FTGLIS ",
                            "Kan inte starta STYRMAN/FTGLIS!\n"
                            );
        }
}
	
void frmListFtgData::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmListFtgData::slotEndOfProcess()
{
    QListViewItem* item;
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "LSTFTGW",
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
    int j,k,l,m,n;
    char antrad[6]="";
    char posttyp[6]="";
    QString beskr="";
    char data[61]="";

    tmppek=tmp;
    qstrcpy(tmp,inrad);
    pos1=strstr(tmp,"OK: NR_");
    pos2=strstr(tmp,"_:");
    i=pos2-pos1;
    m=i+2;		// startposition för första posttyp.
    k=0;
    for (j=7;j<i;j++){
	antrad[k]=tmp[j];
	k++;
    };
    i=atoi(antrad);		// i = antal poster
//    qDebug("antrad=%d",i);
  
    for (k = 1;k <= i; k++){	// gå igenom alla raderna / posterna
	l=0;
	for(j = m; j < sizeof(posttyp) + m; j++){
	    if(tmp[j] != *("_")){
		posttyp[l]=tmp[j];
		l++;
	    }else{
		posttyp[l] = *("\0");
		j=sizeof(posttyp) + m;
	    }
	}
	for (n=0;n<i;n++){
	    if (posttyp == tabell[n][0]){
		beskr=tabell[n][1];
		n=i;
	    }
	}
//	qDebug("posttyp=%s   beskr=%s",posttyp,beskr.latin1());
	m=m+l+2;	// position för data
	l=0;
	for(j = m; j < sizeof(data) + m; j++){
	    if(tmp[j] != *("_")){
		data[l]=tmp[j];
		l++;
	    }else{
		data[l] = *("\0");
		j=sizeof(data) + m;
	    }
	}
	m=m+l+2;
	item = new QListViewItem(ListView1,posttyp,beskr,data);
// 	 rensa posttyp,beskr och data 
  	for (l=0;l<sizeof(posttyp);l++)
		posttyp[l]=*("\0");
	for (l=0;l<sizeof(data);l++)
		data[l]=*("\0");
//	 rensa listrad 
	listrad.remove(0,70);
    }   
}

void frmListFtgData::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmListFtgData::slotReloadFtgData()
{
        ListView1->clear();
        frmListFtgData::GetFtgData();
}

void frmListFtgData::GetPostbeskrivning()
{
	const char *userp = getenv("USER");
            QString usr(userp);
	inrad="";
	errorrad="";
	
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX huvudprogram
	process->addArgument(usr);		// userid
	process->addArgument( "FTGLST");	// OLFIX funktion
		
	frmListFtgData::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmListFtgData::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );	
	frmListFtgData::connect( process, SIGNAL(processExited() ),this, SLOT(slotPostbeskrEndOfProcess() ) );	    
 
	if ( !process->start() ) {
                // error handling
	    QMessageBox::warning( this, "Start av FTGLST ",
                            "Kan inte starta STYRMAN/FTGLST!\n"
                            );
        }
}

void frmListFtgData::slotPostbeskrEndOfProcess()
{
    int i,j,k,l,m,n;
    QString tmp;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "LSTFTGW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
    }
//    qDebug("inrad=%s",inrad.latin1());
    i = inrad.find( QRegExp("NR_"), 0 );
    j = inrad.find( QRegExp("_:"), 0 );
    if (i != -1) {
	QString antrad=inrad.mid(i+3,j);
	 i=atoi(antrad);		// i = antal poster
//	qDebug("antrad=%d",i);    
    }  
    n=0;
    for (j=0;j<i;j++){
	k=inrad.find(QRegExp("_:"),0+n);
	l=inrad.find(QRegExp("_:"),k+2);
	m=inrad.find(QRegExp("_:"),l+2);
	tabell[j][0]=inrad.mid(k+2,l-k-2);
	tabell[j][1]=inrad.mid(l+2,m-l-2);
//	qDebug("tabell[%d][%d]  = %s   tabell[%d][%d] = %s",j,0,tabell[j][0].latin1(),j,1,tabell[j][1].latin1());
	n=m;
     }    
    frmListFtgData::GetFtgData();
}


void frmListFtgData::ListViewRadFormat()
{
    ListView1->setColumnWidth(0,55);		// Posttyp
    ListView1->setColumnAlignment( 0, Qt::AlignLeft );
    ListView1->setColumnWidth(1,300);		// Beskrivning
    ListView1->setColumnAlignment( 1, Qt::AlignLeft );
    ListView1->setColumnWidth(2,150);		// Data
    ListView1->setColumnAlignment( 2, Qt::AlignLeft );

}
