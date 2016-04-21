USE master;
GO

IF EXISTS (SELECT * FROM sysdatabases WHERE NAME='university_sql_import')
BEGIN
	RAISERROR('Dropping university_sql_import',0,1)
	DROP DATABASE university_sql_import;
END
GO

CREATE DATABASE university_sql_import;
GO

USE university_sql_import;
GO

IF DB_NAME()<>'university_sql_import'
BEGIN
	RAISERROR('Error to create university_sql_import database',22,127) WITH log
	DROP DATABASE university_sql_import;
END
GO

-------------------------------------------------------TABLES
CREATE TABLE classroom
(
	classroom_id INT NOT NULL PRIMARY KEY IDENTITY,
	descr INT NOT NULL,
	seat_count INT NOT NULL,
	has_projector BIT NOT NULL,
	building CHAR NOT NULL
);
GO
INSERT INTO classroom(descr,seat_count,has_projector,building) VALUES(101,22,1,'A');
INSERT INTO classroom(descr,seat_count,has_projector,building) VALUES(102,20,1,'A');
INSERT INTO classroom(descr,seat_count,has_projector,building) VALUES(101,10,0,'B');
GO

CREATE TABLE course
(
	course_id INT NOT NULL PRIMARY KEY IDENTITY,
	code VARCHAR(5) NOT NULL,
	descr VARCHAR(32) NOT NULL
);
GO
INSERT INTO course(code,descr) VALUES('ABP01','Programming I');
INSERT INTO course(code,descr) VALUES('ICS01','Information System I');
INSERT INTO course(code,descr) VALUES('ICS02','Information System II');
INSERT INTO course(code,descr) VALUES('CEP01','Signal Processing');
INSERT INTO course(code,descr) VALUES('ICG02','Communication Systems');
GO

CREATE TABLE department
(
	department_id INT NOT NULL PRIMARY KEY IDENTITY,
	descr VARCHAR(32) NOT NULL
);
GO
INSERT INTO department(descr) VALUES('Electrical Engineering');
INSERT INTO department(descr) VALUES('Computer Science');
INSERT INTO department(descr) VALUES('Chemistry');
INSERT INTO department(descr) VALUES('Math');
INSERT INTO department(descr) VALUES('Civil Engineering');
INSERT INTO department(descr) VALUES('Management');
INSERT INTO department(descr) VALUES('Arts');
GO

CREATE TABLE period
(
	period_id INT NOT NULL PRIMARY KEY IDENTITY,
	descr VARCHAR(16) NOT NULL,
	begin_date DATE NOT NULL,
	end_date DATE NOT NULL
);
GO
INSERT INTO period(descr,begin_date,end_date) VALUES('Winter 2014','10-1-2014','11-4-2014');
INSERT INTO period(descr,begin_date,end_date) VALUES('Spring 2014','15-4-2014','14-8-2014');
GO

CREATE TABLE professor
(
	professor_id INT NOT NULL PRIMARY KEY IDENTITY,
	last_name VARCHAR(32) NOT NULL,
	first_name VARCHAR(32) NOT NULL,
	department_id INT NOT NULL REFERENCES department(department_id) ON DELETE CASCADE,
	username VARCHAR(32) NOT NULL,
	user_pass VARCHAR(32) NOT NULL
);
GO
INSERT INTO professor(last_name,first_name,department_id,username,user_pass) VALUES('Orozco',	'Peter',1,	'pete',	'asd55');
INSERT INTO professor(last_name,first_name,department_id,username,user_pass) VALUES('Smith',	'Mary',	1,	'mary',	'hola2000');
INSERT INTO professor(last_name,first_name,department_id,username,user_pass) VALUES('Ledesma',	'Sergio',2,	'sergio','2200');
INSERT INTO professor(last_name,first_name,department_id,username,user_pass) VALUES('Peavier',	'John',	6,	'john',	'bye456');
GO

CREATE TABLE time_block
(
	time_block_id INT NOT NULL PRIMARY KEY IDENTITY,
	descr VARCHAR(16) NOT NULL,
	Monday BIT NOT NULL,
	Tuesday BIT NOT NULL,
	Wednesday BIT NOT NULL,
	Thursday BIT NOT NULL,
	Friday BIT NOT NULL,
	Saturday BIT NOT NULL,
);
GO
INSERT INTO time_block(descr,Monday,Tuesday,Wednesday,Thursday,Friday,Saturday) VALUES('Mon-Wed-Fri',1,0,1,0,1,0);
INSERT INTO time_block(descr,Monday,Tuesday,Wednesday,Thursday,Friday,Saturday) VALUES('Tue-Thu'	,0,1,0,1,0,0);
GO

CREATE TABLE schedule
(
	schedule_id INT NOT NULL PRIMARY KEY IDENTITY,
	professor_id INT NOT NULL REFERENCES professor(professor_id) ON DELETE CASCADE,
	course_id INT NOT NULL REFERENCES course(course_id) ON DELETE CASCADE,
	period_id INT NOT NULL REFERENCES period(period_id) ON DELETE CASCADE,
	time_block_id INT NOT NULL REFERENCES time_block(time_block_id) ON DELETE CASCADE,
	classroom_id INT NOT NULL REFERENCES classroom(classroom_id) ON DELETE CASCADE
);
GO

--_____________________________________________________VIEWS
CREATE VIEW vw_Classroom AS
SELECT classroom_id,
		descr,
		seat_count,
		REPLACE(REPLACE(has_projector, '1','Yes'), '0','No')  AS has_projector,
		building
FROM classroom;
GO

CREATE VIEW vw_Course AS
SELECT	course_id,
		code,
		descr
FROM course;
GO

CREATE VIEW vw_Department AS
SELECT	department_id,
		descr
FROM department;
GO

CREATE VIEW vw_Period AS
SELECT	period_id,
		descr,
		begin_date,
		end_date
FROM period;
GO

CREATE VIEW vw_Professor AS
SELECT	p.professor_id,
		p.first_name+' '+last_name AS name, 
		p.department_id,
		d.descr AS department_descr,
		p.username,
		p.user_pass
FROM professor p, department d
WHERE p.department_id=d.department_id;
GO

CREATE VIEW vw_Time_block AS
SELECT time_block_id,
		descr,
		REPLACE(REPLACE(Monday,		'1','Yes'), '0','No')  AS Monday,
		REPLACE(REPLACE(Tuesday,	'1','Yes'), '0','No')  AS Tuesday,
		REPLACE(REPLACE(Wednesday,	'1','Yes'), '0','No')  AS Wednesday,
		REPLACE(REPLACE(Thursday,	'1','Yes'), '0','No')  AS Thursday,
		REPLACE(REPLACE(Friday,		'1','Yes'), '0','No')  AS Friday,
		REPLACE(REPLACE(Saturday,	'1','Yes'), '0','No')  AS Saturday
FROM time_block;
GO

CREATE VIEW vw_Schedule AS
SELECT s.schedule_id,
		s.professor_id,
		s.course_id,
		s.period_id,
		s.time_block_id,
		s.classroom_id,
		prof.name AS professor_name,
		c.code AS course_code,
		c.descr AS course_name,
		p.descr AS period,
		tb.descr AS time_block,
		cr.descr AS classroom,
		cr.building AS classroom_building
FROM schedule s,
		vw_Professor prof,
	    vw_Course c,
		vw_Period p,
		vw_Time_block tb,
		vw_Classroom cr
WHERE s.professor_id=prof.professor_id AND
		s.course_id=c.course_id AND
		s.period_id=p.period_id AND
		s.time_block_id=tb.time_block_id AND
		s.classroom_id=cr.classroom_id;
GO