CREATE FUNCTION TestBonusuriAngajatiValid()
RETURNS INT
AS
BEGIN
	IF EXISTS (SELECT * FROM BonusuriAngajati b WHERE b.Aid IS NULL AND b.BonusuriId IS NULL)
		RETURN 1
	RETURN 0
END
GO

ALTER TABLE BonusuriAngajati
ADD CONSTRAINT chkData CHECK (dbo.TestBonusuriAngajatiValid() = 0)
GO

CREATE FUNCTION validareID(@idA INT, @idB INT)
RETURNS INT
AS
BEGIN
	IF NOT EXISTS(SELECT * FROM Angajati a WHERE a.Aid = @idA)
		RETURN 1
	IF NOT EXISTS(SELECT * FROM Bonusuri b WHERE b.BonusuriId = @idB)
		RETURN 2
	RETURN 0
END
GO

CREATE PROCEDURE BonusuriAngajatiCRUD
@id1 INT,
@id2 INT,
@flag INT OUTPUT
AS
BEGIN
	IF dbo.validareID(@id1, @id2) != 0
	BEGIN 
		PRINT 'ID-URI INVALIDE'
		SET @flag = 1
		RETURN
	END
	ELSE
	BEGIN
		INSERT INTO BonusuriAngajati(Aid, BonusuriId) VALUES (@id1, @id2)

		SELECT * FROM BonusuriAngajati

		Print 'UPDATE :)'

		DELETE FROM BonusuriAngajati

		PRINT 'CRUD Operations for BonusuriAngajati'
	END
END

SELECT * FROM Angajati
SELECT * FROM Bonusuri
SELECT * FROM BonusuriAngajati
DECLARE @nr INT
EXEC BonusuriAngajatiCRUD 1, 7, @nr OUTPUT
PRINT @nr