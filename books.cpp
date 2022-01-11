#include <iostream>

class Book
{
    private:
        std::string title;
        std::string writer;
        int no;
        Book *next;
        friend class SLL;
};

class SLL
{
    private:
        Book *headPtr;
    public:
        SLL(){
            headPtr = NULL;
        };
        ~SLL(){
            while(!isEmpty())
                removeFront();
        };
        void addFront(std::string, std::string);
        bool isEmpty();
        void removeFront();
        void printList();
        void addFront();
        void removeChosen(int);
};

void print_menu();
void add_book(SLL *);
void remove_book(SLL *);

int main()
{
    SLL *myBooks = new SLL();
    int choice;

    while(1){
        print_menu();
        std::cout << "----> ";
        std::cin >> choice;
        std::cout << std::endl;
        switch(choice){
            case 1:
                add_book(myBooks);
                break;
            case 2: 
                remove_book(myBooks);
                break;
            case 3:
                myBooks->printList();
                break;
            case 4:
                return 0;
            default:
                std::cout << "Please enter only 1, 2, 3 or 4." << std::endl;
                return -1;
        }
    }
    return 0;
}

void SLL::addFront(std::string newBookT, std::string newBookW){
    Book *newBook = new Book;
    newBook->title = newBookT;
    newBook->writer = newBookW;
    newBook->no = 1;
    newBook->next = headPtr;
    headPtr = newBook;

    Book *p = headPtr->next;
    while(p != NULL){
        p->no++;
        p = p->next;
    }
};

bool SLL::isEmpty(){
    if(headPtr == NULL){
        return true;
    }
    return false;
};

void SLL::removeFront(){
    Book *p = headPtr;
    if(p){
        headPtr = headPtr -> next;
        delete p;
    }
};

void SLL::removeChosen(int n){
    Book *curr = headPtr;
    Book *prev = NULL;
    Book *temp = NULL;
    bool flag = false;

    while(curr != NULL){
        if(curr->no == n && prev == NULL){
            headPtr = curr->next;
            temp = curr->next;
            delete curr;
            flag = true;
        }
        else if(curr->no == n && curr->next == NULL){
            prev->next = NULL;
            temp = curr->next;
            delete curr;
            flag = true;
        }
        else if(curr->no == n){
            prev->next = curr->next;
            temp = curr->next;
            delete curr;
            flag = true;
        }
        if(flag){
            std::cout << n << ". book is now deleted." << std::endl;
            while(temp != NULL){
                temp->no--;
                temp = temp->next;
            }
            return;
        }

        prev = curr;
        curr = curr->next;
    }
    std::cout << n << " is not a valid book no." << std::endl;
};

void SLL::printList(){
    Book *ptr = headPtr;
    while(ptr != NULL){
        std::cout << "-" << ptr->no << "-" << std::endl;
        std::cout << "Title: " << ptr->title << std::endl;
        std::cout << "Writer: " << ptr->writer << std::endl;
        ptr = ptr->next;
    }
};

void print_menu(){
    std::cout << "\n=================\n"
                 "1. Add book\n"
                 "2. Remove book\n"
                 "3. List books\n"
                 "4. Exit\n"
                 "=================\n";
}

void add_book(SLL *books){
    std::string newBookT, newBookW;

    std::cin.ignore();
    std::cout << "Title: ";
    std::getline(std::cin, newBookT);
    std::cout << "Writer: ";
    std::getline(std::cin, newBookW);
    books->addFront(newBookT, newBookW);
}

void remove_book(SLL *books){
    int choice = 0;

    books->printList();
    std::cout << "\nWhich book you want to remove: ";
    std::cin >> choice;
    books->removeChosen(choice); 
}

