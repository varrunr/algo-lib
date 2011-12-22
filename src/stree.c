#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_ALPHA 26
struct Node{
int eos;
struct Node* ptrs[MAX_ALPHA];
};

int get_i(char c){return ((int)c - 97);}
void init_node(struct Node**);
void stree_add_word(struct Node **,char *);
int stree_search(struct Node **, char *);
struct Node* path_exists(struct Node**, int);
void alloc_node(struct Node**);
void do_dfs(struct Node **);

int main()
{
    struct Node* root;
    //struct node* stree;
    init_node(&root);
    // Input strings
    stree_add_word(&root,"bat");
    stree_add_word(&root,"cat");
    // DFS to print out all strings
    do_dfs(&root);
    // Search for a string
    if(stree_search(&root,"cat"))
        printf("Yes\n");
    else printf("No\n");
    return 0;
}
void do_dfs(struct Node **cnode)
{
    int i;
    if( (*cnode)->eos == 1) {printf("\n");return;}
    for(i=0;i<MAX_ALPHA;i++){
        if( ((*cnode)->ptrs[i]) != NULL){
            printf("%c",i+97);
            do_dfs(&((*cnode)->ptrs[i]));
        }
    }
    return;
}
void init_node(struct Node** root)
{
    int i;
    *root =(struct Node*)malloc(sizeof(struct Node));
    (*root)->eos = 0;
    for(i=0;i<MAX_ALPHA;i++)
        (*root)->ptrs[i] = NULL;
}
void alloc_node(struct Node** to_alloc)
{
    (*to_alloc) = (struct Node*) malloc(sizeof(struct Node));
}
struct Node* path_exists(struct Node** chk_node, int index)
{
    if((*chk_node)->ptrs[index] !=NULL)
        return (*chk_node)->ptrs[index];
    else{
            // create new node
            struct Node* new_node;
            alloc_node(&new_node);
            (*chk_node)->ptrs[index] = new_node;
            return new_node;
    }
}
    
void stree_add_word(struct Node** root, char* s)
{
    int i=0;
    struct Node* temp = *root;
    for(i=0;i<strlen(s);i++){
        temp = path_exists(&temp,get_i(s[i]));
        if(i == strlen(s) -1)
            temp->eos = 1;
    }
}

int stree_search(struct Node **root, char *q)
{
    int i;
    struct Node *temp = *root;
    for(i=0;i<strlen(q);i++)
    {
       if(temp->ptrs[get_i(q[i])] != NULL)
            temp = temp->ptrs[get_i(q[i])];
        else return 0;
    }
    if( temp->eos == 1) return 1; else return 0;
}
