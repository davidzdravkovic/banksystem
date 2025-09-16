
#ifndef SIGNUP_H
#define SIGNUP_H

#include <drogon/HttpController.h>
using namespace drogon;

class signupController : public drogon::HttpController<signupController>
{
public:
    // Drogon route definitions
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(signupController::signup, "/users/signup", Post,Options);
    METHOD_LIST_END

    void signup(const HttpRequestPtr &req,
               std::function<void(const HttpResponsePtr &)> &&callback);
           
};

#endif 
