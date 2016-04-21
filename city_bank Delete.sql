use city_bank
go

ALTER TABLE client_account NOCHECK CONSTRAINT ALL --FK__client_ac__clien__2180FB33
DELETE
FROM client
WHERE client.client_id in
	(select ca.client_id
	from client_account ca, account a
	where a.balance < 0.0
	AND a.account_id = ca.account_id)
ALTER TABLE client_account NOCHECK CONSTRAINT ALL --FK__client_ac__clien__2180FB33
GO 

DELETE
FROM client_account
WHERE client_account.account_id in
	(select ca.account_id
	from client_account ca, account a
	where a.balance < 0.0
	AND a.account_id = ca.account_id)
GO