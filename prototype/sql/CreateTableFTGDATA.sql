use olfix;
create table FTGDATA(POSTTYP VARCHAR(5) not null PRIMARY KEY,POSTBESKR VARCHAR(60),FDATA TEXT);
load data infile "/usr/local/olfix/data/FTGDATAdata.txt" replace into table FTGDATA Fields terminated by ',' enclosed by '"';
