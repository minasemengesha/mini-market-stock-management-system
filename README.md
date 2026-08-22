# Stock Management System

A console-based Stock Management System built in **C++** with an **SQL Server** backend, developed for *Kidemu Mini Market* as a university software engineering project (Wachemo University — Dept. of Software Engineering) for course Fundamentals of software enginarining, Fundamentals of Database and Computer Programming in C++.

## 📌 Overview

Kidemu Mini Market previously tracked products, stock, sales, and expiry dates manually using notebooks — a process that was slow and error-prone. This system replaces that manual process with a database-driven application that:

- Stores all product and stock information in a structured database
- Automatically updates stock levels after each sale
- Sends alerts for **low stock** and **near-expiry** products
- Supports **role-based access** for three user types: **Admin**, **Owner**, and **Accountant**
- Generates sales, income, and cost reports

## ✨ Features

- 🔐 User authentication and role-based access control
- 📦 Add / update / delete products
- 📊 Add / update / delete stock records
- 🧾 Record sales and auto-update inventory
- ⚠️ Low-stock and expiry alerts
- 📈 Income & cost tracking for the Accountant role
- 🗂️ Report generation and stock viewing

## 🏗️ System Design

The system was designed using standard UML modeling, including:

- Use Case Diagrams
- Sequence Diagrams
- Activity Diagrams
- State Chart Diagrams
- Class Diagrams
- ER Diagram (Entity-Relationship)

Full design documentation, including database normalization (1NF–3NF) and system architecture, is available in [`docs/Stock-Management-System-Document.pdf`](docs/Stock-Management-System-Document.pdf).

## 🛠️ Tech Stack

| Component            | Technology            |
|-----------------------|------------------------|
| Language              | C++                   |
| Database              | SQL Server             |
| IDE / Editor          | Code::Blocks           |
| Modeling Tool         | Enterprise Architect (UML) |
| Development OS        | Windows                |

## 📂 Project Structure

```
stock-management-system/
├── docs/            # Full project documentation (PDF) and design diagrams
├── src/             # C++ source code
├── database/        # SQL scripts (schema, sample data)
└── screenshots/      # UI/console screenshots
```

## ⚙️ Getting Started

### Prerequisites
- A C++ compiler (e.g. g++ / MinGW, or Code::Blocks)
- SQL Server (or update the connection logic if using another DBMS)

### Setup
1. Clone the repository:
   ```bash
   git clone https://github.com/<your-username>/stock-management-system.git
   cd stock-management-system
   ```
2. Set up the database:
   - Open `database/schema.sql` in SQL Server Management Studio (or your DB tool)
   - Run the script to create the required tables
3. Update the database connection details in the C++ source (host, username, password) to match your local setup.
4. Compile and run:
   ```bash
   g++ src/*.cpp -o stock_management
   ./stock_management
   ```

## 👥 User Roles

| Role        | Permissions                                              |
|-------------|-----------------------------------------------------------|
| Admin       | Full access — manage users, products, and stock            |
| Owner       | Add/update products & stock, record sales, view reports    |
| Accountant  | View income and cost reports only (no stock modification)  |

## 📄 Documentation

The complete project report — including problem statement, feasibility analysis, requirement analysis, database design, and system design — is available in the [`docs`](docs) folder.

## Screenshots

### Commit History
![Commit History](images/commit-history.png)
### Main Menu
![Main Menu](images/main-menu.png)
### Add Product
![Add Product](images/add-product.png)
### View Products
![View Products](images/view-products.png)
### Search Product
![Search Product](images/search-product.png)
### Update Product
![Update Product](images/update-product.png)
### Delete Product
![Delete Product](images/delete-product.png)
### Reports
![Reports](images/reports.png)

## 👨‍💻 Contributors

- Minase Mengesha
- Ruhama Alemu
- Fetiha Oumer
- Eyobed Solomon
- Yamilaksira Ashenafi

*Department of Software Engineering, College of Engineering and Technology, Wachemo University*

## 📜 License

This project is licensed under the MIT License — see the [LICENSE](LICENSE) file for details.