/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                          DELUSRW  -  description
                             -------------------
		     version 0.2
    begin     	: Sön 2 febr 2003
    Modified	: Fre 12 nov 2004
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
#include <qregexp.h>
#include <qlistview.h>

#define MAXSTRING 5000

	QProcess* process;
	QString inrad;
	QString inrad_u;
	QString listrad;
	QString errorrad;
            QString Userid;
            QString EndFlag;
	QString nbrrows;

void frmDelUsr::slotPushButtonGet_clicked()
{
    LineEditNamn->clear();
    LineEditAvd->clear();
    LineEditGrupp->clear();
    ListViewBehor->clear();
    inrad="";
    inrad_u="";
    errorrad="";

    frmDelUsr::slotGetRightData();    
}

void frmDelUsr::slotGetUserData()
{
        	const char *userp = getenv("USER");
            QString usr(userp);

	 inrad="";
	 errorrad="";
            process = new QProcess();
	process->addArgument("./STYRMAN");
	process->addArgument(usr.latin1());		// user OLFIX
	process->addArgument( "USERDSP");		// OLFIX program
	process->addArgument( Userid.latin1() );
	
	frmDelUsr::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotUsrDataOnStdout() ) );
            frmDelUsr::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfUsrProcess() ) );
            if ( !process->start() ) {
                // error handling
	QMessageBox::warning( this, "OLFIX - USERDEL",
                            "Kan inte starta USERDSP!\n"
                            );
	}
// 	qWarning( "slotGetUserData: usr=%s  Userid=%s\n", usr.latin1(),Userid.latin1() );

}

void frmDelUsr::slotGetRightData()
{
    	const char *userp = getenv("USER");
            QString usr(userp);
	    
//	qWarning( "slotGetRightData: Userid=%s  usr=%s\n", Userid.latin1(),usr.latin1() );
	 inrad="";
	 errorrad="";

            process = new QProcess();
	process->addArgument("./STYRMAN");
	process->addArgument(usr.latin1());	
	process->addArgument( "RGTDSP");	// OLFIX program
	process->addArgument( Userid.latin1() );
	frmDelUsr::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotRightDataOnStdout() ) );
            frmDelUsr::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfRightProcess() ) );

            if ( !process->start() ) {
                // error handling
	QMessageBox::warning( this, "OLFIX - RGTDSP",
                            "Kan inte starta RGTDSP!\n"
                            );
	}
//	qWarning( "slotGetRightData: Userid=%s \n", Userid.latin1() );
}

void frmDelUsr::slotUseridEntered()
{
    Userid=LineEditUserid->text();
    Userid=Userid.upper();
    LineEditUserid->setText((Userid));
/****************************************************************/       
/*	Start 		2004-11-12    				*/
/****************************************************************/    
    if (Userid == "OLFIX"){
	QMessageBox::warning( this, "OLFIX - DELUSRW",
                            "Om du tar bort användaren OLFIX slutar programmet OLFIX att fungera!\n"
                            );
    }
/****************************************************************/       
/*	Slut 		2004-11-12    				*/
/****************************************************************/    

    PushButtonGet->setFocus();
}

void frmDelUsr::slotRightDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
//	qWarning( "slotRightDataOnStdout: Userid=%s \n", inrad.latin1() );
    }
}

void frmDelUsr::slotEndOfRightProcess()
{
    QListViewItem* item;
    char *pos1;
    char *pos2;
    char tmp[MAXSTRING];
    char *tmppek;
    int i,j,k,l,m;
    char antrad[6]="";
    char user[9]="";
    char funk[9]="";

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
//    fprintf(stderr," i = %d\n",i);
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
	for(j = m; j < sizeof(funk) + m; j++){
	    if(tmp[j] != *("_")){
		funk[l]=tmp[j];
		l++;
	    }else{
		funk[l] = *("\0");
		j=sizeof(funk) + m;
	    }
	}
//	fprintf(stdout,"%s  ",funk);
	m=m+l+2;	// position för funk
	item = new QListViewItem(ListViewBehor,user,funk);
 	/* rensa user,namn,avd och grupp */
	strcpy(user,"");
	strcpy(funk,"");
/*   	for (l=0;l<sizeof(user);l++)
		user[l]=*("\0");
	for (l=0;l<sizeof(funk);l++)
		funk[l]=*("\0");
*/
	/* rensa listrad */
//	listrad.remove(0,70);
    }   
    frmDelUsr::slotGetUserData();
}

void frmDelUsr::slotUsrDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad_u.append(line);
	inrad_u.append("\n");
//	qWarning( "slotUsrDataOnStdout: Userid=%s \n", inrad_u.latin1() );
    }
}

void frmDelUsr::slotEndOfUsrProcess()
{
    int m;
    QString user;
    QString namn;
    QString avd;
    QString grupp;
    
    int i = inrad_u.find( QRegExp("1:"), 0 ); 
    int j = inrad_u.find( QRegExp("2:"), 0 ); 
    int k = inrad_u.find( QRegExp("3:"), 0 ); 
    int l = inrad_u.find( QRegExp("4:"), 0 );
    
    m=j-i;
    if (i != -1){
	user=inrad_u.mid(i+2,m-2);
	LineEditUserid->setText(user);
    }    
    m=k-j;
    if ( j != -1){
	namn=inrad_u.mid(j+2,m-2);
	LineEditNamn->setText(namn);
    }    
    m=l-k;
    if ( k != -1){
	avd=inrad_u.mid(k+2,m-2);
	LineEditAvd->setText(avd);
    }    
    m=inrad_u.length() - l;
    if ( l != -1){
	grupp=inrad_u.mid(l+2,m-2);
	LineEditGrupp->setText(grupp);
    }    
}

void frmDelUsr::slotPushButtonOK_clicked()
{
   char user[9];
   char fnc[9];
    int i = 0;
    
    inrad="";
    inrad_u="";
    errorrad="";

    QListViewItem *item;
    item=ListViewBehor->findItem(Userid,0,ExactMatch);
    strcpy(user,item->key(0,TRUE));
 //   fprintf(stdout,"user=%s\n",user);

    while (item){
	i++;
     strcpy(fnc,item->key(1,TRUE));
//         fprintf(stdout,"fnc(%d)=%s\n",i,fnc);
	 frmDelUsr::slotDelRightData( user, fnc);
	 item=item->itemBelow();
     }
    frmDelUsr::slotDelUsrData( user );
}

void frmDelUsr::slotDelRightData(QString anvID,QString fncID)
{
    	const char *userp = getenv("USER");
            QString usr(userp);
	 inrad="";
	 errorrad="";
	    
//	fprintf(stderr,"slotDelRightData: anvID=%s  fncID=%s\n", anvID.latin1(),fncID.latin1() );	
            process = new QProcess();
	process->addArgument("./STYRMAN");
	process->addArgument(usr.latin1());	
	process->addArgument( "RGTDEL");	// OLFIX program
	process->addArgument( anvID.latin1() );
	process->addArgument( fncID.latin1() );
	frmDelUsr::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotRgtDelDataOnStdout() ) );
	frmDelUsr::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotRgtDelDataOnStderr() ) );
            frmDelUsr::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfRgtDelProcess() ) );

            if ( !process->start() ) {
                // error handling
	QMessageBox::warning( this, "OLFIX - RGTDEL",
                            "Kan inte starta RGTDEL!\n"
                            );
	}
//	fprintf(stderr, "slotDelRightData, process startad: fncID=%s \n", fncID.latin1() );
}


void frmDelUsr::slotEndOfRgtDelProcess()
{
    int i=-1;
    int j=-1;

//    qDebug("inrad=%s",inrad.latin1());
      i = -1;
      i = errorrad.find( QRegExp("Error:"), 0 );
//	qDebug("frmDelUsr-errorrad=%s i=%d\n",errorrad.latin1(),i);
      if (i == 0) {
	QMessageBox::critical( this, "OLFIX - RGTDEL",
		"ERROR!\n"+errorrad
		);
	            errorrad="";
		i = -1;
      }
      j = -1;
      j = errorrad.find( QRegExp("Error: RGTDEL_Deleted error:"), 0 );
      if(j == 0){
	QMessageBox::information( this, "RGTDEL - Error!",
		"Borttagningen av behörighet misslyckades\n"
		);
	errorrad="";
	j = -1;
       }
}


void frmDelUsr::slotRgtDelDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}


void frmDelUsr::slotRgtDelDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}


void frmDelUsr::slotDelUsrData( QString anvID )
{
    	const char *userp = getenv("USER");
            QString usr(userp);
	    
//	fprintf(stderr,"slotDelUsrData: anvID=%s", anvID.latin1() );
	 inrad="";
	 errorrad="";
	
            process = new QProcess();
	process->addArgument("./STYRMAN");
	process->addArgument(usr.latin1());	
	process->addArgument( "USERDEL");	// OLFIX program
	process->addArgument( anvID.latin1() );
	frmDelUsr::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotUsrDelDataOnStdout() ) );
	frmDelUsr::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotUsrDelDataOnStderr() ) );
            frmDelUsr::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfUsrDelProcess() ) );

            if ( !process->start() ) {
                // error handling
	QMessageBox::warning( this, "OLFIX - USERDEL",
                            "Kan inte starta RGTDEL!\n"
                            );
	}
//	fprintf(stderr, "slotDelUsrData, process startad: anvID=%s \n", anvID.latin1() );
}


void frmDelUsr::slotUsrDelDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}


void frmDelUsr::slotUsrDelDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}


void frmDelUsr::slotEndOfUsrDelProcess()
{
    int i=-1;
    int j=-1;

//    qDebug("inrad=%s",inrad.latin1());
      i = -1;
      i = errorrad.find( QRegExp("Error:"), 0 );
//	qDebug("frmDelUsr-errorrad=%s i=%d\n",errorrad.latin1(),i);
      if (i == 0) {
	QMessageBox::critical( this, "OLFIX - USERDEL",
		"ERROR!\n"+inrad
		);
	            inrad="";
		i = -1;
      }
      j = -1;
      j = errorrad.find( QRegExp("Error: USERDEL_Deleted error:"), 0 );
      if(j == 0){
	QMessageBox::information( this, "USERDEL - Error!",
		"Borttagningen av användare misslyckades\n"
		);
	inrad="";
	j = -1;
       }
       i = -1;
       i = inrad.find( QRegExp("OK: USERDEL_"), 0 );
       if(i == 0){
	QMessageBox::information( this, "USERDEL - RGTDEL",
		"Uppdatering OK!\n" 
		);
    }
}
