CREATE PROCEDURE redo4
AS
BEGIN
	ALTER TABLE ExempluModificari
	DROP COLUMN Dob
	print 'Sters dob'
END