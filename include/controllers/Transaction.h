#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <drogon/HttpController.h>
using namespace drogon;

class TransactionController : public drogon::HttpController<TransactionController> {
public:
METHOD_LIST_BEGIN
ADD_METHOD_TO(TransactionController::validation, "/transaction_validate",Post,Options);
ADD_METHOD_TO(TransactionController::readTransaction, "/transaction",Get,Options);
ADD_METHOD_TO(TransactionController::accept, "/transaction_accept",Patch,Options);
ADD_METHOD_TO(TransactionController::decline, "/transaction_decline",Patch,Options);
ADD_METHOD_TO(TransactionController::disable, "/transaction_disable",Patch,Options);
METHOD_LIST_END

void validation (const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callBack); 
void readTransaction (const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callBack);
 void accept (const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callBack);
  void decline (const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callBack);
    void disable (const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callBack);

};
 



#endif