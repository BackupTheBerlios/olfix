/****************************************************************/
/**		CHGFTGW					*/
/**		20003-04-17					*/
/**		Jan Pihlgren	jan@pihlgren.se			*/
/****************************************************************/
/*****************************************************************
 *					                                                 *
 *   This program is free software; you can redistribute it and/or modify 	 *
 *   it under the terms of the GNU General Public License as published by       *
 *   the Free Software Foundation; either version 2 of the License, or     	 *
 *   (at your option) any later version.                                   		 *
 *                                                                         				 *
 *********************************************** *****************/
/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
#include <qmessagebox.h>
#include <qprocess.h>
#include <qdir.h>
#include <stdlib.h>
#include <qstring.h>
#include <qfile.h>
#include <qregexp.h>
#include <qlistview.h>
//#include "frmchgftgdata_extra.h"
#define MAXSTRING 5000

    QProcess* process;
    QString inrad;
    QString errorrad;
    QString* rad;
    QString ptyp;	/* posttyp */
    QString fdata;
    
    QLineEdit* LineEditMoms1;
    QLineEdit* LineEditMoms2;
    QLineEdit* LineEditMoms3;
    QLineEdit* LineEditMoms4;
    QLineEdit* LineEditMoms5;   
    
void frmChgFtgData::init()
{
    frmChgFtgData::slotGetPosttyper();
    LineEditPosttyp->setFocus();
}

void frmChgFtgData::slotGetPosttyp()
{
    ptyp=LineEditPosttyp->text();
    ptyp=ptyp.upper();
    LineEditPosttyp->setText((ptyp));
}

void frmChgFtgData::PushButtonGet_clicked()
{
    inrad="";
    slotGetFtgData(ptyp);
}

void frmChgFtgData::slotGetFtgData(QString posttyp)
{
	const char *userp = getenv("USER");
            QString usr(userp);

	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "FTGDSP");	// OLFIX funktion
	process->addArgument(posttyp);

	frmChgFtgData::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmChgFtgData::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmChgFtgData::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );
	if (ptyp == "" ){
    	    QMessageBox::warning( this, "CHGFTGW",
                      "Posttyp saknas! \n" );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/FTGDSP!\n");
		QMessageBox::warning( this, "CHGFTGW",
                            "Kan inte starta STYRMAN/FTGDSP! \n" );
	    }
	}
}

void frmChgFtgData::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmChgFtgData::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmChgFtgData::slotEndOfProcess()
{
    int h,i,j,k,m;
   QString posttyp;
//    qDebug("frmDspFtgData-inrad=%s",inrad.latin1());
    h= -1;
    h = errorrad.find( QRegExp("Error:"), 0 );
    if (h != -1) {
	QMessageBox::critical( this, "CHGFTGW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	h = -1;
     }
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = k - j;
    posttyp = inrad.mid(j+2,m-2);

//    qDebug("posttyp=%s",posttyp.latin1());
    i = -1;
    i = posttyp.find( QRegExp("ADR1"), 0 );
    if (i != -1){
	slotGetADR1();
    }
    i = -1;
    i = posttyp.find( QRegExp("ADR2"), 0 );
    if (i != -1){
	slotGetADR2();
    }
    i = -1;
    i = posttyp.find( QRegExp("ADR3"), 0 );
    if (i != -1){
	slotGetADR3();
    }
    i = -1;
    i = posttyp.find( QRegExp("FTGNR"), 0 );
    if (i != -1){
	slotGetFTGNR();
    }
    i = -1;
    i = posttyp.find( QRegExp("TFN1"), 0 );
    if (i != -1){
	slotGetTFN1();
    }
    i = -1;
    i = posttyp.find( QRegExp("TFN2"), 0 );
    if (i != -1){
	slotGetTFN2();
    }
    i = -1;
    i = posttyp.find( QRegExp("TFAX"), 0 );
    if (i != -1){
	slotGetTFAX();
    }
    i = -1;
    i = posttyp.find( QRegExp("EML1"), 0 );
    if (i != -1){
	slotGetEML1();
    }
    i = -1;
    i = posttyp.find( QRegExp("MOMS1"), 0 );
    if (i != -1){
	slotGetMOMS1();
    }
}


void frmChgFtgData::slotGetADR1()
{

}

void frmChgFtgData::slotGetADR2()
{

}

void frmChgFtgData::slotGetADR3()
{

}

void frmChgFtgData::slotGetFTGNR()
{
   int i,j,k,m;
   QString posttyp;
   QString adr;
   QString ftgnr;
   QLabel* TextLabelFtgnr;
   QLineEdit* LineEditFtgnr;
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = k - j;
    posttyp = inrad.mid(j+2,m-2);
    m = inrad.length();
    ftgnr = inrad.mid(k+2,m-2);
    
//    qDebug("slotGetFTGNR FTGNR=%s",inrad.latin1());
    TextLabelFtgnr = new QLabel( this, "TextLabelFtgnr" );
    // geometri = x , y , w , h
    TextLabelFtgnr->setGeometry( QRect( 10, 50, 100, 26 ) );
    TextLabelFtgnr->setText( trUtf8( "FÃ¶retagsnummer:" ) );
    
    TextLabelFtgnr->show();
    LineEditFtgnr = new QLineEdit( this, "LineEditFtgnr" );
    LineEditFtgnr->setGeometry( QRect( 110, 50, 100, 26 ) );
    LineEditFtgnr->show();
    LineEditFtgnr->setText(ftgnr);
    LineEditFtgnr->setFocus();
}

void frmChgFtgData::slotGetTFN1()
{

}

void frmChgFtgData::slotGetTFN2()
{

}


void frmChgFtgData::slotGetTFAX()
{

}

void frmChgFtgData::slotGetEML1()
{
   int i,j,k,m;
   QString posttyp;
   QString adr;
   QString email;
   QLabel* TextLabelEmail;
   QLineEdit* LineEditEmail;

    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = k - j;
    posttyp = inrad.mid(j+2,m-2);
    m = inrad.length();
    email = inrad.mid(k+2,m-2);
    
//    qDebug("slotGetEML1 EML1=%s",inrad.latin1());
    TextLabelEmail = new QLabel( this, "TextLabelEmail" );
    // geometri = x , y , w , h
    TextLabelEmail->setGeometry( QRect( 10, 50, 100, 26 ) );
    TextLabelEmail->setText( trUtf8( "e-mailadress:" ) );
    
    TextLabelEmail->show();
    LineEditEmail = new QLineEdit( this, "LineEditEmail" );
    LineEditEmail->setGeometry( QRect( 110, 50, 300, 26 ) );
    LineEditEmail->show();
    LineEditEmail->setText(email);
    LineEditEmail->setFocus();
}

void frmChgFtgData::slotGetMOMS1()
{
   int i,j,k,m;
   QString posttyp;
   QString adr;
   QString moms1;
   QLabel* TextLabelMoms1;
//   QLineEdit* LineEditMoms1;
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = k - j;
    posttyp = inrad.mid(j+2,m-2);
    m = inrad.length();
    moms1 = inrad.mid(k+2,m-2);
    
//    qDebug("slotGetMOMS! MOMS 1=%s",inrad.latin1());
    TextLabelMoms1 = new QLabel( this, "TextLabelMoms1" );
    // geometri = x , y , w , h
    TextLabelMoms1->setGeometry( QRect( 10, 50, 100, 26 ) );
    TextLabelMoms1->setText( trUtf8( "MOMS 1:" ) );
    
    TextLabelMoms1->show();
    LineEditMoms1 = new QLineEdit( this, "LineEditMoms1" );
    LineEditMoms1->setGeometry( QRect( 110, 50, 300, 26 ) );
    connect( LineEditMoms1, SIGNAL(  returnPressed()), this, SLOT( slotLineEditMoms1_returnPressed() ) );
    LineEditMoms1->show();
    LineEditMoms1->setText(moms1);
    LineEditMoms1->setFocus();
}

void frmChgFtgData::slotLineEditMoms1_returnPressed()
{
    fdata=LineEditMoms1->text();
    PushButtonUpdate->setFocus();
}

void frmChgFtgData::slotGetPosttyper()
{
	const char *userp = getenv("USER");
            QString usr(userp);
	QString bibl;

	process = new QProcess();
	process->addArgument("./STYRMAN");
	process->addArgument(usr);		// userid
	process->addArgument( "FTGLST");	// OLFIX funktion

//	fprintf(stderr,"Starta STYRMAN/VALLST! %s\n",user);

	frmChgFtgData::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmChgFtgData::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmChgFtgData::connect( process, SIGNAL(processExited() ),this, SLOT(slotGetPostEndOfProcess() ) );

	if ( !process->start() ) {
                // error handling
	    fprintf(stderr,"Problem starta STYRMAN/CHGFTGW!\n");
	    QMessageBox::warning( this, "Start av FTGLST ",
                            "Kan inte starta STYRMAN/FTGLST!\n"
                            );
        }
}

void frmChgFtgData::slotGetPostEndOfProcess()
{
    QString listrad;
    QListViewItem* item;
    char *pos1;
    char *pos2;
    char tmp[MAXSTRING];
    char *tmppek;
    int i,j,k,l,m;
    char antrad[6]="";
    char posttyp[6]="";
    char benamn[61]="";
    
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "LSTFTGW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
     }

//    qDebug("slotGetPoster %s",inrad.latin1());
    
    tmppek=tmp;
    qstrcpy(tmp,inrad);
    pos1=strstr(tmp,"NR_");
    pos2=strstr(tmp,"_:");
    i=pos2-pos1;
    m=i+2;		// startposition för första posttyp
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
	for(j = m; j < sizeof(posttyp) + m; j++){
	    if(tmp[j] != *("_")){
		posttyp[l]=tmp[j];
		l++;
	    }else{
		posttyp[l] = *("\0");
		j=sizeof(posttyp) + m;
	    }
	}
//	fprintf(stdout,"%s  ",posttyp);
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
	m=m+l+2;	// position för benamn
	item = new QListViewItem(ListView1,posttyp,benamn);
 	/* rensa posttyp och benamn */
   	for (l=0;l<sizeof(posttyp);l++)
		posttyp[l]=*("\0");
	for (l=0;l<sizeof(benamn);l++)
		benamn[l]=*("\0");
	/* rensa listrad */
	listrad.remove(0,70);
	inrad="";
    }   
}

void frmChgFtgData::ListView1_clicked( QListViewItem * item )
{
    char posttyp[6]="";

    if(!item){
	return;
    }
     ListView1->setCurrentItem(item);
     if(!item->key(0,TRUE)){
	 return;
     }

     strcpy(posttyp,item->key(0,TRUE));
     ptyp=posttyp;
     LineEditPosttyp->setText((ptyp));
}


void frmChgFtgData::slotUpdFtgData( QString posttyp, QString ftgdata )
{
	const char *userp = getenv("USER");
            QString usr(userp);
	 
	inrad="";
	errorrad="";
	    
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "FTGUPD");	// OLFIX funktion
	process->addArgument(posttyp);
	process->addArgument(ftgdata);

	frmChgFtgData::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmChgFtgData::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmChgFtgData::connect( process, SIGNAL(processExited() ),this, SLOT(slotUpdateEndOfProcess() ) );
	if (ptyp == "" ){
    	    QMessageBox::warning( this, "CHGFTGW",
                      "Posttyp saknas! \n" );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/FTGUPD!\n");
		QMessageBox::warning( this, "CHGFTGW",
                            "Kan inte starta STYRMAN/FTGUPD! \n" );
	    }
	}
}

void frmChgFtgData::slotUpdateEndOfProcess()
{
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "CHGFTGW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
    }
    else{
	i = inrad.find( QRegExp("OK:"), 0 );
	if (i != -1) {
	    QMessageBox::information( this, "CHGFTGW",
		"Uppdatering OK!\n"
		);
	    inrad="";
	    i = -1;
	    frmChgFtgData::close();
	}
    }
}

void frmChgFtgData::PushButtonUpdate_clicked()
{
    slotUpdFtgData( ptyp, fdata );
}
