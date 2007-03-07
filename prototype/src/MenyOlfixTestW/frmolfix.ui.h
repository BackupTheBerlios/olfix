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
		     version 0.67
    begin               : Tis  16 maj  2003
    modified	        : Ons  7 mars 2007
    copyright        : (C) 2003 by Jan Pihlgren
    email               : jan@pihlgren.se
 ***************************************************************************/
/*************************************************************************
 *						                                       	*
 *   This program is free software; you can redistribute it and/or modify 		*
 *   it under the terms of the GNU General Public License as published by       		*
 *   the Free Software Foundation; either version 2 of the License, or     		*
 *   (at your option) any later version.                                   				*
 *                                                                         					*
*************************************************************************/

#include <qmessagebox.h>
#include <qprocess.h>
#include <qdir.h>
#include <stdlib.h>
#include <qstring.h>
#include <qfile.h>
#include <qregexp.h>
#include <qlistview.h>
#define MAXSTRING 10000
#define PRGNAMN 80		/* 2007-03-07 */


	QProcess* process;
	QProcess* proc;			/* 2005-11-29 */
	
	QString inrad;
	QString inrad2;			/* 2005-11-29 */
	QString errorrad;
	QString program;
	QString version="0.67T  2007-03-07";
	QString rights[1000];		/* 2005-11-29 */
	int rightnbr=0;			/* 2005-11-29 */
	QString flag="FALSK";		/* 2005-11-29 */
	
void frmOlfix::init()
{
//    qDebug("init 1");
    const char *userp = getenv("USER");		/* 2007-03-07 */
    QString usr(userp);			/* 2007-03-07 */
    usr=usr.upper();				/* 2007-03-07 */
    lineEditUser->setText(usr);			/* 2007-03-07 */
    ListView1->setColumnWidth(0,500);		/* 2007-02-11 */
//    ListView1->hideColumn(1);			/* 2007-02-11 */
    qDebug("init 2");
    frmOlfix::getRights();
    frmOlfix::slotGetProgram();
    PushButtonQuit->setFocus();
}

void frmOlfix::slotGetProgram()
{
	const char *userp = getenv("USER");
                QString usr(userp);
	inrad="";
	errorrad="";

	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX huvudprogram
	process->addArgument(usr);		// userid
	process->addArgument( "PRGLST");	// OLFIX funktion

	frmOlfix::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmOlfix::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmOlfix::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );
	
	qDebug("Process Start");
	
	if ( !process->start() ) {
                // error handling
//	    fprintf(stderr,"Problem starta STYRMAN/PRGLST!\n");
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
    qDebug("EndOfProcess");
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
     /* 2005-06-13 Start 	*/
     /* Övriga fel		*/
    i = -1;
    i = errorrad.find( QRegExp("error"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "OLFIXW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
     }
	/* 2005-06-13 End */
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
    
    char *pos1;
    char *pos2;
    char tmp[MAXSTRING];
    char *tmppek;
    int j,k,l,m;
    int pgmfoldnr,mnufoldnr,mnutxtnr;
    int pgmreknare=0;
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
    
    k=0;
    for (j=3;j<i;j++){
	antrad[k]=tmp[j];
	k++;
    };
    i=atoi(antrad);		// i = antal poster
//   qDebug("Antal rader=%d",i);
    
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
	
	QString pgmfold;
	QString mnufold;
	QString txtfold;
	QListViewItem *pgmfolder[30];
	QListViewItem *mnufolder[30];
	QListViewItem *mnutxtfld[30];
	/*************************************************/
	/*    Start 2005-11-29				      */
	/*************************************************/
	int ii = -1;
	for (int i2=0;i2<=rightnbr;i2++) {
	    	ii=rights[i2].find( QRegExp(pgm), 0 );
		if (ii != -1){
		    QString temp=pgm;
		    flag="SANT";
//		    qDebug("Hittat programX nr%d (k=%d)  %s  flag=%s",pgmreknare,k,temp.latin1(),flag.latin1());
		    i2=rightnbr;
		    ii= -1;
		    pgmreknare++;
		}
	}
	/*************************************************/
	/*    End  2005-11-29				*/
	/*************************************************/	
	if (strcmp(prggrptemp,proggrp) != 0){
	    pgmfold=proggrp;
	    pgmfoldnr++;
	    if (flag=="SANT"){				/* 2005-11-29 */
		pgmfolder[pgmfoldnr] = new QListViewItem(ListView1, pgmfold);
	    }
	    strcpy(prggrptemp,proggrp);
	    mnufoldnr=0;
	}
            if (strcmp(mnugrptemp,mnugrp) != 0){
		mnufold=mnugrp;
		mnufoldnr++;
		if(flag=="SANT"){				/* 2005-11-29 */
		    mnufolder[mnufoldnr] = new QListViewItem(pgmfolder[pgmfoldnr] ,mnufold);
		}
		strcpy(mnugrptemp,mnugrp);
		mnutxtnr=0;
	 }
            if (strcmp(mnutxttemp,mnutxt) != 0){
//		qDebug("flag_mnutxt=%s",flag.latin1());
		if (flag=="SANT"){			/* 2005-11-29 */
		    txtfold=mnutxt;
		    mnutxtnr++;
		    mnutxtfld[mnutxtnr] = new QListViewItem(mnufolder[mnufoldnr] ,mnutxt,pgm);
		}
		strcpy(mnutxttemp,mnutxt);
	 }
	 flag="FALSK";
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
    } 					// for ( k=..... slut  
//   ListView1->hideColumn(1);			/* 2007-02-11 */
}

void frmOlfix::ListView1_clicked( QListViewItem * item)
{
    char programnamn[PRGNAMN]="";
    QString prog;
//    ListView1->hideColumn(1);			/* 2007-02-11 */
    
    if(!item){
	return;
    }
     ListView1->setCurrentItem(item);
     if(!item->key(1,TRUE)){
	 return;
     }

     strcpy(programnamn,item->key(1,TRUE));
     prog=programnamn;
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
//	    fprintf(stderr,"Problem starta OLFIXW - %s\n",prog.latin1());	/* 2007-03-07 */
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
		
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX huvudprogram	2004-11-11
	process->addArgument("OLFIX");		// user OLFIX
	process->addArgument( "RGTCHK");	// OLFIX program
	process->addArgument( usr.latin1() );
	process->addArgument( prog.latin1() );
	
	frmOlfix::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnCheckStdout() ) );
	frmOlfix::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnCheckStderr() ) );
	frmOlfix::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfCheckProcess() ) );

	if ( !process->start() ) {
	    // error handling
	    QMessageBox::warning( this, "OLFIX","Kan inte starta RGTCHK!\n" );
	}
}


void frmOlfix::slotEndOfCheckProcess()
{
    int i;
     i = -1;
     i = inrad.find( QRegExp("OK:"), 0 );
     qWarning("slotEndOfCheckProcess(): errorrad=%s inrad=%s i=%d\n",errorrad.latin1(),inrad.latin1(),i);

     if(i != -1){
	 if (program=="BYTFTGW"){
	     frmOlfix::slotRunBytftgProgram(program);
	 }else{
	     frmOlfix::slotRunProgram( program );
	 }
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
			    "2003-05-27\n"
 		             "Version: "+version+"\n"	);
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
	process->addArgument( "./OLFIXHLP" );		// OLFIX program
	
	if ( !process->start() ) {
	    // error handling
	    QMessageBox::warning( this, "OLFIX","Kan inte starta OLFIXHLP!\n" );
	}
}

void frmOlfix::slotRunBytftgProgram( QString prg )
{
    /******************************************************************************/
    /*  Funktion för att kommunicera med BYFTGW, få info om att man byt företag(databas)	*/
    /*		2005-03-03							*/
    /******************************************************************************/
 /*   qDebug("Körs för start av BYFTGW");		*/
           QString prog;
	prog.append("./");
            prog.append(prg);
	inrad="";
	errorrad="";

	process = new QProcess();
	process->addArgument( prog );		// OLFIX program
	frmOlfix::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnBytftgStderr() ) );		
	frmOlfix::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnBytftgStdout() ) );	
	frmOlfix::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfBytftgProcess() ) );

	if ( !process->start() ) {
	    // error handling
	    QMessageBox::warning( this, "OLFIX","Kan inte starta "+prog+"!\n" );
	}
}

void frmOlfix::slotEndOfBytftgProcess()
{
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
}

void frmOlfix::slotDataOnBytftgStderr()
{
   while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmOlfix::slotDataOnBytftgStdout()
{
    int i,l;
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
/*   qDebug("slotDataOnBytftgStdout::inrad=%s",inrad.latin1());		*/
   i = -1;
   i = inrad.find( QRegExp("Databas="), 0 );
   if ( i != -1){   
       l=inrad.length();
       lineEditDatabase->setText(inrad.mid(8,l-8));
   }      
}

	/*************************************************/
	/*    Start 2005-11-29				*/
	/*************************************************/
void frmOlfix::getRights()
{
	const char *userp = getenv("USER");
            QString usr(userp);
	inrad="";
	errorrad="";

	proc = new QProcess();
	proc->addArgument("./STYRMAN");	// OLFIX huvudprogram
	proc->addArgument(usr);			// userid
	proc->addArgument( "RGTLST");		// OLFIX funktion

	frmOlfix::connect( proc, SIGNAL(readyReadStdout() ),this, SLOT(behorDataOnStdout() ) );
	frmOlfix::connect( proc, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmOlfix::connect( proc, SIGNAL(processExited() ),this, SLOT(slotRightEndOfProcess() ) );
	if ( !proc->start() ) {
                // error handling
	    QMessageBox::warning( this, "Start av RGTLST ",
                            "Kan inte starta STYRMAN/RGTLST!\n"
                            );
        }
}

void frmOlfix::slotRightEndOfProcess()
{
    const char *userp = getenv("USER");
    QString usr(userp);

    QString listrad;
    QString behor;	/* behörighet */
    QString anv;		/* användare, user */
    QString funktion;
    rightnbr=0;
    
    char *pos1;
    char *pos2;
    char tmp[MAXSTRING];
    char *tmppek;
    int i,j,k,l,m;
    char antrad[6]="";
    char user[9]="";
    char funk[9]="";

    tmppek=tmp;
    qstrcpy(tmp,inrad2);
    pos1=strstr(tmp,"NR_");
    pos2=strstr(tmp,"_:");
    i=pos2-pos1;
    m=i+2;		// startposition för första userid.
    k=0;
    for (j=3;j<i;j++){
	antrad[k]=tmp[j];
	k++;
    }
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
	
	m=m+l+2;	// position för namn
	l=0;
	for(j = m; j < sizeof(funk) + m; j++){
	    if(tmp[j] != *("_")){
		funk[l]=tmp[j];
		l++;
	    }else{
		funk[l] = *("\0");
		j=sizeof(funk) + m;
	    }
	}
	
	m=m+l+2;	// position för funk
	funktion=funk;
	anv=user;
	anv=anv.upper();
	usr=usr.upper();
//	qDebug("anv=%s usr=%s",anv.latin1(),usr.latin1());
//	if ("TESTARE"==anv){
	if (usr==anv) {
	    if (funktion.right(1)=="W"){
		rightnbr++;
		behor=funk;
		behor=behor.stripWhiteSpace();
		rights[rightnbr]=behor;
//		qDebug("rights[%d]=%s",rightnbr,rights[rightnbr].latin1());
	    }
	}
 	/* rensa user,namn,avd och grupp */
	for (l = 0; l < sizeof(user); l++){
		user[l]=*("\0");
	}
	for (l = 0; l < sizeof(funk); l++){
		funk[l]=*("\0");
	}	
	/* rensa listrad */
	listrad.remove(0,70);
    }
}

void frmOlfix::behorDataOnStdout()
{
    while (proc->canReadLineStdout() ) {
	QString line = proc->readStdout();
	inrad2.append(line);
	inrad2.append("\n");
    }
}
	/*************************************************/
	/*    End       2005-11-29				*/
	/*************************************************/
  
