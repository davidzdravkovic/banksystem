#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H
#include <vector>
#include <string>
class User;

std::string inputVal(const std::string& text);
double digitVal   (const std::string& text);
std :: string digstrVal (const std :: string& text);
std :: string getCurrentTime();
bool uniqueAccount(std::vector<User*> &users,int personalID, int accountNumber);
bool uniqueUser(std::vector<User*> &users,int personalID);
#endif