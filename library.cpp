#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
// Structure to hold book details
struct Book {
    string title;
    string author;
    int publicationYear;
};

// Structure to hold student details
struct Student {
    int id;
    string name;
    vector<Book> borrowedBooks;
};

// Class to manage the library system
class LibrarySystem {
private:

    unordered_map<int, Student> studentRecords;

public:
    
    void addStudent(int id, const string& name) {
        if (studentRecords.find(id) != studentRecords.end()) {
            cout << "Student with ID " << id << " already exists.\n";
            return;
        }
        Student newStudent = {id, name, {}};
        studentRecords[id] = newStudent;
        cout << "Student added successfully!\n";
    }

    
    void borrowBook(int studentId, const Book& book) {
        if (studentRecords.find(studentId) == studentRecords.end()) {
            cout << "Student with ID " << studentId << " does not exist.\n"; 
            return;
        }
        studentRecords[studentId].borrowedBooks.push_back(book);
        cout << "Book borrowed successfully!\n";
    }

    
    void displayStudentRecord(int studentId) const {
        auto it = studentRecords.find(studentId);
        if (it == studentRecords.end()) {
            cout << "Student with ID " << studentId << " does not exist.\n";
            return;
        }

        const Student& student = it->second;
        cout << "\nStudent ID: " << student.id
                  << "\nName: " << student.name
                  << "\nBooks Borrowed:\n";
        for (const auto& book : student.borrowedBooks) {
            cout << "  - Title: " << book.title
                      << ", Author: " << book.author
                      << ", Year: " << book.publicationYear << "\n";
        }
    }

    
    void searchStudentBinary(int id) {
        vector<int> studentIds;
        for (const auto& record : studentRecords) {
            studentIds.push_back(record.first);
        }

        sort(studentIds.begin(), studentIds.end());

        int low = 0, high = studentIds.size() - 1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (studentIds[mid] == id) {
                std::cout << "Student found:\n";
                displayStudentRecord(id);
                return;
            } else if (studentIds[mid] < id) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        cout << "Student with ID " << id << " not found.\n";
    }
};

int main() {
    LibrarySystem library;

    // Adding students
    library.addStudent(1, "Alice");
    library.addStudent(2, "Bob");
    library.addStudent(3, "Charlie");

    // Adding books to students
    library.borrowBook(1, {"C++ Primer", "Stanley B. Lippman", 2013});
    library.borrowBook(2, {"Effective Modern C++", "Scott Meyers", 2014});
    library.borrowBook(3, {"Clean Code", "Robert C. Martin", 2008});

    // Display student records
    library.displayStudentRecord(1);
    library.displayStudentRecord(2);

    // Searching for a student
    library.searchStudentBinary(2);
    library.searchStudentBinary(4);

    return 0;
}
