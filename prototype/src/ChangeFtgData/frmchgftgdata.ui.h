/****************************************************************/
/**		CHGFTGW					*/
/**		Version: 0.2                                                                            */
/**		20003-05-06					*/
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
    QString fdata1;	// ADR1, ADR4, ADR7
    QString fdata2;	//ADR2, ADR5, ADR8
    QString fdata3;	//ADR3, ADR6, ADR9
    
   QString ftgnamn;
   QString ftgpostadr;
   QString ftgpostnr;
   QString ftgort;
    
    QLineEdit* LineEditFtgnr;
    QLineEdit* LineEditFnamn;
    QLineEdit* LineEditFtgNamn;
    QLineEdit* LineEditAdr1PostAdr;
    QLineEdit* LineEditAdr1PostNr;
    QLineEdit* LineEditAdr1Ort;
    QLineEdit* LineEditAdr2BesokAdr;
    QLineEdit* LineEditAdr2PostNr;
    QLineEdit* LineEditAdr2Ort;
    QLineEdit* LineEditAdr3GodsAdr;
    QLineEdit* LineEditAdr3PostNr;
    QLineEdit* LineEditAdr3Ort;

    
    QLineEdit* LineEditTfnnr1;
    QLineEdit* LineEditTfnnr2;
    QLineEdit* LineEditTelefax;
    QLineEdit* LineEditEmail;
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
    if (ptyp == "ADR2" | ptyp == "ADR3"){
	ptyp = "ADR1";
    }
        if (ptyp == "ADR5" | ptyp == "ADR6"){
	ptyp = "ADR4";
    }
     if (ptyp == "ADR8" | ptyp == "ADR9"){
	ptyp = "ADR7";
    }
    slotGetFtgData(ptyp);
}

void frmChgFtgData::slotGetFtgData(QString posttyp)
{
	const char *userp = getenv("USER");
            QString usr(userp);
	inrad="";
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
    }
}

void frmChgFtgData::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
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
	slotGetADR1();
    }
    i = -1;
    i = posttyp.find( QRegExp("ADR3"), 0 );
    if (i != -1){
	slotGetADR1();
    }
    i = -1;
    i = posttyp.find( QRegExp("ADR4"), 0 );
    if (i != -1){
	slotGetADR4();
    }
    i = -1;
    i = posttyp.find( QRegExp("ADR5"), 0 );
    if (i != -1){
	slotGetADR4();
    }
    i = -1;
    i = posttyp.find( QRegExp("ADR6"), 0 );
    if (i != -1){
	slotGetADR4();
    }
        i = -1;
    i = posttyp.find( QRegExp("ADR7"), 0 );
    if (i != -1){
	slotGetADR7();
    }
    i = -1;
    i = posttyp.find( QRegExp("ADR8"), 0 );
    if (i != -1){
	slotGetADR7();
    }
    i = -1;
    i = posttyp.find( QRegExp("ADR9"), 0 );
    if (i != -1){
	slotGetADR7();
    }

    i = -1;
    i = posttyp.find( QRegExp("FTGNR"), 0 );
    if (i != -1){
	slotGetFTGNR();
    }
    i = -1;
    i = posttyp.find( QRegExp("FNAMN"), 0 );
    if (i != -1){
	slotGetFNAMN();
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
    i = -1;
    i = posttyp.find( QRegExp("MOMS2"), 0 );
    if (i != -1){
	slotGetMOMS2();
    }
    i = -1;
    i = posttyp.find( QRegExp("MOMS3"), 0 );
    if (i != -1){
	slotGetMOMS3();
    }
}

void frmChgFtgData::slotGetADR1()
{
   int i,j,k,m;
   QString posttyp;
   QString adr;
   QLabel* TextLabelPostAdr;
   QLabel* TextLabelPostNr;
   QLabel* TextLabelOrt;
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = k-j;
    adr = inrad.mid(j+2,m-2);
    m = inrad.length()-(k+3);
//    qDebug("adr=%s",adr.latin1());
    if (adr.mid(0,4) == "ADR1"){
	ftgpostadr = inrad.mid(k+2,m);
	inrad="";
	slotGetFtgData("ADR2");
    }    
     if (adr.mid(0,4) == "ADR2"){
	ftgpostnr = inrad.mid(k+2,m);
	inrad="";
	slotGetFtgData("ADR3");
    }
     if (adr.mid(0,4) == "ADR3"){
	ftgort = inrad.mid(k+2,m);
	inrad="";
    }
   
    TextLabelPostAdr = new QLabel( this, "TextLabelPostAdr" );
    // geometri = x , y , w , h
    TextLabelPostAdr->setGeometry( QRect( 10, 80, 100, 26 ) );
    TextLabelPostAdr->setText( trUtf8( "Postadress:" ) );
    TextLabelPostAdr->show();
    
    LineEditAdr1PostAdr = new QLineEdit( this, "LineEditAdr1PostAdr" );
    LineEditAdr1PostAdr->setGeometry( QRect( 110, 80, 300, 26 ) );
    connect( LineEditAdr1PostAdr, SIGNAL(  returnPressed()), this, SLOT( slotLineEditAdr1_PostAdr_returnPressed() ) );
    LineEditAdr1PostAdr->show();
    LineEditAdr1PostAdr->setText(ftgpostadr);
    
    TextLabelPostNr = new QLabel( this, "TextLabelPostNr" );
    // geometri = x , y , w , h
    TextLabelPostNr->setGeometry( QRect( 10, 110, 100, 26 ) );
    TextLabelPostNr->setText( trUtf8( "Postnummer:" ) );
    TextLabelPostNr->show();
 
    LineEditAdr1PostNr = new QLineEdit( this, "LineEditAdr1PostNr" );
    LineEditAdr1PostNr->setGeometry( QRect( 110, 110, 60, 26 ) );
    connect( LineEditAdr1PostNr, SIGNAL(  returnPressed()), this, SLOT( slotLineEditAdr1_PostNr_returnPressed() ) );
    LineEditAdr1PostNr->show();
    LineEditAdr1PostNr->setText(ftgpostnr);
    
    TextLabelOrt = new QLabel( this, "TextLabelOrt" );
    // geometri = x , y , w , h
    TextLabelOrt->setGeometry( QRect( 10, 140, 300, 26 ) );
    TextLabelOrt->setText( trUtf8( "Ort:" ) );
    TextLabelOrt->show();
    
    LineEditAdr1Ort = new QLineEdit( this, "LineEditAdr1PostAdr" );
    LineEditAdr1Ort->setGeometry( QRect( 110, 140, 300, 26 ) );
    connect( LineEditAdr1Ort, SIGNAL(  returnPressed()), this, SLOT( slotLineEditAdr1_Ort_returnPressed() ) );
    LineEditAdr1Ort->show();
    LineEditAdr1Ort->setText(ftgort);
    
    LineEditAdr1PostAdr->setFocus();   
}

void frmChgFtgData::slotLineEditAdr1_FtgNamn_returnPressed()
{
    ftgnamn = LineEditFtgNamn->text();
    fdata = ftgnamn;
//    qDebug("slotLineEditAdr1_FtgNamn fdata=%s",fdata.latin1());  
    LineEditAdr1PostAdr->setFocus();
}

void frmChgFtgData::slotLineEditAdr1_PostAdr_returnPressed()
{
    ftgpostadr = LineEditAdr1PostAdr->text();
    fdata1 = ftgpostadr;
    LineEditAdr1PostNr->setFocus();
}

void frmChgFtgData::slotLineEditAdr1_PostNr_returnPressed()
{
    ftgpostnr=LineEditAdr1PostNr->text();
    fdata2 = ftgpostnr;
    LineEditAdr1Ort->setFocus();
}

void frmChgFtgData::slotLineEditAdr1_Ort_returnPressed()
{
    ftgort = LineEditAdr1Ort->text();
    fdata3 = ftgort;
    PushButtonUpdate->setFocus();
}
//===============
void frmChgFtgData::slotGetADR4()
{
   int i,j,k,m;
   QString posttyp;
   QString adr;
   QLabel* TextLabelBesokAdr;
   QLabel* TextLabelPostNr;
   QLabel* TextLabelOrt;
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = k-j;
    adr = inrad.mid(j+2,m-2);
    m = inrad.length()-(k+3);
//    qDebug("adr=%s",adr.latin1());
    if (adr.mid(0,4) == "ADR4"){
	ftgpostadr = inrad.mid(k+2,m);
	inrad="";
	slotGetFtgData("ADR5");
    }    
     if (adr.mid(0,4) == "ADR5"){
	ftgpostnr = inrad.mid(k+2,m);
	inrad="";
	slotGetFtgData("ADR6");
    }
     if (adr.mid(0,4) == "ADR6"){
	ftgort = inrad.mid(k+2,m);
	inrad="";
    }
   
    TextLabelBesokAdr = new QLabel( this, "TextLabelBesokAdr" );
    // geometri = x , y , w , h
    TextLabelBesokAdr->setGeometry( QRect( 10, 80, 100, 26 ) );
    TextLabelBesokAdr->setText( trUtf8( "Besöksadress:" ) );
    TextLabelBesokAdr->show();
    
    LineEditAdr2BesokAdr = new QLineEdit( this, "LineEditAdr2BesokAdr" );
    LineEditAdr2BesokAdr->setGeometry( QRect( 110, 80, 300, 26 ) );
    connect( LineEditAdr2BesokAdr, SIGNAL(  returnPressed()), this, SLOT( slotLineEditAdr2_BesokAdr_returnPressed() ) );
    LineEditAdr2BesokAdr->show();
    LineEditAdr2BesokAdr->setText(ftgpostadr);
    
    TextLabelPostNr = new QLabel( this, "TextLabelPostNr" );
    // geometri = x , y , w , h
    TextLabelPostNr->setGeometry( QRect( 10, 110, 100, 26 ) );
    TextLabelPostNr->setText( trUtf8( "Postnummer:" ) );
    TextLabelPostNr->show();
 
    LineEditAdr2PostNr = new QLineEdit( this, "LineEditAdr2PostNr" );
    LineEditAdr2PostNr->setGeometry( QRect( 110, 110, 60, 26 ) );
    connect( LineEditAdr2PostNr, SIGNAL(  returnPressed()), this, SLOT( slotLineEditAdr2_PostNr_returnPressed() ) );
    LineEditAdr2PostNr->show();
    LineEditAdr2PostNr->setText(ftgpostnr);
    
    TextLabelOrt = new QLabel( this, "TextLabelOrt" );
    // geometri = x , y , w , h
    TextLabelOrt->setGeometry( QRect( 10, 140, 300, 26 ) );
    TextLabelOrt->setText( trUtf8( "Ort:" ) );
    TextLabelOrt->show();
    
    LineEditAdr2Ort = new QLineEdit( this, "LineEditAdr2PostAdr" );
    LineEditAdr2Ort->setGeometry( QRect( 110, 140, 300, 26 ) );
    connect( LineEditAdr2Ort, SIGNAL(  returnPressed()), this, SLOT( slotLineEditAdr2_Ort_returnPressed() ) );
    LineEditAdr2Ort->show();
    LineEditAdr2Ort->setText(ftgort);
    
    LineEditAdr2BesokAdr->setFocus();   
}
//================
void frmChgFtgData::slotLineEditAdr2_BesokAdr_returnPressed()
{
    ftgpostadr = LineEditAdr2BesokAdr->text();
    fdata1 = ftgpostadr;
    LineEditAdr2PostNr->setFocus();
}

void frmChgFtgData::slotLineEditAdr2_PostNr_returnPressed()
{
    ftgpostnr=LineEditAdr2PostNr->text();
    fdata2 = ftgpostnr;
    LineEditAdr2Ort->setFocus();
}

void frmChgFtgData::slotLineEditAdr2_Ort_returnPressed()
{
    ftgort = LineEditAdr2Ort->text();
    fdata3 = ftgort;
    PushButtonUpdate->setFocus();
}
//================
void frmChgFtgData::slotGetADR7()
{
   int i,j,k,m;
   QString posttyp;
   QString adr;
   QLabel* TextLabelGodsAdr;
   QLabel* TextLabelPostNr;
   QLabel* TextLabelOrt;
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = k-j;
//    qDebug("inrad=123456789012345678901234567890");
//    qDebug("inrad=%s",inrad.latin1());
//    qDebug("k=%d j=%d m=%d",k,j,m);
    adr = inrad.mid(j+2,m-2);
    m = inrad.length()-(k+3);
//    qDebug("m=%d",m);
//    qDebug("adr=%s",adr.latin1());
    if (adr.mid(0,4) == "ADR7"){
	ftgpostadr = inrad.mid(k+2,m);
	inrad="";
	slotGetFtgData("ADR8");
    }    
     if (adr.mid(0,4) == "ADR8"){
	ftgpostnr = inrad.mid(k+2,m);
	inrad="";
	slotGetFtgData("ADR9");
    }
     if (adr.mid(0,4) == "ADR9"){
	ftgort = inrad.mid(k+2,m);
	inrad="";
    }
   
    TextLabelGodsAdr = new QLabel( this, "TextLabelGodsAdr" );
    // geometri = x , y , w , h
    TextLabelGodsAdr->setGeometry( QRect( 10, 80, 100, 26 ) );
    TextLabelGodsAdr->setText( trUtf8( "Godsadress:" ) );
    TextLabelGodsAdr->show();
    
    LineEditAdr3GodsAdr = new QLineEdit( this, "LineEditAdr3GodsAdr" );
    LineEditAdr3GodsAdr->setGeometry( QRect( 110, 80, 300, 26 ) );
    connect( LineEditAdr3GodsAdr, SIGNAL(  returnPressed()), this, SLOT( slotLineEditAdr3_GodsAdr_returnPressed() ) );
    LineEditAdr3GodsAdr->show();
    LineEditAdr3GodsAdr->setText(ftgpostadr);
    
    TextLabelPostNr = new QLabel( this, "TextLabelPostNr" );
    // geometri = x , y , w , h
    TextLabelPostNr->setGeometry( QRect( 10, 110, 100, 26 ) );
    TextLabelPostNr->setText( trUtf8( "Postnummer:" ) );
    TextLabelPostNr->show();
 
    LineEditAdr3PostNr = new QLineEdit( this, "LineEditAdr3PostNr" );
    LineEditAdr3PostNr->setGeometry( QRect( 110, 110, 60, 26 ) );
    connect( LineEditAdr3PostNr, SIGNAL(  returnPressed()), this, SLOT( slotLineEditAdr3_PostNr_returnPressed() ) );
    LineEditAdr3PostNr->show();
    LineEditAdr3PostNr->setText(ftgpostnr);
    
    TextLabelOrt = new QLabel( this, "TextLabelOrt" );
    // geometri = x , y , w , h
    TextLabelOrt->setGeometry( QRect( 10, 140, 300, 26 ) );
    TextLabelOrt->setText( trUtf8( "Ort:" ) );
    TextLabelOrt->show();
    
    LineEditAdr3Ort = new QLineEdit( this, "LineEditAdr3Ort" );
    LineEditAdr3Ort->setGeometry( QRect( 110, 140, 300, 26 ) );
    connect( LineEditAdr3Ort, SIGNAL(  returnPressed()), this, SLOT( slotLineEditAdr3_Ort_returnPressed() ) );
    LineEditAdr3Ort->show();
    LineEditAdr3Ort->setText(ftgort);
    
    LineEditAdr3GodsAdr->setFocus();   
}
//================
void frmChgFtgData::slotLineEditAdr3_GodsAdr_returnPressed()
{
    ftgpostadr = LineEditAdr3GodsAdr->text();
    fdata1 = ftgpostadr;
    LineEditAdr3PostNr->setFocus();
}

void frmChgFtgData::slotLineEditAdr3_PostNr_returnPressed()
{
    ftgpostnr=LineEditAdr3PostNr->text();
    fdata2 = ftgpostnr;
    LineEditAdr3Ort->setFocus();
}

void frmChgFtgData::slotLineEditAdr3_Ort_returnPressed()
{
    ftgort = LineEditAdr3Ort->text();
    fdata3 = ftgort;
    PushButtonUpdate->setFocus();
}
//================
void frmChgFtgData::slotGetFNAMN()
{
   int i,j,k,m;
   QString posttyp;
   QString adr;
   QString fnamn;
   QLabel* TextLabelFnamn;
//   QLineEdit* LineEditFtgnr;
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = k - j;
    posttyp = inrad.mid(j+2,m-2);
    m = inrad.length();
    fnamn = inrad.mid(k+2,m-2);
    
//    qDebug("slotGetFTGNR FTGNR=%s",inrad.latin1());
    TextLabelFnamn = new QLabel( this, "TextLabelFnamn" );
    // geometri = x , y , w , h
    TextLabelFnamn->setGeometry( QRect( 10, 50, 100, 26 ) );
    TextLabelFnamn->setText( trUtf8( "FÃ¶retagsnamn:" ) );
    
    TextLabelFnamn->show();
    LineEditFnamn = new QLineEdit( this, "LineEditFnamn" );
    LineEditFnamn->setGeometry( QRect( 110, 50, 100, 26 ) );
    connect( LineEditFnamn, SIGNAL(  returnPressed()), this, SLOT( slotLineEditFnamn_returnPressed() ) );    
    LineEditFnamn->show();
    LineEditFnamn->setText(fnamn);
    LineEditFnamn->setFocus();
}

void frmChgFtgData::slotLineEditFnamn_returnPressed()
{
    fdata=LineEditFnamn->text();
    PushButtonUpdate->setFocus();
}

void frmChgFtgData::slotGetFTGNR()
{
   int i,j,k,m;
   QString posttyp;
   QString adr;
   QString ftgnr;
   QLabel* TextLabelFtgnr;
//   QLineEdit* LineEditFtgnr;
   
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
    connect( LineEditFtgnr, SIGNAL(  returnPressed()), this, SLOT( slotLineEditFtgnr_returnPressed() ) );    
    LineEditFtgnr->show();
    LineEditFtgnr->setText(ftgnr);
    LineEditFtgnr->setFocus();
}

void frmChgFtgData::slotLineEditFtgnr_returnPressed()
{
    fdata=LineEditFtgnr->text();
    PushButtonUpdate->setFocus();
}

void frmChgFtgData::slotGetTFN1()
{
   int i,j,k,m;
   QString posttyp;
   QString adr;
   QString tfnnr1;
   QLabel* TextLabelTfnnr1;
//   QLineEdit* LineEditTfnnr1;
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = k - j;
    posttyp = inrad.mid(j+2,m-2);
    m = inrad.length();
    tfnnr1 = inrad.mid(k+2,m-2);
    
//    qDebug("slotGetTFN1(1) Tfnnr=%s",inrad.latin1());
    TextLabelTfnnr1 = new QLabel( this, "TextLabelTfnnr1" );
    // geometri = x , y , w , h
    TextLabelTfnnr1->setGeometry( QRect( 10, 50, 100, 26 ) );
    TextLabelTfnnr1->setText( trUtf8( "Telefonnummer 1:" ) );   
    TextLabelTfnnr1->show();
//    qDebug("slotGetTFN1(2) Posttyp=%s",posttyp.latin1());
    LineEditTfnnr1 = new QLineEdit( this, "LineEditTfnnr1" );
    LineEditTfnnr1->setGeometry( QRect( 110, 50, 100, 26 ) );
//    qDebug("slotGetTFN1(3) Tfnnr=%s",tfnnr1.latin1());    
    connect( LineEditTfnnr1, SIGNAL(  returnPressed()), this, SLOT( slotLineEditTfnnr1_returnPressed() ) );    
    LineEditTfnnr1->show();
    LineEditTfnnr1->setText(tfnnr1);
    LineEditTfnnr1->setFocus();
}

void frmChgFtgData::slotLineEditTfnnr1_returnPressed()
{
    fdata=LineEditTfnnr1->text();
    PushButtonUpdate->setFocus();
}

void frmChgFtgData::slotGetTFN2()
{
   int i,j,k,m;
   QString posttyp;
   QString adr;
   QString tfnnr2;
   QLabel* TextLabelTfnnr2;
//   QLineEdit* LineEditTfnnr2;
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = k - j;
    posttyp = inrad.mid(j+2,m-2);
    m = inrad.length();
    tfnnr2 = inrad.mid(k+2,m-2);
    
//    qDebug("slotGetTFN2(1) Tfnnr=%s",inrad.latin1());
    TextLabelTfnnr2 = new QLabel( this, "TextLabelTfnnr2" );
    // geometri = x , y , w , h
    TextLabelTfnnr2->setGeometry( QRect( 10, 50, 100, 26 ) );
    TextLabelTfnnr2->setText( trUtf8( "Mobiltfnnummer:" ) );   
    TextLabelTfnnr2->show();
//    qDebug("slotGetTFN2(2) Posttyp=%s",posttyp.latin1());
    LineEditTfnnr2 = new QLineEdit( this, "LineEditTfnnr2" );
    LineEditTfnnr2->setGeometry( QRect( 110, 50, 100, 26 ) );
//    qDebug("slotGetTFN2(3) Tfnnr=%s",tfnnr2.latin1());    
    connect( LineEditTfnnr2, SIGNAL(  returnPressed()), this, SLOT( slotLineEditTfnnr2_returnPressed() ) );
    LineEditTfnnr2->show();
    LineEditTfnnr2->setText(tfnnr2);
    LineEditTfnnr2->setFocus();
}

void frmChgFtgData::slotLineEditTfnnr2_returnPressed()
{
    fdata=LineEditTfnnr2->text();
    PushButtonUpdate->setFocus();
}

void frmChgFtgData::slotGetTFAX()
{
   int i,j,k,m;
   QString posttyp;
   QString adr;
   QString tfax;
   QLabel* TextLabelTelefax;
//   QLineEdit* LineEditTfnnr2;
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = k - j;
    posttyp = inrad.mid(j+2,m-2);
    m = inrad.length();
    tfax = inrad.mid(k+2,m-2);
    
//    qDebug("slotGetTFAX(1) Tfax=%s",inrad.latin1());
    TextLabelTelefax = new QLabel( this, "TextLabelTelefax" );
    // geometri = x , y , w , h
    TextLabelTelefax->setGeometry( QRect( 10, 50, 100, 26 ) );
    TextLabelTelefax->setText( trUtf8( "Telefaxnummer:" ) );   
    TextLabelTelefax->show();
//    qDebug("slotGetTFAX(2) Posttyp=%s",posttyp.latin1());
    LineEditTelefax = new QLineEdit( this, "LineEditTelfax" );
    LineEditTelefax->setGeometry( QRect( 110, 50, 100, 26 ) );
//    qDebug("slotGetTFAX(3) Tfnnr=%s",tfax.latin1());    
    connect( LineEditTelefax, SIGNAL(  returnPressed()), this, SLOT( slotLineEditTelefax_returnPressed() ) );
    LineEditTelefax->show();
    LineEditTelefax->setText(tfax);
    LineEditTelefax->setFocus();
}

void frmChgFtgData::slotLineEditTelefax_returnPressed()
{
    fdata=LineEditTelefax->text();
    PushButtonUpdate->setFocus();
}
void frmChgFtgData::slotGetEML1()
{
   int i,j,k,m;
   QString posttyp;
   QString adr;
   QString email;
   QLabel* TextLabelEmail;
//   QLineEdit* LineEditEmail;

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
    connect( LineEditEmail, SIGNAL(  returnPressed()), this, SLOT( slotLineEditEmail_returnPressed() ) );
    LineEditEmail->show();
    LineEditEmail->setText(email);
    LineEditEmail->setFocus();
}

void frmChgFtgData::slotLineEditEmail_returnPressed()
{
    fdata=LineEditEmail->text();
    PushButtonUpdate->setFocus();
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

void frmChgFtgData::slotGetMOMS2()
{
   int i,j,k,m;
   QString posttyp;
   QString adr;
   QString moms2;
   QLabel* TextLabelMoms2;
//   QLineEdit* LineEditMoms1;
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = k - j;
    posttyp = inrad.mid(j+2,m-2);
    m = inrad.length();
    moms2 = inrad.mid(k+2,m-2);
    
//    qDebug("slotGetMOMS! MOMS 1=%s",inrad.latin1());
    TextLabelMoms2 = new QLabel( this, "TextLabelMoms2" );
    // geometri = x , y , w , h
    TextLabelMoms2->setGeometry( QRect( 10, 50, 100, 26 ) );
    TextLabelMoms2->setText( trUtf8( "MOMS 2:" ) );
    
    TextLabelMoms2->show();
    LineEditMoms2 = new QLineEdit( this, "LineEditMoms2" );
    LineEditMoms2->setGeometry( QRect( 110, 50, 300, 26 ) );
    connect( LineEditMoms2, SIGNAL(  returnPressed()), this, SLOT( slotLineEditMoms2_returnPressed() ) );
    LineEditMoms2->show();
    LineEditMoms2->setText(moms2);
    LineEditMoms2->setFocus();
}

void frmChgFtgData::slotLineEditMoms2_returnPressed()
{
    fdata=LineEditMoms2->text();
    PushButtonUpdate->setFocus();
}

void frmChgFtgData::slotGetMOMS3()
{
   int i,j,k,m;
   QString posttyp;
   QString adr;
   QString moms3;
   QLabel* TextLabelMoms3;
//   QLineEdit* LineEditMoms3;
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = k - j;
    posttyp = inrad.mid(j+2,m-2);
    m = inrad.length();
    moms3 = inrad.mid(k+2,m-2);
    
//    qDebug("slotGetMOMS! MOMS 1=%s",inrad.latin1());
    TextLabelMoms3 = new QLabel( this, "TextLabelMoms3" );
    // geometri = x , y , w , h
    TextLabelMoms3->setGeometry( QRect( 10, 50, 100, 26 ) );
    TextLabelMoms3->setText( trUtf8( "MOMS 3:" ) );
    
    TextLabelMoms3->show();
    LineEditMoms3 = new QLineEdit( this, "LineEditMoms3" );
    LineEditMoms3->setGeometry( QRect( 110, 50, 300, 26 ) );
    connect( LineEditMoms3, SIGNAL(  returnPressed()), this, SLOT( slotLineEditMoms3_returnPressed() ) );
    LineEditMoms3->show();
    LineEditMoms3->setText(moms3);
    LineEditMoms3->setFocus();
}

void frmChgFtgData::slotLineEditMoms3_returnPressed()
{
    fdata=LineEditMoms3->text();
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
    if (ptyp == "ADR1" | ptyp == "ADR2" | ptyp == "ADR3"){
	ptyp = "ADR1";
	slotUpdFtgData( ptyp, fdata1 );
	ptyp = "ADR2";
	slotUpdFtgData( ptyp, fdata2 );
	ptyp = "ADR3";
	slotUpdFtgData( ptyp, fdata3 );
	return;
    }
    if (ptyp == "ADR4" | ptyp == "ADR5" | ptyp == "ADR6"){
	ptyp = "ADR4";
	slotUpdFtgData( ptyp, fdata1 );
	ptyp = "ADR5";
	slotUpdFtgData( ptyp, fdata2 );
	ptyp = "ADR6";
	slotUpdFtgData( ptyp, fdata3 );
	return;
    }
    if (ptyp == "ADR7" | ptyp == "ADR8" | ptyp == "ADR9"){
	ptyp = "ADR7";
	slotUpdFtgData( ptyp, fdata1 );
	ptyp = "ADR8";
	slotUpdFtgData( ptyp, fdata2 );
	ptyp = "ADR9";
	slotUpdFtgData( ptyp, fdata3 );
	return;
    }

    slotUpdFtgData( ptyp, fdata );
}

