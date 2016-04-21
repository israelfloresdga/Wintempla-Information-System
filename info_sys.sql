USE master;
GO

IF EXISTS (SELECT * FROM sysdatabases WHERE NAME='info_sys')
BEGIN
	RAISERROR('Dropping info_sys',0,1)
	DROP DATABASE info_sys;
END
GO

CREATE DATABASE info_sys;
GO

USE info_sys;
GO

IF DB_NAME()<>'info_sys'
BEGIN
	RAISERROR('Error to create info_sys database',22,127) WITH log
	DROP DATABASE info_sys;
END
GO

CREATE TABLE item
(
	item_id INT NOT NULL PRIMARY KEY,
	name VARCHAR(32) NOT NULL,
	cost DECIMAL NOT NULL
);
GO
INSERT INTO item(item_id, name, cost) VALUES(100, 'Monitor X8',		200.50);
INSERT INTO item(item_id, name, cost) VALUES(101, 'Monitor X2',		399.50);
INSERT INTO item(item_id, name, cost) VALUES(102, 'Monitor S3',		453.50);
INSERT INTO item(item_id, name, cost) VALUES(103, 'Hard Drive 15G', 80.99);
INSERT INTO item(item_id, name, cost) VALUES(104, 'Hard Drive 80G', 280.00);
INSERT INTO item(item_id, name, cost) VALUES(105, 'Printer U9',		550.50);
INSERT INTO item(item_id, name, cost) VALUES(106, 'CD ROM',			39.50);
INSERT INTO item(item_id, name, cost) VALUES(107, 'CD Burner',		99.78);
INSERT INTO item(item_id, name, cost) VALUES(108, 'RAM 255M',		54.50);
INSERT INTO item(item_id, name, cost) VALUES(109, 'RAM 512M',		80.99);
INSERT INTO item(item_id, name, cost) VALUES(110, 'Keyboard',		20.00);
INSERT INTO item(item_id, name, cost) VALUES(111, 'Mouse',			15.68);
GO

--Problem 2 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
CREATE TABLE patient
(
	patient_id INT NOT NULL PRIMARY KEY,
	diagnostic VARCHAR(32) NOT NULL,
	medication VARCHAR(64) NOT NULL,
	room INT NOT NULL,
	verification_date DATE NOT NULL,
);
GO
INSERT INTO	patient(patient_id,diagnostic,medication,room,verification_date) VALUES(104, 'Infarto cerebral',	'Operación',					101, '12-05-1999');
INSERT INTO	patient(patient_id,diagnostic,medication,room,verification_date) VALUES(1043, 'Quiste pilonidal',	'Operación, 6 meses de reposo',					351, '25-12-2010');
INSERT INTO	patient(patient_id,diagnostic,medication,room,verification_date) VALUES(503, 'Neumonía',			'Antibioticos, Reposo',			325, '19-6-2003');
INSERT INTO	patient(patient_id,diagnostic,medication,room,verification_date) VALUES(451, 'Parto',				'Trabajo de parto',				248, '26-1-2001');
INSERT INTO	patient(patient_id,diagnostic,medication,room,verification_date) VALUES(843, 'Gastritis',			'Antibíoticos, Dieta blanda',	400, '21-4-2004');
GO

--Problem 3 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
CREATE TABLE department
(
	departement_id CHAR(2) NOT NULL PRIMARY KEY,
	descr VARCHAR(32) NOT NULL
);
GO
INSERT INTO department(departement_id,descr) VALUES('C', 'Computer');
INSERT INTO department(departement_id,descr) VALUES('E', 'Electronics');
INSERT INTO department(departement_id,descr) VALUES('M', 'Mechanics');
INSERT INTO department(departement_id,descr) VALUES('A', 'Arts');
GO

--Problem 4 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
CREATE TABLE statusz
(
	status_id CHAR NOT  NULL PRIMARY KEY,
	descr VARCHAR(32) NOT NULL
);
GO
INSERT INTO statusz(status_id,descr) VALUES('A', 'Activo');
INSERT INTO statusz(status_id,descr) VALUES('D', 'Descanso');
INSERT INTO statusz(status_id,descr) VALUES('E', 'En espera');
INSERT INTO statusz(status_id,descr) VALUES('P', 'Perdido en acción');
INSERT INTO statusz(status_id,descr) VALUES('M', 'Muerto en acción');
GO

--Problem 5 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
CREATE TABLE client
(
	client_id INT NOT NULL PRIMARY KEY,
	name VARCHAR(32) NOT NULL,
	addressz VARCHAR(32) NOT NULL,
	birth_date SMALLDATETIME NOT NULL
);
GO
INSERT INTO client(client_id,name,addressz,birth_date) VALUES(2345, 'Sigal, Tobias', '56 Clayton Road', '10 Abril 1980');
--INSERT INTO client(client_id,name,addressz,birth_date) VALUES();
GO

CREATE TABLE account
(
	account_id INT NOT NULL PRIMARY KEY,
	balance MONEY NOT NULL
);
GO
INSERT INTO account(account_id, balance) VALUES(120768, 234.56);
--INSERT INTO account(account_id, balance) VALUES();
GO

CREATE TABLE account_client
(
	account_id INT REFERENCES account(account_id),
	client_id INT REFERENCES client(client_id),
	PRIMARY KEY (account_id, client_id)
);
GO
