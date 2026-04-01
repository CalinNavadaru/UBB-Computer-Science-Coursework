CREATE PROCEDURE do2
AS
BEGIN
	ALTER TABLE ExempluModificari
	ADD CONSTRAINT df_cv2 DEFAULT 'ana are mere'
	FOR cv2
	print 'constraint df_cv2 creat'

END

EXEC constrangere_direct