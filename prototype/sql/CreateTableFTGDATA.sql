-- MySQL dump 10.9
--
-- Host: localhost    Database: olfixtst
-- ------------------------------------------------------
-- Server version	4.1.12

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `FTGDATA`
--

DROP TABLE IF EXISTS `FTGDATA`;
CREATE TABLE `FTGDATA` (
  `POSTTYP` varchar(5) NOT NULL default '',
  `POSTBESKR` varchar(60) default NULL,
  `FDATA` text,
  PRIMARY KEY  (`POSTTYP`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `FTGDATA`
--


/*!40000 ALTER TABLE `FTGDATA` DISABLE KEYS */;
LOCK TABLES `FTGDATA` WRITE;
INSERT INTO `FTGDATA` (`POSTTYP`, `POSTBESKR`, `FDATA`) VALUES ('FNAMN','Företagsnamn','PROGRAM AB'),
('FTGNR','Företagsnummer','991199-1991'),
('ADR1','Postadress','Box 70'),
('ADR2','Postnummer till Postadress','199 98'),
('ADR3','Ort till Postadress','PROGSTAD'),
('ADR4','Besöksadress','Syntaxvägen 99'),
('ADR5','Postnr till Besöksadress','199 98'),
('ADR6','Ort till Besöksadress','PROGSTAD'),
('ADR7','Godsadress','Verktygsgatan 11'),
('ADR8','Postnr till Godsadress','199 97'),
('ADR9','Ort till Godsadress','PROGSTAD'),
('TFNVX','Telefonnummer till vx','09-199300'),
('TFN1','Telefonnummer','09-199300'),
('TFN2','Mobiltelefonnummer','070-98765411'),
('TFNMB','Mobiltelefonnummer','070-98765411'),
('TFAX','Telefaxnummer','09-199397'),
('TELEX','Telexnummer','12345'),
('EML1','E-mailadress','jan@pihlgren.se'),
('MOMSI','Momskonto, ingående moms','2641'),
('MOMSU','Momskonto, utgående moms','2611'),
('MOMS1','Momssats 1','25'),
('MOMS2','Momssats 2','12'),
('MOMS3','Momssats 3','6'),
('MOMS4','Momssats 4',' '),
('MOMS5','Momssats 5',' '),
('AUTOK','Automatkontering J/N','N'),
('KORNR','Senast använda kundordernr','0'),
('BF1','Bokföringsperiod 1','Januari'),
('BF2','Bokföringsperiod 2','Februari'),
('BF3','Bokföringsperiod 3','Mars'),
('BF4','Bokföringsperiod 4','April'),
('BF5','Bokföringsperiod 5','Maj'),
('BF6','Bokföringsperiod 6','Juni'),
('BF7','Bokföringsperiod 7','Juli'),
('BF8','Bokföringsperiod 8','Augusti'),
('BF9','Bokföringsperiod 9','September'),
('BF10','Bokföringsperiod 10','Oktober'),
('BF11','Bokföringsperiod 11','Novemper'),
('BF12','Bokföringsperiod 12','December'),
('BF13','Bokföringsperiod 13','Januari'),
('INKNR','Senast använda inköpsordernr','28'),
('SNIKD','Branschtillhörighet','82301'),
('WKUNR','Senaste använda webbkundnummer','4379'),
('FAKNR','Senaste fakturanr på kundorder','0'),
('FKNR2','Senaste fakturanr på kundorder,serie 2','100000'),
('FKNRS','Antal fakturanrserier, default = 1','1'),
('PGNR','Plusgironummer','9999999-9'),
('BGNR','Bankgironummer','9999-9999');
UNLOCK TABLES;
/*!40000 ALTER TABLE `FTGDATA` ENABLE KEYS */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

