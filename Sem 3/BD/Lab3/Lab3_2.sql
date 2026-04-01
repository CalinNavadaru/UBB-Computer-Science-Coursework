CREATE PROCEDURE redo1
AS
BEGIN
	ALTER TABLE ExempluModificari
	ALTER COLUMN info VARCHAR(50)
	print 'Info este varchar 50'
END

EXEC modif_invers