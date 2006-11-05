/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
/***************************************************************************
                              CHGOFFW  -  description
	         Ändring av offert.
                             -------------------
                            version 0.1
    begin   	:	 Sön      5 nov   2006
    Updated	: 
    copyright: 	(C) 2006 by Jan Pihlgren
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

    int ganger=0;
    QProcess* process;
    QProcess* processpris;
    QProcess* processartikel;
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
    QString Tmp8;
    QString Tmp9;
    QString Tmp10;
    QString Tmp11;
    QString Tmp12;	    
    QString Tmp13;
    QString Tmp14;    
    QString Tmp15;
    
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
    QString offertstatus;
    
    /*  offertradrad	 */	
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
    
    /* offert 	*/
    QString offertdel;			/*  Del av offertn, H=offerthuvud, R=offertrad */
    QString offertsumma;
    QString momssumma;		/*  Total moms på offertn */
    QString fraktbelopp;
    QString fraktmomskr;
    QString offerttotal;
    
void frmChgOffert::init()
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
    offertleveranstid=offertdatum;
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
    /****  Beräkning av leveransvecka , Slut ****/
    
    frmChgOffert::listViewRader_format();
    frmChgOffert::getoffertLista();
    listViewOffert->setFocus();
}

void frmChgOffert::PickupOffertnr( QListViewItem * item)
{
    char offertnummer[11]="";
//    qDebug("Pickupoffertnr\n");
    if(!item){
	return;
    }
     listViewOffert->setCurrentItem(item);
     if(!item->key(0,TRUE)){
	 return;
     }

     strcpy(offertnummer,item->key(0,TRUE));
     offertnr=offertnummer;
     lineEditOffertNbr->setText((offertnr));
     lineEditOffertNbr->setFocus();
}

void frmChgOffert::offertNr_returnPressed()
{
    listViewRader->clear();
    lineEditOffertSumma->clear();
    lineEditOffertFrakt->clear();
    lineEditFraktmoms->clear();
    lineEditOffertMomsKr->clear();
    lineEditOffertTotal->clear();
    
    offertnr=lineEditOffertNbr->text();
    /* Hämta offert, och kunddata */
    frmChgOffert::getoffertData();
}

void frmChgOffert::slotKundNamn_returnPressed()
{
    offertkundnamn=lineEditKundNamn->text();
//    lineEditKundAdress->setFocus();
}


void frmChgOffert::lineEditKundAdress_returnPressed()
{
    offertkundadress=lineEditKundAdress->text();
//    lineEditKundPostnr->setFocus();
}

void frmChgOffert::lineEditKundPostnr_returnPressed()
{
    offertkundpostnr=lineEditKundPostnr->text();
//    lineEditKundPostAdress->setFocus();
}

void frmChgOffert::lineEditKundPostAdress_returnPressed()
{
    offertkundpostadr=lineEditKundPostAdress->text();
//    lineEditKundLand->setFocus();
}

void frmChgOffert::lineEditKundLand_returnPressed()
{
    offertkundland=lineEditKundLand->text();
//    lineEditKundRef->setFocus();
}

void frmChgOffert::lineEditKundRef_returPressed()
{
    offertkundref=lineEditKundRef->text();
    lineEditKundRef->setText(offertkundref);
}

void frmChgOffert::lineEditKundLevAdress_returnPressed()
{
    offertkundlevadress=lineEditKundLevAdress->text();
    lineEditKundLevAdress->setText(offertkundlevadress);
}

void frmChgOffert::lineEditKundLevPostnr_returnPressed()
{
    offertkundlevpostnr=lineEditKundLevPostnr->text();
    lineEditKundLevPostnr->setText(offertkundlevpostnr);
}

void frmChgOffert::lineEditKundLevPostAdress_returnPressed()
{
    offertkundlevpostadr=lineEditKundLevPostAdress->text();
    lineEditKundLevPostAdress->setText(offertkundlevpostadr);
}

void frmChgOffert::lineEditKundLevLand_return_pressed()
{
    offertkundlevland=lineEditKundLevLand->text();
    lineEditKundLevLand->setText(offertkundlevland);
}

void frmChgOffert::lineEditLevplats_returnPressed()
{
    offertlevplats=lineEditLevplats->text();
//    frmChgOffert::getStdLevplats( offertlevplats );
}

void frmChgOffert::lineEditLevvillkor_returnPressed()
{
    offertlevvillkor=lineEditLevvillkor->text();
}

void frmChgOffert::lineEditBetvilk_returnPressed()
{
    offertbetvillkor=lineEditBetvilk->text();
}

void frmChgOffert::lineEditValuta_returnPressed()
{
    offertvaluta=lineEditValuta->text();
}	

void frmChgOffert::lineEditMomskod_returnPressed()
{
    offertmoms=lineEditMomskod->text();
}

void frmChgOffert::lineEditSeljare_returnPressed()
{
    seljare=lineEditSeljare->text();
}

void frmChgOffert::lineOffertLeveranstid_returnPressed()
{
    offertleveranstid=lineOffertLeveranstid->text();
}

void frmChgOffert::lineEditGodsmarke_returnPressed()
{
    godsmarke=lineEditGodsmarke->text();
}

/**************************************************************************/
/*		offertradrad	Start				*/
/**************************************************************************/

void frmChgOffert::lineEditArtikelNr_returnPressed()
{
    offertartikelnr=lineEditArtikelNr->text();
    frmChgOffert::getArtikeldata();
}

void frmChgOffert::lineEditBenamn_returnPressed()
{
    offertbenamn=lineEditBenamn->text();
}

void frmChgOffert::lineEditLeveransvecka_returnPressed()
{
    radleveransvecka=lineEditLeveransvecka->text();
}

void frmChgOffert::lineEditAntal_returnPressed()
{
    int i;
    double antal;
    offertantal=lineEditAntal->text();
    antal=offertantal.toDouble();
    if ( antal==0){
	QMessageBox::warning( this, "CHGOFFW",
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
    }
}

void frmChgOffert::lineEditAPris_returnPressed()
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

void frmChgOffert::pushBtnOKRad_clicked()
{
//    double summa ,belopp;
//   , moms, momsbelopp;
    QString radmomsbelopp;
    QListViewItem * item;
    int i;
    
    /*	Är artikelnummer ifyllt? 	*/
    if (offertartikelnr==""){
	if (! avbryt){
	    QMessageBox::warning( this, "CHGOFFW",
		      "Artikelnummer måste anges!\n" );
	    lineEditArtikelNr->setFocus();
	}
    }
    
    radmomsbelopp=lineEditRadMoms->text();    
    item = new QListViewItem(listViewRader,offertradnr,offertartikelnr,offertbenamn,radleveransvecka,offertantal,offertradpris,radbelopp,radmomsbelopp);
    item->setText(8,Tmp8);
    item->setText(9,Tmp9);
    item->setText(10,Tmp10);
    item->setText(11,Tmp11);
    item->setText(12,Tmp12);
    item->setText(13,Tmp13);
    item->setText(14,Tmp14);
    item->setText(15,Tmp15);

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
/*    
    summa=offertsumma.toDouble();
    belopp=radbelopp.toDouble();
    summa=summa+belopp;
    offertsumma=offertsumma.setNum(summa,'f',2);
    lineEditoffertSumma->setText(offertsumma);
*/    
    /*  Beräkna momsen hittills för offertn	*/  
    frmChgOffert::CalculateMoms();
    frmChgOffert::Calculateoffert();
    
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
//    lineEditArtikelNr->setFocus();
}

void frmChgOffert::pushBtnRadNej_clicked()
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

void frmChgOffert::listViewRader_clicked( QListViewItem * )
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
    Tmp8=item->text(8);
    Tmp9=item->text(9);
    Tmp10=item->text(10);
    Tmp11=item->text(11);
    Tmp12=item->text(12);
    Tmp13=item->text(13);
    Tmp14=item->text(14);
    Tmp15=item->text(15);
   
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
    radsumma=temp6.toDouble();
    tmpoffertsumma=offertsumma.toDouble();
    tmpoffertsumma=tmpoffertsumma-radsumma;
    offertsumma=offertsumma.setNum(tmpoffertsumma,'f',2);
    lineEditOffertSumma->setText(offertsumma);
    lineEditArtikelNr->setFocus();
    delete listViewRader->currentItem();
}

/************************************************************************/
/*		offertradrad	Slut				*/
/************************************************************************/

void frmChgOffert::lineEditOffertFrakt_returnPressed()
{
    frmChgOffert::Calculateoffert();
    pushBtnOffertKlar->setFocus();
}

void frmChgOffert::pushBtnOffertKlar_clicked()
{
//    lineEditoffertFrakt->setEnabled("FALSE");
//    pushButtonOK->setFocus();			
    frmChgOffert::CreateoffertHuvud();
}

void frmChgOffert::slotBtnOK_clicked()
{
//    frmChgOffert::CreateoffertHuvud();
// Och lägg upp offerthuvud i offertREG
}

void frmChgOffert::Calculateoffert()
{
//    QListViewItem * item;
    double summa ,totalsumma,fraktsumma,radmomssumma,fraktmoms,moms,momsbelopp,tmp;
    double radantal=0;
    double stpris=0;
    double radsumma=0;
    double radmoms=0;	/* i kronor */
    double exklsumma=0;
    double momstotalrader=0;	/* summa av radernas moms i kr */
    int i;
    totalsumma=0;
    QString radmomstotal;
    QString tmpfrakt;
    QString offerttotal;  
//    radmomstotal = lineEditoffertMomsKr->text();
    radmomssumma = radmomstotal.toDouble();
      /*	Summa rad		*/
    QListViewItemIterator it( listViewRader);
    listViewRader->firstChild ();
    for ( ; it.current(); ++it ){
	i++;
	QString temp4=it.current()->text(4);	// antal
	radantal=temp4.toDouble();
	QString temp5=it.current()->text(5);	// pris/st
	stpris=temp5.toDouble();
	QString temp6=it.current()->text(6);	// radsumma
	radsumma=temp6.toDouble();
	QString temp7=it.current()->text(7);	// radmoms
	radmoms=temp7.toDouble();
	momstotalrader=momstotalrader+radmoms;	// summa av radernas moms i kr
	exklsumma=exklsumma+(radantal * stpris);	// summa av radernas summa
    }
   radmomssumma=momstotalrader;
    
    summa=exklsumma;
    offerttotal=offerttotal.setNum(summa,'f',2);
    lineEditOffertSumma->setText(offerttotal);
    qDebug("radmomssumma=%f summa=%f",radmomssumma,summa);
       /*	Fraktkostnad	   */
//    summa = offertsumma.toDouble();
    fraktbelopp = lineEditOffertFrakt->text();
    tmp=fraktbelopp.toDouble();
    fraktbelopp=fraktbelopp.setNum(tmp,'f',2);		/*  Editering till heltal och 2 decimaler */
    lineEditOffertFrakt->setText(fraktbelopp);
    fraktsumma = fraktbelopp.toDouble(); 
    
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
    
       /* offert total 	*/
    totalsumma=summa+fraktsumma+fraktmoms+momsbelopp;
    offertsumma=offertsumma.setNum(totalsumma,'f',2);	/* inklusive moms*/
    lineEditOffertTotal->setText(offertsumma);

}



void frmChgOffert::slotUpdateoffert()
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
	process->addArgument( "OFFCHG");	// OLFIX funktion		offerthuvud till offertREG
	process->addArgument(offerthuvuddata);
	
	frmChgOffert::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmChgOffert::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
                frmChgOffert::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );
	    
	if (offerthuvuddata == "" ){
    	    QMessageBox::warning( this, "CHGOFFW",
                      "Data saknas till offerthuvud! \n" );
	}else {
	    if ( !process->start() ) {
		// error handling
		QMessageBox::warning( this, "CHGOFFW",
                            "Kan inte starta STYRMAN/ORDCHG! \n" );
	    }
	}
}

void frmChgOffert::slotDataOnStdout()
{
     while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }   
}

void frmChgOffert::slotDataOnStderr()
{
      while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }  
}

void frmChgOffert::slotEndOfProcess()
{
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
//   qDebug("Error:%s",errorrad.latin1());
//   qDebug("Inrad:%s",inrad.latin1());
     if (i != -1) {
	QMessageBox::critical( this, "CHGOFFW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
	return;
     }else{
	 i = -1;
	 i = inrad.find( QRegExp("OK:"), 0 );
	 if (i != -1) {
//	     QMessageBox::information( this, "CHGOFFW",
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
	     frmChgOffert::SaveoffertRader();	     
	 } 
     }
}

void frmChgOffert::getoffertLista()
{
    const char *userp = getenv("USER");
    QString usr(userp);
    inrad="";

    process = new QProcess();
    process->addArgument("./STYRMAN");	// OLFIX styrprogram
    process->addArgument(usr);		// userid
    process->addArgument( "OFFLST");	// OLFIX funktion

    frmChgOffert::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
    frmChgOffert::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
    frmChgOffert::connect( process, SIGNAL(processExited() ),this, SLOT(offertListaEndOfProcess() ) );

	if ( !process->start() ) {
                // error handling
	    QMessageBox::warning( this, "Start av OFFLST ",
                            "Kan inte starta STYRMAN/OFFLST!\n"
                            );
        }
}

void frmChgOffert::offertListaEndOfProcess()
{
    QListViewItem* item;
    int i;
    listViewOffert->setSorting(0,TRUE);
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "CHGOFFW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
     }

    i = inrad.find( QRegExp("OK: NR_0_"), 0 );
         if (i != -1) {
	QMessageBox::information( this, "CHGOFFW",
		"offertregistret innehåller inga poster!\n"
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
    char offertnr[11]="";
    char kundnr[11]="";
    char datum[11]="";
    char status[2]="";
    char belopp[14]="";

    tmppek=tmp;
    qstrcpy(tmp,inrad);
    pos1=strstr(tmp,"OK: NR_");	// 7 tecken långt
    pos2=strstr(tmp,"_:");
    i=pos2-pos1;
    m=i+2;			// startposition för första offertnr.
    
//    qDebug("i=%d  m=%d",i,m);
    
    k=0;
    for (j=7;j<i;j++){			// j = första positionen för antal poster,(OK: NR_3_:16_:4383_:2006-02-14_:A_:2682.40_:)
	antrad[k]=tmp[j];
	k++;
    };
    i=atoi(antrad);			// i = antal poster
    
//    qDebug("antrad=%s",antrad);
    
    for (k = 1;k <= i; k++){		// gå igenom alla raderna / posterna
	l=0;
	for(j = m; j < sizeof(offertnr) + m; j++){
	    if(tmp[j] != *("_")){
		offertnr[l]=tmp[j];
		l++;
	    }else{
		offertnr[l] = *("\0");
		j=sizeof(offertnr) + m;
	    }
	}
//	qDebug("%s  ",offertnr);
	m=m+l+2;		// position för kundnr
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
	m=m+l+2;		// position för datum
	l=0;
	for(j = m; j < sizeof(datum) + m; j++){
	    if(tmp[j] != *("_")){
		datum[l]=tmp[j];
		l++;
	    }else{
		datum[l] = *("\0");
		j=sizeof(datum) + m;
	    }
	}
//	qDebug("%s  ",datum);	
	m=m+l+2;		// position för status
	l=0;
	for(j = m; j < sizeof(status) + m; j++){
	    if(tmp[j] != *("_")){
		status[l]=tmp[j];
		l++;
	    }else{
		status[l] = *("\0");
		j=sizeof(status) + m;
	    }
	}
//	qDebug("%s  ",status);	
	m=m+l+2;		// position för belopp
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
//	qDebug("%s  ",belopp);	
	m=m+l+2;
//	qDebug("inrad=%s",inrad.latin1());
//	int st=strcmp("F",status);
//	qDebug("st=%d offertnr=%s Status=%s TRUE=%d",st,offertnr,status,TRUE);
	/* Här är TRUE==1.  strcmp(cs,ct) ger = 0 om cs ==ct */
	/* Altså innbär nedanstående en negation, if "F" <> status skapa en ny item. */
	if ( strcmp("F",status)){		/*Visa inte ordrar som är fakturerade, status=F */
	    item = new QListViewItem(listViewOffert,offertnr,kundnr);
	}
// 	 rensa kundnr och namn
  	for (l=0;l<sizeof(kundnr);l++)
		kundnr[l]=*("\0");
	for (l=0;l<sizeof(offertnr);l++)
		offertnr[l]=*("\0");
//	 rensa listrad 
	listrad.remove(0,80);
    }
}

void frmChgOffert::getoffertnr()
{
	const char *userp = getenv("USER");
            QString usr(userp);


	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "FTGDSP");	// OLFIX funktion
	process->addArgument("KORNR");	// Senas använda kundoffertnummer

	frmChgOffert::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmChgOffert::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmChgOffert::connect( process, SIGNAL(processExited() ),this, SLOT(slotgetoffertnrEndOfProcess() ) );

	if ( !process->start() ) {
                // error handling
	    QMessageBox::warning( this, "Start av FTGDSP ",
                            "Kan inte starta STYRMAN/FTGDSP!\n"
                            );
        }
}

void frmChgOffert::slotgetoffertnrEndOfProcess()
{
    int i,m;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "CHGOFFW",
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
   frmChgOffert::getMoms("MOMS1","H");		/* H = offerthuvud */
}

void frmChgOffert::getMoms(QString momskod,QString typ)
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

	frmChgOffert::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmChgOffert::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmChgOffert::connect( process, SIGNAL(processExited() ),this, SLOT(slotgetMomsEndOfProcess() ) );

	if ( !process->start() ) {
                // error handling
	    QMessageBox::warning( this, "Start av FTGDSP ",
                            "Kan inte starta STYRMAN/FTGDSP!\n"
                            );
        }
}

void frmChgOffert::slotgetMomsEndOfProcess()
{
//    qDebug("slotgetMomsEndOfProcess::inrad=%s",inrad.latin1());
    int i,m;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "CHGOFFW",
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
     frmChgOffert::getSeljare();
}

void frmChgOffert::getSeljare()
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

	frmChgOffert::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotgetUDataOnStdout() ) );
	frmChgOffert::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotgetUDataOnStderr() ) );
	frmChgOffert::connect( process, SIGNAL(processExited() ),this, SLOT(slotgetUserEndOfProcess() ) );

	if ( !process->start() ) {
                // error handling
	    QMessageBox::warning( this, "Start av USERDSP ",
                            "Kan inte starta STYRMAN/USERDSP!\n"
                            );
        }
}

void frmChgOffert::slotgetUserEndOfProcess()
{
//    qDebug("slotgetUserEndOfProcess::Start");
    int i,m;
    i = -1;
    i = errorrad4.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "CHGOFFW",
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

void frmChgOffert::slotgetUDataOnStdout()
{
     while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad4.append(line);
	inrad4.append("\n");
    }   
}

void frmChgOffert::slotgetUDataOnStderr()
{
      while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad4.append(line);
	errorrad4.append("\n");
    }  
}

void frmChgOffert::listViewRader_format()
{
    listViewRader->setColumnWidth(0,44);		// Radnr
    listViewRader->setColumnWidth(1,180);		// Artikelnr
    listViewRader->setColumnWidth(2,295);		// Benämning
    listViewRader->setColumnWidth(3,86);		// Leveransvecka
    listViewRader->setColumnWidth(4,65);		// Antal
    listViewRader->setColumnWidth(5,66);		// Pris
    listViewRader->setColumnWidth(6,86);		// Summa
    listViewRader->setColumnWidth(7,86);		// Moms
}

void frmChgOffert::getArtikeldata()
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
    frmChgOffert::connect( processartikel, SIGNAL(readyReadStdout() ),this, SLOT(slotArdataDataOnStdout() ) );
    frmChgOffert::connect( processartikel, SIGNAL(readyReadStderr() ),this, SLOT(slotArdataDataOnStderr() ) );
    frmChgOffert::connect( processartikel, SIGNAL(processExited() ),this, SLOT(slotArdataEndOfProcess() ) );

    if ( !processartikel->start() ) {
	// error handling
//	fprintf(stderr,"Problem starta STYRMAN/ARDSP!\n");
	QMessageBox::warning( this, "Start av ARDSP",
			      "Kan inte starta STYRMAN/ARDSP!\n"
			      );
    }
}

void frmChgOffert::slotArdataDataOnStdout(){
         while (processartikel->canReadLineStdout() ) {
	QString line = processartikel->readStdout();
	inradArtikel.append(line);
	inradArtikel.append("\n");
    }   
//	 qDebug("ArdataDataOnStdout::inradArtikel=%s",inradArtikel.latin1());	 
}

void frmChgOffert::slotArdataDataOnStderr(){
          while (processartikel->canReadLineStderr() ) {
	QString line = processartikel->readStderr();
	errorradArtikel.append(line);
	errorradArtikel.append("\n");
    }  
}
		
void frmChgOffert::slotArdataEndOfProcess()
{
    int i,m;

    i = -1;
    i = errorradArtikel.find( QRegExp("Error:"), 0 );
//    qDebug("Error:  ArdataEndOfProcess::  %s",errorradArtikel.latin1());
//    qDebug("ArdataEndofProsess::inradArtikel=%s",inradArtikel.latin1());
    
    if (i != -1) {
	QMessageBox::critical( this, "CHGOFFW",
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
//OBS	    frmChgOffert::getPrislista();	    
	    frmChgOffert::getRadMoms();
	}
    }
}

void frmChgOffert::getPrislista()
{
    const char *userp = getenv("USER");
    QString usr(userp);

    inradpris="";
    processpris = new QProcess();
    processpris->addArgument("./STYRMAN");	// OLFIX styrprogram
    processpris->addArgument(usr);		// userid
    processpris->addArgument( "PRISDSP");		// OLFIX funktion
    processpris->addArgument(offertartikelnr);

    frmChgOffert::connect( processpris, SIGNAL(readyReadStdout() ),this, SLOT(slotPrisDataOnStdout() ) );
    frmChgOffert::connect( processpris, SIGNAL(readyReadStderr() ),this, SLOT(slotPrisDataOnStderr() ) );
    frmChgOffert::connect( processpris, SIGNAL(processExited() ),this, SLOT(slotPrisdataEndOfProcess() ) );

    if ( !processpris->start() ) {
	// error handling
	fprintf(stderr,"Problem starta STYRMAN/PRISDSP!\n");
	QMessageBox::warning( this, "Start av PRISDSP",
			      "Kan inte starta STYRMAN/PRISDSP!\n"
			      );
    }
}

void frmChgOffert::slotPrisdataEndOfProcess() 
{
    int i,m;
    prisflag=FALSE;
    i = -1;
    i = errorradpris.find( QRegExp("Error:"), 0 );
    //   qDebug("Error: %s",errorradpris.latin1());
    if (i != -1) {
	QMessageBox::critical( this, "CHGOFFW",
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
	    frmChgOffert::choosePris();
	}
    }
}

void frmChgOffert::slotPrisDataOnStdout()
{
     while (processpris->canReadLineStdout() ) {
	QString line = processpris->readStdout();
	inradpris.append(line);
	inradpris.append("\n");
    }   
}

void frmChgOffert::slotPrisDataOnStderr()
{
      while (processpris->canReadLineStderr() ) {
	QString line = processpris->readStderr();
	errorradpris.append(line);
	errorradpris.append("\n");
    }  
}

void frmChgOffert::getRadMoms()
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
        
    frmChgOffert::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
    frmChgOffert::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
    frmChgOffert::connect( process, SIGNAL(processExited() ),this, SLOT(slotProdkodEndOfProcess() ) );

    if ( !process->start() ) {
	// error handling
	QMessageBox::warning( this, "Start av PKDDSP",
			      "Kan inte starta STYRMAN/PKDDSP!\n"
			      );
    }   
}

void frmChgOffert::slotProdkodEndOfProcess()
{
   int i,m;
   QString momskod="";
   bool flag=TRUE; 
//   qDebug("slotProdkodEndOfProcess::inrad=%s",inrad.latin1());
//   qDebug("slotProdkodEndOfProcess::errorrad=%s",errorrad.latin1());
    i = -1;
    i = inrad.find( QRegExp("Warning:"), 0 );
    if (i != -1){
	QMessageBox::information ( this, "CHGOFFW, PKDDSP",
		       "Varning!\nArtikeln saknar produktkod.\n"
		       );
	momskod="MOMS1";
	errorrad="";
	flag=FALSE;				// Produktkod saknas
	frmChgOffert::getMoms(momskod,"R");
//	return;
    }
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "CHGOFFW, PKDDSP",
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
	frmChgOffert::getMoms(momskod,"R");		 /* R = offertrad */
    }
}

void frmChgOffert::CalculateMoms()
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

void frmChgOffert::CreateoffertHuvud()
{
    QString skilj="_:_";
    offerthuvuddata=skilj;
    
    offerthuvuddata.append(offertnr);
    offerthuvuddata.append(skilj);
//    offerthuvuddata.append(offertdatum);
//    offerthuvuddata.append(skilj);
//    offerthuvuddata.append(offertkundnr);
//    offerthuvuddata.append(skilj);
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
   qDebug("offerthuvuddata=%s",offerthuvuddata.latin1());
    slotUpdateoffert();				/* Spara offerthuvud */
}

void frmChgOffert::slotUpdateoffertnrEndOfProcess()
{
    frmChgOffert::SaveoffertRader();
}

void frmChgOffert::SaveoffertRader()
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
	
	QString temp8=it.current()->text(8);	//levantal
	QString temp9=it.current()->text(9);	//restantal
	QString temp10=it.current()->text(10);	//radrabatt
	QString temp11=it.current()->text(11);	//kalkylpris
	QString temp12=it.current()->text(12);	//levdatum
	QString temp13=it.current()->text(13);	//enhet
	QString temp14=it.current()->text(14);	//faktantal
	QString temp15=it.current()->text(15);	//radtyp
	qDebug("levantal=%s radtyp=%s",temp8.latin1(),temp15.latin1());
//            qDebug("i=%d  temp=%s, %s, %s, %s, %s, %s, %s, %s",i,temp0.latin1(),temp1.latin1(),temp2.latin1(),temp3.latin1(),temp4.latin1(),temp5.latin1(),temp6.latin1(),temp7.latin1());
	frmChgOffert::createoffertrad(temp0,temp1,temp2,temp3, temp4,temp5,temp6,temp7,temp8,temp9,temp10,temp11,temp12,temp13,temp14,temp15);
    }
    listViewRader->clear();
}

void frmChgOffert::createoffertrad(QString tmp0,QString tmp1,QString tmp2,QString tmp3, QString tmp4,QString tmp5,QString tmp6,QString tmp7,QString tmp8,QString tmp9,QString tmp10,QString tmp11,QString tmp12,QString tmp13,QString tmp14,QString tmp15)
{
    offertraddata="";
    QString skilj;
    skilj="_:_";
    offertraddata=skilj;
    offertraddata.append(offertnr);	// offertnr
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
    offertraddata.append(tmp8);	// levantal
    offertraddata.append(skilj);    
    offertraddata.append(tmp9);	// restantal
    offertraddata.append(skilj);
    offertraddata.append(tmp10);	// radrabatt
    offertraddata.append(skilj);    
    offertraddata.append(tmp11);	// kalkylpris
    offertraddata.append(skilj);    
    offertraddata.append(tmp12);	// levdatum
    offertraddata.append(skilj);    
    offertraddata.append(tmp13);	// enhet
    offertraddata.append(skilj);    
    offertraddata.append(tmp14);	// faktantal
    offertraddata.append(skilj);    
    offertraddata.append(tmp15);	// radtyp
    offertraddata.append(skilj);    
    offertraddata.append("END");	

    qDebug("offertraddat=%s",offertraddata.latin1());
    frmChgOffert::ChangeoffertRad();		
//    frmChgOffert::updateReserveratAntal(tmp1,tmp4);  	// parallell bearbetning

}

void frmChgOffert::ChangeoffertRad()
{
    /************************************************************************/
    /*	Uppdatera offertrad,offertRADREG					*/
    /************************************************************************/
    const char *userp = getenv("USER");
    QString usr(userp);
//    qDebug("artnr=%s ant=%s",artnr.latin1(),ant.latin1());
    inrad2="";
    errorrad2="";
 
    process = new QProcess();
    process->addArgument("./STYRMAN");	// OLFIX styrprogram
    process->addArgument(usr);		// userid
    process->addArgument( "OFFRCHG");	// OLFIX funktion
    process->addArgument(offertraddata);

    frmChgOffert::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotoffertradDataOnStdout() ) );
    frmChgOffert::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotoffertadDataOnStderr() ) );
    frmChgOffert::connect( process, SIGNAL(processExited() ),this, SLOT(slotoffertadEndOfProcess() ) );

    if (offertraddata == ""){
	QMessageBox::warning( this, "CHGOFFW",
			      "offertrad saknas \n" );
    }else{
	if ( !process->start() ) {
	    // error handling
	    QMessageBox::critical( this, "CHGOFFW",
				  "Kan inte starta STYRMAN/OFFRCHG! \n" );
	}
    }
}

void frmChgOffert::slotoffertadEndOfProcess()
{
    int i;
    i = -1;
 //   ganger++;
    i = errorrad2.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "CHGOFFW",
			       "ERROR!\n"+errorrad2
			       );
// 	  qDebug("slotoffertadEndOfProcess::errorrad2=%s",errorrad2.latin1());	
	errorrad2="";    
    }
    i = -1;
    i = inrad2.find(QRegExp("OK:"),0);
    if (i != -1) {
//	qDebug("slotoffertadEndOfProcess::ganger=%d  inrad2=%s",ganger,inrad2.latin1());
    }    
}

void frmChgOffert::slotoffertadDataOnStderr()
{
      while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad2.append(line);
	errorrad2.append("\n");
    }
}

void frmChgOffert::slotoffertradDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad2.append(line);
	inrad2.append("\n");
    }   
}

void frmChgOffert::updateReserveratAntal(QString artnr,QString antal)
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
    process->addArgument( "AR2UPD");	// OLFIX funktion
    process->addArgument(val);
    process->addArgument(artnr);
    process->addArgument(antal);
    
//    qDebug("updateReserveratAntal::  val=%s artikelnr=%s antal=%s",val.latin1(),artnr.latin1(),antal.latin1());
    frmChgOffert::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotUpdateReserveratDataOnStdout() ) );
    frmChgOffert::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotUpdateReserveratDataOnStderr() ) );
    frmChgOffert::connect( process, SIGNAL(processExited() ),this, SLOT(slotUpdateReserveratEndOfProcess() ) );

    if (offertraddata == ""){
	QMessageBox::warning( this, "CHGOFFW",
			      "offertrad saknas \n" );
    }else{
	if ( !process->start() ) {
	    // error handling
	    QMessageBox::critical( this, "CHGOFFW",
				  "Kan inte starta STYRMAN/AR2UPD! \n" );
	}
    }    
}

void frmChgOffert::slotUpdateReserveratEndOfProcess()
{
    int i;
    i = -1;
    i = errorrad5.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "CHGOFFW",
			       "ERROR!\n"+errorrad5
			       );
	errorrad5="";    
    }else{
//	qDebug("slotUpdateReserveratEndOfProcess inrad5=%s",inrad5.latin1());
 	frmChgOffert::getoffertnr();
	lineEditOffertKundNr->setFocus();   
    }
}

void frmChgOffert::slotUpdateReserveratDataOnStderr()
{
      while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad5.append(line);
	errorrad5.append("\n");
    }
}

void frmChgOffert::slotUpdateReserveratDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad5.append(line);
	inrad5.append("\n");
    }   
}

void frmChgOffert::pushBtnHelp_clicked()
{
	inrad="";
	frmChgOffert::readResursFil();		// Hämta path till hjälpfilen
	
	int i1 = hjelpfil.find( QRegExp(".html"), 0 );
	hjelpfil=hjelpfil.left(i1);
	hjelpfil=hjelpfil+"_KUNDOFFERT.html";
	hjelpfil=hjelpfil+"#OFFERT_CHANGE";		// Lägg till position
//	qDebug("hjelpfil=%s",hjelpfil.latin1());
	process = new QProcess();
	process->addArgument( "./OLFIXHLP" );		// OLFIX program
	process->addArgument(hjelpfil);

	if ( !process->start() ) {
	    // error handling
	    QMessageBox::warning( this, "OLFIX","Kan inte starta OLFIXHLP!\n" );
	}
//	lineEditArtikelNr->setFocus();
}

void frmChgOffert::readResursFil()
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
/*	    qDebug("hjelpfil=%s",hjelpfil.latin1());		*/
	    hjelpfil=(hjelpfil.right(hjelpfil.length() - 9));
/*	    qDebug("hjelpfil=%s",hjelpfil.latin1());		*/
	}
            lines += line;
        }
    }
    f1.close();
}

void frmChgOffert::clearKundInfo()
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

void frmChgOffert::choosePris()
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

void frmChgOffert::pushButtonAvbryt_clicked()
{
    avbryt=TRUE;
    close();
}

void frmChgOffert::getoffertData()
{
    frmChgOffert::getofferthuvud();
}

void frmChgOffert::getofferthuvud()
{
    /**********************************************************************/
    /*	Hämta kundoffert från offertREG				*/
    /**********************************************************************/
    const char *userp = getenv("USER");
    QString usr(userp);

//    qDebug("frmChgOffert::GetoffertData");
    inrad2="";
    errorrad2="";
    process = new QProcess();
    process->addArgument("./STYRMAN");	// OLFIX styrprogram
    process->addArgument(usr);		// userid
    process->addArgument( "OFFDSP");		// OLFIX funktion
    process->addArgument(offertnr);

    frmChgOffert::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotoffertradDataOnStdout() ) );
    frmChgOffert::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotoffertadDataOnStderr() ) );
    frmChgOffert::connect( process, SIGNAL(processExited() ),this, SLOT(slotofferthuvudEndOfProcess() ) );

    if ( !process->start() ) {
	    // error handling
	    QMessageBox::critical( this, "CHGOFFW",
				  "Kan inte starta STYRMAN/OFFDSP! \n" );
	}

}

void frmChgOffert::slotofferthuvudEndOfProcess()
{
    int i,m;

    i = -1;
    i = errorrad2.find( QRegExp("Error:"), 0 );
 //   qDebug("Error:",errorrad);
         if (i != -1) {
	QMessageBox::critical( this, "CHGOFFW",
		"ERROR!\n"+errorrad2
	);
	errorrad2="";
	i = -1;
     }
     i = -1;

     i = inrad2.find( QRegExp("OK:"), 0 );
     if (i != -1) {
//	 qDebug("inrad=%s",inrad2.latin1());
	 
//	 int i1 = inrad2.find( QRegExp("01:"), 0 );
	 int i2 = inrad2.find( QRegExp("03:"), 0 );	
	 int i3 = inrad2.find( QRegExp("04:"), 0 );
	 int i4 = inrad2.find( QRegExp("05:"), 0 );
	 int i5 = inrad2.find( QRegExp("06:"), 0 );
	 int i6 = inrad2.find( QRegExp("07:"), 0 );
	 int i7 = inrad2.find( QRegExp("08:"), 0 );
	 int i8 = inrad2.find( QRegExp("09:"), 0 );
	 int i9 = inrad2.find( QRegExp("10:"), 0 );
	 int i10 = inrad2.find( QRegExp("11:"), 0 );
	 int i11 = inrad2.find( QRegExp("12:"), 0 );
	 int i12 = inrad2.find( QRegExp("13:"), 0 );
	 int i13 = inrad2.find( QRegExp("14:"), 0 );	
	 int i14 = inrad2.find( QRegExp("15:"), 0 );
	 int i15 = inrad2.find( QRegExp("16:"), 0 );	
	 int i16 = inrad2.find( QRegExp("17:"), 0 );
	 int i17 = inrad2.find( QRegExp("18:"), 0 );
	 int i18 = inrad2.find( QRegExp("19:"), 0 );
	 int i19 = inrad2.find( QRegExp("20:"), 0 );
	 int i20 = inrad2.find( QRegExp("21:"), 0 );
	 int i21 = inrad2.find( QRegExp("22:"), 0 );	
	 int i22 = inrad2.find( QRegExp("23:"), 0 );	
	 int i23 = inrad2.find( QRegExp("24:"), 0 );
	 int i24 = inrad2.find( QRegExp("25:"), 0 );
//	 int i25 = inrad2.find( QRegExp("26:"), 0 );
//	 int i26 = inrad2.find( QRegExp("27:"), 0 );
//	 int i27 = inrad2.find( QRegExp("28:"), 0 );
	 int i28 = inrad2.find( QRegExp("29:"), 0 );
	 int i29 = inrad2.find( QRegExp("30:"), 0 );
	 int i30 = inrad2.find( QRegExp("31:"), 0 );
//	 int i31 = inrad2.find( QRegExp("32:"), 0 );
	 int i32 = inrad2.find( QRegExp("33:"), 0 );
	 int i33 = inrad2.find( QRegExp("34:"), 0 );	
	 int i34 = inrad2.find( QRegExp("35:"), 0 );
	 int i35 = inrad2.find( QRegExp("36:"), 0 );
	 int i36 = inrad2.find( QRegExp("37:"), 0 );
	 int i37 = inrad2.find( QRegExp("END"), 0 );
/*	 int i38 = inrad2.find( QRegExp("39:"), 0 );
	 int i39 = inrad2.find( QRegExp("40:"), 0 );
	 int i40 = inrad2.find( QRegExp("41:"), 0 );
	 int i41 = inrad2.find( QRegExp("42:"), 0 );
	 int i42 = inrad2.length();			*/
/*
	 m=i2-i1;
	 if (i1 != -1){
	     kundid=inrad2.mid(i1+3,m-4);
	     lineEditKundNr->setText(kundid);
	 }
*/
 	 m=i3-i2;
	 if (i2 != -1){
	     offertkundnr=inrad2.mid(i2+3,m-4);
	     lineEditOffertKundNr->setText(offertkundnr);
	 }
/*
	 m=i4-i3;
	 if (i3 != -1){					// offerttyp 
	     offertkundnamn=inrad2.mid(i3+3,m-4);
	     lineEditKundNamn->setText(offertkundnamn);
	 }
*/
/*	 
	 m=i5-i4;					// offertstatus
	 if (i4 != -1){
	     offertstatus=inrad2.mid(i4+3,m-4);
	     lineEditOffertStatus->setText(offertstatus);
	 }
*/
 	 m=i6-i5;
	 if (i5 != -1){					// offertdatum
	     offertdatum=inrad2.mid(i5+3,m-4);
	     textLabelOffertdatum->setText(offertdatum);
	 }

	 m=i7-i6;
	 if (i6 != -1){					// Leveransdatum
	     offertleveranstid=inrad2.mid(i6+3,m-4);
	     lineOffertLeveranstid->setText(offertleveranstid);
	 }

 	 m=i8-i7;
	 if (i7 != -1){					// Kundnamn
	     offertkundnamn=inrad2.mid(i7+3,m-4);
	     lineEditKundNamn->setText(offertkundnamn);
	 }

 	 m=i9-i8;
	 if (i8 != -1){					// Kundadress
	     offertkundadress=inrad2.mid(i8+3,m-4);
	     lineEditKundAdress->setText(offertkundadress);
	 }

	 m=i10-i9;
	 if (i9 != -1){					// Kundpostnummer
	     offertkundpostnr=inrad2.mid(i9+3,m-4);
	     lineEditKundPostnr->setText(offertkundpostnr);
	 }

 	 m=i11-i10;
	 if (i10 != -1){					// Kundpostadress
	     offertkundpostadr=inrad2.mid(i10+3,m-4);
	     lineEditKundPostAdress->setText(offertkundpostadr);
	 }

 	 m=i12-i11;
	 if (i11 != -1){					// Land
	     offertkundland=inrad2.mid(i11+3,m-4);
	     lineEditKundLand->setText(offertkundland);
	 }

 	 m=i13-i12;
	 if (i12 != -1){					// Kundens referens
	     offertkundref=inrad2.mid(i12+3,m-4);
	     lineEditKundRef->setText(offertkundref);
	 }

 	 m=i14-i13;
	 if (i13 != -1){					// Leveransadress
	     offertkundlevadress=inrad2.mid(i13+3,m-4);
	     lineEditKundLevAdress->setText(offertkundlevadress);
	 }

 	 m=i15-i14;
	 if (i14 != -1){					// Leveranspostnr
	     offertkundlevpostnr=inrad2.mid(i14+3,m-4);	
	     lineEditKundLevPostnr->setText(offertkundlevpostnr);
	 }

	 m=i16-i15;
	 if (i15 != -1){					// Leveranspostadress
	    offertkundlevpostadr=inrad2.mid(i15+3,m-4);
	    lineEditKundLevPostAdress->setText(offertkundlevpostadr);
	 }

 	 m=i17-i16;
	 if (i16 != -1){					// Leveransland
	     offertkundlevland=inrad.mid(i16+3,m-5);
	     lineEditKundLevLand->setText(offertkundlevland);
	 }

	 m=i18-i17;
/*	 if (i17 != -1){					// Vår referent
	     offertbetvillkor=inrad2.mid(i17+3,m-4);
	     lineEditBetvilk->setText(offertbetvillkor);
	 }
*/
	 m=i19-i18;
	 if (i18 != -1){					// Seljare
	     seljare=inrad2.mid(i18+3,m-4);
	     lineEditSeljare->setText(seljare);
	 }

	 m=i20-i19;
	 if (i19 != -1){					// Godsmärke
	     godsmarke=inrad2.mid(i19+3,m-4);
	     lineEditGodsmarke->setText(godsmarke);
	 }

	 m=i21-i20;
	 if (i20 != -1){					// Betalningsvillkorstyp
/*	     offertbetvillkortyp=inrad2.mid(i20+3,m-4);
	     lineEditBetvilk->setText(offertbetvillkortyp);
*/	 }

	 m=i22-i21;
	 if (i21 != -1){					// Betalningsvillkor
	     offertbetvillkor=inrad2.mid(i21+3,m-4);
	     lineEditBetvilk->setText(offertbetvillkor);
	 }

	 m=i23-i22;
	 if (i22 != -1){					// Leveransvillkor
	    offertlevvillkor=inrad2.mid(i22+3,m-4);
	    lineEditLevvillkor ->setText(offertlevvillkor);
	 }

	 m=i24-i23;
	 if (i23 != -1){					// Leveransplats /LEVSETT)
	    offertlevplats=inrad2.mid(i23+3,m-4);
	    lineEditLevplats ->setText(offertlevplats);
	 }
/*
	 m=i25-i24;
	 if (i24 != -1){					// Plocklista
	     plocklista=inrad2.mid(i24+3,m-4);
	    lineEditPlocklista ->setText(plocklista);
	 }

	 m=i26-i25;
	 if (i25 != -1){					// Följesedel
	     foljesedel=inrad2.mid(i25+3,m-4);
	    lineEditFoljesedel->setText(foljesedel);
	 }

	 m=i27-i26;
	 if (i26 != -1){					// Fraktavgift	
	     kravbrev=inrad2.mid(i26+3,m-4);
	    lineEditKravbrev ->setText(kravbrev);
	 }

	 m=i28-i27;
	 if (i27 != -1){					// Skattekod
	     sprakkod=inrad2.mid(i27+3,m-4);
	    lineEditSprakkod->setText(sprakkod);
	 }
*/
 	 m=i29-i28;
	 if (i28 != -1){					// Moms i %
	    offertmoms=inrad2.mid(i28+3,m-4);
	    lineEditMomskod->setText(offertmoms);
	 }

	 m=i30-i29;
	 if (i29 != -1){					// Valuta
	    offertvaluta=inrad2.mid(i29+3,m-4);
	    lineEditValuta->setText(offertvaluta);
	 }
/*
	 m=i31-i30;
	 if (i30 != -1){					// Exportkod
	     kreditlimit=inrad2.mid(i30+3,m-4);
	    lineEditKreditlimit->setText(kreditlimit);
	 }

	 m=i32-i31;
	 if (i31 != -1){					//  Språkkod
	     kreditdagar=inrad2.mid(i31+3,m-4);
	    lineEditKreditDagar->setText(kreditdagar);
	 }
*/
	 m=i33-i32;
	 if (i32 != -1){					// offertsumma exklusive moms
	    offertsumma=inrad2.mid(i32+3,m-4);
	    lineEditOffertSumma->setText(offertsumma);
	 }

	 m=i34-i33;
	 if (i33 != -1){					// Fraktavgift i kronor exklusive moms
	    fraktbelopp=inrad2.mid(i33+3,m-4);
	    lineEditOffertFrakt->setText(fraktbelopp);
	 }

 	 m=i35-i34;
	 if (i34 != -1){
	    fraktmomskr=inrad2.mid(i34+3,m-4);		// = Moms i kr på fraktbeloppet
	    lineEditFraktmoms->setText(fraktmomskr);
	 }

 	 m=i36-i35;
	 if (i35 != -1){
	    momssumma=inrad2.mid(i35+3,m-4);		// Total moms på offertn i kronor
	    lineEditOffertMomsKr->setText(momssumma);
	 }

	 m=i37-i36;
	 if (i36 != -1){					// Total offertsumma inklusive moms
	    offerttotal=inrad2.mid(i36+3,m-4);
	    lineEditOffertTotal->setText(offerttotal);
	 }
/*
	 m=i38-i37;
	 if (i37 != -1){
	     drofmalsfakt=inrad2.mid(i37+3,m-4);
	    lineEditDrojFaktura->setText(drofmalsfakt);
	 }

	 m=i39-i38;
	 if (i38 != -1){
	    samfaktura=inrad2.mid(i38+3,m-4);
	    lineEditSamFaktura->setText(samfaktura);
	 }

	 m=i40-i39;
	 if (i39 != -1){
	    kravdatum=inrad2.mid(i39+3,m-4);
	    lineEditKravDatum->setText(kravdatum);
	 }

	 m=i41-i40;
	 if (i40 != -1){
	    skuld=inrad2.mid(i40+3,m-4);
	    lineEditSkuld->setText(skuld);
	 }

	 m=i42-i41;
	 if (i41 != -1){
	    offertstock=inrad2.mid(i41+3,m-4);
	    lineEditoffertstock->setText(offertstock);
	 }
*/
	 inrad2="";
	errorrad2="";
	i = -1;
     }
     pushButtonAvbryt->setFocus();
     frmChgOffert::getoffertrader();
}

void frmChgOffert::getoffertrader()
{
	const char *userp = getenv("USER");
            QString usr(userp);
	 inrad4="";

	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "OFFRDSP");	// OLFIX funktion
	process->addArgument(offertnr );	

	frmChgOffert::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotoffertRadDataOnStdout() ) );
	frmChgOffert::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotoffertRadDataOnStderr() ) );
	frmChgOffert::connect( process, SIGNAL(processExited() ),this, SLOT(slotoffertRaderEndOfProcess() ) );

	if ( !process->start() ) {
                // error handling
	    QMessageBox::warning( this, "Start av OFFRDSP ",
                            "Kan inte starta STYRMAN/OFFRDSP!\n"
                            );
        }
}

void frmChgOffert::slotoffertRaderEndOfProcess()
{
    /*  offertradrad	 */	
//    QString offertradnr="010";    
    QString oldradnr;
    QString radtyp;
    QString offertartikelnr;
    QString prodklass;
    QString offertbenamn;
    QString radleveransvecka;
    QString offertantal;
    QString offertradpris;
    QString radbelopp;
    QString radmoms;		/*  Moms på radbelopp (11) */
    QString levantal;			/* Levererart antal    (12)*/
    QString restantal;		/* Resterande antal   (13)*/
    QString radrabatt;		/*                                   (14)*/
    QString kalkylpris;		/*                                   (15)*/
    QString levdatum;		/* Leveransdatum      (16)*/
    QString enhet;			/* Enhet (st, liter, m)  (17)*/ 
    QString faktantal;		/* Fakturerat antal   (18)*/
//    qDebug("inrad4=%s",inrad4.latin1());
    int i,m,n;
    QString tmp;
    QListViewItem * item;

    i = -1;
    i = errorrad4.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "CHGOFFW",
		"ERROR!\n"+errorrad4
	);
	errorrad4="";
	i = -1;
     }
     i = -1;

     i = inrad4.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	 int p1 = inrad4.find( QRegExp("OK:"), 0 );
	 int p2 = inrad4.find( QRegExp("_:_"), 0 );
	 int n1=(p2)-(p1+3);
	 tmp=inrad4.mid(p1+3,n1);
	 tmp=tmp.stripWhiteSpace();
	 int n2=tmp.toInt();
	 int m1=0;
//	 qDebug("inrad=%s",inrad4.latin1());
//	 qDebug("p1=%d p2=%d n1=%d tmp=%s n2=%d",p1,p2,n1,tmp.latin1(),n2);
	 for (n=1;n<=n2;n++){
	     int i2 = inrad4.find( QRegExp("03_:_"), m1 );		// radnr
	     int i3 = inrad4.find( QRegExp("_:_04_:_"), m1 );	// kundnr
	     int i4 = inrad4.find( QRegExp("_:_05_:_"), m1 );	// radtyp
	     int i5 = inrad4.find( QRegExp("_:_06_:_"), m1 );		// artikelnr
	     int i6 = inrad4.find( QRegExp("_:_07_:_"), m1 );	// benämning
	     int i7 = inrad4.find( QRegExp("_:_08_:_"), m1 );	// leveransvecka
	     int i8 = inrad4.find( QRegExp("_:_09_:_"), m1 );	// antal
	     int i9 = inrad4.find( QRegExp("_:_10_:_"), m1 );	// apris
	     int i10 = inrad4.find( QRegExp("_:_11_:_"), m1 );	// summa rad, belopp exklusive moms
//	     qDebug("i10=%d",i10);
	     int i11 = inrad4.find( QRegExp("_:_12_:_"), m1 );	// Moms i kr
	     int i12 = inrad4.find( QRegExp("_:_13_:"), m1 );	// Levererat antal
	     int i13 = inrad4.find( QRegExp("_:_14_:"), m1 );	// Restnoterat antal
	     int i14 = inrad4.find( QRegExp("_:_15_:"), m1 );	// Radrabatt
	     int i15 = inrad4.find( QRegExp("_:_16_:_"), m1 );	// Kalkylpris
	     int i16 = inrad4.find( QRegExp("_:_17_:_"), m1 );	// Leveransdatum
	     int i17 = inrad4.find( QRegExp("_:_18_:_"), m1 );	// Enhet (st, liter ...)
	     int i18 = inrad4.find(QRegExp("_:_19_:_"),m1 );	// Fakturerat antal
	     int i19 = inrad4.find( QRegExp("_:__:_NEXT_:_"), m1 );
	     m1=m1+i19+10;
	     m=i3 - i2 - 5;
	     oldradnr =inrad4.mid(i2+5,m);
	     oldradnr=oldradnr.stripWhiteSpace();
//	     qDebug("i2=%d I3=%d m=%d  m1=%d",i2,i3,m,m1);
//	     qDebug("oldradnr=%s ",oldradnr.latin1());	     
	     m=(i4-3)-(i3+5);
	     tmp=inrad4.mid(i3+5,m);
//	     qDebug("kundnr=%s ",tmp.latin1());
	     m=i5 - i4 - 8;
	     radtyp=inrad4.mid(i4+8,m);
	     radtyp=radtyp.stripWhiteSpace();
//	     qDebug("radofferttyp=%s ",radtyp.latin1());
	     m=i6 - i5 - 8;
	     offertartikelnr=inrad4.mid(i5+8,m);
	     offertartikelnr=offertartikelnr.stripWhiteSpace();
//	     qDebug("offertartikelnr=%s m=%d",offertartikelnr.latin1(),m);
	     m=i7 - i6 - 8;
	     offertbenamn=inrad4.mid(i6+8,m);
	     offertbenamn=offertbenamn.stripWhiteSpace();
//	     qDebug("benämning=%s",offertbenamn.latin1());
	     m=i8 - i7 - 8;
	     radleveransvecka=inrad4.mid(i7+8,m);
	     radleveransvecka=radleveransvecka.stripWhiteSpace();
//	     qDebug("radleveransvecka=%s",radleveransvecka.latin1());
	     m=i9 - i8 - 8;
	     offertantal=inrad4.mid(i8+8,m);			// antal
	     offertantal=offertantal.stripWhiteSpace();
//	     qDebug("offertantal=%s",offertantal.latin1());
	     m=i10 - i9 - 8;
	     offertradpris=inrad4.mid(i9+8,m);			// apris
	     offertradpris=offertradpris.stripWhiteSpace();
//	     qDebug("offertradpris=%s",offertradpris.latin1());
	     m=i11 - i10 - 8;
	     radbelopp=inrad4.mid(i10 + 8,m);			// summa exklusive moms
	     radbelopp=radbelopp.stripWhiteSpace();
//	     qDebug("radbelopp=%s",radbelopp.latin1());
	     m=i12 - i11 - 8;
	     radmoms=inrad4.mid(i11 + 8,m);			// moms i kronor
	     radmoms=radmoms.stripWhiteSpace();
//	     qDebug("radmoms=%s",radmoms.latin1());
	     m=i13 - i12 - 8;
	     levantal=inrad4.mid(i12 + 8,m);			// levererat antal
	     levantal=levantal.stripWhiteSpace();
//	     qDebug("levererat antal=%s",levantal.latin1());
	     m=i14 - i13 - 8;					// restnoterat
	     restantal=inrad4.mid(i13 + 8,m);	
	     restantal=restantal.stripWhiteSpace();
//	     qDebug("restnoterat antal=%s",restantal.latin1());		
	     m=i15 - i14 - 8;					// radrabatt
	     radrabatt=inrad4.mid(i14 + 8,m);
	     radrabatt=radrabatt.stripWhiteSpace();
//	     qDebug("radrabatt=%s",radrabatt.latin1());		
	     m=i16 - i15 - 8;					// kalkylpris
	     kalkylpris=inrad4.mid(i15 + 8,m);
	     kalkylpris=kalkylpris.stripWhiteSpace();
//	     qDebug("kalkylpris=%s",kalkylpris.latin1());
	     m=i17 - i16 - 8;					// leveransdatum för offertrad
	     levdatum=inrad4.mid(i16 + 8,m);
	     levdatum=levdatum.stripWhiteSpace();
//	     qDebug("leveransdatum=%s",levdatum.latin1());		
	     m=i18 - i17 - 8;					// enhet
	     enhet=inrad4.mid(i17 + 8,m);
	     enhet=enhet.stripWhiteSpace();
//	     qDebug("enhet=%s",enhet.latin1());
	     m=i19 - i18 - 8;					// fakturerat antal
	     faktantal=inrad4.mid(i18 + 8,m);
	     faktantal=faktantal.stripWhiteSpace();
//	     qDebug("fakturerat=%s",faktantal.latin1());
	     
	     item = new QListViewItem(listViewRader,oldradnr,offertartikelnr,offertbenamn,radleveransvecka,offertantal,offertradpris,radbelopp,radmoms);
	     /* Nedanstående avses utnyttjas för att kunna utnyttja REPLACE i MySQL */
	     /* Det sparas  här för att kunna återskrivas i offertRADREG                        */
	     item->setText(8,levantal);
	     item->setText(9,restantal);
	     item->setText(10,radrabatt);
	     item->setText(11,kalkylpris);
	     item->setText(12,levdatum);
	     item->setText(13,enhet);
	     item->setText(14,faktantal);
	     item->setText(15,radtyp);
/*	     QListViewItemIterator it( listViewRader);
	     QString temp7=it.current()->text(14);	
	     qDebug("temp7=%s",temp7.latin1());
*/	     
	     offertradnr=offertradnr.setNum(oldradnr.toInt()+10);
	     offertradnr.prepend("0");
//	     qDebug("oldradnr=%s offertradnr=%s",oldradnr.latin1(),offertradnr.latin1());
	 } 
	 lineEditRadnr->setText(offertradnr);	/* För eventuellt tillägg av ny offertrad */
      }
     pushButtonAvbryt->setFocus();
}

void frmChgOffert::slotoffertRadDataOnStdout()
{
     while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad4.append(line);
	inrad4.append("\n");
    }   
}

void frmChgOffert::slotoffertRadDataOnStderr()
{
      while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad4.append(line);
	errorrad4.append("\n");
    }  
}

