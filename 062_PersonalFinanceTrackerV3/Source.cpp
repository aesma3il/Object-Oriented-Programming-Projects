#include <iostream>
#include <string>
#include <chrono>
#include <memory>
#include <vector>
#include <unordered_map>

// Enums
enum class TransactionType { Income, Expense };
enum class AccountType { Bank, Cash, CreditCard, Investment };

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
    virtual  std::string getColorCode() const = 0;
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
    User(int userID, const std::string& username, const std::string& passwordHash, const std::string& email)
        : UserID(userID), Username(username), PasswordHash(passwordHash), Email(email),
        CreatedAt(std::chrono::system_clock::now()), LastLogin(CreatedAt) {}

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
        : TransactionID(transactionID), UserID(userID), Amount(amount), Date(date),
        CategoryID(categoryID), Type(type) {}

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
    std::string getColorCode() const override { return ColorCode; }
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
    Account(int accountID, const std::string& accountName, double accountBalance, AccountType type)
        : AccountID(accountID), AccountName(accountName), AccountBalance(accountBalance), Type(type) {}

    const std::string& getAccountName() const { return AccountName; }

    // Implement IAccount methods
    int getAccountID() const override { return AccountID; }
    double getAccountBalance() const override { return AccountBalance; }
    AccountType getType() {
        return Type;
    }
};

// UserManager Class
class UserManager {
private:
    std::unordered_map<int, std::unique_ptr<User>> users;
    int nextUserID = 1;

public:
    void createUser(const std::string& username, const std::string& passwordHash, const std::string& email) {
        users[nextUserID] = std::make_unique<User>(nextUserID, username, passwordHash, email);
        nextUserID++;
    }

    User* readUser(int userID) {
        auto it = users.find(userID);
        return it != users.end() ? it->second.get() : nullptr;
    }

    void updateUser(int userID, const std::string& username, const std::string& passwordHash, const std::string& email) {
        User* user = readUser(userID);
        if (user) {
            *user = User(userID, username, passwordHash, email); // Update details
        }
    }

    void deleteUser(int userID) {
        users.erase(userID);
    }

    void displayAllUsers() const {
        for (const auto& pair : users) {
            std::cout << "User ID: " << pair.second->getUserID()
                << ", Username: " << pair.second->getUsername()
                << ", Email: " << pair.second->getEmail() << std::endl;
        }
    }
};

// TransactionManager Class
class TransactionManager {
private:
    std::unordered_map<int, std::unique_ptr<Transaction>> transactions;
    int nextTransactionID = 1;

public:
    void createTransaction(int userID, double amount, int categoryID, TransactionType type) {
        transactions[nextTransactionID] = std::make_unique<Transaction>(nextTransactionID, userID, amount, std::chrono::system_clock::now(), categoryID, type);
        nextTransactionID++;
    }

    Transaction* readTransaction(int transactionID) {
        auto it = transactions.find(transactionID);
        return it != transactions.end() ? it->second.get() : nullptr;
    }

    void updateTransaction(int transactionID, double amount, int categoryID, TransactionType type) {
        Transaction* transaction = readTransaction(transactionID);
        if (transaction) {
            *transaction = Transaction(transactionID, transaction->getTransactionID(), amount, std::chrono::system_clock::now(), categoryID, type); // Update details
        }
    }

    void deleteTransaction(int transactionID) {
        transactions.erase(transactionID);
    }

    void displayAllTransactions() const {
        for (const auto& pair : transactions) {
            std::cout << "Transaction ID: " << pair.second->getTransactionID()
                << ", Amount: " << pair.second->getAmount()
                << ", Type: " << (pair.second->getType() == TransactionType::Income ? "Income" : "Expense") << std::endl;
        }
    }
};

// CategoryManager Class
class CategoryManager {
private:
    std::unordered_map<int, std::unique_ptr<Category>> categories;
    int nextCategoryID = 1;

public:
    void createCategory(const std::string& categoryName, const std::string& colorCode = "") {
        categories[nextCategoryID] = std::make_unique<Category>(nextCategoryID, categoryName, colorCode);
        nextCategoryID++;
    }

    Category* readCategory(int categoryID) {
        auto it = categories.find(categoryID);
        return it != categories.end() ? it->second.get() : nullptr;
    }

    void updateCategory(int categoryID, const std::string& categoryName, const std::string& colorCode) {
        Category* category = readCategory(categoryID);
        if (category) {
            *category = Category(categoryID, categoryName, colorCode); // Update details
        }
    }

    void deleteCategory(int categoryID) {
        categories.erase(categoryID);
    }
    void displayAllCategories() {
        for (const auto& pair : categories) {
            std::cout << "Category ID: " << pair.second->getCategoryID()
                << ", Name: " << pair.second->getCategoryName()
                << ", Color: " << pair.second->getColorCode() << std::endl;
        }
    }
};

// BudgetManager Class
class BudgetManager {
private:
    std::unordered_map<int, std::unique_ptr<Budget>> budgets;
    int nextBudgetID = 1;

public:
    void createBudget(double amount, const std::chrono::system_clock::time_point& startDate, const std::chrono::system_clock::time_point& endDate) {
        budgets[nextBudgetID] = std::make_unique<Budget>(nextBudgetID, amount, startDate, endDate);
        nextBudgetID++;
    }

    Budget* readBudget(int budgetID) {
        auto it = budgets.find(budgetID);
        return it != budgets.end() ? it->second.get() : nullptr;
    }

    void updateBudget(int budgetID, double amount, const std::chrono::system_clock::time_point& startDate, const std::chrono::system_clock::time_point& endDate) {
        Budget* budget = readBudget(budgetID);
        if (budget) {
            *budget = Budget(budgetID, amount, startDate, endDate); // Update details
        }
    }

    void deleteBudget(int budgetID) {
        budgets.erase(budgetID);
    }

    void displayAllBudgets() {
        for (const auto& pair : budgets) {
            std::cout << "Budget ID: " << pair.second->getBudgetID()
                << ", Amount: " << pair.second->getAmount()
                << std::endl;
        }
    }
};

// SavingsGoalManager Class
class SavingsGoalManager {
private:
    std::unordered_map<int, std::unique_ptr<SavingsGoal>> savingsGoals;
    int nextGoalID = 1;

public:
    void createSavingsGoal(double targetAmount, double currentAmount) {
        savingsGoals[nextGoalID] = std::make_unique<SavingsGoal>(nextGoalID, targetAmount, currentAmount);
        nextGoalID++;
    }

    SavingsGoal* readSavingsGoal(int goalID) {
        auto it = savingsGoals.find(goalID);
        return it != savingsGoals.end() ? it->second.get() : nullptr;
    }

    void updateSavingsGoal(int goalID, double targetAmount, double currentAmount) {
        SavingsGoal* goal = readSavingsGoal(goalID);
        if (goal) {
            *goal = SavingsGoal(goalID, targetAmount, currentAmount); // Update details
        }
    }

    void deleteSavingsGoal(int goalID) {
        savingsGoals.erase(goalID);
    }
    void displayAllSavingsGoals() {
        for (const auto& pair : savingsGoals) {
            std::cout << "Savings Goal ID: " << pair.second->getGoalID()
                << ", Target Amount: " << pair.second->getTargetAmount()
                << ", Current Amount: " << pair.second->getCurrentAmount() << std::endl;
        }
    }

};

// AccountManager Class
class AccountManager {
private:
    std::unordered_map<int, std::unique_ptr<Account>> accounts;
    int nextAccountID = 1;

public:
    void createAccount(const std::string& accountName, double accountBalance, AccountType type) {
        accounts[nextAccountID] = std::make_unique<Account>(nextAccountID, accountName, accountBalance, type);
        nextAccountID++;
    }

    Account* readAccount(int accountID) {
        auto it = accounts.find(accountID);
        return it != accounts.end() ? it->second.get() : nullptr;
    }

    void updateAccount(int accountID, const std::string& accountName, double accountBalance) {
        Account* account = readAccount(accountID);
        if (account) {
            *account = Account(accountID, accountName, accountBalance, account->getAccountBalance() >= 0 ? AccountType::Bank : AccountType::CreditCard); // Update details
        }
    }

    void deleteAccount(int accountID) {
        accounts.erase(accountID);
    }
    void displayAllAccounts() {
        for (const auto& pair : accounts) {
            std::cout << "Account ID: " << pair.second->getAccountID()
                << ", Name: " << pair.second->getAccountName()
                << ", Balance: " << pair.second->getAccountBalance()
                << ", Type: " << (pair.second->getType() == AccountType::Bank ? "Bank" : "Cash") << std::endl;
        }
    }

};

// Main function
int main() {
    //UserManager userManager;
    //TransactionManager transactionManager;
    //CategoryManager categoryManager;
    //BudgetManager budgetManager;
    //SavingsGoalManager savingsGoalManager;
    //AccountManager accountManager;


    //// Example Usage
    //userManager.createUser("john_doe", "hashed_password", "john@example.com");
    //userManager.createUser("jane_doe", "hashed_password", "jane@example.com");

    //userManager.displayAllUsers();

    //// Adding categories
    //categoryManager.createCategory("Food", "#FF5733");
    //categoryManager.createCategory("Transport", "#33FF57");

    //// Adding transactions
    //transactionManager.createTransaction(1, 100.0, 1, TransactionType::Expense); // User ID 1
    //transactionManager.createTransaction(2, 200.0, 2, TransactionType::Income); // User ID 2

    //transactionManager.displayAllTransactions();



    UserManager userManager;
    TransactionManager transactionManager;
    CategoryManager categoryManager;
    BudgetManager budgetManager;
    SavingsGoalManager savingsGoalManager;
    AccountManager accountManager;

    // Sample data
    userManager.createUser("JohnDoe", "password123", "john@example.com");
    userManager.createUser("JaneDoe", "password456", "jane@example.com");
    transactionManager.createTransaction(1, 150.0, 1, TransactionType::Income);
    transactionManager.createTransaction(2, 50.0, 1, TransactionType::Expense);
    categoryManager.createCategory("Food", "#FF5733");
    categoryManager.createCategory("Transport", "#33FF57");
    budgetManager.createBudget(1000.0, std::chrono::system_clock::now(), std::chrono::system_clock::now());
    savingsGoalManager.createSavingsGoal(5000.0, 2000.0);
    accountManager.createAccount("Checking", 1500.0, AccountType::Bank);
    accountManager.createAccount("Cash", 200.0, AccountType::Cash);

    // Display all data
    std::cout << "All Users:\n";
    userManager.displayAllUsers();
    std::cout << "\nAll Transactions:\n";
    transactionManager.displayAllTransactions();
    std::cout << "\nAll Categories:\n";
    categoryManager.displayAllCategories();
    std::cout << "\nAll Budgets:\n";
    budgetManager.displayAllBudgets();
    std::cout << "\nAll Savings Goals:\n";
    savingsGoalManager.displayAllSavingsGoals();
    std::cout << "\nAll Accounts:\n";
    accountManager.displayAllAccounts();










    return 0;
}
