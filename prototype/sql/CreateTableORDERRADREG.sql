use olfix;
DROP TABLE IF EXISTS ORDERRADREG;
create table ORDERRADREG(
ORDERNR VARCHAR(10) not null,
ORDERRAD INT(4)not null,
KUNDNR VARCHAR(10) not null,
RADORDERTYP ENUM('N','D')DEFAULT 'N',
ARTIKELNR VARCHAR(30) not null,
BENEMNING VARCHAR(60),
LEVERANSVECKA VARCHAR(5),
BESTELLT DECIMAL(10,2) not null,
APRIS DECIMAL(10,2) not null,
SUMMA DECIMAL(10,2)not null,
MOMSKR DECIMAL(10,2) not null,
LEVERERAT DECIMAL(10,2),
RESTNOTERAT DECIMAL(10,2),
RADRABATT DECIMAL(2,1),
KALKYLPRIS DECIMAL(10,2),
LEVDATUM DATE,
ENHET VARCHAR(4)DEFAULT 'ST'
);
alter table ORDERRADREG ADD PRIMARY KEY (ORDERNR,ORDERRAD);

use olfixtst;
DROP TABLE IF EXISTS ORDERRADREG;
create table ORDERRADREG(
ORDERNR VARCHAR(10) not null,
ORDERRAD INT(4)not null,
KUNDNR VARCHAR(10) not null,
RADORDERTYP ENUM('N','D')DEFAULT 'N',
ARTIKELNR VARCHAR(30) not null,
BENEMNING VARCHAR(60),
LEVERANSVECKA VARCHAR(5),
BESTELLT DECIMAL(10,2) not null,
APRIS DECIMAL(10,2) not null,
SUMMA DECIMAL(10,2)not null,
MOMSKR DECIMAL(10,2) not null,
LEVERERAT DECIMAL(10,2),
RESTNOTERAT DECIMAL(10,2),
RADRABATT DECIMAL(2,1),
KALKYLPRIS DECIMAL(10,2),
LEVDATUM DATE,
ENHET VARCHAR(4)DEFAULT 'ST'
);
alter table ORDERRADREG ADD PRIMARY KEY (ORDERNR,ORDERRAD);
