CREATE FUNCTION validateAngajat (
@nume VARCHAR(100),
@prenume VARCHAR(100),
@cnp VARCHAR(13),
@depid INT,
@poid INT,
@plid INT,
@adrid INT) RETURNS INT AS
BEGIN

IF LEN(@nume) = 0
BEGIN
	RETURN -1
END

IF LEN(@prenume) = 0
BEGIN
	RETURN -2
END

IF LEN(@cnp) != 13 
BEGIN
	RETURN -3
END

IF NOT EXISTS( SELECT * FROM Departamente WHERE Depid = @depid)
BEGIN 
	RETURN -4
END

IF NOT EXISTS( SELECT * FROM Posturi WHERE Poid = @poid)
BEGIN
	RETURN -5
END

IF NOT EXISTS(SELECT * FROM PlatiDeBaza WHERE Plid = @plid)
BEGIN
	RETURN -6
END

IF NOT EXISTS(SELECT * FROM Adrese WHERE AdresaID = @adrid)
BEGIN
	RETURN -6
END
RETURN 0
END

GO

CREATE OR ALTER FUNCTION validateBonus(
@nume VARCHAR(50),
@procent INT) RETURNS INT AS
BEGIN

IF LEN(@nume) = 0
BEGIN
	RETURN -1
END

IF @procent <= 0
BEGIN
	RETURN -2
END
RETURN 0
END

GO

CREATE OR ALTER FUNCTION validateDeductie(
@nume VARCHAR(50),
@procent INT) RETURNS INT AS
BEGIN

IF LEN(@nume) = 0
BEGIN
	RETURN -1
END

IF @procent <= 0
BEGIN
	RETURN -2
END
RETURN 0
END

GO

CREATE TABLE Errors
(
	id INT PRIMARY KEY IDENTITY,
	description VARCHAR(50)
)

INSERT INTO Errors VALUES ('Nume invalid!'), ('Prenume invalid!'),
('Cnp invalid!'), ('Departament inexistent'), ('Post inexistent'),
('Salariu de baza inexistent'), ('adresa inexistenta!')
INSERT INTO Errors VALUES ('nume bonus invalid!'),
('procent invalid')
GO

CREATE TABLE LogTable
(
	id INT PRIMARY KEY IDENTITY,
	typeOperation VARCHAR(50),
	tableOperation VARCHAR(50),
	executionDate DATETIME
)

GO

CREATE OR ALTER PROCEDURE pb1
@nume VARCHAR(100),
@prenume VARCHAR(100),
@cnp VARCHAR(13),
@depid INT,
@poid INT,
@plid INT,
@adrid INT,
@nume_bonus VARCHAR(50),
@procent INT AS 
BEGIN
	BEGIN TRAN
	BEGIN TRY
		DECLARE @resultAngajat INT
		DECLARE @msg VARCHAR(100)
		DECLARE @absoluteValue INT
		DECLARE @resultBonus INT
		SET @resultAngajat = dbo.validateAngajat(@nume, @prenume, @cnp, @depid, @poid, @plid, @adrid)
		IF @resultAngajat <> 0
		BEGIN
			
			SET @absoluteValue = ABS(@resultAngajat)
			SELECT @msg = description FROM Errors WHERE id = @absoluteValue
			RAISERROR(@msg, 14, 1)
		END
		
		SET @resultBonus = dbo.validateBonus(@nume_bonus, @procent)
		IF @resultBonus <> 0
		BEGIN
			SET @absoluteValue = ABS(@resultAngajat)
			SELECT @msg = description FROM Errors WHERE id = @absoluteValue + 2
			RAISERROR(@msg, 14, 1) 
		END

		INSERT INTO Bonusuri VALUES (@nume_bonus, @procent)
		INSERT INTO LogTable VALUES ('Insert', 'Bonusuri', GETDATE())
		INSERT INTO Angajati VALUES (@nume, @prenume, @cnp, @depid, @poid, @plid, @adrid)
		INSERT INTO LogTable VALUES ('Insert', 'Angajati', GETDATE())
		DECLARE @idA INT
		DECLARE @idB INT
		SELECT @idA = MAX(Aid) FROM Angajati
		SELECT @idB = MAX(BonusuriId)FROM Bonusuri

		INSERT INTO BonusuriAngajati VALUES (@idA, @idB)
		INSERT INTO LogTable VALUES ('Insert', 'Bonusuri_Angajati', GETDATE())
		COMMIT TRAN
		PRINT('TRANZACTIE REUSITA(Comisa)! $$$$$$$$')
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
		PRINT('TRANZACTIE NEREUSITA(RollBacked)! :(')
		PRINT(ERROR_MESSAGE())
	END CATCH
END

GO

CREATE OR ALTER PROCEDURE pb2
@nume VARCHAR(100),
@prenume VARCHAR(100),
@cnp VARCHAR(13),
@depid INT,
@poid INT,
@plid INT,
@adrid INT,
@nume_bonus VARCHAR(50),
@procent INT AS 
BEGIN
	DECLARE @tranAngajat INT
	DECLARE @tranBonus INT
	SET @tranAngajat = 1
	SET @tranBonus = 1
	BEGIN TRAN
	BEGIN TRY
		DECLARE @resultAngajat INT
		DECLARE @msg VARCHAR(100)
		DECLARE @absoluteValue INT
		SET @resultAngajat = dbo.validateAngajat(@nume, @prenume, @cnp, @depid, @poid, @plid, @adrid)
		IF @resultAngajat <> 0
		BEGIN
			
			SET @absoluteValue = ABS(@resultAngajat)
			SELECT @msg = description FROM Errors WHERE id = @absoluteValue
			RAISERROR(@msg, 14, 1)
		END
		INSERT INTO Angajati VALUES (@nume, @prenume, @cnp, @depid, @poid, @plid, @adrid)
		INSERT INTO LogTable VALUES ('Insert', 'Angajati', GETDATE())
		COMMIT TRAN
		PRINT('TRANZACTIE Angajat REUSITA(Comisa)! $$$$$$$$')
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
		SET @tranAngajat = 0
		PRINT('TRANZACTIE Angajat NEREUSITA(RollBacked)! :(')
		PRINT(ERROR_MESSAGE())
	END CATCH

	BEGIN TRAN
	BEGIN TRY
		DECLARE @resultBonus INT
		SET @resultBonus = dbo.validateBonus(@nume_bonus, @procent)
		IF @resultBonus <> 0
		BEGIN
			SET @absoluteValue = ABS(@resultAngajat)
			SELECT @msg = description FROM Errors WHERE id = @absoluteValue + 8
			RAISERROR(@msg, 14, 1) 
		END
		INSERT INTO Bonusuri VALUES (@nume_bonus, @procent)
		INSERT INTO LogTable VALUES ('Insert', 'Bonusuri', GETDATE())
		COMMIT TRAN
		PRINT('TRANZACTIE Bonusuri REUSITA(Comisa)! $$$$$$$$')
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
		SET @tranBonus = 0
		PRINT('TRANZACTIE Bonusuri NEREUSITA(RollBacked)! :(')
		PRINT(ERROR_MESSAGE())
	END CATCH

	IF @tranAngajat = 1 AND @tranBonus = 1
	BEGIN
		BEGIN TRAN
		BEGIN TRY
			DECLARE @idA INT
			DECLARE @idB INT
			SELECT @idA = MAX(Aid) FROM Angajati
			SELECT @idB = MAX(BonusuriId)FROM Bonusuri

			INSERT INTO BonusuriAngajati VALUES (@idA, @idB)
			INSERT INTO LogTable VALUES ('Insert', 'BonusuriAngajati', GETDATE())
			COMMIT TRAN
			PRINT('TRANZACTIE BonusuriAngajati REUSITA(Comisa)! $$$$$$$$')
		END TRY
		BEGIN CATCH
		ROLLBACK TRAN
		PRINT('TRANZACTIE BonusuriAngajati NEREUSITA(RollBacked)! :(')
		PRINT(ERROR_MESSAGE())
	END CATCH
	END
END 

EXEC pb1 'Calin123456789', 'Navadaru', '1234567890123', 1, 1, 1, 1, 'Smecherie', 100
SELECT * FROM LogTable
SELECT * FROM Angajati
SELECT * FROM Bonusuri
SELECT * FROM BonusuriAngajati
DELETE FROM LogTable
DELETE FROM Bonusuri WHERE BonusuriId >= 4
DELETE FROM BonusuriAngajati WHERE Aid >= 5
DELETE FROM Angajati WHERE Aid >= 6

EXEC pb1 'Calin123', 'Navadaru', '1234566', 1, 1, 1, 1, 'trgfgr', 13

EXEC pb2 'Calin1234ty543564', 'Navadaru', '1234567890123', 1, 1, 1, 1, '', 213