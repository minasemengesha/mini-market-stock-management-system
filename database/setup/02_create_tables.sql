USE Stock_Management_System;
GO

CREATE TABLE Role (
    Role_Name VARCHAR(50) NOT NULL,
    Role_ID INT IDENTITY(1,1) PRIMARY KEY NOT NULL
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
    Cost_Price DECIMAL(10,2) CHECK (Cost_Price > 0),
    Selling_Price DECIMAL(10,2) CHECK (Selling_Price > 0),
    Products_Type_ID INT REFERENCES Products_Type(Products_Type_ID)
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

CREATE TABLE Stock (
    Stock_ID INT IDENTITY(1,1) PRIMARY KEY NOT NULL,
    Stock_Quantity INT NOT NULL CHECK (Stock_Quantity >= 0),
    Stock_Expire_Date DATE NOT NULL,
    Product_ID INT REFERENCES Products(Product_ID)
);

CREATE TABLE Orders (
    Order_ID INT IDENTITY(1,1) PRIMARY KEY NOT NULL,
    Order_Quantity INT NOT NULL CHECK (Order_Quantity >= 0),
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
    Transaction_Quantity INT NOT NULL CHECK (Transaction_Quantity >= 0),
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