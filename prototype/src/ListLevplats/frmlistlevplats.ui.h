/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                          LSTLEVPW  -  description
                             -------------------
		     version 0.1
    begin                : Mån 8 nov 2004
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
#include <qclipboard.h> 
#define MAXSTRING 5000

	QProcess* process;
	QString inrad;
	QString errorrad;
	QString* rad;
	
void frmListLevplats::GetLev()	
{
	const char *userp = getenv("USER");
            QString usr(userp);

	
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "LEVPLST");	// OLFIX funktion
	
	frmListLevplats::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmListLevplats::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );	
	frmListLevplats::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );	    
 
	if ( !process->start() ) {
                // error handling
	    fprintf(stderr,"Problem starta STYRMAN/LEVPLST!\n");
	    QMessageBox::warning( this, "Start av LEVPLST ",
                            "Kan inte starta STYRMAN/LEVPLST!\n"
                            );
        }
}

void frmListLevplats::init()
{
    PushButtonSluta->setFocus();
    frmListLevplats::GetLev();
}	
	
void frmListLevplats::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmListLevplats::slotEndOfProcess()
{
    QListViewItem* item;
    
    int i;
    ListView1->setSorting(0,TRUE);
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "LSTLEVW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
     }
	 
    i = inrad.find( QRegExp("OK: NR_0_"), 0 );
         if (i != -1) {
	QMessageBox::information( this, "LSTLEVW",
		"Leverantörsregistret innehåller inga poster!\n"
	);
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
    char levpnr[4]="";
    char kundnr[11]="";
    char adress[31]="";
    char postnr[7]="";
    char postadr[31]="";
    char land[31]="";

    tmppek=tmp;
    qstrcpy(tmp,inrad);
    pos1=strstr(tmp,"OK: NR_");	// 7 tecken långt
    pos2=strstr(tmp,"_:");
    i=pos2-pos1;
    m=i+2;		// startposition för första levnr.
    
//    qDebug("i=%d  m=%d",i,m);
    
    k=0;
    for (j=7;j<i;j++){	
	antrad[k]=tmp[j];
	k++;
    };
    i=atoi(antrad);		// i = antal poster
    
//    qDebug("antrad=%s",antrad);
    
    for (k = 1;k <= i; k++){	// gå igenom alla raderna / posterna
	l=0;
	for(j = m; j < sizeof(levpnr) + m; j++){
	    if(tmp[j] != *("_")){
		levpnr[l]=tmp[j];
		l++;
	    }else{
		levpnr[l] = *("\0");
		j=sizeof(levpnr) + m;
	    }
	}
//	qDebug("%s  ",levpnr);
	m=m+l+2;	// position för kundnr
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
	m=m+l+2;
	l=0;
	for(j = m; j < sizeof(adress) + m; j++){
	    if(tmp[j] != *("_")){
		adress[l]=tmp[j];
		l++;
	    }else{
		adress[l] = *("\0");
		j=sizeof(adress) + m;
	    }
	}
	m=m+l+2;
	l=0;
	for(j = m; j < sizeof(postnr) + m; j++){
	    if(tmp[j] != *("_")){
		postnr[l]=tmp[j];
		l++;
	    }else{
		postnr[l] = *("\0");
		j=sizeof(postnr) + m;
	    }
	}
	m=m+l+2;
	l=0;
	for(j = m; j < sizeof(postadr) + m; j++){
	    if(tmp[j] != *("_")){
		postadr[l]=tmp[j];
		l++;
	    }else{
		postadr[l] = *("\0");
		j=sizeof(postadr) + m;
	    }
	}
	m=m+l+2;
	l=0;
	for(j = m; j < sizeof(land) + m; j++){
	    if(tmp[j] != *("_")){
		land[l]=tmp[j];
		l++;
	    }else{
		land[l] = *("\0");
		j=sizeof(land) + m;
	    }
	}	
	m=m+l+2;
    ListView1->setColumnWidth(0,70);		// Levplatsnr
    ListView1->setColumnAlignment( 0, Qt::AlignHCenter );
    ListView1->setColumnWidth(1,80);		// Kundnr
    ListView1->setColumnAlignment( 1, Qt::AlignRight );
    ListView1->setColumnWidth(2,150);		// Adress
    ListView1->setColumnWidth(3,55);		// Postnr
    ListView1->setColumnAlignment( 3, Qt::AlignHCenter );
    ListView1->setColumnWidth(4,170);		// Postadress
	
	item = new QListViewItem(ListView1,levpnr,kundnr,adress,postnr,postadr);
// 	 rensa levpnr och kundnr 
  	for (l=0;l<sizeof(levpnr);l++)
		levpnr[l]=*("\0");
	for (l=0;l<sizeof(kundnr);l++)
		kundnr[l]=*("\0");
  	for (l=0;l<sizeof(adress);l++)
		adress[l]=*("\0");
  	for (l=0;l<sizeof(postnr);l++)
		postnr[l]=*("\0");
  	for (l=0;l<sizeof(postadr);l++)
		postadr[l]=*("\0");
  	for (l=0;l<sizeof(land);l++)
		land[l]=*("\0");
	
//	 rensa listrad 
	listrad.remove(0,80);
    }   
}

void frmListLevplats::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
//	qWarning( "slotDataOnErrout: Userid=%s \n", inrad.latin1() );
    }
}

void frmListLevplats::slotReloadLev()
{
    ListView1->clear();
    frmListLevplats::GetLev();
}



