CREATE PROCEDURE DI1 AS
BEGIN
	DELETE TOP(50) FROM Angajati

	DBCC CHECKIDENT ('[Angajati]', RESEED, 0)

	DECLARE @n INT
	SET @n = 1

	WHILE @n <= 50 
	BEGIN
		DECLARE @nume VARCHAR(50)
		DECLARE @prenume VARCHAR(50)
		DECLARE @CNP CHAR(13)
		SET @CNP = '1234567890123'
		SET @nume = 'Angajati' + CONVERT (VARCHAR(2), @n)
		SET @prenume = 'Angajati' + CONVERT (VARCHAR(2), @n)
		SELECT @depid = MIN(d.Depid) FROM Departamente d
		INSERT INTO Angajati VALUES (@nume, @prenume, @CNP, @depid, 1, 1, 1)
		SET @n = @n + 1
	END
END

GO

CREATE PROCEDURE DI3 AS
BEGIN
	DELETE TOP(50) FROM Deductii

	DBCC CHECKIDENT ('[Deductii]', RESEED, 0)

	DECLARE @n INT
	SET @n = 1

	WHILE @n <= 50 
	BEGIN
		DECLARE @nume VARCHAR(50)
		DECLARE @procent VARCHAR(50)
		SET @nume = 'Deductii' + CONVERT (VARCHAR(2), @n)
		SET @procent = @n
		INSERT INTO Deductii VALUES (@nume, @procent)
		SET @n = @n + 1
	END
END

GO

CREATE PROCEDURE DI2 AS
BEGIN
	DELETE TOP(50) FROM DeductiiAngajati

	DECLARE @n INT
	SET @n = 1
	DECLARE @n1 INT
	SET @n1 = 1

	WHILE @n <= 50 
	BEGIN
		INSERT INTO DeductiiAngajati VALUES (@n, @n1)
		SET @n = @n + 1
	END
END