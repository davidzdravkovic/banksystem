#ifndef STUDENTUSER_H
#define STUDENTUSER_H
#include <string>
#include "User.h"

class studentUser:public User {
    private:
    int studentID;
    std :: string typeEducation;
    int age;
    public:
    int getStudentsID() {return studentID;}
    bool createUser(std::vector<User*> &users) override ;
    virtual void printUsers() const override ;
    virtual void printAccounts(User *user) const override;
      

};

#endif