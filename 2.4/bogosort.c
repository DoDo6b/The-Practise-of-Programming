#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void swap(int* a, int* b){
    int buffer = *a;
    *a = *b;
    *b = buffer;
}

void shuffle(int arr[], int begin, int end){
    srand(time(NULL));
    int randIndex;
    for(int i=begin; i<end; i++){
        randIndex = begin + i + rand() % (end-i-begin);
        swap(&arr[i], &arr[randIndex]);
    }
}

unsigned char is_unsorted(int arr[], int begin, int end){
    for(int i=begin+1; i<end; i++){
        if(arr[i-1]>arr[i]) return 1;
    }
    return 0;
}

void bogosort(int arr[], int begin, int end){
    if(begin==end) return;
    while(is_unsorted(arr, begin, end)) shuffle(arr, begin, end);
}

int main(){
    int n;
    scanf("%d", &n);
    int arr[n];
    for(int i=0; i<n; i++) scanf("%d", &arr[i]);
    bogosort(arr, 0, n);
    for(int i=0; i<n; i++) printf("%d ", arr[i]);
    printf("\n");
    return 0;
}