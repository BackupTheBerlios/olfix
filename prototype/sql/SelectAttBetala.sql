# Connection: olfix
# Host: localhost
# Saved: 2003-08-18 08:13:24
# 
SELECT EXPIREDATUM,LEVNR,FAKTURANR,FAKTBELOPP,VALUTA INTO OUTFILE "/tmp/AttBetala.txt"
FIELDS TERMINATED BY ','
FROM `LEVRESK`
where EXPIREDATUM < " 2003-09-09" and BETALD = "N"
order by LEVNR,EXPIREDATUM,FAKTURANR;
