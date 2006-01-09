/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
/***************************************************************************
			  ADDINKW  -  description
			     -------------------
		     version 0.81
    begin                	: Mån 8 dec 2003
    modified	: Mån 14 mars 2005
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
#include <qdatetime.h>
#define MAXSTRING 5000


QProcess* process;
QString inrad;
QString* rad;
QString errorrad;
QString hjelpfil;

QString bestnr;
QString bestlevnr;
QString bestlevnamn;
QString bestlevadress;
QString bestlevpostnr;
QString bestlevpostadr;
QString bestlevland;
QString levreferent;
QString besterref;
QString bestvarreftfnnr;
QString bestvarreffaxnr;
QString bestvaluta;
QString bestbetvillkor;
QString bestbetvillkortxt;
QString bestlevvillkor;
QString bestlevvillkortxt;
QString bestlevsett;
QString bestlevsetttxt;
QString bestgodsmerke;
QString bestkommentar;
QString besttextnr;
QString besttext;
QString bestvarref;
QString bestdatum;
QString bestleveransdatum;
QString bestkundnr;
QString bestleveransvecka;
QString besttyp;
QString bestartikelnr;
QString bestbenamn;
QString levartikelnr;
QString levartikelbenamn;
QString bestenhet=" ";		// För framtida behov
QString arledtid;
QString bestinkopspris;
QString bestantal;
QString radbelopp;
QString bestradnr="010";
bool radnrflag=FALSE;
QString oldradnr;
QString bestsumma="";

QString posttyp;	// För data från FTGDATA
QString bestftgnamn;
QString bestftgadr;
QString bestftgpostnr;
QString bestftgpostadr;

QString bestorderstatus="N";
QString orderhuvuddata;
QString orderraddata;

void frmAddBest::init()
{
    int vecka;
    int year;
    int dag;
    QString dagnummer;
    QString veckonr;
    QString artal;
    QDateTime dt = QDateTime::currentDateTime();
    dag= QDate::currentDate().dayOfWeek();
    bestdatum=dt.toString("yyyy-MM-dd");
    bestleveransdatum=bestdatum;
    lineEditBestDatum->setText(bestdatum);
    lineEditLeveransDatum->setText(bestleveransdatum);
    vecka= QDate::currentDate().weekNumber(&year);
    veckonr=QString::number(vecka,10);
    dagnummer=QString::number(dag,10);
    if (veckonr.length() < 2){
	veckonr.prepend("0");
    }
    artal=QString::number(year,10);
    bestleveransvecka=artal.mid(3,1) + veckonr + dagnummer;	// ÅVVD
    //    qDebug("vecka=%d, år=%d, leveransvecka=%s _%s_",vecka,year,bestleveransvecka.latin1(),veckonr.latin1());
    lineEditLeveransvecka->setText(bestleveransvecka);
    frmAddBest::listViewRader_format();
    lineEditBestLevNr->setFocus();
}

void frmAddBest::slotLevNr_returnPressed()
{
    bestlevnr=lineEditBestLevNr->text();
    bestradnr="010";
    listViewRader->clear();
    lineEditOrderSumma->clear();
    bestsumma="";
    //    qDebug("slotLevNr_returnPressed:: bestlevnr=%s",bestlevnr.latin1());
    frmAddBest::getLevData();
    lineEditGodsmarke->setFocus();
}

void frmAddBest::slotPickupLevnr( QListViewItem * item)
{
    char levnummer[11]="";
    //    qDebug("PickupLevnr\n");
    if(!item){
	return;
    }
    listViewLev->setCurrentItem(item);
    if(!item->key(0,TRUE)){
	return;
    }
    
    strcpy(levnummer,item->key(0,TRUE));
    bestlevnr=levnummer;
    lineEditBestLevNr->setText((bestlevnr));
    frmAddBest::slotLevNr_returnPressed();
}

void frmAddBest::slotbestNr_returnPressed()
{
    bestnr=lineEditInkOrderNbr->text();
    lineEditGodsmarke->setFocus();
}

void frmAddBest::lineEditGodsmarke_returnPressed()
{
    bestgodsmerke=lineEditGodsmarke->text();
    lineEditVarRef->setFocus();
}

void frmAddBest::lineEditVarRef_returnPressed()
{
    bestvarref=lineEditVarRef->text();
    lineEditErref->setFocus();
}

void frmAddBest::lineEditErref_returnPressed()
{
    besterref=lineEditErref->text();
    lineEditVarrefTfnnr->setFocus();
}

void frmAddBest::lineEditVarrefTfnnr_returnPressed()
{
    bestvarreftfnnr=lineEditVarrefTfnnr->text();
    lineEditVarrefFaxnr->setFocus();
}

void frmAddBest::lineEditVarrefFaxnr_returnPressed()
{
    bestvarreffaxnr=lineEditVarrefFaxnr->text();
    lineEditBesttyp->setFocus();
}

void frmAddBest::lineEditBesttyp_returnPressed()
{
    besttyp=lineEditBesttyp->text();
    lineEditKundnr->setFocus();
}

void frmAddBest::lineEditKundnr_returnPressed()
{
    bestkundnr=lineEditKundnr->text();
    lineEditLeveransDatum->setFocus();
}

void frmAddBest::lineEditLeveransDatum_returnPressed()
{
    bestleveransdatum=lineEditLeveransDatum->text();
    lineEditLevvillkor->setFocus();
}

void frmAddBest::lineEditLevvillkor_returnPressed()
{
    bestlevvillkor=lineEditLevvillkor->text();
    if (bestlevvillkor != ""){
	frmAddBest::CheckLevvillkor();
    }else{
	bestlevvillkortxt=" ";
    }
    lineEditLevsett->setFocus();
}

void frmAddBest::lineEditLevsett_returnPressed()
{
    bestlevsett=lineEditLevsett->text();
    if(bestlevsett !=""){
	frmAddBest::CheckLevsett();
    }else{
	bestlevsetttxt=" ";
    }
    lineEditBetvilk->setFocus();
}

void frmAddBest::lineEditBetvilk_returnPressed()
{
    bestbetvillkor=lineEditBetvilk->text();
    if(bestbetvillkor != ""){
	frmAddBest::CheckBetvillkor();
    }else{
	bestbetvillkortxt=" ";
    }
    lineEditKommentar->setFocus();
}

void frmAddBest::lineEditKommentar_returnPressed()
{
    bestkommentar=lineEditKommentar->text();
    lineEditText->setFocus();
}

void frmAddBest::lineEditText_returnPressed()
{
    besttextnr=lineEditText->text();
    if (besttextnr != ""){
	frmAddBest::CheckText();
    }
    //   bestradnr="010";
    //    bestsumma="";
    lineEditRadnr->setText(bestradnr);
    lineEditArtikelNr->setFocus();
}

/************************************************************************/
/*		Beställningsrad						*/
/************************************************************************/

void frmAddBest::lineEditArtikelNr_returnPressed()
{
    bestartikelnr=lineEditArtikelNr->text();
    if (bestartikelnr==""){
	QMessageBox::warning( this, "ADDINKW",
			      "Artikelnummer måste anges!\n" );
	lineEditArtikelNr->setFocus();
    }else{
	frmAddBest::getArtikeldata();
	lineEditBenamn->setFocus();
    }
}

void frmAddBest::lineEditBenamn_returnPressed()
{
    bestbenamn=lineEditBenamn->text();
    lineEditLeveransvecka->setFocus();
}

void frmAddBest::lineEditLeveransvecka_returnPressed()
{
    int aktuelltveckonr;
    int onskadlevvecka;
    int ledtid;
    int vecka;
    int year;
    bool ok;
    QString veckonr;
    QString artal;
    QString leveransvecka;
    vecka= QDate::currentDate().weekNumber(&year);
    veckonr=QString::number(vecka,10);
    if (veckonr.length() < 2){
	veckonr.prepend("0");
    }
    artal=QString::number(year,10);
    leveransvecka=artal.mid(3,1) + veckonr + "1";	// ÅVVD
    aktuelltveckonr=leveransvecka.toInt(&ok,10);
    ledtid=arledtid.toInt(&ok,10);
    //   qDebug("vecka=%d, år=%d, leveransvecka=%s _%s_,%d",vecka,year,bestleveransvecka.latin1(),veckonr.latin1(),levtid);
    
    bestleveransvecka=lineEditLeveransvecka->text();
    onskadlevvecka=bestleveransvecka.toInt(&ok,10);
    
    //   qDebug("aktuelltveckonr=%d, ledtid=%d, onskadlevvecka=%d",aktuelltveckonr,ledtid,onskadlevvecka);
    
    if((aktuelltveckonr + ledtid) > onskadlevvecka){
	QMessageBox::warning( this, "ADDINKW", "För kortleveranstid! \n Ledtid = "+arledtid );
	vecka=frmAddBest::VeckoBerekning(arledtid);
	veckonr=QString::number(vecka,10);
	//     qDebug("veckonr=%s",veckonr.latin1());
	lineEditLeveransvecka->setText(veckonr);
	lineEditLeveransvecka->setFocus();
    }else{
	lineEditAntal->selectAll ();
	lineEditAntal->setFocus();
    }
}

void frmAddBest::lineEditAntal_returnPressed()
{
    int i;
    double antal;
    bestantal=lineEditAntal->text();
    antal=bestantal.toDouble();
    if ( antal==0){
	QMessageBox::warning( this, "ADDINKW",
			      "Antal måste anges!\n" );
	lineEditAntal->clear();
	lineEditAntal->setFocus();
    }else{
	i = -1;
	i =bestantal.find( QRegExp(","), 0 );
	if (i != -1){
	    bestantal.replace( QChar(','), "." );
	    lineEditAntal->setText(bestantal);
	}
	lineEditAPris->setFocus();
    }
}

void frmAddBest::lineEditAPris_returnPressed()
{
    int i;
    double pris,antal,summa;
    bestinkopspris=lineEditAPris->text();
    i = -1;
    i =bestinkopspris.find( QRegExp(","), 0 );
    if (i != -1){
	bestinkopspris.replace( QChar(','), "." );
	lineEditAPris->setText(bestinkopspris);
    }
    pris=bestinkopspris.toDouble();
    antal=bestantal.toDouble();
    summa=pris*antal;
    radbelopp=radbelopp.setNum(summa,'f',2);
    lineEditRadSumma->setText(radbelopp);
    pushButtonRadJa->setFocus();
}

void frmAddBest::pushButtonRadJa_clicked()
{
    double summa ,belopp;
    QListViewItem * item;
    int i;
    item = new QListViewItem(listViewRader,bestradnr,bestartikelnr,bestbenamn,bestleveransvecka,bestantal,bestinkopspris,radbelopp,levartikelnr);
    item->setText(8,levartikelbenamn);
    if (radnrflag == FALSE){
	i = bestradnr.toInt();
	i = i+10;
	bestradnr=QString::number(i,10);
	if (bestradnr.length() <3){
	    bestradnr="0"+bestradnr;
	}
    }else{
	bestradnr=oldradnr;
	radnrflag=FALSE;
    }
    summa=bestsumma.toDouble();
    belopp=radbelopp.toDouble();
    summa=summa+belopp;
    bestsumma=bestsumma.setNum(summa,'f',2);
    lineEditOrderSumma->setText(bestsumma);
    // ----------------------------------------------
    lineEditRadnr->setText(bestradnr);
    lineEditArtikelNr->clear();
    lineEditBenamn->clear();
    lineEditAntal->clear();
    lineEditAPris->clear();
    lineEditRadSumma->clear();
    bestartikelnr="";
    bestbenamn="";
    bestantal="";
    bestinkopspris="";
    radbelopp="";
    lineEditArtikelNr->setFocus();
}

void frmAddBest::pushButtonRadNej_clicked()
{
    lineEditRadnr->setText(bestradnr);
    lineEditArtikelNr->clear();
    lineEditBenamn->clear();
    lineEditAntal->clear();
    lineEditAPris->clear();
    lineEditRadSumma->clear();
    bestartikelnr="";
    bestbenamn="";
    bestantal="";
    bestinkopspris="";
    radbelopp="";
    lineEditArtikelNr->setFocus();
}

/************************************************************************/
/*
void frmAddBest::pushButtonAvbryt_clicked()
{
    bestorderstatus="M";		// M = Makulerad order.
    frmAddBest::createOrderHuvud();
    frmAddBest::slotAddbest();    
}
*/
void frmAddBest::pushButtonOK_clicked()
{
    frmAddBest::createOrderHuvud();
    frmAddBest::slotAddbest();
}

void frmAddBest::createOrderHuvud()
{
    QString skilj;
    skilj="_:_";
    orderhuvuddata=skilj;
    orderhuvuddata.append(bestnr);
    orderhuvuddata.append(skilj);
    orderhuvuddata.append(besttyp);
    orderhuvuddata.append(skilj);
    orderhuvuddata.append(bestdatum);
    orderhuvuddata.append(skilj);
    orderhuvuddata.append(bestlevnr);
    orderhuvuddata.append(skilj);
    orderhuvuddata.append(bestlevnamn);
    orderhuvuddata.append(skilj);
    if (bestlevadress == ""){
	bestlevadress=" ";
    }
    orderhuvuddata.append(bestlevadress);
    orderhuvuddata.append(skilj);
    if (bestlevpostnr == ""){
	bestlevpostnr=" ";
    }    
    orderhuvuddata.append(bestlevpostnr);
    orderhuvuddata.append(skilj);
    if (bestlevpostadr == ""){
	bestlevpostadr=" ";
    }
    orderhuvuddata.append(bestlevpostadr);
    orderhuvuddata.append(skilj);
    if (bestlevland == ""){
	bestlevland=" ";
    }    
    orderhuvuddata.append(bestlevland);
    orderhuvuddata.append(skilj);
    orderhuvuddata.append(bestvaluta);
    orderhuvuddata.append(skilj);
    orderhuvuddata.append(bestbetvillkortxt);
    orderhuvuddata.append(skilj);
    orderhuvuddata.append(bestlevvillkortxt);
    orderhuvuddata.append(skilj);
    orderhuvuddata.append(bestlevsetttxt);
    orderhuvuddata.append(skilj);
    if (bestgodsmerke == ""){
	bestgodsmerke=" ";
    }    
    orderhuvuddata.append(bestgodsmerke);
    orderhuvuddata.append(skilj);
    orderhuvuddata.append(bestkommentar);
    orderhuvuddata.append(skilj);
    orderhuvuddata.append(besttext);
    orderhuvuddata.append(skilj);
    if (bestvarref == ""){
	bestvarref=" ";
    }    
    orderhuvuddata.append(bestvarref);
    orderhuvuddata.append(skilj);
    orderhuvuddata.append(bestvarreftfnnr);
    orderhuvuddata.append(skilj);
    orderhuvuddata.append(bestvarreffaxnr);
    orderhuvuddata.append(skilj);
    orderhuvuddata.append(besterref);
    orderhuvuddata.append(skilj);    
    if (bestleveransdatum == ""){
	bestleveransdatum=bestdatum;
    }    
    orderhuvuddata.append(bestleveransdatum);
    orderhuvuddata.append(skilj);
    if (bestkundnr == ""){
	bestkundnr=" ";
    }    
    orderhuvuddata.append(bestkundnr);
    orderhuvuddata.append(skilj);
    orderhuvuddata.append(bestftgnamn);
    orderhuvuddata.append(skilj);
    orderhuvuddata.append(bestftgadr);
    orderhuvuddata.append(skilj);
    orderhuvuddata.append(bestftgpostnr);
    orderhuvuddata.append(skilj);
    orderhuvuddata.append(bestftgpostadr);
    orderhuvuddata.append(skilj);
    orderhuvuddata.append(bestorderstatus);
    orderhuvuddata.append(skilj);
    orderhuvuddata.append(bestsumma);
    orderhuvuddata.append(skilj);
    //    qDebug("orderhuvuddata=%s",orderhuvuddata.latin1());
}

void frmAddBest::slotAddbest()
{
    /************************************************************************/
    /*	Uppdatera orderhuvud,INKREG					*/
    /************************************************************************/
    const char *userp = getenv("USER");
    QString usr(userp);
    
    inrad="";   
    errorrad="";
    process = new QProcess();
    process->addArgument("./STYRMAN");	// OLFIX styrprogram
    process->addArgument(usr);		// userid
    process->addArgument( "INKADD");	// OLFIX funktion
    process->addArgument(orderhuvuddata);
    
    frmAddBest::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
    frmAddBest::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
    frmAddBest::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );
    
    if (orderhuvuddata == ""){
	QMessageBox::warning( this, "ADDINKW",
			      "Inköpsorder saknas \n" );
    }
    else {
	if ( !process->start() ) {
	    // error handling
	    fprintf(stderr,"Problem starta STYRMAN/INKADD!\n");
	    QMessageBox::warning( this, "ADDINKW",
				  "Kan inte starta STYRMAN/INKADD! \n" );
	}
    }
}

void frmAddBest::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }   
}

void frmAddBest::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }  
}

void frmAddBest::slotEndOfProcess()
{
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    //   qDebug("Error:%s",errorrad.latin1());
    //   qDebug("Inrad:%s",inrad.latin1());
    if (i != -1) {
	QMessageBox::critical( this, "ADDINKW",
			       "ERROR!\n"+errorrad
			       );
	errorrad="";
	i = -1;
	lineEditBestLevNr->setFocus();
    }else{
	i = -1;
	i = inrad.find( QRegExp("OK:"), 0 );
	if (i != -1) {
	    QMessageBox::information( this, "ADDINKW",
				      "Uppdatering OK!\n"+errorrad
				      );
	    lineEditBestLevNr->clear();
	    lineEditInkOrderNbr->clear();
	    lineEditLevNamn->clear();
	    lineEditLevAdress->clear();
	    lineEditLevPostnr->clear();
	    lineEditLevPostAdress->clear();
	    lineEditLevLand->clear();
	    lineEditValuta->clear();
	    lineEditBetvilk->clear();
	    lineEditErref->clear();
	    lineEditGodsmarke->clear();
	    lineEditText->clear();
	    lineEditVarRef->clear();
	    lineEditVarrefTfnnr->clear();
	    lineEditVarrefFaxnr->clear();
	    lineEditKundnr->clear();
	    lineEditLeveransDatum->clear();
	    lineEditLevvillkor->clear();
	    lineEditLevsett->clear();
	    lineEditBesttyp->clear();
	    lineEditKommentar->clear();
	    lineEditFtgNamn->clear();
	    lineEditFtgAdress->clear();
	    lineEditFtgPostnr->clear();
	    lineEditFtgPostAdress->clear();
	    lineEditOrderSumma->clear();
	    bestsumma="";
	    lineEditBestDatum->setText(bestdatum);
	    lineEditLeveransDatum->setText(bestleveransdatum);
	    lineEditLeveransvecka->setText(bestleveransvecka);
	    lineEditBestLevNr->setFocus();
	    inrad="";
	    i = -1;
	    frmAddBest::uppdateOrderNr();
	    frmAddBest::SaveOrderRader();
	}
    }
}

void frmAddBest::getLevLista()
{
    const char *userp = getenv("USER");
    QString usr(userp);
    
    
    process = new QProcess();
    process->addArgument("./STYRMAN");	// OLFIX styrprogram
    process->addArgument(usr);		// userid
    process->addArgument( "LEVLST");	// OLFIX funktion
    
    frmAddBest::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
    frmAddBest::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
    frmAddBest::connect( process, SIGNAL(processExited() ),this, SLOT(slotLevListaEndOfProcess() ) );
    
    if ( !process->start() ) {
	// error handling
	fprintf(stderr,"Problem starta STYRMAN/KULST!\n");
	QMessageBox::warning( this, "Start av LEVLST ",
			      "Kan inte starta STYRMAN/LEVLST!\n"
			      );
    }
}

void frmAddBest::slotLevListaEndOfProcess()
{
    QListViewItem* item;
    int i;
    listViewLev->setSorting(1,TRUE);
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "ADDINKW",
			       "ERROR!\n"+errorrad
			       );
	errorrad="";
	i = -1;
    }
    
    i = inrad.find( QRegExp("OK: NR_0_"), 0 );
    if (i != -1) {
	QMessageBox::information( this, "ADDINKW",
				  "Leverantörsregistret innehåller inga poster!\n"
				  );
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
    //    int antrad;
    char antrad[6]="";
    char levnr[11]="";
    char namn[61]="";
    
    tmppek=tmp;
    qstrcpy(tmp,inrad);
    pos1=strstr(tmp,"OK: NR_");	// 7 tecken långt
    pos2=strstr(tmp,"_:");
    i=pos2-pos1;
    m=i+2;		// startposition för första levnr.
    
    //    qDebug("i=%d  m=%d",i,m);
    
    k=0;
    for (j=7;j<i;j++){	
	antrad[k]=tmp[j];
	k++;
    };
    i=atoi(antrad);		// i = antal poster
    
    //    qDebug("antrad=%s",antrad);
    
    for (k = 1;k <= i; k++){	// gå igenom alla raderna / posterna
	l=0;
	for(j = m; j < sizeof(levnr) + m; j++){
	    if(tmp[j] != *("_")){
		levnr[l]=tmp[j];
		l++;
	    }else{
		levnr[l] = *("\0");
		j=sizeof(levnr) + m;
	    }
	}
	//	qDebug("%s  ",levnr);
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
	item = new QListViewItem(listViewLev,levnr,namn);
	// 	 rensa levnr och namn
	for (l=0;l<sizeof(levnr);l++)
	    levnr[l]=*("\0");
	for (l=0;l<sizeof(namn);l++)
	    namn[l]=*("\0");
	//	 rensa listrad 
	listrad.remove(0,80);
    }
}


void frmAddBest::getLevData()
{
    const char *userp = getenv("USER");
    QString usr(userp);
    inrad="";
    //             qDebug("frmAddBest::getLevData()::bestlevnr=%s",bestlevnr.latin1());
    
    process = new QProcess();
    process->addArgument("./STYRMAN");	// OLFIX styrprogram
    process->addArgument(usr);		// userid
    process->addArgument( "LEVDSP");	// OLFIX funktion
    process->addArgument(bestlevnr);
    
    frmAddBest::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
    frmAddBest::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
    frmAddBest::connect( process, SIGNAL(processExited() ),this, SLOT(slotLevDataEndOfProcess() ) );
    
    if ( !process->start() ) {
	// error handling
	fprintf(stderr,"Problem starta STYRMAN/LEVDSP!\n");
	QMessageBox::warning( this, "Start av LEVDSP ",
			      "Kan inte starta STYRMAN/LEVDSP!\n"
			      );
    }
}


void frmAddBest::slotLevDataEndOfProcess()
{
    int i,m;
    
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    //   qDebug("Error:",errorrad);
    if (i != -1) {
	QMessageBox::critical( this, "ADDINKW",
			       "ERROR!\n"+errorrad
			       );
	errorrad="";
	i = -1;
    }
    i = -1;
    //     qDebug("slotLevDataEndOfProcess()::inrad=%s",inrad.latin1());
    i = inrad.find( QRegExp("OK:"), 0 );
    if (i != -1) {
	/*	 int i1 = inrad.find( QRegExp("01:"), 0 );
	 int i2 = inrad.find( QRegExp("02:"), 0 );	*/
	int i3 = inrad.find( QRegExp("3:"), 0 );	//	leverantörsnamn
	int i4 = inrad.find( QRegExp("4:"), 0 );	//	Adress
	int i5 = inrad.find( QRegExp("5:"), 0 );	//	Postnr
	int i6 = inrad.find( QRegExp("6:"), 0 );	//	Ort
	int i7 = inrad.find( QRegExp("7:"), 0 );	//	Land
	int i8 = inrad.find( QRegExp("8:"), 0 );
	/*	 int i9 = inrad.find( QRegExp("09:"), 0 );
	 int i10 = inrad.find( QRegExp("10:"), 0 );
	 int i11 = inrad.find( QRegExp("11:"), 0 );
	 int i12 = inrad.find( QRegExp("12:"), 0 );
	 int i13 = inrad.find( QRegExp("13:"), 0 );	*/
	int i14 = inrad.find( QRegExp("14:"), 0 );	// 	leverantörens referens
	int i15 = inrad.find( QRegExp("15:"), 0 );	//	erreftfnnr
	/*	 int i16 = inrad.find( QRegExp("16:"), 0 );	*/
	int i17 = inrad.find( QRegExp("17:"), 0 );
	int i18 = inrad.find( QRegExp("18:"), 0 );
	int i19 = inrad.find( QRegExp("19:"), 0 );	//	Vårt kundnummer hos leverantören
	int i20 = inrad.find( QRegExp("20:"), 0 );	//	Valuta
	int i21 = inrad.find( QRegExp("21:"), 0 );	//	Betalningsvillkor
	/*	 int i22 = inrad.find( QRegExp("22:"), 0 );
	 int i23 = inrad.find( QRegExp("23:"), 0 );
	 int i24 = inrad.find( QRegExp("24:"), 0 );
	 int i25 = inrad.find( QRegExp("25:"), 0 );
	 int i26 = inrad.find( QRegExp("26:"), 0 );
	 int i27 = inrad.find( QRegExp("27:"), 0 );
	 int i28 = inrad.find( QRegExp("28:"), 0 );
	 int i29 = inrad.find( QRegExp("29:"), 0 );
	 int i30 = inrad.find( QRegExp("30:"), 0 );
	 int i31 = inrad.find( QRegExp("31:"), 0 );
	 int i32 = inrad.find( QRegExp("32:"), 0 );
	 int i33 = inrad.find( QRegExp("33:"), 0 );	
	 int i34 = inrad.find( QRegExp("34:"), 0 );
	 int i35 = inrad.find( QRegExp("35:"), 0 );
	 int i36 = inrad.find( QRegExp("36:"), 0 );
	 int i37 = inrad.find( QRegExp("37:"), 0 );
	 int i38 = inrad.find( QRegExp("38:"), 0 );
	 int i39 = inrad.find( QRegExp("39:"), 0 );
	 int i40 = inrad.find( QRegExp("40:"), 0 );
	 int i41 = inrad.find( QRegExp("41:"), 0 );
	 int i42 = inrad.length();			*/
	/*
	 m=i2-i1;
	 if (i1 != -1){
	     levid=inrad.mid(i1+3,m-4);
	     lineEditLevNr->setText(levid);
	 }
	 
	 m=i3-i2;
	 if (i2 != -1){
//	     levorgnr=inrad.mid(i2+2,m-4);
	 }
*/
	m=i4-i3;
	if (i3 != -1){
	    bestlevnamn=inrad.mid(i3+2,m-4);
	    lineEditLevNamn->setText(bestlevnamn);
	}
	
	m=i5-i4;
	if (i4 != -1){
	    bestlevadress=inrad.mid(i4+2,m-4);
	    lineEditLevAdress->setText(bestlevadress);
	}
	
	m=i6-i5;
	if (i5 != -1){
	    bestlevpostnr=inrad.mid(i5+2,m-4);
	    lineEditLevPostnr->setText(bestlevpostnr);
	}
	
	m=i7-i6;
	if (i6 != -1){
	    bestlevpostadr=inrad.mid(i6+2,m-4);
	    lineEditLevPostAdress->setText(bestlevpostadr);
	}
	
	m=i8-i7;
	if (i7 != -1){
	    bestlevland=inrad.mid(i7+2,m-4);
	    lineEditLevLand->setText(bestlevland);
	}
	
	m=i15-i14;
	if (i14 != -1){
	    levreferent=inrad.mid(i14+3,m-4);
	    lineEditErref->setText(levreferent);
	}
	
	m=i18-i17;
	if (i17 != -1){
	    bestbetvillkor=inrad.mid(i17+3,m-4);
	    lineEditBetvilk->setText(bestbetvillkor);
	}
	
	m=i20-i19;
	if (i19 != -1){
	    bestkundnr=inrad.mid(i19+3,m-4);
	    lineEditKundnr->setText(bestkundnr);
	}
	
	m=i21-i20;
	if (i20 != -1){
	    bestvaluta=inrad.mid(i20+3,m-5);
	    lineEditValuta->setText(bestvaluta);
	}
	
	//	 m=i22-i21;
	if (i21 != -1){
	    bestbetvillkor=inrad.mid(i21+3,3);
	    lineEditBetvilk->setText(bestbetvillkor);
	}
	inrad="";
	errorrad="";
	inrad="";
	i = -1;
    }
    frmAddBest::getInkOrderNr();
}

void frmAddBest::getInkOrderNr()
{
    const char *userp = getenv("USER");
    QString usr(userp);
    
    inrad="";
    process = new QProcess();
    process->addArgument("./STYRMAN");	// OLFIX styrprogram
    process->addArgument(usr);		// userid
    process->addArgument( "FTGDSP");	// OLFIX funktion
    process->addArgument("INKNR");
    
    frmAddBest::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
    frmAddBest::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
    frmAddBest::connect( process, SIGNAL(processExited() ),this, SLOT(slotInkNrEndOfProcess() ) );
    
    if ( !process->start() ) {
	// error handling
	fprintf(stderr,"Problem starta STYRMAN/KULST!\n");
	QMessageBox::warning( this, "Start av FTGDSP",
			      "Kan inte starta STYRMAN/FTGDSP!\n"
			      );
    }
}

void frmAddBest::slotInkNrEndOfProcess()
{
    int i,m;
    int bestellningsnr;
    bool ok;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    //   qDebug("Error:",errorrad);
    if (i != -1) {
	QMessageBox::critical( this, "ADDINKW",
			       "ERROR!\n"+errorrad
			       );
	errorrad="";
	i = -1;
    }
    i = -1;
    //    qDebug("slotInkNrEndOfProcess()::inrad=%s",inrad.latin1());
    i = inrad.find( QRegExp("OK:"), 0 );
    if (i != -1) {
	//	 int i1 = inrad.find( QRegExp("1:"), 0 );
	int i2 = inrad.find( QRegExp("2:"), 0 );
	int i3 = inrad.find( QRegExp("3:"), 0 );
	
	m=i3-i2;
	if (i2 != -1){
	    bestnr=inrad.mid(i2+2,m-4);
	    bestellningsnr=bestnr.toInt(&ok,10);
	    bestellningsnr++;
	    bestnr=QString::number(bestellningsnr,10);
	    lineEditInkOrderNbr->setText(bestnr);
	}
	inrad="";
	errorrad="";
	inrad="";
	i = -1;
    }
    frmAddBest::getLeveransadress();
}

void frmAddBest::getArtikeldata()
{
    const char *userp = getenv("USER");
    QString usr(userp);
    
    inrad="";
    process = new QProcess();
    process->addArgument("./STYRMAN");	// OLFIX styrprogram
    process->addArgument(usr);		// userid
    process->addArgument( "ARDSP");	// OLFIX funktion
    process->addArgument(bestartikelnr);
    
    frmAddBest::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
    frmAddBest::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
    frmAddBest::connect( process, SIGNAL(processExited() ),this, SLOT(slotArdataEndOfProcess() ) );
    
    if ( !process->start() ) {
	// error handling
	fprintf(stderr,"Problem starta STYRMAN/ARDSP!\n");
	QMessageBox::warning( this, "Start av ARDSP",
			      "Kan inte starta STYRMAN/ARDSP!\n"
			      );
    }
}

void frmAddBest::slotArdataEndOfProcess()
{
    int i,m;
    
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    //   qDebug("Error:",errorrad);
    if (i != -1) {
	QMessageBox::critical( this, "ADDINKW",
			       "ERROR!\n"+errorrad
			       );
	errorrad="";
	i = -1;
	bestartikelnr="";
	lineEditArtikelNr->clear();
	lineEditArtikelNr->setFocus();
    }else{
	i = -1;
	//     qDebug("slotArdataEndOfProcess()::inrad=%s",inrad.latin1());
	i = inrad.find( QRegExp("OK:"), 0 );
	if (i != -1) {
	    //	    int i1 = inrad.find( QRegExp("01:"), 0 );	//	artikelnr
	    int i2 = inrad.find( QRegExp("02:"), 0 );		//	benämning 1
	    int i3 = inrad.find( QRegExp("03:"), 0 );		//	benämning 2
	    //	    int i4 = inrad.find( QRegExp("04:"), 0 );	//	enhet
	    int i6 = inrad.find( QRegExp("06:"), 0 );		//	ledtid
	    int i7 = inrad.find( QRegExp("07:"), 0 );		//	prodklass
	    int i15= inrad.find(QRegExp("15:"),0);		//	leverantörens artbenämning
	    int i16= inrad.find(QRegExp("16:"),0);
	    int i17= inrad.find(QRegExp("17:"),0);		//	leverantörens artnr
	    int i18= inrad.find(QRegExp("18:"),0);
	    m=i3-i2;
	    if (i2 != -1){
		bestbenamn=inrad.mid(i2+3,m-4);
		lineEditBenamn->setText(bestbenamn);		
	    }
	    m=i7-i6;
	    if (i6 != -1){
		arledtid=inrad.mid(i6+3,m-4);
	    }
	    //	    qDebug("Ledtid=%s",arledtid.latin1());
	    m=i16-i15;
	    if (i15 != -1){
		levartikelbenamn=inrad.mid(i15+3,m-4);
	    }
	    m=i18-i17;
	    if (i17 != -1){
		levartikelnr=inrad.mid(i17+3,m-4);
	    }
//	    qDebug("artnr=%s benämning=%s",levartikelnr.latin1(),levartikelbenamn.latin1());
	    frmAddBest::getArtikelEkonomidata();
	}
    }
}

void frmAddBest::getArtikelEkonomidata()
{
    const char *userp = getenv("USER");
    QString usr(userp);
    
    inrad="";
    process = new QProcess();
    process->addArgument("./STYRMAN");	// OLFIX styrprogram
    process->addArgument(usr);		// userid
    process->addArgument( "ARDSPL");	// OLFIX funktion
    process->addArgument("1");		// Lagerställe 1
    process->addArgument(bestartikelnr);
    
    frmAddBest::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
    frmAddBest::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
    frmAddBest::connect( process, SIGNAL(processExited() ),this, SLOT(slotArEdataEndOfProcess() ) );
    
    if ( !process->start() ) {
	// error handling
	fprintf(stderr,"Problem starta STYRMAN/ARDSP!\n");
	QMessageBox::warning( this, "Start av ARDSPL",
			      "Kan inte starta STYRMAN/ARDSPL!\n"
			      );
    }
}

void frmAddBest::slotArEdataEndOfProcess()
{
    int i,m;
    
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    //   qDebug("Error:",errorrad);
    if (i != -1) {
	QMessageBox::critical( this, "ADDINKW",
			       "ERROR!\n"+errorrad
			       );
	errorrad="";
	i = -1;
	lineEditAntal->setFocus();
    }else{
	i = -1;
	//     qDebug("slotArEdataEndOfProcess()::inrad=%s",inrad.latin1());
	i = inrad.find( QRegExp("OK:"), 0 );
	if (i != -1) {
	    //	    int i1 = inrad.find( QRegExp("01:"), 0 );	//	artikelnr
	    int i8 = inrad.find( QRegExp("08:"), 0 );	//	inköpspris
	    int i9 = inrad.find( QRegExp("09:"), 0 );	//	senaste inköpskvantitet
	    int i10 = inrad.find( QRegExp("10:"), 0 );	//	näst senaste inköpskvantitet
	    m=i9-i8;
	    if (i8 != -1){
		bestinkopspris=inrad.mid(i8+3,m-4);
		lineEditAPris->setText(bestinkopspris);
	    }
	    m=i10-i9;
	    if (i9 != -1){
		bestantal=inrad.mid(i9+3,m-4);
		lineEditAntal->setText(bestantal);
	    }
	}
    }
}

void frmAddBest::listViewRader_format()
{
    listViewRader->setColumnWidth(0,36);		// Radnr
    listViewRader->setColumnWidth(1,185);		// Artikelnr
    listViewRader->setColumnWidth(2,185);		// Benämning
    listViewRader->setColumnWidth(3,55);		// Lev.vecka
    listViewRader->setColumnWidth(4,88);		// Antal
    listViewRader->setColumnWidth(5,88);		// Pris
    listViewRader->setColumnWidth(6,80);		// Summa
}

void frmAddBest::lineEditFtgNamn_returnPressed()
{
    bestftgnamn=lineEditFtgNamn->text();
    lineEditFtgAdress->setFocus();
}

void frmAddBest::lineEditFtgAdress_returnPressed()
{
    bestftgadr=lineEditFtgAdress->text();
    lineEditFtgPostnr->setFocus();
}

void frmAddBest::lineEditFtgPostnr_returnPressed()
{
    bestftgpostnr=lineEditFtgPostnr->text();
    lineEditFtgPostAdress->setFocus();
}

void frmAddBest::lineEditFtgPostAdress_returnPressed()
{
    bestftgpostadr=lineEditFtgPostAdress->text();
    lineEditGodsmarke->setFocus();
}

void frmAddBest::getLeveransadress()
{
    posttyp="FNAMN";
    getFtgdata();
}

void frmAddBest::getFtgdata()
{
    const char *userp = getenv("USER");
    QString usr(userp);
    
    inrad="";
    process = new QProcess();
    process->addArgument("./STYRMAN");	// OLFIX styrprogram
    process->addArgument(usr);		// userid
    process->addArgument( "FTGDSP");	// OLFIX funktion
    process->addArgument(posttyp);		
    
    frmAddBest::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
    frmAddBest::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
    frmAddBest::connect( process, SIGNAL(processExited() ),this, SLOT(slotFtgdataEndOfProcess() ) );
    
    if ( !process->start() ) {
	// error handling
	fprintf(stderr,"Problem starta STYRMAN/FTGDSP!\n");
	QMessageBox::warning( this, "Start av FTGDSP",
			      "Kan inte starta STYRMAN/FTGDSP!\n"
			      );
    }
    
}

void frmAddBest::slotFtgdataEndOfProcess()
{
    int i,j,m,n;
    QString temp;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    //   qDebug("Error:",errorrad);
    if (i != -1) {
	QMessageBox::critical( this, "ADDINKW",
			       "ERROR!\n"+errorrad
			       );
	errorrad="";
	i = -1;
    }else{
	i = -1;
	//     qDebug("slotFtgdataEndOfProcess()::inrad=%s",inrad.latin1());
	i = inrad.find( QRegExp("OK:"), 0 );
	if (i != -1) {
	    int i1 = inrad.find( QRegExp("1:"), 0 );	//	posttyp
	    int i2 = inrad.find( QRegExp("2:"), 0 );	//	data
	    m=i2-i1;
	    n=inrad.length()-i2;
	    if (i1 != -1){
		temp=inrad.mid(i1+2,m-4);
		j = -1;
		j=temp.find(QRegExp("FNAMN"),0);
		if (j != -1){
		    bestftgnamn=inrad.mid(i2+2,n-4);
		    lineEditFtgNamn->setText(bestftgnamn);
		    posttyp="ADR7";
		    getFtgdata();
		}
		j = -1;
		j=temp.find(QRegExp("ADR7"),0);
		if (j != -1){
		    bestftgadr=inrad.mid(i2+2,n-4);
		    lineEditFtgAdress->setText(bestftgadr);
		    posttyp="ADR8";
		    getFtgdata();
		}
		j = -1;
		j = temp.find(QRegExp("ADR8"),0);
		if (j != -1){
		    bestftgpostnr=inrad.mid(i2+2,n-4);
		    lineEditFtgPostnr->setText(bestftgpostnr);
		    posttyp="ADR9";
		    getFtgdata();    
		}
		j = -1;
		j = temp.find(QRegExp("ADR9"),0);
		if (j != -1){
		    bestftgpostadr=inrad.mid(i2+2,n-4);
		    lineEditFtgPostAdress->setText(bestftgpostadr);
		    frmAddBest::getUserdata();
		}
	    } 
	}
    }
}


void frmAddBest::CheckText()
{
    const char *userp = getenv("USER");
    QString usr(userp);
    
    inrad="";
    process = new QProcess();
    process->addArgument("./STYRMAN");	// OLFIX styrprogram
    process->addArgument(usr);		// userid
    process->addArgument( "TXTDSP");	// OLFIX funktion
    process->addArgument(besttextnr);
    
    frmAddBest::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
    frmAddBest::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
    frmAddBest::connect( process, SIGNAL(processExited() ),this, SLOT(slotTxtEndOfProcess() ) );
    
    if ( !process->start() ) {
	// error handling
	fprintf(stderr,"Problem starta STYRMAN/TXTDSP!\n");
	QMessageBox::warning( this, "Start av TXTDSP",
			      "Kan inte starta STYRMAN/TXTDSP!\n"
			      );
    }
}

void frmAddBest::slotTxtEndOfProcess()
{
    int i,m;
    
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    //   qDebug("Error:",errorrad);
    if (i != -1) {
	QMessageBox::critical( this, "ADDINKW",
			       "ERROR!\n"+errorrad
			       );
	errorrad="";
	i = -1;
	besttext="";
	besttextnr="";
	lineEditText->clear();
	lineEditText->setFocus();
    }else{
	i = -1;
	//     qDebug("slotTxtEndOfProcess()::inrad=%s",inrad.latin1());
	i = inrad.find( QRegExp("OK:"), 0 );
	if (i != -1) {
	    //	    int i1 = inrad.find( QRegExp("01:"), 0 );	//	textnr
	    int i2 = inrad.find( QRegExp("02:"), 0 );	//	text (TXT)
	    int i3 = inrad.find( QRegExp("03:"), 0 );	//	
	    m=i3-i2;
	    if (i2 != -1){
		besttext=inrad.mid(i2+3,m-4);
		QMessageBox::information( this, "ADDINKW  TEXTREG",
					  "Kompletterande text till inköpsorder.\n\n"+besttext);
	    }
	}
    }
}

void frmAddBest::getUserdata()
{
    const char *userp = getenv("USER");
    QString usr(userp);
    
    inrad="";
    process = new QProcess();
    process->addArgument("./STYRMAN");	// OLFIX styrprogram
    process->addArgument(usr);		// userid
    process->addArgument( "USERDSP");	// OLFIX funktion
    process->addArgument(usr);
    
    frmAddBest::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
    frmAddBest::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
    frmAddBest::connect( process, SIGNAL(processExited() ),this, SLOT(slotUserEndOfProcess() ) );
    
    if ( !process->start() ) {
	// error handling
	fprintf(stderr,"Problem starta STYRMAN/USERDSP!\n");
	QMessageBox::warning( this, "Start av USERDSP",
			      "Kan inte starta STYRMAN/USERDSP!\n"
			      );
    }
}

void frmAddBest::slotUserEndOfProcess()
{
    int i,m;
    
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    bestvarref="";
    //   qDebug("Error:",errorrad);
    if (i != -1) {
	QMessageBox::critical( this, "ADDINKW",
			       "ERROR!\n"+errorrad
			       );
	errorrad="";
	i = -1;
	bestvarref="";
	lineEditVarRef->clear();
	lineEditVarRef->setFocus();
    }else{
	i = -1;
	//	qDebug("slotUserEndOfProcess()_1::inrad=%s",inrad.latin1());
	i = inrad.find( QRegExp(bestvarref.upper()), 0 );
	//	qDebug("slotUserEndOfProcess()_2::bestvarref=%s",bestvarref.latin1());
	if (i != -1) {
	    //	    int i1 = inrad.find( QRegExp("01:"), 0 );	//	userid
	    int i2 = inrad.find( QRegExp("2:"), 0 );	//	usernamn
	    int i3 = inrad.find( QRegExp("3:"), 0 );	//	avd
	    //    	    int i4 = inrad.find( QRegExp("4:"), 0 );	//	grupp
	    m=i3-i2;
	    //	    qDebug("slotUserEndOfProcess()_3::i2=%d",i2);
	    if (i2 != -1){
		bestvarref=inrad.mid(i2+2,m-4);
		//		qDebug("slotUserEndOfProcess()_4::inrad.mid(i2+2,m-4)=%s",inrad.mid(i2+2,m-4).latin1());
		lineEditVarRef->setText(bestvarref);
	    }
	}
    }
    //    qDebug("slotUserEndOfProcess()_5::Processen avslutad!\n");
}


void frmAddBest::uppdateOrderNr()
{
    const char *userp = getenv("USER");
    QString usr(userp);
    
    inrad="";
    process = new QProcess();
    process->addArgument("./STYRMAN");	// OLFIX styrprogram
    process->addArgument(usr);		// userid
    process->addArgument( "FTGUPD");	// OLFIX funktion
    process->addArgument("INKNR");
    process->addArgument(bestnr);
    
    frmAddBest::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
    frmAddBest::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
    frmAddBest::connect( process, SIGNAL(processExited() ),this, SLOT(slotOrderNbrEndOfProcess() ) );
    
    if ( !process->start() ) {
	// error handling
	fprintf(stderr,"Problem starta STYRMAN/FTGUPD!\n");
	QMessageBox::warning( this, "Start av FTGUPD",
			      "Kan inte starta STYRMAN/FTGUPD!\n"
			      );
    }
}

void frmAddBest::slotOrderNbrEndOfProcess()
{
    int i;
    
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    //   qDebug("Error:",errorrad);
    if (i != -1) {
	QMessageBox::critical( this, "ADDINKW",
			       "ERROR!\n"+errorrad
			       );
    }
    errorrad="";
}


void frmAddBest::SaveOrderRader()
{
    int i=0;    
    QListViewItemIterator it( listViewRader);
    QString rnr;
    for ( ; it.current(); ++it ){
	i++;
	QString temp0=it.current()->text(0);	// radnr
	QString temp1=it.current()->text(1);	// artikelnr
	QString temp2=it.current()->text(2);	// artikelbenämning
	QString temp3=it.current()->text(3);	// leveransvecka
	QString temp4=it.current()->text(4);	// antal
	QString temp5=it.current()->text(5);	// pris/st
	QString temp6=it.current()->text(6);	// radsumma
	QString temp7=it.current()->text(7);	// leverantörens artnr
	QString temp8=it.current()->text(8);	// leverantöreens artbenämning
	
	//      qDebug("i=%d  temp=%s, %s, %s, %s, %s, %s, %s",i,temp0.latin1(),temp1.latin1(),temp2.latin1(),temp3.latin1(),temp4.latin1(),temp5.latin1(),temp6.latin1());
	frmAddBest::createOrderrad(temp0,temp1,temp2,temp3, temp4,temp5,temp7,temp8);
    }
    listViewRader->clear();
    lineEditBestLevNr->setFocus();
}

void frmAddBest::createOrderrad(QString tmp0,QString tmp1,QString tmp2,QString tmp3, QString tmp4,QString tmp5,QString tmp7,QString tmp8)
{
    orderraddata="";
    //    qDebug("bestnr=%s, tmp=%s, %s, %s, %s, %s, %s, %s",bestnr.latin1(),tmp0.latin1(),tmp1.latin1(),tmp3.latin1(),tmp4.latin1(),tmp5.latin1());
    QString skilj;
    skilj="_:_";
    orderraddata=skilj;
    orderraddata.append(bestnr);	// ordernr
    orderraddata.append(skilj);
    orderraddata.append(tmp0);	// radnr
    orderraddata.append(skilj);
    orderraddata.append(tmp1);	//artikelnr
    orderraddata.append(skilj); 
    orderraddata.append(tmp2);	//benämning
    orderraddata.append(skilj);  
    orderraddata.append(tmp7);	//lev artikelnr
    orderraddata.append(skilj); 
    orderraddata.append(tmp8);	//lev benämning
    orderraddata.append(skilj);  
    orderraddata.append(" ");	// enhet
    orderraddata.append(skilj);
    orderraddata.append(tmp4);	// antal
    orderraddata.append(skilj);
    orderraddata.append("0");	// Levererat antal = 0 vid nyreg.
    orderraddata.append(skilj);
    orderraddata.append(tmp4);	// Restnoterat antal = antal vid nyreg.
    orderraddata.append(skilj);
    orderraddata.append(tmp5);	// inköpspris/st
    orderraddata.append(skilj);
    orderraddata.append(tmp3);	// leveransvecka
    orderraddata.append(skilj);
    orderraddata.append("0");	// Tillverkningsordernr
    orderraddata.append(skilj);
    orderraddata.append("0");	// Operationsnummer
    orderraddata.append(skilj);
    
//    qDebug("orderraddat=%s",orderraddata.latin1());
    frmAddBest::AddOrderRad();
}

void frmAddBest::AddOrderRad()
{
    /************************************************************************/
    /*	Uppdatera orderrad,INKRADREG					*/
    /************************************************************************/
    const char *userp = getenv("USER");
    QString usr(userp);
    
    inrad="";   
    errorrad="";
    process = new QProcess();
    process->addArgument("./STYRMAN");	// OLFIX styrprogram
    process->addArgument(usr);		// userid
    process->addArgument( "INKRADD");	// OLFIX funktion
    process->addArgument(orderraddata);
    
    frmAddBest::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
    frmAddBest::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
    frmAddBest::connect( process, SIGNAL(processExited() ),this, SLOT(slotOrderadEndOfProcess() ) );
    
    if (orderraddata == ""){
	QMessageBox::warning( this, "ADDINKW",
			      "Inköpsorder saknas \n" );
    }
    else {
	if ( !process->start() ) {
	    // error handling
	    fprintf(stderr,"Problem starta STYRMAN/INKRADD!\n");
	    QMessageBox::warning( this, "ADDINKW",
				  "Kan inte starta STYRMAN/INKRADD! \n" );
	}
    }
}

void frmAddBest::slotOrderadEndOfProcess()
{
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    //   qDebug("Error:",errorrad);
    if (i != -1) {
	QMessageBox::critical( this, "ADDINKW",
			       "ERROR!\n"+errorrad
			       );
    }
    errorrad="";
}

void frmAddBest::listViewRader_clicked( QListViewItem * )
{
    double radsumma ,ordersumma;
    radnrflag=TRUE;
    oldradnr=bestradnr;
    QListViewItem *item =  listViewRader->currentItem();
    if ( !item )
	return;
    item->setSelected( TRUE );
    QString temp0=item->text(0);	// radnr
    QString temp1=item->text(1);	// artikelnr
    QString temp2=item->text(2);	// artikelbenämning
    QString temp3=item->text(3);	// leveransvecka
    QString temp4=item->text(4);	// antal
    QString temp5=item->text(5);	// pris/st
    QString temp6=item->text(6);	// radsumma
    //    qDebug("temp=%s, %s, %s, %s, %s, %s, %s",temp0.latin1(),temp1.latin1(),temp2.latin1(),temp3.latin1(),temp4.latin1(),temp5.latin1(),temp6.latin1());
    // --------------------------------------------------------------
    lineEditRadnr->setText(temp0);
    bestradnr=temp0;
    lineEditArtikelNr->setText(temp1);
    lineEditBenamn->setText(temp2);
    lineEditLeveransvecka->setText(temp3);
    lineEditAntal->setText(temp4);
    lineEditAPris->setText(temp5);
    lineEditRadSumma->setText(temp6);
    radsumma=temp6.toDouble();
    ordersumma=bestsumma.toDouble();
    ordersumma=ordersumma-radsumma;
    bestsumma=bestsumma.setNum(ordersumma,'f',2);
    lineEditOrderSumma->setText(bestsumma);    
    lineEditArtikelNr->setFocus();
    delete listViewRader->currentItem();
}

int frmAddBest::VeckoBerekning( QString ledtidsdagar)
	/**************************************************/
	/*	Returnerar veckonr = dagens datum + ledtid            */	
	/**************************************************/
{
    int ledtid;
    int dag;
    int vecka;
    int year;
    int levvecka;
    bool ok;
    QString dagnummer;
    QString veckonr;
    QString artal;
    QString datum;
    
    QString leveransvecka;
    /******************************************************/
    /*	Innevarande vecka					*/
    /******************************************************/    
    vecka= QDate::currentDate().weekNumber(&year);
    dag= QDate::currentDate().dayOfWeek();
    veckonr=QString::number(vecka,10);
    if (veckonr.length() < 2){
	veckonr.prepend("0");
    }
    artal=QString::number(year,10);
    dagnummer=QString::number(dag,10);
    leveransvecka=artal.mid(3,1) + veckonr + dagnummer;	// ÅVVD
    
    /******************************************************/
    /*	Innevarande datum				*/
    /******************************************************/    
    QDateTime dt = QDateTime::currentDateTime();
    datum=dt.toString("yyyy-MM-dd");
    
    /******************************************************/ 
    /*	Ledtid						*/
    /******************************************************/  
    ledtid=arledtid.toInt(&ok,10);
    ledtid=ledtidsdagar.toInt(&ok,10);
    
    /******************************************************/ 
    /*	Innevarande datum + ledtid = möjlig leveranstid	*/
    /******************************************************/  
    QDate idag = QDate::currentDate();
    QDate newdate = idag.addDays(ledtid);
    //    QString nydatum=newdate.toString("yyyy-MM-dd");
    //    qDebug("nydatum=%s",nydatum.latin1());
    
    /******************************************************/
    /*	Ny, beräknad  vecka				*/
    /******************************************************/    
    vecka=newdate.weekNumber(&year);
    dag= newdate.dayOfWeek();
    //    qDebug("ny vecka=%d, ny dag=%d",vecka,dag);
    artal=QString::number(year,10);
    veckonr=QString::number(vecka,10);
    if (veckonr.length() < 2){
	veckonr.prepend("0");
    }
    dagnummer=QString::number(dag,10);
    leveransvecka=artal.mid(3,1) + veckonr + dagnummer;	// ÅVVD
    //    qDebug("ny leveransvecka=%s",leveransvecka.latin1()); 
    levvecka=leveransvecka.toInt(&ok,10);
    return levvecka;
}


void frmAddBest::CheckBetvillkor()
{
    const char *userp = getenv("USER");
    QString usr(userp);
    
    inrad="";
    process = new QProcess();
    process->addArgument("./STYRMAN");	// OLFIX styrprogram
    process->addArgument(usr);		// userid
    process->addArgument( "BETDSP");	// OLFIX funktion
    process->addArgument(bestbetvillkor);
    
    frmAddBest::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
    frmAddBest::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
    frmAddBest::connect( process, SIGNAL(processExited() ),this, SLOT(slotBetvillkEndOfProcess() ) );
    
    if ( !process->start() ) {
	// error handling
	fprintf(stderr,"Problem starta STYRMAN/BETDSP!\n");
	QMessageBox::warning( this, "Start av BETDSP",
			      "Kan inte starta STYRMAN/BETDSP!\n"
			      );
    }
}

void frmAddBest::slotBetvillkEndOfProcess()
{
    int i,m;
    
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    //   qDebug("Error:",errorrad);
    if (i != -1) {
	QMessageBox::critical( this, "ADDINKW",
			       "ERROR!\n"+errorrad
			       );
	errorrad="";
	i = -1;
	bestbetvillkor="";
	bestbetvillkortxt="";
	lineEditBetvilk->clear();
	lineEditBetvilk->setFocus();
    }else{
	i = -1;
	//     qDebug("slotBetvillkEndOfProcess()::inrad=%s",inrad.latin1());
	i = inrad.find( QRegExp("OK:"), 0 );
	if (i != -1) {
//	    int i1 = inrad.find( QRegExp("BETVILLKOR:"), 0 );	// villkorsnr
//	    int i2 = inrad.find( QRegExp("DAGAR:"), 0 );		// betvillkor
	    int i3 = inrad.find( QRegExp("BESKRIVNING:"), 0 );	// villkorstext
	    int i4 = inrad.find( QRegExp("END:"),0);			// slut på post
	    m=i4-(i3+12);
	    if (i3 != -1){
//		qDebug("i4=%d i3=%d m=%d",i4,i3,m);
		bestbetvillkortxt=inrad.mid(i3+12,m);
		QMessageBox::information( this, "BETALNINGSVILLKOR",
					  "   Betalningsvillkorstext.     \n\n"+bestbetvillkortxt);
	    }
	}
    }
}


void frmAddBest::CheckLevvillkor()
{
    const char *userp = getenv("USER");
    QString usr(userp);
    
    inrad="";
    process = new QProcess();
    process->addArgument("./STYRMAN");	// OLFIX styrprogram
    process->addArgument(usr);		// userid
    process->addArgument( "LEVVDSP");	// OLFIX funktion
    process->addArgument(bestlevvillkor);
    
    frmAddBest::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
    frmAddBest::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
    frmAddBest::connect( process, SIGNAL(processExited() ),this, SLOT(slotLevvillkEndOfProcess() ) );
    
    if ( !process->start() ) {
	// error handling
	QMessageBox::warning( this, "Start av LEVVDSP",
			      "Kan inte starta STYRMAN/LEVVDSP!\n"
			      );
    }
}

void frmAddBest::slotLevvillkEndOfProcess()
{
    int i,m;
    
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    //   qDebug("Error:",errorrad);
    if (i != -1) {
	QMessageBox::critical( this, "ADDINKW",
			       "ERROR!\n"+errorrad
			       );
	errorrad="";
	i = -1;
	bestlevvillkor="";
	bestlevvillkortxt="";
	lineEditLevvillkor->clear();
	lineEditLevvillkor->setFocus();
    }else{
	i = -1;
	//     qDebug("slotBetvillkEndOfProcess()::inrad=%s",inrad.latin1());
	i = inrad.find( QRegExp("OK:"), 0 );
	if (i != -1) {
//	    int i1 = inrad.find( QRegExp("01:"), 0 );		// villkorsnr
	    int i2 = inrad.find( QRegExp("02:"), 0 );		// leveransvillkor
	    int i3 = inrad.find( QRegExp("END:"),0);		// slut på post
	    m=i3-(i2+3);
	    if (i2 != -1){
//		qDebug("i4=%d i3=%d m=%d",i4,i3,m);
		bestlevvillkortxt=inrad.mid(i2+3,m);
		QMessageBox::information( this, "LEVERANSVILLKOR",
					  "   Leveransvillkorstext.     \n\n"+bestlevvillkortxt);
	    }
	}
    }
}


void frmAddBest::CheckLevsett()
{
    const char *userp = getenv("USER");
    QString usr(userp);
    
    inrad="";
    process = new QProcess();
    process->addArgument("./STYRMAN");	// OLFIX styrprogram
    process->addArgument(usr);		// userid
    process->addArgument( "LEVSDSP");	// OLFIX funktion
    process->addArgument(bestlevsett);
    
    frmAddBest::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
    frmAddBest::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
    frmAddBest::connect( process, SIGNAL(processExited() ),this, SLOT(slotLevsettEndOfProcess() ) );
    
    if ( !process->start() ) {
	// error handling
	QMessageBox::warning( this, "Start av LEVSDSP",
			      "Kan inte starta STYRMAN/LEVSDSP!\n"
			      );
    }
}

void frmAddBest::slotLevsettEndOfProcess()
{
    int i,m;
    
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    //   qDebug("Error:",errorrad);
    if (i != -1) {
	QMessageBox::critical( this, "ADDINKW",
			       "ERROR!\n"+errorrad
			       );
	errorrad="";
	i = -1;
	bestlevsett="";
	bestlevsetttxt="";
	lineEditLevsett->clear();
	lineEditLevsett->setFocus();
    }else{
	i = -1;
	//     qDebug("slotLevsettEndOfProcess()::inrad=%s",inrad.latin1());
	i = inrad.find( QRegExp("OK:"), 0 );
	if (i != -1) {
//	    int i1 = inrad.find( QRegExp("01:"), 0 );		// villkorsnr
	    int i2 = inrad.find( QRegExp("02:"), 0 );		// leveranssätt
	    int i3 = inrad.find( QRegExp("END:"),0);		// slut på post
	    m=i3-(i2+3);
	    if (i2 != -1){
//		qDebug("i4=%d i3=%d m=%d",i4,i3,m);
		bestlevsetttxt=inrad.mid(i2+3,m);
		QMessageBox::information( this, "LEVERANSSÄTT",
					  "   Leveranssättstext.     \n\n"+bestlevsetttxt);
	    }
	}
    }
}

void frmAddBest::TillUtskrift()
{
/************************************************************************/
/*	Gå till PRTINKW, Utskrift av beställning.				*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);

	process = new QProcess();
	process->addArgument( "PRTINKW");	// OLFIX program
	process->addArgument(bestnr);
	frmAddBest::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmAddBest::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
            frmAddBest::connect( process, SIGNAL(processExited() ),this, SLOT(slotUtskriftEndOfProcess() ) );

	if ( !process->start() ) {
		// error handling
		QMessageBox::warning( this, "",
                            "Kan inte starta PRTINKW! \n" );
	}
}

void frmAddBest::slotUtskriftEndOfProcess()
{
 // Kontrollera om utskriftsprogrammet, PRTINKW, blev aroppat utan fel
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::warning( this, "ADDINKWW",
		"Kunde inte hitta programmet för utskrift,PRTINKW\n"+errorrad);
	errorrad="";
    }
     i = -1;
     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
//	QMessageBox::information( this, "ADDINKW","Utskriftsprogrammet,PRTINKW, hittat!\n"+errorrad);
    inrad="";
    }
     lineEditBestLevNr->setFocus();
}

void frmAddBest::pushBtnHelp_clicked()
{
	inrad="";

	frmAddBest::readResursFil();		// Hämta path till hjälpfilen
	hjelpfil=hjelpfil+"#INKOP1";		// Lägg till position
//	qDebug("hjelpfil=%s",hjelpfil.latin1());

	process = new QProcess();
	process->addArgument( "./OLFIXHLP" );	// OLFIX program
	process->addArgument(hjelpfil);

	if ( !process->start() ) {
	    // error handling
	    QMessageBox::warning( this, "OLFIX","Kan inte starta OLFIXHLP!\n" );
	}
	lineEditArtikelNr->setFocus();
}

void frmAddBest::readResursFil()
{
    /*****************************************************/
    /*  Läs in .olfixrc filen här			               */
    /* Plocka fram var hjälpfilen finns			               */
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
