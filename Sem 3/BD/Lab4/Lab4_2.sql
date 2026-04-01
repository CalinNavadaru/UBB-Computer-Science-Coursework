CREATE PROCEDURE Teste AS
BEGIN
	DECLARE @ds DATETIME-- start time test
	DECLARE @di DATETIME-- intermediate time test
	DECLARE @de DATETIME-- end time test
	DECLARE @i INT
	SET @i = 1
	WHILE @i <= 3
	BEGIN
		SET @ds = GETDATE()
		EXEC ('DI' + @i)
		SET @di=GETDATE()
		DECLARE @viewName NVARCHAR(50) = 'View_' + CAST(@i AS VARCHAR(2))
		EXEC ('SELECT * FROM ' + @viewName)
		SET @de=GETDATE()
		-- if you want to see the difference of these 2 times, you can use DATEDIFF
		-- Print DATEDIFF(milisecond, @de, @ds)
		DECLARE @desc VARCHAR(50)
		DECLARE @testid INT
		SELECT @testid = MAX(TestRunID) FROM TestRuns 
		IF (@testid is null)
		BEGIN
			SET @testid = 1
		END
		SET @desc = 'Testul' + CONVERT(VARCHAR(50), @testid)
		
		Insert into TestRuns VALUES (@desc, @ds, @de)
		DECLARE @id INT
		SELECT @id = MAX(TestRunID) FROM TestRuns
		Insert into TestRunTables VALUES (@id, @i, @ds, @di)
		Insert into TestRunViews VALUES(@id, @i, @di, @de)
		SET @i = @i + 1
	END
END