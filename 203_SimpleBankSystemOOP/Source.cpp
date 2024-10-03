#include <iostream>
#include <string>
using namespace std;

// Base class: Account
class Account {
protected:
    string accountNumber;
    string accountHolderName;
    double balance;

public:
    // Constructor
    Account(string accNum, string holderName, double initBalance) {
        accountNumber = accNum;
        accountHolderName = holderName;
        balance = initBalance;
    }

    // Method to deposit money
    virtual void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited $" << amount << " to account " << accountNumber << endl;
        }
        else {
            cout << "Invalid deposit amount." << endl;
        }
    }

    // Virtual method to withdraw money (polymorphic)
    virtual bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawn $" << amount << " from account " << accountNumber << endl;
            return true;
        }
        else {
            cout << "Insufficient balance for withdrawal." << endl;
            return false;
        }
    }

    // Method to check balance
    void checkBalance() const {
        cout << "Balance for account " << accountNumber << ": $" << balance << endl;
    }

    // Virtual Destructor (Important for polymorphism)
    virtual ~Account() {}
};

// Derived class: SavingsAccount
class SavingsAccount : public Account {
private:
    double interestRate;

public:
    // Constructor
    SavingsAccount(string accNum, string holderName, double initBalance, double rate)
        : Account(accNum, holderName, initBalance), interestRate(rate) {}

    // Override the withdraw method (Savings cannot go negative)
    bool withdraw(double amount) override {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawn $" << amount << " from Savings account " << accountNumber << endl;
            return true;
        }
        else {
            cout << "Insufficient balance for withdrawal from Savings account." << endl;
            return false;
        }
    }

    // Method to add interest (for simplicity, just call it when needed)
    void addInterest() {
        double interest = balance * interestRate / 100;
        balance += interest;
        cout << "Added $" << interest << " interest to Savings account " << accountNumber << endl;
    }
};

// Derived class: CheckingAccount
class CheckingAccount : public Account {
private:
    double overdraftLimit;
    double overdraftFee;

public:
    // Constructor
    CheckingAccount(string accNum, string holderName, double initBalance, double overdraftLimit, double overdraftFee)
        : Account(accNum, holderName, initBalance), overdraftLimit(overdraftLimit), overdraftFee(overdraftFee) {}

    // Override the withdraw method (Checking account can go negative with a fee)
    bool withdraw(double amount) override {
        if (amount > 0 && amount <= balance) {
            // Withdraw within balance
            balance -= amount;
            cout << "Withdrawn $" << amount << " from Checking account " << accountNumber << endl;
            return true;
        }
        else if (amount > 0 && balance - amount >= -overdraftLimit) {
            // Withdraw within overdraft limit
            balance -= (amount + overdraftFee);
            cout << "Withdrawn $" << amount << " with overdraft fee $" << overdraftFee << " from Checking account "
                << accountNumber << endl;
            return true;
        }
        else {
            cout << "Insufficient balance and overdraft limit for withdrawal from Checking account." << endl;
            return false;
        }
    }
};

// Main function to demonstrate the bank account system
int main() {
    // Creating a SavingsAccount
    SavingsAccount savings("S12345", "John Doe", 1000.0, 2.0); // 2% interest rate
    savings.checkBalance();
    savings.deposit(500.0);
    savings.withdraw(200.0);
    savings.addInterest();
    savings.checkBalance();

    cout << endl;

    // Creating a CheckingAccount
    CheckingAccount checking("C67890", "Jane Smith", 500.0, 200.0, 35.0); // $200 overdraft limit, $35 fee
    checking.checkBalance();
    checking.deposit(300.0);
    checking.withdraw(700.0); // Within overdraft limit
    checking.checkBalance();
    checking.withdraw(200.0); // Exceeds overdraft limit
    checking.checkBalance();

    return 0;
}
