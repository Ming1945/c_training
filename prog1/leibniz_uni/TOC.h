#ifndef __TOC_H__
#define __TOC_H__

#include "base.h"

struct TNode;

typedef struct Node {
    struct TNode* chapter;
    struct Node* next;
} Node;

typedef struct TNode {
    String name;
	int my_pages;
    Node* subchapters;
} TNode;

//a)
TNode* new_TNode(String name, int my_pages, Node* subchapters);

Node* new_node(TNode* chapter, Node* next);

//b)
void free_TNode(TNode* chapter);

void free_Nodes(Node* node);

//Template function needs new_TNode and new_node;
void add_subchapter(TNode* chapter, String subchapters[], int pages[], int size);

//c)
int calculate_pages(TNode* toc);

//d)
void print_TOC(TNode* toc);


#endif