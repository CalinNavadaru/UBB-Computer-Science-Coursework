BEGIN TRANSACTION
UPDATE Bonusuri SET procent = 69 WHERE BonusuriId = 2
WAITFOR DELAY '00:00:07'
ROLLBACK TRANSACTION
INSERT INTO IstoricTranzactii VALUES ('Update Bonusuri cu rollback', GETDATE(), 'fara probleme la crearea problemei')