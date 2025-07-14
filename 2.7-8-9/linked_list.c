#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode ListNode;
struct ListNode{
    char* key;
    void* value;
    ListNode* next;
};

ListNode* new_node(char* key, void* value){
    ListNode* ptr = (ListNode*)malloc(sizeof(ListNode));
    if(ptr!=NULL){
        ptr->value = value;
        ptr->key = key;
        ptr->next = NULL;
    }
    return ptr;
}


ListNode* find(ListNode* root, char* key){
    for(; root!=NULL; root=root->next){
        if(strcmp(key, root->key)==0) return root;
    }
    return NULL;
}


ListNode* push_front(ListNode* root, ListNode* new_root){
    if(new_root==NULL) return root;
    new_root->next = root;
    return new_root;
}

ListNode* push_back(ListNode* root, ListNode* node){
    if(root==NULL) return node;

    ListNode* end = root;
    for(; end->next!=NULL; end=end->next);

    end->next = node;
    return root;
}


ListNode* insert(ListNode* start, ListNode* source){
    if(start==NULL) return source;

    if(source!=NULL){
        ListNode* end = start->next;
        start->next = source;

        if(end!=NULL){
            ListNode* last_node = source;
            for(; last_node->next!=NULL; last_node = last_node->next);
            last_node->next = end;
        }
    }

    return start;
}

ListNode* insert_key(ListNode* root, char* key, ListNode* source){
    return insert(find(root, key), source);
}


ListNode* copy(ListNode* root){
    ListNode* new_root=NULL;

    for(; root!=NULL; root=root->next){
        new_root = push_back(new_root, new_node(root->key, root->value));
    }

    return new_root;
}

ListNode* copy_reversed(ListNode* root){
    ListNode* new_root=NULL;

    for(; root!=NULL; root=root->next){
        new_root = push_front(new_root, new_node(root->key, root->value));
    }

    return new_root;
}

ListNode* reverse_it(ListNode* root){
    ListNode* new_root=NULL;

    while(root!=NULL){
        ListNode* next = root->next;
        new_root = push_front(new_root, root);
        root = next;
    }

    return new_root;
}

ListNode* reverse_rec(ListNode* root, ListNode* prev){
    if(root==NULL) return NULL;

    if(root->next==NULL){
        root->next = prev;
        return root;
    }

    ListNode* new_root = reverse_rec(root->next, root);
    root->next = prev;

    return new_root;
}


ListNode* remove_ptr(ListNode* root, ListNode* node){
    if(root==node){
        ListNode* next = root->next;
        free(root);
        return next;
    }

    for(ListNode* ptr=root; ptr!=NULL; ptr=ptr->next){
        if(ptr->next==node){
            ptr->next=node->next;
            free(node);
            return root;
        }
    }

    return NULL;
}

ListNode* remove_key(ListNode* root, char* key){
    if(root==NULL) return NULL;

    if(strcmp(root->key, key)==0){
        ListNode* next = root->next;
        free(root);
        return next;
    }

    ListNode* prev = root;
    for(ListNode* ptr=root->next; ptr!=NULL; ptr=ptr->next){
        if(strcmp(ptr->key, key)==0){
            prev->next=ptr->next;
            free(ptr);
            return root;
        }
        prev = ptr;
    }

    return NULL;
}

void freeall(ListNode* root){
    ListNode* next;
    for(; root!=NULL; root=next){
        next = root->next;
        free(root);
    }
}


void print_list_keys(ListNode* root){
    for(ListNode* ptr=root; ptr!=NULL; ptr=ptr->next){
        printf("%s\n", ptr->key);
    }
}


int main(){
    ListNode* root = NULL;

    root = push_back(root, new_node("a", NULL));
    root = push_back(root, new_node("b", NULL));
    ListNode* node_c = new_node("c", NULL);
    root = push_back(root, node_c);
    root = push_back(root, new_node("d", NULL));
    
    root = push_front(root, new_node("x", NULL));

    print_list_keys(root);
    printf("\n");

    root = reverse_rec(root, NULL);

    print_list_keys(root);
    return 0;
}