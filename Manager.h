#ifndef MANAGER_H
#define MANAGER_H

#include <string>
#include <unordered_map>

class Manager {
private:
    std::unordered_map<std::string, std::string> userCredentials; // Store username-password pairs
    bool loggedIn; // To track the login state

public:
    Manager();

    // Constructor to initialize Manager with username and password
    Manager(const std::string& username, const std::string& password);

    // User management operations
    bool createLogin(const std::string& username, const std::string& password);
    bool editLogin(const std::string& username, const std::string& newPassword);
    bool deleteLogin(const std::string& username);
    bool saveLoginCredentialsToFile(const std::string& filename) const;
    bool loadLoginCredentialsFromFile(const std::string& filename);
    bool validateLogin(const std::string& username, const std::string& password) const;

    // Method to check if manager is logged in
    bool isLoggedIn() const { return loggedIn; }

    // Method to set the login status
    void setLoggedIn(bool value) { loggedIn = value; }
};

#endif
