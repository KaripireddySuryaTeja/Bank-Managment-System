// Advanced Bank Management System using OOP & Inheritance
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include <ctime>
#include <map>

using namespace std;

struct Transaction {
    time_t date;
    string type;
    long long amount; // In paise
};

class Account {
protected:
    int accNo;
    string name;
    string pin;
    long long balance;
    vector<Transaction> history;
public:
    virtual ~Account() = default;

    virtual void createAccount() {
        cout << "Account No: "; cin >> accNo;
        cout << "Name: "; cin.ignore(); getline(cin, name);
        cout << "Set 4-digit PIN: "; cin >> pin;
        balance = 0;
    }

    bool authenticate() {
        string p;
        cout << "Enter PIN: "; cin >> p;
        return p == pin;
    }

    void deposit(long long amt) {
        balance += amt;
        history.push_back({ time(nullptr), "Deposit", amt });
        cout << "Deposited. New Balance: " << balance / 100.0 << "\n";
    }

    void withdraw(long long amt) {
        if (amt > balance) {
            cout << "Insufficient funds.\n";
        } else {
            balance -= amt;
            history.push_back({ time(nullptr), "Withdraw", amt });
            cout << "Withdrawn. New Balance: " << balance / 100.0 << "\n";
        }
    }

    virtual void monthlyUpdate() = 0;

    virtual void showAccount() const {
        cout << "\nAccNo: " << accNo << "\nName: " << name
             << "\nBalance: " << balance / 100.0 << "\n";
    }

    void showHistory() const {
        for (auto& t : history) {
            cout << ctime(&t.date) << " - " << t.type << ": " << t.amount / 100.0 << "\n";
        }
    }

    virtual void writeTo(ofstream& os) const {
        os << accNo << "\n" << name << "\n" << pin << "\n" << balance << "\n"
           << history.size() << "\n";
        for (auto& t : history)
            os << t.date << " " << t.type << " " << t.amount << "\n";
    }

    virtual void readFrom(ifstream& is) {
        size_t n;
        is >> accNo >> ws;
        getline(is, name);
        getline(is, pin);
        is >> balance >> n;
        history.clear();
        for (size_t i = 0; i < n; i++) {
            Transaction t;
            is >> t.date >> t.type >> t.amount;
            history.push_back(t);
        }
    }

    int getAccNo() const { return accNo; }
};

class SavingsAccount : public Account {
    double interestRate;
public:
    SavingsAccount(double r = 0.005) : interestRate(r) {}

    void monthlyUpdate() override {
        long long interest = balance * interestRate;
        if (interest > 0) {
            balance += interest;
            history.push_back({ time(nullptr), "Interest", interest });
        }
    }

    void writeTo(ofstream& os) const override {
        os << "S\n";
        Account::writeTo(os);
        os << interestRate << "\n";
    }

    void readFrom(ifstream& is) override {
        Account::readFrom(is);
        is >> interestRate;
    }
};

class CurrentAccount : public Account {
    long long minBalance;
    long long monthlyFee;
public:
    CurrentAccount(long long minB = 5000, long long fee = 1000)
        : minBalance(minB), monthlyFee(fee) {}

    void monthlyUpdate() override {
        if (balance < minBalance) {
            balance -= monthlyFee;
            history.push_back({ time(nullptr), "Monthly Fee", monthlyFee });
        }
    }

    void writeTo(ofstream& os) const override {
        os << "C\n";
        Account::writeTo(os);
        os << minBalance << " " << monthlyFee << "\n";
    }

    void readFrom(ifstream& is) override {
        Account::readFrom(is);
        is >> minBalance >> monthlyFee;
    }
};

class Bank {
    map<int, shared_ptr<Account>> accounts;

public:
    void load() {
        ifstream fin("accounts.dat");
        if (!fin) return;
        while (fin) {
            string type;
            getline(fin, type);
            shared_ptr<Account> acc;
            if (type == "S") acc = make_shared<SavingsAccount>();
            else if (type == "C") acc = make_shared<CurrentAccount>();
            else break;
            acc->readFrom(fin);
            accounts[acc->getAccNo()] = acc;
        }
    }

    void save() {
        ofstream fout("accounts.dat");
        for (auto& entry : accounts) {
            entry.second->writeTo(fout);
        }
    }

    void createAccount() {
        int ch;
        cout << "\n1. Savings\n2. Current\nChoice: ";
        cin >> ch;
        shared_ptr<Account> acc;
        if (ch == 1) acc = make_shared<SavingsAccount>();
        else acc = make_shared<CurrentAccount>();
        acc->createAccount();
        accounts[acc->getAccNo()] = acc;
        cout << "Account created.\n";
    }

    shared_ptr<Account> getAccount() {
        int accNo;
        cout << "Enter Account Number: "; cin >> accNo;
        if (accounts.count(accNo)) {
            auto acc = accounts[accNo];
            if (acc->authenticate()) return acc;
            else cout << "Wrong PIN.\n";
        } else cout << "Account not found.\n";
        return nullptr;
    }

    void deposit() {
        auto acc = getAccount();
        if (acc) {
            float amt;
            cout << "Amount to deposit (INR): "; cin >> amt;
            acc->deposit(amt * 100);
        }
    }

    void withdraw() {
        auto acc = getAccount();
        if (acc) {
            float amt;
            cout << "Amount to withdraw (INR): "; cin >> amt;
            acc->withdraw(amt * 100);
        }
    }

    void showAccount() {
        auto acc = getAccount();
        if (acc) acc->showAccount();
    }

    void showHistory() {
        auto acc = getAccount();
        if (acc) acc->showHistory();
    }

    void monthlyUpdate() {
        for (auto& entry : accounts) entry.second->monthlyUpdate();
        cout << "Monthly update complete.\n";
    }
};

int main() {
    Bank bank;
    bank.load();
    int ch;
    do {
        cout << "\n==== BANK MENU ====";
        cout << "\n1. Create Account\n2. Deposit\n3. Withdraw\n4. View Account\n5. View History\n6. Monthly Update\n7. Exit\nChoice: ";
        cin >> ch;
        switch (ch) {
            case 1: bank.createAccount(); break;
            case 2: bank.deposit(); break;
            case 3: bank.withdraw(); break;
            case 4: bank.showAccount(); break;
            case 5: bank.showHistory(); break;
            case 6: bank.monthlyUpdate(); break;
            case 7: bank.save(); cout << "Goodbye!\n"; break;
            default: cout << "Invalid option.\n";
        }
    } while (ch != 7);

    return 0;
}
