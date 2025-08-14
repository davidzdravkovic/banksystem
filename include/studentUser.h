#ifndef STUDENTUSER_H
#define STUDENTUSER_H
#include "../include/User.h"

class studentUser:public User {
    public:
    void createUser() override ;

    
   virtual void print() const override ;
      

};

#endif