#!/bin/sh
#
#**********************************
#***  OBS! Skall k�ras som root ***
#**********************************

# Namn: install.sh
# Version: 0.3b		2004-01-18 Jan Pihlgren.
# Version: 0.3a		2004-01-14 Jan Pihlgren.
# Version: 0.3		2004-01-08 Jan Pihlgren.
# Version: 0.2		2003-09-02 Jan Pihlgren.
# Version: 0.1d		2003-08-31 Jan Pihlgren.
# Version: 0.1c		2003-08-30 Jan Pihlgren.
# Version: 0.1b		2003-05-06 Jan Pihlgren. R�ttat OLFIX_SOURCE
# Version: 0.1
# Beskrivning: Installations/Uppdaterings script f�r OLFIX version X.X
# Tv� olika loggar skapas,
# en vid installation ($HOME/tmp/InstallOlfix.log)
# och en vid uppgradering ($HOME/tmp/UpdateOlfix.log)

VERSION="OLFIX_0.1.12.A"
# S�tt PATH
PATH=/bin:/sbin:/usr/bin:/usr/sbin

# S�tt OLFIX variabler
# ---------------------------------------------------------------
# install.sh anropas n�r man st�r i $OLFIX_HOME/script
# s� f�r att f� variabel OLFIX_HOME korrekt beh�ver man
# g� upp en niv�, s�tta OLFIX_HOME och sedan g� tillbaka till
# $OLFIX_HOME/script
# ---------------------------------------------------------------
cd ..
OLFIX_HOME=`pwd`
cd script
OLFIX_SOURCE=$OLFIX_HOME/src
OLFIX_SQL=$OLFIX_HOME/sql
OLFIX_DATA=$OLFIX_HOME/data

#QT variabler
QT=`whereis $QTDIR|awk '{print $2}'`
QT_BIN=$QT/bin
QT_INC=$QT/include
QT_LIB=$QT/lib

#MySQL variabler
MYSQLD=`whereis mysqld|awk '{print $2}'`

# TEMP anv�nds f�r att lagra svar fr�n dialog.
TEMP=/tmp/.tempfil

BEHOR=N
OLFIX_EXIST=N


dialog --begin 100 50
dialog --backtitle "OLFIX installation." \
	--msgbox "OLFIX version X\n\n Det h�r scriptet hj�lper dig att installera OLFIX.\n Efter ett antal fr�gor kommer OLFIX att installeras.\n\n Varje fr�ga har ett standandard svar,\n
om du tycker att det �r ok s� tryck bara p� [Enter].\n
Standardsvaret �r markerat med []\n\n Om du vill avbryta installation eller uppgradering\n innan arbetet p�b�rjas s� tryck Ctrl-C.\n" 15 60

#++++++++++++++++++++++++++++++++++++++++++++++++#
# -- Leta upp qt och dess mappar om dem finns -- #
#++++++++++++++++++++++++++++++++++++++++++++++++#

if [[ -d $QT && -d $QT_BIN && -d $QT_INC && -d $QT_LIB ]];then
	dialog --backtitle "OLFIX installation." \
	 --msgbox "** Hittade QT och dess undermappar p� $QT **" 5 60
else
	dialog --backtitle "OLFIX installation." \
	--msgbox "** Kunde inte hitta QT, du m�ste ha QT installerat\n.** Avbryter installationen!\n" 5 60
	exit
fi

#++++++++++++++++++++++++++++++++++++++++++++++++#
# -- leta upp mysqld samt kolla om den svarar -- #
#++++++++++++++++++++++++++++++++++++++++++++++++#

if [[ -f $MYSQLD ]];then
	dialog --backtitle "OLFIX installation." \
	--msgbox "** Hittade mysqld **" 5 27
else
	dialog --backtitle "OLFIX installation." \
	--msgbox "** Hittade inte mysqld\n **" 5 60
	exit
fi

#+++++++++++++++++++++++++++++++++++++++++++++++++++#
# -- Leta upp olfix och dess mappar om dem finns -- #
#+++++++++++++++++++++++++++++++++++++++++++++++++++#
if [[ -d $OLFIX_HOME ]];then
	OLFIX_EXIST=J
#	dialog --backtitle "OLFIX installation." \
#	--msgbox "** Hittade OLFIX p� $OLFIX_HOME, en installation finns redan. **" 5 75
else
	OLFIX_EXIST=N
	dialog --backtitle "OLFIX installation." \
	--msgbox "** Kunde inte hitta OLFIX! **" 5 60
	exit
fi

#++++++++++++++++++++++++++++++++++++++++++++++++?+++#
# -- �r det en installation eller en uppgradering -- #
#++++++++++++++++++++++++++++++++++++++++++++++++++++#

exitcode=0

dialog --backtitle "OLFIX installation." \
--title "OLFIX INSTALLATION" \
--menu "�r detta en Installation eller Uppgradering? " 10 60 2 \
U "Uppgradering" \
I "Installation" 2>$TEMP
exitcode=$?

if [ $exitcode -eq 0 ]
then
	choice=`cat $TEMP`
	case $choice in
	U) UPGRADE=$choice ;;
	I) UPGRADE=$choice ;;
	3) exitcode=1 ;;
	esac
fi
rm -f $TEMP
if [ $exitcode == 1 ]
then
	dialog --backtitle "OLFIX installation." \
	--msgbox "** Installationen avbr�ts! **" 5 35
	clear
	exit
fi

#if test $UPGRADE == "I" && test $OLFIX_EXIST == "J";then
#	OLDPATH=$OLFIX_HOME"_new"
#	dialog --backtitle "OLFIX installation." \
#	--msgbox "** Flyttar gammal installation fr�n "$OLFIX_HOME" till **\n** "$OLDPATH 10 70
#	mv $OLFIX_HOME $OLDPATH
#fi

if test $UPGRADE == "I" ;then
		dialog --backtitle "OLFIX installation." \
	 	--msgbox "** Du har valt att g�ra en INSTALLATION av OLFIX **" 5 60

		echo "** Installation av OLFIX">>$HOME/tmp/InstallOlfix.log
		date >>$HOME/tmp/InstallOlfix.log
#		**********************************************************
#		**********************************************************
#		*************         INSTALLATION           *************
#		**********************************************************
#		**********************************************************

#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#		Ska flera �n en person anv�nda OLFIX?
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		exitcode=0
		dialog --backtitle "OLFIX installation." \
		--title "OLFIX INSTALLATION" \
		--menu "Ska OLFIX anv�ndas av en(1) eller flera anv�ndare? " 10 60 2 \
		E "Enanv�ndarsystem." \
		F "Fleranv�ndarsystem" 2>$TEMP
		exitcode=$?

  		if [ $exitcode -eq 0 ]
  		then
      			choice=`cat $TEMP`
			case $choice in
			E) BEHOR=$choice ;;
			F) BEHOR=$choice ;;
			3) exitcode=1 ;;
			esac
 		fi
  		rm -f $TEMP
		if [ $exitcode == 1 ]
		then
			dialog --backtitle "OLFIX installation." \
			--msgbox "** Installationen avbr�ts! **" 5 35
			clear
			exit
		fi

  		if test $BEHOR == "E";then
  			dialog --backtitle "OLFIX installation." \
		 	--msgbox "** OLFIX installeras f�r anv�ndning av EN anv�ndare! **" 5 60
		fi
		if test $BEHOR != "E";then
  			dialog --backtitle "OLFIX installation." \
	 		--msgbox "** OLFIX installeras f�r anv�ndning av FLERA anv�ndare! **" 5 60
  		fi

#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#		H�mta USER och s�tt userid till versaler
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++

		uppername=`echo $USER | tr a-z A-Z`
		USER_ID=$uppername

#       	+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#		Ifall det �r EN anv�ndare s� ska vedreb�rande ha beh�righet
#		till alla program och funktioner som finns i $OLFIX_SQL/RIGHTSdata.sql
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		if test $BEHOR == "E";then
			exitcode=0
			dialog --backtitle "OLFIX installation." \
			--title "OLFIX INSTALLATION" \
			--inputbox "Vad �r ditt USERID? " 10 60 $USER_ID 2>$TEMP
			exitcode=$?

  			if [ $exitcode -eq 0 ]
  			then
      				choice=`cat $TEMP`
      				USER_ID=$choice
			else
				dialog --backtitle "OLFIX installation." \
				--msgbox "** Installationen avbr�ts! **" 5 35
				clear
				rm -f $TEMP
				exit
  			fi
  			rm -f $TEMP

#			+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#			S�tt USER_ID till versaler
#			+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			uppername=`echo $USER_ID | tr a-z A-Z`
			USER_ID=$uppername
			echo "** Userid=$USER_ID">>$HOME/tmp/InstallOlfix.log
#			+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#			Skapa tempor�r datafil med alla beh�righeter
#			+++++++++++++++++++++++++++++++++++++++++++++++++++++++++

			COMMAND="sed -e s/userid/$USER_ID/ $OLFIX_DATA/StandaloneRIGHTSdata.txt > $OLFIX_DATA/temprightdata.txt"
			echo -e $COMMAND>>$HOME/tmp/InstallOlfix.log
			eval $COMMAND
		fi
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#		Skapa tempor�r datafil med anv�ndardata f�r OLFIX (tabell USR)
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  		dialog --backtitle "OLFIX installation." \
	 	--msgbox "** Du ska nu ange F�RNAMN, EFTERNAMN, AVD och SEKTION\n som beh�vs f�r OLFIX **" 5 70
		exitcode=0
		dialog --backtitle "OLFIX installation." \
		--title "OLFIX INSTALLATION" \
		--inputbox "Ange ditt F�RNAMN! " 10 60  2>$TEMP
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
		--inputbox "Ange ditt EFTERNAMN! " 10 60  2>$TEMP
		exitcode=$?

		if [ $exitcode -eq 0 ]
			then
			choice=`cat $TEMP`
			ENAMN=$choice
		else
			dialog --backtitle "OLFIX installation." \
			--msgbox "** Installationen avbr�ts! **" 5 35
			clear
			rm -f $TEMP
			exit
		fi
		rm -f $TEMP

		AVD="Min_Avdelning"
		SEKT="Min_Sektion"

		exitcode=0
		dialog --backtitle "OLFIX installation." \
		--title "OLFIX INSTALLATION" \
		--inputbox "Med Avdelnig och Sektion menas din organisations ben�mningar p� dessa\nAnge din AVDELNING! " 10 60 $AVD 2>$TEMP
		exitcode=$?

		if [ $exitcode -eq 0 ]
			then
			choice=`cat $TEMP`
			AVD=$choice
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
		--inputbox "Med Avdelnig och Sektion menas din organisations ben�mningar p� dessa\nAnge din SEKTION! " 10 60 $SEKT 2>$TEMP
		exitcode=$?

		if [ $exitcode -eq 0 ]
			then
			choice=`cat $TEMP`
			SEKT=$choice
		else
			dialog --backtitle "OLFIX installation." \
			--msgbox "** Installationen avbr�ts! **" 5 35
			clear
			rm -f $TEMP
			exit

		fi
		rm -f $TEMP

		COMMAND="sed -e s/USERID/$USER_ID/ $OLFIX_DATA/USRdata.txt > $HOME/tmp/usrdata.txt"
		eval $COMMAND
		cp $HOME/tmp/usrdata.txt $HOME/tmp/usrdata2.txt
		COMMAND="sed -e s/Ditt/$FNAMN/ $HOME/tmp/usrdata2.txt > $HOME/tmp/usrdata.txt"
		eval $COMMAND
		cp $HOME/tmp/usrdata.txt $HOME/tmp/usrdata2.txt
		COMMAND="sed -e s/Namn/$ENAMN/ $HOME/tmp/usrdata2.txt > $HOME/tmp/usrdata.txt"
		eval $COMMAND
		cp $HOME/tmp/usrdata.txt $HOME/tmp/usrdata2.txt
		COMMAND="sed -e s/Avd/$AVD/ $HOME/tmp/usrdata2.txt > $HOME/tmp/usrdata.txt"
		eval $COMMAND
		cp $HOME/tmp/usrdata.txt $HOME/tmp/usrdata2.txt
		COMMAND="sed -e s/Sektion/$SEKT/ $HOME/tmp/usrdata2.txt > $HOME/tmp/usrdata.txt"
		eval $COMMAND
		echo "F�rnamn=$FNAMN">>$HOME/tmp/InstallOlfix.log
		echo "Efternamn=$ENAMN">>$HOME/tmp/InstallOlfix.log
		echo "Avdelning=$AVD">>$HOME/tmp/InstallOlfix.log
		echo "Sektion=$SEKT">>$HOME/tmp/InstallOlfix.log

		cp $HOME/tmp/usrdata.txt $OLFIX_DATA/LoadUSRdata.txt
		rm $HOME/tmp/usrdata.txt
		rm $HOME/tmp/usrdata2.txt

#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#		Skapa tempor�r datafil med anv�ndardata f�r mysql (tabell user)
#		Att anv�nda f�r att administrera OLFIX
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		COMMAND="sed -e s/DittNamn/$USER/ $OLFIX_SQL/mall_add_user_DittNamn.sql > $HOME/tmp/mysqldata.sql"
		eval $COMMAND
		cp $HOME/tmp/mysqldata.sql $HOME/tmp/mysqldata2.sql

		exitcode=0
		dialog --backtitle "OLFIX installation." \
		--title "OLFIX INSTALLATION" \
		--passwordbox "Ange password som user f�r MySQL!" 10 60  2>$TEMP
		exitcode=$?

		if [ $exitcode -eq 0 ]
			then
			choice=`cat $TEMP`
			LOSENORD=$choice
		else
			dialog --backtitle "OLFIX installation." \
			--msgbox "** Installationen avbr�ts! **" 5 35
			clear
			rm -f $TEMP
			exit
		fi
		exit
		rm -f $TEMP

		COMMAND="sed -e s/DittPassword/$LOSENORD/ $HOME/tmp/mysqldata2.sql > $HOME/tmp/mysqldata.sql"
		eval $COMMAND
		# Spara orginalfilen
		cp $OLFIX_SQL/add_user_DittNamn.sql $OLFIX_SQL/add_user_DittNamn.org.sql
		# Flytta den nya filen
		cp $HOME/tmp/mysqldata.sql $OLFIX_SQL/add_user_DittNamn.sql
		rm $HOME/tmp/mysqldata2.sql
		rm $HOME/tmp/mysqldata.sql

#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#		OK att starta installationen?
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		exitcode=0
		dialog --backtitle "OLFIX installation." \
		--title "OLFIX INSTALLATION" \
		--menu "OK att starta installationen? " 10 60 2 \
		J "Starta installationen!" \
		N "Avbryt installationen" 2>$TEMP
		exitcode=$?

  		if [ $exitcode -eq 0 ]
  		then
      			choice=`cat $TEMP`
      			SVAR=$choice
		else
			dialog --backtitle "OLFIX installation." \
			--msgbox "** Installationen avbr�ts! **" 5 35
			clear
			rm -f $TEMP
			exit
  		fi
  		rm -f $TEMP

		if test $SVAR != "J";then
			exitcode=0
			dialog --backtitle "OLFIX installation." \
			--msgbox "** Installationen avbryts! **" 5 35
			# �terst�ll orginalfilen
			cp $OLFIX_SQL/add_user_DittNamn.org.sql $OLFIX_SQL/add_user_DittNamn.sql
			echo -e "** Installationen avbryts!">>$HOME/tmp/InstallOlfix.log
			date>>$HOME/tmp/InstallOlfix.log
			clear
			rm -f $TEMP
			exit
		fi
#		exitcode=0
#		dialog --backtitle "OLFIX installation." \
#		--msgbox "** Nu startar installationen! **" 5 35

#		*******************************************************************
#		***			H�R B�RJAR INSTALLATIONEN		***
#		*******************************************************************

#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#		Ifall det �r en ominstallation ska inte user 'olfix'
#		och user 'dig' �ndras i databasen mysql
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		OLFIX_USER_EXIST="N"
		DIG_USER_EXIST="N"

		exitcode=0
		dialog --backtitle "OLFIX installation." \
		--title "OLFIX INSTALLATION" \
		--passwordbox "Ange rootpassword f�r root som user i MySQL!" 10 70  2>$TEMP
		exitcode=$?

		if [ $exitcode -eq 0 ]
		then
			choice=`cat $TEMP`
			LOSENORD=$choice
		else
			dialog --backtitle "OLFIX installation." \
			--msgbox "** Installationen avbr�ts! **" 5 35
			clear
			rm -f $TEMP
			exit
		fi
		rm -f $TEMP
		if test ${USERNAME-$USER} != 'root'
		then
			dialog --backtitle "OLFIX installation." \
			--msgbox "** Installationen avbr�ts! **\n** Inte root som k�r installationen! **" 10 45
			clear
			exit
		fi

		mysqldump mysql user -u$USERNAME $LOSENORD > $HOME/tmp/user.txt
		grep $USER $HOME/tmp/user.txt -c >$TEMP
		choice=`cat $TEMP`
		case $choice in
		0) DIG_USER_EXIST="N";;
		1) DIG_USER_EXIST="J";;
		esac
		rm -f $TEMP
		grep olfix $HOME/tmp/user.txt -c >$TEMP
		choice=`cat $TEMP`
		case $choice in
		0) OLFIX_USER_EXIST="N";;
		1) OLFIX_USER_EXIST="J";;
		esac
		rm -f $TEMP
		rm -f $HOME/tmp/user.txt

		if OLFIX_USER_EXIST=="N"
		then
#			+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#			L�gg till user olfix i databasen mysql
#			+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			echo -e "** L�gger till user olfix!">>$HOME/tmp/InstallOlfix.log
			COMMAND="mysql -h localhost -p <$OLFIX_SQL/add_user_olfix.sql>$HOME/tmp/InstallOlfix.log"
			eval $COMMAND
			echo $COMMAND>>$HOME/tmp/InstallOlfix.log
		fi
		if OLFIX_USER_EXIST=="N"
		then
#			+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#			L�gg till user 'dig' som user i databasen mysql, med adminbeh�righeter
#			+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#			echo -e "** L�gger upp dig som user i mysql!">>$HOME/tmp/InstallOlfix.log
#			COMMAND="mysql -h localhost -p <$OLFIX_SQL/add_user_DittNamn.sql>$HOME/tmp/InstallOlfix.log"
			eval $COMMAND
#			echo $COMMAND>>$HOME/tmp/InstallOlfix.log
			# �terst�ller orginalfilen
			rm $OLFIX_SQL/add_user_DittNamn.sql
			cp $OLFIX_SQL/mall_add_user_DittNamn.sql $OLFIX_SQL/add_user_DittNamn.sql
		fi
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#		Skapa databasen olfix.
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		echo -e "** Skapar databasen olfix!">>$HOME/tmp/InstallOlfix.log
		COMMAND="mysql -h localhost -p <$OLFIX_SQL/CreateDatabaseOlfix.sql>$HOME/tmp/InstallOlfix.log"
		eval $COMMAND
		echo $COMMAND>>$HOME/tmp/InstallOlfix.log

#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#		Skapa tabller.
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		echo -e "** Skapar tabeller till OLFIX!">>$HOME/tmp/InstallOlfix.log
		COMMAND="mysql -h localhost -p <$OLFIX_SQL/CreateAll.sql>$HOME/tmp/InstallOlfix.log"
		eval $COMMAND
		echo $COMMAND>>$HOME/tmp/InstallOlfix.log

#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#		Ladda tabeller (FTGDATA, KTOPLAN, TRANSID, VALUTA, PROGRAM)
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		echo -e "** Laddar tabellerna i OLFIX!">>$HOME/tmp/InstallOlfix.log
		COMMAND="mysql -h localhost -p <$OLFIX_SQL/LoadAll.sql>$HOME/tmp/InstallOlfix.log"
		eval $COMMAND
		echo $COMMAND>>$HOME/tmp/InstallOlfix.log

#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#		Uppdatera tabellen RIGHTS.
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		echo -e "** Uppdaterar beh�righeter till OLFIX!">>$HOME/tmp/InstallOlfix.log
		if test $BEHOR == "E";then
			COMMAND="mysql -h localhost -p <$OLFIX_SQL/LoadStandaloneRIGHTSdata.sql>$HOME/tmp/InstallOlfix.log"
			rm $OLFIX_DATA/temprightdata.txt
		else
			COMMAND="mysql -h localhost -p <$OLFIX_SQL/LoadRIGHTSdata.sql>$HOME/tmp/InstallOlfix.log"
		fi
		eval $COMMAND
		echo $COMMAND>>$HOME/tmp/InstallOlfix.log

#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#		Uppdatera tabellen USR.
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		echo -e "** Uppdaterar tabell USR till OLFIX!">>$HOME/tmp/InstallOlfix.log
		COMMAND="mysql -h localhost -p <$OLFIX_SQL/LoadRIGHTSdata.sql>$HOME/tmp/InstallOlfix.log"
		eval $COMMAND
		echo $COMMAND>>$HOME/tmp/InstallOlfix.log

#		rm $OLFIX_DATA/LoadUSRdata.txt
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#		Installation av databasen olfix �r klar
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#		Installera testdatabasen olfixtst
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		echo -e "** Skapar testdatabasen olfixtst!">>$HOME/tmp/InstallOlfix.log
		COMMAND="mysql -h localhost -p <$OLFIX_SQL/CreateAllOlfixtst.sql>$HOME/tmp/InstallOlfix.log"
		eval $COMMAND
		echo $COMMAND>>$HOME/tmp/InstallOlfix.log

#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#		Ladda testdatabasen olfixtst
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		echo -e "** Laddar testdatabasen olfixtst!">>$HOME/tmp/InstallOlfix.log
		COMMAND="mysql -h localhost -p <$OLFIX_SQL/LoadAll_olfixtst.sql>$HOME/tmp/InstallOlfix.log"
		eval $COMMAND
		echo $COMMAND>>$HOME/tmp/InstallOlfix.log

#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#		Kopiera filen .olficrc till $HOME
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		COMMAND="sed -e s,/usr/local/olfix,$OLFIX_HOME, $OLFIX_HOME/script/.olfixrc >  $OLFIX_HOME/script/.olfixrc.tmp"
		eval $COMMAND
		rm -f $OLFIX_HOME/script/.olfixrc
		mv $OLFIX_HOME/script/.olfixrc.tmp $OLFIX_HOME/script/.olfixrc
		rm -f $OLFIX_HOME/script/.olfixrc.tmp
		cp $OLFIX_HOME/script/.olfixrc $HOME/.olfixrc
		cp $OLFIX_HOME/script/.olfixrc /home/$USER/.olfixrc

#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#		Installation klar!
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		date>>$HOME/tmp/InstallOlfix.log
		echo -e "\n** Uppgradering klar!\n">>$HOME/tmp/UpdateOlfix.log
		dialog --backtitle "OLFIX installation." \
		--msgbox "** Installation klar! **" \ 5 40

		exit

else

#		**********************************************************
#		**********************************************************
#		*************         UPPGRADERING           *************
#		**********************************************************
#		**********************************************************
#		++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#		Anteckna versionsnummer
#		++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

		date >>$HOME/tmp/UpdateOlfix.log
		echo -e "** Uppgradering till version nr $VERSION">>$HOME/tmp/UpdateOlfix.log

		dialog --backtitle "OLFIX uppgradering." \
	 	--msgbox "** Uppgradering till version nr $VERSION           **\n** Du har valt att g�ra en UPPGRADERING av OLFIX.        **\n** Din OLFIXdatabas kommer att backas upp till           **\n** /root/tmp/OLFIXDATABASE.bak. En eventuell tidigare    **\n** bakupfil namn�ndras till /root/tmp/OLFIXDATABASE.old. ** " 10 65

#		++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#		Ange f�rnamn
#		++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

		exitcode=0
		dialog --backtitle "OLFIX uppgradering." \
		--title "OLFIX UPPGRADERING" \
		--inputbox "Ange ditt F�RNAMN! " 10 60  2>$TEMP
		exitcode=$?

		if [ $exitcode -eq 0 ]
		then
			choice=`cat $TEMP`
			FNAMN=$choice
		else
			dialog --backtitle "OLFIX uppgradering." \
			--msgbox "** Uppgraderingen avbr�ts! **" 5 35
			clear
			exit
		fi
		rm -f $TEMP

#		++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#		Ska flera �n en person anv�nda OLFIX?
#		++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		exitcode=0
		dialog --backtitle "OLFIX uppgradering." \
		--title "OLFIX UPPGRADERING" \
		--menu "Ska OLFIX anv�ndas av en(1) eller flera anv�ndare? " 10 60 2 \
		E "Enanv�ndarsystem." \
		F "Fleranv�ndarsystem" 2>$TEMP
		exitcode=$?

  		if [ $exitcode -eq 0 ]
  		then
      			choice=`cat $TEMP`
 	     		BEHOR=$choice
		else
			dialog --backtitle "OLFIX uppgradering." \
			--msgbox "** Uppgraderingen avbr�ts! **" 5 35
			clear
			exit
 		fi
  		rm -f $TEMP

  		if test $BEHOR == "E";then
  			dialog --backtitle "OLFIX uppgradering." \
		 	--msgbox "** OLFIX uppgraderas f�r anv�ndning av EN anv�ndare! **" 5 60
			echo -e "** OLFIX anv�nds av EN anv�ndare">>$HOME/tmp/UpdateOlfix.log
		fi
		if test $BEHOR != "E";then
  			dialog --backtitle "OLFIX uppgradering." \
	 		--msgbox "** OLFIX uppgraderas f�r anv�ndning av FLERA anv�ndare! **" 5 60
			echo -e "** OLFIX anv�nds av FLERA anv�ndare">>$HOME/tmp/UpdateOlfix.log
  		fi

#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#		Om bara en anv�ndare s� ska vederb�rande ha beh�righet
#		till alla program och funktioner som finns i
#		$OLFIX_SQL/RIGHTSdata.sql
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		uppername=`echo $USER | tr a-z A-Z`
		USER_ID=$uppername

		if test $BEHOR == "E";then
			exitcode=0
			dialog --backtitle "OLFIX uppgradering." \
			--title "OLFIX UPPGRADERING" \
			--inputbox "Vad �r ditt USERID? " 10 60 $USER_ID 2>$TEMP
			exitcode=$?

  			if [ $exitcode -eq 0 ]
  			then
      				choice=`cat $TEMP`
      				USER_ID=$choice
			else
				dialog --backtitle "OLFIX uppgradering." \
				--msgbox "** Uppgraderingen avbr�ts! **" 5 35
				clear
				exit
  			fi
  			rm -f $TEMP
#			+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#			S�tt userid till versaler
#			+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			uppername=`echo $USER_ID | tr a-z A-Z`
			USER_ID=$uppername
			echo "** Userid=$USER_ID">>$HOME/tmp/UpdateOlfix.log

#			+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#			Skapa tempor�r datafil med alla beh�righeter
#			+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			COMMAND="sed -e s/userid/$USER_ID/ $OLFIX_DATA/StandaloneRIGHTSdata.txt > $OLFIX_DATA/temprightdata.txt"
			echo "Create tempfil f�r r�ttigheter">>$HOME/tmp/UpdateOlfix.log
#			echo "COMMAND="$COMMAND
			eval $COMMAND
		fi
		dialog --backtitle "OLFIX uppgradering." \
		--msgbox "** Nu startar uppgradering **" \ 5 40

		echo "** Nu startar uppgradering">>$HOME/tmp/UpdateOlfix.log
		date >>$HOME/tmp/UpdateOlfix.log
		mkdir $OLFIX_DATA/$VERSION
		COMMAND="chown $USER $OLFIX_DATA/$VERSION"
		echo $COMMAND>>$HOME/tmp/UpdateOlfix.log
		eval $COMMAND
		COMMAND="chgrp $USER $OLFIX_DATA/$VERSION"
		echo $COMMAND>>$HOME/tmp/UpdateOlfix.log
		eval $COMMAND
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#		Backa up OLFIXdatabasen.
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		if [[ -f $HOME/tmp/OLFIXDATABASE.bak ]];then
			COMMAND="mv $HOME/tmp/OLFIXDATABASE.bak $HOME/tmp/OLFIXDATABASE.old"
			echo $COMMAND>>$HOME/tmp/UpdateOlfix.log
			eval $COMMAND
		fi
		exitcode=0
		dialog --backtitle "OLFIX uppgradering." \
		--title "OLFIX UPPGRADERING." \
		--passwordbox "Ange ditt password till OLFIXdatabasen" 10 60  2>$TEMP
		exitcode=$?

		if [ $exitcode -eq 0 ]
			then
			choice=`cat $TEMP`
			DITTPW=$choice
		else
			dialog --backtitle "OLFIX uppgradering." \
			--msgbox "** Uppgraderingen avbr�ts! **" 5 35
			clear
			exit
		fi
		rm -f $TEMP

		COMMAND="/usr/bin/mysqldump -u$USER -p$DITTPW -q olfix > $HOME/tmp/OLFIXDATABASE.bak"
		eval $COMMAND
		COMMAND="/usr/bin/mysqldump -u$USER -p -q olfix > $HOME/tmp/OLFIXDATABASE.bak"
		echo $COMMAND>>$HOME/tmp/UpdateOlfix.log
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#		Uppdatera tabellen RIGHTS, r�ttigheter/beh�righeter.
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		if test $BEHOR == "E";then
			COMMAND="mysql -h localhost -p$DITTPW <$OLFIX_SQL/LoadStandaloneRIGHTSdata.sql>>$HOME/tmp/UpdateOlfix.log"
			eval $COMMAND
			COMMAND="mysql -h localhost <$OLFIX_SQL/LoadStandaloneRIGHTSdata.sql>>$HOME/tmp/UpdateOlfix.log"
			echo $COMMAND>>$HOME/tmp/UpdateOlfix.log
			rm $OLFIX_DATA/temprightdata.txt
		fi
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#		Uppdatera tabellen PROGRAM.
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		COMMAND="mysql -h localhost -u$USER -p$DITTPW <$OLFIX_SQL/LoadPROGRAM.sql>>$HOME/tmp/UpdateOlfix.log"
		eval $COMMAND
		COMMAND="mysql -h localhost -u$USER <$OLFIX_SQL/LoadPROGRAM.sql>>$HOME/tmp/UpdateOlfix.log"
		echo $COMMAND>>$HOME/tmp/UpdateOlfix.log
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#		Uppdatera tabellen TRANSID.
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		COMMAND="mysql -h localhost -u$USER -p$DITTPW <$OLFIX_SQL/LoadTRANSID.sql>>$HOME/tmp/UpdateOlfix.log"
		eval $COMMAND
		COMMAND="mysql -h localhost -u$USER <$OLFIX_SQL/LoadTRANSID.sql>>$HOME/tmp/UpdateOlfix.log"
		echo $COMMAND>>$HOME/tmp/UpdateOlfix.log
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#		Plats f�r andra uppdateringar mm
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#		Uppdatering klar!
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		date>>$HOME/tmp/UpdateOlfix.log
		echo -e "\n** Uppgradering klar!\n">>$HOME/tmp/UpdateOlfix.log
		dialog --backtitle "OLFIX uppgradering." \
		--msgbox "** Uppgradering klar! **" \ 5 40
fi

exit
