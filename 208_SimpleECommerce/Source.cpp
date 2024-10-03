#include <iostream>
#include <vector>
#include <memory>
#include <iomanip>

class Product {
protected:
    std::string name;
    double price;
    int stockQuantity;

public:
    Product(const std::string& name, double price, int stock)
        : name(name), price(price), stockQuantity(stock) {}

    virtual ~Product() {}

    virtual double getPrice() const { return price; }
    virtual std::string getName() const { return name; }
    virtual void adjustStock(int quantity) {
        stockQuantity -= quantity;
    }

    virtual void display() const {
        std::cout << name << " - $" << std::fixed << std::setprecision(2)
            << price << " (Stock: " << stockQuantity << ")\n";
    }

    int getStockQuantity() const {
        return stockQuantity;
    }
};

class PhysicalProduct : public Product {
private:
    double shippingCost;

public:
    PhysicalProduct(const std::string& name, double price, int stock, double shippingCost)
        : Product(name, price, stock), shippingCost(shippingCost) {}

    double getShippingCost() const {
        return shippingCost;
    }

    double getPrice() const override {
        return price + shippingCost;
    }

    void display() const override {
        Product::display();
        std::cout << "Shipping Cost: $" << shippingCost << "\n";
    }
};

class DigitalProduct : public Product {
public:
    DigitalProduct(const std::string& name, double price, int stock)
        : Product(name, price, stock) {}

    void display() const override {
        Product::display();
        std::cout << "This is a digital product. No shipping cost.\n";
    }
};

class Customer {
private:
    std::string name;
    std::string email;
    std::vector<std::shared_ptr<Product>> shoppingCart;

public:
    Customer(const std::string& name, const std::string& email)
        : name(name), email(email) {}

    void addToCart(std::shared_ptr<Product> product) {
        shoppingCart.push_back(product);
    }

    void viewCart() const {
        std::cout << name << "'s Shopping Cart:\n";
        for (const auto& product : shoppingCart) {
            product->display();
        }
    }

    const std::vector<std::shared_ptr<Product>>& getCart() const {
        return shoppingCart;
    }
};

class Order {
private:
    std::vector<std::shared_ptr<Product>> products;

public:
    void addProduct(std::shared_ptr<Product> product) {
        products.push_back(product);
    }

    double calculateTotal() const {
        double total = 0;
        for (const auto& product : products) {
            total += product->getPrice();
        }
        return total;
    }

    void handlePayment() {
        double total = calculateTotal();
        std::cout << "Total amount to pay: $" << std::fixed << std::setprecision(2) << total << "\n";
        // Here, you would implement actual payment handling
    }

    void displayOrder() const {
        std::cout << "Order Summary:\n";
        for (const auto& product : products) {
            product->display();
        }
        std::cout << "Total: $" << std::fixed << std::setprecision(2) << calculateTotal() << "\n";
    }
};

int main() {
    // Create products
    auto book = std::make_shared<PhysicalProduct>("C++ Programming", 29.99, 10, 5.00);
    auto eBook = std::make_shared<DigitalProduct>("Learn C++", 19.99, 50);

    // Create a customer
    Customer customer("John Doe", "john.doe@example.com");

    // Add products to the customer's cart
    customer.addToCart(book);
    customer.addToCart(eBook);

    // View the shopping cart
    customer.viewCart();

    // Create an order and process payment
    Order order;
    for (const auto& product : customer.getCart()) {
        order.addProduct(product);
    }
    order.displayOrder();
    order.handlePayment();

    return 0;
}
