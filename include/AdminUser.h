#ifndef ADMINUSER_H
#define ADMINEUSER_H
#include <string>
#include "User.h"
class User;
class Manager;
class AdminUser {
 private:
  const std::string name="admin";
  const std::string password="logadmin";
  
  public:
  std::string getAdminPass(){return password;}
  std::string getAdminName(){return name;}
  void adminProfile();
  void listUser(Manager &manager);
  void viewAccounts(Manager &manager);


};
#endif