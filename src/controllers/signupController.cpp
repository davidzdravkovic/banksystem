#include "../include/models/userModel.h"
#include "../include/controllers/signup.h"
#include "../include/businessUser.h"
#include <drogon/HttpController.h>
#include <drogon/HttpAppFramework.h>

void signupController::signup(const HttpRequestPtr &req,
                            std::function<void(const HttpResponsePtr &)> &&callback) {

    // --- Handle CORS and preflight ---
    if(req->method() == drogon::Options) {
        auto resp = drogon::HttpResponse::newHttpResponse();
        resp->addHeader("Access-Control-Allow-Origin", "http://localhost:3000");
        resp->addHeader("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        resp->addHeader("Access-Control-Allow-Headers", "Content-Type");
        callback(resp);
        return;
    }

    auto json = req->getJsonObject();
    if(!json) {
        auto resp = HttpResponse::newHttpResponse();
        resp->addHeader("Access-Control-Allow-Origin", "http://localhost:3000");
        resp->setStatusCode(k400BadRequest);
        resp->setBody("Invalid JSON");
        callback(resp);
        return;
    }
      
    
    bool created=false;
    std::shared_ptr<User> users=nullptr;
    std::string type = (*json)["userType"].asString();
    std::string fullName=((*json)["fullName"].asString());
    std::string password= ((*json)["password"].asString());
    int personalID = std::stoi((*json)["personalID"].asString());



 pqxx::connection conn("dbname=postgres user=postgres password=new_password host=localhost");
   try {
       
    if (type == "personal") {

         users=std::make_shared<personalUser>();
         auto puser=std::dynamic_pointer_cast<personalUser>(users);
         puser->setPersonalID(personalID);
         puser->setUsersPass(password);
         puser->setFullName(fullName);
         puser->setUserType(type);
         UserModel userM;
         created=userM.createPersUser(conn,puser);
 
    }
    if(type == "business") {

        users=std::make_shared<businessUser>();
         auto buser=std::dynamic_pointer_cast<businessUser>(users);
         buser->setPersonalID(personalID);
         buser->setUsersPass(password);
         buser->setFullName(fullName);
         buser->setBusiContact((*json)["businessContact"].asInt());
         buser->setBusiAddress((*json)["businessAddress"].asString());
         buser->setUserType(type);
         UserModel userM;
         created=userM.createBussUser(conn,buser);
    }
    if(type == "student") {


         users=std::make_shared<studentUser>();
         auto suser=std::dynamic_pointer_cast<studentUser>(users);
         suser->setPersonalID(personalID);
         suser->setUsersPass(password);
         suser->setFullName(fullName);
         suser->setUserType(type);
         suser->setAge((*json)["age"].asInt());
         suser->setEducation((*json)["typeEducation"].asString());
         suser->setStudentID((*json)["studentID"].asInt()); 
         UserModel userM;
         created=userM.createStudentUser(conn,suser);


    }
}
    catch (const std::exception &e) {
    auto resp = HttpResponse::newHttpResponse();
    resp->addHeader("Access-Control-Allow-Origin", "http://localhost:3000");
    resp->setStatusCode(k500InternalServerError);
    resp->setBody(std::string("User creation failed: ") + e.what());
    callback(resp);
    return;
}


  if(created==true) {
        Json::Value respJson;
        respJson["success"] = true;
        respJson["userId"] = users->getPersonalID();
        respJson["userName"] = users->getFullName();
        respJson["userType"] = users->getUserType();
        respJson["token"] = "generatedTokenHere"; 

        auto resp = HttpResponse::newHttpJsonResponse(respJson);
        resp->addHeader("Access-Control-Allow-Origin", "http://localhost:3000");
        callback(resp);
        return;
    }
   
    if(created==false) {
    auto resp = HttpResponse::newHttpResponse();
    resp->addHeader("Access-Control-Allow-Origin", "http://localhost:3000");
    resp->setStatusCode(k401Unauthorized);
    resp->setBody("User was not created!");
    callback(resp);
    }
   
}
