#ifndef AVLTREE_H
#define AVLTREE_H
struct node;
unsigned char height(node* p);
int bfactor(node* p);
void fixheight(node* p);
node* rotateright(node* p);
node* rotateleft(node* q);
node* balance(node* p);
node* insert(node* p, int k);
node* findmin(node* p);
node* removemin(node* p);
node* remove(node* p, int k);
node* FindKey(node* node, int k);
int get_key(node* node);


#endif