BEGIN TRAN
WAITFOR DELAY '00:00:07'
INSERT INTO Bonusuri VALUES ('CALIN', 123)
COMMIT TRAN
INSERT INTO IstoricTranzactii VALUES ('Insert Bonusuri cu succes', GETDATE(), 'fara probleme la crearea problemei')