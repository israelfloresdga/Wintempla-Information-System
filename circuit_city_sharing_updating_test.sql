USE master;
GO

IF EXISTS (SELECT * FROM sysdatabases WHERE NAME='circuit_city_sharing')
BEGIN
	RAISERROR('Updating circuit_city_sharing',0,1)
END
GO

USE circuit_city_sharing;
GO

ALTER TABLE client
ADD telephone INT NULL