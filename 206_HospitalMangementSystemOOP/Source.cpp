#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Base class: Person
class Person {
protected:
    string name;
    int age;
    string contactInfo;

public:
    // Constructor
    Person(const string& name, int age, const string& contactInfo)
        : name(name), age(age), contactInfo(contactInfo) {}

    // Virtual function to print person details
    virtual void printDetails() const {
        cout << "Name: " << name << "\nAge: " << age << "\nContact: " << contactInfo << endl;
    }

    virtual ~Person() {}
};

// Derived class: Doctor
class Doctor : public Person {
private:
    string specialization;
    string workSchedule;

public:
    // Constructor
    Doctor(const string& name, int age, const string& contactInfo, const string& specialization, const string& workSchedule)
        : Person(name, age, contactInfo), specialization(specialization), workSchedule(workSchedule) {}

    // Get the specialization
    string getSpecialization() const {
        return specialization;
    }

    // Get the work schedule
    string getWorkSchedule() const {
        return workSchedule;
    }

    // Override the printDetails method
    void printDetails() const override {
        cout << "Doctor Details:\n";
        Person::printDetails();
        cout << "Specialization: " << specialization << "\nWork Schedule: " << workSchedule << endl;
    }
};

// Derived class: Patient
class Patient : public Person {
private:
    string medicalHistory;
    string prescriptionDetails;

public:
    // Constructor
    Patient(const string& name, int age, const string& contactInfo)
        : Person(name, age, contactInfo), medicalHistory("None"), prescriptionDetails("None") {}

    // Encapsulated method to add medical history
    void addMedicalHistory(const string& history) {
        medicalHistory = history;
    }

    // Encapsulated method to get medical history
    string getMedicalHistory() const {
        return medicalHistory;
    }

    // Encapsulated method to add prescription details
    void addPrescription(const string& prescription) {
        prescriptionDetails = prescription;
    }

    // Encapsulated method to get prescription details
    string getPrescriptionDetails() const {
        return prescriptionDetails;
    }

    // Override the printDetails method
    void printDetails() const override {
        cout << "Patient Details:\n";
        Person::printDetails();
        cout << "Medical History: " << medicalHistory << "\nPrescription: " << prescriptionDetails << endl;
    }
};

// Aggregation class: Appointment
class Appointment {
private:
    string appointmentDate;
    string appointmentTime;
    string reasonForVisit;
    Doctor* assignedDoctor;
    Patient* assignedPatient;

public:
    // Constructor
    Appointment(const string& date, const string& time, const string& reason, Doctor* doctor, Patient* patient)
        : appointmentDate(date), appointmentTime(time), reasonForVisit(reason), assignedDoctor(doctor), assignedPatient(patient) {}

    // Display appointment details
    void printAppointmentDetails() const {
        cout << "Appointment Details:\n";
        cout << "Date: " << appointmentDate << "\nTime: " << appointmentTime << "\nReason: " << reasonForVisit << endl;
        cout << "Doctor Info:\n";
        assignedDoctor->printDetails();
        cout << "Patient Info:\n";
        assignedPatient->printDetails();
    }
};

// Main function to demonstrate the Hospital Management System
int main() {
    // Create a doctor
    Doctor doctor1("Dr. Alice Smith", 45, "alice.smith@hospital.com", "Cardiology", "9 AM - 5 PM");

    // Create a patient
    Patient patient1("John Doe", 30, "john.doe@example.com");
    patient1.addMedicalHistory("High Blood Pressure");
    patient1.addPrescription("Medication A");

    // Create an appointment
    Appointment appointment1("2024-09-22", "10:00 AM", "Routine Checkup", &doctor1, &patient1);

    // Print the appointment details
    appointment1.printAppointmentDetails();

    return 0;
}
