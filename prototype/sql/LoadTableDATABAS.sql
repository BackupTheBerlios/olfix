# Connection: olfix
# Host: localhost
# Saved: 2003-12-18 06:43:41
# 
use olfix;
load data infile "/usr/local/olfix/data/TableDATABASdata.txt" replace into table DATABAS Fields terminated by ',' enclosed by '"';
use olfixtst;
load data infile "/usr/local/olfix/data/TableDATABASdata.txt" replace into table DATABAS Fields terminated by ',' enclosed by '"';



