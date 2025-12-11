#ifndef AVL_H
#define AVL_H

#include <string>

class AVL
{
public:
    AVL();
    ~AVL();

    void add(const std::string& k, const std::string& v);
    bool get(const std::string& k, std::string& v);
    void del(const std::string& k);

private:
    struct node 
    {
        std::string key;
        std::string value;
	    int height;
	    node* left;
 	    node* right;

	    node(const std::string& k, const std::string& v) : key(k), value(v), height(1), left(nullptr), right(nullptr){}
    };

    node* root;

    static int height(node* p);
    static int bfactor(node* p);
    static void fixheight(node* p);
    static node* rotateright(node* p);
    static node* rotateleft(node* q);
    static node* balance(node* p);
    static node* findmin(node* p);
    static node* removemin(node* p);
    static node* insert(node* p, const std::string& k, const std::string& v);
    static node* remove(node* p, const std::string& k);
    static node* find(node* p, const std::string& k);
    static void clear(node* p);
};

#endif
