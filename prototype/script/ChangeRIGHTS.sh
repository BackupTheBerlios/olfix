#!/bin/sh
#
# Namn: change_rights.sh
# Version: 0.1
# Beskrivning: Ge alla r�ttigheter f�r olfix till enanv�ndarsystem
OLFIX_BANNER="
 ------------------------------------------------------------------------------\n
-- OLFIX version X --\n\n
Det h�r scriptet hj�lper dig att f� r�ttighet att k�ra alla program i OLFIX,\n
efter ett antal fr�gor kommer r�ttigheterna att s�ttas. \n\n

\n Varje fr�ga har ett standandard svar,\n om du tycker att det �r ok s� tryck bara p� [Enter].\n
 ------------------------------------------------------------------------------\n"

# S�tt PATH
PATH=/bin:/sbin:/usr/bin:/usr/sbin
# S�tt OLFIX variabler
OLFIX_HOME=/usr/local/olfix
OLFIX_SQL=/usr/local/olfix/sql
OLFIX_USER=$USER

echo -e $OLFIX_BANNER
echo -e "�r .." $OLFIX_USER ".. ditt anv�ndarID?"

# sed -e 's/USERID/$userid/' RIGHTSdata.sql> RIGHTSdataChange.sql