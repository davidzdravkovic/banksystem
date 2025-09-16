#ifndef ACCOUNTSEARCH_H
#define ACCOUNTSEARCH_H
#include <drogon/HttpController.h>
using namespace drogon;

class SearchAccount : public drogon::HttpController<SearchAccount> {
public:
METHOD_LIST_BEGIN
ADD_METHOD_TO(SearchAccount::search, "/search",Get,Options);
METHOD_LIST_END

void search (const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callBack); 

};





#endif