#include<iostream>

using namespace std;

class Polinom
{
    int* a;
    int n;
public:
    Polinom(int n);
    Polinom(int n, int* a);
    Polinom(const Polinom& ob);
    ~Polinom();
    friend istream& operator >> (istream& in, Polinom& p);
    friend ostream& operator << (ostream& out, Polinom& p);
    friend Polinom operator * (Polinom p1, Polinom p2);
    // {

    // int n = (p1.n - 1) + (this->n - 1) + 1;
    // int* a = new int[n];
    // for (int i = 0; i < n; i++)
    // {
    //     a[i] = 0;
    // }
    // for (int i = 0; i < p1.n; i++)
    // {
    //     for (int i1 = 0; i1 < this->n; i1++)
    //     {
    //         a[i1 + i] += p1.a[i] * this->a[i1];
    //     }
    // }
    // return Polinom(n, a);
    // }
};

Polinom::Polinom(const Polinom& ob)
{
    n=ob.n;
    a=new int[n];
    for(int i=0;i<n;i++)
        a[i]=ob.a[i];
}

Polinom::~Polinom()
{
    delete [] a;
}

Polinom::Polinom(int n, int* a)
{
    this->n = n;
    this->a = a;
}

Polinom::Polinom(int n)
{
    this->n = n;
    a = new int[n];
}


istream& operator >> (istream& in, Polinom& p)
{
    cout << "Input polinom\n";
    for (int i = p.n - 1; i >= 0; i--)
    {
        in >> p.a[i];
    }
    return in;
}

ostream& operator << (ostream& out, Polinom& p)
{
    out << "( ";
    for (int i = p.n - 1; i >= 0; i--)
    {
        out << p.a[i] << "x^" << i << " + ";
    }
    out << ")\n";
    return out;
}

Polinom operator * (Polinom p1, Polinom p2)
{
    int n = (p1.n - 1) + (p2.n - 1) + 1;
    int* a = new int[n];
    for (int i = 0; i < n; i++)
    {
        a[i] = 0;
    }
    for (int i = 0; i < p1.n; i++)
    {
        for (int i1 = 0; i1 < p2.n; i1++)
        {
            a[i1 + i] += p1.a[i] * p2.a[i1];
        }
    }
    return Polinom(n, a);
}


int main(int argc, char const* argv[])
{

    cout << "Size polinom 1\n";
    int n1;
    cin >> n1;
    Polinom p1(n1);
    cin >> p1;
    cout << p1;
    cout << "Size polinom 2\n";
    int n2;
    cin >> n2;
    Polinom p2(n2);
    cin >> p2;
    cout << p2;
    Polinom p3 = p1 * p2;
    cout << p1 << "*" << p2 << "=" << p3;
    return 0;
}
