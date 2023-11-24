#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <string>
#include <algorithm>
#include "array.h"

using namespace std;

class AVLNode 
{
public:
    string key;
    string value;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(string key, string value): key(key), value(value), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree 
{
public:
    AVLTree() : root(nullptr) {}

    bool isBalanced() 
    {
        return checkBalance(root) != -1;
    }

    //Добавить пару ключ-значение
    void insert(const string& key, const string& value) 
    {
        root = insertInternal(root, key, value);
    }

    //Найти значение по ключу
    string find(const string& key) 
    {
        AVLNode* node = findInternal(root, key);
        return node == nullptr ? "" : node->value;
    }

    //Удалить значение по ключу
    void remove(const string& key) 
    {
        root = removeInternal(root, key);
    }

    //Деструктор для удаления всех узлов
    ~AVLTree() 
    {
        destroyTree(root);
    }

private:
    AVLNode* root;
    int checkBalance(AVLNode* node) 
    {
        if (node == nullptr) 
        {
            return 0;
        }

        int leftHeight = checkBalance(node->left);
        if (leftHeight == -1)
            return -1; //Несбалансированное левое поддерево

        int rightHeight = checkBalance(node->right);
        if (rightHeight == -1)
            return -1; //Несбалансированное правое поддерево

        if (abs(leftHeight - rightHeight) > 1) 
        {
            return -1; //Текущий узел несбалансирован
        }

        return max(leftHeight, rightHeight) + 1; //Возвращаем высоту узла
    }

    int height(AVLNode* node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        return node->height;
    }

    int getBalance(AVLNode* node)
    {
        if (node == nullptr) 
        {
            return 0;
        }
        return height(node->left) - height(node->right);
    }

    AVLNode* rightRotate(AVLNode* y) 
    {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        //Выполнение вращения
        x->right = y;
        y->left = T2;

        //Обновление высот
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        //Возвращаем новый корень
        return x;
    }

    AVLNode* leftRotate(AVLNode* x) 
    {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        //Выполнение вращения
        y->left = x;
        x->right = T2;

        //Обновление высот
        x->height = std::max(height(x->left), height(x->right)) + 1;
        y->height = std::max(height(y->left), height(y->right)) + 1;

        //Возвращаем новый корень
        return y;
    }

    void destroyTree(AVLNode* node) 
    {
        if (node != nullptr) 
        {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    AVLNode* findInternal(AVLNode* node, const string& key)
    {
        if (node == nullptr || node->key == key) 
        {
            return node;
        }

        if (key < node->key) 
        {
            return findInternal(node->left, key);
        }
        else 
        {
            return findInternal(node->right, key);
        }
    }

    AVLNode* insertInternal(AVLNode* node, const string& key, const string& value)
    {
        if (node == nullptr)
        {
            return new AVLNode(key, value);
        }

        if (key < node->key)
        {
            node->left = insertInternal(node->left, key, value);
        }
        else if (key > node->key)
        {
            node->right = insertInternal(node->right, key, value);
        }
        else
        {
            return node; //ключ уже существует
        }

        //Обновить высоту этого узла
        node->height = 1 + max(height(node->left), height(node->right));

        //Проверка баланса и выполнение вращений, если необходимо
        int balance = getBalance(node);
        //Левое-левое вращение
        if (balance > 1 && key < node->left->key) 
        {
            return rightRotate(node);
        }
        //Правое-правое вращение
        if (balance < -1 && key > node->right->key) 
        {
            return leftRotate(node);
        }
        //Левое-правое вращение
        if (balance > 1 && key > node->left->key) 
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        //Правое-левое вращение
        if (balance < -1 && key < node->right->key) 
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    bool isAVLTreeValid(AVLNode* node) 
    {
        if (node == nullptr) {
            return true;
        }

        int leftHeight = height(node->left);
        int rightHeight = height(node->right);

        if (abs(leftHeight - rightHeight) > 1) {
            return false;
        }

        bool isLeftValid = isAVLTreeValid(node->left);
        bool isRightValid = isAVLTreeValid(node->right);

        return isLeftValid && isRightValid;
    }


    AVLNode* removeInternal(AVLNode* node, const string& key)
    {
        //Шаг 1: Обычное удаление BST
        if (node == nullptr)
            return node;

        //Если ключ, который нужно удалить, меньше, чем ключ узла, 
        //то он находится в левом поддереве
        if (key < node->key)
            node->left = removeInternal(node->left, key);

        //Если ключ, который нужно удалить, больше, чем ключ узла, 
        //то он находится в правом поддереве
        else if (key > node->key)
            node->right = removeInternal(node->right, key);

        //Если ключ совпадает с ключом узла, то это узел, который нужно удалить
        else 
        {
            //Узлы с одним потомком или без потомков
            if ((node->left == nullptr) || (node->right == nullptr)) 
            {
                AVLNode* temp = node->left ? node->left : node->right;

                //Нет потомков
                if (temp == nullptr) 
                {
                    temp = node;
                    node = nullptr;
                }
                else 
                {
                    //Один потомок
                    *node = *temp;//Копирование содержимого
                }
                delete temp;
            }
            else 
            {
                //Узел с двумя потомками: Получение узла с наименьшим ключом в правом поддереве
                AVLNode* temp = minValueNode(node->right);

                //Копирование данных из узла с наименьшим ключом в этот узел
                node->key = temp->key;
                node->value = temp->value;

                //Удаление узла с наименьшим ключом
                node->right = removeInternal(node->right, temp->key);
            }
        }

        //Если дерево имело только один узел, то возвращаем его
        if (node == nullptr)
            return node;

        //Шаг 2: Обновление высоты текущего узла
        node->height = 1 + max(height(node->left), height(node->right));

        //Шаг 3: Проверка баланса узла
        int balance = getBalance(node);

        //Если узел стал несбалансированным, то есть 4 случая

        //Левое-левое вращение
        if (balance > 1 && getBalance(node->left) >= 0)
            return rightRotate(node);

        //Левое-правое вращение
        if (balance > 1 && getBalance(node->left) < 0) 
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        //Правое-правое вращение
        if (balance < -1 && getBalance(node->right) <= 0)
            return leftRotate(node);

        //Правое-левое вращение
        if (balance < -1 && getBalance(node->right) > 0) 
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    //Вспомогательная функция для нахождения узла с наименьшим ключом
    AVLNode* minValueNode(AVLNode* node) 
    {
        AVLNode* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }
};

#endif