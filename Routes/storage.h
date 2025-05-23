#include<iostream>
#include<fstream>
#include<sstream>
#include<cstdio>
#include<string>
#include"global.h"
using namespace std;

string name_forcart;

struct storage{
    string id,name,code;
    float price;
    int amount;
};

const int ssize = 1000;
int top = -1;
storage s[ssize];

bool empty(){
    return top == -1;
}
bool full(){
    return top == ssize - 1;
}




void push(){
    if(full()){
        cout<<"The storage is full";
        return;
    }
    
    top++;
    cout<<"enter product name: ";cin>> s[top].name;
    cout<<"enter product id: ";cin>> s[top].id;
    cout<<"enter product code: ";cin>> s[top].code;
    cout<<"enter product price: ";cin>> s[top].price;
    cout<<"enter product amount: "; cin >> s[top].amount;


    cout<<"add product complete"<<endl;
    
    ifstream fin("Database/customer/storage.csv");
    string temp;
    int line = 0;
    while (getline(fin, temp)) {
        line++;
    }
    fin.close();

    ofstream fout ("Database/customer/storage.csv",ios::app);
    fout<<line+1<<","<<s[top].id<<","<<s[top].name<<","<<s[top].code<<","<<s[top].price<< "," << s[top].amount<<endl;
    fout.close();
}

void loadfile(){
    ifstream fin("Database/customer/storage.csv");
    string line;
    while(getline(fin,line)){
        string No,proid,proname,procode,proprice,proamount;
        stringstream ss(line);
        getline(ss,No,',');
        getline(ss,proid,',');
        getline(ss,proname,',');
        getline(ss,procode,',');
        getline(ss,proprice,',');
        getline(ss,proamount,',');

        if(proid.empty()||proname.empty()||procode.empty()||proprice.empty()||proamount.empty()){
           continue; 
        } 
        top++;
        s[top].id = proid;
        s[top].name = proname;
        s[top].code = procode;
        s[top].price = stof(proprice);
        s[top].amount = stoi(proamount);
    }
    fin.close();
}



void pop(){
    loadfile();
    if(empty()){
        cout<<"the storage is empty";
        return;
    }
    top--;
    ofstream fout("Database/customer/storage.csv",ios::out);
    if(!fout){
        cout<<"can't open file"<<endl;
        return;
    }
    for(int i=0;i<=top;i++){
        fout<<i+1<<","<<s[i].id<<","<<s[i].name<<","<<s[i].code<<","<<s[i].price<< "," << s[i].amount<<endl;
    }

    fout.close(); 
    system("cls");
    cout<<"remove complete"<<endl; 
}




void pop_position(int n){
    loadfile();
    if(empty()){
        cout<<"the storage is empty"<<endl;
        return;
    }
    if(n<1 || n> top+1){
        cout<<"invalid position"<<endl;
        return;
    }
    cout<<"delete "<<s[n].name<<" successfully"<<endl;
    for(int i=n-1;i<top;i++){
        s[i] = s[i+1];
    }
    top--;

    ofstream fout("Database/customer/storage.csv");
    for(int i=0;i<=top;i++){
        fout<<i<<","<<s[i].id<<","<<s[i].name<<","<<s[i].code<<","<<s[i].price<< "," << s[i].amount<<endl;
    }
    fout.close();

}




void display(){
    ifstream fin("Database/customer/storage.csv");
    if(!fin){
        cout<<"the file is not exist"<<endl;
        return;
    }

    cout<<"=================== product list ========================"<<endl;
    cout<<"No.\tID\tName\tcode\tprice\tamount"<<endl;

    bool empty = true;

    string line;
    while(getline(fin,line)){
        string No,proid,proname,procode,proprice,proamount;
        stringstream ss(line);

        getline(ss,No,',');
        getline(ss,proid,',');
        getline(ss,proname,',');
        getline(ss,procode,',');
        getline(ss,proprice,',');
        getline(ss,proamount,',');


        cout<<No<<".\t"<<proid<<"\t"<<proname<<"\t"<<procode<<"\t"<<proprice<<"\t"<<proamount<<endl;
        empty = false;
    }
    
    if(empty){
        cout<<"the storage is empty"<<endl;
    }
    fin.close();
}

void update(string code){
    system("cls");
    ifstream fin("Database/customer/storage.csv");
    ofstream temp("temp.csv");

    if(!fin || !temp){
        cout<<"can't open file"<<endl;
    }

    bool found = false;
    string line;
    int i=1;

    while(getline(fin,line)){
        string No,proid,proname,procode,proprice,proamount;
        stringstream ss(line);

        getline(ss,No,',');
        getline(ss,proid,',');
        getline(ss,proname,',');
        getline(ss,procode,',');
        getline(ss,proprice,',');
        getline(ss,proamount, ',');

        if(procode == code){
            found = true;
            cout<<"product found"<<endl;
            string newid,newname,newcode;
            float newprice;
            int newamount;

            cout<<"enter new name: ";cin>>newname;
            cout<<"enter new id: ";cin>>newid;
            cout<<"enter new code: ";cin>>newcode;
            cout<<"enter new price: ";cin>>newprice;
            cout<<"enter new amount: ";cin>>newamount;

            temp<<i<<","<<newid<<","<<newname<<","<<newcode<<","<<newprice<<","<<newamount;
        }else{
            temp <<i<<","<<proid<<","<<proname<<","<<procode<<","<<proprice<<","<<update<<endl;
        }
        i++;
    }

    fin.close();
    temp.close();

    remove("Database/customer/storage.csv");
    rename("temp.csv","Database/customer/storage.csv");

    if(found){
        cout<<"update successfully"<<endl;
    }else{
        cout<<"product not found"<<endl;
    }
}




void find_product(string name){
    system("cls");
    cout<<"==============================================================="<<endl;
    ifstream fin("Database/customer/storage.csv");

    if(!fin){
        cout<<"the storage doesn't exist"<<endl;
    }

    bool found = false;
    string line;

    while(getline(fin,line)){
        string No,proid,proname,procode,proprice,proamount;
        stringstream ss(line);

        getline(ss,No,',');
        getline(ss,proid,',');
        getline(ss,proname,',');
        getline(ss,procode,',');
        getline(ss,proprice,',');
        getline(ss,proamount, ',');

        if(proname == name){
            cout<<"product found: "<<endl;
            cout<<"ID: "<<proid<<endl;
            cout<<"Name: "<<proname<<endl;
            cout<<"code: "<<procode<<endl;
            cout<<"price: "<<proprice<<endl;
            cout<<"amount: " << proamount << endl;
            found = true;
            break;
        }
    }
    cout<<endl;
    if(!found){
        cout<<"product not found"<<endl;
    }
    cout<<"\n==============================================================="<<endl;
}



void addtocart(string name,int amount){
    system("cls");
     ifstream fin("Database/customer/storage.csv");
     ofstream temp("temp.csv");
     ofstream fout("Database/customer/" + name_forcart+"'s cart.csv",ios::app);

     if(!fin || !fout||!temp){
        cout<<"can't open storage or cart file"<<endl;
     }

    bool found = false;
    string line;

    int i=1;

    while(getline(fin,line)){
        string No,proid,proname,procode,proprice,proamount;
        stringstream ss(line);

        getline(ss,No,',');
        getline(ss,proid,',');
        getline(ss,proname,',');
        getline(ss,procode,',');
        getline(ss,proprice,',');
        getline(ss,proamount,',');

        int pamount = stoi(proamount);
        int update = pamount;

        if(proname == name){
            if(amount <= pamount){
                fout<<No<<"."<<proid<<","<<proname<<","<<procode<<","<<proprice<<","<<amount<<endl;
                update = pamount - amount;
                found = true;
            }else{
                cout<<"this product don't have enough amount"<<endl;
            }
        }
        temp <<No<<","<<proid<<","<<proname<<","<<procode<<","<<proprice<<","<<update<<endl;
        i++;
    }
    cout<<"product add success"<<endl;

    if(!found){
        cout<<"product not found"<<endl;
    }

    fin.close();
    fout.close();
    temp.close();

    remove("Database/customer/storage.csv");
    rename("temp.csv","Database/customer/storage.csv");
}


void removecart(){
    ofstream fout("Database/customer/" + name_forcart+"'s cart.csv",ios::trunc);
    fout.close();
    system("cls");
    cout<<"Thank you for buying from our store"<<endl;
}


void checkout(){
    system("cls");
    ifstream fin("Database/customer/" + name_forcart + "'s cart.csv");
    if(!fin){
        cout<<"the file is not exist"<<endl;
        return;
    }

    cout<<"=================== cart list ========================"<<endl;
    cout<<"No.\tID\tName\tcode\tprice\tamount"<<endl;

    bool empty = true;
    float total =0;

    string line;
    while(getline(fin,line)){
        string No,proid,proname,procode,proprice,proamount;
        stringstream ss(line);

        getline(ss,No,',');
        getline(ss,proid,',');
        getline(ss,proname,',');
        getline(ss,procode,',');
        getline(ss,proprice,',');
        getline(ss,proamount,',');

        float price = stof(proprice);
        int amount = stof(proamount);

        cout<<No<<".\t"<<proid<<"\t"<<proname<<"\t"<<procode<<"\t"<<price<<"\t"<<amount<<endl;
        empty = false;
        total += price*amount;
    }
    
    if(empty){
        cout<<"the cart is empty"<<endl;
    }
    fin.close();
    cout<<"======================================================="<<endl;
    cout<<"The total cost: "<<total<<endl;


}


void sort_alpha(){ //need fix
    system("cls");
    ifstream fin("Database/customer/storage.csv");
    
    if(!fin){
        cout<<"the file doesn't exist"<<endl;
        return;
    }

    cout<<"=================== product list ========================"<<endl;
    cout<<"No.\tID\tName\tcode\tprice\tamount"<<endl;

    int count = 0;
    string line;
    while(getline(fin,line)){
        string No,proid,proname,procode,proprice,proamount;
        stringstream ss(line);

        getline(ss,No,',');
        getline(ss,proid,',');
        getline(ss,proname,',');
        getline(ss,procode,',');
        getline(ss,proprice,',');
        getline(ss,proamount,',');

        s[count].id = proid;
        s[count].name = proname;
        s[count].code = procode;
        s[count].price = stof(proprice);
        s[count].amount = stoi(proamount);

        count++;
    }
    fin.close();
    
    if(count == 0){
        cout<<"the storage is empty"<<endl;
        return;
    }

    //using sort bubble
    for(int i=0;i<count-1;i++){
        for(int j=0;j<count-i-1;j++){
            if(s[j].name > s[j+1].name){
                storage temp = s[j];
                s[j] = s[j+1];
                s[j+1] = temp;
            }
        }
    }


    for(int i=0;i<count;i++){
        cout<<i+1<<".\t"<<s[i].id<<"\t"<<s[i].name<<"\t"<<s[i].code<<"\t"<<s[i].price<<"\t"<<s[i].amount<<endl;
    }

    ofstream fout("Database/customer/storage.csv");
    for(int i=0;i<count;i++){
       fout<<i+1<<","<<s[i].id<<","<<s[i].name<<","<<s[i].code<<","<<s[i].price<<","<<s[i].amount<<endl;
    }
    fout.close();

}

void sort_category(){
    system("cls");
    ifstream fin("Database/customer/storage.csv");
    if(!fin){
        cout<<"the file doesn't exist"<<endl;
        return;
    }

    int count = 0;

    string line;
    while(getline(fin,line)&& count < ssize){
        string No,proid,proname,procode,proprice,proamount;
        stringstream ss(line);

        getline(ss,No,',');
        getline(ss,proid,',');
        getline(ss,proname,',');
        getline(ss,procode,',');
        getline(ss,proprice,',');
        getline(ss,proamount,',');

        s[count].id = proid;
        s[count].name = proname;
        s[count].code = procode;
        s[count].price = stof(proprice);
        s[count].amount = stoi(proamount);

        count++;
    }
    fin.close();
    
    if(count == 0){
        cout<<"the storage is empty"<<endl;
    }

    for(int i=0;i<count-1;i++){
        for(int j=0;j<count-i-1;j++){
            if(s[j].code > s[j+1].code){
                storage temp = s[j];
                s[j] = s[j+1];
                s[j+1] = temp;
            }
        }
    }

    cout<<"=================== product list ========================"<<endl;
    cout<<"No.\tID\tName\tcode\tprice\tamount"<<endl;

    for(int i=0;i<count;i++){
        cout<<i+1<<".\t"<<s[i].id<<"\t"<<s[i].name<<"\t"<<s[i].code<<"\t"<<s[i].price<<"\t"<<s[i].amount<<endl;
    }

    ofstream fout("Database/customer/storage.csv");
    for(int i=0;i<count;i++){
        fout<<i+1<<","<<s[i].id<<","<<s[i].name<<","<<s[i].code<<","<<s[i].price<<","<<s[i].amount<<endl;
    }
    fout.close();
}

void sort_price(){
    system("cls");
    ifstream fin("Database/customer/storage.csv");
    if(!fin){
        cout<<"the file doesn't exist"<<endl;
        return;
    }

    int count =0;

    string line;
    while(getline(fin,line)){
        string No,proid,proname,procode,proprice,proamount;
        stringstream ss(line);

        getline(ss,No,',');
        getline(ss,proid,',');
        getline(ss,proname,',');
        getline(ss,procode,',');
        getline(ss,proprice,',');
        getline(ss,proamount,',');

        s[count].id = proid;
        s[count].name = proname;
        s[count].code = procode;
        s[count].price = stof(proprice);
        s[count].amount = stoi(proamount);

       count++;
    }
    fin.close();
    
    if(count == 0){
        cout<<"the storage is empty"<<endl;
    }

    //sort using bubble
    for(int i=0;i<count-1;i++){
        for(int j=0;j<count-i-1;j++){
            if(s[j].price > s[j+1].price){
                storage temp = s[j];
                s[j] = s[j+1];
                s[j+1] = temp;
            }
        }
    }

    cout<<"=================== product list ========================"<<endl;
    cout<<"No.\tID\tName\tcode\tprice\tamount"<<endl;
    
    for(int i=0;i<count;i++){
        cout<<i+1<<".\t"<<s[i].id<<"\t"<<s[i].name<<"\t"<<s[i].code<<"\t"<<s[i].price<<"\t"<<s[i].amount<<endl;
    }

    ofstream fout("Database/customer/storage.csv");
    for(int i=0;i<count;i++){
        fout<<i+1<<","<<s[i].id<<","<<s[i].name<<","<<s[i].code<<","<<s[i].price<<","<<s[i].amount<<endl;
    }
    fout.close();
}