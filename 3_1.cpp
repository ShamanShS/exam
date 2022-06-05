#include<iostream>

using namespace std;


class Rectangle
{
    double* x;
    double* y;
    

    public:
        Rectangle();
        void centerM();
        void turn ();
        friend ostream& operator << (ostream &out, Rectangle &c);
        friend istream& operator >> (istream &in, Rectangle &c);
        friend Rectangle operator ! (Rectangle p);
        friend Rectangle operator +(Rectangle p, double* v);
};

Rectangle::Rectangle()
{
    x = new double[5];
    y = new double[5];
    for(int i = 0; i<5; i++)
    {
        x[i] = 0;
        y[i] = 0;
    }

}

istream& operator >> (istream &in, Rectangle &c)
{
    for (size_t i = 0; i < 4; i++)
    {
        cout << "Input point (x,y) " << i+1 << endl;
        in >> c.x[i+1] >> c.y[i+1];
    }
    c.centerM();
    return in;
}

ostream& operator << (ostream &out, Rectangle &c)
{
    for (size_t i = 0; i < 4; i++)
    {
        out << "Point " << i << " : (" << c.x[i+1] << "," << c.y[i+1] << ")\n"; 
    }
}

Rectangle operator ! (Rectangle p)
{
    double x1[5] = {0, 0, 0 ,0 ,0};
    double y1[5] = {0, 0, 0 ,0 ,0};
    for (size_t i = 0; i < 4; i++)
    {
        x1[i+1] = p.x[i+1] - p.x[0];
        y1[i+1] = p.y[i+1] - p.y[0];
    }
    for (size_t i = 0; i < 4; i++)
    {
        int t = x1[i+1];
        x1[i+1] = y1[i+1];
        y1[i+1] = -t;
    }
    for (size_t i = 0; i < 4; i++)
    {
        p.x[i+1] = x1[i+1] + p.x[0];
        p.y[i+1] = y1[i+1] + p.y[0];
    }    
}

Rectangle operator +(Rectangle p, double* v)
{
    for (size_t i = 0; i < 4; i++)
    {
        p.x[i+1]+=v[0];
        p.y[i+1]+=v[1];
    }
    
}

void Rectangle::centerM()
{
    x[0] = (x[1] + x[2]) / 2;
    y[0] = (y[1] + y[3]) / 2;
}


int main(int argc, char const *argv[])
{
    Rectangle p;
    cin >> p;
    cout << p;
    double vector[2] = {0, 0};
    cout << "Input vector\n";
    cin >> vector[0] >> vector[1];
    p+vector;
    // !p;
    // cout << p;
    // !p;
    // !p;
    // !p;
    cout << p;
    return 0;
}
