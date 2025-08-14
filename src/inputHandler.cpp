#include "../include/inputHandler.h"
#include <cctype>
#include <iostream>

std::string inputVal(const std::string& text) {
      std::string input;
      char a;
      while(true) {
     bool valid=true;
      std :: cout<<text;
     getline(std::cin,input);
     if(input.empty() ) {
       std :: cout<<"The input can not be empty: "<<std::endl;
       valid=false;
    }
    for(int i=0; i<input.size(); i++) {
      
        a=input[i];
        if(!isalpha(a)&&!isspace(a)) {
            std::cout<<"Input must be letter!"<<std::endl;
            valid=false;
            break;
        }
    }
    if(valid) {
        return input;
    }
}

}
int digitVal(const std::string& text) {
    bool valid;
    std::string input;
    int number;
    char a;
    while(true) {
        valid=true;
        std::cout<<text;
        getline(std::cin,input);
        if(input.empty()) {
            std::cout<<"Input can not be empty! "<<std::endl;
            continue;
        }
        for(int i=0; i<input.size(); i++) {
            a=input[i];
            if(!isdigit(a)) {
                std::cout<<"You must enter number!"<<std::endl;
                valid=false;
                break;
            }
            
        }
        if(!valid) {
                continue;
            }
        try {
            number=stoi(input);
        }
        catch(...) {
            std::cout<<"Error occured!"<<std::endl;
            continue;
        }
        if(number>=0) {
            return number;
        }
        else{
            std::cout<<"Number must be positive!"<<std::endl;
            continue;
        }
    }
}
std::string digstrVal(const std::string& text) {
    std :: string input;
    bool valid;
    char a;
    while(true) {
        valid=true;
        std :: cout<<text;
        getline(std :: cin, input);
        if(input.empty()) {
            std :: cout<<"Empty input! "<< std :: endl;
            continue;
        }
        for(int i=0; i<input.size(); i++) {
            a=input[i];
            if(!isdigit(a) && !isalpha(a) && !isspace(a) && a!=',' && a!='.'&& a!='\\' &&a!=':' ) {
                std :: cout<<"Enter valid input!"<<std :: endl;
                valid=false;
            }
        }
        if(valid) {
            return input;
        }
    }
}