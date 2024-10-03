#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Base class: Person (to represent common properties for both Customer and Lead)
class Person {
protected:
    string name;
    string contactInfo;

public:
    // Constructor
    Person(const string& name, const string& contactInfo)
        : name(name), contactInfo(contactInfo) {}

    virtual void handleInteraction() const = 0; // Pure virtual function (Polymorphism)

    // Method to get the name (for reporting purposes)
    string getName() const {
        return name;
    }

    virtual ~Person() {}
};

// Customer class derived from Person
class Customer : public Person {
private:
    vector<string> purchaseHistory;

public:
    // Constructor
    Customer(const string& name, const string& contactInfo)
        : Person(name, contactInfo) {}

    // Method to add a purchase to the history
    void addPurchase(const string& purchase) {
        purchaseHistory.push_back(purchase);
    }

    // Method to display purchase history
    void showPurchaseHistory() const {
        cout << "Purchase history for customer " << name << ":\n";
        for (const auto& purchase : purchaseHistory) {
            cout << "- " << purchase << endl;
        }
    }

    // Override handleInteraction for customer
    void handleInteraction() const override {
        cout << "Handling customer interaction with " << name << "\n";
        showPurchaseHistory();
    }
};

// Lead class derived from Person
class Lead : public Person {
private:
    string status; // e.g., "interested", "follow-up needed"

public:
    // Constructor
    Lead(const string& name, const string& contactInfo, const string& initialStatus = "new")
        : Person(name, contactInfo), status(initialStatus) {}

    // Method to change the lead status
    void updateStatus(const string& newStatus) {
        status = newStatus;
    }

    // Override handleInteraction for lead
    void handleInteraction() const override {
        cout << "Handling lead interaction with " << name << " (Status: " << status << ")\n";
    }
};

// SalesRep class
class SalesRep {
private:
    string name;
    vector<Customer*> customers; // Aggregation of customers
    vector<Lead*> leads;         // Aggregation of leads
    double salesFigures;         // Performance metrics (e.g., total sales)

public:
    // Constructor
    SalesRep(const string& name)
        : name(name), salesFigures(0.0) {}

    // Method to add a customer
    void addCustomer(Customer* customer) {
        customers.push_back(customer);
    }

    // Method to add a lead
    void addLead(Lead* lead) {
        leads.push_back(lead);
    }

    // Method to interact with all customers
    void interactWithCustomers() const {
        cout << "SalesRep " << name << " is interacting with customers:\n";
        for (const auto& customer : customers) {
            customer->handleInteraction();
        }
    }

    // Method to interact with all leads
    void interactWithLeads() const {
        cout << "SalesRep " << name << " is interacting with leads:\n";
        for (const auto& lead : leads) {
            lead->handleInteraction();
        }
    }

    // Method to update sales figures
    void updateSales(double amount) {
        salesFigures += amount;
        cout << "SalesRep " << name << " now has total sales: $" << salesFigures << endl;
    }

    // Method to display sales performance
    void showPerformance() const {
        cout << "SalesRep " << name << "'s sales performance: $" << salesFigures << endl;
    }
};

// Main function to demonstrate CRM system
int main() {
    // Creating customers
    Customer customer1("John Doe", "john.doe@example.com");
    customer1.addPurchase("Laptop");
    customer1.addPurchase("Smartphone");

    Customer customer2("Jane Smith", "jane.smith@example.com");
    customer2.addPurchase("Tablet");

    // Creating leads
    Lead lead1("Mark Brown", "mark.brown@example.com");
    lead1.updateStatus("interested");

    Lead lead2("Lucy White", "lucy.white@example.com");

    // Creating a sales representative
    SalesRep salesRep("Alice Johnson");

    // Assign customers and leads to the sales rep
    salesRep.addCustomer(&customer1);
    salesRep.addCustomer(&customer2);
    salesRep.addLead(&lead1);
    salesRep.addLead(&lead2);

    // Sales rep interacts with customers and leads
    salesRep.interactWithCustomers();
    salesRep.interactWithLeads();

    // Update sales figures
    salesRep.updateSales(1500.00);
    salesRep.updateSales(2500.00);

    // Show sales performance
    salesRep.showPerformance();

    return 0;
}
