/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
/***************************************************************************
                          DSPKUW  -  description
                             -------------------
		     version 0.3
    begin                : Tors 2 okt  2003
    Modified	         : Ons 12 april 2006
    copyright         : (C) 2003 by Jan Pihlgren
    email                : jan@pihlgren.se
 ***************************************************************************/
/*****************************************************************
 *					                                            *
 *   This program is free software; you can redistribute it and/or modify 	 *
 *   it under the terms of the GNU General Public License as published by       	 *
 *   the Free Software Foundation; either version 2 of the License, or     	 *
 *   (at your option) any later version.                                   		 	 *
 *                                                                         				 *
 *****************************************************************/

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
    QString* rad;
    QString errorrad;
    QString hjelpfil;

    QString kundid;
    QString kundorgnr;
    QString kundnamn;
    QString kundadress;
    QString postnr;
    QString postadr;
    QString land;
    QString tfnnr;
    QString faxnr;
    QString email;
    QString erref;
    QString erreftfnnr;
    QString errefemail;
    QString seljare;
    QString distrikt;
    QString kundkat;
    QString levplats;
    QString levvillkor;
    QString levsett;
    QString betvillkor;
    QString valuta;
    QString sprakkod;
    QString ordererk;
    QString plocklista;
    QString foljesedel;
    QString expavg;
    QString fraktavg;
    QString kravbrev;
    QString kreditlimit;
    QString drojmalsrenta;
    QString drofmalsfakt;
    QString fritext;

    QString kreditdagar;
    QString kreditkod;
    QString exportkod;
    QString skattekod;
    QString rabattkod;
    QString samfaktura;
    QString skuld;
    QString kravdatum;
    QString orderstock;
    QString prislista;

void frmDspKund::init()
{
    lineEditKundNr->setFocus();
}

void frmDspKund::lineEditKundNr_returnPressed()
{
    kundid=lineEditKundNr->text();
    if (kundid == "" ){
    	    QMessageBox::warning( this, "DSPKUW",
                      "KundID måste fyllas i! \n" );
	    lineEditKundNr->setFocus();
    }else{
	    GetKund();
    }
}


void frmDspKund::GetKund()
{
/************************************************************************/
/*	Hämta kunddata							*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);

	process = new QProcess();
	process->addArgument( "./STYRMAN");	// OLFIX funktion
	process->addArgument(usr);
	process->addArgument("KUDSP");
	process->addArgument( kundid);
	frmDspKund::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmDspKund::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
            frmDspKund::connect( process, SIGNAL(processExited() ),this, SLOT(slotGetEndOfProcess() ) );

	if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta DSPKUW!\n");
		QMessageBox::warning( this, "",
                            "Kan inte starta DSPKUW/KUDSP! \n" );
	}
}


void frmDspKund::slotGetEndOfProcess()
{
    int i,m;

    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
 //   qDebug("Error:",errorrad);
         if (i != -1) {
	QMessageBox::critical( this, "DSPKUW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
     }
     i = -1;

     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	 int i1 = inrad.find( QRegExp("01:"), 0 );
	 int i2 = inrad.find( QRegExp("02:"), 0 );
	 int i3 = inrad.find( QRegExp("03:"), 0 );
	 int i4 = inrad.find( QRegExp("04:"), 0 );
	 int i5 = inrad.find( QRegExp("05:"), 0 );
	 int i6 = inrad.find( QRegExp("06:"), 0 );
	 int i7 = inrad.find( QRegExp("07:"), 0 );
	 int i8 = inrad.find( QRegExp("08:"), 0 );
	 int i9 = inrad.find( QRegExp("09:"), 0 );
	 int i10 = inrad.find( QRegExp("10:"), 0 );
	 int i11 = inrad.find( QRegExp("11:"), 0 );
	 int i12 = inrad.find( QRegExp("12:"), 0 );
	 int i13 = inrad.find( QRegExp("13:"), 0 );
	 int i14 = inrad.find( QRegExp("14:"), 0 );
	 int i15 = inrad.find( QRegExp("15:"), 0 );
	 int i16 = inrad.find( QRegExp("16:"), 0 );	// språkkod
	 int i17 = inrad.find( QRegExp("17:"), 0 );	// valuta
	 int i18 = inrad.find( QRegExp("18:"), 0 );
	 int i19 = inrad.find( QRegExp("19:"), 0 );
	 int i20 = inrad.find( QRegExp("20:"), 0 );
	 int i21 = inrad.find( QRegExp("21:"), 0 );
	 int i22 = inrad.find( QRegExp("22:"), 0 );
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
	 int i41 = inrad.find( QRegExp("41:"), 0 );	/* Orderstock */
	 int i42 = inrad.find( QRegExp("42:"), 0 );	/* 20060202 prislista.*/
	 int i43 = inrad.find( QRegExp("END:"), 0 );	/* 20060201 prislista.*/

	 m=i2-i1;
	 if (i1 != -1){
	     kundid=inrad.mid(i1+3,m-4);
	     lineEditKundNr->setText(kundid);
	 }

 	 m=i3-i2;
	 if (i2 != -1){
	     kundorgnr=inrad.mid(i2+3,m-4);
	     lineEditKundOrgnr->setText(kundorgnr);
	 }

	 m=i4-i3;
	 if (i3 != -1){
	     kundnamn=inrad.mid(i3+3,m-4);
	     lineEditKundNamn->setText(kundnamn);
	 }

	 m=i5-i4;
	 if (i4 != -1){
	     kundadress=inrad.mid(i4+3,m-4);
	     lineEditKundAdress->setText(kundadress);
	 }

 	 m=i6-i5;
	 if (i5 != -1){
	     postnr=inrad.mid(i5+3,m-4);
	     lineEditKundPostnr->setText(postnr);
	 }

	 m=i7-i6;
	 if (i6 != -1){
	     postadr=inrad.mid(i6+3,m-4);
	     lineEditKundPostAdress->setText(postadr);
	 }

 	 m=i8-i7;
	 if (i7 != -1){
	     land=inrad.mid(i7+3,m-4);
	     lineEditKundLand->setText(land);
	 }

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

 	 m=i12-i11;
	 if (i11 != -1){
	     erref=inrad.mid(i11+3,m-4);
	     lineEditKundErRef->setText(erref);
	 }

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
	     seljare=inrad.mid(i14+3,m-4);
	     lineEditKundSeljare->setText(seljare);
	 }

	 m=i16-i15;
	 if (i15 != -1){
	    fritext=inrad.mid(i15+3,m-4);
	    lineEditFriText->setText(fritext);
	 }

 	 m=i17-i16;
	 if (i16 != -1){
	     valuta=inrad.mid(i16+3,m-4);
	     lineEditValuta->setText(valuta);
	 }

	 m=i18-i17;
	 if (i17 != -1){
	     betvillkor=inrad.mid(i17+3,m-4);
	     lineEditKundBetvilk->setText(betvillkor);
	 }

	 m=i19-i18;
	 if (i18 != -1){
	     levvillkor=inrad.mid(i18+3,m-4);
	     lineEditKundLevvilk->setText(levvillkor);
	 }

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

	 m=i23-i22;
	 if (i22 != -1){
	    levplats=inrad.mid(i22+3,m-4);
	    lineEditKundStdLevplats ->setText(levplats);
	 }

	 m=i24-i23;
	 if (i23 != -1){
	     ordererk=inrad.mid(i23+3,m-4);
	    lineEditOrdererk ->setText(ordererk);
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

 	 m=i35-i34;
	 if (i34 != -1){
	    skattekod=inrad.mid(i34+3,m-4);
	    lineEditSkattekod->setText(skattekod);
	 }

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
	    orderstock=inrad.mid(i41+3,m-4);
	    lineEditOrderstock->setText(orderstock);
	 }
	 
	 m=i43-i42;				/* 20060202 */
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
     pushButtonOK->setFocus();
}

void frmDspKund::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmDspKund::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
//	qDebug("inrad= %s",inrad.latin1());
    }
}

void frmDspKund::readResursFil()
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

void frmDspKund::pushButtonHelp_clicked()
{
    inrad="";				// töm inputbuffer
    frmDspKund::readResursFil();		// Hämta path till hjälpfilen
    int i1 = hjelpfil.find( QRegExp(".html"), 0 );
    hjelpfil=hjelpfil.left(i1);
    hjelpfil=hjelpfil+"_KUNDORDER.html";
    hjelpfil=hjelpfil+"#KUNDER";		// Lägg till position

    process = new QProcess();
    process->addArgument( "./OLFIXHLP");	// OLFIX funktion
    process->addArgument(hjelpfil);
	
    frmDspKund::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
    frmDspKund::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );	
    frmDspKund::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );	    
 
    if ( !process->start() ) {
	// error handling
    QMessageBox::warning( this, "Start av CHGKUW ", "Kan inte starta OLFIXHLP!\n" );
   }
    lineEditKundNr->setFocus();
}

