#!/bin/sh
# Version 0.2	2004-01-18	Jan Pihlgren
INSTALLPATH=/usr/local/olfix

INSTALLPATH=`dialog --backtitle "OLFIX installation." \
--title "OLFIX INSTALLATION" \
--inputbox "Var vill du installera filerna? " 10 60  $INSTALLPATH 2>&1`

if [ "$?" != "0" ]
then
	dialog --backtitle "OLFIX installation." \
	--msgbox "** Installationen avbröts! **" 5 35
	clear
	exit
fi

if [ -d $INSTALLPATH ]; then
	OLDPATH=$INSTALLPATH"_old"
	dialog --backtitle "OLFIX installation." \
	--msgbox "** Katalogen "$INSTALLPATH" finns redan! **\n** Flyttar till katalog "$OLDPATH" **" 10 80
	mv $INSTALLPATH $OLDPATH
fi

mkdir $INSTALLPATH
cp -R * $INSTALLPATH
cd $INSTALLPATH/script
$INSTALLPATH/script/setup2.sh

dialog --backtitle "OLFIX installation." \
--msgbox "** Installationen klar! **" 5 35
clear
