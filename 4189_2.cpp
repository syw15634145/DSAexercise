#include <iostream>
using namespace std;
int N;
struct node{
    int val;
    int sign;
    node* next;
    node(int val_,node* next_ = NULL) : val(val_),next(next_),sign(1) {}
    node():val(0),next(NULL),sign(1) {}
};
class ADJ {
    private:
        node* list;
        int num;
        int* child_max;
        int* child_sum;
    public:
        ADJ(int n_):num(n_),list(new node[n_+1]),child_max(new int[n_+1]),child_sum(new int[n_+1]) {}
        void create() {
            int a,b;
            for (int i = 0;i < num-1;++i) {
                scanf("%d %d",&a,&b);
                list[a].next = new node(b,list[a].next);
                list[b].next = new node(a,list[b].next);
            }
        }
        void find_num(node* t,bool visited[]) {//计算以t->val节点为根的树数目大小是多少
            int max = 0;
            visited[t->val] = true;
            node* temp = list[t->val].next;
            while (temp) {
                if (!visited[temp->val]) {
                        find_num(temp,visited);
                        if (temp->sign > max) max = temp->sign;
                        t->sign += temp->sign;
                    }
                    temp = temp->next;
                }
            child_sum[t->val] = t->sign;
            child_max[t->val] = max;
            return;
        }
        void count(int i) {//计算去掉i节点后剩下连接块的最大规模
            bool visited[num+1];
            for (int i = 0;i <= num;++i) visited[i] = false;
            int max = 0;
            node* t = list[i].next;
            visited[i] = true;
            child_sum[i] = 1;
            while (t) {
                find_num(t,visited);
                if (t->sign > max) max = t->sign;
                child_sum[i] += t->sign;
                //cout<<t->val<<" "<<t->sign<<endl;
                t = t->next;
            }
            child_max[i] = max;
        }
        void print() {
            for (int i = 1;i <= num;++i) {
                cout<<child_sum[i]<<" "<<child_max[i]<<endl;
            }
        }
        void printans() {
            for (int i = 1;i <= num;++i) {
                if (!((child_max[i] > num/2) || (child_sum[i] < num/2)))
                    printf("%d\n",i);
            }
        }
};
int main(){
    int x,y;
    cin>>N;
    ADJ A(N);
    A.create();
    A.count(1);
    //A.print();
    A.printans();
    return 0;
}