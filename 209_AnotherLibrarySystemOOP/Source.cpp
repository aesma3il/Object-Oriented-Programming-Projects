#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <fstream>

using namespace std;

class Book {
public:
    string title;
    string author;
    string category;
    bool isAvailable;
    string condition;  // Track the condition of the book

    Book(string t, string a, string c, string cond = "Good")
        : title(t), author(a), category(c), isAvailable(true), condition(cond) {}
};

class Member {
public:
    int id;
    string name;
    string contactInfo;
    bool isActive;

    Member(int id, string n, string c, bool status = true)
        : id(id), name(n), contactInfo(c), isActive(status) {}
};

class Loan {
public:
    int memberId;
    string bookTitle;
    string dueDate;
    bool isReturned;

    Loan(int mId, string bTitle, string due)
        : memberId(mId), bookTitle(bTitle), dueDate(due), isReturned(false) {}
};

class Reservation {
public:
    int memberId;
    string bookTitle;

    Reservation(int mId, string bTitle)
        : memberId(mId), bookTitle(bTitle) {}
};

class Author {
public:
    string name;
    string bio;

    Author(string n, string b) : name(n), bio(b) {}
};

class Library {
private:
    vector<Book> books;
    vector<Member> members;
    vector<Loan> loans;
    vector<Reservation> reservations;
    vector<Author> authors;
    map<string, int> borrowCount;

public:
    // Add a new book
    void addBook(string title, string author, string category, string condition = "Good") {
        books.emplace_back(title, author, category, condition);
        cout << "Book added: " << title << endl;
    }

    // View all books
    void viewAllBooks() {
        if (books.empty()) {
            cout << "No books in the library." << endl;
            return;
        }
        for (const auto& book : books) {
            cout << "Title: " << book.title << ", Author: " << book.author
                << ", Category: " << book.category << ", Available: "
                << (book.isAvailable ? "Yes" : "No") << ", Condition: " << book.condition << endl;
        }
    }

    // Add a new author
    void addAuthor(string name, string bio) {
        authors.emplace_back(name, bio);
        cout << "Author added: " << name << endl;
    }

    // Remove an author
    void removeAuthor(string name) {
        auto it = remove_if(authors.begin(), authors.end(),
            [&name](Author& a) { return a.name == name; });
        if (it != authors.end()) {
            authors.erase(it, authors.end());
            cout << "Author removed: " << name << endl;
        }
        else {
            cout << "Author not found." << endl;
        }
    }

    // Update author information
    void updateAuthorInfo(string oldName, string newName, string newBio) {
        for (auto& author : authors) {
            if (author.name == oldName) {
                author.name = newName;
                author.bio = newBio;
                cout << "Author updated: " << newName << endl;
                return;
            }
        }
        cout << "Author not found." << endl;
    }

    // Display all authors
    void displayAllAuthors() {
        cout << "Authors in the library:" << endl;
        for (const auto& author : authors) {
            cout << "Name: " << author.name << ", Bio: " << author.bio << endl;
        }
    }

    // Count total books
    int getTotalBooks() {
        return books.size();
    }

    // Count total members
    int getTotalMembers() {
        return members.size();
    }

    // Check membership status
    void checkMembershipStatus(int memberId) {
        for (const auto& member : members) {
            if (member.id == memberId) {
                cout << "Member ID: " << memberId << ", Active: " << (member.isActive ? "Yes" : "No") << endl;
                return;
            }
        }
        cout << "Member not found." << endl;
    }

    // Send reminder for overdue books
    void sendReminderForOverdueBooks(string currentDate) {
        cout << "Reminder for overdue books:" << endl;
        for (const auto& loan : loans) {
            if (!loan.isReturned && loan.dueDate < currentDate) {
                cout << "Reminder sent for book: " << loan.bookTitle << " due on " << loan.dueDate << endl;
            }
        }
    }

    // Display member contact information
    void displayMemberContactInfo(int memberId) {
        for (const auto& member : members) {
            if (member.id == memberId) {
                cout << "Member ID: " << memberId << ", Name: " << member.name
                    << ", Contact Info: " << member.contactInfo << endl;
                return;
            }
        }
        cout << "Member not found." << endl;
    }

    // View book details
    void viewBookDetails(string title) {
        for (const auto& book : books) {
            if (book.title == title) {
                cout << "Title: " << book.title << ", Author: " << book.author
                    << ", Category: " << book.category << ", Available: "
                    << (book.isAvailable ? "Yes" : "No") << ", Condition: " << book.condition << endl;
                return;
            }
        }
        cout << "Book not found." << endl;
    }

    // Batch add books from a file
    void batchAddBooks(string filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Could not open file." << endl;
            return;
        }
        string title, author, category, condition;
        while (getline(file, title, ',') && getline(file, author, ',') && getline(file, category, ',')) {
            getline(file, condition);
            addBook(title, author, category, condition);
        }
        file.close();
        cout << "Books added from file." << endl;
    }

    // Export book list to CSV
    void exportBookListToCSV(string filename) {
        ofstream file(filename);
        for (const auto& book : books) {
            file << book.title << "," << book.author << "," << book.category << "," << book.condition << endl;
        }
        file.close();
        cout << "Book list exported to " << filename << endl;
    }

    // Import book list from CSV
    void importBookListFromCSV(string filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Could not open file." << endl;
            return;
        }
        string title, author, category, condition;
        while (getline(file, title, ',') && getline(file, author, ',') && getline(file, category, ',')) {
            getline(file, condition);
            addBook(title, author, category, condition);
        }
        file.close();
        cout << "Books imported from " << filename << endl;
    }

    // Count borrowed books per member
    void countBorrowedBooksPerMember(int memberId) {
        int count = 0;
        for (const auto& loan : loans) {
            if (loan.memberId == memberId && !loan.isReturned) {
                count++;
            }
        }
        cout << "Member ID: " << memberId << ", Borrowed Books: " << count << endl;
    }

    // Check for duplicate books
    void checkForDuplicateBooks() {
        map<string, int> bookCount;
        for (const auto& book : books) {
            bookCount[book.title]++;
        }
        cout << "Duplicate books:" << endl;
        for (const auto& entry : bookCount) {
            if (entry.second > 1) {
                cout << "Title: " << entry.first << ", Count: " << entry.second << endl;
            }
        }
    }

    // Generate a monthly report
    void generateMonthlyReport() {
        cout << "Monthly Report:" << endl;
        cout << "Total Books Borrowed: " << count_if(loans.begin(), loans.end(), [](Loan& l) { return l.isReturned; }) << endl;
        cout << "Total New Members: " << getTotalMembers() << endl;  // Assuming all members are new for the month
    }

    // Track book conditions
    void trackBookCondition(string title, string condition) {
        for (auto& book : books) {
            if (book.title == title) {
                book.condition = condition;
                cout << "Condition updated for book: " << title << endl;
                return;
            }
        }
        cout << "Book not found." << endl;
    }

    // Set book fine for overdue returns
    void setBookFineForOverdueReturns(string title, double fine) {
        for (auto& loan : loans) {
            if (loan.bookTitle == title && !loan.isReturned) {
                cout << "Fine of $" << fine << " set for overdue book: " << title << endl;
                return;
            }
        }
        cout << "Book not found." << endl;
    }

    // Handle membership renewal
    void handleMembershipRenewal(int memberId) {
        for (auto& member : members) {
            if (member.id == memberId) {
                member.isActive = true;
                cout << "Membership renewed for member ID: " << memberId << endl;
                return;
            }
        }
        cout << "Member not found." << endl;
    }

    // View member feedback
    void viewMemberFeedback() {
        // Placeholder for feedback, assuming we have a structure to hold feedback
        cout << "Member feedback is currently not implemented." << endl;
    }

    // Search for books by category
    void searchForBooksByCategory(string category) {
        cout << "Books in category: " << category << endl;
        for (const auto& book : books) {
            if (book.category == category) {
                cout << "Title: " << book.title << ", Author: " << book.author << endl;
            }
        }
    }

    // Track popular authors
    void trackPopularAuthors() {
        cout << "Most Borrowed Authors:" << endl;
        map<string, int> authorCount;
        for (const auto& loan : loans) {
            if (loan.isReturned) {
                authorCount[loan.bookTitle]++;  // Assuming book titles are unique to authors
            }
        }
        for (const auto& entry : authorCount) {
            cout << "Author: " << entry.first << ", Borrowed: " << entry.second << " times" << endl;
        }
    }

    // Borrow limit check
    void borrowLimitCheck(int memberId) {
        int borrowedCount = count_if(loans.begin(), loans.end(),
            [memberId](Loan& l) { return l.memberId == memberId && !l.isReturned; });
        if (borrowedCount >= 5) {  // Assuming the limit is 5
            cout << "Member ID: " << memberId << " has reached the borrow limit." << endl;
        }
        else {
            cout << "Member ID: " << memberId << " can borrow more books." << endl;
        }
    }

    // Audit trail for book transactions
    void auditTrail() {
        cout << "Audit Trail:" << endl;
        for (const auto& loan : loans) {
            cout << "Member ID: " << loan.memberId << ", Book Title: " << loan.bookTitle
                << ", Due Date: " << loan.dueDate << ", Returned: " << (loan.isReturned ? "Yes" : "No") << endl;
        }
    }

    // View library statistics
    void viewLibraryStatistics() {
        cout << "Library Statistics:" << endl;
        cout << "Total Books: " << getTotalBooks() << endl;
        cout << "Total Members: " << getTotalMembers() << endl;
        cout << "Total Books Borrowed: " << count_if(loans.begin(), loans.end(), [](Loan& l) { return l.isReturned; }) << endl;
    }
    // Add a new member
    void addMember(int id, string name, string contactInfo, bool status = true) {
        members.emplace_back(id, name, contactInfo, status);
        cout << "Member added: " << name << " (ID: " << id << ")" << endl;
    }
    // View all authors
    void viewAllAuthors() {
        if (authors.empty()) {
            cout << "No authors in the library." << endl;
            return;
        }
        for (const auto& author : authors) {
            cout << "Name: " << author.name << ", Bio: " << author.bio << endl;
        }
    }




};

int main() {
    Library library;

    // Example Usage
    library.addAuthor("Author A", "Bio A");
    library.addBook("Book 1", "Author A", "Fiction");
    library.addMember(1, "Member 1", "Contact 1");

    library.viewAllBooks();
    library.viewAllAuthors();
    library.checkMembershipStatus(1);
    library.sendReminderForOverdueBooks("2024-09-30");

    // Add more functionality calls as needed

    return 0;
}
