/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                          LSTPGMW  -  description
                             -------------------
		     version 0.1
    begin     	: Ons   22 mars  2006
    Modified	: 
    copyright            : (C) 2006 by Jan Pihlgren
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
#define MAXSTRING 25000	

	QProcess* process;
	QString inrad;
	QString errorrad;
	QString* rad;
	
void frmListProgram::GetProgram()	
{
	const char *userp = getenv("USER");
            QString usr(userp);
	QString bibl;

	bibl="./STYRMAN";		// OLFIX huvudprogram
	
	process = new QProcess();
	process->addArgument(bibl);
	process->addArgument(usr);		// userid
	process->addArgument( "PRGLST");	// OLFIX funktion
		
	frmListProgram::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmListProgram::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );	
	frmListProgram::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );	    
 
	if ( !process->start() ) {
                // error handling
	    QMessageBox::warning( this, "Start av PRGLST ",
                            "Kan inte starta STYRMAN/PRGLST!\n"
                            );
        }
}

void frmListProgram::init()
{
    PushButtonAgain->hide();
    PushButtonSluta->setFocus();
    frmListProgram::GetProgram();
}	
	
void frmListProgram::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
/*    qDebug("2 .Läser från STYRMAN/PRGLST! %s",inrad.latin1());	*/

}

void frmListProgram::slotEndOfProcess()
{
       QListViewItem* item;
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "LSTPGMW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
     }
	 
    QString listrad;
    rad=&inrad;
//    inrad.latin1();
    char *pos1;
    char *pos2;
    char tmp[MAXSTRING];
    char *tmppek;
    int j,k,l,m;
    char antrad[6]="";
    char prgnr[6]="";
    char menyavd[21]="";
    char menygrp[31]="";
    char menytxt[31]="";    
    char programid[9]="";
//    char listrad[90]="";

    tmppek=tmp;
    qstrcpy(tmp,inrad);
    pos1=strstr(tmp,"NR_");
    pos2=strstr(tmp,"_:");
    i=pos2-pos1;
    m=i+2;		// startposition för första program.
//    fprintf(stdout,"i=%d  m=%d",i,m);
    k=0;
    for (j=3;j<i;j++){
	antrad[k]=tmp[j];
	k++;
    };
    i=atoi(antrad);		// i = antal poster
/*    fprintf(stderr,"Antal rader=%d\n",i);	*/
    for (k = 1;k <= i; k++){	// gå igenom alla raderna / posterna
	l=0;
	for(j = m; j < sizeof(prgnr) + m; j++){
	    if(tmp[j] != *("_:(0)")){
		prgnr[l]=tmp[j];
		l++;
	    }else{
		prgnr[l] = *("\0");
		j=sizeof(prgnr) + m;
	    }
	}
//	fprintf(stdout,"%s  ",prgnr);	
	m=m+l+2+3;	// position för menyavd
	for(j = m; j < sizeof(menyavd) + m; j++){
	    if(tmp[j] != *("_:(1)")){
		menyavd[l]=tmp[j];
		l++;
	    }else{
		menyavd[l] = *("\0");
		j=sizeof(menyavd) + m;
	    }
	}	
//	fprintf(stdout,"%s  ",menyavd);
	m=m+l+2+3;	// position för menygrp
	l=0;
	for(j = m; j < sizeof(menygrp) + m; j++){
	    if(tmp[j] != *("_:(2)")){
		menygrp[l]=tmp[j];
		l++;
	    }else{
		menygrp[l] = *("\0");
		j=sizeof(menygrp) + m;
	    }
	}
//	fprintf(stdout,"%s  ",menygrp);	
	m=m+l+2+3;	// position för menytxt
	l=0;
	for(j = m; j < sizeof(menytxt) + m; j++){
	    if(tmp[j] != *("_:(3)")){
		menytxt[l]=tmp[j];
		l++;
	    }else{
		menytxt[l] = *("\0");
		j=sizeof(menytxt) + m;
	    }
	}
//	fprintf(stdout,"%s  ",menytxt);	
	m=m+l+2+3;	// position för programid
	l=0;
	for(j = m; j < sizeof(programid) + m; j++){
	    if(tmp[j] != *("_:(4)")){
		programid[l]=tmp[j];
		l++;
	    }else{
		programid[l] = *("\0");
		j=sizeof(programid) + m;
	    }
	}
//	fprintf(stdout,"%s  ",programid); 
	
	m=m+l+2+3;
	item = new QListViewItem(ListView1,programid,menytxt);
// 	 rensa prgnr,menyavd, menygrp, menytxt, programid
  	for (l=0;l<sizeof(prgnr);l++)
		prgnr[l]=*("\0");	
  	for (l=0;l<sizeof(menyavd);l++)
		menyavd[l]=*("\0");
	for (l=0;l<sizeof(menygrp);l++)
		menygrp[l]=*("\0");
  	for (l=0;l<sizeof(menytxt);l++)
		menytxt[l]=*("\0");
	for (l=0;l<sizeof(programid);l++)
		programid[l]=*("\0");	
//	 rensa listrad 
	listrad.remove(0,70);
    }   
}

void frmListProgram::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
//	qWarning( "slotDataOnErrout: Userid=%s \n", inrad.latin1() );
    }
}

void frmListProgram::slotReloadProgram()
{
    ListView1->clear();
    frmListProgram::GetProgram();
}
