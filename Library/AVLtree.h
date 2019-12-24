#ifndef AVLTREE_H
#define AVLTREE_H
struct avl_node;
unsigned char avl_height(avl_node* p);
int avl_bfactor(avl_node* p);
void avl_fixheight(avl_node* p);
avl_node* avl_rotateright(avl_node* p);
avl_node* avl_rotateleft(avl_node* q);
avl_node* avl_balance(avl_node* p);
avl_node* avl_insert(avl_node* p, int k);
avl_node* avl_findmin(avl_node* p);
avl_node* avl_removemin(avl_node* p);
avl_node* avl_remove(avl_node* p, int k);
avl_node* avl_FindKey(avl_node* avl_node, int k);
int avl_get_key(avl_node* avl_node);
bool avl_check(avl_node* p);
bool avl_checkheight(avl_node* p);
int avl_checkhelp(avl_node* p);

#endif