#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    char data;
    Node* next;
    Node(char d) { data = d; next = nullptr; }
};

class LinkedListStack {
private:
    Node* top;
public:
    LinkedListStack() { top = nullptr; }
    ~LinkedListStack() {
        while (top) {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    }
    bool isEmpty() { return top == nullptr; }
    void push(char val) {
        Node* newNode = new Node(val);
        newNode->next = top;
        top = newNode;
    }
    char pop() {
        if (isEmpty()) return '\0';
        Node* temp = top;
        char val = temp->data;
        top = top->next;
        delete temp;
        return val;
    }
};

class ArrayStack {
private:
    char* arr;
    int capacity;
    int top;
public:
    ArrayStack(int size) {
        capacity = size;
        arr = new char[capacity];
        top = -1;
    }
    ~ArrayStack() { delete[] arr; }
    bool isEmpty() { return top == -1; }
    bool isFull() { return top == capacity - 1; }
    void push(char val) {
        if (isFull()) return;
        arr[++top] = val;
    }
    char pop() {
        if (isEmpty()) return '\0';
        return arr[top--];
    }
};

void ChangeLocationIterative(char* Array, int b1, int b2, bool useLinkedStack) {
    if (useLinkedStack) {
        LinkedListStack stack;
        for (int i = b1; i <= b2; i++) stack.push(Array[i]);
        for (int i = b1; i <= b2; i++) Array[i] = stack.pop();
    }
    else {
        ArrayStack stack(b2 - b1 + 1);
        for (int i = b1; i <= b2; i++) stack.push(Array[i]);
        for (int i = b1; i <= b2; i++) Array[i] = stack.pop();
    }
}

void PrintPatternIterative(int n, bool useLinkedStack) {
    if (useLinkedStack) {
        LinkedListStack stack;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= i; j++) {
                if (j == i) cout << n - i + 1;
                else cout << 1 << " ";
            }
            cout << endl;
        }
    }
    else {
        ArrayStack stack(100);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= i; j++) {
                if (j == i) cout << n - i + 1;
                else cout << 1 << " ";
            }
            cout << endl;
        }
    }
}

int main() {
    cout << "=== LINKED LIST STACK: ChangeLocation ===" << endl;
    char arr1[8] = { 'C','O','M','P','U','T','E','R' };
    ChangeLocationIterative(arr1, 2, 6, true);
    for (int i = 0; i < 8; i++) cout << arr1[i] << " ";
    cout << "\n\n";

    cout << "=== ARRAY STACK: ChangeLocation ===" << endl;
    char arr2[8] = { 'C','O','M','P','U','T','E','R' };
    ChangeLocationIterative(arr2, 2, 6, false);
    for (int i = 0; i < 8; i++) cout << arr2[i] << " ";
    cout << "\n\n";

    cout << "=== LINKED LIST STACK: Print Pattern ===" << endl;
    int n1 = 4;
    PrintPatternIterative(n1, true);
    cout << "\n";

    cout << "=== ARRAY STACK: Print Pattern ===" << endl;
    int n2 = 4;
    PrintPatternIterative(n2, false);
    cout << "\n";

    cout << "=== Algorithm Analysis Report ===" << endl;
    cout << "Linked List Stack:\n";
    cout << " - Push: O(1)\n";
    cout << " - Pop:  O(1)\n";
    cout << " - Memory: dynamic (extra pointer per node)\n\n";

    cout << "Array Stack:\n";
    cout << " - Push: O(1)\n";
    cout << " - Pop:  O(1)\n";
    cout << " - Memory: fixed, contiguous\n\n";

    cout << "Performance Summary:\n";
    cout << " - Both stacks have O(1) time for push and pop.\n";
    cout << " - Linked list stack is flexible but uses more memory.\n";
    cout << " - Array stack is faster but size-limited.\n";

    return 0;
}
