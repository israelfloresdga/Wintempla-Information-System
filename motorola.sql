USE master;
GO

IF EXISTS (SELECT * FROM sysdatabases WHERE NAME='motorola')
BEGIN
	RAISERROR('Dropping motorola',0,1)
	DROP DATABASE motorola;
END
GO

CREATE DATABASE motorola;
GO

USE motorola;
GO

IF DB_NAME()<>'motorola'
BEGIN
	RAISERROR('Error to create motorola database',22,127) WITH log
	DROP DATABASE motorola;
END
GO

CREATE TABLE skill
(
	skill_id INT NOT NULL PRIMARY KEY,
	descr VARCHAR(12) NOT NULL
);
GO
INSERT INTO skill(skill_id, descr) VALUES(202, 'German');
INSERT INTO skill(skill_id, descr) VALUES(203, 'Typing');
INSERT INTO skill(skill_id, descr) VALUES(204, 'Shorthand');
INSERT INTO skill(skill_id, descr) VALUES(205, 'French');
INSERT INTO skill(skill_id, descr) VALUES(206, 'C++');
INSERT INTO skill(skill_id, descr) VALUES(207, 'Java');
INSERT INTO skill(skill_id, descr) VALUES(208, 'HTML');
INSERT INTO skill(skill_id, descr) VALUES(209, 'XML');
INSERT INTO skill(skill_id, descr) VALUES(210, 'XSL');
INSERT INTO skill(skill_id, descr) VALUES(211, 'C#');
GO


CREATE TABLE department
(
	dept_id INT NOT NULL PRIMARY KEY,
	descr VARCHAR(16) NOT NULL,
	presupuesto	MONEY NOT NULL
);
GO
INSERT INTO department(dept_id,descr, presupuesto) VALUES(60, 'Accounting',	'5050.00');
INSERT INTO department(dept_id,descr, presupuesto) VALUES(90, 'Sales',		'9000.00');
INSERT INTO department(dept_id,descr, presupuesto) VALUES(100, 'Desing',	'4000.00');
GO


CREATE TABLE employee
(
	emp_id INT NOT NULL PRIMARY KEY,
	first_name VARCHAR(16) NOT NULL,
	last_name VARCHAR(16) NOT NULL,
	phone VARCHAR(24) NOT NULL,
	dept_id INT NOT NULL REFERENCES department(dept_id)
);
GO
INSERT INTO employee(emp_id,first_name,last_name,phone,dept_id) VALUES(100, 'Steven',	'King',		'(515) 123-4567', 90);
INSERT INTO employee(emp_id,first_name,last_name,phone,dept_id) VALUES(101, 'Neena',	'Kochhar',	'(515) 123-4668', 90);
INSERT INTO employee(emp_id,first_name,last_name,phone,dept_id) VALUES(102, 'Lex',		'De Haan',	'(515) 123-4569', 90);
INSERT INTO employee(emp_id,first_name,last_name,phone,dept_id) VALUES(103, 'Alexander', 'Hunold',	'(590) 423-4568', 60);
INSERT INTO employee(emp_id,first_name,last_name,phone,dept_id) VALUES(104, 'Bruce',	'Ernst',	'(590) 423-4568', 60);
INSERT INTO employee(emp_id,first_name,last_name,phone,dept_id) VALUES(105, 'David',	'Austin',	'(590) 423-4569', 60);
INSERT INTO employee(emp_id,first_name,last_name,phone,dept_id) VALUES(106, 'Valli',	'Pataballa', '(590) 423-4560', 60);
INSERT INTO employee(emp_id,first_name,last_name,phone,dept_id) VALUES(107, 'Diana',	'Martinez', '(590) 423-5567', 60);
INSERT INTO employee(emp_id,first_name,last_name,phone,dept_id) VALUES(108, 'Nancy',	'Greenberg', '(515) 124-4569', 100);
INSERT INTO employee(emp_id,first_name,last_name,phone,dept_id) VALUES(109, 'Daniel',	'Ledesma',	'(515) 124-4169', 100);
INSERT INTO employee(emp_id,first_name,last_name,phone,dept_id) VALUES(110, 'Julia',	'Chen',		'(515) 124-4269', 100);
INSERT INTO employee(emp_id,first_name,last_name,phone,dept_id) VALUES(111, 'Ismael',	'Sciarra',	'(515) 124-4369', 100);
INSERT INTO employee(emp_id,first_name,last_name,phone,dept_id) VALUES(112, 'José Manuel', 'Urman', '(515) 124-4469', 100);
GO


CREATE TABLE emp_skill
(
	emp_id INT NOT NULL REFERENCES employee(emp_id),
	skill_id INT NOT NULL REFERENCES skill(skill_id),
	PRIMARY KEY(emp_id, skill_id)
);
GO
INSERT INTO emp_skill(emp_id,skill_id) VALUES(100, 202);
INSERT INTO emp_skill(emp_id,skill_id) VALUES(100, 205);
INSERT INTO emp_skill(emp_id,skill_id) VALUES(101, 209);
INSERT INTO emp_skill(emp_id,skill_id) VALUES(101, 210);
INSERT INTO emp_skill(emp_id,skill_id) VALUES(102, 206);
INSERT INTO emp_skill(emp_id,skill_id) VALUES(103, 207);
INSERT INTO emp_skill(emp_id,skill_id) VALUES(103, 211);
INSERT INTO emp_skill(emp_id,skill_id) VALUES(104, 204);
INSERT INTO emp_skill(emp_id,skill_id) VALUES(104, 205);
INSERT INTO emp_skill(emp_id,skill_id) VALUES(105, 205);
INSERT INTO emp_skill(emp_id,skill_id) VALUES(106, 210);
INSERT INTO emp_skill(emp_id,skill_id) VALUES(107, 211);
INSERT INTO emp_skill(emp_id,skill_id) VALUES(108, 210);
INSERT INTO emp_skill(emp_id,skill_id) VALUES(109, 210);
INSERT INTO emp_skill(emp_id,skill_id) VALUES(110, 209);
INSERT INTO emp_skill(emp_id,skill_id) VALUES(111, 208);
INSERT INTO emp_skill(emp_id,skill_id) VALUES(112, 202);
GO


--	VIEWS
CREATE VIEW vw_emp AS
SELECT e.last_name+', '+e.first_name AS name, d.descr AS department, s.descr AS skill
FROM employee e, department d, skill s, emp_skill es
WHERE e.dept_id = d.dept_id AND e.emp_id = es.emp_id AND es.skill_id = s.skill_id
WITH CHECK OPTION;
GO
