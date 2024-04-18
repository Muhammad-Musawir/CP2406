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
		default:
			cerr << "Unknown command." << endl;
			break;
		}
	}

	return 0;
}

int displayMenu()
{
	// Note:
	//		One important note is that this code assumes that the user will
	//		"play nice" and type a number when a number is requested.
	//		When you read about I/O in Chapter 13, you will learn how to
	//		protect against bad input.

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
    cout << "7) Generate new database" << endl; // New option
    cout << "0) Quit" << endl;
    cout << endl;
    cout << "---> ";

    cin >> selection;

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
        Employee& emp = db.getEmployee(employeeNumber);
        emp.fire();
        cout << "Employee " << employeeNumber << " terminated." << endl;
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
// Function to generate a random string of given length
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

// Function to generate a fake address
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

// Function to generate 8000 employees
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

// Function to list all employees
void listAllEmployees(Database& db) {
    db.displayAll();
}
