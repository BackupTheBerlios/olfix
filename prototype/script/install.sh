#!/bin/sh
#
#**********************************
#***  OBS! Skall köras som root ***
#**********************************

# Namn: install.sh
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

# Sätt PATH
PATH=/bin:/sbin:/usr/bin:/usr/sbin
# Sätt OLFIX variabler
OLFIX_HOME=/usr/local/olfix
OLFIX_SOURCE=/usr/local/olfix/src
OLFIX_SQL=/usr/local/olfix/sql
OLFIX_DATA=/usr/local/olfix/data

#QT variabler
QT=/usr/lib/qt3
QT_BIN=/usr/lib/qt3/bin
QT_INC=/usr/lib/qt3/include
QT_LIB=/usr/lib/qt3/lib
#MySQL variabler
MYSQLD=`whereis mysqld|awk '{print $2}'`

BEHOR=N
OLFIX_EXIST=N

echo -e $OLFIX_BANNER
read -e -r -p "Tryck [Enter]" SVAR
echo -e "\n"

#++++++++++++++++++++++++++++++++++++++++++++++++#
# -- Leta upp qt och dess mappar om dem finns -- #
#++++++++++++++++++++++++++++++++++++++++++++++++#

if [[ -d $QT && -d $QT_BIN && -d $QT_INC && -d $QT_LIB ]];then
	echo -e "** Hittade QT och dess undermappar på $QT"
else
	echo "** Kunde inte hitta QT, du måste ha QT installerat\n.** Avbryter installationen!\n"
	exit
fi

#++++++++++++++++++++++++++++++++++++++++++++++++#
# -- leta upp mysqld samt kolla om den svarar -- #
#++++++++++++++++++++++++++++++++++++++++++++++++#

if [[ -f $MYSQLD ]];then
	echo -e "** Hittade mysqld"
else
	echo -e "** Hittade inte mysqld\n"
	exit
fi

#är inte säker om den här testen är så optimal, inte klar!!!!
#MYSQL_EXEC=`mysql -u guest < quit``

#+++++++++++++++++++++++++++++++++++++++++++++++++++#
# -- Leta upp olfix och dess mappar om dem finns -- #
#+++++++++++++++++++++++++++++++++++++++++++++++++++#
if [[ -d $OLFIX_HOME ]];then
	OLFIX_EXIST=J
	echo -e "** Hittade OLFIX på $OLFIX_HOME, en installation finns redan.\n"
else
	OLFIX_EXIST=N
	echo "** Kunde inte hitta OLFIX\n"
fi

#++++++++++++++++++++++++++++++++++++++++++++++++?+++#
# -- Är det en installation eller en uppgradering -- #
#++++++++++++++++++++++++++++++++++++++++++++++++++++#
while (test -z $SVAR);do
	read -e -r -p "Är detta en [I]nstallation eller [U]ppgradering? " SVAR
done
uppersvar=`echo $SVAR | tr a-z A-Z`
UPGRADE=$uppersvar
if test $UPGRADE == "I" && test $OLFIX_EXIST == "J";then
	echo -e "** En redan befintlig installation skrivs över!"
fi
if test $UPGRADE == "I";then
	echo -e "** Du har valt att göra en INSTALLATION av OLFIX\n"
	echo "** Installation av OLFIX">>$HOME/tmp/InstallOlfix.log
	date >>$HOME/tmp/InstallOlfix.log

#	**********************************************************
#	**********************************************************
#	*************         INSTALLATION           *************
#	**********************************************************
#	**********************************************************

#	+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#	Ska flera än en person använda OLFIX?
#	+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	read -e -r -p "Används OLFIX av [E]n(1) eller [F]lera användare? [E]/F " SVAR
	if test -z $SVAR;then
		SVAR="E"
	fi
	if test $SVAR == "e";then
		SVAR=E
	fi
	if test $SVAR == "E";then
		echo -e "** OLFIX används av EN användare\n"
		echo "** OLFIX används av EN användare">>$HOME/tmp/InstallOlfix.log
	else
		if test $SVAR != "E";then
			SVAR=N
			echo -e "** OLFIX används av FLERA användare\n"
			echo "** OLFIX används av FLERA användare">>$HOME/tmp/InstallOlfix.log
		fi
	fi
	BEHOR=$SVAR
#       +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#	En användare
#	så ska vedrebörande ha behörighet
#	till alla program och funktioner som finns i
#	$OLFIX_SQL/RIGHTSdata.sql
#	+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if test $BEHOR == "E";then
		SVAR=""
		USER_ID=$USER
		while (test -z $SVAR);do
			read -e -r -p "Vad är ditt userid? [$USER_ID] " SVAR;
					if test -z $SVAR;then
						SVAR=$USER_ID
					fi
		done
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#		Sätt userid till versaler
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		uppername=`echo $SVAR | tr a-z A-Z`
		USER_ID=$uppername
		echo "** Userid=$USER_ID">>$HOME/tmp/InstallOlfix.log
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#		Skapa temporär datafil med alla behörigheter
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		COMMAND="sed -e s/userid/$USER_ID/ $OLFIX_DATA/StandaloneRIGHTSdata.txt > $OLFIX_DATA/temprightdata.txt"
		echo -e $COMMAND>>$HOME/tmp/InstallOlfix.log
		eval $COMMAND
	fi
#	+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#	Skapa temporär datafil med användardata för OLFIX (tabell USR)
#	+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	echo -e "\nDu ska nu ange förnamn, efternam, avd och sektion som behövs för OLFIX."
	SVAR=""
	while (test -z $SVAR);do
		read -e -r -p "Ange ditt förnamn! " SVAR;
	done
	FNAMN=$SVAR
	SVAR=""
	while (test -z $SVAR);do
		read -e -r -p "Ange ditt efternamn! " SVAR;
	done
	ENAMN=$SVAR
	AVD="Min_Avdelning"
	SEKT="Min_Sektion"
	echo -e "Med Avdelnig och Sektion menas din organisations benämningar på dessa\n"
	SVAR=""
	read -e -r -p "Ange din avdelng! [$AVD]" SVAR;
	if test -z $SVAR;then
		SVAR=$AVD
	fi
	AVD=$SVAR
	SVAR=""
	read -e -r -p "Ange din Sektion! [$SEKT] " SVAR;
	if test -z $SVAR;then
		SVAR=$SEKT
	fi
	SEKT=$SVAR
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

#	+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#	Skapa temporär datafil med användardata för mysql (tabell user)
#	Att använda för att administrera OLFIX
#	+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	COMMAND="sed -e s/DittNamn/$USER/ $OLFIX_SQL/mall_add_user_DittNamn.sql > $HOME/tmp/mysqldata.sql"
	eval $COMMAND
	cp $HOME/tmp/mysqldata.sql $HOME/tmp/mysqldata2.sql

	read -s -e -r -p "Ange password som user för MySQL! " SVAR;
	LOSENORD=$SVAR
	echo -e "\n"
	COMMAND="sed -e s/DittPassword/$LOSENORD/ $HOME/tmp/mysqldata2.sql > $HOME/tmp/mysqldata.sql"
	eval $COMMAND
	cp $HOME/tmp/mysqldata.sql $OLFIX_SQL/add_user_DittNamn.sql
	rm $HOME/tmp/mysqldata2.sql
	rm $HOME/tmp/mysqldata.sql

#	+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#	OK att starta installationen?
#	+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	SVAR=""
	read -e -r -p "OK att starta installationen? [J]/N " SVAR;
	if test -z $SVAR;then
		SVAR="J"
	fi
	if test $SVAR == "j";then
		SVAR=J
	fi
	if test $SVAR != "J";then
		echo -e "** Installationen avbryts!\n"
		echo -e "** Installationen avbryts!">>$HOME/tmp/InstallOlfix.log
		date>>$HOME/tmp/InstallOlfix.log
		exit
	fi
	echo "** Nu startar installationen"
	exit
#	+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#	Skapa databasen olfix.
#	+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	echo -e "** Skapar databasen olfix!"
	echo -e "** Skapar databasen olfix!">>$HOME/tmp/InstallOlfix.log
	COMMAND="mysql -h localhost -p <$OLFIX_SQL/CreateDatabaseOlfix.sql>$HOME/tmp/InstallOlfix.log"
	echo $COMMAND
	echo $COMMAND>>$HOME/tmp/InstallOlfix.log

#	+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#	Lägg till user olfix.
#	+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	echo -e "** Lägger till user olfix!"
	echo -e "** Lägger till user olfix!">>$HOME/tmp/InstallOlfix.log
	COMMAND="mysql -h localhost -p <$OLFIX_SQL/add_user_olfix.sql>$HOME/tmp/InstallOlfix.log"
	echo $COMMAND
	echo $COMMAND>>$HOME/tmp/InstallOlfix.log

#	+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#	Lägg till user admin, dig som user i mysql
#	+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#	echo -e "** Lägger upp dig som user i mysql!"
#	echo -e "** Lägger upp dig som user i mysql!">>$HOME/tmp/InstallOlfix.log
#	COMMAND="mysql -h localhost -p <$OLFIX_SQL/add_user_DittNamn.sql>$HOME/tmp/InstallOlfix.log"
#	echo $COMMAND
#	echo $COMMAND>>$HOME/tmp/InstallOlfix.log
#	rm $OLFIX_SQL/add_user_DittNamn.sql
#	cp mall_add_user_DittNamn.sql add_user_DittNamn.sql

#	+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#	Skapa tabller.
#	+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	echo -e "** Skapar tabeller till OLFIX!"
	echo -e "** Skapar tabeller till OLFIX!">>$HOME/tmp/InstallOlfix.log
	COMMAND="mysql -h localhost -p <$OLFIX_SQL/CreateAll.sql>$HOME/tmp/InstallOlfix.log"
	echo $COMMAND
	echo $COMMAND>>$HOME/tmp/InstallOlfix.log

#	+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#	Ladda tabeller (FTGDATA, KTOPLAN, TRANSID, VALUTA, PROGRAM)
#	+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	echo -e "** Laddar tabellerna i OLFIX!"
	echo -e "** Laddar tabellerna i OLFIX!">>$HOME/tmp/InstallOlfix.log
	COMMAND="mysql -h localhost -p <$OLFIX_SQL/LoadAll.sql>$HOME/tmp/InstallOlfix.log"
	echo $COMMAND
	echo $COMMAND>>$HOME/tmp/InstallOlfix.log

#	+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#	Uppdatera tabellen RIGHTS.
#	+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	echo -e "** Uppdaterar behörigheter till OLFIX!"
	echo -e "** Uppdaterar behörigheter till OLFIX!">>$HOME/tmp/InstallOlfix.log
	if test $BEHOR == "E";then
		COMMAND="mysql -h localhost -p <$OLFIX_SQL/LoadStandaloneRIGHTSdata.sql>$HOME/tmp/InstallOlfix.log"
#		rm $OLFIX_DATA/temprightdata.txt
	else
		COMMAND="mysql -h localhost -p <$OLFIX_SQL/LoadRIGHTSdata.sql>$HOME/tmp/InstallOlfix.log"
	fi
	echo $COMMAND
	echo $COMMAND>>$HOME/tmp/InstallOlfix.log

#	+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#	Uppdatera tabellen USR.
#	+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	echo -e "** Uppdaterar tabell USR till OLFIX!"
	echo -e "** Uppdaterar tabell USR till OLFIX!">>$HOME/tmp/InstallOlfix.log
	COMMAND="mysql -h localhost -p <$OLFIX_SQL/LoadRIGHTSdata.sql>$HOME/tmp/InstallOlfix.log"
	echo $COMMAND
	echo $COMMAND>>$HOME/tmp/InstallOlfix.log

#	rm $OLFIX_DATA/LoadUSRdata.txt




 echo -e  "\n** Installation klar!\n"

else

#	**********************************************************
#	**********************************************************
#	*************         UPPGRADERING           *************
#	**********************************************************
#	**********************************************************

	echo "** Uppgradering av OLFIX">>$HOME/tmp/UpdateOlfix.log
	date >>$HOME/tmp/UpdateOlfix.log

	echo -e "** Du har valt att göra en UPPGRADERING av OLFIX"
	echo -e "** Din OLFIXdatabas kommer att backas upp"
	echo -e "** till /root/tmp/OLFIXDATABASE.bak. En eventuell tidigare"
	echo -e "** bakupfil namnändras till /root/tmp/OLFIXDATABASE.old\n"
	SVAR=""
	read -e -r -p "Vill du fortsätta? [J]/N " SVAR
	if test -z $SVAR;then
		SVAR="J"
	fi
	if test $SVAR == "j";then
		SVAR="J"
	fi
	if test $SVAR != "J";then
		echo -e "** Slutar!\n"
		exit
	fi
#	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#	Ange versionsnummer
#	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	SVAR=""

	while (test -z $SVAR);do
		read -e -r -p "Ange versionsnummer! " SVAR
		VERNR=$SVAR
		if [[ -d $OLFIX_SOURCE/$VERNR ]];then
			echo "** Versionsnummer $VERNR finns redan!"
			SVAR=""
		fi
	done
	echo -e "** Uppgradering till version nr $VERNR\n"
	echo -e "** Uppgradering till version nr $VERNR">>$HOME/tmp/UpdateOlfix.log
#	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#	Ska flera än en person använda OLFIX?
#	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	SVAR=""
	read -e -r -p "Används OLFIX av [E]n eller [F]lera användare? [E]/F " SVAR
	if test -z $SVAR;then
		SVAR="E"
	fi
	if test $SVAR == "e";then
		SVAR=E
	fi
	if test $SVAR == "E";then
		echo -e "** OLFIX används av EN användare\n"
		echo -e "** OLFIX används av EN användare">>$HOME/tmp/UpdateOlfix.log
	else
		if test $SVAR != "E";then
			SVAR=N
			echo -e "** OLFIX används av FLERA användare\n"
			echo -e "** OLFIX används av FLERA användare">>$HOME/tmp/UpdateOlfix.log
		fi
	fi
	BEHOR=$SVAR
#       +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#	Om bara en användare så ska vedrebörande ha behörighet
#	till alla program och funktioner som finns i
#	$OLFIX_SQL/RIGHTSdata.sql
#	+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if test $BEHOR == "E";then
		SVAR=""
		USER_ID=$USER
		while (test -z $SVAR);do
			read -e -r -p "Vad är ditt userid? [$USER_ID] " SVAR;
					if test -z $SVAR;then
						SVAR=$USER_ID
					fi
		done
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#		Sätt userid till versaler
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		uppername=`echo $SVAR | tr a-z A-Z`
		USER_ID=$uppername
		echo -e "Userid=$USER_ID">>$HOME/tmp/UpdateOlfix.log
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#		Skapa temporär datafil med alla behörigheter
#		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		COMMAND="sed -e s/userid/$USER_ID/ $OLFIX_DATA/StandaloneRIGHTSdata.txt > $OLFIX_DATA/temprightdata.txt"
		echo "Create tempfil för rättigheter">>$HOME/tmp/UpdateOlfix.log
#		echo "COMMAND="$COMMAND
		eval $COMMAND
	fi
	echo "** Nu startar uppgradering"
	echo "** Nu startar uppgradering">>$HOME/tmp/UpdateOlfix.log
	date >>$HOME/tmp/UpdateOlfix.log
	mkdir /usr/local/olfix/src/$VERNR
	COMMAND="chown $USER /usr/local/olfix/src/$VERNR"
	echo $COMMAND>>$HOME/tmp/UpdateOlfix.log
	eval $COMMAND
	COMMAND="chgrp $USER /usr/local/olfix/src/$VERNR"
	echo $COMMAND>>$HOME/tmp/UpdateOlfix.log
	eval $COMMAND
#	+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#	Backa up OLFIXdatabasen.
#	+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if [[ -f $HOME/tmp/OLFIXDATABASE.bak ]];then
		COMMAND="mv $HOME/tmp/OLFIXDATABASE.bak $HOME/tmp/OLFIXDATABASE.old"
		echo $COMMAND>>$HOME/tmp/UpdateOlfix.log
		eval $COMMAND
	fi
	echo "** Ange roots password till OLFIXdatabasen!"
	COMMAND="/usr/bin/mysqldump -p -q olfix > $HOME/tmp/OLFIXDATABASE.bak"
	echo $COMMAND>>$HOME/tmp/UpdateOlfix.log
	eval $COMMAND
#	+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#	Uppdatera rättigheter/behörigheter.
#	+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if test $BEHOR == "E";then
		echo -e "** Uppdaterar behörigheter till OLFIX!"
		COMMAND="mysql -h localhost -p <$OLFIX_SQL/LoadStandaloneRIGHTSdata.sql>>$HOME/tmp/UpdateOlfix.log"
		echo $COMMAND>>$HOME/tmp/UpdateOlfix.log
#		rm $OLFIX_DATA/temprightdata.txt
	fi
	echo -e "\n** Uppgradering klar!\n"
	date>>$HOME/tmp/UpdateOlfix.log
	echo -e "\n** Uppgradering klar!\n">>$HOME/tmp/UpdateOlfix.log
fi

exit
