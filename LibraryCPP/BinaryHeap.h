#ifndef BINARYHEAP_H
#define BINARYHEAP_H


#include <vector>
using namespace std;

struct Heap
{
public:

    vector<int> tree;

    void Insert(int x)
    {
        tree.push_back(x);
        sift_up(GetSize() - 1);
    }

    int GetMax()
    {
        if (GetSize() > 0)
        {
            return tree[0];
        }

    }

    void RemoveMax()
    {
        if (GetSize() > 0)
        {
            tree[0] = tree.back();
            tree.pop_back();
            sift_down(0);
        }

    }

    bool Empty()
    {
        return GetSize() == false;
    }

private:
 
    void sift_up(int v)
    {
        if (v == 0)
        {
            return;    
        }

        if (tree[v / 2] < tree[v]) {
            swap(tree[v], tree[v / 2]);
            sift_up(v / 2);
        }
    }

    void sift_down(int v)
    {
        if (v * 2 >= GetSize())
        {
            return;     
        }

        
        int max_idx;
        if (v * 2 + 1 == GetSize())
        {                                      
            max_idx = v * 2;
        }
        else if (tree[v * 2] >= tree[v * 2 + 1])
        {
            max_idx = v * 2;
        }
        else
        {
            max_idx = v * 2 + 1;
        }

        if (tree[v] < tree[max_idx])
        {
            swap(tree[v], tree[max_idx]);
            sift_down(max_idx);
        }
    }

    int GetIndex(int data)
    {
        for (int i = 0; i < GetSize(); i++)
        {
            if (data == tree[i])
            {
                return i;
            }
        }
        return 0;
    }

    int GetSize()
    {
        return tree.size();
    }
};
#endif