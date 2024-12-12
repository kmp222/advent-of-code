#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

struct Node {
    long long data;  
    Node* next; 
    Node* prev;

    Node()
    {
        this->data = 0;
        this->next = nullptr;
        this->prev = nullptr;
    }

    Node(int data)
    {
        this->data = data;
        this->next = nullptr;
        this->prev = nullptr;
    }

};

class DoublyLinkedList {

public:

    Node* head;

    void insertAtEnd(Node*& head, int data)
{
    // Create a new node with the given data.
    Node* newNode = new Node(data);

    // Check if the doubly linked list is empty.
    if (head == nullptr) {
        head = newNode;
        return;
    }

    // Traverse to the last node of the list.
    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }

    // Update the next and previous pointers to insert the
    // new node at the end.
    temp->next = newNode;
    newNode->prev = temp;
    }
    
    DoublyLinkedList() : head(NULL) {}

    void display() {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node* temp = head;
        while (temp) {
            cout << temp->data << " <-> "; 
            temp = temp->next;
        }
        cout << "NULL" << endl; 
    }
};

DoublyLinkedList stones;

void iter_blink(Node *n) {

    while (n != NULL) {
        if (n->data == 0) {
            n->data = 1;
            n = n->next;
            continue;
        }

        string s = to_string(n->data);

        if (s.length() % 2 == 0) {
            Node *first_stone = new Node();
            Node *second_stone = new Node();

            int half_length = s.length() / 2;
            string stone_first_half = s.substr(0, half_length);
            string stone_second_half = s.substr(half_length, half_length);
            first_stone->data = stoi(stone_first_half);
            second_stone->data = stoi(stone_second_half);

            if (n->prev != nullptr) {
                n->prev->next = first_stone;
            } else {
                stones.head = first_stone;
            }

            first_stone->prev = n->prev;
            n->prev = nullptr;
            first_stone->next = second_stone;
            second_stone->prev = first_stone;

            if (n->next != nullptr) {
                second_stone->next = n->next;
                n->next->prev = second_stone;
                n->next = nullptr;

                n = second_stone->next;
                continue;
            }

            n = nullptr;
            continue;
        }

        n->data = (n->data) * 2024;
        n = n->next;
    }
}

int main() {

    std::fstream file("inputs/input.txt");

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
                std::istringstream iss(line);
                int n;
                while (iss >> n) {
                    Node *node = new Node();
                    stones.insertAtEnd(stones.head, n);
                }
        }

    }
    
    file.close();

    Node *n;

    for (int i = 0; i < 25; i++) {
        n = stones.head;
        iter_blink(n);
        std::cout << i << " blink";
    }

    int res = 0;

    n = stones.head;

    while (n != nullptr) {
        res++;
        n = n->next;
    }

    std::cout << res;

    return 0;

}