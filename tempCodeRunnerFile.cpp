#include <iostream>
using namespace std;
class stack
{
    public:
        char *data;
        int ptr;
        stack(int cap):data(new char[cap]),ptr(0){}
        ~stack() { delete [] data; }
        void push(const char& x) { data[ptr++] = x; }
        char pop() { return data[--ptr]; }
        char top() { return data[ptr - 1]; }
        bool empty() { return ptr == 0; }
};

int main()
{
    stack d(1000000),a(1000000),temp(1000000);
    char _c;
    int N,oj;
    cin>>N;
    while(N--) {
        cin>>oj;
        if (oj==1) {
            cin>>_c;
            switch (_c)
            {
                case '(':case '[':case '{':
                   a.push(_c); break;
                case ')':
                   if (!a.empty() && (a.top() == '(') )  temp.push(a.pop()); else a.push(')'); 
                   break;
                case ']':
                   if (!a.empty() && (a.top() == '[') )  temp.push(a.pop()); else a.push(']'); 
                   break;
                case '}':
                   if (!a.empty() && (a.top() == '{') )  temp.push(a.pop()); else a.push('}'); 
                   break;
            }
            d.push(_c);
        }
        if (oj==2) {
            if ( a.top() == d.pop() ) a.pop();
            else a.push( temp.pop() );
        }
        if (oj==3) {
            if (!d.empty()) cout<<d.top()<<endl;
        }
        if (oj==4) {
            if (a.empty()) cout<<"YES"<<endl;
            else cout<<"NO"<<endl;
        }
    }
    return 0;
}