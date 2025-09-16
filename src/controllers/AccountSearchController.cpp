#include "../include/controllers/AccountSearch.h"
#include "../include/models/AccountModel.h"
#include <drogon/HttpController.h>
#include <drogon/HttpAppFramework.h>



void SearchAccount :: search (const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callBack) {
   
    if(req->method()==drogon::Options) {
    auto resp= drogon::HttpResponse::newHttpResponse();
    resp->addHeader("Access-Control-Allow-Origin", "http://localhost:3000");
        resp->addHeader("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        resp->addHeader("Access-Control-Allow-Headers", "Content-Type");
        callBack(resp);
        return;
    } 
     std::vector<std::shared_ptr<Account>> accounts;
     pqxx::connection conn("dbname=postgres user=postgres password=new_password host=localhost");

     
     auto userID = req->getParameter("personalID");
     int personalID = std::stoi(userID);
     accounts = AccountModel::searchAccount(conn,personalID);
    std::cout<<personalID<<std::endl;
     Json::Value accountsArray(Json::arrayValue);


     for(int i=0; i<accounts.size(); i++) {
        Json::Value respJson;
        respJson["accountNumber"]=accounts[i]->getAccountNumber();
        respJson["accountType"]=accounts[i]->getAccountType();
        respJson["balance"]=accounts[i]->getBalance();
        std::cout<<accounts[i]->getBalance();
         accountsArray.append(respJson);
    }
    if(accounts.empty()) {

    auto resp = HttpResponse::newHttpResponse();
    resp->addHeader("Access-Control-Allow-Origin", "http://localhost:3000");
    resp->setStatusCode(k401Unauthorized);
    resp->setBody("No accounts created");
    callBack(resp);
    }
    if(!accounts.empty()) {
        Json::Value theAray;
        theAray["status"]=true;
        theAray["accounts"] =accountsArray;
    auto resp= drogon::HttpResponse::newHttpJsonResponse(theAray);
    resp->addHeader("Access-Control-Allow-Origin", "http://localhost:3000");
    callBack(resp);

    }
     }

    
