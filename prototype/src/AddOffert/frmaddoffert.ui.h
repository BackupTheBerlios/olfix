/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
/***************************************************************************
                          ADDOFFW  -  description
	         Registrering av kundoffert med möjlighet att registrera en ny kund.
                             -------------------
		     version 0.1
    begin   	: 	Fre    21 april    2006
    Updated	: 	
    copyright:	 (C) 2006 by Jan Pihlgren
    email     	:	 jan@pihlgren.se
 ***************************************************************************/
/*****************************************************************
 *					                                            *
 *   This program is free software; you can redistribute it and/or modify 	 *
 *   it under the terms of the GNU General Public License as published by       	 *
 *   the Free Software Foundation; either version 2 of the License, or     	 *
 *   (at your option) any later version.                                   		 	 *
 *                                                                         				 *
 *********************************************** *****************/
#include <qmessagebox.h>
#include <qprocess.h>
#include <qdir.h>
#include <stdlib.h>
#include <qstring.h>
#include <qfile.h>
#include <qregexp.h>
#define MAXSTRING 5000
#define MAXPROCESS 200

    int ganger=0;
    int processnbr=0;
    QProcess* process;
    QProcess* processpris;
    QProcess* processartikel;
    QProcess* radproc[MAXPROCESS];
    QString inrad;
    QString inrad2;
    QString inrad3;    
    QString inrad4;
    QString inrad5;		// updateReserveratAntal()
    QString inradArtikel;
    QString inradpris;
    QString* rad;
    QString errorrad;
    QString errorrad2;
    QString errorrad3;
    QString errorrad4;
    QString errorrad5;	// updateReserveratAntal()
    QString errorradArtikel;
    QString errorradpris;
    QString hjelpfil;    
    QString prislista;		/* 2006-02-03 */
    QString prislista1;
    QString prislista2;
    QString prislista3;
    QString prislista4;
    QString prislista5;
    QString fpris;		// försäljningspris enligt ARTIKELREG
    bool prisflag=FALSE;
    bool avbryt=FALSE;
    
    QString offertdatum;
    QString offertnr;
    QString offertkundnr;
    QString offertkundnamn;
    QString offertkundadress;
    QString offertkundpostnr;
    QString offertkundpostadr;
    QString offertkundland;
    
    QString offertkundref;
    QString offertkundlevadress;
    QString offertkundlevpostnr;
    QString offertkundlevpostadr;
    QString offertkundlevland;
    
    
    QString offerttfnnr;
    QString offertfaxnr;
    QString offerttelexnr;
    QString offertemail;
    QString offertref;
    QString offertreftfnnr;
    QString offertmomskod;
    QString offertmoms;
    QString offertkontonr;
    QString offertpgnr;
    QString offertbgnr;
    QString seljare;
    QString godsmarke;
    QString offertleveranstid;
    QString offertvaluta;
    QString offertbetvillkor;
    QString offertlevvillkor;
    QString offertlevplats;
    QString offerthuvuddata;       
    
    /*  Offertradrad	 */	
    bool radnrflag=FALSE;
    QString offertradnr="010";    
    QString oldradnr;
    QString offertartikelnr;
    QString prodklass;
    QString offertbenamn;
    QString radleveransvecka;
    QString offertantal;
    QString offertradpris;
    QString radbelopp;
    QString radmoms;		/*  Moms på radbelopp */
    QString offertraddata;	    
    
    /* Offert 	*/
    QString offertdel;			/*  Del av offertn, H=offerthuvud, R=offertrad */
    QString offertsumma;
    QString momssumma;		/*  Total moms på offertn */
    QString fraktbelopp;
    QString fraktmomskr;
    bool nykundflag=FALSE;
//    QString kunddata="";		/* för nyregistrering av kund */
    
void frmAddOffert::init()
{
    int vecka;
    int year;
    int dag;
    QString dagnummer;
    QString veckonr;
    QString artal;
    QDateTime dt = QDateTime::currentDateTime();
    dag= QDate::currentDate().dayOfWeek();
    offertdatum=dt.toString("yyyy-MM-dd");
    textLabelOffertdatum->setText(offertdatum);    
    offertleveranstid=offertdatum;
    lineOffertLeveranstid->setText(offertleveranstid);
    /****  Beräkning av leveransvecka , Start ****/
    vecka= QDate::currentDate().weekNumber(&year);
    veckonr=QString::number(vecka,10);
    dagnummer=QString::number(dag,10);
    if (veckonr.length() < 2){
	veckonr.prepend("0");
    }
    artal=QString::number(year,10);
    radleveransvecka=artal.mid(3,1) + veckonr + dagnummer;	// ÅVVD
//    qDebug("vecka=%d, år=%d, radleveransvecka=%s _%s_",vecka,year,radleveransvecka.latin1(),veckonr.latin1());
    lineEditLeveransvecka->setText(radleveransvecka);
    /****  Beräkning av leveransvecka , Slut ****/
    
    frmAddOffert::listViewRader_format();
    frmAddOffert::getKundLista();
    listViewKund->setFocus();
//    lineEditOffertKundNr->setFocus();
    
    textLabel1_8->hide();
    pushBtnOffertKlar->hide();
}

void frmAddOffert::slotKundNr_returnPressed()
{
    long kunr;
    bool ok;
    offertkundnr=lineEditOffertKundNr->text();
    kunr=offertkundnr.toLong(&ok,10);
    if (kunr==0){						/*  eller blank, =0 */
	/* Hämta ett kundnr,FTGDATA-SKUNR(Senast använda kundnr 	*/
	/* getSenasteKundnr()					*/
	/* Fyll i kundnr 					*/
	frmAddOffert::NyKund();
    }else{
	frmAddOffert::getKundData();
	lineEditArtikelNr->setFocus();
    }    
}

void frmAddOffert::slotPickupKundnr( QListViewItem * item)
{
    char kundnummer[11]="";
//    qDebug("PickupKundnr\n");
    if(!item){
	return;
    }
     listViewKund->setCurrentItem(item);
     if(!item->key(0,TRUE)){
	 return;
     }

     strcpy(kundnummer,item->key(0,TRUE));
     offertkundnr=kundnummer;
     lineEditOffertKundNr->setText((offertkundnr));
     lineEditOffertKundNr->setFocus();
}

void frmAddOffert::slotOffertNr_returnPressed()
{
    offertnr=lineEditOffertNbr->text();
//    lineEditKundNamn->setFocus();
}

void frmAddOffert::slotKundNamn_returnPressed()
{
    offertkundnamn=lineEditKundNamn->text();
//    lineEditKundAdress->setFocus();
}


void frmAddOffert::lineEditKundAdress_returnPressed()
{
    offertkundadress=lineEditKundAdress->text();
    lineEditKundPostnr->setFocus();
}

void frmAddOffert::lineEditKundPostnr_returnPressed()
{
    offertkundpostnr=lineEditKundPostnr->text();
    lineEditKundPostAdress->setFocus();
}

void frmAddOffert::lineEditKundPostAdress_returnPressed()
{
    offertkundpostadr=lineEditKundPostAdress->text();
    lineEditKundLand->setFocus();
}

void frmAddOffert::lineEditKundLand_returnPressed()
{
    offertkundland=lineEditKundLand->text();
    lineEditKundRef->setFocus();
}

void frmAddOffert::lineEditKundRef_returPressed()
{
    offertkundref=lineEditKundRef->text();
    lineEditKundRef->setText(offertkundref);
    if ( nykundflag==TRUE){
	lineEditKundLevAdress->setFocus();
    }
}

void frmAddOffert::lineEditKundLevAdress_returnPressed()
{
    offertkundlevadress=lineEditKundLevAdress->text();
    lineEditKundLevAdress->setText(offertkundlevadress);
    if ( nykundflag==TRUE){
	lineEditKundLevPostnr->setFocus();
    }
}

void frmAddOffert::lineEditKundLevPostnr_returnPressed()
{
    offertkundlevpostnr=lineEditKundLevPostnr->text();
    lineEditKundLevPostnr->setText(offertkundlevpostnr);
    if ( nykundflag==TRUE){
	lineEditKundLevPostAdress->setFocus();
    }
}

void frmAddOffert::lineEditKundLevPostAdress_returnPressed()
{
    offertkundlevpostadr=lineEditKundLevPostAdress->text();
    lineEditKundLevPostAdress->setText(offertkundlevpostadr);
    if ( nykundflag==TRUE){
	lineEditKundLevLand->setFocus();
    }
}

void frmAddOffert::lineEditKundLevLand_return_pressed()
{
    offertkundlevland=lineEditKundLevLand->text();
    lineEditKundLevLand->setText(offertkundlevland);
    if ( nykundflag==TRUE){
	lineEditLevplats->setFocus();
    }
}

void frmAddOffert::lineEditLevplats_returnPressed()
{
    offertlevplats=lineEditLevplats->text();
    frmAddOffert::getStdLevplats( offertlevplats );
    if ( nykundflag==TRUE){
	lineEditLevvillkor->setFocus();
    }
}

void frmAddOffert::lineEditLevvillkor_returnPressed()
{
    offertlevvillkor=lineEditLevvillkor->text();
    if ( nykundflag==TRUE){
	lineEditBetvilk->setFocus();
    }
}

void frmAddOffert::lineEditBetvilk_returnPressed()
{
    offertbetvillkor=lineEditBetvilk->text();
    if ( nykundflag==TRUE){
	lineEditValuta->setFocus();
    }    
}

void frmAddOffert::lineEditValuta_returnPressed()
{
    offertvaluta=lineEditValuta->text();
    if ( nykundflag==TRUE){
	lineEditMomskod->setFocus();
    }
}	

void frmAddOffert::lineEditMomskod_returnPressed()
{
    offertmoms=lineEditMomskod->text();
    if ( nykundflag==TRUE){
	QMessageBox mb( "ADDOFFW",
			"Vill du spara kunden som en ny kund?",
			QMessageBox::NoIcon,
			QMessageBox::Yes | QMessageBox::Default,
			QMessageBox::No,0,0);
	
	mb.setButtonText( QMessageBox::Yes, "Ja" );
	mb.setButtonText( QMessageBox::No, "Nej" );

	if ( mb.exec() == QMessageBox::No ){
//	    qDebug("Nej-svar");
	    nykundflag=FALSE;
	}
	if ( mb.exec() == QMessageBox::Yes ){
//	    qDebug("Ja-svar");
	    createNyKund();
	}
	lineEditSeljare->setFocus();	
    }    
}

void frmAddOffert::lineEditSeljare_returnPressed()
{
    seljare=lineEditSeljare->text();
}

void frmAddOffert::lineOffertLeveranstid_returnPressed()
{
    int vecka;
    int year;
   int dag;
    QString dagnummer;
    QString veckonr;
    QString artal;
    
    offertleveranstid=lineOffertLeveranstid->text();	/* ÅÅÅÅ-MM-DD*/
        /****  Beräkning av leveransvecka , Start ****/
    int tmp1=offertleveranstid.mid(0,4).toInt();		/* Årtal, ÅÅÅÅ*/
    int tmp2=offertleveranstid.mid(5,2).toInt();		/* Månad, MM */
    int tmp3=offertleveranstid.mid(8,2).toInt();		/* Dag, DD */
    vecka= QDate(tmp1,tmp2,tmp3).weekNumber(&year);
    dag= QDate(tmp1,tmp2,tmp3).dayOfWeek();
    qDebug("vecka=%d",vecka);
    veckonr=QString::number(vecka,10);
    dagnummer=QString::number(dag,10);
    if (veckonr.length() < 2){
	veckonr.prepend("0");
    }
    artal=QString::number(year,10);
    radleveransvecka=artal.mid(3,1) + veckonr + dagnummer;	// ÅVVD

//    radleveransvecka
    lineEditLeveransvecka->setText(radleveransvecka);			/* ÅVVD */
}

void frmAddOffert::lineEditGodsmarke_returnPressed()
{
    godsmarke=lineEditGodsmarke->text();
    if ( nykundflag==TRUE){
	/*  Visa godkännandeknapp/Avbryt-knapp */
	/* funktion för att spara kunddata samt uppdatera kundnr, FTGDATA-SKUNR */
	
    }
}

/**************************************************************************/
/*		Offertradrad	Start				*/
/**************************************************************************/

void frmAddOffert::lineEditArtikelNr_returnPressed()
{
    offertartikelnr=lineEditArtikelNr->text();
    if (offertartikelnr!=""){
	frmAddOffert::getArtikeldata();
   }
}

void frmAddOffert::lineEditBenamn_returnPressed()
{
    offertbenamn=lineEditBenamn->text();
  //  lineEditLeveransvecka->setFocus();
}

void frmAddOffert::lineEditLeveransvecka_returnPressed()
{
    radleveransvecka=lineEditLeveransvecka->text();
  //  lineEditAntal->setFocus();
}

void frmAddOffert::lineEditAntal_returnPressed()
{
    int i;
    double antal;
    offertantal=lineEditAntal->text();
    antal=offertantal.toDouble();
    if ( antal==0){
	QMessageBox::warning( this, "ADDOFFW",
			      "Antal måste anges!\n" );
	lineEditAntal->clear();
	lineEditAntal->setFocus();
    }else{
	i = -1;
	i =offertantal.find( QRegExp(","), 0 );
	if (i != -1){
	    offertantal.replace( QChar(','), "." );
	    lineEditAntal->setText(offertantal);
	}
//	lineEditAPris->setFocus();
    }
}

void frmAddOffert::lineEditAPris_returnPressed()
{
    int i;
    double pris,antal,moms,summa;
    QString radmomsbelopp;
    offertradpris=lineEditAPris->text();
//    qDebug("offertradpris=%s  radmoms=%s",offertradpris.latin1(),radmoms.latin1());
    if (radmoms<1){
	radmoms=offertmoms;
    }
//    qDebug("offertmoms=%s  radmoms=%s",offertmoms.latin1(),radmoms.latin1());    
    i = -1;
    i =offertradpris.find( QRegExp(","), 0 );
    if (i != -1){
	offertradpris.replace( QChar(','), "." );	// Ersätt decimalkomma med decimalpunkt (komma -> punkt)
	lineEditAPris->setText(offertradpris);
    }
    pris=offertradpris.toDouble();
    antal=offertantal.toDouble();
    moms=radmoms.toDouble();
    summa=pris*antal;
    moms=summa*moms/100;
    radmomsbelopp=radmomsbelopp.setNum(moms,'f',2);
    lineEditRadMoms->setText(radmomsbelopp);
    summa=summa+moms;
    radbelopp=radbelopp.setNum(summa,'f',2);
    lineEditRadSumma->setText(radbelopp);
  //  pushBtnOKRad->setFocus();
}

void frmAddOffert::pushBtnOKRad_clicked()
{
    double summa ,belopp;
//   , moms, momsbelopp;
    QString radmomsbelopp;
    QListViewItem * item;
    int i;
    
    /*	Är artikelnummer ifyllt? 	*/
    if (offertartikelnr==""){
	if (! avbryt){
	    QMessageBox::warning( this, "ADDOFFW",
		      "Artikelnummer måste anges!\n" );
	    lineEditArtikelNr->setFocus();
	}
    }
    
    
    radmomsbelopp=lineEditRadMoms->text();    
    item = new QListViewItem(listViewRader,offertradnr,offertartikelnr,offertbenamn,radleveransvecka,offertantal,offertradpris,radbelopp,radmomsbelopp);
//    item->setText(8,offertbenamn);
    if (radnrflag == FALSE){
	i = offertradnr.toInt();
	i = i+10;
	offertradnr=QString::number(i,10);
	if (offertradnr.length() <3){
	    offertradnr="0"+offertradnr;
	}
    }else{
	offertradnr=oldradnr;
	radnrflag=FALSE;
    }
    
    /* Beräkna offertsumma	*/
    summa=offertsumma.toDouble();
    belopp=radbelopp.toDouble();
    summa=summa+belopp;
    offertsumma=offertsumma.setNum(summa,'f',2);
    lineEditOffertSumma->setText(offertsumma);
    
    /*  Beräkna momsen hittills för offertn	*/  
    frmAddOffert::CalculateMoms();
    
    /* Nästa offertrad 	*/
    lineEditRadnr->setText(offertradnr);
    lineEditArtikelNr->clear();
    lineEditBenamn->clear();
    lineEditAntal->clear();
    lineEditAPris->clear();
    lineEditRadMoms->clear();
    lineEditRadSumma->clear();
    offertartikelnr="";
    offertbenamn="";
    offertantal="";
    offertradpris="";
    radbelopp="";
    lineEditArtikelNr->setFocus();
}

void frmAddOffert::pushBtnRadNej_clicked()
{
    lineEditRadnr->setText(offertradnr);
    lineEditArtikelNr->clear();
    lineEditBenamn->clear();
    lineEditAntal->clear();
    lineEditAPris->clear();
    lineEditRadSumma->clear();
    offertartikelnr="";
    offertbenamn="";
    offertantal="";
    offertradpris="";
    radbelopp="";
    lineEditArtikelNr->setFocus();
}

void frmAddOffert::listViewRader_clicked( QListViewItem * )
{
    double radsumma ,tmpoffertsumma;
    radnrflag=TRUE;
    oldradnr=offertradnr;
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
    QString temp7=item->text(7);	// moms för raden
    //    qDebug("temp=%s, %s, %s, %s, %s, %s",temp0.latin1(),temp1.latin1(),temp2.latin1(),temp3.latin1(),temp4.latin1(),temp5.latin1());
    // --------------------------------------------------------------
    lineEditRadnr->setText(temp0);
    offertradnr=temp0;
    lineEditArtikelNr->setText(temp1);
    lineEditBenamn->setText(temp2);
    lineEditLeveransvecka->setText(temp3);
    lineEditAntal->setText(temp4);
    lineEditAPris->setText(temp5);
    lineEditRadSumma->setText(temp6);    
    lineEditRadMoms->setText(temp7);
    radsumma=temp5.toDouble();
    tmpoffertsumma=offertsumma.toDouble();
    tmpoffertsumma=tmpoffertsumma-radsumma;
    offertsumma=offertsumma.setNum(tmpoffertsumma,'f',2);
    lineEditOffertSumma->setText(offertsumma);
    lineEditArtikelNr->setFocus();
    delete listViewRader->currentItem();
}



/************************************************************************/
/*		Offertradrad	Slut				*/
/************************************************************************/

void frmAddOffert::lineEditOffertFrakt_returnPressed()
{
    double summa ,totalsumma,fraktsumma,radmomssumma,fraktmoms,moms,momsbelopp,tmp;
    totalsumma=0;
    QString radmomstotal;
    QString tmpfrakt;
    radmomstotal = lineEditOffertMomsKr->text();
    radmomssumma = radmomstotal.toDouble();
    
       /*	Fraktkostnad	   */
    summa = offertsumma.toDouble();
    fraktbelopp = lineEditOffertFrakt->text();
    tmp=fraktbelopp.toDouble();
    fraktbelopp=fraktbelopp.setNum(tmp,'f',2);	/*  Editering till heltal och 2 decimaler */
    lineEditOffertFrakt->setText(fraktbelopp);
    fraktsumma = fraktbelopp.toDouble(); 
    
//    lineEditOffertFrakt->setDisabled(TRUE);		/* 2006-02-14 */
    lineEditOffertFrakt->setPaletteForegroundColor(black);
    
       /*  Beräkna fraktmomsen	*/      
    moms = offertmoms.toDouble(); 			/* Från lineEditMomskod, procentsats */ 
    moms = moms/100;				/*  i flyttal, t ex 0.06 */
    fraktmoms = fraktsumma * moms;
    fraktmomskr=fraktmomskr.setNum(fraktmoms,'f',2);
    lineEditFraktmoms->setText(fraktmomskr);
    
    momsbelopp = fraktmoms + radmomssumma;
    momssumma = momssumma.setNum(momsbelopp,'f',2);
    lineEditOffertMomsKr->setText(momssumma);
    
       /* Offert total 	*/
    totalsumma=summa+fraktsumma+fraktmoms+momsbelopp;
    offertsumma=offertsumma.setNum(totalsumma,'f',2);
    lineEditOffertTotal->setText(offertsumma);
    pushBtnOffertKlar->setFocus();
}

/*
void frmAddOffert::pushBtnOffertKlar_clicked()
{
//    lineEditOffertFrakt->setEnabled("FALSE");
    pushButtonOK->setFocus();	 2006-02-14, 17 		 Spara offertn. 
}
*/
    
void frmAddOffert::slotBtnOK_clicked()
{
    frmAddOffert::CreateOffertHuvud();
// Och lägg upp offerthuvud i ORDERREG
}

void frmAddOffert::slotAddOffert()
{
/************************************************************************/
/*	Uppdatera databasen						*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);
	    
	if (offertmomskod == ""){
	    offertmomskod = "1";
	 }
	if (offertbetvillkor == ""){
	    offertbetvillkor ="1";
	}
	
//	qDebug("offertnr=%s",offertnr.latin1());
//	qDebug("offertnamn=%s",offertnamn.latin1());
	    
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "OFFADD");	// OLFIX funktion		Offerthuvud till ORDERREG
	process->addArgument(offerthuvuddata);
	
	frmAddOffert::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmAddOffert::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
                frmAddOffert::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );
	    
	if (offerthuvuddata == "" ){
    	    QMessageBox::warning( this, "ADDOFFW",
                      "Data saknas till offerthuvud! \n" );
	}else {
	    if ( !process->start() ) {
		// error handling
		QMessageBox::warning( this, "ADDOFFW",
                            "Kan inte starta STYRMAN/OFFADD! \n" );
	    }
	}
}

void frmAddOffert::slotDataOnStdout()
{
     while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }   
}

void frmAddOffert::slotDataOnStderr()
{
      while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }  
}

void frmAddOffert::slotEndOfProcess()
{
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
//   qDebug("Error:%s",errorrad.latin1());
//   qDebug("Inrad:%s",inrad.latin1());
     if (i != -1) {
	QMessageBox::critical( this, "ADDOFFW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
	return;
     }else{
	 i = -1;
	 i = inrad.find( QRegExp("OK:"), 0 );
	 if (i != -1) {
//	     QMessageBox::information( this, "ADDOFFW",
//		"Uppdatering OK!\n"+errorrad
//		);
     	     lineEditOffertKundNr->clear();
	     lineEditOffertNbr->clear();
	     lineEditKundNamn->clear();
	     lineEditKundAdress->clear();
	     lineEditKundPostnr->clear();
	     lineEditKundPostAdress->clear();
	     lineEditKundLand->clear();
/*	      ----------------				*/	     
	     lineEditKundRef->clear();
	     lineEditKundLevAdress->clear();
	     lineEditKundLevPostnr->clear();
	     lineEditKundLevPostAdress->clear();
	     lineEditKundLevLand->clear();
	     lineEditLevplats->clear();
	     lineEditLevvillkor->clear();
	     lineEditBetvilk->clear();
	     lineEditValuta->clear();
	     lineEditMomskod->clear();
/*	      ----------------				*/
	     lineEditRadnr->clear();
	     lineEditArtikelNr->clear();
	     lineEditBenamn->clear();
	     lineEditAntal->clear();
	     lineEditAPris->clear();
	     lineEditRadMoms->clear();
	     lineEditRadSumma->clear();
/*	      ----------------				*/
//	     listViewRader->clear();
/*	      ----------------				*/	     
	     lineEditOffertSumma->clear();
	     lineEditOffertFrakt->setEnabled("TRUE");
	     lineEditOffertFrakt->clear();
	     lineEditFraktmoms->clear();
	     lineEditOffertMomsKr->clear();
	     lineEditOffertTotal->clear();
/*	      ----------------				*/	     
	     lineEditOffertNbr->setFocus();
	     offertmomskod="1";

	     inrad="";
	     i = -1;
	     frmAddOffert::UpdateKundOffertNr();	/* Uppdatera offertnummer i FTGDATA, posttyp KORNR=senast använda kundoffertnr*/
	 } 
     }
}

void frmAddOffert::getKundLista()
{
	const char *userp = getenv("USER");
            QString usr(userp);
	 inrad="";

	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "KULST");	// OLFIX funktion

	frmAddOffert::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmAddOffert::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmAddOffert::connect( process, SIGNAL(processExited() ),this, SLOT(slotKundListaEndOfProcess() ) );

	if ( !process->start() ) {
                // error handling
	    fprintf(stderr,"Problem starta STYRMAN/KULST!\n");
	    QMessageBox::warning( this, "Start av KULST ",
                            "Kan inte starta STYRMAN/KULST!\n"
                            );
        }
}

void frmAddOffert::slotKundListaEndOfProcess()
{
    QListViewItem* item;
    int i;
    listViewKund->setSorting(1,TRUE);
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "ADDOFFW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
     }

    i = inrad.find( QRegExp("OK: NR_0_"), 0 );
         if (i != -1) {
	QMessageBox::information( this, "ADORDW",
		"Kundregistret innehåller inga poster!\n"
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
    char kundnr[11]="";
    char namn[61]="";

    tmppek=tmp;
    qstrcpy(tmp,inrad);
    pos1=strstr(tmp,"OK: NR_");	// 7 tecken långt
    pos2=strstr(tmp,"_:");
    i=pos2-pos1;
    m=i+2;		// startposition för första kundnr.
    
//    qDebug("i=%d  m=%d",i,m);
    
    k=0;
    for (j=7;j<i;j++){	// j = första positionen för antal poster,(OK: NR_4_:4377_:Kund AB_:4379_:Småkund AB_:4378_:Storkund AB_:4376_:Test AB_:)
	antrad[k]=tmp[j];
	k++;
    };
    i=atoi(antrad);		// i = antal poster
    
//    qDebug("antrad=%s",antrad);
    
    for (k = 1;k <= i; k++){	// gå igenom alla raderna / posterna
	l=0;
	for(j = m; j < sizeof(kundnr) + m; j++){
	    if(tmp[j] != *("_")){
		kundnr[l]=tmp[j];
		l++;
	    }else{
		kundnr[l] = *("\0");
		j=sizeof(kundnr) + m;
	    }
	}
//	qDebug("%s  ",kundnr);
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
	item = new QListViewItem(listViewKund,kundnr,namn);
// 	 rensa kundnr och namn
  	for (l=0;l<sizeof(kundnr);l++)
		kundnr[l]=*("\0");
	for (l=0;l<sizeof(namn);l++)
		namn[l]=*("\0");
//	 rensa listrad 
	listrad.remove(0,80);
    }
    	frmAddOffert::getOffertnr();
}


void frmAddOffert::getKundData()
{
	const char *userp = getenv("USER");
            QString usr(userp);


	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "KUDSP");	// OLFIX funktion
	process->addArgument(offertkundnr);

	frmAddOffert::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmAddOffert::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmAddOffert::connect( process, SIGNAL(processExited() ),this, SLOT(slotKundDataEndOfProcess() ) );

	if ( !process->start() ) {
                // error handling
	    fprintf(stderr,"Problem starta STYRMAN/KUDSP!\n");
	    QMessageBox::warning( this, "Start av KUDSP ",
                            "Kan inte starta STYRMAN/KUDSP!\n"
                            );
        }
}


void frmAddOffert::slotKundDataEndOfProcess()
{
    int i,m;

    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
 //   qDebug("Error:",errorrad);
         if (i != -1) {
	QMessageBox::critical( this, "ADDOFFW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
     }
     i = -1;

     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
/*	 int i1 = inrad.find( QRegExp("01:"), 0 );
	 int i2 = inrad.find( QRegExp("02:"), 0 );	*/
	 int i3 = inrad.find( QRegExp("03:"), 0 );
	 int i4 = inrad.find( QRegExp("04:"), 0 );
	 int i5 = inrad.find( QRegExp("05:"), 0 );
	 int i6 = inrad.find( QRegExp("06:"), 0 );
	 int i7 = inrad.find( QRegExp("07:"), 0 );
	 int i8 = inrad.find( QRegExp("08:"), 0 );
/*	 int i9 = inrad.find( QRegExp("09:"), 0 );
	 int i10 = inrad.find( QRegExp("10:"), 0 );
*/	 int i11 = inrad.find( QRegExp("11:"), 0 );
	 int i12 = inrad.find( QRegExp("12:"), 0 );
/*	 int i13 = inrad.find( QRegExp("13:"), 0 );	
	 int i14 = inrad.find( QRegExp("14:"), 0 );
	 int i15 = inrad.find( QRegExp("15:"), 0 );	*/
	 int i16 = inrad.find( QRegExp("16:"), 0 );
	 int i17 = inrad.find( QRegExp("17:"), 0 );
	 int i18 = inrad.find( QRegExp("18:"), 0 );
	 int i19 = inrad.find( QRegExp("19:"), 0 );
/*	 int i20 = inrad.find( QRegExp("20:"), 0 );
	 int i21 = inrad.find( QRegExp("21:"), 0 );	*/
	 int i22 = inrad.find( QRegExp("22:"), 0 );	
	 int i23 = inrad.find( QRegExp("23:"), 0 );
/*	 int i24 = inrad.find( QRegExp("24:"), 0 );
	 int i25 = inrad.find( QRegExp("25:"), 0 );
	 int i26 = inrad.find( QRegExp("26:"), 0 );
	 int i27 = inrad.find( QRegExp("27:"), 0 );
	 int i28 = inrad.find( QRegExp("28:"), 0 );
	 int i29 = inrad.find( QRegExp("29:"), 0 );
	 int i30 = inrad.find( QRegExp("30:"), 0 );
	 int i31 = inrad.find( QRegExp("31:"), 0 );
	 int i32 = inrad.find( QRegExp("32:"), 0 );
	 int i33 = inrad.find( QRegExp("33:"), 0 );	*/
	 int i34 = inrad.find( QRegExp("34:"), 0 );
	 int i35 = inrad.find( QRegExp("35:"), 0 );
/*	 int i36 = inrad.find( QRegExp("36:"), 0 );
	 int i37 = inrad.find( QRegExp("37:"), 0 );
	 int i38 = inrad.find( QRegExp("38:"), 0 );
	 int i39 = inrad.find( QRegExp("39:"), 0 );
	 int i40 = inrad.find( QRegExp("40:"), 0 );
	 int i41 = inrad.find( QRegExp("41:"), 0 );	*/
	 int i42 = inrad.find( QRegExp("42:"), 0 );	/* 20060203 prislista.*/
	 int i43 = inrad.find( QRegExp("END:"), 0 );	/* 20060201 prislista.*/
	 
/*
	 m=i2-i1;
	 if (i1 != -1){
	     kundid=inrad.mid(i1+3,m-4);
	     lineEditKundNr->setText(kundid);
	 }

 	 m=i3-i2;
	 if (i2 != -1){
//	     kundorgnr=inrad.mid(i2+2,m-4);
	 }
*/
	 m=i4-i3;
	 if (i3 != -1){
	     offertkundnamn=inrad.mid(i3+3,m-4);
	     lineEditKundNamn->setText(offertkundnamn);
	 }

	 m=i5-i4;
	 if (i4 != -1){
	     offertkundadress=inrad.mid(i4+3,m-4);
	     lineEditKundAdress->setText(offertkundadress);
	 }

 	 m=i6-i5;
	 if (i5 != -1){
	     offertkundpostnr=inrad.mid(i5+3,m-4);
	     lineEditKundPostnr->setText(offertkundpostnr);
	 }

	 m=i7-i6;
	 if (i6 != -1){
	     offertkundpostadr=inrad.mid(i6+3,m-4);
	     lineEditKundPostAdress->setText(offertkundpostadr);
	 }

 	 m=i8-i7;
	 if (i7 != -1){
	     offertkundland=inrad.mid(i7+3,m-4);
	     lineEditKundLand->setText(offertkundland);
	 }
/*
 	 m=i9-i8;
	 if (i8 != -1){
	     tfnnr=inrad.mid(i8+3,m-4);
	     lineEditKundTftnNr->setText(tfnnr);
	 }

	 m=i10-i9;
	 if (i9 != -1){
	     email=inrad.mid(i9+3,m-4);
	     lineEditKundEmail->setText(email);
	 }

 	 m=i11-i10;
	 if (i10 != -1){
	     faxnr=inrad.mid(i10+3,m-4);
	     lineEditKundFaxNr->setText(faxnr);
	 }
*/
 	 m=i12-i11;
	 if (i11 != -1){
	     offertkundref=inrad.mid(i11+3,m-4);
	     lineEditKundRef->setText(offertkundref);
	 }
/*
 	 m=i13-i12;
	 if (i12 != -1){
	     erreftfnnr=inrad.mid(i12+3,m-4);
	     lineEditErRefTfnNr->setText(erreftfnnr);
	 }

 	 m=i14-i13;
	 if (i13 != -1){
	     errefemail=inrad.mid(i13+3,m-4);
	     lineEditKundErRefEmail->setText(errefemail);
	 }

 	 m=i15-i14;
	 if (i14 != -1){
	     seljare=inrad.mid(i14+3,m-4);							Säljare
	     lineEditSeljare->setText(seljare);
	 }

	 m=i16-i15;
	 if (i15 != -1){
	    fritext=inrad.mid(i15+3,m-4);
	    lineEditFriText->setText(fritext);
	 }
*/
 	 m=i17-i16;
	 if (i16 != -1){
	     offertvaluta=inrad.mid(i16+3,m-5);
	     lineEditValuta->setText(offertvaluta);
	 }

	 m=i18-i17;
	 if (i17 != -1){
	     offertbetvillkor=inrad.mid(i17+3,m-4);
	     lineEditBetvilk->setText(offertbetvillkor);
	 }

	 m=i19-i18;
	 if (i18 != -1){
	     offertlevvillkor=inrad.mid(i18+3,m-4);
	     lineEditLevvillkor->setText(offertlevvillkor);
	 }
/*
	 m=i20-i19;
	 if (i19 != -1){
	     levsett=inrad.mid(i19+3,m-4);
	     lineEditKundLevsett->setText(levsett);
	 }

	 m=i21-i20;
	 if (i20 != -1){
	     distrikt=inrad.mid(i20+3,m-4);
	     lineEditKundDistrikt->setText(distrikt);
	 }

	 m=i22-i21;
	 if (i21 != -1){
	    kundkat=inrad.mid(i21+3,m-4);
	    lineEditKundKategori ->setText(kundkat);
	 }
*/
	 m=i23-i22;
	 if (i22 != -1){
	    offertlevplats=inrad.mid(i22+3,m-4);
	    lineEditLevplats ->setText(offertlevplats);
	 }
/*
	 m=i24-i23;
	 if (i23 != -1){
	     offerterk=inrad.mid(i23+3,m-4);
	    lineEditOfferterk ->setText(offerterk);
	 }


	 m=i25-i24;
	 if (i24 != -1){
	     plocklista=inrad.mid(i24+3,m-4);
	    lineEditPlocklista ->setText(plocklista);
	 }

	 m=i26-i25;
	 if (i25 != -1){
	     foljesedel=inrad.mid(i25+3,m-4);
	    lineEditFoljesedel->setText(foljesedel);
	 }

	 m=i27-i26;
	 if (i26 != -1){
	     kravbrev=inrad.mid(i26+3,m-4);
	    lineEditKravbrev ->setText(kravbrev);
	 }

	 m=i28-i27;
	 if (i27 != -1){
	     sprakkod=inrad.mid(i27+3,m-4);
	    lineEditSprakkod->setText(sprakkod);
	 }

 	 m=i29-i28;
	 if (i28 != -1){
	     expavg=inrad.mid(i28+3,m-4);
	    lineEditExpAvgift->setText(expavg);
	 }

	 m=i30-i29;
	 if (i29 != -1){
	     fraktavg=inrad.mid(i29+3,m-4);
	    lineEditFraktAvgift->setText(fraktavg);
	 }

	 m=i31-i30;
	 if (i30 != -1){
	     kreditlimit=inrad.mid(i30+3,m-4);
	    lineEditKreditlimit->setText(kreditlimit);
	 }

	 m=i32-i31;
	 if (i31 != -1){
	     kreditdagar=inrad.mid(i31+3,m-4);
	    lineEditKreditDagar->setText(kreditdagar);
	 }

	 m=i33-i32;
	 if (i32 != -1){
	     kreditkod=inrad.mid(i32+3,m-4);
	    lineEditKreditKod->setText(kreditkod);
	 }

	 m=i34-i33;
	 if (i33 != -1){
	     exportkod=inrad.mid(i33+3,m-4);
	    lineEditExportkod->setText(exportkod);
	 }
*/
 	 m=i35-i34;
	 if (i34 != -1){
	    offertmomskod=inrad.mid(i34+3,m-4);		// = Skattekod
//	    lineEditMomskod->setText(offertmomskod);
	 }
/*
 	 m=i36-i35;
	 if (i35 != -1){
	    rabattkod=inrad.mid(i35+3,m-4);
	    lineEditRabattKod->setText(rabattkod);
	 }

	 m=i37-i36;
	 if (i36 != -1){
	    drojmalsrenta=inrad.mid(i36+3,m-4);
	    lineEditDrojRenta->setText(drojmalsrenta);
	 }

	 m=i38-i37;
	 if (i37 != -1){
	     drofmalsfakt=inrad.mid(i37+3,m-4);
	    lineEditDrojFaktura->setText(drofmalsfakt);
	 }

	 m=i39-i38;
	 if (i38 != -1){
	    samfaktura=inrad.mid(i38+3,m-4);
	    lineEditSamFaktura->setText(samfaktura);
	 }

	 m=i40-i39;
	 if (i39 != -1){
	    kravdatum=inrad.mid(i39+3,m-4);
	    lineEditKravDatum->setText(kravdatum);
	 }

	 m=i41-i40;
	 if (i40 != -1){
	    skuld=inrad.mid(i40+3,m-4);
	    lineEditSkuld->setText(skuld);
	 }

	 m=i42-i41;
	 if (i41 != -1){
	    offertstock=inrad.mid(i41+3,m-4);
	    lineEditOffertstock->setText(offertstock);
	 }
*/
	 m=i43-i42;				/* 20060203 */
	 if (i42 != -1){
	    prislista=inrad.mid(i42+3,m-4);
//	    qDebug("prislista=|%s|",prislista.latin1());
	    lineEditKundPrislista->setText(prislista);
	 }
	 
	 inrad="";
	errorrad="";
	inrad="";
	i = -1;
     }
     frmAddOffert::getStdLevplats( offertlevplats );
}

void frmAddOffert::getOffertnr()
{
	const char *userp = getenv("USER");
            QString usr(userp);


	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "FTGDSP");	// OLFIX funktion
	process->addArgument("KORNR");	// Senas använda kundoffertnummer

	frmAddOffert::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmAddOffert::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmAddOffert::connect( process, SIGNAL(processExited() ),this, SLOT(slotgetOffertnrEndOfProcess() ) );

	if ( !process->start() ) {
                // error handling
	    QMessageBox::warning( this, "Start av FTGDSP ",
                            "Kan inte starta STYRMAN/FTGDSP!\n"
                            );
        }
}

void frmAddOffert::slotgetOffertnrEndOfProcess()
{
    int i,m;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "ADDOFFW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
     }
     i = -1;
     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	 int i1 = inrad.find( QRegExp("1:"), 0 );
	 int i2 = inrad.find( QRegExp("2:"), 0 );	
	 int i3 = inrad.length();
	 m=i2-i1;
	 m=i3-i2;
	 if (i2 != -1){
	     offertnr=inrad.mid(i2+2,m-4);
//	     qDebug("m=%d  offertnr=%s  i3=%d",m,offertnr.latin1(), i3);
	 }
	 bool ok;
	 int ornr = offertnr.toInt( &ok, 10 ); 
	 ornr++;
	 offertnr = QString::number( ornr, 10 );
	 lineEditOffertNbr->setText(offertnr);
	inrad="";
	errorrad="";
	inrad="";
	i = -1;
    }
   frmAddOffert::getMoms("MOMS1","H");		/* H = Offerthuvud */
}

void frmAddOffert::getMoms(QString momskod,QString typ)
{
	const char *userp = getenv("USER");
                QString usr(userp);
	inrad="";   
	offertdel=typ;

	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "FTGDSP");	// OLFIX funktion
	process->addArgument(momskod);	// Senas använda kundoffertnummer

	frmAddOffert::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmAddOffert::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmAddOffert::connect( process, SIGNAL(processExited() ),this, SLOT(slotgetMomsEndOfProcess() ) );

	if ( !process->start() ) {
                // error handling
	    QMessageBox::warning( this, "Start av FTGDSP ",
                            "Kan inte starta STYRMAN/FTGDSP!\n"
                            );
        }
}

void frmAddOffert::slotgetMomsEndOfProcess()
{
//    qDebug("slotgetMomsEndOfProcess::inrad=%s",inrad.latin1());
    int i,m;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "ADDOFFW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
     }
     i = -1;
     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	 int i1 = inrad.find( QRegExp("1:MOMS"), 0 );
	 int i2 = inrad.find( QRegExp("2:"), 0 );	
	 int i3 = inrad.length();
	 m=i2-i1;
	 m=i3-i2;
	 if (i2 != -1){
	     if (offertdel == "H"){
		 offertmoms=inrad.mid(i2+2,m-4);
//		 qDebug("m=%d  moms=%s  i3=%d",m,offertmoms.latin1(), i3);
		 lineEditMomskod->setText(offertmoms);
	     }else{
		 radmoms = inrad.mid(i2+2,m-4);
//		 qDebug("slotgetMomsEndOfProcess::radmoms=%s",radmoms.latin1());
		 lineEditRadMoms->setText(radmoms);
		 getPrislista();
		 return;
	     }
	 }
	inrad="";
	errorrad="";
	inrad="";
	i = -1;
    }
     frmAddOffert::getSeljare();
}

void frmAddOffert::getSeljare()
{
//    qDebug("getSeljare");
    	const char *userp = getenv("USER");
            QString usr(userp);
	 inrad4="";   

	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "USERDSP");	// OLFIX funktion
	process->addArgument(usr);	// Senas använda kundoffertnummer

	frmAddOffert::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotgetUDataOnStdout() ) );
	frmAddOffert::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotgetUDataOnStderr() ) );
	frmAddOffert::connect( process, SIGNAL(processExited() ),this, SLOT(slotgetUserEndOfProcess() ) );

	if ( !process->start() ) {
                // error handling
	    QMessageBox::warning( this, "Start av USERDSP ",
                            "Kan inte starta STYRMAN/USERDSP!\n"
                            );
        }
}

void frmAddOffert::slotgetUserEndOfProcess()
{
//    qDebug("slotgetUserEndOfProcess::Start");
    int i,m;
    i = -1;
    i = errorrad4.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "ADDOFFW",
		"ERROR!\n"+errorrad4
	);
	errorrad4="";
	i = -1;
     }
     i = -1;
//     i = inrad4.find( QRegExp("OK:"), 0 );
  //   if (i != -1) {
	 int i1 = inrad4.find( QRegExp("1:"), 0 );
	 int i2 = inrad4.find( QRegExp("2:"), 0 );	
	 int i3 = inrad4.find( QRegExp("3:"), 0 );
	 m=i2-i1;
	 m=i3-i2;
	 if (i2 != -1){
	     seljare=inrad4.mid(i2+2,m-4);
//	   qDebug("seljare=%s",seljare.latin1());
		 lineEditSeljare->setText(seljare);
	     }
//     }
     inrad4="";
     errorrad4="";
     i = -1;
//     qDebug("slotgetUserEndOfProcess::Slut");
}

void frmAddOffert::slotgetUDataOnStdout()
{
     while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad4.append(line);
	inrad4.append("\n");
    }   
}

void frmAddOffert::slotgetUDataOnStderr()
{
      while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad4.append(line);
	errorrad4.append("\n");
    }  
}

void frmAddOffert::listViewRader_format()
{
    listViewRader->setColumnWidth(0,35);		// Radnr
    listViewRader->setColumnWidth(1,180);		// Artikelnr
    listViewRader->setColumnWidth(2,295);		// Benämning
    listViewRader->setColumnWidth(3,60);		// Leveransvecka
    listViewRader->setColumnWidth(4,55);		// Antal
    listViewRader->setColumnWidth(5,55);		// Pris
    listViewRader->setColumnWidth(6,86);		// Summa
    listViewRader->setColumnWidth(7,70);		// Moms
}

void frmAddOffert::getArtikeldata()
{
    const char *userp = getenv("USER");
    QString usr(userp);

    inradArtikel="";
    errorradArtikel="";
    processartikel = new QProcess();
    processartikel->addArgument("./STYRMAN");		// OLFIX styrprogram
    processartikel->addArgument(usr);			// userid
    processartikel->addArgument( "ARDSP");		// OLFIX funktion
    processartikel->addArgument(offertartikelnr);
//    qDebug("getArtikeldata::artikelnr=%s",offertartikelnr.latin1());
    frmAddOffert::connect( processartikel, SIGNAL(readyReadStdout() ),this, SLOT(slotArdataDataOnStdout() ) );
    frmAddOffert::connect( processartikel, SIGNAL(readyReadStderr() ),this, SLOT(slotArdataDataOnStderr() ) );
    frmAddOffert::connect( processartikel, SIGNAL(processExited() ),this, SLOT(slotArdataEndOfProcess() ) );

    if ( !processartikel->start() ) {
	// error handling
//	fprintf(stderr,"Problem starta STYRMAN/ARDSP!\n");
	QMessageBox::warning( this, "Start av ARDSP",
			      "Kan inte starta STYRMAN/ARDSP!\n"
			      );
    }
}

void frmAddOffert::slotArdataDataOnStdout(){
         while (processartikel->canReadLineStdout() ) {
	QString line = processartikel->readStdout();
	inradArtikel.append(line);
	inradArtikel.append("\n");
    }   
//	 qDebug("ArdataDataOnStdout::inradArtikel=%s",inradArtikel.latin1());	 
}

void frmAddOffert::slotArdataDataOnStderr(){
          while (processartikel->canReadLineStderr() ) {
	QString line = processartikel->readStderr();
	errorradArtikel.append(line);
	errorradArtikel.append("\n");
    }  
}
		
void frmAddOffert::slotArdataEndOfProcess()
{
    int i,m;

    i = -1;
    i = errorradArtikel.find( QRegExp("Error:"), 0 );
//    qDebug("Error:  ArdataEndOfProcess::  %s",errorradArtikel.latin1());
//    qDebug("ArdataEndofProsess::inradArtikel=%s",inradArtikel.latin1());
    
    if (i != -1) {
	QMessageBox::critical( this, "ADDOFFW",
			       "ERROR!\n"+errorradArtikel
			       );
	errorradArtikel="";
	i = -1;
	offertartikelnr="";
	lineEditArtikelNr->clear();
	lineEditArtikelNr->setFocus();
    }else{
	i = -1;
	i = inradArtikel.find( QRegExp("OK:"), 0 );
	if (i != -1) {
	    //	    int i1 = inrad.find( QRegExp("01:"), 0 );		//	artikelnr
	    int i2 = inradArtikel.find( QRegExp("02:"), 0 );		//	benämning 1
	    int i3 = inradArtikel.find( QRegExp("03:"), 0 );		//	benämning 2
	    //	    int i4 = inrad.find( QRegExp("04:"), 0 );		//	enhet
    	    int i5 = inradArtikel.find( QRegExp("05:"), 0 );		//	försäljningspris
	    int i6 = inradArtikel.find( QRegExp("06:"), 0 );		//	ledtid
	    int i7 = inradArtikel.find( QRegExp("07:"), 0 );		//	produktklass
    	    int i8 = inradArtikel.find( QRegExp("08:"), 0 );		//	prodtkonto
//	    int i15= inradArtikel.find(QRegExp("15:"),0);		//	leverantörens artbenämning
//	    int i16= inradArtikel.find(QRegExp("16:"),0);
//	    int i17= inradArtikel.find(QRegExp("17:"),0);		//	leverantörens artnr
//	    int i18= inradArtikel.find(QRegExp("18:"),0);
	    m=i3-i2;
	    if (i2 != -1){
		offertbenamn=inradArtikel.mid(i2+3,m-4);
		lineEditBenamn->setText(offertbenamn);
	    }
   	    m=i6-i5;
	    if (i5 != -1){
		fpris=inradArtikel.mid(i5+3,m-4);		// 2006-02-03
//		lineEditAPris->setText(offertradpris);		// 2006-02-03
	    }	    
/*	    
	    m=i7-i6;
	    if (i6 != -1){
		arledtid=inradArtikel.mid(i6+3,m-4);
	    }
*/
	    m=i8-i7;
	    if (i7 != -1){
		prodklass=inradArtikel.mid(i7+3,m-4);
	    }
	    
/*	    
	    m=i16-i15;
	    if (i15 != -1){
		offertbenamn=inradArtikel.mid(i15+3,m-4);
	    }
*/	    
/*	    m=i18-i17;
	    if (i17 != -1){
		offertartikelnr=inradArtikel.mid(i17+3,m-4);
	    }
*/	    
//OBS	    frmAddOffert::getPrislista();	    
	    frmAddOffert::getRadMoms();
	}
    }
}

void frmAddOffert::getPrislista()
{
    const char *userp = getenv("USER");
    QString usr(userp);

    inradpris="";
    processpris = new QProcess();
    processpris->addArgument("./STYRMAN");	// OLFIX styrprogram
    processpris->addArgument(usr);		// userid
    processpris->addArgument( "PRISDSP");		// OLFIX funktion
    processpris->addArgument(offertartikelnr);

    frmAddOffert::connect( processpris, SIGNAL(readyReadStdout() ),this, SLOT(slotPrisDataOnStdout() ) );
    frmAddOffert::connect( processpris, SIGNAL(readyReadStderr() ),this, SLOT(slotPrisDataOnStderr() ) );
    frmAddOffert::connect( processpris, SIGNAL(processExited() ),this, SLOT(slotPrisdataEndOfProcess() ) );

    if ( !processpris->start() ) {
	// error handling
	fprintf(stderr,"Problem starta STYRMAN/PRISDSP!\n");
	QMessageBox::warning( this, "Start av PRISDSP",
			      "Kan inte starta STYRMAN/PRISDSP!\n"
			      );
    }
}

void frmAddOffert::slotPrisdataEndOfProcess() 
{
    int i,m;
    prisflag=FALSE;
    i = -1;
    i = errorradpris.find( QRegExp("Error:"), 0 );
    //   qDebug("Error: %s",errorradpris.latin1());
    if (i != -1) {
	QMessageBox::critical( this, "ADDOFFW",
			       "ERROR!\n"+errorradpris
			       );
	errorradpris="";
	i = -1;
	return;
    }
    i = -1;
    i = errorradpris.find( QRegExp("Warning:"), 0 );			//  artikeln finns inte i prislistorna.
    if ( i != -1){
	prisflag=FALSE;
	offertradpris=fpris;
    }else{
	i = -1;
	i = inradpris.find( QRegExp("OK:"), 0 );

	if (i != -1) {
     	    prisflag=TRUE;
	    //	    int i0 = inrad.find( QRegExp("00:"), 0 );		//	artikelnr
	    int i1 = inradpris.find( QRegExp("01:"), 0 );		//	prislista 1
	    int i2 = inradpris.find( QRegExp("02:"), 0 );		//	prislista 2
	    int i3 = inradpris.find( QRegExp("03:"), 0 );		//	prislista 3
    	    int i4 = inradpris.find( QRegExp("04:"), 0 );		//	prislista 4
	    int i5 = inradpris.find( QRegExp("05:"), 0 );		//	prislista 5
	    int iEnd = inradpris.find( QRegExp("END:"), 0 );
	    
	    m=i2-i1;
	    if (i1 != -1){
		prislista1=inradpris.mid(i1+3,m-4);
	    }
   	    m=i3-i2;
	    if (i2 != -1){
		prislista2=inradpris.mid(i2+3,m-4);
	    }	        
	    m=i4-i3;
	    if (i3 != -1){
		prislista3=inradpris.mid(i3+3,m-4);
	    }
	    m=i5-i4;
	    if (i4 != -1){
		prislista4=inradpris.mid(i4+3,m-4);
	    }	    
	    m=iEnd-i5;
	    if (i5 != -1){
		prislista5=inradpris.mid(i5+3,m-4);
	    }
	    frmAddOffert::choosePris();
	}
    }
}

void frmAddOffert::slotPrisDataOnStdout()
{
     while (processpris->canReadLineStdout() ) {
	QString line = processpris->readStdout();
	inradpris.append(line);
	inradpris.append("\n");
    }   
}

void frmAddOffert::slotPrisDataOnStderr()
{
      while (processpris->canReadLineStderr() ) {
	QString line = processpris->readStderr();
	errorradpris.append(line);
	errorradpris.append("\n");
    }  
}

void frmAddOffert::getRadMoms()
{
    /* Radmomsen hämtas från PRODUKTGRUPP, momskod, och FTGDATA, MOMSx = momssats */
    const char *userp = getenv("USER");
    QString usr(userp);
    prodklass=prodklass.left(5);
    inrad="";
    
    process = new QProcess();
    process->addArgument("./STYRMAN");	// OLFIX styrprogram
    process->addArgument(usr);		// userid
    process->addArgument( "PKDDSP");	// OLFIX funktion
    process->addArgument(prodklass);
        
    frmAddOffert::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
    frmAddOffert::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
    frmAddOffert::connect( process, SIGNAL(processExited() ),this, SLOT(slotProdkodEndOfProcess() ) );

    if ( !process->start() ) {
	// error handling
	QMessageBox::warning( this, "Start av PKDDSP",
			      "Kan inte starta STYRMAN/PKDDSP!\n"
			      );
    }   
}

void frmAddOffert::slotProdkodEndOfProcess()
{
   int i,m;
   QString momskod="";
   bool flag=TRUE; 
//   qDebug("slotProdkodEndOfProcess::inrad=%s",inrad.latin1());
//   qDebug("slotProdkodEndOfProcess::errorrad=%s",errorrad.latin1());
    i = -1;
    i = inrad.find( QRegExp("Warning:"), 0 );
    if (i != -1){
	QMessageBox::information ( this, "ADDOFFW, PKDDSP",
		       "Varning!\nArtikeln saknar produktkod.\n"
		       );
	momskod="MOMS1";
	errorrad="";
	flag=FALSE;				// Produktkod saknas
	frmAddOffert::getMoms(momskod,"R");
//	return;
    }
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "ADDOFFW, PKDDSP",
			       "ERROR!\n"+errorrad
			       );
	errorrad="";
	i = -1;
	lineEditArtikelNr->setFocus();
    }else{
	i = -1;
	i = inrad.find( QRegExp("OK:"), 0 );
	if (i != -1) {
//	    int i1 = inrad.find( QRegExp("01:"), 0 );	                	//	produktklass
//	    int i2 = inrad.find( QRegExp("02:"), 0 );		//	beskrivning
	    int i3 = inrad.find( QRegExp("03:"), 0 );	//	momskod (för produktklassen)
	    m=5;
	    if (i3 != -1){
		if ( flag == TRUE )
		    momskod=inrad.mid(i3+3,m);
//		qDebug("slotProdkodEndOfProcess::momskod=%s",momskod.latin1());
	    }
	}
	frmAddOffert::getMoms(momskod,"R");		 /* R = Offertrad */
    }
}

void frmAddOffert::getStdLevplats( QString platsnr )
{
    const char *userp = getenv("USER");
    QString usr(userp);
    platsnr=platsnr.left(3);
    inrad="";
   
    process = new QProcess();
    process->addArgument("./STYRMAN");	// OLFIX styrprogram
    process->addArgument(usr);		// userid
    process->addArgument( "LEVPDSP");	// OLFIX funktion
    process->addArgument(offertkundnr);
    process->addArgument(platsnr);
// qDebug("kundnr=%s standardlevplats=%s",offertkundnr.latin1(),platsnr.latin1());
    frmAddOffert::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
    frmAddOffert::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
    frmAddOffert::connect( process, SIGNAL(processExited() ),this, SLOT(slotLevPEndOfProcess() ) );

    if ( !process->start() ) {
	// error handling
	QMessageBox::warning( this, "Start av LEVPDSP",
			      "Kan inte starta STYRMAN/LEVPDSP!\n"
			      );
    }
}

void frmAddOffert::slotLevPEndOfProcess()
{
    int i,m;

    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
// qDebug("Error: %s",errorrad.latin1());
// qDebug("Inrad=%s",inrad);
    if (i != -1) {
	QMessageBox::critical( this, "ADDOFFW",
			       "ERROR!\n"+errorrad
			       );
	errorrad="";
	i = -1;
	/*  När önskad standardleveransplats saknas kopiera ordinarie adress till leveransadress */
	offertkundlevadress=offertkundadress;
	lineEditKundLevAdress->setText(offertkundlevadress);
	offertkundlevpostnr=offertkundpostnr;
	lineEditKundLevPostnr->setText(offertkundlevpostnr);
	offertkundlevpostadr=offertkundpostadr;
	lineEditKundLevPostAdress->setText(offertkundlevpostadr);
	offertkundlevland=offertkundland;
	lineEditKundLevLand->setText(offertkundlevland);
	lineEditLevplats->setText("000");
//	lineEditLevplats->setFocus();
	
    }else{
	i = -1;
	i = inrad.find( QRegExp("OK:"), 0 );
	if (i != -1) {
//	    int i1 = inrad.find( QRegExp("01:"), 0 );	           //	standardleveransplatsnrnr
//	    int i2 = inrad.find( QRegExp("02:"), 0 );		//	kundnr
	    int i3 = inrad.find( QRegExp("03:"), 0 );		//	adress
	    int i4 = inrad.find( QRegExp("04:"), 0 );		//	postnr
    	    int i5 = inrad.find( QRegExp("05:"), 0 );		//	postadress
	    int i6 = inrad.find( QRegExp("06:"), 0 );		//	land
	    int i7 = inrad.find( QRegExp(":END"), 0 );	//	Slutmarkering på inrad
	    m=i4-i3;
	    if (i3 != -1){
		offertkundlevadress=inrad.mid(i3+3,m-4);
		lineEditKundLevAdress->setText(offertkundlevadress);
	    }
	    m=i5-i4;
	    if (i4 != -1){
		offertkundlevpostnr=inrad.mid(i4+3,m-4);
		lineEditKundLevPostnr->setText(offertkundlevpostnr);
	    }
	    m=i6-i5;
	    if (i5 != -1){
		offertkundlevpostadr=inrad.mid(i5+3,m-4);
		lineEditKundLevPostAdress->setText(offertkundlevpostadr);
	    }
	    m=i7-i6;
	    if (i6 != -1){
		offertkundlevland=inrad.mid(i6+3,m-4);
		lineEditKundLevLand->setText(offertkundlevland);
	    }	    
	}
    }
}

void frmAddOffert::CalculateMoms()
{
    int i=0;
    double momssumma=0;
    QListViewItemIterator it( listViewRader);
//    QString rnr;
    QString momstotal="";
    for ( ; it.current(); ++it ){
	i++;
	QString temp0=it.current()->text(0);	// radnr
	QString temp1=it.current()->text(1);	// artikelnr
	QString temp2=it.current()->text(2);	// artikelbenämning
	QString temp3=it.current()->text(3);	// leveransvecka för offertrad
	QString temp4=it.current()->text(4);	// antal
	QString temp5=it.current()->text(5);	// pris/st
	QString temp6=it.current()->text(6);	// radsumma
	QString temp7=it.current()->text(7);	// radmoms (antal * pris/st * moms)

	momssumma=momssumma+temp7.toDouble();
    }
	momstotal=momstotal.setNum(momssumma,'f',2);
	lineEditOffertMomsKr->setText(momstotal);
}

void frmAddOffert::CreateOffertHuvud()
{
    QString skilj="_:_";
    offerthuvuddata=skilj;
    
    offerthuvuddata.append(offertnr);
    offerthuvuddata.append(skilj);
    offerthuvuddata.append("0");		/* Ordernr, alltid 0*/
    offerthuvuddata.append(skilj);
    offerthuvuddata.append(offertdatum);
    offerthuvuddata.append(skilj);
    offerthuvuddata.append(offertkundnr);
    offerthuvuddata.append(skilj);
    offerthuvuddata.append(offertkundnamn);
    offerthuvuddata.append(skilj);
    offerthuvuddata.append(offertkundadress);
    offerthuvuddata.append(skilj);
    offerthuvuddata.append(offertkundpostnr);
    offerthuvuddata.append(skilj);
    offerthuvuddata.append(offertkundpostadr);
    offerthuvuddata.append(skilj);
    offerthuvuddata.append(offertkundland);
    offerthuvuddata.append(skilj);
    offerthuvuddata.append(offertkundref);
    offerthuvuddata.append(skilj);
    offerthuvuddata.append(offertkundlevadress);
    offerthuvuddata.append(skilj);
    offerthuvuddata.append(offertkundlevpostnr);
    offerthuvuddata.append(skilj);
    offerthuvuddata.append(offertkundlevpostadr);
    offerthuvuddata.append(skilj);
    offerthuvuddata.append(offertkundlevland);
    offerthuvuddata.append(skilj);
    offerthuvuddata.append(seljare);
    offerthuvuddata.append(skilj);    
    offerthuvuddata.append(offertleveranstid);
    offerthuvuddata.append(skilj);
    offerthuvuddata.append(offertmoms);
    offerthuvuddata.append(skilj);
    offerthuvuddata.append(offertvaluta);
    offerthuvuddata.append(skilj);
    offerthuvuddata.append(offertbetvillkor);
    offerthuvuddata.append(skilj);
    offerthuvuddata.append(offertlevvillkor);
    offerthuvuddata.append(skilj);
    offerthuvuddata.append(offertlevplats);
    offerthuvuddata.append(skilj);
    offerthuvuddata.append(godsmarke);
    offerthuvuddata.append(skilj);
    offerthuvuddata.append(lineEditOffertSumma->text());	/* Summa exkl moms */
    offerthuvuddata.append(skilj);
    offerthuvuddata.append(fraktbelopp);
    offerthuvuddata.append(skilj);
    offerthuvuddata.append(fraktmomskr);
    offerthuvuddata.append(skilj);        
    offerthuvuddata.append(momssumma);
    offerthuvuddata.append(skilj);
    offerthuvuddata.append(lineEditOffertTotal->text());	/* Summa inkl moms */
    offerthuvuddata.append(skilj);

    offerthuvuddata.append("END");
//    qDebug("offerthuvuddata=%s",offerthuvuddata.latin1());
    frmAddOffert::slotAddOffert();			/* Spara offerthuvud */
}

void frmAddOffert::UpdateKundOffertNr()
{
/*   Uppdatera offertnummer i FTGDATA, posttyp KORNR=senast använda kundoffertnr
      Använd funktion FTGUPD KORNR "offertnr+1"
*/
    const char *userp = getenv("USER");
    QString usr(userp);
	
//	qDebug("offertnr=%s",offertnr.latin1());
	inrad="";
	errorrad="";
	
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "FTGUPD");	// OLFIX funktion		Offerthuvud till ORDERREG
	process->addArgument("OFFNR");
	process->addArgument(offertnr);
	
	frmAddOffert::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmAddOffert::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmAddOffert::connect( process, SIGNAL(processExited() ),this, SLOT(slotUpdateOffertnrEndOfProcess() ) );
	    
	if (offertnr == ""){
    	    QMessageBox::warning( this, "ADDOFFW",
                      "Offertnummer saknas \n" );
	}else {
	    if ( !process->start() ) {
		// error handling
		QMessageBox::warning( this, "ADDOFFW",
                            "Kan inte starta STYRMAN/FTGUPD \n" );
	    }
	}
}

void frmAddOffert::slotUpdateOffertnrEndOfProcess()
{
    frmAddOffert::SaveOffertRader();
}

void frmAddOffert::SaveOffertRader()
{
    // listViewRader
    int i=0;    
    QListViewItemIterator it( listViewRader);
    QString rnr;
    listViewRader->firstChild ();
    for ( ; it.current(); ++it ){
	i++;
	QString temp0=it.current()->text(0);	// radnr
	QString temp1=it.current()->text(1);	// artikelnr
	QString temp2=it.current()->text(2);	// artikelbenämning
	QString temp3=it.current()->text(3);	// leveransvecka
	QString temp4=it.current()->text(4);	// antal
	QString temp5=it.current()->text(5);	// pris/st
	QString temp6=it.current()->text(6);	// radsumma
	QString temp7=it.current()->text(7);	// radmoms
//            qDebug("i=%d  temp=%s, %s, %s, %s, %s, %s, %s, %s",i,temp0.latin1(),temp1.latin1(),temp2.latin1(),temp3.latin1(),temp4.latin1(),temp5.latin1(),temp6.latin1(),temp7.latin1());
	frmAddOffert::createOffertrad(temp0,temp1,temp2,temp3, temp4,temp5,temp6,temp7);
    }
    listViewRader->clear();
}

void frmAddOffert::createOffertrad(QString tmp0,QString tmp1,QString tmp2,QString tmp3, QString tmp4,QString tmp5,QString tmp6,QString tmp7)
{
    offertraddata="";
    QString skilj;
    skilj="_:_";
    offertraddata=skilj;
    offertraddata.append(offertnr);	// offertnr
    offertraddata.append(skilj);
    offertraddata.append("0");		// ordernr, alltid 0
    offertraddata.append(skilj);
    offertraddata.append(tmp0);	// radnr
    offertraddata.append(skilj);    
    offertraddata.append(offertkundnr);	// kundnummer
    offertraddata.append(skilj);
    offertraddata.append(tmp1);	// artikelnr
    offertraddata.append(skilj);
    offertraddata.append(tmp2);	//benämning
    offertraddata.append(skilj);
    offertraddata.append(tmp3);	// leveransvecka
    offertraddata.append(skilj);    
    offertraddata.append(tmp4);	// antal
    offertraddata.append(skilj);
    offertraddata.append(tmp5);	// a'-pris
    offertraddata.append(skilj);
    offertraddata.append(tmp6);	// summa exkl moms.
    offertraddata.append(skilj);    
    offertraddata.append(tmp7);	// momskr.
    offertraddata.append(skilj);    
    offertraddata.append("END");	

//    qDebug("offertraddata=%s",offertraddata.latin1());
    frmAddOffert::AddOffertRad();			// parallell bearbetning
    frmAddOffert::updateReserveratAntal(tmp1,tmp4);  	// parallell bearbetning
}

void frmAddOffert::AddOffertRad()
{
    /************************************************************************/
    /*	Uppdatera offertrad,ORDERRADREG					*/
    /************************************************************************/
    const char *userp = getenv("USER");
    QString usr(userp);
    processnbr++;
    if (processnbr > 195){
	processnbr=1;
    }
//    qDebug("artnr=%s ant=%s",artnr.latin1(),ant.latin1());
    inrad2="";
    errorrad2="";
 
    radproc[processnbr] = new QProcess();
    radproc[processnbr]->addArgument("./STYRMAN");	// OLFIX styrprogram
    radproc[processnbr]->addArgument(usr);		// userid
    radproc[processnbr]->addArgument( "OFFRADD");	// OLFIX funktion
    radproc[processnbr]->addArgument(offertraddata);
    
    frmAddOffert::connect( radproc[processnbr], SIGNAL(readyReadStdout() ),this, SLOT(slotOffertradDataOnStdout() ) );
     frmAddOffert::connect( radproc[processnbr], SIGNAL(readyReadStderr() ),this, SLOT(slotOffertadDataOnStderr() ) );
    frmAddOffert::connect( radproc[processnbr], SIGNAL(processExited() ),this, SLOT(slotOffertadEndOfProcess() ) );

    if (offertraddata == ""){
	QMessageBox::warning( this, "ADDOFFW",
			      "Offertrad saknas \n" );
	return;
    }else{
	if ( !radproc[processnbr]->start() ) {
	    // error handling
	    QMessageBox::critical( this, "ADDOFFW",
				  "Kan inte starta STYRMAN/OFFRADD! \n" );
	}
    }
}

void frmAddOffert::slotOffertadEndOfProcess()
{
    int i;
    i = -1;
 //   ganger++;
    i = errorrad2.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "ADDOFFW",
			       "ERROR!\n"+errorrad2
			       );
// 	  qDebug("slotOffertadEndOfProcess::errorrad2=%s",errorrad2.latin1());	
	errorrad2="";    
    }
    i = -1;
    i = inrad2.find(QRegExp("OK:"),0);
    if (i != -1) {
//	qDebug("slotOffertadEndOfProcess::ganger=%d  inrad2=%s",ganger,inrad2.latin1());
    }    
}

void frmAddOffert::slotOffertadDataOnStderr()
{
      while (radproc[processnbr]->canReadLineStderr() ) {
	QString line = radproc[processnbr]->readStderr();
	errorrad2.append(line);
	errorrad2.append("\n");
    }
}

void frmAddOffert::slotOffertradDataOnStdout()
{
    while (radproc[processnbr]->canReadLineStdout() ) {
	QString line = radproc[processnbr]->readStdout();
	inrad2.append(line);
	inrad2.append("\n");
    }   
}

void frmAddOffert::updateReserveratAntal(QString artnr,QString antal)
{
/*******************************************************************/
/* Uppdatera LAGERSTELLEREG, fält RESERVERAT, med funktion AR2UPD */    
/*******************************************************************/
    const char *userp = getenv("USER");
    QString usr(userp);
    QString val="1";	/* val=1 innebär att fältet RESERVERAT iLAGERSTELLEREG uppdateras */

    inrad5="";
    errorrad5="";
    process = new QProcess();
    process->addArgument("./STYRMAN");	// OLFIX styrprogram
    process->addArgument(usr);		// userid
    process->addArgument( "AR2UPD");		// OLFIX funktion
    process->addArgument(val);
    process->addArgument(artnr);
    process->addArgument(antal);
    
//    qDebug("updateReserveratAntal::  val=%s artikelnr=%s antal=%s",val.latin1(),artnr.latin1(),antal.latin1());
    frmAddOffert::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotUpdateReserveratDataOnStdout() ) );
    frmAddOffert::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotUpdateReserveratDataOnStderr() ) );
    frmAddOffert::connect( process, SIGNAL(processExited() ),this, SLOT(slotUpdateReserveratEndOfProcess() ) );

    if (offertraddata == ""){
	QMessageBox::warning( this, "ADDOFFW",
			      "Offertrad saknas \n" );
    }else{
	if ( !process->start() ) {
	    // error handling
	    QMessageBox::critical( this, "ADDOFFW",
				  "Kan inte starta STYRMAN/AR2UPD! \n" );
	}
    }    
}

void frmAddOffert::slotUpdateReserveratEndOfProcess()
{
    int i;
    i = -1;
    i = errorrad5.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "ADDOFFW",
			       "ERROR!\n"+errorrad5
			       );
	errorrad5="";    
    }else{
//	qDebug("slotUpdateReserveratEndOfProcess inrad5=%s",inrad5.latin1());
 	frmAddOffert::getOffertnr();
	lineEditOffertKundNr->setFocus();   
    }
}

void frmAddOffert::slotUpdateReserveratDataOnStderr()
{
      while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad5.append(line);
	errorrad5.append("\n");
    }
}

void frmAddOffert::slotUpdateReserveratDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad5.append(line);
	inrad5.append("\n");
    }   
}

void frmAddOffert::pushBtnHelp_clicked()
{
	inrad="";
	frmAddOffert::readResursFil();		// Hämta path till hjälpfilen
	
	int i1 = hjelpfil.find( QRegExp(".html"), 0 );
//	int i2 = hjelpfil.length();
	hjelpfil=hjelpfil.left(i1);
	hjelpfil=hjelpfil+"_KUNDORDER.html";
	hjelpfil=hjelpfil+"#OFFERT";		// Lägg till position
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

void frmAddOffert::readResursFil()
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

/*============================================================*/
/***				Ny kund    					***/
/*============================================================*/

void frmAddOffert::NyKund()
{
    /*---------------------------------------------------------------------------------------------------------*/
    /*  Test om det ska registreras en ny kund, villkorstest: om blank, om 0
	   förslag till funktionsnamn = createNyKund() , funktion KUADD kunddata
          hoppa över getKundData 
     */	  
    /*---------------------------------------------------------------------------------------------------------*/

    nykundflag=TRUE;
    /* Radera fält och lineEdit från ev gamla data */
    frmAddOffert::clearKundInfo();
    /* hämta "nästa" kundnummer, acceptera data från fälten och registrera en ny kund*/
    frmAddOffert::getSenasteKundnr();		/* samt addera ett till kundnr */
    lineEditKundNamn->setFocus();
//	frmAddOffert::getOffertnr();		/* hämta offertnr, när getSenasteKundnr() processen är klar */
}

void frmAddOffert::clearKundInfo()
{
     	     lineEditOffertKundNr->clear();
//	     lineEditOffertNbr->clear();
	     lineEditKundNamn->clear();
	     lineEditKundAdress->clear();
	     lineEditKundPostnr->clear();
	     lineEditKundPostAdress->clear();
	     lineEditKundLand->clear();
/*	      ----------------				*/	     
	     lineEditKundRef->clear();
	     lineEditKundLevAdress->clear();
	     lineEditKundLevPostnr->clear();
	     lineEditKundLevPostAdress->clear();
	     lineEditKundLevLand->clear();
	     lineEditLevplats->clear();
	     lineEditLevvillkor->clear();
	     lineEditBetvilk->clear();
	     lineEditValuta->clear();
	     lineEditMomskod->clear();
/*	    -----------------				*/	     
	     lineEditOffertSumma->clear();
	     lineEditOffertFrakt->setEnabled("TRUE");
	     lineEditOffertFrakt->clear();
	     lineEditOffertMomsKr->clear();
	     lineEditOffertTotal->clear();
/*	    -----------------				*/	     
	     offertnr="0";
	     offertkundnr="";
	     offertkundnamn="";
	     offertkundadress="";
	     offertkundpostnr="";
	     offertkundpostadr="";
	     offertkundland="";
 
	     offertkundref="";
	     offertkundlevadress="";
	     offertkundlevpostnr="";
	     offertkundlevpostadr="";
	     offertkundlevland="";
    
	     offerttfnnr="";
	     offertfaxnr="";
	    offerttelexnr="";
	    offertemail="";
	    offertref="";
	    offertreftfnnr="";
	    offertmomskod="";
	    offertmoms="25";
	    offertkontonr="";
	    offertpgnr="";
	    offertbgnr="";
	    seljare="";
	    godsmarke="";
	    offertleveranstid="";
	    offertvaluta="SEK";
	    offertbetvillkor="001";
	    offertlevvillkor="001";
	    offertlevplats="000";
	    offerthuvuddata="";       
}

void frmAddOffert::getSenasteKundnr()
{
	const char *userp = getenv("USER");
            QString usr(userp);
	inrad3="";   

	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "FTGDSP");	// OLFIX funktion
	process->addArgument("SKUNR");	// Senast använda kundnummer

	frmAddOffert::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotgetSKDataOnStdout() ) );
	frmAddOffert::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotgetSKDataOnStderr() ) );
	frmAddOffert::connect( process, SIGNAL(processExited() ),this, SLOT(getSenasteKundnrEndOfProcess() ) );

	if ( !process->start() ) {
                // error handling
	    QMessageBox::warning( this, "Start av FTGDSP ",
                            "Kan inte starta STYRMAN/FTGDSP!\n"
                            );
        }
}

void frmAddOffert::getSenasteKundnrEndOfProcess()
{
//    qDebug("getSenasteKundnrEndOfProcess::Start");
    long kunr;
    int i,m;
    i = -1;
//    qDebug("getSenasteKundnrEndOfProcess::inrad3=%s  errorrad3=%s",inrad3.latin1(),errorrad3.latin1());
    i = errorrad3.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "ADDOFFW",
		"ERROR!\nPosten SKUNR saknas!\n"+errorrad3
	);
	errorrad3="";
	i = -1;
     }
     i = -1;
     i = inrad3.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	 int i1 = inrad3.find( QRegExp("1:SKUNR"), 0 );
	 int i2 = inrad3.find( QRegExp("2:"), 0 );	
	 int i3 = inrad3.length();
	 m=i2-i1;
	 m=i3-i2;
	 if (i2 != -1){
	     offertkundnr=inrad3.mid(i2+2,m-4);
//	     qDebug("offertkundnr=%s",offertkundnr.latin1());
	     kunr=offertkundnr.toLong();
	     kunr=kunr+1;
	     offertkundnr=offertkundnr.setNum(kunr);
//	     qDebug("offertkundnr=%s",offertkundnr.latin1());
	     lineEditOffertKundNr->setText(offertkundnr);
	 }
	inrad3="";
	errorrad3="";
    }
//     qDebug("getSenasteKundnrEndOfProcess::Slut");
     frmAddOffert::getOffertnr();
}

void frmAddOffert::slotgetSKDataOnStdout()
{
     while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad3.append(line);
	inrad3.append("\n");
    }   
}

void frmAddOffert::slotgetSKDataOnStderr()
{
      while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad3.append(line);
	errorrad3.append("\n");
    }  
}

void frmAddOffert::createNyKund()
{
/*    
    // Antal fält = 31 stycken
     format= _:_4376_:_Test AB_:_Provgatan 2_:_199 99_:_LILLEBY_:_Sverige_:_ 09-999990_:_09-999999_:_info@test.se_:_Karl Andersson _:_09-999991_:_     karl.a@test.se_:_
   Caroline Seljare_:_KalmarSoftware _:_001_:_001_:_001_:_1_:_SEK_:_sv_:_J_:_J_:_J_:_J_:_J_:_J_:_2000_:_J_:_J_:_Fritt textfält_:_
*/  
//    qDebug("createNyKund");
    QString skilj="_:_";
    QString kunddata="";
    kunddata=skilj;    
    kunddata.append(offertkundnr);
    kunddata.append(skilj);
    kunddata.append(offertkundnamn);
    kunddata.append(skilj);    
    kunddata.append(offertkundadress);
    kunddata.append(skilj);    
    kunddata.append(offertkundpostnr);
    kunddata.append(skilj);    
    kunddata.append(offertkundpostadr);
    kunddata.append(skilj);    
    kunddata.append(offertkundland);
    kunddata.append(skilj);
    kunddata.append("");			/* tfnnr */
    kunddata.append(skilj);    
    kunddata.append("");			/* tfnnr */
    kunddata.append(skilj);    
    kunddata.append("");			/* mailadress */
    kunddata.append(skilj);    
    kunddata.append(offertref);		/* erref */
    kunddata.append(skilj);    
    kunddata.append("");			/* tfnnr erref */
    kunddata.append(skilj);    
    kunddata.append("");			/* mailadress erref*/
    kunddata.append(skilj);    
    kunddata.append(seljare);			/* säljare */
    kunddata.append(skilj);    
    kunddata.append("");			/* distrikt */
    kunddata.append(skilj);    
    kunddata.append("");			/* kundkategori */
    kunddata.append(skilj);    
    kunddata.append(offertlevplats);		/*  standardleveransplats*/
    kunddata.append(skilj);    
    kunddata.append(offertlevvillkor);		/* leveransvillkor */
    kunddata.append(skilj);    
    kunddata.append("001");			/* leveranssätt */
    kunddata.append(skilj);    
    kunddata.append(offertbetvillkor);		/* betalningsvillkor */
    kunddata.append(skilj);    
    kunddata.append(offertvaluta);		/* valuta */
    kunddata.append(skilj);    
    kunddata.append("");			/* språkkod */
    kunddata.append(skilj);    
    kunddata.append("J");			/* offerterkännande */
    kunddata.append(skilj);    
    kunddata.append("J");			/* plocklista */
    kunddata.append(skilj);    
    kunddata.append("J");			/* följesedel */
    kunddata.append(skilj);    
    kunddata.append("J");			/* expeditionsavgift */
    kunddata.append(skilj);    
    kunddata.append("J");			/* fraktavgift */
    kunddata.append(skilj);    
    kunddata.append("J");			/* kravbrev */
    kunddata.append(skilj);    
    kunddata.append("1000.00");		/* kreditlimmit*/
    kunddata.append(skilj);    
    kunddata.append("J");			/* dröjsmålsränta */
    kunddata.append(skilj);    
    kunddata.append("J");			/* dröjsmålsfaktura */
    kunddata.append(skilj);    
    kunddata.append("");			/* fri text */
    kunddata.append(skilj);   
//       qDebug("kunddata=%s",kunddata.latin1());
       frmAddOffert::AddKund(kunddata);
}

void frmAddOffert::AddKund(QString kund)
{
    /**********************************************************************/
    /*	Spara kunddata i KUNDREG					*/
    /**********************************************************************/
    const char *userp = getenv("USER");
    QString usr(userp);

//    qDebug("frmAddOffert::AddKund");
    inrad2="";
    errorrad2="";
    process = new QProcess();
    process->addArgument("./STYRMAN");	// OLFIX styrprogram
    process->addArgument(usr);		// userid
    process->addArgument( "KUADD");	// OLFIX funktion
    process->addArgument(kund);

    frmAddOffert::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotOffertradDataOnStdout() ) );
    frmAddOffert::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotOffertadDataOnStderr() ) );
    frmAddOffert::connect( process, SIGNAL(processExited() ),this, SLOT(slotNyKundEndOfProcess() ) );

    if ( !process->start() ) {
	    // error handling
	    QMessageBox::critical( this, "ADDOFFW",
				  "Kan inte starta STYRMAN/KUADD! \n" );
	}
}

void frmAddOffert::slotNyKundEndOfProcess()
{
    frmAddOffert::UpdateKundNr();
}

void frmAddOffert::UpdateKundNr()
{
/*   Uppdatera kundnummer i FTGDATA, posttyp SKUNR=senast använda kundnr
      Använd funktion FTGUPD SKUNR "kundnr+1"
*/
    const char *userp = getenv("USER");
    QString usr(userp);
	
//	qDebug("offertnr=%s",offertnr.latin1());
	inrad="";
	errorrad="";
	
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "FTGUPD");	// OLFIX funktion		Offerthuvud till ORDERREG
	process->addArgument("SKUNR");
	process->addArgument(offertkundnr);
	
	frmAddOffert::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmAddOffert::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmAddOffert::connect( process, SIGNAL(processExited() ),this, SLOT(NyttKundNrUpdateEndOfProcess() ) );
	    
	if ( !process->start() ) {
		// error handling
		QMessageBox::warning( this, "ADDOFFW",
                            "Kan inte starta STYRMAN/FTGUPD/SKUNR. \n" );
	    }
}

void frmAddOffert::NyttKundNrUpdateEndOfProcess()
{
    QMessageBox::information( this, "ADDOFFW",
                            "Kunden registrerad!. \n" );	
}

void frmAddOffert::choosePris()
{
    int prislistenr=0;
    double pris=0;
    
//   qDebug("choosePris:: Start! ");
    
    prislistenr=prislista.toInt();			// på kunden angiven prislista (1 - 5 )
    
//    qDebug("choosePris:: prislistenr=%d prislista=5%s ",prislistenr,prislista.latin1());
    
    switch (prislistenr) {
    case 0:
	offertradpris=fpris;			// försäljningspris enligt ARTIKELREG
	break;
      case 1:
	  pris=prislista1.toDouble();
	  if (pris > 0){
	      offertradpris=prislista1;
	  }else{
	      offertradpris=fpris;
	  }
	  break;
      case 2:
	  pris=prislista2.toDouble();
	  if (pris > 0){
	      offertradpris=prislista2;
	  }else{
	      offertradpris=fpris;
	  }
	  break;	  
      case 3: 
	  pris=prislista3.toDouble();
	  if (pris > 0){
	      offertradpris=prislista3;
	  }else{
	      offertradpris=fpris;
	  }
	  break;	  
      case 4:
	  pris=prislista4.toDouble();
	  if (pris > 0){
	      offertradpris=prislista4;
	  }else{
	      offertradpris=fpris;
	  }
	  break;
	  
      case 5:
	pris=prislista5.toDouble(); 
	if (pris > 0){
	    offertradpris=prislista5;
	}else{
	      offertradpris=fpris;
	  }
	break;
    default:
	offertradpris=fpris;			// försäljningspris enligt ARTIKELREG
	break;
   }  
//    qDebug("choosePris:: offertradpris=%s, prislista5=%s pris=%f fpris=%s",offertradpris.latin1(),prislista5.latin1(),pris,fpris.latin1());
    lineEditAPris->setText(offertradpris);
}

void frmAddOffert::pushButtonAvbryt_clicked()
{
    avbryt=TRUE;
    frmAddOffert::close();
}

void frmAddOffert::pushButtonSoek_click()
{
/*   Söka efter artikel */
    const char *userp = getenv("USER");
    QString usr(userp);
	
    inrad="";
    errorrad="";
	
    process = new QProcess();
    process->addArgument( "./SRCHARW");	// OLFIX program, söka artikel	
	
    frmAddOffert::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
    frmAddOffert::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
    frmAddOffert::connect( process, SIGNAL(processExited() ),this, SLOT(SoekArtikelEndOfProcess() ) );
	    
    if ( !process->start() ) {
	// error handling
	QMessageBox::warning( this, "ADDOFFW",
                           "Kan inte starta STYRMAN/SRCHARW. \n" );
    }
}

void frmAddOffert::SoekArtikelEndOfProcess()
{
    QString artnr;
    qDebug("inrad=%s",inrad.latin1());
    artnr=inrad;
    artnr=artnr.stripWhiteSpace();
    lineEditArtikelNr->setText(artnr);
    lineEditArtikelNr->setFocus();
}
