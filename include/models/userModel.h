#ifndef USERMODEL_H
#define USERMODEL_H
#include "Manager.h"
#include "User.h"
#include "businessUser.h"
#include "personalUser.h"
#include "studentUser.h"



class UserModel {
public:
std::shared_ptr<businessUser> bUser=nullptr;
std::shared_ptr<personalUser> pUser=nullptr;
std::shared_ptr<studentUser> sUser=nullptr;


  
    static User* checkLogin(pqxx::connection &conn, int personalID, const std::string &password, int userOption) {
        return Manager::checkPass(conn, personalID, password, userOption);
    }
     bool createBussUser(pqxx::connection &conn,std::shared_ptr<businessUser> user) {
            if (!user) return false;
        return user->createUser(conn, user);
    }
    bool createPersUser(pqxx::connection &conn,std::shared_ptr<personalUser> user) {
            if (!user) return false;
        return user->createUser(conn, user);
    }
    bool createStudentUser(pqxx::connection &conn,std::shared_ptr<studentUser> user) {
       if (!user) return false;
        return user->createUser(conn, user);
    }

};
#endif