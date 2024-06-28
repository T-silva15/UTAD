USE master

--DROP DATABASE Biblioteca_2024
--CREATE DATABASE Biblioteca_2024
USE Biblioteca_2024


--Tables
DROP TABLE Aluno 
CREATE TABLE Aluno(
	numero_aluno	integer		not null	primary key,
	nome			varchar(30)	not null,
	endereco		varchar(30)	not null,
	garantia		money		not null,
	CHECK(numero_aluno>=1),
	CHECK(nome NOT LIKE '%[^a-zA-Z ]%'),
	CHECK(endereco NOT LIKE '%[^a-zA-Z ]%'),
	CHECK(garantia>=0)
)

DROP TABLE Livro
CREATE TABLE Livro(
	numero_livro	integer		not null	primary key,
	titulo			varchar(30) not null,
	autor			varchar(30) not null,
	editor			varchar(20) not null,
	data_compra		smalldatetime not null  default	getdate(),
	estado			bit			not null	default 0,
	CHECK(numero_livro>=1),
	CHECK(titulo NOT LIKE '%[^a-zA-Z !?&#.:-^+*/\1234567890]%'),
	CHECK(autor NOT LIKE '%[^a-zA-Z !?&#.:-^+*/\]%'),
	CHECK(editor NOT LIKE '%[^a-zA-Z 1234567890]%'),
	CHECK(estado = 1 OR estado = 0)
)

DROP TABLE Emprestimo
CREATE TABLE Emprestimo(
	numero_aluno	integer		not null,
	numero_livro	integer		not null,
	data_requisicao datetime	not null	default getdate(),
	data_entrega    datetime,
	CHECK(DATEDIFF(second,data_entrega, data_requisicao) > 0),


	FOREIGN KEY (numero_aluno) REFERENCES Aluno(numero_aluno),
	FOREIGN KEY (numero_livro) REFERENCES Livro(numero_livro),
	PRIMARY KEY (numero_aluno, numero_livro, data_requisicao)
)

--Mudar tabela livro
--UPDATE Livro SET estado = 1 WHERE numero_livro = 1001

UPDATE Emprestimo SET data_entrega = GETDATE() WHERE numero_aluno = 102307

SELECT * FROM Aluno
SELECT * FROM Livro
SELECT * FROM Emprestimo

--Popular a base de dados
--ALUNO



INSERT INTO Aluno VALUES 
(10229, 'Joao Pedro', 'Rua de Baixo', 32),
(10230,'Joao Silva','Rua de Cima', 10),
(102301,'Amaro Costa','Rua A', 20),
(102302,'Daniel Pereira','Rua B', 5),
(102303,'Tiago Ferreira','Rua C', 4),
(102304,'Mariana Silva','Rua D', 23),
(102305,'Vania Freitas','Rua E', 54),
(102306,'Leonor Vaz','Rua F', 13),
(102307,'Matilde Machado','Rua G', 165),
(102308,'Rui Freitas','Rua H', 2),
(102309,'Alexandre Sousa','Rua I', 1),
(102310,'Ricardo Martins','Rua J', 5),
(102311,'Diogo Monteiro','Rua K', 12),
(102312,'Carlos Alberto','Rua L', 25),
(102313,'Rodrigo Fernandes','Rua M', 30),
(102314,'Francisca Ferreira','Rua N', 33),
(102315,'Joao Maria','Rua O', 16),
(102316,'Andre Martins','Rua P', 78),
(102317,'Tomas Silva','Rua Q', 100),
(102318,'Joao Ribeiro','Rua R', 104),
(102319,'Vitor Costa','Rua S', 3),
(102320,'David Martins','Rua T', 2)

--LIVRO
INSERT INTO Livro VALUES
(1001,'Bases de Dados', 'Manuel Antonio', 'editor1', '2013-6-3', 0),
(1002,'Bases de Dados v2', 'Manuel Antonio', 'editor3', '2013-6-5', 1),
(1003,'Bases de Dados v3', 'Manuel Antonio', 'editor5', '2021-12-12', 1),
(1004,'Analise Matematica', 'Paulo Faira', 'editor2', '2000-5-31', 1),
(1005,'Analise Matematica v2', 'Paulo Faria', 'editor8', '2022-4-26', 0),
(1006,'Nausea', 'Jean Paul Sartre', 'editor10', '2015-2-1', 0),
(1007,'No Longer Human ', 'Osamu Dazai', 'editor6', '2024-3-6', 1),
(1008,'1984', 'George Orwell', 'editor6', '2006-1-31', 0),
(1009,'Dracula', 'Bram Stoker', 'editor1', '2005-12-1', 0),
(1010,'The Great Gatsby', 'Scott Fitzgerald', 'editor16', '2023-5-30', 0),
(1011,'Frankenstein', 'Mary SHelley', 'editor12', '2007-9-8', 1),
(1012,'The Catcher in the Rye', 'J.D. Salinger', 'editor6', '2023-2-3', 0),
(1013,'Wuthering Heights', 'Emily Bronte', 'editor13', '2009-1-5', 0),
(1014,'The Picture of Dorian Gray', 'Oscar Wilde', 'editor11', '2011-3-7', 0),
(1015,'Milk and Honey', 'Rupi Kaur', 'editor4', '2023-8-3', 1),
(1016,'Os Maias', 'Eca de Queiros', 'editor39', '2013-2-19', 0),
(1017,'The Bell Jar', 'Sylvia Plath', 'editor5', '2004-6-18', 0),
(1018,'Metamorphosis', 'Franz Kafka', 'editor13', '2015-5-14', 1),
(1019,'Anna Karenina', 'Fyodor Dostoevsky', 'editor17', '2023-2-12', 0),
(1020,'Romeu e Julieta', 'Shakespeare', 'editor15', '2016-1-27', 0),
(1021,'Pride and Prejudice', 'Jane Austen', 'editor9', '2020-8-11', 1),
(1022,'Crime and Punishment', 'Fyodor Dostoevsky', 'editor8', '2022-2-24', 1),
(1023,'The Stranger', 'Albert Camus', 'editor14', '2019-9-25', 1),
(1024,'The Brothers Karamazov', 'Fyodor Dostoevsky', 'editor3', '2018-10-15', 0),
(1025,'War and Peace', 'Leo Tolstoy', 'editor2', '2023-11-16', 0)
--DELETE FROM Livro WHERE numero_livro = 1001

--EMPRESTIMO
INSERT INTO Emprestimo(numero_aluno,numero_livro) VALUES
(10229,1015),
(10229,1011),
(10229,1018),
(10229,1006),
(10229,1004),
(10229,1001),
(10230,1001),
(102301,1016),
(102301,1017),
(102302,1024),
(102304,1021),
(102306,1019),
(102308,1025),
(102309,1022),
(102312,1012),
(102314,1011),
(102316,1010),
(102314,1008),
(102313,1002),
(102312,1008),
(102320,1006),
(102318,1005),
(102316,1004),
(102319,1007),
(102303,1006),
(102304,1005),
(102305,1004),
(102306,1003),
(102307,1002),
(102308,1001)

--DELETE FROM Emprestimo WHERE numero_aluno = 10230

-- QUERY SECTION

SELECT * FROM Livro

SELECT nome FROM Aluno WHERE nome LIKE 'Joao%'

SELECT nome FROM Aluno WHERE garantia >= 10

SELECT titulo FROM Livro

SELECT titulo FROM Livro WHERE autor LIKE 'Manuel Antonio'

SELECT estado,titulo FROM Livro WHERE titulo LIKE '%Bases de Dados%'

SELECT SUM(garantia) FROM Aluno AS total_Garantia

SELECT titulo FROM Livro

--SELECT Livro.numero_livro,titulo FROM Livro JOIN Emprestimo ON Livro.numero_livro = Emprestimo.numero_livro JOIN Aluno ON Emprestimo.numero_aluno = Aluno.numero_aluno WHERE nome = 'Joao Pedro'
SELECT L.numero_livro, titulo FROM Aluno A,Livro L,Emprestimo E WHERE A.nome = 'Joao Pedro' AND A.numero_aluno = E.numero_aluno AND E.numero_livro = L.numero_livro

SELECT COUNT(DISTINCT(numero_livro)) FROM Emprestimo AS emprestado_22_05_2024 WHERE data_requisicao >= '2024-05-22' AND data_requisicao < '2024-05-22' 

SELECT COUNT(DISTINCT(numero_livro)) FROM Emprestimo WHERE DATEDIFF(day, data_requisicao, GETDATE()) > 5 AND data_entrega IS NULL

SELECT COUNT(numero_livro) FROM Emprestimo WHERE numero_aluno = 102304

SELECT COUNT(DISTINCT(numero_livro)) FROM Emprestimo AS livros_emprestados

SELECT titulo FROM Livro WHERE numero_livro = (SELECT TOP 1 numero_livro FROM Emprestimo ORDER BY data_requisicao)
	
-- STORED PROCEDURES

-- DROP PROCEDURE setEstado
CREATE PROCEDURE setEstado @numLivro INTEGER, @estado BIT
AS
	UPDATE Livro SET estado = @estado WHERE numero_livro = @numLivro

-- EXEMPLO DE UTILIZAÇÂO
-- EXECUTE setEstado 1010, 1



CREATE PROCEDURE getEstado @numLivro INTEGER 
AS
	RETURN (SELECT estado FROM Livro WHERE numero_livro = @numLivro)
	
-- EXEMPLO DE UTILIZAÇÂO
--DECLARE @estado INTEGER
--EXECUTE @estado = getEstado 1009;
--PRINT @estado


CREATE PROCEDURE verReq @numAluno INTEGER
AS 
	DECLARE @num_emprestimos INTEGER;
	DECLARE @garantia MONEY;

	-- numEmprestimos
	SET @num_emprestimos = (SELECT COUNT(*) FROM Emprestimo E WHERE E.numero_aluno = @numAluno AND E.data_entrega IS NULL);

	-- garantia (dividida por 5)
	SET @garantia = (SELECT CAST(garantia / 5 AS INTEGER) FROM Aluno A WHERE A.numero_aluno = @numAluno );

	-- verificação
	IF (@garantia > @num_emprestimos)
		RETURN 1;
    ELSE
		PRINT('Não pode requisitar!')
		RETURN -1;

DECLARE @req INTEGER
EXECUTE @req = verReq 102309;
PRINT @req;

CREATE PROCEDURE inserirReq @numLivro INTEGER, @numAluno INTEGER
AS
	
	DECLARE @livroEmStock BIT;
	EXECUTE @livroEmStock = getEstado @numLivro;

	DECLARE @podeReq INTEGER;
	EXECUTE @podeReq = verReq @numAluno;

	-- se livro não está em stock
	IF (@livroEmStock = 1)
		PRINT('Livro não está em Stock!')
		RETURN -1
	-- se aluno pode requisitar
    IF (@podeReq = 1)
    BEGIN
		-- altera estado do livro
        EXECUTE setEstado @numLivro, 1;
		-- insere empréstimo na tabela
        INSERT INTO Emprestimo(numero_aluno, numero_livro, data_entrega, data_requisicao) VALUES (@numAluno, @numLivro, NULL, GETDATE());
        -- devolve 1(sucesso)
		RETURN 1;
    END
    ELSE
    BEGIN
		-- devolve -1(erro)
		PRINT('Aluno não pode requisitar!')
        RETURN -1;
    END


DECLARE @ins INTEGER
EXECUTE @ins = inserirReq 1023, 102307;
PRINT @ins;

DROP PROCEDURE entregarReq
CREATE PROCEDURE entregarReq @numLivro INTEGER, @numAluno INTEGER
AS
	-- verifica se o empréstimo existe 
	IF EXISTS(SELECT numero_livro,numero_aluno,data_requisicao FROM Emprestimo WHERE numero_livro = @numAluno AND numero_aluno = numero_aluno and data_entrega IS NULL)
	BEGIN
		EXECUTE setEstado @numLivro, 0
		UPDATE Emprestimo SET data_entrega = GETDATE() WHERE @numAluno = numero_aluno AND @numLivro = numero_livro AND data_entrega IS NULL;
		RETURN 1;
	END
	ELSE
		RETURN -1;


SELECT * FROM Emprestimo WHERE data_entrega IS NULL and numero_livro = 1023;
DECLARE @ent INTEGER
EXECUTE @ent = entregarReq 1023,102307, '2024-05-16 10:39:31.300';
PRINT @ent


-- (f) CREATE PROCEDURE getEstadoVerdadeiro
DROP PROCEDURE getEstadoVerdadeiro
CREATE PROCEDURE getEstadoVerdadeiro @numLivro INTEGER
AS
BEGIN
	DECLARE @estado BIT

	SET @estado = (SELECT estado FROM Livro WHERE @numLivro = numero_livro)
	
	IF EXISTS(SELECT 1 FROM Emprestimo WHERE numero_livro = @numLivro AND data_requisicao IS NOT NULL AND data_entrega IS NULL)
	BEGIN
		RETURN @estado
	END

	RETURN 0;
	
END

-- (g)
DROP PROCEDURE corrigirEstado
CREATE PROCEDURE corrigirEstado @numLivro INTEGER
AS 
BEGIN
	DECLARE @estadoEmp BIT
	DECLARE @estadoLiv BIT

	-- lê estado dos livros
	IF EXISTS(SELECT numero_livro,data_entrega,data_requisicao FROM Emprestimo WHERE numero_livro = @numLivro AND data_requisicao IS NOT NULL AND data_entrega IS NULL)
		SET @estadoEmp = 1 
	ELSE
		SET @estadoEmp = 0
	SET @estadoLiv = (SELECT estado FROM Livro WHERE numero_livro = @numLivro)
	
	-- verifica se estados são iguais
	IF @estadoEmp = @estadoLiv
		RETURN 1;	
	ELSE
		BEGIN
			-- caso o estado do livro seja diferente nas tabelas, modifica o estado do livro na tabela livro
			UPDATE Livro SET estado = @estadoEmp WHERE numero_livro = @numLivro
		END
END

-- (h)
CREATE PROCEDURE corrigirTodosOsEstados
AS
	DECLARE cursor_estado CURSOR
	FOR SELECT numero_livro FROM Livro

	DECLARE @codLivro INTEGER

	OPEN cursor_estado
	FETCH NEXT FROM cursor_estado INTO @codLivro
	
	IF (@@FETCH_STATUS = -1)
		BEGIN
			PRINT 'Não existem liros registados'
			CLOSE cursor_estado
			DEALLOCATE cursor_estado
			RETURN
		END

	WHILE (@@FETCH_STATUS = 0)
		BEGIN
			EXECUTE corrigirEstado @codLivro
			FETCH NEXT FROM cursor_estado INTO @codLivro
		END
	CLOSE cursor_estado
	DEALLOCATE cursor_estado

	