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
		     version 0.2
    begin                	: Lör 8 mars 2003
    update		:Tors 15 maj 2003
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
    QString inrad="";
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
    arid="";
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
	    inrad="";
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
  QString KontoNr;
  QString tmpKtoNr;
  QString KontoNamn;
  QString tmpKtoNamn;
  QString DK;
  QString BELOPP;
  QString Db;
  QString Kr;
  QString Sum;
  QString Total;
  QString DEBET;
  QString KREDIT;
  
  int i,antrad;
  int j,k,l,m;
  
  double dbbelopp=0;
  double dbtotal=0;
  double krbelopp=0;
  double krtotal=0;
  double summa=0;
  double total=0;
   
//  ListView1->setSorting(-1);
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "RPTKTOWW",
		"ERROR!\n"+errorrad );
	 errorrad="";
	 arid="";
	 LineEditBar->setFocus();
     }
    qDebug("inrad=%s",inrad.latin1());
    i = inrad.find(QRegExp("NR_"),0);
    j = inrad.find(QRegExp("_:"),0);
    m = j - i;
//   qDebug("i=%d, j=%d, m=%d",i,j,m); 
   antrad = (inrad.mid(i+3,m-3)).toInt();
//   qDebug("antrad=%d,",antrad);
   tmpKtoNr="";
   
   for (l = 0;l < antrad; l++){
//      qDebug("l=%d,",l);    
       k = inrad.find(QRegExp("_:"),j+3);  // j+2
       m = k - j;
       KontoNr = inrad.mid(j+2,m-2);
//       qDebug("l=%d, KontoNr=%s",l,KontoNr.latin1());
       
       j = k;
       k = inrad.find(QRegExp("_:"),j+2);
       m = k - j;
       KontoNamn =inrad.mid(j+2,m-2);
//      qDebug("KontoNamn=%s",KontoNamn.latin1());
   
       j = k;
       k = inrad.find(QRegExp("_:"),j+2);
       m = k - j;
       DK =inrad.mid(j+2,m-2);
//       qDebug("DK=%s",DK.latin1());    

       j = k;
       k = inrad.find(QRegExp("_:"),j+2);
       m = k - j;
       BELOPP = inrad.mid(j+2,m-2);
//       qDebug("BELOPP=%s",BELOPP.latin1());    
      
      if ((KontoNr == tmpKtoNr) && (KontoNr !=""))  {
	  if (DK == "D"){
	      DEBET=BELOPP;
	      dbbelopp=dbbelopp+BELOPP.toDouble();
                  dbtotal=dbtotal+BELOPP.toDouble();
	      KREDIT="";
	  }
	  if (DK == "K"){
	      KREDIT=BELOPP;
	      krbelopp=krbelopp+BELOPP.toDouble();
	      krtotal=krtotal+BELOPP.toDouble();
	      DEBET="";
	  }
              summa=dbbelopp-krbelopp;
  	  item = new QListViewItem(ListView1,KontoNr,"z",DEBET,KREDIT,"");    	       
//	  total=total+summa;
      }else{
              Sum.setNum(summa,'f',2);
	  if (tmpKtoNr !=""){
	      item = new QListViewItem(ListView1,tmpKtoNr,"z       Delsumma","","",Sum);
	  }
	  summa=0; 
	  dbbelopp=0;
	  krbelopp=0;
	  
	  if (DK == "D"){
	      DEBET=BELOPP;
	      dbbelopp=dbbelopp+BELOPP.toDouble();
                  dbtotal=dbtotal+BELOPP.toDouble();
	      KREDIT="";
	  }
	  if (DK == "K"){
	      KREDIT=BELOPP;
	      krbelopp=krbelopp+BELOPP.toDouble();
	      krtotal=krtotal+BELOPP.toDouble();	      
	      DEBET="";
	  }
              summa=dbbelopp-krbelopp;
//              total=total+summa;
	  item = new QListViewItem(ListView1,KontoNr,KontoNamn,DEBET,KREDIT,"");      
      }
       tmpKtoNr=KontoNr;
         
       j = k;
   };
   
  Sum.setNum(summa,'f',2);
  item = new QListViewItem(ListView1,tmpKtoNr,"z       Delsumma","","",Sum);

   Db.setNum(dbtotal,'f',2);
   Kr.setNum(krtotal,'f',2);
   
   total=dbtotal-krtotal; 
   Total.setNum(total,'f',2);
   item = new QListViewItem(ListView1,"Total","",Db,Kr,Total); 
   
//	    item = new QListViewItem(ListView1,ktonr,KontoNamn,DEBET,KREDIT,"");
//    if (strlen(tmpktonr) !=0){
//	item = new QListViewItem(ListView1,tmpktonr,"Delsumma",Db,Kr,Sum);
//	  item = new QListViewItem(ListView1,"Total","Summa",Db,Kr,Sum);  
}
