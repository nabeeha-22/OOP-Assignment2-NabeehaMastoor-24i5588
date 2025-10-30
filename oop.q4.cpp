#include <iostream>
#include <string>
using namespace std;

class Customer {
public:
    int CustomerID;
    string Name;
    int Tickets;

    Customer(int id, string n, int t) {
        CustomerID = id;
        Name = n;
        Tickets = t;
    }
};

class Node {
public:
    Customer data;
    Node* next;

    Node(int id, string name, int tickets) : data(id, name, tickets) {
        next = nullptr;
    }
};

class Queue {
private:
    Node* front;
    Node* rear;

public:
    Queue() {
        front = nullptr;
        rear = nullptr;
    }

    ~Queue() {
        while (front) {
            Node* temp = front;
            front = front->next;
            delete temp;
        }
    }

    void enqueue(int id, string name, int tickets) {
        Node* newNode = new Node(id, name, tickets);
        if (!rear) {
            front = rear = newNode;
            return;
        }
        rear->next = newNode;
        rear = newNode;
    }

    void dequeue() {
        if (!front) {
            cout << "Queue is empty!" << endl;
            return;
        }
        Node* temp = front;
        front = front->next;
        if (!front) rear = nullptr;
        delete temp;
    }

    void display() {
        if (!front) {
            cout << "Queue is empty!" << endl;
            return;
        }
        Node* temp = front;
        cout << "Current Queue:\n";
        while (temp) {
            cout << "Customer ID: " << temp->data.CustomerID
                << ", Name: " << temp->data.Name
                << ", Tickets: " << temp->data.Tickets << endl;
            temp = temp->next;
        }
        cout << endl;
    }
};

// Bonus: Priority Queue (serves customers with higher ticket count first)
class PriorityQueue {
private:
    Node* front;

public:
    PriorityQueue() { front = nullptr; }

    ~PriorityQueue() {
        while (front) {
            Node* temp = front;
            front = front->next;
            delete temp;
        }
    }

    void enqueue(int id, string name, int tickets) {
        Node* newNode = new Node(id, name, tickets);
        if (!front || tickets > front->data.Tickets) {
            newNode->next = front;
            front = newNode;
            return;
        }
        Node* temp = front;
        while (temp->next && temp->next->data.Tickets >= tickets)
            temp = temp->next;
        newNode->next = temp->next;
        temp->next = newNode;
    }

    void dequeue() {
        if (!front) {
            cout << "Priority Queue is empty!" << endl;
            return;
        }
        Node* temp = front;
        front = front->next;
        delete temp;
    }

    void display() {
        if (!front) {
            cout << "Priority Queue is empty!" << endl;
            return;
        }
        Node* temp = front;
        cout << "Current Priority Queue:\n";
        while (temp) {
            cout << "Customer ID: " << temp->data.CustomerID
                << ", Name: " << temp->data.Name
                << ", Tickets: " << temp->data.Tickets << endl;
            temp = temp->next;
        }
        cout << endl;
    }
};

int main() {
    cout << "Normal Queue Simulation:\n";
    Queue q;
    q.enqueue(1, "Nabeeha", 2);
    q.enqueue(2, "Ibrahim", 4);
    q.enqueue(3, "Shahzad", 1);

    q.display();

    cout << "After serving one customer (dequeue):\n";
    q.dequeue();
    q.display();

    cout << "Priority Queue Simulation:\n";
    PriorityQueue pq;
    pq.enqueue(4, "Ainish", 3);
    pq.enqueue(5, "Fatima", 5);
    pq.enqueue(6, "Ayesha", 2);

    pq.display();

    cout << "After serving one (dequeue):\n";
    pq.dequeue();
    pq.display();

    return 0;
}
