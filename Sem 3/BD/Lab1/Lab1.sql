create database ManagementPlati
go
use ManagementPlati
go

create table Deductii
(
	DeductiiId INT PRIMARY KEY IDENTITY,
	Nume VARCHAR(50),
	procent INT
)

create table Bonusuri
(
	BonusuriId INT PRIMARY KEY IDENTITY,
	Nume VARCHAR(50),
	procent INT
)

create table PlatiDeBaza
(
	Plid INT PRIMARY KEY IDENTITY,
	PlataDeBaza INT
)

create table Departamente
(
	Depid INT PRIMARY KEY IDENTITY,
	Nume VARCHAR(50)
)

create table Posturi
(
	Poid INT PRIMARY KEY IDENTITY,
	Nume VARCHAR(50)
)

create table Adrese
(
	AdresaID INT PRIMARY KEY IDENTITY,
	Nume VARCHAR(50),
	Numar INT,
	Etaj INT,
	Scara VARCHAR(3),
	CONSTRAINT ETAJ CHECK( Etaj <= 25 ),
	CONSTRAINT NUMAR CHECK( Numar > 0 )
)

create table Angajati
(	Aid INT PRIMARY KEY IDENTITY,
    Nume VARCHAR(50),
    Prenume VARCHAR(50),
    CNP CHAR(13),
    Depid INT FOREIGN KEY REFERENCES Departamente(Depid),
    Poid INT FOREIGN KEY REFERENCES Posturi(Poid),
    Plid INT FOREIGN KEY REFERENCES PlatiDeBaza(Plid),
    Adrid INT FOREIGN KEY REFERENCES Adrese(AdresaID)
)

create table BonusuriAngajati
(
	Aid INT FOREIGN KEY REFERENCES Angajati(AID),
	BonusuriId INT FOREIGN KEY REFERENCES Bonusuri(BonusuriId),
	CONSTRAINT pk_BonusuriAngajati PRIMARY KEY (Aid, BonusuriId)
)

create table DeductiiAngajati
(
	Aid INT FOREIGN KEY REFERENCES Angajati(AID),
	DeductiiId INT FOREIGN KEY REFERENCES Deductii(DeductiiId),
	CONSTRAINT pk_DeductiiAngajati PRIMARY KEY (Aid, DeductiiId)
)

create table DateDeVenire
(
	Did INT FOREIGN KEY REFERENCES Angajati(Aid),
	DataVenire DATE,
	LungimeContract INT,
	CONSTRAINT pk_DateDeVenire PRIMARY KEY(Did)
)

create table Versiune
(
	versiune INT DEFAULT 0
)

create table ExempluModificari
(
	id INT PRIMARY KEY IDENTITY,
	info VARCHAR(50),
	cv2 VARCHAR(1000)
)

