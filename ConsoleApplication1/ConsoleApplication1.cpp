#include <iostream>

using namespace std;

// pozamieniać te inty na templatki wszędzie
//template <typename T>
struct Node {
    struct Node* prev = nullptr;
    int data = NULL;
    struct Node* next = nullptr;
};


struct LinkedList {
    struct Node* head = nullptr;
    struct Node* tail = nullptr;
    int size = 0;

    void pushBack(int data) {

        // tworzenie węzła
        Node* n = new Node();
        n->data = data;

        n->prev = tail;

        // jeśli nie został wcześniej dodany żaden element
        if (tail != nullptr) {
            tail->next = n;
        }
        else {
            head = n;
        }

        tail = n;

        // zwiększenie informacji o ilości elementów znajdujących się w liście
        size++;
    }

    void pushFront(int data) {

        // tworzenie węzła
        Node* n = new Node();
        n->data = data;

        n->next = head;

        // jeśli nie został wcześniej dodany żaden element
        if (head != nullptr) {
            head->prev = n;
        }
        else {
            tail = n;
        }

        head = n;

        // zwiększenie informacji o ilości elementów znajdujących się w liście
        size++;
    }


    void removeFirst() {

        // walidacja czy jakikolwiek element znajduje się w liście
        if (head == nullptr) {
            cout << "\nNie można usunąć, w liście nie znajduje się żaden element\n";
            return;
        }

        // zmiana drugiego element na pierwszy (ustawienie go na pozycji head)
        head = head->next;

        // usunięcie elementu, który przed chwilą pełnił rolę head
        delete head->prev;

        head->prev = nullptr;

        // zmniejszenie informacji o ilości elementów znajdujących się w liście
        size--;
    }

    void removeLast() {

        // walidacja czy jakikolwiek element znajduje się w liście
        if (head == nullptr) {
            cout << "\nNie można usunąć, w liście nie znajduje się żaden element\n";
            return;
        }

        tail = tail->prev;

        delete tail->next;

        tail->next = nullptr;

        // zmniejszenie informacji o ilości elementów znajdujących się w liście
        size--;
    }

    // zmienić z voida
    void get(int i) {

    }

    void changeData(int i, int data) {

    }

    // nie wiem o co chodzi
    void search() {

    }

    // tez nie wiem o co chodzi
    void searchAndDelete() {

    }

    void add() {

    }

    void clear() {
        Node* n = head;
        Node* lastFound = nullptr;
        
        if (head == nullptr) {
            cout << "Lista nie zawiera żadnych elementów";
            return;
        }

        while (true) {
            lastFound = n;

            n = n->next;

            if (n == nullptr)
                break;

            delete n->prev;

            size--;
        }

        delete lastFound;

        // ustawienie tail i head na nullptr
        head = tail = nullptr;
    }

    void print() {

        if (head == nullptr) {
            cout << "Lista jest pusta";
            return;
        }

        Node* n = head;

        // iteracja po węzłach

        while (n != nullptr) {
            cout << n->data << '\n';
            n = n->next;
        }

    }
};

int main()
{
    setlocale(LC_ALL, "pl_PL");

    LinkedList* list1 = new LinkedList();
    list1->removeFirst();
    list1->pushFront(2105);
    list1->pushBack(2001);
    list1->pushBack(4445665);
    list1->pushFront(1);
    list1->removeFirst();
    list1->removeLast();

    list1->print();

    list1->clear();

    list1->print();
    // pamiętać o delete
}
