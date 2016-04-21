SELECT        e.name, p.descr, d.name AS department, pr.salary, pr.eff_date AS trans_date
FROM          employee AS e INNER JOIN
              payroll AS pr ON e.employee_id = pr.employee_id INNER JOIN
              position AS p ON pr.position_id = p.position_id INNER JOIN
              division AS d ON pr.division_id = d.division_id
WHERE        (pr.eff_date =
                             (SELECT        MAX(eff_date) AS Expr1
                               FROM            payroll
                               WHERE        (employee_id = 50)))