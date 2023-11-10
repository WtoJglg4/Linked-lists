#include <iostream>
using namespace std;

struct elem{
    int id;
    int data;
    elem* next;
};

class list{
    public:
        int length;
        elem* head;
        list();
        void append(int);
        void print();  
        void clear();
        int find(int);
        void deleteById(int);
};  

list::list(){
    length = 0;
    head = NULL;
}

void list::append(int data){
    if (length == 0){
        elem* e = new elem{0, data, NULL};
        head = e;
        e->next = head;
    } else{
        elem* curr = head;
        while(curr->next != head){
            curr = curr->next;
        }
        elem* e = new elem{curr->id+1, data, head};
        curr->next = e;
    }      
    length++;
}

void list::print(){
    if (length == 0){
        cerr << "list is empty\n";
        exit(1);
    }
    cout << "index: ";
    elem* curr = head;
    while(curr->next != head){
        cout << curr->id << " ";
        curr = curr->next;
    }
    cout << curr->id << endl;
    
    cout << "list:  ";
    curr = head;
    while(curr->next != head){
        cout << curr->data << " ";
        curr = curr->next;
    }
    cout << curr->data << endl;
}

void list::clear(){
    elem* curr = head;
    elem* tmp;
    while(curr->next != head){
        tmp = curr->next;
        delete curr;
        curr = tmp;
    }
    delete curr, tmp;
    length = 0;
}

int list::find(int value){
    elem* curr = head;
    int indexVal = -1;
    while(curr->next != head){
        if (curr->data == value){
            indexVal = curr->id; 
        }
        curr = curr->next;
    }
    if (curr->data == value){
        indexVal = curr->id; 
    }
    return indexVal;
}

void list::deleteById(int index){
    if (index >= length || index < 0){
        cerr << "wrong index to delete\n";
        exit(1);
    }
    if (index == 0){
        elem* curr = head->next, *newHead = head;
        while(curr->next != head){
            curr->id--;
            curr = curr->next;
        }
        curr->id--;
        curr->next = head->next;
        delete head;
        head = newHead;
    } else if (index == length - 1){
        elem* curr = head;
        while(curr->next->next != head){
            curr = curr->next;
        }
        delete curr->next;
        curr->next = head;
    } else{
        elem* curr = head;
        bool flag = false;
        while(curr->next != head){
            if (curr->next->id == index){
                elem* temp = curr->next->next;
                delete curr->next;
                curr->next = temp;

            }
            if (flag){
                curr->id--;
            }
            curr = curr->next;
        }
        curr->id--;
    }
    length--;
}




int main(){
    list a;
    for (int i = 0; i < 20; i++){
        a.append(i);
    }
    a.print();
    a.append(112);
    a.print();
    
    cout << a.find(112) << " " << a.find(5) << " " << a.find(122) << endl;
    a.deleteById(6);
    a.print();
    a.deleteById(0);
    a.print();
    a.deleteById(20);
    a.print();
}