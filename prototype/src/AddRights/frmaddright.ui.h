/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
			  ADDRGTW  -  description
			     -------------------
		     version 0.5
    begin                : Tis 27 maj 2003
    copyright        : (C) 2003 by Jan Pihlgren
    modified	        : Mån 26 april 2007
    email                : jan@pihlgren.se
 ***************************************************************************/
/* Lagt till "lostFocus" i Funk och LineEditUserid (2003-05-27/japi) */
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
#include <qlistview.h>
#define MAXSTRING 15000

QProcess* process;
QString inrad;
QString errorrad;
QString* rad;
QString Userid;
QString Funk;


void frmAddRight::init()
{
    LineEditUserid->clear();
    LineEditFunk->clear();
    frmAddRight::slotGetFunc();
    LineEditUserid->setFocus();
}

void frmAddRight::slotUseridEntered()
{
    Userid=LineEditUserid->text();
    Userid=Userid.upper();
    LineEditUserid->setText((Userid));
    checkUser(Userid);
}

void frmAddRight::slotRightEntered()
{
    Funk=LineEditFunk->text();
    Funk=Funk.upper();
    LineEditFunk->setText((Funk));
}

void frmAddRight::slotAddRight()
{
    /************************************************************************/
    /*	Uppdatera databasen						*/
    /************************************************************************/
    const char *userp = getenv("USER");
    QString usr(userp);
    
    process = new QProcess();
    process->addArgument("./STYRMAN");	// OLFIX styrprogram
    process->addArgument(usr);		// Userid
    process->addArgument( "RGTADD");	// OLFIX funktion
    process->addArgument(Userid);
    process->addArgument(Funk);
    
    frmAddRight::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
    frmAddRight::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
    frmAddRight::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );
    
    
    if (Userid == "" || Funk ==""){
	QMessageBox::warning( this, "ADDRGTW",
			      "Userid och/eller Behörighet saknas \n" );
    }else{
	if ( !process->start() ) {
	    // error handling
	    qDebug("Problem starta STYRMAN/RGTADD!");
	    QMessageBox::warning( this, "ADDRGTW",
				  "Kan inte starta STYRMAN/RGTADD! \n" );
	}   
    }
}

void frmAddRight::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
	//	qWarning( "slotDataOnStdout: Userid=%s \n", inrad.latin1() );
    }
}

void frmAddRight::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
	//	qWarning( "slotDataOnErrout: Userid=%s \n", inrad.latin1() );
    }
    
}


void frmAddRight::slotEndOfProcess()
{
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "ADDRGTW",
			       "ERROR!\n"+errorrad
			       );
	errorrad="";
	i = -1;
    }
    i = -1;
    i = inrad.find( QRegExp("OK:"), 0 );
    if (i != -1) {
	QMessageBox::information( this, "ADDRGTW",
				  "Uppdatering OK!\n"+errorrad
				  );
	LineEditUserid->clear();
	LineEditFunk->clear();
	LineEditUserid->setFocus();
	inrad="";
	i = -1;
    }
}

void frmAddRight::slotGetFunc()
{
    const char *userp = getenv("USER");
    QString usr(userp);
    QString bibl;
    
    inrad="";
    errorrad="";
        
    process = new QProcess();
    process->addArgument("./STYRMAN");
    process->addArgument(usr);		// userid
    process->addArgument( "TRNSLST");	// OLFIX funktion
    
//    qDebug("Starta STYRMAN/TRNSLST! %s\n",usr.latin1());
    
    frmAddRight::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
    frmAddRight::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
    frmAddRight::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfGetFuncfProcess() ) );
    
    if ( !process->start() ) {
	// error handling
//	qDebug("Problem starta STYRMAN/TRNSLST!\n");
	QMessageBox::warning( this, "Start av TRNSLST ",
			      "Kan inte starta STYRMAN/TRNSLST!\n"
			      );
    }    
}

void frmAddRight::slotEndOfGetFuncfProcess() 
{
    QListViewItem* item;
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "ADDRGTW",
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
	item = new QListViewItem(ListViewBehor_2,trnsid,benamn);
	// 	 rensa user,namn,avd och grupp 
	for (l=0;l<sizeof(trnsid);l++)
	    trnsid[l]=*("\0");
	for (l=0;l<sizeof(benamn);l++)
	    benamn[l]=*("\0");
	//	 rensa listrad
	listrad.remove(0,70);
    }
}


void frmAddRight::slotPickupFunc( QListViewItem * item)
{
    char func[9]="";
    //    qDebug("PickupFunc\n");
    if(!item){
	return;
    }
    ListViewBehor_2->setCurrentItem(item);
    if(!item->key(0,TRUE)){
	return;
    }
    
    strcpy(func,item->key(0,TRUE));
    Funk=func;
    LineEditFunk->setText((Funk));
}

void frmAddRight::checkUser( QString anv )
{
    const char *userp = getenv("USER");
    QString usr(userp);
    
    inrad="";
    errorrad="";
        
    process = new QProcess();
    process->addArgument("./STYRMAN");
    process->addArgument(usr);		// userid, den inloggade
    process->addArgument( "USERDSP");	// OLFIX funktion
    process->addArgument(anv);		// användarid för den som ska få behörighet
    
//    qDebug("checkUser::anv=%s",anv.latin1());
    
    frmAddRight::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
    frmAddRight::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
    frmAddRight::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfCheckUserProcess() ) );
    
    if ( !process->start() ) {
	// error handling
	qDebug("Problem starta STYRMAN/USERDSP!\n");
	QMessageBox::warning( this, "Start av USERDSP ",
			      "Kan inte starta STYRMAN/USERDSP!\n"
			      );
    }  
}

void frmAddRight::slotEndOfCheckUserProcess(){
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::warning( this, "ADDRGTW",
			       /*"ERROR!\n"+*/errorrad
			       );
	errorrad="";
	i = -1;
	LineEditUserid->setFocus();
	LineEditUserid->selectAll();
	Userid="";
	return;
    }else{
	return;
    }
}

void frmAddRight::checkFunction( QString function )
{
    bool flag=FALSE;
    QString i="";
    if( !ListViewBehor_2->findItem( function,0)) {
	flag=FALSE;
    }else{
	flag=TRUE;
    }
    if(flag==FALSE){
	qDebug("%s finns inte!",function.latin1());
    }
}
