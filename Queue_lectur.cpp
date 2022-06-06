
#include <iostream>
 
using namespace std;
 
 
// очередь - частный случай линейной структуры данных, для которой удобно использование односвязного списка
// работает по принципу FIFO - первый пришел, первый ушел
// причины - динамически меняет размер, требуется доступ только к двум концам, поэтому операции минимальны по трудоемкости
class Queue 
{
    // конструктору узла не требуется второй параметр, так как добавляться будет всегда последний элемент
  struct Node
  {
      int info;
      Node* next;
      Node (int info){this->info=info; next=NULL;}
  };
  // для удобства требуется доступ к обоим концам очереди
  Node* head, *tail;
  
  public:
  Queue();
  ~Queue();
  void Print();
  bool IsEmpty();
  void Push(int info);
  int Peek();
  int Pop();
};
 
// инициализация пустой очереди
Queue::Queue()
{
    head=tail=NULL;   
}
 
// удаление всех оставлшихся оставшихся элементов - пока очередь не пуста, извлекаем очередной элемент
Queue::~Queue()
{
    while(!IsEmpty())
        Pop();
}
 
// обычно такой функции нет - включена для проверки
void Queue::Print()
{
    cout<<"(";
    for(Node*cur=head; cur!=NULL; cur=cur->next)
        cout<<(cur->info)<<" ";
    cout<<")"<<endl;
}
 
// проверка пустоты очереди
bool Queue::IsEmpty()
{
    return head==NULL;
}
 
// добавление элемента в очередь
void Queue::Push(int info)
{
    // при добавлении в пустую очередь надо сформировать единственный элемент очереди
    if(IsEmpty())
        head=tail=new Node(info);
    else
    {
        // добавление в конец очереди
        tail->next=new Node(info);
        tail=tail->next;
    }
}
 
// метод определения "кто следующий?"
int Queue::Peek()
{
    if(IsEmpty()) throw 1;
    return head->info;
}
 
// метод извлечения очередного элемента из очереди
int Queue::Pop()
{
    if(IsEmpty()) throw 1;
    int res=head->info;
    Node*help = head;
    head=head->next;
    delete help;
    // отдельная обработка извлечения единственного элемента очереди
    if(head==NULL) tail=NULL;
    return res;
 
}
 
// класс стек - принцип LIFO - последний пришел, первый ушел
class Stack 
{
    // конструктору требуются уже оба параметра, так как будет работать только с одним концом
    // удобным концом для этого является начало списка
  struct Node
  {
      int info;
      Node* next;
      Node (int info,Node*next){this->info=info; this->next=next;}
  };
  // стеку достаточно иметь доступ к первому элементу списка
  Node* head;
  
  public:
  Stack();
  ~Stack();
  void Print();
  bool IsEmpty();
  void Push(int info);
  int Peek();
  int Pop();
};
 
// методы стека аналогичны очереди, иногда проще
Stack::Stack()
{
    head=NULL;   
}
Stack::~Stack()
{
    while(!IsEmpty())
        Pop();
}
void Stack::Print()
{
    cout<<"(";
    for(Node*cur=head; cur!=NULL; cur=cur->next)
        cout<<(cur->info)<<" ";
    cout<<")"<<endl;
}
 
bool Stack::IsEmpty()
{
    return head==NULL;
}
 
void Stack::Push(int info)
{
    head=new Node(info,head);
}
 
int Stack::Peek()
{
    if(IsEmpty()) throw 1;
    return head->info;
}
 
int Stack::Pop()
{
    if(IsEmpty()) throw 1;
    int res=head->info;
    Node*help = head;
    head=head->next;
    delete help;
    
    return res;
}
 
// функция получения двоичного кода целого числа
// полученный двоичный код будем записывать в символьную строку
string BinaryCode(int n)
{
   // последовательно  записываем в стек остатки от деления на 2.
  // их надо будет выписывать в обратном порядке
    Stack s;
    while(n!=0)
    {
        s.Push(n%2);
        n/=2;
    }
// извлекая из стека, получаем нужный порядок    
string res="";
    while(!s.IsEmpty())
    {
        if(s.Pop()==1)
            res=res+"1";
        else
            res+="0";
    }
    return res;
}
 
int main()
{
    Queue q;
    Stack s;
    for(int i=0;i<5; i++)
    {
        q.Push(i); s.Push(i);
    }
    q.Print();
    s.Print();
    cout<<q.Peek()<<" "<<s.Peek()<<endl;
    cout<<"Очередь"<<endl;
    while(!q.IsEmpty())
        cout<<q.Pop()<<" ";
    cout<<endl<<"Стек"<<endl;
    while(!s.IsEmpty())
        cout<<s.Pop()<<" ";
    
 
    return 0;
}
 


