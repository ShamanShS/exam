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
    int size;
    public:
        List();
        ~List();
        void Add(int info, int pos);
        void Remove(int pos);
        void Print();
        bool Sim();
    private:
        void Remove_Node(Node*& node);
        void Remove_Node_Head(Node*& node);
        void Remove_Node_Tail(Node*& node);



};

List::List()
{
    Head = NULL;
    Tail = NULL;
    size = 0;
}

List::~List()
{

}
void List::Remove_Node(Node*& node)
{
    Node* help = node;
    node->next->prev = node ->prev;
    node->prev->next= node ->next;
    delete help;
}

void List::Remove_Node_Head(Node*& node)
{
    Node* help = node;
    node = node ->next;
    node ->prev = NULL;
    delete help;
}

void List::Remove_Node_Tail(Node*& node)
{
    Node* help = node;
    node = node ->prev;
    node ->next = NULL;
    delete help;
}


void List::Add(int info, int pos)
{
    if (pos == 0 && size == 0)
    {
        Head = new Node(info, Head, Tail);
        Tail = Head;
        size++;
        return;
    }
    if (pos == 0)
    {
        Head = new Node(info, Head, NULL);
        Head ->next->prev = Head;
        size++;
        return;
    }

    if (pos == size)
    {
        Tail = new Node(info, NULL, Tail);
        Tail->prev->next = Tail;
        size++;
        return;
    }
    
    if(pos > size/2 + 1)
    {
        Node* cur = Tail;
        int i = size - 1;
        while (i != pos + 1)
        {
            cur = cur ->prev;
            i--;
        }
        cur ->prev = new Node(info, cur, cur->prev);  
        cur ->prev->prev->next = cur->prev;
        size++;
    }
    else
    {
        Node* cur = Head;
        int i = 0;
        while (i != pos - 1)
        {
            i++;
            cur = cur ->next;
        }
        cur ->next = new Node(info, cur->next, cur);
        cur->next->next->prev = cur->next;
        size++;
    }
    
    
}

void List::Remove(int pos)
{
    if (pos == 0)
    {
        Remove_Node_Head(Head);
        size--;
        return;
    }

    if (pos == size - 1)
    {
        Remove_Node_Tail(Tail);
        size--;
        return;
    }
    if(pos > size/2 + 1)
    {
        Node* cur = Tail;
        int i = size - 1;
        while (i != pos)
        {
            cur = cur ->prev;
            i--;
        }
        Remove_Node(cur);
        size--;
        return;
    }
    else
    {
        Node* cur = Head;
        int i = 0;
        while (i != pos)
        {
            i++;
            cur = cur ->next;
        }
        Remove_Node(cur);
        size--;
        return;
    }

}

bool List::Sim()
{
    Node* curH = Head;
    Node* curT = Tail;
    for (size_t i = 0; i < size/2; i++)
    {
        if(curH->info != curT->info)
        {
            return false;
        }
        curH = curH->next;
        curT = curT ->prev;
    }
    return true;
    
    
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
        list.Add(1, i);
    }
    list.Print();
    list.Add(100, 5);
    list.Print();
    list.Add(2, 0);
    list.Print();
    list.Add(2, 12);
    list.Print();
    if(list.Sim())
    {
        cout << 1 << endl;
    }
    else
    {
       cout << 2 << endl; 
    }
    return 0;
}
