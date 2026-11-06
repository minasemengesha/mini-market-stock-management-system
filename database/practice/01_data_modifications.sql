USE Stock_Management_System;
GO

ALTER TABLE Products
ALTER COLUMN Product_Type VARCHAR(90) NOT NULL;

UPDATE Supplier
SET Supplier_First_Name = 'Bekalu',
    Supplier_Last_Name = 'Ashenafi'
WHERE Supplier_Phone = '+251911111111'
  AND Supplier_First_Name = 'Abebe';

DELETE FROM Transactions
WHERE Product_ID = '2';

UPDATE Products
SET Selling_Price = 199
WHERE Selling_Price < (
    SELECT AVG(Selling_Price)
    FROM Products
);