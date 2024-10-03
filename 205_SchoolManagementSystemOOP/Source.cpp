#include <iostream>
#include <string>
#include <vector>
#include <map>
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

    // Getters for name, age, contact information
    string getName() const { return name; }
    int getAge() const { return age; }
    string getContactInfo() const { return contactInfo; }

    virtual ~Person() {}
};

// Derived class: Teacher
class Teacher : public Person {
private:
    string subjectExpertise;
    vector<string> coursesTaught;

public:
    // Constructor
    Teacher(const string& name, int age, const string& contactInfo, const string& subjectExpertise)
        : Person(name, age, contactInfo), subjectExpertise(subjectExpertise) {}

    // Add a course to the teacher's list
    void addCourseTaught(const string& courseName) {
        coursesTaught.push_back(courseName);
    }

    // Get subject expertise
    string getSubjectExpertise() const {
        return subjectExpertise;
    }

    // Display all courses taught by the teacher
    void displayCoursesTaught() const {
        cout << "Courses taught by " << name << ":\n";
        for (const auto& course : coursesTaught) {
            cout << "- " << course << endl;
        }
    }
};

// Derived class: Student
class Student : public Person {
private:
    vector<string> enrolledCourses;
    map<string, float> grades; // Course name as key, grade as value

public:
    // Constructor
    Student(const string& name, int age, const string& contactInfo)
        : Person(name, age, contactInfo) {}

    // Enroll in a course
    void enrollInCourse(const string& courseName) {
        enrolledCourses.push_back(courseName);
    }

    // Add a grade for a course
    void addGrade(const string& courseName, float grade) {
        grades[courseName] = grade;
    }

    // Get grades for all courses
    void displayGrades() const {
        cout << "Grades for student " << name << ":\n";
        for (const auto& grade : grades) {
            cout << "Course: " << grade.first << ", Grade: " << grade.second << endl;
        }
    }

    // Display all enrolled courses
    void displayEnrolledCourses() const {
        cout << "Courses enrolled by " << name << ":\n";
        for (const auto& course : enrolledCourses) {
            cout << "- " << course << endl;
        }
    }
};

// Course class
class Course {
private:
    string courseName;
    int credits;
    Teacher* assignedTeacher; // Composition: A Course has a Teacher
    vector<Student*> enrolledStudents; // Composition: A Course has Students

public:
    // Constructor
    Course(const string& courseName, int credits)
        : courseName(courseName), credits(credits), assignedTeacher(nullptr) {}

    // Assign a teacher to the course
    void assignTeacher(Teacher* teacher) {
        assignedTeacher = teacher;
        teacher->addCourseTaught(courseName);
    }

    // Enroll a student in the course
    void enrollStudent(Student* student) {
        enrolledStudents.push_back(student);
        student->enrollInCourse(courseName);
    }

    // Display course details
    void displayCourseDetails() const {
        cout << "Course: " << courseName << "\nCredits: " << credits << "\n";
        if (assignedTeacher) {
            cout << "Taught by: " << assignedTeacher->getName() << " (Expertise: "
                << assignedTeacher->getSubjectExpertise() << ")\n";
        }
        cout << "Enrolled students:\n";
        for (const auto& student : enrolledStudents) {
            cout << "- " << student->getName() << endl;
        }
    }
};

// Main function to demonstrate the School Management System
int main() {
    // Create some teachers
    Teacher teacher1("Alice Johnson", 35, "alice.johnson@example.com", "Mathematics");
    Teacher teacher2("Bob Smith", 42, "bob.smith@example.com", "Physics");

    // Create some students
    Student student1("John Doe", 20, "john.doe@example.com");
    Student student2("Jane Smith", 19, "jane.smith@example.com");

    // Create courses
    Course mathCourse("Advanced Mathematics", 3);
    Course physicsCourse("Physics 101", 4);

    // Assign teachers to courses
    mathCourse.assignTeacher(&teacher1);
    physicsCourse.assignTeacher(&teacher2);

    // Enroll students in courses
    mathCourse.enrollStudent(&student1);
    mathCourse.enrollStudent(&student2);
    physicsCourse.enrollStudent(&student1);

    // Add grades to students
    student1.addGrade("Advanced Mathematics", 90.5);
    student1.addGrade("Physics 101", 88.0);
    student2.addGrade("Advanced Mathematics", 85.0);

    // Display course details
    mathCourse.displayCourseDetails();
    physicsCourse.displayCourseDetails();

    // Display student grades
    student1.displayGrades();
    student2.displayGrades();

    // Display teacher information
    teacher1.displayCoursesTaught();
    teacher2.displayCoursesTaught();

    return 0;
}
