#include "AVLtree.h"
#include <iostream>
struct avl_node
{
	int key;
	unsigned char height;
	avl_node* left;
	avl_node* right;
	avl_node(int k) { key = k; left = right = 0; height = 1; }
};

unsigned char avl_height(avl_node* p)
{
	return p ? p->height : 0;
}

int avl_bfactor(avl_node* p)                       //¬озвращает разницу деревьев
{
	if (p == NULL) {
		return 0;
	}
	return avl_height(p->right) - avl_height(p->left);
}

void avl_fixheight(avl_node* p)                      //востанавливает высоту
{
	unsigned char hl = avl_height(p->left);
	unsigned char hr = avl_height(p->right);
	p->height = (hl > hr ? hl : hr) + 1;
}

avl_node* avl_rotateright(avl_node* p)
{
	avl_node* q = p->left;
	p->left = q->right;
	q->right = p;
	avl_fixheight(p);
	avl_fixheight(q);
	return q;
}

avl_node* avl_rotateleft(avl_node* q)
{
	avl_node* p = q->right;
	q->right = p->left;
	p->left = q;
	avl_fixheight(q);
	avl_fixheight(p);
	return p;
}

avl_node* avl_balance(avl_node* p) //баланс высоты дерева
{
	avl_fixheight(p);
	if (avl_bfactor(p) == 2)
	{
		if (avl_bfactor(p->right) < 0)
			p->right = avl_rotateright(p->right);
		return avl_rotateleft(p);
	}
	if (avl_bfactor(p) == -2)
	{
		if (avl_bfactor(p->left) > 0)
			p->left = avl_rotateleft(p->left);
		return avl_rotateright(p);
	}
	return p;
}

avl_node* avl_insert(avl_node* p, int k)    //нова€ вершина
{
	if (!p) return new avl_node(k);
	if (k < p->key)
		p->left = avl_insert(p->left, k);
	else
		p->right = avl_insert(p->right, k);
	return avl_balance(p);
}

avl_node* avl_findmin(avl_node* p)            //вернуть мин
{
	return p->left ? avl_findmin(p->left) : p;
}

avl_node* avl_removemin(avl_node* p)          //возврать правого элемента минимального
{
	if (p->left == NULL)
		return p->right;
	p->left = avl_removemin(p->left);
	return avl_balance(p);
}

avl_node* avl_remove(avl_node* p, int k)     //удалить элемент кеу
{
	if (!p) return 0;
	if (k < p->key)
		p->left = avl_remove(p->left, k);
	else if (k > p->key)
		p->right = avl_remove(p->right, k);
	else
	{
		avl_node* q = p->left;
		avl_node* r = p->right;
		delete p;
		if (!r) return q;
		avl_node* min = avl_findmin(r);
		min->right = avl_removemin(r);
		min->left = q;
		return avl_balance(min);
	}
	return avl_balance(p);
}

avl_node* avl_FindKey(avl_node* avl_node, int k) {          //возврат и поиск элемента
	if (avl_node != NULL)
	{
		if (avl_node->key == k) return avl_node;
		if (avl_node->key > k) return avl_FindKey(avl_node->left, k);
		else return avl_FindKey(avl_node->right, k);
	}
	return NULL;
}
int avl_get_key(avl_node* avl_node) {
	return avl_node->key;
}

bool avl_check(avl_node* p)          //проверка на баланс
{
	if (p == NULL)
	{
		return 1;
	}
	if (avl_bfactor(p) > 1 && avl_bfactor(p) < -1)
	{
		return 0;
	}
	if (p->left) {
		avl_check(p->left);
	}
	if (p->right) {
		avl_check(p->right);
	}
	return 1;
}


bool avl_checkheight(avl_node* p, int num) {
	
	p = avl_FindKey(p, num);
	if (avl_checkhelp(p)+1 == p->height)
		return 1;
	else return 0;

}

int avl_checkhelp(avl_node* p){
	if (p->left == NULL && p->right == NULL)
	{
		return 0;
	}
	else if (p->right == NULL)
	{
		return avl_checkhelp(p->left)+1;
	}
	else if (p->left == NULL)
	{
		return avl_checkhelp(p->right)+1;
	}
	else
		return (avl_checkhelp(p->left)+1) > (avl_checkhelp(p->right)+1) ? avl_checkhelp(p->left) + 1 : avl_checkhelp(p->right) + 1;

}