#!/bin/sh
#
#**********************************
#***  OBS! Skall köras som root ***
#**********************************

# Namn: install.sh
# Version: 0.3		2004-01-08 Jan Pihlgren.
# Version: 0.2		2003-09-02 Jan Pihlgren.
# Version: 0.1d		2003-08-31 Jan Pihlgren.
# Version: 0.1c		2003-08-30 Jan Pihlgren.
# Version: 0.1b		2003-05-06 Jan Pihlgren. Rättat OLFIX_SOURCE
# Version: 0.1
# Beskrivning: Installations/Uppdaterings script för OLFIX version X.X
# Två olika loggar skapas, en vid installation ($HOME/tmp/InstallOlfix.log)
# och en vid uppgradering ($HOME/tmp/UpdateOlfix.log)

OLFIX_BANNER="\n------------------------------------------------------------\n
-- OLFIX version X --\n\n
Det här scriptet hjälper dig att installera OLFIX,\n
efter ett antal frågor kommer OLFIX installeras på \n\n

Varje fråga har ett standandard svar,\n
om du tycker att det är ok så tryck bara på [Enter].\n
Standardsvaret är markerat med []\n

Om du vill avbryta installation eller uppgradering\n
innan arbetet påbörjas så tryck Ctrl-C.\n
 ------------------------------------------------------------\n"
VERSION="OLFIX_0.1.12.A"
# Sätt PATH
PATH=/bin:/sbin:/usr/bin:/usr/sbin
# Sätt OLFIX variabler
OLFIX_HOME=/usr/local/olfix
OLFIX_SOURCE=/usr/local/olfix/src
OLFIX_SQL=/usr/local/olfix/sql
OLFIX_DATA=/usr/local/olfix/data

#QT variabler
#QT=/usr/lib/qt3
#QT_BIN=/usr/lib/qt3/bin
#QT_INC=/usr/lib/qt3/include
#QT_LIB=/usr/lib/qt3/lib

QT=`whereis $QTDIR|awk '{print $2}'`
QT_BIN=$QT/bin
QT_INC=$QT/include
QT_LIB=$QT/lib

#MySQL variabler
MYSQLD=`whereis mysqld|awk '{print $2}'`

# TEMP används för att lagra svar från dialog.
TEMP=/tmp/.tempfil
BEHOR=N
OLFIX_EXIST=N


dialog --begin 100 50
dialog --backtitle "OLFIX installation." \
	--msgbox "OLFIX version X\n\n Det här scriptet hjälper dig att installera OLFIX.\n Efter ett antal frågor kommer OLFIX att installeras.\n\n Varje fråga har ett standandard svar,\n
om du tycker att det är ok så tryck bara på [Enter].\n
Standardsvaret är markerat med []\n\n Om du vill avbryta installation eller uppgradering\n innan arbetet påbörjas så tryck Ctrl-C.\n" 15 60

#++++++++++++++++++++++++++++++++++++++++++++++++#
# -- Leta upp qt och dess mappar om dem finns -- #
#++++++++++++++++++++++++++++++++++++++++++++++++#

if [[ -d $QT && -d $QT_BIN && -d $QT_INC && -d $QT_LIB ]];then
	dialog --backtitle "OLFIX installation." \
	 --msgbox "** Hittade QT och dess undermappar på $QT **" 5 60
else
	dialog --backtitle "OLFIX installation." \
	--msgbox "** Kunde inte hitta QT, du måste ha QT installerat\n.** Avbryter installationen!\n" 5 60
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

#är inte säker om den här testen är så optimal, inte klar!!!!
#MYSQL_EXEC=`mysql -u guest < quit``

#+++++++++++++++++++++++++++++++++++++++++++++++++++#
# -- Leta upp olfix och dess mappar om dem finns -- #
#+++++++++++++++++++++++++++++++++++++++++++++++++++#
if [[ -d $OLFIX_HOME ]];then
	OLFIX_EXIST=J
	dialog --backtitle "OLFIX installation." \
	--msgbox "** Hittade OLFIX på $OLFIX_HOME, en installation finns redan. **" 5 75
else
	OLFIX_EXIST=N
	dialog --backtitle "OLFIX installation." \
	--msgbox "** Kunde inte hitta OLFIX! **" 5 60
fi

#++++++++++++++++++++++++++++++++++++++++++++++++?+++#
# -- Är det en installation eller en uppgradering -- #
#++++++++++++++++++++++++++++++++++++++++++++++++++++#

exitcode=0

dialog --backtitle "OLFIX installation." \
--title "OLFIX INSTALLATION" \
--menu "Är detta en Installation eller Uppgradering? " 10 60 2 \
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
	--msgbox "** Installationen avbröts! **" 5 35
	clear
	exit
fi

if test $UPGRADE == "I" && test $OLFIX_EXIST == "J";then
	dialog --backtitle "OLFIX installation." \
 	--msgbox "** En redan befintlig installation kommer att skrivas över! **" 5 70
fi

if test $UPGRADE == "I" ;then
		dialog --backtitle "OLFIX installation." \
	 	--msgbox "** Du har valt att göra en INSTALLATION av OLFIX **" 5 60

#		echo "** Installation av OLFIX">>$HOME/tmp/InstallOlfix.log
#		date >>$HOME/tmp/InstallOlfix.log
#		**********************************************************
#		**********************************************************
#		*************         INSTALLATION           *************
#		**********************************************************
#		**********************************************************

#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#		Ska flera än en person använda OLFIX?
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		exitcode=0
		dialog --backtitle "OLFIX installation." \
		--title "OLFIX INSTALLATION" \
		--menu "Ska OLFIX användas av en(1) eller flera användare? " 10 60 2 \
		E "Enanvändarsystem." \
		F "Fleranvändarsystem" 2>$TEMP
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
			--msgbox "** Installationen avbröts! **" 5 35
			clear
			exit
		fi

  		if test $BEHOR == "E";then
  			dialog --backtitle "OLFIX installation." \
		 	--msgbox "** OLFIX installeras för användning av EN användare! **" 5 60
		fi
		if test $BEHOR != "E";then
  			dialog --backtitle "OLFIX installation." \
	 		--msgbox "** OLFIX installeras för användning av FLERA användare! **" 5 60
  		fi

#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#		Sätt userid till versaler
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++

		uppername=`echo $USER | tr a-z A-Z`
		USER_ID=$uppername

#       	+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#		En användare
#		så ska vedrebörande ha behörighet
#		till alla program och funktioner som finns i
#		$OLFIX_SQL/RIGHTSdata.sql
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		if test $BEHOR == "E";then
			exitcode=0
			dialog --backtitle "OLFIX installation." \
			--title "OLFIX INSTALLATION" \
			--inputbox "Vad är ditt USERID? " 10 60 $USER_ID 2>$TEMP
			exitcode=$?

  			if [ $exitcode -eq 0 ]
  			then
      				choice=`cat $TEMP`
      				USER_ID=$choice
			else
				dialog --backtitle "OLFIX installation." \
				--msgbox "** Installationen avbröts! **" 5 35
				clear
				exit
  			fi
  			rm -f $TEMP

#			+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#			Sätt userid till versaler
#			+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			uppername=`echo $USER_ID | tr a-z A-Z`
			USER_ID=$uppername
			echo "** Userid=$USER_ID">>$HOME/tmp/InstallOlfix.log
#			+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#			Skapa temporär datafil med alla behörigheter
#			+++++++++++++++++++++++++++++++++++++++++++++++++++++++++

			COMMAND="sed -e s/userid/$USER_ID/ $OLFIX_DATA/StandaloneRIGHTSdata.txt > $OLFIX_DATA/temprightdata.txt"
			echo -e $COMMAND>>$HOME/tmp/InstallOlfix.log
			eval $COMMAND
		fi
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#		Skapa temporär datafil med användardata för OLFIX (tabell USR)
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  		dialog --backtitle "OLFIX installation." \
	 	--msgbox "** Du ska nu ange FÖRNAMN, EFTERNAMN, AVD och SEKTION\n som behövs för OLFIX **" 5 70
		exitcode=0
		dialog --backtitle "OLFIX installation." \
		--title "OLFIX INSTALLATION" \
		--inputbox "Ange ditt FÖRNAMN! " 10 60  2>$TEMP
		exitcode=$?

		if [ $exitcode -eq 0 ]
			then
			choice=`cat $TEMP`
			FNAMN=$choice
		else
			dialog --backtitle "OLFIX installation." \
			--msgbox "** Installationen avbröts! **" 5 35
			clear
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
			--msgbox "** Installationen avbröts! **" 5 35
			clear
			exit
		fi
		rm -f $TEMP

		AVD="Min_Avdelning"
		SEKT="Min_Sektion"

		exitcode=0
		dialog --backtitle "OLFIX installation." \
		--title "OLFIX INSTALLATION" \
		--inputbox "Med Avdelnig och Sektion menas din organisations benämningar på dessa\nAnge din AVDELNING! " 10 60 $AVD 2>$TEMP
		exitcode=$?

		if [ $exitcode -eq 0 ]
			then
			choice=`cat $TEMP`
			AVD=$choice
		else
			dialog --backtitle "OLFIX installation." \
			--msgbox "** Installationen avbröts! **" 5 35
			clear
			exit
		fi
		rm -f $TEMP
		exitcode=0
		dialog --backtitle "OLFIX installation." \
		--title "OLFIX INSTALLATION" \
		--inputbox "Med Avdelnig och Sektion menas din organisations benämningar på dessa\nAnge din SEKTION! " 10 60 $SEKT 2>$TEMP
		exitcode=$?

		if [ $exitcode -eq 0 ]
			then
			choice=`cat $TEMP`
			SEKT=$choice
		else
			dialog --backtitle "OLFIX installation." \
			--msgbox "** Installationen avbröts! **" 5 35
			clear
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
		echo "Förnamn=$FNAMN">>$HOME/tmp/InstallOlfix.log
		echo "Efternamn=$ENAMN">>$HOME/tmp/InstallOlfix.log
		echo "Avdelning=$AVD">>$HOME/tmp/InstallOlfix.log
		echo "Sektion=$SEKT">>$HOME/tmp/InstallOlfix.log

		cp $HOME/tmp/usrdata.txt $OLFIX_DATA/LoadUSRdata.txt
		rm $HOME/tmp/usrdata.txt
		rm $HOME/tmp/usrdata2.txt

#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#		Skapa temporär datafil med användardata för mysql (tabell user)
#		Att använda för att administrera OLFIX
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		COMMAND="sed -e s/DittNamn/$USER/ $OLFIX_SQL/mall_add_user_DittNamn.sql > $HOME/tmp/mysqldata.sql"
		eval $COMMAND
		cp $HOME/tmp/mysqldata.sql $HOME/tmp/mysqldata2.sql

		exitcode=0
		dialog --backtitle "OLFIX installation." \
		--title "OLFIX INSTALLATION" \
		--passwordbox "Ange password som user för MySQL!" 10 60  2>$TEMP
		exitcode=$?

		if [ $exitcode -eq 0 ]
			then
			choice=`cat $TEMP`
			LOSENORD=$choice
		else
			dialog --backtitle "OLFIX installation." \
			--msgbox "** Installationen avbröts! **" 5 35
			clear
			exit
		fi
		rm -f $TEMP

		COMMAND="sed -e s/DittPassword/$LOSENORD/ $HOME/tmp/mysqldata2.sql > $HOME/tmp/mysqldata.sql"
		eval $COMMAND
		cp $OLFIX_SQL/add_user_DittNamn.sql $OLFIX_SQL/add_user_DittNamn.org.sql
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
			--msgbox "** Installationen avbröts! **" 5 35
			clear
			exit
  		fi
  		rm -f $TEMP

		if test $SVAR != "J";then
			exitcode=0
			dialog --backtitle "OLFIX installation." \
			--msgbox "** Installationen avbryts! **" 5 35
			cp $OLFIX_SQL/add_user_DittNamn.org.sql $OLFIX_SQL/add_user_DittNamn.sql
			echo -e "** Installationen avbryts!">>$HOME/tmp/InstallOlfix.log
			date>>$HOME/tmp/InstallOlfix.log
			clear
			exit
		fi
		exitcode=0
		dialog --backtitle "OLFIX installation." \
		--msgbox "** Nu startar installationen! **" 5 35

		exit
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#		Skapa databasen olfix.
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		echo -e "** Skapar databasen olfix!"
		echo -e "** Skapar databasen olfix!">>$HOME/tmp/InstallOlfix.log
		COMMAND="mysql -h localhost -p <$OLFIX_SQL/CreateDatabaseOlfix.sql>$HOME/tmp/InstallOlfix.log"
		echo $COMMAND
		echo $COMMAND>>$HOME/tmp/InstallOlfix.log

#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#		Lägg till user olfix.
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		echo -e "** Lägger till user olfix!"
		echo -e "** Lägger till user olfix!">>$HOME/tmp/InstallOlfix.log
		COMMAND="mysql -h localhost -p <$OLFIX_SQL/add_user_olfix.sql>$HOME/tmp/InstallOlfix.log"
		echo $COMMAND
		echo $COMMAND>>$HOME/tmp/InstallOlfix.log

#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#		Lägg till user admin, dig som user i mysql
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#		echo -e "** Lägger upp dig som user i mysql!"
#		echo -e "** Lägger upp dig som user i mysql!">>$HOME/tmp/InstallOlfix.log
#		COMMAND="mysql -h localhost -p <$OLFIX_SQL/add_user_DittNamn.sql>$HOME/tmp/InstallOlfix.log"
#		echo $COMMAND
#		echo $COMMAND>>$HOME/tmp/InstallOlfix.log
#		rm $OLFIX_SQL/add_user_DittNamn.sql
#		cp mall_add_user_DittNamn.sql add_user_DittNamn.sql

#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#		Skapa tabller.
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		echo -e "** Skapar tabeller till OLFIX!"
		echo -e "** Skapar tabeller till OLFIX!">>$HOME/tmp/InstallOlfix.log
		COMMAND="mysql -h localhost -p <$OLFIX_SQL/CreateAll.sql>$HOME/tmp/InstallOlfix.log"
		echo $COMMAND
		echo $COMMAND>>$HOME/tmp/InstallOlfix.log

#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#		Ladda tabeller (FTGDATA, KTOPLAN, TRANSID, VALUTA, PROGRAM)
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		echo -e "** Laddar tabellerna i OLFIX!"
		echo -e "** Laddar tabellerna i OLFIX!">>$HOME/tmp/InstallOlfix.log
		COMMAND="mysql -h localhost -p <$OLFIX_SQL/LoadAll.sql>$HOME/tmp/InstallOlfix.log"
		echo $COMMAND
		echo $COMMAND>>$HOME/tmp/InstallOlfix.log

#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#		Uppdatera tabellen RIGHTS.
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		echo -e "** Uppdaterar behörigheter till OLFIX!"
		echo -e "** Uppdaterar behörigheter till OLFIX!">>$HOME/tmp/InstallOlfix.log
		if test $BEHOR == "E";then
			COMMAND="mysql -h localhost -p <$OLFIX_SQL/LoadStandaloneRIGHTSdata.sql>$HOME/tmp/InstallOlfix.log"
#			rm $OLFIX_DATA/temprightdata.txt
		else
			COMMAND="mysql -h localhost -p <$OLFIX_SQL/LoadRIGHTSdata.sql>$HOME/tmp/InstallOlfix.log"
		fi
		echo $COMMAND
		echo $COMMAND>>$HOME/tmp/InstallOlfix.log

#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#		Uppdatera tabellen USR.
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		echo -e "** Uppdaterar tabell USR till OLFIX!"
		echo -e "** Uppdaterar tabell USR till OLFIX!">>$HOME/tmp/InstallOlfix.log
		COMMAND="mysql -h localhost -p <$OLFIX_SQL/LoadRIGHTSdata.sql>$HOME/tmp/InstallOlfix.log"
		echo $COMMAND
		echo $COMMAND>>$HOME/tmp/InstallOlfix.log

#		rm $OLFIX_DATA/LoadUSRdata.txt

 		echo -e  "\n** Installation klar!\n"
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
	 	--msgbox "** Uppgradering till version nr $VERSION           **\n** Du har valt att göra en UPPGRADERING av OLFIX.        **\n** Din OLFIXdatabas kommer att backas upp till           **\n** /root/tmp/OLFIXDATABASE.bak. En eventuell tidigare    **\n** bakupfil namnändras till /root/tmp/OLFIXDATABASE.old. ** " 10 65

#		++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#		Ange förnamn
#		++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

		exitcode=0
		dialog --backtitle "OLFIX uppgradering." \
		--title "OLFIX UPPGRADERING" \
		--inputbox "Ange ditt FÖRNAMN! " 10 60  2>$TEMP
		exitcode=$?

		if [ $exitcode -eq 0 ]
		then
			choice=`cat $TEMP`
			FNAMN=$choice
		else
			dialog --backtitle "OLFIX uppgradering." \
			--msgbox "** Uppgraderingen avbröts! **" 5 35
			clear
			exit
		fi
		rm -f $TEMP

#		++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#		Ska flera än en person använda OLFIX?
#		++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		exitcode=0
		dialog --backtitle "OLFIX uppgradering." \
		--title "OLFIX UPPGRADERING" \
		--menu "Ska OLFIX användas av en(1) eller flera användare? " 10 60 2 \
		E "Enanvändarsystem." \
		F "Fleranvändarsystem" 2>$TEMP
		exitcode=$?

  		if [ $exitcode -eq 0 ]
  		then
      			choice=`cat $TEMP`
 	     		BEHOR=$choice
		else
			dialog --backtitle "OLFIX uppgradering." \
			--msgbox "** Uppgraderingen avbröts! **" 5 35
			clear
			exit
 		fi
  		rm -f $TEMP

  		if test $BEHOR == "E";then
  			dialog --backtitle "OLFIX uppgradering." \
		 	--msgbox "** OLFIX uppgraderas för användning av EN användare! **" 5 60
			echo -e "** OLFIX används av EN användare">>$HOME/tmp/UpdateOlfix.log
		fi
		if test $BEHOR != "E";then
  			dialog --backtitle "OLFIX uppgradering." \
	 		--msgbox "** OLFIX uppgraderas för användning av FLERA användare! **" 5 60
			echo -e "** OLFIX används av FLERA användare">>$HOME/tmp/UpdateOlfix.log
  		fi

#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#		Om bara en användare så ska vederbörande ha behörighet
#		till alla program och funktioner som finns i
#		$OLFIX_SQL/RIGHTSdata.sql
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		uppername=`echo $USER | tr a-z A-Z`
		USER_ID=$uppername

		if test $BEHOR == "E";then
			exitcode=0
			dialog --backtitle "OLFIX uppgradering." \
			--title "OLFIX UPPGRADERING" \
			--inputbox "Vad är ditt USERID? " 10 60 $USER_ID 2>$TEMP
			exitcode=$?

  			if [ $exitcode -eq 0 ]
  			then
      				choice=`cat $TEMP`
      				USER_ID=$choice
			else
				dialog --backtitle "OLFIX uppgradering." \
				--msgbox "** Uppgraderingen avbröts! **" 5 35
				clear
				exit
  			fi
  			rm -f $TEMP
#			+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#			Sätt userid till versaler
#			+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			uppername=`echo $USER_ID | tr a-z A-Z`
			USER_ID=$uppername
			echo "** Userid=$USER_ID">>$HOME/tmp/UpdateOlfix.log

#			+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#			Skapa temporär datafil med alla behörigheter
#			+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			COMMAND="sed -e s/userid/$USER_ID/ $OLFIX_DATA/StandaloneRIGHTSdata.txt > $OLFIX_DATA/temprightdata.txt"
			echo "Create tempfil för rättigheter">>$HOME/tmp/UpdateOlfix.log
#			echo "COMMAND="$COMMAND
			eval $COMMAND
		fi
		dialog --backtitle "OLFIX uppgradering." \
		--msgbox "** Nu startar uppgradering **" \ 5 40

		echo "** Nu startar uppgradering">>$HOME/tmp/UpdateOlfix.log
		date >>$HOME/tmp/UpdateOlfix.log
		mkdir /usr/local/olfix/src/$VERSION
		COMMAND="chown $USER /usr/local/olfix/src/$VERSION"
		echo $COMMAND>>$HOME/tmp/UpdateOlfix.log
		eval $COMMAND
		COMMAND="chgrp $USER /usr/local/olfix/src/$VERSION"
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
			--msgbox "** Uppgraderingen avbröts! **" 5 35
			clear
			exit
		fi
		rm -f $TEMP

		COMMAND="/usr/bin/mysqldump -u$USER -p$DITTPW -q olfix > $HOME/tmp/OLFIXDATABASE.bak"
		eval $COMMAND
		COMMAND="/usr/bin/mysqldump -u$USER -p -q olfix > $HOME/tmp/OLFIXDATABASE.bak"
		echo $COMMAND>>$HOME/tmp/UpdateOlfix.log
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#		Uppdatera tabellen RIGHTS, rättigheter/behörigheter.
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
#		Plats för andra uppdateringar mm
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
