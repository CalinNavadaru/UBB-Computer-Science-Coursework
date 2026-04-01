USE ManagementPlati
GO

INSERT INTO Departamente(Nume) VALUES
('HR'), ('QA'), ('Finante'), ('Relatii externe'), ('Imagine si PR')

INSERT INTO Deductii(Nume, procent) VALUES
('Intarzieri', 1), ('Asigurare medicala', 2), ('Asigurare masina',1),
('Distrugeri', 3)

INSERT INTO Bonusuri(Nume, procent) VALUES
('Bilete de masa', 10), ('Card de calatorie', 10), 
('Analize medicale', 50)

INSERT INTO Posturi(Nume) VALUES
('Manager'), ('Presedinte'), ('Vicepresedinte'), ('Secretar'), ('Angajat')

INSERT INTO PlatiDeBaza(PlataDeBaza) VALUES
(3000), (4000), (5000), (6000), (7000), (400000000)

INSERT INTO Adrese(Nume, Numar, Etaj, Scara) VALUES
('Str Octavian Goga', 7, 2, 'A'), ('Str Muresului', 45, 3, 'B'),
('Str Bloyai Janos', 2, 2, 'CC'), ('Str Unirii', 20, 1, 'D'),
('Str Siretului', 213, 2, 'CCC')

INSERT INTO Angajati(Nume, Prenume, CNP, Depid, Poid, Plid, Adrid) VALUES
('GIGEL', 'Al Doilea', 5010101123456, 1, 2, 6, 1),
('Dan', 'Daniel', 5101010123456, 3, 1, 1, 3),
('Marcel', 'Ciolan', 5050505123456, 4, 5, 1, 5),
('Tiberiu', 'Cezar', 5020202123456, 3, 4, 2, 2),
('Lica', 'Samadau', 5040404123456, 2, 3, 4, 4)

INSERT INTO DateDeVenire(Did, DataVenire, LungimeContract) VALUES
(1, '2022-01-01', 50),
(5, '2023-01-10', 20),
(3, '2021-08-09', 10),
(2, '2019-03-02', 5),
(4, '2015-01-23', 2)

INSERT INTO DeductiiAngajati(Aid, DeductiiId) VALUES
(1, 1), (1,2), (5,4), (3, 3), (2, 4), (5, 1)

INSERT INTO BonusuriAngajati(Aid, BonusuriId) VALUES
(1, 1), (1,2), (5,3), (3, 3), (2, 2), (5, 2)

SELECT * FROM Deductii
SELECT * FROM DateDeVenire
SELECT * FROM Departamente
SELECT * FROM Posturi
SELECT * FROM Adrese
SELECT * FROM Bonusuri
SELECT * FROM PlatiDeBaza
SELECT * FROM Angajati
SELECT * FROM DeductiiAngajati
SELECT * FROM BonusuriAngajati

DELETE FROM Angajati

DBCC CHECKIDENT('Angajati', RESEED, 0);