# Connection: olfix
# Host: localhost
# Saved: 2003-06-24 16:50:08
# 
use olfix;
create table LEVRESK (
LEVNR VARCHAR(10) not null,
FAKTURANR VARCHAR(20) not null,
REGDATUM DATE,
FAKTDATUM DATE,
EXPIREDATUM DATE,
FAKTTEXT VARCHAR(100),
BAR VARCHAR(2),
MOMSPROCENT DECIMAL(2,2),
VALUTA CHAR(3),
VALUTAKURS DECIMAL(5,2),
VALUTABELOPP DECIMAL(10,2),
LEVKTONR VARCHAR(4),
FAKTBELOPP DECIMAL(10,2),
MOMSKTONR VARCHAR(4),
MOMSBELOPP DECIMAL(10,2),
DEBETKONTONR VARCHAR(4),
DEBETBELOPP DECIMAL(10,2),
USERID VARCHAR(20),
VERNR INT,
BETALD ENUM('J','N')DEFAULT 'N',
BETALDDATUM DATE,
OCRNR VARCHAR(20)
);
alter table LEVRESK ADD PRIMARY KEY (LEVNR,FAKTURANR);
use olfixtst;
create table LEVRESK (
LEVNR VARCHAR(10) not null,
FAKTURANR VARCHAR(20) not null,
REGDATUM DATE,
FAKTDATUM DATE,
EXPIREDATUM DATE,
FAKTTEXT VARCHAR(100),
BAR VARCHAR(2),
MOMSPROCENT DECIMAL(2,2),
VALUTA CHAR(3),
VALUTAKURS DECIMAL(3,2),
VALUTABELOPP DECIMAL(10,2),
LEVKTONR VARCHAR(4),
FAKTBELOPP DECIMAL(10,2),
MOMSKTONR VARCHAR(4),
MOMSBELOPP DECIMAL(10,2),
DEBETKONTONR VARCHAR(4),
DEBETBELOPP DECIMAL(10,2),
USERID VARCHAR(20),
VERNR INT,
BETALD ENUM('J','N')DEFAULT 'N',
BETALDDATUM DATE,
OCRNR VARCHAR(20)
);
alter table LEVRESK ADD PRIMARY KEY (LEVNR,FAKTURANR);

