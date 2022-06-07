#include<iostream>

using namespace std;

class List
{
    struct Node
    {
        Node* next;
        Node* prev;
        int info;
        Node(int info, Node* next, Node* prev)
        {
            this->info = info;
            this->next = next;
            this->prev = prev;
        }
    };
    Node* Head;
    Node* Tail;

    public:
        List();
        ~List();
        void Add(int pos);
        void Remove(int pos);

    private;
        
};