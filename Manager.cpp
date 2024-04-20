#include "Manager.h"
#include <fstream>

Manager::Manager() : loggedIn(false) {}

Manager::Manager(const std::string& username, const std::string& password) {
    // Initialize Manager object with provided username and password
    userCredentials[username] = password;
    loggedIn = false; // Initially not logged in
}

bool Manager::createLogin(const std::string& username, const std::string& password) {
    // Check if the username already exists
    if (userCredentials.find(username) != userCredentials.end()) {
        return false; // Username already exists
    }
    // Add the new username-password pair to the map
    userCredentials[username] = password;
    return true;
}

bool Manager::editLogin(const std::string& username, const std::string& newPassword) {
    // Check if the username exists
    if (userCredentials.find(username) == userCredentials.end()) {
        return false; // Username does not exist
    }
    // Update the password associated with the username
    userCredentials[username] = newPassword;
    return true;
}

bool Manager::deleteLogin(const std::string& username) {
    // Check if the username exists
    if (userCredentials.find(username) == userCredentials.end()) {
        return false; // Username does not exist
    }
    // Remove the username-password pair from the map
    userCredentials.erase(username);
    return true;
}

bool Manager::saveLoginCredentialsToFile(const std::string& filename) const {
    // Open the file for writing
    std::ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        return false; // Failed to open file
    }
    // Write each username-password pair to the file
    for (const auto& pair : userCredentials) {
        outputFile << pair.first << " " << pair.second << std::endl;
    }
    outputFile.close();
    return true;
}

bool Manager::loadLoginCredentialsFromFile(const std::string& filename) {
    // Open the file for reading
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        return false; // Failed to open file
    }
    // Read each username-password pair from the file and store them in the map
    std::string username, password;
    while (inputFile >> username >> password) {
        userCredentials[username] = password;
    }
    inputFile.close();
    return true;
}

bool Manager::validateLogin(const std::string& username, const std::string& password) const {
    // Check if the username exists and the password matches
    return (userCredentials.find(username) != userCredentials.end() && userCredentials.at(username) == password);
}

bool Manager::isLoggedIn() const {
    return loggedIn;
}

bool Manager::setIsLoggedIn(bool value) {
    loggedIn = value;
    return true;
}

bool Manager::setIsManager(bool value) {
    // Here you can implement the logic for setting the isManager flag
    // For simplicity, I'm just returning true
    return true;
}
void Manager::logout() {
    loggedIn = false;
}