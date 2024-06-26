#include "Database.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdexcept>

using namespace std;

namespace Records {

    // Definition of save method
    void Database::save(ofstream& outputFile) {
        for (const auto& employee : mEmployees) {
            outputFile << employee.getFirstName() << " "
                       << employee.getMiddleName() << " "
                       << employee.getLastName() << " "
                       << employee.getAddress() << "\n";
        }
    }

    Employee& Database::addEmployee(const string& firstName,
        const std::string& middleName,
        const string& lastName,
        const std::string& address)
    {
        Employee theEmployee(firstName, middleName, lastName);
        theEmployee.setAddress(address);
        theEmployee.setEmployeeNumber(mNextEmployeeNumber++);
        theEmployee.hire();
        mEmployees.push_back(theEmployee);

        return mEmployees[mEmployees.size() - 1];
    }

    Employee& Database::getEmployee(int employeeNumber)
    {
        for (auto& employee : mEmployees) {
            if (employee.getEmployeeNumber() == employeeNumber) {
                return employee;
            }
        }
        throw logic_error("No employee found.");
    }

    Employee& Database::getEmployee(const string& firstName, const string& lastName)
    {
        for (auto& employee : mEmployees) {
            if (employee.getFirstName() == firstName &&
                employee.getLastName() == lastName) {
                    return employee;
            }
        }
        throw logic_error("No employee found.");
    }

    void Database::displayAll() const
    {
        for (const auto& employee : mEmployees) {
            employee.display();
        }
    }

    void Database::displayCurrent() const
    {
        for (const auto& employee : mEmployees) {
            if (employee.isHired())
                employee.display();
        }
    }

    void Database::displayFormer() const
    {
        for (const auto& employee : mEmployees) {
            if (!employee.isHired())
                employee.display();
        }
    }
    void Database::fireEmployee(int employeeNumber)
{
    auto it = std::find_if(mEmployees.begin(), mEmployees.end(), [employeeNumber](const Employee& employee) {
        return employee.getEmployeeNumber() == employeeNumber;
    });

    if (it != mEmployees.end()) {
        it->fire();
        mEmployees.erase(it);
        std::cout << "Employee " << employeeNumber << " terminated." << std::endl;
    } else {
        std::cout << "Employee " << employeeNumber << " not found." << std::endl;
    }

}
} 
