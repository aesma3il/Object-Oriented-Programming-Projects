#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <map>
#include <algorithm>
#include <iomanip>

// --- Interface for Report Generation ---
class IReportGeneration {
public:
    virtual void generateReport() const = 0;
    virtual ~IReportGeneration() = default;
};

// --- Base Class for Students ---
class Student {
protected:
    int id;
    std::string name;
    std::string level; // Undergraduate or Graduate
public:
    Student(int id, const std::string& name, const std::string& level)
        : id(id), name(name), level(level) {}

    virtual ~Student() = default;

    virtual int getId() const {
        return id;
    }

    virtual std::string getName() const {
        return name;
    }

    virtual std::string getLevel() const {
        return level;
    }

    virtual void displayStudentInfo() const {
        std::cout << "ID: " << id << "\nName: " << name << "\nLevel: " << level << std::endl;
    }
};

// --- Derived Classes for Undergraduate and Graduate Students ---
class UndergraduateStudent : public Student {
public:
    UndergraduateStudent(int id, const std::string& name)
        : Student(id, name, "Undergraduate") {}
};

class GraduateStudent : public Student {
public:
    GraduateStudent(int id, const std::string& name)
        : Student(id, name, "Graduate") {}
};

// --- Class for Course ---
class Course {
    std::string courseName;
    int courseCredits;
public:
    Course(const std::string& name, int credits) : courseName(name), courseCredits(credits) {}

    std::string getCourseName() const {
        return courseName;
    }

    int getCredits() const {
        return courseCredits;
    }

    void displayCourseInfo() const {
        std::cout << "Course: " << courseName << ", Credits: " << courseCredits << std::endl;
    }
};

// --- Class for Grade (Encapsulation of grades) ---
class Grade {
    std::map<std::string, char> courseGrades;
public:
    void addGrade(const std::string& courseName, char grade) {
        courseGrades[courseName] = grade;
    }

    void updateGrade(const std::string& courseName, char grade) {
        if (courseGrades.find(courseName) != courseGrades.end()) {
            courseGrades[courseName] = grade;
        }
    }

    void displayGrades() const {
        std::cout << "Grades:\n";
        for (const auto& entry : courseGrades) {
            std::cout << entry.first << ": " << entry.second << std::endl;
        }
    }

    char getGrade(const std::string& courseName) const {
        if (courseGrades.find(courseName) != courseGrades.end()) {
            return courseGrades.at(courseName);
        }
        return '-';
    }
};

// --- Class for StudentManager (Single Responsibility for Managing Students) ---
class StudentManager {
    std::vector<std::shared_ptr<Student>> students;

public:
    void addStudent(const std::shared_ptr<Student>& student) {
        students.push_back(student);
    }

    void removeStudent(int id) {
        students.erase(std::remove_if(students.begin(), students.end(),
            [id](const std::shared_ptr<Student>& student) { return student->getId() == id; }), students.end());
    }

    void updateStudent(int id, const std::string& newName) {
        for (auto& student : students) {
            if (student->getId() == id) {
                student = std::make_shared<UndergraduateStudent>(id, newName);  // Assuming the student is Undergraduate for simplicity
                break;
            }
        }
    }

    std::shared_ptr<Student> getStudentById(int id) const {
        for (const auto& student : students) {
            if (student->getId() == id) {
                return student;
            }
        }
        return nullptr;
    }

    void displayAllStudents() const {
        std::cout << "All Students:\n";
        for (const auto& student : students) {
            student->displayStudentInfo();
        }
    }
};

// --- Class for Enrollment Management ---
class EnrollmentManager {
    std::map<int, std::vector<Course>> studentCourses;

public:
    void enrollCourse(int studentId, const Course& course) {
        studentCourses[studentId].push_back(course);
    }

    void displayEnrolledCourses(int studentId) const {
        if (studentCourses.find(studentId) != studentCourses.end()) {
            std::cout << "Enrolled Courses:\n";
            for (const auto& course : studentCourses.at(studentId)) {
                course.displayCourseInfo();
            }
        }
    }

    std::vector<Course> getCoursesForStudent(int studentId) const {
        if (studentCourses.find(studentId) != studentCourses.end()) {
            return studentCourses.at(studentId);
        }
        return {};
    }
};

// --- Class for Report Generation (Dependency Inversion Principle) ---
class PerformanceReport : public IReportGeneration {
    std::shared_ptr<Student> student;
    Grade grades;
    std::vector<Course> courses;

public:
    PerformanceReport(const std::shared_ptr<Student>& student, const Grade& grades, const std::vector<Course>& courses)
        : student(student), grades(grades), courses(courses) {}

    void generateReport() const override {
        std::cout << "\nPerformance Report for " << student->getName() << ":\n";
        student->displayStudentInfo();
        grades.displayGrades();
        std::cout << "Courses:\n";
        for (const auto& course : courses) {
            course.displayCourseInfo();
        }
        std::cout << "-----------------------------\n";
    }
};

// --- Main function to demonstrate the system ---
int main() {
    // Create a student manager
    StudentManager studentManager;

    // Add students
    auto student1 = std::make_shared<UndergraduateStudent>(1, "Alice");
    auto student2 = std::make_shared<GraduateStudent>(2, "Bob");
    studentManager.addStudent(student1);
    studentManager.addStudent(student2);

    // Display all students
    studentManager.displayAllStudents();

    // Create courses
    Course math("Math", 3);
    Course physics("Physics", 4);
    Course programming("Programming", 5);

    // Enrollment manager for course enrollment
    EnrollmentManager enrollmentManager;
    enrollmentManager.enrollCourse(1, math);
    enrollmentManager.enrollCourse(1, programming);
    enrollmentManager.enrollCourse(2, physics);

    // Display enrolled courses for student 1
    std::cout << "\nCourses for Student 1 (Alice):\n";
    enrollmentManager.displayEnrolledCourses(1);

    // Add grades for students
    Grade gradesStudent1;
    gradesStudent1.addGrade("Math", 'A');
    gradesStudent1.addGrade("Programming", 'B');

    Grade gradesStudent2;
    gradesStudent2.addGrade("Physics", 'A');

    // Generate performance report for student 1 (Alice)
    PerformanceReport report1(student1, gradesStudent1, enrollmentManager.getCoursesForStudent(1));
    report1.generateReport();

    // Generate performance report for student 2 (Bob)
    PerformanceReport report2(student2, gradesStudent2, enrollmentManager.getCoursesForStudent(2));
    report2.generateReport();

    return 0;
}
