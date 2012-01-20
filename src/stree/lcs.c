#include"stree_lcs.h"
#include<string.h>
#include<stdlib.h>

char* concatenate(char*,char*);
int main()
{
    Node* root;
    Node* temp;
    int i = 0;
    char *str1 = "aabcddd";
    char *str2 = "gfaabfed";
    char* s;
    s = concatenate(str1,str2);
    for(i=0;i<strlen(s);i++)
        printf("%c",s[i]);
        printf("\n");
    return 0;
}

char* concatenate(char* str1,char* str2)
{
    char *search_str = malloc( sizeof(char) * (strlen(str1) + strlen(str2) +1) );
    int i;
    strcpy(search_str,str1);
    search_str[strlen(str1)] = '#';
    strcpy(search_str + strlen(str1) + 1,str2);
    return search_str;
}

void init_node(Node** root)
{
    int i;
    *root =(Node*)malloc(sizeof(Node));
    for(i=0;i<MAX_ALPHA;i++)
        (*root)->ptrs[i] = NULL;
}

Node* path_exists(Node** chk_node, int index)
{
    if((*chk_node)->ptrs[index] !=NULL){
        return (*chk_node)->ptrs[index];
    }
    else{
            // create new node
            Node* new_node;
            init_node(&new_node);
            (*chk_node)->ptrs[index] = new_node;
            return new_node;
    }
}
    
void stree_add_word(Node** root, char* s)
{
    int i=0;
    Node* temp = *root;
    for(i=0;i<strlen(s);i++){
        temp = path_exists(&temp,get_i(s[i]));
    }
}

int stree_search(Node **root, char *q)
{
    int i;
    Node *temp = *root;
    for(i=0;i<strlen(q);i++)
    {
       if(temp->ptrs[get_i(q[i])] == NULL)
            return 0;
        temp = temp->ptrs[get_i(q[i])];
    
    }
    return 1;
}

int get_i(char c){if(c==EOS) return 26; else return ((int)c - 97);}
char to_c(int i){if(i==26)return EOS; else return (char)(i+97);} 

int is_terminal_str(Node **cnode)
{
    if( (*cnode)->ptrs[get_i(EOS)] != NULL) return 1; else return 0;
}
       
void do_dfs(Node **cnode,char *path)
{
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
