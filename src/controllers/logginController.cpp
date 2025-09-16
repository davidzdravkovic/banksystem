#include "../include/models/userModel.h"
#include "../include/controllers/login.h"
#include "../include/businessUser.h"
#include <drogon/HttpController.h>
#include <drogon/HttpAppFramework.h>


void LogInController::login(const HttpRequestPtr &req,
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
    

    int userOption = 0;
    std::shared_ptr<User> newUser;
    std::string type = (*json)["type"].asString();
    
    if (type == "personal") {
      newUser = std::make_shared<personalUser>();
        userOption = 1;
}

    else if(type == "business") {
        newUser = std::make_shared<businessUser>();
        userOption = 2;
    }
    else if(type == "student") {
        newUser = std::make_shared<studentUser>();
        userOption = 3;
    }


    newUser->setPersonalID((*json)["personalID"].asInt());
    newUser->setUsersPass((*json)["password"].asString());
    pqxx::connection conn("dbname=postgres user=postgres password=new_password host=127.0.0.1 port=5432");

    User* userFromDB = UserModel::checkLogin(conn, newUser->getPersonalID(),
                                             newUser->getUsersPass(), userOption);

    if(userFromDB) {
        Json::Value respJson;
        respJson["success"] = true;
        respJson["userId"] = userFromDB->getPersonalID();
        respJson["userName"] = userFromDB->getFullName();
        respJson["userType"] = type;
        respJson["token"] = "generatedTokenHere"; // replace with real token

        auto resp = HttpResponse::newHttpJsonResponse(respJson);
        resp->addHeader("Access-Control-Allow-Origin", "http://localhost:3000");
        callback(resp);
        return;
    }

    // Invalid credentials
    auto resp = HttpResponse::newHttpResponse();
    resp->addHeader("Access-Control-Allow-Origin", "http://localhost:3000");
    resp->setStatusCode(k401Unauthorized);
    resp->setBody("Invalid credentials");
    callback(resp);
    
}
