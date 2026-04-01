CREATE FUNCTION TestProcent(@procent INT)
RETURNS INT
AS
BEGIN
	IF @procent <= 0
	BEGIN
		RETURN 1
	END
	RETURN 0
END
GO

CREATE FUNCTION TestMedieProcent()
RETURNS INT
AS
BEGIN
	DECLARE @nr INT
	SELECT @nr = MIN(procent) FROM Bonusuri
	RETURN @nr
END
GO

ALTER TABLE Bonusuri
ADD CONSTRAINT chkMedieProcent CHECK (dbo.TestMedieProcent() >= 5)
GO

CREATE OR ALTER PROCEDURE BonusuriCRUD
@tabel VARCHAR(50),
@nume VARCHAR(50),
@procent INT,
@flag INT OUTPUT
AS
BEGIN
	if dbo.TestProcent(@procent) != 0
	BEGIN
		PRINT 'Procentul este invalid!'
		SET @flag = 1
	END
	ELSE
	BEGIN
		BEGIN TRY
			INSERT INTO Bonusuri(Nume, procent) VALUES  (@nume, @procent)
		END TRY
		BEGIN CATCH
			PRINT 'Constrangere!'
			SET @flag = 1
			RETURN
		END CATCH

		SELECT * FROM Bonusuri

		UPDATE Bonusuri 
		SET Nume = 'Mircea'
		WHERE procent < 10

		SELECT * FROM Bonusuri

		DELETE FROM Bonusuri WHERE procent = 5

		PRINT 'Operatii CRUD pentru ' + @tabel
		SET @flag = 0
	END
END

INSERT INTO Bonusuri(Nume, procent) VALUES ('sanatate', -5)
DELETE Bonusuri 

SELECT * FROM Bonusuri

DECLARE @flag1 INT
EXEC BonusuriCRUD 'Bonusuri', 'asdasdas', -1, @flag1 OUTPUT
PRINT @flag1