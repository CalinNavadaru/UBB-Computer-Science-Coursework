CREATE PROCEDURE do5
AS
BEGIN
	ALTER TABLE ExempluModificari
	ADD CONSTRAINT c FOREIGN KEY(id) REFERENCES Angajati(Aid)
	print 'Adaugare constrangere c'
END
