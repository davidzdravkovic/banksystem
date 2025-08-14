#ifndef PERSONALUSER_H
#define PERSONALUSER_H
#include "../include/User.h"

class personalUser:public User {
    public:
   void createUser() override ;
   virtual void print() const override ;
      

};

#endif