use olfix;
DROP TABLE IF EXISTS KUNDKATEGORI;
create table KUNDKATEGORI(
KATEGORINR VARCHAR(3) not null PRIMARY KEY,
BESKRIVNING VARCHAR(40)not null);
use olfixtst;
DROP TABLE IF EXISTS KUNDKATEGORI;
create table KUNDKATEGORI(
KATEGORINR VARCHAR(3) not null PRIMARY KEY,
BESKRIVNING VARCHAR(40)not null);



