/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
***************************************************************************/
/***************************************************************************
                          LSTRGTW  -  description
                             -------------------
		     version 0.3
    begin                : Sön  23 febr 2003
    modified	         : Ons  12 dec  2007
    copyright         : (C) 2003 by Jan Pihlgren
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

#include <qprocess.h>
#include <qmessagebox.h>
#include <qdir.h>
#include <stdlib.h>
#include <qstring.h>		
#include <qfile.h>
#include <qlistview.h>
#include <qregexp.h>	/* 2007-12-12 */
// #define MAXSTRING 5000	
#define MAXSTRING 15000	


	QProcess* process;
	QString inrad;
	QString* rad;
	int count=0;
	
void frmListRights::init()
{
    frmListRights::GetRights();
}

void frmListRights::GetRights()
{
	const char *userp = getenv("USER");
	QString usr(userp);
	
	count++;
	inrad="";
	
	process = new QProcess();
//	process->addArgument(bibl);
	process->addArgument("./STYRMAN");
	process->addArgument(usr);		// userid
	process->addArgument( "RGTLST");	// OLFIX funktion
//            fprintf(stderr,"Starta STYRMAN/RGTLST!\n");
	    
	frmListRights::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
                frmListRights::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );
	    
	if ( !process->start() ) {
            // error handling
	    fprintf(stderr,"Problem starta RGTLST!\n");
	    QMessageBox::warning( this, "Start av RGTLST ", "Kan inte starta RGTLST!\n");
        }
    }

void frmListRights::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmListRights::slotEndOfProcess()
{
    QString listrad;
    QListViewItem* item;
    rad=&inrad;
//    inrad.latin1();
    char *pos1;
    char *pos2;
    char tmp[MAXSTRING];
    char *tmppek;
    int i,j,k,l,m;
    char antrad[6]="";
    char user[9]="";
    char funk[9]="";
    
    /*                                                   Start     2007-12-12                                         */
    QString host="";
    int l1, l2, m1, m2;    
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
    /*                                                End         2007-12-12                                         */

    
    
    tmppek=tmp;
    qstrcpy(tmp,inrad);
    pos1=strstr(tmp,"NR_");
    pos2=strstr(tmp,"_:");
    i=pos2-pos1;
    m=i+2;		// startposition f�r f�rsta userid.
    
//    fprintf(stdout,"i=%d  m=%d",i,m);
    k=0;
    for (j=3;j<i;j++){
	antrad[k]=tmp[j];
	k++;
    };
    i=atoi(antrad);		// i = antal poster
//    fprintf(stderr," i = %d\n",i);
    for (k = 1;k <= i; k++){	// g� igenom alla raderna / posterna
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
	m=m+l+2;	// position f�r funk
//	listrad.append(user);
//	while(listrad.length() <10)
//	    listrad.append(" ");
//	listrad.append(funk);
	item = new QListViewItem(ListView1,user,funk);
//	ListBox1->insertItem(listrad);
 	/* rensa user,namn,avd och grupp */
   	for (l=0;l<sizeof(user);l++)
		user[l]=*("\0");
	for (l=0;l<sizeof(funk);l++)
		funk[l]=*("\0");
	/* rensa listrad */
	listrad.remove(0,70);
    }   
//    fprintf(stderr,"Klart!\n");
}

void frmListRights::slotReloadRights()
{
    ListView1->clear();
//    qDebug("slotReloadRights:: count=%d",count);
    frmListRights::GetRights();
}
