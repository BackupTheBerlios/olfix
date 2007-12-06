/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                          LSTVALW  -  description
                             -------------------
		     version 0.1
    begin                : Sön 22 febr 2003
    modified	         : Tors  6  okt  2007    
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
#include <qfont.h>
#include <qlistview.h>
#define MAXSTRING 5000	

	QProcess* process;
	QString inrad;
	QString errorrad;
	QString* rad;


void frmListValuta::GetValuta()
{
	const char *userp = getenv("USER");
            QString usr(userp);
	QString bibl;

	bibl.append("./STYRMAN");		// OLFIX huvudprogram
	
	process = new QProcess();
	process->addArgument(bibl);
	process->addArgument(usr);		// userid
	process->addArgument( "VALLST");	// OLFIX funktion
	
//	fprintf(stderr,"Starta STYRMAN/VALLST! %s\n",user);
	
	frmListValuta::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmListValuta::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );	
	frmListValuta::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );	    
 
	if ( !process->start() ) {
                // error handling
	    fprintf(stderr,"Problem starta STYRMAN/USERLST!\n");
	    QMessageBox::warning( this, "Start av VALLST ",
                            "Kan inte starta STYRMAN/VALLST!\n"
                            );
        }
}

void frmListValuta::init()
{
    PushButtonSluta->setFocus();
    frmListValuta::GetValuta();
}

void frmListValuta::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
//      fprintf(stdout,"2 .L�ser fr�n STYRMAN/VALLST! %s\n",inrad.latin1());
}

void frmListValuta::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}
void frmListValuta::slotEndOfProcess()
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
    char land[16]="";
    char salj[8]="";
    char kop[8]="";
    char beteckn[16]="";
//    char listrad[90]="";

    /*                                                   Start     2007-12-06                                         */
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
    /*                                                End         2007-12-06                                         */
    
    
    
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
    for (k = 1;k <= i; k++){	// g� igenom alla raderna / posterna
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
	m=m+l+2;	// position för sälj
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
//	fprintf(stdout,"%s  ",salj);
	m=m+l+2;	// position för köp
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
	m=m+l+2;
//	fprintf(stdout,"%s\n  ",köp);
	l=0;
	for(j = m; j < sizeof(beteckn) + m; j++){
	    if(tmp[j] != *("_")){
		beteckn[l]=tmp[j];
		l++;
	    }else{
		beteckn[l] = *("\0");
		j=sizeof(beteckn) + m;
	    }
	}
	m=m+l+2;
//	fprintf(stdout,"%s\n  ",beteckn);
	
	item = new QListViewItem(ListView1,valuta,land,salj,kop,beteckn);
// 	 rensa valuta,land,salj,kop,beteckn 
  	for (l=0;l<sizeof(valuta);l++)
		valuta[l]=*("\0");
	for (l=0;l<sizeof(land);l++)
		land[l]=*("\0");
	for (l=0;l<sizeof(salj);l++)
		salj[l]=*("\0");
	for (l=0;l<sizeof(kop);l++)
		kop[l]=*("\0");
	for (l=0;l<sizeof(beteckn);l++)
		beteckn[l]=*("\0");
//	 rensa listrad 
	listrad.remove(0,70);
    }   
//   fprintf(stderr,"%s",tmp);
//    fprintf(stderr,"Klart!\n");
}


void frmListValuta::slotReloadValuta()
{
        ListView1->clear();
        frmListValuta::GetValuta();
}
