/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you want to add, delete, or rename functions or slots, use
** Qt Designer to update this file, preserving your code.
**
** You should not define a constructor or destructor in this file.
** Instead, write your code in functions called init() and destroy().
** These will automatically be called by the form's constructor and
** destructor.
*****************************************************************************/
/***************************************************************************
                               CHGPRISW  -  description
	         Laddning av en eller alla prislistor i tabellen PRISLISTA. Uppdatering.
                             -------------------
		     version 0.1
    begin   	: 	Sö      22 jan   2006
    Updated	: 
    copyright:	 (C) 2003 by Jan Pihlgren
    email     	: 	jan@pihlgren.se
 ***************************************************************************/
/*****************************************************************
 *					                                             *
 *   This program is free software; you can redistribute it and/or modify 	  *
 *   it under the terms of the GNU General Public License as published by                   *
 *   the Free Software Foundation; either version 2 of the License, or     	  *
 *   (at your option) any later version.                                   		                       *
 *                                                                         				  *
 *********************************************** ******************/

#include <qmessagebox.h>
#include <qprocess.h>
#include <qdir.h>
#include <stdlib.h>
#include <qstring.h>
#include <qfile.h>
#include <qregexp.h>
#define MAXSTRING 25000

QProcess* process;
QString inrad;
QString errorrad;
QString hjelpfil;
QString database;
QString pricefilename;
QString tmpfilename;
QString prislista="1";

bool testflag=TRUE;
bool running=FALSE;

void frmLoadPrices::init()
{
    prislista="1";
    pushButtonCancel->setText("Avbryt");
    frmLoadPrices::readResursFil();
    lineEditFilname->setFocus();
}

void frmLoadPrices::lineEditFilname_returnPressed()
{
    pricefilename="";
    pricefilename=lineEditFilname->text();
    running=FALSE;
    return;
//    pushButtonTest->setFocus();
}

void frmLoadPrices::pushButtonOK_clicked()
{
    testflag=FALSE;
    running=TRUE;
    listViewResultat->clear();
    getPricefile();
    qDebug("pushButtonOK: tmpfil=%s prislista=%s",tmpfilename.latin1(),prislista.latin1());
    updatePrices(tmpfilename,prislista);
    pushButtonCancel->setFocus();
}

void frmLoadPrices::pushButtonCancel_clicked()
{
    close();
}

void frmLoadPrices::pushButtonTest_clicked()
{
    testflag=TRUE;
    listViewResultat->clear();
    getPricefile();
}

void frmLoadPrices::radioButton1_clicked()
{
    prislista="1";
}


void frmLoadPrices::radioButton2_clicked()
{
    prislista="2";
}


void frmLoadPrices::radioButton3_clicked()
{
    prislista="3";
}


void frmLoadPrices::radioButton4_clicked()
{
    prislista="4";
}


void frmLoadPrices::radioButton5_clicked()
{
    prislista="5";
}


void frmLoadPrices::radioButtonA_clicked()
{
    prislista="A";
    
}


void frmLoadPrices::radioButtonF_clicked()
{
    prislista="F";
}

void frmLoadPrices::getPricefile()
{
    QListViewItem * item;
    QStringList lines;
    QString line;
    QString record;
    int recordsize;
    QString delemit=";";
    QString homepath;
    homepath=QDir::homeDirPath();

    tmpfilename=homepath;				/* $HOME */
    QString infile=homepath;
    infile=infile.append("/tmp/");			/* $HOME/tmp/ */
    infile=infile.append(pricefilename);			/* Infil, $HOME/tmp/nyaprisfilen*/
    
    tmpfilename=tmpfilename.append("/tmp/pricefile.tmp");	/* Utfil, $HOME/tmp/pricefile.tmp */
    
    QFile pricefile(infile );				/* Infil, den nya prisfilen */
    QFile tempfile(tmpfilename);			/* Utfil */
    ulong offset=0;
    
//   qDebug("prislista=%s",prislista.latin1());
//   qDebug("tmpfilename=%s",tmpfilename.latin1());
//   qDebug("pricefilename=%s",infile.latin1());
    
    tempfile.open( IO_WriteOnly );
    if (pricefile.open( IO_ReadOnly ) ) {
       QTextStream stream( &pricefile );
       while ( !stream.eof() )  {
                line = stream.readLine(); 			/* line of text excluding '\n'	*/
	int i1a=line.find( QRegExp("\""), 0 );		/* Artnr */
	int i1b=line.find( QRegExp("\""), i1a+1 );
	int i2a=line.find( QRegExp("\""), i1b+1 );		/* Fpris */
	int i2b=line.find( QRegExp("\""), i2a+1 );
	int i3a=line.find( QRegExp("\""), i2b+1 );		/* Pris1 */
	int i3b=line.find( QRegExp("\""), i3a+1 );
	int i4a=line.find( QRegExp("\""), i3b+1 );		/* Pris2 */
	int i4b=line.find( QRegExp("\""), i4a+1 );
	int i5a=line.find( QRegExp("\""), i4b+1 );		/* Pris3 */
	int i5b=line.find( QRegExp("\""), i5a+1 );
	int i6a=line.find( QRegExp("\""), i5b+1 );		/* Pris4 */
	int i6b=line.find( QRegExp("\""), i6a+1 );
	int i7a=line.find( QRegExp("\""), i6b+1 );		/* Pris5 */
	int i7b=line.find( QRegExp("\""), i7a+1 );

	if(i1a == 0){
	    QString artnr=line.mid(i1a+1,(i1b-1)-(i1a)).latin1();
	    QString fpris=line.mid(i2a+1,(i2b-1)-(i2a)).latin1();
	    if (fpris == "0" || fpris== NULL){
		fpris="0.00";
	    }
	    QString pris1=line.mid(i3a+1,(i3b-1)-(i3a)).latin1();
	    if (pris1 == "0" || pris1 == NULL){
		pris1="0.00";
	    }
	    QString pris2=line.mid(i4a+1,(i4b-1)-(i4a)).latin1();
	    if (pris2 == "0" || pris2 == NULL){
		pris2="0.00";
	    }
	    QString pris3=line.mid(i5a+1,(i5b-1)-(i5a)).latin1();
	    if (pris3 == "0" || pris3 == NULL){
		pris3="0.00";
	    }
	    QString pris4=line.mid(i6a+1,(i6b-1)-(i6a)).latin1();
	    if (pris4 == "0" || pris4 == NULL){
		pris4="0.00";
	    }
	    QString pris5=line.mid(i7a+1,(i7b-1)-(i7a)).latin1();
	    if ( pris5 == "0" || pris5 == NULL){
		pris5="0.00";
	    }
	    if (testflag == TRUE){
		item = new QListViewItem(listViewResultat,artnr,fpris,pris1,pris2,pris3,pris4,pris5);
	    }else{
//		qDebug("pris1=%s pris2=%s pris3=%s pris4=%s pris5=%s",pris1.latin1(),pris2.latin1(),pris3.latin1(),pris4.latin1(),pris5.latin1());
		if (prislista=="A"){
		    record=artnr+delemit+pris1+delemit+pris2+delemit+pris3+delemit+pris4+delemit+pris5+"\n";
		}
		if (prislista=="1"){
		    record=artnr+delemit+pris1+"\n";
		}
		if (prislista=="2"){
		    record=artnr+delemit+pris2+"\n";
		}
		if (prislista=="3"){
		    record=artnr+delemit+pris3+"\n";
		}
		if (prislista=="4"){
		    record=artnr+delemit+pris4+"\n";
		}
		if (prislista=="5"){
		    record=artnr+delemit+pris5+"\n";
		}
		if (prislista=="F"){
		    record=artnr+delemit+fpris+"\n";
		}				
		recordsize=record.length();
		tempfile.at( offset );
		tempfile.writeBlock(record,recordsize);
		offset += recordsize ;
//		qDebug("offset=%d",offset);				
	    }
	}
            lines += line;
        }
    }
   pricefile.close();
   tempfile.close();  
   return;
}

void frmLoadPrices::updatePrices(QString file, QString price)
{
/************************************************************************/
/*	Uppdatera databasen					                  */
/************************************************************************/
    inrad="";
    errorrad="";
    const char *userp = getenv("USER");
    QString usr(userp);
    if (running != FALSE){
 //   QMessageBox::information(this,"CHGPRISW","Starta PRISUPD!");
    qDebug("updatePrices: tmpfil=%s prislista=%s",tmpfilename.latin1(),price.latin1());	   	    
    process = new QProcess();
    process->addArgument("./STYRMAN");	// OLFIX styrprogram
    process->addArgument(usr);		// Userid
    process->addArgument( "PRISUPD");		// OLFIX funktion
    process->addArgument(file);
    process->addArgument(price);
	
    frmLoadPrices::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
    frmLoadPrices::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
    frmLoadPrices::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );
 
	
    if (pricefilename== "") {
	QMessageBox::warning( this, "CHGPRISW","Filnamn saknas! \n" );
    }else {
	if ( !process->start() ) {
	// error handling
//	fprintf(stderr,"Problem starta STYRMAN/PRISUPD!\n");
	QMessageBox::warning( this, "CHGPRISW",
                           "Kan inte starta STYRMAN/PRISUPD! \n" );
                }   
  }
    qDebug("Startat PRISUPD!");
    running=FALSE;
    pushButtonCancel->setFocus();
 }
}

void frmLoadPrices::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
    qDebug("slotDataOnStdout::inrad=%s",inrad.latin1());
}

void frmLoadPrices::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmLoadPrices::slotEndOfProcess()
{
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "CHGPRISW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
    }else{
//     qDebug("slotEndOfProcess()::inrad=%s",inrad.latin1());
//     qDebug("slotEndOfProcess()::errorrad=%s",errorrad.latin1());
	QMessageBox::information( this, "CHGPRISW",
		"Prisuppdatering Klar!\n"
	);
	lineEditFilname->clear();
	inrad="";
	pushButtonCancel->setText("Sluta");
     }
}

void frmLoadPrices::pushButtonHelp_clicked()
{
	inrad="";
	frmLoadPrices::readResursFil();		// Hämta path till hjälpfilen
	
	int i1 = hjelpfil.find( QRegExp(".html"), 0 );
//	int i2 = hjelpfil.length();
	hjelpfil=hjelpfil.left(i1);
	hjelpfil=hjelpfil+"_ARTIKLAR.html";
	hjelpfil=hjelpfil+"#PRISLISTA";		// Lägg till position
//	qDebug("hjelpfil=%s",hjelpfil.latin1());

	process = new QProcess();
	process->addArgument( "./OLFIXHLP" );	// OLFIX program
	process->addArgument(hjelpfil);

	if ( !process->start() ) {
	    // error handling
	    QMessageBox::warning( this, "OLFIX","Kan inte starta OLFIXHLP!\n" );
	}
}

void frmLoadPrices::readResursFil()
{
    /*****************************************************/
    /*  Läs in .olfixrc filen här			                     */
    /* Plocka fram var hjälpfilen finns		                     */
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
	    hjelpfil=(hjelpfil.right(hjelpfil.length() - 9));
	}
	rad=line.find( QRegExp("DATABASE="), 0 );
	if(rad == 0){
	    database=line;
	    database=(database.right(database.length() - 9));
	}
            lines += line;
        }
    }
    f1.close();
}
