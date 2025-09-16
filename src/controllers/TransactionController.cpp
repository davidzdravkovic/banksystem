#include "../include/models/TransactionModel.h"
#include "../include/controllers/Transaction.h"
#include "../include/businessUser.h"
#include <drogon/HttpController.h>
#include <drogon/HttpAppFramework.h>

void TransactionController::validation(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callBack)
 { 

    if(req->method() == drogon::Options) {
        auto resp = drogon::HttpResponse::newHttpResponse();
        resp->addHeader("Access-Control-Allow-Origin", "http://localhost:3000");
        resp->addHeader("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        resp->addHeader("Access-Control-Allow-Headers", "Content-Type");
        callBack(resp);
        return;
    }

    auto json = req->getJsonObject();
    if(!json) {
        auto resp = HttpResponse::newHttpResponse();
        resp->addHeader("Access-Control-Allow-Origin", "http://localhost:3000");
        resp->setStatusCode(k400BadRequest);
        resp->setBody("Invalid JSON");
        callBack(resp);
        return;
    }
  
    bool created=false;
    bool checkValidation=false;
    int amount=(*json)["amount"].asInt();
    int receiverNumber = std::stoi((*json)["receiverNumber"].asString());
    int senderNumber=(*json)["senderNumber"].asInt();
    std::string type=(*json)["transactionType"].asString();
    int transactionType;

    if(type=="Sending") {
        transactionType=1;

    }
     if(type=="Asking") {
         transactionType=2;

    }
    
      pqxx::connection conn("dbname=postgres user=postgres password=new_password host=localhost");
     
    checkValidation=TransactionModel::validationTrans(conn,senderNumber,receiverNumber,transactionType,amount);
    if(checkValidation) {
     created=TransactionModel::createTransaction(conn,senderNumber,receiverNumber,transactionType,amount);
    }

    if(created) {
     Json::Value jsonResponse;
    jsonResponse["status"]=true;
    auto resp =drogon::HttpResponse::newHttpJsonResponse(jsonResponse);
    resp->addHeader("Access-Control-Allow-Origin", "http://localhost:3000");
    callBack(resp);
    return;
    }

   
}

void TransactionController::accept(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callBack) {\
  std::cout<<"AM I HERE"<<std::endl;
        if(req->method() == drogon::Options) {
        auto resp = drogon::HttpResponse::newHttpResponse();
        resp->addHeader("Access-Control-Allow-Origin", "http://localhost:3000");
        resp->addHeader("Access-Control-Allow-Methods", "GET, PATCH, OPTIONS");
        resp->addHeader("Access-Control-Allow-Headers", "Content-Type");
        callBack(resp);
        return;
    }
    pqxx::connection conn("dbname=postgres user=postgres password=new_password host=localhost");
    std::string transactionNumber=req->getParameter("transactionNumber");
    int transactionID=std::stoi(transactionNumber);

   double newBalance = TransactionModel::acceptTrans(conn,transactionID);
  
   if(newBalance>=0) {
    Json::Value body;
    body["status"]=true;
    body["balance"]=newBalance;
    auto resp= drogon::HttpResponse::newHttpJsonResponse(body);
    resp->addHeader("Access-Control-Allow-Origin", "http://localhost:3000");
    callBack(resp);

   }
    else {
     auto resp = HttpResponse::newHttpResponse();
    resp->addHeader("Access-Control-Allow-Origin", "http://localhost:3000");
    resp->setStatusCode(k401Unauthorized);
    resp->setBody("Transaction failed executing acceptence");
    callBack(resp);
    }


}

void TransactionController::decline (const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callBack) {

      if(req->method() == drogon::Options) {
        auto resp = drogon::HttpResponse::newHttpResponse();
        resp->addHeader("Access-Control-Allow-Origin", "http://localhost:3000");
        resp->addHeader("Access-Control-Allow-Methods", "GET, PATCH, OPTIONS");
        resp->addHeader("Access-Control-Allow-Headers", "Content-Type");
        callBack(resp);
        return;
    }
    pqxx::connection conn("dbname=postgres user=postgres password=new_password host=localhost");
    std::string transactionNumber=req->getParameter("transactionNumber");
    int transactionID=std::stoi(transactionNumber);
  
    bool declined = TransactionModel::declineTrans(conn,transactionID);
    
    if(declined) {
    Json::Value body;
    body["status"]=true;
    auto resp= drogon::HttpResponse::newHttpJsonResponse(body);
    resp->addHeader("Access-Control-Allow-Origin", "http://localhost:3000");
    callBack(resp);
    }
    if(!declined) {
     auto resp = HttpResponse::newHttpResponse();
    resp->addHeader("Access-Control-Allow-Origin", "http://localhost:3000");
    resp->setStatusCode(k401Unauthorized);
    resp->setBody("Transaction failed executing decline");
    callBack(resp);

    }

}
void TransactionController::readTransaction(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callBack) {

     if(req->method() == drogon::Options) {
        auto resp = drogon::HttpResponse::newHttpResponse();
        resp->addHeader("Access-Control-Allow-Origin", "http://localhost:3000");
        resp->addHeader("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        resp->addHeader("Access-Control-Allow-Headers", "Content-Type");
        callBack(resp);
        return;
    }


    pqxx::connection conn("dbname=postgres user=postgres password=new_password host=localhost");

    std::vector<Transactions> trans;

    std::string accNumber = req->getParameter("accountNumber");
    int accountNumber=stoi(accNumber);

     std::string type=req->getParameter("type");

     if(type=="inbox") {

  trans=TransactionModel::inbox(conn,accountNumber);
  Json::Value transactionsArray(Json::arrayValue);

   for(int i=0; i<trans.size(); i++) {
        Json::Value resp;
        resp["senderNumber"]=trans[i].sender;
        resp["transactionID"]=trans[i].transactionNumber;
        resp["amount"]=trans[i].amount;
        resp["type"]=trans[i].transactionType;
         transactionsArray.append(resp);

     }
     if(trans.empty()) {
        
        Json::Value theAray;
        theAray["status"]=true;
        theAray["transactions"] =transactionsArray;

    auto resp = HttpResponse::newHttpJsonResponse(theAray);
    resp->addHeader("Access-Control-Allow-Origin", "http://localhost:3000");
    resp->setStatusCode(k401Unauthorized);
    resp->setBody("No transaction received");
    callBack(resp);
    }
    if(!trans.empty()) {
        Json::Value theAray;
        theAray["status"]=true;
        theAray["transactions"] =transactionsArray;
    auto resp= drogon::HttpResponse::newHttpJsonResponse(theAray);
    resp->addHeader("Access-Control-Allow-Origin", "http://localhost:3000");
    callBack(resp);

    }

     }

    if(type=="sent") {


    trans=TransactionModel::sent(conn,accountNumber);

     Json::Value transactionsArray(Json::arrayValue);

     for(int i=0; i<trans.size(); i++) {
        Json::Value resp;
        resp["receiverNumber"]=trans[i].receiver;
        resp["transactionID"]=trans[i].transactionNumber;
        resp["amount"]=trans[i].amount;
        resp["type"]=trans[i].transactionType;
         transactionsArray.append(resp);

     }
     if(trans.empty()) {

        Json::Value theAray;
        theAray["status"]=true;
        theAray["transactions"] =transactionsArray;

    auto resp = HttpResponse::newHttpJsonResponse(theAray);
    resp->addHeader("Access-Control-Allow-Origin", "http://localhost:3000");
    resp->setStatusCode(k401Unauthorized);
    resp->setBody("No transaction sent");
    callBack(resp);
    }
    if(!trans.empty()) {
        Json::Value theAray;
        theAray["status"]=true;
        theAray["transactions"] =transactionsArray;
    auto resp= drogon::HttpResponse::newHttpJsonResponse(theAray);
    resp->addHeader("Access-Control-Allow-Origin", "http://localhost:3000");
    callBack(resp);

    }


    } 
   

    
 if(type=="history") {
     trans=TransactionModel::history(conn,accountNumber);

     Json::Value transactionsArray(Json::arrayValue);

     for(int i=0; i<trans.size(); i++) {
        Json::Value txnResp;
        txnResp["senderNumber"]=trans[i].sender;
        txnResp["receiverNumber"]=trans[i].receiver;
        txnResp["transactionID"]=trans[i].transactionNumber;
        txnResp["amount"]=trans[i].amount;
        txnResp["type"]=trans[i].transactionType;
        txnResp["transactionStatus"]=trans[i].transStatus;
        transactionsArray.append(txnResp);

     }
     if(trans.empty()) {

       Json::Value theAray;
        theAray["status"]=true;
        theAray["transactions"] =transactionsArray;
    auto resp= drogon::HttpResponse::newHttpJsonResponse(theAray);
    resp->addHeader("Access-Control-Allow-Origin", "http://localhost:3000");
    resp->setStatusCode(k401Unauthorized);
    resp->setBody("No transaction history");
    callBack(resp);
    }
    else {
        Json::Value theAray;
        theAray["status"]=true;
        theAray["transactions"] =transactionsArray;
    auto resp= drogon::HttpResponse::newHttpJsonResponse(theAray);
    resp->addHeader("Access-Control-Allow-Origin", "http://localhost:3000");
    callBack(resp);

    }
}


}
 void TransactionController::disable(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callBack) {
     if(req->method() == drogon::Options) {
        auto resp = drogon::HttpResponse::newHttpResponse();
        resp->addHeader("Access-Control-Allow-Origin", "http://localhost:3000");
        resp->addHeader("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        resp->addHeader("Access-Control-Allow-Headers", "Content-Type");
        callBack(resp);
        return;
    }

    std::string accNumber=req->getParameter("accountNumber");
    std::string transNumber=req->getParameter("transactionID");
     
    int accountNumber=std::stoi(accNumber);
    int transactionNumber=std::stoi(transNumber);

    pqxx::connection conn("dbname=postgres user=postgres password=new_password host=localhost");

    bool disabled = TransactionModel::disabling(conn,transactionNumber,accountNumber);

    if(disabled) {
    Json::Value body;
    body["status"]=true;
    auto resp= drogon::HttpResponse::newHttpJsonResponse(body);
    resp->addHeader("Access-Control-Allow-Origin", "http://localhost:3000");
    callBack(resp);
    }
     else {
     auto resp = HttpResponse::newHttpResponse();
    resp->addHeader("Access-Control-Allow-Origin", "http://localhost:3000");
    resp->setStatusCode(k401Unauthorized);
    resp->setBody("Transaction failed executing decline");
    callBack(resp);
     }

 }