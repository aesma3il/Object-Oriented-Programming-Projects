#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

// --- Interface for Transactions ---
class ITransaction {
public:
    virtual void deposit(double amount) = 0;
    virtual void withdraw(double amount) = 0;
    virtual ~ITransaction() = default;
};

// --- Base Class for Account ---
class Account : public ITransaction {
protected:
    std::string accountHolder;
    int accountNumber;
    double balance;

public:
    Account(const std::string& name, int accNumber, double initialBalance)
        : accountHolder(name), accountNumber(accNumber), balance(initialBalance) {}

    virtual ~Account() = default;

    virtual void displayBalance() const {
        std::cout << "Account Holder: " << accountHolder
            << "\nAccount Number: " << accountNumber
            << "\nBalance: $" << balance << std::endl;
    }

    int getAccountNumber() const { return accountNumber; }

    // Deposit functionality
    void deposit(double amount) override {
        if (amount <= 0) throw std::invalid_argument("Deposit amount must be positive.");
        balance += amount;
        std::cout << "$" << amount << " deposited successfully." << std::endl;
    }

    // Withdraw functionality
    void withdraw(double amount) override {
        if (amount <= 0) throw std::invalid_argument("Withdrawal amount must be positive.");
        if (amount > balance) throw std::runtime_error("Insufficient balance.");
        balance -= amount;
        std::cout << "$" << amount << " withdrawn successfully." << std::endl;
    }

    double getBalance() const { return balance; }

    // Virtual method for transfer - to be overridden by specific account types
    virtual void transfer(Account& toAccount, double amount) {
        if (amount <= 0) throw std::invalid_argument("Transfer amount must be positive.");
        if (amount > balance) throw std::runtime_error("Insufficient balance.");
        withdraw(amount);
        toAccount.deposit(amount);
        std::cout << "$" << amount << " transferred successfully from Account " << accountNumber
            << " to Account " << toAccount.getAccountNumber() << std::endl;
    }
};

// --- Derived Class for Savings Account ---
class SavingsAccount : public Account {
public:
    SavingsAccount(const std::string& name, int accNumber, double initialBalance)
        : Account(name, accNumber, initialBalance) {}

    void displayBalance() const override {
        std::cout << "Savings Account:\n";
        Account::displayBalance();
    }
};

// --- Derived Class for Checking Account ---
class CheckingAccount : public Account {
public:
    CheckingAccount(const std::string& name, int accNumber, double initialBalance)
        : Account(name, accNumber, initialBalance) {}

    void displayBalance() const override {
        std::cout << "Checking Account:\n";
        Account::displayBalance();
    }
};

// --- Class for Bank, Managing Multiple Accounts ---
class Bank {
    std::vector<std::shared_ptr<Account>> accounts;

public:
    // Create and add a new account to the bank
    void addAccount(const std::shared_ptr<Account>& account) {
        accounts.push_back(account);
    }

    // Find account by account number
    std::shared_ptr<Account> getAccountByNumber(int accNumber) {
        for (const auto& account : accounts) {
            if (account->getAccountNumber() == accNumber) {
                return account;
            }
        }
        return nullptr;
    }

    // Display all accounts
    void displayAllAccounts() const {
        std::cout << "Bank Accounts:\n";
        for (const auto& account : accounts) {
            account->displayBalance();
            std::cout << "-------------------\n";
        }
    }
};

// --- Main Function to Demonstrate the Banking System ---
int main() {
    // Create a bank object
    Bank bank;

    // Add savings and checking accounts to the bank
    bank.addAccount(std::make_shared<SavingsAccount>("John Doe", 1001, 500.0));
    bank.addAccount(std::make_shared<CheckingAccount>("Jane Smith", 1002, 1000.0));

    // Display all accounts
    bank.displayAllAccounts();

    // Get John's account and deposit money
    auto johnAccount = bank.getAccountByNumber(1001);
    if (johnAccount) {
        johnAccount->deposit(200);
        johnAccount->displayBalance();
    }

    // Get Jane's account and withdraw money
    auto janeAccount = bank.getAccountByNumber(1002);
    if (janeAccount) {
        janeAccount->withdraw(150);
        janeAccount->displayBalance();
    }

    // Transfer money from John's savings account to Jane's checking account
    if (johnAccount && janeAccount) {
        johnAccount->transfer(*janeAccount, 100);
        johnAccount->displayBalance();
        janeAccount->displayBalance();
    }

    // Display all accounts after transactions
    bank.displayAllAccounts();

    return 0;
}
