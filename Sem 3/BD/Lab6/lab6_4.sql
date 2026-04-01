select * from sys.indexes
GO

IF EXISTS (SELECT name FROM sys.indexes WHERE name = N'N_idx_Nume')
DROP INDEX N_idx_Nume ON Angajati;
GO

CREATE NONCLUSTERED INDEX N_idx_Nume ON Angajati (Nume);
GO

IF EXISTS (SELECT name FROM sys.indexes WHERE name = N'N_idx_BonusuriNume')
DROP INDEX N_idx_BonusuriNume ON Bonusuri;
GO

CREATE NONCLUSTERED INDEX N_idx_BonusuriNume ON Bonusuri (Nume);
GO

IF EXISTS (SELECT name FROM sys.indexes WHERE name = N'N_idx_BonusuriProcent')
DROP INDEX N_idx_BonusuriProcent ON Bonusuri;
GO

CREATE NONCLUSTERED INDEX N_idx_BonusuriProcent ON Bonusuri (Procent);
GO

IF EXISTS (SELECT name FROM sys.indexes WHERE name = N'N_idx_BonusuriA')
DROP INDEX N_idx_BonusuriA ON BonusuriAngajati;
GO

CREATE NONCLUSTERED INDEX N_idx_BonusuriA ON BonusuriAngajati (Aid);
GO

IF EXISTS (SELECT name FROM sys.indexes WHERE name = N'N_idx_BonusuriA2')
DROP INDEX N_idx_BonusuriA2 ON BonusuriAngajati;
GO

CREATE NONCLUSTERED INDEX N_idx_BonusuriA2 ON BonusuriAngajati (BonusuriId);
GO


CREATE OR ALTER VIEW VIEW1
AS
	SELECT a.Nume AS NUME, b.procent AS PROCENT FROM Angajati a
	INNER JOIN BonusuriAngajati da ON da.Aid = a.Aid
	INNER JOIN Bonusuri b ON b.BonusuriId = da.BonusuriId
	ORDER BY a.Nume, b.procent
	offset 0 ROWS
GO
CREATE OR ALTER VIEW VIEW2
AS
	SELECT bb.Nume FROM Bonusuri bb
	WHERE bb.Nume LIKE 'B%'
GO

SELECT * FROM VIEW1
SELECT * FROM Bonusuri
INSERT INTO Bonusuri VALUES ('B', 123),  ('B', 21312312), ('B', 123123)

