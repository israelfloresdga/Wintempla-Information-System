USE master;
GO

IF EXISTS (SELECT * FROM sysdatabases WHERE NAME='circuit_city')
BEGIN
	RAISERROR('Dropping circuit_city',0,1)
	DROP DATABASE circuit_city;
END
GO

CREATE DATABASE circuit_city;
GO

USE circuit_city;
GO

IF DB_NAME()<>'circuit_city'
BEGIN
	RAISERROR('Error to create circuit_city database',22,127) WITH log
	DROP DATABASE circuit_city;
END
GO

CREATE TABLE client
(
	client_id INT NOT NULL PRIMARY KEY IDENTITY,
	name VARCHAR(32) NOT NULL,
	company VARCHAR(32) NOT NULL
);
GO
SET IDENTITY_INSERT client ON;
INSERT INTO client(client_id, name, company) VALUES(5000, 'Smith, Tony', 'Microsoft'); --1
INSERT INTO client(client_id, name, company) VALUES(5001, 'Smith, Julie', 'IBM');
INSERT INTO client(client_id, name, company) VALUES(5002, 'Fry, Kevin', 'IBM');
INSERT INTO client(client_id, name, company) VALUES(5003, 'Flana, Fran', 'Microsoft');
INSERT INTO client(client_id, name, company) VALUES(5004, 'Belleza, Ana', 'Canon');
INSERT INTO client(client_id, name, company) VALUES(5005, 'DiTore, Mike', 'Microsoft');
INSERT INTO client(client_id, name, company) VALUES(5006, 'Ferry, Jim', 'HP');
INSERT INTO client(client_id, name, company) VALUES(5007, 'Lynch, Tim', 'DELL');
INSERT INTO client(client_id, name, company) VALUES(5008, 'Frunch, Ken', 'Pacific Bell');
GO
SET IDENTITY_INSERT client OFF;

CREATE TABLE brand
(
	brand_id INT NOT NULL PRIMARY KEY IDENTITY,
	descr VARCHAR(32) NOT NULL
);
GO
INSERT INTO brand(descr) VALUES('Sony');
INSERT INTO brand(descr) VALUES('HP');
INSERT INTO brand(descr) VALUES('Dell');
INSERT INTO brand(descr) VALUES('Whirpool');
INSERT INTO brand(descr) VALUES('Koblenz');
INSERT INTO brand(descr) VALUES('Toshiba');
INSERT INTO brand(descr) VALUES('Canon');
INSERT INTO brand(descr) VALUES('Samsung');
INSERT INTO brand(descr) VALUES('LG');
INSERT INTO brand(descr) VALUES('RCA');
INSERT INTO brand(descr) VALUES('Coby');
GO

CREATE TABLE category
(
	category_id INT NOT NULL PRIMARY KEY IDENTITY,
	descr VARCHAR(32) NOT NULL
);
GO
--__________________________________________________category
INSERT INTO category(descr) VALUES('Video'); --1
INSERT INTO category(descr) VALUES('Computer'); --2
INSERT INTO category(descr) VALUES('Audio'); --3
INSERT INTO category(descr) VALUES('Music'); --4
INSERT INTO category(descr) VALUES('Digital Photo'); --5
INSERT INTO category(descr) VALUES('Computer Accessory'); --6
INSERT INTO category(descr) VALUES('Appliances'); --7
GO

CREATE TABLE item
(
	item_id INT NOT NULL PRIMARY KEY IDENTITY,
	descr VARCHAR(32) NOT NULL,
	brand_id INT NOT NULL REFERENCES brand(brand_id),
	model VARCHAR(16) NOT NULL,
	category_id INT NOT NULL REFERENCES category(category_id)
);
GO
INSERT INTO item(descr, brand_id, model, category_id) VALUES('TV 20 in',			1, 'SN-1520',		1);
INSERT INTO item(descr, brand_id, model, category_id) VALUES('TV 27 in',			1, 'SN-1527 ES',	1);
INSERT INTO item(descr, brand_id, model, category_id) VALUES('TV 20 in',			6, 'TH-1510',		1);
INSERT INTO item(descr, brand_id, model, category_id) VALUES('TV 27 in',			6, 'TH-1511',		1);
INSERT INTO item(descr, brand_id, model, category_id) VALUES('Cyber-shot Camera',	7, 'KL2012',		5);
INSERT INTO item(descr, brand_id, model, category_id) VALUES('Printer',				7, 'CAN-1511',		5);
INSERT INTO item(descr, brand_id, model, category_id) VALUES('CD/DVD buner 16x',	2, 'ATA202',		2);
INSERT INTO item(descr, brand_id, model, category_id) VALUES('Monitor 20 in',		2, 'LG2202',		2);
INSERT INTO item(descr, brand_id, model, category_id) VALUES('Mouse',				2, 'SN-5678',		2);
INSERT INTO item(descr, brand_id, model, category_id) VALUES('USB Keyboard',		2, 'HP3465-ZAS',	2);
INSERT INTO item(descr, brand_id, model, category_id) VALUES('Scaner',				2, 'HP-122',		2);
INSERT INTO item(descr, brand_id, model, category_id) VALUES('Digital Camera',		7, 'CAN-1511 XES',	5);
INSERT INTO item(descr, brand_id, model, category_id) VALUES('Cyber-shot Camera',	7, 'MPsa1200',		5);
INSERT INTO item(descr, brand_id, model, category_id) VALUES('10 CDs Pack',			1, 'SONY-784',		3);
INSERT INTO item(descr, brand_id, model, category_id) VALUES('Washer',				9, 'LG-K19',		7);
INSERT INTO item(descr, brand_id, model, category_id) VALUES('Refrigerator',		4, 'WH89-XS',		7);
INSERT INTO item(descr, brand_id, model, category_id) VALUES('Printer',				2, 'HP8-344',		6);
INSERT INTO item(descr, brand_id, model, category_id) VALUES('MP3 Player',			1, 'Coby',			4);
INSERT INTO item(descr, brand_id, model, category_id) VALUES('Printer',				3, 'Dell-2021',		6);
INSERT INTO item(descr, brand_id, model, category_id) VALUES('Laptop',				6, 'TOSH-22ZA',		2);
INSERT INTO item(descr, brand_id, model, category_id) VALUES('Laptop',				2, 'HP-NX6515',		2);
GO


CREATE TABLE orderx
(
	order_id INT NOT NULL PRIMARY KEY IDENTITY,
	client_id INT NOT NULL REFERENCES client(client_id) ON DELETE CASCADE
);
GO
SET IDENTITY_INSERT orderx ON;
INSERT INTO orderx (order_id, client_id) VALUES(2000, 5000);
INSERT INTO orderx (order_id, client_id) VALUES(2001, 5008);
INSERT INTO orderx (order_id, client_id) VALUES(2002, 5005);
INSERT INTO orderx (order_id, client_id) VALUES(2003, 5001);
INSERT INTO orderx (order_id, client_id) VALUES(2004, 5008);
INSERT INTO orderx (order_id, client_id) VALUES(2005, 5001);
GO
SET IDENTITY_INSERT orderx OFF;


CREATE TABLE credit_client
(
	client_id INT NOT NULL REFERENCES client(client_id) ON DELETE CASCADE, --PRIMARY KEY IDENTITY, --REFERENCES client(client_id) ON DELETE CASCADE,
	credit money NOT NULL
);
GO
--SET IDENTITY_INSERT credit_client ON;
INSERT INTO credit_client (client_id, credit) VALUES(5000, 1000.00);
INSERT INTO credit_client (client_id, credit) VALUES(5001, 3000.00);
INSERT INTO credit_client (client_id, credit) VALUES(5002, 400.00);
INSERT INTO credit_client (client_id, credit) VALUES(5003, 500.00);
INSERT INTO credit_client (client_id, credit) VALUES(5004, 7000.00);
INSERT INTO credit_client (client_id, credit) VALUES(5005, 8000.00);
INSERT INTO credit_client (client_id, credit) VALUES(5008, 90.00);
GO
--SET IDENTITY_INSERT credit_client OFF;


CREATE TABLE ord_det --LINKING TABLE
(
	order_id INT NOT NULL REFERENCES orderx(order_id) ON DELETE CASCADE, --PRIMARY KEY IDENTITY, --REFERENCES orderx(order_id) ON DELETE CASCADE,
	item_id INT NOT NULL REFERENCES item(item_id) ON DELETE CASCADE,
	item_count INT NOT NULL,
	PRIMARY KEY (order_id, item_id)
);
GO

--SET IDENTITY_INSERT ord_det ON;
--INSERT INTO ord_det (order_id,item_id,item_count) VALUES (2000, 100, 4);
--GO
--SET IDENTITY_INSERT ord_det OFF;
CREATE VIEW vw_Item AS
SELECT i.item_id,
		b.brand_id, 
		c.category_id,
		i.descr AS [item descr],
		b.descr AS [brand descr],
		c.descr AS [category descr],
		i.model
FROM item AS i, brand AS b, category AS c
WHERE b.brand_id=i.brand_id AND c.category_id=i.category_id;
GO
