/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
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

#define MAXSTRING 5000

	QProcess* process;
	QString inrad;
	QString inrad_u;
	QString listrad;
            QString Userid;
            QString EndFlag;


void frmDspUsr::slotPushButtonOK_clicked()
{
    LineEditNamn->clear();
    LineEditAvd->clear();
    LineEditGrupp->clear();
    ListBoxBehor->clear();
    inrad="";
    inrad_u="";

    frmDspUsr::slotGetRightData();     
}


void frmDspUsr::slotGetUserData()
{
        	const char *userp = getenv("USER");
            QString usr(userp);

            process = new QProcess();
	process->addArgument("./STYRMAN");
	process->addArgument(usr.latin1());		// user OLFIX
	process->addArgument( "USERDSP");	// OLFIX program
	process->addArgument( Userid.latin1() );
	frmDspUsr::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotUsrDataOnStdout() ) );
            frmDspUsr::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfUsrProcess() ) );
            if ( !process->start() ) {
                // error handling
	QMessageBox::warning( this, "OLFIX - USERDSP",
                            "Kan inte starta USERDSP!\n"
                            );
	}
// 	qWarning( "slotGetUserData: usr=%s  Userid=%s\n", usr.latin1(),Userid.latin1() );
}

void frmDspUsr::slotGetRightData()
{
    	const char *userp = getenv("USER");
            QString usr(userp);
	    
//	qWarning( "slotGetRightData: Userid=%s  usr=%s\n", Userid.latin1(),usr.latin1() );
	
            process = new QProcess();
	process->addArgument("./STYRMAN");
	process->addArgument(usr.latin1());	
	process->addArgument( "RGTDSP");	// OLFIX program
	process->addArgument( Userid.latin1() );
	frmDspUsr::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotRightDataOnStdout() ) );
            frmDspUsr::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfRightProcess() ) );

            if ( !process->start() ) {
                // error handling
	QMessageBox::warning( this, "OLFIX - RGTDSP",
                            "Kan inte starta RGTDSP!\n"
                            );
	}
//	qWarning( "slotGetRightData: Userid=%s \n", Userid.latin1() );
}

void frmDspUsr::slotUseridEntered()
{
    Userid=LineEditUserid->text();
    Userid=Userid.upper();
    LineEditUserid->setText((Userid));
}

void frmDspUsr::slotRightDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
//	qWarning( "slotRightDataOnStdout: Userid=%s \n", inrad.latin1() );
    }
}


void frmDspUsr::slotEndOfRightProcess()
{
//    QString listrad;
//    rad=&inrad;
//    inrad.latin1();
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
	listrad.append(user);
	while(listrad.length() <10)
	    listrad.append(" ");
	listrad.append(funk);

	ListBoxBehor->insertItem(listrad);
 	/* rensa user,namn,avd och grupp */
   	for (l=0;l<sizeof(user);l++)
		user[l]=*("\0");
	for (l=0;l<sizeof(funk);l++)
		funk[l]=*("\0");
	/* rensa listrad */
	listrad.remove(0,70);
    }   
    frmDspUsr::slotGetUserData();
//    EndFlag="J";
//    fprintf(stderr,"Klart!\n");
}


void frmDspUsr::slotUsrDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad_u.append(line);
	inrad_u.append("\n");
//	qWarning( "slotUsrDataOnStdout: Userid=%s \n", inrad_u.latin1() );
    }
}


void frmDspUsr::slotEndOfUsrProcess()
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
