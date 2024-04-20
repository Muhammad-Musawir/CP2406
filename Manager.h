#ifndef MANAGER_H
#define MANAGER_H

#include <string>
#include <map>

class Manager {
private:
    std::map<std::string, std::string> userCredentials;
    bool loggedIn;
    bool isManager;

public:
    Manager();
    Manager(const std::string& username, const std::string& password);
    bool createLogin(const std::string& username, const std::string& password);
    bool editLogin(const std::string& username, const std::string& newPassword);
    bool deleteLogin(const std::string& username);
    bool saveLoginCredentialsToFile(const std::string& filename) const;
    bool loadLoginCredentialsFromFile(const std::string& filename);
    bool validateLogin(const std::string& username, const std::string& password) const;
    bool isLoggedIn() const;
    bool setIsLoggedIn(bool value); // Declare setIsLoggedIn
    bool setIsManager(bool value); // Declare setIsManager
    void logout();
};

#endif // MANAGER_H
