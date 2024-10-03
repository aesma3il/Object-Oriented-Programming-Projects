#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include <map>

// --- Room Class ---
class Room {
private:
    int roomNumber;
    bool available;
    double pricePerNight;

public:
    Room(int number, double price)
        : roomNumber(number), available(true), pricePerNight(price) {}

    int getRoomNumber() const { return roomNumber; }

    bool isAvailable() const { return available; }

    double getPrice() const { return pricePerNight; }

    void bookRoom() {
        if (!available) {
            throw std::runtime_error("Room is already booked.");
        }
        available = false;
    }

    void releaseRoom() {
        available = true;
    }

    void displayRoomDetails() const {
        std::cout << "Room " << roomNumber << ": $" << pricePerNight
            << " per night, " << (available ? "Available" : "Booked") << std::endl;
    }
};

// --- Customer Class ---
class Customer {
private:
    std::string name;
    std::string email;
    std::string phone;
    std::vector<int> bookingHistory;  // Stores room numbers of past bookings

public:
    Customer(const std::string& customerName, const std::string& customerEmail, const std::string& customerPhone)
        : name(customerName), email(customerEmail), phone(customerPhone) {}

    std::string getName() const { return name; }

    void addBookingToHistory(int roomNumber) {
        bookingHistory.push_back(roomNumber);
    }

    void displayCustomerDetails() const {
        std::cout << "Customer: " << name << "\nEmail: " << email << "\nPhone: " << phone << std::endl;
    }

    void displayBookingHistory() const {
        std::cout << "Booking History for " << name << ": ";
        if (bookingHistory.empty()) {
            std::cout << "No previous bookings.\n";
        }
        else {
            for (const auto& room : bookingHistory) {
                std::cout << "Room " << room << " ";
            }
            std::cout << std::endl;
        }
    }
};

// --- Abstract Payment Class (Polymorphism) ---
class Payment {
protected:
    double amount;

public:
    Payment(double amt) : amount(amt) {}
    virtual ~Payment() = default;

    virtual void processPayment() const = 0; // Pure virtual function
    double getAmount() const { return amount; }
};

// --- Credit Card Payment Class ---
class CreditCardPayment : public Payment {
private:
    std::string cardNumber;

public:
    CreditCardPayment(double amt, const std::string& cardNum)
        : Payment(amt), cardNumber(cardNum) {}

    void processPayment() const override {
        std::cout << "Processing credit card payment of $" << amount
            << " using card number: " << cardNumber << std::endl;
    }
};

// --- PayPal Payment Class ---
class PayPalPayment : public Payment {
private:
    std::string paypalEmail;

public:
    PayPalPayment(double amt, const std::string& email)
        : Payment(amt), paypalEmail(email) {}

    void processPayment() const override {
        std::cout << "Processing PayPal payment of $" << amount
            << " using PayPal email: " << paypalEmail << std::endl;
    }
};

// --- Booking Class ---
class Booking {
private:
    std::shared_ptr<Customer> customer;
    std::shared_ptr<Room> room;
    int nights;
    double totalCost;

public:
    Booking(const std::shared_ptr<Customer>& cust, const std::shared_ptr<Room>& rm, int numNights)
        : customer(cust), room(rm), nights(numNights), totalCost(rm->getPrice()* numNights) {}

    double getTotalCost() const { return totalCost; }

    void processBooking() {
        if (room->isAvailable()) {
            room->bookRoom();
            customer->addBookingToHistory(room->getRoomNumber());
            std::cout << "Booking successful! " << customer->getName() << " has booked room "
                << room->getRoomNumber() << " for " << nights << " night(s). Total cost: $" << totalCost << std::endl;
        }
        else {
            throw std::runtime_error("Room is not available.");
        }
    }
};

// --- Hotel Management System Class ---
class HotelManagementSystem {
private:
    std::vector<std::shared_ptr<Room>> rooms;
    std::vector<std::shared_ptr<Customer>> customers;

public:
    // Add a room to the hotel
    void addRoom(int roomNumber, double pricePerNight) {
        rooms.push_back(std::make_shared<Room>(roomNumber, pricePerNight));
        std::cout << "Room " << roomNumber << " added with price $" << pricePerNight << " per night.\n";
    }

    // Add a customer to the system
    void addCustomer(const std::string& name, const std::string& email, const std::string& phone) {
        customers.push_back(std::make_shared<Customer>(name, email, phone));
        std::cout << "Customer " << name << " added to the system.\n";
    }

    // Find a room by room number
    std::shared_ptr<Room> findRoom(int roomNumber) const {
        for (const auto& room : rooms) {
            if (room->getRoomNumber() == roomNumber) {
                return room;
            }
        }
        throw std::runtime_error("Room not found.");
    }

    // Find a customer by name
    std::shared_ptr<Customer> findCustomer(const std::string& name) const {
        for (const auto& customer : customers) {
            if (customer->getName() == name) {
                return customer;
            }
        }
        throw std::runtime_error("Customer not found.");
    }

    // Display all room details
    void displayAllRooms() const {
        std::cout << "Room List:\n";
        for (const auto& room : rooms) {
            room->displayRoomDetails();
        }
    }

    // Display all customer details
    void displayAllCustomers() const {
        std::cout << "Customer List:\n";
        for (const auto& customer : customers) {
            customer->displayCustomerDetails();
        }
    }

    // Process a booking
    void processBooking(const std::string& customerName, int roomNumber, int nights) {
        auto customer = findCustomer(customerName);
        auto room = findRoom(roomNumber);
        Booking booking(customer, room, nights);
        booking.processBooking();
    }

    // Process a payment (using polymorphism for different payment methods)
    void processPayment(std::unique_ptr<Payment> payment) const {
        payment->processPayment();
    }
};

// --- Main Function to Demonstrate the System ---
int main() {
    HotelManagementSystem system;

    // Add rooms to the system
    system.addRoom(101, 150);
    system.addRoom(102, 200);
    system.addRoom(103, 250);

    // Add customers to the system
    system.addCustomer("Alice", "alice@example.com", "555-1234");
    system.addCustomer("Bob", "bob@example.com", "555-5678");

    // Display all rooms
    system.displayAllRooms();

    // Display all customers
    system.displayAllCustomers();

    // Process booking for a customer
    system.processBooking("Alice", 101, 3);

    // Process payment with a credit card
    std::unique_ptr<Payment> payment1 = std::make_unique<CreditCardPayment>(450, "1234-5678-9012-3456");
    system.processPayment(std::move(payment1));

    // Process payment with PayPal
    std::unique_ptr<Payment> payment2 = std::make_unique<PayPalPayment>(600, "alice@example.com");
    system.processPayment(std::move(payment2));

    return 0;
}
