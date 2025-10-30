#include <iostream>
#include <string>
using namespace std;

class Feature {
public:
    string Name;
    Feature(string n) { Name = n; }
    virtual void analyze() = 0;
    virtual Feature* clone() const = 0;
    virtual ~Feature() {}
};

class LandFeature : public Feature {
public:
    LandFeature(string n) : Feature(n) {}
    void analyze() { cout << "Land Feature: " << Name << " detected" << endl; }
    Feature* clone() const { return new LandFeature(*this); }
};

class WaterFeature : public Feature {
public:
    WaterFeature(string n) : Feature(n) {}
    void analyze() { cout << "Water Feature: " << Name << " detected" << endl; }
    Feature* clone() const { return new WaterFeature(*this); }
};

class Node {
public:
    int FeatureID;
    Feature* feature;
    Node* next;
    Node(int id, Feature* f) {
        FeatureID = id;
        feature = f;
        next = nullptr;
    }
    ~Node() { delete feature; }
};

class SinglyLinkedList {
private:
    Node* head;
public:
    SinglyLinkedList() { head = nullptr; }

    ~SinglyLinkedList() {
        Node* temp;
        while (head) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }

    void insertAtEnd(int featureID, Feature* f) {
        Node* newNode = new Node(featureID, f);
        if (head == nullptr) {
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next != nullptr) temp = temp->next;
        temp->next = newNode;
    }

    void deleteByID(int featureID) {
        if (!head) return;
        if (head->FeatureID == featureID) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }
        Node* curr = head;
        while (curr->next && curr->next->FeatureID != featureID)
            curr = curr->next;
        if (curr->next) {
            Node* temp = curr->next;
            curr->next = temp->next;
            delete temp;
        }
    }

    void displayAll() {
        Node* temp = head;
        while (temp) {
            cout << "Feature ID: " << temp->FeatureID << " -> ";
            temp->feature->analyze();
            temp = temp->next;
        }
        cout << endl;
    }

    void reverseList() {
        Node* prev = nullptr;
        Node* curr = head;
        Node* next = nullptr;
        while (curr) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head = prev;
    }

    SinglyLinkedList operator+(const SinglyLinkedList& other) const {
        SinglyLinkedList result;
        Node* temp = head;
        while (temp) {
            result.insertAtEnd(temp->FeatureID, temp->feature->clone());
            temp = temp->next;
        }
        temp = other.head;
        while (temp) {
            result.insertAtEnd(temp->FeatureID, temp->feature->clone());
            temp = temp->next;
        }
        return result;
    }

    SinglyLinkedList& operator=(const SinglyLinkedList& other) {
        if (this == &other) return *this;
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        head = nullptr;
        Node* temp = other.head;
        while (temp) {
            insertAtEnd(temp->FeatureID, temp->feature->clone());
            temp = temp->next;
        }
        return *this;
    }
};

int main() {
    SinglyLinkedList list1;

    list1.insertAtEnd(1, new LandFeature("Forest"));
    list1.insertAtEnd(2, new WaterFeature("River"));
    list1.insertAtEnd(3, new LandFeature("Mountain"));
    list1.insertAtEnd(4, new WaterFeature("Ocean"));

    cout << "Original List:" << endl;
    list1.displayAll();

    list1.deleteByID(2);
    cout << "After Deleting Feature with ID 2:" << endl;
    list1.displayAll();

    list1.reverseList();
    cout << "After Reversing List:" << endl;
    list1.displayAll();

    SinglyLinkedList list2;
    list2.insertAtEnd(5, new LandFeature("Desert"));
    list2.insertAtEnd(6, new WaterFeature("Lake"));

    cout << "Second List:" << endl;
    list2.displayAll();

    SinglyLinkedList combined = list1 + list2;
    cout << "Combined List (+ Operator):" << endl;
    combined.displayAll();

    SinglyLinkedList copyList;
    copyList = combined;
    cout << "Copied List (= Operator):" << endl;
    copyList.displayAll();

    return 0;
}
