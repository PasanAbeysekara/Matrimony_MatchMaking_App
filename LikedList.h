#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <list>

using namespace std;

template <typename T>
struct Node {
    T data;
    Node<T> *next;
};

template <typename T>
class LinkedList {
public:
    Node<T> *head;
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

    void push_back(const T &data) {
        Node<T> *newNode = new Node<T>();
        newNode->data = data;
        newNode->next = nullptr;

        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        ++size;
    }

    void pop_front() {
        if (!head) return;
        Node<T> *temp = head;
        head = head->next;
        delete temp;
        --size;
    }

    int getSize() const { return size; }

    typedef bool (*Comparator)(const T &, const T &);

    void sort(Comparator comp) {
        if (!head || !head->next) return;

        Node<T> *current = head;
        while (current->next) {
            Node<T> *check = current->next;
            while (check) {
                if (comp(check->data, current->data)) {
                    T temp = current->data;
                    current->data = check->data;
                    check->data = temp;
                }
                check = check->next;
            }
            current = current->next;
        }
    }

    void print() const {
        Node<T> *current = head;
        while (current) {
            cout << current->data << " -> ";
            current = current->next;
        }
        cout << "null" << endl;
    }

private:
    Node<T> *tail;
    int size;
};
