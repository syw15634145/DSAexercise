#include <iostream>
#include <queue>
 
#define MaxN 100000
using namespace std;
 
int n;
int connect[MaxN][100]={0};
int len_c[MaxN]={0};
int seg[MaxN][100]={0};
bool seg_ed[MaxN][100] = {false};
bool caled[MaxN] = {0};
 
struct Component
{
    int source;
    int to;
    int count;
};
 
 
void init(){
    cin>>n;
    //记录连通情况 O(n)
    for (int i = 0; i < n-1; ++i)
    {
        int x,y;
        cin>>x>>y;
        connect[x][len_c[x]++] = y;
        connect[y][len_c[y]++] = x;
    }
    //初始化所有只有一个分支的点的分割情况
//    for (int i = 1; i <= n; ++i) if(len_c[i]==1)
//    {
//        seg[i][0] = n-1;//唯一的一个分支有n-1个点
//        caled[i] = true;//计算过
//    }
    // //初始化所有 有两个分支 且 至少有一个分支只有一个元素的节点的分割情况
    // for (int i = 1; i <= n; ++i) if(len_c[i]==2)
    // {
    //     if(len_c[connect[i][0]]==1){ //0号分支是边界点
    //         seg[i][0] = 1;
    //         seg[i][1] = n-2;
    //     }
    //     if(len_c[connect[i][1]]==1){ //1号分支是边界点
    //         seg[i][1] = 1;
    //         seg[i][0] = n-2;
    //     }
    //     caled[i] = true; //计算过
    // }
    // //
    
}
 
 
 
//计算与s相连的 以x开头的那一个分支有多少个
int getComponent(int s, int x){
    int len = len_c[x];//len是该分支的子分支的个数
    int res = 1;//该分支的总数里肯定有x本身    所以初始化为1
    if(caled[x]){//如果这个分支是计算过的 就直接返回结果
        for (int i = 0; i < len; ++i)
            if(connect[x][i]!=s) //排除和s接通的那个子分支
                res += seg[x][i];
    }else{//说明x的seg情况没有初始化过
        int tmp = 0;
        for (int i = 0; i < len; ++i)
        {
            seg[x][i] = getComponent(x,connect[x][i]);
            tmp += seg[x][i];
            if(connect[x][i]!=s)
                res += seg[x][i];
        }
        // seg[x][len-1] = n-1-tmp;
        // if(connect[x][len-1]!=s)
        //         res += seg[x][len-1];
        caled[x] = true;
    }
    return res;
}
 
// void VisibleBuild(){
//     stack<int> s;
//     s.push(1);
//     while(!s.empty()){
 
//     }
// }
 
 
//计算每个点的每个分支的节点个数
void Build(){
    
    for (int i = 1; i <= n; ++i) if(!caled[i]) //用caled来减少重复计算
    {
        int len = len_c[i]; //len是当前节点的分支的数目
        int tmp = 0; //记录除了最后一个分支的节点数目和 因为最后一个节点可以用补集来算
        for (int j = 0; j < len-1; ++j){
            //递归计算 i的第j个分支的节点数目
            seg[i][j] = getComponent(i,connect[i][j]);
            tmp += seg[i][j];
        }
        seg[i][len-1] = n-1-tmp;//补集的思想 最后一个分治的节点数目就是n-1-前几个分支的节点总数
        caled[i] = true;
    }
}
 
 
void Output(){
    //判断并输出 O(n)
    for (int i = 1; i <= n; ++i)
    {
        bool ok = true;//标志i点是否符合条件
        for (int j = 0; j < len_c[i]; ++j) if(seg[i][j]>n/2)
        {//如果存在某一个分支的节点数目>n/2
            ok = false;
            break;
        }
        if(ok)
            cout<<i<<endl;
    }
    return;
}
 
 
void NewBuild(){
    //以所有的边界点为切入点进入
    for (int i = 1; i <= n; ++i) if(len_c[i]==1)
    {
        //printf("new start %d",i);
        queue<Component> q;
        Component start;
        start.source = i;
        start.to = connect[i][0];
        start.count = 1;
        q.push(start);//把它紧连着的那个分支的根压入
      //  bool wrong = false;
        while(!q.empty()){
            Component todo =  q.front();
            q.pop();
            int newStart = todo.to;
            for (int j = 0; j < len_c[newStart]; ++j)
            {
                if(connect[newStart][j]==todo.source){
                    seg[newStart][j] += todo.count;
//                    printf("-----\n%d : from %d :%d\t from %d :%d\tfrom %d :%d\n",newStart,connect[newStart][0],seg[newStart][0],connect[newStart][1],seg[newStart][1],connect[newStart][2],seg[newStart][2]);
                }else{
                    Component next;
                    next.source = newStart;
                    next.to = connect[newStart][j];
                    int cur = 0;
                    for(;cur<len_c[next.to];++cur) if(connect[next.to][cur]==newStart)
                        break;
                    next.count = seg[next.to][cur]==0 ? todo.count + 1 : todo.count;
                    q.push(next);
                }
            }
//            printf("segment states:\n");
//            for (int i = 1; i <= n; ++i)
//            {
//                printf("%d : from %d :%d\t from %d :%d\tfrom %d :%d\n",i,connect[i][0],seg[i][0],connect[i][1],seg[i][1],connect[i][2],seg[i][2]);
//            }
//            
//            wrong = false;
        }
    }
}
 
int main(int argc, char const *argv[])
{
    init();      //输入和一些边界情况的初始化
    //Build();  //计算每个点的每个分支的节点个数
    NewBuild();
    
    Output(); //遍历每个点判断条件并输出结果
    
    // printf("connect states:\n");
    // for (int i = 1; i <= n; ++i)
    // {
    //     printf("%d : len:%d c0:%d\tc1:%d\tc2:%d\n",i,len_c[i],connect[i][0],connect[i][1],connect[i][2]);
    // }
    // printf("segment states:\n");
    // for (int i = 1; i <= n; ++i)
    // {
    //     printf("%d : seg0:%d\tseg1:%d\tseg2:%d\n",i,seg[i][0],seg[i][1],seg[i][2]);
    // }
    return 0;
}