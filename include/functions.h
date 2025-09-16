#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H
#include "User.h"
#include <vector>
#include <string>


std::string inputVal(const std::string& text);
int digitVal   (const std::string& text);
std :: string digstrVal (const std :: string& text);
std :: string getCurrentTime();
bool uniqueAccount(std::vector<User*> &users,int personalID, int accountNumber);
bool uniqueUser(std::vector<User*> &users,int personalID);
#endif