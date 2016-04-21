USE master;
GO

IF EXISTS (SELECT * FROM sysdatabases WHERE NAME='circuit_city_sharing')
BEGIN
	RAISERROR('Dropping circuit_city_sharing',0,1)
	DROP DATABASE circuit_city_sharing;
END
GO

CREATE DATABASE circuit_city_sharing;
GO

USE circuit_city_sharing;
GO

IF DB_NAME()<>'circuit_city_sharing'
BEGIN
	RAISERROR('Error to create circuit_city_sharing database',22,127) WITH log
	DROP DATABASE circuit_city_sharing;
END
GO

CREATE TABLE client
(
	client_id INT NOT NULL PRIMARY KEY IDENTITY,
	last_name VARCHAR(32) NOT NULL,
	first_name VARCHAR(32) NOT NULL,
	birthdate DATE NOT NULL,
	city VARCHAR(32) NOT NULL
);
GO
--SET IDENTITY_INSERT client ON;
INSERT INTO client(last_name, first_name, birthdate, city) VALUES('Orozco',		'Peter',	'22/10/1979',	'Salamanca'); --1
INSERT INTO client(last_name, first_name, birthdate, city) VALUES('Perez',		'Jonh',		'22/1/1979',	'Celaya');
INSERT INTO client(last_name, first_name, birthdate, city) VALUES('Smith',		'Chaz',		'22/11/1959',	'Irapuato');
INSERT INTO client(last_name, first_name, birthdate, city) VALUES('Rodríguez',	'Paulina',	'22/2/1967',	'Leon');
GO
--SET IDENTITY_INSERT client OFF;


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


CREATE TABLE employee
(
	employee_id INT NOT NULL PRIMARY KEY IDENTITY,
	last_name VARCHAR(32) NOT NULL,
	first_name VARCHAR(32) NOT NULL,
	username VARCHAR(32) NOT NULL,
	user_pass VARCHAR(32) NOT NULL,
	phone VARCHAR(16) NOT NULL,
	is_admi BIT NOT NULL,
);
GO
INSERT INTO employee(last_name,first_name,username,user_pass,phone,is_admi) VALUES('Ferry',	'Jim',	'jimmy', 'easy',		'201-422-3425', 1);
INSERT INTO employee(last_name,first_name,username,user_pass,phone,is_admi) VALUES('Lou',	'Laura','laura', 'difficult',	'212-657-5820', 0);
GO


CREATE TABLE payroll
(
	employee_id INT NOT NULL REFERENCES employee(employee_id) ON DELETE CASCADE,
	descr VARCHAR(32) NOT NULL,
	begin_date DATE NOT NULL,
	end_date DATE NOT  NULL,
	salary MONEY NOT NULL,
	PRIMARY KEY(employee_id,begin_date)
);
GO
INSERT INTO payroll(employee_id,descr,begin_date,end_date,salary) VALUES(1, 'First contract',	'10/1/2010', '31/12/2011',	'12000.00');
INSERT INTO payroll(employee_id,descr,begin_date,end_date,salary) VALUES(1, 'Promotion',		'11/1/2012', '31/12/2012',	'18000.00');
INSERT INTO payroll(employee_id,descr,begin_date,end_date,salary) VALUES(2, 'First contract',	'1/1/2010', '31/12/2012',	'19000.00');
INSERT INTO payroll(employee_id,descr,begin_date,end_date,salary) VALUES(2, 'Promotion',		'2/1/2012', '31/7/2012',	'24000.00');
INSERT INTO payroll(employee_id,descr,begin_date,end_date,salary) VALUES(2, 'Promotion',		'2/8/2012', '31/12/2014',	'124000.00');
GO


CREATE TABLE item_price_history
(
	item_id INT NOT NULL REFERENCES item(item_id) ON DELETE CASCADE,
	effective_date DATE NOT NULL,
	price MONEY NOT NULL,
	PRIMARY KEY (item_id, effective_date)
);
GO
INSERT INTO item_price_history(item_id,effective_date,price) VALUES(1, '25/4/2010', '1000.20');
INSERT INTO item_price_history(item_id,effective_date,price) VALUES(1, '27/4/2011', '900.50');
INSERT INTO item_price_history(item_id,effective_date,price) VALUES(1, '28/4/2012', '800.50');
INSERT INTO item_price_history(item_id,effective_date,price) VALUES(2, '25/2/2007', '7000.00');
INSERT INTO item_price_history(item_id,effective_date,price) VALUES(2, '24/2/2008', '6000.00');
INSERT INTO item_price_history(item_id,effective_date,price) VALUES(2, '23/2/2009', '5000.00');
INSERT INTO item_price_history(item_id,effective_date,price) VALUES(3, '14/3/2007', '6999.00');
INSERT INTO item_price_history(item_id,effective_date,price) VALUES(3, '18/3/2007', '4999.00');
INSERT INTO item_price_history(item_id,effective_date,price) VALUES(3, '29/3/2014', '4900.00');
GO


CREATE TABLE buy_sell
(
	buy_sell_id INT NOT NULL PRIMARY KEY IDENTITY,
	employee_id INT NOT NULL REFERENCES employee(employee_id) ON DELETE CASCADE,
	client_id INT NOT NULL REFERENCES client(client_id) ON DELETE CASCADE,
	datez DATE NOT NULL, 
);
GO
INSERT INTO buy_sell(employee_id,client_id,datez) VALUES(1,1,'15-03-2011');
INSERT INTO buy_sell(employee_id,client_id,datez) VALUES(2,1,'24-12-2011');
INSERT INTO buy_sell(employee_id,client_id,datez) VALUES(2,2,'29-05-2012');
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
INSERT INTO buy_sell_detail(buy_sell_id,item_id,price,item_count) VALUES(1,1,'800.50',	2);
INSERT INTO buy_sell_detail(buy_sell_id,item_id,price,item_count) VALUES(1,2,'5000.00',	5);
INSERT INTO buy_sell_detail(buy_sell_id,item_id,price,item_count) VALUES(1,3,'4999.00',	3);
INSERT INTO buy_sell_detail(buy_sell_id,item_id,price,item_count) VALUES(2,1,'800.50',	2);
INSERT INTO buy_sell_detail(buy_sell_id,item_id,price,item_count) VALUES(2,3,'4999.00',	5);
INSERT INTO buy_sell_detail(buy_sell_id,item_id,price,item_count) VALUES(3,1,'800.50',	10);
INSERT INTO buy_sell_detail(buy_sell_id,item_id,price,item_count) VALUES(3,2,'5000.00',	5);
INSERT INTO buy_sell_detail(buy_sell_id,item_id,price,item_count) VALUES(3,3,'4999.00',	8);
GO

CREATE TABLE cart
(
	client_id INT NOT NULL REFERENCES client(client_id) ON DELETE CASCADE,
	item_id INT NOT NULL REFERENCES item(item_id) ON DELETE CASCADE,
	item_count INT NOT NULL,
	PRIMARY KEY(client_id, item_id)
);
GO

--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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

CREATE VIEW vw_Client AS
SELECT	client_id,
		first_name+' '+last_name AS name, 
		DATEPART(year, GETDATE()) - DATENAME(year, birthdate) AS age, 
		city,
		birthdate
FROM client;
GO


CREATE VIEW vw_Employee AS
SELECT	employee_id,
		first_name+' '+last_name AS name, 
		username,
		phone
FROM employee;
GO


CREATE VIEW vw_Item_price_date AS
SELECT i.item_id,
		i.descr,
		i.model,
		i.brand_id,
		b.descr AS brand_descr,
		iph.price,
		iph.effective_date
FROM	item i,
		item_price_history iph,
		brand b
WHERE	i.item_id=iph.item_id AND
		i.brand_id=b.brand_id;
GO


CREATE VIEW vw_Item_price AS
SELECT i.item_id,
		i.descr,
		i.model,
		i.brand_id,
		b.descr AS brand_descr,
		iph.price,
		iph.effective_date
FROM	item i,
		item_price_history iph,
		brand b
WHERE	i.item_id=iph.item_id AND
		i.brand_id=b.brand_id AND
		iph.effective_date= (
			SELECT MAX(iph1.effective_date)
			FROM item_price_history iph1
			WHERE iph1.effective_date<= GETDATE() AND
				iph.item_id=iph1.item_id);
GO

CREATE VIEW vw_order_price AS
SELECT buy_sell_id, item_id,
	price, item_count, 
	price*item_count AS total
FROM buy_sell_detail;
GO

CREATE VIEW vw_order_total AS
SELECT buy_sell_id, SUM(price*item_count) AS order_total
FROM buy_sell_detail
GROUP BY buy_sell_id;
GO


--____________________________________________________proc_buy
CREATE PROCEDURE proc_buy
	@in_client_id INT,
	@in_employee_id INT
AS
	DECLARE @item_count INT;
	DECLARE @item_id INT;
	DECLARE @count INT;
	DECLARE @buy_sell_id INT;
	DECLARE @price INT;
	
	SET @item_count=0;
	SET @item_id=0;
	SET @count=0;
	SET @buy_sell_id=0;
	
	BEGIN TRANSACTION;--__________________________________
	--____________________________________________________INSERT INTO buy_sell
	INSERT INTO buy_sell(employee_id,client_id) VALUES(@in_employee_id,@in_client_id);
	SET @count= @@ROWCOUNT;
	IF (@count<>1)
	BEGIN
		ROLLBACK TRANSACTION;
		RETURN 0;
	END
	--Be sure an IDENTITY value was generated
	IF (@@IDENTITY=NULL)
	BEGIN
		ROLLBACK TRANSACTION;
		RETURN 0;
	END
	SET @buy_sell_id= @@IDENTITY;--______________________Retrieve the automatically generated buy_sell_id

	DECLARE cur_cart CURSOR READ_ONLY FOR
		SELECT item_id, item_count
		FROM cart
		WHERE client_id= @in_client_id;

	--Go item by item in the cart
	OPEN cur_cart;
		FETCH NEXT FROM cur_cart INTO @item_id, @item_count;
		WHILE (@@FETCH_STATUS=0)
		BEGIN
			--Get the price
			SELECT @price= price
			FROM vw_Item_price
			WHERE item_id= @item_id;
			SET @count= @@ROWCOUNT;
			IF (@count<>1)
			BEGIN
				ROLLBACK TRANSACTION;
				CLOSE cur_cart;
				DEALLOCATE cur_cart;
				RETURN 0;
			END
			SET @count= -1;
			--INSERT INTO buy_sell_detail
			INSERT INTO buy_sell_detail(buy_sell_id,item_id,price,item_count) VALUES(@buy_sell_id,@item_id,@price,@item_count);
			SET @count= @@ROWCOUNT;
			IF (@count<>1)
			BEGIN
				ROLLBACK TRANSACTION;
				CLOSE cur_cart;
				DEALLOCATE cur_cart;
				RETURN 0;
			END
			SET @count= -1;
			--DELETE FROM cart
			DELETE FROM cart WHERE client_id=@in_client_id AND item_id=@item_id;
			SET @count=@@ROWCOUNT;
			IF (@count<>1) 
			BEGIN
				ROLLBACK TRANSACTION;
				CLOSE cur_cart;
				DEALLOCATE cur_cart;
				RETURN 0;
			END
			SET @count=-1;
			--GO TO NEXT item
			FETCH NEXT FROM cur_cart INTO @item_id, @item_count;
		END
	CLOSE cur_cart;
	DEALLOCATE cur_cart;
	COMMIT TRANSACTION;--__________________________________
	RETURN 1;
GO

