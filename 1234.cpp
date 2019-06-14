#include <iostream>
using namespace std;
struct node {
    int a,b;
    int val;
    node(int x,int y,int z):a(x),b(y),val(z) {}
    node() {}
};
void quicksort(node* array[],int begin,int end) {
    if (begin < end) {
        int p = begin - 1;
        int j = begin;
        int x = array[end]->val;
        for (;j < end;++j)
        {
            if (array[j]->val <= x) {
                p++;
                swap(array[j],array[p]);
            }
        }
        p++;
        swap(array[p],array[end]);

        quicksort(array,begin,p-1);
        quicksort(array,p+1,end);
        
    }
}

class DisjointSets {
    private:
        int* parent;
        int num;
    public:
        DisjointSets(int n):num(n),parent(new int[n+1]){
            for (int i = 1;i <= n;++i) parent[i] = -1;
        }
        int find(int x) {
            if (parent[x] < 0) return x;
            return parent[x] = find(parent[x]);
        }
        void union_(int x,int y) {
            if (find(x) == find(y)) return;
            parent[find(x)] = find(y);
        }
};

int main() {
    int n,m,a,b,c;
    node** array;
    cin>>n>>m;
    array = new node* [m+1];
    for (int i = 1;i <= m;++i) {
        scanf("%d %d %d",&a,&b,&c);
        array[i] = new node(a,b,c);
    }
    DisjointSets D(n);
    quicksort(array,1,m);
    int k = 0,sum = 0;
    for (int i = 1;i <= m;++i) {
        if (D.find(array[i]->a) != D.find(array[i]->b)) {
            D.union_(array[i]->a,array[i]->b);
            sum += array[i]->val;
            k++;
        }
        if (k == n-1) break;
    }
    cout<<sum;
}