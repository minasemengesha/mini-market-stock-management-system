USE Stock_Management_System;
GO

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
    (300, '2025-01-10', 'Pending', 1, 1),
    (200, '2025-01-12', 'Delivered', 2, 2),
    (150, '2025-01-15', 'Pending', 1, 3),
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

INSERT INTO Report (Report_Content, Report_Generate_Date)
VALUES
    ('Current stock levels for all products including Oreo, KitKat, Lifebuoy, Always, and Closeup.', '2025-01-20'),
    ('Products below minimum stock level: Lifebuoy soap and Closeup toothpaste.', '2025-01-21'),
    ('Daily sales summary based on OUT transactions recorded by the system.', '2025-01-22'),
    ('List of products approaching expiry date within the next three months.', '2025-01-23');