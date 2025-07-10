#include <stdio.h>

void swap(int* a, int* b){
    int buffer = *a;
    *a = *b;
    *b = buffer;
}

int partition(int arr[], int begin, int end){
    int pivot = arr[end];
    int i = begin-1;
    for(int j=begin; j<end; j++){
        if(arr[j]<=pivot){
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i+1], &arr[end]);
    return i+1;
}

void qsort(int arr[], int begin, int end){
    int stack[end-begin+1];
    int stackSize = -1;

    stack[++stackSize] = begin;
    stack[++stackSize] = end;

    while(stackSize>0){
        end = stack[stackSize--];
        begin = stack[stackSize--];

        int pivot = partition(arr, begin, end);

        if(pivot-1 > begin){
            stack[++stackSize] = begin;
            stack[++stackSize] = pivot-1;
        }else if(pivot+1 < end){
            stack[++stackSize] = pivot+1;
            stack[++stackSize] = end;
        }
    }
}

int main(){
    int n;
    scanf("%d", &n);
    int arr[n];
    for(int i=0; i<n; i++) scanf("%d", &arr[i]);
    qsort(arr, 0, n-1);
    for(int i=0; i<n; i++) printf("%d ", arr[i]);
    printf("\n");
    return 0;
}