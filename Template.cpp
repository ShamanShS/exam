/******************************************************************************
 
Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.
 
*******************************************************************************/
#include <iostream>
 
using namespace std;
 
/* шаблон класса (функции) позволяет использовать одни и те же алгоритмы для разных типов данных.
Если класс или функцию нужно сделать шаблоном, то их определение предваряется ключевым словом template и перечислением в уголовых скобках обозначений шаблонных типов данных
Имя шаблонного типа можно выбирать произвольно согласно правилам именования функций, классов, переменных
*/
template <class T>
class Vector 
{
    int n;     // размерность вектора
    // в месте использования шаблонного типа указывается вместо конкретного типа (double, int и пр) шаблонный тип Т
    T* a; // адрес памяти массива элементов
    
    public:
    // конструкторы
    Vector(int n);
    Vector(int n, T* a);
    // конструктор копирования
    Vector (const Vector& ob);
    ~Vector();
    // переопределение оператора присваивания
    Vector& operator=(Vector ob);
    
    /*Vector Summa(Vector ob);
    Vector Multiply(double b);
    double Multiply(Vector ob);
    */
    void Input();
    void Print();
    
    // перегрузка операций
    Vector operator+(Vector ob);
    Vector operator*(T b);
    T operator*(Vector ob);
    
    template <class V>
    friend istream& operator>>(istream&in, Vector<V>& ob);
    
    template <class V>
    friend ostream& operator<<(ostream&out, Vector<V> ob);
};
 
 
template <class T>
istream& operator>>(istream&in, Vector<T>& ob)
{
    for(int i=0;i<ob.n;i++)
        in>>ob.a[i];
    return in;
}
 
template <class T>
ostream& operator<<(ostream&out, Vector<T> ob)
{
    out<<"(";
    for(int i=0;i<ob.n-1;i++)
        out<<ob.a[i]<<",";
    out<<ob.a[ob.n-1]<<")"<<endl;
    return out;
}
 
// любой метод шаблона класса становится шаблоном функции
// за пределами шаблона класса требуется обращаться с указанием типа (шаблонного или конкретного) в угловых скобках - Vector<T>
template <class T>
Vector<T>::Vector(int n)
{
    if(n<=0) throw 1;
    
    this->n=n;
    a=new T[n];
    for(int i=0;i<n;i++)
        a[i]=0;
}
template <class T>
Vector<T>::Vector(int n, T* a)
{
    if(n<=0) throw 1;
    this->n=n;
    this->a=new T[n];
    for(int i=0;i<n;i++)
        this->a[i]=a[i];
}
 
template <class T>
Vector<T>::Vector(const Vector<T>& ob)
{
    n=ob.n;
    a=new T[n];
    for(int i=0;i<n;i++)
        a[i]=ob.a[i];
}
 
template <class T>
Vector<T>::~Vector()
{
    delete [] a;
}
 
template <class T>
Vector<T>& Vector<T>::operator=(Vector<T> ob)
{
    if(n!=ob.n)
    {
        delete [] a;
        n=ob.n;
        a=new T[n];
    }
    for(int i=0;i<n;i++)
        a[i]=ob.a[i];
    
    // требуется для возможности делать цепочку присваивания: a=b=c;    
    return *this;
}
 
template <class T>
void Vector<T>::Input()
{
    for(int i=0;i<n;i++)
        cin>>a[i];
}
 
template <class T>
void Vector<T>::Print()
{
    cout<<"(";
    for(int i=0;i<n-1;i++)
        cout<<a[i]<<",";
    cout<<a[n-1]<<")"<<endl;
}
 
template <class T>
Vector<T> Vector<T>::operator+(Vector<T> ob)
{
    if(n!=ob.n)
        throw 2;
    Vector<T> res(n);
    for(int i=0;i<n;i++)
        res.a[i]=a[i]+ob.a[i];
    return res;
}
 
template <class T>
Vector<T> Vector<T>::operator*(T b)
{
    Vector<T> res(n);
    for(int i=0;i<n;i++)
        res.a[i]=a[i]*b;
    return res;
}
 
template <class T>
T Vector<T>::operator*(Vector<T> ob)
{
    if(n!=ob.n)
        throw 2;
    T res=0;
    for(int i=0;i<n;i++)
        res+=a[i]*ob.a[i];
    return res;
}
 
template <class T>
Vector<T> operator*(T b, Vector<T> ob)
{
    return ob*b;
}
 
/*
если на основе какого-то класса генерируется конкретная версия класса на основе шаблона, необходимо
предусмотреть в этом классе различные конструкторы, операторы присваивания и другие операторы, которые могли использоваться для
шаблонного типа T при описании шаблона.
Например, если в шаблоне класса создается массив типа T, нужен конструктор по умолчанию.
Если есть присваивание (a[i]=0), нужны конструктор на основе одного числового параметра или оператор присваивания с этим же параметром.
Отсутствие необходимых элемент обнаруживание на этапе компиляции и показывается как ошибка.
*/
class Complex 
{
    double re, im;
    public:
    Complex ();
    Complex (double re);
    Complex (double re, double im);
    Complex& operator=(double re);
    Complex operator+(Complex ob);
    Complex operator*(Complex ob);
    Complex operator*(double a);
    Complex operator+=(Complex ob);
    friend istream& operator>>(istream& in, Complex& ob);
    friend ostream& operator<<(ostream& out, Complex ob);
};
 
Complex::Complex(double re)
{
    this->re=re; im=0;
}
 
Complex& Complex::operator=(double re)
{
    this->re=re; im=0;
    return (*this);
}
 
    
Complex::Complex()
{
    re=im=0;
}
 
Complex::Complex(double re, double im)
{
    this->re=re; this->im=im;
}
 
Complex Complex::operator+(Complex ob)
{
    return Complex(re+ob.re, im+ob.im);
}
 
Complex Complex::operator*(Complex ob)
{
    return Complex(re*ob.re-im*ob.im, re*ob.im+im*ob.re);
}
    
Complex Complex::operator*(double a)
{
    return Complex(re*a, im*a);
}
 
Complex Complex::operator+=(Complex ob)
{
    re+=ob.re; im+=ob.im;
    return (*this);
}
 
istream& operator>>(istream& in, Complex& ob)
{
    in>>ob.re>>ob.im;
    return in;
}
ostream& operator<<(ostream& out, Complex ob)
{
    out<<ob.re<<"i("<<ob.im<<") ";
    return out;
}
 
int main()
{
    try
    {
        // использование шаблона для генерации конкретного класса для вектора из комплексных чисел
        Vector<Complex> a(3),b(3);
        cin>>a>>b; 
        Vector<Complex> c=a+b;
        cout<<c<<endl;
        cout<<(a*b)<<endl;
        cout<<(a*Complex(5))<<endl;
    }
    catch (int i)
    {
        cout<<"Ошибка "<<i<<endl;
    }
    return 0;
}

