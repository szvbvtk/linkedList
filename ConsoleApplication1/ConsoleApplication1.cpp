#include <iostream>
#include <ctime>

using namespace std;

// pozamieniać te inty na templatki wszędzie
template <typename T>
struct Node {
    struct Node<T>* prev = nullptr;
    T data;
    struct Node<T>* next = nullptr;
};

template <typename T>
struct LinkedList {
    struct Node<T>* head = nullptr;
    struct Node<T>* tail = nullptr;
    int size = 0;

    void pushBack(T data) {

        // tworzenie węzła
        Node<T>* n = new Node<T>();
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

    void pushFront(T data) {

        // tworzenie węzła
        Node<T>* n = new Node<T>();
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

        if (size != 1) {
            // zmiana drugiego element na pierwszy (ustawienie go na pozycji head)
            head = head->next;

            // usunięcie elementu, który przed chwilą pełnił rolę head
            delete head->prev;

            head->prev = nullptr;
        }
        else {
            delete head;
            head = tail = nullptr;
        }

        // zmniejszenie informacji o ilości elementów znajdujących się w liście
        size--;
    }

    void removeLast() {

        // walidacja czy jakikolwiek element znajduje się w liście
        if (head == nullptr) {
            cout << "\nNie można usunąć, w liście nie znajduje się żaden element\n";
            return;
        }

        if (size != 1) {
            tail = tail->prev;

            delete tail->next;

            tail->next = nullptr;
        }
        else {
            delete tail;
            tail = head = nullptr;
        }

        // zmniejszenie informacji o ilości elementów znajdujących się w liście
        size--;

    }

    void checkRange(int i) {
        if (size == 0 || i < 0 || i > size - 1) {
            throw out_of_range("Błędny zakres");
        }
    }

    // zmienić z voida można dodać sprawdzeni czy blizej konca czy poczatku i sie przesuwac albo od head next albo od tail prev
    T get(int i) {

        checkRange(i);

        Node<T>* n = head;

        for (int j = 0; j < i; j++) {
            n = n->next;
        }

        return n->data;
    }

    void changeData(int i, T new_data) {

        checkRange(i);

        Node<T>* n = head;

        for (int j = 0; j < i; j++) {
            n = n->next;
        }

        n->data = new_data;
    }

    Node<T>* search(T data, int (*func)(T, T)) {
        Node<T>* n = head;
        int result{};

        while (n != nullptr) {
            result = func(data, n->data);

            if (result == 0) return n;

            n = n->next;
        }
        return nullptr;
    }

    bool searchAndDelete(T data, int (*func)(T, T)) {
        Node<T>* n = search(data, func);

        if (n == nullptr) return false;
        else {
            if (n == head) {
                head = n->next;
                head->prev = nullptr;
            }
            else if (n == tail) {
                tail = n->prev;
                tail->next = nullptr;
            }
            else {
                n->next->prev = n->prev;
                n->prev->next = n->next;
            }

            delete n;
            size--;



            return true;
        }
    }

    void addInOrder(T data, int (*func)(T, T)) {
        if (head == nullptr) {
            pushFront(data);
        }
        else if (func(data, head->data) == -1) {
            pushFront(data);
        }
        else if (func(data, tail->data) == 1) {
            pushBack(data);
        }
        else {

            Node<T>* n = head;

            while (n != nullptr) {
                if (func(data, n->data) == 1) {  // dopóki jest większe
                    n = n->next;
                }
                else {
                    Node<T>* new_node = new Node<T>();
                    new_node->data = data;
                    n->prev->next = new_node;
                    new_node->prev = n->prev;
                    n->prev = new_node;
                    new_node->next = n;
                    break;
                }
            }
        }
        size++;
    }

    void clear() {
        Node<T>* n = head;
        Node<T>* lastFound = nullptr;
        
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

        Node<T>* n = head;

        // iteracja po węzłach

        while (n != nullptr) {
            cout << n->data.f1 << ' ' << n->data.f2 << '\n';
            n = n->next;
        }

    }
};

struct simple_object {
    int f1;
    char f2;
};

int compareSimpleObjects(simple_object o1, simple_object o2) {
    if (o1.f1 == o2.f1)
        return 0;
    else if (o1.f1 < o2.f1)
        return -1;
    else
        return 1;
}

int main()
{
    setlocale(LC_ALL, "pl_PL");

    /*LinkedList<int>* list1 = new LinkedList<int>();
    list1->removeFirst();
    list1->pushFront(2105);
    list1->pushBack(2001);
    list1->pushBack(4445665);
    list1->pushFront(1);
    list1->removeFirst();
    list1->removeLast();
    list1->removeLast();
    list1->print();
    list1->clear();
    list1->print();*/



    //LinkedList<simple_object>* list1 = new LinkedList<simple_object>();
    //simple_object obj1{ 1, 'a' };
    //simple_object obj2{ 2, 'b' };
    //simple_object obj3{ -5, 'c' };
    //simple_object obj4{ 4, 'd' };
    //list1->pushFront(obj1);
    //list1->pushBack(obj2);
    //list1->pushBack(obj4);
    //list1->addInOrder(obj3, compareSimpleObjects);
    //list1->removeLast();
    //list1->removeLast();
    //list1->removeLast();
    //list1->clear();

    //list1->print();

    //list1->changeData(1, obj3);
    // 
    //list1->print();
    /*try {
        simple_object obj3 = list1->get(1);
        cout << '\n' << obj3.f1 << '\n';
    }
    catch (const out_of_range& ex) {
        cout << ex.what();
    }*/

    //Node<simple_object>* returnedNode = list1->search(simple_object{2, 'b' }, compareSimpleObjects);
    //if (returnedNode == nullptr)
    //    cout << "\nNie znaleziono\n";
    //else
    //    cout << '\n' << returnedNode << ' ' << returnedNode->data.f1 << ' ' << returnedNode->data.f2 << '\n';

    //if (list1->searchAndDelete(simple_object{ 4, 'd' }, compareSimpleObjects))
    //    cout << "Węzeł usunięty";
    //else
    //    cout << "Niepowodzenie";

    //cout << "\n\n";
    //list1->print();


    char alphabet[] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','y','x','z' };



    srand(time(NULL));

    LinkedList<simple_object>* list1 = new LinkedList<simple_object>();

    for (int k = 1; k <= 5; k++) {

        int quantity = pow(10, k);

        // dodawanie na końcu
        clock_t start_time = clock();
        for (int i = 0; i < quantity; i++) {
            simple_object obj;
            obj.f1 = (rand() % 50) + 1;
            obj.f2 = alphabet[rand() % 26];
        }
        clock_t end_time = clock();

        double measured_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
        cout << measured_time;

    }
}
