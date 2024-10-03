#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <stdexcept>

// --- Book Class ---
class Book {
private:
    std::string title;
    std::string author;
    std::string isbn;
    bool available;

public:
    Book(const std::string& title, const std::string& author, const std::string& isbn)
        : title(title), author(author), isbn(isbn), available(true) {}

    std::string getTitle() const { return title; }
    std::string getAuthor() const { return author; }
    std::string getIsbn() const { return isbn; }
    bool isAvailable() const { return available; }

    void borrowBook() {
        if (!available) {
            throw std::runtime_error("Book is already borrowed.");
        }
        available = false;
    }

    void returnBook() {
        available = true;
    }

    void displayDetails() const {
        std::cout << "Title: " << title << ", Author: " << author << ", ISBN: " << isbn
            << ", " << (available ? "Available" : "Not Available") << std::endl;
    }
};

// --- Member Class ---
class Member {
protected:
    std::string name;
    std::string memberId;
    std::vector<std::string> borrowedBooks;

public:
    Member(const std::string& name, const std::string& memberId)
        : name(name), memberId(memberId) {}

    virtual ~Member() = default;

    std::string getName() const { return name; }
    std::string getMemberId() const { return memberId; }

    virtual void borrowBook(const std::shared_ptr<Book>& book) = 0;
    virtual void returnBook(const std::shared_ptr<Book>& book) = 0;

    void displayBorrowedBooks() const {
        std::cout << "Borrowed Books by " << name << ": ";
        if (borrowedBooks.empty()) {
            std::cout << "No books borrowed.\n";
        }
        else {
            for (const auto& book : borrowedBooks) {
                std::cout << book << " ";
            }
            std::cout << std::endl;
        }
    }

protected:
    void addBorrowedBook(const std::string& isbn) {
        borrowedBooks.push_back(isbn);
    }

    void removeBorrowedBook(const std::string& isbn) {
        borrowedBooks.erase(std::remove(borrowedBooks.begin(), borrowedBooks.end(), isbn), borrowedBooks.end());
    }
};

// --- Student Class (Inherits from Member) ---
class Student : public Member {
public:
    Student(const std::string& name, const std::string& memberId)
        : Member(name, memberId) {}

    void borrowBook(const std::shared_ptr<Book>& book) override {
        if (book->isAvailable()) {
            book->borrowBook();
            addBorrowedBook(book->getIsbn());
            std::cout << name << " borrowed \"" << book->getTitle() << "\"." << std::endl;
        }
        else {
            std::cout << "Book \"" << book->getTitle() << "\" is not available." << std::endl;
        }
    }

    void returnBook(const std::shared_ptr<Book>& book) override {
        if (std::find(borrowedBooks.begin(), borrowedBooks.end(), book->getIsbn()) != borrowedBooks.end()) {
            book->returnBook();
            removeBorrowedBook(book->getIsbn());
            std::cout << name << " returned \"" << book->getTitle() << "\"." << std::endl;
        }
        else {
            std::cout << "This book was not borrowed by " << name << "." << std::endl;
        }
    }
};

// --- Librarian Class (Inherits from Member) ---
class Librarian : public Member {
public:
    Librarian(const std::string& name, const std::string& memberId)
        : Member(name, memberId) {}

    void borrowBook(const std::shared_ptr<Book>& book) override {
        if (book->isAvailable()) {
            book->borrowBook();
            addBorrowedBook(book->getIsbn());
            std::cout << name << " borrowed \"" << book->getTitle() << "\"." << std::endl;
        }
        else {
            std::cout << "Book \"" << book->getTitle() << "\" is not available." << std::endl;
        }
    }

    void returnBook(const std::shared_ptr<Book>& book) override {
        if (std::find(borrowedBooks.begin(), borrowedBooks.end(), book->getIsbn()) != borrowedBooks.end()) {
            book->returnBook();
            removeBorrowedBook(book->getIsbn());
            std::cout << name << " returned \"" << book->getTitle() << "\"." << std::endl;
        }
        else {
            std::cout << "This book was not borrowed by " << name << "." << std::endl;
        }
    }

    void addBook(const std::shared_ptr<Book>& book) {
        std::cout << "Book \"" << book->getTitle() << "\" added to the library." << std::endl;
    }

    void removeBook(const std::shared_ptr<Book>& book) {
        std::cout << "Book \"" << book->getTitle() << "\" removed from the library." << std::endl;
    }
};

// --- Library Management System Class ---
class LibraryManagementSystem {
private:
    std::vector<std::shared_ptr<Book>> books;
    std::vector<std::shared_ptr<Member>> members;

public:
    // Add a book to the library
    void addBook(const std::string& title, const std::string& author, const std::string& isbn) {
        books.push_back(std::make_shared<Book>(title, author, isbn));
        std::cout << "Book \"" << title << "\" added to the library." << std::endl;
    }

    // Remove a book from the library
    void removeBook(const std::string& isbn) {
        auto it = std::remove_if(books.begin(), books.end(),
            [&isbn](const std::shared_ptr<Book>& book) { return book->getIsbn() == isbn; });
        if (it != books.end()) {
            std::cout << "Book \"" << (*it)->getTitle() << "\" removed from the library." << std::endl;
            books.erase(it, books.end());
        }
        else {
            std::cout << "Book with ISBN " << isbn << " not found." << std::endl;
        }
    }

    // Register a member
    void registerMember(const std::string& name, const std::string& memberId, bool isLibrarian = false) {
        if (isLibrarian) {
            members.push_back(std::make_shared<Librarian>(name, memberId));
            std::cout << "Librarian " << name << " registered." << std::endl;
        }
        else {
            members.push_back(std::make_shared<Student>(name, memberId));
            std::cout << "Student " << name << " registered." << std::endl;
        }
    }

    // Borrow a book
    void borrowBook(const std::string& memberId, const std::string& isbn) {
        auto member = findMember(memberId);
        auto book = findBook(isbn);
        member->borrowBook(book);
    }

    // Return a book
    void returnBook(const std::string& memberId, const std::string& isbn) {
        auto member = findMember(memberId);
        auto book = findBook(isbn);
        member->returnBook(book);
    }

    // Display all books
    void displayAllBooks() const {
        std::cout << "Books in the Library:\n";
        for (const auto& book : books) {
            book->displayDetails();
        }
    }

    // Display all members
    void displayAllMembers() const {
        std::cout << "Library Members:\n";
        for (const auto& member : members) {
            std::cout << member->getName() << " (ID: " << member->getMemberId() << ")" << std::endl;
            member->displayBorrowedBooks();
        }
    }

private:
    // Find a book by ISBN
    std::shared_ptr<Book> findBook(const std::string& isbn) const {
        for (const auto& book : books) {
            if (book->getIsbn() == isbn) {
                return book;
            }
        }
        throw std::runtime_error("Book not found.");
    }

    // Find a member by ID
    std::shared_ptr<Member> findMember(const std::string& memberId) const {
        for (const auto& member : members) {
            if (member->getMemberId() == memberId) {
                return member;
            }
        }
        throw std::runtime_error("Member not found.");
    }
};

// --- Main Function to Demonstrate the System ---
int main() {
    LibraryManagementSystem library;

    // Adding books to the library
    library.addBook("1984", "George Orwell", "9780451524935");
    library.addBook("The Great Gatsby", "F. Scott Fitzgerald", "9780743273565");
    library.addBook("To Kill a Mockingbird", "Harper Lee", "9780061120084");

    // Registering members
    library.registerMember("Alice", "M001");
    library.registerMember("Bob", "M002", true);  // Bob is a librarian

    // Display all books and members
    library.displayAllBooks();
    library.displayAllMembers();

    // Borrowing and returning books
    library.borrowBook("M001", "9780451524935");
    library.borrowBook("M001", "9780743273565");
    library.returnBook("M001", "9780451524935");

    // Display all members again to see borrowed books
    library.displayAllMembers();

    // Remove a book from the library
    library.removeBook("9780743273565");

    // Display all books after removal
    library.displayAllBooks();

    return 0;
}
