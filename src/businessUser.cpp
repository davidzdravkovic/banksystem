#include "../include/businessUser.h"
#include "../include/inputHandler.h"
#include <fstream>
#include <regex>
#include <iostream>


void businessUser::createUser()
{      std :: string path;
      fullName=inputVal("Enter your full name: ");
      personalID=digitVal("Enter your personal ID: " );
      businessContact=digitVal("Enter company contact: ");
      businessAddress=digstrVal("Enter company address: ");
      path=digstrVal("Enter your file path for register number: ");
      importLicenceFromFile(path);

    }
void businessUser::print() const{
        std::cout << "Full name: " << fullName << "\n"
                  << "Personal ID: " << personalID << "\n"
                  << "Contact: " << contact << "\n"
                  << "Address: " << address << std::endl;
    }
void businessUser::importLicenceFromFile(const std::string &filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cout << "Error: Could not open file.\n";
        return;
    }

    std::string line;
    std::regex businessLicense("[A-Z]{2}-[0-9]+"); // e.g., MK-123456
    std::smatch match;

    while (std::getline(file, line)) {
        if (std::regex_search(line, match, businessLicense)) {
            registrationNumber = match.str(); // store in member variable
            std::cout << "License number imported: " << registrationNumber << "\n";
            return; // stop after first match
        }
    }

    std::cout << "No license number found in the file.\n";
}
   
