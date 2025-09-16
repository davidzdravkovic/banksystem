#include "../include/CheckingAccount.h"
#include "../include/models/AccountModel.h"
#include "../include/controllers/AccountCreate.h"
#include <drogon/HttpController.h>
#include <drogon/HttpAppFramework.h>

void AccountCreate :: create (const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    
    if(req->method()==drogon::Options) {
      auto resp =  drogon::HttpResponse::newHttpResponse();
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

    pqxx::connection conn("dbname=postgres user=postgres password=new_password host=127.0.0.1 port=5432");
    int realPersonalID=-1;
    std::shared_ptr<Account> newAccount=nullptr;
    
  
    std::string typeAccount = (*json)["accountType"].asString();
    std::cout << "Received JSON: " << (*json).toStyledString() << std::endl;
    std::cout << "Type account :"<<typeAccount<<std::endl;

     std::string accountDigit=(*json)["accountNumber"].asString();
     int accountNumber=stoi(accountDigit);

    std::string personalID = (*json)["personalID"].asString();
    realPersonalID=stoi(personalID);

   if(typeAccount=="CheckingAccount") {

   newAccount=std::make_shared<CheckingAccount>();
   auto checkingAcc = std::dynamic_pointer_cast<CheckingAccount> (newAccount);

    checkingAcc->setOwnerName((*json)["fullName"].asString());
    checkingAcc->setAccountNumber(accountNumber);
    checkingAcc->SetAccountType("checking_accounts");

    AccountModel accModel;
    newAccount = accModel.createCheckAccount(conn,checkingAcc,realPersonalID);

   }
   else if(typeAccount=="SavingsAccount") {

   newAccount=std::make_shared<SavingAccount>();
   auto savingAcc = std::dynamic_pointer_cast<SavingAccount> (newAccount);

    savingAcc->setOwnerName((*json)["fullName"].asString());
    savingAcc->setAccountNumber(accountNumber);
    savingAcc->SetAccountType("saving_accounts");
    
    AccountModel accModel;
    newAccount = accModel.createSavingkAccount(conn,savingAcc,realPersonalID);

   }
   else if(typeAccount=="CreditAccount") {

   newAccount=std::make_shared<CreditAccount>();
   auto creditAcc = std::dynamic_pointer_cast<CreditAccount> (newAccount);

    creditAcc->setOwnerName((*json)["fullName"].asString());
    creditAcc->setAccountNumber(accountNumber);
    creditAcc->SetAccountType("credit_accounts");
    
    AccountModel accModel;
    newAccount = accModel.createCreditAccount(conn, creditAcc,realPersonalID);

   }
      if (!newAccount) {
    auto resp = HttpResponse::newHttpResponse();
    resp->addHeader("Access-Control-Allow-Origin", "http://localhost:3000");
    resp->setStatusCode(k400BadRequest);
    resp->setBody("Account creation failed now");
    callback(resp);
    return;
}


    Json::Value respJson;
    respJson["success"] = true;

    Json::Value accountJson;
    accountJson["accountNumber"] = newAccount->getAccountNumber();
    accountJson["personalID"] = realPersonalID;
    accountJson["accountType"] = newAccount->getAccountType();
    accountJson["balance"] = newAccount->getBalance();
    accountJson["totalDeposit"] = newAccount->getTotalDeposite();
    accountJson["totalWithdraw"] = newAccount->getTotalWithdraw();
    accountJson["transactionMade"] = newAccount->getTransactionsMade();

    respJson["account"] = accountJson;
    respJson["token"] = "generatedTokenHere";

    auto resp = drogon::HttpResponse::newHttpJsonResponse(respJson);
    resp->addHeader("Access-Control-Allow-Origin", "http://localhost:3000");
    callback(resp);

}


