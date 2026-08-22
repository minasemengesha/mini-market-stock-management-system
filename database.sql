CREATE DATABASE Stock_Management_System;
    USE Stock_Management_System
        CREATE TABLE Role (
            Role_Name VARCHAR(50) NOT NULL,
            Role_ID INT IDENTITY(1,1) PRIMARY KEY NOT NULL
                );
        CREATE TABLE Users (
            User_ID INT IDENTITY(1,1) PRIMARY KEY NOT NULL,
            User_Name VARCHAR(30) NOT NULL UNIQUE,
            User_Password VARCHAR(20) NOT NULL,
            Role_ID INT REFERENCES Role(Role_ID) NOT NULL
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
        CREATE TABLE Products_Type (
            Products_Type_ID INT IDENTITY(1,1) PRIMARY KEY NOT NULL,
            Product_Type_Name VARCHAR(50) NOT NULL,
                );
        CREATE TABLE Products (
            Product_ID INT IDENTITY(1,1) PRIMARY KEY NOT NULL,
            Product_Name VARCHAR(30) NOT NULL,
            Product_Type VARCHAR(30) NOT NULL,
            Product_Description VARCHAR(100),
            Cost_Price DECIMAL(10,2) CHECK(Cost_Price>0),
            Selling_Price DECIMAL(10,2) CHECK(Selling_Price>0),
            Products_Type_ID INT REFERENCES Products_Type(Products_Type_ID)
                );
        CREATE TABLE Stock (
            Stock_ID INT Identity(1,1) PRIMARY KEY NOT NULL,
            Stock_Quantity INT NOT NULL CHECK(Stock_Quantity>=0),
            Stock_Expire_Date DATE NOT NULL,
            Product_ID INT REFERENCES Products(Product_ID)
                );
        CREATE TABLE Orders (
            Order_ID INT IDENTITY(1,1) PRIMARY KEY NOT NULL,
            Order_Quantity INT NOT NULL CHECK(Order_Quantity>=0),
            Order_Date DATE NOT NULL,
            Order_Status VARCHAR(20) NOT NULL,
            Supplier_ID INT REFERENCES Supplier(Supplier_ID),
            Product_ID INT REFERENCES Products(Product_ID)
                );
        CREATE TABLE Transactions_Type (
            Transaction_Type_ID INT IDENTITY(1,1) PRIMARY KEY NOT NULL,
            Transaction_Type_Name varchar(50)
                );
        CREATE TABLE Transactions (
            Transaction_ID INT IDENTITY(1,1) PRIMARY KEY NOT NULL,
            Transaction_Type VARCHAR(20) NOT NULL,
            Transaction_Date DATE NOT NULL,
            Transaction_Quantity INT NOT NULl CHECK(Transaction_Quantity>=0),
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
        CREATE TABLE Report_Content_Table(
            Report_Content_Table_ID INT IDENTITY(1,1) PRIMARY KEY NOT NULL,
            Report_Content VARCHAR(30),
            Report_ID INT REFERENCES Report(Report_ID)
                );
        /* I Ordered To Add Some Sample In This Project*/
INSERT INTO Role (Role_Name) 
    VALUES  
        ('Owner,Sales,StockManager'),
        ('Admin,updateAccount,manageProdut'),
        ('Accountant,view');
INSERT INTO Users (User_Name, User_Password, Role_ID) 
    VALUES
        ('KidmuNasr', 'Owner@123', 1),
        ('BereketTeketel', 'admin@124', 2),
        ('NahomDemsse', 'Acc@125', 3);
INSERT INTO Supplier (Supplier_First_Name, Supplier_Last_Name, Supplier_Phone)
    VALUES
        ('Abebe', 'Kebede', '+251911111111'),
        ('Almaz', 'Aschenaki', '+251911001111');
INSERT INTO Products (Product_Name, Product_Type, Product_Description, Cost_Price, Selling_Price)
    VALUES
        ('Oreo Biscuits', 'Bakery', 'Sweet cream-filled biscuits', 120, 160),
        ('Always Pads', 'Hygiene', 'Sanitary pad pack', 185, 220),
        ('Lifebuoy Soap', 'Hygiene', 'Antibacterial bath soap', 30, 50),
        ('KitKat Chocolate', 'Confectionery', 'Chocolate wafer pack', 185, 220),
        ('Closeup Toothpaste', 'Household', 'Dental care toothpaste', 170, 210);
INSERT INTO Orders (Order_Quantity, Order_Date, Order_Status, Supplier_ID, Product_ID)
    VALUES      
        (300, '2025-01-10', 'Pending', 1, 1);
        (200, '2025-01-12', 'Delivered', 2, 2);
        (150, '2025-01-15', 'Pending', 1, 3);
        (170, '2025-01-18', 'Cancelled', 2, 4);
INSERT INTO Transactions (Transaction_Type, Transaction_Date, Transaction_Quantity, Product_ID)
    VALUES
        ('IN', '2025-01-10', 300, 1),
        ('OUT', '2025-01-11', 40, 1),
        ('IN', '2025-01-12', 200, 2),
        ('OUT', '2025-01-13', 60, 2),
        ('OUT', '2025-01-22', 25, 3),
        ('IN', '2025-01-12', 150, 3),
        ('OUT', '2025-01-16', 35, 2);
INSERT INTO Report ( Report_Content, Report_Generate_Date)
    VALUES
        ('Current stock levels for all products including Oreo, KitKat, Lifebuoy, Always, and Closeup.', '2025-01-20'),
        ('Products below minimum stock level: Lifebuoy soap and Closeup toothpaste.', '2025-01-21'),
        ('Daily sales summary based on OUT transactions recorded by the system.', '2025-01-22'),
        ('List of products approaching expiry date within the next three months.', '2025-01-23');
                    /* I Ordered To Practice The below Commands In This Project*/
    ALTER TABLE Products
        ALTER column Product_Type VARCHAR (90) NOT NULL;
    UPDATE Supplier
        SET supplier_First_Name = 'Bekalu', Supplier_Last_Name = 'Ashenafi' 
            WHERE Supplier_Phone = '+251911111111' 
                AND Supplier_First_Name = 'Abebe';
    SELECT Product_ID 
        FROM Products 
            WHERE Product_Name = 'Always Pads';
    DELETE 
        FROM Transactions 
            WHERE Product_ID = '2';
    SELECT * 
        FROM Products 
            WHERE Product_Name LIKE 'k%';
    SELECT Stock_ID 
        FROM Stock 
            WHERE Stock_ID 
                BETWEEN 120 AND 130;
    SELECT Transaction_Type 
        FROM Transactions 
            WHERE Transaction_Quantity IN (100,200,300);
    SELECT Order_Date 
        FROM Orders 
            WHERE Order_Status IS NULL;
    SELECT * 
        FROM Transactions 
            WHERE (Product_ID='4' OR User_ID='4') 
                OR (Transaction_Quantity IN(150,200,40) 
                    AND Transaction_Type LIKE 'I%') 
                        AND Transaction_Date != '2025-01-12';
    SELECT Transaction_Quantity 
        FROM Transactions 
            WHERE EXISTS(SELECT Transaction_Quantity 
                FROM Transactions 
                    WHERE Transaction_Quantity > 90);
    SELECT * 
        FROM Transactions 
            WHERE Transaction_Quantity > All (SELECT Transaction_Quantity 
                FROM Stock 
                    WHERE Transaction_Quantity <=90);
    SELECT * 
        FROM Transactions 
            WHERE Transaction_Quantity >Any (SELECT Transaction_Quantity 
                FROM Transactions WHERE Product_ID > 3);
    SELECT COUNT (*) 
        FROM Orders 
            WHERE Order_Status = 'pending';
    SELECT SUM (Order_Quantity) 
        FROM Orders;
    SELECT AVG (Order_Quantity) 
        FROM Orders;
    SELECT MAX (Order_Quantity) 
        FROM Orders;
    SELECT MIN (Order_Quantity) 
        FROM Orders;
    UPDATE Products 
        SET Selling_Price = 199 
            WHERE Selling_Price < (SELECT AVG (Selling_Price) FROM Products)
    SELECT p.Product_ID, p.Product_Name, p.Product_Type, p.Product_Description, Cost_Price, Selling_Price 
        FROM Products p 
            JOIN Orders o 
                ON p.Product_ID = p.Product_ID;
    SELECT * 
        FROM Products p 
            LEFT OUTER JOIN Orders o 
                ON p.Product_ID = o.Product_ID;
    SELECT * 
        FROM Products p 
            RIGHT OUTER JOIN Orders o 
                ON p.Product_ID = o.Product_ID;
    SELECT * 
        FROM Products p 
            FULL OUTER JOIN Orders o 
                ON p.Product_ID = o.Product_ID;
    SELECT * 
            FROM Supplier 
                ORDER BY Supplier_First_Name;
    SELECT * 
        FROM Products 
            ORDER BY Selling_Price;
    SELECT Cost_Price, SUM (Selling_Price) 
        FROM Products 
            GROUP BY Cost_Price;
    SELECT Order_Status, SUM (Order_Quantity) 
        AS Total_Quantity 
            FROM Orders 
                GROUP BY Order_Status;
    SELECT Order_Status, SUM (Order_Quantity) 
        AS Total_Quantity 
            FROM Orders 
                GROUP BY Order_Status 
                    HAVING SUM (Order_Quantity) > 150;
                                        /* THE END*/
                                        