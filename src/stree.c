#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_LEN 20
#define MAX_ALPHA 27
#define EOS '$'

struct Node{
struct Node* ptrs[MAX_ALPHA];
};

int get_i(char c){if(c==EOS) return 26; else return ((int)c - 97);}
char to_c(int i){if(i==26)return EOS; else return (char)(i+97);} 
void init_node(struct Node**);
void stree_add_word(struct Node **,char *);
int stree_search(struct Node **, char *);
struct Node* path_exists(struct Node**, int);
void alloc_node(struct Node**);
void do_dfs(struct Node **,char *);
int is_terminal_str(struct Node **);
int stree_search_substr(struct Node **, char *);

int main()
{
    struct Node* root;
    struct Node* temp;
    int i = 0;
    int *blah;
    char *str = "aabcddd$";
    // Initialize root
    init_node(&root);
    // Adding suffixes
    for(i=0;i<strlen(str)-1;i++){
        printf("%s\n",(str+i));
        stree_add_word(&root,str+i);
    }
   // DFS to print out all strings
    printf("Strings:\n");
    do_dfs(&root,"");
   
   // Search for a string
    if(stree_search_substr(&root,"dda"))
        printf("Yes\n");
    else printf("No\n");
    return 0;
}
int is_terminal_str(struct Node **cnode)
{
    if( (*cnode)->ptrs[get_i(EOS)] != NULL) return 1; else return 0;
}
int stree_search_substr(struct Node **root, char *substr)
{
    struct Node *temp = *root;
    int flag = 0,i=0;
    for(i=0;i<strlen(substr);i++){
        if(temp->ptrs[get_i(substr[i])] != NULL){
            temp = temp->ptrs[get_i(substr[i])];
            flag = 1;
        }
        else {flag == 0;break;}
    }
    return flag;
}
        
void do_dfs(struct Node **cnode,char *path)
{
    //DEBUG: 
    int i,j,cur_posn;
    
    char *temp = (char *)malloc(MAX_LEN*sizeof(char));
    strcpy(temp,path);
    cur_posn = strlen(temp);
    if( (is_terminal_str(cnode))) {printf("%s\n",temp);}
    for(i=0;i<MAX_ALPHA;i++){
        if( ((*cnode)->ptrs[i]) != NULL){
            temp[cur_posn] = (i+97);
            do_dfs(&((*cnode)->ptrs[i]),temp);
        }
    }
    return;
}
void init_node(struct Node** root)
{
    int i;
    *root =(struct Node*)malloc(sizeof(struct Node));
    for(i=0;i<MAX_ALPHA;i++)
        (*root)->ptrs[i] = NULL;
}
void alloc_node(struct Node** to_alloc)
{
    (*to_alloc) = (struct Node*) malloc(sizeof(struct Node));
}
struct Node* path_exists(struct Node** chk_node, int index)
{
    if((*chk_node)->ptrs[index] !=NULL){
        return (*chk_node)->ptrs[index];
    }
    else{
            // create new node
            struct Node* new_node;
            //alloc_node(&new_node);
            init_node(&new_node);
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
    return is_terminal_str(&temp);
}
