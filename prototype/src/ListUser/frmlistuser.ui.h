/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                          LSTUSRW  -  description
                             -------------------
		     version 0.04
    begin                : Tis 27 maj 2003
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
    "@(#) $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/olfix/Repository/prototype/src/ListUser/frmlistuser.ui.h,v 1.2 2003/09/28 08:27:53 janpihlgren Exp $ " ;

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
	
void frmListUser::GetUser()	
{
	const char *userp = getenv("USER");
              QString usr(userp);
	QString bibl;
	inrad="";
	errorrad="";
	bibl.append("./STYRMAN");		// OLFIX huvudprogram
	
	process = new QProcess();
	process->addArgument(bibl);
	process->addArgument(usr);		// userid
	process->addArgument( "USERLST");	// OLFIX funktion
	
//	fprintf(stderr,"Starta STYRMAN/USERLST! %s\n",user);
	
	frmListUser::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmListUser::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );	
	frmListUser::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );	    
 
	if ( !process->start() ) {
                // error handling
	    fprintf(stderr,"Problem starta STYRMAN/USERLST!\n");
	    QMessageBox::warning( this, "Start av USERLST ",
                            "Kan inte starta STYRMAN/USERLST!\n"
                            );
        }
}

void frmListUser::init()
{
    PushButtonSluta->setFocus();
    frmListUser::GetUser();
}	
	
void frmListUser::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
//      fprintf(stdout,"2 .Läser från STYRMAN/USERLST! %s\n",inrad.latin1());
}

void frmListUser::slotEndOfProcess()
{
       QListViewItem* item;
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "LSTUSRW",
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
    char user[9]="";
    char namn[31]="";
    char avd[31]="";
    char grupp[11]="";
//    char listrad[90]="";

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
	for(j = m; j < sizeof(user) + m; j++){
	    if(tmp[j] != *("_")){
		user[l]=tmp[j];
		l++;
	    }else{
		user[l] = *("\0");
		j=sizeof(user) + m;
	    }
	}
//	fprintf(stdout,"%s  ",user);
	m=m+l+2;	// position för namn
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
//	fprintf(stdout,"%s  ",namn);
	m=m+l+2;	// position för avd
	l=0;
	for(j = m; j < sizeof(avd) + m; j++){
	    if(tmp[j] != *("_")){
		avd[l]=tmp[j];
		l++;
	    }else{
		avd[l] = *("\0");
		j=sizeof(avd) + m;
	    }
	}
//	fprintf(stdout,"%s  ",avd);
	m=m+l+2;	// position för grupp
	l=0;
	for(j = m; j < sizeof(grupp) + m; j++){
	    if(tmp[j] != *("_")){
		grupp[l]=tmp[j];
		l++;
	    }else{
		grupp[l] = *("\0");
		j=sizeof(grupp) + m;
	    }
	}
	m=m+l+2;
//	fprintf(stdout,"%s\n  ",grupp);
	item = new QListViewItem(ListView1,user,namn,avd,grupp);
// 	 rensa user,namn,avd och grupp 
  	for (l=0;l<sizeof(user);l++)
		user[l]=*("\0");
	for (l=0;l<sizeof(namn);l++)
		namn[l]=*("\0");
	for (l=0;l<sizeof(avd);l++)
		avd[l]=*("\0");
	for (l=0;l<sizeof(grupp);l++)
		grupp[l]=*("\0");
//	 rensa listrad 
	listrad.remove(0,70);
    }   
//   fprintf(stderr,"%s",tmp);
//    fprintf(stderr,"Klart!\n");
}


void frmListUser::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
//	qWarning( "slotDataOnErrout: Userid=%s \n", inrad.latin1() );
    }
}

void frmListUser::slotReloadUser()
{
        ListView1->clear();
        frmListUser::GetUser();
}
