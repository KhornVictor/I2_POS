#include <iostream>
#include <fstream>
#include <sstream>
#include <conio.h>
using namespace std;

#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m" 
#define WHITE   "\033[37m"
#define GRAY    "\033[90m"
#define BOLD    "\033[1m"

struct Node{
    string email;
    string password;
    Node *next;
};

struct Stack{
    int size; 
    Node* head;
    Node* tail;
};

struct Stack{
    int size;
    Node *top;
};

Stack* create(){
    Stack* newlist = new Stack;
    newlist -> top = NULL;
    newlist -> size = 0;
    return newlist;
}

void push(Stack* s, string email, string password){
    Node* newnode = new Node;
    newnode -> email = email;
    newnode -> password = password;
    newnode -> next = s -> top;
    s -> top = newnode;
    s -> size++;
}

string getPassword(){
    string password;
    char ch ;
    cout << "Enter password: " ;
    while((ch = _getch())!= '\r'){
        if(ch == '\b'){
            if(!password.empty()){
                password.pop_back();
                cout << "\b \b";        
            }
        }else{
            password += ch;
            cout << "*";            
        }
    }
    cout << endl;
    return password;
}

void get_all_users_from_csv(Stack* s, string filename) {
    ifstream file;
    file.open(filename, ios::in);
    string line;
    if (!file.is_open()) cout << RED << "Cannot open the file!" << RESET << endl;
    else {
        while (getline(file, line)) { // Correct way to read each line
            stringstream ss(line);
            string name, ageStr, genderStr, phone, roleStr, email, password;
            getline(ss, name, ',');
            getline(ss, ageStr, ',');
            getline(ss, genderStr, ',');
            getline(ss, phone, ',');
            getline(ss, roleStr, ',');
            getline(ss, email, ',');
            getline(ss, password);
            push(s, email, password);
        }
        file.close();
    }
}

bool check_email(Stack *s, string email){
    Node *temporary = s -> top;
    while (temporary != NULL){
        if (temporary -> email == email) return true;
        temporary = temporary -> next;
    } 
    return false;
}


void check_user_sign_in(){
    system("cls");
    Stack *s = create();
    get_all_users_from_csv(s, "Database/user.csv");
    Node input;
    int count = 0;
    cout << CYAN << "Sign up" << RESET << endl;
    do{
        while (true){
            cout << "Enter email: " << YELLOW; cin >> input.email; cout << RESET;
            if (input.email.size() >= 10 && input.email.substr(input.email.size() - 10) == "@gmail.com") break;
            else {
                system("cls");
                cout << RED << "Invalid email" << RESET << endl;
            }
        }
        system("cls");
        cout << GREEN << "Email accepted!" << RESET << endl;
        cout << "Enter email: " << YELLOW << input.email << RESET << endl;
        input.password = getPassword();
        if (check_email(s, input.email)) cout << "Email not found!" << endl;
    } while (true);
    


}