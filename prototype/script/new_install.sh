#!/bin/sh
#
#**********************************
#***  OBS! Skall k�ras som root ***
#**********************************

# Namn: install.sh
# Version: 0.4		2006-01-18 Jan Pihlgren.
# Version: 0.3b		2004-01-18 Jan Pihlgren.
# Version: 0.3a		2004-01-14 Jan Pihlgren.
# Version: 0.3		2004-01-08 Jan Pihlgren.
# Beskrivning: Installations/Uppdaterings script f�r OLFIX version X.X

# En log skapas vid installationen ($HOME/tmp/InstallOlfix.log)
LOGFILE=$HOME/tmp/InstallOlfix.log
echo "START!" >$LOGFILE
date>>$LOGFILE
# ---------------------------------------------------------------
# S�tt OLFIX variabler
# OLFIXs hemmakatalog
OPT=/opt
OLFIX_HOME=/opt/olfix
OLFIX_SOURCE=$OLFIX_HOME/src
OLFIX_SQL=$OLFIX_HOME/sql
OLFIX_DATA=$OLFIX_HOME/data

echo OLFIX_HOME=$OLFIX_HOME>> $LOGFILE

TITLE="OlFIX installation. Version "
VERSION="0.3.1.B"
echo VERSION=$VERSION>> $LOGFILE
# ---------------------------------------------------------------

# S�tt PATH
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/lib
# TEMP anv�nds f�r att lagra svar fr�n dialog. 
TEMP=$HOME/tmp/.tempfil

# ---------------------------------------------------------------
# install.sh anropas n�r man st�r i $OLFIX_HOME/script
# s� f�r att f� variabel OLFIX_HOME korrekt beh�ver man
# ---------------------------------------------------------------
#cd $OLFIX_HOME/script

#TEMP anv�nds f�r att tillf�lligt mellanlagra data
TEMP=$HOME/tmp/.tempfil.log

#QT variabler
QT=$QTDIR
QT_BIN=$QT/bin
QT_INC=$QT/include
QT_LIB=$QT/lib
echo QT=$QT>> $LOGFILE

#MySQL variabler
MYSQLD=`whereis mysqld|awk '{print $2}'`
echo MYSQLD=$MYSQLD>> $LOGFILE

OLFIX_EXIST=N

dialog --begin 100 50
dialog --backtitle "OlFIX installation. Version "$VERSION \
	--msgbox "OLFIX version X\n\n Det h�r scriptet hj�lper dig att installera OLFIX.\n Efter ett antal fr�gor kommer OLFIX att installeras.\n\n Varje fr�ga har ett standandard svar,\n
om du tycker att det �r ok s� tryck bara p� [Enter].\n
Standardsvaret �r markerat med []\n\n Om du vill avbryta installation eller uppgradering\n innan arbetet p�b�rjas s� tryck Ctrl-C.\n" 15 60

#++++++++++++++++++++++++++++++++++++++++++++++++#
# -- Leta upp qt och dess mappar om dem finns -- #
#++++++++++++++++++++++++++++++++++++++++++++++++#
QTEXIST=
if [[ -d $QT && -d $QT_BIN && -d $QT_INC && -d $QT_LIB ]];then
	QTEXIST=J
	echo "QTEXIST= "$QTEXIST" Hittade QT och dess undermappar p�" $QT >> $LOGFILE
#	dialog --backtitle "OlFIX installation. Version "$VERSION \
#	 --msgbox "** Hittade QT och dess undermappar p� $QT **" 5 60
 else
	EXXIST=N
	echo "QTEXIST= "$QTEXIST"QT= "$QT" Hittade inte QT. Avbryter installationen!" >> $LOGFILE 
	dialog --backtitle "OlFIX installation. Version "$VERSION \
	--msgbox "** Kunde inte hitta QT, du m�ste ha QT installerat\n.** Avbryter installationen!\n" 5 60
	exit
fi

#++++++++++++++++++++++++++++++++++++++++++++++++#
# -- leta upp mysqld samt kolla om den svarar -- #
#++++++++++++++++++++++++++++++++++++++++++++++++#
#MYSQLD=
if [[ -f $MYSQLD ]];then
#	dialog --backtitle "OlFIX installation. Version "$VERSION \
#	--msgbox "** Hittade mysqld **" 5 27

	MYSQLLIB=`whereis libmysqlclient.so.|awk '/12/ {print}'`
	MYSQLLIB12=`whereis libmysqlclient.so.12|awk '{print $3}'`
	MYSQLLIB14=`whereis libmysqlclient.so.14|awk '{print $2}'`
	echo MYSQLLIB=$MYSQLLIB>> $LOGFILE
	echo MYSQLLIB12=$MYSQLLIB12>> $LOGFILE
	echo MYSQLLIB14=$MYSQLLIB14>> $LOGFILE
	if [[ $MYSQLLIB ]];then
#		dialog --backtitle "OlFIX installation. Version "$VERSION \
#		--msgbox "** Hittade libmysqlclient.so. **" 5 40
		echo "MYSQLLIB= "$MYSQLLIB>> $LOGFILE
	else

		dialog --backtitle "OlFIX installation. Version "$VERSION \
		--msgbox "** Hittade inte libmysqlclient.so.\n** skapar l�nk" 6 40
#		echo MYSQLLIB=$MYSQLLIB>> $LOGFILE
	fi
else
	dialog --backtitle "OlFIX installation. Version "$VERSION \
	--msgbox "** Hittade inte mysqld\n** MySQL m�ste vara installerad\n** Avslutar utan installation!" 7 40
	exit
fi

#+++++++++++++++++++++++++++++++++++++++++++++++++++#
# -- Leta upp olfix och dess mappar om dem finns -- #
#+++++++++++++++++++++++++++++++++++++++++++++++++++#
if [[ -d $OLFIX_HOME ]];then
	OLFIX_EXIST=J
#	dialog --backtitle "OlFIX installation. Version "$VERSION \
#	--msgbox "** Hittade OLFIX p� $OLFIX_HOME,\n** en installation finns redan. **" 6 40
	echo OLFIX_EXIST=$OLFIX_EXIST>> $LOGFILE
else
	OLFIX_EXIST=N
#	dialog --backtitle "OlFIX installation. Version "$VERSION \
#	--msgbox "** Kunde inte hitta OLFIX! \n** Skapar /opt/olfix\n" 6 30
	echo "OLFIX_EXIST="$OLFIX_EXIST" Skapar /opt/olfix" >> $LOGFILE

	if [[ -d $OPT ]]; then 
		mkdir /opt/olfix
		echo "Skapar katalogen olfix i "$OPT>> $LOGFILE
	else
		mkdir /opt
		echo "Skapar katalogen "$OPT>> $LOGFILE
		mkdir /opt/olfix
		echo "Skapar katalogen olfix i "$OPT>> $LOGFILE
	fi
fi
#+++++++++++++++++++++++++++++++++++++++++++++++++++++#
# -- Leta upp kugar och kspread, finns med koffice -- #
#+++++++++++++++++++++++++++++++++++++++++++++++++++++#
KOFFICE_EXIST=N
KOFFICE=kugar
TEMPORER=`whereis kugar|awk '{print $2}'`
echo TEMPORER=$TEMPORER>> $LOGFILE
if [[ -f $TEMPORER ]];then
	KOFFICE_EXIST=J
#	dialog --backtitle "OlFIX installation. Version "$VERSION \
#	--msgbox "** Hittade inte Kugar.\n** F�r att rapporter mm\n** ska fungera b�r KOffice installeras." 7 50
else
	KOFFICE_EXIST=N
	dialog --backtitle "OlFIX installation. Version "$VERSION \
	--msgbox "** Hittade inte Kugar.\n** F�r att rapporter mm\n** ska fungera b�r KOffice installeras." 7 50

fi
echo KOFFICE_EXIST=$KOFFICE_EXIST>> $LOGFILE
#+++++++++++++++++++++++++++++++++++++++++++++++++++++#
# -- Test om databasmotorn MySQL �r startad	   -- #
#+++++++++++++++++++++++++++++++++++++++++++++++++++++#

MYSQLISLIVE=

MYSQLISLIVE=`mysqladmin ping|awk '{print $1}'`
echo MYSQLISLIVE = $MYSQLISLIVE >> $LOGFILE
if [[ $MYSQLISLIVE ]];then
	echo "MySQL �r startad och jobbet forts�tter!" >> $LOGFILE
else
	dialog --backtitle "OlFIX installation. Version "$VERSION \
	--msgbox "** MySQL �r inte startad och jobbet kan inte forts�tta! **" 5 70
	echo "MySQL �r inte startad och jobbet kan inte forts�tta!" >> $LOGFILE
	exit
fi
#+++++++++++++++++++++++++++++++++++++++++++++++++++++#
# -- Test om olfix redan finns installerad 	   -- #
#+++++++++++++++++++++++++++++++++++++++++++++++++++++#
DATABAS=

DATABAS=`mysqlshow |grep  olfix|awk '{print $2}'`
echo DATABAS = $DATABAS >> $LOGFILE

UPDATE=N
if [[ $DATABAS ]];then
	UPDATE="J"
	echo "OLFIX finns. V�ljer att uppdatera OLFIX! UPDATE="$UPDATE >> $LOGFILE
	exitcode=0
	dialog --backtitle "OlFIX installation. Version "$VERSION \
	--title "OLFIX INSTALLATION" \
	--menu "Vill du uppgradera OLFIX? " 10 60 2 \
	J "Uppgradera OLFIX!" \
	N "Avbryt uppgraderingen" 2>$TEMP
	exitcode=$?
	echo "exitcode="$exitcode >> $LOGFILE
	if [ $exitcode -eq 0 ]
	then
		choice=`cat $TEMP`
		SVAR=$choice
		echo "SVAR = "$SVAR >> $LOGFILE
	else
		dialog --backtitle "OLFIX installation." \
		--msgbox "** Uppgraderingen  avbryts! **" 5 45
		clear
		rm -f $TEMP
#		echo "exitcode="$exitcode >> $LOGFILE
		echo "exitcode="$exitcode " SVAR = "$SVAR >> $LOGFILE
		echo "Uppgradering av OLFIX avbryts!" >> $LOGFILE
		exit
  	fi
  	rm -f $TEMP
	if test $SVAR != "J";then
		exitcode=0
		dialog --backtitle "OLFIX installation." \
		--msgbox "** Uppgradering av OLFIX avbryts! **" 5 45
		echo -e "** Uppgradering av OLFIX avbryts!">>$LOGFILE
		echo "SVAR = "$SVAR >> $LOGFILE
		date>>$LOGFILE
		clear
		rm -f $TEMP
		exit
	fi
else
	echo "P�b�rjar uppgradering av OLFIX!" >> $LOGFILE
fi
date>>$LOGFILE
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++#
# L�s in anv�ndarnamn/UserID f�r OLFIX			--#
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++#
FNAMN= 
dialog --backtitle "OLFIX installation." \
--msgbox "** Du ska nu ange ditt UserID som beh�vs f�r OLFIX\n** Anv�nd samma userid som du anv�nder n�r du loggar in i Linux\n** Skriv med med versaler!" 7 70
exitcode=0
dialog --backtitle "OLFIX installation." \
--title "OLFIX INSTALLATION" \
--inputbox "Ange ditt UserID! " 10 60  2>$TEMP
exitcode=$?
if [ $exitcode -eq 0 ]
then
	choice=`cat $TEMP`
	FNAMN=$choice
else
	dialog --backtitle "OLFIX installation." \
	--msgbox "** Installationen avbr�ts! **" 5 35
	clear
	rm -f $TEMP
	exit
fi
rm -f $TEMP
exitcode=0

dialog --backtitle "OLFIX installation." \
--title "OLFIX INSTALLATION" \
--inputbox "Ange root password! " 10 60  2>$TEMP
exitcode=$?
if [ $exitcode -eq 0 ]
then
	choice=`cat $TEMP`
	ROOTPW=$choice
else
	dialog --backtitle "OLFIX installation." \
	--msgbox "** Installationen avbr�ts! **" 5 35
	clear
	rm -f $TEMP
	exit
fi
rm -f $TEMP

#+++++++++++++++++++++++++++++#
# -- Starta installationen  --#
#+++++++++++++++++++++++++++++#

exitcode=0
SVAR=
dialog --backtitle "OlFIX installation. Version "$VERSION \
--title "OLFIX INSTALLATION" \
--menu "Vill du starta installationen? " 10 60 2 \
J "Starta!" \
N "Avbryt" 2>$TEMP
exitcode=$?
echo "exitcode="$exitcode >> $LOGFILE
if [ $exitcode -eq 0 ]
then
	choice=`cat $TEMP`
	SVAR=$choice
	echo "SVAR = "$SVAR >> $LOGFILE
else
	dialog --backtitle "OLFIX installation. Version "$VERSION \
	--msgbox "** Installationen p�b�rjas ej! **" 5 45
	clear
	rm -f $TEMP
	echo "exitcode="$exitcode " SVAR = "$SVAR" Installationen p�b�rjas ej! (Cancel)" >> $LOGFILE
	exit
fi
rm -f $TEMP
if test $SVAR != "J";then
	exitcode=0
	dialog --backtitle "OLFIX installation. Version "$VERSION \
	--msgbox "** Installationen startas ej! **" 5 45
	echo "SVAR = "$SVAR" Installationen startas ej!" >> $LOGFILE
	date>>$LOGFILE
	clear
	rm -f $TEMP
	exit
fi
echo "P�b�rjar Installation av OLFIX!" >> $LOGFILE
date>>$LOGFILE
#+++++++++++++++++++++++++++++++++++++++++++++++++++++#
# -- Byt ut alla f�rekomster av 'ADMIN' till 'JAN'  --#
# -- samt kopiera in filen add_user_olfix.sql	    --#
#+++++++++++++++++++++++++++++++++++++++++++++++++++++#
echo "Redigerar CreateOLFIX.sql" >> $LOGFILE
namn=`echo $FNAMN|grep $FNAMN |awk '{print toupper($1)} '`
echo "Anv�ndarnamn = "$namn >> $LOGFILE

sed "s/'ADMIN'/'"$namn"'/" $OLFIX_SQL/CreateOLFIX_Update.sql > $HOME/tmp/CreateOLFIXNy.tmp

#+++++++++++++++++++++++++++++++++++++++++++++++++++++#
# -- Kopiera in filen add_user_olfix.sql	    --#
# -- Ska bara g�ras vid ny installation		    --#
#+++++++++++++++++++++++++++++++++++++++++++++++++++++#
if test $UPDATE == "N" ;then
	cat $HOME/tmp/CreateOLFIXNy.tmp add_user_olfix.sql >$HOME/tmp/CreateOLFIXNy.sql
	rm -f $HOME/tmp/CreateOLFIXNy.tmp
	mv $HOME/tmp/CreateOLFIXNy.sql $HOME/tmp/CreateOLFIX.sql
else
	mv $HOME/tmp/CreateOLFIXNy.tmp $HOME/tmp/CreateOLFIX.sql
fi
exitcode=0
#+++++++++++++++++++++++++++++++++++++++++++++++++++++#
# -- Skapar databaserna				    --#
#+++++++++++++++++++++++++++++++++++++++++++++++++++++#
echo "L�ser in CreateOLFIX.sql" >> $LOGFILE
echo "root password ="$ROOTPW >> $LOGFILE
# mysql -u root -p $ROOTPW < $HOME/tmp/CreateOLFIX.sql >& $HOME/tmp/mysql.log
mysql -u root < $HOME/tmp/CreateOLFIX.sql >& $HOME/tmp/mysql.log
#+++++++++++++++++++++++++++++++++++++++++++++++++++++#
# -- Kopiera resursfilen .olfixrc till $HOME	    --#
# -- Ska bara g�ras vid ny installation		    --#
#+++++++++++++++++++++++++++++++++++++++++++++++++++++#
if test $UPDATE == "N" ;then
	cp -f $HOME/.olfixrc $HOME/.olfixrc.old >& $LOGFILE
	cp -f $OLFIX_HOME/script/.olfixrc $HOME/.olfixrc >& $LOGFILE
	chmod 644 $HOME/.olfixrc
	echo "chmod 644 $HOME/.olfixrc" >> $LOGFILE
fi
echo "Installationen KLAR!" >> $LOGFILE
date>>$LOGFILE
clear
echo "********************************"
echo "***** Installationen KLAR! *****"
echo "********************************"
