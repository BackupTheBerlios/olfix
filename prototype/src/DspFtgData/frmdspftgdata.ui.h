/****************************************************************/
/**		DSPFTGW					*/
/**		20003-04-15					*/
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
#define MAXSTRING 5000

    QProcess* process;
    QString inrad;
    QString errorrad;
    QString* rad;
    QString flag;
    QString ptyp;	/* posttyp */

void frmDspFtgData::init()
{
    PushButtonOK->setFocus();
    slotGetFtgData("ADR1");
}


void frmDspFtgData::slotGetFtgData(QString posttyp)
{
	const char *userp = getenv("USER");
            QString usr(userp);

	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "FTGDSP");	// OLFIX funktion
	process->addArgument(posttyp);
	
	frmDspFtgData::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmDspFtgData::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmDspFtgData::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );

	 if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/FTGDSP!\n");
		QMessageBox::warning( this, "DSPFTGW",
                            "Kan inte starta STYRMAN/FTGDSP! \n" );
	    }

}


void frmDspFtgData::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}


void frmDspFtgData::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}


void frmDspFtgData::slotEndOfProcess()
{
    int h,i,j,k,m;
   QString posttyp;
//    qDebug("frmDspFtgData-inrad=%s",inrad.latin1());
    h= -1;
    h = errorrad.find( QRegExp("Error:"), 0 );
    if (h != -1) {
	QMessageBox::critical( this, "DSPFTGW",
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
}


void frmDspFtgData::slotGetADR1()
{
   int i,j,k,m;
   QString posttyp;
   QString adr;
   QString ftgnamn;
   QString postadr; 
   QString postnr;
   QString ort;
   
//   qDebug("flag=%s",flag.latin1()); 
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = k - j;
    posttyp = inrad.mid(j+2,m-2);
//    qDebug("posttyp=%s",posttyp.latin1());   
    m = inrad.length();
    adr = inrad.mid(k+2,m-2);
//    qDebug("adr1=%s",adr.latin1());
    
    i = adr.find(QRegExp(" : "),0);
//    qDebug("adr - i=%d",i);
    ftgnamn = adr.mid(0,i);
    LineEditFtgNamn->setText(ftgnamn);
    
    j = adr.find(QRegExp(" : "),i+2);
//    qDebug("adr - j=%d adr - i=%d adr - j-i =%d",j,i,j-i);
    postadr = adr.mid(i+3,j-(i+3));
    LineEditPostAdress->setText(postadr);
    
    k = adr.find(QRegExp(" : "),j+2);
//    qDebug("adr - j=%d adr - k=%d",j,k);
    postnr = adr.mid(j+3,k-(j+3));
    LineEditPostnr1->setText(postnr);
    
    ort = adr.mid(k+3,m);
    LineEditPostOrt->setText(ort);
    
    inrad="";
    slotGetFtgData("ADR2");
}

void frmDspFtgData::slotGetADR2()
{
   int i,j,k,m;
   QString posttyp;
   QString adr;
   QString ftgnamn;
   QString adress; 
   QString postnr;
   QString ort;
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = k - j;
    posttyp = inrad.mid(j+2,m-2);
//    qDebug("posttyp=%s",posttyp.latin1());   
    m = inrad.length();
    adr = inrad.mid(k+2,m-2);
//    qDebug("adr=%s",adr.latin1());
    
    i = adr.find(QRegExp(" : "),0);   
    j = adr.find(QRegExp(" : "),i+2);
//    qDebug("adr - j=%d adr - i=%d adr - j-i =%d",j,i,j-i);
    adress = adr.mid(i+3,j-(i+3));
    LineEditBesoksAdress->setText(adress);
    
    k = adr.find(QRegExp(" : "),j+2);
//    qDebug("adr - j=%d adr - k=%d",j,k);
    postnr = adr.mid(j+3,k-(j+3));
    LineEditPostnr2->setText(postnr);
    
    ort = adr.mid(k+3,m);
    LineEditBesoksOrt->setText(ort);
    
    inrad="";
    slotGetFtgData("ADR3");
}

void frmDspFtgData::slotGetADR3()
{
   int i,j,k,m;
   QString posttyp;
   QString adr;
   QString ftgnamn;
   QString adress; 
   QString postnr;
   QString ort;
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = k - j;
    posttyp = inrad.mid(j+2,m-2);
//    qDebug("posttyp=%s",posttyp.latin1());   
    m = inrad.length();
    adr = inrad.mid(k+2,m-2);
//    qDebug("adr=%s",adr.latin1());
    
    i = adr.find(QRegExp(" : "),0);
    
    j = adr.find(QRegExp(" : "),i+2);
//    qDebug("adr - j=%d adr - i=%d adr - j-i =%d",j,i,j-i);
    adress = adr.mid(i+3,j-(i+3));
    LineEditGodsAdress->setText(adress);
    
    k = adr.find(QRegExp(" : "),j+2);
//    qDebug("adr - j=%d adr - k=%d",j,k);
    postnr = adr.mid(j+3,k-(j+3));
    LineEditPostnr3->setText(postnr);
    
    ort = adr.mid(k+3,m);
    LineEditGodsOrt->setText(ort);
    
    inrad="";
    slotGetFtgData("FTGNR");
}


void frmDspFtgData::slotGetFTGNR()
{
   int i,j,k,m;
   QString posttyp;
   QString adr;
   QString ftgnr;
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = k - j;
    posttyp = inrad.mid(j+2,m-2);
//    qDebug("posttyp=%s",posttyp.latin1());   
    m = inrad.length();
    ftgnr = inrad.mid(k+2,m-2);
//    qDebug("ftgnr=%s",ftgnr.latin1());
    LineEditFtgNr->setText(ftgnr);
    
    inrad="";
    slotGetFtgData("TFN1");
}


void frmDspFtgData::slotGetTFN1()
{
   int i,j,k,m;
   QString posttyp;
   QString adr;
   QString tfnnr;
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = k - j;
    posttyp = inrad.mid(j+2,m-2);
//    qDebug("posttyp=%s",posttyp.latin1());   
    m = inrad.length();
    tfnnr = inrad.mid(k+2,m-2);
//    qDebug("tfnnr=%s",tfnnr.latin1());
    LineEditTfnnr->setText(tfnnr);
    
    inrad="";
    slotGetFtgData("TFN2");
}


void frmDspFtgData::slotGetTFN2()
{
   int i,j,k,m;
   QString posttyp;
   QString adr;
   QString tfnnr;
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = k - j;
    posttyp = inrad.mid(j+2,m-2);
//    qDebug("posttyp=%s",posttyp.latin1());   
    m = inrad.length();
    tfnnr = inrad.mid(k+2,m-2);
//    qDebug("tfnnr=%s",tfnnr.latin1());
    LineEditMobilTfn->setText(tfnnr);
    
    inrad="";
    slotGetFtgData("TFAX");
}


void frmDspFtgData::slotGetTFAX()
{
   int i,j,k,m;
   QString posttyp;
   QString adr;
   QString tfnnr;
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = k - j;
    posttyp = inrad.mid(j+2,m-2);
//    qDebug("posttyp=%s",posttyp.latin1());   
    m = inrad.length();
    tfnnr = inrad.mid(k+2,m-2);
//    qDebug("tfnnr=%s",tfnnr.latin1());
    LineEditTelefax->setText(tfnnr);
    
    inrad="";
    slotGetFtgData("EML1");
}


void frmDspFtgData::slotGetEML1()
{
   int i,j,k,m;
   QString posttyp;
   QString adr;
   QString mailadr;
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = k - j;
    posttyp = inrad.mid(j+2,m-2);
//    qDebug("posttyp=%s",posttyp.latin1());   
    m = inrad.length();
    mailadr = inrad.mid(k+2,m-2);
//    qDebug("tfnnr=%s",tfnnr.latin1());
    LineEditemailadress->setText(mailadr);
    
    inrad="";
//    slotGetFtgData("EML1");
}
