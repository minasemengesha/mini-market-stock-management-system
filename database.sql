CREATE DATABASE Stock_Management_System;
GO

USE Stock_Management_System;
GO


/* =========================================================
                    CREATE TABLES
   ========================================================= */

CREATE TABLE Role (
    Role_Name VARCHAR(50) NOT NULL,
    Role_ID INT IDENTITY(1,1) PRIMARY KEY NOT NULL
);


CREATE TABLE Users (
    User_ID INT IDENTITY(1,1) PRIMARY KEY NOT NULL,
    User_Name VARCHAR(30) NOT NULL UNIQUE,
    User_Password VARCHAR(25) NOT NULL,
    Role_ID INT REFERENCES Role(Role_ID) NOT NULL
);


CREATE TABLE Products_Type (
    Products_Type_ID INT IDENTITY(1,1) PRIMARY KEY NOT NULL,
    Product_Type_Name VARCHAR(50) NOT NULL
);


CREATE TABLE Products (
    Product_ID INT IDENTITY(1,1) PRIMARY KEY NOT NULL,
    Product_Name VARCHAR(30) NOT NULL,
    Product_Type VARCHAR(30) NOT NULL,
    Product_Description VARCHAR(100),
    Cost_Price DECIMAL(10,2) CHECK(Cost_Price > 0),
    Selling_Price DECIMAL(10,2) CHECK(Selling_Price > 0),
    Products_Type_ID INT REFERENCES Products_Type(Products_Type_ID)
);


CREATE TABLE Supplier (
    Supplier_ID INT IDENTITY(1,1) PRIMARY KEY NOT NULL,
    Supplier_First_Name VARCHAR(20) NOT NULL,
    Supplier_Last_Name VARCHAR(20) NOT NULL,
    Supplier_Phone VARCHAR(15) NOT NULL,
    Product_ID INT REFERENCES Products(Product_ID),
    Street VARCHAR(30),
    Post_Number INT
);


CREATE TABLE Stock (
    Stock_ID INT IDENTITY(1,1) PRIMARY KEY NOT NULL,
    Stock_Quantity INT NOT NULL CHECK(Stock_Quantity >= 0),
    Stock_Expire_Date DATE NOT NULL,
    Product_ID INT REFERENCES Products(Product_ID)
);


CREATE TABLE Orders (
    Order_ID INT IDENTITY(1,1) PRIMARY KEY NOT NULL,
    Order_Quantity INT NOT NULL CHECK(Order_Quantity >= 0),
    Order_Date DATE NOT NULL,
    Order_Status VARCHAR(20) NOT NULL,
    Supplier_ID INT REFERENCES Supplier(Supplier_ID),
    Product_ID INT REFERENCES Products(Product_ID)
);


CREATE TABLE Transactions_Type (
    Transaction_Type_ID INT IDENTITY(1,1) PRIMARY KEY NOT NULL,
    Transaction_Type_Name VARCHAR(50)
);


CREATE TABLE Transactions (
    Transaction_ID INT IDENTITY(1,1) PRIMARY KEY NOT NULL,
    Transaction_Type VARCHAR(20) NOT NULL,
    Transaction_Date DATE NOT NULL,
    Transaction_Quantity INT NOT NULL CHECK(Transaction_Quantity >= 0),
    User_ID INT REFERENCES Users(User_ID),
    Product_ID INT REFERENCES Products(Product_ID)
);


CREATE TABLE Report (
    Report_ID INT IDENTITY(1,1) PRIMARY KEY NOT NULL,
    Report_Type VARCHAR(20),
    Report_Content VARCHAR(200),
    Report_Generate_Date DATE,
    RserID INT REFERENCES Users(User_ID)
);


CREATE TABLE Report_Content_Table (
    Report_Content_Table_ID INT IDENTITY(1,1) PRIMARY KEY NOT NULL,
    Report_Content VARCHAR(30),
    Report_ID INT REFERENCES Report(Report_ID)
);


/* =========================================================
                INSERT SAMPLE DATA
   ========================================================= */

/* Roles */

INSERT INTO Role (Role_Name)
VALUES
    ('Owner,Sales,StockManager'),
    ('Admin,updateAccount,manageProdut'),
    ('Accountant,view');


/* Users */

INSERT INTO Users (User_Name, User_Password, Role_ID)
VALUES
    ('KidmuNasr', 'Owner@123', 1),
    ('BereketTeketel', 'admin@124', 2),
    ('NahomDemsse', 'Acc@125', 3);


/* Suppliers */

INSERT INTO Supplier (
    Supplier_First_Name,
    Supplier_Last_Name,
    Supplier_Phone
)
VALUES
    ('Abebe', 'Kebede', '+251911111111'),
    ('Almaz', 'Aschenaki', '+251911001111');


/* Products */

INSERT INTO Products (
    Product_Name,
    Product_Type,
    Product_Description,
    Cost_Price,
    Selling_Price
)
VALUES
    ('Oreo Biscuits', 'Bakery', 'Sweet cream-filled biscuits', 120, 160),
    ('Always Pads', 'Hygiene', 'Sanitary pad pack', 185, 220),
    ('Lifebuoy Soap', 'Hygiene', 'Antibacterial bath soap', 30, 50),
    ('KitKat Chocolate', 'Confectionery', 'Chocolate wafer pack', 185, 220),
    ('Closeup Toothpaste', 'Household', 'Dental care toothpaste', 170, 210);


/* Orders */

INSERT INTO Orders (
    Order_Quantity,
    Order_Date,
    Order_Status,
    Supplier_ID,
    Product_ID
)
VALUES
    (300, '2025-01-10', 'Pending', 1, 1),
    (200, '2025-01-12', 'Delivered', 2, 2),
    (150, '2025-01-15', 'Pending', 1, 3),
    (170, '2025-01-18', 'Cancelled', 2, 4);


/* Transactions */

INSERT INTO Transactions (
    Transaction_Type,
    Transaction_Date,
    Transaction_Quantity,
    Product_ID
)
VALUES
    ('IN',  '2025-01-10', 300, 1),
    ('OUT', '2025-01-11', 40, 1),
    ('IN',  '2025-01-12', 200, 2),
    ('OUT', '2025-01-13', 60, 2),
    ('OUT', '2025-01-22', 25, 3),
    ('IN',  '2025-01-12', 150, 3),
    ('OUT', '2025-01-16', 35, 2);


/* Reports */

INSERT INTO Report (
    Report_Content,
    Report_Generate_Date
)
VALUES
    (
        'Current stock levels for all products including Oreo, KitKat, Lifebuoy, Always, and Closeup.',
        '2025-01-20'
    ),
    (
        'Products below minimum stock level: Lifebuoy soap and Closeup toothpaste.',
        '2025-01-21'
    ),
    (
        'Daily sales summary based on OUT transactions recorded by the system.',
        '2025-01-22'
    ),
    (
        'List of products approaching expiry date within the next three months.',
        '2025-01-23'
    );


/* =========================================================
   3. PRACTICE COMMANDS
   ========================================================= */

/* ALTER */

ALTER TABLE Products
    ALTER COLUMN Product_Type VARCHAR(90) NOT NULL;


/* UPDATE */

UPDATE Supplier
SET
    Supplier_First_Name = 'Bekalu',
    Supplier_Last_Name = 'Ashenafi'
WHERE
    Supplier_Phone = '+251911111111'
    AND Supplier_First_Name = 'Abebe';


/* SELECT */

SELECT Product_ID
FROM Products
WHERE Product_Name = 'Always Pads';


/* DELETE */

DELETE FROM Transactions
WHERE Product_ID = 2;


/* LIKE */

SELECT *
FROM Products
WHERE Product_Name LIKE 'k%';


/* BETWEEN */

SELECT Stock_ID
FROM Stock
WHERE Stock_ID BETWEEN 120 AND 130;


/* IN */

SELECT Transaction_Type
FROM Transactions
WHERE Transaction_Quantity IN (100, 200, 300);


/* IS NULL */

SELECT Order_Date
FROM Orders
WHERE Order_Status IS NULL;


/* AND / OR / IN / LIKE / != */

SELECT *
FROM Transactions
WHERE
    (Product_ID = 4 OR User_ID = 4)
    OR
    (
        Transaction_Quantity IN (150, 200, 40)
        AND Transaction_Type LIKE 'I%'
    )
    AND Transaction_Date != '2025-01-12';


/* EXISTS */

SELECT Transaction_Quantity
FROM Transactions
WHERE EXISTS (
    SELECT Transaction_Quantity
    FROM Transactions
    WHERE Transaction_Quantity > 90
);


/* ALL
   Original query referred to Transaction_Quantity in Stock.
   Stock table contains Stock_Quantity.
*/

SELECT *
FROM Transactions
WHERE Transaction_Quantity > ALL (
    SELECT Stock_Quantity
    FROM Stock
    WHERE Stock_Quantity <= 90
);


/* ANY */

SELECT *
FROM Transactions
WHERE Transaction_Quantity > ANY (
    SELECT Transaction_Quantity
    FROM Transactions
    WHERE Product_ID > 3
);


/* COUNT */

SELECT COUNT(*)
FROM Orders
WHERE Order_Status = 'pending';


/* SUM */

SELECT SUM(Order_Quantity)
FROM Orders;


/* AVG */

SELECT AVG(Order_Quantity)
FROM Orders;


/* MAX */

SELECT MAX(Order_Quantity)
FROM Orders;


/* MIN */

SELECT MIN(Order_Quantity)
FROM Orders;


/* UPDATE USING SUBQUERY */

UPDATE Products
SET Selling_Price = 199
WHERE Selling_Price < (
    SELECT AVG(Selling_Price)
    FROM Products
);


/* INNER JOIN
   Corrected:
   p.Product_ID = o.Product_ID
*/

SELECT
    p.Product_ID,
    p.Product_Name,
    p.Product_Type,
    p.Product_Description,
    p.Cost_Price,
    p.Selling_Price
FROM Products p
JOIN Orders o
    ON p.Product_ID = o.Product_ID;


/* LEFT OUTER JOIN */

SELECT *
FROM Products p
LEFT OUTER JOIN Orders o
    ON p.Product_ID = o.Product_ID;


/* RIGHT OUTER JOIN */

SELECT *
FROM Products p
RIGHT OUTER JOIN Orders o
    ON p.Product_ID = o.Product_ID;


/* FULL OUTER JOIN */

SELECT *
FROM Products p
FULL OUTER JOIN Orders o
    ON p.Product_ID = o.Product_ID;


/* ORDER BY */

SELECT *
FROM Supplier
ORDER BY Supplier_First_Name;


SELECT *
FROM Products
ORDER BY Selling_Price;


/* GROUP BY */

SELECT
    Cost_Price,
    SUM(Selling_Price)
FROM Products
GROUP BY Cost_Price;


SELECT
    Order_Status,
    SUM(Order_Quantity) AS Total_Quantity
FROM Orders
GROUP BY Order_Status;


/* GROUP BY + HAVING */

SELECT
    Order_Status,
    SUM(Order_Quantity) AS Total_Quantity
FROM Orders
GROUP BY Order_Status
HAVING SUM(Order_Quantity) > 150;


/* ADD PRODUCT EXPIRY DATE */

ALTER TABLE Products
ADD Product_Expiry_Date DATE;


/* =========================================================
                         THE END
   ========================================================= */