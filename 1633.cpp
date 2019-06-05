#include <iostream>
using namespace std;

struct Node {
    int val;
    Node* next;
    Node(int x,Node* next_ = NULL) : val(x),next(next_) {}
};
int infected_[30000];
Node* head[30000];
Node* tail[30000];

int find_infected(Node* head_) {
    int sum = 1;
    Node* t = head_;
    while (t != NULL) {
        if (infected_[t->val] == 0) {
            infected_[t->val] = 1;                                       
            sum = sum + find_infected(head[t->val]);
        }
        t = t->next;
    }
    return sum;
}
int main() {
    int n,m,num;
    cin>>n>>m;
    
    for(int i = 0;i < n;++i) {infected_[i] = 0;head[i] = tail[i] = NULL;}
    
    for (int i = 0;i < m;++i) {
        cin >> num;
        int array[num];
        for (int j = 0;j < num;++j) cin>>array[j];
        for (int k = 0;k < num;++k)  
            for (int q = 0;q < num;++q) {
                if (array[q] != array[k]) {
                    if (tail[array[k]] == NULL) {
                    tail[array[k]] = head[array[k]] = new Node(array[q]);
                    }
                    else {
                        Node* temp = tail[array[k]];
                        tail[array[k]] = new Node(array[q]);
                        temp->next = tail[array[k]];
                    }
                }
            }
        
    }
    infected_[0] = 1;
    cout<<find_infected(head[0]);
}