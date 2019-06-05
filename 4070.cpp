#include <iostream>
#include <cstring>
using namespace std;
void delete_ch(char *&str,char ch) {
    int j = 0,i = 0;
    char *tmp = new char[35];

    for (int j = 0;j < strlen(str);++j) {
        if (str[j] != ch) {tmp[i] = str[j];i++;}
    }
    i++;
    tmp[i] = '\0';
    str = tmp; 
}
void quicksort(char* array[],int begin,int end) {
    if (begin < end) {
        int p = begin - 1;
        int j = begin;
        char* x = array[end];
        for (;j < end;++j)
        {
            if (strcmp(array[j],x) >= 0) {
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
int main() {
    char ch;
    int i = 0,m = 0;
    cin>>ch;
    char *array[31];
    char cmd[35];
    while (true) {
        array[i] = new char[35];
        cin.getline(array[i],35);
        if (*array[i] == '@') break;
        delete_ch(array[i],ch);
        i++;
    }
    m = i;
    int j = 0;
    quicksort(array,0,m-1);
    for (;j < m-1;++j) {
        
        cout<<array[j]<<endl;
        
    }
    cout<<array[j];

}