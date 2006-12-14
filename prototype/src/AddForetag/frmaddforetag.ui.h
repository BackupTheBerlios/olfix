/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                          ADDFORW  -  description
                             -------------------
		     version 0.3
    begin                 : Tis   9 nov  2004
    Modified          : Ons 28 sept 2005
                               :Ons 13 dec  2006  Rättat bugg men OLFIXHLP
    copyright          : (C) 2003 by Jan Pihlgren
    email                : jan@pihlgren.se
 ***************************************************************************/
/*****************************************************************
 *					                                            *
 *   This program is free software; you can redistribute it and/or modify 	 *
 *   it under the terms of the GNU General Public License as published by   	 *
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
#include <qlistview.h>
#include <qwhatsthis.h> 
#define MAXSTRING 5000
#define VERSION "Version: 0.3\n 2006-12-13"

    QProcess* process;
    QString inrad;
    QString inradmysql;
    QString errorrad;
    QString* rad;
    QString dbnamn;
    QString newdatabase;
    QString hjelpfil;
    QString passw;
    QString val="";
    int flag;

void frmAddForetag::init()
{
    LineEditdbnamn->clear();
    lineEditPassword->clear();
    val = "3";			// Lista befintliga databaser utom databasen mysql
    listDatabaser(val);
//    qDebug(" dbnamn=%s)",dbnamn.latin1());
    LineEditdbnamn->setFocus();
}
   

void frmAddForetag::slotdbnamnEntered()
{
    int status=FALSE;
    dbnamn=LineEditdbnamn->text();
    dbnamn=dbnamn.lower();
    status=checkDatabaseExist(dbnamn);
    if (status==TRUE){
	QMessageBox::warning( this, "ADDFORW","Databasen finns redan!\n" );
	LineEditdbnamn->clear();
	LineEditdbnamn->setFocus();
    }else{
	LineEditdbnamn->setText(dbnamn);
	lineEditPassword->setFocus();
    }
}

void frmAddForetag::lineEditPassword_Entered()
{
    passw=lineEditPassword->text();
    PushButtonOK->setFocus();
}

void frmAddForetag::pushButtonHelp_clicked()
{
	inrad="";
	frmAddForetag::readResursFil();		// Hämta path till hjälpfilen

	int i1 = hjelpfil.find( QRegExp(".html"), 0 );
//	int i2 = hjelpfil.length();
	hjelpfil=hjelpfil.left(i1);
	hjelpfil=hjelpfil+"_DATABASER.html";
	hjelpfil=hjelpfil+"#DATABASNY";		// Lägg till position
//	qDebug("hjelpfil=%s",hjelpfil.latin1());

	process = new QProcess();
	process->addArgument( "./OLFIXHLP" );		// OLFIX program  (20061213)
	process->addArgument(hjelpfil);

	if ( !process->start() ) {
	    // error handling
	    QMessageBox::warning( this, "ADDFORW","Kan inte starta OLFIXHLP!\n" );
	}
	LineEditdbnamn->setFocus();
}

void frmAddForetag::slotAddForetag()
{
/************************************************************************/
/*	Skapa databasen i mysql						*/
/************************************************************************/
    const char *userp = getenv("USER");
    QString usr(userp);
    QString user;
    QString orgfile="/tmp/CreateOLFIXtemplate.org";
    QString tmpfile="/tmp/CreateOLFIXtemplate.tmp";
    QString tempfile="/tmp/CreateOLFIXtemplate_temp.tmp";
    QString newsqlfile="/tmp/CreateOLFIXnew.sql";		    
    QString kommando;
    user=usr.upper();
    /* Editera sqlfilen som ska användas för att skapa den nya databasen */
    kommando="cp ../sql/CreateOLFIXtemplate.sql ";
    kommando.append(orgfile);
//    qDebug("kommando 1 = %s",kommando.latin1());
    system(kommando);
    
    kommando="sed 's/olfixtemplate/";
    kommando.append(dbnamn);
    kommando.append("/' ");
    kommando.append(orgfile);
    kommando.append(" > ");
    kommando.append(tmpfile);
    system(kommando);
//    qDebug("kommando 2 = %s",kommando.latin1());
    
    kommando="sed 's/NEWUSER/";
    kommando.append(user);
    kommando.append("/' ");
    kommando.append(tmpfile);
    kommando.append(" > ");
    kommando.append(tempfile);
    system(kommando);
//    qDebug("kommando 3 = %s",kommando.latin1());
    
    kommando="sed 's/newdatabase/";
    kommando.append(dbnamn);
    kommando.append("/' ");
    kommando.append(tempfile);
    kommando.append(" > ");
    kommando.append(newsqlfile);
//    qDebug("kommando 4 = %s",kommando.latin1());    
    system(kommando);
    
    /* Skapa databasen */
    kommando="mysql --password=";
    kommando.append(passw);
    kommando.append(" < ");
    kommando.append(newsqlfile);
//   qDebug("kommando 5 = %s",kommando.latin1());    
    system(kommando);
    /* Radera filer */
    kommando="rm ";
    kommando.append(orgfile);
    system(kommando);
 
    kommando="rm ";
    kommando.append(tmpfile);
    system(kommando),
    
    kommando="rm ";
    kommando.append(tempfile);
    system(kommando);
    
    kommando="rm ";
    kommando.append(newsqlfile);
//    qDebug("kommando 6 = %s",kommando.latin1());    
    system(kommando);   
    
    QMessageBox::information( this, "ADDFORW",
		"Databasen \""+dbnamn+"\" är skapad!\n"
	);

    PushButtonQuit->setFocus();
}

void frmAddForetag::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmAddForetag::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmAddForetag::slotEndOfProcess()
{
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "ADDFORW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
     }
     i = -1;
     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	QMessageBox::information( this, "ADDFORW",
		"Uppdatering OK!\n"+errorrad
	);
	LineEditdbnamn->clear();
	lineEditPassword->clear();
	listViewDatabas->clear();
	val="3";
	listDatabaser(val);
	LineEditdbnamn->setFocus();
	inrad="";
	i = -1;
     }
}

void frmAddForetag::slottInformation()
{
	QMessageBox::information( this, "ADDFORW",
                   "Databasen MÅSTE fysiskt finnas upplagd! \n\n Denna fuktion uppdaterar bara databasen så att man vet att det \n nya företaget existerar samt möjliggör för användarna att arbeta \n med olika företag." );
}


void frmAddForetag::slotCheckIfExistDbnr()
{
	const char *userp = getenv("USER");
	QString usr(userp);
	   	    
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// Userid
	process->addArgument( "DATABASE");	// OLFIX funktion
	process->addArgument("4");		// Kontrollera om tabellen RIGHTS finns i databasen, finns databasen

	frmAddForetag::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmAddForetag::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmAddForetag::connect( process, SIGNAL(processExited() ),this, SLOT(slotCheckDbnrEndOfProcess() ) );
	
	if (dbnamn == ""){
    	    QMessageBox::warning( this, "ADDFORW",
                      "Databasnamn saknas \n" );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/DATABASE!\n");
		QMessageBox::warning( this, "ADDFORW",
                            "Kan inte starta STYRMAN/DATABASE! \n" );
	    }   
	}
}

void frmAddForetag::slotCheckDbnrEndOfProcess()
{
    int i;
    QString message;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
/*    message=errorrad.mid(14,errorrad.length()-14);	*/
     if (i != -1) {
/*	QMessageBox::critical( this, "ADDFORW",
		"ERROR! \n\n"+message
	);	
*/
	errorrad="";
	i = -1;
	LineEditdbnamn->setFocus();
     }
     i = -1;
     
     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	QMessageBox::critical( this, "ADDFORW",
		"Databasen finns redan!\n"
	);
	inrad="";
	i = -1;
	LineEditdbnamn->clear();
	LineEditdbnamn->setFocus();
     }
}

void frmAddForetag::listDatabaser(QString choise)
{
	const char *userp = getenv("USER");
	QString usr(userp);

	process = new QProcess();
	process->addArgument("./STYRMAN");
	process->addArgument(usr);		// userid
	process->addArgument( "DATABASE");	// OLFIX funktion
	process->addArgument( choise);
	process->addArgument( newdatabase);
	
	frmAddForetag::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmAddForetag::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );	
	frmAddForetag::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcessList() ) );

	if ( !process->start() ) {
	    // error handling
	    QMessageBox::warning( this, "Start av DATABASE ", "Kan inte starta DATABASE!\n");
	}
}

void frmAddForetag::slotEndOfProcessList()
{
   QListViewItem* item;
    listViewDatabas->setSorting(0,TRUE);
    int n,j,k=0;
    int i=-1;
    QString temp1;
    QString temp2;
    QString p;
//    qDebug("val=%s",val.latin1());
//    qDebug("inrad=%s",inrad.latin1());
    i = errorrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "BYTFW",
		"ERROR!\n"+errorrad
	);
	if (val=="4"){
	   listViewDatabas->setFocus();
	}  
	errorrad="";
	i = -1;
	return;
     }
     i = -1;
     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	 if (val == "2"){
	     QMessageBox::information( this, "ADDFORW",
				       "Databasbyte genomfört!\n"
				       );
	     PushButtonQuit->setFocus();
	 }
	if (val == "3"){
	    i= -1;
	    i = inrad.find(QRegExp("NR_"),0);
	    if( i != -1){
		int m = inrad.find(QRegExp("_:_"),0);
		n=m-(i+3);
  		p=inrad.mid(i+3,n);
//		qDebug("n=%d  m=%d  p=%s",n,m,p.latin1());
		j=p.toInt();
		n=1;
		while (n <= j){
//		    n++;
		    p.setNum(n);
		    temp1="_:_"+p+"_:_";
//		    qDebug("temp1=%s",temp1.latin1());
		    p.setNum(n+1);
		    if(n != j){			
			temp2="_:_"+p+"_:_";
		    }else{
			temp2="_:_";
		    }			
//		    qDebug("temp2=%s",temp2.latin1());
		    m = inrad.find(QRegExp(temp1),0);
		    if (n == j){
			k = inrad.find(QRegExp(temp2),m+9);
//			qDebug("temp2=%s  k=%d",temp2.latin1(),k);
		    }else{
			k = inrad.find(QRegExp(temp2),0);
		    }
		    i = k - (m+temp1.length());
		    p=inrad.mid(m+temp1.length(),i);
		    if(p != "mysql"){
//			qDebug("p=%s",p.latin1());
			item = new QListViewItem(listViewDatabas,p);
		    }
		    n++;
		}
	    }
	}
  //     qDebug("EndOfProcess():: inrad=%s",inrad.latin1());  
    }
//    fprintf(stderr,"Klart!\n");
}

void frmAddForetag::readResursFil()
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


int frmAddForetag::checkDatabaseExist(QString databasnamn)
{
    int status=FALSE;
    char tmp[50]="";
    QString db="";
     QListViewItemIterator it( listViewDatabas );
        while ( it.current() ) {
            QListViewItem *item = it.current();
            strcpy(tmp, item->key(0,TRUE));
            db=tmp;
            if (databasnamn == db ){
	status=TRUE;
           }
            ++it;
        }
        if(status == TRUE){
	qDebug("Check databas, namn=%s finns redan",db.latin1());
       }
       return status;
}
