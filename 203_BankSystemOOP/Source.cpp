//#include <iostream>
//#include <string>
//#include <stdexcept>
//#include <vector>
//
//// Base class representing an Account
//class Account {
//protected:
//    std::string accountNumber;
//    double balance;
//
//public:
//    Account(const std::string& accountNumber, double initialBalance)
//        : accountNumber(accountNumber), balance(initialBalance) {}
//
//    virtual void deposit(double amount) = 0;
//    virtual void withdraw(double amount) = 0;
//    virtual void transfer(Account& toAccount, double amount) = 0;
//
//    double getBalance() const {
//        return balance;
//    }
//
//    std::string getAccountNumber() const {
//        return accountNumber;
//    }
//
//    virtual ~Account() {}
//};
//
//// SavingsAccount class inheriting from Account
//class SavingsAccount : public Account {
//public:
//    SavingsAccount(const std::string& accountNumber, double initialBalance)
//        : Account(accountNumber, initialBalance) {}
//
//    void deposit(double amount) override {
//        balance += amount;
//    }
//
//    void withdraw(double amount) override {
//        if (balance >= amount) {
//            balance -= amount;
//        }
//        else {
//            throw std::invalid_argument("Insufficient funds");
//        }
//    }
//
//    void transfer(Account& toAccount, double amount) override {
//        if (balance >= amount) {
//            this->withdraw(amount);
//            toAccount.deposit(amount);
//        }
//        else {
//            throw std::invalid_argument("Insufficient funds");
//        }
//    }
//};
//
//// Transaction class representing a bank transaction
//class Transaction {
//protected:
//    std::string transactionId;
//    std::string accountNumber;
//    std::string type; // Deposit, Withdrawal, Transfer
//    double amount;
//    std::string description;
//    std::string status;
//    std::string date;
//    double balanceAfterTransaction;
//
//public:
//    Transaction(const std::string& transactionId, const std::string& accountNumber, const std::string& type, double amount,
//        const std::string& description, const std::string& status, const std::string& date, double balanceAfterTransaction)
//        : transactionId(transactionId), accountNumber(accountNumber), type(type), amount(amount),
//        description(description), status(status), date(date), balanceAfterTransaction(balanceAfterTransaction) {}
//
//    // Getters and setters can be added here as necessary
//};
//
//// Derived classes for different types of transactions
//class Deposit : public Transaction {
//public:
//    Deposit(const std::string& transactionId, const std::string& accountNumber, double amount, const std::string& date)
//        : Transaction(transactionId, accountNumber, "Deposit", amount, "Cash Deposit", "Completed", date, 0) {}
//};
//
//class Withdrawal : public Transaction {
//public:
//    Withdrawal(const std::string& transactionId, const std::string& accountNumber, double amount, const std::string& date)
//        : Transaction(transactionId, accountNumber, "Withdrawal", amount, "ATM Withdrawal", "Completed", date, 0) {}
//};
//
//class Transfer : public Transaction {
//    std::string beneficiaryAccount;
//
//public:
//    Transfer(const std::string& transactionId, const std::string& accountNumber, double amount, const std::string& date, const std::string& beneficiaryAccount)
//        : Transaction(transactionId, accountNumber, "Transfer", amount, "Transfer to " + beneficiaryAccount, "Completed", date, 0), beneficiaryAccount(beneficiaryAccount) {}
//};
//
//// Example usage
//int main() {
//    try {
//        // Create accounts
//        SavingsAccount account1("ACC123", 500.0);
//        SavingsAccount account2("ACC456", 300.0);
//
//        // Perform deposit, withdraw, and transfer
//        account1.deposit(100.0);
//        std::cout << "Account 1 balance after deposit: " << account1.getBalance() << std::endl;
//
//        account1.withdraw(50.0);
//        std::cout << "Account 1 balance after withdrawal: " << account1.getBalance() << std::endl;
//
//        account1.transfer(account2, 200.0);
//        std::cout << "Account 1 balance after transfer: " << account1.getBalance() << std::endl;
//        std::cout << "Account 2 balance after receiving transfer: " << account2.getBalance() << std::endl;
//
//        // Create transactions
//        Deposit deposit("TXN001", account1.getAccountNumber(), 100.0, "2024-09-30");
//        Withdrawal withdrawal("TXN002", account1.getAccountNumber(), 50.0, "2024-09-30");
//        Transfer transfer("TXN003", account1.getAccountNumber(), 200.0, "2024-09-30", account2.getAccountNumber());
//
//    }
//    catch (const std::exception& e) {
//        std::cerr << "Error: " << e.what() << std::endl;
//    }
//
//    return 0;
//}


//--------------------------------------------enhanced 

#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <unordered_map>

// Base class representing an Account
class Account {
protected:
    std::string accountNumber;
    double balance;

public:
    Account(const std::string& accountNumber, double initialBalance)
        : accountNumber(accountNumber), balance(initialBalance) {}

    virtual void deposit(double amount) = 0;
    virtual void withdraw(double amount) = 0;
    virtual void transfer(Account& toAccount, double amount) = 0;

    double getBalance() const {
        return balance;
    }

    std::string getAccountNumber() const {
        return accountNumber;
    }

    virtual ~Account() {}
};

// SavingsAccount class inheriting from Account
class SavingsAccount : public Account {
public:
    SavingsAccount(const std::string& accountNumber, double initialBalance)
        : Account(accountNumber, initialBalance) {}

    void deposit(double amount) override {
        balance += amount;
    }

    void withdraw(double amount) override {
        if (balance >= amount) {
            balance -= amount;
        }
        else {
            throw std::invalid_argument("Insufficient funds");
        }
    }

    void transfer(Account& toAccount, double amount) override {
        if (balance >= amount) {
            this->withdraw(amount);
            toAccount.deposit(amount);
        }
        else {
            throw std::invalid_argument("Insufficient funds");
        }
    }
};

// Transaction class representing a bank transaction
class Transaction {
protected:
    std::string transactionId;
    std::string accountNumber;
    std::string type; // Deposit, Withdrawal, Transfer
    double amount;
    std::string description;
    std::string status;
    std::string date;
    double balanceAfterTransaction;

public:
    Transaction(const std::string& transactionId, const std::string& accountNumber, const std::string& type, double amount,
        const std::string& description, const std::string& status, const std::string& date, double balanceAfterTransaction)
        : transactionId(transactionId), accountNumber(accountNumber), type(type), amount(amount),
        description(description), status(status), date(date), balanceAfterTransaction(balanceAfterTransaction) {}

    std::string getDetails() const {
        return "Transaction ID: " + transactionId + ", Type: " + type + ", Amount: " + std::to_string(amount) +
            ", Status: " + status + ", Date: " + date + ", Balance After: " + std::to_string(balanceAfterTransaction);
    }
};

// Derived classes for different types of transactions
class Deposit : public Transaction {
public:
    Deposit(const std::string& transactionId, const std::string& accountNumber, double amount, const std::string& date, double balanceAfter)
        : Transaction(transactionId, accountNumber, "Deposit", amount, "Cash Deposit", "Completed", date, balanceAfter) {}
};

class Withdrawal : public Transaction {
public:
    Withdrawal(const std::string& transactionId, const std::string& accountNumber, double amount, const std::string& date, double balanceAfter)
        : Transaction(transactionId, accountNumber, "Withdrawal", amount, "ATM Withdrawal", "Completed", date, balanceAfter) {}
};

class Transfer : public Transaction {
    std::string beneficiaryAccount;

public:
    Transfer(const std::string& transactionId, const std::string& accountNumber, double amount, const std::string& date, const std::string& beneficiaryAccount, double balanceAfter)
        : Transaction(transactionId, accountNumber, "Transfer", amount, "Transfer to " + beneficiaryAccount, "Completed", date, balanceAfter), beneficiaryAccount(beneficiaryAccount) {}
};

// BankSystem class to manage accounts and process transactions
class BankSystem {
private:
    std::unordered_map<std::string, Account*> accounts;
    std::vector<Transaction*> transactionHistory;

public:
    void addAccount(Account* account) {
        accounts[account->getAccountNumber()] = account;
    }

    void processDeposit(const std::string& accountNumber, double amount, const std::string& date) {
        Account* account = accounts.at(accountNumber);
        account->deposit(amount);
        double newBalance = account->getBalance();
        Deposit* deposit = new Deposit("TXN" + std::to_string(transactionHistory.size() + 1), accountNumber, amount, date, newBalance);
        transactionHistory.push_back(deposit);
        std::cout << deposit->getDetails() << std::endl;
    }

    void processWithdrawal(const std::string& accountNumber, double amount, const std::string& date) {
        Account* account = accounts.at(accountNumber);
        account->withdraw(amount);
        double newBalance = account->getBalance();
        Withdrawal* withdrawal = new Withdrawal("TXN" + std::to_string(transactionHistory.size() + 1), accountNumber, amount, date, newBalance);
        transactionHistory.push_back(withdrawal);
        std::cout << withdrawal->getDetails() << std::endl;
    }

    void processTransfer(const std::string& fromAccountNumber, const std::string& toAccountNumber, double amount, const std::string& date) {
        Account* fromAccount = accounts.at(fromAccountNumber);
        Account* toAccount = accounts.at(toAccountNumber);
        fromAccount->transfer(*toAccount, amount);
        double newBalance = fromAccount->getBalance();
        Transfer* transfer = new Transfer("TXN" + std::to_string(transactionHistory.size() + 1), fromAccountNumber, amount, date, toAccountNumber, newBalance);
        transactionHistory.push_back(transfer);
        std::cout << transfer->getDetails() << std::endl;
    }

    // Retrieve all transactions
    void getTransactionHistory() const {
        for (const auto& txn : transactionHistory) {
            std::cout << txn->getDetails() << std::endl;
        }
    }
};

// Example usage
int main() {
    try {
        BankSystem bank;

        // Create accounts
        SavingsAccount* account1 = new SavingsAccount("ACC123", 500.0);
        SavingsAccount* account2 = new SavingsAccount("ACC456", 300.0);

        bank.addAccount(account1);
        bank.addAccount(account2);

        // Process transactions
        bank.processDeposit("ACC123", 100.0, "2024-09-30");
        bank.processWithdrawal("ACC123", 50.0, "2024-09-30");
        bank.processTransfer("ACC123", "ACC456", 200.0, "2024-09-30");

        // Retrieve transaction history
        std::cout << "\nTransaction History:\n";
        bank.getTransactionHistory();

        // Clean up
        delete account1;
        delete account2;

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
