#include<iostream>

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


    private:    
        void Add(int info, Node*& root, int lvl);
        void Destroy(Node* root);
        void Print(Node* root);
        void Search(int t, int &res, Node* root);

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
    int a[]={7,3,6,8,1,2,4,5,10, 1002, -3};
    for(int i=0;i<11; i++)
        tree.Add(a[i]);
    tree.Print();
    cout<<endl;
    cout << tree.Search(4);
    return 0;
}
