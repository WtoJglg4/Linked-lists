#include <iostream>
#include <iomanip>
using namespace std;

//элемент списка
struct elem{
    int id;     //индекс
    int data;   //значение
    elem* next; //следующий элемент
};

//односвязный кольцевой список
class list{
    public:
        int length;             //длина
        elem* head;             //первый элемент
        list();                 //контруктор
        void append(int);       //добавление в конец
        void print();           //печать всего списка
        void clear();           //удаление всех элементов
        int find(int);          //поиск индекса элемента по значению
        void deleteById(int);   //удаление элемента по индексу
};  

//интерфейс взаимодействия с пользователем
void menu(){
    cout << "\tОперации со списком\n";
    cout << "\tДобавить элемент в конец - 1\n";
    cout << "\tНайти индекс элемента - 2\n";
    cout << "\tУдалить элемент по индексу - 3\n";
    cout << "\tОчистить список - 4\n";
    cout << "\tНапечатать список - 5\n";
    cout << "\tВыход - 6\n";
    
    int operation;
    list list;
    while (true){
        cin >> operation;
        switch (operation)
        {
            case 1:{
                cout << "Введите элемент: ";
                int el;
                cin >> el;
                cout << endl;
                list.append(el);
                list.print();
                break;
            }
            case 2:{
                cout << "Введите элемент: ";
                int el;
                cin >> el;
                int index = list.find(el);
                if (index == -1){
                    cout << "Элемент не найден\n";
                } else{
                    cout << "Индекс найденного элемента: " << index << endl;
                }
                break;
            }
            case 3:{
                cout << "Введите индекс элемента: ";
                int index;
                cin >> index;
                list.deleteById(index);
                list.print();
                break;
            }
            case 4:{
                list.clear();
                cout << "Список очищен\n";
                break;
            }
            case 5:{
                list.print();
                break;
            }
            case 6:{
                list.clear();
                return;
            }
            default:{
                cout << "введена несуществующая операция\n";
                break;
            }
        }
    }
   
    
}   


//главная функция
int main(){
    menu();
}


//конструктор
list::list(){
    length = 0;
    head = NULL;
}

//добавление в конец
void list::append(int data){
    if (length == 0){
        //создать элемент, закольцованный сам на себя
        elem* e = new elem{0, data, NULL};
        head = e;
        e->next = head;
    } else{
        //добавить элемент после последнего
        //закольцевать на первый элемент
        elem* curr = head;
        while(curr->next != head){
            curr = curr->next;
        }
        elem* e = new elem{curr->id+1, data, head};
        curr->next = e;
    }      
    length++;   //прибавить длину
}

//печать всего списка
void list::print(){
    if (length == 0){
        cerr << "list is empty\n";
        exit(1);
    }

    cout << "index: ";
    elem* curr = head;
    while(curr->next != head){
        cout << setw(5) << curr->id << " ";
        curr = curr->next;
    }
    cout << setw(5) << curr->id << endl;
    
    cout << "list:  ";
    curr = head;
    while(curr->next != head){
        cout << setw(5) << curr->data << " ";
        curr = curr->next;
    }
    cout << setw(5) << curr->data << endl << endl;
}

//удаление всех элементов
void list::clear(){
    if (length == 0){
        return;
    }

    elem* curr = head;
    elem* tmp;
    while(curr->next != head){
        tmp = curr->next;
        delete curr;
        curr = tmp;
    }
    delete curr;
    length = 0;
}

//поиск индекса элемента по значению
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

//удаление элемента по индексу
void list::deleteById(int index){
    if (index >= length || index < 0){
        cerr << "wrong index to delete\n";
        exit(1);
    }
    if (index == 0){
        elem* curr = head->next;
        while(curr->next != head){
            curr->id--;             //понизить все индесы на 1
            curr = curr->next;
        }
        curr->id--;
        curr->next = head->next;    //закольцевать на второй элемент
        delete head;                //удалить первый элемент
        head = curr->next;          //второй теперь первый
    } else if (index == length - 1){
        elem* curr = head;
        while(curr->next->next != head){
            curr = curr->next;
        }
        delete curr->next;          //удалить последний
        curr->next = head;          //закольцевать предпоследний на первый
    } else{
        elem* curr = head;
        bool flag = false;          //отслеживаем удалили или нет
        while(curr->next != head){
            if (flag){              //если уже удалили
                curr->id--;         //понижаем все индексы на 1
            }
            if (curr->next->id == index){
                elem* temp = curr->next->next;
                delete curr->next;
                curr->next = temp;
                flag = true;
            }
            
            curr = curr->next;
        }
        curr->id--;
    }
    length--;
}