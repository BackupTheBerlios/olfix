#!/bin/sh
INSTALLPATH=/usr/local/olfix
OLFIX_PATH=$HOME/tmp/olfix_path.txt

exitcode=0
dialog --backtitle "OLFIX installation." \
--title "OLFIX INSTALLATION" \
--inputbox "Var vill du installera filerna? " 10 60  $INSTALLPATH 2>$OLFIX_PATH
exitcode=$?

if [ $exitcode -eq 0 ]
then
	choice=`cat $OLFIX_PATH`
	INSTALLPATH=$choice
else
	dialog --backtitle "OLFIX installation." \
	--msgbox "** Installationen avbröts! **" 5 35
	clear
	rm -f $OLFIX_PATH
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
$INSTALLPATH/script/install.sh

dialog --backtitle "OLFIX installation." \
--msgbox "** Installationen klar! **" 5 35
clear
