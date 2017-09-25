#include <iostream>

using namespace std;
int pre[1000];
int find(int x)
{
    int r=x;
    while(r!=pre[r])//找到根节点
    r=pre[r];
    int i=x;
    int j;
    while(i!=r)//路径压缩
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
    if(fx!=fy)//对根节点进行连通
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
        int total=n-1;//刚开始的时候，有n个城镇，那么要修n-1条路才能把它们连起来
        for(int i=1;i<=n;i++)
        pre[i]=i;                 //每个点互相独立，自成一个集合，从1编号到n
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
