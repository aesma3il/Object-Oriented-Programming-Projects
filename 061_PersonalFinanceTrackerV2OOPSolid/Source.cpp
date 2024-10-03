#include <iostream>
#include <string>
#include <chrono>
#include <memory>

// Enums
enum class TransactionType { Income, Expense };
enum class AccountType { Bank, CreditCard, Investment };

// Interfaces
class IUser {
public:
    virtual ~IUser() = default;
    virtual int getUserID() const = 0;
    virtual std::string getUsername() const = 0;
    virtual std::string getEmail() const = 0;
};

class ITransaction {
public:
    virtual ~ITransaction() = default;
    virtual int getTransactionID() const = 0;
    virtual double getAmount() const = 0;
    virtual TransactionType getType() const = 0;
};

class ICategory {
public:
    virtual ~ICategory() = default;
    virtual int getCategoryID() const = 0;
    virtual std::string getCategoryName() const = 0;
};

class IBudget {
public:
    virtual ~IBudget() = default;
    virtual int getBudgetID() const = 0;
    virtual double getAmount() const = 0;
};

class ISavingsGoal {
public:
    virtual ~ISavingsGoal() = default;
    virtual int getGoalID() const = 0;
    virtual double getTargetAmount() const = 0;
    virtual double getCurrentAmount() const = 0;
};

class IAccount {
public:
    virtual ~IAccount() = default;
    virtual int getAccountID() const = 0;
    virtual double getAccountBalance() const = 0;
};

// User Class
class User : public IUser {
private:
    int UserID;
    std::string Username;
    std::string PasswordHash;
    std::string Email;
    std::chrono::system_clock::time_point CreatedAt;
    std::chrono::system_clock::time_point LastLogin;

public:
    User(int userID, const std::string& username, const std::string& passwordHash,
        const std::string& email)
        : UserID(userID), Username(username), PasswordHash(passwordHash),
        Email(email), CreatedAt(std::chrono::system_clock::now()), LastLogin(CreatedAt) {}

    // Implement IUser methods
    int getUserID() const override { return UserID; }
    std::string getUsername() const override { return Username; }
    std::string getEmail() const override { return Email; }
};

// Transaction Class
class Transaction : public ITransaction {
private:
    int TransactionID;
    int UserID;
    double Amount;
    std::chrono::system_clock::time_point Date;
    int CategoryID;
    TransactionType Type;

public:
    Transaction(int transactionID, int userID, double amount,
        const std::chrono::system_clock::time_point& date, int categoryID,
        TransactionType type)
        : TransactionID(transactionID), UserID(userID), Amount(amount),
        Date(date), CategoryID(categoryID), Type(type) {}

    // Implement ITransaction methods
    int getTransactionID() const override { return TransactionID; }
    double getAmount() const override { return Amount; }
    TransactionType getType() const override { return Type; }
};

// Category Class
class Category : public ICategory {
private:
    int CategoryID;
    std::string CategoryName;
    std::string ColorCode;

public:
    Category(int categoryID, const std::string& categoryName, const std::string& colorCode = "")
        : CategoryID(categoryID), CategoryName(categoryName), ColorCode(colorCode) {}

    // Implement ICategory methods
    int getCategoryID() const override { return CategoryID; }
    std::string getCategoryName() const override { return CategoryName; }
};

// Budget Class
class Budget : public IBudget {
private:
    int BudgetID;
    double Amount;
    std::chrono::system_clock::time_point StartDate;
    std::chrono::system_clock::time_point EndDate;

public:
    Budget(int budgetID, double amount,
        const std::chrono::system_clock::time_point& startDate,
        const std::chrono::system_clock::time_point& endDate)
        : BudgetID(budgetID), Amount(amount), StartDate(startDate), EndDate(endDate) {}

    // Implement IBudget methods
    int getBudgetID() const override { return BudgetID; }
    double getAmount() const override { return Amount; }
};

// Savings Goal Class
class SavingsGoal : public ISavingsGoal {
private:
    int GoalID;
    double TargetAmount;
    double CurrentAmount;

public:
    SavingsGoal(int goalID, double targetAmount, double currentAmount)
        : GoalID(goalID), TargetAmount(targetAmount), CurrentAmount(currentAmount) {}

    // Implement ISavingsGoal methods
    int getGoalID() const override { return GoalID; }
    double getTargetAmount() const override { return TargetAmount; }
    double getCurrentAmount() const override { return CurrentAmount; }
};

// Account Class
class Account : public IAccount {
private:
    int AccountID;
    std::string AccountName;
    double AccountBalance;
    AccountType Type;

public:
    Account(int accountID, const std::string& accountName,
        double accountBalance, AccountType type)
        : AccountID(accountID), AccountName(accountName),
        AccountBalance(accountBalance), Type(type) {}

    // Implement IAccount methods
    int getAccountID() const override { return AccountID; }
    double getAccountBalance() const override { return AccountBalance; }
};

// Main function (for demonstration)
int main() {
    // Example instantiation of classes
    User user(1, "john_doe", "hashed_password", "john@example.com");
    Transaction transaction(1, user.getUserID(), 50.0, std::chrono::system_clock::now(), 1, TransactionType::Expense);
    Category category(1, "Groceries", "#FF5733");
    Budget budget(1, 300.0, std::chrono::system_clock::now(), std::chrono::system_clock::now() + std::chrono::hours(24 * 30)); // 1 month
    SavingsGoal goal(1, 1000.0, 200.0);
    Account account(1, "Savings Account", 1500.0, AccountType::Bank);

    // Output for demonstration
    std::cout << "User: " << user.getUsername() << ", Email: " << user.getEmail() << std::endl;
    std::cout << "Transaction Amount: " << transaction.getAmount() << ", Type: " << (transaction.getType() == TransactionType::Expense ? "Expense" : "Income") << std::endl;
    std::cout << "Category: " << category.getCategoryName() << std::endl;
    std::cout << "Budget Amount: " << budget.getAmount() << std::endl;
    std::cout << "Savings Goal: " << goal.getGoalID() << ", Target Amount: " << goal.getTargetAmount() << std::endl;
    std::cout << "Account Balance: " << account.getAccountBalance() << std::endl;

    return 0;
}
