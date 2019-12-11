#include <memory>
#include <cmath>

template <typename Key, typename Value>
class Node {
public:
	Key key;
	Value value;
	size_t height;
	std::shared_ptr<Node<Key, Value>> left;
	std::shared_ptr<Node<Key, Value>> right;
	Node(Key key, Value value);
	const int8_t getBFactor();
	void fixHeight();
};

template <typename Key, typename Value>
static size_t getNodeHeight(std::shared_ptr<Node<Key, Value>> node) {
	return node ? node->height : 0;
}

template<typename Key, typename Value>
Node<Key, Value>::Node(Key key, Value value) {
	this->key = key;
	this->value = value;
	this->height = 1;
}

template<typename Key, typename Value>
void Node<Key, Value>::fixHeight()
{
	height = fmax(getNodeHeight<Key, Value>(left), getNodeHeight<Key, Value>(right)) + 1;
}


template<typename Key, typename Value>
const int8_t Node<Key, Value>::getBFactor()
{
	return (getNodeHeight<Key, Value>(right) - getNodeHeight<Key, Value>(left));
}


template <typename Key, typename Value>
class AVLTree {
private:
	std::shared_ptr<Node<Key, Value>> root;
	static std::shared_ptr<Node<Key, Value>> appendTo(std::shared_ptr<Node<Key, Value>> node, Key key, Value value);
	static std::shared_ptr<Node<Key, Value>> rotateLeft(std::shared_ptr<Node<Key, Value>> node);
	static std::shared_ptr<Node<Key, Value>> rotateRight(std::shared_ptr<Node<Key, Value>> node);
	static std::shared_ptr<Node<Key, Value>> balance(std::shared_ptr<Node<Key, Value>> node);
	static std::shared_ptr<Node<Key, Value>> findMin(std::shared_ptr<Node<Key, Value>> node);
	static std::shared_ptr<Node<Key, Value>> removeMin(std::shared_ptr<Node<Key, Value>> node);
	static std::shared_ptr<Node<Key, Value>> remove(std::shared_ptr<Node<Key, Value>> node, Key key);
	static Value find(std::shared_ptr<Node<Key, Value>> node, Key key);
public:
	void insert(Key key, Value value);
	void remove(Key key);
	Value find(Key key);
};


template<typename Key, typename Value>
std::shared_ptr<Node<Key, Value>> AVLTree<Key, Value>::appendTo(std::shared_ptr<Node<Key, Value>> node, Key key, Value value)
{
	if (!node) {
		return std::make_shared<Node<Key, Value>>(key, value);
	}
	else if (node->key == key) {
		node->value = value;
		return node;
	}
	else if (key < node->key) {
		node->left = appendTo(node->left, key, value);
	}
	else {
		node->right = appendTo(node->right, key, value);
	}
	return balance(node);
}

template<typename Key, typename Value>
std::shared_ptr<Node<Key, Value>> AVLTree<Key, Value>::rotateLeft(std::shared_ptr<Node<Key, Value>> node)
{
	std::shared_ptr<Node<Key, Value>> q = node->right;
	node->right = q->left;
	q->left = node;
	node->fixHeight();
	q->fixHeight();
	return q;
}

template<typename Key, typename Value>
std::shared_ptr<Node<Key, Value>> AVLTree<Key, Value>::rotateRight(std::shared_ptr<Node<Key, Value>> node)
{
	std::shared_ptr<Node<Key, Value>> q = node->left;
	node->left = q->right;
	q->right = node;
	node->fixHeight();
	q->fixHeight();
	return q;
}

template<typename Key, typename Value>
std::shared_ptr<Node<Key, Value>> AVLTree<Key, Value>::balance(std::shared_ptr<Node<Key, Value>> node)
{
	node->fixHeight();
	int16_t BFactor = node->getBFactor();
	if (BFactor == 2)
	{
		if (node->right->getBFactor() < 0)
			node->right = rotateRight(node->right);
		return rotateLeft(node);
	}
	else if (BFactor == -2)
	{
		if (node->left->getBFactor() > 0)
			node->left = rotateLeft(node->left);
		return rotateRight(node);
	}
	return node;
}

template<typename Key, typename Value>
std::shared_ptr<Node<Key, Value>> AVLTree<Key, Value>::findMin(std::shared_ptr<Node<Key, Value>> node)
{
	return node->left ? findMin(node->left) : node;
}

template<typename Key, typename Value>
std::shared_ptr<Node<Key, Value>> AVLTree<Key, Value>::removeMin(std::shared_ptr<Node<Key, Value>> node)
{
	if (!node->left) {
		return node->right;
	}
	node->left = removeMin(node->left);
	return balance(node);
}

template<typename Key, typename Value>
std::shared_ptr<Node<Key, Value>> AVLTree<Key, Value>::remove(std::shared_ptr<Node<Key, Value>> node, Key key)
{
	if (!node) {
		return 0;
	}
	if (key < node->key) {
		node->left = remove(node->left, key);
	}
	else if (key > node->key) {
		node->right = remove(node->right, key);
	}
	else
	{
		std::shared_ptr<Node<Key, Value>> l = node->left;
		std::shared_ptr<Node<Key, Value>> r = node->right;
		if (!r) return l;
		std::shared_ptr<Node<Key, Value>> min = findMin(r);
		min->right = removeMin(r);
		min->left = l;
		return balance(min);
	}

	return balance(node);
}

template<typename Key, typename Value>
Value AVLTree<Key, Value>::find(std::shared_ptr<Node<Key, Value>> node, Key key)
{
	if (!node) {
		return Value();
	}
	else if (node->key == key) {
		return node->value;
	}
	else if (key < node->key) {
		return find(node->left, key);
	}
	else {
		return find(node->right, key);
	}
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::insert(Key key, Value value)
{
	{
		if (!root) {
			root = std::make_shared<Node<Key, Value>>(key, value);
		}
		else {
			root = appendTo(root, key, value);
		}
	}
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::remove(Key key)
{
	root = remove(root, key);
}

template<typename Key, typename Value>
Value AVLTree<Key, Value>::find(Key key)
{
	return find(root, key);
}

template <typename Key, typename Value>
class Map {
private:
	std::shared_ptr<AVLTree<Key, Value>> tree;
public:
	void insert(Key key, Value value);
	void erase(Key key);
	Value find(Key key);
	Map();
};



template<typename Key, typename Value>
void Map<Key, Value>::insert(Key key, Value value)
{
	tree->insert(key, value);
}

template<typename Key, typename Value>
void Map<Key, Value>::erase(Key key)
{
	tree->remove(key);
}

template<typename Key, typename Value>
Value Map<Key, Value>::find(Key key)
{
	return tree->find(key);
}

template<typename Key, typename Value>
Map<Key, Value>::Map()
{
	this->tree = std::make_shared<AVLTree<Key, Value>>();
}
