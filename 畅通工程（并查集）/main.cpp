#include <iostream>

using namespace std;
int pre[1000];
int find(int x)
{
    int r=x;
    while(r!=pre[r])//�ҵ����ڵ�
    r=pre[r];
    int i=x;
    int j;
    while(i!=r)//·��ѹ��
    {
        j=pre[i];
        pre[i]=r;
        i=j;
    }
    return r;
}
int join(int x,int y,int total)
{
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy)//�Ը��ڵ������ͨ
    {
        pre[fx]=fy;
        total--;
    }
    return total;
}
int main()
{
    int n;
    int m;
    cin>>n;
    while(n!=0)
    {
        int total=n-1;//�տ�ʼ��ʱ����n��������ôҪ��n-1��·���ܰ�����������
        for(int i=1;i<=n;i++)
        pre[i]=i;                 //ÿ���㻥��������Գ�һ�����ϣ���1��ŵ�n
        cin>>m;
        while(m--)
        {
            int x,y;
            cin>>x;
            cin>>y;
            total=join(x,y,total);
        }
        cout<<total<<endl;
        cin>>n;
    }
}
