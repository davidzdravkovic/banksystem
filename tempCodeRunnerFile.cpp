
            }
            if(option==0) {
                return;
            }
            else {
                cout<<"Wrong input!"<<endl;
                continue;
            }
        }
    }
}

    case 2: {
        userCreation(users);
        break;
    }
    case 3: {
        return;
    }
}  
 
}
        
    }
};
    
    //Prints menu.
void menu() { 
    cout << "===== Bank System Menu =====" << endl;
    cout << "1. Create Account" << endl;
    cout << "2. Deposit Money" << endl;
    cout << "3. Withdraw Money" << endl;
    cout << "4. Check Balance" << endl;
    cout << "5. Display Account Details" << endl;
    cout << "6. Exit" << endl;
} 


int main () {
bankSystem system;
int choice;
system.mainMenu(system.users);

}
 

