CREATE FUNCTION ValidareCNP(@cnp VARCHAR(50))
RETURNS INT
AS
BEGIN
	if LEN(@cnp) != 13
	BEGIN
		RETURN 1
	END
	RETURN 0
END
GO

CREATE FUNCTION ValidareID_uri(@depid INT,
@poid INT,
@plid INT,
@adrid INT)
RETURNS INT
AS BEGIN
	IF NOT EXISTS (SELECT * FROM Departamente d WHERE @depid = d.Depid)
		RETURN 1
	IF NOT EXISTS (SELECT * FROM Posturi p WHERE @poid = p.Poid)
		RETURN 2
	IF NOT EXISTS (SELECT * FROM PlatiDeBaza p WHERE p.Plid = @plid)
		RETURN 3
	IF NOT EXISTS (SELECT * FROM Adrese a WHERE a.AdresaID = @adrid)
		RETURN 4
	RETURN 0
END
GO

CREATE FUNCTION TestAngajati()
RETURNS INT
AS 
BEGIN
	DECLARE @nr INT
	SELECT @nr = COUNT(*) FROM Angajati
	RETURN @nr
END
GO

ALTER TABLE Angajati
ADD CONSTRAINT chkRowCount check (dbo.TestAngajati() >= 1)
GO

CREATE PROCEDURE AngajatiCRUD
@nume VARCHAR(50),
@prenume VARCHAR(50),
@cnp VARCHAR(50),
@depid INT,
@poid INT,
@plid INT,
@adrid INT,
@flag INT OUTPUT
AS
BEGIN
	IF dbo.ValidareCNP(@cnp) != 0
	BEGIN
		SET @flag = 1
		PRINT 'CNP INVALID'
		RETURN 
	END
	IF dbo.ValidareID_uri(@depid, @poid, @plid, @adrid) != 0
	BEGIN
		SET @flag = 2
		PRINT 'ID-URI INVALIDE'
		RETURN
	END

	INSERT INTO Angajati VALUES (@nume, @prenume, @cnp, @depid, @poid, @plid, @adrid)

	SELECT * FROM Angajati

	UPDATE Angajati SET Nume = 'Mircea' WHERE Prenume LIKE 'M%'

	DELETE FROM Angajati WHERE Plid = 2
END

DECLARE @nr INT
EXEC dbo.AngajatiCRUD 'm', 'M', 5030324080048, 1, 1, 2, 1, @nr OUTPUT
PRINT @nr