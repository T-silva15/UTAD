USE master

--DROP DATABASE Editor_2024
--CREATE DATABASE Editor_2024
USE Editor_2024

CREATE TABLE Livro(
	ISBN	varchar(30)	not null	PRIMARY KEY,
	Data_p  Date		not null,
	Edicao  integer		not null,
	Titulo  varchar(20) not null,
	Pvp		decimal		not null,

	CHECK(ISBN NOT LIKE '%[^1234567890-]'),
	CHECK(Titulo NOT LIKE '%[^a-zA-Z !?&#.:-^+*/\1234567890]%'),
	CHECK(Pvp > 0),
	CHECK(Edicao > 0)
)


CREATE TABLE Autor(
	ID_Autor	integer		not null	PRIMARY KEY,
	Nome		varchar(20)	not null,
	Apelido		varchar(20)	not null,
	Pseudonimo	varchar(40),
	
	CHECK(ID_Autor >=1),
	CHECK(Nome NOT LIKE '%[^a-zA-Z ]%'),
	CHECK(Apelido NOT LIKE '%[^a-zA-Z ]%'),
	CHECK(Pseudonimo NOT LIKE '%[^a-zA-Z ]%')
)

CREATE TABLE Livreiros(
	ID_Livreiro integer		not null	PRIMARY KEY,
	Endereco	varchar(50) not null,
	Nome		varchar(40)	not null,

	CHECK(ID_Livreiro >= 1),
	CHECK(Nome NOT LIKE '%[^a-zA-Z ]%'),
	CHECK(Endereco NOT LIKE '%[^a-zA-Z 1234567890./ºª,\"*]%'),
)

CREATE TABLE Escreve(
	ISBN		varchar(30) not null,
	ID_Autor	integer		not null,
	Royalties	float		not null,

	FOREIGN KEY (ISBN) REFERENCES Livro(ISBN),
	FOREIGN KEY (ID_Autor) REFERENCES Autor(ID_Autor),
	PRIMARY KEY (ISBN, ID_Autor),

	CHECK(Royalties > 0)
)

CREATE TABLE Compra(
	ISBN		varchar(30)	not null,
	ID_Livreiro integer		not null,
	Data_v		Date		not null	DEFAULT getdate(),
	Quantidade  integer		not null,

	FOREIGN KEY (ISBN) REFERENCES Livro(ISBN),
	FOREIGN KEY (ID_Livreiro) REFERENCES Livreiros(ID_Livreiro),
	PRIMARY KEY (ISBN,ID_Livreiro,Data_v),
	
	CHECK(Quantidade >= 1)
)

INSERT INTO Livro (ISBN, Data_p, Edicao, Titulo, Pvp)
VALUES 
    ('9781-2345-6789-1234', '2023-01-15', 1, 'Sample Book 1', 29.99),
    ('9782-3456-7890-1123', '2022-05-20', 2, 'Sample Book 2', 39.99),
    ('9783-4567-8901-2234', '2023-10-10', 1, 'Sample Book 3', 19.99),
    ('9784-5678-9012-3345', '2024-02-28', 2, 'Sample Book 4', 49.99),
    ('9785-6789-0123-4456', '2024-03-15', 1, 'Sample Book 5', 24.99),
    ('9786-7890-1234-5567', '2023-08-20', 3, 'Sample Book 6', 34.99),
    ('9787-8901-2345-6678', '2022-11-05', 1, 'Sample Book 7', 29.99),
    ('9788-9012-3456-7789', '2023-04-10', 2, 'Sample Book 8', 19.99),
    ('9789-0123-4567-8901', '2024-01-22', 1, 'Sample Book 9', 39.99),
    ('9780-1234-5678-9012', '2024-05-30', 3, 'Sample Book 10', 29.99);

-- Insert data into Autor table
INSERT INTO Autor (ID_Autor, Nome, Apelido, Pseudonimo)
VALUES 
    (1, 'John', 'Doe', NULL),
    (2, 'Jane', 'Smith', NULL),
    (3, 'David', 'Brown', 'David Brown'),
    (4, 'Emily', 'Johnson', NULL),
    (5, 'Michael', 'Williams', 'Mark Williams'),
    (6, 'Jessica', 'Jones', NULL),
    (7, 'Christopher', 'Davis', 'Chris Davis'),
    (8, 'Sarah', 'Martinez', NULL),
    (9, 'Daniel', 'Anderson', 'Devin Anderson'),
    (10, 'Jennifer', 'Taylor', NULL);

-- Insert data into Livreiros table
INSERT INTO Livreiros (ID_Livreiro, Endereco, Nome)
VALUES 
    (1, '123 Main St, Cityville', 'City Books'),
    (2, '456 Elm St, Townsville', 'Town Books'),
    (3, '789 Oak St, Villagetown', 'Village Books'),
    (4, '101 Pine St, Forest City', 'Forest Books'),
    (5, '222 Maple St, Hillside', 'Hillside Books');

-- FIX ISBN
INSERT INTO Escreve (ISBN, ID_Autor, Royalties)
VALUES 
    ('978-1234-5678-90-0', 1, 30.1),
    ('978-2345-6789-01-1', 2, 50.15),
    ('978-3456-7890-12-2', 3, 24.12),
    ('978-4567-8901-23-3', 4, 2.08),
    ('978-5678-9012-34-4', 5, 1.1),
    ('978-6789-0123-45-5', 6, 28.15),
    ('978-7890-1234-56-6', 7, 42.12),
    ('978-8901-2345-67-7', 8, 8.08),
    ('978-9012-3456-78-8', 9, 20.1),
    ('978-0123-4567-89-9', 10, 39.15);

-- Insert data into Compra table
INSERT INTO Compra (ISBN, ID_Livreiro, Data_v, Quantidade)
VALUES 
    ('978-1234-5678-90-0', 1, '2024-04-18', 50),
    ('978-2345-6789-01-1', 2, '2024-04-17', 30),
    ('978-3456-7890-12-2', 3, '2024-04-16', 20),
    ('978-4567-8901-23-3', 4, '2024-04-15', 25),
    ('978-5678-9012-34-4', 5, '2024-04-14', 40),
    ('978-6789-0123-45-5', 1, '2024-04-13', 35),
    ('978-7890-1234-56-6', 2, '2024-04-12', 45),
    ('978-8901-2345-67-7', 3, '2024-04-11', 55),
    ('978-9012-3456-78-8', 4, '2024-04-10', 60),
    ('978-0123-4567-89-9', 5, '2024-04-09', 70);

-- Stored Procedures

