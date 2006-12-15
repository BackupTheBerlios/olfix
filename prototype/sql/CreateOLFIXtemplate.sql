use mysql;
-- MySQL dump 9.07 2005-04-24
--
-- Host: localhost    Database: olfixtemplate
---------------------------------------------------------
-- Server version	4.0.11a-gamma

--
-- Current Database: olfixtemplate
--


CREATE DATABASE  IF NOT EXISTS olfixtemplate;

USE olfixtemplate;

--
-- Table structure for table 'ARTIKELREG'
--

DROP TABLE IF EXISTS ARTIKELREG;
CREATE TABLE ARTIKELREG (
  ARTIKELNR varchar(30) NOT NULL default '',
  ARBENEMNING1 varchar(30) NOT NULL default '',
  ARBENEMNING2 varchar(30) default NULL,
  ARENHET varchar(5) default NULL,
  ARFPRIS decimal(10,2) default NULL,
  ARLEDTID char(3) default NULL,
  ARPRODKLASS varchar(5) default NULL,
  ARPRODKTO varchar(5) default NULL,
  ARLEVNR1 varchar(10) default NULL,
  ARLEVNR2 varchar(10) default NULL,
  ARLEVNR3 varchar(10) default NULL,
  ARNETTOVIKT decimal(10,2) default NULL,
  ARARTTYP enum('0','1','2','3','4') default '0',
  ARSTRUKT enum('','B','I','T','F') default '',
  ARURBENEMNING varchar(30) default NULL,
  ARURLAND varchar(30) default NULL,
  ARURARTNR varchar(30) default NULL,
  ARTULLTAX varchar(10) default NULL,
  ARVOLYM decimal(4,3) default NULL,
  AROMRFAKTOR int(11) NOT NULL default '1',
  PRIMARY KEY  (ARTIKELNR)
) TYPE=MyISAM;

--
-- Dumping data for table 'ARTIKELREG'
--


--
-- Table structure for table 'BETVILKOR'
--

DROP TABLE IF EXISTS BETVILKOR;
CREATE TABLE BETVILKOR (
  BETVILKOR char(3) NOT NULL default '',
  DAGAR char(3) default NULL,
  BESKRIVNING varchar(40) NOT NULL default '',
  PRIMARY KEY  (BETVILKOR)
) TYPE=MyISAM;

--
-- Dumping data for table 'BETVILKOR'
--

INSERT INTO BETVILKOR (BETVILKOR, DAGAR, BESKRIVNING) VALUES ('1','30','30 dagar netto');
INSERT INTO BETVILKOR (BETVILKOR, DAGAR, BESKRIVNING) VALUES ('2','20','20 dagar netto');
INSERT INTO BETVILKOR (BETVILKOR, DAGAR, BESKRIVNING) VALUES ('3','10','10 dagar netto');
INSERT INTO BETVILKOR (BETVILKOR, DAGAR, BESKRIVNING) VALUES ('4','0','Kontantk�p');
INSERT INTO BETVILKOR (BETVILKOR, DAGAR, BESKRIVNING) VALUES ('5','15','Postf�rskott');

--
-- Table structure for table 'BOKFAR'
--

DROP TABLE IF EXISTS BOKFAR;
CREATE TABLE BOKFAR (
  ARID char(2) NOT NULL default '',
  BENAMNING varchar(25) default NULL,
  ARSTART date default NULL,
  ARSLUT date default NULL,
  ARLAST enum('J','N') default 'N',
  SENVERDAT date default NULL,
  VERNR int(11) default NULL,
  KONTOPLAN varchar(15) default NULL,
  BESKATTNINGSAR varchar(4) default NULL,
  PRIMARY KEY  (ARID)
) TYPE=MyISAM;

--
-- Dumping data for table 'BOKFAR'
--

INSERT INTO BOKFAR (ARID, BENAMNING, ARSTART, ARSLUT, ARLAST, SENVERDAT, VERNR, KONTOPLAN, BESKATTNINGSAR) VALUES ('XX','2003-01-01--2003-12-31','2003-01-01','2003-12-31','N','2003-09-11',26,'EUBAS97','2003');

--
-- Table structure for table 'DATABAS'
--

DROP TABLE IF EXISTS DATABAS;
CREATE TABLE DATABAS (
  DATABASNR char(3) NOT NULL default '',
  DATABASTEXT varchar(15) NOT NULL default '',
  PRIMARY KEY  (DATABASNR)
) TYPE=MyISAM;

--
-- Dumping data for table 'DATABAS'
--

INSERT INTO DATABAS (DATABASNR, DATABASTEXT) VALUES ('01','olfix');
INSERT INTO DATABAS (DATABASNR, DATABASTEXT) VALUES ('99','olfixtst');
INSERT INTO DATABAS (DATABASNR, DATABASTEXT) VALUES ('00','newdatabase');

--
-- Table structure for table 'FTGDATA'
--

DROP TABLE IF EXISTS FTGDATA;
CREATE TABLE FTGDATA (
  POSTTYP varchar(5) NOT NULL default '',
  POSTBESKR varchar(60) default NULL,
  FDATA text,
  PRIMARY KEY  (POSTTYP)
) TYPE=MyISAM;

--
-- Dumping data for table 'FTGDATA'
--

INSERT INTO FTGDATA (POSTTYP, POSTBESKR, FDATA) VALUES ('FNAMN','F�retagsnamn','PROGRAM AB');
INSERT INTO FTGDATA (POSTTYP, POSTBESKR, FDATA) VALUES ('FTGNR','F�retagsnummer','991199-1991');
INSERT INTO FTGDATA (POSTTYP, POSTBESKR, FDATA) VALUES ('ADR1','Postadress','Box 70');
INSERT INTO FTGDATA (POSTTYP, POSTBESKR, FDATA) VALUES ('ADR2','Postnummer till Postadress','199 98');
INSERT INTO FTGDATA (POSTTYP, POSTBESKR, FDATA) VALUES ('ADR3','Ort till Postadress','PROGSTAD');
INSERT INTO FTGDATA (POSTTYP, POSTBESKR, FDATA) VALUES ('ADR4','Bes�ksadress','Syntaxv�gen 99');
INSERT INTO FTGDATA (POSTTYP, POSTBESKR, FDATA) VALUES ('ADR5','Postnr till Bes�ksadress','199 98');
INSERT INTO FTGDATA (POSTTYP, POSTBESKR, FDATA) VALUES ('ADR6','Ort till Bes�ksadress','PROGSTAD');
INSERT INTO FTGDATA (POSTTYP, POSTBESKR, FDATA) VALUES ('ADR7','Godsadress','Verktygsgatan 11');
INSERT INTO FTGDATA (POSTTYP, POSTBESKR, FDATA) VALUES ('ADR8','Postnr till Godsadress','199 97');
INSERT INTO FTGDATA (POSTTYP, POSTBESKR, FDATA) VALUES ('ADR9','Ort till Godsadress','PROGSTAD');
INSERT INTO FTGDATA (POSTTYP, POSTBESKR, FDATA) VALUES ('TFNVX','Telefonnummer till vx','09-199300');
INSERT INTO FTGDATA (POSTTYP, POSTBESKR, FDATA) VALUES ('TFN1','Telefonnummer','09-199300');
INSERT INTO FTGDATA (POSTTYP, POSTBESKR, FDATA) VALUES ('TFN2','Mobiltelefonnummer','070-98765411');
INSERT INTO FTGDATA (POSTTYP, POSTBESKR, FDATA) VALUES ('TFNMB','Mobiltelefonnummer','070-98765411');
INSERT INTO FTGDATA (POSTTYP, POSTBESKR, FDATA) VALUES ('TFAX','Telefaxnummer','09-199397');
INSERT INTO FTGDATA (POSTTYP, POSTBESKR, FDATA) VALUES ('TELEX','Telexnummer','12345');
INSERT INTO FTGDATA (POSTTYP, POSTBESKR, FDATA) VALUES ('EML1','E-mailadress','info@program.com');
INSERT INTO FTGDATA (POSTTYP, POSTBESKR, FDATA) VALUES ('MOMSI','Momskonto, ing�ende moms','2641');
INSERT INTO FTGDATA (POSTTYP, POSTBESKR, FDATA) VALUES ('MOMSU','Momskonto, utg�ende moms','2611');
INSERT INTO FTGDATA (POSTTYP, POSTBESKR, FDATA) VALUES ('MOMS1','Momssats 1','25');
INSERT INTO FTGDATA (POSTTYP, POSTBESKR, FDATA) VALUES ('MOMS2','Momssats 2','12');
INSERT INTO FTGDATA (POSTTYP, POSTBESKR, FDATA) VALUES ('MOMS3','Momssats 3','6');
INSERT INTO FTGDATA (POSTTYP, POSTBESKR, FDATA) VALUES ('MOMS4','Momssats 4',' ');
INSERT INTO FTGDATA (POSTTYP, POSTBESKR, FDATA) VALUES ('MOMS5','Momssats 5',' ');
INSERT INTO FTGDATA (POSTTYP, POSTBESKR, FDATA) VALUES ('MNR','Momsregistreringsnr',' ');
INSERT INTO FTGDATA (POSTTYP, POSTBESKR, FDATA) VALUES ('AUTOK','Automatkontering J/N','N');
INSERT INTO FTGDATA (POSTTYP, POSTBESKR, FDATA) VALUES ('KORNR','Senast anv�nda kundordernr','0');
INSERT INTO FTGDATA (POSTTYP, POSTBESKR, FDATA) VALUES ('BF1','Bokf�ringsperiod 1',NULL);
INSERT INTO FTGDATA (POSTTYP, POSTBESKR, FDATA) VALUES ('BF2','Bokf�ringsperiod 2',NULL);
INSERT INTO FTGDATA (POSTTYP, POSTBESKR, FDATA) VALUES ('BF3','Bokf�ringsperiod 3',NULL);
INSERT INTO FTGDATA (POSTTYP, POSTBESKR, FDATA) VALUES ('BF4','Bokf�ringsperiod 4',NULL);
INSERT INTO FTGDATA (POSTTYP, POSTBESKR, FDATA) VALUES ('BF5','Bokf�ringsperiod 5',NULL);
INSERT INTO FTGDATA (POSTTYP, POSTBESKR, FDATA) VALUES ('BF6','Bokf�ringsperiod 6',NULL);
INSERT INTO FTGDATA (POSTTYP, POSTBESKR, FDATA) VALUES ('BF7','Bokf�ringsperiod 7',NULL);
INSERT INTO FTGDATA (POSTTYP, POSTBESKR, FDATA) VALUES ('BF8','Bokf�ringsperiod 8',NULL);
INSERT INTO FTGDATA (POSTTYP, POSTBESKR, FDATA) VALUES ('BF9','Bokf�ringsperiod 9',NULL);
INSERT INTO FTGDATA (POSTTYP, POSTBESKR, FDATA) VALUES ('BF10','Bokf�ringsperiod 10',NULL);
INSERT INTO FTGDATA (POSTTYP, POSTBESKR, FDATA) VALUES ('BF11','Bokf�ringsperiod 11',NULL);
INSERT INTO FTGDATA (POSTTYP, POSTBESKR, FDATA) VALUES ('BF12','Bokf�ringsperiod 12',NULL);
INSERT INTO FTGDATA (POSTTYP, POSTBESKR, FDATA) VALUES ('BF13','Bokf�ringsperiod 13',NULL);
INSERT INTO FTGDATA (POSTTYP, POSTBESKR, FDATA) VALUES ('FAKNR','Senaste fakturanr p� kundorder','0');
INSERT INTO FTGDATA (POSTTYP, POSTBESKR, FDATA) VALUES ('FKNR2','Senaste fakturanr p� kundorder,serie 2','0');
INSERT INTO FTGDATA (POSTTYP, POSTBESKR, FDATA) VALUES ('FKNRS','Antal fakturanrserier, default = 1','0');
INSERT INTO FTGDATA (POSTTYP, POSTBESKR, FDATA) VALUES ('BGNR','Bankgironummer','0');
INSERT INTO FTGDATA (POSTTYP, POSTBESKR, FDATA) VALUES ('PGNR','Plusgironummer','0');

--
-- Table structure for table 'INKRADREG'
--

DROP TABLE IF EXISTS INKRADREG;
CREATE TABLE INKRADREG (
  INKORDNR varchar(10) NOT NULL default '',
  INKORDRADNR int(4) NOT NULL default '0',
  ARTIKELNR varchar(30) default NULL,
  BENEMNING varchar(30) default NULL,
  LEVARTIKELNR varchar(30) default NULL,
  LEVBENEMNING varchar(30) default NULL,
  ENHET varchar(5) default NULL,
  BESTANTAL decimal(10,2) default NULL,
  LEVERERAT decimal(10,2) default NULL,
  RESTNOTERAT decimal(10,2) default NULL,
  INKPRIS decimal(10,2) default NULL,
  LEVVECKA varchar(5) default NULL,
  TORDNR int(6) default NULL,
  OPNR int(6) default NULL,
  PRIMARY KEY  (INKORDNR,INKORDRADNR)
) TYPE=MyISAM;

--
-- Dumping data for table 'INKRADREG'
--


--
-- Table structure for table 'INKREG'
--

DROP TABLE IF EXISTS INKREG;
CREATE TABLE INKREG (
  INKORDNR varchar(10) NOT NULL default '',
  BESTTYP enum('N','D','I','L','A') default NULL,
  ORDERDATUM date default NULL,
  LEVNR varchar(10) default NULL,
  LEVNAMN varchar(30) default NULL,
  LEVADRESS varchar(30) default NULL,
  LEVPOSTNR varchar(6) default NULL,
  LEVPOSTADR varchar(30) default NULL,
  LEVLAND varchar(30) default NULL,
  LEVVALUTA char(3) default NULL,
  LEVBETVILLKOR varchar(50) default NULL,
  LEVVILLKOR varchar(150) default NULL,
  LEVSETT varchar(150) default NULL,
  GODSMERKE varchar(30) default NULL,
  KOMMENTAR varchar(250) default NULL,
  BESTTEXT text,
  VARREF varchar(30) default NULL,
  VARREFTFN varchar(15) default NULL,
  VARREFFAX varchar(15) default NULL,
  ERREF varchar(20) default NULL,
  LEVDATUM date default NULL,
  KUNDNR varchar(30) default NULL,
  FTGNAMN varchar(30) default NULL,
  FTGADR varchar(30) default NULL,
  FTGPOSTNR varchar(6) default NULL,
  FTGPOSTADR varchar(30) default NULL,
  SPRAKKOD char(3) default 'sv',
  BEKREFTKOD enum('H','D','E') default 'E',
  ORDERSTATUS enum('N','F','B','M') default 'N',
  UTSKRIFTSKOD enum('J','N') default 'J',
  ORDERSUMMA decimal(10,2) default NULL,
  PRIMARY KEY  (INKORDNR)
) TYPE=MyISAM;

--
-- Dumping data for table 'INKREG'
--


--
-- Table structure for table 'KSTALLE'
--

DROP TABLE IF EXISTS KSTALLE;
CREATE TABLE KSTALLE (
  ARID char(2) NOT NULL default '',
  KSTALLE varchar(4) NOT NULL default '',
  BENAMNING varchar(100) default NULL,
  PRIMARY KEY  (ARID,KSTALLE)
) TYPE=MyISAM;

--
-- Dumping data for table 'KSTALLE'
--


--
-- Table structure for table 'KTOPLAN'
--

DROP TABLE IF EXISTS KTOPLAN;
CREATE TABLE KTOPLAN (
  ARID char(2) NOT NULL default '',
  KTONR varchar(4) NOT NULL default '',
  BENAMNING varchar(100) default NULL,
  MANUELL enum('J','N') default 'J',
  MOMSKOD varchar(4) default NULL,
  SRUNR int(3) default NULL,
  KSTALLE varchar(4) default NULL,
  PROJEKT varchar(4) default NULL,
  SUBKTO varchar(4) default NULL,
  KTOPLAN varchar(15) default NULL,
  IB decimal(10,2) default NULL,
  UB decimal(10,2) default NULL,
  PRIMARY KEY  (KTONR,ARID)
) TYPE=MyISAM;

--
-- Dumping data for table 'KTOPLAN'
--


--
-- Table structure for table 'KUNDKATEGORI'
--

DROP TABLE IF EXISTS KURESK;
CREATE TABLE KURESK (
ORDERNR VARCHAR(10) not null,
FAKTURANR VARCHAR(20) not null,
KUNDNR VARCHAR(10) not null,
FAKTURADATUM DATE,
EXPIREDATUM DATE,
NETTOBELOPP DECIMAL(10,2),
MOMSBELOPP DECIMAL(10,2),
FAKTURABELOPP DECIMAL(10,2),
BETALD enum('J','N') DEFAULT 'N' not null,
BETALDATUM date,
USERID VARCHAR(8),
VALUTA char(3) DEFAULT 'SEK',
VALUTAKURS DECIMAL(10,2) DEFAULT '1' not null,
VALUTABELOPP DECIMAL(10,2) DEFAULT '0,00',
BAR VARCHAR(2),
VERNR INT,
MOMSKTONR VARCHAR(4),
KTONR VARCHAR(4),
DEBETBELOPP DECIMAL(10,2)
);
alter table KURESK ADD PRIMARY KEY (ORDERNR,FAKTURANR);

--
-- Dumping data for table 'KURESK'
--


--
-- Table structure for table 'KUNDKATEGORI'
--

DROP TABLE IF EXISTS KUNDKATEGORI;
CREATE TABLE KUNDKATEGORI (
  KATEGORINR char(3) NOT NULL default '',
  BESKRIVNING varchar(40) NOT NULL default '',
  PRIMARY KEY  (KATEGORINR)
) TYPE=MyISAM;

--
-- Dumping data for table 'KUNDKATEGORI'
--


--
-- Table structure for table 'KUNDREG'
--

DROP TABLE IF EXISTS KUNDREG;
CREATE TABLE KUNDREG (
  KUNDNR varchar(10) NOT NULL default '',
  KUNDORGNR varchar(12) default NULL,
  NAMN varchar(60) NOT NULL default '',
  ADRESS varchar(30) default NULL,
  POSTNR varchar(6) default NULL,
  POSTADR varchar(30) default NULL,
  LAND varchar(30) default NULL,
  TFNNR varchar(15) default NULL,
  EMAILADR varchar(30) default NULL,
  FAXNR varchar(15) default NULL,
  ERREFERENT varchar(30) default NULL,
  ERREFTFNNR varchar(15) default NULL,
  ERREFEMAIL varchar(60) default NULL,
  SELJARE varchar(20) default NULL,
  FRITEXT varchar(100) default NULL,
  VALUTA char(3) default NULL,
  BETALVILLKOR char(3) default NULL,
  LEVVILLKOR char(3) default NULL,
  LEVSETT char(3) default NULL,
  DISTRIKT char(3) default NULL,
  KUNDKATEGORI char(3) default NULL,
  STDLEVPLATS char(3) default '001',
  ORDERERKENNANDE enum('J','N') default 'J',
  PLOCKLISTA enum('J','N') default 'J',
  FOLJESEDEL enum('J','N') default 'J',
  KRAVBREV enum('J','N') default 'J',
  SPRAKKOD char(3) default NULL,
  EXPAVGIFT enum('J','N') default 'J',
  FRAKTAVG enum('J','N') default 'J',
  KREDITLIMIT decimal(10,2) default NULL,
  KREDITDAGAR int(11) default NULL,
  KREDITKOD char(3) default NULL,
  EXPORTKOD char(3) default NULL,
  SKATTEKOD char(3) default NULL,
  RABATTKOD char(3) default NULL,
  DROJMALSRTA enum('J','N') default 'J',
  DROJMALSFAKTURA enum('J','N') default 'J',
  SAMLINGSFAKT enum('J','N') default 'J',
  SENASTEKRAVDATUM date default NULL,
  SKULD decimal(10,2) default NULL,
  ORDERSTOCK decimal(10,2) default NULL,
  PRISLISTA int NOT NULL default '0',
  PRIMARY KEY  (KUNDNR)
) TYPE=MyISAM;

--
-- Dumping data for table 'KUNDREG'
--

--
-- Table structure for table 'KURESK'
--

DROP TABLE IF EXISTS KURESK;
CREATE TABLE KURESK (
  ORDERNR varchar(10) NOT NULL default '',
  FAKTURANR varchar(20) NOT NULL default '',
  KUNDNR varchar(10) NOT NULL default '',
  FAKTURADATUM date default NULL,
  EXPIREDATUM date default NULL,
  NETTOBELOPP decimal(10,2) default NULL,
  MOMSBELOPP decimal(10,2) default NULL,
  FAKTURABELOPP decimal(10,2) default NULL,
  BETALD enum('J','N') NOT NULL default 'N',
  BETALDATUM date default NULL,
  USERID varchar(8) default NULL,
  VALUTA char(3) default 'SEK',
  VALUTAKURS decimal(10,2) NOT NULL default '1.00',
  VALUTABELOPP decimal(10,2) default '0.00',
  BAR char(2) default NULL,
  VERNR int(11) default NULL,
  MOMSKTONR varchar(4) default NULL,
  KTONR varchar(4) default NULL,
  DEBETBELOPP decimal(10,2) default NULL,
  PRIMARY KEY  (ORDERNR,FAKTURANR)
) TYPE=MyISAM;

--
-- Dumping data for table 'KURESK'
--

--
-- Table structure for table 'LAGERSTELLEREG'
--

DROP TABLE IF EXISTS LAGERSTELLEREG;
CREATE TABLE LAGERSTELLEREG (
  ARLAGST char(1) NOT NULL default '',
  ARTIKELNR varchar(30) NOT NULL default '',
  ARLAGHYLLA varchar(10) default NULL,
  ARLAGSALDO decimal(10,2) default NULL,
  ARINVGRP char(3) default NULL,
  ARABC char(2) default NULL,
  ARVALUTA char(3) default NULL,
  ARIPRIS decimal(10,2) default '0.00',
  ARIKVANT0 decimal(10,2) default '0.00',
  ARIKVANT1 decimal(10,2) default '0.00',
  ARIKVANT2 decimal(10,2) default '0.00',
  ARKALKPRIS decimal(10,2) default '0.00',
  ARPLANKPRIS decimal(10,2) default '0.00',
  ARFRYSTKPRIS decimal(10,2) default '0.00',
  ARBESTKVANT decimal(10,2) default '0.00',
  ARBESTPUNKT decimal(10,2) default '0.00',
  AROMKOST decimal(10,2) default '0.00',
  RESERVERAT decimal(10,2) default NULL,
  PRIMARY KEY  (ARTIKELNR,ARLAGST)
) TYPE=MyISAM;

--
-- Dumping data for table 'LAGERSTELLEREG'
--


--
-- Table structure for table 'LEVREG'
--

DROP TABLE IF EXISTS LEVREG;
CREATE TABLE LEVREG (
  LEVNR varchar(10) NOT NULL default '',
  LEVORGNR varchar(12) default NULL,
  LEVNAMN varchar(30) NOT NULL default '',
  LEVADRESS varchar(30) default NULL,
  LEVPOSTNR varchar(6) default NULL,
  LEVPOSTADR varchar(30) default NULL,
  LEVLAND varchar(30) default NULL,
  LEVTFNNR varchar(15) default NULL,
  LEVFAXNR varchar(15) default NULL,
  LEVTELEX varchar(10) default NULL,
  LEVEMAIL varchar(30) default NULL,
  LEVPOSTGIRONR varchar(10) default NULL,
  LEVBANKGIRONR varchar(10) default NULL,
  LEVREFERENT varchar(20) default NULL,
  LEVREFTFN varchar(15) default NULL,
  LEVMOMSKOD char(1) default '1',
  LEVSKULD decimal(10,2) default NULL,
  LEVKONTO varchar(4) default NULL,
  LEVKUNDNR varchar(30) default NULL,
  LEVVALUTA char(3) default NULL,
  BETALVILKOR char(3) default NULL,
  PRIMARY KEY  (LEVNR)
) TYPE=MyISAM;

--
-- Dumping data for table 'LEVREG'
--


--
-- Table structure for table 'LEVRESK'
--

DROP TABLE IF EXISTS LEVRESK;
CREATE TABLE LEVRESK (
  LEVNR varchar(10) NOT NULL default '',
  FAKTURANR varchar(20) NOT NULL default '',
  REGDATUM date default NULL,
  FAKTDATUM date default NULL,
  EXPIREDATUM date default NULL,
  FAKTTEXT varchar(100) default NULL,
  BAR char(2) default NULL,
  MOMSPROCENT decimal(3,2) default NULL,
  VALUTA char(3) default NULL,
  VALUTAKURS decimal(3,2) default NULL,
  VALUTABELOPP decimal(10,2) default NULL,
  LEVKTONR varchar(4) default NULL,
  FAKTBELOPP decimal(10,2) default NULL,
  MOMSKTONR varchar(4) default NULL,
  MOMSBELOPP decimal(10,2) default NULL,
  DEBETKONTONR varchar(4) default NULL,
  DEBETBELOPP decimal(10,2) default NULL,
  USERID varchar(8) default NULL,
  VERNR int(11) default NULL,
  BETALD enum('J','N') default 'N',
  BETALDDATUM date default NULL,
  OCRNR varchar(20) default NULL,
  PRIMARY KEY  (LEVNR,FAKTURANR)
) TYPE=MyISAM;

--
-- Dumping data for table 'LEVRESK'
--


--
-- Table structure for table 'LEVSETT'
--

DROP TABLE IF EXISTS LEVSETT;
CREATE TABLE LEVSETT (
  LEVSETTNR char(3) NOT NULL default '',
  LEVSETTTEXT varchar(150) NOT NULL default '',
  PRIMARY KEY  (LEVSETTNR)
) TYPE=MyISAM;

--
-- Dumping data for table 'LEVSETT'
--


--
-- Table structure for table 'LEVVILLKOR'
--

DROP TABLE IF EXISTS LEVVILLKOR;
CREATE TABLE LEVVILLKOR (
  VILLKORSNR char(3) NOT NULL default '',
  VILLKORSTEXT varchar(150) NOT NULL default '',
  PRIMARY KEY  (VILLKORSNR)
) TYPE=MyISAM;

--
-- Dumping data for table 'LEVVILLKOR'
--


--
-- Table structure for table 'ORDERRADREG'
--

DROP TABLE IF EXISTS ORDERRADREG;
CREATE TABLE ORDERRADREG (
  ORDERNR varchar(10) NOT NULL default '',
  ORDERRAD int(4) NOT NULL default '0',
  KUNDNR varchar(10) NOT NULL default '',
  RADORDERTYP enum('N','D') default 'N',
  ARTIKELNR varchar(30) NOT NULL default '',
  BENEMNING varchar(60) default NULL,
  LEVERANSVECKA varchar(5) default NULL,
  BESTELLT decimal(10,2) NOT NULL default '0.00',
  APRIS decimal(10,2) NOT NULL default '0.00',
  SUMMA decimal(10,2) NOT NULL default '0.00',
  MOMSKR decimal(10,2) NOT NULL default '0.00',
  LEVERERAT decimal(10,2) default NULL,
  RESTNOTERAT decimal(10,2) default NULL,
  RADRABATT decimal(2,1) default NULL,
  KALKYLPRIS decimal(10,2) default NULL,
  LEVDATUM date default NULL,
  ENHET varchar(4) default 'ST',
  PRIMARY KEY  (ORDERNR,ORDERRAD)
) TYPE=MyISAM;

--
-- Dumping data for table 'ORDERRADREG'
--


--
-- Table structure for table 'ORDERREG'
--

DROP TABLE IF EXISTS ORDERREG;
CREATE TABLE ORDERREG (
  ORDERNR varchar(10) NOT NULL default '',
  KUNDNR varchar(10) NOT NULL default '',
  ORDERTYP enum('N','D','E','F') default 'N',
  ORDERSTATUS enum('A','N','F','B') default 'A',
  ORDERDATUM date default NULL,
  LEVDATUM date default NULL,
  KUNDNAMN varchar(60) default NULL,
  KUNDADRESS varchar(30) default NULL,
  KUNDPOSTNR varchar(6) default NULL,
  KUNDPOSTADR varchar(30) default NULL,
  KUNDLAND varchar(30) default NULL,
  ERREF varchar(20) default NULL,
  LEVADRESS varchar(30) default NULL,
  LEVPOSTNR varchar(6) default NULL,
  LEVPOSTADR varchar(30) default NULL,
  LEVLAND varchar(30) default NULL,
  VARREF varchar(20) default NULL,
  SELJARE varchar(20) default NULL,
  GODSMERKE varchar(100) default NULL,
  BETVILLKTYP enum('F','P','K') NOT NULL default 'F',
  BETVILLKOR char(3) default '001',
  LEVVILLKOR char(3) default '001',
  LEVSETT char(3) default '001',
  PLOCKLISTA enum('J','N') default 'J',
  FOLJESEDEL enum('J','N') default 'J',
  FRAKTAVG enum('J','N') default 'J',
  SKATTEKOD char(3) NOT NULL default '001',
  MOMS decimal(3,2) default NULL,
  VALUTA char(3) default 'SEK',
  EXPORTKOD char(3) default '001',
  SPRAKKOD char(3) default 'sv',
  ORDERSUMMA decimal(10,2) default NULL,
  FRAKTSUMMA decimal(10,2) default NULL,
  FRAKTMOMSKR decimal(10,2) default NULL,
  ORDERMOMS decimal(10,2) default NULL,
  ORDERTOTAL decimal(10,2) default NULL,
  PRIMARY KEY  (ORDERNR)
) TYPE=MyISAM;

--
-- Dumping data for table 'ORDERREG'
--


--
-- Table structure for table 'PASSW'
--

DROP TABLE IF EXISTS PASSW;
CREATE TABLE PASSW (
  KUNDNR varchar(10) NOT NULL default '',
  PASSW varchar(16) NOT NULL default '',
  PRIMARY KEY  (KUNDNR)
) TYPE=MyISAM;

--
-- Dumping data for table 'PASSW'
--

--
-- Table structure for table 'PLOCKLISTEREG'
--

DROP TABLE IF EXISTS PLOCKLISTEREG;
CREATE TABLE PLOCKLISTEREG (
  PLOCKNR int(11) NOT NULL auto_increment,
  ORDERNR varchar(10) NOT NULL default '',
  ORDERRAD int(4) NOT NULL default '0',
  KUNDNR varchar(10) NOT NULL default '',
  ARTIKELNR varchar(30) NOT NULL default '',
  BENEMNING varchar(60) default NULL,
  LEVERANSVECKA varchar(5) default NULL,
  BESTELLT decimal(10,2) NOT NULL default '0.00',
  ATTLEVERERA decimal(10,2) NOT NULL default '0.00',
  LEVERERAT decimal(10,2) NOT NULL default '0.00',
  PLOCKAT decimal(10,2) NOT NULL default '0.00',
  RESTNOTERAT decimal(10,2) NOT NULL default '0.00',
  LEVDATUM date default NULL,
  ENHET varchar(4) default NULL,
  PLOCKSTATUS enum('P','U','B') default 'P',
  PLOCKDATUM date NOT NULL default '0000-00-00',
  PRIMARY KEY  (PLOCKNR)
) TYPE=MyISAM;

--
-- Table structure for table 'PRISLISTA'
--

DROP TABLE IF EXISTS PRISLISTA;
CREATE TABLE PRISLISTA (
  ARTIKELNR varchar(30) NOT NULL default '',
  PRIS1 decimal(4,3) default '0',
  PRIS2 decimal(4,3) default '0',
  PRIS3 decimal(4,3) default '0',
  PRIS4 decimal(4,3) default '0',
  PRIS5 decimal(4,3) default '0',
  PRIMARY KEY  (ARTIKELNR)
) TYPE=MyISAM;

--
-- Dumping data for table 'PRISLISTA'
--

--
-- Table structure for table 'PRODUKTGRUPP'
--

DROP TABLE IF EXISTS PRODUKTGRUPP;
CREATE TABLE PRODUKTGRUPP (
  PRODKLASS varchar(5) NOT NULL default '',
  BESKRIVNING varchar(30) default NULL,
  MOMSKOD varchar(5) default NULL,
  PRIMARY KEY  (PRODKLASS)
) TYPE=MyISAM;

--
-- Dumping data for table 'PRODUKTGRUPP'
--


--
-- Table structure for table 'PROGRAM'
--

DROP TABLE IF EXISTS PROGRAM;
CREATE TABLE PROGRAM (
  PRGNR char(3) NOT NULL default '',
  MENYAVD varchar(20) default NULL,
  MENYGRP varchar(30) default NULL,
  MENYTXT varchar(30) default NULL,
  PROGRAM varchar(8) default NULL,
  PRIMARY KEY  (PRGNR)
) TYPE=MyISAM;

--
-- Dumping data for table 'PROGRAM'
--

INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('026','Ekonomi','Valutaadministration','�ndra valuta','CHGVALW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('025','Ekonomi','Valutaadministration','Ny valuta','ADDVALW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('024','Ekonomi','Kostnadst�lleadministration','Lista kostnadsst�llen','LSTKSTW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('023','Ekonomi','Kostnadst�lleadministration','Visa ett kostnadsst�lle','DSPKSTW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('022','Ekonomi','Kostnadst�lleadministration','Ta bort kostnadst�lle','');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('021','Ekonomi','Kostnadst�lleadministration','�ndra kostnadst�lle','');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('020','Ekonomi','Kostnadst�lleadministration','Nytt kostnadst�lle','ADDKSTW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('019','Ekonomi','Kontoadministration','Lista konton','LSTKTOW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('018','Ekonomi','Kontoadministration','Visa konto','DSPKTOW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('017','Ekonomi','Kontoadministration','Ta bort konto','');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('016','Ekonomi','Kontoadministration','�ndra konto','CHGKTOW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('015','Ekonomi','Kontoadministration','Nytt konto','ADDKTOW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('013','Ekonomi','Bokf�ring','Registrera verifikation','');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('012','Administration','Funktionsadministration','Lista funktioner','LSTFNCW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('011','Administration','Funktionsadministration','Ny funktion','ADDFNCW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('010','Administration','Beh�righetsadministration','Lista beh�righeter','LSTRGTW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('009','Administration','Beh�righetsadministration','Visa beh�righet','');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('007','Administration','Beh�righetsadministration','�ndra beh�righet','');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('006','Administration','Beh�righetsadministration','Ny beh�righet','ADDRGTW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('003','Administration','Anv�ndaradministration','Ta bort anv�ndare','DELUSRW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('005','Administration','Anv�ndaradministration','Lista anv�ndare','LSTUSRW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('002','Administration','Anv�ndaradministration','�ndra anv�ndarinfo','CHGUSRW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('014','Ekonomi','Bokf�ring','Registrera ver. standard','BOKFORSW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('008','Administration','Beh�righetsadministration','Ta bort beh�righet','DELRGTW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('004','Administration','Anv�ndaradministration','Visa en anv�ndare','DSPUSRW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('001','Administration','Anv�ndaradministration','Ny anv�ndare','ADDUSRW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('027','Ekonomi','Valutaadministration','Ta bort valuta','DELVALW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('028','Ekonomi','Valutaadministration','Visa valuta','DSPVALW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('029','Ekonomi','Valutaadministration','Lista valutor','LSTVALW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('030','Ekonomi','Rapporter','Kontorapport','RPTKTOW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('031','Ekonomi','Rapporter','Rapportgenerator','RPTGENW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('032','Ekonomi','R�kenskaps�r','Nytt bokf�rings�r','ADDBARW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('033','Ekonomi','R�kenskaps�r','�ndra bokf�rings�rsdata','CHGBARW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('034','Administration','F�retagsdata','Ny post','ADDFTGW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('035','Administration','F�retagsdata','�ndra post','CHGFTGW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('036','Administration','F�retagsdata','Visa f�retagsdata','DSPFTGW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('037','F�rs�ljning','Kunddata','Ny kund','ADDKUW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('038','F�rs�ljning','Kunddata','Ny leveransadress f�r kund','ADDLEVPW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('039','Ink�p','Leverant�rsdata','Ny leverant�r','ADDLEVW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('040','Ink�p','Leverant�rsdata','Visa en leverant�r','DSPLEVW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('041','Ink�p','Leverant�rsdata','�ndra leverant�rsdata','CHGLEVW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('042','Ekonomi','Bokf�ring','Reg. leverant�rsfaktura','LEVFAKTW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('043','Ekonomi','Rapporter','Leverant�rsreskontra','LEVRESKW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('054','Administration','Betalningsvillkor','Lista betalningsvillkor','LSTBETVW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('044','Ekonomi','Rapporter','F�rfallna levfakturor','ATTBETW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('045','Ekonomi','Rapporter','Saldolista','SDOLISW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('046','F�rs�ljning','Kunddata','Visa kunddata','DSPKUW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('047','F�rs�ljning','Kunddata','�ndra kunddata','CHGKUW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('048','F�rs�ljning','Kunddata','Lista kunder','LSTKUW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('049','Administration','F�retagsdata','Byta f�retag','BYTFTGW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('050','Materialhantering','Artikeldata','Ny artikel','ADDARW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('051','Materialhantering','Artikeldata','Visa grunddata f�r en artikel','DSPARW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('052','Materialhantering','Artikeldata','Visa en artikels ekonomidata','DSPAREW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('053','Materialhantering','Artikeldata','�ndra artikeldata','CHGARW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('055','Administration','Betalningsvillkor','Nya betalningsvillkor','ADDBETVW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('056','Materialhantering','Artikeldata','Lista artiklar','LSTARW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('057','Administration','Betalningsvillkor','�ndra betalningsvillkor','CHGBETVW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('058','Ink�p','Best�llningar','Registrera ink�psorder','ADDINKW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('059','Ink�p','Best�llningar','(�ndra best�llning)','CHGINKW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('060','Ink�p','Best�llningar','(Annulera best�llning)','DELINKW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('061','Ink�p','Best�llningar','Visa best�llning','DSPINKW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('062','Ink�p','Best�llningar','Best�llningsstock','LSTINKW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('063','Ink�p','Best�llningar','Skriv ut best�llning','PRTINKW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('064','Ink�p','Best�llningar','(Avprickning f�ljesedel)','UPDINKW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('065','F�rs�ljning','Kundorder','Registrera kundorder','ADDORDW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('066','F�rs�ljning','Kundorder','(�ndra kundorder)','CHGORDW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('067','F�rs�ljning','Kundorder','(Makulera kundorder)','DELORDW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('068','F�rs�ljning','Kundorder','Visa en kundorder','DSPORDW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('069','F�rs�ljning','Kundorder','Lista kundorder','LSTORDW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('070','F�rs�ljning','Kundorder','Skriva ut plocklista','PLORDW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('071','F�rs�ljning','Kundorder','(Skriva ut f�ljesedel)','FSORDW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('072','F�rs�ljning','Kundorder','Fakturera kundorder','KUFAKTW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('074','Administration','F�retagsdata','Ny text i textregistret','ADDTXTW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('073','Ink�p','Leverant�rsdata','Lista leverant�rer','LSTLEVW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('076','Administration','Leveransvillkor','Nya leveransvillkor','ADDLEVVW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('075','Administration','F�retagsdata','Radera post i textregistret','DELTXTW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('077','Administration','Leveransvillkor','Lista leveransvillkor','LSTLEVVW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('078','Administration','Leveranss�tt','Nya leveranss�tt','ADDLEVSW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('079','Administration','Leveranss�tt','Lista leveranss�tt','LSTLEVSW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('080','Ekonomi','Rapporter','Balansr�kning','BALRPTW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('081','Ekonomi','Rapporter','Huvudbok','HUVBOKW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('082','Ekonomi','Rapporter','Dagbok','DAGBOKW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('083','F�rs�ljning','Kunddata','Lista kunders leveransplatser','LSTLEVPW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('084','Administration','F�retagsdata','Ny databasregistrering','ADDFORW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('085','Administration','F�retagsdata','Lista databaser','LSTFORW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('086','Materialhantering','Artikeladmin.','Ny produktklass/produktgrupp','ADDPKDW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('087','Materialhantering','Artikeladmin.','Lista produktklass/produktgrup','LSTPKDW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('088','Ekonomi','R�kenskaps�r','Visa bokf�rings�r','DSPBARW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('089','Administration','F�retagsdata','Lista f�retagsdata','LSTFTGW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('090','Ekonomi','Rapporter','Resultatrapport','RESRPTW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('091','Ekonomi','R�kenskaps�r','Lista alla r�kenskaps�r','LSTBARW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('092','F�rs�ljning','Kunddata','S�ka kunder','SRCHKUW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('093','Ekonomi','Rapporter','Skapa SIE-fil','RPTSIEW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('094','F�rs�ljning','Kundorder','Pricka av plocklista','PLCHGW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('095','Ekonomi','Rapporter','Kundreskontra','KURESKW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('096','Administration','F�retagsdata','Lista texter i TEXTREG','LSTTXTW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('097','Administration','F�retagsdata','Visa en post i TEXTREG','DSPTXTW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('098','Materialhantering','Artikeldata','S�ka artikel','SRCHARW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('099','Ekonomi','Bokf�ring','Reg.betald kundfaktura','KUFAKTBW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('100','Materialhantering','Artikeladmin','Lista prislistor','LSTPRISW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('101','Materialhantering','Artikeladmin','Ladda nya prislistor','ADDPRISW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('102','Materialhantering','Artikeladmin','�ndra i prislistor','CHGPRISW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('103','Administration','Funktionsadministration','Lista program/moduler','LSTPRGW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('104','F�rs�ljning','Offerter','Registrera offert','ADDOFFW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('105','F�rs�ljning','Offerter','Visa en offert','DSPOFFW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('106','Materialhantering','Artikeladmin','Visa lagerst�llepost','DSPLSW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('107','Materialhantering','Artikeladmin','Radera lagerst�llepost','DELLSW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('108','Materialhantering','Artikeladmin','�ndra lagerst�llepost','CHGLSW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('109','F�rs�ljning','Offerter','�ndra en offert','CHGOFFW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('110','F�rs�ljning','Offerter','Radera en offert','DELOFFW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('111','F�rs�ljning','Offerter','Skriv ut en offert','PRTOFFW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('112','F�rs�ljning','Offerter','G�ra en offert till order','OFF2ORDW');
INSERT INTO PROGRAM (PRGNR, MENYAVD, MENYGRP, MENYTXT, PROGRAM) VALUES ('113','Administration','Beh�righetsadministration','Tilldela en anv�ndare total beh�righeter','TOTRGTW');

--
-- Table structure for table 'RIGHTS'
--

DROP TABLE IF EXISTS RIGHTS;
CREATE TABLE RIGHTS (
  USERID varchar(8) NOT NULL default '',
  TRNSID varchar(8) NOT NULL default '',
  PRIMARY KEY  (USERID,TRNSID)
) TYPE=MyISAM;

--
-- Dumping data for table 'RIGHTS'
--
INSERT INTO RIGHTS (USERID, TRNSID) VALUES ('NEWUSER','ADDRGTW');
INSERT INTO RIGHTS (USERID, TRNSID) VALUES ('NEWUSER','ARICHK');
INSERT INTO RIGHTS (USERID, TRNSID) VALUES ('NEWUSER','BARDSP');
INSERT INTO RIGHTS (USERID, TRNSID) VALUES ('NEWUSER','KTOCHK');
INSERT INTO RIGHTS (USERID, TRNSID) VALUES ('NEWUSER','KTOLST');
INSERT INTO RIGHTS (USERID, TRNSID) VALUES ('NEWUSER','KTOVIEW');
INSERT INTO RIGHTS (USERID, TRNSID) VALUES ('NEWUSER','PRGLST');
INSERT INTO RIGHTS (USERID, TRNSID) VALUES ('NEWUSER','RGTADD');
INSERT INTO RIGHTS (USERID, TRNSID) VALUES ('NEWUSER','RGTCHK');
INSERT INTO RIGHTS (USERID, TRNSID) VALUES ('NEWUSER','RGTDEL');
INSERT INTO RIGHTS (USERID, TRNSID) VALUES ('NEWUSER','RGTLST');
INSERT INTO RIGHTS (USERID, TRNSID) VALUES ('NEWUSER','TRHDADD');
INSERT INTO RIGHTS (USERID, TRNSID) VALUES ('NEWUSER','TRNSADD');
INSERT INTO RIGHTS (USERID, TRNSID) VALUES ('NEWUSER','TRNSDEL');
INSERT INTO RIGHTS (USERID, TRNSID) VALUES ('NEWUSER','USERADD');
INSERT INTO RIGHTS (USERID, TRNSID) VALUES ('NEWUSER','USERLST');
INSERT INTO RIGHTS (USERID, TRNSID) VALUES ('NEWUSER','VERUPD');
INSERT INTO RIGHTS (USERID, TRNSID) VALUES ('OLFIX','ADDRGTW');
INSERT INTO RIGHTS (USERID, TRNSID) VALUES ('OLFIX','ARICHK');
INSERT INTO RIGHTS (USERID, TRNSID) VALUES ('OLFIX','BARDSP');
INSERT INTO RIGHTS (USERID, TRNSID) VALUES ('OLFIX','KTOCHK');
INSERT INTO RIGHTS (USERID, TRNSID) VALUES ('OLFIX','KTOLST');
INSERT INTO RIGHTS (USERID, TRNSID) VALUES ('OLFIX','KTOVIEW');
INSERT INTO RIGHTS (USERID, TRNSID) VALUES ('OLFIX','PRGLST');
INSERT INTO RIGHTS (USERID, TRNSID) VALUES ('OLFIX','RGTADD');
INSERT INTO RIGHTS (USERID, TRNSID) VALUES ('OLFIX','RGTCHK');
INSERT INTO RIGHTS (USERID, TRNSID) VALUES ('OLFIX','RGTDEL');
INSERT INTO RIGHTS (USERID, TRNSID) VALUES ('OLFIX','RGTLST');
INSERT INTO RIGHTS (USERID, TRNSID) VALUES ('OLFIX','TRHDADD');
INSERT INTO RIGHTS (USERID, TRNSID) VALUES ('OLFIX','TRNSADD');
INSERT INTO RIGHTS (USERID, TRNSID) VALUES ('OLFIX','TRNSDEL');
INSERT INTO RIGHTS (USERID, TRNSID) VALUES ('OLFIX','USERADD');
INSERT INTO RIGHTS (USERID, TRNSID) VALUES ('OLFIX','USERLST');
INSERT INTO RIGHTS (USERID, TRNSID) VALUES ('OLFIX','VERUPD');
INSERT INTO RIGHTS (USERID, TRNSID) VALUES ('TESTARE','LSTUSRW');
INSERT INTO RIGHTS (USERID, TRNSID) VALUES ('TESTARE','PRGLST');
INSERT INTO RIGHTS (USERID, TRNSID) VALUES ('TESTARE','RGTCHK');
INSERT INTO RIGHTS (USERID, TRNSID) VALUES ('TESTARE','USERADD');
INSERT INTO RIGHTS (USERID, TRNSID) VALUES ('TESTARE','USERDSP');
INSERT INTO RIGHTS (USERID, TRNSID) VALUES ('TESTARE','USERLST');

--
-- Table structure for table 'STDLEVPLATS'
--

DROP TABLE IF EXISTS STDLEVPLATS;
CREATE TABLE STDLEVPLATS (
  STDLEVPLATS char(3) NOT NULL default '',
  KUNDNR varchar(10) NOT NULL default '',
  ADRESS varchar(30) NOT NULL default '',
  POSTNR varchar(6) NOT NULL default '',
  POSTADR varchar(30) NOT NULL default '',
  LAND varchar(30) default NULL,
  PRIMARY KEY  (STDLEVPLATS,KUNDNR)
) TYPE=MyISAM;

--
-- Dumping data for table 'STDLEVPLATS'
--


--
-- Table structure for table 'TEXTREG'
--

DROP TABLE IF EXISTS TEXTREG;
CREATE TABLE TEXTREG (
  TEXTNR char(3) NOT NULL default '',
  TXT text,
  PRIMARY KEY  (TEXTNR)
) TYPE=MyISAM;

--
-- Dumping data for table 'TEXTREG'
--


--
-- Table structure for table 'TRANSID'
--

DROP TABLE IF EXISTS `TRANSID`;
CREATE TABLE `TRANSID` (
  `TRNSID` varchar(8) NOT NULL default '',
  `TRNSTXT` varchar(60) default NULL,
  PRIMARY KEY  (`TRNSID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table 'TRANSID'
/*!40000 ALTER TABLE `TRANSID` DISABLE KEYS */;

LOCK TABLES `TRANSID` WRITE;
INSERT INTO `TRANSID` (`TRNSID`, `TRNSTXT`) VALUES ('ARICHK','Kontrollera om visst bokf�rings�r finns'),('BARDSP','H�mta data f�r angivet bokf�rings�r'),('BARCHK','Kontrollera om visst bokf�rings�r finns'),('BOKF','Bokf�ringsprogram'),('FORDSP','Visa info om databas nr x'),('FTGUPD','Uppdatera f�retagsdata'),('KSTADD','Nyuppl�gg av kostnadsst�lle'),('KSTCHK','Kontrollera om visst kostnadst�lle finns'),('KSTDSP','Visa info f�r ett kostnadst�lle'),('KSTLST','Lista kostnadsst�llen p� sk�rm'),('KTOADD','L�gga till en ny post i konto'),('KTOCHG','�ndra info f�r ett kontonr'),('KTOCHK','Kontrollera om visst konto finns'),('KTODEL','Ta bort post i konto (endast utan transaktioner)'),('KTODSP','Visa info p� ett konto'),('KTOLST','Lista alla konton, nr och text'),('KTORPT','Lista alla poster i tabellen VERRAD'),('KTOUPD','Uppdatera konto med antingen debet eller kredit'),('KTOVIEW','Visa kontonr och ben�mning p� sk�rm'),('PRGLST','Lista program'),('RGTADD','L�gga till beh�righet till transaktioner'),('RGTCHK','Kontrolera anv�ndares beh�righet'),('RGTDEL','Ta bort beh�righet till transaktioner'),('RGTDSP','Visa beh�righeter f�r en anv�ndare'),('RGTLST','Lista alla beh�righeter'),('TRHDADD','L�gga till ny loggpost i TRHD'),('TRNSADD','Ny post i TRANSID'),('TRNSCHG','�ndra post i TRANSID'),('TRNSDEL','Ta bort post i TRANSID'),('TRNSDSP','Visa enstaka TRANSID'),('TRNSLST','Lista alla TRANSID'),('USERADD','Ny post i USER'),('USERCHG','�ndra post i USER'),('USERDEL','Ta bort post i USER'),('USERDSP','Visa en anv�ndare'),('USERLST','Lista alla anv�ndare'),('VALLST','Lista valutor'),('VALADD','L�gga upp en ny valuta'),('VALCHG','�ndra valutainformation'),('VALDEL','Ta bort en valuta'),('VALDSP','Visa en valuta'),('VERUPD','Nyuppl�ggning av verifikat'),('VERDSP','Visa enstaka verifikation'),('VRDADD','Ny detaljpost f�r verifikation till VERD'),('VRHADD','Ny huvudpost f�r verifikation till VERH'),('WRREC','Skriva post till tempfilen /tmp/vernr.txt'),('ATTBET','Lista leverant�rsfakturor att betala'),('BARADD','L�gga upp nytt bokf�rings�r'),('BARCHG','�ndra data f�r angivet bokf�rings�r'),('BARFND','Hitta bokf�rings�r f�r angivet datum'),('BETDSP','Visa ett betalningsvillkor'),('FTGADD','L�gga upp en ny f�retagspost'),('FTGDSP','Visa f�retagsdata'),('FTGLST','Lista posttyper f�r f�retagsdata'),('FTGLIS','Lista f�retagsdata'),('KUADD','Registrera nya kunder'),('KUCHG','�ndra kunddata'),('KUCHK','Kontrollera om kundnr finns'),('KUDSP','Visa kunddata'),('KULST','Lista kunder, kundnr och namn'),('LEVADD','L�gga upp en ny leverant�r'),('LEVCHG','�ndra leverant�rsdata'),('LEVDSP','Visa en leverant�r'),('LEVLST','Lista leverant�rer,nr och namn'),('LRESRPT','Lista alla obetalda poster i tabellen LEVRESK'),('LRESADD','Ny post i leverant�rsreskontran'),('RPTCRE','Rapportgenerator. Skapa rapporter'),('SLPADD','Standardleveransplats'),('TRNTST','Detta �r en testfunktion'),('ARCHK','Kontrollera om artikelnummer finns'),('ARADD','L�gga upp en ny artikel'),('AR2ADD','L�gga upp ny artikel i lagerst�lleregister'),('ARDSP','Visa grunddata f�r en artikel'),('ARDSPL','Visa lagerdata f�r en artikel'),('ARCHG','�ndra grunddata f�r en artikel'),('ARCHGL','�ndra lagerst�lledata f�r en artikel'),('BETLST','Lista betalningsvillkor'),('BETADD','L�gga upp ett nytt betalningsvillkor'),('ARLST','Lista artiklar(artikelnr,ben�mn1,ben�mn2)'),('BETCHG','�ndra data f�r betalningsvillkor'),('TXTDSP','Visa texter ur TEXTREG'),('TXTADD','L�gg upp en ny post i TEXTREG'),('INKADD','L�gga upp en ny ink�psorder'),('INKRADD','L�gga upp en ny ink�psorderrad'),('TXTDEL','Radera post i TEXTREG'),('INKRLST','Lista alla rader p� angiven ink�psorder'),('INKHDSP','Visa orderhuvud f�r angiven ink�psorder'),('INKLST','Best�llningsstock'),('LEVVDSP','Visa ett leveransvillkor'),('LEVSDSP','Visa ett leveranss�tt'),('LEVVADD','L�gga upp ett nytt leveransvillkor'),('LEVSADD','L�gga upp ett nytt leveranss�tt'),('LEVVLST','Lista leveransvillkor'),('LEVSLST','Lista leveranss�tt'),('VERHDSP','H�mta mindatum och maxdatum f�r angivet bokf.�r'),('VERHLST','Lista verifikationers huvudposter f�r �nskat bokf�rings�r'),('HBOKRPT','Huvudboksrapport'),('DBOKRPT','Dagboksrapport'),('PRTAPI','Utskriftsinterface'),('LEVPLST','Lista kunders leveransadresser'),('FORCHK','Kontr. om databas finns i tabell DATABAS'),('FORADD','Ny databas i tabellen DATABAS'),('FORLST','Lista databaser i tabell DATABAS'),('PKDADD','Ny produktgrupp/produktkod/produktklass'),('PKDLST','Lista produktgrupper/produktkoder/produktklasser'),('WKUDSP','Visa begr�nsade kunddata f�r webbkund'),('ARLSTL','Lista artiklar med lagersaldo'),('ARLIS','Lista artiklar f�r angiven produktklass'),('ARLSPK','Lista artiklar f�r angiven produktkod'),('AR2UPD','Uppdatera artikelpost i LAGERSTELLEREG'),('BARLST','Lista bokf�rings�r'),('KUSRCH','S�ka kunder p� namn, postnr, tfnnr eller postadr'),('LEVPDSP','Visa en standardleveransplats'),('ORDADD','Nyuppl�gg av kundorderhuvud'),('ORDCHK','Kontrollera diverse uppgifter p� kundorder'),('ORDDSP','Visa en kundorders huvudpost'),('ORDRDSP','Visa en kundorders orderrader'),('PKDDSP','Visa en produktgrupp/produktkod/produktklass'),('SIEEXPK','SIE-export av kontoplan'),('SIEEXPR','SIE-export av resultat'),('SIEEXPV','SIE-export av verifikat'),('DBCHK','Lista databaser registrerade i databasen mysql'),('ORDLST2','Lista kundorder med begr�nsad information'),('ORDLST','Lista kundorder'),('PICKADD','Nytt plock av kundorderrad'),('PICKDSP','Visa plockade men ej utskrivna plock'),('PICKLST','Lista avprickade kundorderrader'),('KRESADD','Ny post till kundreskontran'),('ORADUPD','Uppdatera �nskat f�lt i ORDERRADREG'),('ORDRUPD','Uppdatera ORDERRADREG'),('ORDUPD','Uppdatera �nskat f�lt i ORDERREG'),('ARLSPK2','Lista artiklar/produktkod med saldo'),('KRESLST','Lista poster i kundreskontran'),('ORDRADD','L�gga upp ny rad p� kundorder'),('TXTLST','Lista texter i TEXTREG'),('DSPTXTW','Visa en text i textregistret'),('ARSRCH','S�ka artikel'),('PRISDSP','Visa prislistepriser p� �nskad artikel'),('OFFADD','Registrera ny offert (huvudet)'),('OFFRADD','Registrera ny offert (rad)'),('OFFLST','Lista offerter'),('OFFDSP','Visa en offert'),('OFFRDSP','Visa alla offertrader f�r en offert'),('LSDEL','Radera post i LAGERSTELLEREG.'),('OFFCHG','Uppdatera offertregistret.'),('OFFRCHG','�ndra/uppdatera offertrader'),('OFFDEL','Radera offerter'),('TOTRGT','Skapa totala r�ttigheter f�r en anv�ndare.'),('TOTADD','Ge en anv�ndare fullst�ndig beh�righet.'),('DATABASE','Hantera olika databaser');
UNLOCK TABLES;
/*!40000 ALTER TABLE `TRANSID` ENABLE KEYS */;



--
-- Table structure for table 'TRHD'
--

DROP TABLE IF EXISTS TRHD;
CREATE TABLE TRHD (
  TRNSNR int(11) NOT NULL auto_increment,
  TRNSID varchar(8) NOT NULL default '',
  TID varchar(20) NOT NULL default '',
  USERID varchar(8) NOT NULL default '',
  TRNSDATA varchar(255) default NULL,
  PRIMARY KEY  (TRNSNR)
) TYPE=MyISAM;

--
-- Dumping data for table 'TRHD'
--


--
-- Table structure for table 'USR'
--

DROP TABLE IF EXISTS USR;
CREATE TABLE USR (
  USERID varchar(8) NOT NULL default '',
  NAMN varchar(30) default NULL,
  AVD varchar(10) default NULL,
  GRUPP varchar(10) default NULL,
  PRIMARY KEY  (USERID)
) TYPE=MyISAM;

--
-- Dumping data for table 'USR'
--

INSERT INTO USR (USERID, NAMN, AVD, GRUPP) VALUES ('OLFIX','Olfix Superuser','IT','Stab');
INSERT INTO USR (USERID, NAMN, AVD, GRUPP) VALUES ('TESTARE','Testare Test','Prov','Utv');
INSERT INTO USR (USERID, NAMN, AVD, GRUPP) VALUES ('ADMIN','Adam Administrat�r','IT','Stab');
INSERT INTO USR (USERID, NAMN, AVD, GRUPP) VALUES ('OLLE','Olle Olfixsson','Ekonomi','Stab');
INSERT INTO USR (USERID, NAMN, AVD, GRUPP) VALUES ('NEWUSER','Nyanv�ndare','IT','Stab');

--
-- Table structure for table 'VALUTA'
--

DROP TABLE IF EXISTS VALUTA;
CREATE TABLE VALUTA (
  VALUTAID char(3) NOT NULL default '',
  LAND varchar(15) default NULL,
  SALJ decimal(3,2) default NULL,
  KOP decimal(3,2) default NULL,
  BETECKNING varchar(15) default NULL,
  PRIMARY KEY  (VALUTAID)
) TYPE=MyISAM;

--
-- Dumping data for table 'VALUTA'
--

INSERT INTO VALUTA (VALUTAID, LAND, SALJ, KOP, BETECKNING) VALUES ('DKK','Danmark',1.22,1.22,'Kronor');
INSERT INTO VALUTA (VALUTAID, LAND, SALJ, KOP, BETECKNING) VALUES ('NOK','Norge',1.23,1.23,'Kronor');
INSERT INTO VALUTA (VALUTAID, LAND, SALJ, KOP, BETECKNING) VALUES ('NYZ','Nya Zeeland',4.45,4.45,'Dollar');
INSERT INTO VALUTA (VALUTAID, LAND, SALJ, KOP, BETECKNING) VALUES ('SAR','Saudiarabien',2.40,2.40,'Riyal');
INSERT INTO VALUTA (VALUTAID, LAND, SALJ, KOP, BETECKNING) VALUES ('HKD','Honkong',0.00,0.00,'Dollar');
INSERT INTO VALUTA (VALUTAID, LAND, SALJ, KOP, BETECKNING) VALUES ('MYR','Malaysia',2.36,2.36,'Ringgit');
INSERT INTO VALUTA (VALUTAID, LAND, SALJ, KOP, BETECKNING) VALUES ('SGD','Singapore',5.08,5.08,'Dollar');
INSERT INTO VALUTA (VALUTAID, LAND, SALJ, KOP, BETECKNING) VALUES ('CAD','Kanada',5.66,5.66,'Dollar');
INSERT INTO VALUTA (VALUTAID, LAND, SALJ, KOP, BETECKNING) VALUES ('AUD','Australien',5.03,5.03,'Dollar');
INSERT INTO VALUTA (VALUTAID, LAND, SALJ, KOP, BETECKNING) VALUES ('USD','USA',8.97,8.97,'Dollar');
INSERT INTO VALUTA (VALUTAID, LAND, SALJ, KOP, BETECKNING) VALUES ('JPY','Japan',7.38,7.38,'Yen');
INSERT INTO VALUTA (VALUTAID, LAND, SALJ, KOP, BETECKNING) VALUES ('GBP','Storbritanien',14.26,14.26,'Pund');
INSERT INTO VALUTA (VALUTAID, LAND, SALJ, KOP, BETECKNING) VALUES ('EUR','Europa',9.08,9.08,'Euro');
INSERT INTO VALUTA (VALUTAID, LAND, SALJ, KOP, BETECKNING) VALUES ('CHF','Schweiz',0.00,0.00,'France');
INSERT INTO VALUTA (VALUTAID, LAND, SALJ, KOP, BETECKNING) VALUES ('SEK','Sverige',0.99,0.99,'Kronor');
INSERT INTO VALUTA (VALUTAID, LAND, SALJ, KOP, BETECKNING) VALUES ('EEK','Estland',0.59,0.57,'Kronor');

--
-- Table structure for table 'VERHUVUD'
--

DROP TABLE IF EXISTS VERHUVUD;
CREATE TABLE VERHUVUD (
  VERNR int(11) NOT NULL default '0',
  ARID char(2) NOT NULL default '',
  VERDATUM date default NULL,
  REGDAT date default NULL,
  DEBET decimal(10,2) default NULL,
  KREDIT decimal(10,2) default NULL,
  VERTEXT varchar(60) default NULL,
  KORRIGERAR int(11) default NULL,
  KORRIGERAD int(11) default NULL,
  USERID varchar(8) default NULL,
  PRIMARY KEY  (VERNR,ARID)
) TYPE=MyISAM;

--
-- Dumping data for table 'VERHUVUD'
--


--
-- Table structure for table 'VERRAD'
--

DROP TABLE IF EXISTS VERRAD;
CREATE TABLE VERRAD (
  VERNR int(11) NOT NULL default '0',
  RADNR smallint(6) NOT NULL default '0',
  ARID char(2) NOT NULL default '',
  KTONR varchar(4) default NULL,
  BELOPP decimal(10,2) default NULL,
  DK enum('D','K') default NULL,
  KSTALLE varchar(4) default NULL,
  PROJEKT varchar(4) default NULL,
  SUBKTO varchar(4) default NULL,
  DEFINITIV enum('J','N') default 'N',
  STRUKEN enum('J','N') default 'N',
  PRIMARY KEY  (VERNR,RADNR,ARID)
) TYPE=MyISAM;

--
-- Dumping data for table 'VERRAD'
--

--
-- Table structure for table 'WEBBKUND'
--

DROP TABLE IF EXISTS WEBBKUND;
CREATE TABLE WEBBKUND (
  KUNDNR varchar(10) NOT NULL default '',
  NAMN varchar(60) NOT NULL default '',
  ADRESS varchar(30) default NULL,
  POSTNR varchar(6) default NULL,
  POSTADR varchar(30) default NULL,
  LAND varchar(30) default NULL,
  ADRESS2 varchar(30) default NULL,
  POSTNR2 varchar(6) default NULL,
  POSTADR2 varchar(30) default NULL,
  LAND2 varchar(30) default NULL,
  TFNNR varchar(15) default NULL,
  EMAILADR varchar(30) default NULL,
  BETALVILLKOR char(3) default NULL,
  LEVVILLKOR char(3) default NULL,
  LEVSETT char(3) default NULL,
  ORDERERKENNANDE enum('J','N') default 'J',
  PLOCKLISTA enum('J','N') default 'J',
  FOLJESEDEL enum('J','N') default 'J',
  KRAVBREV enum('J','N') default 'J',
  EXPAVGIFT enum('J','N') default 'J',
  FRAKTAVG enum('J','N') default 'J',
  KREDITLIMIT decimal(10,2) default NULL,
  KREDITDAGAR int(11) default NULL,
  DROJMALSRTA enum('J','N') default 'J',
  DROJMALSFAKTURA enum('J','N') default 'J',
  SENASTEKRAVDATUM date default NULL,
  SKULD decimal(10,2) default NULL,
  ORDERSTOCK decimal(10,2) default NULL,
  PASSWORD varchar(16) NOT NULL default '',
  PRIMARY KEY  (KUNDNR)
) TYPE=MyISAM;
