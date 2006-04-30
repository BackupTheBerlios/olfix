/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                          LSTKTOW  -  description
                             -------------------
		     version 0.4.3
    begin                	: Sön 23 febr 2003
    Modified		: Sön 30 april 2006
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
#include <qstring.h>		
#include <qfile.h>
#include <qregexp.h>
#define MAXSTRING 15000	

    QProcess* process;
    QString inrad;
    QString errorrad;
    QString arid;				// Bokföringsår  (årid)
	

void frmListKonto::init()
{
    ListBox1->clear();
    LineEditBar->clear();
    LineEditBar->setFocus();
}
	
void frmListKonto::slotLineEditBarEntered()
{
    arid=LineEditBar->text();
    arid=arid.upper();
    LineEditBar->setText((arid));
    ListBox1->clear();
}



void frmListKonto::PushButtonLista_clicked()
{
    frmListKonto::checkBokforar();
}

void frmListKonto::getLista()
{	     
	const char *userp = getenv("USER");
	QString usr(userp);
	
	QString bibl;
//	bibl="";
	errorrad="";
	inrad="";
//	bibl.append("./STYRMAN");		// OLFIX huvudprogram
	
	process = new QProcess();
	process->addArgument("./STYRMAN");
	process->addArgument(usr);		// userid
	process->addArgument( "KTOVIEW");	// OLFIX funktion
	process->addArgument(arid);		// bokföringsår
	
	frmListKonto::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmListKonto::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );	
	frmListKonto::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );
	
//	qWarning( "PushButtonLista_clicked: Userid=%s arid=%s bibl=%s\n", usr.latin1(),arid.latin1(),bibl.latin1() );
	
	if (arid == "" ){
    	    QMessageBox::warning( this, "KTOVIEWW",
                      "Bokföringsår saknas \n" );
	}
	else {
                 if ( !process->start() ) {
                     // error handling
	         QMessageBox::warning( this, "Start av KTOVIEW ",
                            "Kan inte starta STYRMAN/KTOVIEW!\n"
                            );
	     }
	}	    
}

void frmListKonto::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
//      fprintf(stdout,"2 .Läser från STYRMAN/KTOVIEW!\n");
//      qWarning( "inrad = "+inrad+"\n" );
}

void frmListKonto::slotEndOfProcess()
{
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "LSTKTOW",
		"ERROR!\n"+errorrad );
	errorrad="";
	arid="";
	LineEditBar->setFocus();
    }else{
	i = -1;
	i = inrad.find( QRegExp("VARNING:"), 0 );
	if (i != -1) {
	    QMessageBox::critical( this, "LSTKTOW",
		"VARNING!\n"+inrad );
	    inrad="";
	    arid="";
	    LineEditBar->setFocus();
	    return;
	}
	QString listrad;
	//    rad=&inrad;
	inrad.latin1();
	char *pos1;
	char *pos2;
	char tmp[MAXSTRING];
	char *tmppek;
	int j,k,l,m;
	char antrad[6]="";
	char ktonr[5]="";
	char benamn[61]="";

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
	for (k = 1;k <= i; k++){	// gå igenom alla raderna / posterna
	    l=0;
	    for(j = m; j < sizeof(ktonr) + m; j++){
		if(tmp[j] != *("_")){
		    ktonr[l]=tmp[j];
		    l++;
		}else{
		    ktonr[l] = *("\0");
		    j=sizeof(ktonr) + m;
		}
	    }
	    //	fprintf(stdout,"%s  ",ktonr);
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
	
	    listrad.append(ktonr);
	    listrad=listrad.leftJustify(10,' ');
	    listrad.append(benamn);
	    ListBox1->insertItem(listrad);
	    /* rensa ktonr,benamn */
	    for (l=0;l<sizeof(ktonr);l++)
		ktonr[l]=*("\0");
	    for (l=0;l<sizeof(benamn);l++)
		benamn[l]=*("\0");
	    /* rensa listrad */
	    listrad.remove(0,80);
	}
    }	    
}

void frmListKonto::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
//	qWarning( "slotDataOnStderr: Userid=%s \n", inrad.latin1() );
    }
}

void frmListKonto::slotReloadKonto()
{
    ListBox1->clear();
    frmListKonto::PushButtonLista_clicked();
}

void frmListKonto::checkBokforar()
{	     
    const char *userp = getenv("USER");
    QString usr(userp);
	
    QString bibl;
//   bibl="";
    errorrad="";
    inrad="";
//  bibl.append("./STYRMAN");		// OLFIX huvudprogram
	
    process = new QProcess();
    process->addArgument("./STYRMAN");
    process->addArgument(usr);		// userid
    process->addArgument( "BARCHK");	// OLFIX funktion
    process->addArgument(arid);		// bokföringsår
	
    frmListKonto::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
    frmListKonto::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );	
    frmListKonto::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfBarcheckProcess() ) );
	
//  qWarning( "PushButtonLista_clicked: Userid=%s arid=%s bibl=%s\n", usr.latin1(),arid.latin1(),bibl.latin1() );
	
    if (arid == "" ){
	QMessageBox::warning( this, "LSTKTOW",
	"Bokföringsår saknas \n" );
    }else {
	if ( !process->start() ) {
	    // error handling
	    QMessageBox::warning( this, "LSTKTOW ",
                            "Kan inte starta STYRMAN/BARCHK!\n"
                    );
	}
    }	    
}

void frmListKonto::slotEndOfBarcheckProcess()
{
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "LSTKTOW",
		"ERROR!\n"+errorrad );
	errorrad="";
	arid="";
	LineEditBar->setFocus();
    }else{
	frmListKonto::getLista();
    }
}
