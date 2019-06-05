#include <iostream>
using namespace std;

struct Node {
    int val;
    int num;
    
    Node(int val_,int num_ = 0) : val(val_) ,num(num_) {}
    Node() : val(0),num(0) {}
};
class hashTable {
    private:
        Node* array;
    public:
        hashTable():array(new Node[4000000]) {}
        void insert(int x) {
            int m = x + 2000000; 
            array[m].num++;
        }
        int find(int x) {
            int m = x + 2000000; 
            
            return array[m].num;
        }
};

int main() {
    int N;
    int arraya[500];
    int arrayb[500];
    int arrayc[500];
    int arrayd[500];
    hashTable T;
    int a,b,c,d;
    cin>>N;
    for (int m = 0;m < N;++m) {
        cin>>a>>b>>c>>d;
        arraya[m] = a;
        arrayb[m] = b;
        arrayc[m] = c;
        arrayd[m] = d;
        
    }
    int ans = 0;
    for (int i = 0;i < N;++i)
        for (int q = 0;q < N;++q) {
            T.insert(arraya[i] + arrayb[q]);
        }
    for (int p = 0;p < N;++p) {
        for (int j = 0;j < N;++j) {
            int x = arrayc[p] + arrayd[j];
            ans += T.find(-x);
        }
    }
    cout<<ans;
}