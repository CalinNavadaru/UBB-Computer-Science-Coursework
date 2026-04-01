CREATE VIEW View_1 AS
	SELECT Nume, Prenume FROM Angajati
GO

CREATE VIEW View_3 AS
	SELECT da.aid FROM DeductiiAngajati da
	INNER JOIN Angajati a ON a.Aid = da.Aid
GO

CREATE VIEW View_2 AS
	SELECT SUM(d.procent) AS ProcentMinim FROM Deductii d
	INNER JOIN DeductiiAngajati da ON d.DeductiiId = da.DeductiiId
	GROUP BY d.procent
	HAVING SUM(d.procent) > 0
GO