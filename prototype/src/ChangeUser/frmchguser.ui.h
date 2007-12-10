/****************************************************************/
/**		CHGUSRW					*/
/**		Ver 0.4					*/
/**		2003-01-21				*/
/** Modified:	2007-11-25 				*/
/**		Jan Pihlgren	jan@pihlgren.se		*/
/****************************************************************/
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
    QProcess* processlist;
    QString inrad;
    QString inradlista;
    QString inrad_u;
    QString errorrad;
    QString errorradlista;
    
    QString userid;
    QString namn="";
    QString avd;
    QString grupp;

void frmChgUser::init()
{
    frmChgUser::listUsers();
    listViewUser->setFocus();
}
        
void frmChgUser::slotGetUser()
{
	const char *userp = getenv("USER");
                QString usr(userp);
	 
	inrad_u="";
	namn="";
	avd="";
	grupp="";
	
    	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "USERDSP");	// OLFIX funktion
	process->addArgument(userid);	// AnvändarID på den vars data ska ändras
//	process->addArgument(userid.latin1());
	
	frmChgUser::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotUsrDataOnStdout() ) );
//	frmChgUser::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotUsrDataOnStderr() ) );
                frmChgUser::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfUsrProcess() ) );

	if (userid == ""){
    	    QMessageBox::warning( this, "CHGUSRW",
                      "userid måste vara ifyllt!\n" );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/USRCHG!\n");
		QMessageBox::warning( this, "CHGUSRW",
                            "Kan inte starta STYRMAN/USERDSP! \n" );
	    }   
	}
}

void frmChgUser::slotChgUser()
{
/************************************************************************/
/*	Uppdatera databasen						*/
/************************************************************************/
	const char *userp = getenv("USER");
                QString usr(userp);
	     
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "USERCHG");	// OLFIX funktion
	process->addArgument(userid);
	process->addArgument(namn);
	process->addArgument(avd);
	process->addArgument(grupp);
	
	frmChgUser::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotChgDataOnStdout() ) );
	frmChgUser::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotChgDataOnStderr() ) );
                frmChgUser::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfChgProcess() ) );
	
//	qWarning( "ChgUser: userid=%s  Namn=%s  Avd=%s  Grupp=%s\n", userid.latin1(),namn.latin1() ,avd.latin1(),grupp.latin1());

	if (userid == "" || namn ==""){
    	    QMessageBox::warning( this, "CHGUSRW",
                      "userid och/eller Namn saknas \n" );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		QMessageBox::warning( this, "CHGUSRW",
                            "Kan inte starta STYRMAN/USRCHG! \n" );
	    }   
	}
}

void frmChgUser::slotUseridEntered()
{
    userid=LineEditUserid->text();
    userid=userid.upper();
    LineEditUserid->setText((userid));
    if ( userid != ""){
	frmChgUser::slotGetUser();
    }
}

void frmChgUser::slotNameEntered()
{
    namn=LineEditNamn->text();
}

void frmChgUser::slotAvdEntered()
{
     avd=LineEditAvd->text();
}

void frmChgUser::slotGruppEntered()
{
    grupp=LineEditGrupp->text();
    PushButtonUpdate->setFocus();
}

void frmChgUser::slotPushButtonUpdate_clicked()
{
//  qDebug("PushButtonUpdate clicked userid=%s",userid.latin1());    
    frmChgUser::slotChgUser();
}

void frmChgUser::slotUsrDataOnStdout()
{
   while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad_u.append(line);
	inrad_u.append("\n");
    }
}

void frmChgUser::slotEndOfUsrProcess()
{
    int m;
    QString user;
    QString namn;
    QString avd;
    QString grupp;
    
//    qDebug("inrad=%s",inrad_u.latin1());
    
    LineEditUserid->clear();
    LineEditNamn->clear();
    LineEditAvd->clear();
    LineEditGrupp->clear();
    
    int i = inrad_u.find( QRegExp("1:"), 0 );
    int j = inrad_u.find( QRegExp("2:"), 0 );
    int k = inrad_u.find( QRegExp("3:"), 0 );
    int l = inrad_u.find( QRegExp("4:"), 0 );

    m=j-i;
    if (i != -1){
	user=inrad_u.mid(i+2,m-2);
	user=user.stripWhiteSpace();
	LineEditUserid->setText(user);
    }
    m=k-j;
    if ( j != -1){
	namn=inrad_u.mid(j+2,m-2);
	namn=namn.stripWhiteSpace();
	LineEditNamn->setText(namn);
    }
    m=l-k;
    if ( k != -1){
	avd=inrad_u.mid(k+2,m-2);
	avd=avd.stripWhiteSpace();
	LineEditAvd->setText(avd);
    }
    m=inrad_u.length() - l;
    if ( l != -1){
	grupp=inrad_u.mid(l+2,m-2);
	grupp=grupp.stripWhiteSpace();
	LineEditGrupp->setText(grupp);
    }
    LineEditNamn->setFocus();
}


void frmChgUser::slotChgDataOnStdout()
{
   while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
//	qWarning( "slotChgDataOnStdout: inrad=%s \n", inrad.latin1() );
    }
}

void frmChgUser::slotChgDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmChgUser::slotEndOfChgProcess()
{
    int i ;
//    qDebug("inrad=%s errorrad=%s",inrad.latin1(),errorrad.latin1());    
     i = -1;
     i = errorrad.find( QRegExp("Error: "), 0 );
    
//     qDebug("frmChgUser-inrad=%s i=%d\n",inrad.latin1(),i);
     
     if (i != -1) {
	QMessageBox::critical( this, "CHGUSRW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
     }
     i = -1;
     i = inrad.find( QRegExp("OK:"), 0 );
//     qDebug("i = %d",i);
     if(i != -1){
	QMessageBox::information( this, "CHGUSRW",
		"Uppdatering OK!\n"
		);
	LineEditUserid->clear();
                LineEditNamn->clear();
	LineEditAvd->clear();
	LineEditGrupp->clear();
	listViewUser->clear();
	listUsers();
//	LineEditUserid->setFocus();
	listViewUser->setFocus();
	inrad="";
	inrad_u="";
	i = -1;
     }
     else{
	 	QMessageBox::information( this, "CHGUSRW",
		"Ingen uppdatering!\n"
		);
	    }
}

void frmChgUser::listUsers()	
{
    const char *userp = getenv("USER");
    QString usr(userp);
    listViewUser->clear();
    inradlista="";
    errorradlista="";
	
    processlist = new QProcess();
    processlist->addArgument("./STYRMAN");	// OLFIX styrprogram
    processlist->addArgument(usr);		// userid
    processlist->addArgument( "USERLST");	// OLFIX funktion
		
    frmChgUser::connect( processlist, SIGNAL(readyReadStdout() ),this, SLOT(slotUserDataOnStdout() ) );
    frmChgUser::connect( processlist, SIGNAL(readyReadStderr() ),this, SLOT(slotUserDataOnStderr() ) );	
    frmChgUser::connect( processlist, SIGNAL(processExited() ),this, SLOT(slotUserEndOfProcess() ) );	    
 
    if ( !processlist->start() ) {
    // error handling
    QMessageBox::warning( this, "Start av USERLST ",
	"Kan inte starta STYRMAN/USERLST!\n"
                );
    }
}

void frmChgUser::slotUserDataOnStdout()
{
    while (processlist->canReadLineStdout() ) {
	QString line = processlist->readStdout();
	inradlista.append(line);
	inradlista.append("\n");
    }
}

void frmChgUser::slotUserDataOnStderr()
{
    while (processlist->canReadLineStderr() ) {
	QString line = processlist->readStderr();
	errorradlista.append(line);
	errorradlista.append("\n");
    }
}

void frmChgUser::slotUserEndOfProcess()
{
    QListViewItem* item;
    int i;
    listViewUser->setSorting(0,TRUE);
    i = -1;
    i = errorradlista.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "CHGUSRW",
		"ERROR!\n"+errorradlista
	);
	errorradlista="";
	i = -1;
     }
	 
    i = inradlista.find( QRegExp("NR_0_"), 0 );
         if (i != -1) {
	QMessageBox::information( this, "CHGUSRW",
		"Användarregistret innehåller inga poster!\n"
	);
	i = -1;
     }
	 
    inradlista.latin1();
    char *pos1;
    char *pos2;
    char tmp[MAXSTRING];
    char *tmppek;
    int j,k,l,m,m1,m2,l1,l2;
    char antrad[6]="";
    char userid[9]="";
    char namn[31]="";
    char avd[11]="";
    char grupp[11]="";
    QString host;
    
    /*                                                   Start     2007-11-25                                         */
    m1=inradlista.find( QRegExp("host="), 0 );
    m2=inradlista.find( QRegExp("NR_"), 0 );
    l1=m2-(m1+5);
    l2=m2-m1;
    host=inradlista.mid(5,l1);
    inradlista=inradlista.mid(m2,inrad.length()-m2);
    
    //  qDebug("host=%s m1=%d m2=%d l1=%d l2=%d\n",host.latin1(),m1,m2,l1,l2);
    if(host != "127.0.0.1 "){
	 if(host != "localhost "){
	     textLabel1->setText("<u><b>Host</b></u>\n");
	     textLabelHostName->setText(host);
	 }
    }else{
	textLabel1->setText("");
    }
    /*                                                End         2007-11-25                                         */
    // qDebug("inradlista=%s",inradlista.latin1());
    tmppek=tmp;
    qstrcpy(tmp,inradlista);
    pos1=strstr(tmp,"NR_");	//3  tecken långt
    pos2=strstr(tmp,"_:");
    i=pos2-pos1;
    m=i+2;		// startposition för  första userid.
    
//    qDebug("i=%d  m=%d",i,m);
    
    k=0;
    for (j=3;j<i;j++){	                   // j = första positionen för antal poster, (NR_6_:ADMINA_:Administratör av OLFIX_:IT_:Stab_:)
	antrad[k]=tmp[j];
	k++;
    };
    i=atoi(antrad);		// i = antal poster
    
//    qDebug("antrad=%s",antrad);
    
    for (k = 1;k <= i; k++){	// g� igenom alla raderna / posterna
	l=0;
	for(j = m; j < sizeof(userid) + m; j++){
	    if(tmp[j] != *("_")){
		userid[l]=tmp[j];
		l++;
	    }else{
		userid[l] = *("\0");
		j=sizeof(userid) + m;
	    }
	}
//	qDebug("%s  ",userid);
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
	for(j = m; j < sizeof(avd) + m; j++){
	    if(tmp[j] != *("_")){
		avd[l]=tmp[j];
		l++;
	    }else{
		avd[l] = *("\0");
		j=sizeof(avd) + m;
	    }
	}
//	qDebug("%s  ",avd);	
	m=m+l+2;
	l=0;
	for(j = m; j < sizeof(grupp) + m; j++){
	    if(tmp[j] != *("_")){
		grupp[l]=tmp[j];
		l++;
	    }else{
		grupp[l] = *("\0");
		j=sizeof(grupp) + m;
	    }
	}
//	qDebug("%s  ",grupp);	
	m=m+l+2;
		
	item = new QListViewItem(listViewUser,namn,userid);
// 	 rensa namn och userid 
  	for (l=0;l<sizeof(userid);l++)
		userid[l]=*("\0");
	for (l=0;l<sizeof(namn);l++)
	               namn[l]=*("\0");
	for (l=0;l<sizeof(avd);l++)
	               avd[l]=*("\0");
	for (l=0;l<sizeof(grupp);l++)
	               grupp[l]=*("\0");	
//	 rensa listrad 
//	listrad.remove(0,80);
    }   
}

void frmChgUser::slotPickupUserID( QListViewItem * item)
{
    char user[21]="";
    LineEditNamn->clear();
    LineEditAvd->clear();
    LineEditGrupp->clear();
    
//    qDebug("PickupUserID\n");
    if(!item){
	return;
    }
     listViewUser->setCurrentItem(item);
     if(!item->key(0,TRUE)){
	 return;
     }

     strcpy(user,item->key(1,TRUE));	// = Användar-ID
     userid=user;
     LineEditUserid->setText(userid);
     LineEditUserid->setFocus();
}

    
    
