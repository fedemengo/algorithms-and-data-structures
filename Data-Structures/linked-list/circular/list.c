#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node {
    
    int elem;
    struct node *next;
    struct node *prev;
    
};
typedef struct node *list;

static struct node *node_alloc(int elem){
    struct node *tmp = (struct node*)malloc(sizeof(struct node));
    
    if(tmp != NULL){
        tmp->elem = elem;
        tmp->next = tmp;
        tmp->prev = tmp;
    }
    return tmp;
}

static struct node *node_search(struct node *L, unsigned int i){
    if(i == 0 || L == NULL)
        return L;
    else {
        struct node *tmp = L->next;
        while(tmp != L && --i>0)
            tmp = tmp->next;
        return tmp == L ? NULL : tmp;
    }
}

static int node_delete(struct node *L){
    
    if(L == NULL)
        return 1;
    else {
        L->next->prev = L->prev;
        L->prev->next = L->next;
        free(L);
        
        return 0;
    }
}

static int node_insert(struct node *L, int elem){
    if(L == NULL)
        return 1;
    else {
        struct node *tmp = node_alloc(elem);
        if(tmp != NULL){
            tmp->prev = L;
            tmp->next = L->next;
            L->next->prev = tmp;
            L->next = tmp;
        }
        
        return tmp == NULL;
    }
}

list list_create(){
    return NULL;
}

void list_delete(list *L){
    if(L != NULL || *L != NULL){
        while(*L != (*L)->next)
            node_delete((*L)->next);
        free(*L);
        *L = NULL;
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
        while(tmp != (*L)->prev && tmp->elem != elem)
            tmp = tmp->next;
        return tmp->elem == elem;
    }
}

int head_insert(list *L, int elem){
    if(L == NULL)
        return 1;
    else if(is_empty(L))
        return (*L = node_alloc(elem)) == NULL;
    else if(node_insert((*L)->prev, elem) == 1)
        return 1;
    else
        return (*L = (*L)->prev) == NULL;
}

int tail_insert(list *L, int elem){
    if(L == NULL)
        return 1;
    else if(is_empty(L))
        return (*L = node_alloc(elem)) == NULL;
    else
        return node_insert((*L)->prev, elem);
}

int indx_insert(list *L, int elem, int index){
    
    if(index == 0 || is_empty(L))
        return head_insert(L, elem);
    else
        return node_insert(node_search(*L, index-1), elem);
}

int head_delete(list *L){
    if(L == NULL)
        return 1;
    else if(is_empty(L))
        return 1;
    else if(*L == (*L)->next){
        free(*L);
        *L = NULL;
        return 0;
    }
    else {
        *L = (*L)->next;
        return node_delete((*L)->prev);
    }
}

int tail_delete(list *L){
    if(L == NULL)
        return 1;
    else if(is_empty(L))
        return 1;
    else if(*L == (*L)->next){
        free(*L);
        *L = NULL;
        return 0;
    }
    else return node_delete((*L)->prev);
}

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
    else return (*L)->prev->elem;
}

int indx_select(list *L, int index){
    if(is_empty(L))
        return 0;
    else {
        struct node *tmp = node_search(*L, index);
        
        if(tmp == NULL)
            return 0;
        else return tmp->elem;
    }
}

int list_size(list *L){
    if(L == NULL)
        return -1;
    else if(is_empty(L))
        return 0;
    else if(*L == (*L)->next)
        return 1;
    else {
        unsigned int s = 0;
        struct node *tmp = *L;
        while(tmp->next != *L){
            s++;
            tmp = tmp->next;
        }
        return s;
    }
}

void print_list(list *L){
    if(L == NULL)
        return;
    else {
        struct node *tmp = *L;

        do{
            printf("%d\n", tmp->elem);
            tmp = tmp->next;
        } while(tmp != *L);
            
        return;
    }
}

void reverse(list *s){
    if(s != NULL && *s != NULL){
        struct node *node = *s;
        /* reverse the list */
        do {
            struct node *tmp = node->next;
            node->next = node->prev;
            node->prev = tmp;
            node = tmp;
        } while(node != *s);
        /* update the pointer */
        *s = (*s)->next;
        return;
    }
}

int get_length(list *L){
    if(L == NULL || *L == NULL)
        return 1;
    else {
        list tmp = *L;
        unsigned int l = 1;
        while(tmp->next != *L){
            tmp = tmp->next;
            l++;
        }
        return l;
    }
}

void reverse_value(list *L){
    int i, len = get_length(L);
    
    for(i=0; i<len/2; i++){
        int tmp = node_search(*L, i)->elem;
        node_search(*L, i)->elem = node_search(*L, len-i-1)->elem;
        node_search(*L, len-i-1)->elem = tmp;
    }
}


int main(int argc, char *argv[]){
    
    list coords = list_create();
    int i, val, index;
    srand(time(NULL));
    
    for(i = 0; i<atoi(argv[1]); i++)
        head_insert(&coords, rand() % 50 + 1);
    
    printf("Insert your choice:\n \
           1 - is empty\n \
           2 - is in list\n \
           3 - head insert\n \
           4 - tail insert\n \
           5 - indx inser\n \
           6 - head remove\n \
           7 - tail remove\n \
           8 - indx remove\n \
           9 - reverse\n \
           10 - get length\n");
    
    while (1) {
        scanf("%d", &i);
        switch (i) {
            case 1:
                printf("%s\n", is_empty(&coords) ? "EMPTY" : "NOT EMPTY");
                break;
            case 2:
                printf("Value to check: ");
                scanf("%d", &val);
                printf("%d is%sin list\n", val, is_in_list(&coords, val) ? " " : " not ");
                break;
            case 3:
                printf("Value to insert on head: ");
                scanf("%d", &val);
                head_insert(&coords, val);
                break;
            case 4:
                printf("Value to insert on tail: ");
                scanf("%d", &val);
                tail_insert(&coords, val);
                break;
            case 5:
                printf("Value to insert on index: ");
                scanf("%d %d", &val, &index);
                indx_insert(&coords, val, index);
                break;
            case 6:
                printf("Remove from head\n");
                head_delete(&coords);
                break;
            case 7:
                printf("Remove from tail\n");
                tail_delete(&coords);
                break;
            case 8:
                printf("Remove from index\n");
                scanf("%d", &index);
                indx_delete(&coords, index);
                break;
            case 9:
                printf("Reverse\n");
                reverse_value(&coords);
                break;
            case 10:
                printf("Lenght = %d\n", get_length(&coords));
                break;
            default:
                printf("-------------------------\n");
                print_list(&coords);
                printf("-------------------------\n");
                break;
        }
    }
    
    return 0;
}
