use olfix;
load data infile "/usr/local/olfix/data/FTGDATAdata.txt" replace into table FTGDATA Fields terminated by ',' enclosed by '"';
load data infile "/usr/local/olfix/data/KTOPLANdata.txt" replace into table KTOPLAN Fields terminated by ',' enclosed by '"';
load data infile "/usr/local/olfix/data/TRANSIDdata.txt" replace into table TRANSID Fields terminated by ',' enclosed by '"';
load data infile "/usr/local/olfix/data/VALUTAdata.txt" replace into table VALUTA Fields terminated by ',' enclosed by '"';
load data infile "/usr/local/olfix/data/PROGRAMdata.txt" replace into table PROGRAM Fields terminated by ',' enclosed by '"';

