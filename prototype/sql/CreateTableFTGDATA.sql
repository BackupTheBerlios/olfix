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
INSERT INTO `FTGDATA` (`POSTTYP`, `POSTBESKR`, `FDATA`) VALUES ('FNAMN','F�retagsnamn','PROGRAM AB'),
('FTGNR','F�retagsnummer','991199-1991'),
('ADR1','Postadress','Box 70'),
('ADR2','Postnummer till Postadress','199 98'),
('ADR3','Ort till Postadress','PROGSTAD'),
('ADR4','Bes�ksadress','Syntaxv�gen 99'),
('ADR5','Postnr till Bes�ksadress','199 98'),
('ADR6','Ort till Bes�ksadress','PROGSTAD'),
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
('MOMSI','Momskonto, ing�ende moms','2641'),
('MOMSU','Momskonto, utg�ende moms','2611'),
('MOMS1','Momssats 1','25'),
('MOMS2','Momssats 2','12'),
('MOMS3','Momssats 3','6'),
('MOMS4','Momssats 4',' '),
('MOMS5','Momssats 5',' '),
('AUTOK','Automatkontering J/N','N'),
('KORNR','Senast anv�nda kundordernr','0'),
('BF1','Bokf�ringsperiod 1','Januari'),
('BF2','Bokf�ringsperiod 2','Februari'),
('BF3','Bokf�ringsperiod 3','Mars'),
('BF4','Bokf�ringsperiod 4','April'),
('BF5','Bokf�ringsperiod 5','Maj'),
('BF6','Bokf�ringsperiod 6','Juni'),
('BF7','Bokf�ringsperiod 7','Juli'),
('BF8','Bokf�ringsperiod 8','Augusti'),
('BF9','Bokf�ringsperiod 9','September'),
('BF10','Bokf�ringsperiod 10','Oktober'),
('BF11','Bokf�ringsperiod 11','Novemper'),
('BF12','Bokf�ringsperiod 12','December'),
('BF13','Bokf�ringsperiod 13','Januari'),
('INKNR','Senast anv�nda ink�psordernr','28'),
('SNIKD','Branschtillh�righet','82301'),
('WKUNR','Senaste anv�nda webbkundnummer','4379'),
('FAKNR','Senaste fakturanr p� kundorder','0'),
('FKNR2','Senaste fakturanr p� kundorder,serie 2','100000'),
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

