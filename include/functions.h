#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H
#include <vector>
#include <string>
class User;

std::string inputVal(const std::string& text);
int digitVal   (const std::string& text);
std :: string digstrVal (const std :: string& text);
std :: string getCurrentTime();
bool unique(std::vector<User*> &users,int personalID, int accountNumber);
#endif