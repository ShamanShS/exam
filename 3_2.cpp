#include<iostream>
#include<vector>

using namespace std;

class Vector
{
    vector<pair <int, int>> v;
    int n;
    public:
        Vector(vector<pair <int, int>> v, int n);
        Vector();
        // ~Vector();

        friend ostream& operator << (ostream& out, Vector& v);
        friend istream& operator >> (istream& in, Vector& v);
        friend Vector operator+(Vector v1, Vector v2);
};

istream& operator >> (istream& in, Vector& vec)
{
    cout << "size vector\n";
    int n;
    in >> vec.n;
    cout << "vector\n";
    for (size_t i = 0; i < vec.n; i++)
    {
        int a;
        in >> a;
        if (a != 0)
        {
            vec.v.push_back(make_pair(a, i));
        }
    }
    return in;
}

ostream& operator << (ostream& out, Vector& vec)
{
    int t = 0;
    out << "[";
    for (size_t i = 0; i < vec.n; i++)
    {
        if(vec.v[t].second == i)
        {
            out << vec.v[t].first <<", ";
            t++;
        }
        else
        {
            out << 0 << ", ";
        }
        
    }
    out << "]";
    return out;
}

Vector::Vector()
{

}

Vector::Vector(vector<pair <int, int>> v, int n)
{
    this ->n = n;
    for (size_t i = 0; i < n; i++)
    {
        if (v[i].first !=0)
        {
            this->v.push_back(v[i]);
        }
    }
    
}

Vector operator+(Vector v1, Vector v2)
{
    vector<pair <int, int>> v;
    int t1 = 0;
    int t2 = 0;
    for (size_t i = 0; i < v1.n; i++)
    {
        if(v1.v[t1].second < v2.v[t2].second)
        {
            v.push_back(make_pair(v1.v[t1].first, v1.v[t1].second));
            t1++;
        }
        else if (v1.v[t1].second > v2.v[t2].second)
        {
            v.push_back(make_pair(v2.v[t2].first, v2.v[t2].second));
            t2++;
        }
        else
        {
            v.push_back(make_pair(v2.v[t2].first + v1.v[t1].first, v2.v[t2].second));
            t1++;
            t2++;
        }
    }
    return Vector(v, v1.n);
}


int main(int argc, char const *argv[])
{
    Vector a;
    Vector b;
    
    cin >> a >> b;
    Vector c = a+b;
    cout << a << " +\n" << b << " =\n" << c;
    return 0;
}
