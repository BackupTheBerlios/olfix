use olfix;
DROP TABLE IF EXISTS PASSW;
create table PASSW(
KUNDNR VARCHAR(10) not null,
PASSW VARCHAR(16) not null
);
alter table PASSW ADD PRIMARY KEY (KUNDNR);
use olfixtst;
DROP TABLE IF EXISTS PASSW;
create table PASSW(
KUNDNR VARCHAR(10) not null,
PASSW VARCHAR(16) not null
);
alter table PASSW ADD PRIMARY KEY (KUNDNR);
