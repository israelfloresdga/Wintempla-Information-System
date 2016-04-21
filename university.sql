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
	teacher_id INT NOT NULL PRIMARY KEY,
	name VARCHAR(32) NOT NULL,
	addressz VARCHAR(32) NOT NULL,
	telephone VARCHAR(16),
	email VARCHAR(32),
	salary MONEY NOT NULL,
	course VARCHAR(32) 
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
	course_id VARCHAR(6) NOT NULL PRIMARY KEY,
	name VARCHAR(32) NOT NULL,
	credits INT NOT NULL,
	descr VARCHAR(64) NOT NULL
);
GO

CREATE TABLE period
(
	period_id CHAR NOT NULL PRIMARY KEY,
	name VARCHAR(12) NOT NULL,
	start_date SMALLDATETIME NOT NULL,
	end_date SMALLDATETIME NOT NULL
);
GO

CREATE TABLE time_block
(
	time_block_id INT NOT NULL PRIMARY KEY,
	isMonday BIT NOT NULL,
	isTuesday BIT NOT NULL,
	isWednesday BIT NOT NULL,
	isThursday BIT NOT NULL,
	isFriday BIT NOT NULL,
	isSaturday BIT NOT NULL,
	isSunday BIT NOT NULL,
	timez TIME NOT NULL,
);
GO
INSERT INTO time_block(time_block_id,isMonday,isTuesday,isWednesday,isThursday,isFriday,isSaturday,isSunday,timez) VALUES(1,1,1,1,1,1,1,1,'10:00AM');

CREATE TABLE schedule
(
	course_id VARCHAR(6) NOT NULL,
	time_block_id INT NOT NULL PRIMARY KEY,
);
GO

