CREATE PROCEDURE do1
AS
BEGIN

	ALTER TABLE ExempluModificari
	ALTER COLUMN info VARCHAR(100) NOT NULL
	print 'Info este varchar(100)'
END


EXEC modif_direct

