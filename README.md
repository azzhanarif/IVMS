# Inventory Management System

A console-based Inventory Management System built in C++, designed to help a small business manage products, track stock, and record sales — all with persistent file-based storage.

## Features

### Product Management
- Add, edit, and remove inventory items
- Duplicate ID detection and input validation

### Inventory Tracking
- View all items in a formatted table
- Search products by ID
- Low-stock detection and alerts
- Restock existing items

### Sales Management
- Record sales with real-time stock deduction
- Apply optional per-item discounts
- Auto-generated bill totals

### Reports & Statistics
- View complete sales history
- Identify top-selling product(s)
- Calculate total revenue generated

### Persistence
- Inventory and sales data are saved to `products.txt` and `sales.txt`
- Data automatically loads on startup and saves after every transaction

## Tech Stack
- **Language:** C++
- **Concepts used:** Structs, file I/O (`fstream`), arrays, input validation loops, modular function design

## How to Run

```bash
g++ main.cpp -o inventory
./inventory
```

> Note: Uses `system("cls")`, so it's designed for Windows. Replace with `system("clear")` for Linux/macOS.

## Project Structure

The program is organized into clearly separated modules:
- File I/O (save/load for products and sales)
- Product management (add/remove/edit)
- Inventory tracking (search/view/restock/low-stock alerts)
- Sales management (recording sales with discounts)
- Reports & statistics
- Menu-driven navigation system

## Contributors
- Azhan
- Mufleh

## License
Feel free to use or extend this project for learning purposes.
