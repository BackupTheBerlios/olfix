/****************************************************************/
/**		ADDFTGW					*/
/**		2003-08-15					*/
/**		Version: 0.1					*/
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
//    QString ptyp;	/* posttyp */


    QString ftgnamn;
    QString ftgnr;
    QString postadr;
    QString postnr1;
    QString postort;
    QString besoksadr;
    QString postnr2;
    QString besoksort;
    QString godsadr;
    QString postnr3;
    QString godsort;
    QString tfnnr;
    QString mobiltfnnr;
    QString telefax;
    QString email;
    QString telex;
    QString moms1;
    QString moms2;
    QString moms3;
    QString moms4;
    QString moms5;
    QString momsin;
    QString momsut;
    QString autokonto;	// automatkontering J/N

void frmAddFtgData::init()
{
    slotGetFtgdata();
    LineEditFtgNamn->setFocus();
}

void frmAddFtgData::slotLineEditFtgNamn_returnPressed()
{
    ftgnamn = LineEditFtgNamn->text();
    LineEditFtgNr->setFocus();
}

void frmAddFtgData::slotLineEditFtgNr_returnPressed()
{
    ftgnr = LineEditFtgNr->text();
    LineEditPostAdress->setFocus();
}

void frmAddFtgData::slotLineEditPostAdress_returnPressed()
{
    postadr = LineEditPostAdress->text();
    LineEditPostnr1->setFocus();
}

void frmAddFtgData::slotLineEditPostnr1_returnPressed()
{
    postnr1 = LineEditPostnr1->text();
    LineEditPostOrt->setFocus();
}

void frmAddFtgData::slotLineEditPostOrt_returnPressed()
{
    postort = LineEditPostOrt->text();
    LineEditBesoksAdress->setFocus();
}

void frmAddFtgData::slotLineEditBesoksAdress_returnPressed()
{
    besoksadr = LineEditBesoksAdress->text();
    LineEditPostnr2->setFocus();
}

void frmAddFtgData::slotLineEditPostnr2_returnPressed()
{
    postnr2 = LineEditPostnr2->text();
    LineEditBesoksOrt->setFocus();
}

void frmAddFtgData::slotLineEditBesoksOrt_returnPressed()
{
    besoksort = LineEditBesoksOrt->text();
    LineEditGodsAdress->setFocus();
}

void frmAddFtgData::slotLineEditGodsAdress_returnPressed()
{
    godsadr = LineEditGodsAdress->text();
    LineEditPostnr3->setFocus();
}

void frmAddFtgData::slotLineEditPostnr3_returnPressed()
{
    postnr3 = LineEditPostnr3->text();
    LineEditGodsOrt->setFocus();
}

void frmAddFtgData::slotLineEditGodsOrt_returnPressed()
{
    godsort = LineEditGodsOrt->text();
    LineEditTfnnr->setFocus();
}

void frmAddFtgData::slotLineEditTfnnr_returnPressed()
{
    tfnnr = LineEditTfnnr->text();
    LineEditMobilTfn->setFocus();
}

void frmAddFtgData::slotLineEditMobilTfn_returnPressed()
{
    mobiltfnnr = LineEditMobilTfn->text();
    LineEditTelefax->setFocus();
}

void frmAddFtgData::slotLineEditTelefax_returnPressed()
{
    telefax = LineEditTelefax->text();
    LineEditemailadress->setFocus();
}

void frmAddFtgData::slotLineEditemailadress_returnPressed()
{
    email = LineEditemailadress->text();
    LineEditTelex->setFocus();
}

void frmAddFtgData::slotLineEditTelex_returnPressed()
{
    telex = LineEditTelex->text();
    LineEditMoms1->setFocus();
}

void frmAddFtgData::slotLineEditMoms1_returnPressed()
{
    moms1 = LineEditMoms1->text();
    LineEditMoms2->setFocus();
}

void frmAddFtgData::slotLineEditMoms2_returnPresse()
{
    moms2 = LineEditMoms2->text();
    LineEditMoms3->setFocus();
}

void frmAddFtgData::slotLineEditMoms3_returnPressed()
{
    moms3 = LineEditMoms3->text();
    LineEditMoms4->setFocus();
}

void frmAddFtgData::slotLineEditMoms4_returnPressed()
{
    moms4 = LineEditMoms4->text();
    LineEditMoms5->setFocus();
}

void frmAddFtgData::slotLineEditMoms5_returnPressed()
{
    moms5 = LineEditMoms5->text();
    lineEditMomsKtoIng->setFocus();
}

void frmAddFtgData::slotlineEditMomsKtoIng_returnPressed()
{
    momsin = lineEditMomsKtoIng->text();
    lineEditMomsKtoUtg->setFocus();
}

void frmAddFtgData::slotlineEditMomsKtoUtg_returnPressed()
{
    momsut = lineEditMomsKtoUtg->text();
    lineEditAutokonto->setFocus();
}

void frmAddFtgData::slotlineEditAutokonto_returnPressed()
{
    autokonto = lineEditAutokonto->text();
    autokonto=autokonto.upper();
    lineEditAutokonto->setText((autokonto));
    PushButtonOK->setFocus();
}

void frmAddFtgData::slotPushButtonOK_clicked()
{
    slotUpdateFtgdata("FNAMN",ftgnamn);
    slotUpdateFtgdata("FTGNR",ftgnr);
    slotUpdateFtgdata("ADR1",postadr);
    slotUpdateFtgdata("ADR2",postnr1);
    slotUpdateFtgdata("ADR3",postort);
    slotUpdateFtgdata("ADR4",besoksadr);
    slotUpdateFtgdata("ADR5",postnr2);
    slotUpdateFtgdata("ADR6",besoksort);
    slotUpdateFtgdata("ADR7",godsadr);
    slotUpdateFtgdata("ADR8",postnr3);
    slotUpdateFtgdata("ADR9",godsort);
    
    slotUpdateFtgdata("TFN1",tfnnr);
    slotUpdateFtgdata("TFN2",mobiltfnnr);
    
    slotUpdateFtgdata("TFAX",telefax);
    slotUpdateFtgdata("TELEX",telex);
    slotUpdateFtgdata("EML1",email);
    
    slotUpdateFtgdata("MOMS1",moms1);
    slotUpdateFtgdata("MOMS2",moms2);
    slotUpdateFtgdata("MOMS3",moms3);
    slotUpdateFtgdata("MOMS4",moms4);
    slotUpdateFtgdata("MOMS5",moms5);
    slotUpdateFtgdata("MOMSI",momsin);		// momkonto ingående moms
    slotUpdateFtgdata("MOMSU",momsut);		// momskonto utgående moms
    slotUpdateFtgdata("AUTOK",autokonto);		// automatisk kontering J/N

}

void frmAddFtgData::slotUpdateFtgdata(QString posttyp, QString ftgdata)
{
	const char *userp = getenv("USER");
            QString usr(userp);

	inrad="";
	errorrad="";
	
//            qDebug("slotUpdateFtgdata::posttyp=%s ftgdata=%s",posttyp.latin1(),ftgdata.latin1());
	    
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "FTGUPD");	// OLFIX funktion
	process->addArgument(posttyp);
	process->addArgument(ftgdata);

	frmAddFtgData::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmAddFtgData::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmAddFtgData::connect( process, SIGNAL(processExited() ),this, SLOT(slotUpdateEndOfProcess() ) );
	if (posttyp == "" ){
    	    QMessageBox::warning( this, "ADDFTGW",
                      "Posttyp saknas! \n" );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/FTGUPD!\n");
		QMessageBox::warning( this, "ADDFTGW",
                            "Kan inte starta STYRMAN/FTGUPD! \n" );
	    }
	}
}

void frmAddFtgData::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmAddFtgData::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}


void frmAddFtgData::slotUpdateEndOfProcess()
{
    int i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i == 0) {
	QMessageBox::critical( this, "OLFIX - FTGUPD",
		"ERROR!\n"+errorrad
	);
	errorrad="";
    }
    else{
	i = -1;
	i = inrad.find( QRegExp("OK:"), 0 );
	if (i != -1) {
	    QMessageBox::information( this, "ADDFTGW",
		"Uppdatering OK!\n"
		);
	    inrad="";
	    errorrad="";
	}    
    }
}

void frmAddFtgData::slotGetFtgdata()
{
	const char *userp = getenv("USER");
            QString usr(userp);

	inrad="";
	errorrad="";
	
//            qDebug("slotGetFtgdata::FTGLST");
	    
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "FTGLIS");	// OLFIX funktion

	frmAddFtgData::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmAddFtgData::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmAddFtgData::connect( process, SIGNAL(processExited() ),this, SLOT(slotGetEndOfProcess() ) );
            if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/FTGLIS!\n");
		QMessageBox::warning( this, "ADDFTGW",
                            "Kan inte starta STYRMAN/FTGLIS! \n" );
	 }
}


void frmAddFtgData::slotGetEndOfProcess()
{
    int i,j,m;
//   qDebug("slotGetEndOfProcess::inrad=%s",inrad.latin1());
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i == 0) {
	QMessageBox::critical( this, "OLFIX - FTGLIS",
		"ERROR!\n"+errorrad
	);
	errorrad="";
    }
    else{
	i = -1;
	i = inrad.find( QRegExp("OK:"), 0 );
	if (i != -1) {
	    i=-1;
	    i = inrad.find( QRegExp("FNAMN_:"), 0 );
	    if (i != -1) {
		j = inrad.find( QRegExp("_:"), i+7 );
		m = j  - (i + 7);
		ftgnamn = inrad.mid(i+7,m);
		LineEditFtgNamn->setText((ftgnamn));
	    }
 	    i=-1;
	    i = inrad.find( QRegExp("FTGNR_:"), 0 );
	    if (i != -1) {
		j = inrad.find( QRegExp("_:"), i+7 );
		m = j - (i + 7);
		ftgnr = inrad.mid(i+7,m);
		LineEditFtgNr->setText((ftgnr));
	    } 	    
	    i=-1;
	    i = inrad.find( QRegExp("ADR1_:"), 0 );
	    if (i != -1) {
		j = inrad.find( QRegExp("_:"), i+7 );
		m = j - (i + 6);
		postadr = inrad.mid(i+6,m);
		LineEditPostAdress->setText((postadr));
	    }
    	    i=-1;
	    i = inrad.find( QRegExp("ADR2_:"), 0 );
	    if (i != -1) {
		j = inrad.find( QRegExp("_:"), i+7 );
		m = j - (i + 6);
		postnr1 = inrad.mid(i+6,m);
		LineEditPostnr1->setText((postnr1));
	    }
    	    i=-1;
	    i = inrad.find( QRegExp("ADR3_:"), 0 );
	    if (i != -1) {
		j = inrad.find( QRegExp("_:"), i+7 );
		m = j - (i + 6);
		postort = inrad.mid(i+6,m);
		LineEditPostOrt->setText((postort));
	    }
    	    i=-1;
	    i = inrad.find( QRegExp("ADR4_:"), 0 );
	    if (i != -1) {
		j = inrad.find( QRegExp("_:"), i+7 );
		m = j - (i + 6);
		besoksadr = inrad.mid(i+6,m);
		LineEditBesoksAdress->setText((besoksadr));
	    }
    	    i=-1;
	    i = inrad.find( QRegExp("ADR5_:"), 0 );
	    if (i != -1) {
		j = inrad.find( QRegExp("_:"), i+7 );
		m = j - (i + 6);
		postnr2 = inrad.mid(i+6,m);
		LineEditPostnr2->setText((postnr2));
	    }
    	    i=-1;
	    i = inrad.find( QRegExp("ADR6_:"), 0 );
	    if (i != -1) {
		j = inrad.find( QRegExp("_:"), i+7 );
		m = j - (i + 6);
		besoksort = inrad.mid(i+6,m);
		LineEditBesoksOrt->setText((besoksort));
	    }
    	    i=-1;
	    i = inrad.find( QRegExp("ADR7_:"), 0 );
	    if (i != -1) {
		j = inrad.find( QRegExp("_:"), i+7 );
		m = j - (i + 6);
		godsadr = inrad.mid(i+6,m);
		LineEditGodsAdress->setText((godsadr));
	    }
    	    i=-1;
	    i = inrad.find( QRegExp("ADR8_:"), 0 );
	    if (i != -1) {
		j = inrad.find( QRegExp("_:"), i+7 );
		m = j - (i + 6);
		postnr3 = inrad.mid(i+6,m);
		LineEditPostnr3->setText((postnr3));
	    }
    	    i=-1;
	    i = inrad.find( QRegExp("ADR9_:"), 0 );
	    if (i != -1) {
		j = inrad.find( QRegExp("_:"), i+7 );
		m = j - (i + 6);
		godsort = inrad.mid(i+6,m);
		LineEditGodsOrt->setText((godsort));
	    }
    	    i=-1;
	    i = inrad.find( QRegExp("TFN1_:"), 0 );
	    if (i != -1) {
		j = inrad.find( QRegExp("_:"), i+7 );
		m = j - (i + 6);
		tfnnr = inrad.mid(i+6,m);
		LineEditTfnnr->setText((tfnnr));
	    }
	    i = inrad.find( QRegExp("TFN2_:"), 0 );
	    if (i != -1) {
		j = inrad.find( QRegExp("_:"), i+7 );
		m = j - (i + 6);
		mobiltfnnr = inrad.mid(i+6,m);
		LineEditMobilTfn->setText((mobiltfnnr));
	    }
	    i = inrad.find( QRegExp("TFAX_:"), 0 );
	    if (i != -1) {
		j = inrad.find( QRegExp("_:"), i+7 );
		m = j - (i + 6);
		telefax = inrad.mid(i+6,m);
		LineEditTelefax->setText((telefax));
	    }
	    i = inrad.find( QRegExp("EML1_:"), 0 );
	    if (i != -1) {
		j = inrad.find( QRegExp("_:"), i+7 );
		m = j - (i + 6);
		email = inrad.mid(i+6,m);
		LineEditemailadress->setText((email));
	    }
	    i = inrad.find( QRegExp("TELEX_:"), 0 );
	    if (i != -1) {
		j = inrad.find( QRegExp("_:"), i+7 );
		m = j - (i + 7);
		telex = inrad.mid(i+7,m);
		LineEditTelex->setText((telex));
	    }
	    i = inrad.find( QRegExp("MOMS1_:"), 0 );
	    if (i != -1) {
		j = inrad.find( QRegExp("_:"), i+7 );
		m = j - (i + 7);
		moms1 = inrad.mid(i+7,m);
		LineEditMoms1->setText((moms1));
	    }
	    i = inrad.find( QRegExp("MOMS2_:"), 0 );
	    if (i != -1) {
		j = inrad.find( QRegExp("_:"), i+7 );
		m = j - (i + 7);
		moms2 = inrad.mid(i+7,m);
		LineEditMoms2->setText((moms2));
	    }
	    i = inrad.find( QRegExp("MOMS3_:"), 0 );
	    if (i != -1) {
		j = inrad.find( QRegExp("_:"), i+7 );
		m = j - (i + 7);
		moms3 = inrad.mid(i+7,m);
		LineEditMoms3->setText((moms3));
	    }
	    i = inrad.find( QRegExp("MOMS4_:"), 0 );
	    if (i != -1) {
		j = inrad.find( QRegExp("_:"), i+7 );
		m = j - (i + 7);
		moms4 = inrad.mid(i+7,m);
		LineEditMoms4->setText((moms4));
	    }
	    i = inrad.find( QRegExp("MOMS5_:"), 0 );
	    if (i != -1) {
		j = inrad.find( QRegExp("_:"), i+7 );
		m = j - (i + 7);
		moms5 = inrad.mid(i+7,m);
		LineEditMoms5->setText((moms5));
	    }
	    i = inrad.find( QRegExp("MOMSI_:"), 0 );
	    if (i != -1) {
		j = inrad.find( QRegExp("_:"), i+7 );
		m = j - (i + 7);
		momsin = inrad.mid(i+7,m);
		lineEditMomsKtoIng->setText((momsin));
	    }
	    i = inrad.find( QRegExp("MOMSU_:"), 0 );
	    if (i != -1) {
		j = inrad.find( QRegExp("_:"), i+7 );
		m = j - (i + 7);
		momsut = inrad.mid(i+7,m);
		lineEditMomsKtoUtg->setText((momsut));
	    }
	    i = inrad.find( QRegExp("AUTOK_:"), 0 );
	    if (i != -1) {
		j = inrad.find( QRegExp("_:"), i+7 );
		m = j - (i + 7);
		autokonto = inrad.mid(i+7,m);
		lineEditAutokonto->setText((autokonto));
	    }	    
	    inrad="";
	    errorrad="";
	}    
    }
}
