#include<iostream>

using namespace std;

class List
{
    struct Node
    {
        int info;
        Node* next;
        Node(int info, Node* next)
        {
            this -> info = info;
            this -> next = next;
        }
    };

    Node* Head;

    public:
        List();
        ~List();
        void Add(int info,int pos);
        void Remove(int pos);
        void Print();
        void Add_sr();

    private:
        void RemoveNode(Node*& node);
};

void List::RemoveNode(Node*& node)
{
    Node* help = node;
    node = node->next;
    delete help;
}


List::List()
{
    Head = NULL;
}

List::~List()
{
    while (Head!=NULL)
    {
        RemoveNode(Head);
    }
    
}

void List::Add(int info, int pos)
{
    if(pos == 0)
    {
        Head = new Node(info, Head);
        return;
    }
    if (pos < 0) throw 1;
    Node* cur = Head;
    int i = 0;
    while(i != pos-1 && cur !=NULL)
    {
        i++;
        cur = cur->next;
    }
    if(cur == NULL)
    {

    }
    cur ->next = new Node(info, cur->next);
}

void List::Remove(int pos)
{
    if (pos == 0)
    {
        RemoveNode(Head);
        return;
    }

    Node*cur = Head;
    int i = 0;
    while (i != pos - 1 && cur->next != NULL)
    {
        i++;
        cur = cur ->next;
    }
    if(cur ->next == NULL)
    {

    }
    RemoveNode(cur->next);
}

void List::Print()
{
    cout<<"(";
    for(Node*cur=Head; cur!=NULL; cur=cur->next)
        cout<<(cur->info)<<" ";
    cout<<")"<<endl;
}

void List::Add_sr()
{
    int pos_m;
    int pos = 0;
    int maxx = 0;
    int minn = 100000;
    for (Node* cur = Head; cur!=NULL; cur = cur -> next)
    {
        if (cur ->info > maxx)
        { 
            maxx = cur -> info;
            pos_m = pos;
        }
        if (cur ->info < minn) minn = cur -> info;
        pos++;
    }
    Add((maxx+minn) / 2, pos_m+1);
}



int main(int argc, char const *argv[])
{
    List list;
    for (size_t i = 0; i < 10; i++)
    {
        list.Add(i+6, i);
    }
    list.Print();
    list.Add_sr();
    list.Print();
    list.Remove(0);
    list.Print();
    return 0;
}

