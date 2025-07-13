#include "stdio.h"
#include "stdlib.h"


enum{
    VECTORINITSIZE = 1,
    VECTORGROWCOEFF = 2,
};

typedef struct{
    int data;
    unsigned char is_used;
}Cell;

typedef struct{
    int length;
    int size;
    Cell* start;
}Vector;


int find(Vector* vec, int data){
    for(int i=0; i<vec->length; i++){
        if(vec->start[i].data == data && vec->start[i].is_used == 1) return i;
    }
    return -1;
}

int push(Vector* vec, int data){
    if(vec->start==NULL){

        vec->start = (Cell*)malloc(sizeof(Cell) * VECTORINITSIZE);
        if(vec->start==NULL) return -1;

        vec->size = VECTORINITSIZE;
        vec->length = 0;
    }

    for(int i=0; i<vec->length; i++){
        if(vec->start[i].is_used==0){
            vec->start[i].data = data;
            vec->start[i].is_used = 1;
            return i;
        }
    }
    
    if(vec->length>=vec->size){

        Cell* buf;
        buf = (Cell*)realloc(vec->start, sizeof(Cell) * vec->size * VECTORGROWCOEFF);
        if(vec->start==NULL) return -1;

        vec->size *= VECTORGROWCOEFF;
        vec->start = buf;
    }

    vec->start[vec->length].data = data;
    vec->start[vec->length].is_used = 1;
    return vec->length++;
}

int pop(Vector* vec, int data){
    int i = find(vec, data);
    if(i == -1) return -1;
    vec->start[i].is_used = 0;
    return i;
}

int popi(Vector* vec, unsigned int index){
    if(index>=vec->length){
        fprintf(stderr, "ERROR: index(%d) out of range(<%d)\n", index, vec->length);
        abort();
    }
    vec->start[index].is_used = 0;
    return vec->start[index].data;
}


void print_vec(Vector* vec){
    for(int i=0; i<vec->length; i++){
            if(vec->start[i].is_used==1) printf("%d ", vec->start[i].data);
        }
        printf("\n");
}


int main(){
    Vector vec;
    vec.start=NULL;

    for(int i=0; i<11; i++){
        push(&vec, i);
    }

    print_vec(&vec);
    printf("\n");

    popi(&vec, 6);

    print_vec(&vec);
    printf("\n");

    for(int i=23; i<31; i++){
        push(&vec, i);
    }

    print_vec(&vec);
    
    return 0;
}
