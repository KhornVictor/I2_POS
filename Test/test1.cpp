#include<iostream>
using namespace std;

string Admin_Capitalization(string index){
    string capitalization;
    bool condition = true;
    for (char i : index){
        if (condition) {capitalization += toupper(i); condition = false;}
        else if (i == ' ') {capitalization += i; condition = true;}
        else capitalization += i;
    }
    return capitalization;
}

int main(){
    string name = "hello i'm victor";
    name = Admin_Capitalization(name);
    cout << "name: " << name << endl;
}