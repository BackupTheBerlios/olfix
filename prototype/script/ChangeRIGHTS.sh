#!/bin/sh
#
# Namn: change_rights.sh
# Version: 0.1
# Beskrivning: Ge alla rättigheter för olfix till enanvändarsystem
OLFIX_BANNER="
 ------------------------------------------------------------------------------\n
-- OLFIX version X --\n\n
Det här scriptet hjälper dig att få rättighet att köra alla program i OLFIX,\n
efter ett antal frågor kommer rättigheterna att sättas. \n\n

\n Varje fråga har ett standandard svar,\n om du tycker att det är ok så tryck bara på [Enter].\n
 ------------------------------------------------------------------------------\n"

# Sätt PATH
PATH=/bin:/sbin:/usr/bin:/usr/sbin
# Sätt OLFIX variabler
OLFIX_HOME=/usr/local/olfix
OLFIX_SQL=/usr/local/olfix/sql
OLFIX_USER=$USER

echo -e $OLFIX_BANNER
echo -e "Är .." $OLFIX_USER ".. ditt användarID?"

# sed -e 's/USERID/$userid/' RIGHTSdata.sql> RIGHTSdataChange.sql