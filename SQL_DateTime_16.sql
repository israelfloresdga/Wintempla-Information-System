SELECT        name, DATEPART(year, GETDATE()) - DATENAME(year, birth_date) AS year
FROM            employee
WHERE        (DATEPART(year, GETDATE()) - DATENAME(year, birth_date) > 50)