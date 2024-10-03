///*
//Demonstrating the SOLID principles effectively often involves projects that showcase object-oriented design and programming practices. Here are some common types of projects that can be used to illustrate the SOLID principles:
//
//### 1. **Library Management System**
//   - **Single Responsibility Principle (SRP)**: Each class has a single responsibility, such as handling books, users, and transactions.
//   - **Open/Closed Principle (OCP)**: New book types or user roles can be added without modifying existing classes.
//   - **Liskov Substitution Principle (LSP)**: Derived classes (e.g., Fiction, Non-Fiction) can replace base classes (Book) without affecting functionality.
//   - **Interface Segregation Principle (ISP)**: Interfaces for different types of users (admin, member) can be created, each with only necessary methods.
//   - **Dependency Inversion Principle (DIP)**: High-level modules (like User Services) depend on abstractions (interfaces) rather than concrete implementations.
//
//### 2. **E-commerce Application**
//   - **SRP**: Separate classes for handling products, orders, and payment processing.
//   - **OCP**: New payment methods (like PayPal, Stripe) can be added as new classes without changing existing code.
//   - **LSP**: Various types of products (digital, physical) can be substituted without altering the order processing logic.
//   - **ISP**: Interfaces for different product types can avoid bloating a single interface.
//   - **DIP**: Use of repository interfaces for data access, allowing for easy swapping of database implementations.
//
//### 3. **Employee Management System**
//   - **SRP**: Classes for employee details, payroll, and performance management.
//   - **OCP**: New types of employees (full-time, part-time, contractor) can be introduced without modifying existing classes.
//   - **LSP**: Derived classes for different employee types can be used interchangeably.
//   - **ISP**: Different interfaces for employees based on their roles (manager, engineer).
//   - **DIP**: High-level classes depend on abstract data access layers rather than specific database implementations.
//
//### 4. **Online Quiz Application**
//   - **SRP**: Classes for quizzes, questions, and results handling.
//   - **OCP**: Adding new question types (multiple-choice, true/false) can be done by extending existing classes.
//   - **LSP**: Derived question types can be used interchangeably in the quiz.
//   - **ISP**: Separate interfaces for different quiz formats.
//   - **DIP**: Quiz logic can depend on question interfaces instead of concrete question classes.
//
//### 5. **Game Development**
//   - **SRP**: Classes for players, enemies, and game mechanics.
//   - **OCP**: New game levels or character types can be added without modifying existing game logic.
//   - **LSP**: Different types of characters can be used interchangeably in game mechanics.
//   - **ISP**: Specific interfaces for different character abilities.
//   - **DIP**: Game systems depend on abstract character interfaces rather than specific character implementations.
//
//### 6. **Blog Application**
//   - **SRP**: Classes for posts, comments, and user management.
//   - **OCP**: New post types (text, video) can be added easily.
//   - **LSP**: Different types of posts can be used in a uniform way.
//   - **ISP**: Interfaces for different user roles (admin, editor, viewer).
//   - **DIP**: Depend on repository interfaces for managing post data.
//
//### 7. **Real Estate Management System**
//   - **SRP**: Classes for properties, agents, and listings.
//   - **OCP**: New property types (commercial, residential) can be added easily.
//   - **LSP**: Different property classes can be used interchangeably.
//   - **ISP**: Separate interfaces for agent functionalities.
//   - **DIP**: Abstract interfaces for property data access.
//
//### Conclusion
//These project ideas can be implemented in various programming languages and frameworks. Each project can serve as a practical demonstration of the SOLID principles, helping to build a solid understanding of how these principles improve software design and maintainability.
//
//*/
 






#include <iostream>
#include <string>

// 1. Library Class
class Library {
protected:
    int libraryID;
    std::string name;
    std::string address;
    std::string contactNumber;
    std::string email;
    std::string openingHours;

public:
    Library(int id, std::string name, std::string address, std::string contactNumber, std::string email, std::string openingHours)
        : libraryID(id), name(name), address(address), contactNumber(contactNumber), email(email), openingHours(openingHours) {}

    virtual void displayInfo() const {
        std::cout << "Library Info: " << name << ", " << address << std::endl;
    }

    // Other common methods...
};

class PublicLibrary : public Library {
public:
    PublicLibrary(int id, std::string name, std::string address, std::string contactNumber, std::string email, std::string openingHours)
        : Library(id, name, address, contactNumber, email, openingHours) {}

    void displayInfo() const override {
        std::cout << "Public Library Info: " << name << ", " << address << std::endl;
    }

    // Additional behaviors specific to public libraries...
};

class UniversityLibrary : public Library {
public:
    UniversityLibrary(int id, std::string name, std::string address, std::string contactNumber, std::string email, std::string openingHours)
        : Library(id, name, address, contactNumber, email, openingHours) {}

    void displayInfo() const override {
        std::cout << "University Library Info: " << name << ", " << address << std::endl;
    }

    // Additional behaviors specific to university libraries...
};

// 2. Member Class
class Member {
protected:
    int memberID;
    std::string firstName;
    std::string lastName;
    std::string dateOfBirth;
    std::string address;
    std::string contactNumber;
    std::string email;
    std::string membershipStartDate;
    std::string membershipType;
    std::string status;

public:
    Member(int id, std::string firstName, std::string lastName, std::string dateOfBirth, std::string address,
        std::string contactNumber, std::string email, std::string startDate, std::string type, std::string status)
        : memberID(id), firstName(firstName), lastName(lastName), dateOfBirth(dateOfBirth), address(address),
        contactNumber(contactNumber), email(email), membershipStartDate(startDate), membershipType(type), status(status) {}

    virtual void displayInfo() const {
        std::cout << "Member Info: " << firstName << " " << lastName << ", " << membershipType << std::endl;
    }

    // Other common methods...
};

class StudentMember : public Member {
public:
    StudentMember(int id, std::string firstName, std::string lastName, std::string dateOfBirth, std::string address,
        std::string contactNumber, std::string email, std::string startDate)
        : Member(id, firstName, lastName, dateOfBirth, address, contactNumber, email, startDate, "Student", "Active") {}

    void displayInfo() const override {
        std::cout << "Student Member Info: " << firstName << " " << lastName << std::endl;
    }

    // Additional behaviors specific to student members...
};

class RegularMember : public Member {
public:
    RegularMember(int id, std::string firstName, std::string lastName, std::string dateOfBirth, std::string address,
        std::string contactNumber, std::string email, std::string startDate)
        : Member(id, firstName, lastName, dateOfBirth, address, contactNumber, email, startDate, "Regular", "Active") {}

    void displayInfo() const override {
        std::cout << "Regular Member Info: " << firstName << " " << lastName << std::endl;
    }

    // Additional behaviors specific to regular members...
};

// 3. Book Class
class Book {
protected:
    int bookID;
    std::string title;
    std::string author;
    std::string isbn;
    int publisherID;
    std::string publicationDate;
    std::string language;

public:
    Book(int id, std::string title, std::string author, std::string isbn, int publisherID,
        std::string publicationDate, std::string language)
        : bookID(id), title(title), author(author), isbn(isbn), publisherID(publisherID),
        publicationDate(publicationDate), language(language) {}

    virtual void displayInfo() const {
        std::cout << "Book Info: " << title << " by " << author << std::endl;
    }

    // Other common methods...
};

class EBook : public Book {
public:
    EBook(int id, std::string title, std::string author, std::string isbn, int publisherID,
        std::string publicationDate, std::string language)
        : Book(id, title, author, isbn, publisherID, publicationDate, language) {}

    void displayInfo() const override {
        std::cout << "EBook Info: " << title << " by " << author << " (eBook)" << std::endl;
    }

    // Additional behaviors specific to eBooks...
};

// 4. BookInventory Class
class BookInventory {
protected:
    int bookInventoryID;
    int bookID;
    int copiesAvailable;
    int totalCopies;

public:
    BookInventory(int inventoryID, int bookID, int available, int total)
        : bookInventoryID(inventoryID), bookID(bookID), copiesAvailable(available), totalCopies(total) {}

    virtual void updateInventory(int copies) {
        copiesAvailable = copies;
        std::cout << "Updated Inventory: " << copiesAvailable << " copies available" << std::endl;
    }

    // Other common methods...
};

class PhysicalBookInventory : public BookInventory {
public:
    PhysicalBookInventory(int inventoryID, int bookID, int available, int total)
        : BookInventory(inventoryID, bookID, available, total) {}

    void updateInventory(int copies) override {
        copiesAvailable = copies;
        std::cout << "Physical Book Inventory Updated: " << copiesAvailable << " copies available" << std::endl;
    }

    // Additional behaviors specific to physical book inventory...
};

// 5. Loan Class
class Loan {
protected:
    int loanID;
    int memberID;
    int bookID;
    std::string loanDate;
    std::string dueDate;
    std::string returnDate;
    std::string status;

public:
    Loan(int id, int memberID, int bookID, std::string loanDate, std::string dueDate, std::string returnDate, std::string status)
        : loanID(id), memberID(memberID), bookID(bookID), loanDate(loanDate), dueDate(dueDate), returnDate(returnDate), status(status) {}

    virtual void updateLoanStatus(std::string newStatus) {
        status = newStatus;
        std::cout << "Loan Status Updated: " << status << std::endl;
    }

    // Other common methods...
};

class EBookLoan : public Loan {
public:
    EBookLoan(int id, int memberID, int bookID, std::string loanDate, std::string dueDate, std::string returnDate, std::string status)
        : Loan(id, memberID, bookID, loanDate, dueDate, returnDate, status) {}

    void updateLoanStatus(std::string newStatus) override {
        status = newStatus;
        std::cout << "EBook Loan Status Updated: " << status << std::endl;
    }

    // Additional behaviors specific to eBook loans...
};

// 6. Staff Class
class Staff {
protected:
    int staffID;
    std::string firstName;
    std::string lastName;
    std::string position;
    std::string contactNumber;
    std::string email;
    std::string hireDate;
    std::string status;

public:
    Staff(int id, std::string firstName, std::string lastName, std::string position,
        std::string contactNumber, std::string email, std::string hireDate, std::string status)
        : staffID(id), firstName(firstName), lastName(lastName), position(position),
        contactNumber(contactNumber), email(email), hireDate(hireDate), status(status) {}

    virtual void displayInfo() const {
        std::cout << "Staff Info: " << firstName << " " << lastName << ", " << position << std::endl;
    }

    // Other common methods...
};

class Librarian : public Staff {
public:
    Librarian(int id, std::string firstName, std::string lastName, std::string contactNumber,
        std::string email, std::string hireDate)
        : Staff(id, firstName, lastName, "Librarian", contactNumber, email, hireDate, "Active") {}

    void displayInfo() const override {
        std::cout << "Librarian Info: " << firstName << " " << lastName << std::endl;
    }

    // Additional behaviors specific to librarians...
};

class Assistant : public Staff {
public:
    Assistant(int id, std::string firstName, std::string lastName, std::string contactNumber,
        std::string email, std::string hireDate)
        : Staff(id, firstName, lastName, "Assistant", contactNumber, email, hireDate, "Active") {}

    void displayInfo() const override {
        std::cout << "Assistant Info: " << firstName << " " << lastName << std::endl;
    }

    // Additional behaviors specific to assistants...
};

// 7. Reservation Class
class Reservation {
protected:
    int reservationID;
    int memberID;
    int bookID;
    std::string reservationDate;
    std::string status;

public:
    Reservation(int id, int memberID, int bookID, std::string reservationDate, std::string status)
        : reservationID(id), memberID(memberID), bookID(bookID), reservationDate(reservationDate), status(status) {}

    virtual void updateReservationStatus(std::string newStatus) {
        status = newStatus;
        std::cout << "Reservation Status Updated: " << status << std::endl;
    }

    // Other common methods...
};

class EBookReservation : public Reservation {
public:
    EBookReservation(int id, int memberID, int bookID, std::string reservationDate, std::string status)
        : Reservation(id, memberID, bookID, reservationDate, status) {}

    void updateReservationStatus(std::string newStatus) override {
        status = newStatus;
        std::cout << "EBook Reservation Status Updated: " << status << std::endl;
    }

    // Additional behaviors specific to eBook reservations...
};

// 8. Fine Class
class Fine {
protected:
    int fineID;
    int loanID;
    double amount;
    std::string fineDate;
    std::string status;

public:
    Fine(int id, int loanID, double amount, std::string fineDate, std::string status)
        : fineID(id), loanID(loanID), amount(amount), fineDate(fineDate), status(status) {}

    virtual void updateFineStatus(std::string newStatus) {
        status = newStatus;
        std::cout << "Fine Status Updated: " << status << std::endl;
    }

    // Other common methods...
};

class OverdueFine : public Fine {
public:
    OverdueFine(int id, int loanID, double amount, std::string fineDate, std::string status)
        : Fine(id, loanID, amount, fineDate, status) {}

    void updateFineStatus(std::string newStatus) override {
        status = newStatus;
        std::cout << "Overdue Fine Status Updated: " << status << std::endl;
    }

    // Additional behaviors specific to overdue fines...
};

class DamageFine : public Fine {
public:
    DamageFine(int id, int loanID, double amount, std::string fineDate, std::string status)
        : Fine(id, loanID, amount, fineDate, status) {}

    void updateFineStatus(std::string newStatus) override {
        status = newStatus;
        std::cout << "Damage Fine Status Updated: " << status << std::endl;
    }

    // Additional behaviors specific to damage fines...
};

// 9. Category Class
class Category {
protected:
    int categoryID;
    std::string name;
    std::string description;

public:
    Category(int id, std::string name, std::string description)
        : categoryID(id), name(name), description(description) {}

    virtual void displayInfo() const {
        std::cout << "Category Info: " << name << ", " << description << std::endl;
    }

    // Other common methods...
};

class FictionCategory : public Category {
public:
    FictionCategory(int id, std::string name, std::string description)
        : Category(id, name, description) {}

    void displayInfo() const override {
        std::cout << "Fiction Category: " << name << std::endl;
    }

    // Additional behaviors specific to fiction categories...
};

class NonFictionCategory : public Category {
public:
    NonFictionCategory(int id, std::string name, std::string description)
        : Category(id, name, description) {}

    void displayInfo() const override {
        std::cout << "Non-Fiction Category: " << name << std::endl;
    }

    // Additional behaviors specific to non-fiction categories...
};

// 10. BookCategory Class
class BookCategory {
protected:
    int bookCategoryID;
    int bookID;
    int categoryID;

public:
    BookCategory(int id, int bookID, int categoryID)
        : bookCategoryID(id), bookID(bookID), categoryID(categoryID) {}

    virtual void displayInfo() const {
        std::cout << "BookCategory Info: BookID " << bookID << " in CategoryID " << categoryID << std::endl;
    }

    // Other common methods...
};

// 11. Publisher Class
class Publisher {
protected:
    int publisherID;
    std::string name;
    std::string address;
    std::string contactNumber;
    std::string email;

public:
    Publisher(int id, std::string name, std::string address, std::string contactNumber, std::string email)
        : publisherID(id), name(name), address(address), contactNumber(contactNumber), email(email) {}

    virtual void displayInfo() const {
        std::cout << "Publisher Info: " << name << ", " << address << std::endl;
    }

    // Other common methods...
};

class InternationalPublisher : public Publisher {
public:
    InternationalPublisher(int id, std::string name, std::string address, std::string contactNumber, std::string email)
        : Publisher(id, name, address, contactNumber, email) {}

    void displayInfo() const override {
        std::cout << "International Publisher Info: " << name << std::endl;
    }

    // Additional behaviors specific to international publishers...
};

class LocalPublisher : public Publisher {
public:
    LocalPublisher(int id, std::string name, std::string address, std::string contactNumber, std::string email)
        : Publisher(id, name, address, contactNumber, email) {}

    void displayInfo() const override {
        std::cout << "Local Publisher Info: " << name << std::endl;
    }

    // Additional behaviors specific to local publishers...
};

// Main function to demonstrate usage
int main() {
    PublicLibrary pl(1, "Central Public Library", "123 Main St", "123-456-7890", "info@publiclibrary.com", "9 AM - 5 PM");
    pl.displayInfo();

    StudentMember sm(101, "John", "Doe", "1995-05-15", "456 Elm St", "987-654-3210", "john.doe@example.com", "2023-01-01");
    sm.displayInfo();

    EBook eb(1001, "C++ Programming", "Bjarne Stroustrup", "1234567890", 201, "2024-01-01", "English");
    eb.displayInfo();

    PhysicalBookInventory pbi(3001, 1001, 10, 15);
    pbi.updateInventory(12);

    Librarian lb(201, "Alice", "Smith", "555-555-5555", "alice.smith@library.com", "2020-01-01");
    lb.displayInfo();

    OverdueFine of(4001, 2001, 25.00, "2024-08-01", "Unpaid");
    of.updateFineStatus("Paid");

    InternationalPublisher ip(301, "Global Publishing", "456 Oak St", "123-123-1234", "contact@globalpublishing.com");
    ip.displayInfo();

    return 0;
}

//
////---------------------aFTER LISKOV PRINCIPLE
//
//
//#include <iostream>
//#include <string>
//
//// 1. Library Class
//class Library {
//protected:
//    int libraryID;
//    std::string name;
//    std::string address;
//    std::string contactNumber;
//    std::string email;
//    std::string openingHours;
//
//public:
//    Library(int id, const std::string& name, const std::string& address, const std::string& contactNumber, const std::string& email, const std::string& openingHours)
//        : libraryID(id), name(name), address(address), contactNumber(contactNumber), email(email), openingHours(openingHours) {}
//
//    virtual void displayInfo() const {
//        std::cout << "Library Info: " << name << ", " << address << std::endl;
//    }
//
//    virtual ~Library() = default;
//};
//
//class PublicLibrary : public Library {
//public:
//    PublicLibrary(int id, const std::string& name, const std::string& address, const std::string& contactNumber, const std::string& email, const std::string& openingHours)
//        : Library(id, name, address, contactNumber, email, openingHours) {}
//
//    void displayInfo() const override {
//        std::cout << "Public Library Info: " << name << ", " << address << std::endl;
//    }
//};
//
//class UniversityLibrary : public Library {
//public:
//    UniversityLibrary(int id, const std::string& name, const std::string& address, const std::string& contactNumber, const std::string& email, const std::string& openingHours)
//        : Library(id, name, address, contactNumber, email, openingHours) {}
//
//    void displayInfo() const override {
//        std::cout << "University Library Info: " << name << ", " << address << std::endl;
//    }
//};
//
//// 2. Member Class
//class Member {
//protected:
//    int memberID;
//    std::string firstName;
//    std::string lastName;
//    std::string dateOfBirth;
//    std::string address;
//    std::string contactNumber;
//    std::string email;
//    std::string membershipStartDate;
//    std::string membershipType;
//    std::string status;
//
//public:
//    Member(int id, const std::string& firstName, const std::string& lastName, const std::string& dateOfBirth, const std::string& address,
//        const std::string& contactNumber, const std::string& email, const std::string& startDate, const std::string& type, const std::string& status)
//        : memberID(id), firstName(firstName), lastName(lastName), dateOfBirth(dateOfBirth), address(address),
//        contactNumber(contactNumber), email(email), membershipStartDate(startDate), membershipType(type), status(status) {}
//
//    virtual void displayInfo() const {
//        std::cout << "Member Info: " << firstName << " " << lastName << ", " << membershipType << std::endl;
//    }
//
//    virtual ~Member() = default;
//};
//
//class StudentMember : public Member {
//public:
//    StudentMember(int id, const std::string& firstName, const std::string& lastName, const std::string& dateOfBirth, const std::string& address,
//        const std::string& contactNumber, const std::string& email, const std::string& startDate)
//        : Member(id, firstName, lastName, dateOfBirth, address, contactNumber, email, startDate, "Student", "Active") {}
//
//    void displayInfo() const override {
//        std::cout << "Student Member Info: " << firstName << " " << lastName << ", " << membershipType << std::endl;
//    }
//};
//
//class RegularMember : public Member {
//public:
//    RegularMember(int id, const std::string& firstName, const std::string& lastName, const std::string& dateOfBirth, const std::string& address,
//        const std::string& contactNumber, const std::string& email, const std::string& startDate)
//        : Member(id, firstName, lastName, dateOfBirth, address, contactNumber, email, startDate, "Regular", "Active") {}
//
//    void displayInfo() const override {
//        std::cout << "Regular Member Info: " << firstName << " " << lastName << ", " << membershipType << std::endl;
//    }
//};
//
//// 3. Book Class
//class Book {
//protected:
//    int bookID;
//    std::string title;
//    std::string author;
//    std::string isbn;
//    int publisherID;
//    std::string publicationDate;
//    std::string language;
//
//public:
//    Book(int id, const std::string& title, const std::string& author, const std::string& isbn, int publisherID,
//        const std::string& publicationDate, const std::string& language)
//        : bookID(id), title(title), author(author), isbn(isbn), publisherID(publisherID),
//        publicationDate(publicationDate), language(language) {}
//
//    virtual void displayInfo() const {
//        std::cout << "Book Info: " << title << " by " << author << std::endl;
//    }
//
//    virtual ~Book() = default;
//};
//
//class EBook : public Book {
//public:
//    EBook(int id, const std::string& title, const std::string& author, const std::string& isbn, int publisherID,
//        const std::string& publicationDate, const std::string& language)
//        : Book(id, title, author, isbn, publisherID, publicationDate, language) {}
//
//    void displayInfo() const override {
//        std::cout << "EBook Info: " << title << " by " << author << " (eBook)" << std::endl;
//    }
//};
//
//// 4. BookInventory Class
//class BookInventory {
//protected:
//    int bookInventoryID;
//    int bookID;
//    int copiesAvailable;
//    int totalCopies;
//
//public:
//    BookInventory(int inventoryID, int bookID, int available, int total)
//        : bookInventoryID(inventoryID), bookID(bookID), copiesAvailable(available), totalCopies(total) {}
//
//    virtual void updateInventory(int copies) {
//        copiesAvailable = copies;
//        std::cout << "Updated Inventory: " << copiesAvailable << " copies available" << std::endl;
//    }
//
//    virtual ~BookInventory() = default;
//};
//
//class PhysicalBookInventory : public BookInventory {
//public:
//    PhysicalBookInventory(int inventoryID, int bookID, int available, int total)
//        : BookInventory(inventoryID, bookID, available, total) {}
//
//    void updateInventory(int copies) override {
//        copiesAvailable = copies;
//        std::cout << "Physical Book Inventory Updated: " << copiesAvailable << " copies available" << std::endl;
//    }
//};
//
//// 5. Loan Class
//class Loan {
//protected:
//    int loanID;
//    int memberID;
//    int bookID;
//    std::string loanDate;
//    std::string dueDate;
//    std::string returnDate;
//    std::string status;
//
//public:
//    Loan(int id, int memberID, int bookID, const std::string& loanDate, const std::string& dueDate, const std::string& returnDate, const std::string& status)
//        : loanID(id), memberID(memberID), bookID(bookID), loanDate(loanDate), dueDate(dueDate), returnDate(returnDate), status(status) {}
//
//    virtual void updateLoanStatus(const std::string& newStatus) {
//        status = newStatus;
//        std::cout << "Loan Status Updated: " << status << std::endl;
//    }
//
//    virtual ~Loan() = default;
//};
//
//class EBookLoan : public Loan {
//public:
//    EBookLoan(int id, int memberID, int bookID, const std::string& loanDate, const std::string& dueDate, const std::string& returnDate, const std::string& status)
//        : Loan(id, memberID, bookID, loanDate, dueDate, returnDate, status) {}
//
//    void updateLoanStatus(const std::string& newStatus) override {
//        status = newStatus;
//        std::cout << "EBook Loan Status Updated: " << status << std::endl;
//    }
//};
//
//// 6. Staff Class
//class Staff {
//protected:
//    int staffID;
//    std::string firstName;
//    std::string lastName;
//    std::string position;
//    std::string contactNumber;
//    std::string email;
//    std::string hireDate;
//    std::string status;
//
//public:
//    Staff(int id, const std::string& firstName, const std::string& lastName, const std::string& position,
//        const std::string& contactNumber, const std::string& email, const std::string& hireDate, const std::string& status)
//        : staffID(id), firstName(firstName), lastName(lastName), position(position),
//        contactNumber(contactNumber), email(email), hireDate(hireDate), status(status) {}
//
//    virtual void displayInfo() const {
//        std::cout << "Staff Info: " << firstName << " " << lastName << ", " << position << std::endl;
//    }
//
//    virtual ~Staff() = default;
//};
//
//class Librarian : public Staff {
//public:
//    Librarian(int id, const std::string& firstName, const std::string& lastName, const std::string& contactNumber,
//        const std::string& email, const std::string& hireDate)
//        : Staff(id, firstName, lastName, "Librarian", contactNumber, email, hireDate, "Active") {}
//
//    void displayInfo() const override {
//        std::cout << "Librarian Info: " << firstName << " " << lastName << ", " << position << std::endl;
//    }
//};
//
//class Assistant : public Staff {
//public:
//    Assistant(int id, const std::string& firstName, const std::string& lastName, const std::string& contactNumber,
//        const std::string& email, const std::string& hireDate)
//        : Staff(id, firstName, lastName, "Assistant", contactNumber, email, hireDate, "Active") {}
//
//    void displayInfo() const override {
//        std::cout << "Assistant Info: " << firstName << " " << lastName << ", " << position << std::endl;
//    }
//};
//
//// 7. Reservation Class
//class Reservation {
//protected:
//    int reservationID;
//    int memberID;
//    int bookID;
//    std::string reservationDate;
//    std::string status;
//
//public:
//    Reservation(int id, int memberID, int bookID, const std::string& reservationDate, const std::string& status)
//        : reservationID(id), memberID(memberID), bookID(bookID), reservationDate(reservationDate), status(status) {}
//
//    virtual void updateReservationStatus(const std::string& newStatus) {
//        status = newStatus;
//        std::cout << "Reservation Status Updated: " << status << std::endl;
//    }
//
//    virtual ~Reservation() = default;
//};
//
//class EBookReservation : public Reservation {
//public:
//    EBookReservation(int id, int memberID, int bookID, const std::string& reservationDate, const std::string& status)
//        : Reservation(id, memberID, bookID, reservationDate, status) {}
//
//    void updateReservationStatus(const std::string& newStatus) override {
//        status = newStatus;
//        std::cout << "EBook Reservation Status Updated: " << status << std::endl;
//    }
//};
//
//// 8. Fine Class
//class Fine {
//protected:
//    int fineID;
//    int loanID;
//    double amount;
//    std::string fineDate;
//    std::string status;
//
//public:
//    Fine(int id, int loanID, double amount, const std::string& fineDate, const std::string& status)
//        : fineID(id), loanID(loanID), amount(amount), fineDate(fineDate), status(status) {}
//
//    virtual void updateFineStatus(const std::string& newStatus) {
//        status = newStatus;
//        std::cout << "Fine Status Updated: " << status << std::endl;
//    }
//
//    virtual ~Fine() = default;
//};
//
//class OverdueFine : public Fine {
//public:
//    OverdueFine(int id, int loanID, double amount, const std::string& fineDate, const std::string& status)
//        : Fine(id, loanID, amount, fineDate, status) {}
//
//    void updateFineStatus(const std::string& newStatus) override {
//        status = newStatus;
//        std::cout << "Overdue Fine Status Updated: " << status << std::endl;
//    }
//};
//
//class DamageFine : public Fine {
//public:
//    DamageFine(int id, int loanID, double amount, const std::string& fineDate, const std::string& status)
//        : Fine(id, loanID, amount, fineDate, status) {}
//
//    void updateFineStatus(const std::string& newStatus) override {
//        status = newStatus;
//        std::cout << "Damage Fine Status Updated: " << status << std::endl;
//    }
//};
//
//// 9. Category Class
//class Category {
//protected:
//    int categoryID;
//    std::string name;
//    std::string description;
//
//public:
//    Category(int id, const std::string& name, const std::string& description)
//        : categoryID(id), name(name), description(description) {}
//
//    virtual void displayInfo() const {
//        std::cout << "Category Info: " << name << ", " << description << std::endl;
//    }
//
//    virtual ~Category() = default;
//};
//
//class FictionCategory : public Category {
//public:
//    FictionCategory(int id, const std::string& name, const std::string& description)
//        : Category(id, name, description) {}
//
//    void displayInfo() const override {
//        std::cout << "Fiction Category: " << name << std::endl;
//    }
//};
//
//class NonFictionCategory : public Category {
//public:
//    NonFictionCategory(int id, const std::string& name, const std::string& description)
//        : Category(id, name, description) {}
//
//    void displayInfo() const override {
//        std::cout << "Non-Fiction Category: " << name << std::endl;
//    }
//};
//
//// 10. BookCategory Class
//class BookCategory {
//protected:
//    int bookCategoryID;
//    int bookID;
//    int categoryID;
//
//public:
//    BookCategory(int id, int bookID, int categoryID)
//        : bookCategoryID(id), bookID(bookID), categoryID(categoryID) {}
//
//    virtual void displayInfo() const {
//        std::cout << "BookCategory Info: BookID " << bookID << " in CategoryID " << categoryID << std::endl;
//    }
//
//    virtual ~BookCategory() = default;
//};
//
//// 11. Publisher Class
//class Publisher {
//protected:
//    int publisherID;
//    std::string name;
//    std::string address;
//    std::string contactNumber;
//    std::string email;
//
//public:
//    Publisher(int id, const std::string& name, const std::string& address, const std::string& contactNumber, const std::string& email)
//        : publisherID(id), name(name), address(address), contactNumber(contactNumber), email(email) {}
//
//    virtual void displayInfo() const {
//        std::cout << "Publisher Info: " << name << ", " << address << std::endl;
//    }
//
//    virtual ~Publisher() = default;
//};
//
//class InternationalPublisher : public Publisher {
//public:
//    InternationalPublisher(int id, const std::string& name, const std::string& address, const std::string& contactNumber, const std::string& email)
//        : Publisher(id, name, address, contactNumber, email) {}
//
//    void displayInfo() const override {
//        std::cout << "International Publisher Info: " << name << std::endl;
//    }
//};
//
//class LocalPublisher : public Publisher {
//public:
//    LocalPublisher(int id, const std::string& name, const std::string& address, const std::string& contactNumber, const std::string& email)
//        : Publisher(id, name, address, contactNumber, email) {}
//
//    void displayInfo() const override {
//        std::cout << "Local Publisher Info: " << name << std::endl;
//    }
//};
//
//// Main function to demonstrate usage
//int main() {
//    PublicLibrary pl(1, "Central Public Library", "123 Main St", "123-456-7890", "info@publiclibrary.com", "9 AM - 5 PM");
//    pl.displayInfo();
//
//    StudentMember sm(101, "John", "Doe", "1995-05-15", "456 Elm St", "987-654-3210", "john.doe@example.com", "2023-01-01");
//    sm.displayInfo();
//
//    EBook eb(1001, "C++ Programming", "Bjarne Stroustrup", "1234567890", 201, "2024-01-01", "English");
//    eb.displayInfo();
//
//    PhysicalBookInventory pbi(3001, 1001, 10, 15);
//    pbi.updateInventory(12);
//
//    Librarian lb(201, "Alice", "Smith", "555-555-5555", "alice.smith@library.com", "2020-01-01");
//    lb.displayInfo();
//
//    OverdueFine of(4001, 2001, 25.00, "2024-08-01", "Unpaid");
//    of.updateFineStatus("Paid");
//
//    InternationalPublisher ip(301, "Global Publishing", "456 Oak St", "123-123-1234", "contact@globalpublishing.com");
//    ip.displayInfo();
//
//    return 0;
//}
//
//
//
//
//
//
//
////------AFTER INTERFACE SEGREGATION PRINCIPLE
//#include <iostream>
//#include <string>
//
//// Interface for Displayable entities
//class IDisplayable {
//public:
//    virtual void displayInfo() const = 0;
//    virtual ~IDisplayable() = default;
//};
//
//// Interface for updatable inventory entities
//class IInventoryUpdatable {
//public:
//    virtual void updateInventory(int copies) = 0;
//    virtual ~IInventoryUpdatable() = default;
//};
//
//// Interface for updatable loan entities
//class ILoanUpdatable {
//public:
//    virtual void updateLoanStatus(const std::string& newStatus) = 0;
//    virtual ~ILoanUpdatable() = default;
//};
//
//// Interface for updatable reservation entities
//class IReservationUpdatable {
//public:
//    virtual void updateReservationStatus(const std::string& newStatus) = 0;
//    virtual ~IReservationUpdatable() = default;
//};
//
//// Interface for updatable fine entities
//class IFineUpdatable {
//public:
//    virtual void updateFineStatus(const std::string& newStatus) = 0;
//    virtual ~IFineUpdatable() = default;
//};
//
//// 1. Library Class
//class Library : public IDisplayable {
//protected:
//    int libraryID;
//    std::string name;
//    std::string address;
//    std::string contactNumber;
//    std::string email;
//    std::string openingHours;
//
//public:
//    Library(int id, const std::string& name, const std::string& address, const std::string& contactNumber, const std::string& email, const std::string& openingHours)
//        : libraryID(id), name(name), address(address), contactNumber(contactNumber), email(email), openingHours(openingHours) {}
//
//    void displayInfo() const override {
//        std::cout << "Library Info: " << name << ", " << address << std::endl;
//    }
//};
//
//// Other library types implementing displayInfo
//class PublicLibrary : public Library {
//public:
//    PublicLibrary(int id, const std::string& name, const std::string& address, const std::string& contactNumber, const std::string& email, const std::string& openingHours)
//        : Library(id, name, address, contactNumber, email, openingHours) {}
//
//    void displayInfo() const override {
//        std::cout << "Public Library Info: " << name << ", " << address << std::endl;
//    }
//};
//
//class UniversityLibrary : public Library {
//public:
//    UniversityLibrary(int id, const std::string& name, const std::string& address, const std::string& contactNumber, const std::string& email, const std::string& openingHours)
//        : Library(id, name, address, contactNumber, email, openingHours) {}
//
//    void displayInfo() const override {
//        std::cout << "University Library Info: " << name << ", " << address << std::endl;
//    }
//};
//
//// 2. Member Class
//class Member : public IDisplayable {
//protected:
//    int memberID;
//    std::string firstName;
//    std::string lastName;
//    std::string dateOfBirth;
//    std::string address;
//    std::string contactNumber;
//    std::string email;
//    std::string membershipStartDate;
//    std::string membershipType;
//    std::string status;
//
//public:
//    Member(int id, const std::string& firstName, const std::string& lastName, const std::string& dateOfBirth, const std::string& address,
//        const std::string& contactNumber, const std::string& email, const std::string& startDate, const std::string& type, const std::string& status)
//        : memberID(id), firstName(firstName), lastName(lastName), dateOfBirth(dateOfBirth), address(address),
//        contactNumber(contactNumber), email(email), membershipStartDate(startDate), membershipType(type), status(status) {}
//
//    void displayInfo() const override {
//        std::cout << "Member Info: " << firstName << " " << lastName << ", " << membershipType << std::endl;
//    }
//};
//
//// Student and Regular members implementing displayInfo
//class StudentMember : public Member {
//public:
//    StudentMember(int id, const std::string& firstName, const std::string& lastName, const std::string& dateOfBirth, const std::string& address,
//        const std::string& contactNumber, const std::string& email, const std::string& startDate)
//        : Member(id, firstName, lastName, dateOfBirth, address, contactNumber, email, startDate, "Student", "Active") {}
//
//    void displayInfo() const override {
//        std::cout << "Student Member Info: " << firstName << " " << lastName << ", " << membershipType << std::endl;
//    }
//};
//
//class RegularMember : public Member {
//public:
//    RegularMember(int id, const std::string& firstName, const std::string& lastName, const std::string& dateOfBirth, const std::string& address,
//        const std::string& contactNumber, const std::string& email, const std::string& startDate)
//        : Member(id, firstName, lastName, dateOfBirth, address, contactNumber, email, startDate, "Regular", "Active") {}
//
//    void displayInfo() const override {
//        std::cout << "Regular Member Info: " << firstName << " " << lastName << ", " << membershipType << std::endl;
//    }
//};
//
//// 3. Book Class
//class Book : public IDisplayable {
//protected:
//    int bookID;
//    std::string title;
//    std::string author;
//    std::string isbn;
//    int publisherID;
//    std::string publicationDate;
//    std::string language;
//
//public:
//    Book(int id, const std::string& title, const std::string& author, const std::string& isbn, int publisherID,
//        const std::string& publicationDate, const std::string& language)
//        : bookID(id), title(title), author(author), isbn(isbn), publisherID(publisherID),
//        publicationDate(publicationDate), language(language) {}
//
//    void displayInfo() const override {
//        std::cout << "Book Info: " << title << " by " << author << std::endl;
//    }
//};
//
//// EBook implements displayInfo
//class EBook : public Book {
//public:
//    EBook(int id, const std::string& title, const std::string& author, const std::string& isbn, int publisherID,
//        const std::string& publicationDate, const std::string& language)
//        : Book(id, title, author, isbn, publisherID, publicationDate, language) {}
//
//    void displayInfo() const override {
//        std::cout << "EBook Info: " << title << " by " << author << " (eBook)" << std::endl;
//    }
//};
//
//// 4. BookInventory Class
//class BookInventory : public IInventoryUpdatable {
//protected:
//    int bookInventoryID;
//    int bookID;
//    int copiesAvailable;
//    int totalCopies;
//
//public:
//    BookInventory(int inventoryID, int bookID, int available, int total)
//        : bookInventoryID(inventoryID), bookID(bookID), copiesAvailable(available), totalCopies(total) {}
//
//    void updateInventory(int copies) override {
//        copiesAvailable = copies;
//        std::cout << "Updated Inventory: " << copiesAvailable << " copies available" << std::endl;
//    }
//};
//
//// PhysicalBookInventory implements updateInventory
//class PhysicalBookInventory : public BookInventory {
//public:
//    PhysicalBookInventory(int inventoryID, int bookID, int available, int total)
//        : BookInventory(inventoryID, bookID, available, total) {}
//
//    void updateInventory(int copies) override {
//        copiesAvailable = copies;
//        std::cout << "Physical Book Inventory Updated: " << copiesAvailable << " copies available" << std::endl;
//    }
//};
//
//// 5. Loan Class
//class Loan : public ILoanUpdatable {
//protected:
//    int loanID;
//    int memberID;
//    int bookID;
//    std::string loanDate;
//    std::string dueDate;
//    std::string returnDate;
//    std::string status;
//
//public:
//    Loan(int id, int memberID, int bookID, const std::string& loanDate, const std::string& dueDate, const std::string& returnDate, const std::string& status)
//        : loanID(id), memberID(memberID), bookID(bookID), loanDate(loanDate), dueDate(dueDate), returnDate(returnDate), status(status) {}
//
//    void updateLoanStatus(const std::string& newStatus) override {
//        status = newStatus;
//        std::cout << "Loan Status Updated: " << status << std::endl;
//    }
//};
//
//// EBookLoan implements updateLoanStatus
//class EBookLoan : public Loan {
//public:
//    EBookLoan(int id, int memberID, int bookID, const std::string& loanDate, const std::string& dueDate, const std::string& returnDate, const std::string& status)
//        : Loan(id, memberID, bookID, loanDate, dueDate, returnDate, status) {}
//
//    void updateLoanStatus(const std::string& newStatus) override {
//        status = newStatus;
//        std::cout << "EBook Loan Status Updated: " << status << std::endl;
//    }
//};
//
//// 6. Staff Class
//class Staff : public IDisplayable {
//protected:
//    int staffID;
//    std::string firstName;
//    std::string lastName;
//    std::string position;
//    std::string contactNumber;
//    std::string email;
//    std::string hireDate;
//    std::string status;
//
//public:
//    Staff(int id, const std::string& firstName, const std::string& lastName, const std::string& position,
//        const std::string& contactNumber, const std::string& email, const std::string& hireDate, const std::string& status)
//        : staffID(id), firstName(firstName), lastName(lastName), position(position),
//        contactNumber(contactNumber), email(email), hireDate(hireDate), status(status) {}
//
//    void displayInfo() const override {
//        std::cout << "Staff Info: " << firstName << " " << lastName << ", " << position << std::endl;
//    }
//};
//
//// Librarian implements displayInfo
//class Librarian : public Staff {
//public:
//    Librarian(int id, const std::string& firstName, const std::string& lastName, const std::string& contactNumber,
//        const std::string& email, const std::string& hireDate)
//        : Staff(id, firstName, lastName, "Librarian", contactNumber, email, hireDate, "Active") {}
//
//    void displayInfo() const override {
//        std::cout << "Librarian Info: " << firstName << " " << lastName << ", " << position << std::endl;
//    }
//};
//
//// Assistant implements displayInfo
//class Assistant : public Staff {
//public:
//    Assistant(int id, const std::string& firstName, const std::string& lastName, const std::string& contactNumber,
//        const std::string& email, const std::string& hireDate)
//        : Staff(id, firstName, lastName, "Assistant", contactNumber, email, hireDate, "Active") {}
//
//    void displayInfo() const override {
//        std::cout << "Assistant Info: " << firstName << " " << lastName << ", " << position << std::endl;
//    }
//};
//
//// 7. Reservation Class
//class Reservation : public IReservationUpdatable {
//protected:
//    int reservationID;
//    int memberID;
//    int bookID;
//    std::string reservationDate;
//    std::string status;
//
//public:
//    Reservation(int id, int memberID, int bookID, const std::string& reservationDate, const std::string& status)
//        : reservationID(id), memberID(memberID), bookID(bookID), reservationDate(reservationDate), status(status) {}
//
//    void updateReservationStatus(const std::string& newStatus) override {
//        status = newStatus;
//        std::cout << "Reservation Status Updated: " << status << std::endl;
//    }
//};
//
//// EBookReservation implements updateReservationStatus
//class EBookReservation : public Reservation {
//public:
//    EBookReservation(int id, int memberID, int bookID, const std::string& reservationDate, const std::string& status)
//        : Reservation(id, memberID, bookID, reservationDate, status) {}
//
//    void updateReservationStatus(const std::string& newStatus) override {
//        status = newStatus;
//        std::cout << "EBook Reservation Status Updated: " << status << std::endl;
//    }
//};
//
//// 8. Fine Class
//class Fine : public IFineUpdatable {
//protected:
//    int fineID;
//    int loanID;
//    double amount;
//    std::string fineDate;
//    std::string status;
//
//public:
//    Fine(int id, int loanID, double amount, const std::string& fineDate, const std::string& status)
//        : fineID(id), loanID(loanID), amount(amount), fineDate(fineDate), status(status) {}
//
//    void updateFineStatus(const std::string& newStatus) override {
//        status = newStatus;
//        std::cout << "Fine Status Updated: " << status << std::endl;
//    }
//};
//
//// OverdueFine implements updateFineStatus
//class OverdueFine : public Fine {
//public:
//    OverdueFine(int id, int loanID, double amount, const std::string& fineDate, const std::string& status)
//        : Fine(id, loanID, amount, fineDate, status) {}
//
//    void updateFineStatus(const std::string& newStatus) override {
//        status = newStatus;
//        std::cout << "Overdue Fine Status Updated: " << status << std::endl;
//    }
//};
//
//// DamageFine implements updateFineStatus
//class DamageFine : public Fine {
//public:
//    DamageFine(int id, int loanID, double amount, const std::string& fineDate, const std::string& status)
//        : Fine(id, loanID, amount, fineDate, status) {}
//
//    void updateFineStatus(const std::string& newStatus) override {
//        status = newStatus;
//        std::cout << "Damage Fine Status Updated: " << status << std::endl;
//    }
//};
//
//// 9. Category Class
//class Category : public IDisplayable {
//protected:
//    int categoryID;
//    std::string name;
//    std::string description;
//
//public:
//    Category(int id, const std::string& name, const std::string& description)
//        : categoryID(id), name(name), description(description) {}
//
//    void displayInfo() const override {
//        std::cout << "Category Info: " << name << ", " << description << std::endl;
//    }
//};
//
//// Fiction and NonFiction categories implementing displayInfo
//class FictionCategory : public Category {
//public:
//    FictionCategory(int id, const std::string& name, const std::string& description)
//        : Category(id, name, description) {}
//
//    void displayInfo() const override {
//        std::cout << "Fiction Category: " << name << std::endl;
//    }
//};
//
//class NonFictionCategory : public Category {
//public:
//    NonFictionCategory(int id, const std::string& name, const std::string& description)
//        : Category(id, name, description) {}
//
//    void displayInfo() const override {
//        std::cout << "Non-Fiction Category: " << name << std::endl;
//    }
//};
//
//// 10. BookCategory Class
//class BookCategory : public IDisplayable {
//protected:
//    int bookCategoryID;
//    int bookID;
//    int categoryID;
//
//public:
//    BookCategory(int id, int bookID, int categoryID)
//        : bookCategoryID(id), bookID(bookID), categoryID(categoryID) {}
//
//    void displayInfo() const override {
//        std::cout << "BookCategory Info: BookID " << bookID << " in CategoryID " << categoryID << std::endl;
//    }
//};
//
//// 11. Publisher Class
//class Publisher : public IDisplayable {
//protected:
//    int publisherID;
//    std::string name;
//    std::string address;
//    std::string contactNumber;
//    std::string email;
//
//public:
//    Publisher(int id, const std::string& name, const std::string& address, const std::string& contactNumber, const std::string& email)
//        : publisherID(id), name(name), address(address), contactNumber(contactNumber), email(email) {}
//
//    void displayInfo() const override {
//        std::cout << "Publisher Info: " << name << ", " << address << std::endl;
//    }
//};
//
//// International and Local publishers implementing displayInfo
//class InternationalPublisher : public Publisher {
//public:
//    InternationalPublisher(int id, const std::string& name, const std::string& address, const std::string& contactNumber, const std::string& email)
//        : Publisher(id, name, address, contactNumber, email) {}
//
//    void displayInfo() const override {
//        std::cout << "International Publisher Info: " << name << std::endl;
//    }
//};
//
//class LocalPublisher : public Publisher {
//public:
//    LocalPublisher(int id, const std::string& name, const std::string& address, const std::string& contactNumber, const std::string& email)
//        : Publisher(id, name, address, contactNumber, email) {}
//
//    void displayInfo() const override {
//        std::cout << "Local Publisher Info: " << name << std::endl;
//    }
//};
//
//// Main function to demonstrate usage
//int main() {
//    PublicLibrary pl(1, "Central Public Library", "123 Main St", "123-456-7890", "info@publiclibrary.com", "9 AM - 5 PM");
//    pl.displayInfo();
//
//    StudentMember sm(101, "John", "Doe", "1995-05-15", "456 Elm St", "987-654-3210", "john.doe@example.com", "2023-01-01");
//    sm.displayInfo();
//
//    EBook eb(1001, "C++ Programming", "Bjarne Stroustrup", "1234567890", 201, "2024-01-01", "English");
//    eb.displayInfo();
//
//    PhysicalBookInventory pbi(3001, 1001, 10, 15);
//    pbi.updateInventory(12);
//
//    Librarian lb(201, "Alice", "Smith", "555-555-5555", "alice.smith@library.com", "2020-01-01");
//    lb.displayInfo();
//
//    OverdueFine of(4001, 2001, 25.00, "2024-08-01", "Unpaid");
//    of.updateFineStatus("Paid");
//
//    InternationalPublisher ip(301, "Global Publishing", "456 Oak St", "123-123-1234", "contact@globalpublishing.com");
//    ip.displayInfo();
//
//    return 0;
//}
//
//
//
//
//
////------------AFTER DEPENDENCY INVERSION PRINCIPLES
//
//
//#include <iostream>
//#include <string>
//#include <memory>
//#include <vector>
//
//// Interface for Displayable entities
//class IDisplayable {
//public:
//    virtual void displayInfo() const = 0;
//    virtual ~IDisplayable() = default;
//};
//
//// Interface for updatable inventory entities
//class IInventoryUpdatable {
//public:
//    virtual void updateInventory(int copies) = 0;
//    virtual ~IInventoryUpdatable() = default;
//};
//
//// Interface for updatable loan entities
//class ILoanUpdatable {
//public:
//    virtual void updateLoanStatus(const std::string& newStatus) = 0;
//    virtual ~ILoanUpdatable() = default;
//};
//
//// Interface for updatable reservation entities
//class IReservationUpdatable {
//public:
//    virtual void updateReservationStatus(const std::string& newStatus) = 0;
//    virtual ~IReservationUpdatable() = default;
//};
//
//// Interface for updatable fine entities
//class IFineUpdatable {
//public:
//    virtual void updateFineStatus(const std::string& newStatus) = 0;
//    virtual ~IFineUpdatable() = default;
//};
//
//// 1. Library Class
//class Library : public IDisplayable {
//protected:
//    int libraryID;
//    std::string name;
//    std::string address;
//    std::string contactNumber;
//    std::string email;
//    std::string openingHours;
//
//public:
//    Library(int id, const std::string& name, const std::string& address, const std::string& contactNumber, const std::string& email, const std::string& openingHours)
//        : libraryID(id), name(name), address(address), contactNumber(contactNumber), email(email), openingHours(openingHours) {}
//
//    void displayInfo() const override {
//        std::cout << "Library Info: " << name << ", " << address << std::endl;
//    }
//};
//
//// Other library types implementing displayInfo
//class PublicLibrary : public Library {
//public:
//    PublicLibrary(int id, const std::string& name, const std::string& address, const std::string& contactNumber, const std::string& email, const std::string& openingHours)
//        : Library(id, name, address, contactNumber, email, openingHours) {}
//
//    void displayInfo() const override {
//        std::cout << "Public Library Info: " << name << ", " << address << std::endl;
//    }
//};
//
//class UniversityLibrary : public Library {
//public:
//    UniversityLibrary(int id, const std::string& name, const std::string& address, const std::string& contactNumber, const std::string& email, const std::string& openingHours)
//        : Library(id, name, address, contactNumber, email, openingHours) {}
//
//    void displayInfo() const override {
//        std::cout << "University Library Info: " << name << ", " << address << std::endl;
//    }
//};
//
//// 2. Member Class
//class Member : public IDisplayable {
//protected:
//    int memberID;
//    std::string firstName;
//    std::string lastName;
//    std::string dateOfBirth;
//    std::string address;
//    std::string contactNumber;
//    std::string email;
//    std::string membershipStartDate;
//    std::string membershipType;
//    std::string status;
//
//public:
//    Member(int id, const std::string& firstName, const std::string& lastName, const std::string& dateOfBirth, const std::string& address,
//        const std::string& contactNumber, const std::string& email, const std::string& startDate, const std::string& type, const std::string& status)
//        : memberID(id), firstName(firstName), lastName(lastName), dateOfBirth(dateOfBirth), address(address),
//        contactNumber(contactNumber), email(email), membershipStartDate(startDate), membershipType(type), status(status) {}
//
//    void displayInfo() const override {
//        std::cout << "Member Info: " << firstName << " " << lastName << ", " << membershipType << std::endl;
//    }
//};
//
//// Student and Regular members implementing displayInfo
//class StudentMember : public Member {
//public:
//    StudentMember(int id, const std::string& firstName, const std::string& lastName, const std::string& dateOfBirth, const std::string& address,
//        const std::string& contactNumber, const std::string& email, const std::string& startDate)
//        : Member(id, firstName, lastName, dateOfBirth, address, contactNumber, email, startDate, "Student", "Active") {}
//
//    void displayInfo() const override {
//        std::cout << "Student Member Info: " << firstName << " " << lastName << ", " << membershipType << std::endl;
//    }
//};
//
//class RegularMember : public Member {
//public:
//    RegularMember(int id, const std::string& firstName, const std::string& lastName, const std::string& dateOfBirth, const std::string& address,
//        const std::string& contactNumber, const std::string& email, const std::string& startDate)
//        : Member(id, firstName, lastName, dateOfBirth, address, contactNumber, email, startDate, "Regular", "Active") {}
//
//    void displayInfo() const override {
//        std::cout << "Regular Member Info: " << firstName << " " << lastName << ", " << membershipType << std::endl;
//    }
//};
//
//// 3. Book Class
//class Book : public IDisplayable {
//protected:
//    int bookID;
//    std::string title;
//    std::string author;
//    std::string isbn;
//    int publisherID;
//    std::string publicationDate;
//    std::string language;
//
//public:
//    Book(int id, const std::string& title, const std::string& author, const std::string& isbn, int publisherID,
//        const std::string& publicationDate, const std::string& language)
//        : bookID(id), title(title), author(author), isbn(isbn), publisherID(publisherID),
//        publicationDate(publicationDate), language(language) {}
//
//    void displayInfo() const override {
//        std::cout << "Book Info: " << title << " by " << author << std::endl;
//    }
//};
//
//// EBook implements displayInfo
//class EBook : public Book {
//public:
//    EBook(int id, const std::string& title, const std::string& author, const std::string& isbn, int publisherID,
//        const std::string& publicationDate, const std::string& language)
//        : Book(id, title, author, isbn, publisherID, publicationDate, language) {}
//
//    void displayInfo() const override {
//        std::cout << "EBook Info: " << title << " by " << author << " (eBook)" << std::endl;
//    }
//};
//
//// 4. BookInventory Class
//class BookInventory : public IInventoryUpdatable {
//protected:
//    int bookInventoryID;
//    int bookID;
//    int copiesAvailable;
//    int totalCopies;
//
//public:
//    BookInventory(int inventoryID, int bookID, int available, int total)
//        : bookInventoryID(inventoryID), bookID(bookID), copiesAvailable(available), totalCopies(total) {}
//
//    void updateInventory(int copies) override {
//        copiesAvailable = copies;
//        std::cout << "Updated Inventory: " << copiesAvailable << " copies available" << std::endl;
//    }
//};
//
//// PhysicalBookInventory implements updateInventory
//class PhysicalBookInventory : public BookInventory {
//public:
//    PhysicalBookInventory(int inventoryID, int bookID, int available, int total)
//        : BookInventory(inventoryID, bookID, available, total) {}
//
//    void updateInventory(int copies) override {
//        copiesAvailable = copies;
//        std::cout << "Physical Book Inventory Updated: " << copiesAvailable << " copies available" << std::endl;
//    }
//};
//
//// 5. Loan Class
//class Loan : public ILoanUpdatable {
//protected:
//    int loanID;
//    int memberID;
//    int bookID;
//    std::string loanDate;
//    std::string dueDate;
//    std::string returnDate;
//    std::string status;
//
//public:
//    Loan(int id, int memberID, int bookID, const std::string& loanDate, const std::string& dueDate, const std::string& returnDate, const std::string& status)
//        : loanID(id), memberID(memberID), bookID(bookID), loanDate(loanDate), dueDate(dueDate), returnDate(returnDate), status(status) {}
//
//    void updateLoanStatus(const std::string& newStatus) override {
//        status = newStatus;
//        std::cout << "Loan Status Updated: " << status << std::endl;
//    }
//};
//
//// EBookLoan implements updateLoanStatus
//class EBookLoan : public Loan {
//public:
//    EBookLoan(int id, int memberID, int bookID, const std::string& loanDate, const std::string& dueDate, const std::string& returnDate, const std::string& status)
//        : Loan(id, memberID, bookID, loanDate, dueDate, returnDate, status) {}
//
//    void updateLoanStatus(const std::string& newStatus) override {
//        status = newStatus;
//        std::cout << "EBook Loan Status Updated: " << status << std::endl;
//    }
//};
//
//// 6. Staff Class
//class Staff : public IDisplayable {
//protected:
//    int staffID;
//    std::string firstName;
//    std::string lastName;
//    std::string position;
//    std::string contactNumber;
//    std::string email;
//    std::string hireDate;
//    std::string status;
//
//public:
//    Staff(int id, const std::string& firstName, const std::string& lastName, const std::string& position,
//        const std::string& contactNumber, const std::string& email, const std::string& hireDate, const std::string& status)
//        : staffID(id), firstName(firstName), lastName(lastName), position(position),
//        contactNumber(contactNumber), email(email), hireDate(hireDate), status(status) {}
//
//    void displayInfo() const override {
//        std::cout << "Staff Info: " << firstName << " " << lastName << ", " << position << std::endl;
//    }
//};
//
//// Librarian implements displayInfo
//class Librarian : public Staff {
//public:
//    Librarian(int id, const std::string& firstName, const std::string& lastName, const std::string& contactNumber,
//        const std::string& email, const std::string& hireDate)
//        : Staff(id, firstName, lastName, "Librarian", contactNumber, email, hireDate, "Active") {}
//
//    void displayInfo() const override {
//        std::cout << "Librarian Info: " << firstName << " " << lastName << ", " << position << std::endl;
//    }
//};
//
//// Assistant implements displayInfo
//class Assistant : public Staff {
//public:
//    Assistant(int id, const std::string& firstName, const std::string& lastName, const std::string& contactNumber,
//        const std::string& email, const std::string& hireDate)
//        : Staff(id, firstName, lastName, "Assistant", contactNumber, email, hireDate, "Active") {}
//
//    void displayInfo() const override {
//        std::cout << "Assistant Info: " << firstName << " " << lastName << ", " << position << std::endl;
//    }
//};
//
//// 7. Reservation Class
//class Reservation : public IReservationUpdatable {
//protected:
//    int reservationID;
//    int memberID;
//    int bookID;
//    std::string reservationDate;
//    std::string status;
//
//public:
//    Reservation(int id, int memberID, int bookID, const std::string& reservationDate, const std::string& status)
//        : reservationID(id), memberID(memberID), bookID(bookID), reservationDate(reservationDate), status(status) {}
//
//    void updateReservationStatus(const std::string& newStatus) override {
//        status = newStatus;
//        std::cout << "Reservation Status Updated: " << status << std::endl;
//    }
//};
//
//// EBookReservation implements updateReservationStatus
//class EBookReservation : public Reservation {
//public:
//    EBookReservation(int id, int memberID, int bookID, const std::string& reservationDate, const std::string& status)
//        : Reservation(id, memberID, bookID, reservationDate, status) {}
//
//    void updateReservationStatus(const std::string& newStatus) override {
//        status = newStatus;
//        std::cout << "EBook Reservation Status Updated: " << status << std::endl;
//    }
//};
//
//// 8. Fine Class
//class Fine : public IFineUpdatable {
//protected:
//    int fineID;
//    int loanID;
//    double amount;
//    std::string fineDate;
//    std::string status;
//
//public:
//    Fine(int id, int loanID, double amount, const std::string& fineDate, const std::string& status)
//        : fineID(id), loanID(loanID), amount(amount), fineDate(fineDate), status(status) {}
//
//    void updateFineStatus(const std::string& newStatus) override {
//        status = newStatus;
//        std::cout << "Fine Status Updated: " << status << std::endl;
//    }
//};
//
//// OverdueFine implements updateFineStatus
//class OverdueFine : public Fine {
//public:
//    OverdueFine(int id, int loanID, double amount, const std::string& fineDate, const std::string& status)
//        : Fine(id, loanID, amount, fineDate, status) {}
//
//    void updateFineStatus(const std::string& newStatus) override {
//        status = newStatus;
//        std::cout << "Overdue Fine Status Updated: " << status << std::endl;
//    }
//};
//
//// DamageFine implements updateFineStatus
//class DamageFine : public Fine {
//public:
//    DamageFine(int id, int loanID, double amount, const std::string& fineDate, const std::string& status)
//        : Fine(id, loanID, amount, fineDate, status) {}
//
//    void updateFineStatus(const std::string& newStatus) override {
//        status = newStatus;
//        std::cout << "Damage Fine Status Updated: " << status << std::endl;
//    }
//};
//
//// 9. Category Class
//class Category : public IDisplayable {
//protected:
//    int categoryID;
//    std::string name;
//    std::string description;
//
//public:
//    Category(int id, const std::string& name, const std::string& description)
//        : categoryID(id), name(name), description(description) {}
//
//    void displayInfo() const override {
//        std::cout << "Category Info: " << name << ", " << description << std::endl;
//    }
//};
//
//// Fiction and NonFiction categories implementing displayInfo
//class FictionCategory : public Category {
//public:
//    FictionCategory(int id, const std::string& name, const std::string& description)
//        : Category(id, name, description) {}
//
//    void displayInfo() const override {
//        std::cout << "Fiction Category: " << name << std::endl;
//    }
//};
//
//class NonFictionCategory : public Category {
//public:
//    NonFictionCategory(int id, const std::string& name, const std::string& description)
//        : Category(id, name, description) {}
//
//    void displayInfo() const override {
//        std::cout << "Non-Fiction Category: " << name << std::endl;
//    }
//};
//
//// 10. BookCategory Class
//class BookCategory : public IDisplayable {
//protected:
//    int bookCategoryID;
//    int bookID;
//    int categoryID;
//
//public:
//    BookCategory(int id, int bookID, int categoryID)
//        : bookCategoryID(id), bookID(bookID), categoryID(categoryID) {}
//
//    void displayInfo() const override {
//        std::cout << "BookCategory Info: BookID " << bookID << " in CategoryID " << categoryID << std::endl;
//    }
//};
//
//// 11. Publisher Class
//class Publisher : public IDisplayable {
//protected:
//    int publisherID;
//    std::string name;
//    std::string address;
//    std::string contactNumber;
//    std::string email;
//
//public:
//    Publisher(int id, const std::string& name, const std::string& address, const std::string& contactNumber, const std::string& email)
//        : publisherID(id), name(name), address(address), contactNumber(contactNumber), email(email) {}
//
//    void displayInfo() const override {
//        std::cout << "Publisher Info: " << name << ", " << address << std::endl;
//    }
//};
//
//// International and Local publishers implementing displayInfo
//class InternationalPublisher : public Publisher {
//public:
//    InternationalPublisher(int id, const std::string& name, const std::string& address, const std::string& contactNumber, const std::string& email)
//        : Publisher(id, name, address, contactNumber, email) {}
//
//    void displayInfo() const override {
//        std::cout << "International Publisher Info: " << name << std::endl;
//    }
//};
//
//class LocalPublisher : public Publisher {
//public:
//    LocalPublisher(int id, const std::string& name, const std::string& address, const std::string& contactNumber, const std::string& email)
//        : Publisher(id, name, address, contactNumber, email) {}
//
//    void displayInfo() const override {
//        std::cout << "Local Publisher Info: " << name << std::endl;
//    }
//};
//
//// Factory class to create objects
//class EntityFactory {
//public:
//    virtual std::shared_ptr<IDisplayable> createDisplayable() const = 0;
//    virtual std::shared_ptr<IInventoryUpdatable> createInventoryUpdatable() const = 0;
//    virtual std::shared_ptr<ILoanUpdatable> createLoanUpdatable() const = 0;
//    virtual std::shared_ptr<IReservationUpdatable> createReservationUpdatable() const = 0;
//    virtual std::shared_ptr<IFineUpdatable> createFineUpdatable() const = 0;
//    virtual ~EntityFactory() = default;
//};
//
//// Concrete factory for creating specific entities
//class ConcreteEntityFactory : public EntityFactory {
//public:
//    std::shared_ptr<IDisplayable> createDisplayable() const override {
//        return std::make_shared<PublicLibrary>(1, "Central Public Library", "123 Main St", "123-456-7890", "info@publiclibrary.com", "9 AM - 5 PM");
//    }
//
//    std::shared_ptr<IInventoryUpdatable> createInventoryUpdatable() const override {
//        return std::make_shared<PhysicalBookInventory>(3001, 1001, 10, 15);
//    }
//
//    std::shared_ptr<ILoanUpdatable> createLoanUpdatable() const override {
//        return std::make_shared<EBookLoan>(2001, 101, 1001, "2023-08-01", "2023-09-01", "", "Checked Out");
//    }
//
//    std::shared_ptr<IReservationUpdatable> createReservationUpdatable() const override {
//        return std::make_shared<EBookReservation>(5001, 101, 1001, "2023-08-01", "Reserved");
//    }
//
//    std::shared_ptr<IFineUpdatable> createFineUpdatable() const override {
//        return std::make_shared<OverdueFine>(4001, 2001, 25.00, "2024-08-01", "Unpaid");
//    }
//};
//
//// Main function to demonstrate usage
//int main() {
//    ConcreteEntityFactory factory;
//
//    auto displayable = factory.createDisplayable();
//    displayable->displayInfo();
//
//    auto inventory = factory.createInventoryUpdatable();
//    inventory->updateInventory(12);
//
//    auto loan = factory.createLoanUpdatable();
//    loan->updateLoanStatus("Returned");
//
//    auto reservation = factory.createReservationUpdatable();
//    reservation->updateReservationStatus("Completed");
//
//    auto fine = factory.createFineUpdatable();
//    fine->updateFineStatus("Paid");
//
//    return 0;
//}








































/*
----------------------------------demo


This C++ code represents a Library Management System utilizing object-oriented programming (OOP) principles and design patterns, particularly focusing on interface-based design, inheritance, and the factory method pattern. Here's a breakdown:

Key Concepts and Principles:
Interfaces and Abstraction: The code defines several abstract interfaces (IDisplayable, IInventoryUpdatable, ILoanUpdatable, IReservationUpdatable, IFineUpdatable) to ensure that different classes can implement similar functionalities. These interfaces force derived classes to implement specific methods like displayInfo(), updateInventory(), updateLoanStatus(), etc.

Inheritance: The code heavily uses inheritance. For instance, Library, Member, Book, and Staff are base classes with derived classes like PublicLibrary, StudentMember, EBook, and Librarian, respectively. This allows shared behavior to be defined in the base class while specific behavior is defined in derived classes.

Polymorphism: The use of interfaces allows polymorphism. A single interface reference can point to objects of different derived types, and the correct method will be called depending on the actual object type at runtime.

Factory Design Pattern: The EntityFactory abstract class and its derived class ConcreteEntityFactory implement the factory method pattern. This pattern provides an interface for creating objects but allows derived classes to alter the type of objects that will be created. This is used here to create various library-related entities dynamically.

Encapsulation: By using protected access modifiers and member functions, the code encapsulates the state and behavior of objects, preventing unauthorized access.

Classes and Their Roles:
Library and Derived Classes: Library is a base class representing a library entity. Derived classes (PublicLibrary, UniversityLibrary) specialize the library type.

Member and Derived Classes: Member represents a library member, with specific types like StudentMember and RegularMember inheriting from it.

Book and Derived Classes: Book is a base class for different types of books, such as EBook.

Inventory Management: The BookInventory and PhysicalBookInventory classes handle the inventory details for books, implementing the IInventoryUpdatable interface for inventory updates.

Loan and Reservation Management: Loan and Reservation classes, along with their derived types (EBookLoan, EBookReservation), handle loan and reservation information. They implement interfaces to update loan and reservation statuses.

Staff and Derived Classes: Staff represents library staff, with specific roles such as Librarian and Assistant.

Fine Management: Fine and its derived classes (OverdueFine, DamageFine) represent fines related to loans, implementing the IFineUpdatable interface to update fine status.

Category and BookCategory: These classes manage book categorization within the library.

Publisher and Derived Classes: Handle publisher information, differentiating between international and local publishers.

Main Functionality:
The main() function demonstrates creating instances of various entities using the factory pattern. It shows how to utilize the polymorphic behavior by invoking methods like displayInfo(), updateInventory(), updateLoanStatus(), etc., on different objects created by the factory.

In summary, this code showcases an OOP approach to a library management system, providing a robust and flexible structure that can be easily extended to accommodate more features or different types of library entities.


*/


