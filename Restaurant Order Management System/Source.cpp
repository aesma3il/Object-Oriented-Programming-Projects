#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <iomanip>

// --- Interface for Order Processing ---
class IOrderProcessing {
public:
    virtual void processOrder() = 0;
    virtual ~IOrderProcessing() = default;
};

// --- Base Class for MenuItem ---
class MenuItem {
protected:
    std::string name;
    double price;
public:
    MenuItem(const std::string& name, double price) : name(name), price(price) {}

    virtual double getPrice() const {
        return price;
    }

    virtual std::string getName() const {
        return name;
    }

    virtual ~MenuItem() = default;
};

// --- Derived Classes for Different Menu Categories ---
class Drink : public MenuItem {
public:
    Drink(const std::string& name, double price) : MenuItem(name, price) {}
};

class MainCourse : public MenuItem {
public:
    MainCourse(const std::string& name, double price) : MenuItem(name, price) {}
};

class Dessert : public MenuItem {
public:
    Dessert(const std::string& name, double price) : MenuItem(name, price) {}
};

// --- Menu Class to Handle Menu Management ---
class Menu {
    std::vector<std::shared_ptr<MenuItem>> items;

public:
    void addItem(const std::shared_ptr<MenuItem>& item) {
        items.push_back(item);
    }

    void removeItem(const std::string& itemName) {
        items.erase(std::remove_if(items.begin(), items.end(),
            [&itemName](const std::shared_ptr<MenuItem>& item) { return item->getName() == itemName; }), items.end());
    }

    void displayMenu() const {
        std::cout << "Restaurant Menu:\n";
        for (const auto& item : items) {
            std::cout << "- " << item->getName() << ": $" << std::fixed << std::setprecision(2) << item->getPrice() << "\n";
        }
    }

    std::shared_ptr<MenuItem> findItem(const std::string& itemName) const {
        for (const auto& item : items) {
            if (item->getName() == itemName)
                return item;
        }
        return nullptr;
    }
};

// --- Order Class to Handle Orders ---
class Order {
    std::vector<std::shared_ptr<MenuItem>> orderedItems;

public:
    void addItem(const std::shared_ptr<MenuItem>& item) {
        orderedItems.push_back(item);
    }

    double calculateTotal() const {
        double total = 0;
        for (const auto& item : orderedItems) {
            total += item->getPrice();
        }
        return total;
    }

    void displayOrder() const {
        std::cout << "Order Details:\n";
        for (const auto& item : orderedItems) {
            std::cout << "- " << item->getName() << ": $" << std::fixed << std::setprecision(2) << item->getPrice() << "\n";
        }
        std::cout << "Total: $" << std::fixed << std::setprecision(2) << calculateTotal() << "\n";
    }
};

// --- Bill Class for Generating Bills ---
class Bill {
    std::shared_ptr<Order> order;

public:
    Bill(const std::shared_ptr<Order>& order) : order(order) {}

    void generateBill() {
        std::cout << "Generating Bill...\n";
        order->displayOrder();
    }
};

// --- Customer Class ---
class Customer {
    std::string name;
public:
    Customer(const std::string& name) : name(name) {}

    std::string getName() const {
        return name;
    }
};

// --- Dine-in Order Class (Polymorphism applied) ---
class DineInOrder : public Order, public IOrderProcessing {
    Customer customer;
public:
    DineInOrder(const std::string& customerName) : customer(customerName) {}

    void processOrder() override {
        std::cout << "Processing dine-in order for " << customer.getName() << "\n";
    }
};

// --- Takeout Order Class (Polymorphism applied) ---
class TakeoutOrder : public Order, public IOrderProcessing {
    Customer customer;
public:
    TakeoutOrder(const std::string& customerName) : customer(customerName) {}

    void processOrder() override {
        std::cout << "Processing takeout order for " << customer.getName() << "\n";
    }
};

// --- OrderManager Class (Single Responsibility and Open/Closed Principles) ---
class OrderManager {
    std::vector<std::shared_ptr<IOrderProcessing>> orders;

public:
    void takeOrder(const std::shared_ptr<IOrderProcessing>& order) {
        orders.push_back(order);
        order->processOrder();
    }

    void processAllOrders() {
        for (const auto& order : orders) {
            order->processOrder();
        }
    }
};

// --- Main Function to Demonstrate the System ---
int main() {
    // Create a menu
    Menu menu;
    menu.addItem(std::make_shared<Drink>("Coca-Cola", 2.50));
    menu.addItem(std::make_shared<MainCourse>("Steak", 15.00));
    menu.addItem(std::make_shared<Dessert>("Ice Cream", 5.00));

    // Display the menu
    menu.displayMenu();

    // Create an order manager
    OrderManager orderManager;

    // Create and process a dine-in order
    auto dineInOrder = std::make_shared<DineInOrder>("Alice");
    dineInOrder->addItem(menu.findItem("Steak"));
    dineInOrder->addItem(menu.findItem("Coca-Cola"));
    orderManager.takeOrder(dineInOrder);

    // Create and process a takeout order
    auto takeoutOrder = std::make_shared<TakeoutOrder>("Bob");
    takeoutOrder->addItem(menu.findItem("Ice Cream"));
    orderManager.takeOrder(takeoutOrder);

    // Generate bills
    Bill dineInBill(dineInOrder);
    Bill takeoutBill(takeoutOrder);
    dineInBill.generateBill();
    takeoutBill.generateBill();

    return 0;
}
