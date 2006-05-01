/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
/***************************************************************************
                          ADDLEVPW  -  description
                             -------------------
		     version 0.4.3
    begin                : Sön   7 aug 2003
    Modified         : Mån  1 maj 2006
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
 *****************************************************************/

#include <qmessagebox.h>
#include <qprocess.h>
#include <qdir.h>
#include <stdlib.h>
#include <qstring.h>
#include <qfile.h>
#include <qregexp.h>
#include <qvalidator.h> 		// 2003-10-21
#define MAXSTRING 5000


    QProcess* process;
    QString inrad;
    QString* rad;
    QString errorrad;

    QString kundid;
    QString levplatsnr;
    QString levadress;
    QString postnr;
    QString postadr;
    QString land;

    QRegExp rx1( "[A-Za-z0-9ÅÄÖåäö]\\w{1,9}" );        
    QRegExp rx2( "[0-9]\\d{2}" );
    QRegExp rx3( "[A-Za-z0-9ÅÄÖåäö ]{1,29}" );    
    QRegExp rx4( "[1-9]\\d{4}" );
    QRegExp rx14("[A-Za-z0-9 ]{1,10}");		// 2003-10-21
    
    QRegExpValidator validator1( rx1, 0 );
    QRegExpValidator validator2( rx2, 0 );
    QRegExpValidator validator3( rx3, 0 );    
    QRegExpValidator validator4( rx4, 0 );
    QRegExpValidator validator14( rx14, 0 );	// 2003-10-21

    
void frmAddLevplats::init()
{
    lineEditKundID->setValidator(&validator1);
    lineEditLevPlatsNr->setValidator(&validator2);
    lineEditLevAdress->setValidator(&validator3);
    lineEditPostnr->setValidator(&validator14);
    lineEditPostAdress->setValidator(&validator3);
    lineEditLand->setValidator(&validator3);

    
    lineEditKundID->setFocus();
    if (kundid==NULL){
	lineEditLevPlatsNr->setText("");
    }
//     qDebug("lineEditKundID::kundid=%s",kundid.latin1());    
}

void frmAddLevplats::lineEditKundID_returnPressed()
{
    kundid=lineEditKundID->text();
//    lineEditLevPlatsNr->setFocus();
}

void frmAddLevplats::lineEditLevPlatsNr_returnPressed()
{
    levplatsnr=lineEditLevPlatsNr->text();
//    lineEditLevAdress->setFocus();
}

void frmAddLevplats::lineEditLevAdress_returnPressed()
{
    levadress=lineEditLevAdress->text();
//    lineEditPostnr->setFocus();
}

void frmAddLevplats::lineEditPostnr_returnPressed()
{
//    QString temp;
    postnr=lineEditPostnr->text();
//    temp=postnr.mid(0,3);
//    temp.append(" ");
//    temp.append(postnr.mid(3,2));
//    postnr=temp;
//	qDebug("postnr=%s\n",postnr.latin1());
//    lineEditPostnr->setText(postnr);
}

void frmAddLevplats::lineEditPostAdress_returnPressed()
{
    postadr=lineEditPostAdress->text();
//    lineEditLand->setFocus();
}

void frmAddLevplats::lineEditLand_returnPressed()
{
    land=lineEditLand->text();
    if (land==""){
	land="-";
            lineEditLand->setText(land);
    }
    pushButtonOK->setFocus();
}

void frmAddLevplats::pushButtonOK_clicked()
{
    int status=0;
    if (kundid == "" ){
	QMessageBox::warning( this, "ADDLEVPW","KundID måste fyllas i! \n" );
	status=-1;
	lineEditKundID->setFocus();
    }
    if (levplatsnr == "" ){
    	    QMessageBox::warning( this, "ADDLEVPW", "Platsnummer måste fyllas i! \n" );
	    status=-1;
	    lineEditLevPlatsNr->setFocus();
   }
   if (levadress == "" ){
    	    QMessageBox::warning( this, "ADDLEVPW", "Leveransadress måste fyllas i! \n" );
	    status=-1;
	    lineEditLevAdress->setFocus();
   }
   if (postnr == "" ){
    	    QMessageBox::warning( this, "ADDLEVPW", "Postnummer måste fyllas i! \n" );
	    status=-1;
	    lineEditPostnr->setFocus();
  }    
  if (postadr == "" ){
    	    QMessageBox::warning( this, "ADDLEVPW", "Postadressen måste fyllas i! \n" );
	    status=-1;
	    lineEditPostAdress->setFocus();
  }    
  if (status==0){
//    qDebug("pushButtonOK_clicked::kundid=%s",kundid.latin1());
      AddStandardLevPlats();
  }
}

void frmAddLevplats::AddStandardLevPlats()
{
/**************************************************************************/
/*	Skapa leveransplats 001, den första leveransadressen för en kund.	           	 */
/**************************************************************************/
	const char *userp = getenv("USER");
	QString usr(userp);
	 
	if (land==""){
	    land="-";
	}    
	    
	process = new QProcess();
	process->addArgument( "./STYRMAN");	// OLFIX funktion
	process->addArgument(usr);
	process->addArgument("SLPADD");	
	process->addArgument(kundid);
	process->addArgument(levplatsnr);
	process->addArgument(levadress);
	process->addArgument(postnr);
	process->addArgument(postadr);
	process->addArgument(land);
	frmAddLevplats::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmAddLevplats::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
            frmAddLevplats::connect( process, SIGNAL(processExited() ),this, SLOT(slotPlatsEndOfProcess() ) );

	if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta ADDLEVPW!\n");
		QMessageBox::warning( this, "",
                            "Kan inte starta STYRMAN/SLPADD! \n" );
	}
}

void frmAddLevplats::slotPlatsEndOfProcess()
{
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "ADDLEVPW",
		"ERROR!\n"+errorrad
	);
     }
     i = -1;
     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	QMessageBox::information( this, "ADDLEVPW",
		"Uppdatering OK!\n"+errorrad
	);
	lineEditKundID->clear();
	lineEditLevPlatsNr->clear();
	lineEditLevAdress->clear();
	lineEditPostnr->clear();
	lineEditPostAdress->clear();
	lineEditLand->clear();
	fprintf(stdout,"OK: \n ");
    }
     errorrad="";
     inrad="";
     lineEditKundID->setFocus();
}

void frmAddLevplats::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
    qDebug("inrad=%s",inrad.latin1());
}
 
void frmAddLevplats::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}
