#include <iostream>
#include "../include/menu.h"
#include "../include/User.h"
#include "../include/Account.h"
#include "../include/personalUser.h"
#include "thread"
#include <drogon/drogon.h>
#include <json/json.h>

int main() {
  

    

drogon::app().addListener("0.0.0.0", 8080).run();

}

