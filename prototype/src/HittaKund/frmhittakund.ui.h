/****************************************************************/
/**		SRCHKUW					*/
/**		Söka efter kunder					*/
/**		Ver 0.1                                                                                    */
/**		Created    2005-03-17				*/
/**		Modified: 					*/
/**   Copyright	Jan Pihlgren	jan@pihlgren.se			*/
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
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
#include <qmessagebox.h>
#include <qprocess.h>
#include <qdir.h>
#include <stdlib.h>
#include <qstring.h>
#include <qfile.h>
#include <qregexp.h>
#include <qdatetime.h>
#include <qradiobutton.h>
#define VERSION "0.1"
#define MAXSTRING 5000

    QProcess* process;
    QString inrad;
    QString errorrad;    
    QString soekord;		// Sökbegrepp
//    QString csvflag;
    QString soekordflag="1";
    QString datum;
    
void frmHittaKund::init()
{    
    QDateTime dt = QDateTime::currentDateTime();
    datum=dt.toString("yyyy-MM-dd");
//    textLabelDatum->setText(datum);
    frmHittaKund::listViewKunder_format();
}

void frmHittaKund::lineEditSoekOrd_returnPressed()
{
    listViewKunder->clear();
    soekord=lineEditSoekOrd->text();
    soekord=soekord.upper();
    lineEditSoekOrd->setText(soekord);
    if (soekord==""){
	QMessageBox::warning( this, "SRCHKUW",
                      "Sökord måste fyllas i! \n" );
	lineEditSoekOrd->setFocus();
    }else{  
	pushButtonOK->setFocus();
    }   
}

void frmHittaKund::radioButton1_toggled( bool )
{
    soekordflag="1";	/* Sökja på kundnamn */
    lineEditSoekOrd->setFocus();
}

void frmHittaKund::radioButton2_toggled( bool )
{
    soekordflag="2";	/* Sökja på postnummer*/
    lineEditSoekOrd->setFocus();
}

void frmHittaKund::radioButton3_toggled( bool )
{
    soekordflag="3";	/* Sökja på  postadress  */
    lineEditSoekOrd->setFocus();
}

void frmHittaKund::radioButton4_toggled( bool )
{
    soekordflag="4";	/* Sökja på  telefonnummer */
    lineEditSoekOrd->setFocus();
}

void frmHittaKund::slotpushButtonOK_clicked()
{
//    qDebug("soekord=%s  soekordflag=%s",soekord.latin1(),soekordflag.latin1());
    /* Här ska start av sökningen göras */    
    /* Gå till getData() */ 
    frmHittaKund::slotGetData();
    pushButtonAvbryt->setFocus();
}

void frmHittaKund::slotGetData()
{
	const char *userp = getenv("USER");
            QString usr(userp);

	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "KUSRCH");	// OLFIX funktion
	process->addArgument(soekordflag);	// sökbegrepp, sökning på, 1=namn, 2=postnummer, 3=telefonnummer, 4=postadress
	process->addArgument(soekord);		// sökord

	frmHittaKund::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmHittaKund::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
            frmHittaKund::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );


	if (soekord == "" ){
    	    QMessageBox::warning( this, "SRCHKUW",
                      "Sökordet måste vara ifyllt!" );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		QMessageBox::warning( this, "SRCHKUW",
                            "Kan inte starta STYRMAN/KUSRCH! \n" );
	    }
	}
}

void frmHittaKund::slotEndOfProcess()
{
    QListViewItem* item;
    int i,flag;
    flag=soekordflag.toInt();
    listViewKunder->setSorting(flag,TRUE);
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "SRCHKUWW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
     }
    i = inrad.find( QRegExp("OK: NR_0_"), 0 );
    if (i != -1) {
	QMessageBox::information( this, "SRCHKUW",
		"Kundregistret innehåller inga poster!\n"
	);
	i = -1;
    }
    QString listrad;
//    rad=&inrad;
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
    char postnr[7]="";
    char postadr[31]="";
    char tfnnr[16]="";	    

    tmppek=tmp;
    qstrcpy(tmp,inrad);
    pos1=strstr(tmp,"OK: NR_");	// 7 tecken långt
    pos2=strstr(tmp,"_:");
    i=pos2-pos1;
    m=i+2;		// startposition för första post
//    qDebug("i=%d  m=%d",i,m);
    k=0;
    for (j=7;j<i;j++){	// j = första positionen för antal poster,(OK: NR_4_:4377_:Kund AB_:4379_:Småkund AB_:4378_:Storkund AB_:4376_:Test AB_:)
	antrad[k]=tmp[j];
	k++;
    };
    i=atoi(antrad);		// i = antal poster
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
	l=0;
	for(j = m; j < sizeof(postnr) + m; j++){
	    if(tmp[j] != *("_")){
		postnr[l]=tmp[j];
		l++;
	    }else{
		postnr[l] = *("\0");
		j=sizeof(postnr) + m;
	    }
	}
//	qDebug("%s  ",postnr);
	m=m+l+2;
	l=0;
	for(j = m; j < sizeof(postadr) + m; j++){
	    if(tmp[j] != *("_")){
		postadr[l]=tmp[j];
		l++;
	    }else{
		postadr[l] = *("\0");
		j=sizeof(postadr) + m;
	    }
	}
//	qDebug("%s  ",postadr);
	m=m+l+2;
	l=0;
	for(j = m; j < sizeof(tfnnr) + m; j++){
	    if(tmp[j] != *("_")){
		tfnnr[l]=tmp[j];
		l++;
	    }else{
		tfnnr[l] = *("\0");
		j=sizeof(tfnnr) + m;
	    }
	}
//	qDebug("%s  ",tfnnr);
	m=m+l+2;	
	item = new QListViewItem(listViewKunder,kundnr,namn,postnr,postadr,tfnnr);
	
  	for (l=0;l<sizeof(kundnr);l++)
		kundnr[l]=*("\0");
	for (l=0;l<sizeof(namn);l++)
		namn[l]=*("\0");
	for (l=0;l<sizeof(postnr);l++)
		postnr[l]=*("\0");
	for (l=0;l<sizeof(postadr);l++)
		postadr[l]=*("\0");
	for (l=0;l<sizeof(tfnnr);l++)
		tfnnr[l]=*("\0");	
//	 rensa listrad
	listrad.remove(0,80);
	inrad="";
	errorrad="";
	soekord="";
	soekordflag="";
    }
}

QString frmHittaKund::CheckDatum( QString datumet )
{
    /*      Kontrollera och formatera datum enligt 20ÅÅ-MM-DD */
    int i;
    int j,k;
    QString tempdatum;
    QString millenium;
//    QString tmp;

    i = datumet.length();
    k = datumet.find( QRegExp("-"), 0 );
    j = datumet.find( QRegExp("-"), k+1 );
    millenium=datum.mid(0,2);

//    qDebug("millenium=%s, datumet=%s, datumetlängd=%d, datumet 1:a - =%d, datumet 2:a - %d",millenium.latin1(),datumet.latin1(),i,k,j);

    tempdatum=datumet;
    if (i < 7 && k < 0 && j < 0){
	tempdatum = millenium+datumet.mid(0,2)+"-"+datumet.mid(2,2)+"-"+datumet.mid(4,2);
    }
    if (i == 7 && k < 0 && j < 0){
	tempdatum = millenium+datumet.mid(1,2)+"-"+datumet.mid(3,2)+"-"+datumet.mid(5,2);
    }
    if (i == 8 && k < 0 && j < 0){
	tempdatum = millenium+datumet.mid(2,2)+"-"+datumet.mid(4,2)+"-"+datumet.mid(6,2);
    }
    if (i == 9 && k < 0 && j < 0){
	tempdatum = millenium+datumet.mid(3,2)+"-"+datumet.mid(5,2)+"-"+datumet.mid(7,2);
    }
    if (i < 10 && k > 0 ){
	if (k > 0 && k <5){
	    if ( j < 0){
		tempdatum =datumet.mid(0,k+1)+datumet.mid(k+1,2)+"-"+datumet.mid(k+3,2);
	    }
	    if (j > 0){
		tempdatum ="20"+datumet.mid(0,k+1)+datumet.mid(k+1,2)+datumet.mid(j,3);
	    }
	}
	if (k > 4 && k <7){
	    if ( j < 0){
		tempdatum =datumet.mid(0,4)+"-"+datumet.mid(4,2)+"-"+datumet.mid(k+1,2);
	    }
	    if (j > 0){
		tempdatum =datumet.mid(0,4)+"-"+datumet.mid(4,2)+datumet.mid(j,3);
	    }
	}
    }
//    qDebug("tempdatum=%s, ",tempdatum.latin1());
        return tempdatum;
}

void frmHittaKund::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmHittaKund::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmHittaKund::listViewKunder_format()
{
    listViewKunder->setColumnWidth(0,55);		// Kundnr
    listViewKunder->setColumnWidth(1,180);	// Kundnamn
    listViewKunder->setColumnWidth(2,55);		// Postnummer
    listViewKunder->setColumnWidth(3,180);	// Postadress (Ort)
    listViewKunder->setColumnWidth(4,55);		// Telefonnummer
}

