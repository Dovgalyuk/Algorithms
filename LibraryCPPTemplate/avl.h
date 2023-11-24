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

    //�������� ���� ����-��������
    void insert(const string& key, const string& value) 
    {
        root = insertInternal(root, key, value);
    }

    //����� �������� �� �����
    string find(const string& key) 
    {
        AVLNode* node = findInternal(root, key);
        return node == nullptr ? "" : node->value;
    }

    //������� �������� �� �����
    void remove(const string& key) 
    {
        root = removeInternal(root, key);
    }

    //���������� ��� �������� ���� �����
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
            return -1; //������������������ ����� ���������

        int rightHeight = checkBalance(node->right);
        if (rightHeight == -1)
            return -1; //������������������ ������ ���������

        if (abs(leftHeight - rightHeight) > 1) 
        {
            return -1; //������� ���� ���������������
        }

        return max(leftHeight, rightHeight) + 1; //���������� ������ ����
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

        //���������� ��������
        x->right = y;
        y->left = T2;

        //���������� �����
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        //���������� ����� ������
        return x;
    }

    AVLNode* leftRotate(AVLNode* x) 
    {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        //���������� ��������
        y->left = x;
        x->right = T2;

        //���������� �����
        x->height = std::max(height(x->left), height(x->right)) + 1;
        y->height = std::max(height(y->left), height(y->right)) + 1;

        //���������� ����� ������
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
            return node; //���� ��� ����������
        }

        //�������� ������ ����� ����
        node->height = 1 + max(height(node->left), height(node->right));

        //�������� ������� � ���������� ��������, ���� ����������
        int balance = getBalance(node);
        //�����-����� ��������
        if (balance > 1 && key < node->left->key) 
        {
            return rightRotate(node);
        }
        //������-������ ��������
        if (balance < -1 && key > node->right->key) 
        {
            return leftRotate(node);
        }
        //�����-������ ��������
        if (balance > 1 && key > node->left->key) 
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        //������-����� ��������
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
        //��� 1: ������� �������� BST
        if (node == nullptr)
            return node;

        //���� ����, ������� ����� �������, ������, ��� ���� ����, 
        //�� �� ��������� � ����� ���������
        if (key < node->key)
            node->left = removeInternal(node->left, key);

        //���� ����, ������� ����� �������, ������, ��� ���� ����, 
        //�� �� ��������� � ������ ���������
        else if (key > node->key)
            node->right = removeInternal(node->right, key);

        //���� ���� ��������� � ������ ����, �� ��� ����, ������� ����� �������
        else 
        {
            //���� � ����� �������� ��� ��� ��������
            if ((node->left == nullptr) || (node->right == nullptr)) 
            {
                AVLNode* temp = node->left ? node->left : node->right;

                //��� ��������
                if (temp == nullptr) 
                {
                    temp = node;
                    node = nullptr;
                }
                else 
                {
                    //���� �������
                    *node = *temp;//����������� �����������
                }
                delete temp;
            }
            else 
            {
                //���� � ����� ���������: ��������� ���� � ���������� ������ � ������ ���������
                AVLNode* temp = minValueNode(node->right);

                //����������� ������ �� ���� � ���������� ������ � ���� ����
                node->key = temp->key;
                node->value = temp->value;

                //�������� ���� � ���������� ������
                node->right = removeInternal(node->right, temp->key);
            }
        }

        //���� ������ ����� ������ ���� ����, �� ���������� ���
        if (node == nullptr)
            return node;

        //��� 2: ���������� ������ �������� ����
        node->height = 1 + max(height(node->left), height(node->right));

        //��� 3: �������� ������� ����
        int balance = getBalance(node);

        //���� ���� ���� ������������������, �� ���� 4 ������

        //�����-����� ��������
        if (balance > 1 && getBalance(node->left) >= 0)
            return rightRotate(node);

        //�����-������ ��������
        if (balance > 1 && getBalance(node->left) < 0) 
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        //������-������ ��������
        if (balance < -1 && getBalance(node->right) <= 0)
            return leftRotate(node);

        //������-����� ��������
        if (balance < -1 && getBalance(node->right) > 0) 
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    //��������������� ������� ��� ���������� ���� � ���������� ������
    AVLNode* minValueNode(AVLNode* node) 
    {
        AVLNode* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }
};

#endif