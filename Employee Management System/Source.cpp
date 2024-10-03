#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include <map>
using namespace std;

// --- Abstract Employee Class ---
class Employee {
protected:
    std::string name;
    int id;
    double baseSalary;

public:
    Employee(const std::string& empName, int empID, double salary)
        : name(empName), id(empID), baseSalary(salary) {}

    virtual ~Employee() = default;

    virtual void displayDetails() const {
        std::cout << "Employee ID: " << id
            << "\nName: " << name
            << "\nBase Salary: $" << baseSalary << std::endl;
    }

    int getId() const { return id; }

    std::string getName() const { return name; }

    double getBaseSalary() const { return baseSalary; }

    virtual double calculateSalary() const = 0; // Pure virtual function

    virtual void promote(double increment) {
        baseSalary += increment;
        std::cout << name << " promoted with a salary increment of $" << increment << std::endl;
    }
};

// --- Full Time Employee Class ---
class FullTimeEmployee : public Employee {
private:
    double bonus;

public:
    FullTimeEmployee(const std::string& empName, int empID, double salary, double empBonus)
        : Employee(empName, empID, salary), bonus(empBonus) {}

    void displayDetails() const override {
        std::cout << "Full-Time Employee:\n";
        Employee::displayDetails();
        std::cout << "Bonus: $" << bonus << std::endl;
    }

    double calculateSalary() const override {
        return baseSalary + bonus;
    }

    void setBonus(double empBonus) { bonus = empBonus; }
};

// --- Part Time Employee Class ---
class PartTimeEmployee : public Employee {
private:
    double hourlyRate;
    int hoursWorked;

public:
    PartTimeEmployee(const std::string& empName, int empID, double rate, int hours)
        : Employee(empName, empID, 0), hourlyRate(rate), hoursWorked(hours) {}

    void displayDetails() const override {
        std::cout << "Part-Time Employee:\n";
        Employee::displayDetails();
        std::cout << "Hourly Rate: $" << hourlyRate
            << "\nHours Worked: " << hoursWorked << std::endl;
    }

    double calculateSalary() const override {
        return hourlyRate * hoursWorked;
    }

    void setHoursWorked(int hours) { hoursWorked = hours; }

    void setHourlyRate(double rate) { hourlyRate = rate; }
};

// --- Department Class ---
class Department {
private:
    std::string departmentName;
    std::vector<std::shared_ptr<Employee>> employees;

public:
    Department(const std::string& name) : departmentName(name) {}

    void addEmployee(const std::shared_ptr<Employee>& employee) {
        employees.push_back(employee);
        std::cout << "Employee " << employee->getName() << " added to " << departmentName << " department.\n";
    }

    void removeEmployee(int empID) {
        for (auto it = employees.begin(); it != employees.end(); ++it) {
            if ((*it)->getId() == empID) {
                std::cout << "Employee " << (*it)->getName() << " removed from " << departmentName << " department.\n";
                employees.erase(it);
                return;
            }
        }
        std::cout << "Employee ID " << empID << " not found in " << departmentName << " department.\n";
    }

    void displayDepartmentDetails() const {
        std::cout << "Department: " << departmentName << "\nEmployees:\n";
        for (const auto& employee : employees) {
            employee->displayDetails();
            std::cout << "-------------------\n";
        }
    }
};

// --- Salary Calculation Utility ---
class SalaryCalculator {
public:
    static double calculateTax(double salary) {
        // Simple tax calculation: 20% of the salary
        return salary * 0.20;
    }

    static void displaySalaryDetails(const Employee& employee) {
        double salary = employee.calculateSalary();
        double tax = calculateTax(salary);
        double netSalary = salary - tax;

        std::cout << "Salary for " << employee.getName() << ": $" << salary
            << "\nTax Deduction: $" << tax
            << "\nNet Salary: $" << netSalary << std::endl;
    }
};

// --- Employee Management System Class ---
class EmployeeManagementSystem {
private:
    std::vector<std::shared_ptr<Employee>> allEmployees;
    std::map<std::string, std::shared_ptr<Department>> departments;

public:
    // Add an employee to the system
    void addEmployee(const std::shared_ptr<Employee>& employee) {
        allEmployees.push_back(employee);
        std::cout << "Employee " << employee->getName() << " added to the system.\n";
    }

    // Remove an employee by ID
    void removeEmployee(int empID) {
        for (auto it = allEmployees.begin(); it != allEmployees.end(); ++it) {
            if ((*it)->getId() == empID) {
                std::cout << "Employee " << (*it)->getName() << " removed from the system.\n";
                allEmployees.erase(it);
                return;
            }
        }
        std::cout << "Employee ID " << empID << " not found in the system.\n";
    }

    // Update an employee's details (promote with a salary increase)
    void promoteEmployee(int empID, double increment) {
        for (const auto& employee : allEmployees) {
            if (employee->getId() == empID) {
                employee->promote(increment);
                return;
            }
        }
        std::cout << "Employee ID " << empID << " not found.\n";
    }

    // Add department to the system
    void addDepartment(const std::string& departmentName) {
        departments[departmentName] = std::make_shared<Department>(departmentName);
        std::cout << "Department " << departmentName << " created.\n";
    }

    // Assign an employee to a department
    void assignEmployeeToDepartment(int empID, const std::string& departmentName) {
        auto department = departments[departmentName];
        for (const auto& employee : allEmployees) {
            if (employee->getId() == empID) {
                department->addEmployee(employee);
                return;
            }
        }
        std::cout << "Employee ID " << empID << " not found.\n";
    }

    // Display all employee details
    void displayAllEmployees() const {
        std::cout << "All Employees:\n";
        for (const auto& employee : allEmployees) {
            employee->displayDetails();
            std::cout << "-------------------\n";
        }
    }

    // Display all departments
    /*void displayAllDepartments() const {
        for (const auto& [name, department] : departments) {
            department->displayDepartmentDetails();
            std::cout << "===================\n";
        }
    }*/

    // Calculate and display salary details for an employee
    void displayEmployeeSalaryDetails(int empID) const {
        for (const auto& employee : allEmployees) {
            if (employee->getId() == empID) {
                SalaryCalculator::displaySalaryDetails(*employee);
                return;
            }
        }
        std::cout << "Employee ID " << empID << " not found.\n";
    }
};

// --- Main Function to Demonstrate the System ---
int main() {
    EmployeeManagementSystem system;

    // Create departments
    system.addDepartment("Human Resources");
    system.addDepartment("Engineering");

    // Add full-time and part-time employees
    auto emp1 = std::make_shared<FullTimeEmployee>("Alice", 1001, 5000, 500);
    auto emp2 = std::make_shared<PartTimeEmployee>("Bob", 1002, 20, 100);
    auto emp3 = std::make_shared<FullTimeEmployee>("Charlie", 1003, 6000, 700);

    system.addEmployee(emp1);
    system.addEmployee(emp2);
    system.addEmployee(emp3);

    // Assign employees to departments
    system.assignEmployeeToDepartment(1001, "Engineering");
    system.assignEmployeeToDepartment(1002, "Human Resources");

    // Display all employee details
    system.displayAllEmployees();

    // Display salary details for an employee
    system.displayEmployeeSalaryDetails(1001);

    // Promote an employee
    system.promoteEmployee(1003, 500);

    // Display all departments
   // system.displayAllDepartments();

    return 0;
}
