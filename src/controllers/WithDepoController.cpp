#include "../include/CheckingAccount.h"
#include "../include/models/AccountModel.h"
#include "../include/controllers/WithDepo.h"
#include <drogon/HttpController.h>
#include <drogon/HttpAppFramework.h>

void WithDepo::deposit (const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    
if(req->method()==drogon::Options) {
    auto resp= drogon::HttpResponse::newHttpResponse();
    resp->addHeader("Access-Control-Allow-Origin", "http://localhost:3000");
        resp->addHeader("Access-Control-Allow-Methods", "GET, PATCH, OPTIONS");
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
     
     pqxx::connection conn("dbname=postgres user=postgres password=new_password host=localhost");
     double amount = (*json)["amount"].asDouble();
    std::string accNumber = req->getParameter("accountNumber");
    int accountNumber = std::stoi(accNumber);
     AccountModel accModel;
     double newAmount =  accModel.deposit(conn,amount,accountNumber);

     if(newAmount==-1) {
        auto resp = HttpResponse::newHttpResponse();
        resp->addHeader("Access-Control-Allow-Origin", "http://localhost:3000");
        resp->setStatusCode(k400BadRequest);
        resp->setBody("Deposit failed");
        callback(resp);
  }
  
   if(newAmount !=-1) {
  
    Json::Value jsonResponse;
    jsonResponse["status"]=true;
    jsonResponse["balance"]=newAmount;
    auto resp =drogon::HttpResponse::newHttpJsonResponse(jsonResponse);
    resp->addHeader("Access-Control-Allow-Origin", "http://localhost:3000");
    callback(resp);
    return;
  }   
        
    
}
void WithDepo::withdraw (const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    
if(req->method()==drogon::Options) {
    auto resp= drogon::HttpResponse::newHttpResponse();
    resp->addHeader("Access-Control-Allow-Origin", "http://localhost:3000");
        resp->addHeader("Access-Control-Allow-Methods", "GET, PATCH, OPTIONS");
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
     
     pqxx::connection conn("dbname=postgres user=postgres password=new_password host=localhost");
     double amount = (*json)["amount"].asDouble();
    std::string accNumber = req->getParameter("accountNumber");
    int accountNumber = std::stoi(accNumber);
     AccountModel accModel;
     double newBalance =  accModel.withdraw(conn,amount,accountNumber);
     
     if(newBalance==-1) {
        auto resp = HttpResponse::newHttpResponse();
        resp->addHeader("Access-Control-Allow-Origin", "http://localhost:3000");
        resp->setStatusCode(k400BadRequest);
        resp->setBody("Withdraw failed");
        callback(resp);
  }
   if(newBalance!=-1) {
  
    Json::Value jsonResponse;
    jsonResponse["status"]=true;
    jsonResponse["balance"]=newBalance;
    auto resp =drogon::HttpResponse::newHttpJsonResponse(jsonResponse);
    resp->addHeader("Access-Control-Allow-Origin", "http://localhost:3000");
    callback(resp);
    return;
  }   
}