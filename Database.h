#pragma once

#include <iostream>
#include <vector>
#include "Employee.h"

namespace Records {
    const int kFirstEmployeeNumber = 1000;

    class Database {
    public:
        Employee& addEmployee(const std::string& firstName,
                              const std::string& middleName,
                              const std::string& lastName,
                              const std::string& address);
        Employee& getEmployee(int employeeNumber);
        Employee& getEmployee(const std::string& firstName,
                              const std::string& lastName);

        void displayAll() const;
        void fireEmployee(int employeeNumber);
        void displayCurrent() const;
        void displayFormer() const;
        void save(std::ofstream& outputFile);
        void loadFromFile(const std::string& filename);
        void editEmployee(int employeeNumber, const std::string& address, int salary, bool hired);
        std::vector<Employee> searchByFirstName(const std::string& firstName) const;
        std::vector<Employee> searchByMiddleName(const std::string& middleName) const;
        std::vector<Employee> searchByLastName(const std::string& lastName) const;
        std::vector<Employee> searchByAddress(const std::string& address) const;

    private:
        std::vector<Employee> mEmployees;
        int mNextEmployeeNumber = kFirstEmployeeNumber;
    };
}
