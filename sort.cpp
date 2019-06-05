#include <iostream>
using namespace std;

void quicksort(int array[],int begin,int end) {
    if (begin < end) {
        int p = begin - 1;
        int j = begin;
        int x = array[end];
        for (;j < end;++j)
        {
            if (array[j] >= x) {
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


void mergesort(int arr[],int begin,int end) {
    if (begin < end) {
        int q = (begin + end)/2;
        mergesort(arr,begin,q);
        mergesort(arr,q+1,end);
        //merge(arr,begin,q,end)

        int left[q-begin+2];
        left[q-begin+1] = 1e9;
        int right[end-q+1];
        right[end-q] = 1e9;
        for (int f = 0;f < q-begin+1;++f) {left[f] = arr[begin+f];}
        for (int t = 0;t < end-q;++t) {right[t] = arr[q+1+t];}

        
        int i = 0,j = 0;
        for (int k = begin;k < end + 1;++k) {
            if (left[i] < right[j]) {
                arr[k] = left[i];
                i++;
            }
            else {
                arr[k] = right[j];
                j++;
            }
        }
    }
}



void coutingsort(int arrayA[],int arrayB[],int A_length,int k) {
    int arrayC[k+1];
    for (int i = 0;i < k+1;++i) {
        arrayC[i] = 0;
    }
    for (int j = 0;j < A_length;++j) {
        arrayC[arrayA[j]]++;
    }
    for (int i = 1;i < k+1;++i) {
        arrayC[i] = arrayC[i] + arrayC[i-1];
    }
    for (int j = A_length - 1;j >= 0;--j) {
        arrayB[arrayC[arrayA[j]]] = arrayA[j];
        arrayC[arrayA[j]]--;
    }


}
int arr[100];
int ans[100];
int main()
{
    int N;
    scanf("%d",&N);
    int k;
    for (int i = 0;i < N;++i) {
        scanf("%d",&k);
        arr[i] = k;
    }
    //quicksort(arr,0,N-1);
    coutingsort(arr,ans,N,1000);
    for (int i = 1;i < N+1;++i) {
        printf("%d ",ans[i]);
    }
    
    
}