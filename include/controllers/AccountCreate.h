#ifndef USERMODEL_H
#define USERMODEL_H
#include <drogon/HttpController.h>
using namespace drogon;


class AccountCreate : public drogon::HttpController<AccountCreate> {
public:
   METHOD_LIST_BEGIN
    ADD_METHOD_TO(AccountCreate::create, "/create", Post,Options);
    METHOD_LIST_END
    
    void create( const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callBack);

};

#endif