USE Stock_Management_System;
GO

-- Product and stock lookups
SELECT Product_ID
FROM Products
WHERE Product_Name = 'Always Pads';

SELECT *
FROM Products
WHERE Product_Name LIKE 'k%';

SELECT Stock_ID
FROM Stock
WHERE Stock_ID BETWEEN 120 AND 130;

SELECT Transaction_Type
FROM Transactions
WHERE Transaction_Quantity IN (100, 200, 300);

SELECT Order_Date
FROM Orders
WHERE Order_Status IS NULL;

SELECT *
FROM Transactions
WHERE (Product_ID = '4' OR User_ID = '4')
   OR (Transaction_Quantity IN (150, 200, 40)
       AND Transaction_Type LIKE 'I%')
      AND Transaction_Date != '2025-01-12';

-- Transaction queries
SELECT Transaction_Quantity
FROM Transactions
WHERE EXISTS (
    SELECT Transaction_Quantity
    FROM Transactions
    WHERE Transaction_Quantity > 90
);

SELECT *
FROM Transactions
WHERE Transaction_Quantity > ALL (
    SELECT Stock_Quantity
    FROM Stock
    WHERE Stock_Quantity <= 90
);

SELECT *
FROM Transactions
WHERE Transaction_Quantity > ANY (
    SELECT Transaction_Quantity
    FROM Transactions
    WHERE Product_ID > 3
);

-- Order and product summaries
SELECT COUNT(*)
FROM Orders
WHERE Order_Status = 'pending';

SELECT SUM(Order_Quantity)
FROM Orders;

SELECT AVG(Order_Quantity)
FROM Orders;

SELECT MAX(Order_Quantity)
FROM Orders;

SELECT MIN(Order_Quantity)
FROM Orders;

SELECT AVG(Selling_Price)
FROM Products;

-- Product and order queries
SELECT p.Product_ID, p.Product_Name, p.Product_Type, p.Product_Description,
       p.Cost_Price, p.Selling_Price
FROM Products AS p
JOIN Orders AS o
    ON p.Product_ID = o.Product_ID;

SELECT *
FROM Products AS p
LEFT OUTER JOIN Orders AS o
    ON p.Product_ID = o.Product_ID;

SELECT *
FROM Products AS p
RIGHT OUTER JOIN Orders AS o
    ON p.Product_ID = o.Product_ID;

SELECT *
FROM Products AS p
FULL OUTER JOIN Orders AS o
    ON p.Product_ID = o.Product_ID;

-- Sorted results
SELECT *
FROM Supplier
ORDER BY Supplier_First_Name;

SELECT *
FROM Products
ORDER BY Selling_Price;

-- Grouped totals
SELECT Cost_Price, SUM(Selling_Price)
FROM Products
GROUP BY Cost_Price;

SELECT Order_Status, SUM(Order_Quantity) AS Total_Quantity
FROM Orders
GROUP BY Order_Status;

SELECT Order_Status, SUM(Order_Quantity) AS Total_Quantity
FROM Orders
GROUP BY Order_Status
HAVING SUM(Order_Quantity) > 150;
