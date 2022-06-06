#include<iostream>
#include <climits>
#include <queue>
#include <stack>
#include <list>
#include <vector>

using namespace std;

class Grath
{
    int n;
    int m;

    int** a;
public:
    Grath(int n, int m);
    ~Grath();
        vector<int> were;
    void Input();
    void Print();

    bool Connect();
    void DFS(int v);
    void change();

private:
    bool Contains(vector<int> w, int t);
};

Grath::Grath(int n, int m)
{
    this->n = n;
    this->m = m;
    a = new int* [n];
    for (size_t i = 0; i < n; i++)
    {
        a[i] = new int[n];
        for (size_t i1 = 0; i1 < n; i1++)
        {
            a[i][i1] = i == i1 ? 0 : INT_MAX;
        }
    }
}


Grath::~Grath()
{
    for (size_t i = 0; i < n; i++)
    {
        delete[] a[i];
    }
    delete[] a;

}


void Grath::Print()
{
    cout<<"Graph:"<<endl;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
            if(a[i][j]!=INT_MAX)
                cout<<a[i][j]<<"\t";
            else
                cout<<"-"<<"\t";
        cout<<endl;
    }
    cout<<endl;
}

void Grath::Input()
{
    for (int i = 0; i < m; i++)
    {
        int begin, end, len;
        int choice;
        cout << "Input" << (i + 1) << " edge:" << endl;
        cout << "Start:"; cin >> begin;
        cout << "end:"; cin >> end;
        cout << "Len:"; cin >> len;
        cout << "Oriented (y - 1,n - 0):";
        cin >> choice;
        a[begin - 1][end - 1] = len;
        if (choice == 0)
            a[end - 1][begin - 1] = len;
    }
}

void Grath::DFS(int v)
{
if (!Contains(were, v)) were.push_back(v);
for (size_t i = 0; i < n; i++)
{
    if(a[v-1][i] != INT_MAX && !Contains(were, i+1) && v-1 !=i) DFS(i+1);
}
}

bool Grath::Contains(vector<int> w, int t)
{
    for (size_t i = 0; i < w.size(); i++)
    {
        if(w[i] == t)
        {
            return true;
        }
    }
    return false;
}

void Grath::change()
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t i1 = 0; i1 < n; i1++)
        {
            if(a[i1][i] !=INT_MAX && i!=i1 && a[i][i1] ==INT_MAX) a[i][i1] = a[i1][i];
        }
        
    }
    
}

bool Grath::Connect()
{
    were.clear();
    change();
    Print();
    DFS(1);
    if(were.size() == n)
    {
        return true;
    }
    else
    {
        return false;
    }
}


int main(int argc, char const* argv[])
{
    Grath g(4, 4);
    g.Input();
    g.Print();
    g.DFS(1);
    for (int n : g.were)
    {
        cout << n << "\t";
    }
    cout << endl;
    if(g.Connect())
    {
        cout << 1;
    }
    else
    {
        cout << 2;
    }
    
    return 0;
}

