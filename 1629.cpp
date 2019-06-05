#include <iostream>
using namespace std;

struct Node {
    int val,size;
    Node* next;
    Node(int x,int size_ = 1,Node* next_ = NULL) : val(x),size(size_),next(next_) {}
};


Node* head[10000];
Node* tail[10000];

void tree_node_num(Node* root,int visited_[]) {
    
    if (root->size > 1) return;
    Node* temp = head[root->val];
    while (temp) {
        if (visited_[temp->val] == 0) {
            visited_[temp->val] = 1;
            tree_node_num(temp,visited_);
            root->size += temp->size;
        }
        temp = temp->next;
    }
    return ;

}
int maxnode(int x) {
    int maxnode_ = 0;
    Node* t = head[x];
     
    while (t) {
        int visited_[10000] = {0};
        visited_[x] = 1;
        visited_[t->val] = 1;
        tree_node_num(t,visited_);
        if (t->size > maxnode_) maxnode_ = t->size; 
        t = t->next;
        
    }
    return maxnode_;
}
int main() {
    int N,a,b;
    cin>>N;
    for(int i = 0;i < N;++i) {head[i] = tail[i] = NULL;}

    for (int i = 0;i < N-1;++i) {
        cin>>a>>b;
        if (tail[a] == NULL) {
            head[a] = tail[a] = new Node(b);
        }
        else {
            Node* temp = tail[a];
            tail[a] = new Node(b);
            temp->next = tail[a];
        }

        if (tail[b] == NULL) {
            head[b] = tail[b] = new Node(a);
        }
        else {
            Node* temp = tail[b];
            tail[b] = new Node(a);
            temp->next = tail[b];
        }
    }
    int MAX = 10000,shot;
    for (int i = 1;i < N;++i) {
        int n = maxnode(i);
        if (n < MAX) {shot = i;MAX = n;}
    }
    cout<<shot<<" "<<MAX;
    //cout<<maxnode(0);
    

}