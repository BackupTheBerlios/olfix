use olfix;
create table TRANSID(TRNSID VARCHAR(8) not null primary key,TRNSTXT VARCHAR(60));
load data infile "/usr/local/olfix/data/TRANSIDdata.txt" replace into table TRANSID Fields terminated by ',' enclosed by '"';




