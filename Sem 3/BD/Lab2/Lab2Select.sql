USE ManagementPlati
GO

-- Angajatii care sunt la HR
SELECT DISTINCT a.Nume AS NUME, a.Prenume AS PRENUME, p.Nume AS DEPARTAMENT FROM Angajati a
INNER JOIN Departamente p ON p.Depid = a.Depid
WHERE p.Nume = 'HR'

-- Lista Angajati cu tot cu departamente si posturi
SELECT a.Nume AS NUME, a.Prenume AS PRENUME, p.Nume AS DEPARTAMENT, d.Nume AS POST FROM Angajati a
INNER JOIN Departamente p ON p.Depid = a.Depid
INNER JOIN Posturi d ON d.Poid = a.Poid

-- Lista Angajat care sunt la Finante 
SELECT a.Nume AS NUME, a.Prenume AS PRENUME, p.Nume AS DEPARTAMENT, d.Nume AS POST FROM Angajati a
INNER JOIN Departamente p ON p.Depid = a.Depid
INNER JOIN Posturi d ON d.Poid = a.Poid
WHERE p.Nume = 'Finante'
--m to m pentru bonusuri
SELECT a.Nume AS NUME, bb.Nume AS Bonus FROM Angajati a
INNER JOIN BonusuriAngajati ba ON a.Aid = ba.Aid
INNER JOIN Bonusuri bb ON ba.BonusuriId = bb.BonusuriId
--m to n pentru deductii
SELECT a.Nume AS NUME, d.Nume AS Deductii FROM Angajati a
INNER JOIN DeductiiAngajati da ON da.Aid = a.Aid
INNER JOIN Deductii d ON da.DeductiiId = d.DeductiiId
-- cine are deductie din salariu cauzata de o distrugere a bunurilor personale
SELECT a.Nume AS NUME, d.Nume AS Deductii, d.procent AS PROCENT , MIN(d.procent) as PROCENT_MINIM FROM Angajati a
INNER JOIN DeductiiAngajati da ON da.Aid = a.Aid
INNER JOIN Deductii d ON da.DeductiiId = d.DeductiiId
GROUP BY a.Nume, d.nume, d.procent
HAVING MIN(d.procent) > 2
--Angajati care au bonus card de calatorie
SELECT a.Nume AS NUME, d.Nume AS Bonusuri, MAX(d.procent) as PROCENT_MAXIM FROM Angajati a
INNER JOIN BonusuriAngajati da ON da.Aid = a.Aid
INNER JOIN Bonusuri d ON da.BonusuriId = d.BonusuriId
GROUP BY a.Nume, d.nume, d.procent
HAVING MAX(d.procent) < 50

--Angajati al caror bonus reprezinta 10% din valoarea salariului lor
SELECT bb.procent PROCENT, bb.Nume AS Bonus FROM Angajati a
INNER JOIN BonusuriAngajati ba ON a.Aid = ba.Aid
INNER JOIN Bonusuri bb ON ba.BonusuriId = bb.BonusuriId
WHERE bb.procent > 10

--grupare angajati dupa bonusuri care au peste 5%
SELECT a.Nume AS NUME, d.Nume AS Bonusuri, d.procent AS PROCENT FROM Angajati a
INNER JOIN BonusuriAngajati da ON da.Aid = a.Aid
INNER JOIN Bonusuri d ON da.BonusuriId = d.BonusuriId
WHERE d.procent > 5
GROUP BY d.Nume, d.procent, a.Nume

--grupare angajati care au deductii din cauza distrugerilor
SELECT DISTINCT a.nume AS Nume, p.PlataDeBaza as SALARIU_BAZA, b.Nume as BONUS, d.Nume as DEDUCTIE FROM Angajati a
INNER JOIN PlatiDeBaza p ON a.Plid = p.Plid
INNER JOIN  BonusuriAngajati ba ON a.Aid = ba.Aid
INNER JOIN Bonusuri b ON b.BonusuriId = ba.BonusuriId
INNER JOIN DeductiiAngajati da ON da.Aid = a.Aid
INNER JOIN Deductii d ON da.DeductiiId = d.DeductiiId
WHERE d.Nume = 'Distrugeri'

--Gresite
SELECT a.Nume AS NUME, d.Nume AS Deductii FROM Angajati a
INNER JOIN DeductiiAngajati da ON da.Aid = a.Aid
INNER JOIN Deductii d ON da.DeductiiId = d.DeductiiId
GROUP BY a.Nume, d.nume
HAVING d.nume = 'Distrugeri'
--Angajati care au bonus card de calatorie
SELECT a.Nume AS NUME, d.Nume AS Bonusuri FROM Angajati a
INNER JOIN BonusuriAngajati da ON da.Aid = a.Aid
INNER JOIN Bonusuri d ON da.BonusuriId = d.BonusuriId
GROUP BY a.Nume, d.nume
HAVING d.nume = 'Card de calatorie'