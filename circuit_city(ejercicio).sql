USE master;
GO

IF EXISTS (SELECT * FROM sysdatabases WHERE NAME='circuit_city2')
BEGIN
	RAISERROR('Dropping circuit_city2',0,1)
	DROP DATABASE circuit_city2;
END
GO

CREATE DATABASE circuit_city2;
GO

USE circuit_city2;
GO

IF DB_NAME()<>'circuit_city2'
BEGIN
	RAISERROR('Error to create circuit_city2 database',22,127) WITH log
	DROP DATABASE circuit_city2;
END
GO

--Basic tables ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
CREATE TABLE client
(
	client_id INT NOT NULL PRIMARY KEY IDENTITY,
	name VARCHAR(32) NOT NULL,
	company VARCHAR(32) NOT NULL
);
GO

CREATE TABLE item
(
	item_id INT NOT NULL PRIMARY KEY IDENTITY,
	name VARCHAR(32) NOT NULL,
	cost money NOT NULL
);
GO

CREATE TABLE item_price_history
(
	item_id INT NOT NULL PRIMARY KEY REFERENCES item(item_id),
	eff_date DATE NOT NULL,
	price MONEY NOT NULL
);
GO

CREATE TABLE item_brand
(
	item_brand_id INT NOT NULL PRIMARY KEY,
	name VARCHAR(32) NOT NULL,
);
GO

CREATE TABLE employee
(
	employee_id INT NOT NULL PRIMARY KEY,
	name VARCHAR(32) NOT NULL,
	job_title VARCHAR(32) NOT NULL,
	contract_date DATE NOT NULL,
	birth_date DATE NOT NULL,
	telephone VARCHAR(14) NOT NULL,
	email VARCHAR(32) NOT NULL,
	addressz VARCHAR(32) NOT NULL,
);
GO

CREATE TABLE payroll
(
	employee_id INT NOT NULL REFERENCES employee(employee_id) ON DELETE CASCADE,
	descr VARCHAR(32) NOT NULL,
	salary MONEY NOT NULL,
	begin_date DATE NOT NULL,
	end_date DATE NOT NULL
);
GO

--Linking tables |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
CREATE TABLE buy_sell
(
	buy_sell_id INT NOT NULL PRIMARY KEY,
	employee_id INT NOT NULL REFERENCES employee(employee_id) ON DELETE CASCADE,
	client_id INT NOT NULL REFERENCES client(client_id) ON DELETE CASCADE,
	datez DATE NOT NULL, 
);
GO

CREATE TABLE buy_sell_detail
(
	buy_sell_id INT NOT NULL REFERENCES buy_sell(buy_sell_id) ON DELETE CASCADE,
	item_id INT NOT NULL REFERENCES item(item_id) ON DELETE CASCADE,
	item_count INT NOT NULL,
	PRIMARY KEY(buy_sell_id, item_id, item_count)
);
GO

--
CREATE TABLE cart
(
	client_id INT NOT NULL REFERENCES client(client_id) ON DELETE CASCADE,
	item_id INT NOT NULL REFERENCES item(item_id) ON DELETE CASCADE,
	item_count INT NOT NULL, --REFERENCES buy_sell_detail(item_count) ON DELETE CASCADE,
	PRIMARY KEY(client_id, item_id, item_count)
);
GO