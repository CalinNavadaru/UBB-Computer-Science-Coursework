USE ManagementPlati
GO


INSERT INTO Versiune VALUES
(0)

GO


CREATE PROCEDURE main 
@vers int
AS
BEGIN
	DECLARE @cv INT
	SELECT @cv = versiune FROM Versiune

	IF @vers > 5 OR @vers < 0
	BEGIN
		print 'Nu se pot face modificari'
		return
	END
	ELSE
		BEGIN
			IF @cv = @vers
			BEGIN
				print 'Nimika'
				RETURN
			END
			IF @cv < @vers
			BEGIN
				WHILE @cv < @vers
				BEGIN
					SET @cv = @cv + 1
					EXECUTE('do' + @cv)
				END
		END
		IF @cv > @vers
		BEGIN
			WHILE @cv > @vers
			BEGIN
				EXECUTE('redo' + @cv)
				SET @cv = @cv - 1
			END
		END
		
		UPDATE Versiune
		SET versiune = @vers
	END
	
END

EXEC main -1
EXEC main 6
EXEC main 2
EXEC main 5
EXEC main 3
EXEC main 0
EXEC main 1


SELECT * FROM Versiune