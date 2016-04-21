USE master;
GO

IF EXISTS (SELECT * FROM sysdatabases WHERE NAME='ford')
BEGIN
	RAISERROR('Dropping ford',0,1)
	DROP DATABASE ford;
END
GO

CREATE DATABASE ford;
GO

USE ford;
GO

IF DB_NAME()<>'ford'
BEGIN
	RAISERROR('Error to create ford database',22,127) WITH log
	DROP DATABASE ford;
END
GO

CREATE TABLE position
(
	position_id INT NOT NULL PRIMARY KEY IDENTITY,
	descr VARCHAR(32) NOT NULL
);
GO
SET IDENTITY_INSERT position ON;
INSERT INTO position(position_id, descr) VALUES(5001, 'Secretary'); --1
INSERT INTO position(position_id, descr) VALUES(5002, 'Operator');
INSERT INTO position(position_id, descr) VALUES(5003, 'Quality Assurance');
INSERT INTO position(position_id, descr) VALUES(5004, 'Consultant');
INSERT INTO position(position_id, descr) VALUES(5005, 'Operation Manager');
INSERT INTO position(position_id, descr) VALUES(5006, 'Systems Engineer');
INSERT INTO position(position_id, descr) VALUES(5007, 'Software engineer');
INSERT INTO position(position_id, descr) VALUES(5008, 'Manager');
INSERT INTO position(position_id, descr) VALUES(5009, 'Departement Head');
INSERT INTO position(position_id, descr) VALUES(5010, 'CEO');

GO
SET IDENTITY_INSERT position OFF;


CREATE TABLE division
(
	division_id INT NOT NULL PRIMARY KEY IDENTITY,
	name VARCHAR(32) NOT NULL
);
GO
SET IDENTITY_INSERT division ON;
INSERT INTO division(division_id, name) VALUES(8001, 'Sales');
INSERT INTO division(division_id, name) VALUES(8002, 'Production');
INSERT INTO division(division_id, name) VALUES(8003, 'Marketing');
INSERT INTO division(division_id, name) VALUES(8004, 'Human Resources');
INSERT INTO division(division_id, name) VALUES(8005, 'Information Technology');
GO
SET IDENTITY_INSERT division OFF;


CREATE TABLE store
(
	store_id INT NOT NULL PRIMARY KEY IDENTITY,
	name VARCHAR(32) NOT NULL,
	address_n VARCHAR(32) NOT NULL,
	city VARCHAR(32) NOT NULL,
	state_n CHAR(4) NOT NULL,
	zip INT NOT NULL,
	phone VARCHAR(13) NOT NULL,
	sales CHAR(2) NOT NULL
);
GO
SET IDENTITY_INSERT store ON;
INSERT INTO store(store_id, name, address_n, city, state_n, zip, phone, sales) VALUES(1302, 'Palma',		'18 Main St',	'Oakland',	'CA',	94345, '717-822-5627', 'E');
INSERT INTO store(store_id, name, address_n, city, state_n, zip, phone, sales) VALUES(1303, 'Floresta',		'22 King St',	'Oakland',	'CA',	94345, '717-822-3322', 'B');
INSERT INTO store(store_id, name, address_n, city, state_n, zip, phone, sales) VALUES(1304, 'Vista Bella', '34 Market St',	'Oakland',	'CA',	94346, '717-801-5699', 'B');
INSERT INTO store(store_id, name, address_n, city, state_n, zip, phone, sales) VALUES(1305, 'Vista Hermosa', '17 North St', 'Oakland',	'CA',	94346, '717-801-2347', 'E');
INSERT INTO store(store_id, name, address_n, city, state_n, zip, phone, sales) VALUES(1306, 'Circuito',		'45 South St', 'Oakland',	'CA',	94345, '717-822-6234', 'E');
INSERT INTO store(store_id, name, address_n, city, state_n, zip, phone, sales) VALUES(1307, 'SL Tecnología', '345 Main Rd', 'Oakland',	'CA',	94349, '717-829-5157', 'G');
INSERT INTO store(store_id, name, address_n, city, state_n, zip, phone, sales) VALUES(1404, 'Tecnología Azul', '554 Sun Rd', 'Hoboken', 'NJ',	94007, '201-217-2133', 'E');
INSERT INTO store(store_id, name, address_n, city, state_n, zip, phone, sales) VALUES(1405, 'Buen Carro',	'23 Luz Dr',	'Hoboken',	'NJ',	94006, '201-216-2525', 'G');
INSERT INTO store(store_id, name, address_n, city, state_n, zip, phone, sales) VALUES(1406, 'Tecnología Verde', '34 Koala Rd', 'Hoboken', 'NJ', 94006, '201-216-9987', 'B');
INSERT INTO store(store_id, name, address_n, city, state_n, zip, phone, sales) VALUES(1407, 'Solo lo mejor', '343 Oak St',	'Hoboken',	'NJ',	94007, '201-217-5627', 'E');

GO
SET IDENTITY_INSERT store OFF;


CREATE TABLE employee
(
	employee_id INT NOT NULL PRIMARY KEY IDENTITY,
	name VARCHAR(32) NOT NULL,
	contract_date DATE NOT NULL,
	birth_date DATE NOT NULL
);
GO
SET IDENTITY_INSERT employee ON;
INSERT INTO employee(employee_id, name, contract_date, birth_date) VALUES(50, 'Martinez, Oscar',	'1998-01-05', '1970-03-05');
INSERT INTO employee(employee_id, name, contract_date, birth_date) VALUES(51, 'Lou, Tim',			'1982-01-15', '1952-02-22');
INSERT INTO employee(employee_id, name, contract_date, birth_date) VALUES(52, 'Lee, Xu',			'1999-05-25', '1972-03-18');
INSERT INTO employee(employee_id, name, contract_date, birth_date) VALUES(53, 'Ley, Martin',		'1980-12-05', '1950-06-10');
INSERT INTO employee(employee_id, name, contract_date, birth_date) VALUES(54, 'Ley, Joseph',		'1970-04-22', '1959-11-11');
GO
SET IDENTITY_INSERT employee OFF;


CREATE TABLE payroll
(
	employee_id INT NOT NULL REFERENCES employee(employee_id) ON DELETE CASCADE, --PRIMARY KEY IDENTITY, --REFERENCES orderx(order_id) ON DELETE CASCADE,
	eff_date DATE NOT NULL, 
	position_id INT NOT NULL REFERENCES position(position_id) ON DELETE CASCADE,
	division_id INT NOT NULL REFERENCES division(division_id) ON DELETE CASCADE,
	salary MONEY NOT NULL,
	PRIMARY KEY (employee_id, eff_date)
);
GO
--SET IDENTITY_INSERT ord_det ON;
INSERT INTO payroll (employee_id,eff_date,position_id,division_id, salary) VALUES (50, '1998-01-05', 5001, 8001, 18000.00);
INSERT INTO payroll (employee_id,eff_date,position_id,division_id, salary) VALUES (50, '1999-04-22', 5001, 8001, 28000.00);
INSERT INTO payroll (employee_id,eff_date,position_id,division_id, salary) VALUES (50, '1999-12-22', 5002, 8001, 32000.00);
INSERT INTO payroll (employee_id,eff_date,position_id,division_id, salary) VALUES (50, '2000-04-10', 5003, 8004, 33000.00);
INSERT INTO payroll (employee_id,eff_date,position_id,division_id, salary) VALUES (50, '2001-11-15', 5003, 8004, 33500.00);
INSERT INTO payroll (employee_id,eff_date,position_id,division_id, salary) VALUES (50, '2005-08-15', 5005, 8005, 55007.00);
INSERT INTO payroll (employee_id,eff_date,position_id,division_id, salary) VALUES (51, '1982-01-15', 5005, 8005, 78000.00);
INSERT INTO payroll (employee_id,eff_date,position_id,division_id, salary) VALUES (51, '1989-12-12', 5006, 8005, 79060.00);
INSERT INTO payroll (employee_id,eff_date,position_id,division_id, salary) VALUES (51, '1998-02-28', 5007, 8005, 88502.00);
INSERT INTO payroll (employee_id,eff_date,position_id,division_id, salary) VALUES (52, '1999-05-25', 5003, 8002, 48502.00);
INSERT INTO payroll (employee_id,eff_date,position_id,division_id, salary) VALUES (52, '1999-11-25', 5003, 8003, 58502.00);
INSERT INTO payroll (employee_id,eff_date,position_id,division_id, salary) VALUES (52, '2004-05-20', 5004, 8002, 59965.00);
INSERT INTO payroll (employee_id,eff_date,position_id,division_id, salary) VALUES (53, '1980-12-05', 5006, 8002, 89965.00);
INSERT INTO payroll (employee_id,eff_date,position_id,division_id, salary) VALUES (53, '1989-09-09', 5007, 8002, 99965.00);
INSERT INTO payroll (employee_id,eff_date,position_id,division_id, salary) VALUES (53, '1990-10-10', 5009, 8002, 105909.00);
INSERT INTO payroll (employee_id,eff_date,position_id,division_id, salary) VALUES (53, '2004-12-29', 5010, 8002, 250000.00);
INSERT INTO payroll (employee_id,eff_date,position_id,division_id, salary) VALUES (54, '1970-04-22', 5004, 8003, 50000.00);
INSERT INTO payroll (employee_id,eff_date,position_id,division_id, salary) VALUES (54, '1990-06-10', 5004, 8004, 58000.00);
GO
--SET IDENTITY_INSERT ord_det OFF;
