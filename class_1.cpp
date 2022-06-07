/******************************************************************************
 
Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.
 
*******************************************************************************/
#include <iostream>
#include <cmath>
#include <vector>
 
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
  friend istream& operator>>(istream& in, Point& p);
};
 
// абстрактный класс обычно является вершиной иерархии классов, определяя только самое важное общее для всех классов-наследников
// так, в данном примере, фигура - абстракция. В классе определены только виртуальные методы для описания действий, которые можно сделать с любыми фигурами независимо от их типа
// Так как как печатать информацию о фигуре, определять ее площадь - совсем не ясно, то конкретной реализации виртуальных методов здесь сделать нельзя
// Присваивание прототипу функции значения 0 является способом показать, что это чисто виртуальная (абстрактная) функция, тело которой определить нельзя
// Класс, в котором есть хотя бы одна чисто виртуальная функция, называется абстрактным. Нельзя создать экземпляр этого класса, но можно создавать указатели и ссылки  и наследовать этот класс
// При наследовании будут унаследованы не права использования тех или иных уже реализованных функций, а обязанности переопределить чисто виртуальные функции в классе-наследнике
// Для фигуры определим чисто виртуальные функции - печати информации о фигуре, вычисления длины контура, площади и проверки принадлежности точки фигуре
class Figure
{
   public:
   virtual void Print()=0;
    virtual double Perimetr()=0;
    virtual double Area()=0;
    virtual bool InFigure(Point p)=0;
    
    // статическая функция принадлежит классу, а не объекту, поэтому может быть создана в том числе в
    // абстрактном классе, и может быть вызвана без объекта
    // данная статическая функция называется фабричным методом. Она возвращает указатель на созданный объект из некоторой иерархии классов
    // что за объект создавать, определяется методом, чтобы использующие классы (в нашем случае Paint) не знал конкретных классов-наследников фигуры
    static Figure* createFigure(int i);
};
 
// класс треугольника является наследником абстрактного класса фигуры, т.е. в нем мы обязаны переопределить все чисто виртуальные функции, иначе класс треугольника останется абстрактным
class Triangle : public Figure
{
    // в классе-родителе может понадобиться разрешить обращаться к private-элементам класса-родителя из наследников
    // для этого используется модификатор доступа protected
    protected:
    Point a,b,c;
    
    public:
    Triangle();
    Triangle(double x1, double y1,double x2, double y2, double x3, double y3);
    Triangle(Point _a, Point _b, Point _c);
   
    void Print();
    double Perimetr();
    
    double Area();
    bool InFigure(Point p);
    
    
    friend istream& operator>>(istream& in, Triangle& t);
    };
 
// при наследовании при определении класса после имени класса указывается режим наследования и имя родительского класса
// режим наследования - public, protected, private - задает правила, по которым будут определены модификаторы доступа унаследованных элементов в дочернем классе-родителе
// public - все правила доступа остаются такими же, как в классе-родителе
// protected -  public меняется на protacted
// private - все унаследованные элементы будут private
 
// класс четырехугольника наследует от класса треугольника, но тоже входит в иерархию классов-наследников от класса фигуры 
class Tetragon : public Triangle
{
    Point p;
    
    public:
    // новые методы
    Tetragon();
    Tetragon(double x1, double y1,double x2, double y2, double x3, double y3, double x4, double y4);
    Tetragon(Point _a, Point _b, Point _c, Point _d);
    bool IsConvex();
    
    // переопределение унаследованных методов
    void Print();
    double Perimetr();
    double Area();
    bool InFigure(Point p);
    friend istream& operator>>(istream& in, Tetragon& t);
};
 
// класс круга - тоже наследник фигуры, имеет другую структуру по сравнению с классами-многоугольниками (треугольником и четырехугольником)
// но для круга также можно выполнить все операции, определенные в абстрактном классе фигуры
class Circle : public Figure
{
    Point center; // центр
    double radius;  // радиус
    
    public:
    Circle(Point _p, double r);
    Circle();
    void Print();
    double Perimetr();
    double Area();
    bool InFigure(Point p);
    friend istream& operator>>(istream& in, Circle& c);
};
 
// класс для хранения рисунка в виде списка фигур.
class Paint
{
    // динамический массив будет хранить указатели на абстрактный класс фигуры. 
    // согласно принципу подставимости в этот массив можно будет помещать адреса любых наследников класса фигуры
    vector<Figure*> paint;
    
    public:
    void Add(int i);
    void Print();
};
 
// операторы ввода требуется добавить в классы-наследники фигуры, чтобы обеспечить ввод данных через универсальный механизм
istream& operator>>(istream& in, Point& p)
{
    in>>p.x>>p.y;
    return in;
}
 
istream& operator>>(istream& in, Triangle& t)
{
    in>>t.a>>t.b>>t.c;
    return in;
}
 
istream& operator>>(istream& in, Tetragon& t)
{
    in>>t.a>>t.b>>t.c>>t.p;
    return in;
}
 
istream& operator>>(istream& in, Circle& c)
{
    in>>c.center>>c.radius;
    return in;
}
 
 
// методы класса "Точка"
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
 
// методы класса "Треугольник"
Triangle::Triangle(double x1, double y1,double x2, double y2, double x3, double y3):a(x1,y1),b(x2,y2),c(x3,y3)
{}
 
Triangle::Triangle(Point _a, Point _b, Point _c):a(_a),b(_b),c(_c)
{}
 
// для работы фабричного метода создания объекта из иерархии классов-фигур требуется конструктор по умолчанию для наследников
Triangle::Triangle():a(0,0), b(0,0), c(0,0)
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
 
 
// методы класса "Четырехугольник"
// в заголовке должна быть проинициализирована базовая часть класса-наследника путем вызова конструктора базового класса
Tetragon::Tetragon(double x1, double y1,double x2, double y2, double x3, double y3, double x4, double y4):Triangle(x1,y1,x2,y2,x3,y3),p(x4,y4)
{cout<<"создано!"<<endl;}
 
Tetragon::Tetragon(Point _a, Point _b, Point _c, Point _d):Triangle(_a,_b,_c),p(_d)
{}
 
Tetragon::Tetragon(): Triangle(0,0,0,0,0,0),p(0,0)
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
   // вызов родительской версии унаследованного виртуального метода может привести к ошибке Triangle::InFigure(p)
   // ошибка связана с тем, что вирутальная природа заставляет вызываться не метод класса треугольника, а все-таки метод для четырехугольника
   // в результате чего возможна бесконечная рекурсия
   // выход - в ситуации, когда знаем о том, что функция является виртуальной, принудительно создавать объект нужного класса (в нашем случае - класса треугольник),
   // чтобы гарантировать вызов метода именно для этого типа
    return !Triangle(a,b,c).InFigure(p);
}
 
// методы для класса "Круг"
Circle::Circle(Point _p, double r): center(_p)
{
     radius=r;
}
 
Circle::Circle():center(0,0),radius(0)
{ }
    
void Circle::Print()
{
     cout<<"Окружность: \n Центр=";
     center.Print();
     cout<<"Радиус="<<radius<<endl;
}
 
double Circle::Perimetr()
{
     return 2*3.14*radius;
}
 
double Circle::Area()
{
     return 3.14*radius*radius;
}
 
bool Circle::InFigure(Point p)
{
     double d=center.Distance(p);
     return d<=radius;
}
 
// методы для класса "Рисунок"
// методы обеспечивают универсальную обработку любых объектов из иерархии классов-фигур
// необходимо писать эти методы так, чтобы они знали только про базовый класс иерархии Figure
// т.е. конкретные типы определяются только в методах класса Figure, тем самым определяя 
// место программного кода, куда нужно вносить изменения при расширении иерархии классов-фигур
void Paint::Add(int i)
{
    // создание фигуры обеспечивается статическим методом
    // передается номер выбранной пользоватем фигуры
    // для обращения к статической функции требуется указать имя класса и после двойного двоеточия имя метода
    Figure * f=Figure::createFigure(i);
    // адрес созданной фигуры добавляется в список
    paint.push_back(f);
}
 
// метод печати информации о рисунке - универсальная обработка классов-наследников абстрактного класса - алгоритм обработки не зависит от типов объектов-наследников и может быть описан в терминах абстрактного класса-родителя
void Paint::Print()
{
    cout<<"Рисунок:"<<endl;
    // вектор paint содержит адреса объектов-наследников класса фигура. На конкретном месте в этом векторе может находиться любой объект-наследник
    // поэтому пользуемся виртуальной природой функции Print()
    // paint[i] имеет тип Figure*, так как функция Print() является виртуальной, будет рассматриваться тип объекта-содержимого по адресу и вызываться версия функции Print() именно из этого класса
    
    for(int i=0;i<paint.size(); i++)
        paint[i]->Print();
    
    cout<<endl;
}
 
// фабричный метод создания фигуры
Figure* Figure::createFigure(int i)
{
    // создание фигуры обеспечивается на основе выбора пользователя (значение переменной i)
    // все ветки имеют одинаковую структуру кода, привязанную к конкретному классу иерархии
    // через возвращаемое значение в виде указателя на базовый класс обеспечивается возможность вернуть любого наследника
    switch(i)
    {
        case 1: 
        {
            // при создании объекта внутри ветки case требуется явно указать скобки, чтобы была видна область видимости и жизни
            // создаваемой переменной.
            // создается объект конкретного класса динамически, далее осуществляется вызов операции ввода - конкретная
            // реализации операции ввода обеспечивается за счет того, что в фабричном методе известен конкретный класс
            Triangle* f=new Triangle(); cin>>*f; return f;
        }
        case 2: 
        {
            Tetragon* f=new Tetragon(); cin>>*f; return f;
        }
        case 3: 
        {
            Circle* f=new Circle(); cin>>*f; return f;
        }
    }
    return NULL;
}
 
 
int main()
{
  /*  Triangle t(0,0,0,4,4,0);
    cout<<"Периметр="<<t.Perimetr()<<endl;
    cout<<"Площадь="<<t.Area()<<endl;
    Point p1(1,1), p2(4,4);
    cout<<t.InFigure(p1)<<" "<<t.InFigure(p2)<<endl;
   
    Tetragon tr(0,0,0,4,4,4,4,0);
    tr.Print();
    cout<<"Периметр="<<tr.Perimetr()<<endl;
    cout<<"Площадь="<<tr.Area()<<endl;
    Point p3(3,5);
    cout<<tr.InFigure(p1)<<" "<<tr.InFigure(p2)<<" "<<tr.InFigure(p3)<<endl;
   
    // принцип подставимости - любой объект-наследник может встать на место своего родителя
    // реализуется за счет того, что указатель или ссылка на объект базового класса может хранить адрес объекта класса-наследника
    Figure* p=&tr;
    // при работе с обычной переопределенной в наследнике функцией будет вызывать метод базового класса
    // p имеет тип Triangle, поэтому при обычной ситуации метод Perimetr() берется из базового класса
    // если функция виртуальная, то будет выбираться версия метода Perimetr() из класса-наследника
    // т.е. выбор версии метода осуществляется в момент выполнения программы по типу содержимого памяти, на которую указывает указатель
    cout<<"Периметр="<<(p->Perimetr())<<endl;
    cout<<"Площадь="<<(p->Area())<<endl;
    cout<<(p->InFigure(p1))<<" "<<(p->InFigure(p2))<<" "<<(p->InFigure(p3))<<endl;
   
    Circle circ(Point(0,0),2);
    p=&circ;
    cout<<"Периметр="<<(p->Perimetr())<<endl;
    cout<<"Площадь="<<(p->Area())<<endl;
    cout<<(p->InFigure(p1))<<" "<<(p->InFigure(p2))<<" "<<(p->InFigure(p3))<<endl;
    */
    
    Paint paint;
    for(int i=0;i<3;i++)
    {
        cout<<"Треугольник - 1, Четырехугольник - 2, Круг -3";
        int j;
        cin>>j;
        paint.Add(j);
    }
    paint.Print();
    
    return 0;
}
 
 
 
 
 
 


