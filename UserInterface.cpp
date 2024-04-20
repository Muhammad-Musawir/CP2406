#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <exception>
#include "Database.h"
#include "Manager.h" // Include Manager header

using namespace std;
using namespace Records;

// Function prototypes
int displayManagerMenu(); 
int displayEmployeeMenu();
string generateRandomString(int length);
string generateFakeAddress();
void generateNewDatabase(Database& db);
void listAllEmployees(Database& db);
void doHire(Database& db);
void doFire(Database& db);
void doPromote(Database& db);
void saveDatabaseToFile(Database& db);
void loadDatabaseFromFile(Database& db);
void editEmployee(Database& db);
void searchEmployee(Database& db);
void managerLogin(Manager& manager); 
void managerLogout(Manager& manager);

int main()
{
    Database employeeDB;
    Manager manager("admin", "admin123");// Create Manager object

    bool done = false;
    bool loggedIn = false;
    bool isManager = false;

    while (!done) {
        if (!loggedIn) {
            int loginChoice;
            cout << "Login as:" << endl;
            cout << "1) Manager" << endl;
            cout << "2) Employee" << endl;
            cout << "0) Quit" << endl;
            cout << "---> ";
            cin >> loginChoice;

            switch (loginChoice) {
                case 1: {
                    managerLogin(manager);
                    if (manager.isLoggedIn()) {
                        loggedIn = true;
                        isManager = true;
                    }
                    break;
                }
                case 2: {
                    loggedIn = true;
                    isManager = false;
                    break;
                }
                case 0: {
                    done = true;
                    break;
                }
                default: {
                    cerr << "Invalid choice. Please try again." << endl;
                    break;
                }
            }
        } else {
            if (isManager) {
                // Manager menu options
                int selection;
                while (true) {
                    selection = displayManagerMenu();
                    if (selection == 0) {
                        manager.logout(); // Logout manager
                        loggedIn = false; // Set loggedIn to false
                        break;
                    } else if (selection == 12) {
                        manager.logout(); // Logout manager
                        loggedIn = false; // Set loggedIn to false
                        break;
                    }
                    // Handle other manager menu options
                    switch (selection) {
                        case 1:
                            doHire(employeeDB);
                            break;
                        case 2:
                            doFire(employeeDB);
                            break;
                        case 3:
                            doPromote(employeeDB);
                            break;
                        case 4:
                            employeeDB.displayAll();
                            break;
                        case 5:
                            employeeDB.displayCurrent();
                            break;
                        case 6:
                            employeeDB.displayFormer();
                            break;
                        case 7:
                            generateNewDatabase(employeeDB);
                            break;
                        case 8:
                            saveDatabaseToFile(employeeDB);
                            break;
                        case 9:
                            loadDatabaseFromFile(employeeDB);
                            break;
                        case 10:
                            editEmployee(employeeDB);
                            break;
                        case 11:
                            searchEmployee(employeeDB);
                            break;
                        default:
                            cerr << "Unknown command." << endl;
                            break;
                    }
                }
            } else {
                // Employee menu options
                int selection;
while (true) {
    selection = displayEmployeeMenu();
    if (selection == 0) {
        done = true;
        break;
    }

    // Handle employee menu options
    switch (selection) {
        case 1:
            employeeDB.displayAll();
            break;
        case 2:
            employeeDB.displayCurrent();
            break;
        case 3:
            employeeDB.displayFormer();
            break;
        case 4:
            searchEmployee(employeeDB);
            break;
        default:
            cerr << "Unknown command." << endl;
            break;
                  }
            }
            }
        }
    }

    return 0;
}


int displayManagerMenu()
{
    int selection;

    cout << endl;
    cout << "Manager Menu" << endl;
    cout << "-----------------" << endl;
    cout << "1) Hire a new employee" << endl;
    cout << "2) Fire an employee" << endl;
    cout << "3) Promote an employee" << endl;
    cout << "4) List all employees" << endl;
    cout << "5) List all current employees" << endl;
    cout << "6) List all former employees" << endl;
    cout << "7) Generate new database" << endl;
    cout << "8) Save database to file" << endl;
    cout << "9) Load database from file" << endl;
    cout << "10) Edit employee" << endl;
    cout << "11) Search employee" << endl;
    cout << "12) Manager Logout" << endl;
    cout << "0) Quit" << endl;
    cout << endl;
    cout << "---> ";

    cin >> selection;

    // Clear the input buffer to prevent any leftover characters
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return selection;
}

int displayEmployeeMenu()
{
    int selection;

    cout << endl;
    cout << "Employee Menu" << endl;
    cout << "-----------------" << endl;
    cout << "1) List all employees" << endl;
    cout << "2) List all current employees" << endl;
    cout << "3) List all former employees" << endl;
    cout << "4) Search employee" << endl;
    cout << "0) Quit" << endl;
    cout << endl;
    cout << "---> ";

    cin >> selection;

    // Clear the input buffer to prevent any leftover characters
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return selection;
}

void doHire(Database& db)
{
    string firstName;
    string middleName = "";
    string lastName;
    string address = "";

    cout << "First name? ";
    cin >> firstName;
    cout << "Last name? ";
    cin >> lastName;

    db.addEmployee(firstName, middleName, lastName, address);
}

void doFire(Database& db)
{
    int employeeNumber;

    cout << "Employee number? ";
    cin >> employeeNumber;

    try {
        db.fireEmployee(employeeNumber);
    } catch (const std::logic_error& exception) {
        cerr << "Unable to terminate employee: " << exception.what() << endl;
    }
}

void doPromote(Database& db)
{
    int employeeNumber;
    int raiseAmount;

    cout << "Employee number? ";
    cin >> employeeNumber;
    cout << "How much of a raise? ";
    cin >> raiseAmount;

    try {
        Employee& emp = db.getEmployee(employeeNumber);
        emp.promote(raiseAmount);
    } catch (const std::logic_error& exception) {
        cerr << "Unable to promote employee: " << exception.what() << endl;
    }
}

void searchEmployee(Database& db) {
    int searchOption;
    cout << "How would you like to search?" << endl;
    cout << "1) By first name" << endl;
    cout << "2) By middle name" << endl;
    cout << "3) By last name" << endl;
    cout << "4) By address" << endl;
    cout << "---> ";
    cin >> searchOption;

    string searchText;
    cout << "Enter the search text: ";
    cin >> searchText;

    switch (searchOption) {
        case 1: {
            auto results = db.searchByFirstName(searchText);
            cout << "Search results by first name:" << endl;
            for (const auto& employee : results) {
                employee.display();
            }
            break;
        }
        case 2: {
            auto results = db.searchByMiddleName(searchText);
            cout << "Search results by middle name:" << endl;
            for (const auto& employee : results) {
                employee.display();
            }
            break;
        }
        case 3: {
            auto results = db.searchByLastName(searchText);
            cout << "Search results by last name:" << endl;
            for (const auto& employee : results) {
                employee.display();
            }
            break;
        }
        case 4: {
            auto results = db.searchByAddress(searchText);
            cout << "Search results by address:" << endl;
            for (const auto& employee : results) {
                employee.display();
            }
            break;
        }
        default:
            cerr << "Invalid search option." << endl;
            break;
    }
}


void generateNewDatabase(Database& db)
{
    const int numberOfEmployees = 8000;
    const int numberOfFirstNames = 20;
    const int numberOfMiddleNames = 20;
    const int numberOfLastNames = 20;

    for (int i = 0; i < numberOfEmployees; ++i) {
        string firstName = "First" + to_string(i % numberOfFirstNames);
        string middleName = "Middle" + to_string(i % numberOfMiddleNames);
        string lastName = "Last" + to_string(i % numberOfLastNames);
        string address = generateFakeAddress(); 
        db.addEmployee(firstName, middleName, lastName, address);
    }

    cout << "New database generated with 8000 employees." << endl;
}

void saveDatabaseToFile(Database& db)
{
    string filename;
    cout << "Enter the name of the file to save the database: ";
    cin >> filename;

    ofstream outputFile(filename);
    if (outputFile.is_open()) {
        db.save(outputFile);
        cout << "Database saved to " << filename << endl;
    } else {
        cerr << "Unable to open file for writing." << endl;
    }
}

void loadDatabaseFromFile(Database& db)
{
    string filename;
    cout << "Enter the name of the file to load the database from: ";
    cin >> filename;
    db.loadFromFile(filename);
}

void editEmployee(Database& db)
{
    int employeeNumber;
    cout << "Enter the employee number you want to edit: ";
    cin >> employeeNumber;
    cout << "Enter the new address: ";
    string address;
    cin >> address;
    cout << "Enter the new salary: ";
    int salary;
    cin >> salary;
    cout << "Is the employee hired? (1 for yes, 0 for no): ";
    int hireStatus;
    cin >> hireStatus;
    db.editEmployee(employeeNumber, address, salary, hireStatus == 1);
}

void managerLogin(Manager& manager) {
    string username, password;
    cout << "Enter manager username: ";
    cin >> username;
    cout << "Enter manager password: ";
    cin >> password;

    if (manager.validateLogin(username, password)) {
        cout << "Manager login successful." << endl;
        manager.setIsLoggedIn(true); 
        manager.setIsManager(true); 
    } else {
        cerr << "Invalid manager username or password." << endl;
    }
}
void managerLogout(Manager& manager) {
    manager.logout();
    cout << "Manager logout successful." << endl;
}


string generateRandomString(int length) {
    static const string charset = "abcdefghijklmnopqrstuvwxyz";
    static default_random_engine randomEngine{random_device{}()};
    static uniform_int_distribution<int> distribution(0, charset.length() - 1);
    string result;

    for (int i = 0; i < length; ++i) {
        result += charset[distribution(randomEngine)];
    }

    return result;
}

string generateFakeAddress() {
    static const vector<string> streetNames = {"Main St", "Broadway", "Elm St", "Maple Ave", "Oak St"};
    static const vector<string> cities = {"New York", "Los Angeles", "Chicago", "Houston", "Phoenix"};
    static const vector<string> states = {"NY", "CA", "IL", "TX", "AZ"};
    static default_random_engine randomEngine{random_device{}()};
    static uniform_int_distribution<int> streetDist(1, 1000);
    static uniform_int_distribution<int> cityStateDist(0, cities.size() - 1);

    string address = to_string(streetDist(randomEngine)) + " " +
                     streetNames[randomEngine() % streetNames.size()] + ", " +
                     cities[cityStateDist(randomEngine)] + ", " +
                     states[cityStateDist(randomEngine)];

    return address;
}
