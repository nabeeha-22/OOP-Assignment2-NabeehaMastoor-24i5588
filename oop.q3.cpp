#include <iostream>
#include <string>
using namespace std;

class Book {
public:
    int BookID;
    string Title;
    string Author;

    Book(int id, string t, string a) {
        BookID = id;
        Title = t;
        Author = a;
    }
};

class Node {
public:
    Book data;
    Node* next;
    Node* prev;

    Node(int id, string t, string a) : data(id, t, a) {
        next = nullptr;
        prev = nullptr;
    }
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;

public:
    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    ~DoublyLinkedList() {
        Node* temp;
        while (head) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }

    void addAtBeginning(int id, string title, string author) {
        Node* newNode = new Node(id, title, author);
        if (!head) {
            head = tail = newNode;
            return;
        }
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }

    void addAtEnd(int id, string title, string author) {
        Node* newNode = new Node(id, title, author);
        if (!tail) {
            head = tail = newNode;
            return;
        }
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

    void addAtPosition(int pos, int id, string title, string author) {
        if (pos <= 1) {
            addAtBeginning(id, title, author);
            return;
        }
        Node* temp = head;
        for (int i = 1; i < pos - 1 && temp; i++)
            temp = temp->next;
        if (!temp || !temp->next) {
            addAtEnd(id, title, author);
            return;
        }
        Node* newNode = new Node(id, title, author);
        newNode->next = temp->next;
        newNode->prev = temp;
        temp->next->prev = newNode;
        temp->next = newNode;
    }

    void deleteByID(int id) {
        if (!head) return;
        Node* temp = head;
        while (temp && temp->data.BookID != id)
            temp = temp->next;
        if (!temp) return;

        if (temp == head) head = head->next;
        if (temp == tail) tail = tail->prev;
        if (temp->prev) temp->prev->next = temp->next;
        if (temp->next) temp->next->prev = temp->prev;
        delete temp;
    }

    void displayForward() {
        Node* temp = head;
        while (temp) {
            cout << "BookID: " << temp->data.BookID
                << ", Title: " << temp->data.Title
                << ", Author: " << temp->data.Author << endl;
            temp = temp->next;
        }
        cout << endl;
    }

    void displayBackward() {
        Node* temp = tail;
        while (temp) {
            cout << "BookID: " << temp->data.BookID
                << ", Title: " << temp->data.Title
                << ", Author: " << temp->data.Author << endl;
            temp = temp->prev;
        }
        cout << endl;
    }

    // Bonus: Iterator class
    class Iterator {
    private:
        Node* current;
    public:
        Iterator(Node* node) { current = node; }
        Book& operator*() { return current->data; }
        Iterator& operator++() { current = current->next; return *this; }
        Iterator& operator--() { current = current->prev; return *this; }
        bool operator!=(const Iterator& other) const { return current != other.current; }
    };

    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }
    Iterator rbegin() { return Iterator(tail); }
    Iterator rend() { return Iterator(nullptr); }
};

int main() {
    DoublyLinkedList library;

    library.addAtEnd(1, "The Martian", "Andy Weir");
    library.addAtEnd(2, "Dune", "Frank Herbert");
    library.addAtBeginning(3, "1984", "George Orwell");
    library.addAtPosition(2, 4, "Foundation", "Isaac Asimov");

    cout << "Library (Forward):" << endl;
    library.displayForward();

    cout << "Library (Backward):" << endl;
    library.displayBackward();

    library.deleteByID(2);
    cout << "After deleting BookID 2:" << endl;
    library.displayForward();

    cout << "Using ranged-for (Forward):" << endl;
    for (auto book : library) {
        cout << "BookID: " << book.BookID
            << ", Title: " << book.Title
            << ", Author: " << book.Author << endl;
    }
    cout << endl;

    cout << "Using manual reverse iterator (Backward):" << endl;
    for (auto it = library.rbegin(); it != library.rend(); --it) {
        cout << "BookID: " << (*it).BookID
            << ", Title: " << (*it).Title
            << ", Author: " << (*it).Author << endl;
        if ((*it).BookID == library.begin().operator*().BookID) break;
    }

    return 0;
}
