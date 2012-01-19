#include<stdio.h>
#ifndef __STREE_H__
#define __STREE_H__

#define MAX_LEN 20
#define MAX_ALPHA 27
#define EOS '$'

typedef struct Node
{
    struct Node* ptrs[MAX_ALPHA];
}Node;

int get_i(char c);
char to_c(int i);
void init_node(Node**);
void stree_add_word(Node **,char *);
int stree_search(Node **, char *);
Node* path_exists(Node**, int);
void do_dfs(Node **,char *);
int is_terminal_str(Node **);

#endif
