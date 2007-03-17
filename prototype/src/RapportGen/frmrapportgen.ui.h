/****************************************************************/
/**		RPTGENW					*/
/**		2003-08-26				*/
/**		Ver 0.2                                                                                    	*/
/**    Modified:	2007-03-17				*/
/**   Copyright	Jan Pihlgren	jan@pihlgren.se		*/
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
#include <qtextedit.h> 

#include <qfiledialog.h> 

#define VERSION "0.2"
#define MAXSTRING 5000
#define FIL "/tmp/rptcre.txt"

    QProcess* process;
    QString inrad;
    QString errorrad;
    QString sqlquery;
    QString fileName;
    QString hjelpfil;

void frmRapportGen::init()
{
    QString filnamn;
    filnamn=FIL;
    slotFileRemove(filnamn);
    textEditSQL->setFocus();
}

void frmRapportGen::slottextEditSQL_returnPressed()
{
    sqlquery=textEditSQL->text();
//    qDebug("sqlquery=%s\n",sqlquery.latin1());
}

void frmRapportGen::slottextEditSQL_TextChanged()
{
        sqlquery=textEditSQL->text();
}

void frmRapportGen::slotpushButtonOK_clicked()
{
    slotFileRemove(FIL);
    slotCreateTmpFile();
}


void frmRapportGen::slotCreateTmpFile()
{
    const char *userp = getenv("USER");
    QString usr(userp);

    process = new QProcess();
    process->addArgument("./STYRMAN");	// OLFIX styrprogram
    process->addArgument(usr);		// userid
    process->addArgument( "RPTCRE");	// OLFIX funktion
    process->addArgument(sqlquery);	// SQLfråga

    frmRapportGen::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
    frmRapportGen::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
    frmRapportGen::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );


	if (sqlquery == "" ){
    	    QMessageBox::warning( this, "SRPTGENW",
                      "SQLfrågan får inte vara blank" );
	}else {
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/RPTCRE!\n");
		QMessageBox::warning( this, "RPTGENW",
                            "Kan inte starta STYRMAN/RPTCRE! \n" );
	    }
	}   
}

void frmRapportGen::slotEndOfProcess()
{
    QString command;
    int i =  -1;
    
    command="kspread ";
    command.append(FIL);

//    qDebug("slotEndOfProcess::command=%s\n",command.latin1());    
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i == 0) {
	QMessageBox::critical( this, "OLFIX - RPTGENW",
		"ERROR!\n"+errorrad
		);
	errorrad="";
	slotFileRemove(FIL);
    }else{
//	system("kspread /tmp/Saldolista.txt");
	system(command);
    }
}

void frmRapportGen::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmRapportGen::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmRapportGen::slotFileRemove(QString filnamn)
{
//  Ta bort temporärfilen  /tmp/rptcre.txt
    bool status;
    QDir d = QDir::root();                   // "/"
    status=d.remove(filnamn,FALSE);
//    qDebug("slotFileRemove()::TRUE=%d FALSE=%d",TRUE,FALSE);
//    qDebug("slotFileRemove()::filnamn=%s",filnamn.latin1());
//    qDebug("slotFileRemove()::status=%d",status);
}


void frmRapportGen::GetFileDialog()
{ 
/************************************************
                                   Hämta hemmabibliotek
************************************************/      
    const char *userp = getenv("HOME");
    QString homedir(userp);
/************************************************
                                   Hämta filnamn
************************************************/  
    QFileDialog* fd = new QFileDialog( this, "file dialog", TRUE );
    fd->setDir(homedir);
    fd->setFilter( "SQL-filer (*.sql *.txt )" );
    if ( fd->exec() == QDialog::Accepted ){
	fileName = fd->selectedFile();
	slotGetQueryFile();
    }   
//    qDebug("GetFileDialog():: fileName=%s\n",fileName.latin1());
}


void frmRapportGen::slotGetQueryFile()
{
/************************************************
                                   Hämta filen
************************************************/  
    QString line;
    QStringList lines;
//    int i = 1;
    
    sqlquery="";
    QFile file(fileName );
    if ( file.open( IO_ReadOnly ) ) {
	QTextStream stream( &file );
//	i=1;
	while ( !stream.eof() ) {
	    line = stream.readLine(); // line of text excluding '\n'
	    line.append("\n");
	    //	    fprintf( stderr,"%3d: %s\n", i++, line.latin1() );
//	    lines += line;
	    sqlquery.append(line);
	}
	file.close();
    }
//    qDebug("slotGetQueryFile():: sqlquery=%s",sqlquery.latin1());
    textEditSQL->setText(sqlquery);
}

void frmRapportGen::SaveFileDialog()
{ 
/************************************************
                                   Hämta hemmabibliotek
************************************************/      
    const char *userp = getenv("HOME");
    QString homedir(userp);
/************************************************
                                   Hämta filnamn
************************************************/  
/*    QFileDialog* fd = new QFileDialog( this, "file dialog", TRUE );
    fd->setDir(homedir);
    fd->setFilter( "SQL-filer (*.sql *.txt )" );
    if ( fd->exec() == QDialog::Accepted ){
	fileName = fd->selectedFile();
	slotSaveQueryFile();
    }
*/
    QString s = QFileDialog::getSaveFileName(
                    homedir,
                    "Filnamn (*.sql *.txt)",
                    this,
                    "save file dialog"
                    "Choose a filename to save under" );
    
//    qDebug("SaveFileDialog():: s=%s\n",s.latin1());
/************************************************
                                   Spara filen
************************************************/  
    QString line;
    QStringList lines;
    
    QFile file(s);
    if ( file.open( IO_WriteOnly ) ) {
	QTextStream stream( &file );
//	stream << rapportrad;
	stream << sqlquery;
	file.close();
    }
//    qDebug("slotGetQueryFile():: sqlquery=%s",sqlquery.latin1());
}


void frmRapportGen::slotClearSqlQuery()
{
    sqlquery="";
    textEditSQL->setText(sqlquery);
}

void frmRapportGen::pushButtonHelp_clicked()
{
	inrad="";
	frmRapportGen::readResursFil();		// Hämta path till hjälpfilen

	int i1 = hjelpfil.find( QRegExp(".html"), 0 );
//	int i2 = hjelpfil.length();
	hjelpfil=hjelpfil.left(i1);
	hjelpfil=hjelpfil+"_RAPPORTER.html";
	hjelpfil=hjelpfil+"#RAPPORTGENERATOR";	// Lägg till position
//	qDebug("hjelpfil=%s",hjelpfil.latin1());

	process = new QProcess();
	process->addArgument( "./OLFIXHLP" );		// OLFIX program  (20061213)
	process->addArgument(hjelpfil);

	if ( !process->start() ) {
	    // error handling
	    QMessageBox::warning( this, "RPTGENW","Kan inte starta OLFIXHLP!\n" );
	}
	pushButtonGetFile->setFocus();
}


void frmRapportGen::readResursFil()
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
