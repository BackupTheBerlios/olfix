use olfix;
create table BETVILKOR(BETVILKOR VARCHAR(3) not null PRIMARY KEY,DAGAR VARCHAR(3),BESKRIVNING VARCHAR(40)not null );
load data infile "/usr/local/olfix/data/BETVILKORdata.txt" replace into table BETVILKOR Fields terminated by ',' enclosed by '"';
use olfixtst;
create table BETVILKOR(BETVILKOR VARCHAR(3) not null PRIMARY KEY,DAGAR VARCHAR(3),BESKRIVNING VARCHAR(40)not null );
load data infile "/usr/local/olfix/data/BETVILKORdata.txt" replace into table BETVILKOR Fields terminated by ',' enclosed by '"';



