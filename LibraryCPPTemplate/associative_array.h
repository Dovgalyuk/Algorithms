#ifndef RB_ASSOCIATIVE_ARRAY_H
#define RB_ASSOCIATIVE_ARRAY_H
#include <iostream>
#include <string>

using namespace std;

template<typename Key, typename Value> class RBAssociativeArray
{
public:

	struct Node
	{
		friend class RBAssociativeArray;

		string getKey()
		{
			return key;
		}

	private:
		string key, value, searchNode;  // Ключ, значение, искомое значение (оставил на всякий случай, тк функция поиска булевая)
		Node* parent = nullptr;
		Node* left = nullptr;
		Node* right = nullptr;
		char color = 'B';

		Node(string key, string value) : key(key), value(value) {}
	}; Node* main = nullptr;

	typedef Node* NodePtr;

	RBAssociativeArray(string key, string value)
	{
		TNULL = new Node(key, value);
		TNULL->color = 'B';
		TNULL->left = nullptr;
		TNULL->right = nullptr;
		root = TNULL;
		searchPtr = TNULL;          // Уазатель на искомое значение
	}
	~RBAssociativeArray()
	{
		delete[] main;
	}

	bool SearchTree(string key)
	{
		return SearchTreeP(this->root, key);
	}

	NodePtr Minimum(NodePtr node)
	{
		while (node->left != TNULL)
		{
			node = node->left;
		}
		return node;
	}

	void Insert(string key, string value)
	{
		NodePtr node = new Node(key, value);
		node->parent = nullptr;
		node->key = key;
		node->value = value;
		node->left = TNULL;
		node->right = TNULL;
		node->color = 'R';

		NodePtr y = nullptr;
		NodePtr x = this->root;

		while (x != TNULL)
		{
			y = x;
			if (node->value.size() > x->value.size())
			{
				x = x->right;
			}
			else if (node->value < x->value)
			{
				x = x->left;
			}
			else
			{
				x = x->right;
			}
		}

		node->parent = y;
		if (y == nullptr)
		{
			root = node;
		}
		else if (node->value.size() > y->value.size())
		{
			y->right = node;
		}
		else if (node->value < y->value)
		{

			y->left = node;
		}
		else
		{
			y->right = node;
		}

		if (node->parent == nullptr)
		{
			node->color = 'B';
			return;
		}

		if (node->parent->parent == nullptr)
		{
			return;
		}
		FixInsert(node);
	}

	void DeleteNode(string key)
	{
		DeleteNodeP(this->root, key);
	}

private:
	NodePtr root;
	NodePtr TNULL;
	NodePtr searchPtr;

	void LeftRotate(NodePtr x)
	{
		NodePtr y = x->right;
		x->right = y->left;
		if (y->left != TNULL)
		{
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr)
		{
			this->root = y;
		}
		else if (x == x->parent->left)
		{
			x->parent->left = y;
		}
		else
		{
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}

	void RightRotate(NodePtr x)
	{
		NodePtr y = x->left;
		x->left = y->right;
		if (y->right != TNULL)
		{
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr)
		{
			this->root = y;
		}
		else if (x == x->parent->right)
		{
			x->parent->right = y;
		}
		else
		{
			x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
	}

	bool SearchTreeP(NodePtr node, string key)
	{
		if (node == nullptr)
		{
			return false;
		}
		if (node->key == key)
		{
			node->searchNode = node->value;  // Запоминаем найденное значечение, чтобы была возможность его получить при необходимости
			searchPtr = node;               // Запоминаем указатель искомого значения
			return true;
		}
		if (SearchTreeP(node->left, key) || SearchTreeP(node->right, key))
		{
			node->searchNode = node->value;
			return true;
		}
		return false;
	}

	void FixDelete(NodePtr x)
	{
		NodePtr s;
		while (x != root && x->color == 'B')
		{
			if (x == x->parent->left)
			{
				s = x->parent->right;
				if (s->color == 'R')
				{
					s->color = 'B';
					x->parent->color = 'R';
					LeftRotate(x->parent);
					s = x->parent->right;
				}

				if (s->left->color == 'B' && s->right->color == 'B')
				{
					s->color = 'R';
					x = x->parent;
				}
				else
				{
					if (s->right->color == 'B')
					{
						s->left->color = 'B';
						s->color = 'R';
						RightRotate(s);
						s = x->parent->right;
					}
					s->color = x->parent->color;
					x->parent->color = 'B';
					s->right->color = 'B';
					LeftRotate(x->parent);
					x = root;
				}
			}
			else
			{
				s = x->parent->left;
				if (s->color == 'R')
				{
					s->color = 'B';
					x->parent->color = 'R';
					RightRotate(x->parent);
					s = x->parent->left;
				}

				if (s->left->color == 'B' && s->right->color == 'B')
				{
					s->color = 'R';
					x = x->parent;
				}
				else
				{
					if (s->left->color == 'B')
					{
						s->right->color = 'B';
						s->color = 'R';
						LeftRotate(s);
						s = x->parent->left;
					}
					s->color = x->parent->color;
					x->parent->color = 'B';
					s->left->color = 'B';
					RightRotate(x->parent);
					x = root;
				}
			}
		}
		x->color = 'B';
		root->color = 'B';
	}


	void RBTransplant(NodePtr u, NodePtr v)
	{
		if (u->parent == nullptr)
		{
			root = v;
		}
		else if (u == u->parent->left)
		{
			u->parent->left = v;
		}
		else
		{
			u->parent->right = v;
		}
		v->parent = u->parent;
	}

	void DeleteNodeP(NodePtr node, string key)
	{
		NodePtr z = TNULL;
		NodePtr x, y;

		if (SearchTreeP(this->root, key))
		{
			z = searchPtr;
		}
		else return;

		y = z;
		char y_original_color = y->color;
		if (z->left == TNULL)
		{
			x = z->right;
			RBTransplant(z, z->right);
		}
		else if (z->right == TNULL)
		{
			x = z->left;
			RBTransplant(z, z->left);
		}
		else
		{
			y = Minimum(z->right);
			y_original_color = y->color;
			x = y->right;
			if (y->parent == z) {
				x->parent = y;
			}
			else
			{
				RBTransplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}

			RBTransplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
		delete z;
		if (y_original_color == 'B')
		{
			FixDelete(x);
		}
	}

	void FixInsert(NodePtr k)
	{
		NodePtr u;
		while (k->parent->color == 'R')
		{
			if (k->parent == k->parent->parent->right)
			{
				u = k->parent->parent->left; // uncle
				if (u->color == 'R')
				{
					u->color = 'B';
					k->parent->color = 'B';
					k->parent->parent->color = 'R';
					k = k->parent->parent;
				}
				else
				{
					if (k == k->parent->left)
					{
						k = k->parent;
						RightRotate(k);
					}
					k->parent->color = 'B';
					k->parent->parent->color = 'R';
					LeftRotate(k->parent->parent);
				}
			}
			else
			{
				u = k->parent->parent->right; // uncle

				if (u->color == 1)
				{
					u->color = 'B';
					k->parent->color = 'B';
					k->parent->parent->color = 'R';
					k = k->parent->parent;
				}
				else {
					if (k == k->parent->right)
					{
						k = k->parent;
						LeftRotate(k);
					}
					k->parent->color = 'B';
					k->parent->parent->color = 'R';
					RightRotate(k->parent->parent);
				}
			}
			if (k == root)
			{
				break;
			}
		}
		root->color = 'B';
	}
};
#endif