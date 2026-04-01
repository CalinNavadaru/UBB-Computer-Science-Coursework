CREATE PROCEDURE redo2
AS
BEGIN
	ALTER TABLE ExempluModificari
	DROP CONSTRAINT df_cv2
	print 'constraint df_cv2 sters'
END

EXEC constrangere_invers