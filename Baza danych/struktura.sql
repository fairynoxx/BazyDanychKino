DROP DATABASE kino;
CREATE DATABASE IF NOT EXISTS kino;
USE kino;
CREATE TABLE IF NOT EXISTS klient ( 
id_klienta INT PRIMARY KEY AUTO_INCREMENT, 
imie VARCHAR(64), 
nazwisko VARCHAR(64), 
nr_telefonu INT,
e_mail VARCHAR(64)
);

CREATE TABLE IF NOT EXISTS rezerwacja (
id_rezerwacji INT PRIMARY KEY AUTO_INCREMENT, 
id_klienta INT,
CONSTRAINT FK_idklientarezerwacja FOREIGN KEY (id_klienta) REFERENCES klient(id_klienta) 
);

CREATE TABLE IF NOT EXISTS stanowisko (
id_stanowiska INT AUTO_INCREMENT PRIMARY KEY, 
nazwa VARCHAR(64), 
wynagrodzenie INT
);

CREATE TABLE IF NOT EXISTS status_zatrudnienia(
stan INT PRIMARY KEY,
opis VARCHAR(64)
);

CREATE TABLE IF NOT EXISTS Pracownik (
id_pracownika INT PRIMARY KEY AUTO_INCREMENT,
PESEL LONG, 
stanowisko INT, 
imie VARCHAR(64), nazwisko VARCHAR(64), 
adres VARCHAR(256),
e_mail VARCHAR(64), 
nr_telefonu INT, 
data_zatrudnienia DATE,
status_zatrudnienia INT,
CONSTRAINT FK_Statuspracownik FOREIGN KEY (status_zatrudnienia) REFERENCES status_zatrudnienia(stan),
CONSTRAINT FK_Stanowiskopracownik FOREIGN KEY (stanowisko) REFERENCES Stanowisko(id_stanowiska)
);

CREATE TABLE IF NOT EXISTS sala (
id_sali INT PRIMARY KEY AUTO_INCREMENT,
ilosc_miejsc INT,
liczba_rzedow INT,
liczba_miejsc_w_rzedzie INT
);

CREATE TABLE IF NOT EXISTS fotel (
id_sali INT,
rzad INT,
nr_w_rzedzie INT,
PRIMARY KEY (id_sali, rzad, nr_w_rzedzie),
CONSTRAINT FK_salafotel FOREIGN KEY (id_sali) REFERENCES sala(id_sali)
);

CREATE TABLE IF NOT EXISTS ograniczenia (
id_ograniczenia INT PRIMARY KEY,
wiek INT
);

CREATE TABLE IF NOT EXISTS film (
id_filmu INT PRIMARY KEY,
tytul VARCHAR(128),
wytwornia VARCHAR(128),
rezyser VARCHAR(128),
data_premiery DATE,
czas_trwania TIME,
ograniczenie_wiekowe INT,
CONSTRAINT FK_Ograniczeniafilm FOREIGN KEY (ograniczenie_wiekowe) REFERENCES ograniczenia(id_ograniczenia)
);

CREATE TABLE IF NOT EXISTS dzwiek (
id_dzwieku INT PRIMARY KEY,
wersja VARCHAR(64)
);


CREATE TABLE IF NOT EXISTS seans (
id_seansu INT PRIMARY KEY AUTO_INCREMENT,
czas_seansu TIMESTAMP,
id_sali INT REFERENCES sala(id_sali),
id_filmu INT REFERENCES film(id_filmu),
dzwiek INT,
CONSTRAINT FK_Salaseans FOREIGN KEY (id_sali) REFERENCES sala(id_sali),
CONSTRAINT FK_Filmsesans FOREIGN KEY (id_filmu) REFERENCES film(id_filmu)
);

CREATE TABLE IF NOT EXISTS status_miejsca (
stan INT PRIMARY KEY,
opis VARCHAR(64)
);

CREATE TABLE IF NOT EXISTS rodzaj_biletu (
rodzaj INT PRIMARY KEY,
opis VARCHAR(64),
cena INT
);

CREATE TABLE IF NOT EXISTS bilet (
id_miejsca INT PRIMARY KEY AUTO_INCREMENT,
rzad INT REFERENCES fotel(rzad),
nr_w_rzedzie INT REFERENCES fotel(nr_w_rzedzie),
id_seansu INT,
id_rezerwacji INT REFERENCES rezerwacja(id_rezerwacji),
status_miejsca INT,
rodzaj_biletu INT,
CONSTRAINT FK_miejsce FOREIGN KEY(status_miejsca)REFERENCES status_miejsca(stan),
CONSTRAINT FK_seansbilet FOREIGN KEY (id_seansu) REFERENCES seans(id_seansu)
);

CREATE TABLE IF NOT EXISTS dostepnosc_produktu (
stan INT PRIMARY KEY,
opis VARCHAR(64)
);
CREATE TABLE IF NOT EXISTS produkt (
id_produktu INT PRIMARY KEY,
cena INT,
nazwa VARCHAR (128),
dostepnosc INT REFERENCES dostepnosc_PRODUKTU(stan)
);

CREATE TABLE IF NOT EXISTS raport_sprzedazy (
id_raportu INT PRIMARY KEY,
dzien DATE
);

CREATE TABLE IF NOT EXISTS raporty (
produkt INT REFERENCES produkt(id_produktu),
raport INT REFERENCES raport_sprzedazy(id_raportu),
ilosc INT,
PRIMARY KEY (produkt, raport)
);

