
==========

# 🏦 Advanced Bank Management System (C++)

This is a C++ console-based bank management system that uses **Object-Oriented Programming (OOP)** principles, including **Inheritance**, **Encapsulation**, and **Polymorphism**. It features persistent data storage and basic PIN-based security.

---

## 🔧 Features

- Create **Savings** and **Current** accounts
- Deposit and withdraw funds
- View account details and transaction history
- **Change PIN** with validation
- **Monthly update**: 
  - Savings: applies interest
  - Current: deducts fee if balance is below threshold
- **View all accounts** (for admin/overview)
- File-based data persistence using `accounts.dat`

---

## 📁 Project Structure

- `main.cpp`: Complete application source code
- `accounts.dat`: Binary/text file to store account information between sessions

---

## 🛠️ Compilation & Execution

### Requirements
- A C++17 compatible compiler

### Compile
```
g++ -std=c++17 -o bank main.cpp

```
### Run
```
./bank
```

---

## 🧠 Account Types

### 🟢 Savings Account
- Accumulates monthly interest
- Default interest rate: 0.5%

### 🔴 Current Account
- Requires minimum balance (₹50)
- Charges ₹10 (1000 paise) if balance is insufficient

---

## 🔐 Security
- Users set a 4-digit PIN during account creation.
- PIN is required for all operations (deposit, withdraw, view).
- Change PIN option available.
- (Optional Enhancement): Forgot PIN feature can be added with additional verification.

---

## 📦 Data Persistence
- All account data, including balance and transaction history, is saved in a file accounts.dat. This allows the program to maintain continuity across sessions.

---

## 📈 Monthly Update
A menu option applies:
- Interest to savings accounts
- Penalty fees to current accounts if balance is low

---

## 🧪 Sample Enhancements
- Forgot PIN recovery using security questions
- Admin authentication
- Export transaction history to file (CSV/PDF)
- GUI or Web interface (e.g., Qt, Electron, React)

---

## 👤 Author
Karipireddy Surya Teja Gopal Reddy
National Institute of Technology Meghalaya