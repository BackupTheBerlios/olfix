/****************************************************************/
/**		ADDFTGW					*/
/**		2003-08-15				*/
/**		Version: 0.46				*/
/**		Modifierad: 2006-05-01			*/
/**			2006-12-15			*/
/**			2007-01-31			*/
/**			2007-02-25--27			*/
/**		Jan Pihlgren	jan@pihlgren.se		*/
/****************************************************************/
/*****************************************************************
 *					                                            *
 *   This program is free software; you can redistribute it and/or modify 	 *
 *   it under the terms of the GNU General Public License as published by       	 *
 *   the Free Software Foundation; either version 2 of the License, or     	 *
 *   (at your option) any later version.                                   		 	 *
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

    int processnr=1;			// 2007-01-31
    QProcess* process[50];		// 2007-01-31
    QProcess* proc;
    QString inrad;
    QString errorrad;
    QString* rad;
//    QString ptyp;	/* posttyp */
    QString hjelpfil;			// 2007-01-31

    QString ftgnamn;
    QString ftgnr;
    QString snikd;
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
    QString momsnr;		// 2006-05-01
    QString moms1;
    QString moms2;
    QString moms3;
    QString moms4;
    QString moms5;
    QString momsin;
    QString momsut;
    QString autokonto;	// automatkontering J/N
    QString bgnr;		// 2006-05-01
    QString pgnr;		// 2006-05-01

void frmAddFtgData::init()
{
    processnr=1;
    slotGetFtgdata();			// 2007-02-27
//    pushButtonQuit->setFocus();    
    LineEditFtgNamn->setFocus();	// 2007-02-25
}

void frmAddFtgData::slotLineEditFtgNamn_returnPressed()
{
    ftgnamn = LineEditFtgNamn->text();
}

void frmAddFtgData::slotLineEditFtgNr_returnPressed()
{
    ftgnr = LineEditFtgNr->text();
}

void frmAddFtgData::slotLineEditBranschkod_returnPressed()
{
    snikd = LineEditBranschkod->text();
}

void frmAddFtgData::slotLineEditPostAdress_returnPressed()
{
    postadr = LineEditPostAdress->text();
}

void frmAddFtgData::slotLineEditPostnr1_returnPressed()
{
    postnr1 = LineEditPostnr1->text();
}

void frmAddFtgData::slotLineEditPostOrt_returnPressed()
{
    postort = LineEditPostOrt->text();
}

void frmAddFtgData::slotLineEditBesoksAdress_returnPressed()
{
    besoksadr = LineEditBesoksAdress->text();
}

void frmAddFtgData::slotLineEditPostnr2_returnPressed()
{
    postnr2 = LineEditPostnr2->text();
}

void frmAddFtgData::slotLineEditBesoksOrt_returnPressed()
{
    besoksort = LineEditBesoksOrt->text();
}

void frmAddFtgData::slotLineEditGodsAdress_returnPressed()
{
    godsadr = LineEditGodsAdress->text();
}

void frmAddFtgData::slotLineEditPostnr3_returnPressed()
{
    postnr3 = LineEditPostnr3->text();
}

void frmAddFtgData::slotLineEditGodsOrt_returnPressed()
{
    godsort = LineEditGodsOrt->text();
}

void frmAddFtgData::slotLineEditTfnnr_returnPressed()
{
    tfnnr = LineEditTfnnr->text();
}

void frmAddFtgData::slotLineEditMobilTfn_returnPressed()
{
    mobiltfnnr = LineEditMobilTfn->text();
}

void frmAddFtgData::slotLineEditTelefax_returnPressed()
{
    telefax = LineEditTelefax->text();
}

void frmAddFtgData::slotLineEditemailadress_returnPressed()
{
    email = LineEditemailadress->text();
}

void frmAddFtgData::slotLineEditTelex_returnPressed()
{
    telex = LineEditTelex->text();
}

void frmAddFtgData::slotLineEditMoms1_returnPressed()
{
    moms1 = LineEditMoms1->text();
}

void frmAddFtgData::slotLineEditMoms2_returnPresse()
{
    moms2 = LineEditMoms2->text();
}

void frmAddFtgData::slotLineEditMoms3_returnPressed()
{
    moms3 = LineEditMoms3->text();
}

void frmAddFtgData::slotLineEditMoms4_returnPressed()
{
    moms4 = LineEditMoms4->text();
}

void frmAddFtgData::slotLineEditMoms5_returnPressed()
{
    moms5 = LineEditMoms5->text();
}

void frmAddFtgData::slotlineEditMomsKtoIng_returnPressed()
{
    momsin = lineEditMomsKtoIng->text();
}

void frmAddFtgData::slotLineEditMomsnr_returnPressed()
{
    momsnr = LineEditMomsnr->text();
}

void frmAddFtgData::slotlineEditMomsKtoUtg_returnPressed()
{
    momsut = lineEditMomsKtoUtg->text();
}

void frmAddFtgData::slotlineEditAutokonto_returnPressed()
{
    autokonto = lineEditAutokonto->text();
    autokonto=autokonto.upper();
    lineEditAutokonto->setText((autokonto));
}

void frmAddFtgData::slotlineEditBgnr_returnPressed()
{
    bgnr = lineEditBgnr->text();
}

void frmAddFtgData::slotlineEditPgnr_returnPressed()
{
    pgnr = lineEditPgnr->text();
}

void frmAddFtgData::slotPushButtonOK_clicked()
{
//    qDebug("FNAMN=%s",ftgnamn.latin1());
    slotUpdateFtgdata("FNAMN",ftgnamn);
    slotUpdateFtgdata("FTGNR",ftgnr);
    slotUpdateFtgdata("SNIKD",snikd);
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
    
    slotUpdateFtgdata("MNR",momsnr);		//2006-05-01
    slotUpdateFtgdata("MOMS1",moms1);
    slotUpdateFtgdata("MOMS2",moms2);
    slotUpdateFtgdata("MOMS3",moms3);
    slotUpdateFtgdata("MOMS4",moms4);
    slotUpdateFtgdata("MOMS5",moms5);
    slotUpdateFtgdata("MOMSI",momsin);		// momkonto ingående moms
    slotUpdateFtgdata("MOMSU",momsut);		// momskonto utgående moms
    slotUpdateFtgdata("AUTOK",autokonto);		// automatisk kontering J/N
    slotUpdateFtgdata("BGNR",bgnr);
    slotUpdateFtgdata("PGNR",pgnr);
    init();
}

void frmAddFtgData::slotUpdateFtgdata(QString posttyp, QString ftgdata)
{
	const char *userp = getenv("USER");
                QString usr(userp);

	inrad="";
	errorrad="";
	
//            qDebug("slotUpdateFtgdata::posttyp=%s ftgdata=%s",posttyp.latin1(),ftgdata.latin1());
	processnr++;   
	process[processnr] = new QProcess();
	process[processnr]->addArgument("./STYRMAN");	// OLFIX styrprogram
	process[processnr]->addArgument(usr);		// userid
	process[processnr]->addArgument( "FTGUPD");	// OLFIX funktion
	process[processnr]->addArgument(posttyp);
	process[processnr]->addArgument(ftgdata);

	frmAddFtgData::connect( process[processnr], SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmAddFtgData::connect( process[processnr], SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmAddFtgData::connect( process[processnr], SIGNAL(processExited() ),this, SLOT(slotUpdateEndOfProcess() ) );
	if (posttyp == "" ){
    	    QMessageBox::warning( this, "ADDFTGW",
                      "Posttyp saknas! \n" );
	}
	else {
	    if ( !process[processnr]->start() ) {
		// error handling
		QMessageBox::warning( this, "ADDFTGW",
                            "Kan inte starta STYRMAN/FTGUPD! \n" );
	    }
	}
//	qDebug("Uppdatering processnr=%d posttyp=%s ftgdata=%s",processnr,posttyp.latin1(),ftgdata.latin1());
}

void frmAddFtgData::slotDataOnStdout()
{
    while (process[processnr]->canReadLineStdout() ) {
	QString line = process[processnr]->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmAddFtgData::slotDataOnStderr()
{
    while (process[processnr]->canReadLineStderr() ) {
	QString line = process[processnr]->readStderr();
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
	    
	process[processnr] = new QProcess();
	process[processnr]->addArgument("./STYRMAN");	// OLFIX styrprogram
	process[processnr]->addArgument(usr);		// userid
	process[processnr]->addArgument( "FTGLIS");	// OLFIX funktion

	frmAddFtgData::connect( process[processnr], SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmAddFtgData::connect( process[processnr], SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmAddFtgData::connect( process[processnr], SIGNAL(processExited() ),this, SLOT(slotGetEndOfProcess() ) );
	if ( !process[processnr]->start() ) {
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
	    i = inrad.find( QRegExp("SNIKD_:"), 0 );
	    if (i != -1) {
		j = inrad.find( QRegExp("_:"), i+7 );
		m = j - (i + 7);
		snikd = inrad.mid(i+7,m);
		LineEditBranschkod->setText((snikd));
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
		j = inrad.find( QRegExp("_:"), i+6 );
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
	    i = inrad.find( QRegExp("MNR_:"), 0 );
	    if (i != -1) {
		j = inrad.find( QRegExp("_:"), i+7 );
		m = j - (i + 5);
		momsnr = inrad.mid(i+5,m);
		LineEditMomsnr->setText((momsnr));
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
	    i = inrad.find( QRegExp("BGNR_:"), 0 );
	    if (i != -1) {
		j = inrad.find( QRegExp("_:"), i+6 );
		m = j - (i + 6);
		bgnr = inrad.mid(i+6,m);
		lineEditBgnr->setText((bgnr));
	    }	    
	    i = inrad.find( QRegExp("PGNR_:"), 0 );
	    if (i != -1) {
		j = inrad.find( QRegExp("_:"), i+6 );
		m = j - (i + 6);
		pgnr = inrad.mid(i+6,m);
		lineEditPgnr->setText((pgnr));
	    }	    
	    
	    inrad="";
	    errorrad="";
	}    
    }
}

void frmAddFtgData::slotHelp()			// 2007-01-31
{
	inrad="";
	frmAddFtgData::readResursFil();			// Hämta path till hjälpfilen
	
	int i1 = hjelpfil.find( QRegExp(".html"), 0 );
	hjelpfil=hjelpfil.left(i1);
	hjelpfil=hjelpfil+"_FTGADMIN.html";
	hjelpfil=hjelpfil+"#NEWFTGDATA";			// Lägg till position
/*	qDebug("hjelpfil=%s",hjelpfil.latin1());	*/

	proc = new QProcess();
	proc->addArgument( "./OLFIXHLP" );			// OLFIX program
	proc->addArgument(hjelpfil);

	if ( !proc->start() ) {
	    // error handling
	    QMessageBox::warning( this, "OLFIX","Kan inte starta OLFIXHLP!\n" );
	}
}

void frmAddFtgData::readResursFil()			// 2007-01-31
{
    /*****************************************************/
    /*  Läs in .olfixrc filen här			            	*/
    /* Plocka fram var hjälpfilen finns			*/
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

