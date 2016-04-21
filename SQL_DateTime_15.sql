SELECT        employee_id, 
		CAST(DATEDIFF(day, contract_date, '2007-12-31') * 7 AS MONEY) AS fund
FROM            employee