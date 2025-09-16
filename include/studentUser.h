#ifndef STUDENTUSER_H
#define STUDENTUSER_H
#include <string>

class User;


class studentUser:public User {
    private:
    int studentID;
    std :: string typeEducation;
    int age;
    public:
    int getStudentsID() {return studentID;}
    void setStudentID(int id) {studentID=id;}
   
    std::string getEducation() {return typeEducation;}
    void setEducation(std::string education) {typeEducation=education;}

    int getAge(){return age;}
    void setAge(int studentAge){age=studentAge;}
    
    bool createUser(pqxx::connection &conn,std::shared_ptr<User> user) override ;
    virtual void printUsers(pqxx::connection &conn) const override ;
    virtual void printAccounts(pqxx::connection &conn) const override;
      

};

#endif