/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                          DSPVALW  -  description
                             -------------------
		     version 0.1
    begin                	: Fre 21 febr 2003
    modified		: Fre   7 dec  2007
    copyright           	 : (C) 2003 by Jan Pihlgren
    email                	: jan@pihlgren.se
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
#define MAXSTRING 5000

    QProcess* process;
    QString inrad;
    QString* rad;
    QString errorrad;
    QString valuta;
    QString beteckning;
    QString land;
    QString kop;
    QString salj;

void frmDspValuta::init()
{
    listValuta();
    LineEditValuta->setFocus();
}

void frmDspValuta::slotGetValuta()
{
	const char *userp = getenv("USER");
	QString usr(userp);

	 LineEditValuta->clear();
	 LineEditBeteck->clear();
	 LineEditLand->clear();
	 LineEditKop->clear();
	 LineEditSalj->clear();
   	    
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// valutaid
	process->addArgument( "VALDSP");	// OLFIX funktion
	process->addArgument(valuta);

	frmDspValuta::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmDspValuta::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmDspValuta::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );

	if (valuta == "" ){
    	    QMessageBox::warning( this, "DSPVALW",
                      "Valuta saknas \n" );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/VALDSP!\n");
		QMessageBox::warning( this, "DSPVALW",
                            "Kan inte starta STYRMAN/VALDSP! \n" );
	    }   
	}
}

void frmDspValuta::LineEditValuta_returnPressed()
{
    valuta=LineEditValuta->text();
    valuta=valuta.upper();
    LineEditValuta->setText((valuta));
    PushButtonGet->setFocus();
}


void frmDspValuta::PushButtonGet_clicked()
{
    inrad="";
    errorrad="";
    land="";
    beteckning="";
    kop="";
    salj="";
    
    LineEditValuta->setFocus();

    frmDspValuta::slotGetValuta();
}

void frmDspValuta::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmDspValuta::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmDspValuta::slotEndOfProcess()
{
    int h;
    h = -1;
    h = errorrad.find( QRegExp("Error:"), 0 );
//    qDebug("Error:",errorrad);
         if (h != -1) {
	QMessageBox::critical( this, "DSPVALW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	h = -1;
     }
    int m;
    QString valuta;
    QString land;
    QString beteckning;
    QString kop;
    QString salj;

 /*                                                   Start     2007-12-07                                         
    int l1,l2,m1,m2;
    QString host="";
    m1=inrad.find( QRegExp("host="), 0 );
    m2=inrad.find( QRegExp("NR_"), 0 );
    l1=m2-(m1+5);
    l2=m2-m1;
    host=inrad.mid(5,l1);
    inrad=inrad.mid(m2,inrad.length()-m2);
    
   qDebug("host=%s m1=%d m2=%d l1=%d l2=%d\n",host.latin1(),m1,m2,l1,l2);
    if(host != "127.0.0.1 "){
	 if(host != "localhost "){
	     textLabel1->setText("<u><b>Host</b></u>\n");
	     textLabelHostName->setText(host);
	 }
    }else{
	textLabel1->setText("");
    }
                                                End         2007-12-07                                         */

    int i = inrad.find( QRegExp("1:"), 0 );
    int j = inrad.find( QRegExp("2:"), 0 );
    int k = inrad.find( QRegExp("3:"), 0 );
    int l = inrad.find( QRegExp("4:"), 0 );
    int n = inrad.find(QRegExp("5:"),0);

    m=j-i;
    if (i != -1){
	valuta=inrad.mid(i+2,m-2);
	LineEditValuta->setText(valuta);
    }
    m=k-j;
    if ( j != -1){
	land=inrad.mid(j+2,m-2);
	LineEditLand->setText(land);
    }
    m=l-k;
    if ( k != -1){
	beteckning=inrad.mid(k+2,m-2);
	LineEditBeteck->setText(beteckning);
    }
     m=n-l;
    if ( l != -1){
	kop=inrad.mid(l+2,m-2);
	LineEditKop->setText(kop);
    }
    m=inrad.length() - n;
    if ( n != -1){
	salj=inrad.mid(n+2,m-3);
	LineEditSalj->setText(salj);
    } 
        LineEditValuta->setFocus();
}

void frmDspValuta::listValuta()
{
	const char *userp = getenv("USER");
	QString usr(userp);
	    
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// valutaid
	process->addArgument( "VALLST");	// OLFIX funktion

	frmDspValuta::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmDspValuta::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
                frmDspValuta::connect( process, SIGNAL(processExited() ),this, SLOT(slotListaEndOfProcess() ) );

	if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/VALLST!\n");
		QMessageBox::warning( this, "DSPVALW",
                            "Kan inte starta STYRMAN/VALLST! \n" );
	    }   	
}

void frmDspValuta::slotListaEndOfProcess()
{
       QListViewItem* item;
    int i;
    
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "LSTVALW",
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
    int j,k,l,m,m1,m2,l1,l2;
    char antrad[6]="";
    char valuta[4]="";
    char beteckning[16]="";
    char kop[8]="";
    char salj[8]="";
    char land[16]="";
    QString host="";
    /*                                                   Start     2007-12-07                                         */
    m1=inrad.find( QRegExp("host="), 0 );
    m2=inrad.find( QRegExp("NR_"), 0 );
    l1=m2-(m1+5);
    l2=m2-m1;
    host=inrad.mid(5,l1);
    inrad=inrad.mid(m2,inrad.length()-m2);
    
//   qDebug("host=%s m1=%d m2=%d l1=%d l2=%d\n",host.latin1(),m1,m2,l1,l2);
    if(host != "127.0.0.1 "){
	 if(host != "localhost "){
	     textLabel1->setText("<u><b>Host</b></u>\n");
	     textLabelHostName->setText(host);
	 }
    }else{
	textLabel1->setText("");
    }
    /*                                                End         2007-12-07                                         */
    
    tmppek=tmp;
    qstrcpy(tmp,inrad);
    pos1=strstr(tmp,"NR_");
    pos2=strstr(tmp,"_:");
    i=pos2-pos1;
    m=i+2;		// startposition för första valutaid.
//    fprintf(stdout,"i=%d  m=%d",i,m);
    k=0;
    for (j=3;j<i;j++){
	antrad[k]=tmp[j];
	k++;
    };
    i=atoi(antrad);		// i = antal poster
    for (k = 1;k <= i; k++){	// gå igenom alla raderna / posterna
	l=0;
	for(j = m; j < sizeof(valuta) + m; j++){
	    if(tmp[j] != *("_")){
		valuta[l]=tmp[j];
		l++;
	    }else{
		valuta[l] = *("\0");
		j=sizeof(valuta) + m;
	    }
	}
//	fprintf(stdout,"%s  ",valuta);
	m=m+l+2;	// position för land
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
//	fprintf(stdout,"%s  ",land);
	m=m+l+2;	// position för kop
	l=0;
	for(j = m; j < sizeof(kop) + m; j++){
	    if(tmp[j] != *("_")){
		kop[l]=tmp[j];
		l++;
	    }else{
		kop[l] = *("\0");
		j=sizeof(kop) + m;
	    }
	}
//	fprintf(stdout,"%s  ",kop);
	m=m+l+2;	// position för salj
	l=0;
	for(j = m; j < sizeof(salj) + m; j++){
	    if(tmp[j] != *("_")){
		salj[l]=tmp[j];
		l++;
	    }else{
		salj[l] = *("\0");
		j=sizeof(salj) + m;
	    }
	}
//	fprintf(stdout,"%s\n  ",salj);			
	m=m+l+2;	// position för beteckning
	l=0;
	for(j = m; j < sizeof(beteckning) + m; j++){
	    if(tmp[j] != *("_")){
		beteckning[l]=tmp[j];
		l++;
	    }else{
		beteckning[l] = *("\0");
		j=sizeof(beteckning) + m;
	    }
	}
//	fprintf(stdout,"%s\n  ",beteckning);	
	m=m+l+2;
		
	item = new QListViewItem(listViewValuta,valuta,beteckning);
// 	 rensa valuta,beteckning,kop och salj 
  	for (l=0;l<sizeof(valuta);l++)
		valuta[l]=*("\0");
	for (l=0;l<sizeof(beteckning);l++)
		beteckning[l]=*("\0");
/*	
	for (l=0;l<sizeof(kop);l++)
		kop[l]=*("\0");
	for (l=0;l<sizeof(salj);l++)
		salj[l]=*("\0");
*/		
	listrad.remove(0,70);
    }   
}

void frmDspValuta::slotPickupValuta( QListViewItem * item)
{
    char val[4]="";
//    qDebug("PickupValuta\n");
    if(!item){
	return;
    }
     listViewValuta->setCurrentItem(item);
     if(!item->key(0,TRUE)){
	 return;
     }

     strcpy(val,item->key(0,TRUE));	// = Valuta
     valuta=val;
     LineEditValuta->setText(valuta);
     LineEditValuta->setFocus();
}
