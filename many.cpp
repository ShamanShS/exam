#include<iostream>
#include<vector>

using namespace std;

class List
{

    public:
        struct Node
        {
            int info;
            Node* next;
            Node(int info, Node* next)
            {
                this->info = info;
                this->next = next;
            }
        };
        Node* Head;
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
}

List::~List()
{
    while (Head !=NULL)
    {
        Remove_Node(Head);
    }
    
}

void List::Remove_Node(Node*& node)
{
    Node* help = node;
    node = node->next;
    delete help;
}

void List::Add(int info, int pos)
{
    if(pos == 0)
    {
        Head = new Node(info, Head);
        return;
    }

    Node* cur =Head;
    int i = 0;
    while (i != pos -1 && cur !=NULL)
    {
        i++;
        cur = cur->next;
    }
    cur->next = new Node(info, cur->next);
}

void List::Remove(int pos)
{
    if(pos == 0)
    {
        Remove_Node(Head);
        return;
    }

    Node* cur = Head;
    int i = 0;
    while (i != pos - 1 && cur->next != NULL)
    {
        i++;
        cur = cur->next;
    }
    Remove_Node(cur->next);
}

void List::Print()
{
    cout << "(";
    for(Node* cur = Head; cur!= NULL; cur = cur->next)
    {
        cout << cur->info << " ";
    }
    cout << ")\n";
}

class Many : public List
{
    List list;

    public:
        Many(vector<int> a);
        Many();
        ~Many();
        void Add(int info, int pos);
        Many intersection(Many a, Many b);
        void Print();
};

Many::Many()
{
    List();
}

Many::Many(vector<int> a)
{
    for (size_t i = 0; i < a.size(); i++)
    {
        list.Add(a[i], i);
    }
}

Many::~Many()
{
    list.~List();
}

void Many::Add(int info, int pos)
{
    list.Add(info, pos);
}

void Many::Print()
{
    list.Print();
}

Many Many::intersection(Many a, Many b)
{
    vector<pair<int, int>> c_0;
    bool boo = true;
    for (Node* cur = a.Head; cur->next!=NULL; cur = cur->next )
    {
        boo = true;
        for (size_t i = 0; i < c_0.size(); i++)
        {
            if(c_0[i].first == cur->info && boo ) 
            {
                c_0[i].second++;
                boo = false;
            }
        }
        c_0.push_back(make_pair(cur->info, 1));
    }
    for (Node* cur = b.Head; cur->next!=NULL; cur = cur->next )
    {
        boo = true;
        for (size_t i = 0; i < c_0.size(); i++)
        {
            if(c_0[i].first == cur->info && boo ) 
            {
                c_0[i].second++;
                boo = false;
            }
        }
        c_0.push_back(make_pair(cur->info, 1));
    }
    vector<int> c;
    for (size_t i = 0; i < c_0.size(); i++)
    {
        if(c_0[i].second > 1)
        {
            c.push_back(c_0[i].first);
        }
    }
    return Many(c);
}

int main(int argc, char const *argv[])
{
    // List list;
    // for (size_t i = 0; i < 10; i++)
    // {
    //     list.Add(i+6, i);
    // }
    // list.Print();
    // list.Remove(0);
    // list.Print();
    
    Many many2;
    for (size_t i = 0; i < 10; i++)
    {
        many2.Add(i+6, i);
    }
    many2.Print();
    Many many1;
    for (size_t i = 0; i < 10; i++)
    {
        many1.Add(i, i);
    }
    many1.Print();
    Many many3 = many1.intersection(many1, many2);
    many3.Print();
    return 0;
}


