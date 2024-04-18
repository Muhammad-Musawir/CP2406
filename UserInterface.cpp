#include <iostream>
#include <vector>
#include<random>
#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <exception>
#include "Database.h"

using namespace std;
using namespace Records;

int displayMenu();
string generateRandomString(int length);
string generateFakeAddress();
void generateNewDatabase(Database& db);
void listAllEmployees(Database& db);
void doHire(Database& db);
void doFire(Database& db);
void doPromote(Database& db);
void doDemote(Database& db);
void saveDatabaseToFile(Database& db);

int main()
{
    Database employeeDB;

    bool done = false;
    while (!done) {
        int selection = displayMenu();
        switch (selection) {
        case 0:
            done = true;
            break;
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
    {
        string filename;
        cout << "Enter the name of the file to load the database from: ";
        cin >> filename;
        employeeDB.loadFromFile(filename);
        break;
    }
            break;
        default:
            cerr << "Unknown command." << endl;
            break;
        }
    }

    return 0;
}

int displayMenu()
{
    int selection;

    cout << endl;
    cout << "Employee Database" << endl;
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

void generateNewDatabase(Database& db) {
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

void listAllEmployees(Database& db) {
    db.displayAll();
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
void loadDatabaseFromFile(Database& db) {
    std::string filename;
    std::cout << "Enter the name of the file to load the database from: ";
    std::cin >> filename;

    db.loadFromFile(filename);
}
