CREATE PROCEDURE redo5
AS
BEGIN
	ALTER TABLE ExempluModificari
	DROP CONSTRAINT c
	print 'Stergere constrangere'
END