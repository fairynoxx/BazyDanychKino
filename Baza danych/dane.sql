USE kino;

INSERT INTO stanowisko(nazwa, wynagrodzenie) VALUE
("kasjer", 20 ),
("pracownik baru", 17 ),
("kierownik sprzedazy", 25),
("technik audiowizualny", 20),
("manager kina", 30),
("pracownik obslugi kina", 17),
("pracownik ochrony", 20),
("personel sprzatajacy", 17);


INSERT INTO status_miejsca(stan, opis) VALUE
(1, "wolne"),
(2, "zarezwowane"),
(3, "wykupione"),
(4, "oczekujace"),
(5, "do zakupu");

INSERT INTO rodzaj_biletu(rodzaj, opis, cena) VALUE
(1, "normalny", 20),
(2, "ulgowy", 12);

INSERT INTO status_zatrudnienia(stan, opis) VALUE
(1, "pracownik"),
(2, "byly pracownik");

INSERT INTO dostepnosc_produktu(stan, opis) VALUE
(0, "niedostepny"),
(1, "dostepny");

INSERT INTO sala(id_sali, ilosc_miejsc, liczba_rzedow, liczba_miejsc_w_rzedzie) VALUE 
(1, 340, 17, 20),
(2, 256, 16, 16),
(3, 238, 14, 17),
(4, 208, 16, 13),
(5, 323, 17, 19),
(6, 224, 16, 14),
(7, 224, 16, 14),
(8, 224, 16, 14),
(9, 224, 16, 14),
(10, 224, 16, 14);

INSERT INTO produkt(id_produktu, cena, nazwa, dostepnosc) VALUE
(1, 10, "popcorn maly", 1),
(2, 15, "popcorn duzy", 1),
(3, 10, "napoj duzy", 1),
(4, 6, "napoj maly", 1),
(5, 16, "kanapka drwala", 0),
(6, 15, "nachosy male", 1),
(7, 20, "nachosy duze", 1);

INSERT INTO dzwiek (id_dzwieku, wersja) VALUE
(1, "napisy"),
(2, "lektor"),
(3, "dubbing"),
(4, "oryginalny");


INSERT INTO `Pracownik` VALUES 
('1','30622392968','1','Benedict','Hilll','2637 Creola Station Apt. 177\nLake Simeon, KY 02115-7757','marie.mclaughlin@hotmail.com','804763253','2010-03-15','1'),
('2','68484445694','5','Felicity','McDermott','924 Cole Lodge Suite 158\nLake Beau, ME 03893-2170','broderick.legros@yahoo.com','801702636','2012-12-05','2'),
('3','80051668652','4','Unique','Stanton','8285 Bethany Fort Apt. 261\nLake Madieton, LA 52413-1294','kamille04@yahoo.com','281222485','2011-07-23','2'),
('4','70319715459','4','Jaren','Kirlin','571 Gislason Lake\nPadbergshire, IN 56073','adam.pouros@yahoo.com','933894708','2014-03-23','2'),
('5','52408035453','4','Claude','O\'Hara','1710 Bayer Extension Suite 612\nLeannonmouth, AZ 79488','eino83@gmail.com','686786846','2014-03-30','2'),
('6','40912549954','3','Greg','Corkery','088 Augustus Rest Suite 137\nPort Abdielview, MO 35537','wuckert.darron@gmail.com','830566954','2010-02-05','2'),
('7','91459899856','7','Dayna','Cummings','52745 Margret Place\nConroyshire, NJ 95236','wisoky.janick@hotmail.com','713974275','2012-01-05','2'),
('8','41035678658','2','Vladimir','Kris','396 Koch Crest\nPort Marion, OH 83319-2021','leopold.bernier@gmail.com','488436497','2013-05-04','1'),
('9','67967057246','7','Ryann','Veum','0800 Arvel Highway\nLilachester, IN 91968-7842','blaze10@gmail.com','494502069','2014-04-04','2'),
('10','10174567588','2','Sonya','Braun','55010 Rath Groves\nWest Tanyaberg, CT 15794','danyka86@hotmail.com','956950323','2012-02-05','1'),
('11','12425114356','1','Fabiola','Bradtke','5345 Viviane Fort Apt. 112\nTurnerbury, NJ 60654-1928','jo\'keefe@yahoo.com','261235018','2012-09-25','2'),
('12','45761844897','1','Ashlynn','Morar','286 Hirthe Prairie\nLake Norbertofurt, DE 83819','sreichert@gmail.com','329450463','2010-02-25','2'),
('13','31454788997','7','Antonetta','Streich','027 Rowe Lodge\nPort Tyshawnmouth, VA 05346','kcronin@yahoo.com','582565917','2010-04-13','1'),
('14','88564526287','6','Rhea','Sanford','972 Reichel Ports Suite 788\nWest Kielburgh, CO 07813','selmer47@gmail.com','762654670','2016-06-06','1'),
('15','52436276273','3','Francesco','Hirthe','388 Winfield Point Suite 606\nHallieburgh, OK 56094','jameson41@gmail.com','658927376','2017-02-02','1'),
('16','33724966878','1','Enoch','Miller','2468 Quigley Prairie Suite 292\nKaymouth, NJ 38282-9299','vivien.pfeffer@gmail.com','241248430','2012-02-05','1'),
('17','18223172940','5','Antonina','Ratke','792 Sid Glens Apt. 832\nMarcuschester, NV 07037-5974','lreynolds@gmail.com','336084004','2012-01-05','1'),
('18','89937452900','7','Allan','Corkery','25117 Bartoletti Gateway\nRosalindaborough, IL 78093','amuller@hotmail.com','244140801','2011-02-02','1'),
('19','22672505624','8','Jacquelyn','Kuhic','153 Oberbrunner Turnpike Suite 240\nNorth Pattown, KY 73774-1815','carol.kuhlman@yahoo.com','647035700','2012-02-25','2'),
('20','57340727975','2','Domenick','Waelchi','0074 Jada Shoal Apt. 890\nNew Judyberg, RI 82320','wlesch@hotmail.com','724016852','2010-07-23','1'); 
INSERT INTO ograniczenia VALUES
(1, 3),
(2, 12),
(3, 16),
(4, 18);


INSERT INTO `film` VALUES 
('1','Zielona mila','Warner Bros. Pictures','Frank Darabont','1999-04-10','02:54:47','3'),
('2','Skazani na Shawshank','Castle Rock Entertainment','Frank Darabont','1994-05-05','02:21:32','3'),
('3','Forrest Gump','Paramount Pictures','Robert Zemeckis','1994-10-01','02:14:06','2'),
('4','Leon Zawodowiec','Gamount','Luc Besson','1994-08-18','02:18:48','2'),
('5','Requiem dla snu','Artisan Entertainment','Darren Aronofsky','2000-09-06','02:10:51','4'),
('6','Matrix','Warner Bros. Pictures','Lilly Wachowski','1999-04-13','03:17:19','2'),
('7','Milczenie owiec','Orion Pictures','Jonathan Demme','1991-09-28','02:09:56','4'),
('8','Gladiator','Dreamworks','Ridley Scott','2000-07-02','02:23:05','2'),
('9','Avatar','20th Century Fox','James Cameron','2009-09-21','02:59:24','1'),
('10','Shrek','Dreamworks','Andrew Adamson','2001-06-30','01:52:39','1'),
('11','Szeregowiec Ryan','Dreamworks','Steven Spielberg','1998-04-16','02:35:06','2'),
('12','Podziemny krag','20th Century Fox','David Fincher','1999-04-16','02:48:58','3'),
('13','Pulp fiction','Miramax Films','Quentin Tarantino','1994-02-03','03:03:17','3');


INSERT INTO `seans` VALUES 
('1','2020-08-13 15:00:00','4','8','3'),
('2','2020-08-21 19:00:00','3','1','4'),
('3','2020-04-09 16:00:00','3','8','3'),
('4','2020-07-11 10:00:00','8','8','4'),
('5','2020-01-15 21:00:00','4','4','4'),
('6','2020-07-30 13:00:00','7','6','4'),
('7','2020-04-04 17:00:00','10','3','3'),
('8','2020-08-30 15:00:00','2','7','1'),
('9','2020-04-11 21:00:00','7','6','2'),
('10','2020-09-12 19:00:00','5','3','4'),
('11','2020-06-14 20:00:00','10','9','1'),
('12','2020-10-24 16:00:00','10','7','3'),
('13','2020-01-04 14:00:00','1','11','4'),
('14','2020-10-11 20:00:00','10','10','3'),
('15','2020-12-04 22:00:00','10','13','1'),
('16','2020-04-17 19:00:00','10','6','3'),
('17','2020-11-30 16:00:00','7','1','3'),
('18','2020-09-23 12:00:00','7','7','2'),
('19','2020-12-01 19:00:00','7','11','3'),
('20','2020-12-19 13:00:00','8','5','4'),
('21','2020-10-07 22:00:00','5','10','4'),
('22','2020-12-04 18:00:00','8','13','2'),
('23','2020-12-25 20:00:00','1','7','1'),
('24','2020-04-17 11:00:00','1','8','1'),
('25','2020-02-10 15:00:00','1','8','1'),
('26','2020-03-10 17:00:00','3','1','2'),
('27','2020-12-17 20:00:00','9','11','4'),
('28','2020-02-07 12:00:00','4','4','2'),
('29','2020-11-05 21:00:00','6','11','4'),
('30','2020-12-21 17:00:00','6','2','1'),
('31','2020-12-21 19:00:00','7','6','2'),
('32','2020-08-13 16:00:00','10','4','1'),
('33','2020-10-24 16:00:00','10','5','1'),
('34','2020-06-20 10:00:00','9','2','1'),
('35','2020-09-13 19:00:00','9','3','1'),
('36','2020-05-10 13:00:00','4','7','4'),
('37','2020-03-26 18:00:00','4','12','1'),
('38','2020-09-24 12:00:00','4','7','4'),
('39','2020-07-19 21:00:00','4','8','1'),
('40','2020-12-24 15:00:00','10','12','1'),
('41','2020-10-24 08:00:00','10','7','1'),
('42','2020-12-05 20:00:00','9','3','1'),
('43','2020-09-24 19:00:00','2','8','1'),
('44','2020-03-22 20:00:00','9','10','1'),
('45','2020-08-23 16:00:00','9','13','1'),
('46','2020-11-28 15:00:00','6','8','4'),
('47','2020-05-09 13:00:00','8','8','1'),
('48','2020-01-23 11:00:00','3','13','1'),
('49','2020-12-28 20:00:00','1','2','2'),
('50','2020-09-26 12:00:00','2','7','2'); 




INSERT INTO `klient` VALUES 
('1','Mia','Grant','683770964','itorp@yahoo.com'),
('2','Urban','Halvorson','761734118','monahan.ruben@gmail.com'),
('3','Milton','Konopelski','757357571','aida16@hotmail.com'),
('4','Alfonzo','Beahan','719334741','pkshlerin@yahoo.com'),
('5','Micaela','Cruickshank','795246146','alfonzo02@yahoo.com'),
('6','Violette','Marquardt','679444433','rick.howe@yahoo.com'),
('7','Liliane','Tromp','644901624','mbode@yahoo.com'),
('8','Norene','Hammes','717922551','vfeeney@hotmail.com'),
('9','Emile','Kunde','760228029','pebert@gmail.com'),
('10','Retta','Konopelski','756478184','hroob@hotmail.com'),
('11','Nico','Olson','588954387','kemmer.cruz@gmail.com'),
('12','Thaddeus','Schmidt','563664894','janelle.lemke@hotmail.com'),
('13','Ericka','Grant','736885133','qmcclure@hotmail.com'),
('14','Isom','Kunde','759984974','joan.moore@gmail.com'),
('15','Hassie','Anderson','543314218','skyla73@gmail.com'),
('16','Einar','Bins','705241259','summer97@gmail.com'),
('17','Mable','Leuschke','598311981','jackie04@hotmail.com'),
('18','Newton','Runolfsdottir','626826007','powlowski.isom@hotmail.com'),
('19','Alf','Jacobs','757157511','emmalee.corwin@hotmail.com'),
('20','Jakob','Gerlach','529569782','franco40@gmail.com'),
('21','Darryl','Rowe','552458383','whintz@hotmail.com'),
('22','Agnes','Funk','574544203','smitham.johan@hotmail.com'),
('23','Martin','Legros','794617342','rblick@yahoo.com'),
('24','Mireille','Koepp','606800561','lenny05@yahoo.com'),
('25','Vickie','Hilll','577251399','pollich.myah@hotmail.com'),
('26','Dylan','Ratke','582046755','yzulauf@hotmail.com'),
('27','Nasir','Funk','609727285','vschmitt@gmail.com'),
('28','Walton','Corwin','759660799','gfisher@hotmail.com'),
('29','Abigayle','O\'Reilly','566003966','trace32@gmail.com'),
('30','Darien','Walter','769152124','ekuphal@gmail.com'),
('31','Casandra','Rogahn','724477808','lonie87@hotmail.com'),
('32','Kasandra','Kunde','578167174','juliet14@hotmail.com'),
('33','Valentin','O\'Kon','729952959','tianna.leannon@gmail.com'),
('34','Melody','Barton','590762373','ddubuque@gmail.com'),
('35','Kirstin','Hartmann','728924523','scot.marquardt@gmail.com'),
('36','Anissa','Gerlach','660524617','bahringer.leda@gmail.com'),
('37','Wayne','Grant','623130055','julian.kuhn@hotmail.com'),
('38','Ocie','Koss','795240931','bo\'reilly@yahoo.com'),
('39','Manley','Cummerata','585627530','koelpin.breanne@yahoo.com'),
('40','Owen','Abernathy','587992758','katarina.schaden@gmail.com'),
('41','Scottie','Cummings','612575655','fahey.braxton@yahoo.com'),
('42','Narciso','Kohler','624361891','roberta20@yahoo.com'),
('43','Danielle','Wolff','623324348','gtromp@yahoo.com'),
('44','Blake','Wyman','663405649','gusikowski.pearlie@gmail.com'),
('45','Rosina','Quitzon','764276430','cummerata.jadyn@yahoo.com'),
('46','Jose','Connelly','726034611','vonrueden.lavonne@yahoo.com'),
('47','Mafalda','Grant','528372610','eldora.breitenberg@gmail.com'),
('48','Meagan','Bednar','616542235','anastasia.lowe@yahoo.com'),
('49','Carolina','Langosh','763713255','vida.terry@gmail.com'),
('50','Bridie','Lemke','747336894','anna.king@hotmail.com'),
('51','Jevon','Zieme','740346341','fgerhold@yahoo.com'),
('52','Arno','Walsh','756612966','donavon.stark@hotmail.com'),
('53','Aylin','Ratke','665149320','courtney.king@gmail.com'),
('54','Tina','Marks','549646632','wilma86@gmail.com'),
('55','Lucius','Waelchi','793983763','addison14@hotmail.com'),
('56','Adrianna','O\'Keefe','627139625','schinner.lionel@yahoo.com'),
('57','Edmond','Johns','735284040','trisha71@hotmail.com'),
('58','Lexi','Conroy','710806522','dgutmann@hotmail.com'),
('59','Dixie','Hammes','564092951','rosenbaum.garth@hotmail.com'),
('60','Art','Denesik','709010555','erwin12@yahoo.com'),
('61','Thea','Kunze','602555104','fbalistreri@hotmail.com'),
('62','Clay','Cassin','585200303','zprice@yahoo.com'),
('63','Marie','Flatley','565114134','buckridge.trever@gmail.com'),
('64','Albina','Nikolaus','720468611','qlindgren@yahoo.com'),
('65','Chadd','Treutel','513928867','william.beier@gmail.com'),
('66','Maegan','Ratke','750851780','qmoore@gmail.com'),
('67','Zackery','Brown','612571121','payton.braun@gmail.com'),
('68','Demond','Jones','626369773','volkman.shawn@hotmail.com'),
('69','Dejuan','Grady','778471195','monroe.huel@gmail.com'),
('70','Mateo','Abshire','692131649','janie.davis@hotmail.com'),
('71','Nya','Hane','761360152','mertz.alexander@yahoo.com'),
('72','Amaya','Leffler','745478420','amani24@yahoo.com'),
('73','Alexandro','Stroman','593764742','stewart.christiansen@hotmail.com'),
('74','Sedrick','Fahey','570460650','aherman@gmail.com'),
('75','Oceane','Will','588116066','jacobson.ed@hotmail.com'),
('76','Zella','Goldner','511770772','xbrekke@hotmail.com'),
('77','Guadalupe','Lind','777714624','ddach@yahoo.com'),
('78','Sonia','Bode','668733088','stan.crooks@gmail.com'),
('79','Jeremy','McClure','600992621','bernier.emelie@hotmail.com'),
('80','Tanya','Zulauf','684714709','randy.purdy@hotmail.com'),
('81','Helmer','Nienow','599118806','berenice.jenkins@gmail.com'),
('82','Annabell','Feil','663231208','wstroman@gmail.com'),
('83','Augusta','Hahn','554968102','mazie32@gmail.com'),
('84','Daphne','Bergstrom','736395211','mireille.koelpin@hotmail.com'),
('85','Glennie','Littel','748648680','tjenkins@hotmail.com'),
('86','Connie','Swaniawski','542141453','price.paolo@gmail.com'),
('87','Virgil','Howell','727018360','tmitchell@yahoo.com'),
('88','Ebba','Schneider','508113573','reynolds.junius@hotmail.com'),
('89','Salvatore','Lowe','722688708','igoodwin@gmail.com'),
('90','Melba','Hauck','634457159','ryley.robel@yahoo.com'),
('91','Cathy','Murray','546641732','bpfeffer@gmail.com'),
('92','Concepcion','Marks','631214072','cmarks@hotmail.com'),
('93','Brown','Parker','769440511','toney.raynor@yahoo.com'),
('94','Blaze','Kerluke','704085064','herminio70@yahoo.com'),
('95','Minnie','Ruecker','696526255','stehr.ward@yahoo.com'),
('96','Donny','Lehner','782009961','pkris@yahoo.com'),
('97','Sage','Blanda','791375178','gkertzmann@yahoo.com'),
('98','Maddison','Harvey','602093693','francisca78@yahoo.com'),
('99','Ardith','Metz','609261985','mauricio00@yahoo.com'),
('100','Maynard','Stanton','601838811','moen.bart@yahoo.com'); 

INSERT INTO fotel VALUES
(10,10,10),
(10,10,11),
(10,10,12),
(10,10,13),
(10,10,14),
(10,11,10),
(10,11,11),
(10,11,12),
(10,11,13),
(10,11,14);

-- INSERT INTO rezerwacja(id_klienta) VALUES
-- (4),
-- (7),
-- (4);

-- INSERT INTO `bilet` ( rzad, nr_w_rzedzie, id_seansu, id_rezerwacji, status_miejsca, rodzaj_biletu)VALUES 
-- (10, 11, 15, 1, 2, 2),
-- (10, 12, 15, 1, 2, 1),
-- (10, 13, 15, 1, 2, 1),
-- (10, 14, 15, 1, 2, 1),
-- (10, 14, 15, 1, 2, 1),
-- (11, 10, 15, 2, 2, 1),
-- (11, 11, 15, 2, 2, 1),
-- (11, 12, 15, 2, 2, 1),
-- (11, 13, 15, 2, 2, 2),
-- (11, 14, 15, 2, 2, 1),
-- (11, 10, 14, 3, 2, 1),
-- (11, 11, 14, 3, 2, 1),
-- (11, 12, 14, 3, 2, 2),
-- (11, 13, 14, 3, 2, 1),
-- (11, 14, 14, 3, 2, 1);
INSERT INTO `bilet` ( rzad, nr_w_rzedzie, id_seansu, status_miejsca)VALUES 
(10, 11, 11, 1),
(10, 12, 11, 1),
(10, 13, 11, 1),
(10, 14, 11, 1),
(11, 1, 11, 1),
(11, 2, 11, 1),
(11, 3, 11, 1),
(11, 4, 11, 1);




