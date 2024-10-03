#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

// Abstract Base Class: Vehicle
class Vehicle {
protected:
    string make;
    string model;
    int year;
    double rentalRate;
    bool availability;

public:
    Vehicle(const string& make, const string& model, int year, double rentalRate)
        : make(make), model(model), year(year), rentalRate(rentalRate), availability(true) {}

    virtual double calculateRentalPrice(int days) const = 0; // Pure virtual function

    void setAvailability(bool available) {
        availability = available;
    }

    bool isAvailable() const {
        return availability;
    }

    virtual void printDetails() const {
        cout << "Make: " << make << "\nModel: " << model << "\nYear: " << year << "\nRental Rate: $" << rentalRate << "/day\n";
    }

    virtual ~Vehicle() {}
};

// Derived Class: Car
class Car : public Vehicle {
private:
    int numberOfSeats;

public:
    Car(const string& make, const string& model, int year, double rentalRate, int numberOfSeats)
        : Vehicle(make, model, year, rentalRate), numberOfSeats(numberOfSeats) {}

    double calculateRentalPrice(int days) const override {
        return rentalRate * days; // Simple calculation for demonstration
    }

    void printDetails() const override {
        Vehicle::printDetails();
        cout << "Number of Seats: " << numberOfSeats << endl;
    }
};

// Derived Class: Bike
class Bike : public Vehicle {
private:
    string type; // e.g., mountain, road

public:
    Bike(const string& make, const string& model, int year, double rentalRate, const string& type)
        : Vehicle(make, model, year, rentalRate), type(type) {}

    double calculateRentalPrice(int days) const override {
        return rentalRate * days; // Simple calculation
    }

    void printDetails() const override {
        Vehicle::printDetails();
        cout << "Type: " << type << endl;
    }
};

// Derived Class: Truck
class Truck : public Vehicle {
private:
    double loadCapacity; // in tons

public:
    Truck(const string& make, const string& model, int year, double rentalRate, double loadCapacity)
        : Vehicle(make, model, year, rentalRate), loadCapacity(loadCapacity) {}

    double calculateRentalPrice(int days) const override {
        double surcharge = (loadCapacity > 5) ? 50.0 : 0.0; // Surcharge for heavy loads
        return (rentalRate + surcharge) * days;
    }

    void printDetails() const override {
        Vehicle::printDetails();
        cout << "Load Capacity: " << loadCapacity << " tons" << endl;
    }
};

// Vehicle Rental System
class VehicleRentalSystem {
private:
    vector<shared_ptr<Vehicle>> vehicles;

public:
    void addVehicle(shared_ptr<Vehicle> vehicle) {
        vehicles.push_back(vehicle);
    }

    void displayAvailableVehicles() const {
        cout << "Available Vehicles:\n";
        for (const auto& vehicle : vehicles) {
            if (vehicle->isAvailable()) {
                vehicle->printDetails();
                cout << "-----------------------------------\n";
            }
        }
    }

    double rentVehicle(int index, int days) {
        if (index < 0 || index >= vehicles.size() || !vehicles[index]->isAvailable()) {
            cout << "Vehicle not available for rent." << endl;
            return 0.0;
        }
        vehicles[index]->setAvailability(false);
        return vehicles[index]->calculateRentalPrice(days);
    }

    void returnVehicle(int index) {
        if (index < 0 || index >= vehicles.size()) {
            cout << "Invalid vehicle index." << endl;
            return;
        }
        vehicles[index]->setAvailability(true);
    }
};

// Main function
int main() {
    VehicleRentalSystem rentalSystem;

    // Adding vehicles
    rentalSystem.addVehicle(make_shared<Car>("Toyota", "Camry", 2020, 50.0, 5));
    rentalSystem.addVehicle(make_shared<Bike>("Yamaha", "MT-07", 2021, 30.0, "Sport"));
    rentalSystem.addVehicle(make_shared<Truck>("Ford", "F-150", 2019, 80.0, 6));

    // Display available vehicles
    rentalSystem.displayAvailableVehicles();

    // Rent a vehicle
    double cost = rentalSystem.rentVehicle(0, 3); // Rent Car for 3 days
    cout << "Total Rental Cost: $" << cost << endl;

    // Return a vehicle
    rentalSystem.returnVehicle(0);

    // Display available vehicles again
    rentalSystem.displayAvailableVehicles();

    return 0;
}
