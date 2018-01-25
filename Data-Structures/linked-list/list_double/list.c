#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node {
    
    int elem;
    struct node *next;
    struct node *prev;
    
};
typedef struct node *list;

list list_create(){
    return NULL;
}

void list_delete(list *L){
    if(L != NULL && *L != NULL){
        list_delete(&(*L)->next);
        free(*L);
        *L = NULL;
    }
}
/* allocate new node */
struct node *node_alloc(int elem){
    
    struct node *tmp = (struct node *)malloc(sizeof(struct node));
    
    if(tmp != NULL){
        tmp->elem = elem;
        tmp->next = NULL;
        tmp->prev = NULL;
    }
    return tmp;
}
/* return node at some index */
struct node *node_search(struct node *L, int index){
    
    while(index-- > 0 && L != NULL)
        L = L->next;
    
    return L;
}
/* insert node after a selected one */
int node_insert(struct node *L, int elem){
    
    if(L == NULL){
        return 1;
    }
    else {
        struct node *tmp = node_alloc(elem);
        
        if(tmp != NULL){
            tmp->next = L->next;
            tmp->prev = L;
            L->next = tmp;
            
            if(tmp->next != NULL)
                tmp->next->prev = tmp;
        }
        return tmp == NULL;
    }
}
/* remove the current node */
int node_delete(struct node *L){
    
    if(L == NULL || L->next == NULL){
        return 1;
    }
    else {
        if(L->next != NULL)
            L->next->prev = L->prev;
        if(L->prev != NULL)
            L->prev->next = L->next;
        free(L);
        return 0;
    }
}

int is_empty(list *L){
    return (L == NULL) || (*L == NULL);
}

int is_in_list(list *L, int elem){
    
    if(is_empty(L))
        return 0;
    else {
        struct node *tmp = *L;
        
        while(tmp->next != NULL && tmp->elem != elem)
            tmp = tmp->next;
        
        return tmp == NULL;
    }
}

/* allocate new node at the beginning of the list */
int head_insert(list *L, int elem){
    
    if(L == NULL){
        return 1;
    }
    else if (is_empty(L)){
        return (*L = node_alloc(elem)) == NULL;
    }
    else {
        struct node *tmp = node_alloc(elem);
        
        if(tmp != NULL){
            tmp->next = *L;
            (*L)->prev = tmp;
            *L = tmp;
        }
        return tmp == NULL;
    }
}

int tail_insert(list *L, int elem){
    if(L == NULL){
        return 1;
    }
    else if(is_empty(L)){
        return head_insert(L, elem);
    }
    else {
        struct node *tmp = *L;
        while(tmp->next != NULL)
            tmp = tmp->next;
        
        return node_insert(tmp, elem);
    }
}

int indx_insert(list *L, int elem, int index){
    
    if(index == 0)
        return head_insert(L, elem);
    else
        return node_insert(node_search(*L, index-1), elem);
}
/* delete the first element */
int head_delete(list *L){
    
    if(is_empty(L)){
        return 1;
    }
    else {
        struct node *tmp = *L;
        
        *L = (*L)->next;
        free(tmp);
        return 0;
    }
}
/* delete the last element */
int tail_delete(list *L){
    if(L == NULL){
        return 1;
    }
    else if((*L)->next == NULL){
        return head_delete(L);
    } else {
        struct node *tmp = *L;
        
        while(tmp->next->next != NULL)
            tmp = tmp->next;
        
        node_delete(tmp);
        return 0;
    }
}
/* delete ementet at some index */
int indx_delete(list *L, int index){
    if(index == 0)
        return head_delete(L);
    else
        return node_delete(node_search(*L, index));
}

int head_select(list *L){
    if(is_empty(L))
        return 0;
    else
        return (*L)->elem;
}

int tail_select(list *L){
    if(is_empty(L))
        return 0;
    else {
        struct node *tmp = *L;
        while(tmp->next != NULL)
            tmp = tmp->next;
        return tmp->elem;
    }
}

int indx_select(list *L, int index){
    if(is_empty(L))
        return -1;
    else {
        struct node *tmp = node_search(*L, index);
        
        if(tmp == NULL)
            return -2;
        else return tmp->elem;
    }
}

int main(){
    
    list coords = list_create();
    int i, val;
    srand(time(NULL));
    
    val = rand() % 50 + 1;
    
    for(i=0; i<5; i++){
        val = rand() % 50 + 1;
        tail_insert(&coords, val);
        printf("%d\n", val);
    }
    
    printf("----------------------------\n");
    
    for(i=0; i<5; i++)
        printf("%d\n", indx_select(&coords, i));
    
    
    return 0;
}
