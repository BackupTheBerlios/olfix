use mysql;
CREATE DATABASE olfixtst;
use olfixtst;
create table ARTIKELREG(
ARTIKELNR	VARCHAR(30) not null,
ARBENEMNING1	VARCHAR(30) not null,
ARBENEMNING2	VARCHAR(30),
ARENHET		VARCHAR(5),
AROMRFAKTOR	INT not null DEFAULT '1',
ARFPRIS		DECIMAL(10,2),
ARLEDTID	VARCHAR(3),
ARPRODKLASS	VARCHAR(5),
ARPRODKTO	VARCHAR(5),
ARLEVNR1	VARCHAR(10),
ARLEVNR2	VARCHAR(10),
ARLEVNR3	VARCHAR(10),
ARNETTOVIKT	DECIMAL(10,2),
ARARTTYP	ENUM ('0','1','2','3')DEFAULT '0',
ARSTRUKT	ENUM (' ','B','I','T','F')DEFAULT ' ',
ARURBENEMNING	VARCHAR(30),
ARURLAND	VARCHAR(30),
ARURARTNR	VARCHAR(30),
ARTULLTAX	VARCHAR(7),
ARVOLYM		DECIMAL(2,3)
);
use olfixtst;
alter table ARTIKELREG ADD PRIMARY KEY (ARTIKELNR);
use olfixtst;
create table BETVILKOR(BETVILKOR VARCHAR(3) not null PRIMARY KEY,DAGAR VARCHAR(3),BESKRIVNING VARCHAR(40)not null );
use olfixtst;
create table BOKFAR(ARID VARCHAR(2) not null primary key,BENAMNING VARCHAR(25),ARSTART DATE ,ARSLUT DATE,ARLAST ENUM('J','N')DEFAULT 'N',SENVERDAT DATE,VERNR INT(11),KONTOPLAN VARCHAR(15),BESKATTNINGSAR VARCHAR(4));
use olfixtst;
create table FTGDATA(POSTTYP VARCHAR(5) not null PRIMARY KEY,POSTBESKR VARCHAR(60),FDATA TEXT);
use olfixtst;
create table INKREG(
INKORDNR VARCHAR(10) not null,
BESTTYP ENUM('N','D','I','L','A'),
ORDERDATUM DATE,
LEVNR VARCHAR(10),
LEVNAMN VARCHAR (30),
LEVADRESS VARCHAR(30),
LEVPOSTNR VARCHAR(6),
LEVPOSTADR VARCHAR(30),
LEVLAND VARCHAR(30),
LEVVALUTA VARCHAR(3),
LEVBETVILLKOR VARCHAR(3),
GODSMERKE VARCHAR(30),
BESTTEXT VARCHAR(3),
VARREF VARCHAR (30),
LEVDATUM DATE,
KUNDNR VARCHAR(30),
FTGNAMN VARCHAR(30),
FTGADR VARCHAR(30),
FTGPOSTNR VARCHAR(6),
FTGPOSTADR VARCHAR(30),
SPRAKKOD VARCHAR(3) DEFAULT 'sv',
BEKREFTKOD ENUM('H','D','E')DEFAULT 'E',
ORDERSTATUS ENUM('N','F','B','M')DEFAULT 'N',
UTSKRIFTSKOD ENUM('J','N')DEFAULT 'J',
ORDERSUMMA DECIMAL(10,2)
);
alter table INKREG ADD PRIMARY KEY (INKORDNR);
use olfixtst;
create table INKRADREG(
INKORDNR VARCHAR(10) not null,
INKORDRADNR INT(4)not null,
ARTIKELNR VARCHAR(30),
ENHET VARCHAR(5),
BESTANTAL DECIMAL(10,2),
LEVERERAT DECIMAL(10,2),
RESTNOTERAT DECIMAL(10,2),
INKPRIS DECIMAL(10,2),
LEVVECKA VARCHAR(5),
TORDNR INT(6),
OPNR INT(6)
);
alter table INKRADREG ADD PRIMARY KEY (INKORDNR,INKORDRADNR);
use olfixtst;
create table KTOPLAN(ARID VARCHAR(2) not null,KTONR VARCHAR(4) not null,BENAMNING VARCHAR(100),MANUELL ENUM('J','N')DEFAULT 'J',MOMSKOD VARCHAR(4),SRUNR INT(3),KSTALLE VARCHAR(4),PROJEKT VARCHAR(4),SUBKTO VARCHAR(4),KTOPLAN VARCHAR(15),IB DECIMAL(10,2),UB DECIMAL(10,2));
alter table KTOPLAN ADD PRIMARY KEY (KTONR,ARID);
use olfixtst;
create table KSTALLE(ARID VARCHAR(2) not null,KSTALLE VARCHAR(4)not null ,BENAMNING VARCHAR(100));
alter table KSTALLE ADD PRIMARY KEY (ARID,KSTALLE);
use olfixtst;
create table KUNDREG(
KUNDNR VARCHAR(10) not null,
KUNDORGNR VARCHAR(12),
NAMN VARCHAR(60) not null,
ADRESS VARCHAR(30),
POSTNR VARCHAR(6),
POSTADR VARCHAR(30),
LAND VARCHAR(30),
TFNNR VARCHAR(15),
EMAILADR VARCHAR(30),
FAXNR VARCHAR(15),
ERREFERENT VARCHAR(30),
ERREFTFNNR VARCHAR(15),
ERREFEMAIL VARCHAR(60),
SELJARE VARCHAR(20),
FRITEXT VARCHAR(100),
VALUTA VARCHAR(3),
BETALVILLKOR VARCHAR(3),
LEVVILLKOR VARCHAR(3),
LEVSETT VARCHAR(3),
DISTRIKT VARCHAR(3),
KUNDKATEGORI VARCHAR(3),
STDLEVPLATS VARCHAR(3) DEFAULT '001',
ORDERERKENNANDE ENUM('J','N')DEFAULT 'J',
PLOCKLISTA ENUM('J','N')DEFAULT 'J',
FOLJESEDEL ENUM('J','N')DEFAULT 'J',
KRAVBREV ENUM('J','N')DEFAULT 'J',
SPRAKKOD VARCHAR(3),
EXPAVGIFT ENUM('J','N')DEFAULT 'J',
FRAKTAVG ENUM('J','N')DEFAULT 'J',
KREDITLIMIT DECIMAL(10,2),
KREDITDAGAR INT,
KREDITKOD VARCHAR(3),
EXPORTKOD VARCHAR(3),
SKATTEKOD VARCHAR(3),
RABATTKOD VARCHAR(3),
DROJMALSRTA ENUM('J','N')DEFAULT 'J',
DROJMALSFAKTURA ENUM('J','N')DEFAULT 'J',
SAMLINGSFAKT ENUM('J','N')DEFAULT 'J',
SENASTEKRAVDATUM DATE,
SKULD DECIMAL(10,2),
ORDERSTOCK DECIMAL(10,2)
);
alter table KUNDREG ADD PRIMARY KEY (KUNDNR);
use olfixtst;
create table LAGERSTELLEREG(
ARLAGST		VARCHAR(1)  not null,
ARTIKELNR	VARCHAR(30) not null,
ARLAGHYLLA	VARCHAR(10),
ARLAGSALDO	DECIMAL(10,2),
ARINVGRP	VARCHAR(3),
ARABC		VARCHAR(2),
ARVALUTA	VARCHAR(3),
ARIPRIS		DECIMAL(10,2) DEFAULT "0.00",
ARIKVANT0	DECIMAL(10,2) DEFAULT "0.00",
ARIKVANT1	DECIMAL(10,2) DEFAULT "0.00",
ARIKVANT2	DECIMAL(10,2) DEFAULT "0.00",
ARKALKPRIS	DECIMAL(10,2) DEFAULT "0.00",
ARPLANKPRIS	DECIMAL(10,2) DEFAULT "0.00",
ARFRYSTKPRIS	DECIMAL(10,2) DEFAULT "0.00",
ARBESTKVANT	DECIMAL(10,2) DEFAULT "0.00",
ARBESTPUNKT	DECIMAL(10,2) DEFAULT "0.00",
AROMKOST	DECIMAL(10,2) DEFAULT "0.00"
);
use olfixtst;
alter table LAGERSTELLEREG ADD PRIMARY KEY (ARTIKELNR,ARLAGST);
use olfixtst;
create table LEVREG (
LEVNR VARCHAR(10) not null,
LEVORGNR VARCHAR(12),
LEVNAMN VARCHAR(30) not null,
LEVADRESS VARCHAR(30),
LEVPOSTNR VARCHAR(6),
LEVPOSTADR VARCHAR(30),
LEVLAND VARCHAR(30),
LEVTFNNR VARCHAR(15),
LEVFAXNR VARCHAR(15),
LEVTELEX VARCHAR(10),
LEVEMAIL VARCHAR(30),
LEVPOSTGIRONR VARCHAR(10),
LEVBANKGIRONR VARCHAR(10),
LEVREFERENT VARCHAR(20),
LEVREFTFN VARCHAR(15),
LEVMOMSKOD VARCHAR(1) DEFAULT '1',
LEVSKULD DECIMAL(10,2),
LEVKONTO VARCHAR(4),
LEVKUNDNR VARCHAR(30),
LEVVALUTA CHAR(3),
BETALVILKOR VARCHAR(3)
);
alter table LEVREG ADD PRIMARY KEY (LEVNR);
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
USERID VARCHAR(8),
VERNR INT,
BETALD ENUM('J','N')DEFAULT 'N',
BETALDDATUM DATE,
OCRNR VARCHAR(20)
);
alter table LEVRESK ADD PRIMARY KEY (LEVNR,FAKTURANR);
use olfixtst;
create table ORDERRADREG(
ORDERNR VARCHAR(10) not null,
ORDERRAD INT(4)not null,
KUNDNR VARCHAR(10) not null,
RADORDERTYP ENUM('N','D')DEFAULT 'N',
ARTIKELNR VARCHAR(30) not null,
BESTELLT DECIMAL(10,2) not null,
LEVERERAT DECIMAL(10,2),
RESTNOTERAT DECIMAL(10,2),
APRIS DECIMAL(10,2),
RADRABATT DECIMAL(2,1),
KALKYLPRIS DECIMAL(10,2),
SKATTEKOD VARCHAR(5) not null,
LEVDATUM DATE,
ENHET VARCHAR(4)DEFAULT 'ST'
);
alter table ORDERRADREG ADD PRIMARY KEY (ORDERNR,ORDERRAD);
use olfixtst;
create table ORDERREG(
ORDERNR VARCHAR(10) not null,
KUNDNR VARCHAR(10) not null,
ORDERTYP ENUM('N','D','E','F')DEFAULT 'N',
ORDERSTATUS ENUM('A','N','F','B')DEFAULT 'A',
ORDERDATUM DATE,
LEVDATUM DATE,
LEVADRESS VARCHAR(3)DEFAULT '001',
VARREF VARCHAR(20),
ERREF VARCHAR(20),
SELJARE VARCHAR(20),
GODSMERKE VARCHAR(100),
BETVILLKTYP ENUM('F','P','K') not null,
BETVILLKOR VARCHAR(3) DEFAULT '001',
LEVVILLKOR VARCHAR(3) DEFAULT '001',
LEVSETT VARCHAR(3) DEFAULT '001',
PLOCKLISTA ENUM('J','N') DEFAULT 'J',
FOLJESEDEL ENUM('J','N') DEFAULT 'J',
FRAKTAVG ENUM('J','N') DEFAULT 'J',
SKATTEKOD VARCHAR(3) DEFAULT '001' not null,
VALUTA VARCHAR(3) DEFAULT 'SEK',
EXPORTKOD VARCHAR(3) DEFAULT '001',
SPRAKKOD VARCHAR(3)DEFAULT 'sv'
);
alter table ORDERREG ADD PRIMARY KEY (ORDERNR);
use olfixtst;
create table PROGRAM(PRGNR VARCHAR(3) not null primary key,MENYAVD VARCHAR(20),MENYGRP VARCHAR(30), MENYTXT VARCHAR(30),PROGRAM VARCHAR(8));
create table RIGHTS(USERID VARCHAR(8) not null ,TRNSID VARCHAR(8)not null );
alter table RIGHTS ADD PRIMARY KEY(USERID,TRNSID);
use olfixtst;
create table STDLEVPLATS(
STDLEVPLATS VARCHAR(3) not null,
KUNDNR VARCHAR(10) not null,
ADRESS VARCHAR(30) not null,
POSTNR VARCHAR(6) not null,
POSTADR VARCHAR(30) not null,
LAND VARCHAR(30)
);
alter table STDLEVPLATS ADD PRIMARY KEY (STDLEVPLATS,KUNDNR);
use olfixtst;
use olfixtst;
create table TEXTREG(TEXTNR VARCHAR(3) not null primary key,TXT TEXT);
create table TRANSID(TRNSID VARCHAR(8) not null primary key,TRNSTXT VARCHAR(60));
use olfixtst;
create table TRHD(TRNSNR INT not null auto_increment PRIMARY KEY,TRNSID VARCHAR(8) not null ,TID VARCHAR(20) not null ,USERID VARCHAR(8) not null,TRNSDATA VARCHAR(255));
use olfixtst;
create table USR(USERID VARCHAR(8) not null primary key,NAMN VARCHAR(30),AVD VARCHAR(10),GRUPP VARCHAR(10));
use olfixtst;
create table VALUTA(VALUTAID VARCHAR(3) not null primary key,LAND VARCHAR(15),SALJ DECIMAL(3,2),KOP DECIMAL(3,2),BETECKNING VARCHAR(15));
use olfixtst;
create table VERHUVUD(VERNR INT not null ,ARID VARCHAR(2) not null ,VERDATUM DATE,REGDAT DATE, DEBET DECIMAL(10,2),KREDIT DECIMAL(10,2),VERTEXT VARCHAR(60),KORRIGERAR INT,KORRIGERAD INT,USERID VARCHAR(8));
alter table VERHUVUD ADD PRIMARY KEY (VERNR,ARID);
use olfixtst;
create table VERRAD(VERNR INT not null ,RADNR SMALLINT not null,ARID VARCHAR(2) not null ,KTONR VARCHAR(4),BELOPP DECIMAL(10,2),DK ENUM('D','K'),KSTALLE VARCHAR(4),PROJEKT VARCHAR(4),SUBKTO VARCHAR(4),DEFINITIV ENUM('J','N')DEFAULT 'N',STRUKEN ENUM('J','N')DEFAULT 'N');
alter table VERRAD ADD PRIMARY KEY (VERNR,RADNR,ARID);
