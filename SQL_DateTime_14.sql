SELECT        name, birth_date AS age, 
		DATEPART(year, GETDATE()) AS year_t, 
		DATENAME(year, birth_date) AS year_n, 
		DATEPART(year, GETDATE()) - DATENAME(year, birth_date) AS year_m
FROM            employee