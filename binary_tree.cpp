#include<iostream>
#include <climits>

using namespace std;

class Tree
{
    struct Node
    {
        int info;
        int lvl;
        Node* Left;
        Node* Right;
        Node(int info, int lvl)
        {
            this ->info = info;
            this ->lvl = lvl;
            Right=Left=NULL;
        }
    };

    Node* main_root;

    public:
        Tree();
        ~Tree();
        
        void Add(int info);
        void Print();
        int Search(int t);
        bool Repetition();

    private:    
        int Min_Right_root(Node* root);
        void Add(int info, Node*& root, int lvl);
        void Destroy(Node* root);
        void Print(Node* root);
        void Search(int t, int &res, Node* root);
        void Repetition(Node* root, int &min, bool &b);

};

Tree::Tree()
{
    main_root = NULL;
}

void Tree::Destroy(Node* root)
{
    if (root == NULL) return;
    Destroy(root->Left);
    Destroy(root->Right);
    delete root;
}

Tree::~Tree()
{
    Destroy(main_root);
}

void Tree::Add(int info)
{
    Add(info, main_root, 0);
}

void Tree::Add(int info, Node*& root, int lvl)
{
    if(root == NULL)
    {
        root = new Node(info, lvl);
        return;
    }
    if (root ->info > info)
    {
        Add(info, root->Left, root->lvl + 1);
    }
    else
    {
        Add(info, root->Right, root->lvl + 1);
    }
}


int Tree::Search(int t)
{
    int res = 0;
    Search(t, res, main_root);
    return res;
}

void Tree::Search(int t, int& res, Node* root)
{
    if(root->lvl == t)
    {
        res++;
        return;
    }
    if(root->Left!=NULL)
    {
        Search(t, res, root->Left);
    }
    if (root->Right!=NULL)
    {
        Search(t, res, root->Right);
    } 
}

bool Tree::Repetition()
{
    int min = INT_MAX;
    bool b = true;
    Repetition(main_root, min, b);
    return b;

}

int Tree::Min_Right_root(Node* root)
{
    root = root ->Right;
    while (root->Left!=NULL)
    {
        root = root ->Left;
    }
    return root->info;
    
}
void Tree::Repetition(Node* root, int &min, bool &b)
{
    if(!b) return;
    if (root -> Left != NULL)
    {
         Repetition(root ->Left, min, b);
    }
    
    if(root ->Right != NULL)
    {
        if (root->info == Min_Right_root(root))
        {
            b = false;
            return;
        }
        Repetition(root ->Right, min, b);
    }
}

void Tree::Print()
{
    if(main_root == NULL)
    {
        cout << "NULL" << endl;
    }
    else
    {
        Print(main_root);
    }
}

void Tree::Print(Node* root)
{
    if (root == NULL) return;
    Print(root->Left);
    cout << root->info <<"(" << root->lvl << ")" <<" ";
    Print(root->Right);
}


int main(int argc, char const *argv[])
{
    Tree tree;
    int a[]={7,3,6,1,13,2,11,0,10, 111, 3};
    for(int i=0;i<11; i++)
        tree.Add(a[i]);
    tree.Print();
    cout<<endl;
    cout << tree.Search(4);
    cout<<endl;
    if(tree.Repetition())
    {
        cout<< "N" <<endl;
    }
    else{
        cout<< "Y" <<endl;
    }
    return 0;
}
