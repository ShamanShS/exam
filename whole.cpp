
#include <iostream>
#include <cmath>
 
using namespace std;
 
/*
отношение "часть-целое" (агрегация и композиция) описывает общие правила контруирования и функционирования сложных объектов,
состояющих из других объектов
*/
 
// класс "Точка на плоскости"
class Point
{
  double x,y;   // координаты точки
  
  public:
  Point(double x, double y);
  void Print();
  // функция получения расстояния между двумя точками
  double Distance(Point p);
};
 
// класс "Треугольник"
class Triangle
{
    // треугольник задается тремя вершинами - объектами-точками
    Point a,b,c;
    
    
    public:
    // конструкторы нужны на все случаи, которыми удобно будет инициализировать объекты
    // пользователь может знать про точку как составляющую треугольника, может не знать - тогда
    // инициализация проводится покоординатно
    Triangle(double x1, double y1, double x2, double y2, double x3, double y3);
    Triangle(Point p1, Point p2, Point p3);
    void Print(); 
    // операция получения периметра треугольника
    double Perimetr();
    // операция получения площади треугольника
    double Area();
    // операция проверки принадлежности точки треугольнику
    bool InTriangle(Point p);
    // функции-геттеры (getter) - чтобы обеспечить доступ к данным класса, чтобы
    // не было возможности изменить данные класса, можно добавлять специальные функции
    // для получения (для чтения) нужных данных объектов классов - в данном случае получить доступ к вершинам
    Point getA();
    Point getB();
    Point getC();
};
 
// класс "Четырехугольник"
class Tetragon
{
    // можно преставить как треугольник (3 вершины будет содержать треугольник) и четвертой точки
    Triangle t;
    Point p;
    
    public:
    Tetragon(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
    Tetragon(Point p1, Point p2, Point p3, Point p4);
    void Print(); 
    double Perimetr();
    double Area();
    bool InTetragon(Point p);
    // помимо аналогичных треугольнику операций добавляем операцию проверки выпуклости четырехугольника
    bool IsConvex();
};
 
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
 
// контруктор целого должен обеспечить создание частей до начала основного алгоритма инициализации целого
// поэтому вызов констукторов частей осуществляется в заголовке - указание имени переменной класса и параметров, которыми
// этот объект должен быть проинициализирован
Triangle::Triangle(double x1, double y1, double x2, double y2, double x3, double y3):a(x1,y1),b(x2,y2),c(x3,y3)
{
    /*
    ошибка - так как нарушен уровень доступа - x и y - private-данные класса Point, поэтому закрыты для 
    внешнего использования, включая и класс-целое, в данном случае из класса Triangle
    a.x=x1; a.y=y1;
    b.x=x2; b.y=y2;
    c.x=x3; c.y=y3;
    */
}
 
// в данном случае вызывается конструктор копирования класса Point - он создается автоматически, если не объявлен программистом
Triangle::Triangle(Point p1, Point p2, Point p3): a(p1),b(p2), c(p3)
{
}
 
void Triangle::Print()
{
    cout<<"{"; 
    a.Print(); cout<<",";
    b.Print(); cout<<",";
    c.Print(); cout<<"}";
}
 
double Triangle::Perimetr()
{
    return a.Distance(b)+b.Distance(c)+c.Distance(a);
}
 
// вычисление площади по формуле Герона
double Triangle::Area()
{
    double p=Perimetr()/2;
    return sqrt(p*(p-a.Distance(b))*(p-b.Distance(c))*(p-c.Distance(a)));
}
 
// точка принадлежит треугольнику, если сумма площадей треугольников, которые образованы
// ребром исходного треугольника и проверяемой точкой, совпадает с площадью всего треугольника
bool Triangle::InTriangle(Point p)
{
    double s=Area();
    // создаем локальный объект треугольника и вычисляем его площадь
    Triangle t(a,b,p);
    double s1=t.Area();
    
    // так как вспомогательные треугольники нужны только для выполнения одной операции, можно
    // создавать анонимные объекты - вызов конструктора без сохранения объекта и сразу же вызов нужного метода для этого объекта
    // повторно обратиться к этому объекту уже будет нельзя
    double s2=Triangle(b,c,p).Area();
    double s3=Triangle(a,c,p).Area();
    return s1+s2+s3-s<0.00001;
        
}
 
Point Triangle::getA()
{
    return a;    
}
Point Triangle::getB()
{
    return b;
}
 
Point Triangle::getC()
{
    return c;
}
 
Tetragon::Tetragon(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4):t(x1,y1,x2,y2,x3,y3),p(x4,y4)
{}
 
Tetragon::Tetragon(Point p1, Point p2, Point p3, Point p4):t(p1,p2,p3),p(p4)
{}
 
void Tetragon::Print()
{
    cout<<"{"; 
    t.getA().Print(); cout<<",";
    t.getB().Print(); cout<<",";
    t.getC().Print(); cout<<",";
    p.Print(); cout<<"}";    
}
double Tetragon::Perimetr()
{
    return t.getA().Distance(t.getB())+t.getB().Distance(t.getC())+t.getC().Distance(p)+p.Distance(t.getA());
}
 
// операции вычисления площади четырехугольника, проверки принадлежности точки четырехугольнику зависят
// от того, является ли четырехугольник выпуклым
double Tetragon::Area()
{
    if(IsConvex())
        return t.Area()+Triangle(t.getB(), t.getC(), p).Area();
    return t.Area()-Triangle(t.getB(), t.getC(), p).Area();
        
}
 
bool Tetragon::InTetragon(Point p1)
{
    if(IsConvex())
        return t.InTriangle(p1) || Triangle(t.getB(), t.getC(), p).InTriangle(p1);
    return t.InTriangle(p1) && !Triangle(t.getB(), t.getC(), p).InTriangle(p1);
    
}
 
bool Tetragon::IsConvex()
{
    // для любого четырехугольника существует порядок перебора вершин, чтобы проверка выпуклости
    // заключалась исключительно в проверке принадлежности четвертой вершины треугольнику,
    // образованным тремя первыми точками
    return !t.InTriangle(p);
}
 
 
int main()
{
    cout<<"Треугольник"<<endl;
    Triangle t(0,0,0,4,4,0);
    t.Print();
    cout<<"Площадь:"<<t.Area()<<endl;
    Point p1(1,1), p2(4,4);
    cout<<t.InTriangle(p1)<<endl;
    cout<<t.InTriangle(p2)<<endl;
 
    cout<<"Четырехугольник выпуклый"<<endl;
    Tetragon tg1(Point(0,0),Point(0,1), Point(2,1), Point(1,0));
    tg1.Print();
    cout<<"Площадь:"<<tg1.Area()<<endl;
    cout<<tg1.InTetragon(p1)<<endl;
    cout<<tg1.InTetragon(p2)<<endl;
    
    cout<<"Четырехугольник не выпуклый"<<endl;
    Tetragon tg2(Point(0,0),Point(0,5), Point(2,1), Point(5,0));
    tg2.Print();
    cout<<"Площадь:"<<tg2.Area()<<endl;
    cout<<tg2.InTetragon(p1)<<endl;
    cout<<tg2.InTetragon(p2)<<endl;
    
    return 0;
}


