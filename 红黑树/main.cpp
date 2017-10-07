/*
性质1. 节点是红色或黑色
性质2. 根是黑色
性质3. 每个红色节点的两个子节点都是黑色 (从每个叶子到根的所有路径上不能有两个连续的红色节点)
性质4. 从任一节点到其每个叶子的所有路径都包含相同数目的黑色节点
*/

#include <stdio.h>
#include <stdlib.h>
typedef enum Color   // 使用枚举类型，定义红黑树结点颜色
{
    RED = 0,
    BLACK = 1
}Color;

typedef struct Node     //定义红黑树结点类型
{
    struct Node *parent;
    struct Node *left;
    struct Node *right;
    int value;
    Color color;
}Node, *Tree;

Node *nil=NULL;           //为了避免讨论结点的边界情况，定义一个nil结点代替所有的NULL
Node* Parent(Node *z)     //返回某结点的父母
{
    return z->parent;
}
Node* Left(Node *z)       //返回左子树
{
    return z->left;
}
Node *Right(Node *z)      //返回右子树
{
    return z->right;
}
void LeftRotate(Tree &T, Node *x)     //左旋转：结点x原来的右子树y旋转成为x的父母
{
    if( x-> right != nil )  // x的右孩子不为空
    {
        Node *y=Right(x); //y是x的右孩子
        x->right=y->left;  //y的左孩子成为x的右孩子
        if(y->left != nil)  // 如果y的左孩子不为空，那么y的左孩子的父亲是x
        {
            y->left->parent=x;
        }
        y->parent=x->parent;  //x的父亲成为y的父亲
        if( x->parent == nil )  //如果x的父亲是空，那么y成为根节点
        {
            T=y;
        }
        else
        {
            if( x == Left(Parent(x)) )  //x的父亲的左孩子是x ——> x的父亲的左孩子是y
            {
                x->parent->left=y;
            }
            else // 同上
            {
                x->parent->right=y;
            }
        }
        y->left=x;
        x->parent=y;
    }
    else
    {
        printf("%s/n","Can't LeftRotate");
    }
}

void RightRotate(Tree &T, Node *x)   //右旋转：结点x原来的左子树y旋转成为x的父母
{
    if( x->left != nil )
    {
        Node *y=Left(x);
        x->left=y->right;
        if( y->right != nil )
        {
            y->right->parent=x;
        }
        y->parent=x->parent;
        if( x->parent == nil )
        {
            T=y;
        }
        else
        {
            if(x == Left(Parent(x)) )
            {
                x->parent->left=y;
            }
            else
            {
                x->parent->right=y;
            }
        }
        y->right=x;
        x->parent=y;
    }
    else
    {
        printf("%s/n","Can't RightRotate");
    }

}

void InsertFixup(Tree &T, Node *z)     // 插入结点z一定是红色的
{
    Node *y;
    while( Parent(z)->color == RED )  // 如果插入结点z的父亲是红色的
    {
        if( Parent(Parent(z))->left == Parent(z) )
        {
            y=Parent(Parent(z))->right;         // y是z的叔叔结点。定位到叔叔节点，叔叔节点是右孩子
            if( y->color == RED )       // 叔叔节点是红色的。
            {
                y->color=BLACK; //将叔叔涂黑
                z->parent->color=BLACK; //将父结点涂黑
                z->parent->parent->color=RED; //将祖父节点涂成红色
                z=z->parent->parent; //  当前节点的祖父节点成为新的当前节点
            }
            else
            {
                if( z == z->parent->right )    // 如果叔叔节点是黑色的，且z是右孩子
                {
                    z=z->parent;// 当前节点的父结点成为新的当前结点
                    LeftRotate(T, z);// 以新当前结点为支点进行左旋
                }
                else    // 如果叔叔节点是黑色的，且z是左孩子
                {
                    z->parent->color=BLACK;       // 将父结点涂黑
                    z->parent->parent->color=RED;    // 将祖父节点涂红
                    RightRotate(T,z->parent->parent);  // 以祖父节点为支点进行右旋
                }
            }
        }
        else               //与前一种情况对称，要插入的结点z是其父结点的右子树,注释略去
        {
            y=Parent(Parent(z))->left;  // y是z的叔叔结点。定位到叔叔节点，叔叔节点是左孩子
            if( y->color == RED)
            {
                z->parent->color=BLACK;
                y->color=BLACK;
                z->parent->parent->color=RED;
                z=z->parent->parent;
            }
            else
            {
                if( z == z->parent->left )
                {
                    z=z->parent;
                    RightRotate(T,z);
                }
                else
                {
                    z->parent->color=BLACK;
                    z->parent->parent->color=RED;
                    LeftRotate(T,z->parent->parent);
                }
            }
        }
    }
    T->color=BLACK;    // 将根节点涂成黑色
}
void Insert(Tree &T, int val)    //插入结点
{
    if(T == NULL)    //初始化工作：如果根尚不存在，那么new一个新结点给根，同时new一个新结点给nil
    {
        T=(Tree)malloc(sizeof(Node));
        nil=(Node*)malloc(sizeof(Node));
        nil->color=BLACK;            // nil（叶子节点）的颜色设置为黑
        T->left=nil;
        T->right=nil;
        T->parent=nil;
        T->value=val;
        T->color=BLACK;         // 根的颜色设置为黑色
    }
    else             // 如果此树已经不为空，那么从根开始，从上往下查找插入点
    {
        Node *x=T;          // x是当前结点，p是x的父结点
        Node *p=nil;
        while(x != nil)       //如果val小于当前结点的value值，则从左边下去，否则从右边下去
        {
            p=x;
            if(val < x->value )
            {
                x=x->left;
            }
            else if(val > x->value)
            {
                x=x->right;
            }
            else
            {
                printf("%s %d/n","重复的值，插入失败",val);   //如果查找到与val值相同的结点，则什么也不做，直接返回
                return;
            }

        }
        x=(Node*)malloc(sizeof(Node));
        x->color=RED;             //新插入的结点颜色设置为红色
        x->left=nil;
        x->right=nil;
        x->parent=p;
        x->value=val;
        if( val < p->value )
        {
            p->left = x;
        }
        else
        {
            p->right = x;
        }

        InsertFixup(T, x);         //插入后对树进行调整

    }
}

Node* Successor(Tree &T, Node *x)   //寻找结点x的中序后继
{
    if( x->right != nil )         //如果x的右子树不为空，那么为右子树中最左边的结点
    {
        Node *q=nil;
        Node *p=x->right; // p是当前结点，q是父结点
        while( p->left != nil )
        {
            q=p;
            p=p->left;
        }
        return q;
    }
    else                       //如果x的右子树为空，那么x的后继为x的所有祖先中为左子树的祖先
    {
        Node *y=x->parent;
        while(  y != nil && x == y->right ) // 如果x是右孩子（x是改侧中最大的一个），则需一直向上查询，直到改侧分支的左孩子都被遍历，画图可更直观了解
        {
            x=y;
            y=y->parent;
        }

        return y;
    }
}

void DeleteFixup(Tree &T, Node *x)    //删除黑色结点
{
    while( x != T && x->color == BLACK )  // 如果x是黑色。
    {
        if( x == x->parent->left )     // 如果x是左孩子
        {
            Node *w=x->parent->right;       // 设w是x的兄弟结点
            if( w->color == RED )         // 如果兄弟节点w的颜色为红色的话
            {
                w->color=BLACK;  // 把兄弟节点涂成黑色
                x->parent->color=RED; // 父结点涂成红色
                LeftRotate(T, x->parent); // 以当前结点的父结点为支点进行左旋
                w=x->parent->right;// x的兄弟节点发生变化，要重新定位
            }
            if( w->color == BLACK && w->left->color == BLACK && w->right->color == BLACK )   //  w的颜色为黑色，且w的左右孩子都为黑色
            {
                w->color=RED; //将兄弟节点w涂成红色
                x=x->parent; //将当前结点的父结点作为新的当前结点
            }
            if( w->color == BLACK && w->left->color == RED && w->right->color == BLACK )         //  w的颜色为黑色，且w的左孩子为红色，w的右孩子为黑色。
            {
                w->color=RED; // 把兄弟节点涂成红色
                w->left->color=BLACK; // 把兄弟节点的左子节点涂黑
                RightRotate(T, w);// 以兄弟节点为支点做右旋操作
                w=x->parent->right;// x的兄弟节点发生变化，要重新定位
            }
            if( w->color == BLACK && w->right->color == RED)    //  w是黑色的，且w的右孩子是红色，左孩子是任意颜色
            {
                w->color=x->parent->color;  //  把兄弟结点涂成和父结点相同的颜色
                x->parent->color=BLACK; //   将父亲结点染成黑色
                w->right->color=BLACK;//    将兄弟结点的右孩子染成黑色
                LeftRotate(T , x->parent);  // 以当前结点的父结点为支点进行左旋
                w=x->parent->right;// x的兄弟节点发生变化，要重新定位
            }
            x=T; //当前节点指向根节点
        }
        else           //对称情况，如果x是右孩子
        {
            Node *w=x->parent->left;
            if( w->color == RED )
            {
                w->color=BLACK;
                x->parent->color=RED;
                RightRotate(T, x->parent);
                w=x->parent->left;
            }
            if( w->color == BLACK && w->left->color == BLACK && w->right->color == BLACK )
            {
                w->color=RED;
                x=x->parent;
            }
            if( w->color == BLACK && w->left->color == BLACK && w->right->color == RED )
            {
                w->color=RED;
                w->right->color=BLACK;
                LeftRotate(T, w);
                w=x->parent->left;
            }
            if( w->color == BLACK && w->left->color == RED)
            {
                w->color=x->parent->color;
                x->parent->color=BLACK;
                w->left->color=BLACK;
                RightRotate(T , x->parent);
            }

            x=T;

        }
    }
    x->color=BLACK; // 根节点设置为黑色
}

void Delete(Tree &T, Node *z)     //在红黑树T中删除结点z
{
    Node *y;   //y指向将要被删除的结点
    Node *x;    //x指向将要被删除的结点的唯一儿子
    if( z->left == nil || z->right == nil )    //如果z有一个子树为空的话，那么将直接删除z,即y指向z
    {
        y=z;
    }
    else
    {
        y=Successor(T, z);     //如果z的左右子树皆不为空的话，则寻找z的中序后继y，
    }                          //用其值代替z的值，然后将y删除 ( 注意: y肯定是没有左子树的 )

    if( y->left != nil )         //如果y的左子树不为空，则x指向y的左子树
    {
        x=y->left;
    }
    else
    {
        x=y->right;
    }
    x->parent=y->parent;    //将原来y的父母设为x的父母，y即将被删除
    if( y->parent == nil )  //如果y的父亲为空，那么x成为新的根节点
    {
        T=x;
    }
    else                    // y的父亲的左孩子或右孩子变为x
    {
        if( y == y->parent->left )
        {
            y->parent->left=x;
        }
        else
        {
            y->parent->right=x;
        }
    }
    if( y != z )   //如果被删除的结点y不是原来将要删除的结点z，
    {              //即只是用y的值来代替z的值，然后变相删除y以达到删除z的效果
        z->value=y->value;
    }
    if( y->color == BLACK )    //如果被删除的结点y的颜色为黑色，要重新进行平衡
    {
        DeleteFixup(T, x);
    }
}
Node* Search(Tree T, int val)
{
    if( T != nil )
    {
        if( val < T->value )
        {
            Search(T->left, val);
        }
        else if ( val > T->value )
        {
            Search(T->right,val);
        }
        else
        {
            return T;
        }
    }
}

void MidTranverse(Tree T) // 中序遍历
{
    if( T != NULL && T != nil )
    {
        MidTranverse(T->left);
        printf("%d ",T->value);
        MidTranverse(T->right);
    }

}
int main()
{
    Tree t=NULL;
    Insert(t,10);
    Insert(t,85);
    Insert(t,15);
    Insert(t,70);
    Insert(t,20);
    Insert(t,60);
    Insert(t,30);
    Insert(t,50);
    Insert(t,65);
    Insert(t,80);
    Insert(t,90);
    Insert(t,40);
    Insert(t,5);
    Insert(t,55);
    Delete(t,Search(t,30));
    Delete(t,Search(t,65));
    MidTranverse(t);
    return 0;
}
