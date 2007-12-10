/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                          DSPUSRW  -  description
                             -------------------
                     version 0.4
    begin       	: Sön     2 febr 2003
    Modified    	: Mån 10 dec  2007
    copyright            	: (C) 2003 by Jan Pihlgren
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
#include <qregexp.h>

#define MAXSTRING 5000


   QProcess* process;
   QProcess* processlist;
   QString inrad;
   QString inradlista;
   QString errorradlista;
   QString inrad_u;
   QString listrad;
   QString userid;
   QString EndFlag;
   QString hjelpfil;

void frmDspUser::init()
{
//    ListBoxBehor->hide();
    frmDspUser::listUsers();
    listViewUser->setFocus();
}

void frmDspUser::slotPushButtonOK_clicked()
{
    LineEditNamn->clear();
    LineEditAvd->clear();
    LineEditGrupp->clear();
    ListBoxBehor->clear();
    inrad="";
    inrad_u="";

    frmDspUser::slotGetRightData();     
}


void frmDspUser::slotGetUserData()
{
        	const char *userp = getenv("USER");
	QString usr(userp);

	inrad_u="";
	process = new QProcess();
	process->addArgument("./STYRMAN");
	process->addArgument(usr);		// user OLFIX
	process->addArgument( "USERDSP");	// OLFIX program
	process->addArgument( userid );
	frmDspUser::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotUsrDataOnStdout() ) );
            frmDspUser::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfUsrProcess() ) );
            if ( !process->start() ) {
                // error handling
	QMessageBox::warning( this, "OLFIX - USERDSP",
                            "Kan inte starta USERDSP!\n"
                            );
	}
// 	qWarning( "slotGetUserData: usr=%s  userid=%s\n", usr.latin1(),userid.latin1() );
}

void frmDspUser::slotGetRightData()
{
    	const char *userp = getenv("USER");
	QString usr(userp);
	    
//	qWarning( "slotGetRightData: userid=%s  usr=%s\n", userid.latin1(),usr.latin1() );
	inrad="";
	
	process = new QProcess();
	process->addArgument("./STYRMAN");
	process->addArgument(usr);	
	process->addArgument( "RGTDSP");	// OLFIX program
	process->addArgument( userid );
	frmDspUser::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotRightDataOnStdout() ) );
            frmDspUser::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfRightProcess() ) );

            if ( !process->start() ) {
                // error handling
	QMessageBox::warning( this, "OLFIX - RGTDSP",
                            "Kan inte starta RGTDSP!\n"
                            );
	}
//	qWarning( "slotGetRightData: userid=%s \n", userid.latin1() );
}

void frmDspUser::slotuseridEntered()
{
    userid=LineEdituserid->text();
    userid=userid.upper();
    LineEdituserid->setText((userid));
}

void frmDspUser::slotRightDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
//	qWarning( "slotRightDataOnStdout: userid=%s \n", inrad.latin1() );
    }
}


void frmDspUser::slotEndOfRightProcess()
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
 /*                                                   Start     2007-12-10                                         */
    QString host="";
    int l1,l2,m1,m2;
    m1=inrad.find( QRegExp("host="), 0 );
    m2=inrad.find( QRegExp("NR_"), 0 );
    l1=m2-(m1+5);
    l2=m2-m1;
    host=inrad.mid(5,l1);
    inrad=inrad.mid(m2,inrad.length()-m2);
    /*
//  qDebug("host=%s m1=%d m2=%d l1=%d l2=%d\n",host.latin1(),m1,m2,l1,l2);
    if(host != "127.0.0.1 "){
	 if(host != "localhost "){
	     textLabel1->setText("<u><b>Host</b></u>\n");
	     textLabelHostName->setText(host);
	 }
    }else{
	textLabel1->setText("");
    }
    */
/*                                                End         2007-12-10                                         */
    tmppek=tmp;
    qstrcpy(tmp,inrad);
//    qDebug("inrad=%s tmp=%s",inrad.latin1(),tmp);
    pos1=strstr(tmp,"NR_");
    pos2=strstr(tmp,"_:");
    i=pos2-pos1;
    
    m=i+2;		// startposition för första userid.
//    fprintf(stdout,"i=%d  m=%d",i,m);
    if (i < 1){
	return;
    }
    k=0;
    for (j=3;j<i;j++){
	antrad[k]=tmp[j];
	k++;
    };
    i=atoi(antrad);		// i = antal poster
//    fprintf(stderr," i = %d\n",i);
    for (k = 1;k <= i; k++){	// går igenom alla raderna / posterna
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
	m=m+l+2;	// position f�r namn
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
    frmDspUser::slotGetUserData();
//    EndFlag="J";
//    fprintf(stderr,"Klart!\n");
}


void frmDspUser::slotUsrDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad_u.append(line);
	inrad_u.append("\n");
//	qWarning( "slotUsrDataOnStdout: userid=%s \n", inrad_u.latin1() );
    }
}


void frmDspUser::slotEndOfUsrProcess()
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
	LineEdituserid->setText(user);
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

void frmDspUser::listUsers()	
{
    const char *userp = getenv("USER");
    QString usr(userp);
    listViewUser->clear();
    inradlista="";
    errorradlista="";
    inrad="";
    inrad_u="";
	
    processlist = new QProcess();
    processlist->addArgument("./STYRMAN");	// OLFIX styrprogram
    processlist->addArgument(usr);		// userid
    processlist->addArgument( "USERLST");	// OLFIX funktion
		
    frmDspUser::connect( processlist, SIGNAL(readyReadStdout() ),this, SLOT(slotUserDataOnStdout() ) );
    frmDspUser::connect( processlist, SIGNAL(readyReadStderr() ),this, SLOT(slotUserDataOnStderr() ) );	
    frmDspUser::connect( processlist, SIGNAL(processExited() ),this, SLOT(slotUserEndOfProcess() ) );	    
 
    if ( !processlist->start() ) {
    // error handling
    QMessageBox::warning( this, "Start av USERLST ",
	"Kan inte starta STYRMAN/USERLST!\n"
                );
    }
}

void frmDspUser::slotUserDataOnStdout()
{
    while (processlist->canReadLineStdout() ) {
	QString line = processlist->readStdout();
	inradlista.append(line);
	inradlista.append("\n");
    }
}

void frmDspUser::slotUserDataOnStderr()
{
    while (processlist->canReadLineStderr() ) {
	QString line = processlist->readStderr();
	errorradlista.append(line);
	errorradlista.append("\n");
    }
}

void frmDspUser::slotUserEndOfProcess()
{
    QListViewItem* item;
    int i;
    listViewUser->setSorting(0,TRUE);
    i = -1;
    i = errorradlista.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "CHGUSRW",
		"ERROR!\n"+errorradlista
	);
	errorradlista="";
	i = -1;
     }
	 
    i = inradlista.find( QRegExp("NR_0_"), 0 );
         if (i != -1) {
	QMessageBox::information( this, "CHGUSRW",
		"Användarregistret innehåller inga poster!\n"
	);
	i = -1;
     }
	 
//    QString listrad;
//    rad=&inrad;
    inradlista.latin1();
    char *pos1;
    char *pos2;
    char tmp[MAXSTRING];
    char *tmppek;
    int j,k,l,m;
//    int antrad;
    char antrad[6]="";
    char userid[9]="";
    char namn[31]="";
    char avd[11]="";
    char grupp[11]="";
 /*                                                   Start     2007-12-10                                         */
    QString host="";
    int l1,l2,m1,m2;
    m1=inradlista.find( QRegExp("host="), 0 );
    m2=inradlista.find( QRegExp("NR_"), 0 );
    l1=m2-(m1+5);
    l2=m2-m1;
    host=inradlista.mid(5,l1);
    inradlista=inradlista.mid(m2,inrad.length()-m2);
    
//  qDebug("host=%s m1=%d m2=%d l1=%d l2=%d\n",host.latin1(),m1,m2,l1,l2);
    if(host != "127.0.0.1 "){
	 if(host != "localhost "){
	     textLabel1->setText("<u><b>Host</b></u>\n");
	     textLabelHostName->setText(host);
	 }
    }else{
	textLabel1->setText("");
    }
/*                                                End         2007-12-10                                         */

    
    tmppek=tmp;
    qstrcpy(tmp,inradlista);
    pos1=strstr(tmp,"NR_");	//3  tecken långt
    pos2=strstr(tmp,"_:");
    i=pos2-pos1;
    m=i+2;		// startposition för första userid.
    
//    qDebug("i=%d  m=%d",i,m);
    
    k=0;
    for (j=3;j<i;j++){	// j = första positionen för antal poster, (NR_6_:ADMINA_:Administratör av OLFIX_:IT_:Stab_:)
	antrad[k]=tmp[j];
	k++;
    };
    i=atoi(antrad);		// i = antal poster
    
//    qDebug("antrad=%s",antrad);
    
    for (k = 1;k <= i; k++){	// går� igenom alla raderna / posterna
	l=0;
	for(j = m; j < sizeof(userid) + m; j++){
	    if(tmp[j] != *("_")){
		userid[l]=tmp[j];
		l++;
	    }else{
		userid[l] = *("\0");
		j=sizeof(userid) + m;
	    }
	}
//	qDebug("%s  ",userid);
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
//	qDebug("%s  ",namn);
	m=m+l+2;	
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
//	qDebug("%s  ",avd);	
	m=m+l+2;
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
//	qDebug("%s  ",grupp);	
	m=m+l+2;
		
	item = new QListViewItem(listViewUser,namn,userid);
// 	 rensa namn och userid 
  	for (l=0;l<sizeof(userid);l++)
		userid[l]=*("\0");
	for (l=0;l<sizeof(namn);l++)
	               namn[l]=*("\0");
	for (l=0;l<sizeof(avd);l++)
	               avd[l]=*("\0");
	for (l=0;l<sizeof(grupp);l++)
	               grupp[l]=*("\0");	
//	 rensa listrad 
//	listrad.remove(0,80);
    }   
}

void frmDspUser::slotPickupUserID( QListViewItem * item)
{
    char user[11]="";
//    qDebug("PickupUserID\n");
    if(!item){
	return;
    }
     listViewUser->setCurrentItem(item);
     if(!item->key(0,TRUE)){
	 return;
     }

     strcpy(user,item->key(1,TRUE));	// = Användar-ID
     userid=user;
     LineEdituserid->setText(userid);
     LineEdituserid->setFocus();
}

void frmDspUser::pushBtnHelp_clicked()
{
	inrad="";
	frmDspUser::readResursFil();		// Hämta path till hjälpfilen

	int i1 = hjelpfil.find( QRegExp(".html"), 0 );
//	int i2 = hjelpfil.length();
	hjelpfil=hjelpfil.left(i1);
	hjelpfil=hjelpfil+"_ADMINISTRATION.html";
	hjelpfil=hjelpfil+"#DSPUSER";		// Lägg till position
//	qDebug("hjelpfil=%s",hjelpfil.latin1());

	process = new QProcess();
	process->addArgument( "./OLFIXHLP" );	// OLFIX program
	process->addArgument(hjelpfil);

	if ( !process->start() ) {
	    // error handling
	    QMessageBox::warning( this, "OLFIX","Kan inte starta OLFIXHLP!\n" );
	}
	LineEdituserid->setFocus();
}

void frmDspUser::readResursFil()
{
    /*****************************************************/
    /*  Läs in .olfixrc filen här			               	*/
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
    
    
