#ifndef WITHDEPO_H
#define WITHDEPO_H
#include <drogon/HttpController.h>
using namespace drogon;

class WithDepo : public drogon::HttpController<WithDepo> {
public:
METHOD_LIST_BEGIN
ADD_METHOD_TO(WithDepo::deposit,"/deposit",Patch,Options);
ADD_METHOD_TO(WithDepo::withdraw, "/withdraw",Patch,Options);
METHOD_LIST_END

void deposit (const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callBack); 


void withdraw (const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callBack); 

};


#endif