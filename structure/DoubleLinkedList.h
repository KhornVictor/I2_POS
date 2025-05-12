#include<iostream>
using namespace std;

struct Node{
    string data;
    Node *next;
    Node *previous;
};

struct List{
    int size;
    Node *head;
    Node *tail;
};

List* create(){
    List* newlist = new List;
    newlist -> head = NULL;
    newlist -> tail = NULL;
    newlist -> size = 0;
    return newlist;
}

void add_begin(List *list,string newdata){
    cout << "Insert the " << newdata << " at the begin of list" << endl;
    Node *newnode = new Node;
    newnode -> data = newdata;
    newnode -> previous = NULL;
    newnode -> next = list -> head;
    if (list -> size == 0) list -> tail = newnode;
    else list -> head -> previous = newnode;
    list -> head = newnode;
    list -> size++;
}

void add_end(List *list, string newdata){
    cout << "Insert the " << newdata << " at the end of the list" << endl;
    Node *newnode = new Node;
    newnode -> data = newdata;
    newnode -> previous = list -> tail;
    newnode -> next = NULL;
    if (list -> size == 0) list -> head = newnode;
    else list -> tail -> next = newnode;
    list -> tail = newnode;
    list -> size ++;
}

void add_specific(List *list, string newdata, int position) {
    Node* newnode = new Node;
    newnode->data = newdata;
    if (position == 0 || list->size == 0) add_begin(list, newdata);
    else if (position = list->size) add_end(list, newdata); 
    else if(position < 0 || position > list -> size) cout << "Invalid Position" << endl;
    else {
        Node* temporary = list->head;
        for (int i = 1; i < position - 1; i++){temporary = temporary->next;}
        newnode->previous = temporary;
        newnode->next = temporary->next; 
        if (temporary->next != NULL)temporary->next->previous = newnode;
        temporary->next = newnode;
        list->size++;
    }
}

void display_head(List* list){
    cout << "Display head: " << endl;
    Node *temporary = new Node;
    temporary = list -> head;
    while(temporary != NULL){
        cout << "- " << temporary -> data << endl;
        temporary = temporary -> next;
    }
}

void display_tail(List* list){
    cout << "Display tail: " << endl;
    Node *temporary = new Node;
    temporary = list -> tail;
    while(temporary != NULL){
        cout << "- " << temporary -> data << endl;
        temporary = temporary -> previous;
    }
}


