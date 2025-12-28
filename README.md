# 🏦 S7S-Bank-System (C++)

A complete **Console-Based Bank Management System** built using **C++**, designed to simulate real-world banking operations with persistent data storage using files.

This project reflects a solid understanding of **C++ fundamentals**, focusing on clean logic, file handling, and structured programming.

---

## 🚀 Features

### 👤 Client Management
- Add New Clients
- Update Existing Client Information
- Delete Clients (Soft Delete using MarkForDelete)
- Find Client by Account Number
- Display All Clients in a Table Format

### 💰 Transactions
- Deposit Money
- Withdraw Money (with full balance validation)
- View Total Balances of All Clients

### 📂 File Handling
- Persistent storage using text files
- Automatic loading and saving of client data
- Safe update and delete operations

---

## 🛡️ Input Validation

The system ensures:
- No program crashes due to invalid input
- No characters instead of numbers
- No negative or zero deposit values
- Withdrawals cannot exceed the available balance
- Confirmation before critical transactions

---

## 🧠 Concepts & Techniques Used

- `struct` for client data modeling
- `enum` for menu and transaction options
- File I/O using `fstream`
- `vector` for dynamic data storage
- Clean menu-driven navigation
- Defensive programming and validation
- Separation between UI logic and business logic (partially applied)

---

## 👨‍🏫 Course Reference
This project is part of the **seventh course** in **[Dr. Mohamed Abu-Hadhoud](https://programmingadvices.com/l/dashboard)** Programming Advices curriculum, focusing on practical C++ development.
