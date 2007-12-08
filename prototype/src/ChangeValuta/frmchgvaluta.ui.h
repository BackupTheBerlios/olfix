/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                         CHGVALW  -  description
                             -------------------
		     version 0.1
    begin                : Fre 21 febr 2003
    modified	         : Lör   8 dec  2007
    copyright         : (C) 2003 by Jan Pihlgren
    email                 : jan@pihlgren.se
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
    QString hjelpfil;


    
void frmChgValuta::init()
{
    listValuta();			/* 20071208  */
//    LineEditValuta->setFocus();
}

void frmChgValuta::slotGetValuta()
{
	const char *userp = getenv("USER");
                QString usr(userp);

	 inrad="";
	 LineEditValuta->clear();
	 LineEditBeteck->clear();
	 LineEditLand->clear();
	 LineEditKop->clear();
	 LineEditSalj->clear();
   	    
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "VALDSP");	// OLFIX funktion
	process->addArgument(valuta);

	frmChgValuta::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotValDataOnStdout() ) );
	frmChgValuta::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotValDataOnStderr() ) );
            frmChgValuta::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfValProcess() ) );

	if (valuta == "" ){
    	    QMessageBox::warning( this, "CHGVALW",
                      "Valuta saknas \n" );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/VALDSP!\n");
		QMessageBox::warning( this, "CHGVALW",
                            "Kan inte starta STYRMAN/VALDSP! \n" );
	    }   
	}
}

void frmChgValuta::slotChgValuta()
{
 /************************************************************************/
/*	Uppdatera databasen						*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);

	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "VALCHG");	// OLFIX funktion
	process->addArgument(valuta);
	process->addArgument(land);
	process->addArgument(salj);
	process->addArgument(kop);
	process->addArgument(beteckning);

	frmChgValuta::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotChgDataOnStdout() ) );
	frmChgValuta::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotChgDataOnStderr() ) );
            frmChgValuta::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfChgProcess() ) );

	if (valuta == "" || beteckning ==""){
    	    QMessageBox::warning( this, "CHGVALW",
                      "Valuta och/eller beteckning saknas \n" );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/VALCHG!\n");
		QMessageBox::warning( this, "CHGVALW",
                            "Kan inte starta STYRMAN/VALCHG! \n" );
	    }
	}     
}

void frmChgValuta::slotValutaEntered()
{
    valuta=LineEditValuta->text();
    valuta=valuta.upper();
    LineEditValuta->setText((valuta));
//    LineEditBeteck->setFocus();
}

void frmChgValuta::slotBeteckningEntered()
{
    beteckning=LineEditBeteck->text();
//    LineEditLand->setFocus();
}

void frmChgValuta::slotLandEntered()
{
    land=LineEditLand->text();
//   LineEditKop->setFocus(); 
}

void frmChgValuta::slotKopEntered()
{
    kop=LineEditKop->text();
//    LineEditSalj->setFocus();
}

void frmChgValuta::slotSaljEntered()
{
    salj=LineEditSalj->text();
//    PushButtonUpdate->setFocus();
}

void frmChgValuta::slotPushButtonGet_clicked()
{
    frmChgValuta::slotGetValuta();
    LineEditValuta->setFocus();
}


void frmChgValuta::slotValDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmChgValuta::slotValDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmChgValuta::slotEndOfValProcess()
{
    int h;
    h = -1;
    h = errorrad.find( QRegExp("Error:"), 0 );
    if (h != -1) {
	QMessageBox::critical( this, "CHGVALW",
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

    int i = inrad.find( QRegExp("1:"), 0 );
    int j = inrad.find( QRegExp("2:"), 0 );
    int k = inrad.find( QRegExp("3:"), 0 );
    int l = inrad.find( QRegExp("4:"), 0 );
    int n = inrad.find(QRegExp("5:"), 0);

    m=j-i;
    if (i != -1){
	valuta=inrad.mid(i+2,m-2);
	valuta = valuta.stripWhiteSpace();
	LineEditValuta->setText(valuta);
    }
    m=k-j;
    if ( j != -1){
	land=inrad.mid(j+2,m-2);
	land=land.stripWhiteSpace();
	LineEditLand->setText(land);
    }
    m=l-k;
    if ( k != -1){
	beteckning=inrad.mid(k+2,m-2);
	beteckning=beteckning.stripWhiteSpace();
	LineEditBeteck->setText(beteckning);
    }
     m=n-l;
    if ( l != -1){
	kop=inrad.mid(l+2,m-2);
	kop=kop.stripWhiteSpace();
	LineEditKop->setText(kop);
    }
    m=inrad.length() - n;
    if ( n != -1){
	salj=inrad.mid(n+2,m-2);
	salj=salj.stripWhiteSpace();
	LineEditSalj->setText(salj);
    } 
        LineEditBeteck->setFocus();
}

void frmChgValuta::slotChgDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmChgValuta::slotChgDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmChgValuta::slotEndOfChgProcess()
{
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "CHGALW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
     }
     i = -1;
     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	QMessageBox::information( this, "CHGVALW",
		"Uppdatering OK!\n"+errorrad
	);
	LineEditValuta->clear();
	LineEditBeteck->clear();
	LineEditLand->clear();
	LineEditKop->clear();
	LineEditSalj->clear();
	LineEditLand->setFocus();
	inrad="";
	i = -1;
            LineEditValuta->setFocus();
    }
}

void frmChgValuta::listValuta()
{
	const char *userp = getenv("USER");
	QString usr(userp);
	    
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// valutaid
	process->addArgument( "VALLST");	// OLFIX funktion

	frmChgValuta::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotChgDataOnStdout() ) );
	frmChgValuta::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotChgDataOnStderr() ) );
                frmChgValuta::connect( process, SIGNAL(processExited() ),this, SLOT(slotListaEndOfProcess() ) );

	if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/VALLST!\n");
		QMessageBox::warning( this, "DSPVALW",
                            "Kan inte starta STYRMAN/VALLST! \n" );
	    }   	
}

void frmChgValuta::slotListaEndOfProcess()
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
    int j,k,l,m;
    char antrad[6]="";
    char valuta[4]="";
    char beteckning[16]="";
    char kop[8]="";
    char salj[8]="";
    char land[16]="";
    /*                                                   Start     2007-12-08                                         */    
    QString host="";
    int l1,l2,m1,m2;
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
    /*                                                End         2007-12-08                                         */
    
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

void frmChgValuta::slotPickupValuta( QListViewItem * item)
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
     PushButtonGet->setFocus();
}

void frmChgValuta::pushBtnHelp_clicked()
{
	inrad="";
	frmChgValuta::readResursFil();		// Hämta path till hjälpfilen

	int i1 = hjelpfil.find( QRegExp(".html"), 0 );
//	int i2 = hjelpfil.length();
	hjelpfil=hjelpfil.left(i1);
	hjelpfil=hjelpfil+"_EKONOMI.html";
	hjelpfil=hjelpfil+"#CHGVALUTA";		// Lägg till position
//	qDebug("hjelpfil=%s",hjelpfil.latin1());

	process = new QProcess();
	process->addArgument( "./OLFIXHLP" );	// OLFIX program
	process->addArgument(hjelpfil);

	if ( !process->start() ) {
	    // error handling
	    QMessageBox::warning( this, "OLFIX","Kan inte starta OLFIXHLP!\n" );
	}
	LineEditValuta->setFocus();
}

void frmChgValuta::readResursFil()
{
    /*****************************************************/
    /*  Läs in .olfixrc filen h�r			               	*/
    /* Plocka fram var hjälpfilen finns			*/
    /*****************************************************/

    QStringList lines;
    QString homepath;
    homepath=QDir::homeDirPath();
/*    qDebug("Home Path=%s",homepath.latin1());		*/

    QFile f1( homepath+"/.olfixrc" );
   if ( f1.open( IO_ReadOnly ) ) {
        QTextStream stream( &f1 );
        QString line;
        int rad = -1;
        while ( !stream.eof() ) {
            line = stream.readLine(); /* line of text excluding '\n'	*/
	rad=line.find( QRegExp("HELPFILE="), 0 );
	if(rad == 0){
	    hjelpfil=line;
/*	    qDebug("hjelpfil=%s",hjelpfil.latin1());		*/
	    hjelpfil=(hjelpfil.right(hjelpfil.length() - 9));
/*	    qDebug("hjelpfil=%s",hjelpfil.latin1());		*/
	}
            lines += line;
        }
    }
    f1.close();
}


