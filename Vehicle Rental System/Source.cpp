#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <algorithm>

// --- Interface for Rental Management ---
class IRentalManagement {
public:
    virtual void rentVehicle(int vehicleId, int customerId) = 0;
    virtual void returnVehicle(int vehicleId) = 0;
    virtual ~IRentalManagement() = default;
};

// --- Base Class for Vehicle ---
class Vehicle {
protected:
    int id;
    std::string brand;
    std::string model;
    double rentalRatePerDay;
    bool isAvailable;

public:
    Vehicle(int id, const std::string& brand, const std::string& model, double rate)
        : id(id), brand(brand), model(model), rentalRatePerDay(rate), isAvailable(true) {}

    virtual ~Vehicle() = default;

    virtual void displayInfo() const {
        std::cout << "ID: " << id << "\nBrand: " << brand << "\nModel: " << model
            << "\nRate: $" << rentalRatePerDay << " per day\nAvailable: " << (isAvailable ? "Yes" : "No") << std::endl;
    }

    virtual int getId() const { return id; }
    virtual double getRate() const { return rentalRatePerDay; }
    virtual bool getAvailability() const { return isAvailable; }

    virtual void setAvailability(bool availability) {
        isAvailable = availability;
    }
};

// --- Derived Classes for Vehicle Types ---
class Car : public Vehicle {
public:
    Car(int id, const std::string& brand, const std::string& model, double rate)
        : Vehicle(id, brand, model, rate) {}
};

class Bike : public Vehicle {
public:
    Bike(int id, const std::string& brand, const std::string& model, double rate)
        : Vehicle(id, brand, model, rate) {}
};

// --- Class for Customer ---
class Customer {
    int id;
    std::string name;
    std::vector<int> rentalHistory; // Store vehicle IDs rented by the customer

public:
    Customer(int id, const std::string& name) : id(id), name(name) {}

    int getId() const { return id; }
    std::string getName() const { return name; }

    void addToRentalHistory(int vehicleId) {
        rentalHistory.push_back(vehicleId);
    }

    void displayRentalHistory() const {
        std::cout << "Rental History for " << name << ":\n";
        for (int vehicleId : rentalHistory) {
            std::cout << "Vehicle ID: " << vehicleId << std::endl;
        }
    }
};

// --- Class for Vehicle Catalog Management ---
class VehicleCatalog {
    std::vector<std::shared_ptr<Vehicle>> vehicles;

public:
    void addVehicle(const std::shared_ptr<Vehicle>& vehicle) {
        vehicles.push_back(vehicle);
    }

    void removeVehicle(int id) {
        vehicles.erase(std::remove_if(vehicles.begin(), vehicles.end(),
            [id](const std::shared_ptr<Vehicle>& vehicle) { return vehicle->getId() == id; }), vehicles.end());
    }

    void displayAllVehicles() const {
        std::cout << "Vehicle Catalog:\n";
        for (const auto& vehicle : vehicles) {
            vehicle->displayInfo();
            std::cout << "-----------------------------\n";
        }
    }

    std::shared_ptr<Vehicle> getVehicleById(int id) const {
        for (const auto& vehicle : vehicles) {
            if (vehicle->getId() == id) {
                return vehicle;
            }
        }
        return nullptr;
    }
};

// --- Class for Rental Management ---
class RentalManager : public IRentalManagement {
    VehicleCatalog& vehicleCatalog;
    std::map<int, int> currentRentals; // Maps vehicleId to customerId

public:
    RentalManager(VehicleCatalog& catalog) : vehicleCatalog(catalog) {}

    void rentVehicle(int vehicleId, int customerId) override {
        auto vehicle = vehicleCatalog.getVehicleById(vehicleId);
        if (vehicle && vehicle->getAvailability()) {
            vehicle->setAvailability(false);
            currentRentals[vehicleId] = customerId;
            std::cout << "Vehicle ID " << vehicleId << " has been rented to Customer ID " << customerId << ".\n";
        }
        else {
            std::cout << "Vehicle ID " << vehicleId << " is not available for rent.\n";
        }
    }

    void returnVehicle(int vehicleId) override {
        auto vehicle = vehicleCatalog.getVehicleById(vehicleId);
        if (vehicle && !vehicle->getAvailability()) {
            vehicle->setAvailability(true);
            currentRentals.erase(vehicleId);
            std::cout << "Vehicle ID " << vehicleId << " has been returned.\n";
        }
        else {
            std::cout << "Vehicle ID " << vehicleId << " was not rented.\n";
        }
    }

    void displayRentedVehicles() const {
        std::cout << "Currently Rented Vehicles:\n";
        for (const auto& rental : currentRentals) {
            std::cout << "Vehicle ID: " << rental.first << " rented by Customer ID: " << rental.second << std::endl;
        }
    }
};

// --- Class for Customer Management ---
class CustomerManager {
    std::vector<std::shared_ptr<Customer>> customers;

public:
    void addCustomer(const std::shared_ptr<Customer>& customer) {
        customers.push_back(customer);
    }

    std::shared_ptr<Customer> getCustomerById(int id) const {
        for (const auto& customer : customers) {
            if (customer->getId() == id) {
                return customer;
            }
        }
        return nullptr;
    }

    void displayAllCustomers() const {
        std::cout << "Customer List:\n";
        for (const auto& customer : customers) {
            std::cout << "ID: " << customer->getId() << "\nName: " << customer->getName() << "\n---------------------\n";
        }
    }
};

// --- Main function to demonstrate the system ---
int main() {
    // Create vehicle catalog
    VehicleCatalog vehicleCatalog;

    // Add vehicles to the catalog
    vehicleCatalog.addVehicle(std::make_shared<Car>(1, "Toyota", "Camry", 50.0));
    vehicleCatalog.addVehicle(std::make_shared<Bike>(2, "Honda", "CBR600", 30.0));

    // Display all vehicles
    vehicleCatalog.displayAllVehicles();

    // Create customer manager and add customers
    CustomerManager customerManager;
    customerManager.addCustomer(std::make_shared<Customer>(101, "John Doe"));
    customerManager.addCustomer(std::make_shared<Customer>(102, "Jane Smith"));

    // Display all customers
    customerManager.displayAllCustomers();

    // Create rental manager
    RentalManager rentalManager(vehicleCatalog);

    // Rent vehicles
    rentalManager.rentVehicle(1, 101); // John rents the Toyota Camry
    rentalManager.rentVehicle(2, 102); // Jane rents the Honda Bike

    // Display rented vehicles
    rentalManager.displayRentedVehicles();

    // John returns the Toyota Camry
    rentalManager.returnVehicle(1);

    // Display rented vehicles after return
    rentalManager.displayRentedVehicles();

    // Display all vehicles after some rentals and returns
    vehicleCatalog.displayAllVehicles();

    // Generate and display rental history for John and Jane
    auto john = customerManager.getCustomerById(101);
    auto jane = customerManager.getCustomerById(102);

    if (john) john->displayRentalHistory();
    if (jane) jane->displayRentalHistory();

    return 0;
}
