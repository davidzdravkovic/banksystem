#ifndef LOGIN_H
#define LOGIN_H

#include <drogon/HttpController.h>
using namespace drogon;

class LogInController : public drogon::HttpController<LogInController>
{
public:
    // Drogon route definitions
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(LogInController::login, "/users/login", Post,Options);
    METHOD_LIST_END

    void login(const HttpRequestPtr &req,
               std::function<void(const HttpResponsePtr &)> &&callback);
};

#endif // LOGIN_H
