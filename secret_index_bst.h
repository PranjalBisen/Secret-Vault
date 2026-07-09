
    //ॐ गं गणपतये नमः
    //जय श्री राम
    //ॐ नमः शिवाय
#include <bits/stdc++.h>
using namespace std;

#ifndef SECRET_INDEX_BST_H
#define SECRET_INDEX_BST_H

struct BSTNode{
    string key;
    long long offset;
    BSTNode* left_child;
    BSTNode* right_child;
};

BSTNode* create_new_node(string,long long);
void insert_new_node_in_bst(BSTNode*,BSTNode*&);
BSTNode* search_node_in_bst(string,BSTNode*);
void inorder_traversal_of_bst(BSTNode*);
#endif
