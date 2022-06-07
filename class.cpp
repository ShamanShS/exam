/******************************************************************************
 
Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.
 
*******************************************************************************/
#include <iostream>
#include <cmath>
 
using namespace std;
 
/*
наследование.
дочерний класс принимает все, что есть у класса-родителя
1) могут быть новые методы
2) могут быть новые данные
3) могут быть новые реализации унаследованных методов
*/
 
class Point
{
  double x,y;
  
  public:
  Point(double x, double y);
  void Print();
  double Distance(Point p);
};
 
class Triangle
{
    // в классе-родителе может понадобиться разрешить обращаться к private-элементам класса-родителя из наследников
    // для этого используется модификатор доступа protected
    protected:
    Point a,b,c;
    
    public:
    Triangle(double x1, double y1,double x2, double y2, double x3, double y3);
    Triangle(Point _a, Point _b, Point _c);
    void Print();
    
    // виртуальная функция вызывается для ситуации вызова через ссылку или указатель на базовый класс
    // достаточно указать ключевое слово virtual при определении функции в базовом классе
    virtual double Perimetr();
    double Area();
    bool InFigure(Point p);
    };
 
// при наследовании при определении класса после имени класса указывается режим наследования и имя родительского класса
// режим наследования - public, protected, private - задает правила, по которым будут определены модификаторы доступа унаследованных элементов в дочернем классе-родителе
// public - все правила доступа остаются такими же, как в классе-родителе
// protected -  public меняется на protacted
// private - все унаследованные элементы будут private
class Tetragon : public Triangle
{
    Point p;
    
    public:
    // новые методы
    Tetragon(double x1, double y1,double x2, double y2, double x3, double y3, double x4, double y4);
    Tetragon(Point _a, Point _b, Point _c, Point _d);
    bool IsConvex();
    
    // переопределение унаследованных методов
    void Print();
    double Perimetr();
    double Area();
    bool InFigure(Point p);
    
};
 
// в заголовке должна быть проинициализирована базовая часть класса-наследника путем вызова конструктора базового класса
Tetragon::Tetragon(double x1, double y1,double x2, double y2, double x3, double y3, double x4, double y4):Triangle(x1,y1,x2,y2,x3,y3),p(x4,y4)
{}
 
Tetragon::Tetragon(Point _a, Point _b, Point _c, Point _d):Triangle(_a,_b,_c),p(_d)
{}
 
void Tetragon::Print()
{
    /*
    Triangle::Print(); // вызов унаследованного метода, который переопределн в классе-наследнике - указание полного имени с указанием имени базового класса 
    p.Print();
    */
    cout<<"{";a.Print();
    cout<<",";b.Print();
    cout<<",";c.Print();
    cout<<",";p.Print();
    cout<<"}"<<endl;  
    
}
double Tetragon::Perimetr()
{
    // a,b,c теперь доступны, так как они унаследованы и имеют в базовом классе доступ типа protected
    return a.Distance(b)+b.Distance(c)+c.Distance(p)+a.Distance(p);
}
double Tetragon::Area()
{
    if(IsConvex())
        return Triangle(a,b,c).Area()+Triangle(a,c,p).Area();
    else
        return Triangle(a,b,c).Area()-Triangle(a,c,p).Area();
}
bool Tetragon::InFigure(Point p)
{
    // вызов базовой версии Triangle::InFigure(p) функции может трактоваться как вызов для объета-родителя
    // базовая версия метода работает с теми данными и методами, про которые ей известно, т.е. про данные и 
    // методы базового класса
    if (IsConvex())
        return Triangle::InFigure(p) || Triangle(a,c,this->p).InFigure(p);
    else
        return Triangle::InFigure(p) && !Triangle(a,c,this->p).InFigure(p);
}
 
bool Tetragon::IsConvex()
{
    return !Triangle::InFigure(p);
}
 
Triangle::Triangle(double x1, double y1,double x2, double y2, double x3, double y3):a(x1,y1),b(x2,y2),c(x3,y3)
{}
 
Triangle::Triangle(Point _a, Point _b, Point _c):a(_a),b(_b),c(_c)
{}
 
void Triangle::Print()
{
    cout<<"{";a.Print();
    cout<<",";b.Print();
    cout<<",";c.Print();
    cout<<"}"<<endl;
}
 
double Triangle::Perimetr()
{
    return a.Distance(b)+b.Distance(c)+a.Distance(c);
}
double Triangle::Area()
{
    double p=Perimetr()/2;
    return sqrt(p*(p-a.Distance(b))*(p-b.Distance(c))*(p-a.Distance(c)));
}
bool Triangle::InFigure(Point p)
{
    double s=Area();
    
    Triangle t1(a,b,p);
    double s1=t1.Area();
    double s2=Triangle(a,c,p).Area();
    double s3=Triangle(b,c,p).Area();
    
    return labs(s1+s2+s3-s)<=0.000001;
}
 
 
 
Point::Point(double x, double y)
{
    this->x=x; this->y=y;    
}
 
void Point::Print()
{
    cout<<"("<<x<<","<<y<<") ";
}
 
double Point::Distance(Point p)
{
    return sqrt((x-p.x)*(x-p.x)+(y-p.y)*(y-p.y));
}
 
int main()
{
    Triangle t(0,0,0,4,4,0);
    cout<<"Периметр="<<t.Perimetr()<<endl;
    cout<<"Площадь="<<t.Area()<<endl;
    Point p1(1,1), p2(4,4);
    cout<<t.InFigure(p1)<<" "<<t.InFigure(p2)<<endl;
   
    Tetragon tr(0,0,0,4,4,4,4,0);
    cout<<"Периметр="<<tr.Perimetr()<<endl;
    cout<<"Площадь="<<tr.Area()<<endl;
    Point p3(3,5);
    cout<<tr.InFigure(p1)<<" "<<tr.InFigure(p2)<<" "<<tr.InFigure(p3)<<endl;
   
    // принцип подставимости - любой объект-наследник может встать на место своего родителя
    // реализуется за счет того, что указатель или ссылка на объект базового класса может хранить адрес объекта класса-наследника
    Triangle* p=&tr;
    // при работе с обычной переопределенной в наследнике функцией будет вызывать метод базового класса
    // p имеет тип Triangle, поэтому при обычной ситуации метод Perimetr() берется из базового класса
    // если функция виртуальная, то будет выбираться версия метода Perimetr() из класса-наследника
    // т.е. выбор версии метода осуществляется в момент выполнения программы по типу содержимого памяти, на которую указывает указатель
    cout<<"Периметр="<<(p->Perimetr())<<endl;
    
     
    return 0;
}
 
 


