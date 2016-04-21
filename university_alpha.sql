USE master;
GO

IF EXISTS (SELECT * FROM sysdatabases WHERE NAME='university')
BEGIN
	RAISERROR('Dropping university',0,1)
	DROP DATABASE university;
END
GO

CREATE DATABASE university;
GO

USE university;
GO

IF DB_NAME()<>'university'
BEGIN
	RAISERROR('Error to create university database',22,127) WITH log
	DROP DATABASE university;
END
GO

CREATE TABLE professor
(
	teacher_id INT NOT NULL PRIMARY KEY REFERENCES professor_descr(teacher_id),
	course_id VARCHAR(6) 
);
GO

CREATE TABLE departement
(
	department_id CHAR(2) NOT NULL PRIMARY KEY,
	descr VARCHAR(32) NOT NULL
);
GO

CREATE TABLE professor_descr
(
	teacher_id INT NOT NULL PRIMARY KEY,
	department_id CHAR(2) NOT NULL REFERENCES department(department_id),
	name VARCHAR(32) NOT NULL,
	addressz VARCHAR(32) NOT NULL,
	telephone VARCHAR(16),
	email VARCHAR(32),
	salary MONEY NOT NULL
);
GO

CREATE TABLE classroom
(
	classroom_id INT NOT NULL PRIMARY KEY,
	seats INT NOT NULL,
	is_projector CHAR NOT NULL
);
GO

CREATE TABLE course
(

);
GO

CREATE TABLE period
(

);
GO

CREATE TABLE period_time
(

);
GO

CREATE TABLE schedule
(

);
GO

