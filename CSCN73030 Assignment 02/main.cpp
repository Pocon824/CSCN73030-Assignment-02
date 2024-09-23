#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

typedef struct STUDENT_DATA {
	std::string firstName;
	std::string lastName;
}studentData;

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
        // Replace the first comma with a space and parse the name
        std::istringstream ss(line);
        std::string lastName, firstName;
        if (getline(ss, lastName, ',') && getline(ss, firstName)) {
            // Remove any leading spaces from firstName
            firstName.erase(0, firstName.find_first_not_of(" \t"));
            students.push_back({ firstName, lastName });
        }
    }

    file.close();
    return students;
}

int main() {

    const std::string filename = "StudentData.txt";

    // Parse the student data from the file
    std::vector<studentData> students = parseStudentData(filename);

#ifdef _DEBUG
    // Output the student data in Debug mode only
    for (const auto& student : students) {
        std::cout << "First Name: " << student.firstName << ", Last Name: " << student.lastName << std::endl;
    }
#endif

	return 1;
}