use olfix;
create table FTGDATA(POSTTYP VARCHAR(5) not null ,POSTBESKR VARCHAR(60),FDATA TEXT);
alter table FTGDATA ADD PRIMARY KEY (POSTTYP);
load data infile "/usr/local/olfix/data/FTGDATAdata.txt" replace into table FTGDATA Fields terminated by ',' enclosed by '"';
use olfixtst;
create table FTGDATA(POSTTYP VARCHAR(5) not null ,POSTBESKR VARCHAR(60),FDATA TEXT);
alter table FTGDATA ADD PRIMARY KEY (POSTTYP);
load data infile "/usr/local/olfix/data/FTGDATAdata.txt" replace into table FTGDATA Fields terminated by ',' enclosed by '"';
