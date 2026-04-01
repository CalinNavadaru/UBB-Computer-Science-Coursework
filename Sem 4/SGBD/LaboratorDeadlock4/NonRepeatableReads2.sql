INSERT INTO Bonusuri VALUES ('asdasd1', 90)

Begin Tran
WAITFOR DELAY '00:00:07'
DELETE FROM Bonusuri WHERE Nume = 'asdasd1'
COMMIT TRAN
INSERT INTO IstoricTranzactii VALUES ('Delete Bonusuri cu succes', GETDATE(), 'fara probleme la crearea problemei')