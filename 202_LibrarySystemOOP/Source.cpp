#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Book class to store details about each book
class Book {
private:
    string title;
    string author;
    string isbn;
    bool isAvailable;

public:
    // Constructor
    Book(string title, string author, string isbn) {
        this->title = title;
        this->author = author;
        this->isbn = isbn;
        this->isAvailable = true; // Initially, the book is available
    }

    // Method to get the book's title
    string getTitle() {
        return title;
    }

    // Method to get the book's author
    string getAuthor() {
        return author;
    }

    // Method to check availability
    bool checkAvailability() {
        return isAvailable;
    }

    // Method to borrow the book (sets availability to false)
    bool borrowBook() {
        if (isAvailable) {
            isAvailable = false;
            return true;
        }
        else {
            return false;
        }
    }

    // Method to return the book (sets availability to true)
    void returnBook() {
        isAvailable = true;
    }

    // Method to display book details
    void displayDetails() {
        cout << "Title: " << title << ", Author: " << author << ", ISBN: " << isbn;
        if (isAvailable) {
            cout << " (Available)" << endl;
        }
        else {
            cout << " (Borrowed)" << endl;
        }
    }
};

// Library class to manage book collection
class Library {
private:
    vector<Book> collection;

public:
    // Method to add a book to the collection
    void addBook(Book book) {
        collection.push_back(book);
    }

    // Method to display all available books
    void displayAvailableBooks() {
        cout << "Available books:" << endl;
        for (auto& book : collection) {
            if (book.checkAvailability()) {
                book.displayDetails();
            }
        }
    }

    // Method to search for a book by title or author
    void searchBook(string searchTerm) {
        bool found = false;
        cout << "Search results for '" << searchTerm << "':" << endl;
        for (auto& book : collection) {
            if (book.getTitle() == searchTerm || book.getAuthor() == searchTerm) {
                book.displayDetails();
                found = true;
            }
        }
        if (!found) {
            cout << "No book found for the search term: " << searchTerm << endl;
        }
    }

    // Method to borrow a book by title
    void borrowBook(string title) {
        for (auto& book : collection) {
            if (book.getTitle() == title) {
                if (book.borrowBook()) {
                    cout << "You borrowed the book: " << title << endl;
                }
                else {
                    cout << "The book is currently unavailable." << endl;
                }
                return;
            }
        }
        cout << "The book with the title '" << title << "' was not found in the library." << endl;
    }

    // Method to return a book by title
    void returnBook(string title) {
        for (auto& book : collection) {
            if (book.getTitle() == title) {
                book.returnBook();
                cout << "You returned the book: " << title << endl;
                return;
            }
        }
        cout << "The book with the title '" << title << "' was not found in the library." << endl;
    }
};

// Main function to demonstrate the library system
int main() {
    Library library;

    // Adding books to the library
    library.addBook(Book("1984", "George Orwell", "123456789"));
    library.addBook(Book("To Kill a Mockingbird", "Harper Lee", "987654321"));
    library.addBook(Book("The Great Gatsby", "F. Scott Fitzgerald", "567890123"));

    // Display available books
    library.displayAvailableBooks();
    cout << endl;

    // Borrowing a book
    library.borrowBook("1984");
    cout << endl;

    // Try to borrow the same book again
    library.borrowBook("1984");
    cout << endl;

    // Display available books after borrowing
    library.displayAvailableBooks();
    cout << endl;

    // Returning a book
    library.returnBook("1984");
    cout << endl;

    // Display available books after returning
    library.displayAvailableBooks();
    cout << endl;

    // Search for a book by title
    library.searchBook("The Great Gatsby");
    cout << endl;

    // Search for a book by author
    library.searchBook("Harper Lee");
    cout << endl;

    // Search for a non-existing book
    library.searchBook("Non-Existing Book");

    return 0;
}
