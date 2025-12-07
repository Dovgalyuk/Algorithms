#include "avl.h"
#include <string>

AVL::AVL() : root(nullptr) {}

AVL::~AVL() 
{
    clear(root);
}

void AVL::clear(node* p) 
{
    if(p != nullptr) 
    {
        clear(p->left);
        clear(p->right);

        delete p;
    }
}

int AVL::height(node* p) 
{
    if(p == nullptr)
    {
        return 0;
    }

    return p->height;
}

int AVL::bfactor(node* p) 
{
    return height(p->right) - height(p->left);
}

void AVL::fixheight(node* p) 
{
    int hl = height(p->left);
    int hr = height(p->right);

    if(hl > hr)
    {
        p->height = hl + 1;
    }
    else 
    {
        p->height = hr + 1;
    }
}

AVL::node* AVL::rotateright(node* p) 
{
    node* q = p->left;
    p->left = q->right;
    q->right = p;

    fixheight(p);
    fixheight(q);

    return q;
}

AVL::node* AVL::rotateleft(node* q) 
{
    node* p = q->right;
    q->right = p->left;
    p->left = q;

    fixheight(q);
    fixheight(p);

    return p;
}

AVL::node* AVL::balance(node* p) 
{
    fixheight(p);

    if(bfactor(p) == 2) 
    {
        if(bfactor(p->right) < 0)
        {
            p->right = rotateright(p->right);
        }

        return rotateleft(p);
    }
    if(bfactor(p) == -2) 
    {
        if(bfactor(p->left) > 0)
        {
            p->left = rotateleft(p->left);
        }

        return rotateright(p);
    }

    return p;
}

AVL::node* AVL::insert(node* p, const std::string& k, const std::string& v) 
{
    if(p == nullptr) 
    {
        return new node(k, v);
    }

    if(k < p->key)
    {
        p->left = insert(p->left, k, v);
    }
    else if(k > p->key)
    {
        p->right = insert(p->right, k, v);
    }
    else
    {
        p->value = v;
    }

    return balance(p);
}

AVL::node* AVL::findmin(node* p) 
{
    if(p == nullptr) 
    {
        return nullptr;  
    }

    if(p->left == nullptr) 
    {
        return p; 
    }

    return findmin(p->left);
}

AVL::node* AVL::removemin(node* p) 
{
    if(p->left == nullptr)
    {
        return p->right;
    }
    
    p->left = removemin(p->left);

    return balance(p);
}

AVL::node* AVL::remove(node* p, const std::string& k) 
{
    if(p == nullptr)
    {
        return nullptr;
    }
    
    if(k < p->key)
    {
        p->left = remove(p->left, k);
    }
    else if(k > p->key)
    {
        p->right = remove(p->right, k);
    }
    else 
    {
        node* q = p->left;
        node* r = p->right;
        delete p;
        
        if(r == nullptr)
        {
            return q;
        }
        
        node* min = findmin(r);
        min->right = removemin(r);
        min->left = q;

        return balance(min);
    }

    return balance(p);
}

AVL::node* AVL::find(node* p, const std::string& k) 
{
    if(p == nullptr) 
    {
        return nullptr;
    } 
    
    if(k < p->key)
    {
        return find(p->left, k);
    }
    else if(k > p->key)
    {
        return find(p->right, k);
    }
    else
    {
        return p;
    }
}

void AVL::add(const std::string& k, const std::string& v) 
{
    root = insert(root, k, v);
}

bool AVL::get(const std::string& k, std::string& v) 
{
    node* found = find(root, k);

    if(found != nullptr) 
    {
        v = found->value;
        return true;
    }

    return false; 
}

void AVL::del(const std::string& k) 
{
    root = remove(root, k);
}