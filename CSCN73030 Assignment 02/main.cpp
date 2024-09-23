#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

//#define PRE_RELEASE

typedef struct STUDENT_DATA {
    std::string firstName;
    std::string lastName;

#ifdef PRE_RELEASE
    std::string email;
#endif
} studentData;

// Function to parse the file and store data in a vector of Student structs
std::vector<studentData> parseStudentData(const std::string& filename) {
    std::vector<studentData> students;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return students;
    }

    std::string line;
    while (getline(file, line)) {
        std::istringstream ss(line);
        std::string lastName, firstName;

        // Parse last name and first name, as before
        if (getline(ss, lastName, ',') && getline(ss, firstName, ',')) {
            // Remove any leading spaces from firstName
            firstName.erase(0, firstName.find_first_not_of(" \t"));

#ifdef PRE_RELEASE
            // In pre-release mode, also parse the email field
            std::string email;
            if (getline(ss, email)) {
                // Add student with email
                students.push_back({ firstName, lastName, email });
            }
#else
            // In non-pre-release mode, only add first and last names
            students.push_back({ firstName, lastName });
#endif
        }
    }

    file.close();
    return students;
}

int main() {

#ifdef PRE_RELEASE
    std::cout << "*ALERT* Running program in PRE_RELEASE mode *ALERT*" << std::endl;
    const std::string filename = "StudentData_Emails.txt";
#else
    std::cout << "Program running in standard mode" << std::endl;
    const std::string filename = "StudentData.txt";
#endif

    // Parse the student data from the file
    std::vector<studentData> students = parseStudentData(filename);

#ifdef _DEBUG
    // Output the student data in Debug or Pre-Release mode
    for (const auto& student : students) {
        std::cout << "First Name: " << student.firstName << ", Last Name: " << student.lastName;

#ifdef PRE_RELEASE
        // Also print the email if in pre-release mode
        std::cout << ", Email: " << student.email;
#endif

        std::cout << std::endl;
    }
#endif

    return 0;
}
