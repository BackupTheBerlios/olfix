/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                          OLFIXW  -  description
                             -------------------
		     version 0.5
    begin                   : Tis 16 maj 2003
    modified	: Fre 20 febr 2004
    copyright            : (C) 2003 by Jan Pihlgren
    email                  : jan@pihlgren.se
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
//#include <qfont.h>
#include <qlistview.h>
#define MAXSTRING 10000
#define PRGNAMN 40

	QProcess* process;
	QString* rad;
	QString inrad;
	QString errorrad;
	QString program;

void frmOlfix::init()
{
    frmOlfix::slotGetProgram();
    PushButtonQuit->setFocus();
}


void frmOlfix::slotGetProgram()
{
	const char *userp = getenv("USER");
            QString usr(userp);
//	QString bibl;
	inrad="";
	errorrad="";
//	bibl.append("./STYRMAN");		// OLFIX huvudprogram

	process = new QProcess();
//	process->addArgument(bibl);
	process->addArgument("./STYRMAN");	// OLFIX huvudprogram
	process->addArgument(usr);		// userid
	process->addArgument( "PRGLST");	// OLFIX funktion

//	fprintf(stderr,"Starta STYRMAN/PRGLST! %s\n",user);

	frmOlfix::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmOlfix::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmOlfix::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );
	if ( !process->start() ) {
                // error handling
	    fprintf(stderr,"Problem starta STYRMAN/PRGLST!\n");
	    QMessageBox::warning( this, "Start av PRGLST ",
                            "Kan inte starta STYRMAN/PRGLST!\n"
                            );
        }
}


void frmOlfix::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
//    fprintf(stdout,"Läser från slotDataOnStdout STYRMAN/PRGLST! %s\n",inrad.latin1());
}


void frmOlfix::slotDataOnStderr()
{
   while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}


void frmOlfix::slotEndOfProcess()
{
//    QListViewItem* item;
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "OLFIXW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
     }
    i = -1;
    i = inrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "OLFIXW",
		"ERROR!\n"+inrad
	);
	inrad="";
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
    int pgmfoldnr,mnufoldnr,mnutxtnr;
    
    char antrad[6]="";
    char prgnr[4]="";
    char proggrp[21]="";
    char prggrptemp[21]="";
    char mnugrp[31]="";
    char mnugrptemp[31]="";
    char mnutxt[31]="";
    char mnutxttemp[31]="";
    char pgm[9]="";

    pgmfoldnr=0;
    mnufoldnr=0;
    mnutxtnr=0;
    tmppek=tmp;
    qstrcpy(tmp,inrad);
    pos1=strstr(tmp,"NR_");
    pos2=strstr(tmp,"_:");
    i=pos2-pos1;
    m=i+2+3;		// startposition
//    fprintf(stdout,"i=%d  m=%d",i,m);
    k=0;
    for (j=3;j<i;j++){
	antrad[k]=tmp[j];
	k++;
    };
    i=atoi(antrad);		// i = antal poster
//    fprintf(stderr,"Antalrader=%d\n",i);
    
    for (k = 1;k <= i; k++){	// gå igenom alla raderna / posterna
	l=0;
	for(j = m; j < sizeof(prgnr) + m; j++){
	    if(tmp[j] != *("_")){
		prgnr[l]=tmp[j];
		l++;
	    }else{
		prgnr[l] = *("\0");
		j=sizeof(prgnr) + m;
	    }
	}
//	fprintf(stdout,"%s  ",prgnr);
	m=m+l+2+3;	// position för proggrp
	l=0;
	for(j = m; j < sizeof(proggrp) + m; j++){
	    if(tmp[j] != *("_")){
		proggrp[l]=tmp[j];
		l++;
	    }else{
		proggrp[l] = *("\0");
		j=sizeof(proggrp) + m;
	    }
	}
//	fprintf(stdout,"%s  ",proggrp);
	m=m+l+2+3;	// position för mnugrp
	l=0;
	for(j = m; j < sizeof(mnugrp) + m; j++){
	    if(tmp[j] != *("_")){
		mnugrp[l]=tmp[j];
		l++;
	    }else{
		mnugrp[l] = *("\0");
		j=sizeof(mnugrp) + m;
	    }
	}
//	fprintf(stdout,"%s  ",mnugrp);
	m=m+l+2+3;	// position för mnutxt
	l=0;
	for(j = m; j < sizeof(mnutxt) + m; j++){
	    if(tmp[j] != *("_")){
		mnutxt[l]=tmp[j];
		l++;
	    }else{
		mnutxt[l] = *("\0");
		j=sizeof(mnutxt) + m;
	    }
	}
//	fprintf(stdout,"%s\n  ",mnutxt);
	m=m+l+2+3;	//position för pgm	
	l=0;
	for(j = m; j < sizeof(pgm) + m; j++){
	    if(tmp[j] != *("_")){
		pgm[l]=tmp[j];
		l++;
	    }else{
		pgm[l] = *("\0");
		j=sizeof(pgm) + m;
	    }
	}
	m=m+l+2+3;
// 	fprintf(stdout,"%s\n  ",mnutxt);	
//	fprintf(stderr,"%s %s %s %s\n",proggrp,mnugrp,mnutxt,pgm);
	
	QString pgmfold;
	QString mnufold;
	QString txtfold;
	QListViewItem *pgmfolder[30];
	QListViewItem *mnufolder[30];
	QListViewItem *mnutxtfld[30];
	
	if (strcmp(prggrptemp,proggrp) != 0){
	    pgmfold=proggrp;
	    pgmfoldnr++;
	    pgmfolder[pgmfoldnr] = new QListViewItem(ListView1, pgmfold);
	    strcpy(prggrptemp,proggrp);
	    mnufoldnr=0;
	}
            if (strcmp(mnugrptemp,mnugrp) != 0){
		mnufold=mnugrp;
		mnufoldnr++;
		mnufolder[mnufoldnr] = new QListViewItem(pgmfolder[pgmfoldnr] ,mnufold);
		strcpy(mnugrptemp,mnugrp);
		mnutxtnr=0;
	 }
            if (strcmp(mnutxttemp,mnutxt) != 0){
		txtfold=mnutxt;
		mnutxtnr++;
		mnutxtfld[mnutxtnr] = new QListViewItem(mnufolder[mnufoldnr] ,mnutxt,pgm);
		strcpy(mnutxttemp,mnutxt);
//		item = new QListViewItem(ListView1,"",pgm);	    
//		mnufolder[mnufoldnr]->setText(1,pgm);
	    }
//  	mnufolder[mnufoldnr]->setText(1,pgm);
//	fprintf(stderr,"slut (%d) %s (%d) %s (%d) %s\n",pgmfoldnr,prggrptemp,mnufoldnr,mnugrptemp,mnutxtnr,mnutxt);

// 	 rensa pgrnr,proggrp,mnugrp,mnutxt,pgm
  	for (l=0;l<sizeof(prgnr);l++)
		prgnr[l]=*("\0");
	for (l=0;l<sizeof(proggrp);l++)
		proggrp[l]=*("\0");
	for (l=0;l<sizeof(mnugrp);l++)
		mnugrp[l]=*("\0");
	for (l=0;l<sizeof(mnutxt);l++)
		mnutxt[l]=*("\0");
	for (l=0;l<sizeof(pgm);l++)
		pgm[l]=*("\0");
//	 rensa listrad
	listrad.remove(0,70);
    }
//   fprintf(stderr,"%s",tmp);
//    fprintf(stderr,"Klart!\n");
}

void frmOlfix::ListView1_clicked( QListViewItem * item)
{
    char programnamn[PRGNAMN]="";
    QString prog;

    if(!item){
	return;
    }
     ListView1->setCurrentItem(item);
     if(!item->key(1,TRUE)){
	 return;
     }

     strcpy(programnamn,item->key(1,TRUE));
     prog=programnamn;
//     fprintf(stderr,"item=%s\n",data);
     inrad="";
     errorrad="";
     frmOlfix::CheckBehor( programnamn );
}

void frmOlfix::slotRunProgram( QString prg )
{
 	QString prog;
	prog.append("./");
            prog.append(prg);
	inrad="";
	errorrad="";

	process = new QProcess();
	process->addArgument( prog );		// OLFIX program
	frmOlfix::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnPrgStderr() ) );
	frmOlfix::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfPrgProcess() ) );

	if ( !process->start() ) {
	    // error handling
	    fprintf(stderr,"Problem starta OLFIXW - %s\n",prog.latin1());
	    QMessageBox::warning( this, "OLFIX","Kan inte starta "+prog+"!\n" );
	}
    }

void frmOlfix::slotDataOnPrgStderr()
{
   while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmOlfix::slotEndOfPrgProcess()
{
    int i;
    i = -1;
    i = inrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "OLFIXW",
		"ERROR!\n"+inrad
	);
	inrad="";
	i = -1;
     }
}

void frmOlfix::CheckBehor(QString prog)
{
    	const char *userp = getenv("USER");
            QString usr(userp);
	QString bibl;
	inrad="";
	errorrad="";
	program=prog;
	bibl.append("./STYRMAN");		// OLFIX huvudprogram
		
	process = new QProcess();
	process->addArgument(bibl);
	process->addArgument("OLFIX");		// user OLFIX
	process->addArgument( "RGTCHK");	// OLFIX program
	process->addArgument( usr.latin1() );
	process->addArgument( prog.latin1() );
//	qWarning("slotCheckBehor:  %s %s %s\n",bibl.latin1(),usr.latin1(),prog.latin1()); 
	frmOlfix::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnCheckStdout() ) );
	frmOlfix::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnCheckStderr() ) );
	frmOlfix::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfCheckProcess() ) );

	if ( !process->start() ) {
	    // error handling
	    fprintf(stderr,"Problem starta OLFIXW - %s\n",prog.latin1());
	    QMessageBox::warning( this, "OLFIX","Kan inte starta RGTCHK!\n" );
	}
}


void frmOlfix::slotEndOfCheckProcess()
{
    int i;
     i = -1;
     i = inrad.find( QRegExp("OK:"), 0 );
//     qWarning("slotEndOfCheckProcess(): errorrad=%s inrad=%s i=%d\n",errorrad.latin1(),inrad.latin1(),i);

     if(i != -1){
	 frmOlfix::slotRunProgram( program );
     }
     else{
	QMessageBox::warning( this, "OLFIX - Behörighet",
                            "Du har inte behörighet att köra programet "+program+"!\n"  );
     }
 }

void frmOlfix::slotDataOnCheckStdout()
{
    while (process->canReadLineStdout() ){
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
//   qWarning("slotDataOnCheckStdout(): inrad=%s\n",inrad.latin1());
}

void frmOlfix::slotDataOnCheckStderr()
{
   while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmOlfix::slotOmOlfix()
{
	QMessageBox::information( this, "Om OLFIX",
		"OLFIX är ett order/lager/faktureringssystem"
			    " för Linux.\n"
                            "(C) 2003 av Jan-Gunnar Pihlgren\n"
			    "2003-05-27"
	);
}

void frmOlfix::slotLicensvillkor()
{
  QMessageBox::information( this, "OLFIX - Licensvillkor",
                            " This program is free software; \n"
			    "you can redistribute it and/or modify it under the\n"
			    "terms of the GNU General Public License\n"
			    "as published by the Free Software Foundation;\n"
			    "either version 2 of the License, or (at your option)\n"
			    "any later version.\n"
                            );
}


void frmOlfix::slotHelp()
{
	inrad="";
	errorrad="";

	process = new QProcess();
	process->addArgument( "OLFIXHLP" );		// OLFIX program
	process->addArgument("/doc/helpfiles/usermanual/UserManual.html");
	
	if ( !process->start() ) {
	    // error handling
	    QMessageBox::warning( this, "OLFIX","Kan inte starta OLFIXHLP!\n" );
	}

/*  QMessageBox::information( this, "Hjälpindexl",
                            "Ännu inte implementerad!"
                            );
*/			    
}

