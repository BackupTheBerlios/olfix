/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                          RPTKTOW  -  description
                             -------------------
		     version 0.1
    begin                : Lör 8 mars 2003
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
#include <qstring.h>		
#include <qfile.h>
#include <qregexp.h>
#include <qfont.h>
#include <qlistview.h>
#include <qdatetime.h>
#define MAXSTRING 15000

    QProcess* process;
    QString inrad;
    QString* rad;
    QString errorrad;
    int status = 0;
 //   QString inradktolist;

    QString datum;
    QString arid;		// Bokföringsår.


void frmKtoRapport::init()
{
    QDateTime dt = QDateTime::currentDateTime();

    datum=dt.toString("yyyy-MM-dd");
    TextLabelDatum->setText(datum);
    LineEditBar->setFocus();
}

void frmKtoRapport::slotLineEditBar_returnPressed()
{
    status=0;
    ListView1->clear();
    arid=LineEditBar->text();
    arid=arid.upper();
    LineEditBar->setText((arid));
    if (arid==""){
	QMessageBox::warning( this, "OLFIX - RPTKTOW",
                      "Bokföringsår måste fyllas i! \n" );
	LineEditBar->setFocus();
	status = -1;
     }
    if (status == 0){
//	ListView1->clear();
	frmKtoRapport::slotCheckBar();
    }
}

void frmKtoRapport::slotGetVerrader()
{
	const char *userp = getenv("USER");
            QString usr(userp);

	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "KTORPT");	// OLFIX funktion
	process->addArgument(arid);
//	fprintf(stderr,"Bokföringsår=%s\n",arid.latin1());
	frmKtoRapport::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmKtoRapport::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmKtoRapport::connect( process, SIGNAL(processExited() ),this, SLOT(slotKTORPTEndOfProcess() ) );

	if ( !process->start() ) {
	    // error handling
//	    fprintf(stderr,"Problem starta STYRMAN/BARCHK!\n");
	    QMessageBox::warning( this, "RPTKTOW",
                            "Kan inte starta STYRMAN/BARCHK! \n" );
	    }

}


void frmKtoRapport::slotCheckBar()
{
	const char *userp = getenv("USER");
            QString usr(userp);

	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "BARCHK");	// OLFIX funktion
	process->addArgument(arid);
//	fprintf(stderr,"Bokföringsår=%s\n",arid.latin1());
	frmKtoRapport::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmKtoRapport::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmKtoRapport::connect( process, SIGNAL(processExited() ),this, SLOT(slotBARCHKEndOfProcess() ) );

	if ( !process->start() ) {
	    // error handling
//	    fprintf(stderr,"Problem starta STYRMAN/BARCHK!\n");
	    QMessageBox::warning( this, "RPTKTOW",
                            "Kan inte starta STYRMAN/BARCHK! \n" );
	    }
}


void frmKtoRapport::slotBARCHKEndOfProcess()
{
    int i = -1;

    i = errorrad.find( QRegExp("Error:"), 0 );
//	qDebug("errorrad=%s i=%d\n",errorrad.latin1(),i);
            if (i == 0) {
		QMessageBox::critical( this, "OLFIX - BARCHK",
			"ERROR!\n"+errorrad
		);
	            errorrad="";
		i = -1;
		status = -1;
		LineEditBar->clear();
		LineEditBar->setFocus();
	    }
	    else{
		i = -1;
		i = inrad.find( QRegExp("OK:"), 0 );  
		if(i == 0){
		    status = 0;
		    inrad="";
		    errorrad="";
		    frmKtoRapport::slotGetVerrader();
		}
	    }
	    frmKtoRapport::slotGetVerrader();
}


void frmKtoRapport::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}


void frmKtoRapport::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}


void frmKtoRapport::slotKTORPTEndOfProcess()
{
  QListViewItem* item;
  QString Db;
  QString Kr;
  QString Sum;
  QString DEBET;
  QString KREDIT;
  int i;
  int j,k,l,m;
  char *pos1;
  char *pos2;
  char tmp[MAXSTRING];
  char *tmppek;
  char antrad[6]="";
  char ktonr[5]="";
  char tmpktonr[5]="";
  char debet[13]="";
  char kredit[13]="";
  char belopp[13]="";
  double debetsumma=0;
  double kreditsumma=0;
  double delsummadb=0;
  double delsummakr=0;
  double summa=0;
  char dk[2]="";

    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "RPTKTOWW",
		"ERROR!\n"+errorrad );
	 errorrad="";
	 arid="";
	 LineEditBar->setFocus();
     }else{
//	 inradktolist.latin1();
//	 qDebug("inradktolist=%s\n",inradktolist.latin1());
//	 qDebug("inrad=%s\n",inrad.latin1());
	 tmppek=tmp;
	 qstrcpy(tmp,inrad);
	 pos1=strstr(tmp,"NR_");
	 pos2=strstr(tmp,"_:");
	 i = pos2 - pos1;
	 m=i+2;		// startposition för första ktonr.
//	 qDebug("i=%d m=%d\n",i,m);
	 k=0;
	 for (j=3;j<i;j++){
	     antrad[k]=tmp[j];
	     k++;
	 };
	 i = atoi(antrad);		// i = antal poster
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
	     if (strlen(tmpktonr) == 0 ){
		 strcpy(tmpktonr,ktonr);
	     }
//	     fprintf(stdout,"tmpktonr=%s ktonr=%s\n ",tmpktonr,ktonr);
	     m=m+l+2;	// position för dk
	     l=0;
	     for(j = m; j < sizeof(dk) + m; j++){
		 if(tmp[j] != *("_")){
		     dk[l]=tmp[j];
		     l++;
		  }else{
		      dk[l] = *("\0");
		      j=sizeof(dk) + m;
		  }
	      }
		 //	fprintf(stdout,"%s  ",dk);
	     m=m+l+2;	// position för belopp
	     l=0;
	     for(j = m; j < sizeof(belopp) + m; j++){
		 if(tmp[j] != *("_")){
		     belopp[l]=tmp[j];
		     l++;
		  }else{
		      belopp[l] = *("\0");
		      j=sizeof(belopp) + m;
		  }
	      }
		 //	fprintf(stdout,"%s  ",belopp);
	     m=m+l+2;
	     if (strcmp(tmpktonr,ktonr) != 0){
		 summa=delsummadb-delsummakr;
		Db = Db.setNum(delsummadb,'f',2);
		Kr = Kr.setNum(delsummakr,'f',2);
		Sum=Sum.setNum(summa,'f',2);
		while (Db.length() < 13){
		    Db.prepend(" ");
		}
		while (Kr.length() < 13){
		    Kr.prepend(" ");
		}
		while (Sum.length() < 13){
		    Sum.prepend(" ");
		}
		item = new QListViewItem(ListView1,tmpktonr,"Delsumma",Db,Kr,Sum);
		delsummadb=0;
		delsummakr=0;
		strcpy(tmpktonr,ktonr);
	     }
	     
	     if (strcmp(dk,"D") ==0){
		 strcpy(debet,belopp);
		 strcpy(kredit,"");
		 Db=belopp;
		 debetsumma=debetsumma+Db.toDouble();
		 delsummadb=delsummadb+Db.toDouble();
	     }else{
		 strcpy(debet,"");
		 strcpy(kredit,belopp);
		 Kr=belopp;
		 kreditsumma=kreditsumma+Kr.toDouble();
		 delsummakr=delsummakr+Kr.toDouble();
	     }
	     DEBET=debet;
	     KREDIT=kredit;
	     while (DEBET.length() <13){
		 DEBET.prepend(" ");
	     }
	     while (KREDIT.length() < 13){
		 KREDIT.prepend(" ");
	     }
//	     item = new QListViewItem(ListView1,ktonr,"",debet,kredit,"");
	    item = new QListViewItem(ListView1,ktonr,"",DEBET,KREDIT,"");
		 /* rensa ktonr,dk,belopp */
	     for (l=0;l<sizeof(ktonr);l++){
		 ktonr[l]=*("\0");
	     }
	     for (l=0;l<sizeof(dk);l++){
		     dk[l]=*("\0");
	     }
     	     for (l=0;l<sizeof(belopp);l++){
		     belopp[l]=*("\0");
	     }
	 }
     }
    summa=delsummadb-delsummakr;
    Db = Db.setNum(delsummadb,'f',2);
    Kr = Kr.setNum(delsummakr,'f',2);
    Sum=Sum.setNum(summa,'f',2);    
    while (Db.length() < 13){
	Db.prepend(" ");
    }
    while (Kr.length() < 13){
	Kr.prepend(" ");
    }
    while (Sum.length() < 13){
	Sum.prepend(" ");
    }
    if (strlen(tmpktonr) !=0){
	item = new QListViewItem(ListView1,tmpktonr,"Delsumma",Db,Kr,Sum);
    }    
    summa=debetsumma-kreditsumma;
     Db = Db.setNum(debetsumma,'f',2);
     Kr = Kr.setNum(kreditsumma,'f',2);
     Sum=Sum.setNum(summa,'f',2); 
     while (Db.length() < 13){
	 Db.prepend(" ");
     }
     while (Kr.length() < 13){
	 Kr.prepend(" ");
     }
     while (Sum.length() < 13){
	 Sum.prepend(" ");     
     }
     if (debetsumma != 0){
	  item = new QListViewItem(ListView1,"Total","Summa",Db,Kr,Sum);  
      }	 
}
