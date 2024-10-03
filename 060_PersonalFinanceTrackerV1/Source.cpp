#include <iostream>
#include <string>
#include <chrono>

// Enums
enum class TransactionType { Income, Expense };
enum class AccountType { Bank, CreditCard, Investment };

// User Class
class User {
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

    // Getters
    int getUserID() const { return UserID; }
    std::string getUsername() const { return Username; }
    std::string getEmail() const { return Email; }
    std::chrono::system_clock::time_point getCreatedAt() const { return CreatedAt; }
    std::chrono::system_clock::time_point getLastLogin() const { return LastLogin; }

    // Setters
    void setLastLogin(const std::chrono::system_clock::time_point& lastLogin) { LastLogin = lastLogin; }
};

// Transaction Class
class Transaction {
private:
    int TransactionID;
    int UserID;
    double Amount;
    std::chrono::system_clock::time_point Date;
    int CategoryID;
    std::string Description;
    TransactionType Type;

public:
    Transaction(int transactionID, int userID, double amount,
        const std::chrono::system_clock::time_point& date, int categoryID,
        const std::string& description, TransactionType type)
        : TransactionID(transactionID), UserID(userID), Amount(amount),
        Date(date), CategoryID(categoryID), Description(description), Type(type) {}

    // Getters
    int getTransactionID() const { return TransactionID; }
    double getAmount() const { return Amount; }
    std::chrono::system_clock::time_point getDate() const { return Date; }
    TransactionType getType() const { return Type; }
};

// Category Class
class Category {
private:
    int CategoryID;
    int UserID;
    std::string CategoryName;
    std::string ColorCode;

public:
    Category(int categoryID, int userID, const std::string& categoryName, const std::string& colorCode = "")
        : CategoryID(categoryID), UserID(userID), CategoryName(categoryName), ColorCode(colorCode) {}

    // Getters
    int getCategoryID() const { return CategoryID; }
    std::string getCategoryName() const { return CategoryName; }
    std::string getColorCode() const { return ColorCode; }
};

// Budget Class
class Budget {
private:
    int BudgetID;
    int UserID;
    int CategoryID;
    double Amount;
    std::chrono::system_clock::time_point StartDate;
    std::chrono::system_clock::time_point EndDate;
    std::chrono::system_clock::time_point CreatedAt;

public:
    Budget(int budgetID, int userID, int categoryID, double amount,
        const std::chrono::system_clock::time_point& startDate,
        const std::chrono::system_clock::time_point& endDate)
        : BudgetID(budgetID), UserID(userID), CategoryID(categoryID),
        Amount(amount), StartDate(startDate), EndDate(endDate),
        CreatedAt(std::chrono::system_clock::now()) {}

    // Getters
    int getBudgetID() const { return BudgetID; }
    double getAmount() const { return Amount; }
    std::chrono::system_clock::time_point getStartDate() const { return StartDate; }
    std::chrono::system_clock::time_point getEndDate() const { return EndDate; }
};

// Savings Goal Class
class SavingsGoal {
private:
    int GoalID;
    int UserID;
    std::string GoalName;
    double TargetAmount;
    double CurrentAmount;
    std::chrono::system_clock::time_point Deadline;
    std::chrono::system_clock::time_point CreatedAt;

public:
    SavingsGoal(int goalID, int userID, const std::string& goalName,
        double targetAmount, double currentAmount,
        const std::chrono::system_clock::time_point& deadline)
        : GoalID(goalID), UserID(userID), GoalName(goalName),
        TargetAmount(targetAmount), CurrentAmount(currentAmount),
        Deadline(deadline), CreatedAt(std::chrono::system_clock::now()) {}

    // Getters
    int getGoalID() const { return GoalID; }
    double getTargetAmount() const { return TargetAmount; }
    double getCurrentAmount() const { return CurrentAmount; }
};

// Account Class
class Account {
private:
    int AccountID;
    int UserID;
    std::string AccountName;
    double AccountBalance;
    AccountType Type;
    std::chrono::system_clock::time_point CreatedAt;

public:
    Account(int accountID, int userID, const std::string& accountName,
        double accountBalance, AccountType type)
        : AccountID(accountID), UserID(userID), AccountName(accountName),
        AccountBalance(accountBalance), Type(type), CreatedAt(std::chrono::system_clock::now()) {}

    // Getters
    int getAccountID() const { return AccountID; }
    double getAccountBalance() const { return AccountBalance; }
    AccountType getType() const { return Type; }
};

// Main function (for demonstration)
int main() {
    // Example instantiation of classes
    User user(1, "john_doe", "hashed_password", "john@example.com");
    Transaction transaction(1, user.getUserID(), 50.0, std::chrono::system_clock::now(), 1, "Grocery Shopping", TransactionType::Expense);
    Category category(1, user.getUserID(), "Groceries", "#FF5733");
    Budget budget(1, user.getUserID(), category.getCategoryID(), 300.0, std::chrono::system_clock::now(), std::chrono::system_clock::now() + std::chrono::hours(24 * 30)); // 1 month
    SavingsGoal goal(1, user.getUserID(), "Emergency Fund", 1000.0, 200.0, std::chrono::system_clock::now() + std::chrono::hours(24 * 30)); // 1 month
    Account account(1, user.getUserID(), "Savings Account", 1500.0, AccountType::Bank);

    // Output for demonstration
    std::cout << "User: " << user.getUsername() << ", Email: " << user.getEmail() << std::endl;
    std::cout << "Transaction Amount: " << transaction.getAmount() << ", Type: " << (transaction.getType() == TransactionType::Expense ? "Expense" : "Income") << std::endl;
    std::cout << "Category: " << category.getCategoryName() << ", Color Code: " << category.getColorCode() << std::endl;
    std::cout << "Budget Amount: " << budget.getAmount() << std::endl;
    std::cout << "Savings Goal: " << goal.getGoalID() << ", Target Amount: " << goal.getTargetAmount() << std::endl;
    std::cout << "Account Balance: " << account.getAccountBalance() << std::endl;

    return 0;
}
