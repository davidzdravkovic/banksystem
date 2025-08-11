#include <iostream>
#include <limits>
#include <vector>
using namespace std;


//Class for user, where the accounts will be stored in vector of one user trough personal id.
class User {
    public:
    string name;
    string lastName;
    int ID;
    string password;
    vector<Account> accounts;
   User(string name, string lastName, int ID, string password) {
    this->name = name;
    this->lastName = lastName;
    this->ID = ID;
    this->password = password;
}
User () {} //maybe i need to put here vector accounts
  
};
//Blue print for basic bank account.
class Account {
    public:
    double balance;
    int number;
    Account (double balance, int number) {
        this->balance=balance;
        this->number=number;
    }
   
   
};

//Input validation for account number, checks:
//if the input is blank, not number or negative number
//then the lenght of the string, after that the string is converted from string to integer 
//if the convertation is correct then returns the number
int TWO(const string& text) {
string input;
int number;
    while(true) {
        cout<<text;
        getline(cin,input);
        bool hasLetter = false;
        for(char c: input) {
        if(isalpha(c)) {
           hasLetter=true;
            break;
        }
    }
    if(hasLetter) {
         cout<<"You must enter numbers only! "<<endl;
         continue;
    }
        if(input.empty()) {
            cout<<"You entered empty input! "<<endl;
            continue;
        }
        try {
             number=stoi(input);
        }
        catch(...) {
            cout<<"Error occured! "<<endl;
            continue;
        }
        if(number>=0) {
            return number;
        }
        else {
            cout<<"Please enter positive number! "<<endl;
        }
    }
}
int findeUser(vector<User>& users) {
    bool found= false;
    int ID = TWO("Enter your personal ID: ");
    for(int i=0; i<users.size(); i++) {
     if(ID==users[i].ID) {
        found=true;
        return i;
     }
    }
    if(!found) {
        cout<<"User not found!"<<endl;
        return -1;
    }

}

//Receives account number to search for account index in vector.
  //It returns the index of the account where that number exist.
int FIVE (vector<User>& users, int index) {
       int number=TWO("Enter your account number: ");
        for(int i=0; i<users[index].accounts.size(); i++)
        if(number==users[index].accounts[i].number) {
            return i;
        }
    
        return -1;
      }
      

 //Receives an index to check if the password is matched for that index.
 //If it so it returns true.
bool checkPass (const string& text,vector<User>& users,int index) {
    string password;
    int attempts=3;
    int choice;
    while(attempts--) {
        cout<<"Enter you password: ";
        getline(cin,password);
            if(password==users[index].password) {
                return 1;
            }

       if(attempts==0) {
       cout<<"You wasted all 3 attempts!"<<endl;
       return 0;
       }
            else {
                cout<<"You entered wrong password you have " << attempts << " attempts left"<<endl;
            }
            while(true) {
                cout<<"Enter 1 to retry 0 to exit: ";
                cin>>choice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if(choice==1) {
                    break;
                }
                if(choice==0) {
                    return 0;
                }
                else{ 
                    cout<<"Incorect input! "<<endl;
                }

            }
        
    } 
   
}
//Function for account number validation and uniqueness.
//The number mustn't be blank, no digit number or longer then 8 numbers.
//If so far is valid the string will be transformed in integer.
//After the valid integer is searched does it match another account with same number.
//If there are none account with same account number it returns the valid/UNIQUE account number.
 int unique (const string& text, vector<User>& users) {
    string input;
    int number;
    while(true) {
        cout<<text;
        getline(cin,input);
        if(input.empty() || input.find_first_not_of("0123456789")!=string::npos) {
            cout<<"You entered invalid input! "<<endl;
            continue;
    }
    
    if (input.length() > 8) {
            std::cout << "Number too long. Try again: "<<endl;
            continue;
        }
        try {
             number=stoi(input);
        }
            catch(...) {
                cout<<"Invalid input"<<endl;
                continue;
            }
         bool exists=false;
          for(int i=0; i<users.size(); i++) {
            if(number==users[i].ID) {
             exists=true;
             break;
            }
          }
           if(exists) {
                cout<<"Choose unique account number! "<<endl;
                continue;
            }
          return number;
        }
 }
 //Function for user's name.
//It mustn't be blank, longer then 10 char and it must contain letters or spaces.
//Returns the user's name.
 string inputName(const string& text) {
    string name;
    
    while(true) {
        cout<<text;
        getline(cin,name);
        if(name.empty()) {
            cout<<"You entered blank input! "<<endl;  
            continue;
        }
        if(name.length()>10) {
            cout<<"Long username! "<<endl;
            continue;
        }
        bool valid=true;
        bool letter=false;
        for(int i=0; i<name.size(); i++) {
            if(!isalpha(name[i])&& !isspace(name[i]))
            valid=false;
    
            if(isalpha(name[i])) {
                letter=true;
             
            }
        }
             if(!letter) {
            cout << "Name must contain at least one letter!" << endl;
            continue;
        }
        if(!valid) {
           cout << "Name can only contain letters and spaces!" << endl;
           continue;
        }
       
        return name;
    }
   
 }
 //InputPass function, the user enter his password for check up.
//The password mustn't be blank, longer then 10 char, without 1 letter or number.
//The password is limited to 1 symbol.
//Upper case is not allowed.
//Returns the correct password.
string inputPass(const string& text) {
    string password;
    while(true) {
        cout<<text;
        getline(cin,password);
        if(password.empty()) {
            cout<<"You entered blank space!"<<endl;
            continue;
        }
        if(password.length()>10) {
            cout<<"Too long password"<<endl;
            continue;
        }
        int symbol=0;
        bool upperCase=false;
        bool valid = true;
        bool isLetter=false;
        bool isDiggit=false;
        string allowedSymbols="!@#$%^&*()";
        for(char c: password) {
            if (isupper(c)) {
              upperCase=true;
            } 
             if(isalpha(c)) {
                isLetter=true;
            }
              else if(isdigit(c)) {
                isDiggit=true;
            }
        
              else if(allowedSymbols.find(c)!=string::npos) {
                symbol++;
                if(symbol>1){
                    valid=false;
                    break;
                }
            }
            else{
                valid=false;
                break;
            }
        }
        
         if(!isLetter) {
                cout<<"Password must have at least one letter!"<<endl;
                continue;
            }
            if(!isDiggit) {
                cout<<"Password must have at least one number!"<<endl;
                continue;
            }
            if (!valid) {
            cout << "Password can only contain letters, digits, and at most one symbol (!@#$%^&*())." <<endl;
            continue;
        }
         if(upperCase) {
            cout<< "Upper case is not allowed!" <<endl;
            continue;
         }
        return password;

    }
} 
 
//Account creation.
 //With all function that are neccessery for 1 account that is :
 //with user's name that is only with letters and spaces not to long,
 //with user's account number that is only number not to long and is unique.
 //with password that is 1 letter and 1 number, with optional 1 symbol.
 //with initial balance that is a valid integer.
 //creates the object that is bank account user and is places in the accounts list.
void accountCreation (User& newUser)  {
  
    int number=TWO("Enter your account number: ");
    double balance=TWO("Enter your balance: ");

    Account newAccount(number,balance);
    newUser.accounts.push_back(newAccount);
    cout<<"You created your account successfully!" <<endl;
}
 void userCreation(vector<User>& users) {
    string name =inputName("Enter your first name: ");
    string lastName =inputName("Enter your last name: ");
    string password =inputPass("Enter your password: ");
    int ID=unique("Enter your personal ID: ",users);
    User newUser(name,lastName,ID,password);
    users.push_back(newUser);
    cout<<"Profile successfully created! "<<endl;
   


    
    
}
void displayProfile (vector<User>& users,int index) {
    cout<<endl;
    cout<<"Name: "<<users[index].name<<"                            "<<"            Personal id: "<<users[index].ID<<endl;
    cout<<"Last name: "<<users[index].lastName<<endl;
    cout<<endl;
    cout<<"To create account press number 1!"<<endl;
    cout<<"To display account press number 2!                To exit press number 0!"<<endl;
    
  }
  
void displayAccount(vector<User>& users,int index, int number) {
    cout<<endl;
    cout<<"Account number: "<<users[index].accounts[number].number<<endl;
    displayAccount(users,index,number);
    cout<<endl;
    cout<<"Enter 1 to deposit money. "<<endl;
    cout<<"Enter 2 to withdraw money. "<<endl;
    cout<<"Enter 0 to exit. "<<endl;


}
int transformation(vector<User>& users,int index, int number) {


    for(int i=0; i<users[index].accounts.size(); i++){
        if(number==users[index].accounts[i].number) {
            return i;
        }
    }
    cout<<"Account not found!"<<endl;
    return -1;
    
}

class bankSystem  { 
    public:
    vector<User> users;
//Withdraw function it allows the user to take money of his account.
//The user needs to go enter account number, if that account exist.
//He is required for password. 
//After correct password he can manage only then the withdraw transaction.
void withdraw() {
        int choice;
     int withdraw;
       string password;
          int index = findeUser(users);
           if(index==-1) {
                cout<<"The account does not exist! " <<endl;
                return;
            }
        
            int number=TWO("Enter your account number: ");
            number=FIVE(users,index);
           
           bool check=checkPass(" ",users, index);
            while(true) {
            if(check) 
            {
               withdraw=TWO("Enter your withdraw sum: ");
               if(withdraw>users[index].accounts[number].balance) {
                cout<<"Not enough money! "<<endl;
             
               }
               else{
           users[index].accounts[number].balance-=withdraw;
              cout<<"Your balance now is:" <<users[index].accounts[number].balance<<endl;
           
              }
            }
        
         while(true) {
             choice=TWO("Enter 1 to withdraw again or 0 to exit: ");
             if(choice==1) {
                break;
            }
           else if(choice==0) {
            return;
             }
           else {
               cout<<"Just 1 or 0 is allowed! "<<endl;
       }
    }
    }

void mainMenu() {
    Account acc;
    int choice;
    int number;
    string password;
    while (true) {
        cout << "\n=== Main Menu ===\n";
        cout << "1. Log in to existing profile\n";
        cout << "2. Create a new user's profile\n";
        cout << "0. Exit\n";
       choice=TWO("Enter your choice: ");
       switch (choice)
{
    case 1: {
        bool check;
        int ID = findeUser(users);
        if(ID!=-1) {
         check = checkPass(" ", users, ID);
        }
        if(check) { 
        while(true) {
            displayProfile(users, ID);
            int option = TWO("Select option: ");
            if (option == 1) {
                accountCreation(users[ID]);
                break;
            }
           else if(option==2) {
                cout<<"Here are all accounts by number: ";
                for(int i=0; i<users[ID].accounts.size(); i++ ){
                     cout << i + 1 << ". " << users[ID].accounts[i].number << endl;
                    
                }
                int accNumber=TWO("Enter account number: ");
                int a=transformation(users,ID,accNumber);
                if(a==-1) {
                    continue;
                }
                displayAccount(users,ID,a);
                int move;
                for(int i=0; i<users[ID].accounts.size(); i++ ) {
                if(accNumber==users[ID].accounts[a].number) {
                  move=TWO("Enter your choice: ");
                  if (move==1) {  
                  int deposit=TWO("Enter your deposit sum: ");
                  if(acc.deposit(deposit)) {
                    displayAccount(users,ID,a);
                  }
                  }
                 else if(move==2) {
                    int withdraw=TWO("Enter your withdraw sum: ");
                    if(acc.withdraw(withdraw)) {
                    displayAccount(users,ID,a);
                  }
                  else {
                    cout<<"Not enough fund!"<<endl;
                  }
                }
                  else if(move==0) {
                    break;
                  }
                }
                else {
                    cout<<"Account number did not matched!"<<endl;
                }
            }
            
            
        }
           else if(option==0) {
            break;
        }
                
            
            else {
                cout<<"Wrong input!"<<endl;
                continue;
            }
        
      
        }
    }
        break;
}


    case 2: {
        userCreation(users);
        break;
    }
    case 0: {
        return;
    }
}  
 
}
        
    }
};
int main () {
bankSystem system;
int choice;
system.mainMenu(system.users);

}
 

