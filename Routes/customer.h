#include<iostream>
#include<fstream>
#include"storage.h"
using namespace std;

void sort(){
        system("cls");
        int n;
        while(true){
                cout<<"\nsort product by: "<<endl;
                cout<<"1.Alphabet"<<endl;
                cout<<"2.category"<<endl;
                cout<<"3.price"<<endl;
                cout<<"4.back"<<endl;
                cout<<"enter a number: ";cin>>n;
                switch(n){
                case 1:{
                        system("cls");
                        sort_alpha();
                        break;
                }
                case 2:{
                        system("cls");
                        sort_category();
                        break;
                }
                case 3:{
                        system("cls");
                        sort_price();
                        break;
                }
                case 4:{
                        system("cls");
                        return;
                        break;
                }
                default:{
                        cout<<"invalid choice"<<endl;
                        break;
                }
        
                }
        }
}

void customer_introduction(){
        while(true){
                int n;
                cout<<"1.sort products"<<endl;
                cout<<"2.find a product"<<endl;
                cout<<"3.display products"<<endl;
                cout<<"4.back"<<endl;
                cout<<"enter the number: ";cin>>n;
                switch(n){
                case 1: {
                        sort();
                        break;
                }
                case 2:{
                        string k;
                        cout<<"name of the product: ";cin>>k;
                        find_product(k);
                        break;
                }
                case 3:{
                        system("cls");
                        string p;
                        int m;
        
                        
                        while(true){
                                display();
                                cout<<"product name(stop to finish): ";cin>>p;
                                if(p == "stop") break;
                                cout<<"How many?: ";cin>>m;
                                addtocart(p,m);
                        }
        
                        checkout();
                        char confirm;
                        while(true){
                                cout<<"Are you Done buying(y/n): ";cin>>confirm;
                                if(confirm == 'y' || confirm=='Y'){
                                        removecart();
                                        break;
                                }
                                else if(confirm == 'n' || confirm == 'N'){
                                        return;
                                }else{
                                        cout<<"invalid choice"<<endl;
                                }
                        }
                        break;
                }
                case 4:{
                        return;
                        break;
                }
                default:{
                        cout<<"invalid choice"<<endl;
                        break;
                }
        
                }
        }
}

