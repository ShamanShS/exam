#include<iostream>

using namespace std;

class List
{
    struct Node
    {
        int info;
        Node* next;
        Node* prev;
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
        void Add(int info, int pos);
        void Remove(int pos);
        void Print();
    
    private:
        void Remove_Node(Node*& node);


};

List::List()
{
    Head = NULL;
    Tail = NULL;
}

List::~List()
{

}
void List::Remove_Node(Node*& node)
{
    Node* help = node;
    node = node ->prev;
    node = node -> next;
    delete help;
}


void List::Print()
{
    cout<<"(";
    for(Node*cur=Head; cur!=NULL; cur=cur->next)
        cout<<(cur->info)<<" ";
    cout<<")"<<endl;
}



int main(int argc, char const *argv[])
{
    List list;
    for (size_t i = 0; i < 10; i++)
    {
        list.Add(i+6, i);
    }
    list.Print();
    return 0;
}
