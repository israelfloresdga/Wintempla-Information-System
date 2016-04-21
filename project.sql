USE master;
GO

IF EXISTS (SELECT * FROM sysdatabases WHERE NAME='project')
BEGIN
	RAISERROR('Dropping project',0,1)
	DROP DATABASE project;
END
GO

CREATE DATABASE project;
GO

USE project;
GO

IF DB_NAME()<>'project'
BEGIN
	RAISERROR('Error to create project database',22,127) WITH log
	DROP DATABASE project;
END
GO
--------------------------------------------------------------------------------
CREATE TABLE client
(
	client_id INT NOT NULL PRIMARY KEY IDENTITY,
	last_name VARCHAR(32) NOT NULL,
	first_name VARCHAR(32) NOT NULL,
	telephone VARCHAR(16),
	celphone VARCHAR(16),
	email VARCHAR(32),
	city VARCHAR(32) NOT NULL,
	statez VARCHAR(32) NOT NULL
);
GO


CREATE TABLE store
(
	store_id INT NOT NULL PRIMARY KEY IDENTITY,
	descr VARCHAR(32) NOT NULL,
	telephone VARCHAR(16) NOT NULL,
	city VARCHAR(32) NOT NULL,
	statez VARCHAR(32) NOT NULL
);


CREATE TABLE employee
(
	employee_id INT NOT NULL PRIMARY KEY IDENTITY,
	last_name VARCHAR(32) NOT NULL,
	first_name VARCHAR(32) NOT NULL,
	telephone VARCHAR(16) NOT NULL,
	celphone VARCHAR(16),
	email VARCHAR(32) NOT NULL,
	username VARCHAR(32) NOT NULL,
	userpass VARCHAR(32) NOT NULL,
	is_admin BIT NOT NULL,
	store_id INT NOT NULL REFERENCES store(store_id)
);
GO


CREATE TABLE platformz
(
	platform_id INT NOT NULL PRIMARY KEY IDENTITY,
	descr VARCHAR(32) NOT NULL
);
GO


CREATE TABLE genre
(
	genre_id INT NOT NULL PRIMARY KEY IDENTITY,
	descr VARCHAR(32) NOT NULL
);
GO


CREATE TABLE rated
(
	rated_id INT NOT NULL PRIMARY KEY IDENTITY,
	descr VARCHAR(32) NOT NULL
);
GO


CREATE TABLE versionz
(
	version_id INT NOT NULL PRIMARY KEY IDENTITY,
	descr VARCHAR(32) NOT NULL
);
GO


CREATE TABLE item
(
	item_id INT NOT NULL PRIMARY KEY IDENTITY,
	descr VARCHAR(32) NOT NULL,
	platform_id INT NOT NULL REFERENCES platformz(platform_id),
	genre_id INT NOT NULL REFERENCES genre(genre_id),
	rated_id INT NOT NULL REFERENCES rated(rated_id),
	max_players INT NOT NULL,
	version_id INT NOT NULL REFERENCES versionz(version_id)
);
GO


CREATE TABLE payroll
(
	employee_id INT NOT NULL REFERENCES employee(employee_id),
	descr VARCHAR(32) NOT NULL,
	begin_date DATE NOT NULL,
	end_date DATE NOT  NULL,
	salary MONEY NOT NULL,
	PRIMARY KEY(employee_id,begin_date)
);
GO


CREATE TABLE item_price_history
(
	item_id INT NOT NULL REFERENCES item(item_id) ON DELETE CASCADE,
	effective_date DATE NOT NULL,
	price MONEY NOT NULL,
	PRIMARY KEY (item_id, effective_date)
);
GO


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
	price MONEY NOT NULL,
	item_count INT NOT NULL,
	PRIMARY KEY(buy_sell_id, item_id)
);
GO


CREATE TABLE cart
(
	client_id INT NOT NULL REFERENCES client(client_id) ON DELETE CASCADE,
	item_id INT NOT NULL REFERENCES item(item_id) ON DELETE CASCADE,
	item_count INT NOT NULL,
	PRIMARY KEY(client_id, item_id)
);
GO

CREATE VIEW vw_Item AS
SELECT i.item_id,
		p.platform_id, 
		g.genre_id,
		r.rated_id,
		v.version_id,
		i.descr AS item_descr,
		p.descr AS platform_descr,
		g.descr AS genre_descr,
		r.descr AS rated_descr,
		i.max_players,
		v.descr AS version_descr
FROM item i, 
		platformz p, 
		genre g,
		rated r,
		versionz v
WHERE p.platform_id=i.platform_id AND 
		g.genre_id=i.genre_id AND 
		r.rated_id=i.rated_id AND
		v.version_id=i.version_id;
GO

CREATE VIEW vw_Client AS
SELECT	client_id,
		first_name+' '+last_name AS name, 
		telephone,
		celphone,
		email,
		city,
		statez
FROM client;
GO

CREATE VIEW vw_Employee AS
SELECT	employee_id,
		first_name+' '+last_name AS name, 
		telephone,
		celphone,
		email,
		username,
		userpass,
		REPLACE(REPLACE(is_admin, '0','Employee'), '1','Admin') AS privilege
FROM employee;
GO

--CREATE VIEW vw_Buy_Sell AS
--SELECT bs.buy_sell_id,
--		bs.employee_id,
--		bs.client_id,
--		bs.datez,
--		bsd.item_id,
--		price
--FROM buy_sell bs,
--		buy_sell_detail bsd
--WHERE bs.buy_sell_id=bsd.buy_sell_id;
--GO
