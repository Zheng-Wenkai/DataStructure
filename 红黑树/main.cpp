/*
����1. �ڵ��Ǻ�ɫ���ɫ
����2. ���Ǻ�ɫ
����3. ÿ����ɫ�ڵ�������ӽڵ㶼�Ǻ�ɫ (��ÿ��Ҷ�ӵ���������·���ϲ��������������ĺ�ɫ�ڵ�)
����4. ����һ�ڵ㵽��ÿ��Ҷ�ӵ�����·����������ͬ��Ŀ�ĺ�ɫ�ڵ�
*/

#include <stdio.h>
#include <stdlib.h>
typedef enum Color   // ʹ��ö�����ͣ��������������ɫ
{
    RED = 0,
    BLACK = 1
}Color;

typedef struct Node     //���������������
{
    struct Node *parent;
    struct Node *left;
    struct Node *right;
    int value;
    Color color;
}Node, *Tree;

Node *nil=NULL;           //Ϊ�˱������۽��ı߽����������һ��nil���������е�NULL
Node* Parent(Node *z)     //����ĳ���ĸ�ĸ
{
    return z->parent;
}
Node* Left(Node *z)       //����������
{
    return z->left;
}
Node *Right(Node *z)      //����������
{
    return z->right;
}
void LeftRotate(Tree &T, Node *x)     //����ת�����xԭ����������y��ת��Ϊx�ĸ�ĸ
{
    if( x-> right != nil )  // x���Һ��Ӳ�Ϊ��
    {
        Node *y=Right(x); //y��x���Һ���
        x->right=y->left;  //y�����ӳ�Ϊx���Һ���
        if(y->left != nil)  // ���y�����Ӳ�Ϊ�գ���ôy�����ӵĸ�����x
        {
            y->left->parent=x;
        }
        y->parent=x->parent;  //x�ĸ��׳�Ϊy�ĸ���
        if( x->parent == nil )  //���x�ĸ����ǿգ���ôy��Ϊ���ڵ�
        {
            T=y;
        }
        else
        {
            if( x == Left(Parent(x)) )  //x�ĸ��׵�������x ����> x�ĸ��׵�������y
            {
                x->parent->left=y;
            }
            else // ͬ��
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

void RightRotate(Tree &T, Node *x)   //����ת�����xԭ����������y��ת��Ϊx�ĸ�ĸ
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

void InsertFixup(Tree &T, Node *z)     // ������zһ���Ǻ�ɫ��
{
    Node *y;
    while( Parent(z)->color == RED )  // ���������z�ĸ����Ǻ�ɫ��
    {
        if( Parent(Parent(z))->left == Parent(z) )
        {
            y=Parent(Parent(z))->right;         // y��z�������㡣��λ������ڵ㣬����ڵ����Һ���
            if( y->color == RED )       // ����ڵ��Ǻ�ɫ�ġ�
            {
                y->color=BLACK; //������Ϳ��
                z->parent->color=BLACK; //�������Ϳ��
                z->parent->parent->color=RED; //���游�ڵ�Ϳ�ɺ�ɫ
                z=z->parent->parent; //  ��ǰ�ڵ���游�ڵ��Ϊ�µĵ�ǰ�ڵ�
            }
            else
            {
                if( z == z->parent->right )    // �������ڵ��Ǻ�ɫ�ģ���z���Һ���
                {
                    z=z->parent;// ��ǰ�ڵ�ĸ�����Ϊ�µĵ�ǰ���
                    LeftRotate(T, z);// ���µ�ǰ���Ϊ֧���������
                }
                else    // �������ڵ��Ǻ�ɫ�ģ���z������
                {
                    z->parent->color=BLACK;       // �������Ϳ��
                    z->parent->parent->color=RED;    // ���游�ڵ�Ϳ��
                    RightRotate(T,z->parent->parent);  // ���游�ڵ�Ϊ֧���������
                }
            }
        }
        else               //��ǰһ������Գƣ�Ҫ����Ľ��z���丸����������,ע����ȥ
        {
            y=Parent(Parent(z))->left;  // y��z�������㡣��λ������ڵ㣬����ڵ�������
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
    T->color=BLACK;    // �����ڵ�Ϳ�ɺ�ɫ
}
void Insert(Tree &T, int val)    //������
{
    if(T == NULL)    //��ʼ��������������в����ڣ���ônewһ���½�������ͬʱnewһ���½���nil
    {
        T=(Tree)malloc(sizeof(Node));
        nil=(Node*)malloc(sizeof(Node));
        nil->color=BLACK;            // nil��Ҷ�ӽڵ㣩����ɫ����Ϊ��
        T->left=nil;
        T->right=nil;
        T->parent=nil;
        T->value=val;
        T->color=BLACK;         // ������ɫ����Ϊ��ɫ
    }
    else             // ��������Ѿ���Ϊ�գ���ô�Ӹ���ʼ���������²��Ҳ����
    {
        Node *x=T;          // x�ǵ�ǰ��㣬p��x�ĸ����
        Node *p=nil;
        while(x != nil)       //���valС�ڵ�ǰ����valueֵ����������ȥ��������ұ���ȥ
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
                printf("%s %d/n","�ظ���ֵ������ʧ��",val);   //������ҵ���valֵ��ͬ�Ľ�㣬��ʲôҲ������ֱ�ӷ���
                return;
            }

        }
        x=(Node*)malloc(sizeof(Node));
        x->color=RED;             //�²���Ľ����ɫ����Ϊ��ɫ
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

        InsertFixup(T, x);         //�����������е���

    }
}

Node* Successor(Tree &T, Node *x)   //Ѱ�ҽ��x��������
{
    if( x->right != nil )         //���x����������Ϊ�գ���ôΪ������������ߵĽ��
    {
        Node *q=nil;
        Node *p=x->right; // p�ǵ�ǰ��㣬q�Ǹ����
        while( p->left != nil )
        {
            q=p;
            p=p->left;
        }
        return q;
    }
    else                       //���x��������Ϊ�գ���ôx�ĺ��Ϊx������������Ϊ������������
    {
        Node *y=x->parent;
        while(  y != nil && x == y->right ) // ���x���Һ��ӣ�����һֱ���ϲ�ѯ����ͼ�ɸ�ֱ���˽�
        {
            x=y;
            y=y->parent;
        }

        return y;
    }
}

void DeleteFixup(Tree &T, Node *x)    //ɾ����ɫ���
{
    while( x != T && x->color == BLACK )  // ���x�Ǻ�ɫ��
    {
        if( x == x->parent->left )     // ���x������
        {
            Node *w=x->parent->right;       // ��w��x���ֵܽ��
            if( w->color == RED )         // ����ֵܽڵ�w����ɫΪ��ɫ�Ļ�
            {
                w->color=BLACK;  // ���ֵܽڵ�Ϳ�ɺ�ɫ
                x->parent->color=RED; // �����Ϳ�ɺ�ɫ
                LeftRotate(T, x->parent); // �Ե�ǰ���ĸ����Ϊ֧���������
                w=x->parent->right;// x���ֵܽڵ㷢���仯��Ҫ���¶�λ
            }
            if( w->color == BLACK && w->left->color == BLACK && w->right->color == BLACK )   //  w����ɫΪ��ɫ����w�����Һ��Ӷ�Ϊ��ɫ
            {
                w->color=RED; //���ֵܽڵ�wͿ�ɺ�ɫ
                x=x->parent; //����ǰ���ĸ������Ϊ�µĵ�ǰ���
            }
            if( w->color == BLACK && w->left->color == RED && w->right->color == BLACK )         //  w����ɫΪ��ɫ����w������Ϊ��ɫ��w���Һ���Ϊ��ɫ��
            {
                w->color=RED; // ���ֵܽڵ�Ϳ�ɺ�ɫ
                w->left->color=BLACK; // ���ֵܽڵ�����ӽڵ�Ϳ��
                RightRotate(T, w);// ���ֵܽڵ�Ϊ֧������������
                w=x->parent->right;// x���ֵܽڵ㷢���仯��Ҫ���¶�λ
            }
            if( w->color == BLACK && w->right->color == RED)    //  w�Ǻ�ɫ�ģ���w���Һ����Ǻ�ɫ��������������ɫ
            {
                w->color=x->parent->color;  //  ���ֵܽ��Ϳ�ɺ͸������ͬ����ɫ
                x->parent->color=BLACK; //   �����׽��Ⱦ�ɺ�ɫ
                w->right->color=BLACK;//    ���ֵܽ����Һ���Ⱦ�ɺ�ɫ
                LeftRotate(T , x->parent);  // �Ե�ǰ���ĸ����Ϊ֧���������
                w=x->parent->right;// x���ֵܽڵ㷢���仯��Ҫ���¶�λ
            }
            x=T; //��ǰ�ڵ�ָ����ڵ�
        }
        else           //�Գ���������x���Һ���
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
    x->color=BLACK; // ���ڵ�����Ϊ��ɫ
}

void Delete(Tree &T, Node *z)     //�ں����T��ɾ�����z
{
    Node *y;   //yָ��Ҫ��ɾ���Ľ��
    Node *x;    //xָ��Ҫ��ɾ���Ľ���Ψһ����
    if( z->left == nil || z->right == nil )    //���z��һ������Ϊ�յĻ�����ô��ֱ��ɾ��z,��yָ��z
    {
        y=z;
    }
    else
    {
        y=Successor(T, z);     //���z�����������Բ�Ϊ�յĻ�����Ѱ��z��������y��
    }                          //����ֵ����z��ֵ��Ȼ��yɾ�� ( ע��: y�϶���û���������� )

    if( y->left != nil )         //���y����������Ϊ�գ���xָ��y��������
    {
        x=y->left;
    }
    else
    {
        x=y->right;
    }
    x->parent=y->parent;    //��ԭ��y�ĸ�ĸ��Ϊx�ĸ�ĸ��y������ɾ��
    if( y->parent == nil )  //���y�ĸ���Ϊ�գ���ôx��Ϊ�µĸ��ڵ�
    {
        T=x;
    }
    else                    // y�ĸ��׵����ӻ��Һ��ӱ�Ϊx
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
    if( y != z )   //�����ɾ���Ľ��y����ԭ����Ҫɾ���Ľ��z��
    {              //��ֻ����y��ֵ������z��ֵ��Ȼ�����ɾ��y�Դﵽɾ��z��Ч��
        z->value=y->value;
    }
    if( y->color == BLACK )    //�����ɾ���Ľ��y����ɫΪ��ɫ��Ҫ���½���ƽ��
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

void MidTranverse(Tree T) // �������
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
